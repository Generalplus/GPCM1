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
#include "glibc_wrapper.h"


/*---------------------------------------------------------------------------------------
 * Gobal Variable Declaration Area
 *---------------------------------------------------------------------------------------*/
uint8_t SrcBuf1[16] = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F};
uint8_t DstBuf1[16];
uint8_t SrcBuf2[16] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF};
uint8_t DstBuf2[16];


/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/
/**
 * @brief
 *	 Read bytes data from SPI flash
 * @param
 *   SpiAddr [in]: SPI flash address
 *  *pDstBuf [out]: Destination buffer address
 *   NumByteToRead [in]: Data length (Byte)
 * @return
 *        None
 */
void SPI_Flash_ReadNBytes_DMA(uint32_t SpiAddr, uint8_t *pDstBuf, uint32_t NumByteToRead)
{
  SPI_TYPE_DEF 	*mSpiHandle = SPI0;
  __IO uint32_t *mSpiCsPin = &GPIOA_OBIT->OBIT11;

	*mSpiCsPin = 0;                                                    // CS low
	SPI_Write(SPI_FLASH_READ);

	#if SPI_FLASH_4BYTE_ADDR_EN
	SPI_Write((ReadAddr & 0xFF000000) >> 24);                          // for 4-bytes address
	#endif

	SPI_Write((SpiAddr & 0xFF0000) >> 16);                             // addressH
	SPI_Write((SpiAddr & 0xFF00) >> 8);                                // addressM
	SPI_Write(SpiAddr & 0xFF);                                         // addressL

  /*
   * SPI RX DMA
   */
  DMA_Init(DMA0, DMA_REQSEL_SPI0, DMA_SRC_DATA_8B, DMA_SRC_ADDR_FIX, DMA_DST_DATA_8B, DMA_DST_ADDR_INC);
  while(DMA_CheckBusy(DMA0) != 0);                                   // Check DMAx busy
  DMA_Trigger(DMA0, (uint32_t)&mSpiHandle->RX_DATA , (uint32_t)&pDstBuf[0], NumByteToRead);
  while(DMA_CheckBusy(DMA0) != 0);

	*mSpiCsPin = 0xFFFFFFFF;                                           // CS high
}

/**
 * @brief
 *   Write N bytes data to SPI flash
 * @param
 *   SpiAddr [in]: SPI flash address
 *  *pSrcBuf [in]: Source buffer address
 *   NumBytes [in]: Data length (Byte)
 * @return
 *   None
 */
void SPI_Flash_WritePage_DMA(uint32_t SpiAddr, uint8_t* pSrcBuf, uint32_t NumBytes)
{
  SPI_TYPE_DEF 	*mSpiHandle = SPI0;
  __IO uint32_t *mSpiCsPin = &GPIOA_OBIT->OBIT11;

	Flash_Write_Enable();
	*mSpiCsPin = 0;                                                    // CS low
	SPI_Write(SPI_FLASH_PP);

	#if SPI_FLASH_4BYTE_ADDR_EN
	SPI_Write((WriteAddr & 0xFF000000) >> 24);                         // for 4-bytes address
	#endif

	SPI_Write((SpiAddr & 0xFF0000) >> 16);                             // addressH
	SPI_Write((SpiAddr & 0xFF00) >> 8);                                // addressM
	SPI_Write(SpiAddr & 0xFF);                                         // addressL

	/*
   * SPI TX DMA
	 */
  DMA_Init(DMA0, DMA_REQSEL_SPI0, DMA_SRC_DATA_8B, DMA_SRC_ADDR_INC, DMA_DST_DATA_8B, DMA_DST_ADDR_FIX);
  while(DMA_CheckBusy(DMA0) != 0);                                   // Check DMAx busy
  DMA_Trigger(DMA0, (uint32_t)&pSrcBuf[0], (uint32_t)&mSpiHandle->TX_DATA, NumBytes);
  while(DMA_CheckBusy(DMA0) != 0);

	while(((mSpiHandle->STS) & SPI_CTRL_TX_DONE_FLAG) == 0);
	mSpiHandle->STS |= SPI_CTRL_TX_DONE_FLAG;
	*mSpiCsPin = 0xFFFFFFFF;                                           // CS high
	while((SPI_Flash_ReadSR() & SPI_FLASH_SR_WIP_BIT) != 0);
}


/*---------------------------------------------------------------------------------------
 * Main Function
 *---------------------------------------------------------------------------------------*/
int main(void)
{
  SystemInit();

  SPI_Flash_Open();

	SPI_Flash_Sector_Erase(0);
	SPI_Flash_SendNBytes(0x0100, (uint8_t *)SrcBuf1, sizeof(SrcBuf1));
	SPI_Flash_ReadNBytes(0x0100, (uint8_t *)DstBuf1, sizeof(DstBuf1));

	SPI_Flash_Sector_Erase(0);
	// For SPI0 DMA test
  SPI_Flash_WritePage_DMA(0x0100, (uint8_t *)SrcBuf2, sizeof(SrcBuf2));
  SPI_Flash_ReadNBytes_DMA(0x0100, (uint8_t *)DstBuf2, sizeof(DstBuf2));

  while(1)
	{
		WDT_Clear();
	}
}
