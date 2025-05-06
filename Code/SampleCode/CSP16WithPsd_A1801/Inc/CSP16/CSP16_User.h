/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   CSP16_User.h
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   December 13, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _CSP16_USER_H_
#define _CSP16_USER_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "CSP16_API.h"


/*---------------------------------------------------------------------------------------
 * User Definition Area
 *---------------------------------------------------------------------------------------*/

/* 
 * Definition for SD model
 */
#define SIMODEL_SIZE				 (0x10000)                                         // 64KB, need modify if SI model is bigger than 64KB 
#define NUM_UTTR             (2)
#define SD_TAG_NUM           (7)


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
#define SD_WORD_SIZE		     (0x1000)                                          // 4KB
#define UTTR_BUF_SIZE        (0x2000)		                                       // 8KB
#define SDTRAIN_BUFSIZE      (NUM_UTTR * UTTR_BUF_SIZE)
#define SDMODEL_SIZE         ((SD_WORD_SIZE * SD_TAG_NUM) + SDTRAIN_BUFSIZE)   // cmds(each cmd 4KB) + SDTRAIN_BUFSIZE


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

int32_t UnpackCspModel(uint32_t* PackedModelStartAddr, uint8_t *CspModelAddrBuf[], int32_t CspModelAddrBufSize);
CSP_HANDLE CSP16_User_Init(CSP16_WORKING_RAM *CspWorkingRam, CSP16_PCM_BUFFER *Csp16PcmBuffer);
int32_t CSP16_User_TrainSdCommand(int32_t PsdTagId);
void CSP16_User_EraseAllSdCommand(void);
int32_t CSP16_User_GetTagID(int32_t CmdID);
	
/*
 * CSP16 Callback Function Declaration
 */	
CSP_HANDLE CSP16_CB_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP16_WORKING_RAM *CspWorkingRam, int32_t Csp16KernelRamSize, uint8_t *Csp16StateBuf);
void CSP16_CB_GetAdc_DmaIsr(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP16_CB_Start(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP16_CB_Stop(void);
int32_t SPIMgr_Write(uint8_t *dest, uint8_t *src, int32_t nSize);
int32_t SPIMgr_Erase(uint8_t *dest, int32_t nSize);
int32_t SPIMgr_Read(uint8_t *dest, uint8_t *src, int32_t nSize);
int32_t SPIMgr_ReadNoWait(uint8_t *dest, uint8_t *src, int32_t nSize);
	

#ifdef __cplusplus
}
#endif	

#endif
