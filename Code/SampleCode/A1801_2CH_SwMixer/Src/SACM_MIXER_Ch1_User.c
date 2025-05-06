/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   SACM_MIXER_Ch1_User.c
 * @Version:
 *   V0.9.2
 * @Date:
 *   April, 2022
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "SACM_MIXER_Ch1_User.h"
#include "SACM_A1801_User.h"
#include "SACM_A1801_CH2_User.h"
#include "APP_SwVolumeControl.h"
#include "APP_SwMixer.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
TIMER_TYPE_DEF *mDacTimerHandle;
DMA_TYPE_DEF *mDacCh1DmaHandle;


/*---------------------------------------------------------------------------------------
 * Extern Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
extern uint16_t mA1801Status;
extern uint16_t mA1801Ch2Status;
extern SACM_A1801_WORKING_RAM A1801WorkingRam;
extern SACM_A1801_WORKING_RAM A1801Ch2WorkingRam;
extern SACM_A1801_PCM_BUFFER A1801PcmBuffer;


/*---------------------------------------------------------------------------------------
 * User Subroutine Area
 *---------------------------------------------------------------------------------------*/

/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void static RampUpDacCh0()
{
	int16_t DacDataTemp1;
	int16_t DacDataTemp2;
	int16_t DacDataBuf[8];
	int16_t iCount;
	int16_t DataLen;

	DataLen = sizeof(DacDataBuf) / 2;
  DacDataTemp1 = DAC->DAC_CH0_DMA_DATA0 & 0xFFC0;
	DacDataTemp2 = DacDataTemp1;
	do
	{
		DacDataTemp2 = DacDataTemp1;
	  for(iCount = 0; iCount < DataLen; iCount++)
	  {
	    if(DacDataTemp1 > 0)
	    {
			  DacDataTemp1 -= 0x40;
		  }
	    else if(DacDataTemp1 < 0)
		  {
			  DacDataTemp1 += 0x40;
		  }
			DacDataBuf[iCount] = DacDataTemp1;
	  }
	  CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH0_DMA_ENABLE);          // DAC_Ch0 DMA request disabled.
    TIMER_Close(mDacTimerHandle);
	  DMA_Init(mDacCh1DmaHandle, DMA_REQSEL_DAC_CH0, DMA_SRC_DATA_16B, DMA_SRC_ADDR_INC, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
	  DMA_Trigger(mDacCh1DmaHandle, (uint32_t)&DacDataBuf[0], (uint32_t)&DAC->DAC_CH0_DMA_DATA0, DataLen);
		TIMER_Open(mDacTimerHandle);
		while(DMA_CheckBusy(mDacCh1DmaHandle) != 0);                // Wait DMAx busy
	} while(DacDataTemp2 != 0);
}

/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void static RampUpDacCh1()
{
	int16_t DacDataTemp1;
	int16_t DacDataTemp2;
	int16_t DacDataBuf[8];
	int16_t iCount;
	int16_t DataLen;

	DataLen = sizeof(DacDataBuf) / 2;
  DacDataTemp1 = DAC->DAC_CH1_DMA_DATA0 & 0xFFC0;
	DacDataTemp2 = DacDataTemp1;
	do
	{
		DacDataTemp2 = DacDataTemp1;
	  for(iCount = 0; iCount < DataLen; iCount++)
	  {
	    if(DacDataTemp1 > 0)
	    {
			  DacDataTemp1 -= 0x40;
		  }
	    else if(DacDataTemp1 < 0)
		  {
			  DacDataTemp1 += 0x40;
		  }
			DacDataBuf[iCount] = DacDataTemp1;
	  }
	  CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_DMA_ENABLE);          // DAC_Ch1 DMA request disabled.
    TIMER_Close(mDacTimerHandle);
		DMA_Init(mDacCh1DmaHandle, DMA_REQSEL_DAC_CH1, DMA_SRC_DATA_16B, DMA_SRC_ADDR_INC, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
		DMA_Trigger(mDacCh1DmaHandle, (uint32_t)&DacDataBuf[0], (uint32_t)&DAC->DAC_CH1_DMA_DATA0, DataLen);
		TIMER_Open(mDacTimerHandle);
		while(DMA_CheckBusy(mDacCh1DmaHandle) != 0);                // Wait DMAx busy
	} while(DacDataTemp2 != 0);
}

/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void static RampDownDacCh0()
{
  RampUpDacCh0();
}

/**
 * @brief
 *
 * @param
 *   None.
 * @return
 *   None.
 */
void static RampDownDacCh1()
{
  RampUpDacCh1();
}

/**
 * @brief
 *
 * @param
 *   A1801Status [in]: A1801 status
 * @return
 *   None.
 */
void static DacAutoRampUp(uint16_t A1801Status)
{
  if((A1801Status & A1801_AUTO_RAMP_UP_ENABLE_FLAG) != 0)
	{
		if((A1801Status & A1801_ENABLE_DAC_CH0_FLAG) != 0)
		{
			RampUpDacCh0();
		}

		if((A1801Status & A1801_ENABLE_DAC_CH1_FLAG) != 0)
		{
			RampUpDacCh1();
		}
	}
}

/**
 * @brief
 *
 * @param
 *   A1801Status [in]: A1801 status
 * @return
 *   None.
 */
void static DacAutoRampDown(uint16_t A1801Status)
{
  if((A1801Status & A1801_AUTO_RAMP_DOWN_ENABLE_FLAG) != 0)
	{
		if((A1801Status & A1801_ENABLE_DAC_CH0_FLAG) != 0)
		{
			RampDownDacCh0();
		}

		if((A1801Status & A1801_ENABLE_DAC_CH1_FLAG) != 0)
		{
			RampDownDacCh1();
		}
	}
}


/*---------------------------------------------------------------------------------------
 * Callback Function Area
 *---------------------------------------------------------------------------------------*/
/**
 * @brief
 *   Callback function. Implemented by user.
 *   When user call API function SACM_MIXER_Ch1_Initial, this function is called by MIXER Ch0 Library.
 * @param
 *  *MixerCh1WorkingRam [in]: Mixer ch0 working RAM address.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_Init(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam)
{
	mDacCh1DmaHandle = DMA0;
	mDacTimerHandle = TM0;

  TIMER_Open(mDacTimerHandle);
	TIMER_SetFreq(mDacTimerHandle, (16000 * 4));	               	// Sample rate: 10000 x 4 = 40000(Hz), for H/W 4x upsampling

	DAC_Open();
	DAC_Scale_Enable();
	DAC_CH0_Init(DAC_TRG_SEL_TM0);
	DAC_CH1_Init(DAC_TRG_SEL_TM0);
	DAC_AudioPwm_Open();
}

/**
 * @brief
 *   Callback function. To be implemented by user.
 *   When user call API function SACM_MIC2DAC_Play, this function is called by MIC Library.
 * @param
 *  *MixerCh1WorkingRam [in]: MIC2DAC working RAM address.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_StartPlay(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam)
{
	DAC_AudioPwm_IP_Enable();
	DacAutoRampUp(SACM_A1801_GetStatus());                        // DAC auto ramp up

	if((SACM_MIXER_Ch1_GetStatus() & MIXER_CH1_ENABLE_DAC_CH1_FLAG) != 0)
	{
    CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_DMA_ENABLE);          // DAC_Ch1 DMA request disabled.
		DMA_Init(mDacCh1DmaHandle, DMA_REQSEL_DAC_CH1, DMA_SRC_DATA_16B, DMA_SRC_ADDR_INC, DMA_DST_DATA_16B, DMA_DST_ADDR_FIX);
    DMA_InstallIsrService(mDacCh1DmaHandle, SACM_MIXER_Ch1_SendDac_DmaIsrService);
	  DMA_EnableInt(mDacCh1DmaHandle);
	  NVIC_EnableIRQ(DMA_IRQn);
		DMA_Trigger(mDacCh1DmaHandle, (uint32_t)MixerCh1WorkingRam->DacOutBufPtr, (uint32_t)&DAC->DAC_CH1_DMA_DATA0, MIXER_CH1_FRAME_SIZE);
	}
}

/**
 * @brief
 *   Callback function.
 * @param
 *  *MixerCh1WorkingRam [in]: MIXER_Ch1 working RAM address.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_StopPlay(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam)
{
	if((SACM_MIXER_Ch1_GetStatus() & MIXER_CH1_PLAY_FLAG) != 0)
  {
	  DacAutoRampDown(SACM_A1801_GetStatus());	                  // DAC auto ramp down

		if((SACM_MIXER_Ch1_GetStatus() & MIXER_CH1_ENABLE_DAC_CH1_FLAG) != 0)
	  {
		  DMA_Close(mDacCh1DmaHandle);
		}

    DAC_AudioPwm_IP_Disable();
  }
}

/**
 * @brief
 *   Callback function. Implemented by user.
 *   When user call API function SACM_MIC2DAC_Pause, this function is called by MIC Library.
 * @param
 *  *MixerCh1WorkingRam [in]: MIC2DAC library working RAM address.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_Pause(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam)
{
}

/**
 * @brief
 *   Callback function. Implemented by user.
 *   When user call API function SACM_MIC2DAC_Resume, this function is Called by MIC Library.
 * @param
 *  *MixerCh1WorkingRam [in]: MIC2DAC library working RAM address.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_Resume(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam)
{
	if((SACM_MIXER_Ch1_GetStatus() & MIXER_CH1_ENABLE_DAC_CH1_FLAG) != 0)
	{
    DMA_Trigger(mDacCh1DmaHandle, (uint32_t)MixerCh1WorkingRam->DacOutBufPtr, (uint32_t)&DAC->DAC_CH1_DMA_DATA0, MIXER_CH1_FRAME_SIZE);
	}
}
/**
 * @brief
 *   Callback function. Implemented by user.
 *   When playing, this function is called by MIC Library to trigger DS-ADC DMA.
 * @param
 *  *MixerCh1WorkingRam [in]: MIC2DAC working RAM address.
 *  *DstBufAddr [out]: ADC input buffer address pointer.
 *   DataLen [in]: Data length (halfword)
 * @return
 *   None.
 */
void MIXER_Ch1_CB_GetAdc_DmaIsr(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam, int8_t *DstBufAddr, uint16_t DataLen)
{
}

/**
 * @brief
 *   Callback function. Implemented by user.
 *   When playing, this function is called by MIC Library to trigger DAC DMA.
 * @param
 *  *MixerCh1WorkingRam [in]: MIC2DAC working RAM address.
 *  *SrcBufAddr [in]: DAC Output Buffer address pointer.
 *   DataLen [in]: Data length (halfword)
 * @return
 *   None.
 */
void MIXER_Ch1_CB_SendDac_DmaIsr(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam, int16_t *SrcBufAddr, uint16_t DataLen)
{
	if((SACM_MIXER_Ch1_GetStatus() & MIXER_CH1_ENABLE_DAC_CH1_FLAG) != 0)
	{
		while(DMA_CheckBusy(mDacCh1DmaHandle) != 0);        			  // Check DMAx busy
    DMA_Trigger(mDacCh1DmaHandle, (uint32_t)SrcBufAddr, (uint32_t)&DAC->DAC_CH1_DMA_DATA0, DataLen);
	}
}

/**
 * @brief
 *   Callback function. Implemented by user.
 *   When playing, this function is called by MIC library to encode data.
 * @param
 *  *MixerCh1WorkingRam [in]: MIXER_Ch1 working RAM address.
 *  *DstBufAddr [out]: Destination buffer address pointer.
 *  *SrcBufAddr [in]: Source buffer address pointer.
 * @return
 *   None.
 */
void MIXER_Ch1_CB_VoiceProcess(const SACM_MIXER_CH1_WORKING_RAM *MixerCh1WorkingRam, int16_t *DstBufAddr, int8_t *SrcBufAddr)
{
	uint32_t iCount;
  int16_t *SwMixerCh1Ptr;
  int16_t *SwMixerCh2Ptr;

  if(((SACM_A1801_GetStatus() & A1801_PLAY_FLAG) != 0) && (SACM_A1801_GetStatus() & A1801_PAUSE_FLAG) == 0)
	{
    if((mA1801Status & A1801_DECODE_END_FLAG)!= 0)
    {
      SACM_A1801_Stop();
      SwMixerCh1Ptr = 0x0000;
    }
    else
    {
      mA1801Status |= A1801_DECODE_WORK_FLAG;
      A1801WorkingRam.A1801DecodeBufPtr = A1801PcmBuffer.A1801PcmBuffer;
      SACM_A1801_ServiceLoop();
      for(iCount = 0; iCount < MIXER_CH1_FRAME_SIZE; iCount++)
      {
        DstBufAddr[iCount] = A1801PcmBuffer.A1801PcmBuffer[iCount];
      }
      SwMixerCh1Ptr = &DstBufAddr[0];
      APP_SwVolCtrl_VolProcess(0, SwMixerCh1Ptr, MIXER_CH1_FRAME_SIZE);
    }
	}
	else
	{
    SwMixerCh1Ptr = 0x0000;
	}

	if(((SACM_A1801_CH2_GetStatus() & A1801_PLAY_FLAG) != 0) && (SACM_A1801_CH2_GetStatus() & A1801_PAUSE_FLAG) == 0)
	{
    if((mA1801Ch2Status & A1801_DECODE_END_FLAG)!= 0)
    {
      SACM_A1801_CH2_Stop();
      SwMixerCh2Ptr = 0x0000;
    }
    else
    {
      mA1801Ch2Status |= A1801_DECODE_WORK_FLAG;
      A1801Ch2WorkingRam.A1801DecodeBufPtr = A1801PcmBuffer.A1801PcmBuffer;
      SACM_A1801_CH2_ServiceLoop();
      SwMixerCh2Ptr = &A1801PcmBuffer.A1801PcmBuffer[0];
      APP_SwVolCtrl_VolProcess(1, SwMixerCh2Ptr, MIXER_CH1_FRAME_SIZE);
    }
	}
	else
	{
    SwMixerCh2Ptr = 0x0000;
	}
  APP_SwMixer_2ch(SwMixerCh1Ptr, SwMixerCh2Ptr, DstBufAddr, MIXER_CH1_FRAME_SIZE);
}
