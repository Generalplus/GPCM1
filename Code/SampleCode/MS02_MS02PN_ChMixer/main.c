/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1F MS02 and MS02_PN merge to one channel demo code.
 * @Version: V1.0
 *
 * @Date: 202.07.18
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
#include "SACM_MS02PN_User.h"
#include "SACM_MIXER_Ch1_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#define Aligned4B __align(4)
__align(4) SACM_MS02_WORKING_RAM MS02WorkingRam;
__align(4) uint8_t MS02KernelRam[MS02_DEC_Memory];
__align(4) SACM_MS02PN_WORKING_RAM MS02PNWorkingRam;
__align(4) uint8_t MS02PNKernelRam[MS02PN_DEC_Memory];
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
#define Aligned4B __attribute__ ((aligned (4)))
__attribute__ ((aligned (4))) SACM_MS02_WORKING_RAM MS02WorkingRam;
__attribute__ ((aligned (4))) uint8_t MS02KernelRam[MS02_DEC_Memory];
__attribute__ ((aligned (4))) SACM_MS02PN_WORKING_RAM MS02PNWorkingRam;
__attribute__ ((aligned (4))) uint8_t MS02PNKernelRam[MS02PN_DEC_Memory];
#endif

Aligned4B	int16_t MicCh1PcmBuffer[(2 * MIXER_CH1_FRAME_SIZE)];        // Ch1 Mixer A/B Buffer.
Aligned4B	SACM_MIXER_CH1_WORKING_RAM	MixerCh1WorkingRam;

int16_t MS02InBuffer[MS02_IN_BUFFER_SIZE];

Aligned4B	KEYSCAN_WORKING_RAM				  KeyscanWorkingRam;

// int16_t MS02PcmBuffer[MS02_OUT_BUFFER_SIZE];

uint32_t ScanedKey;
int8_t PauseFlag = 0;

// For Midi MS02 & MS02PN
uint16_t MidiChNum = MS02_CH_Num;
uint16_t MidiPNChNum = MS02PN_CH_Num;
uint16_t MidiNum = 0;
int16_t MidiIdx = 3;
int16_t MS02LibIdx =1;
uint8_t OKONFlag = 0;

int16_t MS02PNLibIdx =1;
int16_t MidiGain = 0x40;
uint8_t AudioOutType = AUD_OUT_PWM;
int16_t AudPwmGain = 0X1f;

int8_t MS02SwVolGain = 3;
int8_t MS02PNSwVolGain = 9;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	SystemInit();

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																						// SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV2);
	SPIFC_AutoMode(SPIFC_4IO_MODE);													// SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)    // Calibrate SPIFC clock timing.
	{
		while(1);                                             // SPIFC clock timing calibration fail!
	}
	SACM_MIXER_Ch1_Initial(&MixerCh1WorkingRam, MicCh1PcmBuffer, MIXER_CH1_FRAME_SIZE, MIXER_CH1_BITS);
	SACM_MIXER_Ch1_Play(MIXER_CH1_DAC_CH1 , MIXER_CH1_AUTO_RAMP_UP + MIXER_CH1_AUTO_RAMP_DOWN);

	/*
	 * MS02 & MS02_PN init
	 */
	MidiNum = GetMidiNum();
	// SACM_MS02_Initial(&MS02WorkingRam, MicCh1PcmBuffer, MS02KernelRam, AUD_OUT_PWM, MS02_CH1, MS02_Timer_20K);
  SACM_MS02_Initial(&MS02WorkingRam, MS02InBuffer, MicCh1PcmBuffer, MS02KernelRam, MS02_IN_BUFFER_SIZE, MS02_OUT_BUFFER_SIZE, AUD_OUT_PWM, MS02_CH1, MS02_Timer_20K);

	SACM_MS02_SetChannelStatus(0xFFFF);                     // Set MIDI Ch 0~15 1:ON/0:OFF
  SACM_MS02_SetDrumStatus(0xFFFF);                        // Set drum track 0~15 1:ON/0:OFF
  SACM_MS02_SetKeyChStatus(0xFFFF);                       // Set keyshift ch 0~15 1:ON/0:OFF
  SACM_MS02_KeyShift(0);                                  // Set initial value of the keyshift

  SACM_MS02PN_Initial(&MS02PNWorkingRam, MicCh1PcmBuffer, MS02PNKernelRam, GetMS02PNLibStartAddr(MS02PNLibIdx), AudioOutType, MS02_CH1, MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
	DAC_SetAudPwmGain(AudPwmGain);

	APP_SwVolCtrl_Init();                                   // Software volume control init.
  APP_SwVolCtrl_SetVolGain(0, MS02SwVolGain);             // For MS02
	APP_SwVolCtrl_SetVolGain(1, MS02PNSwVolGain);           // For MS02 PN
	KeyScan_Initial(&KeyscanWorkingRam);

	/*
	 * Power on play MS02
	 */
	SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);

	while(1)
	{
		WDT_Clear();
		SACM_MIXER_Ch1_ServiceLoop();
		KeyScan_ServiceLoop();

		if(SACM_MIXER_Ch1_CheckCpuOverload() != 0)
		{
			SACM_MIXER_Ch1_ClearCpuOverload();
		}

		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
		  case 0x01:                                           // IOA0+VDD: Play Note
        SACM_MS02PN_Initial(&MS02PNWorkingRam, MicCh1PcmBuffer, MS02PNKernelRam, GetMS02PNLibStartAddr(MS02PNLibIdx), AudioOutType, MS02_CH1, MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
		    SACM_MS02PN_PlayNote(5, 0x32, MidiGain, 0xFF);
        break;

			case 0x02:                                           // IOA1+VDD: Play Drum
        SACM_MS02PN_Initial(&MS02PNWorkingRam, MicCh1PcmBuffer, MS02PNKernelRam, GetMS02PNLibStartAddr(MS02PNLibIdx), AudioOutType, MS02_CH1, MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
        SACM_MS02PN_PlayDrum(3, 0x02, MidiGain, 0xFF);
				break;

			case 0x04:                                           // IOA2+VDD: Play next midi
        SACM_MS02_Stop();
				MidiIdx = ++MidiIdx > MidiNum ? 2 : MidiIdx;
				SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
        break;

			case 0x08:                                           // IOA3+VDD: Play current midi
        SACM_MS02_Stop();
				SACM_MS02_Play(GetMS02LibStartAddr(MS02LibIdx), GetMidiStartAddr(MidiIdx), MS02_AUTO_RAMP_UP + MS02_AUTO_RAMP_DOWN, MS02_DAC_20K);
        break;

			case 0x10:                                           // IOA4+VDD:	 MS02 stop
        SACM_MS02_Stop();
        SACM_MS02PN_Stop();
        // SACM_MIXER_Ch1_Stop();
				break;

      case 0x20:                                           // IOA5+VDD:	Pause/ Resume
				if(PauseFlag == 0)
				{
					PauseFlag = 1;
				  SACM_MIXER_Ch1_Pause();
				}
				else
				{
					PauseFlag = 0;
				  SACM_MIXER_Ch1_Resume();
				}
				break;

      case 0x40:                                           // IOA6+VDD:	Volume Up
				MS02SwVolGain   = ++MS02SwVolGain   >= MAX_VOL_GAIN ? MAX_VOL_GAIN : MS02SwVolGain;
				MS02PNSwVolGain = ++MS02PNSwVolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : MS02PNSwVolGain;
        APP_SwVolCtrl_SetVolGain(0, MS02SwVolGain);               // For MS02
        APP_SwVolCtrl_SetVolGain(1, MS02PNSwVolGain);             // For MS02_PN
				break;

			case 0x80:                                           // IOA7+VDD:	Volume Dn
			  MS02SwVolGain   = --MS02SwVolGain   <= MIN_VOL_GAIN ? MIN_VOL_GAIN : MS02SwVolGain;
			  MS02PNSwVolGain = --MS02PNSwVolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : MS02PNSwVolGain;
        APP_SwVolCtrl_SetVolGain(0, MS02SwVolGain);               // For MS02
        APP_SwVolCtrl_SetVolGain(1, MS02PNSwVolGain);             // For MS02_PN
        break;
		}
	}
}
