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
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) SACM_DVR1801_WORKING_RAM Dvr1801WorkingRam;
__align(4) SACM_DVR1801_TEMP_RAM Dvr1801TempBuffer;
__align(4) SACM_DVR1801_PCM_BUFFER Dvr1801PcmBuffer;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_DVR1801_WORKING_RAM Dvr1801WorkingRam;
__attribute__ ((aligned (4))) SACM_DVR1801_TEMP_RAM Dvr1801TempBuffer;
__attribute__ ((aligned (4))) SACM_DVR1801_PCM_BUFFER Dvr1801PcmBuffer;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint16_t A1801Num = 0;
int16_t A1801PlayIdx = 1;
int16_t SwVolGain = 8;


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
	//SPIFC_EN4B();																           // SPIFC enable 4 bytes
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		             // SPIFC auto mode
	SPIFC_AutoMode(SPIFC_2IO_MODE);					                 // SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     // Calibrate SPIFC clock timing.
	{
		while(1);                                              // SPIFC clock timing calibration fail!
	}

	A1801Num = DVR1801_User_GetA1801Num();
	SACM_DVR1801_Initial(&Dvr1801WorkingRam, &Dvr1801TempBuffer, &Dvr1801PcmBuffer);
	SACM_DVR1801_Play(DVR1801_User_GetA1801StartAddr(A1801PlayIdx), DVR1801_DAC_CH1, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);

	APP_SwVolCtrl_Init();                                    // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, SwVolGain);
	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

  while(1)
	{
		WDT_Clear();
		DVR1801_User_DVR1801WithGpEvent_ServerLoop();
		KeyScan_ServiceLoop();

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Stop
				SACM_DVR1801_Stop();
        break;

			case 0x02:                                           // IOA1+VDD: Play next song
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  //SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);
				SPIFC_AutoMode(SPIFC_2IO_MODE);
				SACM_DVR1801_Play(DVR1801_User_GetA1801StartAddr(A1801PlayIdx), DVR1801_DAC_CH0 , DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
			  A1801PlayIdx = ++A1801PlayIdx > A1801Num ? 1 : A1801PlayIdx;
				break;

			case 0x04:	                                         // IOA2+VDD: Play prev song
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  //SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);
			  SPIFC_AutoMode(SPIFC_2IO_MODE);
				SACM_DVR1801_Play(DVR1801_User_GetA1801StartAddr(A1801PlayIdx), DVR1801_DAC_CH1, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
			  A1801PlayIdx = --A1801PlayIdx < 1 ? A1801Num : A1801PlayIdx;
				break;

			case 0x08:                                           // IOA3+VDD: Pause/Resume
				if((SACM_DVR1801_GetStatus() & DVR1801_PAUSE_FLAG) == 0)
				{
				  SACM_DVR1801_Pause();
				}
				else
				{
				  SACM_DVR1801_Resume();
				}
			  break;

			case 0x10:                                           // IOA4+VDD:	Volume up
				SwVolGain = ++SwVolGain > MAX_VOL_GAIN ? 1 : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
				break;

      case 0x20:		                                       // IOA5+VDD:	Volume down
			  SwVolGain = --SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
				break;

			case 0x40:                                           // IOA6+VDD: Record
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  SACM_DVR1801_Initial(&Dvr1801WorkingRam, &Dvr1801TempBuffer, &Dvr1801PcmBuffer);
				SPIFC_BlockErase(0x00200000);
			  SPIFC_BlockErase(0x00210000);
			  SACM_DVR1801_Rec((int16_t *) 0x00200000, DVR1801_RECORD_BITRATE_16000);
			  break;

			case 0x80:                                           // IOA7+VDD:
				SACM_DVR1801_Stop();
			  //SPIFC_EnhanModeReset();
			  //SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);
			  SPIFC_AutoMode(SPIFC_2IO_MODE);
			  SACM_DVR1801_Initial(&Dvr1801WorkingRam, &Dvr1801TempBuffer, &Dvr1801PcmBuffer);
			  SACM_DVR1801_Play((int16_t *)0x04200000, DVR1801_DAC_CH0, DVR1801_AUTO_RAMP_UP + DVR1801_AUTO_RAMP_DOWN);
				break;
	  }
	}
}
