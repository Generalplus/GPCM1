/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1F A34Pro 4-Ch Mixer demo code
 * @Version:
 *
 * @Date: 2025.01.14
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
#include "SACM_A3400Pro_CH3_User.h"
#include "SACM_A3400Pro_CH4_User.h"
#include "SACM_MIXER_Ch0_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#define Aligned4B __align(4)
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#define Aligned4B __attribute__ ((aligned (4)))
#endif

Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProWorkingRam;
Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProCh2WorkingRam;
Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProCh3WorkingRam;
Aligned4B SACM_A3400PRO_WORKING_RAM			A3400ProCh4WorkingRam;

Aligned4B	int16_t MicCh0PcmBuffer[(2 * MIXER_CH0_FRAME_SIZE)];        // Ch0 Mixer A/B Buffer.
Aligned4B	SACM_MIXER_CH0_WORKING_RAM	MixerCh0WorkingRam;

uint16_t A3400ProNum = 0;
int16_t A3400ProPlayIdx = 1;
int16_t A3400ProCh2PlayIdx = 2;
int16_t A3400ProCh3PlayIdx = 3;
int16_t A3400ProCh4PlayIdx = 4;

int8_t PlayCon = 0;
int8_t PauseFlag = 0;
int8_t A34Ch0SwVolGain = 5;
int8_t A34Ch1SwVolGain = 5;
int8_t A34Ch2SwVolGain = 5;
int8_t A34Ch3SwVolGain = 5;

uint32_t ScanedKey;


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

  SACM_MIXER_Ch0_Initial(&MixerCh0WorkingRam, (int8_t *)MicCh0PcmBuffer, MIXER_CH0_FRAME_SIZE, MIXER_CH0_BITS);
	SACM_MIXER_Ch0_Play(MIXER_CH0_DAC_CH0, MIXER_CH0_AUTO_RAMP_UP + MIXER_CH0_AUTO_RAMP_DOWN);

	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init
	/*
	 * A3400Pro init
	 */
	A3400ProNum = GetA3400ProNum();
	SACM_A3400Pro_Initial(&A3400ProWorkingRam, &MicCh0PcmBuffer[0], A3400PRO_FRAME_SIZE);
	SACM_A3400Pro_CH2_Initial(&A3400ProCh2WorkingRam, &MicCh0PcmBuffer[0], A3400PRO_FRAME_SIZE);
	SACM_A3400Pro_CH3_Initial(&A3400ProCh3WorkingRam, &MicCh0PcmBuffer[0], A3400PRO_FRAME_SIZE);
	SACM_A3400Pro_CH4_Initial(&A3400ProCh4WorkingRam, &MicCh0PcmBuffer[0], A3400PRO_FRAME_SIZE);

	APP_SwVolCtrl_Init();                                    // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, A34Ch0SwVolGain);
	APP_SwVolCtrl_SetVolGain(1, A34Ch1SwVolGain);
	APP_SwVolCtrl_SetVolGain(2, A34Ch2SwVolGain);
	APP_SwVolCtrl_SetVolGain(3, A34Ch3SwVolGain);

  SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0 , A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
  SACM_A3400Pro_CH2_Play(GetA3400ProCh2StartAddr(A3400ProCh2PlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
  SACM_A3400Pro_CH3_Play(GetA3400ProCh3StartAddr(A3400ProCh3PlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
  SACM_A3400Pro_CH4_Play(GetA3400ProCh4StartAddr(A3400ProCh4PlayIdx), A3400PRO_DAC_CH0, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);

  while(1)
	{
		WDT_Clear();
    SACM_MIXER_Ch0_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_MIXER_Ch0_CheckCpuOverload() != 0)
		{
			SACM_MIXER_Ch0_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                 						// IOA0+VDD: A3400Pro Ch1 play next song
				PlayCon = 0;
				SACM_A3400Pro_Stop();
			  A3400ProPlayIdx = ++A3400ProPlayIdx > A3400ProNum ? 1 : A3400ProPlayIdx;
				SACM_A3400Pro_Play(GetA3400ProStartAddr(A3400ProPlayIdx), A3400PRO_DAC_CH0 , A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
        break;

			case 0x02:                                 						// IOA1+VDD: A3400Pro Ch2 play next song
				PlayCon = 0;
				SACM_A3400Pro_CH2_Stop();
			  A3400ProCh2PlayIdx = ++A3400ProCh2PlayIdx > A3400ProNum ? 1 : A3400ProCh2PlayIdx;
				SACM_A3400Pro_CH2_Play(GetA3400ProCh2StartAddr(A3400ProCh2PlayIdx), A3400PRO_DAC_CH1, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
				break;

			case 0x04:                                 						// IOA2+VDD: A3400Pro_Ch3 play next song
				PlayCon = 0;
				SACM_A3400Pro_CH3_Stop();
			  A3400ProCh3PlayIdx = ++A3400ProCh3PlayIdx > A3400ProNum ? 1 : A3400ProCh3PlayIdx;
				SACM_A3400Pro_CH3_Play(GetA3400ProCh3StartAddr(A3400ProCh3PlayIdx), A3400PRO_DAC_CH1, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
				break;

			case 0x08:                                 						// IOA3+VDD: A3400Pro_Ch4 play next song
				PlayCon = 0;
				SACM_A3400Pro_CH4_Stop();
			  A3400ProCh4PlayIdx = ++A3400ProCh4PlayIdx > A3400ProNum ? 1 : A3400ProCh4PlayIdx;
				SACM_A3400Pro_CH4_Play(GetA3400ProCh4StartAddr(A3400ProCh4PlayIdx), A3400PRO_DAC_CH1, A3400PRO_AUTO_RAMP_UP + A3400PRO_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                 						// IOA4+VDD: Stop
				PlayCon = 0;
				SACM_A3400Pro_Stop();
				SACM_A3400Pro_CH2_Stop();
				SACM_A3400Pro_CH3_Stop();
				SACM_A3400Pro_CH4_Stop();
				break;

      case 0x20:                                 						// IOA5+VDD:	Pause/Resume
				if(PauseFlag == 0)
				{
					PauseFlag = 1;
				  SACM_A3400Pro_Pause();
				  SACM_A3400Pro_CH2_Pause();
          SACM_A3400Pro_CH3_Pause();
          SACM_A3400Pro_CH4_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_A3400Pro_Resume();
				  SACM_A3400Pro_CH2_Resume();
				  SACM_A3400Pro_CH3_Resume();
				  SACM_A3400Pro_CH4_Resume();
				}
				break;

			case 0x40:                                 						// IOA6+VDD: Volume Up
				A34Ch0SwVolGain = ++A34Ch0SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : A34Ch0SwVolGain;
				APP_SwVolCtrl_SetVolGain(0, A34Ch0SwVolGain);            	// Set A3400Pro CH1 software volume gain
				A34Ch1SwVolGain = ++A34Ch1SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : A34Ch1SwVolGain;
			  APP_SwVolCtrl_SetVolGain(1, A34Ch1SwVolGain);            	// Set A3400Pro CH2 software volume gain
				A34Ch2SwVolGain = ++A34Ch2SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : A34Ch2SwVolGain;
			  APP_SwVolCtrl_SetVolGain(2, A34Ch2SwVolGain);            	// Set A3400Pro CH3 software volume gain
				A34Ch3SwVolGain = ++A34Ch3SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : A34Ch3SwVolGain;
			  APP_SwVolCtrl_SetVolGain(3, A34Ch3SwVolGain);            	// Set A3400Pro CH4 software volume gain
			  break;

			case 0x80:                                 						// IOA7+VDD: Volume Dn
        A34Ch0SwVolGain = --A34Ch0SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : A34Ch0SwVolGain;
        APP_SwVolCtrl_SetVolGain(0, A34Ch0SwVolGain);            	// Set A3400Pro CH1 software volume gain
			  A34Ch1SwVolGain = --A34Ch1SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : A34Ch1SwVolGain;
			  APP_SwVolCtrl_SetVolGain(1, A34Ch1SwVolGain);            	// Set A3400Pro CH2 software volume gain
			  A34Ch2SwVolGain = --A34Ch2SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : A34Ch2SwVolGain;
			  APP_SwVolCtrl_SetVolGain(2, A34Ch2SwVolGain);            	// Set A3400Pro CH3 software volume gain
			  A34Ch3SwVolGain = --A34Ch3SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : A34Ch3SwVolGain;
			  APP_SwVolCtrl_SetVolGain(3, A34Ch3SwVolGain);            	// Set A3400Pro CH4 software volume gain
				break;
	  }
	}
}
