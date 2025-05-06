/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   CSP32_User.c
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   December 13, 2021
 * @Abstract: 
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "CSP32_User.h"
#include "CSP32_FileMerger.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/ 
DMA_TYPE_DEF *mDsAdcDmaHandle;


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/ 

/**
 * @brief  
 *         	
 * @param 
 *   PackedModelStartAddr [in]:
 *   CspModelAddrBuf [out]:
 *   CspModelAddrBufSize [in]:
 * @return 
 *   Un-pack model number.
 */
int32_t UnpackCspModel(uint32_t* PackedModelStartAddr, uint8_t *CspModelAddrBuf[], int32_t CspModelAddrBufSize)
{	
	int32_t CspModelNum = PackedModelStartAddr[0];
	uint32_t *BinSize = PackedModelStartAddr + 1;
	int32_t UnpackModelNum;

	CspModelAddrBuf[0] = (uint8_t *)(BinSize + CspModelNum);
	for(UnpackModelNum = 1; UnpackModelNum < CspModelNum; UnpackModelNum++)
	{
		if(UnpackModelNum >= CspModelAddrBufSize)
		{
			break;
		}
		CspModelAddrBuf[UnpackModelNum] = CspModelAddrBuf[UnpackModelNum - 1] + BinSize[UnpackModelNum - 1];
	}

	return UnpackModelNum;
}

/**
 * @brief  
 *         	
 * @param 
 *  *CspWorkingRam [in]: CSP working RAM pointer
 * @return 
 *   CSpotterHandle: Handle of a recognizer
 */
CSP_HANDLE CSP32_User_Init(CSP32_WORKING_RAM *CspWorkingRam, CSP32_PCM_BUFFER *Csp32PcmBuffer)
{	
	CSP_HANDLE Csp32Handle;
	uint8_t *CspModelAddr[3];						// CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ... /CspModelAddr[n-1]:ExtRej Model	
  	
	UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));	
	Csp32Handle = CSP32_Init(CspModelAddr[0], CspModelAddr[1], CSP32_MAX_TIME, CspModelAddr[2], CspWorkingRam, CSP32_KERNEL_RAM_SIZE, Csp32PcmBuffer);
	if(Csp32Handle == NULL)
	{
	  return NULL;
	}
	else
	{
	  CSpotter_Reset(Csp32Handle);
		CSpotter_SetEnableNBest(Csp32Handle, 1);
		CSpotter_SetEnableRejectedResult(Csp32Handle, 1);			
		
	  CSpotter_SetRejectionLevel(Csp32Handle, 9);
	  CSpotter_SetCmdRewardOffset(Csp32Handle, 0, -2);
	  CSpotter_SetCmdRewardOffset(Csp32Handle, 1, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 2, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 3, -1);		
		CSpotter_SetCmdRewardOffset(Csp32Handle, 4, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 5, 0);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 6, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 7, 0);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 8, 0);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 9, 99);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 10, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 11, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 12, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 13, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 14, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 15, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 16, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 17, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 18, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 19, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 20, 100);
    CSpotter_SetRejectedResultEnergyThreshd(Csp32Handle, 500);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 9, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 10, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 11, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 12, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 13, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 14, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 15, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 16, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 17, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 18, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 19, 20);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 20, 20);
		
		return Csp32Handle;
	}
}


/*---------------------------------------------------------------------------------------
 * Callback Function Area                                                                              
 *---------------------------------------------------------------------------------------*/

/** 
 * @brief  
 *   Callback function. Implemented by user.
 *   When user call API function CSP32_Init, this function is called by CSP32 Library.      
 * @param 
 *  *BackgroundModelAddr [in]: The background model address, contents of CYBase.mod.
 *  *CmdModelAddr [in]: The command model address.
 *   MaxTime [in]: The maximum buffer length in number of frames for keeping the status of commands.
 *  *RejModelAddr [in]: The rejection model address.
 *  *CspWorkingRam [in]: CSP working RAM pointer
 *   Csp32KernelRamSize [in]: CSP32 kernel RAM size.
 *  *Csp32StateBuf [in]: state buffer zize (bytes)
 * @return 
 *   CSpotterHandle: Handle of a recognizer.
 */
CSP_HANDLE CSP32_CB_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP32_WORKING_RAM *CspWorkingRam, int32_t Csp32KernelRamSize, uint8_t *Csp32StateBuf)
{  
	int32_t ErrCode;	
	CSP_HANDLE CSpotterHandle = NULL;		
	
	#if CSP32_USE_REJECTION_MODEL == 1	
	if(CSpotter_GetMemoryUsage_SepWithExtRejModel(BackgroundModelAddr, CmdModelAddr, MaxTime, RejModelAddr) > CSP32_KERNEL_RAM_SIZE)  // Check kernel RAM size
	{
		return NULL; 
	}
	else
	{	    
		CSpotterHandle = CSpotter_Init_SepWithExtRejModel(BackgroundModelAddr, CmdModelAddr, MaxTime, RejModelAddr, CspWorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
				
		return CSpotterHandle;
	}
	#else
	if(CSpotter_GetMemoryUsage_Sep(BackgroundModelAddr, CmdModelAddr, MaxTime) > CSP32_KERNEL_RAM_SIZE)                               // Check kernel RAM size	
	{
		return NULL; 
	}
	else
	{	
    CSpotterHandle = CSpotter_Init_Sep(BackgroundModelAddr, CmdModelAddr, MaxTime, CspWorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);		
				
		return CSpotterHandle;
	}	
	#endif
}

/** 
 * @brief  
 *   Callback function. Implemented by user.
 *   When CSP16 working, this function is called by CSP16 Library to trigger DS-ADC DMA.     
 * @param 
 *  *DstPcmBufAddr [in]: Destination PCM buffer address pointer.
 *   DataLen [in]: Data length (halfword)
 * @return 
 *   None.
 */
void CSP32_CB_Start(int16_t *DstPcmBufAddr, uint16_t DataLen)
{
	/*
	 * DS-ADC init
	 */	
	DSADC_Init(16000);
	DSADC_SetBoostGain(3);
	DSADC_SetPgaGain(11);	

	/*
	 * Digital AGC init
	 */		
	/*
	DAGC_SetCenterBoundary(0x20, 0x1000);
	DAGC_SetSensitivity(0x1E, 0x01, 0xFE);
	DAGC_SetAttackScale(ATTACK_X1);
	DAGC_SetReleaseScale(RELEASE_X1);
	DAGC_ZeroCross_Enable();
	DAGC_Enable();
	*/
		
	mDsAdcDmaHandle = DMA0;	
	DMA_Init(mDsAdcDmaHandle, DMA_REQSEL_DSADC, DMA_SRC_DATA_16B, DMA_SRC_ADDR_FIX, DMA_DST_DATA_16B, DMA_DST_ADDR_INC);	
	DMA_InstallIsrService(mDsAdcDmaHandle, CSP32_DmaIsrService);
	DMA_EnableInt(mDsAdcDmaHandle);
	NVIC_EnableIRQ(DMA_IRQn);		
	
  DMA_Trigger(mDsAdcDmaHandle, (uint32_t)&DS_ADC->DATA, (uint32_t)DstPcmBufAddr, DataLen);
}

/** 
 * @brief  
 *          
 * @param 
 *  
 * @return 
 *   None.
 */
void CSP32_CB_Stop()
{	  
	DSADC_Close();
	DMA_Close(mDsAdcDmaHandle);
}

/** 
 * @brief  
 *   Callback function. Implemented by user.
 *   When CSP32 working, this function is called by CSP32 Library to trigger DS-ADC DMA.     
 * @param 
 *  *DstPcmBufAddr [in]: Destination PCM buffer address pointer.
 *   DataLen [in]: Data length (halfword)
 * @return 
 *   None.
 */
void CSP32_CB_GetAdc_DmaIsr(int16_t *DstPcmBufAddr, uint16_t DataLen)
{
  DMA_Trigger(mDsAdcDmaHandle, (uint32_t)&DS_ADC->DATA, (uint32_t)DstPcmBufAddr, DataLen);
}

/** 
 * @brief  
 *          
 * @param 
 *  *dest [out]: Destination address
 *  *src [in]: Source buffer address
 *   nSize [in]: Data length (Byte)
 * @return 
 *   
 */
int32_t SPIMgr_Write(uint8_t *dest, uint8_t *src, int32_t nSize)
{		
	return 0;
}

/** 
 * @brief  
 *          
 * @param 
 *  *dest [out]: Destination address 
 *   nSize [in]: Data length (Byte)
 * @return 
 *   
 */
int32_t SPIMgr_Erase(uint8_t *dest, int32_t nSize)
{		
	return 0;
}

/** 
 * @brief  
 *          
 * @param 
 *  *dest [out]: Destination buffer address
 *  *src [in]: Source address
 *   nSize [in]: Data length (Byte)
 * @return 
 *   
 */
int32_t SPIMgr_Read(uint8_t *dest, uint8_t *src, int32_t nSize)
{		
	return 0;
}

/** 
 * @brief  
 *          
 * @param 
 *  *dest [out]: Destination buffer address
 *  *src [in]: Source address
 *   nSize [in]: Data length (Byte)
 * @return 
 *   
 */
int32_t SPIMgr_ReadNoWait(uint8_t *dest, uint8_t *src, int32_t nSize)
{		
	return 0;
}
