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

  /*
	 * TB init
	 */
	TIMEBASE_Open(TB_CLK_SEL_IOSC32K);
	TIMEBASE_EnableInt(TB_INT_2HZ);
	NVIC_EnableIRQ(TIMEBASE_IRQn);

  /*
	 * IOA[12:8] and IOA[15] output low
	 */
  GPIO_SetMode(GPIOA, 0x00009F00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00009F00, 0);

  while(1)
  {
    WDT_Clear();

    WDT_Close();
    WDG->KEYCODE = WDG_KEYCODE_ACCESS_ENABLE;
    MODIFY_REG(WDG->CTRL, WDG_CTRL_CLK_SEL_MSK, WDG_CLK_32768_DIV_64);      // 8s, default count = 4096
    MODIFY_REG(WDG->CTRL, WDG_CTRL_CNT_MSK, ((2304 << WDG_CTRL_CNT_POS) & WDG_CTRL_CNT_MSK));  // 4.5 sec
    // MODIFY_REG(WDG->CTRL, WDG_CTRL_CNT_MSK, ((0x64 << WDG_CTRL_CNT_POS) & WDG_CTRL_CNT_MSK));   // 2 sec
    WDG->KEYCODE = WDG_KEYCODE_ACCESS_DISABLE;
    WDT_Open();

    while(1)
    {
      __NOP();
    }

    // DrvUart_SendString("Event Sleep mode test.\r\n ");
    READ_REG(GPIOA->IDATA);	                            //IO status latched.
    SCB->SCR = 0x00000000; // Sleep Mode
    __WFE();               // Sleep Mode
    __WFE();               // Sleep Mode

    // DrvUart_SendString("Deep sleep mode test.\r\n");
    READ_REG(GPIOA->IDATA);	                            //IO status latched.
    SCB->SCR = (1UL << 2); // Deep Sleep Mode
    __WFI();
    __NOP();
    __NOP();
  }


	KeyScan_Initial(&KeyScanWorkingRam);                                                        // Key scan init

  while(1)
	{
		WDT_Clear();

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
      case 0x01:                                                                              // IOA0+VDD: Open TB. Clock source from IOSC32K.
			  TIMEBASE_Open(TB_CLK_SEL_IOSC32K);
        break;

		  case 0x02:                                                                              // IOA1+VDD: Open TB. Clock source from XTAL32K.
			  TIMEBASE_Open(TB_CLK_SEL_XTAL32K);
        break;

		  case 0x04:                                                                              // IOA2+VDD: Enable TB 2Hz interrupt.
			  TIMEBASE_EnableInt(TB_INT_2HZ);
        break;

		  case 0x08:                                                                              // IOA3+VDD: Enable TB 16Hz/64Hz interrupt.
				TIMEBASE_EnableInt(TB_INT_16HZ | TB_INT_64HZ);
        break;

		  case 0x10:                                                                              // IOA4+VDD: Enable TB 512Hz/2KHz/4KHz interrupt.
				TIMEBASE_EnableInt(TB_INT_512HZ | TB_INT_2KHZ | TB_INT_4KHZ);
        break;

      case 0x20:                                                                              // IOA5+VDD: Disable TB all interrupt.
				TIMEBASE_DisableInt(TB_INT_2HZ | TB_INT_16HZ | TB_INT_64HZ | TB_INT_512HZ | TB_INT_2KHZ | TB_INT_4KHZ);
        break;

			case 0x40:                                                                              // IOA6+VDD: Reset TB count.
			  TIMEBASE_Reset();
			  break;

      case 0x80:                                                                              // IOA7+VDD: Close TB.
				TIMEBASE_Close();
        break;
		}
	}
}


/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/

/**
 * @brief
 *   TimeBase IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void TIMEBASE_IRQHandler(void)
{
	if((TIMEBASE->STS & TIMEBASE_STS_2HZ_INTF_FLAG) != 0)
	{
		XOR_BIT(GPIOA->OBUF, BIT8);																	                              // Toggle IOA[8]
    TIMEBASE->STS = TIMEBASE_STS_2HZ_INTF_FLAG;	                                              // Clear TimeBase 2Hz interrupt flag
	}

	if((TIMEBASE->STS & TIMEBASE_STS_16HZ_INTF_FLAG) != 0)
	{
	  XOR_BIT(GPIOA->OBUF, BIT9);																		                            // Toggle IOA[9]
		TIMEBASE->STS = TIMEBASE_STS_16HZ_INTF_FLAG;                                              // Clear TimeBase 16Hz interrupt flag
	}

	if((TIMEBASE->STS & TIMEBASE_STS_64HZ_INTF_FLAG) != 0)
	{
		XOR_BIT(GPIOA->OBUF, BIT10);																		                          // Toggle IOA[10]
		TIMEBASE->STS = TIMEBASE_STS_64HZ_INTF_FLAG;                                              // Clear TimeBase 64Hz interrupt flag
	}

	if((TIMEBASE->STS & TIMEBASE_STS_512HZ_INTF_FLAG) != 0)
	{
		XOR_BIT(GPIOA->OBUF, BIT11);																		                          // Toggle IOA[11]
		TIMEBASE->STS = TIMEBASE_STS_512HZ_INTF_FLAG;	                                            // Clear TimeBase 64Hz interrupt flag
	}

	if((TIMEBASE->STS & TIMEBASE_STS_2KHZ_INTF_FLAG) != 0)
	{
		XOR_BIT(GPIOA->OBUF, BIT12);																		                          // Toggle IOA[12]
		TIMEBASE->STS = TIMEBASE_STS_2KHZ_INTF_FLAG;                                              // Clear TimeBase 2KHz interrupt flag
	}

	if((TIMEBASE->STS & TIMEBASE_STS_4KHZ_INTF_FLAG) != 0)
	{
		XOR_BIT(GPIOA->OBUF, BIT15);																		                          // Toggle IOA[15]
		TIMEBASE->STS = TIMEBASE_STS_4KHZ_INTF_FLAG;                                              // Clear TimeBase 4KHz interrupt flag
	}
}
