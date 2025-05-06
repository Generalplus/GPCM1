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


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/

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
	DMA_Trigger(DMA0, (uint32_t)&DS_ADC->DATA, (uint32_t)&DAC->DAC_CH0_DMA_DATA0, 320);    // DMA0 trigger
}


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  uint32_t DsAdcSmpRate;

  SystemInit();

  /*
	 * DAC init
	 */
	DAC_Open();
	DAC_Scale_Enable();
	DAC_CH0_Init(DAC_TRG_SEL_TM0);
	DAC_AudioPwm_Open();
	DAC_SetAudPwmGain(5);
	DAC_AudioPwm_IP_Enable();

  DsAdcSmpRate = DSADC_Init(16000);                                                      // DSADC init

  /*
	 * Timer0 init
	 */
  TIMER_Open(TM0);
	TIMER_SetFreq(TM0, (DsAdcSmpRate * 4));	                                               // DAC sample rate: DsAdcSmpRate x 4, for H/W 4x upsampling

  /*
	 * DMA0 init
	 */
  DMA_Init(DMA0, DMA_REQSEL_DAC_CH0, DMA_SRC_DATA_16B, DMA_SRC_ADDR_FIX, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
	DMA_InstallIsrService(DMA0, DmaIsr_Dma0Trigger);
	DMA_EnableInt(DMA0);
	NVIC_EnableIRQ(DMA_IRQn);

	DMA_Trigger(DMA0, (uint32_t)&DS_ADC->DATA, (uint32_t)&DAC->DAC_CH0_DMA_DATA0, 320);    // DMA0 trigger

  while(1)
	{
		WDT_Clear();

	}
}
