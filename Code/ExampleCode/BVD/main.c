/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1F BVD example code
 *    Note: The BVD is to detect the voltage of the VDD_IO pin
 *    IOA[10:8] Output pins and to show the BVD result.
 *        000	≤1.94V+/-7.5%
 *        001	2.134V+/-7.5%
 *        010	2.328V+/-7.5%
 *        011	2.522V+/-7.5%
 *        100	2.716V+/-7.5%
 *        101	2.91V+/-7.5%
 *        110	3.2v+/-7.5%
 *        111	>3.2v+/-7.5%
 * @Version: V 0.9
 *
 * @Date: 2021.11.22
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
uint32_t BVDResult;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  /*
	 * BVD init
	 */
  SET_BIT(ACU->BVD_CTRL, 0x00000008);

  /*
	 * IOA[15:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x0000FF00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x0000FF00, 0);

	KeyScan_Initial(&KeyScanWorkingRam);                                                        // Key scan init

  while(1)
	{
		WDT_Clear();

		BVDResult = READ_REG(ACU->BVD_CTRL);
		BVDResult &= 0x00000007;
		BVDResult = BVDResult << 8;
		MODIFY_REG(GPIOA->OBUF, 0x0000FF00, BVDResult);

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
      case 0x01:                                                                              // IOA0+VDD: Open TB. Clock source from IOSC32K.
        break;

		  case 0x02:                                                                              // IOA1+VDD: Open TB. Clock source from XTAL32K.
        break;

		  case 0x04:                                                                              // IOA2+VDD: Enable TB 2Hz interrupt.
        break;

		  case 0x08:                                                                              // IOA3+VDD: Enable TB 16Hz/64Hz interrupt.
        break;

		  case 0x10:                                                                              // IOA4+VDD: Enable TB 512Hz/2KHz/4KHz interrupt.
        break;

      case 0x20:                                                                              // IOA5+VDD: Disable TB all interrupt.
        break;

			case 0x40:                                                                              // IOA6+VDD: Reset TB count.
			  break;

      case 0x80:                                                                              // IOA7+VDD: Close TB.
        break;
		}
	}
}


