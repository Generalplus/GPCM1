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
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();
  NVIC_DisableIRQ(DMA_IRQn);

  /*
	 * IOA[23:20] output low
	 */
  GPIO_SetMode(GPIOA, 0x00F00000, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00F00000, 0);

  /*
	 * Initialize external interrupt 0
	 *  - External interrupt IO: IOA0
	 *  - Interrupt trigger method: rising edge
	 */
	GPIO_ExtInterrupt_Init(EXT_INT0, EXT_INT_RISING_EDGE_TRIG, EXT_INT_SEL_IOA0);
	GPIO_ExtInterrupt_Enable(EXT_INT0);
	NVIC_EnableIRQ(EXTI0_IRQn);

  /*
	 * Initialize external interrupt 1
	 *  - External interrupt IO: IOA1
	 *  - Interrupt trigger method: falling edge
	 */
	GPIO_ExtInterrupt_Init(EXT_INT1, EXT_INT_FALLING_EDGE_TRIG, EXT_INT_SEL_IOA1);
	GPIO_ExtInterrupt_Enable(EXT_INT1);
	NVIC_EnableIRQ(EXTI1_IRQn);

  /*
	 * Initialize external interrupt 2
	 *  - External interrupt IO: IOA2
	 *  - Interrupt trigger method: rising edge
	 */
	GPIO_ExtInterrupt_Init(EXT_INT2, EXT_INT_RISING_EDGE_TRIG, EXT_INT_SEL_IOA2);
	GPIO_ExtInterrupt_Enable(EXT_INT2);
	NVIC_EnableIRQ(EXTI2_IRQn);

  /*
	 * Initialize external interrupt 3
	 *  - External interrupt IO: IOA3
	 *  - Interrupt trigger method: falling edge
	 */
	GPIO_ExtInterrupt_Init(EXT_INT3, EXT_INT_FALLING_EDGE_TRIG, EXT_INT_SEL_IOA3);
	GPIO_ExtInterrupt_Enable(EXT_INT3);
	NVIC_EnableIRQ(EXTI3_IRQn);

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

/**
 * @brief
 *   External interrupt 1 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void EXTI1_IRQHandler(void)
{
  XOR_BIT(GPIOA->OBUF, BIT21);																		   // Toggle IOA[21]
	ITU->EXTIFLG = ITU_EXTIEN_EXT1_INT_ENABLE;                         // Clear external interrupt 1 flag
}

/**
 * @brief
 *   External interrupt 2 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void EXTI2_IRQHandler(void)
{
  XOR_BIT(GPIOA->OBUF, BIT22);																		   // Toggle IOA[22]
	ITU->EXTIFLG = ITU_EXTIEN_EXT2_INT_ENABLE;                         // Clear external interrupt 2 flag
}

/**
 * @brief
 *   External interrupt 3 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void EXTI3_IRQHandler(void)
{
  XOR_BIT(GPIOA->OBUF, BIT23);																		   // Toggle IOA[23]
	ITU->EXTIFLG = ITU_EXTIEN_EXT3_INT_ENABLE;                         // Clear external interrupt 3 flag
}
