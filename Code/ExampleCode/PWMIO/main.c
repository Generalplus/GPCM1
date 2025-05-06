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
#if defined(__CC_ARM)
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#endif 

uint32_t ScanedKey;
uint8_t IoToggleEn;


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/

/**
 * @brief
 *   Initialize PWMIO: IOA[12:5]
 * @param
 *   None.
 * @return
 *   None.
 */
void PwmIo_Init(void)
{
  SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_PWMIO_CLK_ENABLE);	         // PWMIO clock enable
	
	PWMIO->CTRL0 = PWMIO_CTRL0_SYNC_ENABLE | PWMIO_CTRL_CLK_SEL_FCPU_DIV_16;
	PWMIO->CTRL1 = PWMIO_CTRL_PWM0_ENABLE | PWMIO_CTRL_PWM1_ENABLE | PWMIO_CTRL_PWM2_ENABLE | PWMIO_CTRL_PWM3_ENABLE |
	               PWMIO_CTRL_PWM4_ENABLE | PWMIO_CTRL_PWM5_ENABLE | PWMIO_CTRL_PWM6_ENABLE | PWMIO_CTRL_PWM7_ENABLE;
	
	PWMIO->PERIOD_CTRL = PWMIO_CTRL_PERIOD0_256 | PWMIO_CTRL_PERIOD1_256 | PWMIO_CTRL_PERIOD2_256 | PWMIO_CTRL_PERIOD3_256 |
                       PWMIO_CTRL_PERIOD4_256 | PWMIO_CTRL_PERIOD5_256 | PWMIO_CTRL_PERIOD6_256 | PWMIO_CTRL_PERIOD7_256;
	
	PWMIO->PWMIO0_Duty = 10;
	PWMIO->PWMIO1_Duty = 20;
	PWMIO->PWMIO2_Duty = 40;
	PWMIO->PWMIO3_Duty = 70;
	PWMIO->PWMIO4_Duty = 110;
	PWMIO->PWMIO5_Duty = 150;
	PWMIO->PWMIO6_Duty = 200;
	PWMIO->PWMIO7_Duty = 255;	
}


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	IoToggleEn = 0;
	
  SystemInit();
	
	KeyScan_Initial(&KeyScanWorkingRam);                               // key scan init.
	
  /*
	 * IOA[12:5] output low
	 */
  GPIO_SetMode(GPIOA, 0x0001FE0, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x0001FE0, 0);
	
	PwmIo_Init();
	
  while(1)
	{
		WDT_Clear();
		
		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:                                                     // IOA0+VDD: Mask PWMIO0, PWMIO2, PWMIO4, PWMIO6.
        PWMIO->CTRL1 |= (PWMIO_CTRL_PWM0_MSK_ON | PWMIO_CTRL_PWM2_MSK_ON | PWMIO_CTRL_PWM4_MSK_ON | PWMIO_CTRL_PWM6_MSK_ON);
        break;
			
			case 0x02:                                                     // IOA1+VDD: Unmask PWMIO0, PWMIO2, PWMIO4, PWMIO6.
				PWMIO->CTRL1 &= ~(PWMIO_CTRL_PWM0_MSK_ON | PWMIO_CTRL_PWM2_MSK_ON | PWMIO_CTRL_PWM4_MSK_ON | PWMIO_CTRL_PWM6_MSK_ON);
				break;
			
			case 0x04:                                                     // IOA2+VDD: PWMIO inverse output.
				PWMIO->CTRL1 |= (PWMIO_CTRL_PWM0_INV_ON | PWMIO_CTRL_PWM1_INV_ON | PWMIO_CTRL_PWM2_INV_ON | PWMIO_CTRL_PWM3_INV_ON |
			                   PWMIO_CTRL_PWM4_INV_ON | PWMIO_CTRL_PWM5_INV_ON | PWMIO_CTRL_PWM6_INV_ON | PWMIO_CTRL_PWM7_INV_ON);
				break;
			
			case 0x08:                                                     // IOA3+VDD: PWMIO non-inverse output.
				PWMIO->CTRL1 &= ~(PWMIO_CTRL_PWM0_INV_ON | PWMIO_CTRL_PWM1_INV_ON | PWMIO_CTRL_PWM2_INV_ON | PWMIO_CTRL_PWM3_INV_ON |
			                    PWMIO_CTRL_PWM4_INV_ON | PWMIO_CTRL_PWM5_INV_ON | PWMIO_CTRL_PWM6_INV_ON | PWMIO_CTRL_PWM7_INV_ON);
				break;	

      case 0x10:
				if(IoToggleEn == 0)
				{
					IoToggleEn = 1;
					PWMIO->TOGGLE_CTRL = PWMIO_CTRL_TOGGLE0_ENABLE | PWMIO_CTRL_TOGGLE1_ENABLE | PWMIO_CTRL_TOGGLE2_ENABLE | PWMIO_CTRL_TOGGLE3_ENABLE |
					                     PWMIO_CTRL_TOGGLE4_ENABLE | PWMIO_CTRL_TOGGLE5_ENABLE | PWMIO_CTRL_TOGGLE6_ENABLE | PWMIO_CTRL_TOGGLE7_ENABLE;
				}
				else
				{
					IoToggleEn = 0;
					PWMIO->TOGGLE_CTRL = 0;
				}
        break;				
		}			
	}		
}
