/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   CSP16_User.c
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
#include "CSP16_User.h"
#include "CSP16_FileMerger.h"
#include "CSpotterSD16TrainApi.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
DMA_TYPE_DEF *mDsAdcDmaHandle;

CSP16_WORKING_RAM *pCsp16A1801WorkingRam;
uint32_t SdTrainAddr;
uint32_t SdModelAddr;
int32_t PsiNumWord;
int32_t PsdNumWord;
int8_t UttrIdx;


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
CSP_HANDLE CSP16_User_Init(CSP16_WORKING_RAM *CspWorkingRam, CSP16_PCM_BUFFER *Csp16PcmBuffer)
{
	uint8_t *CspModelAddr[3];							         // CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ...

	pCsp16A1801WorkingRam = CspWorkingRam;
	UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
	SdModelAddr = (uint32_t)CspModelAddr[1] + SIMODEL_SIZE;;
	if(((uint32_t)SdModelAddr & 0x0FFF) != 0) {
		SdModelAddr = ((((uint32_t)SdModelAddr) >> 12) + 1) << 12;
  }
	SdTrainAddr = SdModelAddr + SDMODEL_SIZE;
	CspModelAddr[2] = (uint8_t *)SdModelAddr;

	PsiNumWord = CSpotter16_GetNumWord((uint8_t *)CspModelAddr[1]);
	PsdNumWord = CSpotter16_GetNumWord((uint8_t *)SdModelAddr);	
  
	if(PsdNumWord >= 1)
	{		
		CspModelAddr[2] = (uint8_t *)SdModelAddr;		
	  if(CSpotter16_GetMemoryUsage_Multi_FromSPI((uint8_t *)CspModelAddr[0], &CspModelAddr[1], 2, CSP16_MAX_TIME) > CSP16_KERNEL_RAM_SIZE)   // Check kernel RAM size
	  {
		  return NULL;                               // CSP16_KERNEL_RAM_SIZE is not enough. return NULL.
	  }		
	}
	else
	{	
	  if(CSpotter16_GetMemoryUsage_Sep((uint8_t *)CspModelAddr[0], (uint8_t *)CspModelAddr[1], CSP16_MAX_TIME) > CSP16_KERNEL_RAM_SIZE)      // Check kernel RAM size
	  {
		  return NULL;                               // CSP16_KERNEL_RAM_SIZE is not enough. return NULL.
	  }
	}
	
	return CSP16_Init(CspModelAddr[0], CspModelAddr[1], CSP16_MAX_TIME, NULL, CspWorkingRam, CSP16_KERNEL_RAM_SIZE, Csp16PcmBuffer);	
}

/**
 * @brief
 *
 * @param
 *  *CspWorkingRam [in]: CSP working RAM pointer
 * @return
 *   0 -> train SD command success
 *  -1 -> train SD command no success
 *  -2 -> skip training SD command
 */
int32_t CSP16_User_TrainSdCommand(int32_t PsdTagId)
{
	int32_t SkipFrameNum = 40;
	uint8_t *CspModelAddr[3];							                                                 // CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ...
	CSP_HANDLE CSpotterHandle = NULL;
	int32_t ErrCode;
	int32_t UsedSize;

  UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
	if(CSpotterSD16_GetMemoryUsage_FromSPI(CspModelAddr[1], 0) > CSP16_KERNEL_RAM_SIZE)    // Check kernel RAM size
	{
		return -1;                                                                           // CSP16_KERNEL_RAM_SIZE is not enough. return NULL.
	}

  CSpotterHandle = CSpotterSD16_Init_FromSPI(CspModelAddr[0], pCsp16A1801WorkingRam->CspKernelRam, CSP16_KERNEL_RAM_SIZE, &ErrCode);
  CSpotterSD16_DeleteWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDTRAIN_BUFSIZE, PsdTagId, &UsedSize);
	PsdNumWord = CSpotter16_GetNumWord((uint8_t *)SdModelAddr);
	CSpotterSD16_SetBackgroundEnergyThreshd(CSpotterHandle, 1200);

	UttrIdx = 0;
	while(UttrIdx < NUM_UTTR)
	{
	  if((ErrCode = CSpotterSD16_AddUttrStart_FromSPI(CSpotterHandle, UttrIdx, (uint8_t*)(SdTrainAddr + UttrIdx * UTTR_BUF_SIZE), UTTR_BUF_SIZE)) != CSPOTTER_SUCCESS)
		{
		  break;
		}

		while(1)
		{
		  WDT_Clear();
	    if((CSP16_GetStatus() & CSP16_WORK_FLAG) != 0)
	    {
				if(SkipFrameNum > 0)
				{
					SkipFrameNum--;
				}
				else
				{
			    if((ErrCode = CSpotterSD16_AddSample_FromSPI(CSpotterHandle, pCsp16A1801WorkingRam->Csp16VrBufPtr, CSP16_FRAME_SIZE)) != CSPOTTER_ERR_NeedMoreSample)
		      {
				    break;
		      }
				}

				CSP16_ClrWorkFlag();
			}

			GPIOA->OBUF = ((~(GPIOA->OBUF)) & 0x1000) | ((UttrIdx + 1) << 8);

		  KeyScan_ServiceLoop();
		  if(KeyScan_GetCh() != 0)
		  {
				return -2;
			}
	  }

		GPIOA->OBUF = ((UttrIdx + 1) << 8) | 0x2000;
		if((ErrCode = CSpotterSD16_AddUttrEnd_FromSPI(CSpotterHandle)) != CSPOTTER_SUCCESS)
		{
 		  return -1;
		}

    if(UttrIdx == 0 && (CSpotterSD16_SimilarityCheckWithRejLevel_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, 0)) >= 0)
		{
			return -1;
    }

    if(UttrIdx > 0 && (ErrCode = (CSpotterSD16_DifferenceCheckWithRejLevel_FromSPI(CSpotterHandle, 0))) != CSPOTTER_SUCCESS)
		{
			return -1;
    }

    UttrIdx++;
	}

  GPIOA->OBUF = 0x4000;
	if((ErrCode = CSpotterSD16_TrainWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDMODEL_SIZE, PsdTagId, 0, &UsedSize)) != CSPOTTER_SUCCESS)
	{
		return -1;
	}
	else
	{
		PsdNumWord = CSpotter16_GetNumWord((uint8_t *)SdModelAddr);
	}

	return 0;
}

/**
 * @brief
 *
 * @param
 *  *CspWorkingRam [in]: CSP working RAM pointer
 * @return
 *   CSpotterHandle: Handle of a recognizer
 */
void CSP16_User_EraseAllSdCommand(void)
{
	CSP_HANDLE CSpotterHandle;
	uint8_t *CspModelAddr[2];							         // CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ...
	int32_t ErrCode;
	int32_t UsedSize;
	int32_t iCount;

	UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
  CSpotterHandle = CSpotterSD16_Init_FromSPI(CspModelAddr[0], pCsp16A1801WorkingRam->CspKernelRam, CSP16_KERNEL_RAM_SIZE, &ErrCode);
	for(iCount = 0; iCount < SD_TAG_NUM; iCount++)
	{
    CSpotterSD16_DeleteWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDTRAIN_BUFSIZE, iCount, &UsedSize);
    WDT_Clear();
  }

  PsdNumWord = CSpotter16_GetNumWord((uint8_t *)SdModelAddr);
}

/**
 * @brief
 *
 * @param
 *   CspCmdID [in]: CSP command ID
 * @return
 *   CSP Tag ID
 */
int32_t CSP16_User_GetTagID(int32_t CspCmdID)
{
  return CSpotterSD16_GetTagID_FromSPI((uint8_t *)SdModelAddr, CspCmdID);
}


/*---------------------------------------------------------------------------------------
 * Callback Function Area
 *---------------------------------------------------------------------------------------*/

/**
 * @brief
 *   Callback function. Implemented by user.
 *   When user call API function CSP16_Init, this function is called by CSP16 Library.
 * @param
 *  *BackgroundModelAddr [in]: The background model address, contents of CYBase.mod.
 *  *CmdModelAddr [in]: The command model address.
 *   MaxTime [in]: The maximum buffer length in number of frames for keeping the status of commands.
 *  *RejModelAddr [in]: The rejection model address.
 *  *CspWorkingRam [in]: CSP working RAM pointer
 *   Csp16KernelRamSize [in]: CSP16 kernel RAM size.
 *  *CspStateBuf [in]: state buffer zize (bytes)
 * @return
 *   CSpotterHandle: Handle of a recognizer.
 */
CSP_HANDLE CSP16_CB_Init(uint8_t *BackgroundModelAddr, uint8_t *CmdModelAddr, int32_t MaxTime, uint8_t *RejModelAddr, CSP16_WORKING_RAM *CspWorkingRam, int32_t Csp16KernelRamSize, uint8_t *Csp16StateBuf)
{
	int32_t ErrCode;
	CSP_HANDLE CSpotterHandle = NULL;
	uint8_t *CspCmdModelAddr[2];

  if(PsdNumWord > 0)
	{
		CspCmdModelAddr[0] = CmdModelAddr;
		CspCmdModelAddr[1] = (uint8_t *)SdModelAddr;
		CSpotterHandle = CSpotter16_Init_Multi(BackgroundModelAddr, &CspCmdModelAddr[0], 2, MaxTime, pCsp16A1801WorkingRam->CspKernelRam, Csp16KernelRamSize, Csp16StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
  }
  else
	{
		CSpotterHandle = CSpotter16_Init_Sep(BackgroundModelAddr, CmdModelAddr, MaxTime, CspWorkingRam->CspKernelRam, Csp16KernelRamSize, Csp16StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
	}

	if(CSpotterHandle == NULL)
	{
		return CSpotterHandle;;
	}
	else
	{
	  CSpotter16_Reset(CSpotterHandle);
		//CSpotter16_SetEnableNBest(CSpotterHandle, 1);
		//CSpotter16_SetEnableRejectedResult(CSpotterHandle, 1);

	  CSpotter16_SetRejectionLevel(CSpotterHandle, 3);
	  //CSpotter16_SetCmdRewardOffset(CSpotterHandle, 0, 1);
	  //CSpotter16_SetCmdRewardOffset(CSpotterHandle, 1, 1);
    CSpotter16_SetRejectedResultEnergyThreshd(CSpotterHandle, 500);
	  //CSpotter_SetCmdResponseOffset(CSpotterHandle, 0, 30);

		return CSpotterHandle;
	}
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
void CSP16_CB_Start(int16_t *DstPcmBufAddr, uint16_t DataLen)
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
	DMA_InstallIsrService(mDsAdcDmaHandle, CSP16_DmaIsrService);
	DMA_EnableInt(mDsAdcDmaHandle);
	NVIC_EnableIRQ(DMA_IRQn);	
	
  DMA_Trigger(mDsAdcDmaHandle, (uint32_t)&DS_ADC->DATA, (uint32_t)DstPcmBufAddr, DataLen);
}

/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void CSP16_CB_Stop()
{
	DSADC_Close();
	DMA_Close(mDsAdcDmaHandle);
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
void CSP16_CB_GetAdc_DmaIsr(int16_t *DstPcmBufAddr, uint16_t DataLen)
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
	SPIFC_WriteNBytes((uint32_t)dest, src, nSize);
	Cache_Init();
	SPIFC_AutoMode(SPIFC_2IO_MODE);

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
	int32_t iCount;

	for(iCount = 0; iCount < nSize; iCount += 0x1000)
	{
		SPIFC_SectorErase((uint32_t)(dest + iCount));
	}

	Cache_Init();
	SPIFC_AutoMode(SPIFC_2IO_MODE);

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
	memcpy(dest, src, nSize);

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
	memcpy(dest, src, nSize);

	return 0;
}

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 */
int32_t DataFlash_Write(uint8_t *dest, uint8_t *src, int32_t nSize)
{
	return 0;
}

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 */
int32_t DataFlash_Erase(uint8_t *dest, int32_t nSize)
{
	return 0;
}
