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
#include "SACM_DVR1801_User.h"
#include "SACM_VC3_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
 #if defined(__CC_ARM)
__align(4) SACM_DVR1801_WORKING_RAM gDvr1801WorkingRam;
__align(4) SACM_DVR1801_TEMP_RAM gDvr1801TempBuffer;
__align(4) SACM_DVR1801_PCM_BUFFER Dvr1801PcmBuffer;
__align(4) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam;
__align(4) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam2;
__align(4) SACM_VC3_VM_KERNEL_RAM Vc3VmKernelWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_DVR1801_WORKING_RAM gDvr1801WorkingRam;
__attribute__ ((aligned (4))) SACM_DVR1801_TEMP_RAM gDvr1801TempBuffer;
__attribute__ ((aligned (4))) SACM_DVR1801_PCM_BUFFER Dvr1801PcmBuffer;
__attribute__ ((aligned (4))) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam;
__attribute__ ((aligned (4))) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam2;
__attribute__ ((aligned (4))) SACM_VC3_KERNEL_RAM Vc3VmKernelWorkingRam;
#endif

KEYSCAN_WORKING_RAM KeyScanWorkingRam;
uint32_t ScanedKey;
uint16_t A1801Num = 0;
int16_t A1801PlayIdx = 1;
int8_t PlayCon = 0;
int8_t Vc3ChangeSpeed = -6;
int16_t Dvr1801SwVolGain = 6;
int16_t Vc3SwVolGain = 13;
uint8_t Vc3EffectEn = 0;


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
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV1);
	//SPIFC_EN4B();																           // SPIFC enable 4 bytes.
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		             // SPIFC auto mode.
	SPIFC_AutoMode(SPIFC_2IO_MODE);					                 // SPIFC auto mode.
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     // Calibrate SPIFC clock timing.
	{
		while(1);                                              // SPIFC clock timing calibration fail!
	}

	A1801Num = GetA1801Num();
	SACM_DVR1801_Initial(&gDvr1801WorkingRam, &gDvr1801TempBuffer, &Dvr1801PcmBuffer);

	/*
	 * Initialize VC3: speed control + robot + echo
	 */
	SACM_VC3_Mode(VC3_CHANGE_SPEED_MODE, &Vc3KernelWorkingRam);
	SACM_VC3_ChangeSpeedMode_SetSpeed(Vc3ChangeSpeed);
	SACM_VC3_Mode(VC3_VM_ROBOT_EFFECT1_MODE, &Vc3VmKernelWorkingRam);
	SACM_VC3_Mode(VC3_ECHO_MODE, &Vc3KernelWorkingRam2);
  SACM_VC3_EchoMode_SetGain(4);

	APP_SwVolCtrl_Init();                                    // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, Dvr1801SwVolGain);
	APP_SwVolCtrl_SetVolGain(1, Vc3SwVolGain);

	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

  while(1)
	{
		WDT_Clear();
		SACM_DVR1801_ServiceLoop();
		KeyScan_ServiceLoop();

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Stop
				PlayCon = 0;
				SACM_DVR1801_Stop();
        break;

			case 0x02:                                           // IOA1+VDD: Play concatenate
			  SACM_DVR1801_Stop();

			  //SPIFC_EnhanModeReset();
			  //SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);
			  SPIFC_AutoMode(SPIFC_2IO_MODE);

			  PlayCon = 1;
			  A1801PlayIdx = 1;
			  SACM_DVR1801_Play(GetA1801StartAddr(A1801PlayIdx++), DVR1801_DAC_CH0, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
			  break;

      case 0x04:                                           // IOA2+VDD: VC3 Volume up
				Vc3SwVolGain = ++Vc3SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : Vc3SwVolGain;
			  APP_SwVolCtrl_SetVolGain(1, Vc3SwVolGain);
				break;

			case 0x08:                                           // IOA3+VDD: VC3 Volume down
			  Vc3SwVolGain = --Vc3SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : Vc3SwVolGain;
			  APP_SwVolCtrl_SetVolGain(1, Vc3SwVolGain);
			  break;

			case 0x10:                                           // IOA4+VDD: VC3 effect enable/disable
				if(Vc3EffectEn == 0)
				{
					Vc3EffectEn = 1;
					A1801_Vc3EffectEnable();
				}
				else
				{
					Vc3EffectEn = 0;
					A1801_Vc3EffectDisable();
				}
			  break;

			case 0x20:                                           // IOA5+VDD: Speed control
				Vc3ChangeSpeed = ++Vc3ChangeSpeed > MAX_VC3_SPEED_CTRL_LIMIT ? MIN_VC3_SPEED_CTRL_LIMIT : Vc3ChangeSpeed;
			  SACM_VC3_ChangeSpeedMode_SetSpeed(Vc3ChangeSpeed);
				break;

			case 0x40:                                           // IOA6+VDD: Record
				PlayCon = 0;
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  SACM_DVR1801_Initial(&gDvr1801WorkingRam, &gDvr1801TempBuffer, &Dvr1801PcmBuffer);
				SPIFC_BlockErase(0x00200000);
			  SPIFC_BlockErase(0x00210000);
			  SACM_DVR1801_Rec((int16_t *) 0x00200000, DVR1801_RECORD_BITRATE_16000);
			  break;

			case 0x80:                                           // IOA7+VDD: Play recorded voice
				PlayCon = 0;
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  //SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);
			  SPIFC_AutoMode(SPIFC_2IO_MODE);
			  SACM_DVR1801_Initial(&gDvr1801WorkingRam, &gDvr1801TempBuffer, &Dvr1801PcmBuffer);
			  SACM_DVR1801_Play((int16_t *)0x04200000, DVR1801_DAC_CH0, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
				break;
	  }

		if((PlayCon != 0) && (SACM_DVR1801_Check_Con() == 0))
		{
			SACM_DVR1801_Play_Con(GetA1801StartAddr(A1801PlayIdx++), DVR1801_DAC_CH0, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
			if(A1801PlayIdx > A1801Num)
		  {
				PlayCon = 0;
			}
		}
	}
}
