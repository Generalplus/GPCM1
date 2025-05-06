/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   I2C_GPCM1Fx.c
 * @Version:  
 *   V0.9.1
 * @Date:     
 *   July 30, 2021
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
 *   I2cSelIo [in]:
 *    - I2C_IOA0_1, I2C_IOA13_17, I2C_IOA15_16 
 * @return 
 *   None.
 */
void I2C_Master_Init(uint32_t I2cSelIo)
{
	MODIFY_REG(IOFUNC->CTRL0, GPIOFUNC_CTRL0_I2C_MSK, I2cSelIo);
	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_I2C_CLK_ENABLE);             // I2C Clock enable
	
  switch(I2cSelIo)
	{
		case I2C_IOA0_1:
			GPIO_SetMode(GPIOA, (BIT0 | BIT1), GPIO_MODE_FLOATING);
			break;
		
		case I2C_IOA13_17:
			GPIO_SetMode(GPIOA, (BIT13 | BIT17), GPIO_MODE_FLOATING);
			break;
		
		case I2C_IOA15_16:
			GPIO_SetMode(GPIOA, (BIT15 | BIT16), GPIO_MODE_FLOATING);
			break;		
	}	
	
	I2C->CTRL = I2C_CTRL_I2C_ENABLE | I2C_CTRL_CLK_SEL_HCLK_DIV_1024 | I2C_CTRL_MODE_SEL_MASTER;	
	I2C->ADDR = I2C_ADDR_MODE_7BIT;
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   None.
 */
void I2C_Close()
{		
	I2C->CTRL = 0;
	CLEAR_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_I2C_CLK_ENABLE);           // I2C Clock disable
}

/**
 * @brief
 *
 * @param
 *   I2cClkDiv [in]:
 *    - I2C_CLK_SEL_HCLK_DIV_16,  I2C_CLK_SEL_HCLK_DIV_32,  I2C_CLK_SEL_HCLK_DIV_64, I2C_CLK_SEL_HCLK_DIV_128,
 *    - I2C_CLK_SEL_HCLK_DIV_256, I2C_CLK_SEL_HCLK_DIV_768, I2C_CLK_SEL_HCLK_DIV_1024
 * @return
 *   None.
 */
void I2C_SetClkDiv(uint32_t I2cClkDiv)
{
  MODIFY_REG(I2C->CTRL, I2C_CTRL_CLK_SEL_MSK, I2cClkDiv);
}

/** 
 * @brief  
 *         
 * @param 
 *   SlaveAddr [in]: I2C slave address
 *   RW_Bit [in]:
 *    - I2C_WRITE, I2C_READ
 * @return 
 *   1: ACK
 *   0: NAK
 */
uint8_t I2C_Master_StartAndAddr(uint16_t SlaveAddr, uint8_t RW_Bit)
{ 	
	MODIFY_REG(I2C->ADDR, (I2C_ADDR_ADDRESS_MSK | I2C_RW_SEL_MSK), ((SlaveAddr & 0xFE) | RW_Bit));
	I2C->CTRL &= ~I2C_CTRL_MST_NACK;
	I2C->CTRL |= I2C_CTRL_MST_STR | I2C_CTRL_I2C_TRIGGER;		
	while((I2C->STS & I2C_STS_TRS_DONE_FLAG) == 0);	
	I2C->STS |= I2C_STS_TRS_DONE_FLAG;
	while(I2C_CheckBusy() != 0);
	
	if((I2C->STS & I2C_STS_RX_NO_ACK_FLAG) != 0)
	{	    
		I2C->STS = I2C_STS_RX_NO_ACK_FLAG;
		
		return 0;
	}
	
	return 1;
}


/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   None.
 */
void I2C_Master_Stop()
{ 	
	if(I2C_CheckBusy() != 0)
	{
	  while((I2C->STS & I2C_STS_TRS_DONE_FLAG) == 0);	
	  I2C->STS |= I2C_STS_TRS_DONE_FLAG;				
	}	
	
	I2C->CTRL |= I2C_CTRL_MST_STP | I2C_CTRL_I2C_TRIGGER;	
	while(I2C_CheckBusy() != 0);  
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   None.
 */
void I2C_Master_SendByte(uint8_t DataByte)
{
	I2C->DATA = DataByte;
	while((I2C->STS & I2C_STS_TRS_DONE_FLAG) == 0);
	I2C->STS |= I2C_STS_TRS_DONE_FLAG;
  while(I2C_CheckBusy() != 0);  	
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   A byte data
 */
void I2C_Master_ReadByteTrigger()
{	
  volatile uint32_t DataTemp;	
	
	DataTemp = I2C->DATA;	
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   A byte data
 */
uint8_t I2C_Master_ReadByteAck()
{	
	I2C->CTRL &= ~I2C_CTRL_MST_NACK;
	while((I2C->STS & I2C_STS_TRS_DONE_FLAG) == 0);	
	I2C->STS |= I2C_STS_TRS_DONE_FLAG;
  while(I2C_CheckBusy() != 0);  	
	
	return I2C->DATA;	
}

/** 
 * @brief  
 *         
 * @param 
 *   None.
 * @return 
 *   A byte data
 */
uint8_t I2C_Master_ReadByteNack()
{	
	I2C->CTRL |= I2C_CTRL_MST_NACK;  
	while((I2C->STS & I2C_STS_TRS_DONE_FLAG) == 0);	
	I2C->STS |= I2C_STS_TRS_DONE_FLAG; 
  while(I2C_CheckBusy() != 0);  	
	
	return I2C->DATA;
}

/** 
 * @brief  
 *   Check I2C busy status      
 * @param 
 *   None.
 * @return 
 *   0 -> I2C done.
 *   nonzero -> I2C busy.
 */
uint32_t I2C_CheckBusy(void)
{  
	return (I2C->STS & I2C_STS_BUSY_FLAG);
}
