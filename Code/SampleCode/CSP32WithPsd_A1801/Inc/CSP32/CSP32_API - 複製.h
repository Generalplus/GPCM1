/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   CSP32_API.h
 * @Version:  
 *   V1.0.3
 * @Date:     
 *   March 28, 2022
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _CSP32_API_H_
#define _CSP32_API_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "CSpotterSDKApi.h"


/*---------------------------------------------------------------------------------------
 * User Definition Area
 *---------------------------------------------------------------------------------------*/
#define CSP32_KERNEL_RAM_SIZE                   (10 * 1024)
#define CSP32_MAX_TIME	                        (252)           // 4 bytes aligned!


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/ 
#define CSP32_FRAME_SIZE                        (160) 
 
/*
 * CSP32 status definition
 */
#define CSP32_START_FLAG                        (0x01)
#define	CSP32_BUF_EVEN_FLAG                     (0x02)
#define CSP32_WORK_FLAG                         (0x04)
#define CSP32_CPU_OVERLOAD_FLAG                 (0x10)
#define CSP32_ISR_SERVICE_ENABLE_FLAG           (0x80)


/*---------------------------------------------------------------------------------------
 * Structure Definition Area
 *---------------------------------------------------------------------------------------*/ 
typedef struct _CSP32_WORKING_RAM
{	
  int16_t *Csp32PcmBufPtr;
	int16_t *Csp32VrBufPtr;
	int16_t Csp32PcmBuf[2][CSP32_FRAME_SIZE];	
  uint8_t CspKernelRam[CSP32_KERNEL_RAM_SIZE];
} CSP32_WORKING_RAM;


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif 

CSP_HANDLE CSP32_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP32_WORKING_RAM *Csp32WorkingRam, int32_t Csp32KernelRamSize);
void CSP32_ClearStateBuf(void);	
void CSP32_Start(CSP_HANDLE Csp32Handle);
void CSP32_Stop(CSP_HANDLE Csp32Handle);
void CSP32_DmaIsrService(void);
int32_t CSP32_GetResult(CSP_HANDLE Csp32Handle);
uint32_t CSP32_CheckCpuOverload(void);
void CSP32_ClearCpuOverloadFlag(void);
uint32_t CSP32_GetStatus(void);
void CSP32_ClrWorkFlag();
	
#ifdef __cplusplus
}
#endif		
	
#endif
