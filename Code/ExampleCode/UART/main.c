/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1F UART example Code
 *        UART pins: IOA[23:22](default)
 *        Baud rate: 115200 (Default)
 *
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
#include <stdio.h>


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
void ShowMainTestList();


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
 uint32_t ScanedKey;
_Bool ScanRx(uint32_t *DstNum, uint8_t DataLen);


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();
	UART_Init(UART_IOA22_23, 115200);
  ShowMainTestList();

  while(1)
	{
		WDT_Clear();

    ScanRx(&ScanedKey, 2);
	  switch(ScanedKey)
		{
		  case 0x00:
			  printf("Your input number is 0 \r\n");
			  ScanedKey = 0;
        break;

      case 0x01:
			  printf("Your input number is 1 \r\n");
			  ScanedKey = 0;
        break;

      case 0x02:
			  printf("Your input number is 2 \r\n");
			  ScanedKey = 0;
        break;

      case 0x03:
			  printf("Your input number is 3 \r\n");
			  ScanedKey = 0;
        break;

      case 0x04:
			  printf("Your input number is 4 \r\n");
			  ScanedKey = 0;
        break;

      case 0x05:
			  printf("Your input number is 5 \r\n");
			  ScanedKey = 0;
        break;

      case 0x06:
			  printf("Your input number is 6 \r\n");
			  ScanedKey = 0;
        break;

       case 0x07:
			  printf("Your input number is 7 \r\n");
			  ScanedKey = 0;
        break;

      case 0x08:
			  printf("Your input number is 8 \r\n");
			  ScanedKey = 0;
        break;

      case 0x09:
			  printf("Your input number is 9 \r\n");
			  ScanedKey = 0;
        break;

      default:
				printf("Invalid number\r\n");
        ScanedKey = 0;
				break;
    }

	}
}


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/
 /**
 * @brief
 *
 * @param
 *          None.
 * @return
 *          None.
 */
void ShowMainTestList()
{
	printf("\r\n");
	printf("Hello world!\r\n");
	printf("Please input number:(0~9)\r\n");
}


/**
 * @brief
 *
 * @param
 *         None
 * @return
 *         None
 */
int32_t DrvUART_Read(uint8_t	*pu8RxBuf, uint32_t	u32ReadBytes)
{
  uint32_t  iCount;
  uint32_t	u32delayno;

  for(iCount = 0; iCount < u32ReadBytes; iCount++)
	{
    u32delayno = 0;

		while(READ_BIT(UART->STS, UART_STS_RX_DAT_NEMP_FLAG) == 0)
		{
			WDT_Clear();
	    u32delayno++;
	    if(u32delayno >= 0x40000000)
			{
	      return -1;
			}
    }
    CLEAR_FLAG(UART->STS, UART_STS_RX_DAT_NEMP_MSK, UART_STS_RX_DAT_NEMP_FLAG);
    pu8RxBuf[iCount] = UART->DATA;					     // Get Data from UART RX
  }

  return 0;
}

/**
 * @brief
 *         Conver 0~F char to uint8_t
 * @param
 *         *DstNum    -[out] uint8_t
 *          KeyBuffer -[in]  Ascii code
 * @return
 *         1 : Done
 *         0 : Input are not 0~F char
 */
_Bool AsciiCodeToUINT(uint8_t *DstNum, uint8_t *KeyBuffer)
{
  if((*KeyBuffer >= '0') && (*KeyBuffer <= '9'))
	{
    *DstNum = *KeyBuffer - 48;
    return 1;
  }
	else if((*KeyBuffer >= 'A') && (*KeyBuffer <= 'F'))
	{
    *DstNum = *KeyBuffer - 55;
    return 1;
  }
	else if((*KeyBuffer >= 'a') && (*KeyBuffer <= 'f'))
	{
    *DstNum = *KeyBuffer - 87;
    return 1;
  }
	else
	{
    return 0;
  }
}

/**
 * @brief
 *         Get hex data from Uart
 * @param
 *         *DstNum  -[out] uint32_t
 *          DataLen -[in]  Input data length, unit: byte
 * @return
 *         1 : Done
 *         0 : Cancel
 */
_Bool ScanRx(uint32_t *DstNum, uint8_t DataLen)
{
  uint8_t TmpNum = 0;
	uint8_t InputCnt = 0;
	uint8_t UartRxBuf;

  while(1)
	{
    DrvUART_Read(&UartRxBuf, 1);
    if(AsciiCodeToUINT(&TmpNum, &UartRxBuf) && (InputCnt < DataLen))
		{
			printf("%c\r\n", UartRxBuf);
      *DstNum = *DstNum * 16 + TmpNum;
      InputCnt += 1;
      continue;
    }
		else if(UartRxBuf == 0x08)                   // BACKSPACE Key: 0x08
		{
      if(InputCnt == 0) {
        InputCnt = 0;
      } else {
        // To clear 1 char
				printf("%c", UartRxBuf);
				printf("%c", 0x20);
        printf("%c", UartRxBuf);

        InputCnt -= 1;
      }
      *DstNum /= 16;
      continue;
    }
		else if(UartRxBuf == 0x0D)                   // Enter Key: 0x0D
		{
      return 1;
    }
		else if(UartRxBuf == 0x1B)                   // ESC Key: 0x1B
		{
      return 0;
    }
  }
}


