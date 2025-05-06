/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1F I2S Rx Master mode example code
 *    P.S: Use with INMP441 Mic I2S Tx demo.
 * @Function:
 *            I2S IOA[21:19](Rx only, Slave mode)
 *            GPCM1F CLK: IOA[19] <=> SCK INMP441
 *                    SLR: IOA[20] <=> WS
 *                    SDA: IOA[21] <=> SD
 *                        VDD(3V) <=> L/R
 *                        VDD(3V) <=> VDD
 *                        GND     <=> GND
 * @Version: V0.9
 *
 * @Date: 2024.10.24
 *
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"

#define    MAX_VOL_GAIN       (63)
#define    MIN_VOL_GAIN       (1)


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif

uint32_t ScanedKey;
uint8_t VolGain = 15;

/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/
/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void DmaIsr_Dma0Trigger()
{
	DMA_Trigger(DMA0, (uint32_t)&I2S->DATA, (uint32_t)&DAC->DAC_CH0_DMA_DATA0, 320);    // DMA0 trigger
}


/*
 * @brief
 *				I2S Interrupt Handler0
 * @param
 * 				None
 * @return
 * 				None
 *
 */
void I2S_IRQHandler(void)
{
	// DAC->DAC_CH0_DATA = I2S->DATA;

	I2S->STS|= I2S_STS_HALF_FULL_FLAG;
}


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

	KeyScan_Initial(&KeyScanWorkingRam);                               // key scan init.

  /*
	 * Timer0 init
	 */
  TIMER_Open(TM0);
	TIMER_SetFreq(TM0, (16000 * 4));	                                               // DAC sample rate: DsAdcSmpRate x 4, for H/W 4x upsampling

	/*
	 * Audio Output Initial
	 */
	DAC_Open();
	DAC_Scale_Enable();
	DAC_CH0_Init(DAC_TRG_SEL_TM0);
	DAC_AudioPwm_Open();
	DAC_SetAudPwmGain(VolGain);
	DAC_AudioPwm_IP_Enable();

	/*
	 * Init I2S I/F for GPCE4F I2S setup.
	 */
	I2S_Init();

  /*
	 * DMA0 init
	 */
  DMA_Init(DMA0, DMA_REQSEL_DAC_CH0, DMA_SRC_DATA_16B, DMA_SRC_ADDR_FIX, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
  // DMA_Init(DMA0, DMA_REQSEL_I2S, DMA_SRC_DATA_16B, DMA_SRC_ADDR_FIX, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
	DMA_InstallIsrService(DMA0, DmaIsr_Dma0Trigger);
	DMA_EnableInt(DMA0);
	NVIC_EnableIRQ(DMA_IRQn);

	DMA_Trigger(DMA0, (uint32_t)&I2S->DATA, (uint32_t)&DAC->DAC_CH0_DMA_DATA0, 320);    // DMA0 trigger

  while(1)
	{
		WDT_Clear();

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                                     // IOA0+VDD: Volume Up
        VolGain = ++VolGain >= MAX_VOL_GAIN ? MAX_VOL_GAIN : VolGain;
        DAC_SetAudPwmGain(VolGain);
        break;

		  case 0x02:                                                     // IOA1+VDD: Volume Dn
        VolGain = --VolGain <= MIN_VOL_GAIN ? MIN_VOL_GAIN : VolGain;
        DAC_SetAudPwmGain(VolGain);
        break;
		}
	}
}


