/**************************************************************************************************
 * Copyright(c) 2018 GENERALPLUS Technology Corporation. All rights reserved.
 *-------------------------------------------------------------------------------------------------
 * @File:
 *
 * @Version:
 *
 * @Date:
 *
 * @Abstract:
 *
 **************************************************************************************************/

/*---------------------------------------------------------------------------------------
 * Device Header
 *---------------------------------------------------------------------------------------*/
#include "GPCM1Fx.h"
#include "Touch_User.h"
#include "SACM_A1801_User.h"
/*---------------------------------------------------------------------------------------
 * Constant Definition Area
 *---------------------------------------------------------------------------------------*/
#define C_IOA0								0
#define C_IOA1								1
#define C_IOA2								2
#define C_IOA3								3
#define C_IOA4								4
#define C_IOA5								5
#define C_IOA6								6
#define C_IOA7								7
#define C_IOA8								8
#define C_IOA9								9
//
// Touch sensor parameter. Be defined by user. ++
//
#define C_CalDefault					40
#define	C_PadNumber						8							// Max. = 10
#define	C_WakeUpPadNumber			2							// Max. = 10
#define	C_ScanNo							50						//50
#define	C_NumOfScans					1
#define	C_UpStep							10					//20
#define	C_DnStep							10					//40
#define	C_AbnorDetCntEn				1							//0:Disable, 1:Enable
#define	C_AbnorDetCnt					100					//40
#define	C_FilterMode					0							//0:IIR 1:Slew rate filter 2:L-Point avarge 3:Median
#define	C_LPointBuf						8							//LPoint Buffer length
#define	C_MedianBuf						4							//Median Buffer length
#define	C_SlewMaxStep					0x30					//Slew rate Maxstep

#define C_SchmittH1           200
#define C_SchmittL1           100
#define C_SchmittH2           140
#define C_SchmittL2           70

#define C_ScanNumforCtsTimer	(65536-C_ScanNo)
#define C_CTS_ChargeCurrent 	CTS_CTRL_CHARGE_CURRENT_50uA		//25 50

#define CTS_TMBDATA				  	0x8000				// measure time
#define	C_TouchProbe					0							//01:ON , 0:OFF

#define	C_TouchPad1						C_IOA0
#define	C_TouchPad2						C_IOA1
#define	C_TouchPad3						C_IOA2
#define	C_TouchPad4						C_IOA3
#define	C_TouchPad5						C_IOA4
#define	C_TouchPad6						C_IOA5
#define	C_TouchPad7						C_IOA6
#define	C_TouchPad8						C_IOA7
#define	C_TouchPad9						C_IOA8
#define	C_TouchPad10					C_IOA9
//***************************************************************************************
// Table Definition Area (be used by Touch Library)
//***************************************************************************************
const uint16_t T_TouchInfo[12] =
{
	C_PadNumber,
	C_ScanNo,
	C_UpStep,
	C_DnStep,
	C_AbnorDetCnt,
	C_NumOfScans,
	C_AbnorDetCntEn,
	C_CalDefault,
	C_FilterMode,
	C_LPointBuf,
	C_MedianBuf,
	C_SlewMaxStep
};

//***************************************************************************************
// RAM Definition Area
//***************************************************************************************
uint16_t mTouch_Sum[C_PadNumber];
uint16_t mTouch_Reference[C_PadNumber];
uint32_t mTouch_ReferenceL[C_PadNumber];
uint16_t mTouch_ScanNo[C_PadNumber];
uint16_t mTouch_Schmitt_H[C_PadNumber];
uint16_t mTouch_Schmitt_L[C_PadNumber];

uint16_t mTouch_ReferenceDAC[C_PadNumber];
uint16_t mTouch_SchmittHighIndex;
uint16_t mTouch_SchmittLowIndex;
uint16_t mTouch_ScanNoIndex;


uint16_t mTouch_LPointBuf[C_PadNumber*C_LPointBuf];
uint16_t mTouch_MedianBuf[C_PadNumber*C_MedianBuf];

uint16_t	CTS_PauseFlag;

uint16_t	CTS_TMAcnt;
uint16_t	CTS_TMBcnt;
uint16_t	CTS_TMBcnt1;
uint16_t	CTS_TMBcnt2;
const uint16_t T_ScanNo_1[10] =
{
//		Pad1			Pad2			Pad3		 Pad4		 	Pad5		Pad6		Pad7			Pad8			Pad9			Pad10
		C_ScanNo, C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo, C_ScanNo, C_ScanNo
};

const uint16_t T_ScanNo_2[10] =
{
//		Pad1			Pad2			Pad3		 Pad4		 	Pad5		Pad6		Pad7			Pad8			Pad9			Pad10
		C_ScanNo, C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo,C_ScanNo, C_ScanNo, C_ScanNo
};

const uint16_t T_SchmittH_1[10] =
{
//	Pad1				Pad2					Pad3				Pad4		 		Pad5				Pad6				Pad7				Pad8				Pad9				 Pad10
		C_SchmittH1, C_SchmittH1,C_SchmittH1,C_SchmittH1,C_SchmittH1,C_SchmittH1,C_SchmittH1,C_SchmittH1, C_SchmittH1, C_SchmittH1
};

const uint16_t T_SchmittH_2[10] =
{
//	Pad1				Pad2					Pad3				Pad4		 		Pad5				Pad6				Pad7				Pad8				Pad9					Pad10
    C_SchmittH2, C_SchmittH2,C_SchmittH2,C_SchmittH2,C_SchmittH2,C_SchmittH2,C_SchmittH2,C_SchmittH2, C_SchmittH2, C_SchmittH2
};

const uint16_t T_SchmittL_1[10] =
{
//	Pad1				Pad2					Pad3				Pad4		 		Pad5				Pad6				Pad7				Pad8				Pad9					Pad10
    C_SchmittL1, C_SchmittL1,C_SchmittL1,C_SchmittL1,C_SchmittL1,C_SchmittL1,C_SchmittL1,C_SchmittL1, C_SchmittL1, C_SchmittL1
};

const uint16_t T_SchmittL_2[10] =
{
//	Pad1				Pad2					Pad3				Pad4		 		Pad5				Pad6				Pad7				Pad8				Pad9					Pad10
    C_SchmittL2, C_SchmittL2,C_SchmittL2,C_SchmittL2,C_SchmittL2,C_SchmittL2,C_SchmittL2,C_SchmittL2, C_SchmittL2, C_SchmittL2
};

const uint16_t* T_SchmittH[2] =
{
	&T_SchmittH_1[0],
	&T_SchmittH_2[0]
};

const uint16_t* T_SchmittL[2] =
{
	&T_SchmittL_1[0],
	&T_SchmittL_2[0]
};
const uint16_t* T_ScanNo[2] =
{
	&T_ScanNo_1[0],
	&T_ScanNo_2[0]
};

const uint16_t T_TouchPad[10] =
{
//	Pad1				Pad2					Pad3				Pad4		 		Pad5				Pad6				Pad7				Pad8				Pad9					Pad10
    C_TouchPad1, C_TouchPad2,C_TouchPad3,C_TouchPad4,C_TouchPad5,C_TouchPad6,C_TouchPad7,C_TouchPad8, C_TouchPad9, C_TouchPad10
};
const uint32_t T_CTS_Interface[10] =
{
    CTS_PADSEL_IO0_ENABLE, CTS_PADSEL_IO1_ENABLE,  CTS_PADSEL_IO2_ENABLE,  CTS_PADSEL_IO3_ENABLE, CTS_PADSEL_IO4_ENABLE,
		CTS_PADSEL_IO5_ENABLE, CTS_PADSEL_IO6_ENABLE,  CTS_PADSEL_IO7_ENABLE,  CTS_PADSEL_IO8_ENABLE, CTS_PADSEL_IO9_ENABLE
};

const volatile uint32_t* T_CTS_TMBPload[10] =
{
    &(CTS->TMB0PLOAD),&(CTS->TMB1PLOAD), &(CTS->TMB2PLOAD), &(CTS->TMB3PLOAD), &(CTS->TMB4PLOAD), &(CTS->TMB5PLOAD),
		&(CTS->TMB6PLOAD), &(CTS->TMB7PLOAD), &(CTS->TMB8PLOAD), &(CTS->TMB9PLOAD),
};
//***************************************************************************************
// CODE Definition Area
//***************************************************************************************
/*
 * @brief
 *         	Hardware initilazation for Touch, called by library
 * @param
 *          None.
 * @return
 *          None.
 */
void F_Touch_User_Init(void)
{
		mTouch_SchmittHighIndex = 0;
		mTouch_SchmittLowIndex = 0;
		mTouch_ScanNoIndex = 0;
		CTS_PauseFlag = 0;

	SET_BIT(CLOCK->APBCKEN, CLOCK_APBCKEN_CTS_TB_CLK_ENABLE);
	MODIFY_REG(CLOCK->AHBCKSEL, CLOCK_AHBCKSEL_SYS32K_SEL_MSK, CLOCK_AHBCKSEL_SYS32K_SEL_IOSC32K);	//Kim add 2019.07.03
//	CTS->PADSEL = T_CTS_Interface[0];					//Select CTS Pin
  CTS->PADSEL = T_CTS_Interface[T_TouchPad[0]];					//Select CTS Pin
	CTS->CTRL =   CTS_CTRL_CTSEN_ENABLE | CTS_CTRL_AUTOSTOP_ENABLE | C_CTS_ChargeCurrent | \
								CTS_CTRL_TMA_INTEN_SEL_ENABLE | CTS_CTRL_TMB_INTEN_SEL_ENABLE | \
								CTS_CTRL_TMA_MODE_CTSTMR | CTS_CTRL_TMB_MODE_CTSTMR | \
								CTS_CTRL_TMA_CLK_SEL_CTSMODULE | CTS_CTRL_TMB_CLK_SEL_IOSC16M | \
								CTS_CTRL_START_ENABLE;

	CTS->TMB0PLOAD = CTS_TMBDATA;
	CTS->TMBCOUNT = CTS_TMBDATA;
	CTS->TMAPLOAD = C_ScanNo;
	CTS->TMACOUNT = C_ScanNo;

	NVIC_EnableIRQ(CTS_TM0_IRQn);               // Enable CTS_TMA INT
	NVIC_EnableIRQ(CTS_TM1_IRQn);               // Enable CTS_TMB INT

}

/*
 * @brief
 *         	called by library to start CTS
 * @param
 *          None.
 * @return
 *          None.
 */
void CTS_Start(void)
{
	if(CTS_PauseFlag != 0x8000)
	{
	CTS->CTRL &= ~CTS_CTRL_START_ENABLE;
	CTS->CTRL |= CTS_CTRL_START_ENABLE;
	}
}
/*
 * @brief
 *         	Get ScanNo for TouchSensor
 * @param
 *         [IN]: PadIndex
 *         [IN]: GroupIndex
 * @return
*          ScanNo
 */
uint16_t Get_ScanNo(uint32_t PadIndex, uint32_t GroupIndex)
{
  uint16_t ScanNo;
	const uint16_t* ScanNoPtr;

	ScanNoPtr = T_ScanNo[GroupIndex];
	ScanNo = ScanNoPtr[PadIndex];
	mTouch_ScanNo[PadIndex] = ScanNo;

	return ScanNo;
}

/*
 * @brief
 *         	called by library to switch CTS channel
 * @param
 *          R1: CTS channel
 * @return
 *          None.
 */
void CTS_CH_Sel(uint16_t CTS_Ch)
{
	CTS->PADSEL = T_CTS_Interface[T_TouchPad[CTS_Ch]];					//Select CTS Pin
	CTS->TMAPLOAD = Get_ScanNo(CTS_Ch,mTouch_ScanNoIndex);
	CTS->TMACOUNT = Get_ScanNo(CTS_Ch,mTouch_ScanNoIndex);

}
/*
 * @brief
 *         	Get OFFThreshold for TouchSensor
 * @param
 *         [IN]: PadIndex
 *         [IN]: GroupIndex
 * @return
*          Schmitt Low
 */
uint16_t Get_SchmittL(uint32_t PadIndex, uint32_t GroupIndex)
{
	uint16_t SchmittLow;
	const uint16_t* SchmittLPtr;

	SchmittLPtr = T_SchmittL[GroupIndex];
	SchmittLow = SchmittLPtr[PadIndex];
	mTouch_Schmitt_L[PadIndex] = SchmittLow;

	return SchmittLow;
}

/*
 * @brief
 *         	Get ONThreshold for TouchSensor
 * @param
 *          [IN] PadIndex
 *          [IN] GroupIndex
 * @return
 *          Schmitt High
 */
uint16_t Get_SchmittH(uint32_t PadIndex, uint32_t GroupIndex)
{
	uint16_t SchmittHigh;
	const uint16_t* SchmittHPtr;

	SchmittHPtr = T_SchmittH[GroupIndex];
	SchmittHigh = SchmittHPtr[PadIndex];
	mTouch_Schmitt_H[PadIndex] = SchmittHigh;

	return SchmittHigh;
}

/*
 * @brief
 *         	Touch sensor library calls this function when finish a round of touch pad scan
 * @param
*          [IN]: Sensor Result Pointer
 * @return
 *          None
 */
void TouchScanOneRound(uint16_t *SensorResultPtr)
{
//	uint32_t temp;

//	temp = *SensorResultPtr;
//	temp <<= 12;
//	GPIOA->OBUF &= 0xFFFF0FFF;
//	GPIOA->OBUF |= temp;

#if C_TouchProbe
	TP_ServiceLoop(SensorResultPtr);
#endif

	if(CTS_PauseFlag)
	{
		CTS_ScanPause();
		CTS_PauseFlag = 0x8000;
	}
}

/*
 * @brief
 *         	Get total charge and discharge time when finishing the number of scans(C_ScanNo) per pad.
 * @param
 *          None.
 * @return
 *          None.
 */
uint16_t F_CTS_GetScanTime(void)
{
	return CTS->TMBCAP;			// Get charge & discharge total time
}

/**
 * @brief
 *
 * @param
 *          None.
 * @return
 *          None.
 */
void CTS_TM1_IRQHandler(void)
{
	CLEAR_FLAG(CTS->STS, CTS_STS_TMB_INTF_MSK, CTS_STS_TMB_INTF_FLAG);
}

/**
 * @brief
 *
 * @param
 *          None.
 * @return
 *          None.
 */
void CTS_TM0_IRQHandler(void)
{
	ISR_Service_CTS();
	CLEAR_FLAG(CTS->STS, CTS_STS_TMA_INTF_MSK, CTS_STS_TMA_INTF_FLAG);
}

void CTS_BeforeSleep(void)
{
	uint8_t Temp;
	volatile uint32_t* TimePtr;

	NVIC_DisableIRQ(CTS_TM0_IRQn);               // Disable CTS_TMA INT
	NVIC_DisableIRQ(CTS_TM1_IRQn);               // Disable CTS_TMB INT


	CLEAR_BIT(CTS->CTRL,(CTS_CTRL_START_ENABLE | CTS_CTRL_CTSEN_ENABLE | CTS_CTRL_SLEEP_CLK_SEL_POS));
	SET_BIT(CTS->CTRL,CTS_CTRL_SLEEP_MULTIIO_EN_ENABLE);

	WRITE_REG(CTS->TMAPLOAD,  C_ScanNo);
	WRITE_REG(CTS->TMACOUNT,  C_ScanNo);

	WRITE_REG(CTS->TMB0PLOAD, (mTouch_ReferenceL[0]>>16)+mTouch_Schmitt_H[0]);
	WRITE_REG(CTS->TMBCOUNT,  (mTouch_ReferenceL[0]>>16)+mTouch_Schmitt_H[0]);
	SET_BIT(CTS->PADSEL, T_CTS_Interface[T_TouchPad[0]]);
		TimePtr = &(CTS->TMB1PLOAD);
	for(Temp=0;Temp<C_WakeUpPadNumber;Temp++)
	{

		TimePtr = (volatile uint32_t* )T_CTS_TMBPload[T_TouchPad[Temp]];
		WRITE_REG(*TimePtr,  (mTouch_ReferenceL[Temp]>>16)+mTouch_Schmitt_H[Temp]);
		SET_BIT(CTS->PADSEL, T_CTS_Interface[T_TouchPad[Temp]]);
	}
		NVIC_EnableIRQ(CTS_TM1_IRQn);               // Enable CTS_TMB INT

	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY1);
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, SMU_SYSLOCK_UNLOCK_KEY2);	       // SMU nulock
  MODIFY_REG(ACU->REG33_CTRL, ACU_REG33_CTRL_DSADC_REG_EN_MSK, ACU_REG33_CTRL_DSADC_REG_EN_DISABLE);		     //REG33 pins.
	MODIFY_REG(SMU->SYSLOCK, SMU_SYSLOCK_UNLOCK_KEY_MSK, 0);	                             // SMU lock
	//	T_CTS_Interface[];
		WRITE_REG(CTS->CTRL, (CTS_CTRL_CTSEN_ENABLE | CTS_CTRL_AUTOSTOP_DISABLE | CTS_CTRL_CHARGE_CURRENT_50uA
	                    | CTS_CTRL_SLEEP_CLK_SEL_8Hz | CTS_CTRL_SLEEP_EN_ENABLE | CTS_CTRL_SLEEP_MULTIIO_EN_ENABLE | CTS_CTRL_TMB_INTEN_SEL_ENABLE
                    	| CTS_CTRL_TMA_MODE_CTSTMR | CTS_CTRL_TMB_MODE_CTSTMR | CTS_CTRL_TMA_CLK_SEL_CTSMODULE | CTS_CTRL_TMB_CLK_SEL_IOSC16M | CTS_CTRL_START_ENABLE));


//	SCB->SCR = (1UL << 2); // Deep Sleep Mode
//	__WFI();  // Sleep Mode

}

void CTS_Pause_Clr(void)
{
		CTS_PauseFlag = 0;

}
void CTS_Pause(void)
{
		CTS_PauseFlag = 1;

}

uint16_t CTS_PauseStatus(void)
{
		return CTS_PauseFlag;
}
