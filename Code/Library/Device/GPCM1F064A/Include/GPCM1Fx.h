/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *   GPCM1Fx.h
 * @Version:
 *   V1.0.1
 * @Date:
 *   March 30, 2022
 * @Abstract:
 *   Registers definition for Generalplus GPCM1Fx Series
 *   2022.03.17 Update CCPx TMCMP_CTRL[7:4]
 *   2022.03.30 Remove CTS TMB10PLOAD register
 **************************************************************************************************/
#ifndef _GPCM1Fx_H_
#define _GPCM1Fx_H_

/**
 * <Device>
 * =================================================================================
 * |Name             |GPCM1Fxxx
 * |Version 		     |
 * |Description	     |GPCM1Fxxx
 * |AddressUnitBits  |8
 * |Width            |32
 * |ResetValue       |0
 * |ResetMask        |0
 * =================================================================================
 * </Device>
 */

/* GPIO Configration
 * =================================================================================
 * CFG[1:0] OBUF	Function Description	 Wakeup
 *  0    0    0		Input Pull Low          Yes
 *  0    0    1		Input Pull High         Yes
 *  0    1    x		Input Floating					Yes
 *  1    0    0		Output Open Drain       No
 *  1    0    1		Output Sink mode        No
 *  1    1    0		Output Low              No
 *  1    1    1		Output High             No
 * =================================================================================
 * Default: Input with pull low.
 */

/* Special IO Function
 * =================================================================================
 * IOA[15:0]  IOA00  IOA01  IOA02  IOA03  IOA04  IOA05  IOA06  IOA07  IOA08  IOA09  IOA10  IOA11  IOA12  IOA13  IOA14  IOA15
 * CCP        CCP0_1 CCP0_1 CCP0_1 CCP0_1   -      -      -      -      -      -      -      -      -    CCP0_0 CCP0_0 CCP0_0
 * CTS         YES    YES    YES    YES    YES    YES    YES    YES    YES    YES     -      -      -      -      -      -
 * I2C        SCK_0  SDA_0    -      -      -      -      -      -      -      -      -      -      -    SCK_2    -    SCK_1
 * IOPWM        -      -      -      -      -     YES    YES    YES    YES    YES    YES    YES    YES     -      -      -
 * IR_Tx        -      -      -      -    Tx_1     -      -      -      -      -      -      -      -      -      -      -
 * UART       Tx_3     -      -      -    Tx_0    Rx_0    -      -      -    Rx_3     -      -      -    Tx_1   Rx_1     -
 * SPI0         -      -      -      -      -      -      -      -      -    SCLK_1 SI_1   CS_1   SO_1     -      -      -
 * SPI1       SCLK_1 SI_1   CS_1   SO_1     -      -      -      -      -      -      -      -      -      -      -      -
 * WakeUp      YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES    YES
 * X32K         -      -      -      -      -      -      -      -      -      -      -      -      -    X32KI  X32KO    -

 * ----------------------------------------------------------------------------
 * IOA[24:16] IOA16  IOA17  IOA18  IOA19  IOA20  IOA21  IOA22  IOA23  IOA24
 * CCP        CCP0_0   -    CCP1   CCP1   CCP1   CCP1     -      -      -
 * I2C        SDA_1  SDA_2    -      -      -      -      -      -      -
 * I2S          -      -    MCLK   BCLK   LR     DATA     -      -      -
 * ICE I/F      -      -      -      -      -      -      -      -     SDA
 * IR_Tx        -    Tx_0     -      -      -      -      -      -      -
 * LineIN       -     YES    YES    YES    YES    YES    YES    YES    YES
 * QD           -      -    QD0_A  QD0_B  QD1_A  QD1_B    -      -      -
 * UART         -      -      -      -      -      -     Tx_2   Rx_2    -
 * SPI1         -      -    SCLK_0 SI_0   CS_0   SO_0     -      -      -
 * WakeUp      YES    YES    YES    YES    YES    YES    YES    YES    YES

 * ----------------------------------------------------------------------------
 * IOB[5:0]   IOB00  IOB01  IOB02  IOB03  IOB04  IOB05
 * SPIFC      SIO3   SCLK   SIO0   CS     SIO1   SIO2
 * SPI0         -    SCLK_0 SI_0   CS_0   SO_0     -
 * WakeUp     YES    YES    YES    YES    YES    YES

 * =================================================================================
 * Note: GPCM1F064A (SRAM:13KB, ROM:64KB, 31 IOs)
 *       GPCM1F064B (SRAM:8KB,  ROM:64KB, 29 IOs, without IOA[23:22])
 */


/*---------------------------------------------------------------------------------------
 * Interrupt Number Definition
 *---------------------------------------------------------------------------------------*/
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers *************************************/
  NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt          */
  HardFault_IRQn                = -13,      /*!<  3 HardFault Interrupt             */
  SVCall_IRQn                   =  -5,      /*!< 11 SV Call Interrupt               */
  PendSV_IRQn                   =  -2,      /*!< 14 Pend SV Interrupt               */
  SysTick_IRQn                  =  -1,      /*!< 15 System Tick Interrupt           */

/******  GPCM1Fx Specific Interrupt Numbers *************************************/
  //Reserved 										= 0,       	/*!< Reserved                           */
  //Reserved 									  = 1,       	/*!< Reserved										        */
  DMA_IRQn 										  = 2,       	/*!< DMA Interrupt                      */
  MAC_IRQn 									    = 3,      	/*!< MAC Interrupt                      */
  QD_IRQn 									    = 4,      	/*!< PWMIO Interrupt                    */
  SAR_ADC_IRQn									= 5,      	/*!< SAR ADC Interrupt                  */
  DS_ADC_IRQn										= 6,      	/*!< Delta-sigma ADC Interrupt          */
  DAC_CH0_IRQn								 	= 7,     		/*!<                                    */
  DAC_CH1_IRQn 									= 8,     		/*!<                                    */
  CCP0_IRQn 										= 9,     		/*!< CCP0 Interrupt                     */
  CCP1_IRQn 										= 10,   		/*!< CCP1 Interrupt                     */
  CTS_TM0_IRQn						      = 11,   		/*!<                                    */
  CTS_TM1_IRQn						      = 12,   		/*!<                                    */
  TIMEBASE_IRQn						      = 13,     	/*!<                                    */
  I2C0_IRQn										  = 14,     	/*!< I2C0 Interrupt                     */
  //Reserved									  = 15,     	/*!< Reserved                           */
  UART0_IRQn 										= 16,    		/*!< UART0 Interrupt                    */
  //Reserved 										= 17,      	/*!< Reserved										        */
  I2S_IRQn 										  = 18,    		/*!< I2S Interrupt                      */
  SPI0_IRQn										  = 19,     	/*!< SPI0 Interrupt                     */
  SPI1_IRQn 									  = 20,     	/*!< SPI1 Interrupt                     */
  EXTI0_IRQn 										= 21,    		/*!< External Input 0 Interrupt         */
  EXTI1_IRQn 										= 22,    		/*!< External Input 1 Interrupt         */
  EXTI2_IRQn 										= 23,    		/*!< External Input 2 Interrupt         */
  EXTI3_IRQn 										= 24,  	  	/*!< External Input 3 Interrupt         */
  //Reserved						      	= 25, 			/*!< Reserved                           */
  TIMER0_IRQn									  = 26,  	 		/*!< Timer0 Interrupt                   */
  TIMER1_IRQn 								 	= 27,    		/*!< Timer1 Interrupt                   */
  TIMER2_IRQn 						  		= 28,    		/*!< Timer2 Interrupt                   */
  KEYCHG_IRQn 									= 29,  			/*!<                                    */
  //Reserved                		= 30,   		/*!<                                    */
  //Reserved  									= 31    		/*!<                                    */
} IRQn_Type;


/*---------------------------------------------------------------------------------------
 * Processor and Core Peripheral Section
 *---------------------------------------------------------------------------------------*/
#define __CM0_REV               0 				  /*!< Core Revision r0p0                            		*/
#define __MPU_PRESENT           0 				  /*!< do not provide MPU                  							*/
#define __NVIC_PRIO_BITS        2 				  /*!< 2 Bits for the Priority Levels 									*/
#define __Vendor_SysTickConfig  0 				  /*!< Set to 1 if different SysTick Config is used 		*/


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include <core_cm0.h>												// Cortex-M0 processor and core peripherals
#include <stdint.h>
#include <string.h>


/*---------------------------------------------------------------------------------------
 * SPI Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // SPI Control Register
	__IO uint32_t STS;                        // SPI Status Register
	__IO uint32_t TX_DATA;                    // SPI Transmit Data Register
	__IO uint32_t RX_DATA;                    // SPI Receive Data Register
} SPI_TYPE_DEF;

/*
 * Bit definition for SPI_CTRL[31] - Manual mode auto read/write enable
 */
#define SPI_CTRL_MASTER_RX_TRIG_POS         (31)
#define SPI_CTRL_MASTER_RX_TRIG_MSK         (0x1UL << SPI_CTRL_MASTER_RX_TRIG_POS)
#define SPI_CTRL_MASTER_RX_TRIG_ENABLE      (0x1UL << SPI_CTRL_MASTER_RX_TRIG_POS)
#define SPI_CTRL_MASTER_RX_TRIG_DISABLE		  (0x0UL << SPI_CTRL_MASTER_RX_TRIG_POS)

/*
 * Bit definition for SPI_CTRL[30] - Tx function disable
 */
#define SPI_CTRL_TX_DISABLE_POS             (30)
#define SPI_CTRL_TX_DISABLE_MSK             (0x1UL << SPI_CTRL_TX_DISABLE_POS)
#define SPI_CTRL_TX_DISABLE					        (0x1UL << SPI_CTRL_TX_DISABLE_POS)
#define SPI_CTRL_TX_ENABLE					        (0x0UL << SPI_CTRL_TX_DISABLE_POS)

/*
 * Bit definition for SPI_CTRL[23:20] - SPI clock selection
 */
#define SPI_CTRL_CLK_SEL_PCLK_DIV_POS				(20)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_MSK				(0xFUL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_1024      (0xBUL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_512       (0xAUL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_256				(0x9UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_128       (0x8UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_64       	(0x7UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_32       	(0x6UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_16        (0x5UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_10        (0x4UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_8        	(0x3UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_6         (0x2UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_4         (0x1UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)
#define SPI_CTRL_CLK_SEL_PCLK_DIV_2         (0x0UL << SPI_CTRL_CLK_SEL_PCLK_DIV_POS)

/*
 * Bit definition for SPI_CTRL[18] - Manual mode auto read/write enable
 */
#define SPI_CTRL_MAUT_RW_EN_POS             (18)
#define SPI_CTRL_MAUT_RW_EN_MSK             (0x1UL << SPI_CTRL_MAUT_RW_EN_POS)
#define SPI_CTRL_MAUT_RW_EN_ENABLE          (0x1UL << SPI_CTRL_MAUT_RW_EN_POS)
#define SPI_CTRL_MAUT_RW_EN_DISABLE         (0x0UL << SPI_CTRL_MAUT_RW_EN_POS)

/*
 * Bit definition for SPI_CTRL[17] - Rx DMA enable
 */
#define SPI_CTRL_RX_DMA_EN_POS              (17)
#define SPI_CTRL_RX_DMA_EN_MSK              (0x1UL << SPI_CTRL_RX_DMA_EN_POS)
#define SPI_CTRL_RX_DMA_ENABLE              (0x1UL << SPI_CTRL_RX_DMA_EN_POS)
#define SPI_CTRL_RX_DMA_DISABLE             (0x0UL << SPI_CTRL_RX_DMA_EN_POS)

/*
 * Bit definition for SPI_CTRL[16] - Tx DMA enable
 */
#define SPI_CTRL_TX_DMA_EN_POS              (16)
#define SPI_CTRL_TX_DMA_EN_MSK              (0x1UL << SPI_CTRL_TX_DMA_EN_POS)
#define SPI_CTRL_TX_DMA_ENABLE              (0x1UL << SPI_CTRL_TX_DMA_EN_POS)
#define SPI_CTRL_TX_DMA_DISABLE             (0x0UL << SPI_CTRL_TX_DMA_EN_POS)
/*
 * Bit definition for SPI_CTRL[15] - SPI CSB control by SW(Bit.11 CSB_GPIO) enable
 */
#define SPI_CTRL_CSB_SW_EN_POS              (15)
#define SPI_CTRL_CSB_SW_EN_MSK              (0x1UL << SPI_CTRL_CSB_SW_EN_POS)
#define SPI_CTRL_CSB_SW_ENABLE							(0x1UL << SPI_CTRL_CSB_SW_EN_POS)
#define SPI_CTRL_CSB_SW_DISABLE							(0x0UL << SPI_CTRL_CSB_SW_EN_POS)

/*
 * Bit definition for SPI_CTRL[11] - SPI CSB control bit
 */
#define SPI_CTRL_CSB_GPIO_POS             	(11)
#define SPI_CTRL_CSB_GPIO_MSK              	(0x1UL << SPI_CTRL_CSB_GPIO_POS)
#define SPI_CTRL_CSB_GPIO_HIGH							(0x1UL << SPI_CTRL_CSB_GPIO_POS)
#define SPI_CTRL_CSB_GPIO_LOW								(0x0UL << SPI_CTRL_CSB_GPIO_POS)

/*
 * Bit definition for SPI_CTRL[10] - Error interrupt enable
 */
#define SPI_CTRL_ERR_INT_EN_POS             (10)
#define SPI_CTRL_ERR_INT_EN_MSK             (0x1UL << SPI_CTRL_ERR_INT_EN_POS)
#define SPI_CTRL_ERR_INT_ENABLE             (0x1UL << SPI_CTRL_ERR_INT_EN_POS)
#define SPI_CTRL_ERR_INT_DISABLE            (0x0UL << SPI_CTRL_ERR_INT_EN_POS)

/*
 * Bit definition for SPI_CTRL[9] - SPI Received complete interrupt enable
 */
#define SPI_CTRL_RX_INT_EN_POS              (9)
#define SPI_CTRL_RX_INT_EN_MSK              (0x1UL << SPI_CTRL_RX_INT_EN_POS)
#define SPI_CTRL_RX_INT_ENABLE              (0x1UL << SPI_CTRL_RX_INT_EN_POS)
#define SPI_CTRL_RX_INT_DISABLE             (0x0UL << SPI_CTRL_RX_INT_EN_POS)

/*
 * Bit definition for SPI_CTRL[8] - SPI transmitted complete interrupt enable
 */
#define SPI_CTRL_TX_INT_EN_POS              (8)
#define SPI_CTRL_TX_INT_EN_MSK              (0x1UL << SPI_CTRL_TX_INT_EN_POS)
#define SPI_CTRL_TX_INT_ENABLE              (0x1UL << SPI_CTRL_TX_INT_EN_POS)
#define SPI_CTRL_TX_INT_DISABLE             (0x0UL << SPI_CTRL_TX_INT_EN_POS)

/*
 * Bit definition for SPI_CTRL[5] - SPI loop-back enable
 */
#define SPI_CTRL_LOOPBACK_EN_POS            (5)
#define SPI_CTRL_LOOPBACK_EN_MSK            (0x1UL << SPI_CTRL_LOOPBACK_EN_POS)
#define SPI_CTRL_LOOPBACK_ENABLE            (0x1UL << SPI_CTRL_LOOPBACK_EN_POS)
#define SPI_CTRL_LOOPBACK_DISABLE           (0x0UL << SPI_CTRL_LOOPBACK_EN_POS)

/*
 * Bit definition for SPI_CTRL[4] - SPI clock polarity
 */
#define SPI_CTRL_CLK_POL_POS                (4)
#define SPI_CTRL_CLK_POL_MSK                (0x1UL << SPI_CTRL_CLK_POL_POS)
#define SPI_CTRL_CLK_POL1                   (0x1UL << SPI_CTRL_CLK_POL_POS)
#define SPI_CTRL_CLK_POL0                   (0x0UL << SPI_CTRL_CLK_POL_POS)

/*
 * Bit definition for SPI_CTRL[3] - SPI clock phase
 */
#define SPI_CTRL_CLK_PHA_POS                (3)
#define SPI_CTRL_CLK_PHA_MSK                (0x1UL << SPI_CTRL_CLK_PHA_POS)
#define SPI_CTRL_CLK_PHA_SHIFT              (0x1UL << SPI_CTRL_CLK_PHA_POS)
#define SPI_CTRL_CLK_PHA_NORMAL             (0x0UL << SPI_CTRL_CLK_PHA_POS)

/*
 * Bit definition for SPI_CTRL[2] - SPI CSB keeping low control
 */
#define SPI_CTRL_CSB_KEEPL_POS              (2)
#define SPI_CTRL_CSB_KEEPL_MSK              (0x1UL << SPI_CTRL_CSB_KEEPL_POS)
#define SPI_CTRL_CSB_KEEPL_ENABLE					  (0x1UL << SPI_CTRL_CSB_KEEPL_POS)
#define SPI_CTRL_CSB_KEEPL_DISABLE					(0x0UL << SPI_CTRL_CSB_KEEPL_POS)

/*
 * Bit definition for SPI_CTRL[1] - SPI operating mode select
 */
#define SPI_CTRL_MODE_SEL_POS               (1)
#define SPI_CTRL_MODE_SEL_MSK               (0x1UL << SPI_CTRL_MODE_SEL_POS)
#define SPI_CTRL_SLAVE_MODE                 (0x1UL << SPI_CTRL_MODE_SEL_POS)
#define SPI_CTRL_MASTER_MODE                (0x0UL << SPI_CTRL_MODE_SEL_POS)

/*
 * Bit definition for SPI_CTRL[0] - SPI enable
 */
#define SPI_CTRL_SPI_EN_POS                 (0)
#define SPI_CTRL_SPI_EN_MSK                 (0x1UL << SPI_CTRL_SPI_EN_POS)
#define SPI_CTRL_SPI_ENABLE                 (0x1UL << SPI_CTRL_SPI_EN_POS)
#define SPI_CTRL_SPI_DISABLE                (0x0UL << SPI_CTRL_SPI_EN_POS)

/*
 * Bit definition for SPI_STS[4] - Receive buffer not empty
 */
#define SPI_CTRL_RX_BUF_NEMPTY_FLAG_POS     (4)
#define SPI_CTRL_RX_BUF_NEMPTY_FLAG_MSK     (0x1UL << SPI_CTRL_RX_BUF_NEMPTY_FLAG_POS)
#define SPI_CTRL_RX_BUF_NEMPTY_FLAG         (0x1UL << SPI_CTRL_RX_BUF_NEMPTY_FLAG_POS)

/*
 * Bit definition for SPI_STS[3] - SPI received over run
 */
#define SPI_CTRL_RX_OVER_RUN_FLAG_POS       (3)
#define SPI_CTRL_RX_OVER_RUN_FLAG_MSK       (0x1UL << SPI_CTRL_RX_OVER_RUN_FLAG_POS)
#define SPI_CTRL_RX_OVER_RUN_FLAG           (0x1UL << SPI_CTRL_RX_OVER_RUN_FLAG_POS)

/*
 * Bit definition for SPI_STS[2] - SPI receive complete flag
 */
#define SPI_CTRL_RX_DONE_FLAG_POS           (2)
#define SPI_CTRL_RX_DONE_FLAG_MSK           (0x1UL << SPI_CTRL_RX_DONE_FLAG_POS)
#define SPI_CTRL_RX_DONE_FLAG               (0x1UL << SPI_CTRL_RX_DONE_FLAG_POS)

/*
 * Bit definition for SPI_STS[0] - SPI transmission complete flag
 */
#define SPI_CTRL_TX_DONE_FLAG_POS           (0)
#define SPI_CTRL_TX_DONE_FLAG_MSK           (0x1UL << SPI_CTRL_TX_DONE_FLAG_POS)
#define SPI_CTRL_TX_DONE_FLAG               (0x1UL << SPI_CTRL_TX_DONE_FLAG_POS)


/*---------------------------------------------------------------------------------------
 * UART Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
 typedef struct
{
	__IO uint32_t CTRL;							          // UART Control Register
	__IO uint32_t STS;							          // UART Status Register
	__IO uint32_t BAUD_RATE;				          // UART Baud Rate Register
	__IO uint32_t DATA;							          // UART Data Shadow Register
} UART_TYPE_DEF;

/*
 * Bit definition for UART_CTRL[21] - Rx buffer DMA enable
 */
#define UART_CTRL_RX_DMAE_POS               (21)
#define UART_CTRL_RX_DMAE_MSK               (0x1UL << UART_CTRL_RX_DMAE_POS)
#define UART_CTRL_RX_DMA_ENABLE							(0x1UL << UART_CTRL_RX_DMAE_POS)
#define UART_CTRL_RX_DMA_DISABLE						(0x0UL << UART_CTRL_RX_DMAE_POS)

/*
 * Bit definition for UART_CTRL[20] - Tx buffer DMA enable
 */
#define UART_CTRL_TX_DMAE_POS               (20)
#define UART_CTRL_TX_DMAE_MSK               (0x1UL << UART_CTRL_TX_DMAE_POS)
#define UART_CTRL_TX_DMA_ENABLE							(0x1UL << UART_CTRL_TX_DMAE_POS)
#define UART_CTRL_TX_DMA_DISABLE						(0x0UL << UART_CTRL_TX_DMAE_POS)

/*
 * Bit definition for UART_CTRL[19] - UART loop-back enable
 */
#define UART_CTRL_LOOPBACK_EN_POS           (19)
#define UART_CTRL_LOOPBACK_EN_MSK           (0x1UL << UART_CTRL_LOOPBACK_EN_POS)
#define UART_CTRL_LOOPBACK_ENABLE						(0x1UL << UART_CTRL_LOOPBACK_EN_POS)
#define UART_CTRL_LOOPBACK_DISABLE          (0x0UL << UART_CTRL_LOOPBACK_EN_POS)

/*
 * Bit definition for UART_CTRL[18] - STOP bits select
 */
#define UART_CTRL_STOP_SEL_POS              (18)
#define UART_CTRL_STOP_SEL_MSK              (0x1UL << UART_CTRL_STOP_SEL_POS)
#define UART_CTRL_STOP_SEL_2BIT             (0x1UL << UART_CTRL_STOP_SEL_POS)
#define UART_CTRL_STOP_SEL_1BIT             (0x0UL << UART_CTRL_STOP_SEL_POS)

/*
 * Bit definition for UART_CTRL[17] - UART send idle enable
 */
#define UART_CTRL_SEND_IDLE_POS             (17)
#define UART_CTRL_SEND_IDLE_MSK             (0x1UL << UART_CTRL_SEND_IDLE_POS)
#define UART_CTRL_SEND_IDLE_ENABLE					(0x1UL << UART_CTRL_SEND_IDLE_POS)
#define UART_CTRL_SEND_IDLE_DISABLE         (0x0UL << UART_CTRL_SEND_IDLE_POS)

/*
 * Bit definition for UART_CTRL[15] - UART received break interrupt enable
 */
#define UART_CTRL_RX_BRK_INT_EN_POS         (15)
#define UART_CTRL_RX_BRK_INT_EN_MSK         (0x1UL << UART_CTRL_RX_BRK_INT_EN_POS)
#define UART_CTRL_RX_BRK_INT_ENABLE         (0x1UL << UART_CTRL_RX_BRK_INT_EN_POS)
#define UART_CTRL_RX_BRK_INT_DISABLE        (0x0UL << UART_CTRL_RX_BRK_INT_EN_POS)

/*
 * Bit definition for UART_CTRL[14] - UART detected idle interrupt enable
 */
#define UART_CTRL_RX_IDLE_INT_EN_POS        (14)
#define UART_CTRL_RX_IDLE_INT_EN_MSK        (0x1UL << UART_CTRL_RX_IDLE_INT_EN_POS)
#define UART_CTRL_RX_IDLE_INT_ENABLE        (0x1UL << UART_CTRL_RX_IDLE_INT_EN_POS)
#define UART_CTRL_RX_IDLE_INT_DISABLE       (0x0UL << UART_CTRL_RX_IDLE_INT_EN_POS)

/*
 * Bit definition for UART_CTRL[13] - UART received a word interrupt enable
 */
#define UART_CTRL_RX_INT_EN_POS             (13)
#define UART_CTRL_RX_INT_EN_MSK             (0x1UL << UART_CTRL_RX_INT_EN_POS)
#define UART_CTRL_RX_INT_ENABLE							(0x1UL << UART_CTRL_RX_INT_EN_POS)
#define UART_CTRL_RX_INT_DISABLE						(0x0UL << UART_CTRL_RX_INT_EN_POS)

/*
 * Bit definition for UART_CTRL[12] - UART transmission done interrupt enable
 */
#define UART_CTRL_TX_INT_EN_POS             (12)
#define UART_CTRL_TX_INT_EN_MSK             (0x1UL << UART_CTRL_TX_INT_EN_POS)
#define UART_CTRL_TX_INT_ENABLE							(0x1UL << UART_CTRL_TX_INT_EN_POS)
#define UART_CTRL_TX_INT_DISABLE						(0x0UL << UART_CTRL_TX_INT_EN_POS)

/*
 * Bit definition for UART_CTRL[11] - Parity selection
 */
#define UART_CTRL_PRITY_SEL_POS             (11)
#define UART_CTRL_PRITY_SEL_MSK             (0x1UL << UART_CTRL_PRITY_SEL_POS)
#define UART_CTRL_PRITY_SEL_ODD             (0x1UL << UART_CTRL_PRITY_SEL_POS)
#define UART_CTRL_PRITY_SEL_EVEN            (0x0UL << UART_CTRL_PRITY_SEL_POS)

/*
 * Bit definition for UART_CTRL[10] - Parity check enable
 */
#define UART_CTRL_PARITY_CHK_EN_POS         (10)
#define UART_CTRL_PARITY_CHK_EN_MSK         (0x1UL << UART_CTRL_PARITY_CHK_EN_POS)
#define UART_CTRL_PARITY_CHECK_ENABLE				(0x1UL << UART_CTRL_PARITY_CHK_EN_POS)
#define UART_CTRL_PARITY_CHECK_DISABLE      (0x0UL << UART_CTRL_PARITY_CHK_EN_POS)

/*
 * Bit definition for UART_CTRL[9] - Parity bit enable
 */
#define UART_CTRL_WORD_LEN_POS              (9)
#define UART_CTRL_WORD_LEN_MSK              (0x1UL << UART_CTRL_WORD_LEN_POS)
#define UART_CTRL_PARITY_BIT_ENABLE         (0x1UL << UART_CTRL_WORD_LEN_POS)
#define UART_CTRL_PARITY_BIT_DISABLE	      (0x0UL << UART_CTRL_WORD_LEN_POS)

/*
 * Bit definition for UART_CTRL[8] - UART enable
 */
#define UART_CTRL_UART_EN_POS               (8)
#define UART_CTRL_UART_EN_MSK               (0x1UL << UART_CTRL_UART_EN_POS)
#define UART_CTRL_UART_ENABLE								(0x1UL << UART_CTRL_UART_EN_POS)
#define UART_CTRL_UART_DISABLE  						(0x0UL << UART_CTRL_UART_EN_POS)

/*
 * Bit definition for UART_CTRL[1] - UART receiver enable
 */
#define UART_CTRL_UART_RX_EN_POS            (1)
#define UART_CTRL_UART_RX_EN_MSK            (0x1UL << UART_CTRL_UART_RX_EN_POS)
#define UART_CTRL_UART_RX_ENABLE            (0x1UL << UART_CTRL_UART_RX_EN_POS)
#define UART_CTRL_UART_RX_DISABLE           (0x0UL << UART_CTRL_UART_RX_EN_POS)

/*
 * Bit definition for UART_CTRL[0] - UART transmitter enable
 */
#define UART_CTRL_UART_TX_EN_POS            (0)
#define UART_CTRL_UART_TX_EN_MSK            (0x1UL << UART_CTRL_UART_TX_EN_POS)
#define UART_CTRL_UART_TX_ENABLE            (0x1UL << UART_CTRL_UART_TX_EN_POS)
#define UART_CTRL_UART_TX_DISABLE           (0x0UL << UART_CTRL_UART_TX_EN_POS)

/*
 * Bit definition for UART_STS[15] - UART receiver break detected flag
 */
#define UART_STS_RX_BRK_POS                 (15)
#define UART_STS_RX_BRK_MSK                 (0x1UL << UART_STS_RX_BRK_POS)
#define UART_STS_RX_BRK_FLAG                (0x1UL << UART_STS_RX_BRK_POS)

/*
 * Bit definition for UART_STS[14] - UART Rx idle detected flag
 */
#define UART_STS_RX_IDLE_POS                (14)
#define UART_STS_RX_IDLE_MSK                (0x1UL << UART_STS_RX_IDLE_POS)
#define UART_STS_RX_IDLE_FLAG               (0x1UL << UART_STS_RX_IDLE_POS)

/*
 * Bit definition for UART_STS[13] - UART read data register not empty flag
 */
#define UART_STS_RX_DAT_NEMP_POS            (13)
#define UART_STS_RX_DAT_NEMP_MSK            (0x1UL << UART_STS_RX_DAT_NEMP_POS)
#define UART_STS_RX_DAT_NEMP_FLAG           (0x1UL << UART_STS_RX_DAT_NEMP_POS)

/*
 * Bit definition for UART_STS[12] - UART transmission complete flag
 */
#define UART_STS_TX_DONE_POS                (12)
#define UART_STS_TX_DONE_MSK                (0x1UL << UART_STS_TX_DONE_POS)
#define UART_STS_TX_DONE_FLAG               (0x1UL << UART_STS_TX_DONE_POS)

/*
 * Bit definition for UART_STS[8] - UART receiver stop bit error flag
 */
#define UART_STS_RX_STP_ERR_POS             (8)
#define UART_STS_RX_STP_ERR_MSK             (0x1UL << UART_STS_RX_STP_ERR_POS)
#define UART_STS_RX_STP_ERR_FLAG            (0x1UL << UART_STS_RX_STP_ERR_POS)

/*
 * Bit definition for UART_STS[7] - UART receiver parity error flag
 */
#define UART_STS_RX_PARITY_ERR_POS          (7)
#define UART_STS_RX_PARITY_ERR_MSK          (0x1UL << UART_STS_RX_PARITY_ERR_POS)
#define UART_STS_RX_PARITY_ERR_FLAG         (0x1UL << UART_STS_RX_PARITY_ERR_POS)

/*
 * Bit definition for UART_STS[6] - UART receiver parity bit
 */
#define UART_STS_RX_PRITY_POS               (6)
#define UART_STS_RX_PRITY_MSK               (0x1UL << UART_STS_RX_PRITY_POS)
#define UART_STS_RX_PRITY_BIT               (0x1UL << UART_STS_RX_PRITY_POS)

/*
 * Bit definition for UART_STS[5] - UART over run error flag
 */
#define UART_STS_RX_OV_RUN_POS              (5)
#define UART_STS_RX_OV_RUN_MSK              (0x1UL << UART_STS_RX_OV_RUN_POS)
#define UART_STS_RX_OV_RUN_FLAG             (0x1UL << UART_STS_RX_OV_RUN_POS)

/*
 * Bit definition for UART_STS[1] - UART transmit data register empty flag
 */
#define UART_STS_TX_DAT_EMP_POS             (1)
#define UART_STS_TX_DAT_EMP_MSK             (0x1UL << UART_STS_TX_DAT_EMP_POS)
#define UART_STS_TX_DAT_EMP_FLAG            (0x1UL << UART_STS_TX_DAT_EMP_POS)

/*
 * Bit definition for UART_BAUD_RATE[20] - Baud rate compensate selection
 */
#define UART_BAUD_RATE_BR_CMP_SEL_POS       (20)
#define UART_BAUD_RATE_BR_CMP_SEL_MSK       (0x1UL << UART_BAUD_RATE_BR_CMP_SEL_POS)
#define UART_BAUD_RATE_BR_CMP_SEL_SUB       (0x1UL << UART_BAUD_RATE_BR_CMP_SEL_POS)
#define	UART_BAUD_RATE_BR_CMP_SEL_ADD       (0x0UL << UART_BAUD_RATE_BR_CMP_SEL_POS)

/*
 * Bit definition for UART_BAUD_RATE[19:16] - Baud rate compensate cycles
 */
#define UART_BAUD_RATE_BR_CMP_CYCLE_POS     (16)
#define UART_BAUD_RATE_BR_CMP_CYCLE_MSK     (0xFUL << UART_BAUD_RATE_BR_CMP_CYCLE_POS)

/*
 * Bit definition for UART_BAUD_RATE[11:0] - Baud rate divider
 */
#define UART_BAUD_RATE_BR_DIV_POS           (0)
#define UART_BAUD_RATE_BR_DIV_MSK           (0xFFFUL << UART_BAUD_RATE_BR_DIV_POS)


/*---------------------------------------------------------------------------------------
 * I2C Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // I2C Control Register
	__IO uint32_t STS;                        // I2C Status Register
	__IO uint32_t ADDR;                       // I2C Address Register
	__IO uint32_t DATA;                       // I2C Data Register
} I2C_TYPE_DEF;

/*
 * Bit definition for I2C_CTRL[26] - I2C Rx mode DMA enable
 */
#define I2C_CTRL_RX_DMA_EN_POS              (26)
#define I2C_CTRL_RX_DMA_EN_MSK              (0x1UL << I2C_CTRL_RX_DMA_EN_POS)
#define I2C_CTRL_RX_DMA_ENABLE              (0x1UL << I2C_CTRL_RX_DMA_EN_POS)
#define I2C_CTRL_RX_DMA_DISABLE             (0x0UL << I2C_CTRL_RX_DMA_EN_POS)

/*
 * Bit definition for I2C_CTRL[25] - I2C Tx mode DMA enable
 */
#define I2C_CTRL_TX_DMA_EN_POS              (25)
#define I2C_CTRL_TX_DMA_EN_MSK              (0x1UL << I2C_CTRL_TX_DMA_EN_POS)
#define I2C_CTRL_TX_DMA_ENABLE              (0x1UL << I2C_CTRL_TX_DMA_EN_POS)
#define I2C_CTRL_TX_DMA_DISABLE             (0x0UL << I2C_CTRL_TX_DMA_EN_POS)

/*
 * Bit definition for I2C_CTRL[24] - I2C controller operating mode select
 */
#define I2C_CTRL_MODE_SEL_POS               (24)
#define I2C_CTRL_MODE_SEL_MSK               (0x1UL << I2C_CTRL_MODE_SEL_POS)
#define I2C_CTRL_MODE_SEL_MASTER            (0x1UL << I2C_CTRL_MODE_SEL_POS)
#define I2C_CTRL_MODE_SEL_SLAVE             (0x0UL << I2C_CTRL_MODE_SEL_POS)

/*
 * Bit definition for I2C_CTRL[23] - Slave address error interrupt enable
 */
#define I2C_CTRL_ERR_SADR_INT_EN_POS        (23)
#define I2C_CTRL_ERR_SADR_INT_EN_MSK        (0x1UL << I2C_CTRL_ERR_SADR_INT_EN_POS)
#define I2C_CTRL_ERR_SADR_INT_ENABLE        (0x1UL << I2C_CTRL_ERR_SADR_INT_EN_POS)
#define I2C_CTRL_ERR_SADR_INT_DISABLE       (0x0UL << I2C_CTRL_ERR_SADR_INT_EN_POS)

/*
 * Bit definition for I2C_CTRL[22] - I2C interrupt enable
 */
#define I2C_CTRL_I2C_INT_EN_POS             (22)
#define I2C_CTRL_I2C_INT_EN_MSK             (0x1UL << I2C_CTRL_I2C_INT_EN_POS)
#define I2C_CTRL_I2C_INT_ENABLE             (0x1UL << I2C_CTRL_I2C_INT_EN_POS)
#define I2C_CTRL_I2C_INT_DISABLE            (0x0UL << I2C_CTRL_I2C_INT_EN_POS)

/*
 * Bit definition for I2C_CTRL[21:16] - SCL / SDA input de-bounce time
 */
#define I2C_CTRL_DB_TIME_POS                (16)
#define I2C_CTRL_DB_TIME_MSK                (0x3FUL << I2C_CTRL_MST_STR_POS)

/*
 * Bit definition for I2C_CTRL[15] - I2C controller issued start command enable
 */
#define I2C_CTRL_MST_STR_POS                (15)
#define I2C_CTRL_MST_STR_MSK                (0x1UL << I2C_CTRL_MST_STR_POS)
#define I2C_CTRL_MST_STR                    (0x1UL << I2C_CTRL_MST_STR_POS)

/*
 * Bit definition for I2C_CTRL[14] - I2C controller issued stop command enable
 */
#define I2C_CTRL_MST_STP_POS                (14)
#define I2C_CTRL_MST_STP_MSK                (0x1UL << I2C_CTRL_MST_STP_POS)
#define I2C_CTRL_MST_STP                    (0x1UL << I2C_CTRL_MST_STP_POS)

/*
 * Bit definition for I2C_CTRL[13] - I2C controller issued non-acknowledge
 */
#define I2C_CTRL_MST_NACK_POS               (13)
#define I2C_CTRL_MST_NACK_MSK               (0x1UL << I2C_CTRL_MST_NACK_POS)
#define I2C_CTRL_MST_NACK                   (0x1UL << I2C_CTRL_MST_NACK_POS)

/*
 * Bit definition for I2C_CTRL[11:9] - I2C controller serial clock select
 */
#define I2C_CTRL_CLK_SEL_POS                (9)
#define I2C_CTRL_CLK_SEL_MSK                (0x7UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_1024      (0x6UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_768       (0x5UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_256       (0x4UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_128       (0x3UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_64        (0x2UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_32        (0x1UL << I2C_CTRL_CLK_SEL_POS)
#define I2C_CTRL_CLK_SEL_HCLK_DIV_16        (0x0UL << I2C_CTRL_CLK_SEL_POS)

/*
 * Bit definition for I2C_CTRL[8] - I2C controller enable bit
 */
#define I2C_CTRL_I2C_EN_POS                 (8)
#define I2C_CTRL_I2C_EN_MSK                 (0x1UL << I2C_CTRL_I2C_EN_POS)
#define I2C_CTRL_I2C_ENABLE                 (0x1UL << I2C_CTRL_I2C_EN_POS)
#define I2C_CTRL_I2C_DISABLE                (0x0UL << I2C_CTRL_I2C_EN_POS)

/*
 * Bit definition for I2C_CTRL[0] - I2C start transmission trigger bit
 */
#define I2C_CTRL_I2C_STR_POS                (0)
#define I2C_CTRL_I2C_STR_MSK                (0x1UL << I2C_CTRL_I2C_STR_POS)
#define I2C_CTRL_I2C_START                  (0x1UL << I2C_CTRL_I2C_STR_POS)

/*
 * Bit definition for I2C_CTRL[0] - I2C start transmission trigger bit
 */
#define I2C_CTRL_I2C_TRG_POS                (0)
#define I2C_CTRL_I2C_TRG_MSK                (0x1UL << I2C_CTRL_I2C_TRG_POS)
#define I2C_CTRL_I2C_TRIGGER                (0x1UL << I2C_CTRL_I2C_TRG_POS)

/*
 * Bit definition for I2C_STS[11] - I2C Slave address error flag
 */
#define I2C_STS_SLV_ADR_ERR_POS             (11)
#define I2C_STS_SLV_ADR_ERR_MSK             (0x1UL << I2C_STS_SLV_ADR_ERR_POS)
#define I2C_STS_SLV_ADR_ERR_FLAG            (0x1UL << I2C_STS_SLV_ADR_ERR_POS)

/*
 * Bit definition for I2C_STS[10] - I2C controller busy flag
 */
#define I2C_STS_BUSY_POS                    (10)
#define I2C_STS_BUSY_MSK                    (0x1UL << I2C_STS_BUSY_POS)
#define I2C_STS_BUSY_FLAG                   (0x1UL << I2C_STS_BUSY_POS)

/*
 * Bit definition for I2C_STS[9] - I2C general call flag
 */
#define I2C_STS_GEN_CALL_POS                (9)
#define I2C_STS_GEN_CALL_MSK                (0x1UL << I2C_STS_GEN_CALL_POS)
#define I2C_STS_GEN_CALL_FLAG               (0x1UL << I2C_STS_GEN_CALL_POS)

/*
 * Bit definition for I2C_STS[6] - I2C bus arbitration lost flag
 */
#define I2C_STS_ARB_LOST_POS                (6)
#define I2C_STS_ARB_LOST_MSK                (0x1UL << I2C_STS_ARB_LOST_POS)
#define I2C_STS_ARB_LOST_FLAG               (0x1UL << I2C_STS_ARB_LOST_POS)

/*
 * Bit definition for I2C_STS[4] - I2C Slave address received flag
 */
#define I2C_STS_SLV_DATA_DONE_POS           (4)
#define I2C_STS_SLV_DATA_DONE_MSK           (0x1UL << I2C_STS_SLV_DATA_DONE_POS)
#define I2C_STS_SLV_DATA_DONE_FLAG          (0x1UL << I2C_STS_SLV_DATA_DONE_POS)

/*
 * Bit definition for I2C_STS[3] - I2C Tx/Rx Data Done flag
 */
#define I2C_STS_DATA_DONE_POS               (3)
#define I2C_STS_DATA_DONE_MSK               (0x1UL << I2C_STS_DATA_DONE_POS)
#define I2C_STS_DATA_DONE_FLAG              (0x1UL << I2C_STS_DATA_DONE_POS)

/*
 * Bit definition for I2C_STS[2] - I2C Stop command received flag
 */
#define I2C_STS_RX_STOP_CMD_POS             (2)
#define I2C_STS_RX_STOP_CMD_MSK             (0x1UL << I2C_STS_RX_STOP_CMD_POS)
#define I2C_STS_RX_STOP_CMD_FLAG            (0x1UL << I2C_STS_RX_STOP_CMD_POS)

/*
 * Bit definition for I2C_STS[1] - I2C No Ack received flag
 */
#define I2C_STS_RX_NO_ACK_POS               (1)
#define I2C_STS_RX_NO_ACK_MSK               (0x1UL << I2C_STS_RX_NO_ACK_POS)
#define I2C_STS_RX_NO_ACK_FLAG              (0x1UL << I2C_STS_RX_NO_ACK_POS)

/*
 * Bit definition for I2C_STS[0] - I2C transmission complete flag
 */
#define I2C_STS_TRS_DONE_POS                (0)
#define I2C_STS_TRS_DONE_MSK                (0x1UL << I2C_STS_TRS_DONE_POS)
#define I2C_STS_TRS_DONE_FLAG               (0x1UL << I2C_STS_TRS_DONE_POS)

/*
 * Bit definition for I2C_ADDR[16] - I2C address mode control bit
 */
#define I2C_ADDR_MODE_POS                   (16)
#define I2C_ADDR_MODE_10BIT                 (0x1UL << I2C_ADDR_MODE_POS)
#define I2C_ADDR_MODE_7BIT                  (0x0UL << I2C_ADDR_MODE_POS)

/*
 * Bit definition for I2C_ADDR[15:1] - I2C slave address
 */
#define I2C_ADDR_ADDRESS                    (1)
#define I2C_ADDR_ADDRESS_MSK                (0x7FUL << I2C_ADDR_MODE_POS)

/*
 * Bit definition for I2C_ADDR[0] - I2C read/write control bit
 */
#define I2C_RW_SEL_POS                      (0)
#define I2C_RW_SEL_MSK                      (0x1UL << I2C_RW_SEL_POS)
#define I2C_RW_SEL_READ                     (0x1UL << I2C_RW_SEL_POS)
#define I2C_RW_SEL_WRITE                    (0x0UL << I2C_RW_SEL_POS)


/*---------------------------------------------------------------------------------------
 * I2S Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // I2S Control Register
	__IO uint32_t DATA;                       // I2S Receive Data Register
	__IO uint32_t STS;                        // I2S Status Register
	__IO uint32_t CTRL2;                      // I2S RX Control2 Register	c
} I2S_TYPE_DEF;

/*
 * Bit definition for I2S_CTRL[21] - Mono Mode Enable
 */
#define I2S_CTRL_MONO_MODE_POS              (21)
#define I2S_CTRL_MONO_MODE_MSK              (0x1UL << I2S_CTRL_MONO_MODE_POS)
#define I2S_CTRL_MONO_MODE_ENABLE           (0x1UL << I2S_CTRL_MONO_MODE_POS)
#define I2S_CTRL_MONO_MODE_DISABLE          (0x0UL << I2S_CTRL_MONO_MODE_POS)

/*
 * Bit definition for I2S_CTRL[20] - Right Channel At LSB
 */
#define I2S_CTRL_RIGHT_LSB_POS              (20)
#define I2S_CTRL_RIGHT_LSB_MSK              (0x1UL << I2S_CTRL_RIGHT_LSB_POS)
#define I2S_CTRL_RIGHT_LSB_ENABLE           (0x1UL << I2S_CTRL_RIGHT_LSB_POS)
#define I2S_CTRL_RIGHT_LSB_DISABLE          (0x0UL << I2S_CTRL_RIGHT_LSB_POS)

/*
 * Bit definition for I2S_CTRL[19] - MERGE
 */
#define I2S_CTRL_MERGE_POS              		(19)
#define I2S_CTRL_MERGE_MSK              		(0x1UL << I2S_CTRL_MERGE_POS)
#define I2S_CTRL_MERGE_ENABLE              	(0x1UL << I2S_CTRL_MERGE_POS)
#define I2S_CTRL_MERGE_DISABLE             	(0x0UL << I2S_CTRL_MERGE_POS)

/*
 * Bit definition for I2S_CTRL[16] - Enable Half Full Interrupt
 */
#define I2S_CTRL_HALF_FULL_INT_POS        	(16)
#define I2S_CTRL_HALF_FULL_INT_MSK          (0x1UL << I2S_CTRL_HALF_FULL_INT_POS)
#define I2S_CTRL_HALF_FULL_INT_ENABLE       (0x1UL << I2S_CTRL_HALF_FULL_INT_POS)
#define I2S_CTRL_HALF_FULL_INT_DISABLE      (0x0UL << I2S_CTRL_HALF_FULL_INT_POS)

/*
 * Bit definition for I2S_CTRL[14] - INT Rising or Falling edge triggered.
 */
#define I2S_CTRL_INT_SEL_POS            	  (14)
#define I2S_CTRL_INT_SEL_MSK            	  (0x1UL << I2S_CTRL_INT_SEL_POS)
#define I2S_CTRL_INT_SEL_RISE							  (0x1UL << I2S_CTRL_INT_SEL_POS)
#define I2S_CTRL_INT_SEL_FALL							  (0x0UL << I2S_CTRL_INT_SEL_POS)

/*
 * Bit definition for I2S_CTRL[13] - Master Mode
 */
#define I2S_CTRL_MODE_SEL_POS            	  (13)
#define I2S_CTRL_MODE_SEL_MSK            	  (0x1UL << I2S_CTRL_MODE_SEL_POS)
#define I2S_CTRL_MODE_SEL_MASTER					  (0x1UL << I2S_CTRL_MODE_SEL_POS)
#define I2S_CTRL_MODE_SEL_SLAVE						  (0x0UL << I2S_CTRL_MODE_SEL_POS)

/*
* Bit definition for I2S_CTRL[12:11] - Framing Mode
 */
#define I2S_CTRL_FRAMING_MODE_SEL_POS      	(11)
#define I2S_CTRL_FRAMING_MODE_SEL_MSK       (0x3UL << I2S_CTRL_FRAMING_MODE_SEL_POS)
#define I2S_CTRL_FRAMING_MODE_SEL_NORMAL		(0x1UL << I2S_CTRL_FRAMING_MODE_SEL_POS)	//01
#define I2S_CTRL_FRAMING_MODE_SEL_I2S				(0x0UL << I2S_CTRL_FRAMING_MODE_SEL_POS)	//00

/*
* Bit definition for I2S_CTRL[10:9] - Frame size
 */
#define I2S_CTRL_FRAME_SIZE_SEL_POS      		(9)
#define I2S_CTRL_FRAME_SIZE_SEL_MSK       	(0x3UL << I2S_CTRL_FRAME_SIZE_SEL_POS)
#define I2S_CTRL_FRAME_SIZE_SEL_Slave     	(0x3UL << I2S_CTRL_FRAME_SIZE_SEL_POS)	// 11
#define I2S_CTRL_FRAME_SIZE_SEL_32BITS    	(0x2UL << I2S_CTRL_FRAME_SIZE_SEL_POS)	// 10
#define I2S_CTRL_FRAME_SIZE_SEL_24BITS			(0x1UL << I2S_CTRL_FRAME_SIZE_SEL_POS)	// 01
#define I2S_CTRL_FRAME_SIZE_SEL_16BITS			(0x0UL << I2S_CTRL_FRAME_SIZE_SEL_POS)	// 00

/*
 * Bit definition for I2S_CTRL[8:6] - Valid Data Length
 */
#define I2S_CTRL_DATA_LENGTH_SEL_POS        (6)
#define I2S_CTRL_DATA_LENGTH_SEL_MSK        (0x7UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_32BITS			(0x5UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_24BITS			(0x4UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_22BITS			(0x3UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_20BITS			(0x2UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_18BITS			(0x1UL << I2S_CTRL_DATA_LENGTH_SEL_POS)
#define I2S_CTRL_DATA_LENGTH_SEL_16BITS			(0x0UL << I2S_CTRL_DATA_LENGTH_SEL_POS)

/*
 * Bit definition for I2S_CTRL[5] - Received Data Left Alignment,
 */
#define I2S_CTRL_ALIGN_SEL_POS            	(5)
#define I2S_CTRL_ALIGN_SEL_MSK            	(0x1UL << I2S_CTRL_ALIGN_SEL_POS)
#define I2S_CTRL_ALIGN_SEL_LEFT							(0x1UL << I2S_CTRL_ALIGN_SEL_POS)
#define I2S_CTRL_ALIGN_SEL_RIGHT						(0x0UL << I2S_CTRL_ALIGN_SEL_POS)

/*
 * Bit definition for I2S_CTRL[4] - I2S RX Data endianness selection
 */
#define I2S_CTRL_RX_DATA_ENDIANNESS_SEL_POS (4)
#define I2S_CTRL_RX_DATA_ENDIANNESS_SEL_MSK (0x1UL << I2S_CTRL_RX_DATA_ENDIANNESS_SEL_POS)
#define I2S_CTRL_RX_DATA_MSB								(0x0UL << I2S_CTRL_RX_DATA_ENDIANNESS_SEL_POS)
#define I2S_CTRL_RX_DATA_LSB								(0x1UL << I2S_CTRL_RX_DATA_ENDIANNESS_SEL_POS)

/*
 * Bit definition for I2S_CTRL[3] - I2S receiving mode selection
 */
#define I2S_CTRL_RX_DATA_LATCH_SEL_POS      (3)
#define I2S_CTRL_RX_DATA_LATCH_SEL_MSK      (0x1UL << I2S_CTRL_RX_DATA_LATCH_SEL_POS)
#define I2S_CTRL_RX_DATA_LATCH_SEL_RISE     (0x1UL << I2S_CTRL_RX_DATA_LATCH_SEL_POS)
#define I2S_CTRL_RX_DATA_LATCH_SEL_FALL     (0x0UL << I2S_CTRL_RX_DATA_LATCH_SEL_POS)

/*
 * Bit definition for I2S_CTRL[2] - I2S RX frame polarity,,  0: LRCK=0 is the right frame (Default), 	1: LRCK=0 is the left frame
 */
#define I2S_CTRL_RX_FRAME_POL_POS           (2)
#define I2S_CTRL_RX_FRAME_POL_MSK           (0x1UL << I2S_CTRL_RX_FRAME_POL_POS)
#define I2S_CTRL_RX_FRAME_RIGHT             (0x1UL << I2S_CTRL_RX_FRAME_POL_POS)
#define I2S_CTRL_RX_FRAME_LEFT              (0x0UL << I2S_CTRL_RX_FRAME_POL_POS)

/*
 * Bit definition for I2S_CTRL[1] - I2S RX the first frame polarity,0: Left frame (Default), 1: Right frame
 */
#define I2S_CTRL_RX_1ST_FRAME_POL_POS       (1)
#define I2S_CTRL_RX_1ST_FRAME_POL_MSK       (0x1UL << I2S_CTRL_RX_1ST_FRAME_POL_POS)
#define I2S_CTRL_RX_1ST_FRAME_RIGHT         (0x1UL << I2S_CTRL_RX_1ST_FRAME_POL_POS)
#define I2S_CTRL_RX_1ST_FRAME_LEFT          (0x0UL << I2S_CTRL_RX_1ST_FRAME_POL_POS)

/*
 * Bit definition for I2S_CTRL[0] - I2S RX enable bit
 */
#define I2S_CTRL_RX_EN_POS                  (0)
#define I2S_CTRL_RX_EN_MSK                  (0x1UL << I2S_CTRL_RX_EN_POS)
#define I2S_CTRL_RX_ENABLE                  (0x1UL << I2S_CTRL_RX_EN_POS)
#define I2S_CTRL_RX_DISABLE                 (0x0UL << I2S_CTRL_RX_EN_POS)

/*
 * Bit definition for I2S_STS[18] - FIFO Clear
 */
#define I2S_STS_CLEAR_FIFO_POS    					(18)
#define I2S_STS_CLEAR_FIFO_MSK              (0x1UL << I2S_STS_CLEAR_FIFO_POS)
#define I2S_STS_CLEAR_FIFO_ENABLE         	(0x1UL << I2S_STS_CLEAR_FIFO_POS)
#define I2S_STS_CLEAR_FIFO_DISABLE        	(0x0UL << I2S_STS_CLEAR_FIFO_POS)

/*
 * Bit definition for I2S_STS[17] - HALF FULL FLAG
 */
#define I2S_STS_HALF_FULL_FLAG_POS					(17)
#define I2S_STS_HALF_FULL_FLAG_MSK          (0x1UL << I2S_STS_HALF_FULL_FLAG_POS)
#define I2S_STS_HALF_FULL_FLAG           	  (0x1UL << I2S_STS_HALF_FULL_FLAG_POS)

/*
 * Bit definition for I2S_STS[15] - Overflow Flag
 */
#define I2S_STS_OVERFLOW_FLAG_POS					(15)
#define I2S_STS_OVERFLOW_FLAG_MSK         	(0x1UL << I2S_STS_OVERFLOW_FLAG_POS)
#define I2S_STS_OVERFLOW_FLAG           		(0x1UL << I2S_STS_OVERFLOW_FLAG_POS)

/*
 * Bit definition for I2S_STS[3:2] - RX FIFO NUMBER
 */
#define I2S_CTRL_FIFO_INT_LEVEL_SEL					(2)
#define I2S_CTRL_FIFO_INT_LEVEL_MSK					(0x3FUL << I2S_CTRL_FIFO_INT_LEVEL_SEL)

/*
 * Bit definition for I2S_STS[1] - RX FIFO Full Flag
 */
#define I2S_CTRL_FIFO_FULL_FLAG_POS         (1)
#define I2S_CTRL_FIFO_FULL_FLAG_MSK         (0x1UL << I2S_CTRL_FIFO_FULL_FLAG_POS)
#define I2S_CTRL_FIFO_FULL_FLAG             (0x1UL << I2S_CTRL_FIFO_FULL_FLAG_POS)

/*
 * Bit definition for I2S_STS[0] - RX FIFO Empty Flag
 */
#define I2S_CTRL_FIFO_EMPTY_FLAG_POS  		  (0)
#define I2S_CTRL_FIFO_EMPTY_FLAG_MSK			  (0x1UL << I2S_CTRL_FIFO_EMPTY_FLAG_POS)
#define I2S_CTRL_FIFO_EMPTY_FLAG					  (0x1UL << I2S_CTRL_FIFO_EMPTY_FLAG_POS)

/*
 * Bit definition for I2S_CTRL2[31:29] - BCLK_DIV
 */
#define I2S_CTRL2_BCLK_DIV_SEL_POS          (29)
#define I2S_CTRL2_BCLK_DIV_SEL_MSK          (0x7UL << I2S_CTRL2_BCLK_DIV_SEL_POS)
#define I2S_CTRL2_BCLK_DIV_2        			  (0x2UL << I2S_CTRL2_BCLK_DIV_SEL_POS)
#define I2S_CTRL2_BCLK_DIV_3        			  (0x3UL << I2S_CTRL2_BCLK_DIV_SEL_POS)
#define I2S_CTRL2_BCLK_DIV_4        			  (0x4UL << I2S_CTRL2_BCLK_DIV_SEL_POS)
#define I2S_CTRL2_BCLK_DIV_6        			  (0x6UL << I2S_CTRL2_BCLK_DIV_SEL_POS)
#define I2S_CTRL2_BCLK_DIV_8        			  (0x7UL << I2S_CTRL2_BCLK_DIV_SEL_POS)

/*
 * Bit definition for I2S_CTRL2[5:0] - MCLK_DIV
 */
#define I2S_CTRL2_MCLK_DIV_POS      		    (0)
#define I2S_CTRL2_MCLK_DIV_MSK        		  (0x3FUL << I2S_CTRL2_MCLK_DIV_POS)
#define I2S_CTRL2_MCLK_DIV_2        			  (0x0UL 	<< I2S_CTRL2_MCLK_DIV_POS)
#define I2S_CTRL2_MCLK_DIV_3        			  (0x2UL  << I2S_CTRL2_MCLK_DIV_POS)
#define I2S_CTRL2_MCLK_DIV_4        			  (0x3UL  << I2S_CTRL2_MCLK_DIV_POS)


/*---------------------------------------------------------------------------------------
 * Watchdog Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t KEYCODE;                    // Watchdog Key Code Register
	__IO uint32_t CTRL;                       // Watchdog Control Register
	__IO uint32_t STS;                        // Watchdog Status Register
} WDG_TYPE_DEF;

/*
 * Bit definition for WDG_KEYCODE[7:0] - Watch dog keycode
 */
#define WDG_KEYCODE_POS                     (0)
#define WDG_KEYCODE_MSK                     (0xFFUL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_WDG_CLEAR               (0xAAUL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_RESET_DISABLE           (0x99UL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_RESET_ENABLE            (0x66UL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_ACCESS_ENABLE           (0x55UL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_ACCESS_DISABLE          (0x44UL << WDG_KEYCODE_POS)
#define WDG_KEYCODE_WDG_DISABLE             (0x00UL << WDG_KEYCODE_POS)

/*
 * Bit definition for WDG_CTRL[27:16] -  Watchdog counter reload value
 */
#define WDG_CTRL_CNT_POS                    (16)
#define WDG_CTRL_CNT_MSK                    (0xFFFUL << WDG_CTRL_CNT_POS)

/*
 * Bit definition for WDG_CTRL[12] -  Illegal keycode reset enable
 */
#define WDG_CTRL_ILL_RST_EN_POS             (12)
#define WDG_CTRL_ILL_RST_EN_MSK             (0x1UL << WDG_CTRL_ILL_RST_EN_POS)
#define WDG_CTRL_ILL_RST_ENABLE             (0x1UL << WDG_CTRL_ILL_RST_EN_POS)
#define WDG_CTRL_ILL_RST_DISABLE            (0x0UL << WDG_CTRL_ILL_RST_EN_POS)

/*
 * Bit definition for WDG_CTRL[10:8] - Watchdog clock source selection
 */
#define WDG_CTRL_CLK_SEL_POS                (8)
#define WDG_CTRL_CLK_SEL_MSK                (0x7UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_256      (0x7UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_128      (0x6UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_64       (0x5UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_32       (0x4UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_16       (0x3UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_8        (0x2UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_4        (0x1UL << WDG_CTRL_CLK_SEL_POS)
#define WDG_CTRL_CLK_SEL_32768_DIV_1        (0x0UL << WDG_CTRL_CLK_SEL_POS)

/*
 * Bit definition for WDG_CTRL[1] - Watchdog timer timeout flag
 */
#define WDG_CTRL_TIMEOUT_FLAG_POS           (1)
#define WDG_CTRL_TIMEOUT_FLAG_MSK           (0x1UL << WDG_CTRL_TIMEOUT_FLAG_POS)
#define WDG_CTRL_TIMEOUT_FLAG               (0x1UL << WDG_CTRL_TIMEOUT_FLAG_POS)

/*
 * Bit definition for WDG_STS[1] - Watch dog illegal access reset flag
 */
#define WDG_STS_ILL_RESET_FLAG_POS          (1)
#define WDG_STS_ILL_RESET_FLAG_MSK          (0x1UL << WDG_STS_ILL_RESET_FLAG_POS)
#define WDG_STS_ILL_RESET_FLAG              (0x1UL << WDG_STS_ILL_RESET_FLAG_POS)


/*---------------------------------------------------------------------------------------
 * CTS Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // CTS Control Register
	__IO uint32_t STS;                        // CTS Status Register
	__IO uint32_t TMAPLOAD;	                  // CTS Preload Register for TimerA
	__IO uint32_t TMACOUNT;	                  // CTS Counter Register for TimerA
	__IO uint32_t TMB0PLOAD;	                // CTS Preload Register for TimerB0
	__IO uint32_t TMBCOUNT;	                  // CTS Counter Register for TimerB
	__IO uint32_t TMBCAP; 	                  // CTS Capture Register for TimerB
	__IO uint32_t PADSEL;                     // CTS Pad Select Register
	__IO uint32_t TMB1PLOAD;	                // CTS Preload Register for TimerB1
	__IO uint32_t TMB2PLOAD;	                // CTS Preload Register for TimerB2
	__IO uint32_t TMB3PLOAD;	                // CTS Preload Register for TimerB3
	__IO uint32_t TMB4PLOAD;	                // CTS Preload Register for TimerB4
	__IO uint32_t TMB5PLOAD;	                // CTS Preload Register for TimerB5
	__IO uint32_t TMB6PLOAD;	                // CTS Preload Register for TimerB6
	__IO uint32_t TMB7PLOAD;	                // CTS Preload Register for TimerB7
	__IO uint32_t TMB8PLOAD;	                // CTS Preload Register for TimerB8
	__IO uint32_t TMB9PLOAD;	                // CTS Preload Register for TimerB9
	__IO uint32_t TMB10PLOAD;	                // CTS Preload Register for TimerB10
} CTS_TYPE_DEF;


/*
 * Bit definition for CTS_CTRL[29] - CTS TMB INT Enable Select
 */
#define CTS_CTRL_TMB_INTEN_SEL_POS          (29)
#define CTS_CTRL_TMB_INTEN_SEL_MSK          (0x1UL << CTS_CTRL_TMB_INTEN_SEL_POS)
#define CTS_CTRL_TMB_INTEN_SEL_ENABLE       (0x1UL << CTS_CTRL_TMB_INTEN_SEL_POS)
#define CTS_CTRL_TMB_INTEN_SEL_DISABLE      (0x0UL << CTS_CTRL_TMB_INTEN_SEL_POS)

/*
 * Bit definition for CTS_CTRL[28] - CTS TMA INT Enable Select
 */
#define CTS_CTRL_TMA_INTEN_SEL_POS          (28)
#define CTS_CTRL_TMA_INTEN_SEL_MSK          (0x1UL << CTS_CTRL_TMA_INTEN_SEL_POS)
#define CTS_CTRL_TMA_INTEN_SEL_ENABLE       (0x1UL << CTS_CTRL_TMA_INTEN_SEL_POS)
#define CTS_CTRL_TMA_INTEN_SEL_DISABLE      (0x0UL << CTS_CTRL_TMA_INTEN_SEL_POS)

/*
 * Bit definition for CTS_CTRL[23:21] - CTS TMB Clock Source Select
 */
#define CTS_CTRL_TMB_CLK_SEL_POS            (21)
#define CTS_CTRL_TMB_CLK_SEL_MSK            (0x7UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_IOSC16M        (0x7UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK_DIV_32    (0x6UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK_DIV_16    (0x5UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK_DIV_8     (0x4UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK_DIV_4     (0x3UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK_DIV_2     (0x2UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_HCLK           (0x1UL << CTS_CTRL_TMB_CLK_SEL_POS)
#define CTS_CTRL_TMB_CLK_SEL_DISABLE        (0x0UL << CTS_CTRL_TMB_CLK_SEL_POS)

/*
 * Bit definition for CTS_CTRL[20] - CTS TMB dedicated for CTS timer or General timer
 */
#define CTS_CTRL_TMB_MODE_POS               (20)
#define CTS_CTRL_TMB_MODE_MSK               (0x1UL << CTS_CTRL_TMB_MODE_POS)
#define CTS_CTRL_TMB_MODE_GENERALTMR        (0x1UL << CTS_CTRL_TMB_MODE_POS)
#define CTS_CTRL_TMB_MODE_CTSTMR            (0x0UL << CTS_CTRL_TMB_MODE_POS)

/*
 * Bit definition for CTS_CTRL[19:17] - CTS TMA Clock Source Select
 */
#define CTS_CTRL_TMA_CLK_SEL_POS            (17)
#define CTS_CTRL_TMA_CLK_SEL_MSK            (0x7UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_HCLK_DIV_16    (0x7UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_HCLK_DIV_8     (0x6UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_HCLK_DIV_4     (0x5UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_HCLK_DIV_2     (0x4UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_HCLK           (0x3UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_CTSMODULE      (0x2UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_IO             (0x1UL << CTS_CTRL_TMA_CLK_SEL_POS)
#define CTS_CTRL_TMA_CLK_SEL_DISABLE        (0x0UL << CTS_CTRL_TMA_CLK_SEL_POS)

/*
 * Bit definition for CTS_CTRL[16] - CTS TMA dedicated for CTS timer or General timer
 */
#define CTS_CTRL_TMA_MODE_POS               (16)
#define CTS_CTRL_TMA_MODE_MSK               (0x1UL << CTS_CTRL_TMA_MODE_POS)
#define CTS_CTRL_TMA_MODE_GENERALTMR        (0x1UL << CTS_CTRL_TMA_MODE_POS)
#define CTS_CTRL_TMA_MODE_CTSTMR            (0x0UL << CTS_CTRL_TMA_MODE_POS)

/*
 * Bit definition for CTS_CTRL[12] - CTS Charge/Discharge Current Select
 */
#define CTS_CTRL_CHARGE_CURRENT_POS         (12)
#define CTS_CTRL_CHARGE_CURRENT_MSK         (0x1UL << CTS_CTRL_CHARGE_CURRENT_POS)
#define CTS_CTRL_CHARGE_CURRENT_50uA        (0x1UL << CTS_CTRL_CHARGE_CURRENT_POS)
#define CTS_CTRL_CHARGE_CURRENT_25uA        (0x0UL << CTS_CTRL_CHARGE_CURRENT_POS)

/*
 * Bit definition for CTS_CTRL[7] - CTS Multi-IO Enable bit
 */
#define CTS_CTRL_SLEEP_MULTIIO_EN_POS       (7)
#define CTS_CTRL_SLEEP_MULTIIO_EN_MSK       (0x1UL << CTS_CTRL_SLEEP_MULTIIO_EN_POS)
#define CTS_CTRL_SLEEP_MULTIIO_EN_ENABLE    (0x1UL << CTS_CTRL_SLEEP_MULTIIO_EN_POS)
#define CTS_CTRL_SLEEP_MULTIIO_EN_DISABLE   (0x0UL << CTS_CTRL_SLEEP_MULTIIO_EN_POS)

/*
 * Bit definition for CTS_CTRL[6] - CTS Low Power Mode Enable bit
 */
#define CTS_CTRL_SLEEP_EN_POS               (6)
#define CTS_CTRL_SLEEP_EN_MSK               (0x1UL << CTS_CTRL_SLEEP_EN_POS)
#define CTS_CTRL_SLEEP_EN_ENABLE            (0x1UL << CTS_CTRL_SLEEP_EN_POS)
#define CTS_CTRL_SLEEP_EN_DISABLE           (0x0UL << CTS_CTRL_SLEEP_EN_POS)

/*
 * Bit definition for CTS_CTRL[5:4] - CTS Low Power Mode Clock Source Select
 */
#define CTS_CTRL_SLEEP_CLK_SEL_POS          (4)
#define CTS_CTRL_SLEEP_CLK_SEL_MSK          (0x3UL << CTS_CTRL_SLEEP_CLK_SEL_POS)
#define CTS_CTRL_SLEEP_CLK_SEL_128Hz        (0x3UL << CTS_CTRL_SLEEP_CLK_SEL_POS)
#define CTS_CTRL_SLEEP_CLK_SEL_32Hz         (0x2UL << CTS_CTRL_SLEEP_CLK_SEL_POS)
#define CTS_CTRL_SLEEP_CLK_SEL_16Hz         (0x1UL << CTS_CTRL_SLEEP_CLK_SEL_POS)
#define CTS_CTRL_SLEEP_CLK_SEL_8Hz          (0x0UL << CTS_CTRL_SLEEP_CLK_SEL_POS)

/*
 * Bit definition for CTS_CTRL[2] - CTS Auto Stop bit
 */
#define CTS_CTRL_AUTOSTOP_POS               (2)
#define CTS_CTRL_AUTOSTOP_MSK               (0x1UL << CTS_CTRL_AUTOSTOP_POS)
#define CTS_CTRL_AUTOSTOP_ENABLE            (0x1UL << CTS_CTRL_AUTOSTOP_POS)
#define CTS_CTRL_AUTOSTOP_DISABLE           (0x0UL << CTS_CTRL_AUTOSTOP_POS)

/*
 * Bit definition for CTS_CTRL[1] - CTS Start bit
 */
#define CTS_CTRL_START_POS                  (1)
#define CTS_CTRL_START_MSK                  (0x1UL << CTS_CTRL_START_POS)
#define CTS_CTRL_START_ENABLE               (0x1UL << CTS_CTRL_START_POS)
#define CTS_CTRL_START_DISABLE              (0x0UL << CTS_CTRL_START_POS)

/*
 * Bit definition for CTS_CTRL[0] - CTS enable bit
 */
#define CTS_CTRL_CTSEN_POS                  (0)
#define CTS_CTRL_CTSEN_MSK                  (0x1UL << CTS_CTRL_CTSEN_POS)
#define CTS_CTRL_CTSEN_ENABLE               (0x1UL << CTS_CTRL_CTSEN_POS)
#define CTS_CTRL_CTSEN_DISABLE              (0x0UL << CTS_CTRL_CTSEN_POS)

/*
 * Bit definition for CTS_STS[29] - CTS TMB Flag
 */
#define CTS_STS_TMB_INTF_POS                (29)
#define CTS_STS_TMB_INTF_MSK                (0x1UL << CTS_STS_TMB_INTF_POS)
#define CTS_STS_TMB_INTF_FLAG               (0x1UL << CTS_STS_TMB_INTF_POS)

/*
 * Bit definition for CTS_STS[28] - CTS TMA Flag
 */
#define CTS_STS_TMA_INTF_POS                (28)
#define CTS_STS_TMA_INTF_MSK                (0x1UL << CTS_STS_TMA_INTF_POS)
#define CTS_STS_TMA_INTF_FLAG               (0x1UL << CTS_STS_TMA_INTF_POS)


/*
 * Bit definition for PADSEL[9:0] - CTS TMA clock source select(From CTS module) when the CTS_CTRL[19:17] = 010
 */
#define CTS_PADSEL_POS                      (0)
#define CTS_PADSEL_MSK                      (0x3FFUL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO9_ENABLE               (0x200UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO9_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO8_ENABLE               (0x100UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO8_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO7_ENABLE               (0x080UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO7_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO6_ENABLE               (0x040UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO6_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO5_ENABLE               (0x020UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO5_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO4_ENABLE               (0x010UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO4_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO3_ENABLE               (0x008UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO3_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO2_ENABLE               (0x004UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO2_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO1_ENABLE               (0x002UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO1_DISABLE              (0x000UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO0_ENABLE               (0x001UL << CTS_PADSEL_POS)
#define CTS_PADSEL_IO0_DISABLE              (0x000UL << CTS_PADSEL_POS)

/*
 * Bit definition for PADSEL[4:0] - CTS TMA clock source select(From IO PAD) if CTS_CTRL[19:17] = 001
 */
#define CTS_PADSEL_TMA_CLKSRC_POS           (0)
#define CTS_PADSEL_TMA_CLKSRC_MSK           (0x1FUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA0     (0x00UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA1     (0x01UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA2     (0x02UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA3     (0x03UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA4     (0x04UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA5     (0x05UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA6     (0x06UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA7     (0x07UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA8     (0x08UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA9     (0x09UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA10    (0x0AUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA11    (0x0BUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA12    (0x0CUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA13    (0x0DUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA14    (0x0EUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA15    (0x0FUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA16    (0x10UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA17    (0x11UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA18    (0x12UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA19    (0x13UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA20    (0x14UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA21    (0x15UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA22    (0x16UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA23    (0x17UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOA24    (0x18UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB0     (0x19UL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB1     (0x1AUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB2     (0x1BUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB3     (0x1CUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB4     (0x1DUL << CTS_PADSEL_TMA_CLKSRC_POS)
#define CTS_PADSEL_TMA_CLKSRC_FROM_IOB5     (0x1EUL << CTS_PADSEL_TMA_CLKSRC_POS)

/*---------------------------------------------------------------------------------------
 * TimeBase Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // TimeBase Control Register
	__IO uint32_t STS;                        // TimeBase Status Register
} TIMEBASE_TYPE_DEF;

/*
 * Bit definition for TIMEBASE_CTRL[9] - TimeBase clear bit
 */
#define TIMEBASE_CTRL_CLRCNT_POS            (9)
#define TIMEBASE_CTRL_CLRCNT_MSK            (0x1UL << TIMEBASE_CTRL_CLRCNT_POS)
#define TIMEBASE_CTRL_CLRCNT_ENABLE         (0x1UL << TIMEBASE_CTRL_CLRCNT_POS)
#define TIMEBASE_CTRL_CLRCNT_DISABLE        (0x0UL << TIMEBASE_CTRL_CLRCNT_POS)

/*
 * Bit definition for TIMEBASE_CTRL[8] - TimeBase enable bit
 */
#define TIMEBASE_CTRL_TB_EN_POS              (8)
#define TIMEBASE_CTRL_TB_EN_MSK              (0x1UL << TIMEBASE_CTRL_TB_EN_POS)
#define TIMEBASE_CTRL_TB_ENABLE              (0x1UL << TIMEBASE_CTRL_TB_EN_POS)
#define TIMEBASE_CTRL_TB_DISABLE             (0x0UL << TIMEBASE_CTRL_TB_EN_POS)

/*
 * Bit definition for TIMEBASE_CTRL[5] - 4KHz INT enable bit
 */
#define TIMEBASE_CTRL_4KHZ_POS              (5)
#define TIMEBASE_CTRL_4KHZ_MSK              (0x1UL << TIMEBASE_CTRL_4KHZ_POS)
#define TIMEBASE_CTRL_4KHZ_ENABLE           (0x1UL << TIMEBASE_CTRL_4KHZ_POS)
#define TIMEBASE_CTRL_4KHZ_DISABLE          (0x0UL << TIMEBASE_CTRL_4KHZ_POS)

/*
 * Bit definition for TIMEBASE_CTRL[4] - 2KHz INT enable bit
 */
#define TIMEBASE_CTRL_2KHZ_POS              (4)
#define TIMEBASE_CTRL_2KHZ_MSK              (0x1UL << TIMEBASE_CTRL_2KHZ_POS)
#define TIMEBASE_CTRL_2KHZ_ENABLE           (0x1UL << TIMEBASE_CTRL_2KHZ_POS)
#define TIMEBASE_CTRL_2KHZ_DISABLE          (0x0UL << TIMEBASE_CTRL_2KHZ_POS)

/*
 * Bit definition for TIMEBASE_CTRL[3] - 512Hz INT enable bit
 */
#define TIMEBASE_CTRL_512HZ_POS             (3)
#define TIMEBASE_CTRL_512HZ_MSK             (0x1UL << TIMEBASE_CTRL_512HZ_POS)
#define TIMEBASE_CTRL_512HZ_ENABLE          (0x1UL << TIMEBASE_CTRL_512HZ_POS)
#define TIMEBASE_CTRL_512HZ_DISABLE         (0x0UL << TIMEBASE_CTRL_512HZ_POS)

/*
 * Bit definition for TIMEBASE_CTRL[2] - 64Hz INT enable bit
 */
#define TIMEBASE_CTRL_64HZ_POS              (2)
#define TIMEBASE_CTRL_64HZ_MSK              (0x1UL << TIMEBASE_CTRL_64HZ_POS)
#define TIMEBASE_CTRL_64HZ_ENABLE           (0x1UL << TIMEBASE_CTRL_64HZ_POS)
#define TIMEBASE_CTRL_64HZ_DISABLE          (0x0UL << TIMEBASE_CTRL_64HZ_POS)

/*
 * Bit definition for TIMEBASE_CTRL[1] - 16Hz INT enable bit
 */
#define TIMEBASE_CTRL_16HZ_POS              (1)
#define TIMEBASE_CTRL_16HZ_MSK              (0x1UL << TIMEBASE_CTRL_16HZ_POS)
#define TIMEBASE_CTRL_16HZ_ENABLE           (0x1UL << TIMEBASE_CTRL_16HZ_POS)
#define TIMEBASE_CTRL_16HZ_DISABLE          (0x0UL << TIMEBASE_CTRL_16HZ_POS)

/*
 * Bit definition for TIMEBASE_CTRL[0] - 2Hz INT enable bit
 */
#define TIMEBASE_CTRL_2HZ_POS               (0)
#define TIMEBASE_CTRL_2HZ_MSK               (0x1UL << TIMEBASE_CTRL_2HZ_POS)
#define TIMEBASE_CTRL_2HZ_ENABLE            (0x1UL << TIMEBASE_CTRL_2HZ_POS)
#define TIMEBASE_CTRL_2HZ_DISABLE           (0x0UL << TIMEBASE_CTRL_2HZ_POS)

/*
 * Bit definition for TIMEBASE_STS[5] - 4KHz INT Flag
 */
#define TIMEBASE_STS_4KHZ_INTF_POS          (5)
#define TIMEBASE_STS_4KHZ_INTF_MSK          (0x1UL << TIMEBASE_STS_4KHZ_INTF_POS)
#define TIMEBASE_STS_4KHZ_INTF_FLAG         (0x1UL << TIMEBASE_STS_4KHZ_INTF_POS)

/*
 * Bit definition for TIMEBASE_STS[4] - 2KHz INT Flag
 */
#define TIMEBASE_STS_2KHZ_INTF_POS          (4)
#define TIMEBASE_STS_2KHZ_INTF_MSK          (0x1UL << TIMEBASE_STS_2KHZ_INTF_POS)
#define TIMEBASE_STS_2KHZ_INTF_FLAG         (0x1UL << TIMEBASE_STS_2KHZ_INTF_POS)

/*
 * Bit definition for TIMEBASE_STS[3] - 512Hz INT Flag
 */
#define TIMEBASE_STS_512HZ_INTF_POS         (3)
#define TIMEBASE_STS_512HZ_INTF_MSK         (0x1UL << TIMEBASE_STS_512HZ_INTF_POS)
#define TIMEBASE_STS_512HZ_INTF_FLAG        (0x1UL << TIMEBASE_STS_512HZ_INTF_POS)

/*
 * Bit definition for TIMEBASE_STS[2] - 64Hz INT Flag
 */
#define TIMEBASE_STS_64HZ_INTF_POS          (2)
#define TIMEBASE_STS_64HZ_INTF_MSK          (0x1UL << TIMEBASE_STS_64HZ_INTF_POS)
#define TIMEBASE_STS_64HZ_INTF_FLAG         (0x1UL << TIMEBASE_STS_64HZ_INTF_POS)

/*
 * Bit definition for TIMEBASE_STS[1] - 16Hz INT Flag
 */
#define TIMEBASE_STS_16HZ_INTF_POS          (1)
#define TIMEBASE_STS_16HZ_INTF_MSK          (0x1UL << TIMEBASE_STS_16HZ_INTF_POS)
#define TIMEBASE_STS_16HZ_INTF_FLAG         (0x1UL << TIMEBASE_STS_16HZ_INTF_POS)

/*
 * Bit definition for TIMEBASE_STS[0] - 2Hz INT Flag
 */
#define TIMEBASE_STS_2HZ_INTF_POS           (0)
#define TIMEBASE_STS_2HZ_INTF_MSK           (0x1UL << TIMEBASE_STS_2HZ_INTF_POS)
#define TIMEBASE_STS_2HZ_INTF_FLAG          (0x1UL << TIMEBASE_STS_2HZ_INTF_POS)


/*---------------------------------------------------------------------------------------
 * SAR ADC Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t GCTRL;                           // ADC Global Control Register
	__IO uint32_t CTRL;  					                 // ADC Control Register
	__IO uint32_t STS;	  					               // ADC Status Register
	__IO uint32_t SMP0;  						               // ADC Sample Time Control Register 0
	__IO uint32_t SMP1;							               // ADC Sample Time Control Register 1
	__IO uint32_t REG_COV; 		 		                 // ADC Regular Mode Conversion Channel
	__IO uint32_t REG_SEQ; 		 		                 // ADC Regular Sequence Register
	__IO uint32_t INJ_SEQ;  				               // ADC Injected Sequence Register
	__IO uint32_t WDG_TH;						               // ADC Watch-Dog Threshold Register
	__IO uint32_t REG_DATA;  				               // ADC Regular Data Register
	__IO uint32_t INJ0_DATA;				               // ADC Injected0 Data Register
	__IO uint32_t INJ1_DATA; 		 		               // ADC Injected1 Data Register
	__IO uint32_t INJ2_DATA;				               // ADC Injected2 Data Register
	__IO uint32_t INJ3_DATA; 		 		               // ADC Injected3 Data Register
} SAR_ADC_TYPE_DEF;

/*
 * Bit definition for SAR_ADC_GCTRL[30] - Analog watch-dog interrupt enable on injected channel
 */
#define SAR_ADC_GCTRL_ANALOG_WDGJ_INT_EN_POS     (30)
#define SAR_ADC_GCTRL_ANALOG_WDGJ_INT_EN_MSK     (0x1UL << SAR_ADC_GCTRL_ANALOG_WDGJ_INT_EN_POS)
#define SAR_ADC_GCTRL_ANALOG_WDGJ_INT_ENABLE     (0x1UL << SAR_ADC_GCTRL_ANALOG_WDGJ_INT_EN_POS)
#define SAR_ADC_GCTRL_ANALOG_WDGJ_INT_DISABLE    (0x0UL << SAR_ADC_GCTRL_ANALOG_WDGJ_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[29] - Analog watch-dog interrupt enable on regular channel
 */
#define SAR_ADC_GCTRL_ANALOG_WDGR_INT_EN_POS     (29)
#define SAR_ADC_GCTRL_ANALOG_WDGR_INT_EN_MSK     (0x1UL << SAR_ADC_GCTRL_ANALOG_WDGR_INT_EN_POS)
#define SAR_ADC_GCTRL_ANALOG_WDGR_INT_ENABLE     (0x1UL << SAR_ADC_GCTRL_ANALOG_WDGR_INT_EN_POS)
#define SAR_ADC_GCTRL_ANALOG_WDGR_INT_DISABLE    (0x0UL << SAR_ADC_GCTRL_ANALOG_WDGR_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[28] - Injected conversion interrupt enable of channel 3
 */
#define SAR_ADC_GCTRL_INJ3_INT_EN_POS            (28)
#define SAR_ADC_GCTRL_INJ3_INT_EN_MSK            (0x1UL << SAR_ADC_GCTRL_INJ3_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ3_INT_ENABLE            (0x1UL << SAR_ADC_GCTRL_INJ3_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ3_INT_DISABLE           (0x0UL << SAR_ADC_GCTRL_INJ3_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[27] - Injected conversion interrupt enable of channel 2
 */
#define SAR_ADC_GCTRL_INJ2_INT_EN_POS            (27)
#define SAR_ADC_GCTRL_INJ2_INT_EN_MSK            (0x1UL << SAR_ADC_GCTRL_INJ2_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ2_INT_ENABLE            (0x1UL << SAR_ADC_GCTRL_INJ2_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ2_INT_DISABLE           (0x0UL << SAR_ADC_GCTRL_INJ2_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[26] - Injected conversion interrupt enable of channel 1
 */
#define SAR_ADC_GCTRL_INJ1_INT_EN_POS            (26)
#define SAR_ADC_GCTRL_INJ1_INT_EN_MSK            (0x1UL << SAR_ADC_GCTRL_INJ1_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ1_INT_ENABLE            (0x1UL << SAR_ADC_GCTRL_INJ1_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ1_INT_DISABLE           (0x0UL << SAR_ADC_GCTRL_INJ1_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[25] - Injected conversion interrupt enable of channel 0
 */
#define SAR_ADC_GCTRL_INJ0_INT_EN_POS            (25)
#define SAR_ADC_GCTRL_INJ0_INT_EN_MSK            (0x1UL << SAR_ADC_GCTRL_INJ0_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ0_INT_ENABLE            (0x1UL << SAR_ADC_GCTRL_INJ0_INT_EN_POS)
#define SAR_ADC_GCTRL_INJ0_INT_DISABLE           (0x0UL << SAR_ADC_GCTRL_INJ0_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[24] - Regular mode interrupt enable
 */
#define SAR_ADC_GCTRL_REG_MODE_INT_EN_POS        (24)
#define SAR_ADC_GCTRL_REG_MODE_INT_EN_MSK        (0x1UL << SAR_ADC_GCTRL_REG_MODE_INT_EN_POS)
#define SAR_ADC_GCTRL_REG_MODE_INT_ENABLE        (0x1UL << SAR_ADC_GCTRL_REG_MODE_INT_EN_POS)
#define SAR_ADC_GCTRL_REG_MODE_INT_DISABLE       (0x0UL << SAR_ADC_GCTRL_REG_MODE_INT_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[12:8] - ADC clock select bits
 */
#define SAR_ADC_GCTRL_ADC_CLK_SEL_POS            (8)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_MSK            (0x1FUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV64     (0x1FUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV62     (0x1EUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV60     (0x1DUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV58     (0x1CUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV56     (0x1BUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV54     (0x1AUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV52     (0x19UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV50     (0x18UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV48     (0x17UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV46     (0x16UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV44     (0x15UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV42     (0x14UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV40     (0x13UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV38     (0x12UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV36     (0x11UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV34     (0x10UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV32     (0x0FUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV30     (0x0EUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV28     (0x0DUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV26     (0x0CUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV24     (0x0BUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV22     (0x0AUL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV20     (0x09UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV18     (0x08UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV16     (0x07UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV14     (0x06UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV12     (0x05UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV10     (0x04UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV8      (0x03UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV6      (0x02UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV4      (0x01UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)
#define SAR_ADC_GCTRL_ADC_CLK_SEL_PCLK_DIV2      (0x00UL << SAR_ADC_GCTRL_ADC_CLK_SEL_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[4] - ADC DMA request enable
 */
#define SAR_ADC_GCTRL_DMA_EN_POS                 (4)
#define SAR_ADC_GCTRL_DMA_EN_MSK                 (0x1UL << SAR_ADC_GCTRL_DMA_EN_POS)
#define SAR_ADC_GCTRL_DMA_ENABLE                 (0x1UL << SAR_ADC_GCTRL_DMA_EN_POS)
#define SAR_ADC_GCTRL_DMA_DISABLE                (0x0UL << SAR_ADC_GCTRL_DMA_EN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[2] - ADC output data alignment
 */
#define SAR_ADC_GCTRL_DAT_ALIGN_POS              (2)
#define SAR_ADC_GCTRL_DAT_ALIGN_MSK              (0x1UL << SAR_ADC_GCTRL_DAT_ALIGN_POS)
#define SAR_ADC_GCTRL_DAT_ALIGN_RIGHT            (0x1UL << SAR_ADC_GCTRL_DAT_ALIGN_POS)
#define SAR_ADC_GCTRL_DAT_ALIGN_LEFT             (0x0UL << SAR_ADC_GCTRL_DAT_ALIGN_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[1] - ADC data signed/unsigned select
 */
#define SAR_ADC_GCTRL_ADC_FMT_SEL_POS            (1)
#define SAR_ADC_GCTRL_ADC_FMT_SEL_MSK            (0x1UL << SAR_ADC_GCTRL_ADC_FMT_SEL_POS)
#define SAR_ADC_GCTRL_ADC_FMT_SEL_SIGN           (0x1UL << SAR_ADC_GCTRL_ADC_FMT_SEL_POS)
#define SAR_ADC_GCTRL_ADC_FMT_SEL_UNSIGN         (0x0UL << SAR_ADC_GCTRL_ADC_FMT_SEL_POS)

/*
 * Bit definition for SAR_ADC_GCTRL[0] - ADC analog block enable
 */
#define SAR_ADC_GCTRL_ADC_EN_POS                 (0)
#define SAR_ADC_GCTRL_ADC_EN_MSK                 (0x1UL << SAR_ADC_GCTRL_ADC_EN_POS)
#define SAR_ADC_GCTRL_ADC_ENABLE                 (0x1UL << SAR_ADC_GCTRL_ADC_EN_POS)
#define SAR_ADC_GCTRL_ADC_DISABLE                (0x0UL << SAR_ADC_GCTRL_ADC_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[31:29] - Injection channel 3 trigger source select bits
 */
#define SAR_ADC_CTRL_INJ3_TRG_SEL_POS            (29)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_MSK            (0x7UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_CTS_TM1        (0x6UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_CTS_TM0        (0x5UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_CCP1_TM        (0x4UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_CCP0_TM        (0x3UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_TM2            (0x2UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_TM1            (0x1UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ3_TRG_SEL_TM0            (0x0UL << SAR_ADC_CTRL_INJ3_TRG_SEL_POS)

/*
 * Bit definition for SAR_ADC_CTRL[28] - Injection channel 3 enable bit
 */
#define SAR_ADC_CTRL_INJ3_EN_POS                 (28)
#define SAR_ADC_CTRL_INJ3_EN_MSK                 (0x1UL << SAR_ADC_CTRL_INJ3_EN_POS)
#define SAR_ADC_CTRL_INJ3_ENABLE                 (0x1UL << SAR_ADC_CTRL_INJ3_EN_POS)
#define SAR_ADC_CTRL_INJ3_DISABLE                (0x0UL << SAR_ADC_CTRL_INJ3_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[27:25] - Injection channel 2 trigger source select bits
 */
#define SAR_ADC_CTRL_INJ2_TRG_SEL_POS            (25)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_MSK            (0x7UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_CTS_TM1        (0x6UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_CTS_TM0        (0x5UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_CCP1_TM        (0x4UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_CCP0_TM        (0x3UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_TM2            (0x2UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_TM1            (0x1UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ2_TRG_SEL_TM0            (0x0UL << SAR_ADC_CTRL_INJ2_TRG_SEL_POS)

/*
 * Bit definition for SAR_ADC_CTRL[24] - Injection channel 2 enable bit
 */
#define SAR_ADC_CTRL_INJ2_EN_POS                 (24)
#define SAR_ADC_CTRL_INJ2_EN_MSK                 (0x1UL << SAR_ADC_CTRL_INJ2_EN_POS)
#define SAR_ADC_CTRL_INJ2_ENABLE                 (0x1UL << SAR_ADC_CTRL_INJ2_EN_POS)
#define SAR_ADC_CTRL_INJ2_DISABLE                (0x0UL << SAR_ADC_CTRL_INJ2_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[23:21] - Injection channel 1 trigger source select bits
 */
#define SAR_ADC_CTRL_INJ1_TRG_SEL_POS            (21)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_MSK            (0x7UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_CTS_TM1        (0x6UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_CTS_TM0        (0x5UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_CCP1_TM        (0x4UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_CCP0_TM        (0x3UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_TM2            (0x2UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_TM1            (0x1UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ1_TRG_SEL_TM0            (0x0UL << SAR_ADC_CTRL_INJ1_TRG_SEL_POS)

/*
 * Bit definition for SAR_ADC_CTRL[20] - Injection channel 1 enable bit
 */
#define SAR_ADC_CTRL_INJ1_EN_POS                 (20)
#define SAR_ADC_CTRL_INJ1_EN_MSK                 (0x1UL << SAR_ADC_CTRL_INJ1_EN_POS)
#define SAR_ADC_CTRL_INJ1_ENABLE                 (0x1UL << SAR_ADC_CTRL_INJ1_EN_POS)
#define SAR_ADC_CTRL_INJ1_DISABLE                (0x0UL << SAR_ADC_CTRL_INJ1_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[19:17] - Injection channel 0 trigger source select bits
 */
#define SAR_ADC_CTRL_INJ0_TRG_SEL_POS            (17)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_MSK            (0x7UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_CTS_TM1        (0x6UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_CTS_TM0        (0x5UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_CCP1_TM        (0x4UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_CCP0_TM        (0x3UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_TM2            (0x2UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_TM1            (0x1UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)
#define SAR_ADC_CTRL_INJ0_TRG_SEL_TM0            (0x0UL << SAR_ADC_CTRL_INJ0_TRG_SEL_POS)

/*
 * Bit definition for SAR_ADC_CTRL[16] - Injection channel 0 enable bit
 */
#define SAR_ADC_CTRL_INJ0_EN_POS                 (16)
#define SAR_ADC_CTRL_INJ0_EN_MSK                 (0x1UL << SAR_ADC_CTRL_INJ0_EN_POS)
#define SAR_ADC_CTRL_INJ0_ENABLE                 (0x1UL << SAR_ADC_CTRL_INJ0_EN_POS)
#define SAR_ADC_CTRL_INJ0_DISABLE                (0x0UL << SAR_ADC_CTRL_INJ0_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[15] - Analog watch-dog enable on injected channel
 */
#define SAR_ADC_CTRL_ANALOG_WDGJ_EN_POS          (15)
#define SAR_ADC_CTRL_ANALOG_WDGJ_EN_MSK          (0x1UL << SAR_ADC_CTRL_ANALOG_WDGJ_EN_POS)
#define SAR_ADC_CTRL_ANALOG_WDGJ_ENABLE          (0x1UL << SAR_ADC_CTRL_ANALOG_WDGJ_EN_POS)
#define SAR_ADC_CTRL_ANALOG_WDGJ_DISABLE         (0x0UL << SAR_ADC_CTRL_ANALOG_WDGJ_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[11:8] - Regular sequence gap select bits
 */
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS         (8)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_MSK         (0xFUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_MANUAL      (0xFUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_CTS_TM1     (0xEUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_CTS_TM0     (0xDUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_CCP1_TM     (0xCUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_CCP0_TM     (0xBUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_TM2         (0xAUL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_TM1         (0x9UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_TM0         (0x8UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_7ADCCLK     (0x7UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_6ADCCLK     (0x6UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_5ADCCLK     (0x5UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_4ADCCLK     (0x4UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_3ADCCLK     (0x3UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_2ADCCLK     (0x2UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_1ADCCLK     (0x1UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)
#define SAR_ADC_CTRL_REG_SEQ_GAP_SEL_0ADCCLK     (0x0UL << SAR_ADC_CTRL_REG_SEQ_GAP_SEL_POS)

/*
 * Bit definition for SAR_ADC_CTRL[7:4] - Channel number during regular sequence
 */
#define SAR_ADC_CTRL_REG_CH_NUM_POS              (4)
#define SAR_ADC_CTRL_REG_CH_NUM_MSK              (0xFUL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_8                (0x7UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_7                (0x6UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_6                (0x5UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_5                (0x4UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_4                (0x3UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_3                (0x2UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_2                (0x1UL << SAR_ADC_CTRL_REG_CH_NUM_POS)
#define SAR_ADC_CTRL_REG_CH_NUM_1                (0x0UL << SAR_ADC_CTRL_REG_CH_NUM_POS)

/*
 * Bit definition for SAR_ADC_CTRL[3] - Analog watch-dog enable on regular channel
 */
#define SAR_ADC_CTRL_ANALOG_WDGR_EN_POS          (3)
#define SAR_ADC_CTRL_ANALOG_WDGR_EN_MSK          (0x1UL << SAR_ADC_CTRL_ANALOG_WDGR_EN_POS)
#define SAR_ADC_CTRL_ANALOG_WDGR_ENABLE          (0x1UL << SAR_ADC_CTRL_ANALOG_WDGR_EN_POS)
#define SAR_ADC_CTRL_ANALOG_WDGR_DISABLE         (0x0UL << SAR_ADC_CTRL_ANALOG_WDGR_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[2] - ADC loop scan enable bit
 */
#define SAR_ADC_CTRL_LOOP_EN_POS                 (2)
#define SAR_ADC_CTRL_LOOP_EN_MSK                 (0x1UL << SAR_ADC_CTRL_LOOP_EN_POS)
#define SAR_ADC_CTRL_LOOP_ENABLE                 (0x1UL << SAR_ADC_CTRL_LOOP_EN_POS)
#define SAR_ADC_CTRL_LOOP_DISABLE                (0x0UL << SAR_ADC_CTRL_LOOP_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[1] - Regular mode enable bit
 */
#define SAR_ADC_CTRL_REG_EN_POS                  (1)
#define SAR_ADC_CTRL_REG_EN_MSK                  (0x1UL << SAR_ADC_CTRL_REG_EN_POS)
#define SAR_ADC_CTRL_REG_ENABLE                  (0x1UL << SAR_ADC_CTRL_REG_EN_POS)
#define SAR_ADC_CTRL_REG_DISABLE                 (0x0UL << SAR_ADC_CTRL_REG_EN_POS)

/*
 * Bit definition for SAR_ADC_CTRL[0] - Software start bit
 */
#define SAR_ADC_CTRL_SFT_STR_POS                 (0)
#define SAR_ADC_CTRL_SFT_STR_MSK                 (0x1UL << SAR_ADC_CTRL_SFT_STR_POS)
#define SAR_ADC_CTRL_SFT_START                   (0x1UL << SAR_ADC_CTRL_SFT_STR_POS)

/*
 * Bit definition for SAR_ADC_STS[30] - Analog watch-dog interrupt flag on injected channel
 */
#define SAR_ADC_STS_ANALOG_WDGJ_INTF_POS         (30)
#define SAR_ADC_STS_ANALOG_WDGJ_INTF_MSK         (0x1UL << SAR_ADC_STS_ANALOG_WDGJ_INTF_POS)
#define SAR_ADC_STS_ANALOG_WDGJ_INT_FLAG         (0x1UL << SAR_ADC_STS_ANALOG_WDGJ_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[29] - Analog watch-dog interrupt flag on regular channel
 */
#define SAR_ADC_STS_ANALOG_WDGR_INTF_POS         (29)
#define SAR_ADC_STS_ANALOG_WDGR_INTF_MSK         (0x1UL << SAR_ADC_STS_ANALOG_WDGR_INTF_POS)
#define SAR_ADC_STS_ANALOG_WDGR_INT_FLAG         (0x1UL << SAR_ADC_STS_ANALOG_WDGR_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[28] - Injected conversion interrupt flag of channel 3
 */
#define SAR_ADC_STS_INJ3_INTF_POS                (28)
#define SAR_ADC_STS_INJ3_INTF_MSK                (0x1UL << SAR_ADC_STS_INJ3_INTF_POS)
#define SAR_ADC_STS_INJ3_INT_FLAG                (0x1UL << SAR_ADC_STS_INJ3_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[27] - Injected conversion interrupt flag of channel 2
 */
#define SAR_ADC_STS_INJ2_INTF_POS                (27)
#define SAR_ADC_STS_INJ2_INTF_MSK                (0x1UL << SAR_ADC_STS_INJ2_INTF_POS)
#define SAR_ADC_STS_INJ2_INT_FLAG                (0x1UL << SAR_ADC_STS_INJ2_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[26] - Injected conversion interrupt flag of channel 1
 */
#define SAR_ADC_STS_INJ1_INTF_POS                (26)
#define SAR_ADC_STS_INJ1_INTF_MSK                (0x1UL << SAR_ADC_STS_INJ1_INTF_POS)
#define SAR_ADC_STS_INJ1_INT_FLAG                (0x1UL << SAR_ADC_STS_INJ1_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[25] - Injected conversion interrupt flag of channel 0
 */
#define SAR_ADC_STS_INJ0_INTF_POS                (25)
#define SAR_ADC_STS_INJ0_INTF_MSK                (0x1UL << SAR_ADC_STS_INJ0_INTF_POS)
#define SAR_ADC_STS_INJ0_INT_FLAG                (0x1UL << SAR_ADC_STS_INJ0_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[24] - Regular conversion interrupt flag
 */
#define SAR_ADC_STS_REG_MODE_INTF_POS            (24)
#define SAR_ADC_STS_REG_MODE_INTF_MSK            (0x1UL << SAR_ADC_STS_REG_MODE_INTF_POS)
#define SAR_ADC_STS_REG_MODE_INT_FLAG            (0x1UL << SAR_ADC_STS_REG_MODE_INTF_POS)

/*
 * Bit definition for SAR_ADC_STS[0] - ADC ready flag
 */
#define SAR_ADC_STS_ADC_RDY_POS                  (0)
#define SAR_ADC_STS_ADC_RDY_MSK                  (0x1UL << SAR_ADC_STS_ADC_RDY_POS)
#define SAR_ADC_STS_ADC_RDY_FLAG                 (0x1UL << SAR_ADC_STS_ADC_RDY_POS)

/*
 * Bit definition for SAR_ADC_SMP0[30:28] - Channel 7 sample time selection
 */
#define SAR_DC_SMP0_CH7_SMP_SEL_POS              (28)
#define SAR_ADC_SMP0_CH7_SMP_SEL_MSK             (0x7UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_64ADCCLK        (0x7UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_48ADCCLK        (0x6UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_32ADCCLK        (0x5UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_16ADCCLK        (0x4UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_8ADCCLK         (0x3UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_4ADCCLK         (0x2UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_2ADCCLK         (0x1UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH7_SMP_SEL_1ADCCLK         (0x0UL << SAR_DC_SMP0_CH7_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[26:24] - Channel 6 sample time selection
 */
#define SAR_ADC_SMP0_CH6_SMP_SEL_POS             (24)
#define SAR_ADC_SMP0_CH6_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH6_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH6_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[22:20] - Channel 5 sample time selection
 */
#define SAR_ADC_SMP0_CH5_SMP_SEL_POS            (20)
#define SAR_ADC_SMP0_CH5_SMP_SEL_MSK            (0x7UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_64ADCCLK       (0x7UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_48ADCCLK       (0x6UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_32ADCCLK       (0x5UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_16ADCCLK       (0x4UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_8ADCCLK        (0x3UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_4ADCCLK        (0x2UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_2ADCCLK        (0x1UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH5_SMP_SEL_1ADCCLK        (0x0UL << SAR_ADC_SMP0_CH5_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[18:16] - Channel 4 sample time selection
 */
#define SAR_ADC_SMP0_CH4_SMP_SEL_POS             (16)
#define SAR_ADC_SMP0_CH4_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH4_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH4_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[14:12] - Channel 3 sample time selection
 */
#define SAR_ADC_SMP0_CH3_SMP_SEL_POS             (12)
#define SAR_ADC_SMP0_CH3_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH3_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH3_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[10:8] - Channel 2 sample time selection
 */
#define SAR_ADC_SMP0_CH2_SMP_SEL_POS             (8)
#define SAR_ADC_SMP0_CH2_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH2_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH2_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[6:4] - Channel 1 sample time selection
 */
#define SAR_ADC_SMP0_CH1_SMP_SEL_POS             (4)
#define SAR_ADC_SMP0_CH1_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH1_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH1_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP0[2:0] - Channel 0 sample time selection
 */
#define SAR_ADC_SMP0_CH0_SMP_SEL_POS             (0)
#define SAR_ADC_SMP0_CH0_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)
#define SAR_ADC_SMP0_CH0_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP0_CH0_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP1[6:4] - Channel 9 sample time selection
 */
#define SAR_ADC_SMP1_CH9_SMP_SEL_POS             (4)
#define SAR_ADC_SMP1_CH9_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH9_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP1_CH9_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_SMP1[2:0] - Channel 8 sample time selection
 */
#define SAR_ADC_SMP1_CH8_SMP_SEL_POS             (0)
#define SAR_ADC_SMP1_CH8_SMP_SEL_MSK             (0x7UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_64ADCCLK        (0x7UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_48ADCCLK        (0x6UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_32ADCCLK        (0x5UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_16ADCCLK        (0x4UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_8ADCCLK         (0x3UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_4ADCCLK         (0x2UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_2ADCCLK         (0x1UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)
#define SAR_ADC_SMP1_CH8_SMP_SEL_1ADCCLK         (0x0UL << SAR_ADC_SMP1_CH8_SMP_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[31:28] - Regular sequence 7 selection
 */
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS           (28)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ7TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ7TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[27:24] - Regular sequence 6 selection
 */
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS           (24)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ6TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ6TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[23:20] - Regular sequence 5 selection
 */
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS           (20)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ5TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ5TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[19:16] - Regular sequence 4 selection
 */
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS           (16)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ4TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ4TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[15:12] - Regular sequence 3 selection
 */
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS           (12)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ3RD_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ3RD_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[11:8] - Regular sequence 2 selection
 */
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS           (8)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ2ND_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ2ND_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[7:4] - Regular sequence 1 selection
 */
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS           (4)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ1ST_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ1ST_SEL_POS)

/*
 * Bit definition for SAR_ADC_REG_SEQ[3:0] - Regular sequence 0 selection
 */
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS           (0)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_MSK           (0xFUL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_REG_SEQ_SEQ0TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_REG_SEQ_SEQ0TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_INJ_SEQ[15:12] - Injected sequence 3 selection
 */
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS           (12)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_MSK           (0xFUL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH9       (0x9UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH8       (0x8UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH7       (0x7UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH6       (0x6UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH5       (0x5UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH4       (0x4UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH3       (0x3UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH2       (0x2UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH1       (0x1UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ3RD_SEL_ADC_CH0       (0x0UL << SAR_ADC_INJ_SEQ_SEQ3RD_SEL_POS)

/*
 * Bit definition for SAR_ADC_INJ_SEQ[11:8] - Injected sequence 2 selection
 */
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS           (8)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_MSK           (0xFUL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH9       (0x9UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH8       (0x8UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH7       (0x7UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH6       (0x6UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH5       (0x5UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH4       (0x4UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH3       (0x3UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH2       (0x2UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH1       (0x1UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ2ND_SEL_ADC_CH0       (0x0UL << SAR_ADC_INJ_SEQ_SEQ2ND_SEL_POS)

/*
 * Bit definition for SAR_ADC_INJ_SEQ[7:4] - Injected sequence 1 selection
 */
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS           (4)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_MSK           (0xFUL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH9       (0x9UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH8       (0x8UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH7       (0x7UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH6       (0x6UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH5       (0x5UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH4       (0x4UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH3       (0x3UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH2       (0x2UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH1       (0x1UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ1ST_SEL_ADC_CH0       (0x0UL << SAR_ADC_INJ_SEQ_SEQ1ST_SEL_POS)

/*
 * Bit definition for SAR_ADC_INJ_SEQ[3:0] - Injected sequence 0 selection
 */
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS           (0)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_MSK           (0xFUL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH9       (0x9UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH8       (0x8UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH7       (0x7UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH6       (0x6UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH5       (0x5UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH4       (0x4UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH3       (0x3UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH2       (0x2UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH1       (0x1UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)
#define SAR_ADC_INJ_SEQ_SEQ0TH_SEL_ADC_CH0       (0x0UL << SAR_ADC_INJ_SEQ_SEQ0TH_SEL_POS)

/*
 * Bit definition for SAR_ADC_WDG_TH[27:16] - Analog watch-dog high threshold
 */
#define SAR_ADC_WDG_TH_HIGH_THRESHOLD_POS         (16)
#define SAR_ADC_WDG_TH_HIGH_THRESHOLD_MSK         (0xFFFUL << SAR_ADC_WDG_TH_HIGH_THRESHOLD_POS)

/*
 * Bit definition for SAR_ADC_WDG_TH[11:0] - Analog watch-dog low threshold
 */
#define SAR_ADC_WDG_TH_LOW_THRESHOLD_POS          (0)
#define SAR_ADC_WDG_TH_LOW_THRESHOLD_MSK          (0xFFFUL << SAR_ADC_WDG_TH_LOW_THRESHOLD_POS)


/*---------------------------------------------------------------------------------------
 * Delta-sigma ADC Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                            // Delta-sigma ADC Control Register
	__IO uint32_t AGC_CTRL0;  					           // AGC Control Register 0
	__IO uint32_t AGC_CTRL1;  					           // AGC Control Register 1
	__IO uint32_t MUTE_CTRL0; 					           // Auto-mute Control Register 0
	__IO uint32_t MUTE_CTRL1; 					           // Auto-mute Control Register 1
	__IO uint32_t RESERVED; 					             //
	__IO uint32_t STS;	 	                         // Delta-sigma ADC Status Register
	__IO uint32_t DATA;                            // Sigma-Delta ADC Data Register
	__IO uint32_t WAKEUP_CTRL0 ;                   // Sigma-Delta ADC Wakeup Control Register0
	__IO uint32_t WAKEUP_CTRL1 ;                   // Sigma-Delta ADC Wakeup Control Register1
} DS_ADC_TYPE_DEF;

/*
 * Bit definition for DS_ADC_CTRL[22:20] - Delta-Sigma ADC FIFO level
 */
#define DS_ADC_CTRL_FIFO_LVL_POS                 (20)
#define DS_ADC_CTRL_FIFO_LVL_MSK                 (0x7UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_7                   (0x7UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_6                   (0x6UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_5                   (0x5UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_4                   (0x4UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_3                   (0x3UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_2                   (0x2UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_1                   (0x1UL << DS_ADC_CTRL_FIFO_LVL_POS)
#define DS_ADC_CTRL_FIFO_LVL_0                   (0x0UL << DS_ADC_CTRL_FIFO_LVL_POS)

/*
 * Bit definition for DS_ADC_CTRL[18] - Delta-Sigma ADC interrupt enable
 */
#define DS_ADC_CTRL_INT_EN_POS                   (18)
#define DS_ADC_CTRL_INT_EN_MSK                   (0x1UL << DS_ADC_CTRL_INT_EN_POS)
#define DS_ADC_CTRL_INT_ENABLE                   (0x1UL << DS_ADC_CTRL_INT_EN_POS)
#define DS_ADC_CTRL_INT_DISBLE                   (0x0UL << DS_ADC_CTRL_INT_EN_POS)

/*
 * Bit definition for DS_ADC_CTRL[17] - Delta-Sigma ADC FIFO overwrite enable
 */
#define DS_ADC_CTRL_FIFO_OVWR_EN_POS             (17)
#define DS_ADC_CTRL_FIFO_OVWR_EN_MSK             (0x1UL << DS_ADC_CTRL_FIFO_OVWR_EN_POS)
#define DS_ADC_CTRL_FIFO_OVWR_ENABLE             (0x1UL << DS_ADC_CTRL_FIFO_OVWR_EN_POS)
#define DS_ADC_CTRL_FIFO_OVWR_DISABLE            (0x0UL << DS_ADC_CTRL_FIFO_OVWR_EN_POS)

/*
 * Bit definition for DS_ADC_CTRL[16] - Delta-Sigma ADC FIFO enable
 */
#define DS_ADC_CTRL_FIFO_EN_POS                  (16)
#define DS_ADC_CTRL_FIFO_EN_MSK                  (0x1UL << DS_ADC_CTRL_FIFO_EN_POS)
#define DS_ADC_CTRL_FIFO_ENABLE                  (0x1UL << DS_ADC_CTRL_FIFO_EN_POS)
#define DS_ADC_CTRL_FIFO_DISABLE                 (0x0UL << DS_ADC_CTRL_FIFO_EN_POS)

/*
 * Bit definition for DS_ADC_CTRL[15] - Sigma-Delta ADC Output Data signed/unsigned select
 */
#define DS_ADC_CTRL_FMT_SEL_POS                  (15)
#define DS_ADC_CTRL_FMT_SEL_MSK                  (0x1UL << DS_ADC_CTRL_FMT_SEL_POS)
#define DS_ADC_CTRL_FMT_SEL_SIGN                 (0x1UL << DS_ADC_CTRL_FMT_SEL_POS)
#define DS_ADC_CTRL_FMT_SEL_UNSIGN               (0x0UL << DS_ADC_CTRL_FMT_SEL_POS)

/*
 * Bit definition for DS_ADC_CTRL[12:8] - PGA gain
 */
#define DS_ADC_CTRL_PGA_GAIN_POS                 (8)
#define DS_ADC_CTRL_PGA_GAIN_MSK                 (0x1FUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV0                 (0x1FUL << DS_ADC_CTRL_PGA_GAIN_POS)    // Min. Gain
#define DS_ADC_CTRL_PGA_GAIN_LV1                 (0x1EUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV2                 (0x1DUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV3                 (0x1CUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV4                 (0x1BUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV5                 (0x1AUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV6                 (0x19UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV7                 (0x18UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV8                 (0x17UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV9                 (0x16UL << DS_ADC_CTRL_PGA_GAIN_POS)    // 0db
#define DS_ADC_CTRL_PGA_GAIN_LV10                (0x15UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV11                (0x14UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV12                (0x13UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV13                (0x12UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV14                (0x11UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV15                (0x10UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV16                (0x0FUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV17                (0x0EUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV18                (0x0DUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV19                (0x0CUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV20                (0x0BUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV21                (0x0AUL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV22                (0x09UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV23                (0x08UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV24                (0x07UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV25                (0x06UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV26                (0x05UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV27                (0x04UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV28                (0x03UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV29                (0x02UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV30                (0x01UL << DS_ADC_CTRL_PGA_GAIN_POS)
#define DS_ADC_CTRL_PGA_GAIN_LV31                (0x00UL << DS_ADC_CTRL_PGA_GAIN_POS)    // Max. Gain

/*
 * Bit definition for DS_ADC_CTRL[7:6] - Delta-Sigma ADC input limist range
 */
#define DS_ADC_CTRL_IN_LIMIT_POS                 (6)
#define DS_ADC_CTRL_IN_LIMIT_MSK                 (0x3UL << DS_ADC_CTRL_IN_LIMIT_POS)
#define DS_ADC_CTRL_IN_LIMIT_0P5FULL             (0x3UL << DS_ADC_CTRL_IN_LIMIT_POS)
#define DS_ADC_CTRL_IN_LIMIT_0P6FULL             (0x2UL << DS_ADC_CTRL_IN_LIMIT_POS)
#define DS_ADC_CTRL_IN_LIMIT_0P71FULL            (0x1UL << DS_ADC_CTRL_IN_LIMIT_POS)
#define DS_ADC_CTRL_IN_LIMIT_O084FULL            (0x0UL << DS_ADC_CTRL_IN_LIMIT_POS)

/*
 * Bit definition for DS_ADC_CTRL[5:4] - Delta-Sigma ADC boost gain
 */
#define DS_ADC_CTRL_BOOST_GAIN_POS               (4)
#define DS_ADC_CTRL_BOOST_GAIN_MSK               (0x3UL << DS_ADC_CTRL_BOOST_GAIN_POS)
#define DS_ADC_CTRL_BOOST_GAIN_LV3               (0x3UL << DS_ADC_CTRL_BOOST_GAIN_POS)
#define DS_ADC_CTRL_BOOST_GAIN_LV2               (0x2UL << DS_ADC_CTRL_BOOST_GAIN_POS)
#define DS_ADC_CTRL_BOOST_GAIN_LV1               (0x1UL << DS_ADC_CTRL_BOOST_GAIN_POS)
#define DS_ADC_CTRL_BOOST_GAIN_LV0               (0x0UL << DS_ADC_CTRL_BOOST_GAIN_POS)

/*
 * Bit definition for DS_ADC_CTRL[3] - Delta-Sigma ADC enable
 */
#define DS_ADC_CTRL_DSADC_EN_POS                 (3)
#define DS_ADC_CTRL_DSADC_EN_MSK                 (0x1UL << DS_ADC_CTRL_DSADC_EN_POS)
#define DS_ADC_CTRL_DSADC_ENABLE                 (0x1UL << DS_ADC_CTRL_DSADC_EN_POS)
#define DS_ADC_CTRL_DSADC_DISABLE                (0x0UL << DS_ADC_CTRL_DSADC_EN_POS)

/*
 * Bit definition for DS_ADC_CTRL[2] - Delta-Sigma ADC reset
 */
#define DS_ADC_CTRL_DSADC_RST_POS                (2)
#define DS_ADC_CTRL_DSADC_RST_MSK                (0x1UL << DS_ADC_CTRL_DSADC_RST_POS)
#define DS_ADC_CTRL_DSADC_NORMAL                 (0x1UL << DS_ADC_CTRL_DSADC_RST_POS)
#define DS_ADC_CTRL_DSADC_RESET                  (0x0UL << DS_ADC_CTRL_DSADC_RST_POS)

/*
 * Bit definition for DS_ADC_CTRL[1] - High pass filter enable
 */
#define DS_ADC_CTRL_HPF_EN_POS                   (1)
#define DS_ADC_CTRL_HPF_EN_MSK                   (0x1UL << DS_ADC_CTRL_HPF_EN_POS)
#define DS_ADC_CTRL_HPF_ENABLE                   (0x1UL << DS_ADC_CTRL_HPF_EN_POS)
#define DS_ADC_CTRL_HPF_DISABLE                  (0x0UL << DS_ADC_CTRL_HPF_EN_POS)

/*
 * Bit definition for DS_ADC_CTRL[0] - Mic enable
 */
#define DS_ADC_CTRL_MIC_EN_POS                   (0)
#define DS_ADC_CTRL_MIC_EN_MSK                   (0x1UL << DS_ADC_CTRL_MIC_EN_POS)
#define DS_ADC_CTRL_MIC_ENABLE                   (0x1UL << DS_ADC_CTRL_MIC_EN_POS)
#define DS_ADC_CTRL_MIC_DISABLE                  (0x0UL << DS_ADC_CTRL_MIC_EN_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL0[30:16] - Toggle Threshold
 */
#define DS_ADC_AGC_CTRL0_TOGGLE_THRESHOLD_POS    (16)
#define DS_ADC_AGC_CTRL0_TOGGLE_THRESHOLD_MSK    (0x7FFFUL << DS_ADC_AGC_CTRL0_TOGGLE_THRESHOLD_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL0[14:8] - Threshold
 */
#define DS_ADC_AGC_CTRL0_THRESHOLD_POS           (8)
#define DS_ADC_AGC_CTRL0_THRESHOLD_MSK           (0x7FUL << DS_ADC_AGC_CTRL0_THRESHOLD_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL0[2] - Digital AGC enable
 */
#define DS_ADC_AGC_CTRL0_DAGC_EN_POS             (2)
#define DS_ADC_AGC_CTRL0_DAGC_EN_MSK             (0x1UL << DS_ADC_AGC_CTRL0_DAGC_EN_POS)
#define DS_ADC_AGC_CTRL0_DAGC_ENABLE             (0x1UL << DS_ADC_AGC_CTRL0_DAGC_EN_POS)
#define DS_ADC_AGC_CTRL0_DAGC_DISABLE            (0x0UL << DS_ADC_AGC_CTRL0_DAGC_EN_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL0[1] - Zero Cross Function of Compressor Control
 */
#define DS_ADC_AGC_CTRL0_ZERO_CROSS_POS          (1)
#define DS_ADC_AGC_CTRL0_ZERO_CROSS_MSK          (0x1UL << DS_ADC_AGC_CTRL0_ZERO_CROSS_POS)
#define DS_ADC_AGC_CTRL0_ZERO_CROSS_DISABLE      (0x1UL << DS_ADC_AGC_CTRL0_ZERO_CROSS_POS)
#define DS_ADC_AGC_CTRL0_ZERO_CROSS_ENABLE       (0x0UL << DS_ADC_AGC_CTRL0_ZERO_CROSS_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL0[0] - AGC Mode Control
 */
#define DS_ADC_AGC_CTRL0_MODE_SEL_POS            (0)
#define DS_ADC_AGC_CTRL0_MODE_SEL_MSK            (0x1UL << DS_ADC_AGC_CTRL0_MODE_SEL_POS)
#define DS_ADC_AGC_CTRL0_MODE_SEL_PEAK           (0x1UL << DS_ADC_AGC_CTRL0_MODE_SEL_POS)
#define DS_ADC_AGC_CTRL0_MODE_SEL_RMS            (0x0UL << DS_ADC_AGC_CTRL0_MODE_SEL_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL1[31:20] - Update frequence
 */
#define DS_ADC_AGC_CTRL1_UPDATE_FREQ_POS         (20)
#define DS_ADC_AGC_CTRL1_UPDATE_FREQ_MSK         (0xFFFUL << DS_ADC_AGC_CTRL1_UPDATE_FREQ_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL1[19:18] - Release time scale control
 */
#define DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS       (18)
#define DS_ADC_AGC_CTRL1_RELEASE_SCALE_MSK       (0x3UL << DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS)
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_X64        (0x3UL << DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS)
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_X16        (0x2UL << DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS)
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_X4         (0x1UL << DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS)
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_X1         (0x0UL << DS_ADC_AGC_CTRL1_RELEASE_SCALE_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL1[17:10] - Release time
 */
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_POS        (10)
#define DS_ADC_AGC_CTRL1_RELEASE_TIME_MSK        (0xFFUL << DS_ADC_AGC_CTRL1_RELEASE_TIME_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL1[9:8] - Attack time scale control
 */
#define DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS        (8)
#define DS_ADC_AGC_CTRL1_ATTACK_SCALE_MSK        (0x3UL << DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS)
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_X64         (0x3UL << DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS)
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_X16         (0x2UL << DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS)
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_X4          (0x1UL << DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS)
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_X1          (0x0UL << DS_ADC_AGC_CTRL1_ATTACK_SCALE_POS)

/*
 * Bit definition for DS_ADC_AGC_CTRL1[7:0] - Attack time
 */
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_POS         (0)
#define DS_ADC_AGC_CTRL1_ATTACK_TIME_MSK         (0xFFUL << DS_ADC_AGC_CTRL1_ATTACK_TIME_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL0[31:16] - Silence Threshold
 */
#define DS_ADC_MUTE_CTRL0_SILENCE_TH_POS         (16)
#define DS_ADC_MUTE_CTRL0_SILENCE_TH_MSK         (0xFFFFUL << DS_ADC_MUTE_CTRL0_SILENCE_TH_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL0[4] - Echo canceling control bit
 */
#define DS_ADC_MUTE_CTRL0_ECHO_CANCEL_EN_POS     (4)
#define DS_ADC_MUTE_CTRL0_ECHO_CANCEL_EN_MSK     (0x1UL << DS_ADC_MUTE_CTRL0_ECHO_CANCEL_EN_POS)
#define DS_ADC_MUTE_CTRL0_ECHO_CANCEL_ENABLE     (0x1UL << DS_ADC_MUTE_CTRL0_ECHO_CANCEL_EN_POS)
#define DS_ADC_MUTE_CTRL0_ECHO_CANCEL_DISABLE    (0x0UL << DS_ADC_MUTE_CTRL0_ECHO_CANCEL_EN_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL0[3:2] - Ramp counter step
 */
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS       (2)
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_MSK       (0x3UL << DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS)
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_3         (0x3UL << DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS)
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_2         (0x2UL << DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS)
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_1         (0x1UL << DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS)
#define DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_0         (0x0UL << DS_ADC_MUTE_CTRL0_RAMPCNT_STEP_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL0[1] - MIC AGC signed/unsigned data select
 */
#define DS_ADC_MUTE_CTRL0_FMT_SEL_POS            (1)
#define DS_ADC_MUTE_CTRL0_FMT_SEL_MSK            (0x1UL << DS_ADC_MUTE_CTRL0_FMT_SEL_POS)
#define DS_ADC_MUTE_CTRL0_FMT_SEL_SIGN           (0x1UL << DS_ADC_MUTE_CTRL0_FMT_SEL_POS)
#define DS_ADC_MUTE_CTRL0_FMT_SEL_UNSIGN         (0x1UL << DS_ADC_MUTE_CTRL0_FMT_SEL_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL0[0] - MIC auto mute enable
 */
#define DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_EN_POS    (0)
#define DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_EN_MSK    (0x1UL << DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_EN_POS)
#define DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_ENABLE    (0x1UL << DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_EN_POS)
#define DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_DISABLE   (0x0UL << DS_ADC_MUTE_CTRL0_MIC_AUTOMUTE_EN_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL1[31:16] - Normal debounce
 */
#define DS_ADC_MUTE_CTRL1_NORMAL_DEBOUNCE_POS    (16)
#define DS_ADC_MUTE_CTRL1_NORMAL_DEBOUNCE_MSK    (0xFFFFUL << DS_ADC_MUTE_CTRL1_NORMAL_DEBOUNCE_POS)

/*
 * Bit definition for DS_ADC_MUTE_CTRL1[15:0] - Silence debounce
 */
#define DS_ADC_MUTE_CTRL1_SILENCE_DEBOUNCE_POS   (0)
#define DS_ADC_MUTE_CTRL1_SILENCE_DEBOUNCE_MSK   (0xFFFFUL << DS_ADC_MUTE_CTRL1_SILENCE_DEBOUNCE_POS)

/*
 * Bit definition for DS_ADC_STS[19] - Delta-Sigma ADC FIFO full flag
 */
#define DS_ADC_STS_FIFO_FULL_POS                 (19)
#define DS_ADC_STS_FIFO_FULL_MSK                 (0x1UL << DS_ADC_STS_FIFO_FULL_POS)
#define DS_ADC_STS_FIFO_FULL_FLAG                (0x1UL << DS_ADC_STS_FIFO_FULL_POS)

/*
 * Bit definition for DS_ADC_STS[18] - Delta-Sigma ADC interrupt flag
 */
#define DS_ADC_STS_INTF_POS                      (18)
#define DS_ADC_STS_INTF_MSK                      (0x1UL << DS_ADC_STS_INTF_POS)
#define DS_ADC_STS_INT_FLAG                      (0x1UL << DS_ADC_STS_INTF_POS)

/*
 * Bit definition for DS_ADC_STS[12:8] - Actually PGAG gain value
 */
#define DS_ADC_STS_CURPGA_GAIN_POS               (8)
#define DS_ADC_STS_CURPGA_GAIN_MSK               (0x1FUL << DS_ADC_STS_CURPGA_GAIN_POS)


/*---------------------------------------------------------------------------------------
 * DAC Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
  __IO uint32_t CTRL;                       // DAC Control Register
  __IO uint32_t STS;    					          // DAC Status Register
	__I  uint32_t RESERVED1;  		            // Reserved
	__IO uint32_t AUDPWM_CTRL;                // AUDIO PWM Control Register
  __IO uint32_t DAC_CH0_DATA;	  					  // DAC Channel0 Input Data
  __IO uint32_t DAC_CH1_DATA;	  					  // DAC Channel1 Input Data
	__IO uint32_t MIX_DATA_OUT;	  					  // DAC Mixed Output Data
	__I  uint32_t RESERVED2;  		            // Reserved
	__IO uint32_t DAC_CH0_DMA_DATA0;	  			// DAC Channel0 DMA fifo data0
	__IO uint32_t DAC_CH0_DMA_DATA1;	  			// DAC Channel0 DMA fifo data1
	__I  uint32_t RESERVED3[2];	              // Reserved
  __IO uint32_t DAC_CH1_DMA_DATA0; 					// DAC Channel1 DMA fifo data0
	__IO uint32_t DAC_CH1_DMA_DATA1; 					// DAC Channel1 DMA fifo data1
} DAC_TYPE_DEF;

/*
 * Bit definition for DAC_CTRL[31] - DAC Channel1 DMA fifo Error interrupt enable
 */
#define DAC_CTRL_DAC_CH1_DMAERR_INT_EN_POS  (31)
#define DAC_CTRL_DAC_CH1_DMAERR_INT_EN_MSK  (0x1UL << DAC_CTRL_DAC_CH1_DMAERR_INT_EN_POS)
#define DAC_CTRL_DAC_CH1_DMAERR_INT_ENABLE  (0x1UL << DAC_CTRL_DAC_CH1_DMAERR_INT_EN_POS)
#define DAC_CTRL_DAC_CH1_DMAERR_INT_DISABLE (0x0UL << DAC_CTRL_DAC_CH1_DMAERR_INT_EN_POS)

/*
 * Bit definition for DAC_CTRL[30] - DAC Channel0 DMA fifo Error interrupt enable
 */
#define DAC_CTRL_DAC_CH0_DMAERR_INT_EN_POS  (30)
#define DAC_CTRL_DAC_CH0_DMAERR_INT_EN_MSK  (0x1UL << DAC_CTRL_DAC_CH0_DMAERR_INT_EN_POS)
#define DAC_CTRL_DAC_CH0_DMAERR_INT_ENABLE  (0x1UL << DAC_CTRL_DAC_CH0_DMAERR_INT_EN_POS)
#define DAC_CTRL_DAC_CH0_DMAERR_INT_DISABLE (0x0UL << DAC_CTRL_DAC_CH0_DMAERR_INT_EN_POS)

/*
 * Bit definition for DAC_CTRL[29] - DAC Channel1 interrupt enable
 */
#define DAC_CTRL_DAC_CH1_INT_EN_POS         (29)
#define DAC_CTRL_DAC_CH1_INT_EN_MSK         (0x1UL << DAC_CTRL_DAC_CH1_INT_EN_POS)
#define DAC_CTRL_DAC_CH1_INT_ENABLE         (0x1UL << DAC_CTRL_DAC_CH1_INT_EN_POS)
#define DAC_CTRL_DAC_CH1_INT_DISABLE        (0x0UL << DAC_CTRL_DAC_CH1_INT_EN_POS)

/*
 * Bit definition for DAC_CTRL[28] - DAC Channel0 interrupt enable
 */
#define DAC_CTRL_DAC_CH0_INT_EN_POS         (28)
#define DAC_CTRL_DAC_CH0_INT_EN_MSK         (0x1UL << DAC_CTRL_DAC_CH0_INT_EN_POS)
#define DAC_CTRL_DAC_CH0_INT_ENABLE         (0x1UL << DAC_CTRL_DAC_CH0_INT_EN_POS)
#define DAC_CTRL_DAC_CH0_INT_DISABLE        (0x0UL << DAC_CTRL_DAC_CH0_INT_EN_POS)

/*
 * Bit definition for DAC_CTRL[25] - Up sample function Software reset
 */
#define DAC_CTRL_UPSMP_SW_RST_POS           (25)
#define DAC_CTRL_UPSMP_SW_RST_MSK           (0x1UL << DAC_CTRL_UPSMP_SW_RST_POS)
#define DAC_CTRL_UPSMP_SW_RESET             (0x1UL << DAC_CTRL_UPSMP_SW_RST_POS)

/*
 * Bit definition for DAC_CTRL[24] - DAC software reset
 */
#define DAC_CTRL_DAC_SW_RST_POS             (24)
#define DAC_CTRL_DAC_SW_RST_MSK             (0x1UL << DAC_CTRL_DAC_SW_RST_POS)
#define DAC_CTRL_DAC_SW_RESET               (0x1UL << DAC_CTRL_DAC_SW_RST_POS)

/*
 * Bit definition for DAC_CTRL[23] - Current DAC IP enable
 */
#define DAC_CTRL_CURRENT_DAC_EN_POS         (23)
#define DAC_CTRL_CURRENT_DAC_EN_MSK         (0x1UL << DAC_CTRL_CURRENT_DAC_EN_POS)
#define DAC_CTRL_CURRENT_DAC_ENABLE         (0x1UL << DAC_CTRL_CURRENT_DAC_EN_POS)
#define DAC_CTRL_CURRENT_DAC_DISABLE        (0x0UL << DAC_CTRL_CURRENT_DAC_EN_POS)

/*
 * Bit definition for DAC_CTRL[21] - DAC output data signed/unsigned select
 */
#define DAC_CTRL_DACOUT_FMT_SEL_POS         (21)
#define DAC_CTRL_DACOUT_FMT_SEL_MSK         (0x1UL << DAC_CTRL_DACOUT_FMT_SEL_POS)
#define DAC_CTRL_DACOUT_FMT_SEL_SIGN        (0x1UL << DAC_CTRL_DACOUT_FMT_SEL_POS)
#define DAC_CTRL_DACOUT_FMT_SEL_UNSIGN      (0x0UL << DAC_CTRL_DACOUT_FMT_SEL_POS)

/*
 * Bit definition for DAC_CTRL[20] - DAC input data signed/unsigned select
 */
#define DAC_CTRL_DACIN_FMT_SEL_POS          (20)
#define DAC_CTRL_DACIN_FMT_SEL_MSK          (0x1UL << DAC_CTRL_DACIN_FMT_SEL_POS)
#define DAC_CTRL_DACIN_FMT_SEL_UNSIGN       (0x1UL << DAC_CTRL_DACIN_FMT_SEL_POS)
#define DAC_CTRL_DACIN_FMT_SEL_SIGN         (0x0UL << DAC_CTRL_DACIN_FMT_SEL_POS)

/*
 * Bit definition for DAC_CTRL[16] - DAC scale enable
 */
#define DAC_CTRL_SCALE_EN_POS               (16)
#define DAC_CTRL_SCALE_EN_MSK               (0x1UL << DAC_CTRL_SCALE_EN_POS)
#define DAC_CTRL_SCALE_ENABLE               (0x1UL << DAC_CTRL_SCALE_EN_POS)
#define DAC_CTRL_SCALE_DISABLE              (0x0UL << DAC_CTRL_SCALE_EN_POS)

/*
 * Bit definition for DAC_CTRL[15] - DAC Channel1 half volume enable
 */
#define DAC_CTRL_DAC_CH1_HALF_EN_POS        (15)
#define DAC_CTRL_DAC_CH1_HALF_EN_MSK        (0x1UL << DAC_CTRL_DAC_CH1_HALF_EN_POS)
#define DAC_CTRL_DAC_CH1_HALF_ENABLE        (0x1UL << DAC_CTRL_DAC_CH1_HALF_EN_POS)
#define DAC_CTRL_DAC_CH1_HALF_DISABLE       (0x0UL << DAC_CTRL_DAC_CH1_HALF_EN_POS)

/*
 * Bit definition for DAC_CTRL[14:12] - DAC channel1 Trigger source selection
 */
#define DAC_CTRL_DAC_CH1_TRG_SEL_POS        (12)
#define DAC_CTRL_DAC_CH1_TRG_SEL_MSK        (0x7UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_CTS_TM1    (0x7UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_CTS_TM0    (0x6UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_CCP1_TM    (0x5UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_CCP0_TM    (0x4UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_TM2        (0x3UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_TM1        (0x2UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_TM0        (0x1UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH1_TRG_SEL_Manual     (0x0UL << DAC_CTRL_DAC_CH1_TRG_SEL_POS)

/*
 * Bit definition for DAC_CTRL[11:10] - DAC channel1 UpSampling selection
 */
#define DAC_CTRL_DAC_CH1_UPSMP_MODE_POS     (10)
#define DAC_CTRL_DAC_CH1_UPSMP_MODE_MSK     (0x3UL << DAC_CTRL_DAC_CH1_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH1_UPSMP_MODE_4X      (0x2UL << DAC_CTRL_DAC_CH1_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH1_UPSMP_MODE_1X      (0x1UL << DAC_CTRL_DAC_CH1_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH1_UPSMP_MODE_DISABLE (0x0UL << DAC_CTRL_DAC_CH1_UPSMP_MODE_POS)

/*
 * Bit definition for DAC_CTRL[9] - DAC Channel1 DMA enable
 */
#define DAC_CTRL_DAC_CH1_DMA_EN_POS         (9)
#define DAC_CTRL_DAC_CH1_DMA_EN_MSK         (0x1UL << DAC_CTRL_DAC_CH1_DMA_EN_POS)
#define DAC_CTRL_DAC_CH1_DMA_ENABLE         (0x1UL << DAC_CTRL_DAC_CH1_DMA_EN_POS)
#define DAC_CTRL_DAC_CH1_DMA_DISABLE        (0x0UL << DAC_CTRL_DAC_CH1_DMA_EN_POS)

/*
 * Bit definition for DAC_CTRL[8] - DAC channel1 enable
 */
#define DAC_CTRL_DAC_CH1_EN_POS             (8)
#define DAC_CTRL_DAC_CH1_EN_MSK             (0x1UL << DAC_CTRL_DAC_CH1_EN_POS)
#define DAC_CTRL_DAC_CH1_ENABLE             (0x1UL << DAC_CTRL_DAC_CH1_EN_POS)
#define DAC_CTRL_DAC_CH1_DISABLE            (0x0UL << DAC_CTRL_DAC_CH1_EN_POS)

/*
 * Bit definition for DAC_CTRL[7] - DAC Channel0 half volume enable
 */
#define DAC_CTRL_DAC_CH0_HALF_EN_POS        (7)
#define DAC_CTRL_DAC_CH0_HALF_EN_MSK        (0x1UL << DAC_CTRL_DAC_CH0_HALF_EN_POS)
#define DAC_CTRL_DAC_CH0_HALF_ENABLE        (0x1UL << DAC_CTRL_DAC_CH0_HALF_EN_POS)
#define DAC_CTRL_DAC_CH0_HALF_DISABLE       (0x0UL << DAC_CTRL_DAC_CH0_HALF_EN_POS)

/*
 * Bit definition for DAC_CTRL[6:4] - DAC channel0 Trigger source selection
 */
#define DAC_CTRL_DAC_CH0_TRG_SEL_POS        (4)
#define DAC_CTRL_DAC_CH0_TRG_SEL_MSK        (0x7UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_CTS_TM1    (0x7UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_CTS_TM0    (0x6UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_CCP1_TM    (0x5UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_CCP0_TM    (0x4UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_TM2        (0x3UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_TM1        (0x2UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_TM0        (0x1UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)
#define DAC_CTRL_DAC_CH0_TRG_SEL_MANUAL     (0x0UL << DAC_CTRL_DAC_CH0_TRG_SEL_POS)

/*
 * Bit definition for DAC_CTRL[3:2] - DAC channel0 UpSampling selection
 */
#define DAC_CTRL_DAC_CH0_UPSMP_MODE_POS     (2)
#define DAC_CTRL_DAC_CH0_UPSMP_MODE_MSK     (0x3UL << DAC_CTRL_DAC_CH0_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH0_UPSMP_MODE_4X      (0x2UL << DAC_CTRL_DAC_CH0_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH0_UPSMP_MODE_1X      (0x1UL << DAC_CTRL_DAC_CH0_UPSMP_MODE_POS)
#define DAC_CTRL_DAC_CH0_UPSMP_MODE_DISABLE (0x0UL << DAC_CTRL_DAC_CH0_UPSMP_MODE_POS)

/*
 * Bit definition for DAC_CTRL[1] - DAC Channel0 DMA enable
 */
#define DAC_CTRL_DAC_CH0_DMA_EN_POS         (1)
#define DAC_CTRL_DAC_CH0_DMA_EN_MSK         (0x1UL << DAC_CTRL_DAC_CH0_DMA_EN_POS)
#define DAC_CTRL_DAC_CH0_DMA_ENABLE         (0x1UL << DAC_CTRL_DAC_CH0_DMA_EN_POS)
#define DAC_CTRL_DAC_CH0_DMA_DISABLE        (0x0UL << DAC_CTRL_DAC_CH0_DMA_EN_POS)

/*
 * Bit definition for DAC_CTRL[0] - DAC channel0 enable
 */
#define DAC_CTRL_DAC_CH0_EN_POS             (0)
#define DAC_CTRL_DAC_CH0_EN_MSK             (0x1UL << DAC_CTRL_DAC_CH0_EN_POS)
#define DAC_CTRL_DAC_CH0_ENABLE             (0x1UL << DAC_CTRL_DAC_CH0_EN_POS)
#define DAC_CTRL_DAC_CH0_DISABLE            (0x0UL << DAC_CTRL_DAC_CH0_EN_POS)

/*
 * Bit definition for DAC_STS[31] - DAC Channel1 error flag
 */
#define DAC_STS_DAC_CH1_ERR_POS             (31)
#define DAC_STS_DAC_CH1_ERR_MSK             (0x1UL << DAC_STS_DAC_CH1_ERR_POS)
#define DAC_STS_DAC_CH1_ERR_FLAG            (0x1UL << DAC_STS_DAC_CH1_ERR_POS)

/*
 * Bit definition for DAC_STS[30] - DAC Channel0 error flag
 */
#define DAC_STS_DAC_CH0_ERR_POS             (30)
#define DAC_STS_DAC_CH0_ERR_MSK             (0x1UL << DAC_STS_DAC_CH0_ERR_POS)
#define DAC_STS_DAC_CH0_ERR_FLAG            (0x1UL << DAC_STS_DAC_CH0_ERR_POS)

/*
 * Bit definition for DAC_STS[29] - DAC Channel1 interrupt flag
 */
#define DAC_STS_DAC_CH1_INTF_POS            (29)
#define DAC_STS_DAC_CH1_INTF_MSK            (0x1UL << DAC_STS_DAC_CH1_INTF_POS)
#define DAC_STS_DAC_CH1_INT_FLAG            (0x1UL << DAC_STS_DAC_CH1_INTF_POS)

/*
 * Bit definition for DAC_STS[28] - DAC Channel0 interrupt flag
 */
#define DAC_STS_DAC_CH0_INTF_POS            (28)
#define DAC_STS_DAC_CH0_INTF_MSK            (0x1UL << DAC_STS_DAC_CH0_INTF_POS)
#define DAC_STS_DAC_CH0_INT_FLAG            (0x1UL << DAC_STS_DAC_CH0_INTF_POS)

/*
 * Bit definition for AUDPWM_CTRL[28] - Audio Flag
 */
#define AUDPWM_CTRL_AUD_DETECT_FLAG_POS     (28)
#define AUDPWM_CTRL_AUD_DETECT_FLAG_MSK     (0x1UL << AUDPWM_CTRL_AUD_DETECT_FLAG_POS)

/*
 * Bit definition for AUDPWM_CTRL[24] - Audio Detect
 */
#define AUDPWM_CTRL_AUD_DETECT_POS          (24)
#define AUDPWM_CTRL_AUD_DETECT_MSK          (0x1UL << AUDPWM_CTRL_AUD_DETECT_POS)
#define AUDPWM_CTRL_AUD_DETECT_START        (0x1UL << AUDPWM_CTRL_AUD_DETECT_POS)

/*
 * Bit definition for AUDPWM_CTRL[16] - PWM enable control
 */
#define AUDPWM_CTRL_AUDPWM_IP_EN_POS        (16)
#define AUDPWM_CTRL_AUDPWM_IP_EN_MSK        (0x1UL << AUDPWM_CTRL_AUDPWM_IP_EN_POS)
#define AUDPWM_CTRL_AUDPWM_IP_ENABLE        (0x1UL << AUDPWM_CTRL_AUDPWM_IP_EN_POS)
#define AUDPWM_CTRL_AUDPWM_IP_DISABLE       (0x0UL << AUDPWM_CTRL_AUDPWM_IP_EN_POS)

/*
 * Bit definition for AUDPWM_CTRL[11:10] - Audio PWM Clock mute state selection
 */
#define AUDPWM_CTRL_MUTE_STATE_SEL_POS      (10)
#define AUDPWM_CTRL_MUTE_STATE_SEL_MSK      (0x3UL << AUDPWM_CTRL_MUTE_STATE_SEL_POS)
#define AUDPWM_CTRL_MUTE_STATE_SEL_2MHZ     (0x3UL << AUDPWM_CTRL_MUTE_STATE_SEL_POS)
#define AUDPWM_CTRL_MUTE_STATE_SEL_4MHZ     (0x2UL << AUDPWM_CTRL_MUTE_STATE_SEL_POS)
#define AUDPWM_CTRL_MUTE_STATE_SEL_8MHZ     (0x1UL << AUDPWM_CTRL_MUTE_STATE_SEL_POS)
#define AUDPWM_CTRL_MUTE_STATE_SEL_16MHZ    (0x0UL << AUDPWM_CTRL_MUTE_STATE_SEL_POS)

/*
 * Bit definition for AUDPWM_CTRL[9:4] - Audio PWM Gain
 */
#define AUDPWM_CTRL_AUDPWM_GAIN_POS         (4)
#define AUDPWM_CTRL_AUDPWM_GAIN_MSK         (0x3FUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV63        (0x3FUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV62        (0x3EUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV61        (0x3DUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV60        (0x3CUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV59        (0x3BUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV58        (0x3AUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV57        (0x39UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV56        (0x38UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV55        (0x37UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV54        (0x36UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV53        (0x35UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV52        (0x34UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV51        (0x33UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV50        (0x32UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV49        (0x31UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV48        (0x30UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV47        (0x2FUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV46        (0x2EUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV45        (0x2DUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV44        (0x2CUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV43        (0x2BUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV42        (0x2AUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV41        (0x29UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV40        (0x28UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV39        (0x27UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV38        (0x26UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV37        (0x25UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV36        (0x24UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV35        (0x23UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV34        (0x22UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV33        (0x21UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV32        (0x20UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV31        (0x1FUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV30        (0x1EUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV29        (0x1DUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV28        (0x1CUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV27        (0x1BUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV26        (0x1AUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV25        (0x19UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV24        (0x18UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV23        (0x17UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV22        (0x16UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV21        (0x15UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV20        (0x14UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV19        (0x13UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV18        (0x12UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV17        (0x11UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV16        (0x10UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV15        (0xFUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV14        (0xEUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV13        (0xDUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV12        (0xCUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV11        (0xBUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV10        (0xAUL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV9         (0x9UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV8         (0x8UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV7         (0x7UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV6         (0x6UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV5         (0x5UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV4         (0x4UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV3         (0x3UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV2         (0x2UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV1         (0x1UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)
#define AUDPWM_CTRL_AUDPWM_GAIN_LV0         (0x0UL << AUDPWM_CTRL_AUDPWM_GAIN_POS)

/*
 * Bit definition for AUDPWM_CTRL[3:2] - Auto Mute control
 */
#define AUDPWM_CTRL_AUTOMUTE_SETTING_POS    (2)
#define AUDPWM_CTRL_AUTOMUTE_SETTING_MSK    (0x3UL << AUDPWM_CTRL_AUTOMUTE_SETTING_POS)
#define AUDPWM_CTRL_AUTOMUTE_OFF            (0x3UL << AUDPWM_CTRL_AUTOMUTE_SETTING_POS)
#define AUDPWM_CTRL_AUTOMUTE_DATAKEEP_16MS  (0x2UL << AUDPWM_CTRL_AUTOMUTE_SETTING_POS)
#define AUDPWM_CTRL_AUTOMUTE_DATAKEEP_2MS   (0x1UL << AUDPWM_CTRL_AUTOMUTE_SETTING_POS)
#define AUDPWM_CTRL_AUTOMUTE_ZERO           (0x0UL << AUDPWM_CTRL_AUTOMUTE_SETTING_POS)


/*
 * Bit definition for AUDPWM_CTRL[1] - Audio PWM input data signed/unsigned select
 */
#define AUDPWM_CTRL_DATAIN_FMT_SEL_POS      (1)
#define AUDPWM_CTRL_DATAIN_FMT_SEL_MSK      (0x1UL << AUDPWM_CTRL_DATAIN_FMT_SEL_POS)
#define AUDPWM_CTRL_DATAIN_FMT_SEL_UNSIGN   (0x1UL << AUDPWM_CTRL_DATAIN_FMT_SEL_POS)
#define AUDPWM_CTRL_DATAIN_FMT_SEL_SIGN     (0x0UL << AUDPWM_CTRL_DATAIN_FMT_SEL_POS)

/*
 * Bit definition for AUDPWM_CTRL[0] - Audio PWM enable
 */
#define AUDPWM_CTRL_AUDPWM_EN_POS           (0)
#define AUDPWM_CTRL_AUDPWM_EN_MSK           (0x1UL << AUDPWM_CTRL_AUDPWM_EN_POS)
#define AUDPWM_CTRL_AUDPWM_ENABLE           (0x1UL << AUDPWM_CTRL_AUDPWM_EN_POS)
#define AUDPWM_CTRL_AUDPWM_DISABLE          (0x0UL << AUDPWM_CTRL_AUDPWM_EN_POS)


/*---------------------------------------------------------------------------------------
 * PWMIO Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
 typedef struct
{
	__IO uint32_t CTRL0;							        // PWMIO Control0 Register
	__IO uint32_t CTRL1;							        // PWMIO Control1 Register
	__IO uint32_t TOGGLE_CTRL;							  // PWMIO Toggle Control Register
	__IO uint32_t PERIOD_CTRL;				        // PWMIO Period Control Register
	__IO uint32_t PWMIO0_Duty;							  // PWMIO0 Duty Control Register
	__IO uint32_t PWMIO1_Duty;							  // PWMIO1 Duty Control Register
	__IO uint32_t PWMIO2_Duty;							  // PWMIO2 Duty Control Register
	__IO uint32_t PWMIO3_Duty;							  // PWMIO3 Duty Control Register
	__IO uint32_t PWMIO4_Duty;							  // PWMIO4 Duty Control Register
	__IO uint32_t PWMIO5_Duty;							  // PWMIO5 Duty Control Register
	__IO uint32_t PWMIO6_Duty;							  // PWMIO6 Duty Control Register
	__IO uint32_t PWMIO7_Duty;							  // PWMIO7 Duty Control Register
} PWMIO_TYPE_DEF;

/*
 * Bit definition for PWMIO_CTRL0[8] - SYNC enable
 */
#define PWMIO_CTRL0_SYNC_EN_POS             (8)
#define PWMIO_CTRL0_SYNC_EN_MSK             (0x1UL << PWMIO_CTRL0_SYNC_EN_POS)
#define PWMIO_CTRL0_SYNC_ENABLE							(0x1UL << PWMIO_CTRL0_SYNC_EN_POS)
#define PWMIO_CTRL0_SYNC_DISABLE  					(0x0UL << PWMIO_CTRL0_SYNC_EN_POS)

/*
 * Bit definition for PWMIO_CTRL0[7:4] - Set the clock source of PWM I/O
 */
#define PWMIO_CTRL_CLK_SEL_POS              (4)
#define PWMIO_CTRL_CLK_SEL_MSK              (0xFUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_4096    (0xEUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_1024		(0xDUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_256     (0xCUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_64    	(0xBUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_32			(0xAUL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_16     	(0x9UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_FCPU_DIV_8      	(0x8UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_CCP1           	(0x5UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_CCP0          		(0x4UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_TIMER2           (0x3UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_TIMER1           (0x2UL << PWMIO_CTRL_CLK_SEL_POS)
#define PWMIO_CTRL_CLK_SEL_TIMER0           (0x1UL << PWMIO_CTRL_CLK_SEL_POS)

/*
 * Bit definition for PWMIO_CTRL1[23] - PWMIO channel 7 INV
 */
#define PWMIO_CTRL_PWM7_INV_POS            	(23)
#define PWMIO_CTRL_PWM7_INV_MSK             (0x1UL << PWMIO_CTRL_PWM7_INV_POS)
#define PWMIO_CTRL_PWM7_INV_ON							(0x1UL << PWMIO_CTRL_PWM7_INV_POS)
#define PWMIO_CTRL_PWM7_INV_OFF							(0x0UL << PWMIO_CTRL_PWM7_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[22] - PWMIO channel 6 INV
 */
#define PWMIO_CTRL_PWM6_INV_POS            	(22)
#define PWMIO_CTRL_PWM6_INV_MSK             (0x1UL << PWMIO_CTRL_PWM6_INV_POS)
#define PWMIO_CTRL_PWM6_INV_ON							(0x1UL << PWMIO_CTRL_PWM6_INV_POS)
#define PWMIO_CTRL_PWM6_INV_OFF							(0x0UL << PWMIO_CTRL_PWM6_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[21] - PWMIO channel 5 INV
 */
#define PWMIO_CTRL_PWM5_INV_POS            	(21)
#define PWMIO_CTRL_PWM5_INV_MSK             (0x1UL << PWMIO_CTRL_PWM5_INV_POS)
#define PWMIO_CTRL_PWM5_INV_ON							(0x1UL << PWMIO_CTRL_PWM5_INV_POS)
#define PWMIO_CTRL_PWM5_INV_OFF							(0x0UL << PWMIO_CTRL_PWM5_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[20] - PWMIO channel 4 INV
 */
#define PWMIO_CTRL_PWM4_INV_POS            	(20)
#define PWMIO_CTRL_PWM4_INV_MSK             (0x1UL << PWMIO_CTRL_PWM4_INV_POS)
#define PWMIO_CTRL_PWM4_INV_ON							(0x1UL << PWMIO_CTRL_PWM4_INV_POS)
#define PWMIO_CTRL_PWM4_INV_OFF							(0x0UL << PWMIO_CTRL_PWM4_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[19] - PWMIO channel 3 INV
 */
#define PWMIO_CTRL_PWM3_INV_POS            	(19)
#define PWMIO_CTRL_PWM3_INV_MSK             (0x1UL << PWMIO_CTRL_PWM3_INV_POS)
#define PWMIO_CTRL_PWM3_INV_ON							(0x1UL << PWMIO_CTRL_PWM3_INV_POS)
#define PWMIO_CTRL_PWM3_INV_OFF							(0x0UL << PWMIO_CTRL_PWM3_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[18] - PWMIO channel 2 INV
 */
#define PWMIO_CTRL_PWM2_INV_POS            	(18)
#define PWMIO_CTRL_PWM2_INV_MSK             (0x1UL << PWMIO_CTRL_PWM2_INV_POS)
#define PWMIO_CTRL_PWM2_INV_ON							(0x1UL << PWMIO_CTRL_PWM2_INV_POS)
#define PWMIO_CTRL_PWM2_INV_OFF							(0x0UL << PWMIO_CTRL_PWM2_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[17] - PWMIO channel 1 INV
 */
#define PWMIO_CTRL_PWM1_INV_POS            	(17)
#define PWMIO_CTRL_PWM1_INV_MSK             (0x1UL << PWMIO_CTRL_PWM1_INV_POS)
#define PWMIO_CTRL_PWM1_INV_ON							(0x1UL << PWMIO_CTRL_PWM1_INV_POS)
#define PWMIO_CTRL_PWM1_INV_OFF							(0x0UL << PWMIO_CTRL_PWM1_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[16] - PWMIO channel 0 INV
 */
#define PWMIO_CTRL_PWM0_INV_POS            	(16)
#define PWMIO_CTRL_PWM0_INV_MSK             (0x1UL << PWMIO_CTRL_PWM0_INV_POS)
#define PWMIO_CTRL_PWM0_INV_ON							(0x1UL << PWMIO_CTRL_PWM0_INV_POS)
#define PWMIO_CTRL_PWM0_INV_OFF							(0x0UL << PWMIO_CTRL_PWM0_INV_POS)

/*
 * Bit definition for PWMIO_CTRL1[15] - PWMIO channel 7 mask
 */
#define PWMIO_CTRL_PWM7_MSK_POS            	(15)
#define PWMIO_CTRL_PWM7_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM7_MSK_POS)
#define PWMIO_CTRL_PWM7_MSK_ON							(0x1UL << PWMIO_CTRL_PWM7_MSK_POS)
#define PWMIO_CTRL_PWM7_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM7_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[14] - PWMIO channel 6 mask
 */
#define PWMIO_CTRL_PWM6_MSK_POS            	(14)
#define PWMIO_CTRL_PWM6_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM6_MSK_POS)
#define PWMIO_CTRL_PWM6_MSK_ON							(0x1UL << PWMIO_CTRL_PWM6_MSK_POS)
#define PWMIO_CTRL_PWM6_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM6_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[13] - PWMIO channel 5 mask
 */
#define PWMIO_CTRL_PWM5_MSK_POS            	(13)
#define PWMIO_CTRL_PWM5_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM5_MSK_POS)
#define PWMIO_CTRL_PWM5_MSK_ON							(0x1UL << PWMIO_CTRL_PWM5_MSK_POS)
#define PWMIO_CTRL_PWM5_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM5_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[12] - PWMIO channel 4 mask
 */
#define PWMIO_CTRL_PWM4_MSK_POS            	(12)
#define PWMIO_CTRL_PWM4_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM4_MSK_POS)
#define PWMIO_CTRL_PWM4_MSK_ON							(0x1UL << PWMIO_CTRL_PWM4_MSK_POS)
#define PWMIO_CTRL_PWM4_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM4_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[11] - PWMIO channel 3 mask
 */
#define PWMIO_CTRL_PWM3_MSK_POS            	(11)
#define PWMIO_CTRL_PWM3_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM3_MSK_POS)
#define PWMIO_CTRL_PWM3_MSK_ON							(0x1UL << PWMIO_CTRL_PWM3_MSK_POS)
#define PWMIO_CTRL_PWM3_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM3_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[10] - PWMIO channel 2 mask
 */
#define PWMIO_CTRL_PWM2_MSK_POS            	(10)
#define PWMIO_CTRL_PWM2_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM2_MSK_POS)
#define PWMIO_CTRL_PWM2_MSK_ON							(0x1UL << PWMIO_CTRL_PWM2_MSK_POS)
#define PWMIO_CTRL_PWM2_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM2_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[9] - PWMIO channel 1 mask
 */
#define PWMIO_CTRL_PWM1_MSK_POS            	(9)
#define PWMIO_CTRL_PWM1_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM1_MSK_POS)
#define PWMIO_CTRL_PWM1_MSK_ON							(0x1UL << PWMIO_CTRL_PWM1_MSK_POS)
#define PWMIO_CTRL_PWM1_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM1_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[8] - PWMIO channel 0 mask
 */
#define PWMIO_CTRL_PWM0_MSK_POS            	(8)
#define PWMIO_CTRL_PWM0_MSK_MSK             (0x1UL << PWMIO_CTRL_PWM0_MSK_POS)
#define PWMIO_CTRL_PWM0_MSK_ON							(0x1UL << PWMIO_CTRL_PWM0_MSK_POS)
#define PWMIO_CTRL_PWM0_MSK_OFF							(0x0UL << PWMIO_CTRL_PWM0_MSK_POS)

/*
 * Bit definition for PWMIO_CTRL1[7] - PWMIO channel 7 enable
 */
#define PWMIO_CTRL_PWM7_EN_POS              (7)
#define PWMIO_CTRL_PWM7_EN_MSK              (0x1UL << PWMIO_CTRL_PWM7_EN_POS)
#define PWMIO_CTRL_PWM7_ENABLE              (0x1UL << PWMIO_CTRL_PWM7_EN_POS)
#define PWMIO_CTRL_PWM7_DISABLE             (0x0UL << PWMIO_CTRL_PWM7_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[6] - PWMIO channel 6 enable
 */
#define PWMIO_CTRL_PWM6_EN_POS              (6)
#define PWMIO_CTRL_PWM6_EN_MSK              (0x1UL << PWMIO_CTRL_PWM6_EN_POS)
#define PWMIO_CTRL_PWM6_ENABLE              (0x1UL << PWMIO_CTRL_PWM6_EN_POS)
#define PWMIO_CTRL_PWM6_DISABLE             (0x0UL << PWMIO_CTRL_PWM6_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[5] - PWMIO channel 5 enable
 */
#define PWMIO_CTRL_PWM5_EN_POS              (5)
#define PWMIO_CTRL_PWM5_EN_MSK              (0x1UL << PWMIO_CTRL_PWM5_EN_POS)
#define PWMIO_CTRL_PWM5_ENABLE              (0x1UL << PWMIO_CTRL_PWM5_EN_POS)
#define PWMIO_CTRL_PWM5_DISABLE             (0x0UL << PWMIO_CTRL_PWM5_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[4] - PWMIO channel 4 enable
 */
#define PWMIO_CTRL_PWM4_EN_POS              (4)
#define PWMIO_CTRL_PWM4_EN_MSK              (0x1UL << PWMIO_CTRL_PWM4_EN_POS)
#define PWMIO_CTRL_PWM4_ENABLE              (0x1UL << PWMIO_CTRL_PWM4_EN_POS)
#define PWMIO_CTRL_PWM4_DISABLE             (0x0UL << PWMIO_CTRL_PWM4_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[3] - PWMIO channel 3 enable
 */
#define PWMIO_CTRL_PWM3_EN_POS              (3)
#define PWMIO_CTRL_PWM3_EN_MSK              (0x1UL << PWMIO_CTRL_PWM3_EN_POS)
#define PWMIO_CTRL_PWM3_ENABLE              (0x1UL << PWMIO_CTRL_PWM3_EN_POS)
#define PWMIO_CTRL_PWM3_DISABLE             (0x0UL << PWMIO_CTRL_PWM3_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[2] - PWMIO channel 2 enable
 */
#define PWMIO_CTRL_PWM2_EN_POS              (2)
#define PWMIO_CTRL_PWM2_EN_MSK              (0x1UL << PWMIO_CTRL_PWM2_EN_POS)
#define PWMIO_CTRL_PWM2_ENABLE              (0x1UL << PWMIO_CTRL_PWM2_EN_POS)
#define PWMIO_CTRL_PWM2_DISABLE             (0x0UL << PWMIO_CTRL_PWM2_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[1] - PWMIO channel 1 enable
 */
#define PWMIO_CTRL_PWM1_EN_POS              (1)
#define PWMIO_CTRL_PWM1_EN_MSK              (0x1UL << PWMIO_CTRL_PWM1_EN_POS)
#define PWMIO_CTRL_PWM1_ENABLE              (0x1UL << PWMIO_CTRL_PWM1_EN_POS)
#define PWMIO_CTRL_PWM1_DISABLE             (0x0UL << PWMIO_CTRL_PWM1_EN_POS)

/*
 * Bit definition for PWMIO_CTRL1[0] - PWMIO channel 0 enable
 */
#define PWMIO_CTRL_PWM0_EN_POS              (0)
#define PWMIO_CTRL_PWM0_EN_MSK              (0x1UL << PWMIO_CTRL_PWM0_EN_POS)
#define PWMIO_CTRL_PWM0_ENABLE              (0x1UL << PWMIO_CTRL_PWM0_EN_POS)
#define PWMIO_CTRL_PWM0_DISABLE             (0x0UL << PWMIO_CTRL_PWM0_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[7] - PWMIO Channel 7 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE7_EN_POS           (7)
#define PWMIO_CTRL_TOGGLE7_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE7_EN_POS)
#define PWMIO_CTRL_TOGGLE7_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE7_EN_POS)
#define PWMIO_CTRL_TOGGLE7_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE7_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[6] - PWMIO Channel 6 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE6_EN_POS           (6)
#define PWMIO_CTRL_TOGGLE6_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE6_EN_POS)
#define PWMIO_CTRL_TOGGLE6_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE6_EN_POS)
#define PWMIO_CTRL_TOGGLE6_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE6_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[5] - PWMIO Channel 5 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE5_EN_POS           (5)
#define PWMIO_CTRL_TOGGLE5_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE5_EN_POS)
#define PWMIO_CTRL_TOGGLE5_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE5_EN_POS)
#define PWMIO_CTRL_TOGGLE5_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE5_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[4] - PWMIO Channel 4 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE4_EN_POS           (4)
#define PWMIO_CTRL_TOGGLE4_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE4_EN_POS)
#define PWMIO_CTRL_TOGGLE4_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE4_EN_POS)
#define PWMIO_CTRL_TOGGLE4_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE4_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[3] - PWMIO Channel 3 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE3_EN_POS           (3)
#define PWMIO_CTRL_TOGGLE3_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE3_EN_POS)
#define PWMIO_CTRL_TOGGLE3_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE3_EN_POS)
#define PWMIO_CTRL_TOGGLE3_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE3_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[2] - PWMIO Channel 2 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE2_EN_POS           (2)
#define PWMIO_CTRL_TOGGLE2_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE2_EN_POS)
#define PWMIO_CTRL_TOGGLE2_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE2_EN_POS)
#define PWMIO_CTRL_TOGGLE2_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE2_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[1] - PWMIO Channel 1 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE1_EN_POS           (1)
#define PWMIO_CTRL_TOGGLE1_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE1_EN_POS)
#define PWMIO_CTRL_TOGGLE1_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE1_EN_POS)
#define PWMIO_CTRL_TOGGLE1_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE1_EN_POS)

/*
 * Bit definition for PWMIO_TOGGLE_CTRL[0] - PWMIO Channel 0 Toggle Control enable
 */
#define PWMIO_CTRL_TOGGLE0_EN_POS           (0)
#define PWMIO_CTRL_TOGGLE0_EN_MSK           (0x1UL << PWMIO_CTRL_TOGGLE0_EN_POS)
#define PWMIO_CTRL_TOGGLE0_ENABLE           (0x1UL << PWMIO_CTRL_TOGGLE0_EN_POS)
#define PWMIO_CTRL_TOGGLE0_DISABLE          (0x0UL << PWMIO_CTRL_TOGGLE0_EN_POS)


/*
 * Bit definition for PWMIO_PERIOD_CTRL[15:14] - PWMIO Period Control 7
 */
#define PWMIO_CTRL_PERIOD7_EN_POS           (14)
#define PWMIO_CTRL_PERIOD7_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD7_EN_POS)
#define PWMIO_CTRL_PERIOD7_32             	(0x3UL << PWMIO_CTRL_PERIOD7_EN_POS)
#define PWMIO_CTRL_PERIOD7_64             	(0x2UL << PWMIO_CTRL_PERIOD7_EN_POS)
#define PWMIO_CTRL_PERIOD7_128             	(0x1UL << PWMIO_CTRL_PERIOD7_EN_POS)
#define PWMIO_CTRL_PERIOD7_256             	(0x0UL << PWMIO_CTRL_PERIOD7_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[13:12] - PWMIO Period Control 6
 */
#define PWMIO_CTRL_PERIOD6_EN_POS           (12)
#define PWMIO_CTRL_PERIOD6_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD6_EN_POS)
#define PWMIO_CTRL_PERIOD6_32             	(0x3UL << PWMIO_CTRL_PERIOD6_EN_POS)
#define PWMIO_CTRL_PERIOD6_64             	(0x2UL << PWMIO_CTRL_PERIOD6_EN_POS)
#define PWMIO_CTRL_PERIOD6_128             	(0x1UL << PWMIO_CTRL_PERIOD6_EN_POS)
#define PWMIO_CTRL_PERIOD6_256             	(0x0UL << PWMIO_CTRL_PERIOD6_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[11:10] - PWMIO Period Control 5
 */
#define PWMIO_CTRL_PERIOD5_EN_POS           (10)
#define PWMIO_CTRL_PERIOD5_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD5_EN_POS)
#define PWMIO_CTRL_PERIOD5_32             	(0x3UL << PWMIO_CTRL_PERIOD5_EN_POS)
#define PWMIO_CTRL_PERIOD5_64             	(0x2UL << PWMIO_CTRL_PERIOD5_EN_POS)
#define PWMIO_CTRL_PERIOD5_128             	(0x1UL << PWMIO_CTRL_PERIOD5_EN_POS)
#define PWMIO_CTRL_PERIOD5_256             	(0x0UL << PWMIO_CTRL_PERIOD5_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[9:8] - PWMIO Period Control 4
 */
#define PWMIO_CTRL_PERIOD4_EN_POS           (8)
#define PWMIO_CTRL_PERIOD4_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD4_EN_POS)
#define PWMIO_CTRL_PERIOD4_32             	(0x3UL << PWMIO_CTRL_PERIOD4_EN_POS)
#define PWMIO_CTRL_PERIOD4_64             	(0x2UL << PWMIO_CTRL_PERIOD4_EN_POS)
#define PWMIO_CTRL_PERIOD4_128             	(0x1UL << PWMIO_CTRL_PERIOD4_EN_POS)
#define PWMIO_CTRL_PERIOD4_256             	(0x0UL << PWMIO_CTRL_PERIOD4_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[7:6] - PWMIO Period Control 3
 */
#define PWMIO_CTRL_PERIOD3_EN_POS           (6)
#define PWMIO_CTRL_PERIOD3_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD3_EN_POS)
#define PWMIO_CTRL_PERIOD3_32             	(0x3UL << PWMIO_CTRL_PERIOD3_EN_POS)
#define PWMIO_CTRL_PERIOD3_64             	(0x2UL << PWMIO_CTRL_PERIOD3_EN_POS)
#define PWMIO_CTRL_PERIOD3_128             	(0x1UL << PWMIO_CTRL_PERIOD3_EN_POS)
#define PWMIO_CTRL_PERIOD3_256             	(0x0UL << PWMIO_CTRL_PERIOD3_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[5:4] - PWMIO Period Control 2
 */
#define PWMIO_CTRL_PERIOD2_EN_POS           (4)
#define PWMIO_CTRL_PERIOD2_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD2_EN_POS)
#define PWMIO_CTRL_PERIOD2_32             	(0x3UL << PWMIO_CTRL_PERIOD2_EN_POS)
#define PWMIO_CTRL_PERIOD2_64             	(0x2UL << PWMIO_CTRL_PERIOD2_EN_POS)
#define PWMIO_CTRL_PERIOD2_128             	(0x1UL << PWMIO_CTRL_PERIOD2_EN_POS)
#define PWMIO_CTRL_PERIOD2_256             	(0x0UL << PWMIO_CTRL_PERIOD2_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[3:2] - PWMIO Period Control 1
 */
#define PWMIO_CTRL_PERIOD1_EN_POS           (2)
#define PWMIO_CTRL_PERIOD1_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD1_EN_POS)
#define PWMIO_CTRL_PERIOD1_32             	(0x3UL << PWMIO_CTRL_PERIOD1_EN_POS)
#define PWMIO_CTRL_PERIOD1_64             	(0x2UL << PWMIO_CTRL_PERIOD1_EN_POS)
#define PWMIO_CTRL_PERIOD1_128             	(0x1UL << PWMIO_CTRL_PERIOD1_EN_POS)
#define PWMIO_CTRL_PERIOD1_256             	(0x0UL << PWMIO_CTRL_PERIOD1_EN_POS)

/*
 * Bit definition for PWMIO_PERIOD_CTRL[1:0] - PWMIO Period Control 0
 */
#define PWMIO_CTRL_PERIOD0_EN_POS           (0)
#define PWMIO_CTRL_PERIOD0_EN_MSK           (0x3UL << PWMIO_CTRL_PERIOD0_EN_POS)
#define PWMIO_CTRL_PERIOD0_32             	(0x3UL << PWMIO_CTRL_PERIOD0_EN_POS)
#define PWMIO_CTRL_PERIOD0_64             	(0x2UL << PWMIO_CTRL_PERIOD0_EN_POS)
#define PWMIO_CTRL_PERIOD0_128             	(0x1UL << PWMIO_CTRL_PERIOD0_EN_POS)
#define PWMIO_CTRL_PERIOD0_256             	(0x0UL << PWMIO_CTRL_PERIOD0_EN_POS)


/*---------------------------------------------------------------------------------------
 * Quadrature Decoder Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
 typedef struct
{
	__IO uint32_t QD0_CNT;							      // QD0 Counter Register
	__IO uint32_t QD1_CNT;							      // QD1 Counter Register
	__IO uint32_t QD0_CLR;							      // QD0 Clear Register
	__IO uint32_t QD1_CLR;				            // QD1 Clear Register
	__IO uint32_t CTRL;							    			// QD Control Register
	__IO uint32_t STS;							    			// QD Status Register
	__IO uint32_t FW_TH;                      // QD Forward counter Threshold
	__IO uint32_t BW_TH;                      // QD Backward counter Threshold
} QD_TYPE_DEF;

/*
 * Bit definition for QD_CTRL[11] - QD1 motor reverse interrupt enable
 */
#define QD_CTRL_QD1_REV_EN_POS              (11)
#define QD_CTRL_QD1_REV_EN_MSK              (0x1UL << QD_CTRL_QD1_REV_EN_POS)
#define QD_CTRL_QD1_REV_ENABLE              (0x1UL << QD_CTRL_QD1_REV_EN_POS)
#define QD_CTRL_QD1_REV_DISABLE             (0x0UL << QD_CTRL_QD1_REV_EN_POS)

/*
 * Bit definition for QD_CTRL[10] - QD1 motor positive interrupt enable
 */
#define QD_CTRL_QD1_POS_EN_POS              (10)
#define QD_CTRL_QD1_POS_EN_MSK              (0x1UL << QD_CTRL_QD1_POS_EN_POS)
#define QD_CTRL_QD1_POS_ENABLE              (0x1UL << QD_CTRL_QD1_POS_EN_POS)
#define QD_CTRL_QD1_POS_DISABLE             (0x0UL << QD_CTRL_QD1_POS_EN_POS)

/*
 * Bit definition for QD_CTRL[9] - QD0 motor reverse interrupt enable
 */
#define QD_CTRL_QD0_REV_EN_POS              (9)
#define QD_CTRL_QD0_REV_EN_MSK							(0x1UL << QD_CTRL_QD0_REV_EN_POS)
#define QD_CTRL_QD0_REV_ENABLE							(0x1UL << QD_CTRL_QD0_REV_EN_POS)
#define QD_CTRL_QD0_REV_DISABLE  						(0x0UL << QD_CTRL_QD0_REV_EN_POS)

/*
 * Bit definition for QD_CTRL[8] - QD0 motor positive interrupt enable
 */
#define QD_CTRL_QD0_POS_EN_POS              (8)
#define QD_CTRL_QD0_POS_EN_MSK							(0x1UL << QD_CTRL_QD0_POS_EN_POS)
#define QD_CTRL_QD0_POS_ENABLE							(0x1UL << QD_CTRL_QD0_POS_EN_POS)
#define QD_CTRL_QD0_POS_DISABLE  						(0x0UL << QD_CTRL_QD0_POS_EN_POS)

/*
 * Bit definition for QD_CTRL[7] - QD overflow mode2
 */
#define QD_CTRL_OVERFLOW_MODE2_POS          (7)
#define QD_CTRL_OVERFLOW_MODE2_MSK					(0x1UL << QD_CTRL_OVERFLOW_MODE2_POS)
#define QD_CTRL_OVERFLOW_MODE2_ENABLE				(0x1UL << QD_CTRL_OVERFLOW_MODE2_POS)
#define QD_CTRL_OVERFLOW_MODE2_DISABLE  		(0x0UL << QD_CTRL_OVERFLOW_MODE2_POS)

/*
* Bit definition for QD_CTRL[6:4] - QD input debounce select
 */
#define QD_CTRL_DEBOUNCE_SEL_POS						(4)
#define QD_CTRL_DEBOUNCE_SEL_MSK            (0x7UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_0T							(0x0UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_4T							(0x1UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_8T							(0x2UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_16T						(0x3UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_32T						(0x4UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_40T						(0x5UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_80T						(0x6UL << QD_CTRL_DEBOUNCE_SEL_POS)
#define QD_CTRL_DEBOUNCE_SEL_128T						(0x7UL << QD_CTRL_DEBOUNCE_SEL_POS)

/*
 * Bit definition for QD_CTRL[3] - QD1 control bit
 */
#define QD_CTRL_QD1_EN_POS               		(3)
#define QD_CTRL_QD1_EN_MSK									(0x1UL << QD_CTRL_QD1_EN_POS)
#define QD_CTRL_QD1_ENABLE									(0x1UL << QD_CTRL_QD1_EN_POS)
#define QD_CTRL_QD1_DISABLE  								(0x0UL << QD_CTRL_QD1_EN_POS)

/*
 * Bit definition for QD_CTRL[2] - QD1 interrupt mode
 */
#define QD_CTRL_QD1_INT_MODE_POS            (2)
#define QD_CTRL_QD1_INT_MODE_MSK            (0x1UL << QD_CTRL_QD1_INT_MODE_POS)
#define QD_CTRL_QD1_OVERFLOW_MODE           (0x1UL << QD_CTRL_QD1_INT_MODE_POS)
#define QD_CTRL_QD1_ALL_MODE                (0x0UL << QD_CTRL_QD1_INT_MODE_POS)

/*
 * Bit definition for QD_CTRL[1] - QD0 control bit
 */
#define QD_CTRL_QD0_EN_POS               		(1)
#define QD_CTRL_QD0_EN_MSK									(0x1UL << QD_CTRL_QD0_EN_POS)
#define QD_CTRL_QD0_ENABLE									(0x1UL << QD_CTRL_QD0_EN_POS)
#define QD_CTRL_QD0_DISABLE  								(0x0UL << QD_CTRL_QD0_EN_POS)

/*
 * Bit definition for QD_CTRL[0] - QD0 interrupt mode
 */
#define QD_CTRL_QD0_INT_MODE_POS            (0)
#define QD_CTRL_QD0_INT_MODE_MSK            (0x1UL << QD_CTRL_QD0_INT_MODE_POS)
#define QD_CTRL_QD0_OVERFLOW_MODE           (0x1UL << QD_CTRL_QD0_INT_MODE_POS)
#define QD_CTRL_QD0_ALL_MODE                (0x0UL << QD_CTRL_QD0_INT_MODE_POS)

/*
 * Bit definition for QD_STS[11] - QD1 motor reverse interrupt flag
 */
#define QD_CTRL_QD1_REV_INTF_POS            (11)
#define QD_CTRL_QD1_REV_INTF_MSK            (0x1UL << QD_CTRL_QD1_REV_INTF_POS)
#define QD_CTRL_QD1_REV_INT_FLAG            (0x1UL << QD_CTRL_QD1_REV_INTF_POS)

/*
 * Bit definition for QD_STS[10] - QD1 motor positive interrupt flag
 */
#define QD_CTRL_QD1_POS_INTF_POS            (10)
#define QD_CTRL_QD1_POS_INTF_MSK            (0x1UL << QD_CTRL_QD1_POS_INTF_POS)
#define QD_CTRL_QD1_POS_INT_FLAG            (0x1UL << QD_CTRL_QD1_POS_INTF_POS)

/*
 * Bit definition for QD_STS[9] - QD0 motor reverse interrupt flag
 */
#define QD_CTRL_QD0_REV_INTF_POS            (9)
#define QD_CTRL_QD0_REV_INTF_MSK            (0x1UL << QD_CTRL_QD0_REV_INTF_POS)
#define QD_CTRL_QD0_REV_INT_FLAG            (0x1UL << QD_CTRL_QD0_REV_INTF_POS)

/*
 * Bit definition for QD_STS[8] - QD0 motor positive interrupt flag
 */
#define QD_CTRL_QD0_POS_INTF_POS            (8)
#define QD_CTRL_QD0_POS_INTF_MSK            (0x1UL << QD_CTRL_QD0_POS_INTF_POS)
#define QD_CTRL_QD0_POS_INT_FLAG            (0x1UL << QD_CTRL_QD0_POS_INTF_POS)


/*---------------------------------------------------------------------------------------
 * System Management Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t SYSLOCK;					          // System Control Signal Lock Register
	__IO uint32_t PID;							          // Produce ID Register
	__IO uint32_t UID0;							          // User Defined ID 0 Mirror Register
	__IO uint32_t UID1;							          // User Defined ID 1 Mirror Register
	__IO uint32_t UID2;							          // User Defined ID 2 Mirror Register
	__IO uint32_t UID3;							          // User Defined ID 2 Mirror Register
	__I  uint32_t RESERVED0[6];
	__IO uint32_t CACHE_CTRL;
} SMU_TYPE_DEF;

/*
 * Bit definition for SMU_SYSLOCK[8]- System UnLock Status
 */
#define SMU_SYSLOCK_UNLOCK_STS_POS          (8)
#define SMU_SYSLOCK_UNLOCK_STS_MSK          (0x1UL << SMU_SYSLOCK_UNLOCK_STS_POS)
#define SMU_SYSLOCK_UNLOCK_STS_FLAG         (0x1UL << SMU_SYSLOCK_UNLOCK_STS_POS)

/*
 * Bit definition for SMU_SYSLOCK[7:0]- System UnLock Key
 */
#define SMU_SYSLOCK_UNLOCK_KEY_POS          (0)
#define SMU_SYSLOCK_UNLOCK_KEY_MSK          (0xFFUL << SMU_SYSLOCK_UNLOCK_KEY_POS)
#define SMU_SYSLOCK_UNLOCK_KEY1             (0xABUL << SMU_SYSLOCK_UNLOCK_KEY_POS)
#define SMU_SYSLOCK_UNLOCK_KEY2             (0x12UL << SMU_SYSLOCK_UNLOCK_KEY_POS)

/*
 * Bit definition for SMU_CACHE_CTRL[0]- Cache Enable
 */
#define SMU_CACHE_CTRL_CACHE_EN_POS         (0)
#define SMU_CACHE_CTRL_CACHE_EN_MSK         (0x1UL << SMU_CACHE_CTRL_CACHE_EN_POS)
#define SMU_CACHE_CTRL_CACHE_ENABLE         (0x1UL << SMU_CACHE_CTRL_CACHE_EN_POS)
#define SMU_CACHE_CTRL_CACHE_DISABLE        (0x0UL << SMU_CACHE_CTRL_CACHE_EN_POS)


/*---------------------------------------------------------------------------------------
 * Clock Control Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t AHBCKEN;                    // AHB Peripherals Clock Enable Register
	__I  uint32_t RESERVED0[3];               // Reserved
	__IO uint32_t APBCKEN;                    // APB Peripherals Clock Enable Register
	__I  uint32_t RESERVED1[3];               // Reserved
	__IO uint32_t AHBCKSEL ;                  // AHB Peripherals Clock Selection 0 Register
	__I  uint32_t RESERVED2[3];               // Reserved
	__IO uint32_t CLKDIV1;                    // Clock Divider Register
	__I  uint32_t RESERVED3[7];               // Reserved
	__IO uint32_t CLKSTS;						          // Clock Status Register
	__I  uint32_t RESERVED5[7];               // Reserved
	__IO uint32_t CLKDIV3;					          // Clock Divider Register
} CLOCK_TYPE_DEF;

/*
 * Bit definition for CLOCK_AHBCKEN[15]- CPU clock enable
 */
#define CLOCK_AHBCKEN_CPU_CLK_EN_POS        (15)
#define CLOCK_AHBCKEN_CPU_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_CPU_CLK_EN_POS)
#define CLOCK_AHBCKEN_CPU_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_CPU_CLK_EN_POS)
#define CLOCK_AHBCKEN_CPU_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_CPU_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[14]- SysTick clock enable
 */
#define CLOCK_AHBCKEN_SYSTICK_CLK_EN_POS    (14)
#define CLOCK_AHBCKEN_SYSTICK_CLK_EN_MSK    (0x1UL << CLOCK_AHBCKEN_SYSTICK_CLK_EN_POS)
#define CLOCK_AHBCKEN_SYSTICK_CLK_ENABLE    (0x1UL << CLOCK_AHBCKEN_SYSTICK_CLK_EN_POS)
#define CLOCK_AHBCKEN_SYSTICK_CLK_DISABLE   (0x0UL << CLOCK_AHBCKEN_SYSTICK_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[13]- Analog Controller clock enable
 */
#define CLOCK_AHBCKEN_ANALOG_CLK_EN_POS     (13)
#define CLOCK_AHBCKEN_ANALOG_CLK_EN_MSK     (0x1UL << CLOCK_AHBCKEN_ANALOG_CLK_EN_POS)
#define CLOCK_AHBCKEN_ANALOG_CLK_ENABLE     (0x1UL << CLOCK_AHBCKEN_ANALOG_CLK_EN_POS)
#define CLOCK_AHBCKEN_ANALOG_CLK_DISABLE    (0x0UL << CLOCK_AHBCKEN_ANALOG_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[12]- Interrupt Controller clock enable
 */
#define CLOCK_AHBCKEN_INT_CLK_EN_POS        (12)
#define CLOCK_AHBCKEN_INT_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_INT_CLK_EN_POS)
#define CLOCK_AHBCKEN_INT_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_INT_CLK_EN_POS)
#define CLOCK_AHBCKEN_INT_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_INT_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[11]- Internal RAM clock enable
 */
#define CLOCK_AHBCKEN_RAM_CLK_EN_POS        (11)
#define CLOCK_AHBCKEN_RAM_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_RAM_CLK_EN_POS)
#define CLOCK_AHBCKEN_RAM_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_RAM_CLK_EN_POS)
#define CLOCK_AHBCKEN_RAM_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_RAM_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[10]- APB sub bus clock enable
 */
#define CLOCK_AHBCKEN_APB_CLK_EN_POS        (10)
#define CLOCK_AHBCKEN_APB_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_APB_CLK_EN_POS)
#define CLOCK_AHBCKEN_APB_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_APB_CLK_EN_POS)
#define CLOCK_AHBCKEN_APB_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_APB_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[9]- AHB bus matrix clock enable
 */
#define CLOCK_AHBCKEN_AHBBUS_CLK_EN_POS     (9)
#define CLOCK_AHBCKEN_AHBBUS_CLK_EN_MSK     (0x1UL << CLOCK_AHBCKEN_AHBBUS_CLK_EN_POS)
#define CLOCK_AHBCKEN_AHBBUS_CLK_ENABLE     (0x1UL << CLOCK_AHBCKEN_AHBBUS_CLK_EN_POS)
#define CLOCK_AHBCKEN_AHBBUS_CLK_DISABLE    (0x0UL << CLOCK_AHBCKEN_AHBBUS_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[8]- Flash clock enable
 */
#define CLOCK_AHBCKEN_FLASH_CLK_EN_POS      (8)
#define CLOCK_AHBCKEN_FLASH_CLK_EN_MSK      (0x1UL << CLOCK_AHBCKEN_FLASH_CLK_EN_POS)
#define CLOCK_AHBCKEN_FLASH_CLK_ENABLE      (0x1UL << CLOCK_AHBCKEN_FLASH_CLK_EN_POS)
#define CLOCK_AHBCKEN_FLASH_CLK_DISABLE     (0x0UL << CLOCK_AHBCKEN_FLASH_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[7]- GPIO clock enable
 */
#define CLOCK_AHBCKEN_GPIO_CLK_EN_POS       (7)
#define CLOCK_AHBCKEN_GPIO_CLK_EN_MSK       (0x1UL << CLOCK_AHBCKEN_GPIO_CLK_EN_POS)
#define CLOCK_AHBCKEN_GPIO_CLK_ENABLE       (0x1UL << CLOCK_AHBCKEN_GPIO_CLK_EN_POS)
#define CLOCK_AHBCKEN_GPIO_CLK_DISABLE      (0x0UL << CLOCK_AHBCKEN_GPIO_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[4]- SPIFC clock enable
 */
#define CLOCK_AHBCKEN_SPIFC_CLK_EN_POS      (4)
#define CLOCK_AHBCKEN_SPIFC_CLK_EN_MSK      (0x1UL << CLOCK_AHBCKEN_SPIFC_CLK_EN_POS)
#define CLOCK_AHBCKEN_SPIFC_CLK_ENABLE      (0x1UL << CLOCK_AHBCKEN_SPIFC_CLK_EN_POS)
#define CLOCK_AHBCKEN_SPIFC_CLK_DISABLE     (0x0UL << CLOCK_AHBCKEN_SPIFC_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[3]- MAC clock enable
 */
#define CLOCK_AHBCKEN_MAC_CLK_EN_POS        (3)
#define CLOCK_AHBCKEN_MAC_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_MAC_CLK_EN_POS)
#define CLOCK_AHBCKEN_MAC_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_MAC_CLK_EN_POS)
#define CLOCK_AHBCKEN_MAC_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_MAC_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[2]- CCP1 clock enable
 */
#define CLOCK_AHBCKEN_CCP1_CLK_EN_POS       (2)
#define CLOCK_AHBCKEN_CCP1_CLK_EN_MSK       (0x1UL << CLOCK_AHBCKEN_CCP1_CLK_EN_POS)
#define CLOCK_AHBCKEN_CCP1_CLK_ENABLE       (0x1UL << CLOCK_AHBCKEN_CCP1_CLK_EN_POS)
#define CLOCK_AHBCKEN_CCP1_CLK_DISALBE      (0x0UL << CLOCK_AHBCKEN_CCP1_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[1]- CCP0 clock enable
 */
#define CLOCK_AHBCKEN_CCP0_CLK_EN_POS       (1)
#define CLOCK_AHBCKEN_CCP0_CLK_EN_MSK       (0x1UL << CLOCK_AHBCKEN_CCP0_CLK_EN_POS)
#define CLOCK_AHBCKEN_CCP0_CLK_ENABLE       (0x1UL << CLOCK_AHBCKEN_CCP0_CLK_EN_POS)
#define CLOCK_AHBCKEN_CCP0_CLK_DISALBE      (0x0UL << CLOCK_AHBCKEN_CCP0_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKEN[0]- DMA clock enable
 */
#define CLOCK_AHBCKEN_DMA_CLK_EN_POS        (0)
#define CLOCK_AHBCKEN_DMA_CLK_EN_MSK        (0x1UL << CLOCK_AHBCKEN_DMA_CLK_EN_POS)
#define CLOCK_AHBCKEN_DMA_CLK_ENABLE        (0x1UL << CLOCK_AHBCKEN_DMA_CLK_EN_POS)
#define CLOCK_AHBCKEN_DMA_CLK_DISABLE       (0x0UL << CLOCK_AHBCKEN_DMA_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[15]- Watch dog clock enable
 */
#define CLOCK_APBCKEN_WDG_CLK_EN_POS        (15)
#define CLOCK_APBCKEN_WDG_CLK_EN_MSK        (0x1UL << CLOCK_APBCKEN_WDG_CLK_EN_POS)
#define CLOCK_APBCKEN_WDG_CLK_ENABLE        (0x1UL << CLOCK_APBCKEN_WDG_CLK_EN_POS)
#define CLOCK_APBCKEN_WDG_CLK_DISABLE       (0x0UL << CLOCK_APBCKEN_WDG_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[11]- AUDPWM clock enable
 */
#define CLOCK_APBCKEN_AUDPWM_CLK_EN_POS     (11)
#define CLOCK_APBCKEN_AUDPWM_CLK_EN_MSK     (0x1UL << CLOCK_APBCKEN_AUDPWM_CLK_EN_POS)
#define CLOCK_APBCKEN_AUDPWM_CLK_ENABLE     (0x1UL << CLOCK_APBCKEN_AUDPWM_CLK_EN_POS)
#define CLOCK_APBCKEN_AUDPWM_CLK_DISABLE    (0x0UL << CLOCK_APBCKEN_AUDPWM_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[10]- CTS & TimeBase clock enable
 */
#define CLOCK_APBCKEN_CTS_TB_CLK_EN_POS        (10)
#define CLOCK_APBCKEN_CTS_TB_CLK_EN_MSK        (0x1UL << CLOCK_APBCKEN_CTS_TB_CLK_EN_POS)
#define CLOCK_APBCKEN_CTS_TB_CLK_ENABLE        (0x1UL << CLOCK_APBCKEN_CTS_TB_CLK_EN_POS)
#define CLOCK_APBCKEN_CTS_TB_CLK_DISABLE       (0x0UL << CLOCK_APBCKEN_CTS_TB_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[9]- I2S clock enable
 */
#define CLOCK_APBCKEN_I2S_CLK_EN_POS        (9)
#define CLOCK_APBCKEN_I2S_CLK_EN_MSK        (0x1UL << CLOCK_APBCKEN_I2S_CLK_EN_POS)
#define CLOCK_APBCKEN_I2S_CLK_ENABLE        (0x1UL << CLOCK_APBCKEN_I2S_CLK_EN_POS)
#define CLOCK_APBCKEN_I2S_CLK_DISABLE       (0x0UL << CLOCK_APBCKEN_I2S_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[8]- Delta sigma ADC clock enable
 */
#define CLOCK_APBCKEN_DSADC_CLK_EN_POS      (8)
#define CLOCK_APBCKEN_DSADC_CLK_EN_MSK      (0x1UL << CLOCK_APBCKEN_DSADC_CLK_EN_POS)
#define CLOCK_APBCKEN_DSADC_CLK_ENABLE      (0x1UL << CLOCK_APBCKEN_DSADC_CLK_EN_POS)
#define CLOCK_APBCKEN_DSADC_CLK_DISABLE     (0x0UL << CLOCK_APBCKEN_DSADC_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[7]- SAR ADC clock enable
 */
#define CLOCK_APBCKEN_SARADC_CLK_EN_POS     (7)
#define CLOCK_APBCKEN_SARADC_CLK_EN_MSK     (0x1UL << CLOCK_APBCKEN_SARADC_CLK_EN_POS)
#define CLOCK_APBCKEN_SARADC_CLK_ENABLE     (0x1UL << CLOCK_APBCKEN_SARADC_CLK_EN_POS)
#define CLOCK_APBCKEN_SARADC_CLK_DISABLE    (0x0UL << CLOCK_APBCKEN_SARADC_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[6]- SPI1 clock enable
 */
#define CLOCK_APBCKEN_SPI1_CLK_EN_POS       (6)
#define CLOCK_APBCKEN_SPI1_CLK_EN_MSK       (0x1UL << CLOCK_APBCKEN_SPI1_CLK_EN_POS)
#define CLOCK_APBCKEN_SPI1_CLK_ENABLE       (0x1UL << CLOCK_APBCKEN_SPI1_CLK_EN_POS)
#define CLOCK_APBCKEN_SPI1_CLK_DISABLE      (0x0UL << CLOCK_APBCKEN_SPI1_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[5]- SPI0 clock enable
 */
#define CLOCK_APBCKEN_SPI0_CLK_EN_POS       (5)
#define CLOCK_APBCKEN_SPI0_CLK_EN_MSK       (0x1UL << CLOCK_APBCKEN_SPI0_CLK_EN_POS)
#define CLOCK_APBCKEN_SPI0_CLK_ENABLE       (0x1UL << CLOCK_APBCKEN_SPI0_CLK_EN_POS)
#define CLOCK_APBCKEN_SPI0_CLK_DISABLE      (0x0UL << CLOCK_APBCKEN_SPI0_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[4]- UART clock enable
 */
#define CLOCK_APBCKEN_UART_CLK_EN_POS       (4)
#define CLOCK_APBCKEN_UART_CLK_EN_MSK       (0x1UL << CLOCK_APBCKEN_UART_CLK_EN_POS)
#define CLOCK_APBCKEN_UART_CLK_ENABLE       (0x1UL << CLOCK_APBCKEN_UART_CLK_EN_POS)
#define CLOCK_APBCKEN_UART_CLK_DISABLE      (0x0UL << CLOCK_APBCKEN_UART_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[3]- I2C clock enable
 */
#define CLOCK_APBCKEN_I2C_CLK_EN_POS        (3)
#define CLOCK_APBCKEN_I2C_CLK_EN_MSK        (0x1UL << CLOCK_APBCKEN_I2C_CLK_EN_POS)
#define CLOCK_APBCKEN_I2C_CLK_ENABLE        (0x1UL << CLOCK_APBCKEN_I2C_CLK_EN_POS)
#define CLOCK_APBCKEN_I2C_CLK_DISABLE       (0x0UL << CLOCK_APBCKEN_I2C_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[2]- Timer clock enable
 */
#define CLOCK_APBCKEN_TIMER_CLK_EN_POS      (2)
#define CLOCK_APBCKEN_TIMER_CLK_EN_MSK      (0x1UL << CLOCK_APBCKEN_TIMER_CLK_EN_POS)
#define CLOCK_APBCKEN_TIMER_CLK_ENABLE      (0x1UL << CLOCK_APBCKEN_TIMER_CLK_EN_POS)
#define CLOCK_APBCKEN_TIMER_CLK_DISABLE     (0x0UL << CLOCK_APBCKEN_TIMER_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[1]- DAC clock enable
 */
#define CLOCK_APBCKEN_DAC_CLK_EN_POS        (1)
#define CLOCK_APBCKEN_DAC_CLK_EN_MSK        (0x1UL << CLOCK_APBCKEN_DAC_CLK_EN_POS)
#define CLOCK_APBCKEN_DAC_CLK_ENABLE        (0x1UL << CLOCK_APBCKEN_DAC_CLK_EN_POS)
#define CLOCK_APBCKEN_DAC_CLK_DISABLE       (0x0UL << CLOCK_APBCKEN_DAC_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[0]- QD clock enable
 */
#define CLOCK_APBCKEN_QD_CLK_EN_POS         (0)
#define CLOCK_APBCKEN_QD_CLK_EN_MSK         (0x1UL << CLOCK_APBCKEN_QD_CLK_EN_POS)
#define CLOCK_APBCKEN_QD_CLK_ENABLE         (0x1UL << CLOCK_APBCKEN_QD_CLK_EN_POS)
#define CLOCK_APBCKEN_QD_CLK_DISABLE        (0x0UL << CLOCK_APBCKEN_QD_CLK_EN_POS)

/*
 * Bit definition for CLOCK_APBCKEN[0]- PWMIO clock enable
 */
#define CLOCK_APBCKEN_PWMIO_CLK_EN_POS      (0)
#define CLOCK_APBCKEN_PWMIO_CLK_EN_MSK      (0x1UL << CLOCK_APBCKEN_PWMIO_CLK_EN_POS)
#define CLOCK_APBCKEN_PWMIO_CLK_ENABLE      (0x1UL << CLOCK_APBCKEN_PWMIO_CLK_EN_POS)
#define CLOCK_APBCKEN_PWMIO_CLK_DISABLE     (0x0UL << CLOCK_APBCKEN_PWMIO_CLK_EN_POS)

/*
 * Bit definition for CLOCK_AHBCKSEL[12]- SYS32K Selection
 */
#define CLOCK_AHBCKSEL_SYS32K_SEL_POS       (12)
#define CLOCK_AHBCKSEL_SYS32K_SEL_MSK       (0x1UL << CLOCK_AHBCKSEL_SYS32K_SEL_POS)
#define CLOCK_AHBCKSEL_SYS32K_SEL_IOSC32K   (0x1UL << CLOCK_AHBCKSEL_SYS32K_SEL_POS)
#define CLOCK_AHBCKSEL_SYS32K_SEL_XTAL32K   (0x0UL << CLOCK_AHBCKSEL_SYS32K_SEL_POS)

/*
 * Bit definition for CLOCK_AHBCKSEL[1:0]- HCLK Source Selection
 */
#define CLOCK_AHBCKSEL_HCLK_SEL_POS         (0)
#define CLOCK_AHBCKSEL_HCLK_SEL_MSK         (0x3UL << CLOCK_AHBCKSEL_HCLK_SEL_POS)
#define CLOCK_AHBCKSEL_HCLK_SEL_SYS32K      (0x2UL << CLOCK_AHBCKSEL_HCLK_SEL_POS)
#define CLOCK_AHBCKSEL_HCLK_SEL_PLL         (0x1UL << CLOCK_AHBCKSEL_HCLK_SEL_POS)
#define CLOCK_AHBCKSEL_HCLK_SEL_IOSC8M      (0x0UL << CLOCK_AHBCKSEL_HCLK_SEL_POS)

/*
 * Bit definition for CLOCK_CLKDIV1[7:4] - DS ADC Clock divder
 */
#define CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS  (4)
#define CLOCK_CLKDIV1_DSADC_CLK_DIVDER_MSK  (0xFUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_16      (0xFUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_15      (0xEUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_14      (0xDUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_13      (0xCUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_12      (0xBUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_11      (0xAUL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_10      (0x9UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_9       (0x8UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_8       (0x7UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_7       (0x6UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_6       (0x5UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_5       (0x4UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_4       (0x3UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_3       (0x2UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_2       (0x1UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV1_DSADC_CLK_DIV_1       (0x0UL << CLOCK_CLKDIV1_DSADC_CLK_DIVDER_POS)

/*
 * Bit definition for CLOCK_CLKDIV1[3:0] - Audio PWM Clock divder
 */
#define CLOCK_CLKDIV1_AUDCLK_SEL_POS             (0)
#define CLOCK_CLKDIV1_AUDCLK_SEL_MSK             (0xFUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_16   (0xFUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_15   (0xEUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_14   (0xDUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_13   (0xCUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_12   (0xBUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_11   (0xAUL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_10   (0x9UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_9    (0x8UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_8    (0x7UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_7    (0x6UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_6    (0x5UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_5    (0x4UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_4    (0x3UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_3    (0x2UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_2    (0x1UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)
#define CLOCK_CLKDIV1_AUDCLK_SEL_SYSCLK_DIV_1    (0x0UL << CLOCK_CLKDIV1_AUDCLK_SEL_POS)

/*
 * Bit definition for CLOCK_CLKSTS[3]- External Crystal Oscillator Ready Flag(XTAL 32KHz)
 */
#define CLOCK_CLKSTS_XTAL32K_POS        	  (3)
#define CLOCK_CLKSTS_XTAL32K_MSK        	  (0x1UL << CLOCK_CLKSTS_XTAL32K_POS)
#define CLOCK_CLKSTS_XTAL32K_RDY  		      (0x1UL << CLOCK_CLKSTS_XTAL32K_POS)
#define CLOCK_CLKSTS_XTAL32K_NOT_RDY 	      (0x0UL << CLOCK_CLKSTS_XTAL32K_POS)

/*
 * Bit definition for CLOCK_CLKSTS[2] - PLL Ready Flag
 */
#define CLOCK_CLKSTS_PLL_RDY_POS            (2)
#define CLOCK_CLKSTS_PLL_RDY_MSK            (0x1UL << CLOCK_CLKSTS_PLL_RDY_POS)
#define CLOCK_CLKSTS_PLL_RDY                (0x1UL << CLOCK_CLKSTS_PLL_RDY_POS)
#define CLOCK_CLKSTS_PLL_NOT_RDY            (0x0UL << CLOCK_CLKSTS_PLL_RDY_POS)

/*
 * Bit definition for CLOCK_CLKSTS[1]- Low Speed Internal RC Ready Flag(Iosc 32KHz)  Kim 2019.08.20
 */
#define CLOCK_CLKSTS_IOSC32K_POS        	  (1)
#define CLOCK_CLKSTS_IOSC32K_MSK        	  (0x1UL << CLOCK_CLKSTS_IOSC32K_POS)
#define CLOCK_CLKSTS_IOSC32K_RDY  		      (0x1UL << CLOCK_CLKSTS_IOSC32K_POS)
#define CLOCK_CLKSTS_IOSC32K_NOT_RDY        (0x0UL << CLOCK_CLKSTS_IOSC32K_POS)

/*
 * Bit definition for CLOCK_CLKSTS[0] - IOSC8M Ready Flag
 */
#define CLOCK_CLKSTS_IOSC8M_RDY_POS         (0)
#define CLOCK_CLKSTS_IOSC8M_RDY_MSK         (0x1UL << CLOCK_CLKSTS_IOSC8M_RDY_POS)
#define CLOCK_CLKSTS_IOSC8M_RDY             (0x1UL << CLOCK_CLKSTS_IOSC8M_RDY_POS)
#define CLOCK_CLKSTS_IOSC8M_NOT_RDY         (0x0UL << CLOCK_CLKSTS_IOSC8M_RDY_POS)

/*
 * Bit definition for CLOCK_CLKDIV3[1:0] - DS ADC Clock divder
 */
#define CLOCK_CLKDIV3_DSADC_CLK_DIVDER_POS  (0)
#define CLOCK_CLKDIV3_DSADC_CLK_DIVDER_MSK  (0x3UL << CLOCK_CLKDIV3_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV3_DSADC_CLK_DIV_4       (0x3UL << CLOCK_CLKDIV3_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV3_DSADC_CLK_DIV_2       (0x1UL << CLOCK_CLKDIV3_DSADC_CLK_DIVDER_POS)
#define CLOCK_CLKDIV3_DSADC_CLK_DIV_1       (0x0UL << CLOCK_CLKDIV3_DSADC_CLK_DIVDER_POS)


/*---------------------------------------------------------------------------------------
 * Reset control unit 0x50003000
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;
	__IO uint32_t STS;
} RCU_TYPE_DEF;

/*
 * Bit definition for RCU_CTRL[0] - Master Reset Trigger Register
 */
#define RCU_CTRL_MRST_EN_POS                (0)
#define RCU_CTRL_MRST_EN_MSK                (0x1UL << RCU_CTRL_MRST_EN_POS)
#define RCU_CTRL_MRST_EN_TRIGGER            (0x0UL << RCU_CTRL_MRST_EN_POS)

/*
 * Bit definition for RCU_STS[6] - WatchDog reset
 */
#define RCU_STS_SYS_WDT_POS                 (6)
#define RCU_STS_SYS_WDT_MSK                 (0x1UL << RCU_STS_SYS_WDT_POS)
#define RCU_STS_SYS_WDT_FLAG                (0x1UL << RCU_STS_SYS_WDT_POS)

/*
 * Bit definition for RCU_STS[4] - LVR reset
 */
#define RCU_STS_LVR_RST_POS									(4)
#define RCU_STS_LVR_RST_MSK									(0x1UL << RCU_STS_LVR_RST_POS)
#define RCU_STS_LVR_RST_FLAG								(0x1UL << RCU_STS_LVR_RST_POS)

/*
 * Bit definition for RCU_STS[3] - System reset
 */
#define RCU_STS_SYS_RST_POS                 (3)
#define RCU_STS_SYS_RST_MSK                 (0x1UL << RCU_STS_SYS_RST_POS)
#define RCU_STS_SYS_RST_FLAG                (0x1UL << RCU_STS_SYS_RST_POS)

/*
 * Bit definition for RCU_STS[2] - Software reset
 */
#define RCU_STS_SOFT_RST_POS                (2)
#define RCU_STS_SOFT_RST_MSK                (0x1UL << RCU_STS_SOFT_RST_POS)
#define RCU_STS_SOFT_RST_FLAG               (0x1UL << RCU_STS_SOFT_RST_POS)

/*
 * Bit definition for RCU_STS[1] - H/W Key reset
 */
#define RCU_STS_KEY_RST_POS                 (1)
#define RCU_STS_KEY_RST_MSK                 (0x1UL << RCU_STS_KEY_RST_POS)
#define RCU_STS_KEY_RST_FLAG                (0x1UL << RCU_STS_KEY_RST_POS)

/*
 * Bit definition for RCU_STS[0] - Power on reset
 */
#define RCU_STS_POR_POS                     (0)
#define RCU_STS_POR_MSK                     (0x1UL << RCU_STS_POR_POS)
#define RCU_STS_POR_FLAG                    (0x1UL << RCU_STS_POR_POS)


/*---------------------------------------------------------------------------------------
 * Interrupt control unit
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t NMICTRL;                    // NMI Interrupt Control Register
	__IO uint32_t SWIRQ;	                    // Software Interrupt Request Register
	__I  uint32_t RESERVED0[2];               // Reserved
	__IO uint32_t EXTIEN;                     // External Interrupt Enable Register
	__IO uint32_t EXTEEN;                     // External Event Enable Register
	__IO uint32_t EXTRHT;                     // External Rising Edge / High Level Trigger Register
	__I  uint32_t RESERVED1[1];               // Reserved
	__IO uint32_t EXTFLT;                     // External Falling Edge / Low Level Trigger Register
	__I  uint32_t RESERVED2[1];               // Reserved
	__IO uint32_t EXTIFLG;                    // External Interrupt Flag Register
	__IO uint32_t EXTEFLG;                    // External Event Flag Register
	__IO uint32_t EXTSWIE;                    // External Software Trigger Interrupt Event Register
} ITU_TypeDef;

/*
 * Bit definition for 0x10 ITU_NMICTRL[16] - NMI Interrupt Enabe
 */
#define ITU_NMICTRL_INT_EN_POS              (16)
#define ITU_NMICTRL_INT_EN_MSK              (0x1UL << ITU_NMICTRL_INT_EN_POS)
#define ITU_NMICTRL_INT_ENABLE              (0x1UL << ITU_NMICTRL_INT_EN_POS)
#define ITU_NMICTRL_INT_DISABLE             (0x0UL << ITU_NMICTRL_INT_EN_POS)

/*
 * Bit definition for 0x10 ITU_NMICTRL[4:0] - NMI Source Selection
 */
#define ITU_NMICTRL_SRC_SEL_POS             (0)
#define ITU_NMICTRL_SRC_SEL_MSK             (0x1FUL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_KEYCHG          (0x1DUL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_TM2             (0x1CUL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_TM1             (0x1BUL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_TM0             (0x1AUL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_EXTI3           (0x18UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_EXTI2           (0x17UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_EXTI1           (0x16UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_EXTI0           (0x15UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_SPI1            (0x14UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_SPI0            (0x13UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_I2S             (0x12UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_UART            (0x10UL << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_I2C             (0xEUL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_TIMEBASE        (0xDUL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_CTS_TMA1        (0xCUL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_CTS_TMA0        (0xBUL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_CCP1            (0xAUL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_CCP0            (0x9UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_DAC_CH1         (0x8UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_DAC_CH0         (0x7UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_DS_ADC          (0x6UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_SAR_ADC         (0x5UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_QD              (0x4UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_MAC             (0x3UL  << ITU_NMICTRL_SRC_SEL_POS)
#define ITU_NMICTRL_SRC_SEL_DMA             (0x2UL  << ITU_NMICTRL_SRC_SEL_POS)

/*
 * Bit definition for ITU_EXTIEN[3] - External Input 3 Interrupt Enable
 */
#define ITU_EXTIEN_EXT3_INT_EN_POS          (3)
#define ITU_EXTIEN_EXT3_INT_EN_MSK          (0x1UL << ITU_EXTIEN_EXT3_INT_EN_POS)
#define ITU_EXTIEN_EXT3_INT_ENABLE          (0x1UL << ITU_EXTIEN_EXT3_INT_EN_POS)
#define ITU_EXTIEN_EXT3_INT_DISABLE         (0x0UL << ITU_EXTIEN_EXT3_INT_EN_POS)

/*
 * Bit definition for ITU_EXTIEN[2] - External Input 2 Interrupt Enable
 */
#define ITU_EXTIEN_EXT2_INT_EN_POS          (2)
#define ITU_EXTIEN_EXT2_INT_EN_MSK          (0x1UL << ITU_EXTIEN_EXT2_INT_EN_POS)
#define ITU_EXTIEN_EXT2_INT_ENABLE          (0x1UL << ITU_EXTIEN_EXT2_INT_EN_POS)
#define ITU_EXTIEN_EXT2_INT_DISABLE         (0x0UL << ITU_EXTIEN_EXT2_INT_EN_POS)

/*
 * Bit definition for ITU_EXTIEN[1] - External Input 1 Interrupt Enable
 */
#define ITU_EXTIEN_EXT1_INT_EN_POS          (1)
#define ITU_EXTIEN_EXT1_INT_EN_MSK          (0x1UL << ITU_EXTIEN_EXT1_INT_EN_POS)
#define ITU_EXTIEN_EXT1_INT_ENABLE          (0x1UL << ITU_EXTIEN_EXT1_INT_EN_POS)
#define ITU_EXTIEN_EXT1_INT_DISABLE         (0x0UL << ITU_EXTIEN_EXT1_INT_EN_POS)

/*
 * Bit definition for ITU_EXTIEN[0] - External Input 0 Interrupt Enable
 */
#define ITU_EXTIEN_EXT0_INT_EN_POS          (0)
#define ITU_EXTIEN_EXT0_INT_EN_MSK          (0x1UL << ITU_EXTIEN_EXT0_INT_EN_POS)
#define ITU_EXTIEN_EXT0_INT_ENABLE          (0x1UL << ITU_EXTIEN_EXT0_INT_EN_POS)
#define ITU_EXTIEN_EXT0_INT_DISABLE         (0x0UL << ITU_EXTIEN_EXT0_INT_EN_POS)

/*
 * Bit definition for EXTEEN[4] - Key Change Event Enable
 */
#define ITU_EXTEEN_KEYCHG_EVT_EN_POS        (4)
#define ITU_EXTEEN_KEYCHG_EVT_EN_MSK        (0x1UL << ITU_EXTEEN_KEYCHG_EVT_EN_POS)
#define ITU_EXTEEN_KEYCHG_EVT_ENABLE        (0x1UL << ITU_EXTEEN_KEYCHG_EVT_EN_POS)
#define ITU_EXTEEN_KEYCHG_EVT_DISABLE       (0x0UL << ITU_EXTEEN_KEYCHG_EVT_EN_POS)

/*
 * Bit definition for ITU_EXTEEN[3] - External Input 3 Event Enable
 */
#define ITU_EXTEEN_EXT3_EVT_EN_POS          (3)
#define ITU_EXTEEN_EXT3_EVT_EN_MSK          (0x1UL << ITU_EXTEEN_EXT3_EVT_EN_POS)
#define ITU_EXTEEN_EXT3_EVT_ENABLE          (0x1UL << ITU_EXTEEN_EXT3_EVT_EN_POS)
#define ITU_EXTEEN_EXT3_EVT_DISABLE         (0x0UL << ITU_EXTEEN_EXT3_EVT_EN_POS)

/*
 * Bit definition for ITU_EXTEEN[2] - External Input 2 Event Enable
 */
#define ITU_EXTEEN_EXT2_EVT_EN_POS          (2)
#define ITU_EXTEEN_EXT2_EVT_EN_MSK          (0x1UL << ITU_EXTEEN_EXT2_EVT_EN_POS)
#define ITU_EXTEEN_EXT2_EVT_ENABLE          (0x1UL << ITU_EXTEEN_EXT2_EVT_EN_POS)
#define ITU_EXTEEN_EXT2_EVT_DISABLE         (0x0UL << ITU_EXTEEN_EXT2_EVT_EN_POS)

/*
 * Bit definition for ITU_EXTEEN[1] - External Input 1 Event Enable
 */
#define ITU_EXTEEN_EXT1_EVT_EN_POS          (1)
#define ITU_EXTEEN_EXT1_EVT_EN_MSK          (0x1UL << ITU_EXTEEN_EXT1_EVT_EN_POS)
#define ITU_EXTEEN_EXT1_EVT_ENABLE          (0x1UL << ITU_EXTEEN_EXT1_EVT_EN_POS)
#define ITU_EXTEEN_EXT1_EVT_DISABLE         (0x0UL << ITU_EXTEEN_EXT1_EVT_EN_POS)

/*
 * Bit definition for ITU_EXTEEN[0] - External Input 0 Event Enable
 */
#define ITU_EXTEEN_EXT0_EVT_EN_POS          (0)
#define ITU_EXTEEN_EXT0_EVT_EN_MSK          (0x1UL << ITU_EXTEEN_EXT0_EVT_EN_POS)
#define ITU_EXTEEN_EXT0_EVT_ENABLE          (0x1UL << ITU_EXTEEN_EXT0_EVT_EN_POS)
#define ITU_EXTEEN_EXT0_EVT_DISABLE         (0x0UL << ITU_EXTEEN_EXT0_EVT_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[19] - External Input 3 High Level Trigger Enable
 */
#define ITU_EXTRHT_EXT3_HLVL_TRIG_EN_POS    (19)
#define ITU_EXTRHT_EXT3_HLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTRHT_EXT3_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT3_HLVL_TRIG_ENABLE    (0x1UL << ITU_EXTRHT_EXT3_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT3_HLVL_TRIG_DISABLE   (0x0UL << ITU_EXTRHT_EXT3_HLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[18] - External Input 2 High Level Trigger Enable
 */
#define ITU_EXTRHT_EXT2_HLVL_TRIG_EN_POS    (18)
#define ITU_EXTRHT_EXT2_HLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTRHT_EXT2_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT2_HLVL_TRIG_ENABLE    (0x1UL << ITU_EXTRHT_EXT2_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT2_HLVL_TRIG_DISABLE   (0x0UL << ITU_EXTRHT_EXT2_HLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[17] - External Input 1 High Level Trigger Enable
 */
#define ITU_EXTRHT_EXT1_HLVL_TRIG_EN_POS    (17)
#define ITU_EXTRHT_EXT1_HLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTRHT_EXT1_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT1_HLVL_TRIG_ENABLE    (0x1UL << ITU_EXTRHT_EXT1_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT1_HLVL_TRIG_DISABLE   (0x0UL << ITU_EXTRHT_EXT1_HLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[16] - External Input 0 High Level Trigger Enable
 */
#define ITU_EXTRHT_EXT0_HLVL_TRIG_EN_POS    (16)
#define ITU_EXTRHT_EXT0_HLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTRHT_EXT0_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT0_HLVL_TRIG_ENABLE    (0x1UL << ITU_EXTRHT_EXT0_HLVL_TRIG_EN_POS)
#define ITU_EXTRHT_EXT0_HLVL_TRIG_DISABLE   (0x0UL << ITU_EXTRHT_EXT0_HLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[3] - External Input 3 Rising Trigger Enable
 */
#define ITU_EXTRHT_EXT3_RISING_TRIG_EN_POS  (3)
#define ITU_EXTRHT_EXT3_RISING_TRIG_EN_MSK  (0x1UL << ITU_EXTRHT_EXT3_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT3_RISING_TRIG_ENABLE  (0x1UL << ITU_EXTRHT_EXT3_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT3_RISING_TRIG_DISABLE (0x0UL << ITU_EXTRHT_EXT3_RISING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[2] - External Input 2 Rising Trigger Enable
 */
#define ITU_EXTRHT_EXT2_RISING_TRIG_EN_POS  (2)
#define ITU_EXTRHT_EXT2_RISING_TRIG_EN_MSK  (0x1UL << ITU_EXTRHT_EXT2_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT2_RISING_TRIG_ENABLE  (0x1UL << ITU_EXTRHT_EXT2_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT2_RISING_TRIG_DISABLE (0x0UL << ITU_EXTRHT_EXT2_RISING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[1] - External Input 1 Rising Trigger Enable
 */
#define ITU_EXTRHT_EXT1_RISING_TRIG_EN_POS  (1)
#define ITU_EXTRHT_EXT1_RISING_TRIG_EN_MSK  (0x1UL << ITU_EXTRHT_EXT1_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT1_RISING_TRIG_ENABLE  (0x1UL << ITU_EXTRHT_EXT1_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT1_RISING_TRIG_DISABLE (0x0UL << ITU_EXTRHT_EXT1_RISING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTRHT[0] - External Input 0 Rising Trigger Enable
 */
#define ITU_EXTRHT_EXT0_RISING_TRIG_EN_POS  (0)
#define ITU_EXTRHT_EXT0_RISING_TRIG_EN_MSK  (0x1UL << ITU_EXTRHT_EXT0_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT0_RISING_TRIG_ENABLE  (0x1UL << ITU_EXTRHT_EXT0_RISING_TRIG_EN_POS)
#define ITU_EXTRHT_EXT0_RISING_TRIG_DISABLE (0x0UL << ITU_EXTRHT_EXT0_RISING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[19] - External Input 3 Low Level Trigger Enable
 */
#define ITU_EXTFLT_EXT3_LLVL_TRIG_EN_POS    (19)
#define ITU_EXTFLT_EXT3_LLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTFLT_EXT3_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT3_LLVL_TRIG_ENABLE    (0x1UL << ITU_EXTFLT_EXT3_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT3_LLVL_TRIG_DISABLE   (0x0UL << ITU_EXTFLT_EXT3_LLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[18] - External Input 2 Low Level Trigger Enable
 */
#define ITU_EXTFLT_EXT2_LLVL_TRIG_EN_POS    (18)
#define ITU_EXTFLT_EXT2_LLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTFLT_EXT2_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT2_LLVL_TRIG_ENABLE    (0x1UL << ITU_EXTFLT_EXT2_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT2_LLVL_TRIG_DISABLE   (0x0UL << ITU_EXTFLT_EXT2_LLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[17] - External Input 1 Low Level Trigger Enable
 */
#define ITU_EXTFLT_EXT1_LLVL_TRIG_EN_POS    (17)
#define ITU_EXTFLT_EXT1_LLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTFLT_EXT1_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT1_LLVL_TRIG_ENABLE    (0x1UL << ITU_EXTFLT_EXT1_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT1_LLVL_TRIG_DISABLE   (0x0UL << ITU_EXTFLT_EXT1_LLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[16] - External Input 0 Low Level Trigger Enable
 */
#define ITU_EXTFLT_EXT0_LLVL_TRIG_EN_POS    (16)
#define ITU_EXTFLT_EXT0_LLVL_TRIG_EN_MSK    (0x1UL << ITU_EXTFLT_EXT0_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT0_LLVL_TRIG_ENABLE    (0x1UL << ITU_EXTFLT_EXT0_LLVL_TRIG_EN_POS)
#define ITU_EXTFLT_EXT0_LLVL_TRIG_DISABLE   (0x0UL << ITU_EXTFLT_EXT0_LLVL_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[3] - External Input 3 Falling Trigger Enable
 */
#define ITU_EXTFLT_EXT3_FALLING_TRIG_EN_POS      (3)
#define ITU_EXTFLT_EXT3_FALLING_TRIG_EN_MSK      (0x1UL << ITU_EXTFLT_EXT3_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT3_FALLING_TRIG_ENABLE      (0x1UL << ITU_EXTFLT_EXT3_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT3_FALLING_TRIG_DISABLE     (0x0UL << ITU_EXTFLT_EXT3_FALLING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[2] - External Input 2 Falling Trigger Enable
 */
#define ITU_EXTFLT_EXT2_FALLING_TRIG_EN_POS      (2)
#define ITU_EXTFLT_EXT2_FALLING_TRIG_EN_MSK      (0x1UL << ITU_EXTFLT_EXT2_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT2_FALLING_TRIG_ENABLE      (0x1UL << ITU_EXTFLT_EXT2_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT2_FALLING_TRIG_DISABLE     (0x0UL << ITU_EXTFLT_EXT2_FALLING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[1] - External Input 1 Falling Trigger Enable
 */
#define ITU_EXTFLT_EXT1_FALLING_TRIG_EN_POS      (1)
#define ITU_EXTFLT_EXT1_FALLING_TRIG_EN_MSK      (0x1UL << ITU_EXTFLT_EXT1_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT1_FALLING_TRIG_ENABLE      (0x1UL << ITU_EXTFLT_EXT1_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT1_FALLING_TRIG_DISABLE     (0x0UL << ITU_EXTFLT_EXT1_FALLING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTFLT[0] - External Input 0 Falling Trigger Enable
 */
#define ITU_EXTFLT_EXT0_FALLING_TRIG_EN_POS      (0)
#define ITU_EXTFLT_EXT0_FALLING_TRIG_EN_MSK      (0x1UL << ITU_EXTFLT_EXT0_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT0_FALLING_TRIG_ENABLE      (0x1UL << ITU_EXTFLT_EXT0_FALLING_TRIG_EN_POS)
#define ITU_EXTFLT_EXT0_FALLING_TRIG_DISABLE     (0x0UL << ITU_EXTFLT_EXT0_FALLING_TRIG_EN_POS)

/*
 * Bit definition for ITU_EXTIFLG[3] - External Input 3 Interrupt Flag
 */
#define ITU_EXTIFLG_EXT3_INTF_POS           (3)
#define ITU_EXTIFLG_EXT3_INTF_MSK           (0x1UL << ITU_EXTIFLG_EXT3_INTF_POS)
#define ITU_EXTIFLG_EXT3_INT_FLAG           (0x1UL << ITU_EXTIFLG_EXT3_INTF_POS)

/*
 * Bit definition for ITU_EXTIFLG[2] - External Input 2 Interrupt Flag
 */
#define ITU_EXTIFLG_EXT2_INTF_POS           (2)
#define ITU_EXTIFLG_EXT2_INTF_MSK           (0x1UL << ITU_EXTIFLG_EXT2_INTF_POS)
#define ITU_EXTIFLG_EXT2_INT_FLAG           (0x1UL << ITU_EXTIFLG_EXT2_INTF_POS)

/*
 * Bit definition for ITU_EXTIFLG[1] - External Input 1 Interrupt Flag
 */
#define ITU_EXTIFLG_EXT1_INTF_POS           (1)
#define ITU_EXTIFLG_EXT1_INTF_MSK           (0x1UL << ITU_EXTIFLG_EXT1_INTF_POS)
#define ITU_EXTIFLG_EXT1_INT_FLAG           (0x1UL << ITU_EXTIFLG_EXT1_INTF_POS)

/*
 * Bit definition for ITU_EXTIFLG[0] - External Input 0 Interrupt Flag
 */
#define ITU_EXTIFLG_EXT0_INTF_POS           (0)
#define ITU_EXTIFLG_EXT0_INTF_MSK           (0x1UL << ITU_EXTIFLG_EXT0_INTF_POS)
#define ITU_EXTIFLG_EXT0_INT_FLAG           (0x1UL << ITU_EXTIFLG_EXT0_INTF_POS)

/*
 * Bit definition for ITU_EXTEFLG[4] - Key Change Event Flag
 */
#define ITU_EXTEFLG_KEYCHG_EVTF_POS         (4)
#define ITU_EXTEFLG_KEYCHG_EVTF_MSK         (0x1UL << ITU_EXTEFLG_KEYCHG_EVTF_POS)
#define ITU_EXTEFLG_KEYCHG_EVT_FLAG         (0x1UL << ITU_EXTEFLG_KEYCHG_EVTF_POS)

/*
 * Bit definition for ITU_EXTEFLG[3] - External Input 3 Event Flag
 */
#define ITU_EXTEFLG_EXT3_EVTF_POS           (3)
#define ITU_EXTEFLG_EXT3_EVTF_MSK           (0x1UL << ITU_EXTEFLG_EXT3_EVTF_POS)
#define ITU_EXTEFLG_EXT3_EVT_FLAG           (0x1UL << ITU_EXTEFLG_EXT3_EVTF_POS)

/*
 * Bit definition for ITU_EXTEFLG[2] - External Input 2 Event Flag
 */
#define ITU_EXTEFLG_EXT2_EVTF_POS           (2)
#define ITU_EXTEFLG_EXT2_EVTF_MSK           (0x1UL << ITU_EXTEFLG_EXT2_EVTF_POS)
#define ITU_EXTEFLG_EXT2_EVT_FLAG           (0x1UL << ITU_EXTEFLG_EXT2_EVTF_POS)

/*
 * Bit definition for ITU_EXTEFLG[1] - External Input 1 Event Flag
 */
#define ITU_EXTEFLG_EXT1_EVTF_POS           (1)
#define ITU_EXTEFLG_EXT1_EVTF_MSK           (0x1UL << ITU_EXTEFLG_EXT1_EVTF_POS)
#define ITU_EXTEFLG_EXT1_EVT_FLAG           (0x1UL << ITU_EXTEFLG_EXT1_EVTF_POS)

/*
 * Bit definition for ITU_EXTEFLG[0] - External Input 0 Event Flag
 */
#define ITU_EXTEFLG_EXT0_EVTF_POS           (0)
#define ITU_EXTEFLG_EXT0_EVTF_MSK           (0x1UL << ITU_EXTEFLG_EXT0_EVTF_POS)
#define ITU_EXTEFLG_EXT0_EVT_FLAG           (0x1UL << ITU_EXTEFLG_EXT0_EVTF_POS)


/*---------------------------------------------------------------------------------------
 * Analog control unit
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t REG33_CTRL;
	__IO uint32_t RESERVED1;
	__IO uint32_t RESERVED2;
	__IO uint32_t PLL_CTRL;
	__IO uint32_t X32K_CTRL;
	__IO uint32_t I32K_CTRL;
	__I  uint32_t RESERVED3[6];
	__IO uint32_t BVD_CTRL;
	__IO uint32_t APAD_CTRL;
} ACU_TYPE_DEF;

/*
 * Bit definition for ACU_REG33_CTRL[5] - REG33 SPI Regulator Sleep Mode Control
 */
#define ACU_REG33_CTRL_SLEEP_EN_POS         (5)
#define ACU_REG33_CTRL_SLEEP_EN_MSK         (0x1UL << ACU_REG33_CTRL_SLEEP_EN_POS)
#define ACU_REG33_CTRL_SLEEP_EN_ENABLE      (0x1UL << ACU_REG33_CTRL_SLEEP_EN_POS)
#define ACU_REG33_CTRL_SLEEP_EN_DISABLE     (0x0UL << ACU_REG33_CTRL_SLEEP_EN_POS)

/*
 * Bit definition for ACU_REG33_CTRL[4] - DS-ADC(Mic) Regulator Enable
 */
#define ACU_REG33_CTRL_DSADC_REG_EN_POS     (4)
#define ACU_REG33_CTRL_DSADC_REG_EN_MSK     (0x1UL << ACU_REG33_CTRL_DSADC_REG_EN_POS)
#define ACU_REG33_CTRL_DSADC_REG_EN_ENABLE  (0x1UL << ACU_REG33_CTRL_DSADC_REG_EN_POS)
#define ACU_REG33_CTRL_DSADC_REG_EN_DISABLE (0x0UL << ACU_REG33_CTRL_DSADC_REG_EN_POS)

/*
 * Bit definition for ACU_REG33_CTRL[3:2] - REG33 SPI Regulator Output Voltage Select
 */
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS   (2)
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_MSK   (0x3UL << ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS)
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_3D6V  (0x3UL << ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS)
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_3D3V  (0x2UL << ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS)
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_3D0V  (0x1UL << ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS)
#define ACU_REG33_CTRL_OUTPUT_VOL_SEL_2D7V  (0x0UL << ACU_REG33_CTRL_OUTPUT_VOL_SEL_POS)

/*
 * Bit definition for ACU_PLL_CTRL[8] - PLL Clock selection
 */
#define ACU_PLL_CTRL_CLK_SEL_POS            (8)
#define ACU_PLL_CTRL_CLK_SEL_MSK						(0x7UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_81D920M        (0x7UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_73D728M        (0x6UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_65D536M        (0x5UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_57D344M        (0x4UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_49D192M        (0x3UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_40D960M        (0x2UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_32D768M        (0x1UL << ACU_PLL_CTRL_CLK_SEL_POS)
#define ACU_PLL_CTRL_CLK_SEL_24D576M        (0x0UL << ACU_PLL_CTRL_CLK_SEL_POS)

/*
 * Bit definition for ACU_CTRL[0] - PLL Enable
 */
#define ACU_PLL_CTRL_EN_POS                 (0)
#define ACU_PLL_CTRL_PLL_EN_MSK							(0x1UL << ACU_PLL_CTRL_EN_POS)
#define ACU_PLL_CTRL_PLL_ENABLE							(0x1UL << ACU_PLL_CTRL_EN_POS)
#define ACU_PLL_CTRL_PLL_DISABLE						(0x0UL << ACU_PLL_CTRL_EN_POS)

/*
 * Bit definition for ACU_X32K_CTRL[2] - Iosc32K/X32K ON/OFF in deep sleep mode
 */
#define ACU_X32K_CTRL_32K_SLP_EN_POS        (2)
#define ACU_X32K_CTRL_32K_SLP_EN_MSK				(0x1UL << ACU_X32K_CTRL_32K_SLP_EN_POS)
#define ACU_X32K_CTRL_32K_SLP_ENABLE				(0x1UL << ACU_X32K_CTRL_32K_SLP_EN_POS)
#define ACU_X32K_CTRL_32K_SLP_DISABLE			  (0x0UL << ACU_X32K_CTRL_32K_SLP_EN_POS)

/*
 * Bit definition for ACU_X32K_CTRL[1] - Strong/Weak mode Select
 */
#define ACU_X32K_CTRL_MODE_SEL_POS          (1)
#define ACU_X32K_CTRL_MODE_SEL_MSK					(0x1UL << ACU_X32K_CTRL_MODE_SEL_POS)
#define ACU_X32K_CTRL_MODE_STRONG						(0x1UL << ACU_X32K_CTRL_MODE_SEL_POS)
#define ACU_X32K_CTRL_MODE_WEAK							(0x0UL << ACU_X32K_CTRL_MODE_SEL_POS)

/*
 * Bit definition for ACU_X32K_CTRL[0] - Enable X32K , low active
 */
#define ACU_X32K_CTRL_X32K_EN_POS           (0)
#define ACU_X32K_CTRL_X32K_EN_MSK						(0x1UL << ACU_X32K_CTRL_X32K_EN_POS)
#define ACU_X32K_CTRL_X32K_DISABLE					(0x1UL << ACU_X32K_CTRL_X32K_EN_POS)
#define ACU_X32K_CTRL_X32K_ENABLE						(0x0UL << ACU_X32K_CTRL_X32K_EN_POS)

/*
 * Bit definition for ACU_I32K_CTRL[0] - Enable I32K , low active
 */
#define ACU_I32K_CTRL_I32K_EN_POS           (0)
#define ACU_I32K_CTRL_I32K_EN_MSK						(0x1UL << ACU_I32K_CTRL_I32K_EN_POS)
#define ACU_I32K_CTRL_I32K_DISABLE					(0x1UL << ACU_I32K_CTRL_I32K_EN_POS)
#define ACU_I32K_CTRL_I32K_ENABLE						(0x0UL << ACU_I32K_CTRL_I32K_EN_POS)

/*
 * Bit definition for ACU_BVD_CTRL[3] - Battery voltage detect enable
 */
#define ACU_BVD_CTRL_EN_POS            			(3)
#define ACU_BVD_CTRL_EN_MSK									(0x1UL << ACU_BVD_CTRL_EN_POS)
#define ACU_BVD_CTRL_ENABLE	  							(0x1UL << ACU_BVD_CTRL_EN_POS)
#define ACU_BVD_CTRL_DISABLE								(0x0UL << ACU_BVD_CTRL_EN_POS)

/*
 * Bit definition for ACU_BVD_CTRL[2:0] - Battery voltage detect trigger level,tolerance +/-7.5% (Read only)
 */
#define ACU_BVD_LVL_SEL_POS            			(0)
#define ACU_BVD_LVL_SEL_MSK									(0x7UL << ACU_BVD_LVL_SEL_POS)

/*
 * Bit definition for ACU_APAD[8] - Crystal 32KHz pad (IOA[14:13]) enable
 */
#define ACU_APAD_X32K_PAD_EN_POS            (8)
#define ACU_APAD_X32K_PAD_EN_MSK						(0x1UL << ACU_APAD_X32K_PAD_EN_POS)
#define ACU_APAD_X32K_PAD_ENABLE						(0x1UL << ACU_APAD_X32K_PAD_EN_POS)
#define ACU_APAD_X32K_PAD_DISABLE						(0x0UL << ACU_APAD_X32K_PAD_EN_POS)

/*
 * Bit definition for ACU_APAD[7:0] - Line-in pad enable
 */
#define ACU_APAD_LINE_PAD_EN_POS        		(0)
#define ACU_APAD_LINE_PAD_EN_MSK						(0xFFUL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA17							(0x80UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA18							(0x40UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA19							(0x20UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA20							(0x10UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA21							(0x08UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA22							(0x04UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA23							(0x02UL << ACU_APAD_LINE_PAD_EN_POS)
#define ACU_APAD_LINE_PAD_IOA24							(0x01UL << ACU_APAD_LINE_PAD_EN_POS)


/*---------------------------------------------------------------------------------------
 * Non-Volatile Memory Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL_UNLOCK;                // Flash Control Register Unlock Key
	__IO uint32_t RESERVED1;
	__IO uint32_t CTRL;                       // Flash Control Register
	__IO uint32_t ERASE_ADDR;                 // Flash Erase Address Register
	__IO uint32_t STS;
	__IO uint32_t OPTION0_STS;
	__IO uint32_t RESERVED2;
	__IO uint32_t RESERVED3;
	__IO uint32_t ERASE_CTRL;                 // Flash Erase Control Register
} FLASH_TYPE_DEF;

#define UNLOCK_KEY1													0xABCD5678
#define UNLOCK_KEY2													0x1234FEDC

/*
 * Bit definition for FLASH_CTRL[11:8] - Flash Erase Type
 */
#define FLASH_CTRL_TYPE_POS                 (8)
#define FLASH_CTRL_TYPE_MSK									(0x3UL << FLASH_CTRL_TYPE_POS)
#define FLASH_CTRL_TYPE_CHIPERASE           (0x3UL << FLASH_CTRL_TYPE_POS)
#define FLASH_CTRL_TYPE_PAGEERASE           (0x2UL << FLASH_CTRL_TYPE_POS)
#define FLASH_CTRL_TYPE_PROGRAM             (0x1UL << FLASH_CTRL_TYPE_POS)
#define FLASH_CTRL_TYPE_READ                (0x0UL << FLASH_CTRL_TYPE_POS)

/*
 * Bit definition for FLASH_CTRL[0] - Lock / Unlock Status Flag
 */
#define FLASH_CTRL_LOCK_POS                 (0)
#define FLASH_CTRL_LOCK_MSK                 (0x1UL << FLASH_CTRL_LOCK_POS)
#define FLASH_CTRL_LOCK_FLAG                (0x1UL << FLASH_CTRL_LOCK_POS)
#define FLASH_CTRL_LOCK                     (0x1UL << FLASH_CTRL_LOCK_POS)

/*
 * Bit definition for FLASH_STS[0]- Status Flag
 */
#define FLASH_STS_POS                       (0)
#define FLASH_STS_MSK                       (0x1UL << FLASH_STS_POS)
#define FLASH_STS_FLAG                      (0x1UL << FLASH_STS_POS)

/*
 * Bit definition for OPTION0_STS[0]- Security Status Flag
 */
#define FLASH_SECURITY_STS_POS              (0)
#define FLASH_SECURITY_STS_MSK              (0x1UL << FLASH_STS_POS)
#define FLASH_SECURITY_STS_FLAG             (0x1UL << FLASH_STS_POS)

/*
 * Bit definition for FLASH_OPTION0_STS[2:0]- Latency Wait State Configuration
 */
#define FLASH_OPTION0_STS_WAITSTATE_POS     (0)
#define FLASH_OPTION0_STS_WAITSTATE_MSK     (0x7UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_7WAITSTATE        (0x7UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_6WAITSTATE        (0x6UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_5WAITSTATE        (0x5UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_4WAITSTATE        (0x4UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_3WAITSTATE        (0x3UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_2WAITSTATE        (0x2UL << FLASH_OPTION0_STS_WAITSTATE_POS)
#define FLASH_OPTION0_STS_1WAITSTATE        (0x1UL << FLASH_OPTION0_STS_WAITSTATE_POS)

/*
 * Bit definition for ERASE_CTRL[0]- NVM Operation Start
 */
#define FLASH_ERASE_CTRL_NVM_START_POS      (0)
#define FLASH_ERASE_CTRL_NVM_START_MSK      (0x1UL << FLASH_ERASE_CTRL_NVM_START_POS)
#define FLASH_ERASE_CTRL_NVM_START          (0x1UL << FLASH_ERASE_CTRL_NVM_START_POS)


/*---------------------------------------------------------------------------------------
 * MAC Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                       // MAC Control Register
	__IO uint32_t LENGTH;                     // MAC Length Register
	__IO uint32_t ADDR_X ; 		                // MAC Start address X Register
	__IO uint32_t ADDR_Y;                     // MAC Start address Y Register
	__IO uint32_t STEP_XY;                    // MAC Step X/Y Register
	__IO int32_t OUTPUT;                      // MAC Output Register
	__IO int32_t OUTPUT_EXT8;                 // MAC Output Extention Register
	__IO int32_t SATURATION;                  // MAC OUT Saturation Register
	__IO int32_t INTSTS;                      // MAC Interrupt Status Register
} MAC_TYPE_DEF;

/*
 * Bit definition for MAC_CTRL[12:8] - Output shift control
 */
#define MAC_CTRL_OUTPUT_SHIFT_POS           (8)
#define MAC_CTRL_OUTPUT_SHIFT_MSK           (0x1FUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_LEFT_1        (0x1FUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_16      (0x10UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_15      (0x0FUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_14      (0x0EUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_13      (0x0DUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_12      (0x0CUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_11      (0x0BUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_10      (0x0AUL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_9       (0x09UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_8       (0x08UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_7       (0x07UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_6       (0x06UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_5       (0x05UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_4       (0x04UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_3       (0x03UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_2       (0x02UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_1       (0x01UL << MAC_CTRL_OUTPUT_SHIFT_POS)
#define MAC_CTRL_OUTPUT_SHIFT_RIGHT_0       (0x00UL << MAC_CTRL_OUTPUT_SHIFT_POS)

/*
 * Bit definition for MAC_CTRL[7] - MAC interrupt enable
 */
#define MAC_CTRL_INT_EN_POS                 (7)
#define MAC_CTRL_INT_EN_MSK                 (0x1UL << MAC_CTRL_INT_EN_POS)
#define MAC_CTRL_INT_ENABLE                 (0x1UL << MAC_CTRL_INT_EN_POS)
#define MAC_CTRL_INT_DISBLE                 (0x0UL << MAC_CTRL_INT_EN_POS)

/*
 * Bit definition for MAC_CTRL[6] - Operation mode selection
 */
#define MAC_CTRL_OPERATION_MODE_SEL_POS     (6)
#define MAC_CTRL_OPERATION_MODE_SEL_MSK     (0x1UL << MAC_CTRL_OPERATION_MODE_SEL_POS)
#define MAC_CTRL_OPERATION_MODE_SEL_SU      (0x1UL << MAC_CTRL_OPERATION_MODE_SEL_POS)
#define MAC_CTRL_OPERATION_MODE_SEL_SS      (0x0UL << MAC_CTRL_OPERATION_MODE_SEL_POS)

/*
 * Bit definition for MAC_CTRL[5:4] - Saturation mode selection
 */
#define MAC_CTRL_SATURATION_MODE_SEL_POS    (4)
#define MAC_CTRL_SATURATION_MODE_SEL_MSK    (0x3UL << MAC_CTRL_SATURATION_MODE_SEL_POS)
#define MAC_CTRL_SATURATION_MODE_SEL_8B     (0x2UL << MAC_CTRL_SATURATION_MODE_SEL_POS)
#define MAC_CTRL_SATURATION_MODE_SEL_32B    (0x1UL << MAC_CTRL_SATURATION_MODE_SEL_POS)
#define MAC_CTRL_SATURATION_MODE_SEL_16B    (0x0UL << MAC_CTRL_SATURATION_MODE_SEL_POS)

/*
 * Bit definition for MAC_CTRL[1] - MAC reset
 */
#define MAC_CTRL_RESET_POS                  (1)
#define MAC_CTRL_RESET_MSK                  (0x1UL << MAC_CTRL_RESET_POS)
#define MAC_CTRL_RESET                      (0x1UL << MAC_CTRL_RESET_POS)

/*
 * Bit definition for MAC_CTRL[0] - MAC start
 */
#define MAC_CTRL_START_POS                  (0)
#define MAC_CTRL_START_MSK                  (0x1UL << MAC_CTRL_START_POS)
#define MAC_CTRL_START                      (0x1UL << MAC_CTRL_START_POS)
#define MAC_CTRL_BUSY                       (0x1UL << MAC_CTRL_START_POS)

/*
 * Bit definition for MAC_LENGTH[7:0] - MAC length
 */
#define MAC_CTRL_LENGTH_POS                 (0)
#define MAC_CTRL_LENGTH_MSK                 (0xFFUL << MAC_CTRL_LENGTH_POS)

/*
 * Bit definition for MAC_STEP_XY[12:8] - MAC AddressY Step control
 */
#define MAC_STEP_XY_ADDRY_STEP_POS          (8)
#define MAC_STEP_XY_ADDRY_STEP_MSK          (0x1FUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_16     (0x10UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_15     (0x11UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_14     (0x12UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_13     (0x13UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_12     (0x14UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_11     (0x15UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_10     (0x16UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_9      (0x17UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_8      (0x18UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_7      (0x19UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_6      (0x1AUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_5      (0x1BUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_4      (0x1CUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_3      (0x1DUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_2      (0x1EUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_MINUS_1      (0x1FUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_15      (0xFUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_14      (0xEUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_13      (0xDUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_12      (0xCUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_11      (0xBUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_10      (0xAUL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_9       (0x9UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_8       (0x8UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_7       (0x7UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_6       (0x6UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_5       (0x5UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_4       (0x4UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_3       (0x3UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_2       (0x2UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_1       (0x1UL << MAC_STEP_XY_ADDRY_STEP_POS)
#define MAC_STEP_XY_ADDRY_STEP_PLUS_0       (0x0UL << MAC_STEP_XY_ADDRY_STEP_POS)

/*
 * Bit definition for MAC_STEP_XY[4:0] - MAC AddressX Step control
 */
#define MAC_STEP_XY_ADDRX_STEP_POS          (0)
#define MAC_STEP_XY_ADDRX_STEP_MSK          (0x1FUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_16     (0x10UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_15     (0x11UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_14     (0x12UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_13     (0x13UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_12     (0x14UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_11     (0x15UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_10     (0x16UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_9      (0x17UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_8      (0x18UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_7      (0x19UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_6      (0x1AUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_5      (0x1BUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_4      (0x1CUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_3      (0x1DUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_2      (0x1EUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_MINUS_1      (0x1FUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_15      (0xFUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_14      (0xEUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_13      (0xDUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_12      (0xCUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_11      (0xBUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_10      (0xAUL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_9       (0x9UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_8       (0x8UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_7       (0x7UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_6       (0x6UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_5       (0x5UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_4       (0x4UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_3       (0x3UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_2       (0x2UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_1       (0x1UL << MAC_STEP_XY_ADDRX_STEP_POS)
#define MAC_STEP_XY_ADDRX_STEP_PLUS_0       (0x0UL << MAC_STEP_XY_ADDRX_STEP_POS)

/*
 * Bit definition for MAC_STS[0] - MAC interrupt flag
 */
#define MAC_INTSTS_INTF_POS                 (0)
#define MAC_INTSTS_INTF_MSK                 (0x1UL << MAC_INTSTS_INTF_POS)
#define MAC_INTSTS_INT_FLAG                 (0x1UL << MAC_INTSTS_INTF_POS)


/*---------------------------------------------------------------------------------------
 * CCP Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t TMCMP_CTRL;                 // CCP Timer Control and Compare Mode Control Register
	__IO uint32_t CAP_CTRL;                   // CCP Capture Mode Control Register
	__IO uint32_t PWM_CTRL;                   // CCP PWM Mode Control Register
	__I  uint32_t RESERVED;  		              // Reserved
	__IO uint32_t INTEN;                      // CCP Interrupt Enable Register
	__IO uint32_t INTSTS;                     // CCP Interrupt Status Register
	__IO uint32_t TMR_COUNT;                  // CCP Timer Actual Value Register
	__IO uint32_t TMR_PLOAD;                  // CCP Timer Pre-Load Data Register
	__IO uint32_t CCPR0;                      // CCP Compare/Capture/PWM duty Register 0
	__IO uint32_t CCPR1;                      // CCP Compare/Capture/PWM duty Register 1
	__IO uint32_t CCPR2;                      // CCP Compare/Capture/PWM duty Register 2
	__IO uint32_t CCPR3;                      // CCP Compare/Capture/PWM duty Register 3
	__IO uint32_t PWM_DTIME;                  // CCP PWM Dead-Time Register
} CCP_TYPE_DEF;

/*
 * Bit definition for CCPx TMCMP_CTRL[15] - CCPx compare channel 3 enable
 */
#define CCP_TMCMPCTRL_CMP3_EN_POS           (15)
#define CCP_TMCMPCTRL_CMP3_EN_MSK           (0x1UL << CCP_TMCMPCTRL_CMP3_EN_POS)
#define CCP_TMCMPCTRL_CMP3_ENABLE           (0x1UL << CCP_TMCMPCTRL_CMP3_EN_POS)
#define CCP_TMCMPCTRL_CMP3_DISABLE          (0x0UL << CCP_TMCMPCTRL_CMP3_EN_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[14] - CCPx compare channel 2 enable
 */
#define CCP_TMCMPCTRL_CMP2_EN_POS           (14)
#define CCP_TMCMPCTRL_CMP2_EN_MSK           (0x1UL << CCP_TMCMPCTRL_CMP2_EN_POS)
#define CCP_TMCMPCTRL_CMP2_ENABLE           (0x1UL << CCP_TMCMPCTRL_CMP2_EN_POS)
#define CCP_TMCMPCTRL_CMP2_DISABLE          (0x0UL << CCP_TMCMPCTRL_CMP2_EN_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[13] - CCPx compare channel 1 enable
 */
#define CCP_TMCMPCTRL_CMP1_EN_POS           (13)
#define CCP_TMCMPCTRL_CMP1_EN_MSK           (0x1UL << CCP_TMCMPCTRL_CMP1_EN_POS)
#define CCP_TMCMPCTRL_CMP1_ENABLE           (0x1UL << CCP_TMCMPCTRL_CMP1_EN_POS)
#define CCP_TMCMPCTRL_CMP1_DISABLE          (0x0UL << CCP_TMCMPCTRL_CMP1_EN_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[12] - CCPx compare channel 0 enable
 */
#define CCP_TMCMPCTRL_CMP0_EN_POS           (12)
#define CCP_TMCMPCTRL_CMP0_EN_MSK           (0x1UL << CCP_TMCMPCTRL_CMP0_EN_POS)
#define CCP_TMCMPCTRL_CMP0_ENABLE           (0x1UL << CCP_TMCMPCTRL_CMP0_EN_POS)
#define CCP_TMCMPCTRL_CMP0_DISABLE          (0x0UL << CCP_TMCMPCTRL_CMP0_EN_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[11] - CCP1 PWM channel 3 control by CCPx Timer
 */
#define CCP1_PWM3_TIMER_CTRL_POS            (11)
#define CCP1_PWM3_TIMER_CTRL_MSK            (0x1UL << CCP1_PWM3_TIMER_CTRL_POS)
#define CCP1_PWM3_TIMER_CCP0                (0x1UL << CCP1_PWM3_TIMER_CTRL_POS)
#define CCP1_PWM3_TIMER_CCP1                (0x0UL << CCP1_PWM3_TIMER_CTRL_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[10] - CCP1 PWM channel 3 control by CCPx Timer
 */
#define CCP1_PWM2_TIMER_CTRL_POS            (10)
#define CCP1_PWM2_TIMER_CTRL_MSK            (0x1UL << CCP1_PWM2_TIMER_CTRL_POS)
#define CCP1_PWM2_TIMER_CCP0                (0x1UL << CCP1_PWM2_TIMER_CTRL_POS)
#define CCP1_PWM2_TIMER_CCP1                (0x0UL << CCP1_PWM2_TIMER_CTRL_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[8] - Timer up/down count selection
 */
#define CCP_TMCMPCTRL_TMR_UDC_SEL_POS       (8)
#define CCP_TMCMPCTRL_TMR_UDC_SEL_MSK       (0x1UL << CCP_TMCMPCTRL_TMR_UDC_SEL_POS)
#define CCP_TMCMPCTRL_TMR_UDC_UP_CNT        (0x1UL << CCP_TMCMPCTRL_TMR_UDC_SEL_POS)
#define CCP_TMCMPCTRL_TMR_UDC_DOWN_CNT      (0x0UL << CCP_TMCMPCTRL_TMR_UDC_SEL_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[7:4] - Timer input slock source selection
 */
#define CCP_TMCMPCTRL_TMR_CLK_SEL_POS       (4)
#define CCP_TMCMPCTRL_TMR_CLK_SEL_MSK       (0xFUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_TMC      (0x0FUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_TMB      (0x0EUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_TMA      (0x0DUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_EXT2     (0x0CUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_EXT1     (0x0BUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_IOSC_32K      (0x0AUL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_4096 (0x09UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_2048 (0x08UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_1024 (0x07UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_256  (0x06UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_64   (0x05UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_16   (0x04UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_8    (0x03UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_4    (0x02UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK_DIV_2    (0x01UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)
#define CCP_TMCMPCTRL_TMR_CLK_HCLK          (0x00UL << CCP_TMCMPCTRL_TMR_CLK_SEL_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[3:2] - Timer operating mode selection
 */
#define CCP_TMCMPCTRL_TMR_MODE_SEL_POS      (2)
#define CCP_TMCMPCTRL_TMR_MODE_SEL_MSK      (0x3UL << CCP_TMCMPCTRL_TMR_MODE_SEL_POS)
#define CCP_TMCMPCTRL_TMR_MODE_PWM          (0x2UL << CCP_TMCMPCTRL_TMR_MODE_SEL_POS)
#define CCP_TMCMPCTRL_TMR_MODE_CAPTURE      (0x1UL << CCP_TMCMPCTRL_TMR_MODE_SEL_POS)
#define CCP_TMCMPCTRL_TMR_MODE_COMPARE      (0x0UL << CCP_TMCMPCTRL_TMR_MODE_SEL_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[1] - Data direct write enable
 */
#define CCP_TMCMPCTRL_DIRECT_WR_EN_POS      (1)
#define CCP_TMCMPCTRL_DIRECT_WR_EN_MSK      (0x1UL << CCP_TMCMPCTRL_DIRECT_WR_EN_POS)
#define CCP_TMCMPCTRL_DIRECT_WR_ENABLE      (0x1UL << CCP_TMCMPCTRL_DIRECT_WR_EN_POS)
#define CCP_TMCMPCTRL_DIRECT_WR_DISABLE     (0x0UL << CCP_TMCMPCTRL_DIRECT_WR_EN_POS)

/*
 * Bit definition for CCPx TMCMP_CTRL[0] - Timer enable
 */
#define CCP_TMCMPCTRL_TMR_EN_POS            (0)
#define CCP_TMCMPCTRL_TMR_EN_MSK            (0x1UL << CCP_TMCMPCTRL_TMR_EN_POS)
#define CCP_TMCMPCTRL_TMR_ENABLE            (0x1UL << CCP_TMCMPCTRL_TMR_EN_POS)
#define CCP_TMCMPCTRL_TMR_DISABLE           (0x0UL << CCP_TMCMPCTRL_TMR_EN_POS)

/*
 * Bit definition for CCPx CAP_CTRL[14:12] - Capture mode low pass filter selection
 */
#define CCP_CAPCTRL_CAP_LPF_SEL_POS         (12)
#define CCP_CAPCTRL_CAP_LPF_SEL_MSK         (0x7UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_128HCLK     (0x7UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_80HCLK      (0x6UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_40HCLK      (0x5UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_32HCLK      (0x4UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_16HCLK      (0x3UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_8HCLK       (0x2UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_SEL_4HCLK       (0x1UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)
#define CCP_CAPCTRL_CAP_LPF_DISABLE         (0x0UL << CCP_CAPCTRL_CAP_LPF_SEL_POS)

/*
 * Bit definition for CCPx CAP_CTRL[11:10] - CCPx CAP3 sample edge selection
 */
#define CCP_CAPCTRL_CAP3_EDGE_POS           (10)
#define CCP_CAPCTRL_CAP3_EDGE_MSK           (0x3UL << CCP_CAPCTRL_CAP3_EDGE_POS)
#define CCP_CAPCTRL_CAP3_EDGE_DUAL          (0x3UL << CCP_CAPCTRL_CAP3_EDGE_POS)
#define CCP_CAPCTRL_CAP3_EDGE_FALL          (0x2UL << CCP_CAPCTRL_CAP3_EDGE_POS)
#define CCP_CAPCTRL_CAP3_EDGE_RISE          (0x1UL << CCP_CAPCTRL_CAP3_EDGE_POS)
#define CCP_CAPCTRL_CAP3_EDGE_NO_ACTIVE     (0x0UL << CCP_CAPCTRL_CAP3_EDGE_POS)

/*
 * Bit definition for CCPx CAP_CTRL[9:8] - CCPx CAP2 sample edge selection
 */
#define CCP_CAPCTRL_CAP2_EDGE_POS           (8)
#define CCP_CAPCTRL_CAP2_EDGE_MSK           (0x3UL << CCP_CAPCTRL_CAP2_EDGE_POS)
#define CCP_CAPCTRL_CAP2_EDGE_DUAL          (0x3UL << CCP_CAPCTRL_CAP2_EDGE_POS)
#define CCP_CAPCTRL_CAP2_EDGE_FALL          (0x2UL << CCP_CAPCTRL_CAP2_EDGE_POS)
#define CCP_CAPCTRL_CAP2_EDGE_RISE          (0x1UL << CCP_CAPCTRL_CAP2_EDGE_POS)
#define CCP_CAPCTRL_CAP2_EDGE_NO_ACTIVE     (0x0UL << CCP_CAPCTRL_CAP2_EDGE_POS)

/*
 * Bit definition for CCPx CAP_CTRL[7:6] - CCPx CAP1 sample edge selection
 */
#define CCP_CAPCTRL_CAP1_EDGE_POS           (6)
#define CCP_CAPCTRL_CAP1_EDGE_MSK           (0x3UL << CCP_CAPCTRL_CAP1_EDGE_POS)
#define CCP_CAPCTRL_CAP1_EDGE_DUAL          (0x3UL << CCP_CAPCTRL_CAP1_EDGE_POS)
#define CCP_CAPCTRL_CAP1_EDGE_FALL          (0x2UL << CCP_CAPCTRL_CAP1_EDGE_POS)
#define CCP_CAPCTRL_CAP1_EDGE_RISE          (0x1UL << CCP_CAPCTRL_CAP1_EDGE_POS)
#define CCP_CAPCTRL_CAP1_EDGE_NO_ACTIVE     (0x0UL << CCP_CAPCTRL_CAP1_EDGE_POS)

/*
 * Bit definition for CCPx CAP_CTRL[5:4] - CCPx CAP0 sample edge selection
 */
#define CCP_CAPCTRL_CAP0_EDGE_POS           (4)
#define CCP_CAPCTRL_CAP0_EDGE_MSK           (0x3UL << CCP_CAPCTRL_CAP0_EDGE_POS)
#define CCP_CAPCTRL_CAP0_EDGE_DUAL          (0x3UL << CCP_CAPCTRL_CAP0_EDGE_POS)
#define CCP_CAPCTRL_CAP0_EDGE_FALL          (0x2UL << CCP_CAPCTRL_CAP0_EDGE_POS)
#define CCP_CAPCTRL_CAP0_EDGE_RISE          (0x1UL << CCP_CAPCTRL_CAP0_EDGE_POS)
#define CCP_CAPCTRL_CAP0_EDGE_NO_ACTIVE     (0x0UL << CCP_CAPCTRL_CAP0_EDGE_POS)

/*
 * Bit definition for CCPx CAP_CTRL[3] - CCPx capture channel 3 enable
 */
#define CCP_CAPCTRL_CAP3_EN_POS             (3)
#define CCP_CAPCTRL_CAP3_EN_MSK             (0x1UL << CCP_CAPCTRL_CAP3_EN_POS)
#define CCP_CAPCTRL_CAP3_ENABLE             (0x1UL << CCP_CAPCTRL_CAP3_EN_POS)
#define CCP_CAPCTRL_CAP3_DISABLE            (0x0UL << CCP_CAPCTRL_CAP3_EN_POS)

/*
 * Bit definition for CCPx CAP_CTRL[2] - CCPx capture channel 2 enable
 */
#define CCP_CAPCTRL_CAP2_EN_POS             (2)
#define CCP_CAPCTRL_CAP2_EN_MSK             (0x1UL << CCP_CAPCTRL_CAP2_EN_POS)
#define CCP_CAPCTRL_CAP2_ENABLE             (0x1UL << CCP_CAPCTRL_CAP2_EN_POS)
#define CCP_CAPCTRL_CAP2_DISABLE            (0x0UL << CCP_CAPCTRL_CAP2_EN_POS)

/*
 * Bit definition for CCPx CAP_CTRL[1] - CCPx capture channel 1 enable
 */
#define CCP_CAPCTRL_CAP1_EN_POS             (1)
#define CCP_CAPCTRL_CAP1_EN_MSK             (0x1UL << CCP_CAPCTRL_CAP1_EN_POS)
#define CCP_CAPCTRL_CAP1_ENABLE             (0x1UL << CCP_CAPCTRL_CAP1_EN_POS)
#define CCP_CAPCTRL_CAP1_DISABLE            (0x0UL << CCP_CAPCTRL_CAP1_EN_POS)

/*
 * Bit definition for CCPx CAP_CTRL[0] - CCPx capture channel 0 enable
 */
#define CCP_CAPCTRL_CAP0_EN_POS             (0)
#define CCP_CAPCTRL_CAP0_EN_MSK             (0x1UL << CCP_CAPCTRL_CAP0_EN_POS)
#define CCP_CAPCTRL_CAP0_ENABLE             (0x1UL << CCP_CAPCTRL_CAP0_EN_POS)
#define CCP_CAPCTRL_CAP0_DISABLE            (0x0UL << CCP_CAPCTRL_CAP0_EN_POS)

/*
 * Bit definition for CCPx PWM_CTRL[9] - CCPx PWM channel 2/3 operationg mode selection
 */
#define CCP_PWMCTRL_PWM23_CHM_POS           (9)
#define CCP_PWMCTRL_PWM23_CHM_MSK           (0x1UL << CCP_PWMCTRL_PWM23_CHM_POS)
#define CCP_PWMCTRL_PWM23_COMPLEMENT        (0x1UL << CCP_PWMCTRL_PWM23_CHM_POS)
#define CCP_PWMCTRL_PWM23_INDEPENDENT       (0x0UL << CCP_PWMCTRL_PWM23_CHM_POS)

/*
 * Bit definition for CCPx PWM_CTRL[8] - CCPx PWM channel 0/1 operationg mode selection
 */
#define CCP_PWMCTRL_PWM01_CHM_POS           (8)
#define CCP_PWMCTRL_PWM01_CHM_MSK           (0x1UL << CCP_PWMCTRL_PWM01_CHM_POS)
#define CCP_PWMCTRL_PWM01_COMPLEMENT        (0x1UL << CCP_PWMCTRL_PWM01_CHM_POS)
#define CCP_PWMCTRL_PWM01_INDEPENDENT       (0x0UL << CCP_PWMCTRL_PWM01_CHM_POS)

/*
 * Bit definition for CCPx PWM_CTRL[7] - CCPx PWM channel 3 polarity control
 */
#define CCP_PWMCTRL_PWM3_POL_POS            (7)
#define CCP_PWMCTRL_PWM3_POL_MSK            (0x1UL << CCP_PWMCTRL_PWM3_POL_POS)
#define CCP_PWMCTRL_PWM3_POL1               (0x1UL << CCP_PWMCTRL_PWM3_POL_POS)
#define CCP_PWMCTRL_PWM3_POL0               (0x0UL << CCP_PWMCTRL_PWM3_POL_POS)

/*
 * Bit definition for CCPx PWM_CTRL[6] - CCPx PWM channel 2 polarity control
 */
#define CCP_PWMCTRL_PWM2_POL_POS            (6)
#define CCP_PWMCTRL_PWM2_POL_MSK            (0x1UL << CCP_PWMCTRL_PWM2_POL_POS)
#define CCP_PWMCTRL_PWM2_POL1               (0x1UL << CCP_PWMCTRL_PWM2_POL_POS)
#define CCP_PWMCTRL_PWM2_POL0               (0x0UL << CCP_PWMCTRL_PWM2_POL_POS)

/*
 * Bit definition for CCPx PWM_CTRL[5] - CCPx PWM channel 1 polarity control
 */
#define CCP_PWMCTRL_PWM1_POL_POS            (5)
#define CCP_PWMCTRL_PWM1_POL_MSK            (0x1UL << CCP_PWMCTRL_PWM1_POL_POS)
#define CCP_PWMCTRL_PWM1_POL1               (0x1UL << CCP_PWMCTRL_PWM1_POL_POS)
#define CCP_PWMCTRL_PWM1_POL0               (0x0UL << CCP_PWMCTRL_PWM1_POL_POS)

/*
 * Bit definition for CCPx PWM_CTRL[4] - CCPx PWM channel 0 polarity control
 */
#define CCP_PWMCTRL_PWM0_POL_POS            (4)
#define CCP_PWMCTRL_PWM0_POL_MSK            (0x1UL << CCP_PWMCTRL_PWM0_POL_POS)
#define CCP_PWMCTRL_PWM0_POL1               (0x1UL << CCP_PWMCTRL_PWM0_POL_POS)
#define CCP_PWMCTRL_PWM0_POL0               (0x0UL << CCP_PWMCTRL_PWM0_POL_POS)

/*
 * Bit definition for CCPx PWM_CTRL[3] - CCPx PWM channel 3 enable
 */
#define CCP_PWMCTRL_PWM3_EN_POS             (3)
#define CCP_PWMCTRL_PWM3_EN_MSK             (0x1UL << CCP_PWMCTRL_PWM3_EN_POS)
#define CCP_PWMCTRL_PWM3_ENABLE             (0x1UL << CCP_PWMCTRL_PWM3_EN_POS)
#define CCP_PWMCTRL_PWM3_DISABLE            (0x0UL << CCP_PWMCTRL_PWM3_EN_POS)

/*
 * Bit definition for CCPx PWM_CTRL[2] - CCPx PWM channel 2 enable
 */
#define CCP_PWMCTRL_PWM2_EN_POS             (2)
#define CCP_PWMCTRL_PWM2_EN_MSK             (0x1UL << CCP_PWMCTRL_PWM2_EN_POS)
#define CCP_PWMCTRL_PWM2_ENABLE             (0x1UL << CCP_PWMCTRL_PWM2_EN_POS)
#define CCP_PWMCTRL_PWM2_DISABLE            (0x0UL << CCP_PWMCTRL_PWM2_EN_POS)

/*
 * Bit definition for CCPx PWM_CTRL[1] - CCPx PWM channel 1 enable
 */
#define CCP_PWMCTRL_PWM1_EN_POS             (1)
#define CCP_PWMCTRL_PWM1_EN_MSK             (0x1UL << CCP_PWMCTRL_PWM1_EN_POS)
#define CCP_PWMCTRL_PWM1_ENABLE             (0x1UL << CCP_PWMCTRL_PWM1_EN_POS)
#define CCP_PWMCTRL_PWM1_DISABLE            (0x0UL << CCP_PWMCTRL_PWM1_EN_POS)

/*
 * Bit definition for CCPx PWM_CTRL[0] - CCPx PWM channel 0 enable
 */
#define CCP_PWMCTRL_PWM0_EN_POS             (0)
#define CCP_PWMCTRL_PWM0_EN_MSK             (0x1UL << CCP_PWMCTRL_PWM0_EN_POS)
#define CCP_PWMCTRL_PWM0_ENABLE             (0x1UL << CCP_PWMCTRL_PWM0_EN_POS)
#define CCP_PWMCTRL_PWM0_DISABLE            (0x0UL << CCP_PWMCTRL_PWM0_EN_POS)

/*
 * Bit definition for CCPx INTEN[8] - CCPx Timer interrupt enable
 */
#define CCP_INTEN_TMR_INT_EN_POS            (8)
#define CCP_INTEN_TMR_INT_EN_MSK            (0x1UL << CCP_INTEN_TMR_INT_EN_POS)
#define CCP_INTEN_TMR_INT_ENABLE            (0x1UL << CCP_INTEN_TMR_INT_EN_POS)
#define CCP_INTEN_TMR_INT_DISABLE           (0x0UL << CCP_INTEN_TMR_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[7] - CCPx capture channel 3 interrupt enable
 */
#define CCP_INTEN_CAP3_INT_EN_POS           (7)
#define CCP_INTEN_CAP3_INT_EN_MSK           (0x1UL << CCP_INTEN_CAP3_INT_EN_POS)
#define CCP_INTEN_CAP3_INT_ENABLE           (0x1UL << CCP_INTEN_CAP3_INT_EN_POS)
#define CCP_INTEN_CAP3_INT_DISABLE          (0x0UL << CCP_INTEN_CAP3_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[6] - CCPx capture channel 2 interrupt enable
 */
#define CCP_INTEN_CAP2_INT_EN_POS           (6)
#define CCP_INTEN_CAP2_INT_EN_MSK           (0x1UL << CCP_INTEN_CAP2_INT_EN_POS)
#define CCP_INTEN_CAP2_INT_ENABLE           (0x1UL << CCP_INTEN_CAP2_INT_EN_POS)
#define CCP_INTEN_CAP2_INT_DISABLE          (0x0UL << CCP_INTEN_CAP2_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[5] - CCPx capture channel 1 interrupt enable
 */
#define CCP_INTEN_CAP1_INT_EN_POS           (5)
#define CCP_INTEN_CAP1_INT_EN_MSK           (0x1UL << CCP_INTEN_CAP1_INT_EN_POS)
#define CCP_INTEN_CAP1_INT_ENABLE           (0x1UL << CCP_INTEN_CAP1_INT_EN_POS)
#define CCP_INTEN_CAP1_INT_DISABLE          (0x0UL << CCP_INTEN_CAP1_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[4] - CCPx capture channel 0 interrupt enable
 */
#define CCP_INTEN_CAP0_INT_EN_POS           (4)
#define CCP_INTEN_CAP0_INT_EN_MSK           (0x1UL << CCP_INTEN_CAP0_INT_EN_POS)
#define CCP_INTEN_CAP0_INT_ENABLE           (0x1UL << CCP_INTEN_CAP0_INT_EN_POS)
#define CCP_INTEN_CAP0_INT_DISABLE          (0x0UL << CCP_INTEN_CAP0_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[3] - CCPx compare channel 3 interrupt enable
 */
#define CCP_INTEN_CMP3_INT_EN_POS           (3)
#define CCP_INTEN_CMP3_INT_EN_MSK           (0x1UL << CCP_INTEN_CMP3_INT_EN_POS)
#define CCP_INTEN_CMP3_INT_ENABLE           (0x1UL << CCP_INTEN_CMP3_INT_EN_POS)
#define CCP_INTEN_CMP3_INT_DISABLE          (0x0UL << CCP_INTEN_CMP3_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[2] - CCPx compare channel 2 interrupt enable
 */
#define CCP_INTEN_CMP2_INT_EN_POS           (2)
#define CCP_INTEN_CMP2_INT_EN_MSK           (0x1UL << CCP_INTEN_CMP2_INT_EN_POS)
#define CCP_INTEN_CMP2_INT_ENABLE           (0x1UL << CCP_INTEN_CMP2_INT_EN_POS)
#define CCP_INTEN_CMP2_INT_DISABLE          (0x0UL << CCP_INTEN_CMP2_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[1] - CCPx compare channel 1 interrupt enable
 */
#define CCP_INTEN_CMP1_INT_EN_POS           (1)
#define CCP_INTEN_CMP1_INT_EN_MSK           (0x1UL << CCP_INTEN_CMP1_INT_EN_POS)
#define CCP_INTEN_CMP1_INT_ENABLE           (0x1UL << CCP_INTEN_CMP1_INT_EN_POS)
#define CCP_INTEN_CMP1_INT_DISABLE          (0x0UL << CCP_INTEN_CMP1_INT_EN_POS)

/*
 * Bit definition for CCPx INTEN[0] - CCPx compare channel 0 interrupt enable
 */
#define CCP_INTEN_CMP0_INT_EN_POS           (0)
#define CCP_INTEN_CMP0_INT_EN_MSK           (0x1UL << CCP_INTEN_CMP0_INT_EN_POS)
#define CCP_INTEN_CMP0_INT_ENABLE           (0x1UL << CCP_INTEN_CMP0_INT_EN_POS)
#define CCP_INTEN_CMP0_INT_DISABLE          (0x0UL << CCP_INTEN_CMP0_INT_EN_POS)

/*
 * Bit definition for CCPx INTSTS[8] - CCPx Timer interrupt flag
 */
#define CCP_INTEN_TMR_INTF_POS              (8)
#define CCP_INTEN_TMR_INTF_MSK              (0x1UL << CCP_INTEN_TMR_INTF_POS)
#define CCP_INTEN_TMR_INT_FLAG              (0x1UL << CCP_INTEN_TMR_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[7] - CCPx capture channel 3 interrupt flag
 */
#define CCP_INTSTS_CAP3_INTF_POS            (7)
#define CCP_INTSTS_CAP3_INTF_MSK            (0x1UL << CCP_INTSTS_CAP3_INTF_POS)
#define CCP_INTSTS_CAP3_INT_FLAG            (0x1UL << CCP_INTSTS_CAP3_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[6] - CCPx capture channel 2 interrupt flag
 */
#define CCP_INTSTS_CAP2_INTF_POS            (6)
#define CCP_INTSTS_CAP2_INTF_MSK            (0x1UL << CCP_INTSTS_CAP2_INTF_POS)
#define CCP_INTSTS_CAP2_INT_FLAG            (0x1UL << CCP_INTSTS_CAP2_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[5] - CCPx capture channel 1 interrupt flag
 */
#define CCP_INTSTS_CAP1_INTF_POS            (5)
#define CCP_INTSTS_CAP1_INTF_MSK            (0x1UL << CCP_INTSTS_CAP1_INTF_POS)
#define CCP_INTSTS_CAP1_INT_FLAG            (0x1UL << CCP_INTSTS_CAP1_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[4] - CCPx capture channel 0 interrupt flag
 */
#define CCP_INTSTS_CAP0_INTF_POS            (4)
#define CCP_INTSTS_CAP0_INTF_MSK            (0x1UL << CCP_INTSTS_CAP0_INTF_POS)
#define CCP_INTSTS_CAP0_INT_FLAG            (0x1UL << CCP_INTSTS_CAP0_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[3] - CCPx compare channel 3 interrupt flag
 */
#define CCP_INTSTS_CMP3_INTF_POS            (3)
#define CCP_INTSTS_CMP3_INTF_MSK            (0x1UL << CCP_INTSTS_CMP3_INTF_POS)
#define CCP_INTSTS_CMP3_INT_FLAG            (0x1UL << CCP_INTSTS_CMP3_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[2] - CCPx compare channel 2 interrupt flag
 */
#define CCP_INTSTS_CMP2_INTF_POS            (2)
#define CCP_INTSTS_CMP2_INTF_MSK            (0x1UL << CCP_INTSTS_CMP2_INTF_POS)
#define CCP_INTSTS_CMP2_INT_FLAG            (0x1UL << CCP_INTSTS_CMP2_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[1] - CCPx compare channel 1 interrupt flag
 */
#define CCP_INTSTS_CMP1_INTF_POS            (1)
#define CCP_INTSTS_CMP1_INTF_MSK            (0x1UL << CCP_INTSTS_CMP1_INTF_POS)
#define CCP_INTSTS_CMP1_INT_FLAG            (0x1UL << CCP_INTSTS_CMP1_INTF_POS)

/*
 * Bit definition for CCPx INTSTS[0] - CCPx compare channel 0 interrupt flag
 */
#define CCP_INTSTS_CMP0_INTF_POS            (0)
#define CCP_INTSTS_CMP0_INTF_MSK            (0x1UL << CCP_INTSTS_CMP0_INTF_POS)
#define CCP_INTSTS_CMP0_INT_FLAG            (0x1UL << CCP_INTSTS_CMP0_INTF_POS)


/*---------------------------------------------------------------------------------------
 * TIMER Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t PLOAD;                      // Timer Pre-Load Data Register
	__IO uint32_t COUNT;                      // Timer Actual Value Register
	__IO uint32_t CTRL;                       // Timer Baud Control Register
	__IO uint32_t CAPSRC;                     // Timer Capture Mode Source Selection Register
} TIMER_TYPE_DEF;

typedef struct
{
	__IO uint32_t INTEN;                      // Timer Interrupt Enable Register
	__IO uint32_t INTSTS;                     // Timer Interrupt Status Register
} TIMER_INT_TYPE_DEF;

/*
 * Bit definition for TMx_PLOAD[15:0] - Timer Pre-Load Data
 */
#define TIMER_PLOAD_PRELOAD_DATA_POS        (0)
#define TIMER_PLOAD_PRELOAD_DATA_MSK        (0xFFFFUL << TIMER_PLOAD_PRELOAD_DATA_POS)

/*
 * Bit definition for TMx_CTRL[15:12] - Timer Interrupt divider
 */
#define TIMER_CTRL_TMINT_DIV_POS            (12)
#define TIMER_CTRL_TMINT_DIV_MSK            (0xFUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_16             (0xFUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_15             (0xEUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_14             (0xDUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_13             (0xCUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_12             (0xBUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_11             (0xAUL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_10             (0x9UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_9              (0x8UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_8              (0x7UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_7              (0x6UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_6              (0x5UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_5              (0x4UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_4              (0x3UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_3              (0x2UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_2              (0x1UL << TIMER_CTRL_TMINT_DIV_POS)
#define TIMER_CTRL_TMINT_DIV_1              (0x0UL << TIMER_CTRL_TMINT_DIV_POS)

/*
 * Bit definition for TMx_CTRL[11] - Capture end edge switch
 */
#define TIMER_CTRL_CAP_ENDSW_POS            (11)
#define TIMER_CTRL_CAP_ENDSW_MSK            (0x1UL << TIMER_CTRL_CAP_ENDSW_POS)
#define TIMER_CTRL_CAP_ENDSW_FALL_EDGE      (0x1UL << TIMER_CTRL_CAP_ENDSW_POS)
#define TIMER_CTRL_CAP_ENDSW_RISE_EDGE      (0x0UL << TIMER_CTRL_CAP_ENDSW_POS)

/*
 * Bit definition for TMx_CTRL[10] - Capture end flag
 */
#define TIMER_CTRL_CAP_END_POS              (10)
#define TIMER_CTRL_CAP_END_MSK              (0x1UL << TIMER_CTRL_CAP_END_POS)
#define TIMER_CTRL_CAP_END_FLAG             (0x1UL << TIMER_CTRL_CAP_END_POS)

/*
 * Bit definition for TMx_CTRL[9] - Capture start
 */
#define TIMER_CTRL_CAP_START_POS            (9)
#define TIMER_CTRL_CAP_START_MSK            (0x1UL << TIMER_CTRL_CAP_START_POS)
#define TIMER_CTRL_CAP_START                (0x1UL << TIMER_CTRL_CAP_START_POS)

/*
 * Bit definition for TMx_CTRL[8] - Capture mode enable
 */
#define TIMER_CTRL_CAPMODE_POS              (8)
#define TIMER_CTRL_CAPMODE_MSK              (0x1UL << TIMER_CTRL_CAPMODE_POS)
#define TIMER_CTRL_CAPMODE_ENABLE           (0x1UL << TIMER_CTRL_CAPMODE_POS)
#define TIMER_CTRL_CAPMODE_DISABLE          (0x0UL << TIMER_CTRL_CAPMODE_POS)

/*
 * Bit definition for TMx_CTRL[7:5] - Timer input clock source selection
 */
#define TIMER_CTRL_CLK_SEL_POS              (5)
#define TIMER_CTRL_CLK_SEL_MSK              (0x7UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_32K              (0x7UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_EXTCLK           (0x6UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK_DIV_32      (0x5UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK_DIV_16      (0x4UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK_DIV_8       (0x3UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK_DIV_4       (0x2UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK_DIV_2       (0x1UL << TIMER_CTRL_CLK_SEL_POS)
#define TIMER_CTRL_CLK_SEL_HCLK             (0x0UL << TIMER_CTRL_CLK_SEL_POS)

/*
 * Bit definition for TMx_CTRL[4:2] - Capture mode low pass filter selection
 */
#define TIMER_CTRL_CAP_LPF_SEL_POS          (2)
#define TIMER_CTRL_CAP_LPF_SEL_MSK          (0x7UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_128HCLK      (0x7UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_80HCLK       (0x6UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_40HCLK       (0x5UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_32HCLK       (0x4UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_16HCLK       (0x3UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_8HCLK        (0x2UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_SEL_4HCLK        (0x1UL << TIMER_CTRL_CAP_LPF_SEL_POS)
#define TIMER_CTRL_CAP_LPF_DISABLE          (0x0UL << TIMER_CTRL_CAP_LPF_SEL_POS)

/*
 * Bit definition for TMx_CTRL[1] - Timer reload
 */
#define TIMER_CTRL_TM_RELOAD_POS            (1)
#define TIMER_CTRL_TM_RELOAD_MSK            (0x1UL << TIMER_CTRL_TM_RELOAD_POS)
#define TIMER_CTRL_TM_RELOAD                (0x1UL << TIMER_CTRL_TM_RELOAD_POS)

/*
 * Bit definition for TMx_CTRL[0] - Timer enable
 */
#define TIMER_CTRL_TM_EN_POS                (0)
#define TIMER_CTRL_TM_EN_MSK                (0x1UL << TIMER_CTRL_TM_EN_POS)
#define TIMER_CTRL_TM_ENABLE                (0x1UL << TIMER_CTRL_TM_EN_POS)
#define TIMER_CTRL_TM_DISABLE							  (0x0UL << TIMER_CTRL_TM_EN_POS)

/*
 * Bit definition for TMx_CAPSRC[4:0] - Timer Capture mode source selection
 */
#define TIMER_CAPSRC_IOSEL_POS              (0)
#define TIMER_CAPSRC_IOSEL_MSK              (0x1FUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB5             (0x1BUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB4             (0x1AUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB3             (0x19UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB2             (0x18UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB1             (0x17UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOB0             (0x16UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA21            (0x15UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA20            (0x14UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA19            (0x13UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA18            (0x12UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA17            (0x11UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA16            (0x10UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA15            (0xFUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA14            (0xEUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA13            (0xDUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA12            (0xCUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA11            (0xBUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA10            (0xAUL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA9             (0x9UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA8             (0x8UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA7             (0x7UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA6             (0x6UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA5             (0x5UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA4             (0x4UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA3             (0x3UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA2             (0x2UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA1             (0x1UL << TIMER_CAPSRC_IOSEL_POS)
#define TIMER_CAPSRC_IOSEL_IOA0             (0x0UL << TIMER_CAPSRC_IOSEL_POS)

/*
 * Bit definition for TM_INTEN[5] - TM2 capture mode interrupt enable
 */
#define TIMER_INTEN_TM2_CAPINT_EN_POS       (5)
#define TIMER_INTEN_TM2_CAPINT_EN_MSK       (0x1UL << TIMER_INTEN_TM2_CAPINT_EN_POS)
#define TIMER_INTEN_TM2_CAPINT_ENABLE       (0x1UL << TIMER_INTEN_TM2_CAPINT_EN_POS)
#define TIMER_INTEN_TM2_CAPINT_DISABLE      (0x0UL << TIMER_INTEN_TM2_CAPINT_EN_POS)

/*
 * Bit definition for TM_INTEN[4] - TM2 interrupt enable
 */
#define TIMER_INTEN_TM2_INT_EN_POS          (4)
#define TIMER_INTEN_TM2_INT_EN_MSK          (0x1UL << TIMER_INTEN_TM2_INT_EN_POS)
#define TIMER_INTEN_TM2_INT_ENABLE          (0x1UL << TIMER_INTEN_TM2_INT_EN_POS)
#define TIMER_INTEN_TM2_INT_DISABLE         (0x0UL << TIMER_INTEN_TM2_INT_EN_POS)

/*
 * Bit definition for TM_INTEN[3] - TM1 capture mode interrupt enable
 */
#define TIMER_INTEN_TM1_CAPINT_EN_POS       (3)
#define TIMER_INTEN_TM1_CAPINT_EN_MSK       (0x1UL << TIMER_INTEN_TM1_CAPINT_EN_POS)
#define TIMER_INTEN_TM1_CAPINT_ENABLE       (0x1UL << TIMER_INTEN_TM1_CAPINT_EN_POS)
#define TIMER_INTEN_TM1_CAPINT_DISABLE      (0x0UL << TIMER_INTEN_TM1_CAPINT_EN_POS)

/*
 * Bit definition for TM_INTEN[2] - TM1 interrupt enable
 */
#define TIMER_INTEN_TM1_INT_EN_POS          (2)
#define TIMER_INTEN_TM1_INT_EN_MSK          (0x1UL << TIMER_INTEN_TM1_INT_EN_POS)
#define TIMER_INTEN_TM1_INT_ENABLE          (0x1UL << TIMER_INTEN_TM1_INT_EN_POS)
#define TIMER_INTEN_TM1_INT_DISABLE         (0x0UL << TIMER_INTEN_TM1_INT_EN_POS)

/*
 * Bit definition for TM_INTEN[1] - TM0 capture mode interrupt enable
 */
#define TIMER_INTEN_TM0_CAPINT_EN_POS       (1)
#define TIMER_INTEN_TM0_CAPINT_EN_MSK       (0x1UL << TIMER_INTEN_TM0_CAPINT_EN_POS)
#define TIMER_INTEN_TM0_CAPINT_ENABLE       (0x1UL << TIMER_INTEN_TM0_CAPINT_EN_POS)
#define TIMER_INTEN_TM0_CAPINT_DISABLE      (0x0UL << TIMER_INTEN_TM0_CAPINT_EN_POS)

/*
 * Bit definition for TM_INTEN[0] - TM0 interrupt enable
 */
#define TIMER_INTEN_TM0_INT_EN_POS          (0)
#define TIMER_INTEN_TM0_INT_EN_MSK          (0x1UL << TIMER_INTEN_TM0_INT_EN_POS)
#define TIMER_INTEN_TM0_INT_ENABLE          (0x1UL << TIMER_INTEN_TM0_INT_EN_POS)
#define TIMER_INTEN_TM0_INT_DISABLE         (0x0UL << TIMER_INTEN_TM0_INT_EN_POS)

/*
 * Bit definition for TM_INTSTS[5] - TM2 capture mode interrupt flag
 */
#define TIMER_INTSTS_TM2_CAPINTF_POS        (5)
#define TIMER_INTSTS_TM2_CAPINTF_MSK        (0x1UL << TIMER_INTSTS_TM2_CAPINTF_POS)
#define TIMER_INTSTS_TM2_CAPINT_FLAG        (0x1UL << TIMER_INTSTS_TM2_CAPINTF_POS)

/*
 * Bit definition for TM_INTSTS[4] - TM2 interrupt flag
 */
#define TIMER_INTSTS_TM2_INTF_POS           (4)
#define TIMER_INTSTS_TM2_INTF_MSK           (0x1UL << TIMER_INTSTS_TM2_INTF_POS)
#define TIMER_INTSTS_TM2_INT_FLAG           (0x1UL << TIMER_INTSTS_TM2_INTF_POS)

/*
 * Bit definition for TM_INTSTS[3] - TM1 capture mode interrupt flag
 */
#define TIMER_INTSTS_TM1_CAPINTF_POS        (3)
#define TIMER_INTSTS_TM1_CAPINTF_MSK        (0x1UL << TIMER_INTSTS_TM1_CAPINTF_POS)
#define TIMER_INTSTS_TM1_CAPINT_FLAG        (0x1UL << TIMER_INTSTS_TM1_CAPINTF_POS)

/*
 * Bit definition for TM_INTSTS[2] - TM1 interrupt flag
 */
#define TIMER_INTSTS_TM1_INTF_POS           (2)
#define TIMER_INTSTS_TM1_INTF_MSK           (0x1UL << TIMER_INTSTS_TM1_INTF_POS)
#define TIMER_INTSTS_TM1_INT_FLAG           (0x1UL << TIMER_INTSTS_TM1_INTF_POS)

/*
 * Bit definition for TM_INTSTS[1] - TM0 capture mode interrupt flag
 */
#define TIMER_INTSTS_TM0_CAPINTF_POS        (1)
#define TIMER_INTSTS_TM0_CAPINTF_MSK        (0x1UL << TIMER_INTSTS_TM0_CAPINTF_POS)
#define TIMER_INTSTS_TM0_CAPINT_FLAG        (0x1UL << TIMER_INTSTS_TM0_CAPINTF_POS)

/*
 * Bit definition for TM_INTSTS[0] - TM0 interrupt flag
 */
#define TIMER_INTSTS_TM0_INTF_POS           (0)
#define TIMER_INTSTS_TM0_INTF_MSK           (0x1UL << TIMER_INTSTS_TM0_INTF_POS)
#define TIMER_INTSTS_TM0_INT_FLAG           (0x1UL << TIMER_INTSTS_TM0_INTF_POS)


/*---------------------------------------------------------------------------------------
 * SPIFC Control Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL0;                      // SPIFC Control Register0 				0
	__IO uint32_t CMD;                        // SPIFC Command Register					4
	__IO uint32_t PARA;                      	// SPIFC Control Register1				8
	__IO uint32_t ADDRL;                      // SPIFC Address RegisterL				C
	__IO uint32_t ADDRH;                      // SPIFC Address RegisterH				10
	__IO uint32_t TX_DATA;                    // SPIFC TX Data Register					14
	__IO uint32_t RX_DATA;                    // SPIFC RX Data Register					18
	__IO uint32_t TX_BC;                      // SPIFC TX Byte Count Register		1C
	__IO uint32_t RX_BC;                      // SPIFC RX Byte Count Register		20
	__IO uint32_t TIMING;                     // SPIFC Timing Delay Register 		24
	__IO uint32_t Reserve1;                   // SPIFC SPIFC Reserve Register1	28
	__IO uint32_t CTRL1;                      // SPIFC Control Register1				2C
	__IO uint32_t Reserve2;                   // SPIFC SPIFC Reserve Register2 	30
	__IO uint32_t CTRL2;                   		// SPIFC SPIFC Reserve Register3 	34
	__IO uint32_t TX_DATA32;                  // SPIFC TX Word Data Register		38
	__IO uint32_t Reserve3;                   // SPIFC Reserve Register 				3C
	__IO uint32_t SCRAMBLE_CTRL;              // SPIFC Scramble Control Register 			40
	__IO uint32_t DEC_ADDR_START;             // SPIFC Scramble Decode Start Address	44
	__IO uint32_t DEC_ADDR_END;               // SPIFC Scramble Decode End Address		48
	__IO uint32_t REG_USER_KEY0;              // SPIFC Scramble Decode Start Address	4C
	__IO uint32_t REG_USER_KEY1;              // SPIFC Scramble Decode End Address		50
} SPIFC_TYPE_DEF;

/*
 * Bit definition for SPIFC_CTRL0[15] - SPIFC TX done flag
 */
#define SPIFC_CTRL0_TX_DONE_FLAG_POS        (15)
#define SPIFC_CTRL0_TX_DONE_FLAG_MSK        (1UL << SPIFC_CTRL0_TX_DONE_FLAG_POS)
#define SPIFC_CTRL0_TX_DONE_FLAG            (1UL << SPIFC_CTRL0_TX_DONE_FLAG_POS)

/*
 * Bit definition for SPIFC_CTRL0[14] - SPIFC RX FIFO empty flag
 */
#define SPIFC_CTRL0_RX_FIFO_EMP_FLAG_POS    (14)
#define SPIFC_CTRL0_RX_FIFO_EMP_FLAG_MSK    (1UL << SPIFC_CTRL0_RX_FIFO_EMP_FLAG_POS)
#define SPIFC_CTRL0_RX_FIFO_EMP_FLAG        (1UL << SPIFC_CTRL0_RX_FIFO_EMP_FLAG_POS)

/*
 * Bit definition for SPIFC_CTRL0[9] - Ignore last clock
 */
#define SPIFC_CTRL0_IGNORE_LAST_CLK_POS     (9)
#define SPIFC_CTRL0_IGNORE_LAST_CLK_MSK     (1UL << SPIFC_CTRL0_IGNORE_LAST_CLK_POS)
#define SPIFC_CTRL0_IGNORE_LAST_CLK_ENABLE  (1UL << SPIFC_CTRL0_IGNORE_LAST_CLK_POS)
#define SPIFC_CTRL0_IGNORE_LAST_CLK_DISABLE (0UL << SPIFC_CTRL0_IGNORE_LAST_CLK_POS)

/*
 * Bit definition for SPIFC_CTRL0[8] - SPIFC operation mode
 */
#define SPIFC_CTRL0_OPERATION_MODE_POS      (8)
#define SPIFC_CTRL0_OPERATION_MODE_MSK      (1UL << SPIFC_CTRL0_OPERATION_MODE_POS)
#define SPIFC_CTRL0_MANUAL_MODE             (1UL << SPIFC_CTRL0_OPERATION_MODE_POS)
#define SPIFC_CTRL0_AUTO_MODE               (0UL << SPIFC_CTRL0_OPERATION_MODE_POS)

/*
 * Bit definition for SPIFC_CTRL0[7:6] - IO bit width definition for command
 */
#define SPIFC_CTRL0_CMIO_POS                (6)
#define SPIFC_CTRL0_CMIO_MSK                (3UL << SPIFC_CTRL0_CMIO_POS)
#define SPIFC_CTRL0_CMIO_4BIT               (2UL << SPIFC_CTRL0_CMIO_POS)
#define SPIFC_CTRL0_CMIO_2BIT               (1UL << SPIFC_CTRL0_CMIO_POS)
#define SPIFC_CTRL0_CMIO_1BIT               (0UL << SPIFC_CTRL0_CMIO_POS)

/*
 * Bit definition for SPIFC_CTRL0[5:4] - IO bit width definition for address
 */
#define SPIFC_CTRL0_AMIO_POS                (4)
#define SPIFC_CTRL0_AMIO_MSK                (3UL << SPIFC_CTRL0_AMIO_POS)
#define SPIFC_CTRL0_AMIO_4BIT               (2UL << SPIFC_CTRL0_AMIO_POS)
#define SPIFC_CTRL0_AMIO_2BIT               (1UL << SPIFC_CTRL0_AMIO_POS)
#define SPIFC_CTRL0_AMIO_1BIT               (0UL << SPIFC_CTRL0_AMIO_POS)

/*
 * Bit definition for SPIFC_CTRL0[3:2] - Multi-IO mode,IO bit width definition for TX & RX data.
 */
#define SPIFC_CTRL0_MIO_POS                 (2)
#define SPIFC_CTRL0_MIO_MSK                 (0x3UL << SPIFC_CTRL0_MIO_POS)
#define SPIFC_CTRL0_MIO_4BIT                (0x2UL << SPIFC_CTRL0_MIO_POS)
#define SPIFC_CTRL0_MIO_2BIT                (0x1UL << SPIFC_CTRL0_MIO_POS)
#define SPIFC_CTRL0_MIO_1BIT                (0x0UL << SPIFC_CTRL0_MIO_POS)

/*
 * Bit definition for SPIFC_CTRL0[1] - SPI clock state
 */
#define SPIFC_CTRL0_CLK_STATE_POS           (1)
#define SPIFC_CTRL0_CLK_STATE_MSK           (0x1UL << SPIFC_CTRL0_MIO_POS)
#define SPIFC_CTRL0_CLK_STATE_HIGH          (0x1UL << SPIFC_CTRL0_MIO_POS)
#define SPIFC_CTRL0_CLK_STATE_LOW           (0x0UL << SPIFC_CTRL0_MIO_POS)

/*
 * Bit definition for SPIFC_CTRL0[0] - SPIFC pending flag
 */
#define SPIFC_CTRL0_PENDING_FLAG_POS        (0)
#define SPIFC_CTRL0_PENDING_FLAG_MSK        (0x1UL << SPIFC_CTRL0_PENDING_FLAG_POS)
#define SPIFC_CTRL0_PENDING_FLAG            (0x1UL << SPIFC_CTRL0_PENDING_FLAG_POS)

/*
 * Bit definition for SPIFC_CMD[13] - Only the first transaction has command
 */
#define SPIFC_CMD_1ST_TRANS_WITHCMD_EN_POS  (13)
#define SPIFC_CMD_1ST_TRANS_WITHCMD_EN_MSK  (0x1UL << SPIFC_CMD_1ST_TRANS_WITHCMD_EN_POS)
#define SPIFC_CMD_1ST_TRANS_WITHCMD_ENABLE  (0x1UL << SPIFC_CMD_1ST_TRANS_WITHCMD_EN_POS)
#define SPIFC_CMD_1ST_TRANS_WITHCMD_DISABLE (0x0UL << SPIFC_CMD_1ST_TRANS_WITHCMD_EN_POS)

/*
 * Bit definition for SPIFC_CMD[9] - A Transaction contains only command information
 */
#define SPIFC_CMD_ONLYCMD_EN_POS            (9)
#define SPIFC_CMD_ONLYCMD_EN_MSK            (0x1UL << SPIFC_CMD_ONLYCMD_EN_POS)
#define SPIFC_CMD_ONLYCMD_ENABLE            (0x1UL << SPIFC_CMD_ONLYCMD_EN_POS)
#define SPIFC_CMD_ONLYCMD_DISABLE           (0x0UL << SPIFC_CMD_ONLYCMD_EN_POS)

/*
 * Bit definition for SPIFC_CMD[8] - A Transaction without command
 */
#define SPIFC_CMD_WITHOUTCMD_EN_POS         (8)
#define SPIFC_CMD_WITHOUTCMD_EN_MSK         (0x1UL << SPIFC_CMD_WITHOUTCMD_EN_POS)
#define SPIFC_CMD_WITHOUTCMD_ENABLE         (0x1UL << SPIFC_CMD_WITHOUTCMD_EN_POS)
#define SPIFC_CMD_WITHOUTCMD_DISABLE        (0x0UL << SPIFC_CMD_WITHOUTCMD_EN_POS)

/*
 * Bit definition for SPIFC_CMD[7:0] - SPI Command
 */
#define SPIFC_CMD_SPICMD_POS                (0)
#define SPIFC_CMD_SPICMD_MSK                (0xFFUL << SPIFC_CMD_SPICMD_POS)

/*
 * Bit definition for SPIFC_PARA[14] - A Transaction does not contain enhancement bits
 */
#define SPIFC_PARA_ENHAN_EN_POS             (14)
#define SPIFC_PARA_ENHAN_EN_MSK             (0x1UL << SPIFC_PARA_ENHAN_EN_POS)
#define SPIFC_PARA_ENHAN_DISABLE            (0x1UL << SPIFC_PARA_ENHAN_EN_POS)
#define SPIFC_PARA_ENHAN_ENABLE             (0x0UL << SPIFC_PARA_ENHAN_EN_POS)

/*
 * Bit definition for SPIFC_PARA[13] - A Transaction only contain address bits
 */
#define SPIFC_PARA_ONLY_ADDR_EN_POS         (13)
#define SPIFC_PARA_ONLY_ADDR_EN_MSK         (0x1UL << SPIFC_PARA_ONLY_ADDR_EN_POS)
#define SPIFC_PARA_ONLY_ADDR_ENABLE         (0x1UL << SPIFC_PARA_ONLY_ADDR_EN_POS)
#define SPIFC_PARA_ONLY_ADDR_DISABLE        (0x0UL << SPIFC_PARA_ONLY_ADDR_EN_POS)

/*
 * Bit definition for SPIFC_PARA[12] - A Transaction does not contain address bits
 */
#define SPIFC_PARA_WITHOUT_ADDR_EN_POS      (12)
#define SPIFC_PARA_WITHOUT_ADDR_EN_MSK      (0x1UL << SPIFC_PARA_WITHOUT_ADDR_EN_POS)
#define SPIFC_PARA_WITHOUT_ADDR_ENABLE      (0x1UL << SPIFC_PARA_WITHOUT_ADDR_EN_POS)
#define SPIFC_PARA_WITHOUT_ADDR_DISABLE     (0x0UL << SPIFC_PARA_WITHOUT_ADDR_EN_POS)

/*
 * Bit definition for SPIFC_PARA[11:8] - Enhancement bits in a transaction
 */
#define SPIFC_PARA_DUMMY_CLK_POS            (8)
#define SPIFC_PARA_DUMMY_CLK_MSK            (0xFUL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_9_CYCLE        (0x9UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_8_CYCLE        (0x8UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_7_CYCLE        (0x7UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_6_CYCLE        (0x6UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_5_CYCLE        (0x5UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_4_CYCLE        (0x4UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_3_CYCLE        (0x3UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_2_CYCLE        (0x2UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_1_CYCLE        (0x1UL << SPIFC_PARA_DUMMY_CLK_POS)
#define SPIFC_PARA_DUMMY_CLK_0_CYCLE        (0x0UL << SPIFC_PARA_DUMMY_CLK_POS)

/*
 * Bit definition for SPIFC_PARA[7:0] - Enhancement bits in a transaction
 */
#define SPIFC_PARA_ENHANCE_BIT_POS          (0)
#define SPIFC_PARA_ENHANCE_BIT_MSK          (0xFFUL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT7             (0x80UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT6             (0x40UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT5             (0x20UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT4             (0x10UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT3             (0x08UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT2             (0x04UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT1             (0x02UL << SPIFC_PARA_ENHANCE_BIT_POS)
#define SPIFC_PARA_ENHANCE_BIT0             (0x01UL << SPIFC_PARA_ENHANCE_BIT_POS)

/*
 * Bit definition for SPIFC_TIMING[7:4] - Sample delay for received data
 */
#define SPIFC_TIMING_SMP_DELAY_POS          (4)
#define SPIFC_TIMING_SMP_DELAY_MSK          (0xFUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_15           (0xFUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_14           (0xEUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_13           (0xDUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_12           (0xCUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_11           (0xBUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_10           (0xAUL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_9            (0x9UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_8            (0x8UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_7            (0x7UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_6            (0x6UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_5            (0x5UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_4            (0x4UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_3            (0x3UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_2            (0x2UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_1            (0x1UL << SPIFC_TIMING_SMP_DELAY_POS)
#define SPIFC_TIMING_SMP_DELAY_0            (0x0UL << SPIFC_TIMING_SMP_DELAY_POS)

/*
 * Bit definition for SPIFC_TIMING[2:0] - Sample timing for received data
 */
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS   (0)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_MSK   (0x7UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_7     (0x7UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_6     (0x6UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_5     (0x5UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_4     (0x4UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_3     (0x3UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_2     (0x2UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_1     (0x1UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)
#define SPIFC_TIMING_SMP_CLK_EDGE_SEL_0     (0x0UL << SPIFC_TIMING_SMP_CLK_EDGE_SEL_POS)

/*
 * Bit definition for SPIFC_CTRL1[15:8] - 4 bytes address enable
 */
#define SPIFC_CTRL1_4BYTES_ADDR_EN_POS      (8)
#define SPIFC_CTRL1_4BYTES_ADDR_EN_MSK      (0xFFUL << SPIFC_CTRL1_4BYTES_ADDR_EN_POS)
#define SPIFC_CTRL1_4BYTES_ADDR_ENABLE      (0xFFUL << SPIFC_CTRL1_4BYTES_ADDR_EN_POS)
#define SPIFC_CTRL1_4BYTES_ADDR_DISABLE     (0x00UL << SPIFC_CTRL1_4BYTES_ADDR_EN_POS)

/*
 * Bit definition for SPIFC_CTRL1[0] - SPI flash controller enable
 */
#define SPIFC_CTRL1_SPIFC_EN_POS            (0)
#define SPIFC_CTRL1_SPIFC_EN_MSK            (0x1UL << SPIFC_CTRL1_SPIFC_EN_POS)
#define SPIFC_CTRL1_SPIFC_ENABLE            (0x1UL << SPIFC_CTRL1_SPIFC_EN_POS)
#define SPIFC_CTRL1_SPIFC_DISABLE           (0x0UL << SPIFC_CTRL1_SPIFC_EN_POS)

/*
 * Bit definition for SPIFC_CTRL2[9:8] - SPIFC clock divide
 */
#define SPIFC_CTRL2_CLK_SEL_POS             (8)
#define SPIFC_CTRL2_CLK_SEL_MSK             (0x3UL << SPIFC_CTRL2_CLK_SEL_POS)
#define SPIFC_CTRL2_CLK_SEL_HCLK_DIV_4      (0x3UL << SPIFC_CTRL2_CLK_SEL_POS)
#define SPIFC_CTRL2_CLK_SEL_HCLK_DIV_3      (0x2UL << SPIFC_CTRL2_CLK_SEL_POS)
#define SPIFC_CTRL2_CLK_SEL_HCLK_DIV_2      (0x1UL << SPIFC_CTRL2_CLK_SEL_POS)
#define SPIFC_CTRL2_CLK_SEL_HCLK_DIV_1      (0x0UL << SPIFC_CTRL2_CLK_SEL_POS)


/*---------------------------------------------------------------------------------------
 * General-purpose I/O Control Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CFG0;                       //
	__IO uint32_t CFG1;                       //
	__IO uint32_t DRV0;                       //
	__IO uint32_t DRV1;                       //
	__IO uint32_t SMT;                        //
	__IO uint32_t OBUF;                       //
	__IO uint32_t IDATA;                      //
	__IO uint32_t RESERVED;                   //
	__IO uint32_t OBIT[24];
} GPIO_TYPE_DEF;

/*
 * Bit definition for GPIO_DRV0[1:0] - GPIOA/B_0 Drive Current Select
 */
#define GPIO_DRV0_IO0_DRV_SEL_POS           (0)
#define GPIO_DRV0_IO0_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO0_DRV_SEL_POS)
#define GPIO_DRV0_IO0_DRV_16mA              (0x3UL << GPIO_DRV0_IO0_DRV_SEL_POS)
#define GPIO_DRV0_IO0_DRV_12mA              (0x2UL << GPIO_DRV0_IO0_DRV_SEL_POS)
#define GPIO_DRV0_IO0_DRV_8mA               (0x1UL << GPIO_DRV0_IO0_DRV_SEL_POS)
#define GPIO_DRV0_IO0_DRV_4mA               (0x0UL << GPIO_DRV0_IO0_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[3:2] - GPIOA/B_1 Drive Current Select
 */
#define GPIO_DRV0_IO1_DRV_SEL_POS           (2)
#define GPIO_DRV0_IO1_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO1_DRV_SEL_POS)
#define GPIO_DRV0_IO1_DRV_16mA              (0x3UL << GPIO_DRV0_IO1_DRV_SEL_POS)
#define GPIO_DRV0_IO1_DRV_12mA              (0x2UL << GPIO_DRV0_IO1_DRV_SEL_POS)
#define GPIO_DRV0_IO1_DRV_8mA               (0x1UL << GPIO_DRV0_IO1_DRV_SEL_POS)
#define GPIO_DRV0_IO1_DRV_4mA               (0x0UL << GPIO_DRV0_IO1_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[5:4] - GPIOA/B_2 Drive Current Select
 */
#define GPIO_DRV0_IO2_DRV_SEL_POS           (4)
#define GPIO_DRV0_IO2_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO2_DRV_SEL_POS)
#define GPIO_DRV0_IO2_DRV_16mA              (0x3UL << GPIO_DRV0_IO2_DRV_SEL_POS)
#define GPIO_DRV0_IO2_DRV_12mA              (0x2UL << GPIO_DRV0_IO2_DRV_SEL_POS)
#define GPIO_DRV0_IO2_DRV_8mA               (0x1UL << GPIO_DRV0_IO2_DRV_SEL_POS)
#define GPIO_DRV0_IO2_DRV_4mA               (0x0UL << GPIO_DRV0_IO2_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[7:6] - GPIOA/B_3 Drive Current Select
 */
#define GPIO_DRV0_IO3_DRV_SEL_POS           (6)
#define GPIO_DRV0_IO3_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO3_DRV_SEL_POS)
#define GPIO_DRV0_IO3_DRV_16mA              (0x3UL << GPIO_DRV0_IO3_DRV_SEL_POS)
#define GPIO_DRV0_IO3_DRV_12mA              (0x2UL << GPIO_DRV0_IO3_DRV_SEL_POS)
#define GPIO_DRV0_IO3_DRV_8mA               (0x1UL << GPIO_DRV0_IO3_DRV_SEL_POS)
#define GPIO_DRV0_IO3_DRV_4mA               (0x0UL << GPIO_DRV0_IO3_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[9:8] - GPIOA/B_4 Drive Current Select
 */
#define GPIO_DRV0_IO4_DRV_SEL_POS           (8)
#define GPIO_DRV0_IO4_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO4_DRV_SEL_POS)
#define GPIO_DRV0_IO4_DRV_16mA              (0x3UL << GPIO_DRV0_IO4_DRV_SEL_POS)
#define GPIO_DRV0_IO4_DRV_12mA              (0x2UL << GPIO_DRV0_IO4_DRV_SEL_POS)
#define GPIO_DRV0_IO4_DRV_8mA               (0x1UL << GPIO_DRV0_IO4_DRV_SEL_POS)
#define GPIO_DRV0_IO4_DRV_4mA               (0x0UL << GPIO_DRV0_IO4_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[11:10] - GPIOA/B_5 Drive Current Select
 */
#define GPIO_DRV0_IO5_DRV_SEL_POS           (10)
#define GPIO_DRV0_IO5_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO5_DRV_SEL_POS)
#define GPIO_DRV0_IO5_DRV_16mA              (0x3UL << GPIO_DRV0_IO5_DRV_SEL_POS)
#define GPIO_DRV0_IO5_DRV_12mA              (0x2UL << GPIO_DRV0_IO5_DRV_SEL_POS)
#define GPIO_DRV0_IO5_DRV_8mA               (0x1UL << GPIO_DRV0_IO5_DRV_SEL_POS)
#define GPIO_DRV0_IO5_DRV_4mA               (0x0UL << GPIO_DRV0_IO5_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[13:12] - GPIOA_6 Drive Current Select
 */
#define GPIO_DRV0_IO6_DRV_SEL_POS           (12)
#define GPIO_DRV0_IO6_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO6_DRV_SEL_POS)
#define GPIO_DRV0_IO6_DRV_16mA              (0x3UL << GPIO_DRV0_IO6_DRV_SEL_POS)
#define GPIO_DRV0_IO6_DRV_12mA              (0x2UL << GPIO_DRV0_IO6_DRV_SEL_POS)
#define GPIO_DRV0_IO6_DRV_8mA               (0x1UL << GPIO_DRV0_IO6_DRV_SEL_POS)
#define GPIO_DRV0_IO6_DRV_4mA               (0x0UL << GPIO_DRV0_IO6_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[15:14] - GPIOA_7 Drive Current Select
 */
#define GPIO_DRV0_IO7_DRV_SEL_POS           (14)
#define GPIO_DRV0_IO7_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO7_DRV_SEL_POS)
#define GPIO_DRV0_IO7_DRV_16mA              (0x3UL << GPIO_DRV0_IO7_DRV_SEL_POS)
#define GPIO_DRV0_IO7_DRV_12mA              (0x2UL << GPIO_DRV0_IO7_DRV_SEL_POS)
#define GPIO_DRV0_IO7_DRV_8mA               (0x1UL << GPIO_DRV0_IO7_DRV_SEL_POS)
#define GPIO_DRV0_IO7_DRV_4mA               (0x0UL << GPIO_DRV0_IO7_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[17:16] - GPIOA_8 Drive Current Select
 */
#define GPIO_DRV0_IO8_DRV_SEL_POS           (16)
#define GPIO_DRV0_IO8_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO8_DRV_SEL_POS)
#define GPIO_DRV0_IO8_DRV_16mA              (0x3UL << GPIO_DRV0_IO8_DRV_SEL_POS)
#define GPIO_DRV0_IO8_DRV_12mA              (0x2UL << GPIO_DRV0_IO8_DRV_SEL_POS)
#define GPIO_DRV0_IO8_DRV_8mA               (0x1UL << GPIO_DRV0_IO8_DRV_SEL_POS)
#define GPIO_DRV0_IO8_DRV_4mA               (0x0UL << GPIO_DRV0_IO8_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[19:18] - GPIOA_9 Drive Current Select
 */
#define GPIO_DRV0_IO9_DRV_SEL_POS           (18)
#define GPIO_DRV0_IO9_DRV_SEL_MSK           (0x3UL << GPIO_DRV0_IO9_DRV_SEL_POS)
#define GPIO_DRV0_IO9_DRV_16mA              (0x3UL << GPIO_DRV0_IO9_DRV_SEL_POS)
#define GPIO_DRV0_IO9_DRV_12mA              (0x2UL << GPIO_DRV0_IO9_DRV_SEL_POS)
#define GPIO_DRV0_IO9_DRV_8mA               (0x1UL << GPIO_DRV0_IO9_DRV_SEL_POS)
#define GPIO_DRV0_IO9_DRV_4mA               (0x0UL << GPIO_DRV0_IO9_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[21:20] - GPIOA_10 Drive Current Select
 */
#define GPIO_DRV0_IO10_DRV_SEL_POS          (20)
#define GPIO_DRV0_IO10_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO10_DRV_SEL_POS)
#define GPIO_DRV0_IO10_DRV_16mA             (0x3UL << GPIO_DRV0_IO10_DRV_SEL_POS)
#define GPIO_DRV0_IO10_DRV_12mA             (0x2UL << GPIO_DRV0_IO10_DRV_SEL_POS)
#define GPIO_DRV0_IO10_DRV_8mA              (0x1UL << GPIO_DRV0_IO10_DRV_SEL_POS)
#define GPIO_DRV0_IO10_DRV_4mA              (0x0UL << GPIO_DRV0_IO10_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[23:22] - GPIOA_11 Drive Current Select
 */
#define GPIO_DRV0_IO11_DRV_SEL_POS          (22)
#define GPIO_DRV0_IO11_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO11_DRV_SEL_POS)
#define GPIO_DRV0_IO11_DRV_16mA             (0x3UL << GPIO_DRV0_IO11_DRV_SEL_POS)
#define GPIO_DRV0_IO11_DRV_12mA             (0x2UL << GPIO_DRV0_IO11_DRV_SEL_POS)
#define GPIO_DRV0_IO11_DRV_8mA              (0x1UL << GPIO_DRV0_IO11_DRV_SEL_POS)
#define GPIO_DRV0_IO11_DRV_4mA              (0x0UL << GPIO_DRV0_IO11_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[25:24] - GPIOA_12 Drive Current Select
 */
#define GPIO_DRV0_IO12_DRV_SEL_POS          (24)
#define GPIO_DRV0_IO12_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO12_DRV_SEL_POS)
#define GPIO_DRV0_IO12_DRV_16mA             (0x3UL << GPIO_DRV0_IO12_DRV_SEL_POS)
#define GPIO_DRV0_IO12_DRV_12mA             (0x2UL << GPIO_DRV0_IO12_DRV_SEL_POS)
#define GPIO_DRV0_IO12_DRV_8mA              (0x1UL << GPIO_DRV0_IO12_DRV_SEL_POS)
#define GPIO_DRV0_IO12_DRV_4mA              (0x0UL << GPIO_DRV0_IO12_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[27:26] - GPIOA_13 Drive Current Select
 */
#define GPIO_DRV0_IO13_DRV_SEL_POS          (26)
#define GPIO_DRV0_IO13_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO13_DRV_SEL_POS)
#define GPIO_DRV0_IO13_DRV_16mA             (0x3UL << GPIO_DRV0_IO13_DRV_SEL_POS)
#define GPIO_DRV0_IO13_DRV_12mA             (0x2UL << GPIO_DRV0_IO13_DRV_SEL_POS)
#define GPIO_DRV0_IO13_DRV_8mA              (0x1UL << GPIO_DRV0_IO13_DRV_SEL_POS)
#define GPIO_DRV0_IO13_DRV_4mA              (0x0UL << GPIO_DRV0_IO13_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[29:28] - GPIOA_14 Drive Current Select
 */
#define GPIO_DRV0_IO14_DRV_SEL_POS          (28)
#define GPIO_DRV0_IO14_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO14_DRV_SEL_POS)
#define GPIO_DRV0_IO14_DRV_16mA             (0x3UL << GPIO_DRV0_IO14_DRV_SEL_POS)
#define GPIO_DRV0_IO14_DRV_12mA             (0x2UL << GPIO_DRV0_IO14_DRV_SEL_POS)
#define GPIO_DRV0_IO14_DRV_8mA              (0x1UL << GPIO_DRV0_IO14_DRV_SEL_POS)
#define GPIO_DRV0_IO14_DRV_4mA              (0x0UL << GPIO_DRV0_IO14_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV0[31:30] - GPIOA_15 Drive Current Select
 */
#define GPIO_DRV0_IO15_DRV_SEL_POS          (30)
#define GPIO_DRV0_IO15_DRV_SEL_MSK          (0x3UL << GPIO_DRV0_IO15_DRV_SEL_POS)
#define GPIO_DRV0_IO15_DRV_16mA             (0x3UL << GPIO_DRV0_IO15_DRV_SEL_POS)
#define GPIO_DRV0_IO15_DRV_12mA             (0x2UL << GPIO_DRV0_IO15_DRV_SEL_POS)
#define GPIO_DRV0_IO15_DRV_8mA              (0x1UL << GPIO_DRV0_IO15_DRV_SEL_POS)
#define GPIO_DRV0_IO15_DRV_4mA              (0x0UL << GPIO_DRV0_IO15_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[1:0] - GPIOA_16 Drive Current Select
 */
#define GPIO_DRV1_IO16_DRV_SEL_POS          (0)
#define GPIO_DRV1_IO16_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO16_DRV_SEL_POS)
#define GPIO_DRV1_IO16_DRV_16mA             (0x3UL << GPIO_DRV1_IO16_DRV_SEL_POS)
#define GPIO_DRV1_IO16_DRV_12mA             (0x2UL << GPIO_DRV1_IO16_DRV_SEL_POS)
#define GPIO_DRV1_IO16_DRV_8mA              (0x1UL << GPIO_DRV1_IO16_DRV_SEL_POS)
#define GPIO_DRV1_IO16_DRV_4mA              (0x0UL << GPIO_DRV1_IO16_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[3:2] - GPIOA_17 Drive Current Select
 */
#define GPIO_DRV1_IO17_DRV_SEL_POS          (2)
#define GPIO_DRV1_IO17_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO17_DRV_SEL_POS)
#define GPIO_DRV1_IO17_DRV_17mA             (0x3UL << GPIO_DRV1_IO17_DRV_SEL_POS)
#define GPIO_DRV1_IO17_DRV_12mA             (0x2UL << GPIO_DRV1_IO17_DRV_SEL_POS)
#define GPIO_DRV1_IO17_DRV_8mA              (0x1UL << GPIO_DRV1_IO17_DRV_SEL_POS)
#define GPIO_DRV1_IO17_DRV_4mA              (0x0UL << GPIO_DRV1_IO17_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[5:4] - GPIOA_18 Drive Current Select
 */
#define GPIO_DRV1_IO18_DRV_SEL_POS          (4)
#define GPIO_DRV1_IO18_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO18_DRV_SEL_POS)
#define GPIO_DRV1_IO18_DRV_18mA             (0x3UL << GPIO_DRV1_IO18_DRV_SEL_POS)
#define GPIO_DRV1_IO18_DRV_12mA             (0x2UL << GPIO_DRV1_IO18_DRV_SEL_POS)
#define GPIO_DRV1_IO18_DRV_8mA              (0x1UL << GPIO_DRV1_IO18_DRV_SEL_POS)
#define GPIO_DRV1_IO18_DRV_4mA              (0x0UL << GPIO_DRV1_IO18_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[7:6] - GPIOA_19 Drive Current Select
 */
#define GPIO_DRV1_IO19_DRV_SEL_POS          (6)
#define GPIO_DRV1_IO19_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO19_DRV_SEL_POS)
#define GPIO_DRV1_IO19_DRV_19mA             (0x3UL << GPIO_DRV1_IO19_DRV_SEL_POS)
#define GPIO_DRV1_IO19_DRV_12mA             (0x2UL << GPIO_DRV1_IO19_DRV_SEL_POS)
#define GPIO_DRV1_IO19_DRV_8mA              (0x1UL << GPIO_DRV1_IO19_DRV_SEL_POS)
#define GPIO_DRV1_IO19_DRV_4mA              (0x0UL << GPIO_DRV1_IO19_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[9:8] - GPIOA_20 Drive Current Select
 */
#define GPIO_DRV1_IO20_DRV_SEL_POS          (8)
#define GPIO_DRV1_IO20_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO20_DRV_SEL_POS)
#define GPIO_DRV1_IO20_DRV_20mA             (0x3UL << GPIO_DRV1_IO20_DRV_SEL_POS)
#define GPIO_DRV1_IO20_DRV_12mA             (0x2UL << GPIO_DRV1_IO20_DRV_SEL_POS)
#define GPIO_DRV1_IO20_DRV_8mA              (0x1UL << GPIO_DRV1_IO20_DRV_SEL_POS)
#define GPIO_DRV1_IO20_DRV_4mA              (0x0UL << GPIO_DRV1_IO20_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[11:10] - GPIOA_21 Drive Current Select
 */
#define GPIO_DRV1_IO21_DRV_SEL_POS          (10)
#define GPIO_DRV1_IO21_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO21_DRV_SEL_POS)
#define GPIO_DRV1_IO21_DRV_21mA             (0x3UL << GPIO_DRV1_IO21_DRV_SEL_POS)
#define GPIO_DRV1_IO21_DRV_12mA             (0x2UL << GPIO_DRV1_IO21_DRV_SEL_POS)
#define GPIO_DRV1_IO21_DRV_8mA              (0x1UL << GPIO_DRV1_IO21_DRV_SEL_POS)
#define GPIO_DRV1_IO21_DRV_4mA              (0x0UL << GPIO_DRV1_IO21_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[13:12] - GPIOA_22 Drive Current Select
 */
#define GPIO_DRV1_IO22_DRV_SEL_POS          (12)
#define GPIO_DRV1_IO22_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO22_DRV_SEL_POS)
#define GPIO_DRV1_IO22_DRV_22mA             (0x3UL << GPIO_DRV1_IO22_DRV_SEL_POS)
#define GPIO_DRV1_IO22_DRV_12mA             (0x2UL << GPIO_DRV1_IO22_DRV_SEL_POS)
#define GPIO_DRV1_IO22_DRV_8mA              (0x1UL << GPIO_DRV1_IO22_DRV_SEL_POS)
#define GPIO_DRV1_IO22_DRV_4mA              (0x0UL << GPIO_DRV1_IO22_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[15:14] - GPIOA_23 Drive Current Select
 */
#define GPIO_DRV1_IO23_DRV_SEL_POS          (14)
#define GPIO_DRV1_IO23_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO23_DRV_SEL_POS)
#define GPIO_DRV1_IO23_DRV_23mA             (0x3UL << GPIO_DRV1_IO23_DRV_SEL_POS)
#define GPIO_DRV1_IO23_DRV_12mA             (0x2UL << GPIO_DRV1_IO23_DRV_SEL_POS)
#define GPIO_DRV1_IO23_DRV_8mA              (0x1UL << GPIO_DRV1_IO23_DRV_SEL_POS)
#define GPIO_DRV1_IO23_DRV_4mA              (0x0UL << GPIO_DRV1_IO23_DRV_SEL_POS)

/*
 * Bit definition for GPIO_DRV1[17:16] - GPIOA_24 Drive Current Select
 */
#define GPIO_DRV1_IO24_DRV_SEL_POS          (16)
#define GPIO_DRV1_IO24_DRV_SEL_MSK          (0x3UL << GPIO_DRV1_IO24_DRV_SEL_POS)
#define GPIO_DRV1_IO24_DRV_24mA             (0x3UL << GPIO_DRV1_IO24_DRV_SEL_POS)
#define GPIO_DRV1_IO24_DRV_12mA             (0x2UL << GPIO_DRV1_IO24_DRV_SEL_POS)
#define GPIO_DRV1_IO24_DRV_8mA              (0x1UL << GPIO_DRV1_IO24_DRV_SEL_POS)
#define GPIO_DRV1_IO24_DRV_4mA              (0x0UL << GPIO_DRV1_IO24_DRV_SEL_POS)

/*
 * Bit definition for GPIO_SMT[0] - GPIOA/B_0 schmitt control register.
 */
#define GPIO_SMT_IO0_EN_POS                 (0)
#define GPIO_SMT_IO0_EN_MSK                 (0x1UL << GPIO_SMT_IO0_EN_POS)
#define GPIO_SMT_IO0_EN_ENABLE              (0x1UL << GPIO_SMT_IO0_EN_POS)
#define GPIO_SMT_IO0_EN_DISABLE             (0x0UL << GPIO_SMT_IO0_EN_POS)

/*
 * Bit definition for GPIO_SMT[1] - GPIOA/B_1 schmitt control register.
 */
#define GPIO_SMT_IO1_EN_POS                 (1)
#define GPIO_SMT_IO1_EN_MSK                 (0x1UL << GPIO_SMT_IO1_EN_POS)
#define GPIO_SMT_IO1_EN_ENABLE              (0x1UL << GPIO_SMT_IO1_EN_POS)
#define GPIO_SMT_IO1_EN_DISABLE             (0x0UL << GPIO_SMT_IO1_EN_POS)

/*
 * Bit definition for GPIO_SMT[2] - GPIOA/B_2 schmitt control register.
 */
#define GPIO_SMT_IO2_EN_POS                 (2)
#define GPIO_SMT_IO2_EN_MSK                 (0x1UL << GPIO_SMT_IO2_EN_POS)
#define GPIO_SMT_IO2_EN_ENABLE              (0x1UL << GPIO_SMT_IO2_EN_POS)
#define GPIO_SMT_IO2_EN_DISABLE             (0x0UL << GPIO_SMT_IO2_EN_POS)

/*
 * Bit definition for GPIO_SMT[3] - GPIOA/B_3 schmitt control register.
 */
#define GPIO_SMT_IO3_EN_POS                 (3)
#define GPIO_SMT_IO3_EN_MSK                 (0x1UL << GPIO_SMT_IO3_EN_POS)
#define GPIO_SMT_IO3_EN_ENABLE              (0x1UL << GPIO_SMT_IO3_EN_POS)
#define GPIO_SMT_IO3_EN_DISABLE             (0x0UL << GPIO_SMT_IO3_EN_POS)

/*
 * Bit definition for GPIO_SMT[4] - GPIOA/B_4 schmitt control register.
 */
#define GPIO_SMT_IO4_EN_POS                 (4)
#define GPIO_SMT_IO4_EN_MSK                 (0x1UL << GPIO_SMT_IO4_EN_POS)
#define GPIO_SMT_IO4_EN_ENABLE              (0x1UL << GPIO_SMT_IO4_EN_POS)
#define GPIO_SMT_IO4_EN_DISABLE             (0x0UL << GPIO_SMT_IO4_EN_POS)

/*
 * Bit definition for GPIO_SMT[5] - GPIOA/B_5 schmitt control register.
 */
#define GPIO_SMT_IO5_EN_POS                 (5)
#define GPIO_SMT_IO5_EN_MSK                 (0x1UL << GPIO_SMT_IO5_EN_POS)
#define GPIO_SMT_IO5_EN_ENABLE              (0x1UL << GPIO_SMT_IO5_EN_POS)
#define GPIO_SMT_IO5_EN_DISABLE             (0x0UL << GPIO_SMT_IO5_EN_POS)

/*
 * Bit definition for GPIO_SMT[6] - GPIOA_6 schmitt control register.
 */
#define GPIO_SMT_IO6_EN_POS                 (6)
#define GPIO_SMT_IO6_EN_MSK                 (0x1UL << GPIO_SMT_IO6_EN_POS)
#define GPIO_SMT_IO6_EN_ENABLE              (0x1UL << GPIO_SMT_IO6_EN_POS)
#define GPIO_SMT_IO6_EN_DISABLE             (0x0UL << GPIO_SMT_IO6_EN_POS)

/*
 * Bit definition for GPIO_SMT[7] - GPIOA_7 schmitt control register.
 */
#define GPIO_SMT_IO7_EN_POS                 (7)
#define GPIO_SMT_IO7_EN_MSK                 (0x1UL << GPIO_SMT_IO7_EN_POS)
#define GPIO_SMT_IO7_EN_ENABLE              (0x1UL << GPIO_SMT_IO7_EN_POS)
#define GPIO_SMT_IO7_EN_DISABLE             (0x0UL << GPIO_SMT_IO7_EN_POS)

/*
 * Bit definition for GPIO_SMT[8] - GPIOA_8 schmitt control register.
 */
#define GPIO_SMT_IO8_EN_POS                 (8)
#define GPIO_SMT_IO8_EN_MSK                 (0x1UL << GPIO_SMT_IO8_EN_POS)
#define GPIO_SMT_IO8_EN_ENABLE              (0x1UL << GPIO_SMT_IO8_EN_POS)
#define GPIO_SMT_IO8_EN_DISABLE             (0x0UL << GPIO_SMT_IO8_EN_POS)

/*
 * Bit definition for GPIO_SMT[9] - GPIOA_9 schmitt control register.
 */
#define GPIO_SMT_IO9_EN_POS                 (9)
#define GPIO_SMT_IO9_EN_MSK                 (0x1UL << GPIO_SMT_IO9_EN_POS)
#define GPIO_SMT_IO9_EN_ENABLE              (0x1UL << GPIO_SMT_IO9_EN_POS)
#define GPIO_SMT_IO9_EN_DISABLE             (0x0UL << GPIO_SMT_IO9_EN_POS)

/*
 * Bit definition for GPIO_SMT[10] - GPIOA_10 schmitt control register.
 */
#define GPIO_SMT_IO10_EN_POS                 (10)
#define GPIO_SMT_IO10_EN_MSK                 (0x1UL << GPIO_SMT_IO10_EN_POS)
#define GPIO_SMT_IO10_EN_ENABLE              (0x1UL << GPIO_SMT_IO10_EN_POS)
#define GPIO_SMT_IO10_EN_DISABLE             (0x0UL << GPIO_SMT_IO10_EN_POS)

/*
 * Bit definition for GPIO_SMT[11] - GPIOA_11 schmitt control register.
 */
#define GPIO_SMT_IO11_EN_POS                 (11)
#define GPIO_SMT_IO11_EN_MSK                 (0x1UL << GPIO_SMT_IO11_EN_POS)
#define GPIO_SMT_IO11_EN_ENABLE              (0x1UL << GPIO_SMT_IO11_EN_POS)
#define GPIO_SMT_IO11_EN_DISABLE             (0x0UL << GPIO_SMT_IO11_EN_POS)

/*
 * Bit definition for GPIO_SMT[12] - GPIOA_12 schmitt control register.
 */
#define GPIO_SMT_IO12_EN_POS                 (12)
#define GPIO_SMT_IO12_EN_MSK                 (0x1UL << GPIO_SMT_IO12_EN_POS)
#define GPIO_SMT_IO12_EN_ENABLE              (0x1UL << GPIO_SMT_IO12_EN_POS)
#define GPIO_SMT_IO12_EN_DISABLE             (0x0UL << GPIO_SMT_IO12_EN_POS)

/*
 * Bit definition for GPIO_SMT[13] - GPIOA_13 schmitt control register.
 */
#define GPIO_SMT_IO13_EN_POS                 (13)
#define GPIO_SMT_IO13_EN_MSK                 (0x1UL << GPIO_SMT_IO13_EN_POS)
#define GPIO_SMT_IO13_EN_ENABLE              (0x1UL << GPIO_SMT_IO13_EN_POS)
#define GPIO_SMT_IO13_EN_DISABLE             (0x0UL << GPIO_SMT_IO13_EN_POS)

/*
 * Bit definition for GPIO_SMT[14] - GPIOA_14 schmitt control register.
 */
#define GPIO_SMT_IO14_EN_POS                 (14)
#define GPIO_SMT_IO14_EN_MSK                 (0x1UL << GPIO_SMT_IO14_EN_POS)
#define GPIO_SMT_IO14_EN_ENABLE              (0x1UL << GPIO_SMT_IO14_EN_POS)
#define GPIO_SMT_IO14_EN_DISABLE             (0x0UL << GPIO_SMT_IO14_EN_POS)

/*
 * Bit definition for GPIO_SMT[15] - GPIOA_15 schmitt control register.
 */
#define GPIO_SMT_IO15_EN_POS                 (15)
#define GPIO_SMT_IO15_EN_MSK                 (0x1UL << GPIO_SMT_IO15_EN_POS)
#define GPIO_SMT_IO15_EN_ENABLE              (0x1UL << GPIO_SMT_IO15_EN_POS)
#define GPIO_SMT_IO15_EN_DISABLE             (0x0UL << GPIO_SMT_IO15_EN_POS)

/*
 * Bit definition for GPIO_SMT[16] - GPIOA_16 schmitt control register.
 */
#define GPIO_SMT_IO16_EN_POS                 (16)
#define GPIO_SMT_IO16_EN_MSK                 (0x1UL << GPIO_SMT_IO16_EN_POS)
#define GPIO_SMT_IO16_EN_ENABLE              (0x1UL << GPIO_SMT_IO16_EN_POS)
#define GPIO_SMT_IO16_EN_DISABLE             (0x0UL << GPIO_SMT_IO16_EN_POS)

/*
 * Bit definition for GPIO_SMT[17] - GPIOA_17 schmitt control register.
 */
#define GPIO_SMT_IO17_EN_POS                 (17)
#define GPIO_SMT_IO17_EN_MSK                 (0x1UL << GPIO_SMT_IO17_EN_POS)
#define GPIO_SMT_IO17_EN_ENABLE              (0x1UL << GPIO_SMT_IO17_EN_POS)
#define GPIO_SMT_IO17_EN_DISABLE             (0x0UL << GPIO_SMT_IO17_EN_POS)

/*
 * Bit definition for GPIO_SMT[18] - GPIOA_18 schmitt control register.
 */
#define GPIO_SMT_IO18_EN_POS                 (18)
#define GPIO_SMT_IO18_EN_MSK                 (0x1UL << GPIO_SMT_IO18_EN_POS)
#define GPIO_SMT_IO18_EN_ENABLE              (0x1UL << GPIO_SMT_IO18_EN_POS)
#define GPIO_SMT_IO18_EN_DISABLE             (0x0UL << GPIO_SMT_IO18_EN_POS)

/*
 * Bit definition for GPIO_SMT[19] - GPIOA_19 schmitt control register.
 */
#define GPIO_SMT_IO19_EN_POS                 (19)
#define GPIO_SMT_IO19_EN_MSK                 (0x1UL << GPIO_SMT_IO19_EN_POS)
#define GPIO_SMT_IO19_EN_ENABLE              (0x1UL << GPIO_SMT_IO19_EN_POS)
#define GPIO_SMT_IO19_EN_DISABLE             (0x0UL << GPIO_SMT_IO19_EN_POS)

/*
 * Bit definition for GPIO_SMT[20] - GPIOA_20 schmitt control register.
 */
#define GPIO_SMT_IO20_EN_POS                 (20)
#define GPIO_SMT_IO20_EN_MSK                 (0x1UL << GPIO_SMT_IO20_EN_POS)
#define GPIO_SMT_IO20_EN_ENABLE              (0x1UL << GPIO_SMT_IO20_EN_POS)
#define GPIO_SMT_IO20_EN_DISABLE             (0x0UL << GPIO_SMT_IO20_EN_POS)

/*
 * Bit definition for GPIO_SMT[21] - GPIOA_21 schmitt control register.
 */
#define GPIO_SMT_IO21_EN_POS                 (21)
#define GPIO_SMT_IO21_EN_MSK                 (0x1UL << GPIO_SMT_IO21_EN_POS)
#define GPIO_SMT_IO21_EN_ENABLE              (0x1UL << GPIO_SMT_IO21_EN_POS)
#define GPIO_SMT_IO21_EN_DISABLE             (0x0UL << GPIO_SMT_IO21_EN_POS)

/*
 * Bit definition for GPIO_SMT[22] - GPIOA_22 schmitt control register.
 */
#define GPIO_SMT_IO22_EN_POS                 (22)
#define GPIO_SMT_IO22_EN_MSK                 (0x1UL << GPIO_SMT_IO22_EN_POS)
#define GPIO_SMT_IO22_EN_ENABLE              (0x1UL << GPIO_SMT_IO22_EN_POS)
#define GPIO_SMT_IO22_EN_DISABLE             (0x0UL << GPIO_SMT_IO22_EN_POS)

/*
 * Bit definition for GPIO_SMT[23] - GPIOA_23 schmitt control register.
 */
#define GPIO_SMT_IO23_EN_POS                 (23)
#define GPIO_SMT_IO23_EN_MSK                 (0x1UL << GPIO_SMT_IO23_EN_POS)
#define GPIO_SMT_IO23_EN_ENABLE              (0x1UL << GPIO_SMT_IO23_EN_POS)
#define GPIO_SMT_IO23_EN_DISABLE             (0x0UL << GPIO_SMT_IO23_EN_POS)









typedef struct
{
	__IO uint32_t CTRL0;                      //
	__IO uint32_t CTRL1;                      //
	__IO uint32_t CTRL2;                      //
	__I  uint32_t RESERVED0[1]; 							// Reserved
	__IO uint32_t WAKEEN;           					// Key Change Wake up Enable
	__IO uint32_t STS;              					// Key Change INT Status
} GPIOFUNC_TYPE_DEF;

typedef struct
{
	__IO uint32_t OBIT00;
	__IO uint32_t OBIT01;
	__IO uint32_t OBIT02;
	__IO uint32_t OBIT03;
	__IO uint32_t OBIT04;
	__IO uint32_t OBIT05;
	__IO uint32_t OBIT06;
	__IO uint32_t OBIT07;
	__IO uint32_t OBIT08;
	__IO uint32_t OBIT09;
	__IO uint32_t OBIT10;
	__IO uint32_t OBIT11;
	__IO uint32_t OBIT12;
	__IO uint32_t OBIT13;
	__IO uint32_t OBIT14;
	__IO uint32_t OBIT15;
	__IO uint32_t OBIT16;
	__IO uint32_t OBIT17;
	__IO uint32_t OBIT18;
	__IO uint32_t OBIT19;
	__IO uint32_t OBIT20;
	__IO uint32_t OBIT21;
	__IO uint32_t OBIT22;
	__IO uint32_t OBIT23;
	__IO uint32_t OBIT24;
} GPIO_BIT_OPERATION_TYPE_DEF;

/*
 * Bit definition for GPIOFUNC_CTRL0[17:16] - I2C pins Select
 */
#define GPIOFUNC_CTRL0_I2C_POS              (16)
#define GPIOFUNC_CTRL0_I2C_MSK              (0x3UL << GPIOFUNC_CTRL0_I2C_POS)
#define GPIOFUNC_CTRL0_I2C_IOA13_17         (0x2UL << GPIOFUNC_CTRL0_I2C_POS)
#define GPIOFUNC_CTRL0_I2C_IOA15_16         (0x1UL << GPIOFUNC_CTRL0_I2C_POS)
#define GPIOFUNC_CTRL0_I2C_IOA0_1           (0x0UL << GPIOFUNC_CTRL0_I2C_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[14] -
 */
#define GPIOFUNC_CTRL0_SPI0_IOSEL_POS       (14)
#define GPIOFUNC_CTRL0_SPI0_IOSEL_MSK       (0x1UL << GPIOFUNC_CTRL0_SPI0_IOSEL_POS)
#define GPIOFUNC_CTRL0_SPI0_IOB1_4          (0x1UL << GPIOFUNC_CTRL0_SPI0_IOSEL_POS)
#define GPIOFUNC_CTRL0_SPI0_IOA9_12         (0x0UL << GPIOFUNC_CTRL0_SPI0_IOSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[13] - CCP0 Output pins control
 */
#define GPIOFUNC_CTRL0_CCP0_POS             (13)
#define GPIOFUNC_CTRL0_CCP0_MSK             (0x1UL << GPIOFUNC_CTRL0_CCP0_POS)
#define GPIOFUNC_CTRL0_CCP0_IOA0_3          (0x0UL << GPIOFUNC_CTRL0_CCP0_POS)
#define GPIOFUNC_CTRL0_CCP0_IOA13_16        (0x1UL << GPIOFUNC_CTRL0_CCP0_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[12] -
 */
#define GPIOFUNC_CTRL0_SPIFC_IOSEL_POS      (12)
#define GPIOFUNC_CTRL0_SPIFC_IOSEL_MSK      (0x1UL << GPIOFUNC_CTRL0_SPIFC_IOSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[11: 10] -
 */
#define IOFUNC_CTRL0_UART_IOSEL_POS         (10)
#define IOFUNC_CTRL0_UART_IOSEL_MSK         (0x3UL << IOFUNC_CTRL0_UART_IOSEL_POS)
#define IOFUNC_CTRL0_UART_IOA0_9            (0x3UL << IOFUNC_CTRL0_UART_IOSEL_POS)
#define IOFUNC_CTRL0_UART_IOA22_23          (0x2UL << IOFUNC_CTRL0_UART_IOSEL_POS)
#define IOFUNC_CTRL0_UART_IOA13_14          (0x1UL << IOFUNC_CTRL0_UART_IOSEL_POS)
#define IOFUNC_CTRL0_UART_IOA4_5            (0x0UL << IOFUNC_CTRL0_UART_IOSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[9] -
 */
#define GPIOFUNC_CTRL0_SPI1_IOSEL_POS       (9)
#define GPIOFUNC_CTRL0_SPI1_IOSEL_MSK       (0x1UL << GPIOFUNC_CTRL0_SPI1_IOSEL_POS)
#define GPIOFUNC_CTRL0_SPI1_IOA18_21        (0x1UL << GPIOFUNC_CTRL0_SPI1_IOSEL_POS)
#define GPIOFUNC_CTRL0_SPI1_IOA0_3          (0x0UL << GPIOFUNC_CTRL0_SPI1_IOSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[8] -
 */
#define GPIOFUNC_CTRL0_IR_IOSEL_POS         (8)
#define GPIOFUNC_CTRL0_IR_IOSEL_MSK         (0x1UL << GPIOFUNC_CTRL0_IR_IOSEL_POS)
#define GPIOFUNC_CTRL0_IR_IOA17             (0x1UL << GPIOFUNC_CTRL0_IR_IOSEL_POS)
#define GPIOFUNC_CTRL0_IR_IOA4              (0x0UL << GPIOFUNC_CTRL0_IR_IOSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[5] - SPI1 CS H/W control enable
 */
#define GPIOFUNC_CTRL0_SPI1_HWCS_EN_POS     (5)
#define GPIOFUNC_CTRL0_SPI1_HWCS_EN_MSK     (0x1UL << GPIOFUNC_CTRL0_SPI1_HWCS_EN_POS)
#define GPIOFUNC_CTRL0_SPI1_HWCS_ENABLE     (0x1UL << GPIOFUNC_CTRL0_SPI1_HWCS_EN_POS)
#define GPIOFUNC_CTRL0_SPI1_HWCS_DISABLE    (0x0UL << GPIOFUNC_CTRL0_SPI1_HWCS_EN_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[4] - SPI0 CS H/W control enable
 */
#define GPIOFUNC_CTRL0_SPI0_HWCS_EN_POS     (4)
#define GPIOFUNC_CTRL0_SPI0_HWCS_EN_MSK     (0x1UL << GPIOFUNC_CTRL0_SPI0_HWCS_EN_POS)
#define GPIOFUNC_CTRL0_SPI0_HWCS_ENABLE     (0x1UL << GPIOFUNC_CTRL0_SPI0_HWCS_EN_POS)
#define GPIOFUNC_CTRL0_SPI0_HWCS_DISABLE    (0x0UL << GPIOFUNC_CTRL0_SPI0_HWCS_EN_POS)

/*
 * Bit definition for GPIOFUNC_CTRL0[0] - ICE enable
 */
#define GPIOFUNC_CTRL0_ICE_EN_POS           (0)
#define GPIOFUNC_CTRL0_ICE_EN_MSK           (0x1UL << GPIOFUNC_CTRL0_ICE_EN_POS)
#define GPIOFUNC_CTRL0_ICE_ENABLE           (0x1UL << GPIOFUNC_CTRL0_ICE_EN_POS)
#define GPIOFUNC_CTRL0_ICE_DISABLE          (0x0UL << GPIOFUNC_CTRL0_ICE_EN_POS)

/*
 * Bit definition for GPIOFUNC_CTRL1[7] - IR TX Polarity
 */
#define GPIOFUNC_CTRL1_IR_POL_POS            	(7)
#define GPIOFUNC_CTRL1_IR_POL_MSK             (0x1UL << GPIOFUNC_CTRL1_IR_POL_POS)
#define GPIOFUNC_CTRL1_IR_POL_NEGATIVE				(0x1UL << GPIOFUNC_CTRL1_IR_POL_POS)
#define GPIOFUNC_CTRL1_IR_POL_POSITIVE				(0x0UL << GPIOFUNC_CTRL1_IR_POL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL1[6] - IR TX Mask
 */
#define GPIOFUNC_CTRL1_IR_MAK_POS            	(6)
#define GPIOFUNC_CTRL1_IR_MAK_MSK             (0x1UL << GPIOFUNC_CTRL1_IR_MAK_POS)
#define GPIOFUNC_CTRL1_IR_MAK_ENABLE					(0x1UL << GPIOFUNC_CTRL1_IR_MAK_POS)
#define GPIOFUNC_CTRL1_IR_MAK_DISABLE					(0x0UL << GPIOFUNC_CTRL1_IR_MAK_POS)

/*
 * Bit definition for GPIOFUNC_CTRL1[5: 3] - IR TX CLK Source Selection
 */
#define GPIOFUNC_CTRL1_IR_CLK_SEL_POS     		(3)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_MSK         (0x7UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_CTS1				(0x6UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_CTS0				(0x5UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_CCP1        (0x4UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_CCP0        (0x3UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_TIMER2      (0x2UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_TIMER1      (0x1UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)
#define GPIOFUNC_CTRL1_IR_CLK_SEL_TIMER0      (0x0UL << GPIOFUNC_CTRL1_IR_CLK_SEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL1[2: 1] - IR TX Duty
 */
#define GPIOFUNC_CTRL1_IR_DUTY_POS         		(1)
#define GPIOFUNC_CTRL1_IR_DUTY_MSK         		(0x3UL << GPIOFUNC_CTRL1_IR_DUTY_POS)
#define GPIOFUNC_CTRL1_IR_DUTY_DIV_5          (0x3UL << GPIOFUNC_CTRL1_IR_DUTY_POS)
#define GPIOFUNC_CTRL1_IR_DUTY_DIV_4         	(0x2UL << GPIOFUNC_CTRL1_IR_DUTY_POS)
#define GPIOFUNC_CTRL1_IR_DUTY_DIV_3         	(0x1UL << GPIOFUNC_CTRL1_IR_DUTY_POS)
#define GPIOFUNC_CTRL1_IR_DUTY_DIV_2          (0x0UL << GPIOFUNC_CTRL1_IR_DUTY_POS)

/*
 * Bit definition for GPIOFUNC_CTRL1[0] - IR TX Enable
 */
#define GPIOFUNC_CTRL1_IR_TX_EN_POS        		(0)
#define GPIOFUNC_CTRL1_IR_TX_EN_MSK           (0x1ul << GPIOFUNC_CTRL1_IR_TX_EN_POS)
#define GPIOFUNC_CTRL1_IR_TX_ENABLE           (0x1ul << GPIOFUNC_CTRL1_IR_TX_EN_POS)
#define GPIOFUNC_CTRL1_IR_TX_DISABLE          (0x0ul << GPIOFUNC_CTRL1_IR_TX_EN_POS)

/*
 * Bit definition for GPIOFUNC_CTRL2[28:24] -  EXT3 input pins select
 */
#define GPIOFUNC_CTRL2_EXT3_PINSEL_POS      (24)
#define GPIOFUNC_CTRL2_EXT3_PINSEL_MSK      (0x1FUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB5            (0x1EUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB4            (0x1DUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB3            (0x1CUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB2            (0x1BUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB1            (0x1AUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOB0            (0x19UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA24           (0x18UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA23           (0x17UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA22           (0x16UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA21           (0x15UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA20           (0x14UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA19           (0x13UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA18           (0x12UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA17           (0x11UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA16           (0x10UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA15           (0x0FUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA14           (0x0EUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA13           (0x0DUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA12           (0x0CUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA11           (0x0BUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA10           (0x0AUL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA9            (0x09UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA8            (0x08UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA7            (0x07UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA6            (0x06UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA5            (0x05UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA4            (0x04UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA3            (0x03UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA2            (0x02UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA1            (0x01UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT3_IOA0            (0x00UL << GPIOFUNC_CTRL2_EXT3_PINSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL2[20:16] -  EXT2 input pins select
 */
#define GPIOFUNC_CTRL2_EXT2_PINSEL_POS      (16)
#define GPIOFUNC_CTRL2_EXT2_PINSEL_MSK      (0x1FUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB5            (0x1EUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB4            (0x1DUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB3            (0x1CUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB2            (0x1BUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB1            (0x1AUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOB0            (0x19UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA24           (0x18UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA23           (0x17UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA22           (0x16UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA21           (0x15UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA20           (0x14UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA19           (0x13UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA18           (0x12UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA17           (0x11UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA16           (0x10UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA15           (0x0FUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA14           (0x0EUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA13           (0x0DUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA12           (0x0CUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA11           (0x0BUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA10           (0x0AUL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA9            (0x09UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA8            (0x08UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA7            (0x07UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA6            (0x06UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA5            (0x05UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA4            (0x04UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA3            (0x03UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA2            (0x02UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA1            (0x01UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT2_IOA0            (0x00UL << GPIOFUNC_CTRL2_EXT2_PINSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL2[12:8] -  EXT1 input pins select
 */
#define GPIOFUNC_CTRL2_EXT1_PINSEL_POS      (8)
#define GPIOFUNC_CTRL2_EXT1_PINSEL_MSK      (0x1FUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB5            (0x1EUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB4            (0x1DUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB3            (0x1CUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB2            (0x1BUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB1            (0x1AUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOB0            (0x19UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA24           (0x18UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA23           (0x17UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA22           (0x16UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA21           (0x15UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA20           (0x14UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA19           (0x13UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA18           (0x12UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA17           (0x11UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA16           (0x10UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA15           (0x0FUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA14           (0x0EUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA13           (0x0DUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA12           (0x0CUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA11           (0x0BUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA10           (0x0AUL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA9            (0x09UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA8            (0x08UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA7            (0x07UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA6            (0x06UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA5            (0x05UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA4            (0x04UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA3            (0x03UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA2            (0x02UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA1            (0x01UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT1_IOA0            (0x00UL << GPIOFUNC_CTRL2_EXT1_PINSEL_POS)

/*
 * Bit definition for GPIOFUNC_CTRL2[4:0] -  EXT0 input pins select
 */
#define GPIOFUNC_CTRL2_EXT0_PINSEL_POS      (0)
#define GPIOFUNC_CTRL2_EXT0_PINSEL_MSK      (0x1FUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB5            (0x1EUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB4            (0x1DUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB3            (0x1CUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB2            (0x1BUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB1            (0x1AUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOB0            (0x19UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA24           (0x18UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA23           (0x17UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA22           (0x16UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA21           (0x15UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA20           (0x14UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA19           (0x13UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA18           (0x12UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA17           (0x11UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA16           (0x10UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA15           (0x0FUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA14           (0x0EUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA13           (0x0DUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA12           (0x0CUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA11           (0x0BUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA10           (0x0AUL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA9            (0x09UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA8            (0x08UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA7            (0x07UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA6            (0x06UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA5            (0x05UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA4            (0x04UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA3            (0x03UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA2            (0x02UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA1            (0x01UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)
#define GPIOFUNC_CTRL2_EXT0_IOA0            (0x00UL << GPIOFUNC_CTRL2_EXT0_PINSEL_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[31] - GPIO key change interrupt enable
 */
#define GPIOFUNC_WAKEEN_INT_EN_POS          (31)
#define GPIOFUNC_WAKEEN_INT_EN_MSK          (0x1UL << GPIOFUNC_WAKEEN_INT_EN_POS)
#define GPIOFUNC_WAKEEN_INT_ENABLE          (0x1UL << GPIOFUNC_WAKEEN_INT_EN_POS)
#define GPIOFUNC_WAKEEN_INT_DISABLE         (0x0UL << GPIOFUNC_WAKEEN_INT_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[30] - IOB5 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB5_EN_POS         (30)
#define GPIOFUNC_WAKEEN_IOB5_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB5_EN_POS)
#define GPIOFUNC_WAKEEN_IOB5_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB5_EN_POS)
#define GPIOFUNC_WAKEEN_IOB5_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB5_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[29] - IOB4 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB4_EN_POS         (29)
#define GPIOFUNC_WAKEEN_IOB4_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB4_EN_POS)
#define GPIOFUNC_WAKEEN_IOB4_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB4_EN_POS)
#define GPIOFUNC_WAKEEN_IOB4_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB4_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[28] - IOB3 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB3_EN_POS         (28)
#define GPIOFUNC_WAKEEN_IOB3_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB3_EN_POS)
#define GPIOFUNC_WAKEEN_IOB3_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB3_EN_POS)
#define GPIOFUNC_WAKEEN_IOB3_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB3_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[27] - IOB2 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB2_EN_POS         (27)
#define GPIOFUNC_WAKEEN_IOB2_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB2_EN_POS)
#define GPIOFUNC_WAKEEN_IOB2_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB2_EN_POS)
#define GPIOFUNC_WAKEEN_IOB2_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB2_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[26] - IOB1 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB1_EN_POS         (26)
#define GPIOFUNC_WAKEEN_IOB1_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB1_EN_POS)
#define GPIOFUNC_WAKEEN_IOB1_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB1_EN_POS)
#define GPIOFUNC_WAKEEN_IOB1_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB1_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[25] - IOB0 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOB0_EN_POS         (25)
#define GPIOFUNC_WAKEEN_IOB0_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOB0_EN_POS)
#define GPIOFUNC_WAKEEN_IOB0_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOB0_EN_POS)
#define GPIOFUNC_WAKEEN_IOB0_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOB0_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[24] - IOA24 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA24_EN_POS        (24)
#define GPIOFUNC_WAKEEN_IOA24_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA24_EN_POS)
#define GPIOFUNC_WAKEEN_IOA24_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA24_EN_POS)
#define GPIOFUNC_WAKEEN_IOA24_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA24_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[23] - IOA23 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA23_EN_POS        (23)
#define GPIOFUNC_WAKEEN_IOA23_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA23_EN_POS)
#define GPIOFUNC_WAKEEN_IOA23_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA23_EN_POS)
#define GPIOFUNC_WAKEEN_IOA23_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA23_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[22] - IOA22 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA22_EN_POS        (22)
#define GPIOFUNC_WAKEEN_IOA22_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA22_EN_POS)
#define GPIOFUNC_WAKEEN_IOA22_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA22_EN_POS)
#define GPIOFUNC_WAKEEN_IOA22_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA22_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[21] - IOA21 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA21_EN_POS        (21)
#define GPIOFUNC_WAKEEN_IOA21_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA21_EN_POS)
#define GPIOFUNC_WAKEEN_IOA21_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA21_EN_POS)
#define GPIOFUNC_WAKEEN_IOA21_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA21_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[20] - IOA20 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA20_EN_POS        (20)
#define GPIOFUNC_WAKEEN_IOA20_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA20_EN_POS)
#define GPIOFUNC_WAKEEN_IOA20_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA20_EN_POS)
#define GPIOFUNC_WAKEEN_IOA20_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA20_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[19] - IOA19 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA19_EN_POS        (19)
#define GPIOFUNC_WAKEEN_IOA19_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA19_EN_POS)
#define GPIOFUNC_WAKEEN_IOA19_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA19_EN_POS)
#define GPIOFUNC_WAKEEN_IOA19_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA19_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[18] - IOA18 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA18_EN_POS        (18)
#define GPIOFUNC_WAKEEN_IOA18_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA18_EN_POS)
#define GPIOFUNC_WAKEEN_IOA18_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA18_EN_POS)
#define GPIOFUNC_WAKEEN_IOA18_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA18_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[17] - IOA17 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA17_EN_POS        (17)
#define GPIOFUNC_WAKEEN_IOA17_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA17_EN_POS)
#define GPIOFUNC_WAKEEN_IOA17_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA17_EN_POS)
#define GPIOFUNC_WAKEEN_IOA17_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA17_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[16] - IOA16 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA16_EN_POS        (16)
#define GPIOFUNC_WAKEEN_IOA16_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA16_EN_POS)
#define GPIOFUNC_WAKEEN_IOA16_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA16_EN_POS)
#define GPIOFUNC_WAKEEN_IOA16_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA16_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[15] - IOA15 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA15_EN_POS        (15)
#define GPIOFUNC_WAKEEN_IOA15_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA15_EN_POS)
#define GPIOFUNC_WAKEEN_IOA15_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA15_EN_POS)
#define GPIOFUNC_WAKEEN_IOA15_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA15_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[14] - IOA14 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA14_EN_POS        (14)
#define GPIOFUNC_WAKEEN_IOA14_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA14_EN_POS)
#define GPIOFUNC_WAKEEN_IOA14_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA14_EN_POS)
#define GPIOFUNC_WAKEEN_IOA14_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA14_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[13] - IOA13 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA13_EN_POS        (13)
#define GPIOFUNC_WAKEEN_IOA13_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA13_EN_POS)
#define GPIOFUNC_WAKEEN_IOA13_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA13_EN_POS)
#define GPIOFUNC_WAKEEN_IOA13_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA13_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[12] - IOA12 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA12_EN_POS        (12)
#define GPIOFUNC_WAKEEN_IOA12_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA12_EN_POS)
#define GPIOFUNC_WAKEEN_IOA12_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA12_EN_POS)
#define GPIOFUNC_WAKEEN_IOA12_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA12_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[11] - IOA11 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA11_EN_POS        (11)
#define GPIOFUNC_WAKEEN_IOA11_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA11_EN_POS)
#define GPIOFUNC_WAKEEN_IOA11_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA11_EN_POS)
#define GPIOFUNC_WAKEEN_IOA11_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA11_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[10] - IOA10 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA10_EN_POS        (10)
#define GPIOFUNC_WAKEEN_IOA10_EN_MSK        (0x1UL << GPIOFUNC_WAKEEN_IOA10_EN_POS)
#define GPIOFUNC_WAKEEN_IOA10_ENABLE        (0x1UL << GPIOFUNC_WAKEEN_IOA10_EN_POS)
#define GPIOFUNC_WAKEEN_IOA10_DISABLE       (0x0UL << GPIOFUNC_WAKEEN_IOA10_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[9] - IOA9 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA9_EN_POS         (9)
#define GPIOFUNC_WAKEEN_IOA9_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA9_EN_POS)
#define GPIOFUNC_WAKEEN_IOA9_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA9_EN_POS)
#define GPIOFUNC_WAKEEN_IOA9_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA9_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[8] - IOA8 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA8_EN_POS         (8)
#define GPIOFUNC_WAKEEN_IOA8_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA8_EN_POS)
#define GPIOFUNC_WAKEEN_IOA8_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA8_EN_POS)
#define GPIOFUNC_WAKEEN_IOA8_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA8_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[7] - IOA7 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA7_EN_POS         (7)
#define GPIOFUNC_WAKEEN_IOA7_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA7_EN_POS)
#define GPIOFUNC_WAKEEN_IOA7_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA7_EN_POS)
#define GPIOFUNC_WAKEEN_IOA7_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA7_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[6] - IOA6 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA6_EN_POS         (6)
#define GPIOFUNC_WAKEEN_IOA6_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA6_EN_POS)
#define GPIOFUNC_WAKEEN_IOA6_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA6_EN_POS)
#define GPIOFUNC_WAKEEN_IOA6_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA6_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[5] - IOA5 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA5_EN_POS         (5)
#define GPIOFUNC_WAKEEN_IOA5_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA5_EN_POS)
#define GPIOFUNC_WAKEEN_IOA5_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA5_EN_POS)
#define GPIOFUNC_WAKEEN_IOA5_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA5_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[4] - IOA4 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA4_EN_POS         (4)
#define GPIOFUNC_WAKEEN_IOA4_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA4_EN_POS)
#define GPIOFUNC_WAKEEN_IOA4_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA4_EN_POS)
#define GPIOFUNC_WAKEEN_IOA4_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA4_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[3] - IOA3 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA3_EN_POS         (3)
#define GPIOFUNC_WAKEEN_IOA3_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA3_EN_POS)
#define GPIOFUNC_WAKEEN_IOA3_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA3_EN_POS)
#define GPIOFUNC_WAKEEN_IOA3_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA3_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[2] - IOA2 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA2_EN_POS         (2)
#define GPIOFUNC_WAKEEN_IOA2_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA2_EN_POS)
#define GPIOFUNC_WAKEEN_IOA2_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA2_EN_POS)
#define GPIOFUNC_WAKEEN_IOA2_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA2_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[1] - IOA1 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA1_EN_POS         (1)
#define GPIOFUNC_WAKEEN_IOA1_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA1_EN_POS)
#define GPIOFUNC_WAKEEN_IOA1_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA1_EN_POS)
#define GPIOFUNC_WAKEEN_IOA1_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA1_EN_POS)

/*
 * Bit definition for GPIOFUNC_WAKEEN[0] - IOA0 key change wakeup function enable
 */
#define GPIOFUNC_WAKEEN_IOA0_EN_POS         (0)
#define GPIOFUNC_WAKEEN_IOA0_EN_MSK         (0x1UL << GPIOFUNC_WAKEEN_IOA0_EN_POS)
#define GPIOFUNC_WAKEEN_IOA0_ENABLE         (0x1UL << GPIOFUNC_WAKEEN_IOA0_EN_POS)
#define GPIOFUNC_WAKEEN_IOA0_DISABLE        (0x0UL << GPIOFUNC_WAKEEN_IOA0_EN_POS)

/*
 * Bit definition for GPIOFUNC_STS[31] - GPIO key change interrupt flag
 */
#define GPIOFUNC_STS_INTF_POS             	(31)
#define GPIOFUNC_STS_INTF_MSK								(0x1UL << GPIOFUNC_STS_INTF_POS)
#define GPIOFUNC_STS_INTF_FLAG							(0x1UL << GPIOFUNC_STS_INTF_POS)


/*---------------------------------------------------------------------------------------
 * DMA Control Unit Memory Mapped Structure & Constant Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t INTSTS;                     // DMA Interrupt Status Register
} DMA_INT_TYPE_DEF;

typedef struct
{
	__IO uint32_t CTRL;                       // DMA Control Register
	__IO uint32_t DTN;                        // DMA Data Transfer Number Register
	__IO uint32_t SRCADR;                     // DMA Source Address Register
	__IO uint32_t DSTADR;                     // DMA Destination Address Register
} DMA_TYPE_DEF;

/*
 * Bit definition for DMAx_CTRL[25] - DMA Double Buffer Full Flag
 */
#define DMA_CTRL_DMA_FULL_FLAG_POS          (25)
#define DMA_CTRL_DMA_FULL_FLAG_MSK          (0x1UL << DMA_CTRL_DMA_FULL_FLAG_POS)
#define DMA_CTRL_DMA_FULL_FLAG              (0x1UL << DMA_CTRL_DMA_FULL_FLAG_POS)

/*
 * Bit definition for DMAx_CTRL[24] - DMA operation status
 */
#define DMA_CTRL_DMA_BUSY_POS               (24)
#define DMA_CTRL_DMA_BUSY_MSK               (0x1UL << DMA_CTRL_DMA_BUSY_POS)
#define DMA_CTRL_DMA_BUSY_FLAG              (0x1UL << DMA_CTRL_DMA_BUSY_POS)

/*
 * Bit definition for DMAx_CTRL[16] - DMA software start bit
 */
#define DMA_CTRL_DMA_STR_POS                (16)
#define DMA_CTRL_DMA_STR_MSK                (0x1UL << DMA_CTRL_DMA_STR_POS)
#define DMA_CTRL_DMA_START                  (0x1UL << DMA_CTRL_DMA_STR_POS)

/*
 * Bit definition for DMAx_CTRL[15:12] - DMA peripheral REQ selection
 */
#define DMA_CTRL_DMA_REQSEL_POS             (12)
#define DMA_CTRL_DMA_REQSEL_MSK             (0xFUL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_MEM             (0xBUL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_SPI1            (0x8UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_DSADC           (0x7UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_I2C             (0x6UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_I2S             (0x5UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_UART            (0x4UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_SPI0            (0x3UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_DAC_CH1         (0x2UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_DAC_CH0         (0x1UL << DMA_CTRL_DMA_REQSEL_POS)
#define DMA_CTRL_DMA_REQSEL_SARADC          (0x0UL << DMA_CTRL_DMA_REQSEL_POS)

/*
 * Bit definition for DMAx_CTRL[11:10] - Source data size
 */
#define DMA_CTRL_DMA_SRCSIZE_POS            (10)
#define DMA_CTRL_DMA_SRCSIZE_MSK            (0x3UL << DMA_CTRL_DMA_SRCSIZE_POS)
#define DMA_CTRL_DMA_SRCSIZE_RSV            (0x3UL << DMA_CTRL_DMA_SRCSIZE_POS)
#define DMA_CTRL_DMA_SRCSIZE_32B            (0x2UL << DMA_CTRL_DMA_SRCSIZE_POS)
#define DMA_CTRL_DMA_SRCSIZE_16B            (0x1UL << DMA_CTRL_DMA_SRCSIZE_POS)
#define DMA_CTRL_DMA_SRCSIZE_8B             (0x0UL << DMA_CTRL_DMA_SRCSIZE_POS)

/*
 * Bit definition for DMAx_CTRL[9:8] - Destination data size
 */
#define DMA_CTRL_DMA_DSTSIZE_POS            (8)
#define DMA_CTRL_DMA_DSTSIZE_MSK            (0x3UL << DMA_CTRL_DMA_DSTSIZE_POS)
#define DMA_CTRL_DMA_DSTSIZE_RSV            (0x3UL << DMA_CTRL_DMA_DSTSIZE_POS)
#define DMA_CTRL_DMA_DSTSIZE_32B            (0x2UL << DMA_CTRL_DMA_DSTSIZE_POS)
#define DMA_CTRL_DMA_DSTSIZE_16B            (0x1UL << DMA_CTRL_DMA_DSTSIZE_POS)
#define DMA_CTRL_DMA_DSTSIZE_8B             (0x0UL << DMA_CTRL_DMA_DSTSIZE_POS)

/*
 * Bit definition for DMAx_CTRL[6] - DMA burst transfer mode enable
 */
#define DMA_CTRL_DMA_BURST_EN_POS           (6)
#define DMA_CTRL_DMA_BURST_EN_MSK           (0x1UL << DMA_CTRL_DMA_BURST_EN_POS)
#define DMA_CTRL_DMA_BURST_ENABLE           (0x1UL << DMA_CTRL_DMA_BURST_EN_POS)
#define DMA_CTRL_DMA_BURST_DISABLE          (0x0UL << DMA_CTRL_DMA_BURST_EN_POS)

/*
 * Bit definition for DMAx_CTRL[5] - DMA source address increment mode enable
 */
#define DMA_CTRL_DMA_SRCINC_EN_POS          (5)
#define DMA_CTRL_DMA_SRCINC_EN_MSK          (0x1UL << DMA_CTRL_DMA_SRCINC_EN_POS)
#define DMA_CTRL_DMA_SRCINC_ENABLE          (0x1UL << DMA_CTRL_DMA_SRCINC_EN_POS)
#define DMA_CTRL_DMA_SRCINC_DISABLE         (0x0UL << DMA_CTRL_DMA_SRCINC_EN_POS)

/*
 * Bit definition for DMAx_CTRL[4] - DMA destination address increment mode enable
 */
#define DMA_CTRL_DMA_DSTINC_EN_POS          (4)
#define DMA_CTRL_DMA_DSTINC_EN_MSK          (0x1UL << DMA_CTRL_DMA_DSTINC_EN_POS)
#define DMA_CTRL_DMA_DSTINC_ENABLE          (0x1UL << DMA_CTRL_DMA_DSTINC_EN_POS)
#define DMA_CTRL_DMA_DSTINC_DISABLE         (0x0UL << DMA_CTRL_DMA_DSTINC_EN_POS)

/*
 * Bit definition for DMA_CTRL[3] - DMA circular mode enable
 */
#define DMA_CTRL_DMA_CIRC_EN_POS            (3)
#define DMA_CTRL_DMA_CIRC_EN_MSK            (0x1UL << DMA_CTRL_DMA_CIRC_EN_POS)
#define DMA_CTRL_DMA_CIRC_ENABLE            (0x1UL << DMA_CTRL_DMA_CIRC_EN_POS)
#define DMA_CTRL_DMA_CIRC_DISABLE           (0x0UL << DMA_CTRL_DMA_CIRC_EN_POS)

/*
 * Bit definition for DMA_CTRL[2] - DMA transaction error interrupt enable
 */
#define DMA_CTRL_DMA_ERR_INT_EN_POS         (2)
#define DMA_CTRL_DMA_ERR_INT_EN_MSK         (0x1UL << DMA_CTRL_DMA_ERR_INT_EN_POS)
#define DMA_CTRL_DMA_ERR_INT_ENABLE         (0x1UL << DMA_CTRL_DMA_ERR_INT_EN_POS)
#define DMA_CTRL_DMA_ERR_INT_DISABLE        (0x0UL << DMA_CTRL_DMA_ERR_INT_EN_POS)

/*
 * Bit definition for DMA_CTRL[1] - DMA transaction complete interrupt enable
 */
#define DMA_CTRL_DMA_DONE_INT_EN_POS        (1)
#define DMA_CTRL_DMA_DONE_INT_EN_MSK        (0x1UL << DMA_CTRL_DMA_DONE_INT_EN_POS)
#define DMA_CTRL_DMA_DONE_INT_ENABLE        (0x1UL << DMA_CTRL_DMA_DONE_INT_EN_POS)
#define DMA_CTRL_DMA_DONE_INT_DISABLE       (0x0UL << DMA_CTRL_DMA_DONE_INT_EN_POS)

/*
 * Bit definition for DMA_CTRL[0] - DMA channel enable
 */
#define DMA_CTRL_DMA_EN_POS                 (0)
#define DMA_CTRL_DMA_EN_MSK                 (0x1UL << DMA_CTRL_DMA_EN_POS)
#define DMA_CTRL_DMA_ENABLE                 (0x1UL << DMA_CTRL_DMA_EN_POS)
#define DMA_CTRL_DMA_DISABLE                (0x0UL << DMA_CTRL_DMA_EN_POS)

/*
 * Bit definition for DMA_INTSTS[10] - DMA channel 2 transfer error flag
 */
#define DMA_INTSTS_DMA2_TX_ERR_INTF_POS     (10)
#define DMA_INTSTS_DMA2_TX_ERR_INTF_MSK     (0x1UL << DMA_INTSTS_DMA2_TX_ERR_INTF_POS)
#define DMA_INTSTS_DMA2_TX_ERR_INT_FLAG     (0x1UL << DMA_INTSTS_DMA2_TX_ERR_INTF_POS)

/*
 * Bit definition for DMA_INTSTS[9] - DMA channel 1 transfer error flag
 */
#define DMA_INTSTS_DMA1_TX_ERR_INTF_POS     (9)
#define DMA_INTSTS_DMA1_TX_ERR_INTF_MSK     (0x1UL << DMA_INTSTS_DMA1_TX_ERR_INTF_POS)
#define DMA_INTSTS_DMA1_TX_ERR_INT_FLAG     (0x1UL << DMA_INTSTS_DMA1_TX_ERR_INTF_POS)

/*
 * Bit definition for DMA_INTSTS[8] - DMA channel 0 transfer error flag
 */
#define DMA_INTSTS_DMA0_TX_ERR_INTF_POS     (8)
#define DMA_INTSTS_DMA0_TX_ERR_INTF_MSK     (0x1UL << DMA_INTSTS_DMA0_TX_ERR_INTF_POS)
#define DMA_INTSTS_DMA0_TX_ERR_INT_FLAG     (0x1UL << DMA_INTSTS_DMA0_TX_ERR_INTF_POS)

/*
 * Bit definition for DMA_INTSTS[2] - DMA channel 2 transaction complete interrupt flag
 */
#define DMA_INTSTS_DMA2_DONE_INTF_POS       (2)
#define DMA_INTSTS_DMA2_DONE_INTF_MSK       (0x1UL << DMA_INTSTS_DMA2_DONE_INTF_POS)
#define DMA_INTSTS_DMA2_DONE_INT_FLAG       (0x1UL << DMA_INTSTS_DMA2_DONE_INTF_POS)

/*
 * Bit definition for DMA_INTSTS[1] - DMA channel 1 transaction complete interrupt flag
 */
#define DMA_INTSTS_DMA1_DONE_INTF_POS       (1)
#define DMA_INTSTS_DMA1_DONE_INTF_MSK       (0x1UL << DMA_INTSTS_DMA1_DONE_INTF_POS)
#define DMA_INTSTS_DMA1_DONE_INT_FLAG       (0x1UL << DMA_INTSTS_DMA1_DONE_INTF_POS)

/*
 * Bit definition for DMA_INTSTS[0] - DMA channel 0 transaction complete interrupt flag
 */
#define DMA_INTSTS_DMA0_DONE_INTF_POS       (0)
#define DMA_INTSTS_DMA0_DONE_INTF_MSK       (0x1UL << DMA_INTSTS_DMA0_DONE_INTF_POS)
#define DMA_INTSTS_DMA0_DONE_INT_FLAG       (0x1UL << DMA_INTSTS_DMA0_DONE_INTF_POS)


/*---------------------------------------------------------------------------------------
 * Peripheral memory map
 *---------------------------------------------------------------------------------------*/
#define SPI0_BASE                 					(0x40090000)
#define SPI1_BASE                 					(0x40091000)
#define UART_BASE                           (0x400A0000)
#define I2C_BASE                            (0x400B0000)
#define I2S_BASE                            (0x400C0000)
#define WDG_BASE                            (0x400D0000)
#define CTS_BASE                            (0x400E0000)
#define TIMEBASE_BASE                       (0x400E0060)
#define	SAR_ADC_BASE                        (0x40120000)
#define	DS_ADC_BASE                         (0x40121000)
#define	DAC_BASE                            (0x40130000)
#define	PWMIO_BASE													(0x40160000)
#define	QD_BASE                             (0x40160040)
#define SMU_BASE                            (0x50000000)
#define CLOCK_BASE                          (0x50001000)
#define RCU_BASE                            (0x50003000)
#define ITU_BASE	     					            (0x50004000)
#define ACU_BASE	     					            (0x50005000)
#define NVM_BASE                            (0x50010000)
#define FLASH_BASE													(0x50010000)
#define	MAC_BASE                            (0x50030000)
#define CCP0_BASE                           (0x50040000)
#define CCP1_BASE                           (0x50041000)
#define TM0_BASE                            (0x50050000)
#define TM1_BASE                            (0x50050010)
#define TM2_BASE                            (0x50050020)
#define TM_INT_BASE                         (0x50050030)
#define SPIFC_BASE                          (0x50060000)
#define GPIOA_BASE                          (0x50070000)
#define GPIOA_BIT_OPERATION_BASE            (0x50070020)
#define GPIOB_BASE                          (0x50070100)
#define GPIOB_BIT_OPERATION_BASE            (0x50070120)
#define GPIOFUNC_BASE                       (0x50070200)
#define DMA_INT_BASE                        (0x500F0000)
#define DMA0_BASE                           (0x500F0010)
#define DMA1_BASE                           (0x500F0020)
#define DMA2_BASE                           (0x500F0030)


/*---------------------------------------------------------------------------------------
 * Peripheral declaration
 *---------------------------------------------------------------------------------------*/
#define SPI0               									((SPI_TYPE_DEF *) SPI0_BASE)
#define SPI1               									((SPI_TYPE_DEF *) SPI1_BASE)
#define UART                                ((UART_TYPE_DEF *) UART_BASE)
#define I2C                                 ((I2C_TYPE_DEF *) I2C_BASE)
#define I2S                                 ((I2S_TYPE_DEF *) I2S_BASE)
#define WDG                                 ((WDG_TYPE_DEF *) WDG_BASE)
#define CTS                                 ((CTS_TYPE_DEF *) CTS_BASE)
#define TIMEBASE                            ((TIMEBASE_TYPE_DEF *) TIMEBASE_BASE)
#define SAR_ADC                             ((SAR_ADC_TYPE_DEF *) SAR_ADC_BASE)
#define DS_ADC                              ((DS_ADC_TYPE_DEF *) DS_ADC_BASE)
#define DAC                                 ((DAC_TYPE_DEF *) DAC_BASE)
#define PWMIO                               ((PWMIO_TYPE_DEF *) PWMIO_BASE)
#define QD																	((QD_TYPE_DEF *) QD_BASE)
#define SMU                                 ((SMU_TYPE_DEF *) SMU_BASE)
#define CLOCK                               ((CLOCK_TYPE_DEF *) CLOCK_BASE)
#define RCU                                 ((RCU_TYPE_DEF *) RCU_BASE)
#define ITU                                 ((ITU_TypeDef *) ITU_BASE)
#define ACU                                 ((ACU_TYPE_DEF *) ACU_BASE)
#define FLASH                               ((FLASH_TYPE_DEF *) FLASH_BASE)
#define MAC                                 ((MAC_TYPE_DEF *) MAC_BASE)
#define CCP0                                ((CCP_TYPE_DEF *) CCP0_BASE)
#define CCP1                                ((CCP_TYPE_DEF *) CCP1_BASE)
#define TM0                                 ((TIMER_TYPE_DEF *) TM0_BASE)
#define TM1                                 ((TIMER_TYPE_DEF *) TM1_BASE)
#define TM2                                 ((TIMER_TYPE_DEF *) TM2_BASE)
#define TM_INT                              ((TIMER_INT_TYPE_DEF *) TM_INT_BASE)
#define SPIFC                              	((SPIFC_TYPE_DEF *) SPIFC_BASE)
#define GPIOA                               ((GPIO_TYPE_DEF *) GPIOA_BASE)
#define GPIOA_OBIT                          ((GPIO_BIT_OPERATION_TYPE_DEF *) GPIOA_BIT_OPERATION_BASE)
#define GPIOB                               ((GPIO_TYPE_DEF *) GPIOB_BASE)
#define GPIOB_OBIT                          ((GPIO_BIT_OPERATION_TYPE_DEF *) GPIOB_BIT_OPERATION_BASE)
#define IOFUNC                              ((GPIOFUNC_TYPE_DEF *) GPIOFUNC_BASE)
#define DMA_INT                             ((DMA_INT_TYPE_DEF *) DMA_INT_BASE)
#define DMA0                                ((DMA_TYPE_DEF *) DMA0_BASE)
#define DMA1                                ((DMA_TYPE_DEF *) DMA1_BASE)
#define DMA2                                ((DMA_TYPE_DEF *) DMA2_BASE)


/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#if defined(__CC_ARM)
#include "RTE_Components.h"
#endif

#include "DAC_GPCM1Fx.h"
#include "DMA_GPCM1Fx.h"
#include "DSADC_GPCM1Fx.h"
#include "eFlash_GPCM1Fx.h"
#include "GPIO_GPCM1Fx.h"
#include "I2C_GPCM1Fx.h"
#include "MAC_GPCM1Fx.h"
#include "SARADC_GPCM1Fx.h"
#include "SPI_FLASH_GPCM1Fx.h"
#include "SPIFC_GPCM1Fx.h"
#include "SYS_GPCM1Fx.h"
#include "system_GPCM1Fx.h"
#include "TimeBase_GPCM1Fx.h"
#include "Timer_GPCM1Fx.h"
#include "Uart_GPCM1Fx.h"
#include "WDT_GPCM1Fx.h"


/*---------------------------------------------------------------------------------------
 * Macro
 *---------------------------------------------------------------------------------------*/
#define SET_BIT(REG, BIT)										((REG) |= (BIT))
#define WRITE_REG(REG, VAL)									((REG) = (VAL))

#define READ_BIT(REG, BIT)									((REG) & (BIT))
#define READ_REG(REG)												((REG))

#define CLEAR_BIT(REG, BIT)									((REG) &= ~(BIT))
#define CLEAR_FLAG(REG, MASKBIT, CLEARBIT)	((REG) &= ((MASKBIT) | (CLEARBIT)))
#define CLEAR_REG(REG)											((REG) = (0x00000000))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)	WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define SHIFT_L(CONTENT, BIT)								((CONTENT) << (BIT))
#define SHIFT_R(CONTENT, BIT)								((CONTENT) >> (BIT))

#define XOR_BIT(REG, BIT)										((REG) ^= (BIT))


/*---------------------------------------------------------------------------------------
 * Constant Definition
 *---------------------------------------------------------------------------------------*/
/*
 * Bit Mask Definitions
 */
#define BIT0                                (0x00000001)
#define BIT1                                (0x00000002)
#define BIT2                                (0x00000004)
#define BIT3                                (0x00000008)
#define BIT4                                (0x00000010)
#define BIT5                                (0x00000020)
#define BIT6                                (0x00000040)
#define BIT7                                (0x00000080)
#define BIT8                                (0x00000100)
#define BIT9                                (0x00000200)
#define BIT10                               (0x00000400)
#define BIT11                               (0x00000800)
#define BIT12                               (0x00001000)
#define BIT13                               (0x00002000)
#define BIT14                               (0x00004000)
#define BIT15                               (0x00008000)
#define BIT16                               (0x00010000)
#define BIT17                               (0x00020000)
#define BIT18                               (0x00040000)
#define BIT19                               (0x00080000)
#define BIT20                               (0x00100000)
#define BIT21                               (0x00200000)
#define BIT22                               (0x00400000)
#define BIT23                               (0x00800000)
#define BIT24                               (0x01000000)
#define BIT25                               (0x02000000)
#define BIT26                               (0x04000000)
#define BIT27                               (0x08000000)
#define BIT28                               (0x10000000)
#define BIT29                               (0x20000000)
#define BIT30                               (0x40000000)
#define BIT31                               (0x80000000)

/*
 * Byte Mask Definitions
 */
#define BYTE0_MSK                           (0x000000FF)
#define BYTE1_MSK                           (0x0000FF00)
#define BYTE2_MSK                           (0x00FF0000)
#define BYTE3_MSK                           (0xFF000000)

#define TRUE                                (1)
#define FALSE                               (0)

#define ENABLE                              (1)
#define DISABLE                             (0)


#endif
