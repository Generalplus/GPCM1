/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *
 * @Version:  
 *   V0.9.0
 * @Date:     
 *   30th, April 2019
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _UART_GPCM1F_H_
#define _UART_GPCM1F_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/ 
 
/*
 * Definition for the 1st parameter of UART_Init()
 */ 
#define UART_IOA4_5                  IOFUNC_CTRL0_UART_IOA4_5
#define UART_IOA13_14                IOFUNC_CTRL0_UART_IOA13_14
#define UART_IOA22_23                IOFUNC_CTRL0_UART_IOA22_23
#define UART_IOA0_9                  IOFUNC_CTRL0_UART_IOA0_9

//#define UART_BAUD_RATE_ERR         0.045


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif 
 
void UART_Init(uint32_t UartSelIo, uint32_t BaurdRate);
void UART_Close(void);
void UART_TxInt_Enable(void);
void UART_TxInt_Disable(void);
void UART_RxInt_Enable(void);
void UART_RxInt_Disable(void);


#ifdef __cplusplus
}
#endif		

#endif
