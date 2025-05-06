/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   main.c
 * @Version:
 *
 * @Date:
 *
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "SACM_A1801_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"

#include "Touch_Sensor.h"
#include "Touch_User.h"
#include "TouchProbe_Driver.h"

#define C_TouchSleep	0		//1 TouchSleep Mode

void SleepService(void);
/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) SACM_A1801_WORKING_RAM A1801WorkingRam;
__align(4) SACM_A1801_TEMP_RAM A1801TempBuffer;
__align(4) SACM_A1801_PCM_BUFFER A1801PcmBuffer;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_A1801_WORKING_RAM A1801WorkingRam;
__attribute__ ((aligned (4))) SACM_A1801_TEMP_RAM A1801TempBuffer;
__attribute__ ((aligned (4))) SACM_A1801_PCM_BUFFER A1801PcmBuffer;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint16_t SpeechNum = 0;
int16_t A1801PlayIdx = 1;
int8_t PlayCon = 0;
int8_t SwVolGain = 9;


uint16_t SleepFlag = 0;
uint8_t WakeFlag = 0;
uint8_t WakeCnt = 0;
uint16_t SleepWait = 0;

uint32_t ScanedKey=0;
uint32_t CTSResult=0;
uint32_t CTSResultPre=0;

/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	           // SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV4);
	//SPIFC_EN4B();																           // SPIFC enable 4 bytes.
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		             // SPIFC auto mode.
	SPIFC_AutoMode(SPIFC_2IO_MODE);					                 // SPIFC auto mode.
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     // Calibrate SPIFC clock timing.
	{
		while(1);                                              // SPIFC clock timing calibration fail!
	}

	SpeechNum = A1801_User_GetA1801Num();
	SACM_A1801_Initial(&A1801WorkingRam, &A1801TempBuffer, &A1801PcmBuffer);

	APP_SwVolCtrl_Init();                                    // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, SwVolGain);
	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init.

	CTS_Initial();
	CTS_FilterSetting(0);
	CTS_Scan();

	TP_Initial();
	TP_Start();
	SleepFlag = 0;
#if C_TouchSleep == 1
	TIMEBASE_Open(TB_CLK_SEL_IOSC32K);
	TIMEBASE_EnableInt(TB_INT_2HZ);
	NVIC_EnableIRQ(TIMEBASE_IRQn);
#endif

  while(1)
	{
		WDT_Clear();
		SACM_A1801_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_A1801_CheckCpuOverload() != 0)
		{
			SACM_A1801_ClearCpuOverload();
		}

		CTS_ServiceLoop();
		SleepService();
		CTSResult = (uint16_t )CTS_GetResult();
		ScanedKey = CTSResult & ~CTSResultPre;
		CTSResultPre = CTSResult;
		switch(ScanedKey)
		{
		  case 0x01:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(1), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);

        break;

			case 0x02:

				SACM_A1801_Play(A1801_User_GetA1801StartAddr(2), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);

				break;

			case 0x04:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(3), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x08:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(4), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			  break;

			case 0x10:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(5), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

      case 0x20:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(6), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x40:
            #if C_TouchSleep == 1
				CTS_Pause();
				SleepFlag = 1;
				SleepWait = 2;
            #else
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(7), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
            #endif
			  break;

			case 0x80:
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(8), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;
	  }

		if((PlayCon != 0) && (SACM_A1801_Check_Con() == 0))
		{
			SACM_A1801_Play_Con(A1801_User_GetA1801StartAddr(A1801PlayIdx++), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			A1801PlayIdx = A1801PlayIdx > SpeechNum ? 1 : A1801PlayIdx;
		}
	}
}

/**
 * @brief
 *   TimeBase IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void TIMEBASE_IRQHandler(void)
{
	if((TIMEBASE->STS & TIMEBASE_STS_2HZ_INTF_FLAG) != 0)
	{
    TIMEBASE->STS = TIMEBASE_STS_2HZ_INTF_FLAG;	                                              // Clear TimeBase 2Hz interrupt flag
		WakeFlag = 1;
		WakeCnt += 1;
		if(SleepWait) SleepWait -= 1;
	}
}
void SleepService(void)
{
#if C_TouchSleep == 1
		if((SleepFlag==1) && (SleepWait == 0))
		{
			while(CTS_PauseStatus()!=0x8000)
			{
				CTS_Pause();
				WDT_Clear();
				SACM_A1801_ServiceLoop();
				CTS_ServiceLoop();
			}
			if(CTS_PauseStatus()==0x8000)			//
			{
					DAC_Close();
					CTS_BeforeSleep();
					SPIFC_EnhanModeReset();
					SPIFC_Cmd(0xB9);						//Flash deep power down
					WakeFlag = 0;
					SCB->SCR = SCB_SCR_SLEEPDEEP_Msk; // Deep Sleep Mode
					__WFI();  // Sleep Mode

					SPIFC_EnhanModeReset();
					SPIFC_Cmd(0xAB);						// release DP
					SPIFC_AutoMode(SPIFC_4IO_MODE);
				if(WakeFlag==0)		//Touch wakeup
				{
					//open DSADC Reg33
					MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY1);
					MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);        // SMU nulock
					MODIFY_REG(ACU->REG33_CTRL, ACU_REG33_CTRL_DSADC_REG_EN_MSK, ACU_REG33_CTRL_DSADC_REG_EN_ENABLE);       //REG33 pins.
					MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);	                             // SMU lock

					SleepFlag =0;
					CTS_Pause_Clr();		//Touch Wake Up
					F_Touch_User_Init();
					CTS_Scan();
					SACM_A1801_Initial(&A1801WorkingRam, &A1801TempBuffer, &A1801PcmBuffer);
				}

				if(WakeCnt>4)		//RTC Wakeup 2.5S Scan one loop
				{
					WakeCnt = 0;
					F_Touch_User_Init();
					CTS_Scan();
					CTS_Pause();			//Touch only scan one loop
				}

			}
		}
#endif
}
