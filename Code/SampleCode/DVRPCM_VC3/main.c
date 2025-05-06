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
#include "SACM_DVRPCM_User.h"
#include "SACM_VC3_User.h"
#include "APP_SwVolumeControl.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) SACM_DVRPCM_WORKING_RAM DvrPcmWorkingRam;
__align(4) int16_t  DvrDataBuffer[2 * DVRPCM_FRAME_SIZE];
__align(4) SACM_VC3_API_WORKING_RAM Vc3ApiWorkingRam;
__align(4) SACM_VC3_PCM_BUFFER Vc3PcmBuffer;
__align(4) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam;
__align(4) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam2;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) SACM_DVRPCM_WORKING_RAM DvrPcmWorkingRam;
__attribute__ ((aligned (4))) int16_t DvrDataBuffer[2 * DVRPCM_FRAME_SIZE];
__attribute__ ((aligned (4))) SACM_VC3_API_WORKING_RAM Vc3ApiWorkingRam;
__attribute__ ((aligned (4))) SACM_VC3_PCM_BUFFER Vc3PcmBuffer;
__attribute__ ((aligned (4))) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam;
__attribute__ ((aligned (4))) SACM_VC3_KERNEL_RAM Vc3KernelWorkingRam2;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint16_t PcmNum = 0;
int16_t PcmPlayIdx = 1;
int8_t PlayCon = 0;

uint8_t Vc3EffectEn = 0;
int8_t Vc3Mode = VC3_SHIFT_PITCH_MODE;
int8_t Vc3ShiftPitch = 10;
int8_t Vc3ChangeSpeed = -6;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();
	WDT_SetClk(WDG_CLK_32768_DIV_32);

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	                          // SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV4);
	//SPIFC_EN4B();																                          // SPIFC enable 4 bytes
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		                            // SPIFC auto mode
	SPIFC_AutoMode(SPIFC_2IO_MODE);					                                // SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)                    // Calibrate SPIFC clock timing.
	{
		while(1);                                                             // SPIFC clock timing calibration fail!
	}

	PcmNum = GetPcmNum();
	SACM_DVRPCM_Initial(&DvrPcmWorkingRam, &DvrDataBuffer[0], DVRPCM_FRAME_SIZE);

	SACM_VC3_Initial(&Vc3ApiWorkingRam, &Vc3PcmBuffer);
	SACM_VC3_Mode(Vc3Mode, &Vc3KernelWorkingRam);
	SACM_VC3_Mode(VC3_CHANGE_SPEED_MODE, &Vc3KernelWorkingRam2);
	SACM_VC3_ChangeSpeedMode_SetSpeed(Vc3ChangeSpeed);
	SACM_VC3_ShiftPitchMode_SetPitch(Vc3ShiftPitch);

  APP_SwVolCtrl_Init();                                                   // Software volume control init.
	APP_SwVolCtrl_SetVolGain(0, 5);
	APP_SwVolCtrl_SetVolGain(1, 9);

	KeyScan_Initial(&KeyScanWorkingRam);                                    // key scan init

  /*
	 * IOA[15:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x0000FF00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x0000FF00, 0);

  while(1)
	{
		WDT_Clear();
		SACM_DVRPCM_ServiceLoop();
		KeyScan_ServiceLoop();

		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                                          // IOA0+VDD:
				if(Vc3EffectEn == 0)
				{
					Vc3EffectEn = 1;
					Vc3EffectEnable();
					GPIOA->OBUF |= BIT8;
				}
				else
				{
					Vc3EffectEn = 0;
					Vc3EffectDisable();
					GPIOA->OBUF &= ~BIT8;
				}
        break;

			case 0x02:                                                         // IOA1+VDD: Play next song
				SPIFC_AutoMode(SPIFC_2IO_MODE);
				PlayCon = 0;
				SACM_DVRPCM_Stop();
				SACM_DVRPCM_Play(GetPcmStartAddr(PcmPlayIdx), DVRPCM_DAC_CH0 , DVRPCM_AUTO_RAMP_UP + DVRPCM_AUTO_RAMP_DOWN);
			  PcmPlayIdx = ++PcmPlayIdx > PcmNum ? 1 : PcmPlayIdx;
				break;

			case 0x04:	                                                        // IOA2+VDD: Recording
				PlayCon = 0;
				SACM_DVRPCM_Stop();
			  SACM_DVRPCM_Initial(&DvrPcmWorkingRam, &DvrDataBuffer[0], DVRPCM_FRAME_SIZE);
				SACM_DVRPCM_SetRecLength(0x10000);
				SPIFC_BlockErase(0x00200000);
			  SPIFC_BlockErase(0x00210000);
			  SPIFC_BlockErase(0x00220000);
			  SPIFC_BlockErase(0x00230000);
			  SACM_DVRPCM_Rec((int16_t *) 0x00200000);
				break;

			case 0x08:                                                          // IOA3+VDD: Playback
				PlayCon = 0;
				SACM_DVRPCM_Stop();
			  SACM_DVRPCM_Norm((int16_t *)0x04200000, (int16_t *)0x04220000);
			  SACM_DVRPCM_Play((int16_t *)0x04220000, DVRPCM_DAC_CH0, DVRPCM_AUTO_RAMP_UP + DVRPCM_AUTO_RAMP_DOWN);
			  break;

			case 0x10:                                                          // IOA4+VDD:
        Vc3ChangeSpeed = ++Vc3ChangeSpeed > MAX_VC3_SPEED_CTRL_LIMIT ? MAX_VC3_SPEED_CTRL_LIMIT : Vc3ChangeSpeed;
			  SACM_VC3_ChangeSpeedMode_SetSpeed(Vc3ChangeSpeed);
				break;

      case 0x20:
        Vc3ChangeSpeed = --Vc3ChangeSpeed < MIN_VC3_SPEED_CTRL_LIMIT ? MIN_VC3_SPEED_CTRL_LIMIT : Vc3ChangeSpeed;
			  SACM_VC3_ChangeSpeedMode_SetSpeed(Vc3ChangeSpeed);
				break;

			case 0x40:                                                          // IOA4+VDD:
        Vc3ShiftPitch = ++Vc3ShiftPitch > MAX_VC3_SHIFT_PITCH_LIMIT ? MAX_VC3_SHIFT_PITCH_LIMIT : Vc3ShiftPitch;
			  SACM_VC3_ShiftPitchMode_SetPitch(Vc3ShiftPitch);
			  break;

			case 0x80:                                                          // IOA5+VDD:
        Vc3ShiftPitch = --Vc3ShiftPitch < MIN_VC3_SHIFT_PITCH_LIMIT ? MIN_VC3_SHIFT_PITCH_LIMIT : Vc3ShiftPitch;
			  SACM_VC3_ShiftPitchMode_SetPitch(Vc3ShiftPitch);
			  break;
	  }

		if((PlayCon != 0) && (SACM_DVRPCM_Check_Con() == 0))
		{
			SACM_DVRPCM_Play_Con(GetPcmStartAddr(PcmPlayIdx++), DVRPCM_DAC_CH0, DVRPCM_AUTO_RAMP_UP + DVRPCM_AUTO_RAMP_DOWN);
			PcmPlayIdx = PcmPlayIdx > PcmNum ? 1 : PcmPlayIdx;
		}
	}
}
