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
#include "glibc_wrapper.h"
#include "SACM_MS02_User.h"
#include "MS02dec.h"
#include "APP_SwVolumeControl.h"
#include "DAC_GPCM1Fx.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) SACM_MS02_WORKING_RAM MS02WorkingRam;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
__align(4) uint8_t MS02KernelRam[MS02_DEC_Memory];
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_MS02_WORKING_RAM MS02WorkingRam;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
__attribute__ ((aligned (4))) uint8_t MS02KernelRam[MS02_DEC_Memory];
#endif

uint8_t MidiChNum = MS02_CH_Num;
int16_t MS02InBuffer[MS02_IN_BUFFER_SIZE];
int16_t MS02PcmBuffer[2*MS02_OUT_BUFFER_SIZE];

/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	uint32_t ScanedKey;
	int16_t AudPwmGain = 0X1f;
	int8_t PauseFlag = 0;
	uint8_t PlayCon = 1;

	uint16_t MidiNum = 0;
	int16_t MidiIdx = 2;
	int16_t MS02LibIdx =1;
  int8_t SwVolGain = 7;
	uint8_t OKONFlag = 0;

	SystemInit();

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	 // SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV1);
	SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		     // SPIFC auto mode
	SPIFC_TimingFineTune();                        // Calibrate SPIFC clock timing

	MidiNum = GetMidiNum();
	// SACM_MS02_Initial(&MS02WorkingRam, MS02PcmBuffer, MS02KernelRam, AUD_OUT_PWM, MS02_CH1, MS02_Timer_20K);
	SACM_MS02_Initial(&MS02WorkingRam, MS02InBuffer, MS02PcmBuffer, MS02KernelRam, MS02_IN_BUFFER_SIZE, MS02_OUT_BUFFER_SIZE, AUD_OUT_PWM, MS02_CH1, MS02_Timer_20K);
	SACM_MS02_SetChannelStatus(0xFFFF);             //Set MIDI Ch 0~15 1:ON/0:OFF
  SACM_MS02_SetDrumStatus(0xFFFF);                //Set drum track 0~15 1:ON/0:OFF
  SACM_MS02_SetKeyChStatus(0xFFFF);               //Set keyshift ch 0~15 1:ON/0:OFF
  SACM_MS02_KeyShift(0);                          //Set initial value of the keyshift

	APP_SwVolCtrl_SetVolGain(0, SwVolGain);
	DAC_SetAudPwmGain(AudPwmGain);
	SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);

	KeyScan_Initial(&KeyScanWorkingRam);           // key scan init

  while(1)
	{
		WDT_Clear();
		SACM_MS02_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_MS02_CheckCpuOverload() != 0)
		{
			SACM_MS02_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                 // IOA0+VDD: Play next MIDI
        SACM_MS02_Stop();
				MidiIdx = ++MidiIdx > MidiNum ? 2 : MidiIdx;
				SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
				break;

			case 0x02:                                 // IOA1+VDD: Play current MIDI
        SACM_MS02_Stop();
				SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
				break;

			case 0x04:	                               // IOA2+VDD: Pause/ Resume
				if(PauseFlag == 0)
				{
					PauseFlag = 1;
				  SACM_MS02_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_MS02_Resume();
				}
				break;

			case 0x08:                                 // IOA3+VDD:	Stop
				SACM_MS02_Stop();
			  break;

			case 0x10:                                 // IOA4+VDD:	Audio PWM gain Up
				AudPwmGain+=6;
				if(AudPwmGain >= 63)
				{
				  AudPwmGain = 62;
				}
				DAC_SetAudPwmGain(AudPwmGain);

				break;

			case 0x20:                                 // IOA4+VDD:	Audio PWM gain Dn
				AudPwmGain-=6;
				if(AudPwmGain <= 0)
				{
				  AudPwmGain = 0;
				}
				DAC_SetAudPwmGain(AudPwmGain);
				break;

			case 0x40:                                 // IOA6+VDD: MS02 S/W volume Up
				SwVolGain = ++SwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
			  break;

			case 0x80:                                 // IOA7+VDD: MS02 S/W volume Dn
			  SwVolGain = --SwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : SwVolGain;
			  APP_SwVolCtrl_SetVolGain(0, SwVolGain);
				break;
	  }

		if((PlayCon != 0) && (SACM_MS02_Check_Con() == 0))
		{
				// MidiIdx = ++MidiIdx > MidiNum ? 2 : MidiIdx;
        SACM_MS02_Play_Con(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
		}

	}
}
