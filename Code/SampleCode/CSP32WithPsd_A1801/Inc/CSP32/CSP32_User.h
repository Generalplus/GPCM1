/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   CSP32_User.h
 * @Version:
 *   V1.0.3
 * @Date:
 *   March 28, 2022
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
/*
 * Definition for SD model
 */
#define SIMODEL_SIZE				 (0x20000)                                         // 128KB, need modify if SI model is bigger than 128KB
#define NUM_UTTR             (2)
#define SD_TAG_NUM           (7)

/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
#define SD_WORD_SIZE		     (0x1000)                                          // 4KB
#define UTTR_BUF_SIZE        (0x2000)		                                       // 8KB
#define SDTRAIN_BUFSIZE      (NUM_UTTR * UTTR_BUF_SIZE)
#define SDMODEL_SIZE         ((SD_WORD_SIZE * SD_TAG_NUM) + SDTRAIN_BUFSIZE)   // cmds(each cmd 4KB) + SDTRAIN_BUFSIZE

#define CSP32_USE_REJECTION_MODEL		1

/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

int32_t UnpackCspModel(uint32_t* PackedModelStartAddr, uint8_t *CspModelAddrBuf[], int32_t CspModelAddrBufSize);
CSP_HANDLE CSP32_User_Init(CSP32_WORKING_RAM *CspWorkingRam, CSP32_PCM_BUFFER *Csp32PcmBuffer);
int32_t CSP32_User_TrainSdCommand(int32_t PsdTagId);
void CSP32_User_EraseAllSdCommand(void);
int32_t CSP32_User_GetTagID(int32_t CmdID);

/*
 * CSP32 Callback Function Declaration
 */
CSP_HANDLE CSP32_CB_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP32_WORKING_RAM *CspWorkingRam, int32_t Csp32KernelRamSize, uint8_t *Csp32StateBuf);
void CSP32_CB_GetAdc_DmaIsr(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP32_CB_Start(int16_t *DstPcmBufAddr, uint16_t DataLen);
void CSP32_CB_Stop(void);
int32_t SPIMgr_Write(uint8_t *dest, uint8_t *src, int32_t nSize);
int32_t SPIMgr_Erase(uint8_t *dest, int32_t nSize);
int32_t SPIMgr_Read(uint8_t *dest, uint8_t *src, int32_t nSize);
int32_t SPIMgr_ReadNoWait(uint8_t *dest, uint8_t *src, int32_t nSize);


#ifdef __cplusplus
}
#endif

#endif
