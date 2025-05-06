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
#include "CCP_GPCM1Fx.h"


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
	 * CCPx Compare mode initial
	 */
	CCP0_Compare_Initial();
  // CCP1_Compare_Initial();

  /*
	 * IOA[12:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x00001F00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00001F00, 0);

	KeyScan_Initial(&KeyScanWorkingRam);                                                        // Key scan init

  while(1)
	{
		WDT_Clear();

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
      case 0x01:                                                                              // IOA0+VDD:
        break;

		  case 0x02:                                                                              // IOA1+VDD:
        break;

		  case 0x04:                                                                              // IOA2+VDD:
        break;

		  case 0x08:                                                                              // IOA3+VDD:
        break;

		  case 0x10:                                                                              // IOA4+VDD:

        break;

      case 0x20:                                                                              // IOA5+VDD:
        CCP0_Close();
        CCP1_Close();
        break;

			case 0x40:                                                                              // IOA6+VDD:
        CCP0_CMPx_Ctrl(CCP_TMCMPCTRL_CMP2_ENABLE | CCP_TMCMPCTRL_CMP3_ENABLE);    // Enable CMP2 & 3
        // CCP1_CMPx_Ctrl(CCP_TMCMPCTRL_CMP0_ENABLE | CCP_TMCMPCTRL_CMP1_ENABLE);    // Enable CMP0 & 1
			  break;

      case 0x80:                                                                              // IOA7+VDD:
        break;
		}
	}
}


/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/
/**
 * @brief
 *   CCP0 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void CCP0_IRQHandler(void)
{
	if(READ_BIT(CCP0->INTSTS, CCP_INTEN_TMR_INT_FLAG))          // CCP0_Timer INT
	{
    XOR_BIT(GPIOA->OBUF, BIT8);                               // Toggle IOA.8
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTEN_TMR_INTF_MSK, CCP_INTEN_TMR_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CMP0_INT_FLAG))        // CCP0_CMP0 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT9);                               // Toggle IOA.9
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CMP0_INTF_MSK, CCP_INTSTS_CMP0_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CMP1_INT_FLAG))        // CCP0_CMP1 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT10);                               // Toggle IOA.10
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CMP1_INTF_MSK, CCP_INTSTS_CMP1_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CMP2_INT_FLAG))        // CCP0_CMP2 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT11);                               // Toggle IOA.11
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CMP2_INTF_MSK, CCP_INTSTS_CMP2_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CMP3_INT_FLAG))        // CCP0_CMP3 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT12);                               // Toggle IOA.12
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CMP3_INTF_MSK, CCP_INTSTS_CMP3_INT_FLAG);
	}
}

/**
 * @brief
 *   CCP1 IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */
void CCP1_IRQHandler(void)
{
	if(READ_BIT(CCP1->INTSTS, CCP_INTEN_TMR_INT_FLAG))          // CCP1_Timer INT
	{
    XOR_BIT(GPIOA->OBUF, BIT8);                               // Toggle IOA.8
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTEN_TMR_INTF_MSK, CCP_INTEN_TMR_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CMP0_INT_FLAG))        // CCP1_CMP0 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT9);                               // Toggle IOA.9
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CMP0_INTF_MSK, CCP_INTSTS_CMP0_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CMP1_INT_FLAG))        // CCP1_CMP1 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT10);                               // Toggle IOA.10
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CMP1_INTF_MSK, CCP_INTSTS_CMP1_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CMP2_INT_FLAG))        // CCP1_CMP2 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT11);                               // Toggle IOA.11
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CMP2_INTF_MSK, CCP_INTSTS_CMP2_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CMP3_INT_FLAG))        // CCP1_CMP3 INT
	{
		XOR_BIT(GPIOA->OBUF, BIT12);                               // Toggle IOA.12
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CMP3_INTF_MSK, CCP_INTSTS_CMP3_INT_FLAG);
	}
}
