/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   DAC_GPCM1Fx.h
 * @Version:  
 *   V1.0.2
 * @Date:     
 *   May 20, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _DAC_GPCM1F_H_
#define _DAC_GPCM1F_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>


/*---------------------------------------------------------------------------------------
 * User Definition Area
 *---------------------------------------------------------------------------------------*/
#define CURRENT_DAC_RAMP_UP_DELAY           (700)
#define CURRENT_DAC_RAMP_DOWN_DELAY         (500)


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
#define AUDPWM_CLK_IN                       (8192000UL)                                       // 8.192Mhz. USER DO NOT MODIFY
#define CALC_AUDPWM_CLK_DIV(SysCoreClk)     (((SysCoreClk) / (AUDPWM_CLK_IN)) - 1)

/*
 * Definition for the 1st parameter of DAC_Init()
 */ 
#define DAC_TRG_SEL_MANUAL                  (0)
#define DAC_TRG_SEL_TM0                     (1)
#define DAC_TRG_SEL_TM1                     (2)
#define DAC_TRG_SEL_TM2                     (3)
#define DAC_TRG_SEL_CCP0_TM                 (4)
#define DAC_TRG_SEL_CCP1_TM                 (5)
#define DAC_TRG_SEL_CTS_TM0                 (6)
#define DAC_TRG_SEL_CTS_TM1                 (7)


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif 
 
void DAC_Open(void);
void DAC_Close(void);
void DAC_CurrentDac_Enable(void);
void DAC_CurrentDac_Disable(void);
void DAC_CurrentDac_Reset(void);
void DAC_Scale_Enable(void);
void DAC_Scale_Disable(void);
void DAC_CH0_Init(uint32_t TriggerSel);
void DAC_CH0_Disable(void);
void DAC_CH0_HalfVol_Enable(void);
void DAC_CH0_HalfVol_Disable(void);
void DAC_CH1_Init(uint32_t TriggerSel);
void DAC_CH1_Disable(void);
void DAC_CH1_HalfVol_Enable(void);
void DAC_CH1_HalfVol_Disable(void);

void DAC_AudioPwm_Open(void);
void DAC_AudioPwm_Close(void);	
void DAC_AudioPwm_IP_Enable(void);	
void DAC_AudioPwm_IP_Disable(void);
void DAC_SetAudPwmGain(uint32_t AudPwmGain);	

#ifdef __cplusplus
}
#endif

#endif
