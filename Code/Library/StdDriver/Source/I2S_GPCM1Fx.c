/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   I2S_GPCM1Fx.c
 * @Version:
 *   V0.9.
 * @Date:
 *   Nov. 22, 2022
 * @Abstract:
 *   GPCE4F I2S Tx Output: IOB[10]: DATA/ IOB[11]: SLR
 *   GPCM1F I2S Rx Input:  IOA[21]: DATA/ IOA[20]:SLR
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
void I2S_Init(void)
{
	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_I2S_CLK_ENABLE);	           // I2S clock enable
  // NVIC_EnableIRQ(I2S_IRQn);
	WRITE_REG(I2S->CTRL2,(I2S_CTRL2_BCLK_DIV_6));

  WRITE_REG(I2S->CTRL,(I2S_CTRL_MONO_MODE_ENABLE | I2S_CTRL_MERGE_DISABLE | I2S_CTRL_HALF_FULL_INT_DISABLE | I2S_CTRL_INT_SEL_RISE |
	                     I2S_CTRL_MODE_SEL_MASTER | I2S_CTRL_FRAMING_MODE_SEL_I2S | I2S_CTRL_FRAME_SIZE_SEL_16BITS | I2S_CTRL_DATA_LENGTH_SEL_16BITS |
                    // I2S_CTRL_MODE_SEL_SLAVE | I2S_CTRL_FRAMING_MODE_SEL_I2S | I2S_CTRL_FRAME_SIZE_SEL_16BITS | I2S_CTRL_DATA_LENGTH_SEL_16BITS |
	                     I2S_CTRL_ALIGN_SEL_LEFT | I2S_CTRL_RX_DATA_MSB | I2S_CTRL_RX_DATA_LATCH_SEL_FALL |I2S_CTRL_RX_FRAME_LEFT |
	                     I2S_CTRL_RX_1ST_FRAME_LEFT | I2S_CTRL_RX_ENABLE));
}


