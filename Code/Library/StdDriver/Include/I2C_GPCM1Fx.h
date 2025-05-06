/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:     
 *   I2C_GPCM1Fx.h
 * @Version:  
 *   V0.9.1
 * @Date:     
 *   July 30, 2021
 * @Abstract: 
 *
 **************************************************************************************************/
#ifndef _I2C_GPCM1F_H_
#define _I2C_GPCM1F_H_


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"


/*---------------------------------------------------------------------------------------
 * Definition Area
 *---------------------------------------------------------------------------------------*/
 
/*
 * Definition for the 1st parameter of I2C_Master_Init()
 */ 
#define I2C_IOA0_1                     GPIOFUNC_CTRL0_I2C_IOA0_1
#define I2C_IOA13_17                   GPIOFUNC_CTRL0_I2C_IOA13_17
#define I2C_IOA15_16                   GPIOFUNC_CTRL0_I2C_IOA15_16

/*
 * Definition for the 1st parameter of I2C_SetClkDiv()
 */
#define I2C_CLK_SEL_HCLK_DIV_16         I2C_CTRL_CLK_SEL_HCLK_DIV_16
#define I2C_CLK_SEL_HCLK_DIV_32         I2C_CTRL_CLK_SEL_HCLK_DIV_32  
#define I2C_CLK_SEL_HCLK_DIV_64         I2C_CTRL_CLK_SEL_HCLK_DIV_64 
#define I2C_CLK_SEL_HCLK_DIV_128        I2C_CTRL_CLK_SEL_HCLK_DIV_128
#define I2C_CLK_SEL_HCLK_DIV_256        I2C_CTRL_CLK_SEL_HCLK_DIV_256 
#define I2C_CLK_SEL_HCLK_DIV_768        I2C_CTRL_CLK_SEL_HCLK_DIV_768
#define I2C_CLK_SEL_HCLK_DIV_1024       I2C_CTRL_CLK_SEL_HCLK_DIV_1024 

/*
 * Definition for the 2nd parameter of I2C_Master_StartAndAddr()
 */ 
#define I2C_WRITE                       I2C_RW_SEL_WRITE
#define I2C_READ                        I2C_RW_SEL_READ


/*---------------------------------------------------------------------------------------
 * Prototype Function Declaration Area
 *---------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

void I2C_Master_Init(uint32_t I2CSelIo);
void I2C_Close(void);
void I2C_SetClkDiv(uint32_t I2cClkDiv);
uint8_t I2C_Master_StartAndAddr(uint16_t SlaveAddr, uint8_t RW_bit);
void I2C_Master_Stop(void);
void I2C_Master_SendByte(uint8_t DataByte);
void I2C_Master_ReadByteTrigger(void);
uint8_t I2C_Master_ReadByteAck(void);
uint8_t I2C_Master_ReadByteNack(void);
uint32_t I2C_CheckBusy(void);
	
	
#ifdef __cplusplus
}
#endif

#endif
