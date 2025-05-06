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
#include "CSP32_User.h"
#include "SACM_A1801_User.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
__align(4) uint8_t Csp32A1801WorkingRam[sizeof(CSP32_WORKING_RAM)];
__align(4) CSP32_PCM_BUFFER Csp32PcmBuffer;
#elif defined(__GNUC__)
__attribute__ ((aligned (4))) uint8_t Csp32A1801WorkingRam[sizeof(CSP32_WORKING_RAM)];
__attribute__ ((aligned (4))) CSP32_PCM_BUFFER Csp32PcmBuffer;
#endif

CSP_HANDLE CSP32Handle = NULL;


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
	int32_t CspResult;
  int32_t pnCmdIdx[5];
  int32_t pnScore[5];	
	int32_t iCount;	

	SystemInit();

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

  /*
	 * IOA[15:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x0000FF00, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x0000FF00, 0);

	while((CSP32Handle = CSP32_User_Init((CSP32_WORKING_RAM*)Csp32A1801WorkingRam, &Csp32PcmBuffer)) == NULL)
	{
		GPIOA->OBUF |= 0x0000FF00;                             // CSP32 init fail.
	}

  CSP32_Start(CSP32Handle);
  GPIOA->OBUF |= BIT15;

	while(1)
	{
		WDT_Clear();

	  CspResult = CSP32_GetResult(CSP32Handle);

	  if((CspResult >= 0) && (CspResult < 8))
	  {
			CSP32_Stop(CSP32Handle);
      GPIOA->OBUF &= ~BIT15;
		  //GPIOA->OBUF = CspResult + 1;

			SACM_A1801_Initial((SACM_A1801_WORKING_RAM*)Csp32A1801WorkingRam, (SACM_A1801_TEMP_RAM*)&Csp32A1801WorkingRam[sizeof(SACM_A1801_WORKING_RAM)], (SACM_A1801_PCM_BUFFER*)&Csp32A1801WorkingRam[(sizeof(SACM_A1801_WORKING_RAM) + sizeof(SACM_A1801_TEMP_RAM))]);
			SACM_A1801_Play(A1801_User_GetA1801StartAddr(CspResult + 1), A1801_DAC_CH0, A1801_AUTO_RAMP_UP + A1801_AUTO_RAMP_DOWN);
		  while((SACM_A1801_GetStatus() & A1801_PLAY_FLAG) != 0)
		  {
		    SACM_A1801_ServiceLoop();
			  WDT_Clear();
		  }

	    CSP32Handle = CSP32_User_Init((CSP32_WORKING_RAM*)Csp32A1801WorkingRam, &Csp32PcmBuffer);
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
	}
}
