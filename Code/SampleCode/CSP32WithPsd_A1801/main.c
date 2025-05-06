/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *
 * @Version:
 *
 * @Date:
 *
 * @Abstract:
 *
 **************************************************************************************************/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "SACM_A1801_User.h"
#include "CSP32_User.h"
#include "CSpotterSDTrainApi.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#define Aligned4B __align(4)
#elif defined(__GNUC__)
#define Aligned4B __attribute__ ((aligned (4)))
#endif

typedef union Lib_RAM_Allocate
{
  struct A18_RAM
  {
    uint8_t A1801WorkingRam[sizeof(SACM_A1801_WORKING_RAM)];
    uint8_t A1801TempBuffer[sizeof(SACM_A1801_TEMP_RAM)];
    uint8_t A1801PcmBuffer[sizeof(SACM_A1801_PCM_BUFFER )];
  }A18_RAM;

  struct CSP32_RAM
  {
    uint8_t Csp32WorkingRam[sizeof(CSP32_WORKING_RAM)];
    uint8_t Csp32PcmBuffer[sizeof(CSP32_PCM_BUFFER)];
  }CSP32_RAM;

}Lib_RAM_Allocate;

Aligned4B Lib_RAM_Allocate LibRAM;

SACM_A1801_WORKING_RAM  *A1801WorkingRam = (SACM_A1801_WORKING_RAM*)LibRAM.A18_RAM.A1801WorkingRam;
SACM_A1801_TEMP_RAM     *A1801TempBuffer = (SACM_A1801_TEMP_RAM*)LibRAM.A18_RAM.A1801TempBuffer;
SACM_A1801_PCM_BUFFER   *A1801PcmBuffer = (SACM_A1801_PCM_BUFFER*)LibRAM.A18_RAM.A1801PcmBuffer;;

CSP32_WORKING_RAM       *Csp32WorkingRam = (CSP32_WORKING_RAM*)LibRAM.CSP32_RAM.Csp32WorkingRam;
CSP32_PCM_BUFFER        *Csp32PcmBuffer  = (CSP32_PCM_BUFFER*)LibRAM.CSP32_RAM.Csp32PcmBuffer;

Aligned4B KEYSCAN_WORKING_RAM KeyScanWorkingRam;

CSP_HANDLE CSP32Handle = NULL;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	int32_t CspResult;
  int32_t pnCmdIdx[5];
  int32_t pnScore[5];
	int32_t PsdTagId = -1;
	uint32_t ScanedKey;
	int32_t iCount;

	SystemInit();
	WDT_SetClk(WDG_CLK_32768_DIV_32);

	/*
	 * SPIFC init
	 */
	SPIFC_Open();																	           // SPIFC open
	SPIFC_SetClkDiv(SPIFC_CLKSEL_HCLK_DIV2);
	//SPIFC_EN4B();																           // SPIFC enable 4 bytes
	//SPIFC_AutoMode(SPIFC_4IO_ENHANCE_MODE);		             // SPIFC auto mode
	//SPIFC_AutoMode(SPIFC_4IO_MODE);					               // SPIFC auto mode
	SPIFC_AutoMode(SPIFC_2IO_MODE);					                 // SPIFC auto mode
	if(SPIFC_TimingFineTune() == SPIFC_CALIBRATION_FAIL)     // Calibrate SPIFC clock timing.
	{
		while(1);                                              // SPIFC clock timing calibration fail!
	}

  KeyScan_Initial(&KeyScanWorkingRam);                     // key scan init

  /*
	 * IOA[15:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x0000FF00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x0000FF00, 0);

	while((CSP32Handle = CSP32_User_Init(Csp32WorkingRam, Csp32PcmBuffer)) == NULL)
	{
		GPIOA->OBUF |= 0x0000FF00;                             // CSP32 init fail.
	}

  CSP32_Start(CSP32Handle);
  GPIOA->OBUF |= BIT15;

	while(1)
	{
		WDT_Clear();

	  CspResult = CSP32_GetResult(CSP32Handle);

	  if(CspResult >= 0)
	  {
			CSP32_Stop(CSP32Handle);
      GPIOA->OBUF &= ~BIT15;
		  //GPIOA->OBUF = CspResult + 1;

			if((CspResult >= 0) && (CspResult < 8))
			{
				SACM_A1801_Initial(A1801WorkingRam, A1801TempBuffer, A1801PcmBuffer);
				SACM_A1801_Play(A1801_User_GetA1801StartAddr(CspResult + 1), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
				while((SACM_A1801_GetStatus() & A1801_PLAY_FLAG) != 0)
				{
					SACM_A1801_ServiceLoop();
					WDT_Clear();
				}
			}
	    CSP32Handle = CSP32_User_Init(Csp32WorkingRam, Csp32PcmBuffer);
			CSP32_Start(CSP32Handle);
			GPIOA->OBUF |= BIT15;
    }
		else if(CspResult == CSPOTTER_ERR_Rejected)
		{
			/*
			 * Clear pnCmdIdx[] & pnScore[]
			 */
			for(iCount = 0; iCount < 5; iCount++)
			{
				pnCmdIdx[iCount] = 0;
				pnScore[iCount] = 0;
			}

      CSpotter_GetNBestScore(CSP32Handle, pnCmdIdx, pnScore, 5);
		}

		if(CSP32_CheckCpuOverload() != 0)
		{
			CSP32_ClearCpuOverloadFlag();
		}

		KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
	  switch(ScanedKey)
		{
		  case 0x01:
				PsdTagId = 0;
        break;

		  case 0x02:
				PsdTagId = 1;
        break;

		  case 0x04:
				PsdTagId = 2;
        break;

		  case 0x08:
				PsdTagId = 3;
        break;

		  case 0x10:
				PsdTagId = 4;
        break;

		  case 0x20:
				PsdTagId = 5;
        break;

		  case 0x40:
				PsdTagId = 6;
        break;

		  case 0x80:                                           // Erase all SD command
        SACM_A1801_Stop();
				CSP32_Stop(CSP32Handle);
        CSP32_User_EraseAllSdCommand();
			  GPIOA->OBUF = (BIT8 | BIT10 | BIT12 | BIT14);
				CSP32Handle = CSP32_User_Init(Csp32WorkingRam, Csp32PcmBuffer);
		    CSP32_Start(CSP32Handle);
			  GPIOA->OBUF |= BIT15;
        break;
    }

    if(PsdTagId >= 0)
		{
      SACM_A1801_Stop();
      while(CSP32_User_TrainSdCommand(PsdTagId) == -1);
			PsdTagId = -1;
			CSP32_User_Init(Csp32WorkingRam, Csp32PcmBuffer);
			CSP32_Start(CSP32Handle);
			GPIOA->OBUF = BIT15;
	  }
	}
}
