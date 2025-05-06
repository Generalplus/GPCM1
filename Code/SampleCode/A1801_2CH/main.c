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
#include "SACM_A1801_CH2_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) SACM_A1801_WORKING_RAM A1801WorkingRam;
__align(4) SACM_A1801_WORKING_RAM A1801Ch2WorkingRam;
__align(4) SACM_A1801_TEMP_RAM A1801TempBuffer;
__align(4) SACM_A1801_PCM_BUFFER A1801PcmBuffer;
__align(4) SACM_A1801_PCM_BUFFER A1801Ch2PcmBuffer;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_A1801_WORKING_RAM A1801WorkingRam;
__attribute__ ((aligned (4))) SACM_A1801_WORKING_RAM A1801Ch2WorkingRam;
__attribute__ ((aligned (4))) SACM_A1801_TEMP_RAM A1801TempBuffer;
__attribute__ ((aligned (4))) SACM_A1801_PCM_BUFFER A1801PcmBuffer;
__attribute__ ((aligned (4))) SACM_A1801_PCM_BUFFER A1801Ch2PcmBuffer;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint16_t A1801Num = 0;
int16_t A1801PlayIdx = 1;
int16_t A1801Ch2PlayIdx = 2;
int8_t PlayCon = 0;
int8_t PauseFlag = 0;
int8_t SwVolGain = 6;


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

	A1801Num = A1801_User_GetA1801Num();
	SACM_A1801_Initial(&A1801WorkingRam, &A1801TempBuffer, &A1801PcmBuffer);
	SACM_A1801_CH2_Initial(&A1801Ch2WorkingRam, &A1801TempBuffer, &A1801Ch2PcmBuffer);
	SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
	SACM_A1801_CH2_Play(A1801_User_GetA1801StartAddr(A1801Ch2PlayIdx), A1801_DAC_CH1, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);


	APP_SwVolCtrl_Init();                                    // Software volume control init.
  APP_SwVolCtrl_SetVolGain(0, SwVolGain);                  // Set A1801 CH1 software volume gain
	APP_SwVolCtrl_SetVolGain(1, SwVolGain);                  // Set A1801 CH2 software volume gain
	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

  while(1)
	{
		WDT_Clear();
		SACM_A1801_ServiceLoop();
		SACM_A1801_CH2_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_A1801_CheckCpuOverload() != 0)
		{
			SACM_A1801_ClearCpuOverload();
		}

		if(SACM_A1801_CH2_CheckCpuOverload() != 0)
		{
			SACM_A1801_CH2_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Stop
				PlayCon = 0;
				SACM_A1801_Stop();
			  SACM_A1801_CH2_Stop();
        break;

			case 0x02:                                           // IOA1+VDD: A1801 play next song
				PlayCon = 0;
				SACM_A1801_Stop();
			  A1801PlayIdx = ++A1801PlayIdx > A1801Num ? 1 : A1801PlayIdx;
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx), A1801_DAC_CH0 , A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x04:	                                         // IOA2+VDD: A1801_CH2 play next song
				//PlayCon = 0;
				SACM_A1801_CH2_Stop();
			  A1801Ch2PlayIdx = ++A1801Ch2PlayIdx > A1801Num ? 1 : A1801Ch2PlayIdx;
			  SACM_A1801_CH2_Play(A1801_User_GetA1801StartAddr(A1801Ch2PlayIdx), A1801_DAC_CH1, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				break;

			case 0x08:                                           // IOA3+VDD: A1801 Play concatenate
				PlayCon = 1;
			  SACM_A1801_Stop();
			  A1801PlayIdx = 1;
			  SACM_A1801_Play(A1801_User_GetA1801StartAddr(A1801PlayIdx++), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                           // IOA4+VDD:	Pause/Resume
				if(PauseFlag == 0)
				{
					PauseFlag = 1;
				  SACM_A1801_Pause();
					SACM_A1801_CH2_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_A1801_Resume();
					SACM_A1801_CH2_Resume();
				}
				break;

      case 0x20:
				SwVolGain = ++SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);            // Set A1801 CH1 software volume gain
			  APP_SwVolCtrl_SetVolGain(1, SwVolGain);            // Set A1801 CH2 software volume gain
				break;

			case 0x40:
			  SwVolGain = --SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);            // Set A1801 CH1 software volume gain
			  APP_SwVolCtrl_SetVolGain(1, SwVolGain);            // Set A1801 CH2 software volume gain
			  break;

			case 0x80:
				break;
	  }

		if((PlayCon != 0) && (SACM_A1801_Check_Con() == 0))
		{
			SACM_A1801_Play_Con(A1801_User_GetA1801StartAddr(A1801PlayIdx++), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			A1801PlayIdx = A1801PlayIdx > A1801Num ? 1 : A1801PlayIdx;
		}
	}
}
