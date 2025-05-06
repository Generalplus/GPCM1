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
uint16_t PWMIODuty = 0;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  /*
	 * CCPx PWMIO init
	 */
  CCP0_PWMIO_Open(IoSel_IOA13_16);    // IOA[16:13] or IOA[3:0]
  CCP1_PWMIO_Open();

	KeyScan_Initial(&KeyScanWorkingRam);                                                        // Key scan init

  while(1)
	{
		WDT_Clear();

		if(PWMIODuty < CCP_PWM_FullLo)
		{
      PWMIODuty+=1;
		}
		else
		{
      PWMIODuty = 0;
		}
		CCP0_PWMIOx_SetDuty(PWM0,PWMIODuty);
		CCP0_PWMIOx_SetDuty(PWM1,PWMIODuty);

/*
		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
      case 0x01:                                                                              // IOA0+VDD:
        break;

		  case 0x02:                                                                              // IOA1+VDD:
        break;

		  case 0x04:                                                                              // IOA2+VDD:
         // CCP0_PWMIOx_Ctrl(CCP_PWMCTRL_PWM0_ENABLE | CCP_PWMCTRL_PWM1_ENABLE); // PWM0 & 1 enabled. PWM2 & 3 disabled.
         CCP1_PWMIOx_Ctrl(CCP_PWMCTRL_PWM2_ENABLE | CCP_PWMCTRL_PWM3_ENABLE); // PWM2 & 3 enabled. PWM0 & 1 disabled.
        break;

		  case 0x08:                                                                              // IOA3+VDD:
        // CCP0_PWMxx_ModeSelect(PWM01, CCP_PWMCTRL_PWM01_COMPLEMENT);
        // CCP0_PWMxx_ModeSelect(PWM01, CCP_PWMCTRL_PWM01_INDEPENDENT);
        // CCP0_PWMxx_ModeSelect(PWM23, CCP_PWMCTRL_PWM23_COMPLEMENT);
        // CCP0_PWMxx_ModeSelect(PWM23, CCP_PWMCTRL_PWM23_INDEPENDENT);
        CCP1_PWMxx_ModeSelect(PWM01, CCP_PWMCTRL_PWM01_COMPLEMENT);
        // CCP1_PWMxx_ModeSelect(PWM01, CCP_PWMCTRL_PWM01_INDEPENDENT);
        CCP1_PWMxx_ModeSelect(PWM23, CCP_PWMCTRL_PWM23_COMPLEMENT);
        // CCP1_PWMxx_ModeSelect(PWM23, CCP_PWMCTRL_PWM23_INDEPENDENT);
        break;

		  case 0x10:                                                                              // IOA4+VDD:
        CCP0_Close();
        CCP1_Close();
        break;

      case 0x20:                                                                              // IOA5+VDD:
        CCP0_PWMIO_Open(IoSel_IOA13_16);
        CCP1_PWMIO_Open();
        break;

			case 0x40:                                                                              // IOA6+VDD:
        // CCP0_PWMIOx_Inverse(PWM0);
        // CCP0_PWMIOx_Inverse(PWM2);
        CCP1_PWMIOx_Inverse(PWM1);
        CCP1_PWMIOx_Inverse(PWM3);
			  break;

      case 0x80:                                                                              // IOA7+VDD:
        // CCP0_PWMIOx_SetDuty(PWM0,0x80);
        // CCP0_PWMIOx_SetDuty(PWM1,CCP_PWM_FullLo);
        CCP1_PWMIOx_SetDuty(PWM2,0x80);
        CCP1_PWMIOx_SetDuty(PWM3,CCP_PWM_FullHi);
        break;
		}
	*/
	}
}


/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/
/**
 * @brief
 *   CCP IRQ Handler
 * @param
 *   None.
 * @return
 *   None.
 */

