/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   KeyScan.c
 * @Version:  
 *   V0.9.0
 * @Date:     
 *   April 30, 2019
 * @Abstract: 
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
KEYSCAN_WORKING_RAM *mKeyScanWorkingRamPtr;


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/

/** 
 * @brief  
 *   Key scan initialzation
 * @param 
 *   None.
 * @return 
 *   None.
 */
void KeyScan_Initial(KEYSCAN_WORKING_RAM *KeyScanWorkingRam)
{
	mKeyScanWorkingRamPtr = KeyScanWorkingRam;

	#if SCAN_8_BITS
	GPIO_SetMode(GPIOA, 0x000000FF, GPIO_MODE_INPUT);
	#else
	GPIO_SetMode(GPIOA, 0x0000FFFF, GPIO_MODE_INPUT);
	#endif

	mKeyScanWorkingRamPtr->KeyDebounceReg = 0;
	mKeyScanWorkingRamPtr->KeyBuf = 0;
	mKeyScanWorkingRamPtr->KeyStrobe = 0;
	mKeyScanWorkingRamPtr->KeyDebounceCnt = DEBOUNCE_CNT;
}

/**
 * @brief
 *   Get Key code from key pad
 * @param 
 *   None.
 * @return 
 *   None.
 */
void KeyScan_ServiceLoop(void)
{
	uint32_t R_PrevData;
	
	if(mKeyScanWorkingRamPtr->KeyDebounceCnt != 0)
	{
		mKeyScanWorkingRamPtr->KeyDebounceCnt -= 1;
	}
	
	R_PrevData = mKeyScanWorkingRamPtr->KeyDebounceReg;                          // get prev I/O
	
	/*
   *   SCAN_8_BITS = 1, ScanKey 8bits
   *   SCAN_8_BITS = 0, ScanKey 16bits 	
	 */
	#if SCAN_8_BITS										
		mKeyScanWorkingRamPtr->KeyDebounceReg = (GPIOA->IDATA & 0x000000FF);						
	#else
		mKeyScanWorkingRamPtr->KeyDebounceReg = (GPIOA->IDATA & 0x0000FFFF);						
	#endif
	
	if(R_PrevData != mKeyScanWorkingRamPtr->KeyDebounceReg)                      // if prev != curr
	{
		mKeyScanWorkingRamPtr->KeyDebounceCnt = DEBOUNCE_CNT;                      // debounce counter reset
		return;
	}
	
	if(mKeyScanWorkingRamPtr->KeyDebounceCnt != 0)
	{
		return;
	}
	
	R_PrevData = mKeyScanWorkingRamPtr->KeyBuf;															     // prev buf
	mKeyScanWorkingRamPtr->KeyBuf = mKeyScanWorkingRamPtr->KeyDebounceReg;	     // update curr buf

	#if SCAN_8_BITS	
		R_PrevData ^= 0x00FF;    														
		R_PrevData &= mKeyScanWorkingRamPtr->KeyBuf;		
		R_PrevData &= 0x00FF;
	#else
		R_PrevData ^= 0xFFFF;    					
		R_PrevData &= mKeyScanWorkingRamPtr->KeyBuf;
		R_PrevData &= 0xFFFF;
	#endif
	
	mKeyScanWorkingRamPtr->KeyStrobe |= R_PrevData;
	
	return;	
}

/**
 * @brief  
 *   Get Key code
 * @param 
 *   None.
 * @return 
 *   None.
 */
uint32_t KeyScan_GetCh(void)
{
	uint32_t temp;
	
	temp = mKeyScanWorkingRamPtr->KeyStrobe;                                     // Get Key code
	mKeyScanWorkingRamPtr->KeyStrobe = 0x0000;                                   // Clear KeyStrobe for next key
	
	return temp;
}
