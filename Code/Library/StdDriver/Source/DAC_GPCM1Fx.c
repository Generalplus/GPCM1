/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   DAC_GPCM1Fx.c
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   May 20, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
 
 
/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/

/** 
 * @brief  
 *   Open DAC and Audio PWM
 * @param 
 *   None. 
 * @return 
 *   None.
 */
void DAC_Open(void) 
{
	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_DAC_CLK_ENABLE);	           // DAC clock enable	
}
 
/** 
 * @brief  
 *  Close DAC and AUDPWM
 * @param 
 *   None. 
 * @return 
 *   None.
 */
void DAC_Close()
{ 
	DAC->CTRL = 0;	
	CLEAR_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_DAC_CLK_ENABLE);	         // DAC clock disable	
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CurrentDac_Enable()
{			
	int16_t DacDataTemp1;
	int16_t DacDataTemp2;
	int16_t DacDataTemp3;
	int16_t DacDataTemp4;
	int16_t iCount;
	uint32_t DelayCount;	
	
	SET_BIT(DAC->CTRL, DAC_CTRL_CURRENT_DAC_ENABLE);	
	
  DacDataTemp1 = DAC->DAC_CH0_DATA & 0xFFE0;
	DacDataTemp2 = DacDataTemp1;
	
  DacDataTemp3 = DAC->DAC_CH1_DATA & 0xFFE0;
	DacDataTemp4 = DacDataTemp3;	
	do
	{	
		DacDataTemp2 = DacDataTemp1;
		DacDataTemp4 = DacDataTemp3;
	  for(iCount = 0; iCount < 8; iCount++)
	  {			
	    if(DacDataTemp1 > 0)
	    {
			  DacDataTemp1 -= 0x10;
		  }
	    else if(DacDataTemp1 < 0)
		  {
			  DacDataTemp1 += 0x10;
		  }										

	    if(DacDataTemp3 > 0)
	    {
			  DacDataTemp3 -= 0x10;
		  }
	    else if(DacDataTemp3 < 0)
		  {
			  DacDataTemp3 += 0x10;
		  }				
			
			DAC->DAC_CH0_DATA = DacDataTemp1;
			DAC->DAC_CH1_DATA = DacDataTemp3;		
      for(DelayCount = 0; DelayCount < CURRENT_DAC_RAMP_UP_DELAY; DelayCount++);			
	  }
	} while((DacDataTemp2 != 0) || (DacDataTemp4 != 0));
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CurrentDac_Disable()
{	
	int16_t DacDataTemp1;
	int16_t DacDataTemp2;		
	int16_t DacDataTemp3;
	int16_t DacDataTemp4;			
	int16_t iCount;
	uint32_t DelayCount;		
	
	MODIFY_REG(DAC->CTRL, (DAC_CTRL_DAC_CH0_TRG_SEL_MSK | DAC_CTRL_DAC_CH1_TRG_SEL_MSK), (DAC_CTRL_DAC_CH0_TRG_SEL_MANUAL | DAC_CTRL_DAC_CH1_TRG_SEL_Manual));
	
  DacDataTemp1 = DAC->DAC_CH0_DATA & 0xFFC0;
	DacDataTemp2 = DacDataTemp1;
  DacDataTemp3 = DAC->DAC_CH1_DATA & 0xFFC0;
	DacDataTemp4 = DacDataTemp3;	
	do
	{	
		DacDataTemp2 = DacDataTemp1;
		DacDataTemp4 = DacDataTemp3;
	  for(iCount = 0; iCount < 8; iCount++)
	  {	
      DacDataTemp1 ^= 0x8000;
	    if(DacDataTemp1 != 0)
	    {
			  DacDataTemp1 -= 0x40;
		  }
			DacDataTemp1 ^= 0x8000;	    			

      DacDataTemp3 ^= 0x8000;			
	    if(DacDataTemp3 != 0)
	    {
			  DacDataTemp3 -= 0x40;
		  }
	    DacDataTemp3 ^= 0x8000;
			
			DAC->DAC_CH0_DATA = DacDataTemp1;		
			DAC->DAC_CH1_DATA = DacDataTemp3;				
			for(DelayCount = 0; DelayCount < CURRENT_DAC_RAMP_DOWN_DELAY; DelayCount++);
	  }
	} while(((DacDataTemp2 ^= 0x8000) != 0) || ((DacDataTemp4 ^= 0x8000) != 0));			
	
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_CURRENT_DAC_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CurrentDac_Reset()
{	
	DAC->DAC_CH0_DATA = 0x8000;
	DAC->DAC_CH1_DATA = 0x8000;
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_Scale_Enable()
{	
	SET_BIT(DAC->CTRL, DAC_CTRL_SCALE_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_Scale_Disable()
{	
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_SCALE_ENABLE);
}

/** 
 * @brief  
 *         
 * @param 
 *   TriggerSel [in]:
 *    - DAC_TRG_SEL_TM0, DAC_TRG_SEL_TM1, DAC_TRG_SEL_TM2, DAC_TRG_SEL_CCP0_TM, 
 *      DAC_TRG_SEL_CCP1_TM, DAC_TRG_SEL_CTS_TM0, DAC_TRG_SEL_CTS_TM1
 * @return 
 *   None.
 */
void DAC_CH0_Init(uint32_t TriggerSel)
{	
	MODIFY_REG(DAC->CTRL, DAC_CTRL_DAC_CH0_TRG_SEL_MSK, (TriggerSel << DAC_CTRL_DAC_CH0_TRG_SEL_POS));
	MODIFY_REG(DAC->CTRL, DAC_CTRL_DAC_CH0_UPSMP_MODE_MSK, DAC_CTRL_DAC_CH0_UPSMP_MODE_4X);	
	SET_BIT(DAC->CTRL, DAC_CTRL_DAC_CH0_ENABLE);	                     //	Enable DAC channel0	
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH0_Disable()
{
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH0_ENABLE);	                   //	Disable DAC channel0	
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH0_HalfVol_Enable()
{	
	SET_BIT(DAC->CTRL, DAC_CTRL_DAC_CH0_HALF_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH0_HalfVol_Disable()
{	
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH0_HALF_ENABLE);
}

/** 
 * @brief  
 *         
 * @param 
 *   TriggerSel [in]:
 *    - DAC_TRG_SEL_TM0, DAC_TRG_SEL_TM1, DAC_TRG_SEL_TM2, DAC_TRG_SEL_CCP0_TM, 
 *      DAC_TRG_SEL_CCP1_TM, DAC_TRG_SEL_CTS_TM0, DAC_TRG_SEL_CTS_TM1
 * @return 
 *   None.
 */
void DAC_CH1_Init(uint32_t TriggerSel)
{	
	MODIFY_REG(DAC->CTRL, DAC_CTRL_DAC_CH1_TRG_SEL_MSK, (TriggerSel << DAC_CTRL_DAC_CH1_TRG_SEL_POS));
	MODIFY_REG(DAC->CTRL, DAC_CTRL_DAC_CH1_UPSMP_MODE_MSK, DAC_CTRL_DAC_CH1_UPSMP_MODE_4X);	
	SET_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_ENABLE);	                     //	Enable DAC channel1
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH1_Disable()
{
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_ENABLE);	                   //	Disable DAC channel1	
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH1_HalfVol_Enable()
{	
	SET_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_HALF_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_CH1_HalfVol_Disable()
{	
	CLEAR_BIT(DAC->CTRL, DAC_CTRL_DAC_CH1_HALF_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_AudioPwm_Open()
{		
	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_AUDPWM_CLK_ENABLE);          // AUDPWM clock enable
  MODIFY_REG(CLOCK->CLKDIV1, CLOCK_CLKDIV1_AUDCLK_SEL_MSK, (CALC_AUDPWM_CLK_DIV(System_GetCoreClock()) << CLOCK_CLKDIV1_AUDCLK_SEL_POS));
	DAC->AUDPWM_CTRL = AUDPWM_CTRL_AUDPWM_ENABLE | AUDPWM_CTRL_AUDPWM_GAIN_LV31 | AUDPWM_CTRL_AUTOMUTE_OFF | AUDPWM_CTRL_MUTE_STATE_SEL_8MHZ | AUDPWM_CTRL_AUDPWM_IP_DISABLE;
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_AudioPwm_Close()
{		
	DAC->AUDPWM_CTRL = 0;
	CLEAR_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_AUDPWM_CLK_ENABLE);        // AUDPWM clock disable		
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_AudioPwm_IP_Enable()
{		
	MODIFY_REG(DAC->AUDPWM_CTRL, AUDPWM_CTRL_AUDPWM_IP_EN_MSK, AUDPWM_CTRL_AUDPWM_IP_ENABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   None.
 * @return 
 *   None.
 */
void DAC_AudioPwm_IP_Disable()
{		
	MODIFY_REG(DAC->AUDPWM_CTRL, AUDPWM_CTRL_AUDPWM_IP_EN_MSK, AUDPWM_CTRL_AUDPWM_IP_DISABLE);
}

/** 
 * @brief  
 *          
 * @param 
 *   AudPwmGain [in]: Audio PWM Gain level 0 ~ level 62.
 *    - input range: 0 ~ 62
 * @return 
 *   None.
 */
void DAC_SetAudPwmGain(uint32_t AudPwmGain)
{
	MODIFY_REG(DAC->AUDPWM_CTRL, AUDPWM_CTRL_AUDPWM_GAIN_MSK, ((AudPwmGain << AUDPWM_CTRL_AUDPWM_GAIN_POS) & AUDPWM_CTRL_AUDPWM_GAIN_MSK));
}
