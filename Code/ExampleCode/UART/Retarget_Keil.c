/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   RETARGET.C
 * @Version:
 *   V0.9.0
 * @Date:
 *   April 30, 2019
 * @Abstract:
 *   This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 **************************************************************************************************/

/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#if defined(__CC_ARM)
#include <rt_misc.h>
#endif
#include "GPCM1Fx.h"

#pragma import(__use_no_semihosting_swi)


/*---------------------------------------------------------------------------------------
 * Code Area
 *---------------------------------------------------------------------------------------*/
int sendchar(uint32_t tempuartdata)
{
	UART->DATA = (tempuartdata & 0x000000FF);                                    // Send data to UART buffer
	while(!(READ_BIT(UART->STS, UART_STS_TX_DONE_FLAG)));                        // Wait until transmission is done.
	CLEAR_FLAG(UART->STS, UART_STS_TX_DONE_MSK, UART_STS_TX_DONE_FLAG);	         // Clear transmission flag after transmission is completed.
	return 0;
}

int getkey(void)
{
	while(!(READ_BIT(UART->STS, UART_STS_RX_DAT_NEMP_FLAG)));                    // Wait for receiving data from PC or any device (for RX incoming data acquire)
	CLEAR_FLAG(UART->STS, UART_STS_RX_DAT_NEMP_MSK, UART_STS_RX_DAT_NEMP_FLAG);  // After data received, clear UART status data is not empty flag.
	return (int8_t)(READ_BIT(UART->DATA, 0xFF));                                 // Return key-in data to UART_DATA
}
#if defined(__CC_ARM)
struct __FILE { int handle; /* Add whatever you need here */ };
#endif
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  return (sendchar(ch));
}

int fgetc(FILE *f) {
  return (sendchar(getkey()));
}
#if defined(__CC_ARM)
int ferror(FILE *f) {
  // Your implementation of ferror
  return EOF;
}
#endif
void _ttywrch(int ch) {
  sendchar (ch);
}

void _sys_exit(int return_code) {
  while (1);    // endless loop
}

#if defined(__GNUC__)
void
__aeabi_memclr (void *dest, size_t n)
{
  memset (dest, 0, n);
}
#endif
