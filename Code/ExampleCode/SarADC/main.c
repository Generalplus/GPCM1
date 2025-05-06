/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   main.c
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
#include "KeyScan.h"
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
KEYSCAN_WORKING_RAM KeyScanWorkingRam;
uint32_t ScanedKey;

uint8_t AdcCovChTemp[256];                                           // Temp buffer for recording ADC regular mode sequence
uint32_t AdcCovChTempIdx = 0;
uint32_t iCount;


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/
 
/** 
 * @brief  
 *   Initialize SAR-ADC regular mode
 *    - Input from SAR-ADC ch6 (line-in from IOA[23])
 *    - When ADC conversion is done, IOA[8] is toggled.
 *    - Output the convered data to IOB[6:0]. 
 * @param 
 *   None.
 * @return 
 *   None.
 */ 
void SarAdc_RegularModeInitial()
{	
	uint8_t AdcChSeq[] = {6};                                          // sequence: always ch6
	
	SAR_ADC_Open();
	SAR_ADC_SetAdcChSampleTime(6, SAR_ADC_SMPTIME_32ADCCLK);	         // Set SAR-ADC ch6 sample time = 32 ADC clock
	SAR_ADC_RegMode_Init(AdcChSeq, SAR_ADC_REG_CH_NUM_1, SAR_ADC_GAP_SEL_TM0, SAR_ADC_LOOP_DISABLE);	
	SAR_ADC_LineInPadEnable(LINE_PAD_IOA23);
	WRITE_REG(SAR_ADC->STS , SAR_ADC_STS_REG_MODE_INT_FLAG);           // Clear regular mode interrupt flag
	SAR_ADC_RegMode_EnableInt();
	NVIC_EnableIRQ(SAR_ADC_IRQn);
}

/** 
 * @brief  
 *   Initialize SAR-ADC regular loop mode
 *    - Input from SAR-ADC ch0/ch1/ch2/ch3/ch4/ch5/ch8/ch9
 *    - When ADC conversion is done, IOA[8] is toggled.
 *    - Output the convered data to IOB[6:0].
 * @param 
 *   None.
 * @return 
 *   None.
 */ 
void SarAdc_RegularModeLoopInitial()
{
	uint8_t AdcChSampleTimeTable[] = {
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 0 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 1 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 2 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 3 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 4 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 5 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 6 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 7 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK,        // Sar-ADC Channel 8 sample time
	                                  SAR_ADC_SMPTIME_32ADCCLK         // Sar-ADC Channel 9 sample time		
	                                 };	
  uint8_t RegModeSequenceTable[] = {0, 1, 2, 3, 4, 5, 8, 9};         // Channel sequence of the regular loop mode: ch0(IOA[17]) -> ch1(IOA[18]) -> ch2(IOA[19]) -> ch3(IOA[20]) ->
                                                                     //	                                           ch4(IOA[21]) -> ch5(IOA[22]) -> ch8(V15_ADC) -> ch9(VSS_ADC) -> (loop)
	
	SAR_ADC_Open();
	SAR_ADC_SetAdcMultiChSampleTime(AdcChSampleTimeTable, sizeof(AdcChSampleTimeTable));
  SAR_ADC_RegMode_Init(RegModeSequenceTable, SAR_ADC_REG_CH_NUM_8, SAR_ADC_GAP_SEL_TM0, SAR_ADC_LOOP_ENABLE);
	SAR_ADC_LineInPadEnable(LINE_PAD_IOA17 | LINE_PAD_IOA18 | LINE_PAD_IOA19 | LINE_PAD_IOA20 | LINE_PAD_IOA21 | LINE_PAD_IOA22);
	WRITE_REG(SAR_ADC->STS , SAR_ADC_STS_REG_MODE_INT_FLAG);           // Clear regular mode interrupt flag
	SAR_ADC_RegMode_EnableInt();
	NVIC_EnableIRQ(SAR_ADC_IRQn);
}

/** 
 * @brief  
 *   Initialize SAR-ADC injection mode
 *    - Input from SAR-ADC ch5
 *    - When ADC conversion is done, IOA[9] is toggled.
 *    - Output the convered data to IOB[6:0].
 * @param 
 *   None.
 * @return 
 *   None.
 */ 
void SarAdc_Injection_Initial()
{
  SAR_ADC_Open();
	SAR_ADC_SetAdcChSampleTime(5, SAR_ADC_SMPTIME_32ADCCLK);           // Set SAR-ADC ch5 sample time = 32 adc clock
	SAR_ADC_LineInPadEnable(LINE_PAD_IOA22);
	SAR_ADC_InjMode_Init(0, 5, SAR_ADC_INJ_TRG_SEL_TM0);               // Initialize SAR-ADC injection 0, ADC channel: ch5, trigger source: Timer0.
	WRITE_REG(SAR_ADC->STS , SAR_ADC_STS_INJ0_INT_FLAG);               // Clear injection0 interrupt flag
	SAR_ADC_InjMode_EnableInt(0);
	NVIC_EnableIRQ(SAR_ADC_IRQn);	
}


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{	
  SystemInit();
	
	KeyScan_Initial(&KeyScanWorkingRam);                               // Key scan init	

  /*
	 * IOA[9:8] output low
	 */
  GPIO_SetMode(GPIOA, 0x00000300, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOA->OBUF, 0x00000300, 0);	
	
  /*
	 * IOB[5:0] output low
	 */
  GPIO_SetMode(GPIOB, 0x0000003F, GPIO_MODE_OUTPUT);
  MODIFY_REG(GPIOB->OBUF, 0x0000003F, 0);	
	
  while(1)
	{		
		WDT_Clear();
    KeyScan_ServiceLoop();
		ScanedKey = KeyScan_GetCh();
		switch(ScanedKey)
		{
		  case 0x01:                                                     // IOA0+VDD: Regular mode
				TIMER_Close(TM0);
        SarAdc_RegularModeInitial();			  
			  SAR_ADC_RegMode_Start();
        TIMER_Open(TM0);
	      TIMER_SetFreq(TM0, 2000);			
        break;			
			
		  case 0x02:                                                     // IOA1+VDD:	Regular loop mode
				TIMER_Close(TM0);
			  SarAdc_RegularModeLoopInitial();			  
				SAR_ADC_RegMode_Start();
        TIMER_Open(TM0);
	      TIMER_SetFreq(TM0, 2000);
        break;

		  case 0x04:                                                     // IOA2+VDD: Stop regular loop mode
				TIMER_Close(TM0);
        SAR_ADC_RegMode_Stop();
			  AdcCovChTempIdx = 0;
        break;		
			
			case 0x08:                                                     // IOA3+VDD: Injection 0
				TIMER_Close(TM0);
				SAR_ADC_RegMode_Stop();
        SarAdc_Injection_Initial();
        TIMER_Open(TM0);
	      TIMER_SetFreq(TM0, 2000);			  			
				break;
		}				
	}
}


/*---------------------------------------------------------------------------------------
 * IRQ Handler
 *---------------------------------------------------------------------------------------*/

/** 
 * @brief  
 *   Sar-ADC IRQ handler
 * @param 
 *   None.
 * @return 
 *   None.
 */
void SAR_ADC_IRQHandler(void)
{		
	if((SAR_ADC->STS & SAR_ADC_STS_REG_MODE_INT_FLAG) != 0)
	{			
		GPIOA->OBUF ^= BIT8;
		
		AdcCovChTemp[AdcCovChTempIdx++] = SAR_ADC->REG_COV;
		if(AdcCovChTempIdx == sizeof(AdcCovChTemp))
		{
			AdcCovChTempIdx = 0;
		}
		
		switch(SAR_ADC->REG_COV)
		{
			case 0x0:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x1:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x2:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x3:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x4:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x5:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x6:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;
			
			case 0x7:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);				
				break;
			
			case 0x8:
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;

			case 0x9:		
				GPIOB->OBUF = (SAR_ADC->REG_DATA >> 10);
				break;			
		}		

		SAR_ADC->STS = SAR_ADC_STS_REG_MODE_INT_FLAG;                    // Clear regular mode interrupt flag
	}		
	
	if((SAR_ADC->STS & SAR_ADC_STS_INJ0_INT_FLAG) != 0)
	{	
		GPIOA->OBUF ^= BIT9;
		GPIOB->OBUF = (SAR_ADC->INJ0_DATA >> 10);		

		SAR_ADC->STS = SAR_ADC_STS_INJ0_INT_FLAG;                        // Clear injection0 interrupt flag
	}	
}
