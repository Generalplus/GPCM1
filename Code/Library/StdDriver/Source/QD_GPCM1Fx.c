/**************************************************************************************************
 * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File: QD_GPCM1Fx.c
 *
 * @Version: v0.9
 *
 * @Date: 2022.10.17
 *
 * @Abstract:
 * 		IOA[18]		QD0_A(I)
 * 		IOA[19]		QD0_B(I)
 *
 * 		IOA[20]		QD1_A(I)
 * 		IOA[21]		QD1_B(I)
 **************************************************************************************************/

/*---------------------------------------------------------------------------------------
 * Header File Included Area
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"

/*
extern int counter;
extern uint8_t counter_forward;
extern uint8_t counter_backward;
*/

/*---------------------------------------------------------------------------------------
 * Subroutine Area
 *---------------------------------------------------------------------------------------*/

/*
 * @brief
 *				Initial QD module
 * @param
 * 				None
 * @return
 * 				None
 */
void QD_Open(uint8_t QDSel, uint8_t INT_Mode)
{

	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_QD_CLK_ENABLE);
	QD->CTRL = 0;
	if( QDSel == 0)   // QD0 initial
	{
		QD->CTRL |= QD_CTRL_QD0_ENABLE | QD_CTRL_QD0_POS_ENABLE | QD_CTRL_QD0_REV_ENABLE;
		if(INT_Mode == 0)
		{
      QD->CTRL |= QD_CTRL_QD0_ALL_MODE;
		}
		else
		{
      QD->CTRL |= QD_CTRL_QD0_OVERFLOW_MODE;
		}
	}

	else            // QD1 initial
	{
		QD->CTRL |= QD_CTRL_QD1_ENABLE | QD_CTRL_QD1_POS_ENABLE | QD_CTRL_QD1_REV_ENABLE;

		if(INT_Mode == 0)
		{
      QD->CTRL |= QD_CTRL_QD1_ALL_MODE;
		}
		else
		{
      QD->CTRL |= QD_CTRL_QD1_OVERFLOW_MODE;
		}
	}

	QD->CTRL |= QD_CTRL_DEBOUNCE_SEL_80T;

    QD->FW_TH = 0x0001;
    QD->BW_TH = 0xFFFF;

	// QD->FW_TH = 0x0003;
	// QD->BW_TH = 0xFFFD;

//	QD->CTRL |= QD_CTRL_OVERFLOW_MODE2_ENABLE;

	if( QDSel == 0)
	{
		QD->QD0_CLR = 0;
	}
	else
	{
		QD->QD1_CLR = 0;
	}

	NVIC_EnableIRQ(QD_IRQn);
}


/*
 * @brief
 *				QD close
 * @param
 * 				None
 * @return
 * 				None
 */
void QD_Close(uint8_t QDSel)
{
	if( QDSel == 0)   // QD0 initial
	{
    CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_ENABLE);
	}
	else
	{
    CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_ENABLE);
	}
}


#if 0
/**
 * @brief
 *
 * @param
 *          None.
 * @return
 *          None.
 */
void QdTest(void)
{
	uint32_t ScanedKey;

	QD_Open();
	while(1)
	{
		SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_QD_CLK_ENABLE);	                                       	//	Enable QD Clock
		MODIFY_REG(CCP0->TMR_PLOAD, 0x0000FFFF, 0x00008000);                       // CCP Timer Clock: HCLK

	  switch(ScanedKey)
		{
      case 0x01:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_ENABLE);	               								// QD0 Disable QD0
				break;
      case 0x02:
				SET_BIT(QD->CTRL, QD_CTRL_QD0_ENABLE);	                 								// QD0 Enable QD0
			  break;
      case 0x03:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_FlowMode);	           									// QD0 Enable All Interrupt Mode
			  break;
      case 0x04:
				SET_BIT(QD->CTRL, QD_CTRL_QD0_FlowMode);	           										// QD0 Enable Overflow Mode
				break;

      case 0x11:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_POS_ENABLE);	           								// QD0 Disable Positive Interrupt
			  break;
      case 0x12:
				SET_BIT(QD->CTRL,   QD_CTRL_QD0_POS_ENABLE);	           								// QD0 Enable Positive Interrupt
			  break;
      case 0x13:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_REV_ENABLE);	           								// QD0 Disable Reverse Interrupt
			  break;
      case 0x14:
				SET_BIT(QD->CTRL,   QD_CTRL_QD0_REV_ENABLE);	           								// QD0 Enable Reverse Interrupt
			  break;


      case 0x21:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_ENABLE);	               								// QD1 Disable
				break;
      case 0x22:
				SET_BIT(QD->CTRL, QD_CTRL_QD1_ENABLE);	                 								// QD1 Enable
			  break;
      case 0x23:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_FlowMode);	           									// QD1 Enable All Interrupt Mode
			  break;
      case 0x24:
				SET_BIT(QD->CTRL, QD_CTRL_QD1_FlowMode);	           										// QD1 Enable Overflow Mode
			  break;

      case 0x31:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_POS_ENABLE);	           								// QD1 Disable Positive Interrupt
			  break;
      case 0x32:
				SET_BIT(QD->CTRL,   QD_CTRL_QD1_POS_ENABLE);	           								// QD1 Enable Positive Interrupt
			  break;
      case 0x33:
				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_REV_ENABLE);	           								// QD1 Disable Reverse Interrupt
			  break;
      case 0x34:
				SET_BIT(QD->CTRL,   QD_CTRL_QD1_REV_ENABLE);	           								// QD1 Enable Reverse Interrupt
			  break;

      case 0x41:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_0T);	           								// QD Debounce 0T
			  break;
      case 0x42:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_4T);	           								// QD Debounce 4T
			  break;
			case 0x43:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_8T);	           								// QD Debounce 8T
			  break;
      case 0x44:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_16T);	           							// QD Debounce 16T
			  break;
      case 0x45:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_32T);	           							// QD Debounce 32T
			  break;
      case 0x46:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_40T);	           							// QD Debounce 40T
			  break;
      case 0x47:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_80T);	           							// QD Debounce 80T
			  break;
      case 0x48:
				CLEAR_BIT(QD->CTRL, QD_CTRL_DEBOUNCE_SEL_MSK);
				SET_BIT(QD->CTRL,   QD_CTRL_DEBOUNCE_SEL_128T);	           							// QD Debounce 128T
			  break;

      case 0x50:
				QD->FW_THR = 0x0007;
				QD->BW_THR = 0xFFF9;
				QD->CTRL &= ~QD_CTRL_OVERFLOW_MODE2_ENABLE;

				printf("\r\n");
				ttt = QD->FW_THR;
				printf("QD0 Mode1 FW threshold:%x\r\n", ttt);
				ttt = QD->BW_THR;
				printf("QD1 Mode1 BW threshold:%x\r\n", ttt);
			  break;

      case 0x51:
				QD->FW_THR = 0x0007;
				QD->BW_THR = 0xFFF9;
				QD->CTRL |= QD_CTRL_OVERFLOW_MODE2_ENABLE;

				printf("\r\n");
				ttt = QD->FW_THR;
				printf("QD0 Mode2 FW threshold:%x\r\n", ttt);
				ttt = QD->BW_THR;
				printf("QD1 Mode2 BW threshold:%x\r\n", ttt);
			  break;

      case 0x60:
				DisplayFlag = 1;
				QD->FW_THR = 0xFFFF;
				QD->BW_THR = 0x0000;
//				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_POS_ENABLE);	           								// QD0 Disable Positive Interrupt
//				CLEAR_BIT(QD->CTRL, QD_CTRL_QD0_REV_ENABLE);	           								// QD0 Disable Reverse Interrupt
//				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_POS_ENABLE);	           								// QD0 Disable Positive Interrupt
//				CLEAR_BIT(QD->CTRL, QD_CTRL_QD1_REV_ENABLE);	           								// QD0 Disable Reverse Interrupt
			  break;

			case 0x70:
					SCB->SCR = (1UL << 0); // Non Deep Sleep Mode
					__WFI();
				break;

			default:
				break;
		}
	}
}
#endif


/**
 * @brief
 *
 * @param
 *          None.
 * @return
 *          None.
 */
void QD_IRQHandler(void)
{
	if(QD->STS & QD_CTRL_QD0_REV_INT_FLAG)
	{
		QD->STS = QD_CTRL_QD0_REV_INT_FLAG;
	}

	if(QD->STS & QD_CTRL_QD0_POS_INT_FLAG)
	{
		QD->STS = QD_CTRL_QD0_POS_INT_FLAG;
	}

	if(QD->STS & QD_CTRL_QD1_POS_INT_FLAG)
	{
    QD->STS = QD_CTRL_QD1_POS_INT_FLAG;
	}

	if(QD->STS & QD_CTRL_QD1_REV_INT_FLAG)
	{
    QD->STS = QD_CTRL_QD1_REV_INT_FLAG;
	}

	QD->QD0_CLR = 0;
	QD->QD1_CLR = 0;

}



