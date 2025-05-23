/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File: QD_GPCM1Fx.h
 *
 * @Version:
 *   V0.9.0
 * @Date:
 *   17th, October 2022
 * @Abstract:
 *
 **************************************************************************************************/
#ifndef _QD_GPCM1F_H_
#define _QD_GPCM1F_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
#define 	QD0			                0
#define 	QD1			                1

#define 	INT_ALL_MODE			      0
#define 	INT_OVERFLOW_MODE 			1

/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

void QD_Open(uint8_t QDSel, uint8_t INT_Mode);
void QD_Close(uint8_t QDSel);

#ifdef __cplusplus
}
#endif

#endif







