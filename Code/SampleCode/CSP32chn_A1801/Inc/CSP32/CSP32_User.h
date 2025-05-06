/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   CSP32_User.h
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   December 13, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _CSP32_USER_H_
#define _CSP32_USER_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "CSP32_API.h"


/*---------------------------------------------------------------------------------------
 * CSP32 User Definition Area
 *---------------------------------------------------------------------------------------*/
#define CSP32_USE_REJECTION_MODEL    1


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

int32_t UnpackCspModel(uint32_t* PackedModelStartAddr, uint8_t *CspModelAddrBuf[], int32_t CspModelAddrBufSize);
CSP_HANDLE CSP32_User_Init(CSP32_WORKING_RAM *CspWorkingRam, CSP32_PCM_BUFFER *Csp32PcmBuffer);
	
/*
 * CSP32 Callback Function Declaration
 */	
CSP_HANDLE CSP32_CB_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP32_WORKING_RAM *CspWorkingRam, int32_t Csp32KernelRamSize, uint8_t *Csp32StateBuf);
void CSP32_CB_GetAdc_DmaIsr(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP32_CB_Start(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP32_CB_Stop(void);


#ifdef __cplusplus
}
#endif	

#endif
