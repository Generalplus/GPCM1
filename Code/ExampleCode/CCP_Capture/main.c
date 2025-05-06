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
	 * CCPx Capture init
	 */
	CCP0_Capture_Initial(IoSel_IOA0_3, CAP_TRG_RISING);
	CCP1_Capture_Initial(CAP_TRG_RISING);

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
        CCP0_Timer_Reload(CCP0_CAPTMR_PLOAD);    // Timer counter reset
        break;

      case 0x20:                                                                              // IOA5+VDD:
        CCP0_Close();
        CCP1_Close();
        break;

			case 0x40:                                                                              // IOA6+VDD:
        CCP0_CAPx_Ctrl(CCP_CAPCTRL_CAP0_ENABLE | CCP_CAPCTRL_CAP1_ENABLE);    // Enable CCP0 Pin.0 & 1 and disable Pin.2 & 3
        CCP1_CAPx_Ctrl(CCP_CAPCTRL_CAP2_ENABLE | CCP_CAPCTRL_CAP3_ENABLE);    // Enable CCP1 Pin.2 & 3 and disable Pin.0 & 1
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
	uint32_t CCPTimer_CurValue;

	if(READ_BIT(CCP0->INTSTS, CCP_INTEN_TMR_INT_FLAG))          // CCP0_Timer INT
	{
    XOR_BIT(GPIOA->OBUF, BIT8);                               // Toggle IOA.8
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTEN_TMR_INTF_MSK, CCP_INTEN_TMR_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CAP0_INT_FLAG))        // CCP0_CAP0 INT
	{
    XOR_BIT(GPIOA->OBUF, BIT9);                               // Toggle IOA.9
		CCPTimer_CurValue = READ_REG(CCP0->CCPR0);
    CCP0_Timer_Reload(CCP0_CAPTMR_PLOAD);                                      // Reset Timer
		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CAP0_INTF_MSK, CCP_INTSTS_CAP0_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CAP1_INT_FLAG))        // CCP0_CAP1 INT
	{
    XOR_BIT(GPIOA->OBUF, BIT10);                               // Toggle IOA.10
		CCPTimer_CurValue = READ_REG(CCP0->CCPR1);

		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CAP1_INTF_MSK, CCP_INTSTS_CAP1_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CAP2_INT_FLAG))        // CCP0_CAP2 INT
	{
    XOR_BIT(GPIOA->OBUF, BIT11);                               // Toggle IOA.11
		CCPTimer_CurValue = READ_REG(CCP0->CCPR2);

		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CAP2_INTF_MSK, CCP_INTSTS_CAP2_INT_FLAG);
	}

	if(READ_BIT(CCP0->INTSTS, CCP_INTSTS_CAP3_INT_FLAG))        // CCP0_CAP3 INT
	{
    XOR_BIT(GPIOA->OBUF, BIT12);                               // Toggle IOA.12
		CCPTimer_CurValue = READ_REG(CCP0->CCPR3);

		CLEAR_FLAG(CCP0->INTSTS, CCP_INTSTS_CAP3_INTF_MSK, CCP_INTSTS_CAP3_INT_FLAG);
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
	uint32_t CCPTimer_CurValue;

	if(READ_BIT(CCP1->INTSTS, CCP_INTEN_TMR_INT_FLAG))          // CCP1_Timer INT
	{
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTEN_TMR_INTF_MSK, CCP_INTEN_TMR_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CAP0_INT_FLAG))        // CCP1_CAP0 INT
	{
		CCPTimer_CurValue = READ_REG(CCP1->CCPR0);
    CCP1_Timer_Reload(CCP1_CAPTMR_PLOAD);                                      // Reset Timer
		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CAP0_INTF_MSK, CCP_INTSTS_CAP0_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CAP1_INT_FLAG))        // CCP1_CAP1 INT
	{
		CCPTimer_CurValue = READ_REG(CCP1->CCPR1);

		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CAP1_INTF_MSK, CCP_INTSTS_CAP1_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CAP2_INT_FLAG))        // CCP1_CAP2 INT
	{
		CCPTimer_CurValue = READ_REG(CCP1->CCPR2);

		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CAP2_INTF_MSK, CCP_INTSTS_CAP2_INT_FLAG);
	}

	if(READ_BIT(CCP1->INTSTS, CCP_INTSTS_CAP3_INT_FLAG))        // CCP1_CAP3 INT
	{
		CCPTimer_CurValue = READ_REG(CCP1->CCPR3);

		CLEAR_FLAG(CCP1->INTSTS, CCP_INTSTS_CAP3_INTF_MSK, CCP_INTSTS_CAP3_INT_FLAG);
	}

}

