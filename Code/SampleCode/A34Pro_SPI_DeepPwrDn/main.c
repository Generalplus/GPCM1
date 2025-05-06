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
#include "SACM_A3400Pro_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"

#define SPI_FLASH_DP                   (0xB9)     // Deep power down mode
#define SPI_FLASH_RDP                  (0xAB)     // Release from deep power down mode


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#define Aligned4B __align(4)
#elif defined(__GNUC__)
#define Aligned4B __attribute__ ((aligned (4)))
#endif

Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProWorkingRam;
Aligned4B int16_t  											A3400ProBuffer[2 * A3400PRO_FRAME_SIZE];
KEYSCAN_WORKING_RAM 										KeyScanWorkingRam;

uint32_t iCount;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  uint32_t ScanedKey;
  uint16_t A3400ProNum = 0;
  int16_t A3400ProPlayIdx = 1;
  int8_t PlayCon = 1;
  int8_t PauseFlag = 0;
	int8_t SwVolGain = 9;

  SystemInit();

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	 						// SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV2);
	SPIFC_AutoMode(SPIFC_2IO_MODE);					     							// SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     	// Calibrate SPIFC clock timing.
	{
		while(1);                                              	// SPIFC clock timing calibration fail!
	}

	/*
	 * KeyScan init
	 */
	KeyScan_Initial(&KeyScanWorkingRam);           						// key scan init

  /*
	 * KeyChange wakeup init
	 */
  GPIO_SetMode(GPIOA, BIT8, GPIO_MODE_OUTPUT);          // IOA.8 = Output pin
  MODIFY_REG(GPIOA->OBUF, BIT8, 0);

  /*
	 * KeyChange wakeup init
	 * - IOA[2:0]	key change can wake up IC
	 */
	GPIO_KeyChangeWakeupIoSel(KEYCHG_WAKEUP_EN_IOA0 | KEYCHG_WAKEUP_EN_IOA1 | KEYCHG_WAKEUP_EN_IOA2);
	GPIO_KeyChangeWakeupIntEnable();
  NVIC_EnableIRQ(KEYCHG_IRQn);

	/*
	 * A3400Pro init
	 */
	A3400ProNum = GetA3400ProNum();
	SACM_A3400Pro_Initial(&A3400ProWorkingRam, &A3400ProBuffer[0], A3400PRO_FRAME_SIZE);
	SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0 , A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);

	APP_SwVolCtrl_Init();
	APP_SwVolCtrl_SetVolGain(0, SwVolGain);

  while(1)
	{
 		SACM_A3400Pro_ServiceLoop();
		KeyScan_ServiceLoop();
		WDT_Clear();

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                 						// IOA0+VDD: Deep sleep mode
				PlayCon = 0;
				SACM_A3400Pro_Stop();

        for(iCount = 0; iCount < 1000000; iCount++)
        {
          GPIOA_OBIT->OBIT08 = 0xFFFFFFFF;
          WDT_Clear();
        }
        GPIOA_OBIT->OBIT08 = 0x00000000;

        iCount = GPIOA->IDATA;	                             // Latch IOA DATA
        GoToSleep();
        break;

			case 0x02:                                 						// IOA1+VDD: A3400Pro play next song
				PlayCon = 0;
				SACM_A3400Pro_Stop();
			  A3400ProPlayIdx = ++A3400ProPlayIdx > A3400ProNum ? 1 : A3400ProPlayIdx;
				SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0 , A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
				break;

			case 0x04:                                 						// IOA2+VDD: A3400Pro play prev song
				PlayCon = 0;
				SACM_A3400Pro_Stop();
			  A3400ProPlayIdx = --A3400ProPlayIdx < 1 ? A3400ProNum : A3400ProPlayIdx;
				SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0 , A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
				break;

			case 0x08:                                 						// IOA3+VDD: A3400Pro Play concatenate
				PlayCon = 1;
			  SACM_A3400Pro_Stop();
			  A3400ProPlayIdx = 1;
			  SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx++), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                 						// IOA4+VDD:	Pause/Resume
				if(PauseFlag == 0)
				{
					PauseFlag = 1;
				  SACM_A3400Pro_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_A3400Pro_Resume();
				}
				break;

      case 0x20:
				SwVolGain = ++SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
				break;

			case 0x40:
			  SwVolGain = --SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
			  break;

			case 0x80:
				break;
	  }
		if((PlayCon != 0) && (SACM_A3400Pro_Check_Con() == 0))
		{
			A3400ProPlayIdx = ++A3400ProPlayIdx > A3400ProNum ? 1 : A3400ProPlayIdx;
			SACM_A3400Pro_Play_Con(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
		}
	}
}

/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/
void GoToSleep(void)
{
SPIFC_EnhanModeReset();
SPIFC_Cmd(SPI_FLASH_DP);						//Flash deep power down

MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);
MODIFY_REG(ACU->REG33_CTRL, ACU_REG33_CTRL_SLEEP_EN_MSK, ACU_REG33_CTRL_SLEEP_EN_ENABLE);
MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);

// Latch GPIOA
iCount = GPIOA->IDATA;              // Latch IOA DATA for test
SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;   // Deep Sleep Mode

// Wake up process
__WFE();
__WFE();

MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);
MODIFY_REG(ACU->REG33_CTRL, ACU_REG33_CTRL_SLEEP_EN_MSK, ACU_REG33_CTRL_SLEEP_EN_DISABLE);
MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);

SPIFC_EnhanModeReset();
SPIFC_Cmd(SPI_FLASH_RDP);                     			// release DP
SPIFC_AutoMode(SPIFC_2IO_MODE);
}


/**
 * @brief
 *   KeyChange IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void KEYCHG_IRQHandler(void)
{
	IOFUNC->STS = GPIOFUNC_STS_INTF_FLAG;
}

