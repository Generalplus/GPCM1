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
#include "CSP16_User.h"
#include "CSpotterSD16TrainApi.h"
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) uint8_t Csp16A1801WorkingRam[sizeof(CSP16_WORKING_RAM)];
__align(4) CSP16_PCM_BUFFER CspPcmBuffer;
__align(4) KEYSCAN_WORKING_RAM KeyScanWorkingRam;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) uint8_t Csp16A1801WorkingRam[sizeof(CSP16_WORKING_RAM)];
__attribute__ ((aligned (4))) CSP16_PCM_BUFFER CspPcmBuffer;;
__attribute__ ((aligned (4))) KEYSCAN_WORKING_RAM KeyScanWorkingRam;;
#endif


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	CSP_HANDLE CSP16Handle;
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

  /*
	 * CSP init
	 */
	while((CSP16Handle = CSP16_User_Init((CSP16_WORKING_RAM*)Csp16A1801WorkingRam, &CspPcmBuffer)) == NULL)
	{
		GPIOA->OBUF |= 0x0000FF00;                             // CSP16 init fail.
	}
  CSP16_Start(CSP16Handle);
  GPIOA->OBUF |= BIT15;

	while(1)
	{
		WDT_Clear();

	  CspResult = CSP16_GetResult(CSP16Handle);
		if(CspResult >= 0)
	  {
			CSP16_Stop(CSP16Handle);
      GPIOA->OBUF = 0;

			SACM_A1801_Initial((SACM_A1801_WORKING_RAM*)Csp16A1801WorkingRam, (SACM_A1801_TEMP_RAM*)&Csp16A1801WorkingRam[sizeof(SACM_A1801_WORKING_RAM)], (SACM_A1801_PCM_BUFFER*)&Csp16A1801WorkingRam[(sizeof(SACM_A1801_WORKING_RAM) + sizeof(SACM_A1801_TEMP_RAM))]);
			if(CspResult >= 1)
			{
			  SACM_A1801_Play(A1801_User_GetA1801StartAddr(CSP16_User_GetTagID(CspResult - 1) + 1), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
			}

		  while((SACM_A1801_GetStatus() & A1801_PLAY_FLAG) != 0)
		  {
		    SACM_A1801_ServiceLoop();
			  WDT_Clear();
		  }

	    CSP16Handle = CSP16_User_Init((CSP16_WORKING_RAM*)Csp16A1801WorkingRam, &CspPcmBuffer);
		  CSP16_Start(CSP16Handle);
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

      CSpotter16_GetNBestScore(CSP16Handle, pnCmdIdx, pnScore, 5);
		}

		if(CSP16_CheckCpuOverload() != 0)
		{
		  CSP16_ClearCpuOverloadFlag();
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
				CSP16_Stop(CSP16Handle);
        CSP16_User_EraseAllSdCommand();
			  GPIOA->OBUF = (BIT8 | BIT10 | BIT12 | BIT14);
	      CSP16Handle = CSP16_User_Init((CSP16_WORKING_RAM*)Csp16A1801WorkingRam, &CspPcmBuffer);
		    CSP16_Start(CSP16Handle);
			  GPIOA->OBUF |= BIT15;
        break;
    }

    if(PsdTagId >= 0)
		{
      SACM_A1801_Stop();
      while(CSP16_User_TrainSdCommand(PsdTagId) == -1);
			PsdTagId = -1;
			CSP16_User_Init((CSP16_WORKING_RAM*)Csp16A1801WorkingRam, &CspPcmBuffer);
			CSP16_Start(CSP16Handle);
			GPIOA->OBUF = BIT15;
	  }
	}
}
