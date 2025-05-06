/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   Sleep & Key Change Wake up example code
 *     Function: Enter the deep sleep mode automatically after power on
 *     Key change wake up IO: IOA[2:0] (Default)
 * @Version: V0.9
 *
 * @Date: 2022.03.25
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
uint32_t iCount;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  /*
	 * IOA[2:0] input pull-low
	 */
  GPIO_SetMode(GPIOA, (BIT0 | BIT1 | BIT2), GPIO_MODE_INPUT);
  MODIFY_REG(GPIOA->OBUF, (BIT0 | BIT1 | BIT2), 0);
  // MODIFY_REG(GPIOA->OBUF, BIT15, 0x8000);      // IOA.15 pull-high


  /*
	 * IOA[8] output low
	 */
  GPIO_SetMode(GPIOA, BIT8, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, BIT8, 0);

  /*
	 * KeyChange wakeup init
	 * - IOA[2:0]	key change can wake up IC
	 */
	GPIO_KeyChangeWakeupIoSel(KEYCHG_WAKEUP_EN_IOA0 | KEYCHG_WAKEUP_EN_IOA1 | KEYCHG_WAKEUP_EN_IOA2);
	GPIO_KeyChangeWakeupIntEnable();
  NVIC_EnableIRQ(KEYCHG_IRQn);

  while(1)
	{
		for(iCount = 0; iCount < 1000000; iCount++)
		{
			GPIOA_OBIT->OBIT08 = 0xFFFFFFFF;
			WDT_Clear();
		}
		GPIOA_OBIT->OBIT08 = 0x00000000;

		iCount = GPIOA->IDATA;	                             // Latch IOA DATA
		SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;                    // Deep sleep mode
	  __WFI();
	}
}

/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/

/**
 * @brief
 *   KeyChange IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void KEYCHG_IRQHandler(void)
{
	IOFUNC->STS = GPIOFUNC_STS_INTF_FLAG;
}
