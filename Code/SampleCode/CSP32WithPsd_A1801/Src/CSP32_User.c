/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   CSP32_User.c
 * @Version:
 *   V1.0.3
 * @Date:
 *   March 28, 2022
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "CSP32_User.h"
#include "CSP32_FileMerger.h"
#include "CSpotterSDTrainApi.h"
#include "KeyScan.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
DMA_TYPE_DEF *mDsAdcDmaHandle;

CSP32_WORKING_RAM *pCsp32WorkingRam;
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
CSP_HANDLE CSP32_User_Init(CSP32_WORKING_RAM *CspWorkingRam, CSP32_PCM_BUFFER *Csp32PcmBuffer)
{
	CSP_HANDLE Csp32Handle;
	uint8_t *CspModelAddr[3];            // CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ... /CspModelAddr[n-1]:ExtRej Model

	pCsp32WorkingRam = CspWorkingRam;

	UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
	Csp32Handle = CSP32_Init(CspModelAddr[0], CspModelAddr[1], CSP32_MAX_TIME, CspModelAddr[2], CspWorkingRam, CSP32_KERNEL_RAM_SIZE, Csp32PcmBuffer);
	if(Csp32Handle == NULL)
	{
		return Csp32Handle;
	}
	else
	{
	  CSpotter_Reset(Csp32Handle);
		CSpotter_SetEnableNBest(Csp32Handle, 1);
		CSpotter_SetEnableRejectedResult(Csp32Handle, 1);

		CSpotter_SetRejectionLevel(Csp32Handle, 8);
	  CSpotter_SetCmdRewardOffset(Csp32Handle, 0, 0);
	  CSpotter_SetCmdRewardOffset(Csp32Handle, 1, 2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 2, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 3, 3);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 4, 1);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 5, -3);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 6, 3);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 7, -2);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 8, 100);
		CSpotter_SetCmdRewardOffset(Csp32Handle, 9, 100);
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

    CSpotter_SetRejectedResultEnergyThreshd(Csp32Handle, 500);
		CSpotter_SetCmdResponseOffset(Csp32Handle, 8, 20);
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

		return Csp32Handle;
	}
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
int32_t CSP32_User_TrainSdCommand(int32_t PsdTagId)
{
	int32_t Size;
	int32_t SkipFrameNum = 40;
	uint8_t *CspModelAddr[3];							                                                 	// CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ...
	CSP_HANDLE CSpotterHandle = NULL;
	int32_t ErrCode;
	int32_t UsedSize;

  UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
	Size = CSpotterSD_GetMemoryUsage_FromSPI(CspModelAddr[0], 0);
	if(Size > CSP32_KERNEL_RAM_SIZE)    																										// Check kernel RAM size
	{
		return -1;                                                                           	// CSP32_KERNEL_RAM_SIZE is not enough. return NULL.
	}

  CSpotterHandle = CSpotterSD_Init_FromSPI(CspModelAddr[0], pCsp32WorkingRam->CspKernelRam, CSP32_KERNEL_RAM_SIZE, &ErrCode);
  CSpotterSD_DeleteWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDTRAIN_BUFSIZE, PsdTagId, &UsedSize);
	PsdNumWord = CSpotter_GetNumWord((uint8_t *)SdModelAddr);
	CSpotterSD_SetBackgroundEnergyThreshd(CSpotterHandle, 1200);

	UttrIdx = 0;
	while(UttrIdx < NUM_UTTR)
	{
	  if((ErrCode = CSpotterSD_AddUttrStart_FromSPI(CSpotterHandle, UttrIdx, (uint8_t*)(SdTrainAddr + UttrIdx * UTTR_BUF_SIZE), UTTR_BUF_SIZE)) != CSPOTTER_SUCCESS)
		{
		  break;
		}

		while(1)
		{
		  WDT_Clear();
	    if((CSP32_GetStatus() & CSP32_WORK_FLAG) != 0)
	    {
				if(SkipFrameNum > 0)
				{
					SkipFrameNum--;
				}
				else
				{
			    if((ErrCode = CSpotterSD_AddSample_FromSPI(CSpotterHandle, pCsp32WorkingRam->Csp32VrBufPtr, CSP32_FRAME_SIZE)) != CSPOTTER_ERR_NeedMoreSample)
		      {
				    break;
		      }
				}

				CSP32_ClrWorkFlag();
			}

			GPIOA->OBUF = ((~(GPIOA->OBUF)) & 0x1000) | ((UttrIdx + 1) << 8);

		  KeyScan_ServiceLoop();
		  if(KeyScan_GetCh() != 0)
		  {
				return -2;
			}
	  }

		GPIOA->OBUF = ((UttrIdx + 1) << 8) | 0x2000;
		if((ErrCode = CSpotterSD_AddUttrEnd_FromSPI(CSpotterHandle)) != CSPOTTER_SUCCESS)
		{
 		  return -1;
		}

    if(UttrIdx == 0 && (CSpotterSD_SimilarityCheckWithRejLevel_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, 0)) >= 0)
		{
			return -1;
    }

    if(UttrIdx > 0 && (ErrCode = (CSpotterSD_DifferenceCheckWithRejLevel_FromSPI(CSpotterHandle, 0))) != CSPOTTER_SUCCESS)
		{
			return -1;
    }

    UttrIdx++;
	}

  GPIOA->OBUF = 0x4000;
	if((ErrCode = CSpotterSD_TrainWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDMODEL_SIZE, PsdTagId, 0, &UsedSize)) != CSPOTTER_SUCCESS)
	{
		return -1;
	}
	else
	{
		PsdNumWord = CSpotter_GetNumWord((uint8_t *)SdModelAddr);
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
void CSP32_User_EraseAllSdCommand(void)
{
	CSP_HANDLE CSpotterHandle;
	uint8_t *CspModelAddr[2];							         // CspModelAddr[0]:Background Model/CspModelAddr[1]:SI Command Model ...
	int32_t ErrCode;
	int32_t UsedSize;
	int32_t iCount;

	UnpackCspModel((uint32_t *)_GROUP_TABLE_ADDR, CspModelAddr, (sizeof(CspModelAddr) / sizeof(CspModelAddr[0])));
  CSpotterHandle = CSpotterSD_Init_FromSPI(CspModelAddr[0], pCsp32WorkingRam->CspKernelRam, CSP32_KERNEL_RAM_SIZE, &ErrCode);
	for(iCount = 0; iCount < SD_TAG_NUM; iCount++)
	{
    CSpotterSD_DeleteWord_FromSPI(CSpotterHandle, (uint8_t *)SdModelAddr, SDTRAIN_BUFSIZE, iCount, &UsedSize);
    WDT_Clear();
  }

  PsdNumWord = CSpotter_GetNumWord((uint8_t *)SdModelAddr);
}

/**
 * @brief
 *
 * @param
 *   CspCmdID [in]: CSP command ID
 * @return
 *   CSP Tag ID
 */
int32_t CSP32_User_GetTagID(int32_t CspCmdID)
{
  return CSpotterSD_GetTagID_FromSPI((uint8_t *)SdModelAddr, CspCmdID);
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
	int32_t Size;
	int32_t ErrCode;
	CSP_HANDLE CSpotterHandle = NULL;
	uint8_t *CspCmdModelAddr[2];

	SdModelAddr = (uint32_t)BackgroundModelAddr + SIMODEL_SIZE;;
	if(((uint32_t)SdModelAddr & 0x0FFF) != 0) {
		SdModelAddr = ((((uint32_t)SdModelAddr) >> 12) + 1) << 12;
  }
	SdTrainAddr = SdModelAddr + SDMODEL_SIZE;

	PsiNumWord = CSpotter_GetNumWord((uint8_t *)CmdModelAddr);
	PsdNumWord = CSpotter_GetNumWord((uint8_t *)SdModelAddr);

	#if CSP32_USE_REJECTION_MODEL == 1
	if(PsdNumWord > 0)
	{
		CspCmdModelAddr[0] = CmdModelAddr;
		CspCmdModelAddr[1] = (uint8_t *)SdModelAddr;
		Size = CSpotter_GetMemoryUsage_MultiWithExtRejModel_FromSPI((uint8_t *)BackgroundModelAddr, &CspCmdModelAddr[0], 2, MaxTime, RejModelAddr);
	  if(Size > CSP32_KERNEL_RAM_SIZE)   						// Check kernel RAM size
	  {
		  return NULL;                               	// CSP_KERNEL_RAM_SIZE is not enough. return NULL.
	  }
		else
		{
			CSpotterHandle = CSpotter_Init_MultiWithExtRejModel(BackgroundModelAddr, &CspCmdModelAddr[0], 2, MaxTime, RejModelAddr, pCsp32WorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
			return CSpotterHandle;
		}
  }
	else
	{
		Size = CSpotter_GetMemoryUsage_SepWithExtRejModel((uint8_t *)BackgroundModelAddr, (uint8_t *)CmdModelAddr, MaxTime, RejModelAddr);
	  if(Size> CSP32_KERNEL_RAM_SIZE)      					// Check kernel RAM size
	  {
		  return NULL;                               	// CSP_KERNEL_RAM_SIZE is not enough. return NULL.
	  }
		else
		{
			CSpotterHandle = CSpotter_Init_SepWithExtRejModel(BackgroundModelAddr, CmdModelAddr, MaxTime, RejModelAddr, CspWorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
			return CSpotterHandle;
		}
	}
	#else
	if(PsdNumWord > 0)
	{
		CspCmdModelAddr[0] = CmdModelAddr;
		CspCmdModelAddr[1] = (uint8_t *)SdModelAddr;
		Size = CSpotter_GetMemoryUsage_Multi_FromSPI((uint8_t *)BackgroundModelAddr, &CspCmdModelAddr[0], 2, CSP32_MAX_TIME);
	  if(Size > CSP32_KERNEL_RAM_SIZE)   						// Check kernel RAM size
	  {
		  return NULL;                               	// CSP_KERNEL_RAM_SIZE is not enough. return NULL.
	  }
		else
		{
			CSpotterHandle = CSpotter_Init_Multi(BackgroundModelAddr, &CspCmdModelAddr[0], 2, MaxTime, pCsp32WorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
			return CSpotterHandle;
		}
  }
	else
	{
		Size = CSpotter_GetMemoryUsage_Sep((uint8_t *)BackgroundModelAddr, (uint8_t *)CmdModelAddr, MaxTime);
	  if(Size> CSP32_KERNEL_RAM_SIZE)      					// Check kernel RAM size
	  {
		  return NULL;                               	// CSP_KERNEL_RAM_SIZE is not enough. return NULL.
	  }
		else
		{
			CSpotterHandle = CSpotter_Init_Sep(BackgroundModelAddr, CmdModelAddr, MaxTime, CspWorkingRam->CspKernelRam, Csp32KernelRamSize, Csp32StateBuf, CSPOTTER_STATE_SIZE, &ErrCode);
			return CSpotterHandle;
		}
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
