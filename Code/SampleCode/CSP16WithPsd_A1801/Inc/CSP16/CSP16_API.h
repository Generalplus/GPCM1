/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   CSP16_API.h
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   October 19, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _CSP16_API_H_
#define _CSP16_API_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "CSpotterSDK16Api.h"


/*---------------------------------------------------------------------------------------
 * User Definition Area
 *---------------------------------------------------------------------------------------*/
#define CSP16_KERNEL_RAM_SIZE                    (8 * 1024)
#define CSP16_MAX_TIME	                         (252)           // 4 bytes aligned!


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/ 
#define CSP16_FRAME_SIZE                         (160) 
 
/*
 * CSP16 status definition
 */
#define CSP16_START_FLAG                         (0x01)
#define	CSP16_BUF_EVEN_FLAG                      (0x02)
#define CSP16_WORK_FLAG                          (0x04)
#define CSP16_CPU_OVERLOAD_FLAG                  (0x10)
#define CSP16_ISR_SERVICE_ENABLE_FLAG            (0x80)


/*---------------------------------------------------------------------------------------
 * Structure Definition Area
 *---------------------------------------------------------------------------------------*/ 
typedef struct _CSP16_WORKING_RAM
{	
  int16_t *Csp16PcmBufPtr;
	int16_t *Csp16VrBufPtr;	
	int16_t *Csp16PcmBufStartAddress;
  uint8_t CspKernelRam[CSP16_KERNEL_RAM_SIZE];
} CSP16_WORKING_RAM;

typedef struct _CSP16_PCM_BUFFER
{		
	int16_t Csp16PcmBuf[2][CSP16_FRAME_SIZE];	
} CSP16_PCM_BUFFER;


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif 

CSP_HANDLE CSP16_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP16_WORKING_RAM *Csp16WorkingRam, int32_t Csp16KernelRamSize, void *Csp16PcmBuffer);
void CSP16_ClearStateBuf(void);	
void CSP16_Start(CSP_HANDLE Csp16Handle);
void CSP16_Stop(CSP_HANDLE Csp16Handle);
void CSP16_DmaIsrService(void);
int32_t CSP16_GetResult(CSP_HANDLE Csp16Handle);
uint32_t CSP16_CheckCpuOverload(void);
void CSP16_ClearCpuOverloadFlag(void);
uint32_t CSP16_GetStatus(void);
void CSP16_ClrWorkFlag(void);
	

#ifdef __cplusplus
}
#endif		
	
#endif
