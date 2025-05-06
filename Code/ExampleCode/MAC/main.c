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
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
int16_t SignArrayX[10] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
int16_t SignArrayY[10] = {-1, -1, -1, -1, -1, 1, 1, 1, 1, 1};
uint16_t UnsignArrayY[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int32_t SwMacResult_SU;
int32_t SwMacResult_SS;

int32_t HwMacResult_SU;
int32_t HwMacResult_SS;

uint32_t iCount;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	SystemInit();
	
	/*
	 * Software MAC example ++
	 */
	SwMacResult_SU = 0;
	for(iCount = 0; iCount < 10; iCount++)
	{
		SwMacResult_SU += SignArrayX[iCount] * UnsignArrayY[iCount];
	}

	SwMacResult_SS = 0;
	for(iCount = 0; iCount < 10; iCount++)
	{
		SwMacResult_SS += SignArrayX[iCount] * (int32_t)SignArrayY[iCount];
	}
	/*
	 * Software MAC example --
	 */

	/*
	 * Hardware MAC example ++
	 */
	MAC_Init(MAC_SAT_MODE_32B, MAC_SU, MAC_ARRAY_X_STEP_PLUS_1, MAC_ARRAY_Y_STEP_PLUS_1, MAC_OUTPUT_SHIFT_RIGHT_0);
	MAC_Start((uint32_t)SignArrayX, (uint32_t)UnsignArrayY, 10);
	while(MAC_CheckBusy() != 0);                   // Wait for MAC busy
	HwMacResult_SU = MAC_GetResult();

	MAC_Init(MAC_SAT_MODE_32B, MAC_SS, MAC_ARRAY_X_STEP_PLUS_1, MAC_ARRAY_Y_STEP_PLUS_1, MAC_OUTPUT_SHIFT_RIGHT_0);
	MAC_Start((uint32_t)SignArrayX, (uint32_t)SignArrayY, 10);
	while(MAC_CheckBusy() != 0);                   // Wait for MAC busy
	HwMacResult_SS = MAC_GetResult();
	
	MAC_Close();
	/*
	 * Hardware MAC example --
	 */

  while(1)
	{
		WDT_Clear();
	}
}
