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
	SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);

	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

  while(1)
	{
		WDT_Clear();
		SACM_A1801_ServiceLoop();
		KeyScan_ServiceLoop();

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Stop
				PlayCon = 0;
				SACM_A1801_Stop();
        break;

			case 0x02:                                           // IOA1+VDD: Play next song
				PlayCon = 0;
				SACM_A1801_Stop();
			  A1801PlayIdx = ++A1801PlayIdx > SpeechNum ? 1 : A1801PlayIdx;
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x04:	                                         // IOA2+VDD: Play prev song
				PlayCon = 0;
				SACM_A1801_Stop();
			  A1801PlayIdx = --A1801PlayIdx < 1 ? SpeechNum : A1801PlayIdx;
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx), A1801_DAC_CH1, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x08:                                           // IOA3+VDD: Play concatenate
				PlayCon = 1;
			  SACM_A1801_Stop();
			  A1801PlayIdx = 1;
			  SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx++), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                           // IOA4+VDD:	Pause/Resume
				if((SACM_A1801_GetStatus() & A1801_PAUSE_FLAG)== 0)
				{
				  SACM_A1801_Pause();
				}
				else
				{
				  SACM_A1801_Resume();
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
	  }

		if((PlayCon != 0) && (SACM_A1801_Check_Con() == 0))
		{
			SACM_A1801_Play_Con(A1801_User_GetA1801StartAddr(A1801PlayIdx++), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			A1801PlayIdx = A1801PlayIdx > SpeechNum ? 1 : A1801PlayIdx;
		}
	}
}
