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
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
KEYSCAN_WORKING_RAM KeyScanWorkingRam;
uint32_t ScanedKey;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{	
  SystemInit();
	MODIFY_REG(CLOCK->AHBCKSEL, CLOCK_AHBCKSEL_SYS32K_SEL_MSK, CLOCK_AHBCKSEL_SYS32K_SEL_IOSC32K);

  /*
	 * IOA[10:8] output low
	 */	
  GPIO_SetMode(GPIOA, 0x00000700, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00000700, 0);
	
	KeyScan_Initial(&KeyScanWorkingRam);           // Key scan init
	
  while(1)
	{
		WDT_Clear();
		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
		  case 0x01:                                 // IOA0+VDD: Setting Timer0 interrupt frequenct = 8Khz 
			  TIMER_Open(TM0);
			  TIMER_SetFreq(TM0, 8000);
			  TIMER_EnableInt(TM0);
			  NVIC_EnableIRQ(TIMER0_IRQn);
        break;

		  case 0x02:                                 // IOA1+VDD: Setting Timer1 interrupt frequenct = 16Khz			
			  TIMER_Open(TM1);
			  TIMER_SetFreq(TM1, 16000);
			  TIMER_EnableInt(TM1);
			  NVIC_EnableIRQ(TIMER1_IRQn);
        break;

		  case 0x04:                                 // IOA2+VDD: Setting Timer2 interrupt frequenct = 10hz
			  TIMER_Open(TM2);
			  TIMER_SetClkIn(TM2, TM_CLK_SEL_32K);
			  TIMER_SetFreq(TM2, 10);
			  TIMER_EnableInt(TM2);
			  NVIC_EnableIRQ(TIMER2_IRQn);
        break;		
		}		
	}
}

/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/

/** 
 * @brief  
 *   Timer0 IRQ handler
 * @param 
 *   None.
 * @return 
 *   None.
 */
void TIMER0_IRQHandler(void)
{  
	GPIOA->OBUF ^= BIT8;                           // Toggle IOA[8]
	TM_INT->INTSTS = TIMER_INTSTS_TM0_INT_FLAG;    //	Clear Timer0 intterupt flag
}

/** 
 * @brief  
 *   Timer1 IRQ handler
 * @param 
 *   None.
 * @return 
 *   None.
 */
void TIMER1_IRQHandler(void)
{  
	GPIOA->OBUF ^= BIT9;                           // Toggle IOA[9] 
	TM_INT->INTSTS = TIMER_INTSTS_TM1_INT_FLAG;    //	Clear Timer1 intterupt flag
}

/** 
 * @brief  
 *   Timer2 IRQ handler
 * @param 
 *   None.
 * @return 
 *   None.
 */
void TIMER2_IRQHandler(void)
{  
	GPIOA->OBUF ^= BIT10;                          // Toggle IOA[10]  
	TM_INT->INTSTS = TIMER_INTSTS_TM2_INT_FLAG;    //	Clear Timer2 intterupt flag
}
