/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   QD example code
 * @Version: V0.9
 *
 * @Date: 2022.10.17
 *
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "KeyScan.h"
#include "QD_GPCM1Fx.h"
#include "glibc_wrapper.h"

/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
KEYSCAN_WORKING_RAM KeyScanWorkingRam;
uint32_t ScanedKey;

// For QD
/*
int counter;
uint8_t counter_forward = 0;
uint8_t counter_backward = 0;
*/

/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  /*
	 * QD init, QD0: IOA[19:18] & QD1: IOA[21:20]
	 */
	QD_Open(QD0,INT_ALL_MODE);

	KeyScan_Initial(&KeyScanWorkingRam);                                                        // Key scan init

  while(1)
	{
		WDT_Clear();

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
      case 0x01: // IOA0+VDD: QD0 Open & INT changed to overflow mode
        QD_Open(QD0,INT_OVERFLOW_MODE);
        break;

		  case 0x02: // IOA2+VDD: QD0 Open & INT changed to All mode
        QD_Open(QD0,INT_ALL_MODE);
        break;

		  case 0x04:  // IOA1+VDD: QD0 closed
        QD_Close(QD0);
        break;

		  case 0x08:  // IOA3+VDD: QD1 Open & INT changed to overflow mode
        QD_Open(QD1,INT_OVERFLOW_MODE);
        break;

		  case 0x10:  // IOA4+VDD: QD1 Open & INT changed to All mode
        QD_Open(QD1,INT_ALL_MODE);
        break;

      case 0x20:  // IOA5+VDD: QD1 closed
        QD_Close(QD1);
				break;

			case 0x40:  // IOA6+VDD:

			  break;

      case 0x80:  // IOA7+VDD:

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
