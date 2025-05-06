/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   eFlash_GPCM1Fx.c
 * @Version:  
 *   V0.9.2
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
 *   
 * @param 
 *   None.
 * @return 
 *   None.
 */
void NVM_WaitBusy()
{
	uint32_t iCount;
	
	for(iCount = 0 ; iCount < 10; iCount++);
	while((FLASH->STS & 0x0001) != 0);
}

/** 
 * @brief  
 *   Erase one page(1KB) of eFlash 
 * @param 
 *   eFlashAddr [in]: eFlash address
 * @return 
 *   None.
 */
void EFlash_PageErase(uint32_t* eFlashAddr)
{	
	Cache_Disable();
	
	/*
	 * eFlash unlock
	 */ 
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY1);
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY2);  
  NVM_WaitBusy();	
	
	/*
	 * eFlash page erase
	 */
	MODIFY_REG(FLASH->CTRL, FLASH_CTRL_TYPE_MSK, FLASH_CTRL_TYPE_PAGEERASE);
  WRITE_REG(FLASH->ERASE_ADDR, (uint32_t)eFlashAddr);
	WRITE_REG(FLASH->ERASE_CTRL, FLASH_ERASE_CTRL_NVM_START);
	NVM_WaitBusy();	
  while((FLASH->ERASE_CTRL & 0x0001) != 0);	
	
	MODIFY_REG(FLASH->CTRL, FLASH_CTRL_TYPE_MSK, FLASH_CTRL_TYPE_READ);
	SET_BIT(FLASH->CTRL, FLASH_CTRL_LOCK);	                                // eFlash lock		
	Cache_Enable();
}

/** 
 * @brief  
 *   Write N word data to flash
 * @param 
 *  *pSrcAddr [in]: Source address
 *  *pDstAddr [in]: Destination address(eFlash address)
 *   NumWords [in]: Data length
 * @return 
 *   None
 */
void EFlash_WritePage(uint32_t *pSrcBuf, uint32_t *pDstAddr , uint32_t NumWords)
{ 
	uint32_t iCount;
	
	Cache_Disable();

	/*
	 * eFlash unlock
	 */ 
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY1);
	WRITE_REG(FLASH->CTRL_UNLOCK, UNLOCK_KEY2);
  NVM_WaitBusy();				
	
	MODIFY_REG(FLASH->CTRL,FLASH_CTRL_TYPE_MSK,FLASH_CTRL_TYPE_PROGRAM);	  
	for(iCount = 0; iCount < NumWords; iCount++)
	{	  
		*pDstAddr++ = *pSrcBuf++;
	}
	NVM_WaitBusy();			
	
	MODIFY_REG(FLASH->CTRL, FLASH_CTRL_TYPE_MSK, FLASH_CTRL_TYPE_READ);
	SET_BIT(FLASH->CTRL, FLASH_CTRL_LOCK);	                                // eFlash lock	
	Cache_Enable();
}
