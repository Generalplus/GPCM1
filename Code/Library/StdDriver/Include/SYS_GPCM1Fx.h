/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *
 * @Version:  
 *   V0.9.3
 * @Date:     
 *   December 07, 2020
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _SYS_GPCM1F_H_
#define _SYS_GPCM1F_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <stdint.h>


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/

/*
 * Definition for the 1st parameter of System_WaitState()
 */ 
#define ONE_WAITSTATE                                      FLASH_OPTION0_STS_1WAITSTATE
#define TWO_WAITSTATE                                      FLASH_OPTION0_STS_2WAITSTATE
#define THREE_WAITSTATE                                    FLASH_OPTION0_STS_3WAITSTATE
#define FOUR_WAITSTATE                                     FLASH_OPTION0_STS_4WAITSTATE
#define FIVE_WAITSTATE                                     FLASH_OPTION0_STS_5WAITSTATE
#define SIX_WAITSTATE                                      FLASH_OPTION0_STS_6WAITSTATE
#define SEVEN_WAITSTATE                                    FLASH_OPTION0_STS_7WAITSTATE

/*
 * Definition for the 1st parameter of PLL_ChangeClk()
 */ 
#define PLL_81D920M                                        ACU_PLL_CTRL_CLK_SEL_81D920M
#define PLL_73D728M                                        ACU_PLL_CTRL_CLK_SEL_73D728M
#define PLL_65D536M                                        ACU_PLL_CTRL_CLK_SEL_65D536M
#define PLL_57D344M                                        ACU_PLL_CTRL_CLK_SEL_57D344M
#define PLL_49D192M                                        ACU_PLL_CTRL_CLK_SEL_49D192M
#define PLL_40D960M                                        ACU_PLL_CTRL_CLK_SEL_40D960M
#define PLL_32D768M                                        ACU_PLL_CTRL_CLK_SEL_32D768M
#define PLL_24D576M                                        ACU_PLL_CTRL_CLK_SEL_24D576M

/*
 * Definition for the 1st parameter of HCLK_SrcSel()
 */ 
#define HCLK_SEL_SYS32K                                    CLOCK_AHBCKSEL_HCLK_SEL_SYS32K
#define HCLK_SEL_PLL                                       CLOCK_AHBCKSEL_HCLK_SEL_PLL
#define HCLK_SEL_IOSC8M                                    CLOCK_AHBCKSEL_HCLK_SEL_IOSC8M


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif
	
void Cache_Init(void);
void Cache_Enable(void);
void Cache_Disable(void);
uint32_t System_GetCoreClock(void);
void System_WaitState(uint32_t WaitState);
void PLL_Enable(void);
void PLL_Disable(void);
void PLL_ChangeClk(uint32_t PllClkFreq);
void HCLK_SrcSel(uint32_t HclkSrc);


#ifdef __cplusplus
}
#endif	
	
#endif
