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
#include "SACM_A3400Pro_CH2_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#define Aligned4B __align(4)
#elif defined(__GNUC__)
#define Aligned4B __attribute__ ((aligned (4)))
#endif

Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProWorkingRam;
Aligned4B int16_t												A3400ProBuffer[2 * A3400PRO_FRAME_SIZE];
Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProCh2WorkingRam;
Aligned4B int16_t												A3400ProCh2Buffer[2 * A3400PRO_CH2_FRAME_SIZE];
KEYSCAN_WORKING_RAM 										KeyScanWorkingRam;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  uint32_t ScanedKey;
  uint16_t A3400ProNum = 0;
  int16_t A3400ProPlayIdx = 1;
  int16_t A3400ProCh2PlayIdx = 1;
  int8_t PlayCon = 1;
  int8_t PauseFlag = 0;
	int8_t SwVolGain = 9;

  SystemInit();

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	 						// SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV1);
	SPIFC_AutoMode(SPIFC_4IO_MODE);					     							// SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     	// Calibrate SPIFC clock timing.
	{
		while(1);                                              	// SPIFC clock timing calibration fail!
	}

	/*
	 * A3400Pro init
	 */
	A3400ProNum = GetA3400ProNum();
	SACM_A3400Pro_Initial(&A3400ProWorkingRam, &A3400ProBuffer[0], A3400PRO_FRAME_SIZE);
	SACM_A3400Pro_CH2_Initial(&A3400ProCh2WorkingRam, &A3400ProCh2Buffer[0], A3400PRO_CH2_FRAME_SIZE);
	
	SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
  SACM_A3400Pro_CH2_Play(GetA3400ProCh2StartAddr(A3400ProCh2PlayIdx), A3400PRO_DAC_CH1, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);

	APP_SwVolCtrl_Init();                                    	// Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, SwVolGain);
	APP_SwVolCtrl_SetVolGain(1, SwVolGain);

	/*
	 * KeyScan init
	 */
	KeyScan_Initial(&KeyScanWorkingRam);           						// key scan init

  while(1)
	{
		WDT_Clear();
		KeyScan_ServiceLoop();
 		SACM_A3400Pro_ServiceLoop();
 		SACM_A3400Pro_CH2_ServiceLoop();

		if(SACM_A3400Pro_CheckCpuOverload() != 0)
		{
			SACM_A3400Pro_ClearCpuOverload();
		}

		if(SACM_A3400Pro_CH2_CheckCpuOverload() != 0)
		{
			SACM_A3400Pro_CH2_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                 						// IOA0+VDD: Stop
				PlayCon = 0;
				SACM_A3400Pro_Stop();
			  SACM_A3400Pro_CH2_Stop();
        break;

			case 0x02:                                 						// IOA1+VDD: A3400Pro play next song
				PlayCon = 0;
				SACM_A3400Pro_Stop();
			  A3400ProPlayIdx = ++A3400ProPlayIdx > A3400ProNum ? 1 : A3400ProPlayIdx;
				SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
				break;

			case 0x04:                                 						// IOA2+VDD: A3400Pro_CH2 play next song
				PlayCon = 0;
				SACM_A3400Pro_CH2_Stop();
			  A3400ProCh2PlayIdx = ++A3400ProCh2PlayIdx > A3400ProNum ? 1 : A3400ProCh2PlayIdx;
				SACM_A3400Pro_CH2_Play(GetA3400ProCh2StartAddr(A3400ProCh2PlayIdx), A3400PRO_DAC_CH1, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
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
				  SACM_A3400Pro_CH2_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_A3400Pro_Resume();
				  SACM_A3400Pro_CH2_Resume();
				}
				break;

      case 0x20:
				SwVolGain = ++SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);            	// Set A3400Pro CH1 software volume gain
			  APP_SwVolCtrl_SetVolGain(1, SwVolGain);            	// Set A3400Pro CH2 software volume gain
				break;

			case 0x40:
			  SwVolGain = --SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);            	// Set A3400Pro CH1 software volume gain
			  APP_SwVolCtrl_SetVolGain(1, SwVolGain);            	// Set A3400Pro CH2 software volume gain
			  break;

			case 0x80:
				break;
	  }
		if((PlayCon != 0) && (SACM_A3400Pro_Check_Con() == 0))
		{
			SACM_A3400Pro_Play_Con(GetA3400ProStartAddr(A3400ProPlayIdx++), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
			A3400ProPlayIdx = A3400ProPlayIdx > A3400ProNum ? 1 : A3400ProPlayIdx;
		}
	}
}
