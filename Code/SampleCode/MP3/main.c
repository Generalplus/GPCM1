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
#include "MP3_User.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) MP3_LIB_WORKING_RAM Mp3LibWorkingRam;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) MP3_LIB_WORKING_RAM Mp3LibWorkingRam;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	uint8_t Mp3Num;
	int32_t ScanedKey;
	int16_t AudPwmGain = 31;
	int16_t Mp3PlayIdx = 1;
  int8_t PlayCon = 0;

	SystemInit();
  WDT_SetClk(WDG_CLK_32768_DIV_16);

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	           // SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV4);
	//SPIFC_EN4B();																           // SPIFC enable 4 bytes
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		             // SPIFC auto mode
	SPIFC_AutoMode(SPIFC_4IO_MODE);					                 // SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     // Calibrate SPIFC clock timing.
	{
		while(1);                                              // SPIFC clock timing calibration fail!
	}

	KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

	Mp3Num = GetMp3Num();
	Mp3Num -= 1;	                                           // The last MP3 is a pseudo file. The (n)th MP3 address - the (n-1)th MP3 address is the data length of the (n-1)th MP3.
	MP3_Initial(&Mp3LibWorkingRam);
  MP3_Play(GetMp3StartAddr(Mp3PlayIdx), GetMp3Length(Mp3PlayIdx), MP3_DAC_CH0 , MP3_AUTO_RAMP_UP + MP3_AUTO_RAMP_DOWN);

	while(1)
	{
		WDT_Clear();
		MP3_ServiceLoop();
		KeyScan_ServiceLoop();

		ScanedKey = KeyScan_GetCh();
		switch (ScanedKey)
		{
			case 0x01:                                           // IOA0+VDD: Stop
				PlayCon = 0;
				MP3_Stop();
				break;

			case 0x02:                                           // IOA1+VDD: replay
				PlayCon = 0;
				MP3_Stop();
				MP3_Play(GetMp3StartAddr(Mp3PlayIdx), GetMp3Length(Mp3PlayIdx), MP3_DAC_CH0, MP3_AUTO_RAMP_UP + MP3_AUTO_RAMP_DOWN);
			  DAC_SetAudPwmGain(AudPwmGain);
				break;

			case 0x04:                                           // IOA2+VDD: Play next song
				PlayCon = 0;
				MP3_Stop();
			  Mp3PlayIdx = ++Mp3PlayIdx > Mp3Num ? 1 : Mp3PlayIdx;
				MP3_Play(GetMp3StartAddr(Mp3PlayIdx), GetMp3Length(Mp3PlayIdx), MP3_DAC_CH1, MP3_AUTO_RAMP_UP + MP3_AUTO_RAMP_DOWN);
			  DAC_SetAudPwmGain(AudPwmGain);
				break;

			case 0x08:                                           // IOA3+VDD: Play concatenate
				PlayCon = 1;
			  MP3_Stop();
			  Mp3PlayIdx = 1;
			  MP3_Play(GetMp3StartAddr(Mp3PlayIdx), GetMp3Length(Mp3PlayIdx), MP3_DAC_CH0, MP3_AUTO_RAMP_UP + MP3_AUTO_RAMP_DOWN);
			  DAC_SetAudPwmGain(AudPwmGain);
			  break;

			case 0x10:                                           // IOA4+VDD:	Pause/Resume
				if((MP3_GetStatus() & MP3_PAUSE_FLAG) == 0)
				{
				  MP3_Pause();
				}
				else
				{
				  MP3_Resume();
				}
				break;

			case 0x40:
				AudPwmGain++;
			  if(AudPwmGain >= 63)
				{
				  AudPwmGain = 62;
				}
			  DAC_SetAudPwmGain(AudPwmGain);
				break;

			case 0x80:
				AudPwmGain--;
			  if(AudPwmGain <= 1)
				{
				  AudPwmGain = 1;
				}
			  DAC_SetAudPwmGain(AudPwmGain);
				break;

			default:
				break;
		}

		if((PlayCon != 0) && (MP3_Check_Con() == 0))
		{
      Mp3PlayIdx = ++Mp3PlayIdx > Mp3Num ? 1 : Mp3PlayIdx;
			MP3_Play_Con(GetMp3StartAddr(Mp3PlayIdx), GetMp3Length(Mp3PlayIdx), MP3_DAC_CH0, MP3_AUTO_RAMP_UP + MP3_AUTO_RAMP_DOWN);
		}

		if(MP3_CheckCpuOverload() != 0)
		{
			MP3_ClearCpuOverload();
		}
	}
}
