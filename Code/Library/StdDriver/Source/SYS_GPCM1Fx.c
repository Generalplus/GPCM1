/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   SYS_GPCM1Fx.c
 * @Version:  
 *   V0.9.3
 * @Date:     
 *   December 07, 2020
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
 *  Clear cache       
 * @param 
 *   None.
 * @return 
 *   None.
 */
void Cache_Init()
{	
  SMU->CACHE_CTRL &= ~SMU_CACHE_CTRL_CACHE_ENABLE;
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	SMU->CACHE_CTRL |= SMU_CACHE_CTRL_CACHE_ENABLE;
}

 /** 
 * @brief  
 *  Enable cache        
 * @param 
 *   None.
 * @return 
 *   None.
 */
void Cache_Enable()
{	
	SMU->CACHE_CTRL |= SMU_CACHE_CTRL_CACHE_ENABLE;
}

/** 
 * @brief  
 *   Disable cache        
 * @param 
 *   None.
 * @return 
 *   None.
 */
void Cache_Disable()
{	
  SMU->CACHE_CTRL &= ~SMU_CACHE_CTRL_CACHE_ENABLE;
	__NOP();
	__NOP();
	__NOP();
	__NOP();	
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   System core clock (Hz)
 */
uint32_t System_GetCoreClock(void)
{	
	if((ACU->PLL_CTRL & ACU_PLL_CTRL_PLL_ENABLE) != 0)
	{	
	  switch(ACU->PLL_CTRL & ACU_PLL_CTRL_CLK_SEL_MSK)
	  {			
		  case ACU_PLL_CTRL_CLK_SEL_24D576M:
			  return 24576000;
		
		  case ACU_PLL_CTRL_CLK_SEL_32D768M:
			  return 32768000;

		  case ACU_PLL_CTRL_CLK_SEL_40D960M:
			  return 40960000;

		  case ACU_PLL_CTRL_CLK_SEL_49D192M:
			  return 49152000;

		  case ACU_PLL_CTRL_CLK_SEL_57D344M:
			  return 57344000;

		  case ACU_PLL_CTRL_CLK_SEL_65D536M:
			  return 65536000;

		  case ACU_PLL_CTRL_CLK_SEL_73D728M:
			  return 73728000;
			
			default:
		  case ACU_PLL_CTRL_CLK_SEL_81D920M:			
			  return 81920000;
	  }
	}
	else
	{
		return 8192000;
	}		
}

/** 
 * @brief  
 *   
 * @param 
 *   WaitState [in]:    
 *    - ONE_WAITSTATE,  TWO_WAITSTATE, THREE_WAITSTATE, FOUR_WAITSTATE,
 *      FIVE_WAITSTATE, SIX_WAITSTATE, SEVEN_WAITSTATE
 * @return 
 *   None.
 */
void System_WaitState(uint32_t WaitState)
{	
	Cache_Disable();	
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY1);
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY2);                                            // NVM nulock		
	MODIFY_REG(FLASH->OPTION0_STS, FLASH_OPTION0_STS_WAITSTATE_MSK, WaitState);	           // Setting wait state;	
	WRITE_REG(FLASH->CTRL_UNLOCK, 0);                                                      // NVM lock
	Cache_Enable();
}

/** 
 * @brief  
 *   Enable PLL        
 * @param 
 *   None.
 * @return 
 *   None.
 */
void PLL_Enable()
{	
  uint32_t iCount;
	
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY1);
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);	       // SMU nulock		
	while((CLOCK->CLKSTS & CLOCK_CLKSTS_IOSC8M_RDY) == 0);                                 // Wait IOSC8M stable
	SET_BIT(ACU->PLL_CTRL, ACU_PLL_CTRL_PLL_ENABLE);                                       // PLL enable	
  for(iCount = 0; iCount < 20; iCount++);                                                // Wait H/W update PLL Ready Flag
	while((CLOCK->CLKSTS & CLOCK_CLKSTS_PLL_RDY) == 0);                                    // Wait PLL stable			
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);	                             // SMU lock	
}

/** 
 * @brief  
 *   Disable PLL        
 * @param 
 *   None.
 * @return 
 *   None.
 */
void PLL_Disable()
{	
  uint32_t iCount;
	
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY1);
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);	       // SMU nulock		
	while((CLOCK->CLKSTS & CLOCK_CLKSTS_IOSC8M_RDY) == 0);                                 // Wait IOSC8M stable
	CLEAR_BIT(ACU->PLL_CTRL, ACU_PLL_CTRL_PLL_ENABLE);                                     // PLL disable
  for(iCount = 0; iCount < 20; iCount++);
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);	                             // SMU lock	
}

/** 
 * @brief  
 *   
 * @param 
 *   PllClkFreq [in]:    
 *    - PLL_24D576M, PLL_32D768M, PLL_40D960M, PLL_49D192M,
 *      PLL_57D344M, PLL_65D536M, PLL_73D728M, PLL_81D920M
 * @return 
 *   None.
 */
void PLL_ChangeClk(uint32_t PllClkFreq)
{		
	uint32_t iCount;
	
	System_WaitState(SEVEN_WAITSTATE);	
	while((CLOCK->CLKSTS & CLOCK_CLKSTS_IOSC8M_RDY) == 0);                                 // Wait IOSC8M stable	
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY1);
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);	       // SMU nulock			
	MODIFY_REG(ACU->PLL_CTRL, ACU_PLL_CTRL_CLK_SEL_MSK, PllClkFreq);		
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);	                             // SMU lock
	for(iCount = 0; iCount < 20; iCount++);                                                // Wait H/W update PLL Ready Flag
	while((CLOCK->CLKSTS & CLOCK_CLKSTS_PLL_RDY) == 0);                                    // Wait PLL stable
	
	switch(PllClkFreq)
	{
		case PLL_24D576M:
			System_WaitState(ONE_WAITSTATE);
		  break;
		
		case PLL_32D768M:
			System_WaitState(ONE_WAITSTATE);
		  break;		
		
		case PLL_40D960M:
			System_WaitState(ONE_WAITSTATE);
		  break;	

		case PLL_49D192M:
			System_WaitState(TWO_WAITSTATE);
		  break;	

		case PLL_57D344M:
			System_WaitState(TWO_WAITSTATE);
		  break;		
		
		case PLL_65D536M:
			System_WaitState(TWO_WAITSTATE);
		  break;

		case PLL_73D728M:
			System_WaitState(THREE_WAITSTATE);
		  break;		
		
		case PLL_81D920M:
			System_WaitState(FOUR_WAITSTATE);
		  break;				
	}	
	
	SystemCoreClockUpdate();
}

/** 
 * @brief  
 *   
 * @param 
 *   HclkSrc [in]:    
 *    - HCLK_SEL_SYS32K, HCLK_SEL_PLL, HCLK_SEL_IOSC8M
 * @return 
 *   None.
 */
void HCLK_SrcSel(uint32_t HclkSrc)
{  
	MODIFY_REG(CLOCK->AHBCKSEL, CLOCK_AHBCKSEL_HCLK_SEL_MSK, (HclkSrc & CLOCK_AHBCKSEL_HCLK_SEL_MSK));
}
