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
#include "SACM_DVRIMA_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_DVRIMA_WORKING_RAM DVRIMAWorkingRam;
__attribute__ ((aligned (4))) SACM_DVRIMA_TEMP_RAM DVRIMATempBuffer;
__attribute__ ((aligned (4))) SACM_DVRIMA_PCM_BUFFER DVRIMAPcmBuffer;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint16_t SpeechNum = 0;
int16_t DVRIMAPlayIdx = 1;
int8_t PlayCon = 0;
int8_t SwVolGain = 9;


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

	SpeechNum = DVRIMA_User_GetDVRIMANum();
	SACM_DVRIMA_Initial(&DVRIMAWorkingRam, &DVRIMATempBuffer, &DVRIMAPcmBuffer);

	APP_SwVolCtrl_Init();                                    // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, SwVolGain);
	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init.

  SACM_DVRIMA_Play(DVRIMA_User_GetDVRIMAStartAddr(DVRIMAPlayIdx), DVRIMA_DAC_CH0 , DVRIMA_AUTO_RAMP_UP + DVRIMA_AUTO_RAMP_DOWN);

  while(1)
	{
		WDT_Clear();
		SACM_DVRIMA_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_DVRIMA_CheckCpuOverload() != 0)
		{
			SACM_DVRIMA_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Stop
				PlayCon = 0;
				SACM_DVRIMA_Stop();
        break;

			case 0x02:                                           // IOA1+VDD: Play next song
				PlayCon = 0;
				SACM_DVRIMA_Stop();
			  DVRIMAPlayIdx = ++DVRIMAPlayIdx > SpeechNum ? 1 : DVRIMAPlayIdx;
				SACM_DVRIMA_Play(DVRIMA_User_GetDVRIMAStartAddr(DVRIMAPlayIdx), DVRIMA_DAC_CH0 , DVRIMA_AUTO_RAMP_UP + DVRIMA_AUTO_RAMP_DOWN);
				break;

			case 0x04:	                                         // IOA2+VDD: Play prev song
				PlayCon = 0;
				SACM_DVRIMA_Stop();
			  DVRIMAPlayIdx = --DVRIMAPlayIdx < 1 ? SpeechNum : DVRIMAPlayIdx;
				SACM_DVRIMA_Play(DVRIMA_User_GetDVRIMAStartAddr(DVRIMAPlayIdx), DVRIMA_DAC_CH1, DVRIMA_AUTO_RAMP_UP + DVRIMA_AUTO_RAMP_DOWN);
				break;

			case 0x08:                                           // IOA3+VDD: Play concatenate
				PlayCon = 1;
			  SACM_DVRIMA_Stop();
			  DVRIMAPlayIdx = 1;
			  SACM_DVRIMA_Play(DVRIMA_User_GetDVRIMAStartAddr(DVRIMAPlayIdx++), DVRIMA_DAC_CH0, DVRIMA_AUTO_RAMP_UP + DVRIMA_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                           // IOA4+VDD:	Pause/Resume
				if((SACM_DVRIMA_GetStatus() & DVRIMA_PAUSE_FLAG) == 0)
				{
				  SACM_DVRIMA_Pause();
				}
				else
				{
				  SACM_DVRIMA_Resume();
				}
				break;

      case 0x20:                                           // IOA5+VDD:
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

		if((PlayCon != 0) && (SACM_DVRIMA_Check_Con() == 0))
		{
			SACM_DVRIMA_Play_Con(DVRIMA_User_GetDVRIMAStartAddr(DVRIMAPlayIdx++), DVRIMA_DAC_CH0, DVRIMA_AUTO_RAMP_UP + DVRIMA_AUTO_RAMP_DOWN);
			DVRIMAPlayIdx = DVRIMAPlayIdx > SpeechNum ? 1 : DVRIMAPlayIdx;
		}
	}
}
