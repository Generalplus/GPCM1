/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   KeyScan.h
 * @Version:  
 *   V0.9.0
 * @Date:     
 *   30th, April 2019
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
#define DEBOUNCE_CNT			  (0x0100)
#define SCAN_8_BITS         (1) 							// 0 for 16Bits		


/*---------------------------------------------------------------------------------------
 * Structure Definition Area
 *---------------------------------------------------------------------------------------*/ 
typedef struct _KEYSCAN_WORKING_RAM
{	
	uint32_t KeyDebounceReg;
	uint32_t KeyBuf;
	uint32_t KeyStrobe;
	uint16_t KeyDebounceCnt;	
} KEYSCAN_WORKING_RAM;


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif 
	
void KeyScan_Initial(KEYSCAN_WORKING_RAM*);
void KeyScan_ServiceLoop(void);
uint32_t KeyScan_GetCh(void);


#ifdef __cplusplus
}
#endif	

#endif




	
