#ifndef __CSPOTTERSDK_API_H
#define __CSPOTTERSDK_API_H

#if defined(_WIN32)
	#ifdef CSpotterDll_EXPORTS
		#define CSPDLL_API __declspec(dllexport)
	#endif
#endif

#ifndef CSPDLL_API
#define CSPDLL_API
#endif

#include <stdint.h>
#include "CSpotterSDKApi_Const.h"

#ifdef __cplusplus
extern "C"{
#endif

#define CSP_HANDLE                            void*	
	
// lpbyCYBase(IN): The background model, contents of CYBase.mod.
// lppbyModel(IN): The command model.
// nMaxTime(IN): The maximum buffer length in number of frames for keeping the status of commands.
// lpbyMemPool(IN/OUT): Memory buffer for the recognizer.
// nMemSize(IN): Size in bytes of the memory buffer lpbyMemPool.
// lpbyState(IN/OUT): State buffer for recognizer.
// nStateSize(IN): Size in bytes of the state buffer lpbyState.
// pnErr(OUT): CSPOTTER_SUCCESS indicates success, else error code. It can be NULL.
// Return: a recognizer handle or NULL
CSPDLL_API CSP_HANDLE CSpotter_Init_Sep(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API CSP_HANDLE CSpotter_Init_Multi(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);

// Purpose: Destroy a recognizer (free resources)
// hCSpotter(IN): a handle of the recognizer
// Return: Success or error code
CSPDLL_API int32_t CSpotter_Release(CSP_HANDLE hCSpotter);

// Purpose: Reset recognizer
// hCSpotter(IN): a handle of the recognizer
// Return: Success or error code
CSPDLL_API int32_t CSpotter_Reset(CSP_HANDLE hCSpotter);

// Purpose: Transfer voice samples to the recognizer for recognizing.
// hCSpotter(IN): a handle of the recognizer
// lpsSample(IN): the pointer of voice data buffer
// nNumSample(IN): the number of voice data (a unit is a short, we prefer to add 160 samples per call)
// Return: "CSPOTTER_ERR_NeedMoreSample" indicates call this function again, else call CSpotter_GetResult(...)
CSPDLL_API int32_t CSpotter_AddSample(CSP_HANDLE hCSpotter, int16_t *lpsSample, int32_t nNumSample);

// Purpose: Get recognition results.
// hCSpotter(IN): a handle of the recognizer
// Return: the command ID. It is 0 based
CSPDLL_API int32_t CSpotter_GetResult(CSP_HANDLE hCSpotter);
CSPDLL_API int32_t CSpotter_GetResultEPD(CSP_HANDLE hCSpotter, int32_t *pnWordDura, int32_t *pnEndDelay);
CSPDLL_API int32_t CSpotter_GetResultScore(CSP_HANDLE hCSpotter);

CSPDLL_API int32_t CSpotter_SetEnableNBest(CSP_HANDLE hCSpotter, int32_t bEnable);
CSPDLL_API int32_t CSpotter_GetNBestScore(CSP_HANDLE hCSpotter, int32_t pnCmdIdx[], int32_t pnScore[], int32_t nMaxNBest);

CSPDLL_API int32_t CSpotter_GetNumWord(uint8_t *lpbyModel);

CSPDLL_API int32_t CSpotter_GetMemoryUsage(uint8_t *lpbyModel, int32_t nMaxTime);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_Sep(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_Multi(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime);

CSPDLL_API int32_t CSpotter_GetStateSize(uint8_t *lpbyModel);

CSPDLL_API const char *CSpotter_VerInfo(void);

/************************************************************************/
//  Threshold Adjust API                                                                   
/************************************************************************/
// Purpose: Set model rejection level
// hCSpotter(IN): a handle of the recognizer
// nRejectionLevel(IN): rejection level
// Return: Success or error code
CSPDLL_API int32_t CSpotter_SetRejectionLevel(CSP_HANDLE hCSpotter, int32_t nRejectionLevel);

// Purpose: Set engine response time
// hCSpotter(IN): a handle of the recognizer
// nResponseTime(IN): response time
// Return: Success or error code
CSPDLL_API int32_t CSpotter_SetResponseTime(CSP_HANDLE hCSpotter, int32_t nResponseTime);

// Purpose: Set Cmd reward
// hCSpotter(IN): a handle of the recognizer
// nCmdIdx(IN): the command ID. It is 0 based
// nOffset(IN): the offset
// Return: Success or error code
CSPDLL_API int32_t CSpotter_SetCmdReward(CSP_HANDLE hCSpotter, int32_t nCmdIdx, int32_t nReward);				// Deprecated
CSPDLL_API int32_t CSpotter_SetCmdRewardOffset(CSP_HANDLE hCSpotter, int32_t nCmdIdx, int32_t nOffset);

// Purpose: Set Cmd response reward
// hCSpotter(IN): a handle of the recognizer
// nCmdIdx(IN): the command ID. It is 0 based
// nOffset(IN): the offset
// Return: Success or error code
CSPDLL_API int32_t CSpotter_SetCmdResponseReward(CSP_HANDLE hCSpotter, int32_t nCmdIdx, int32_t nReward);		// Deprecated
CSPDLL_API int32_t CSpotter_SetCmdResponseOffset(CSP_HANDLE hCSpotter, int32_t nCmdIdx, int32_t nOffset);

CSPDLL_API int32_t CSpotter_SetFreqWarpFactor(CSP_HANDLE hCSpotter, int32_t nFactor256);
// The default is 50. It is equal to the RMS amplitude and the wave amplitude is more than 4 times of that amount.
CSPDLL_API int32_t CSpotter_SetMinEnergyThreshd(CSP_HANDLE hCSpotter, int32_t nThreshold);

CSPDLL_API int32_t CSpotter_SetEnableRejectedResult(CSP_HANDLE hCSpotter, int32_t bEnable);
CSPDLL_API int32_t CSpotter_SetRejectedResultEnergyThreshd(CSP_HANDLE hCSpotter, int32_t nThreshold);

CSPDLL_API int32_t CSpotter_GetModelCmdReward(uint8_t *lpbyModel, int32_t nCmdIdx);


CSPDLL_API int32_t CSpotter_SetResultMapID_Multi(CSP_HANDLE hCSpotter, uint16_t **lppnMapID, int32_t nNumMapID);
CSPDLL_API int32_t CSpotter_GetResultMapID(CSP_HANDLE hCSpotter);


//-----------------------------------------------------------------------------
//	Support Speaker Model (Optional)
//-----------------------------------------------------------------------------
CSPDLL_API int32_t CSpotter_SetSpeakerModel(CSP_HANDLE hCSpotter, uint8_t *lpbySpeakerModel);
CSPDLL_API int32_t CSpotter_GetSpeakerResult(CSP_HANDLE hCSpotter, int32_t *pnScore);
CSPDLL_API int32_t CSpotter_SetSpeakerIdentLevel(CSP_HANDLE hCSpotter, int32_t nIdentLevel);

CSPDLL_API int32_t CSpotter_GetMemoryUsage_SepWithSpeaker(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbySpeakerModel);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_MultiWithSpeaker(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbySpeakerModel);

//-----------------------------------------------------------------------------
//	Support External Rejection Model (Optional)
//-----------------------------------------------------------------------------
CSPDLL_API CSP_HANDLE CSpotter_Init_SepWithExtRejModel(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyRejModel, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API CSP_HANDLE CSpotter_Init_MultiWithExtRejModel(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyRejModel, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);

CSPDLL_API int32_t CSpotter_GetMemoryUsage_SepWithExtRejModel(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyRejModel);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_MultiWithExtRejModel(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyRejModel);

CSPDLL_API int32_t CSpotter_GetMemoryUsage_SepWithSpeakerAndExtRejModel(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbySpeakerModel, uint8_t *lpbyRejModel);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_MultiWithSpeakerAndExtRejModel(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbySpeakerModel, uint8_t *lpbyRejModel);

//-----------------------------------------------------------------------------
//	Support VAD (Optional)
//-----------------------------------------------------------------------------
CSPDLL_API int32_t CSpotter_VAD_Enable(CSP_HANDLE hCSpotter, int32_t bEnable);
CSPDLL_API int32_t CSpotter_VAD_SetThreshold(CSP_HANDLE hCSpotter, int32_t nThreshold);			// The default is 10000.
CSPDLL_API int32_t CSpotter_VAD_SetMinEnergyThreshd(CSP_HANDLE hCSpotter, int32_t nThreshold);	// The default is 500. It is equal to the RMS amplitude and the wave amplitude is more than 4 times of that amount.

//-----------------------------------------------------------------------------
//	Support SPI Flash (Optional)
//-----------------------------------------------------------------------------
CSPDLL_API CSP_HANDLE CSpotter_Init_Sep_FromSPI(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API CSP_HANDLE CSpotter_Init_Multi_FromSPI(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API CSP_HANDLE CSpotter_Init_SepWithExtRejModel_FromSPI(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyRejModel, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API CSP_HANDLE CSpotter_Init_MultiWithExtRejModel_FromSPI(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyRejModel, uint8_t *lpbyMemPool, int32_t nMemSize, uint8_t *lpbyState, int32_t nStateSize, int32_t *pnErr);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_Sep_FromSPI(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_Multi_FromSPI(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_SepWithExtRejModel_FromSPI(uint8_t *lpbyCYBase, uint8_t *lpbyModel, int32_t nMaxTime, uint8_t *lpbyRejModel);
CSPDLL_API int32_t CSpotter_GetMemoryUsage_MultiWithExtRejModel_FromSPI(uint8_t *lpbyCYBase, uint8_t *lppbyModel[], int32_t nNumModel, int32_t nMaxTime, uint8_t *lpbyRejModel);
CSPDLL_API int32_t CSpotter_GetNumWord_FromSPI(uint8_t *lpbyModel);
CSPDLL_API int32_t CSpotter_GetModelCmdReward_FromSPI(uint8_t *lpbyModel, int32_t nCmdIdx);

#ifdef __cplusplus
}
#endif

#endif // __CSPOTTERSDK_API_H
