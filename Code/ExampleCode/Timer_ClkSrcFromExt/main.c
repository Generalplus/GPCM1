/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   main.c
 * @Version:
 *
 * @Date:
 *
 * @Abstract: Timer using external CLK src.
 *            CLK Input Pin: IOA[0]
 *            TM0 INT Output toggle Pin: IOA[8]
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  /*
	 * IOA[23:20 & 10:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x00F00700, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00F00700, 0);

  /*
	 * Initialize external interrupt 0
	 *  - External interrupt IO: IOA0
	 *  - Interrupt trigger method: rising edge
	 */
	GPIO_ExtInterrupt_Init(EXT_INT0, EXT_INT_RISING_EDGE_TRIG, EXT_INT_SEL_IOA0);

  TIMER_Open(TM0);
  TIMER_SetFreq(TM0, 8000);
  TIMER_EnableInt(TM0);
  NVIC_EnableIRQ(TIMER0_IRQn);

  while(1)
	{
		WDT_Clear();
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
 *   External interrupt 0 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void EXTI0_IRQHandler(void)
{
  XOR_BIT(GPIOA->OBUF, BIT20);																		   // Toggle IOA[20]
	ITU->EXTIFLG = ITU_EXTIEN_EXT0_INT_ENABLE;                         // Clear external interrupt 0 flag
}


