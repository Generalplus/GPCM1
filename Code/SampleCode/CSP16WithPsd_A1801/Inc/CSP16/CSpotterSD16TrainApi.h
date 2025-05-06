
#ifndef __CSPOTTERSD16TRAIN_API_H
#define __CSPOTTERSD16TRAIN_API_H

#include "CSpotterSDK16Api.h"

#ifdef __cplusplus
extern "C"{
#endif

// Purpose: Create a trainer
// lpbyCYBase(IN): a base model for trainer
// lpbyMemPool(OUT): memory buffer for trainer
// nMemSize(IN): memory buffer size
// pnErr(OUT): CSPOTTER_SUCCESS indicates success, else error code. It can be NULL.
// Return: a trainer handle or NULL
CSPDLL_API CSP_HANDLE CSpotterSD16_Init(uint8_t *lpbyCYBase, uint8_t *lpbyMemPool, int32_t nMemSize, int32_t *pnErr);

// Purpose: Destroy a trainer (free resources)
// hCSpotter(IN): a handle of the trainer
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_Release(CSP_HANDLE hCSpotter);

CSPDLL_API int32_t CSpotterSD16_GetMemoryUsage(uint8_t *lpbyCYBase, int32_t bEnableSpeakerMode);

// Purpose: Reset trainer
// hCSpotter(IN): a handle of the trainer
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_Reset(CSP_HANDLE hCSpotter);

// Purpose: Prepare to add a new utterance for training
// hCSpotter(IN): a handle of the trainer
// nUttrID(IN): identifier, the range is [0, 2], we prefer to use 3 utterances to train a voice tag
// lpszDataBuf(IN/OUT): the pointer of data buffer, it must be a DATA FALSH pointer, the buffer is used to store the voice data
// nBufSize(IN): the size of data buffer
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_AddUttrStart(CSP_HANDLE hCSpotter, int32_t nUttrID, uint8_t *lpszDataBuf, int32_t nBufSize);

CSPDLL_API int32_t CSpotterSD16_AddUttrStartForSpeaker(CSP_HANDLE hCSpotter);

// Purpose: Transfer voice samples to the trainer for training
// hCSpotter(IN): a handle of the trainer
// lpsSample(IN): the pointer of voice data buffer
// nNumSample(IN): the number of voice data (a unit is a short, we prefer to add 160 samples per call)
// Return: "CSPOTTER_ERR_NeedMoreSample" indicates call this function again, otherwise Success or error code
CSPDLL_API int32_t CSpotterSD16_AddSample(CSP_HANDLE hCSpotter, int16_t *lpsSample, int32_t nNumSample);

// Purpose: Finish the adding process
// hCSpotter(IN): a handle of the trainer
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_AddUttrEnd(CSP_HANDLE hCSpotter);

// Purpose: Get the utterance boundary
// hCSpotter(IN): a handle of the trainer
// pnStart(OUT): starting point (samples)
// pnEnd(OUT): ending point (samples)
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_GetUttrEPD(CSP_HANDLE hCSpotter, int32_t *pnStart, int32_t *pnEnd);

// Purpose: Check whether the added utterance is different from the first one
// hCSpotter(IN): a handle of the trainer
// nDiffChkLevel(IN): the difference check level
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_DifferenceCheck(CSP_HANDLE hCSpotter, int32_t nDiffChkLevel);				// Deprecated
CSPDLL_API int32_t CSpotterSD16_DifferenceCheckWithRejLevel(CSP_HANDLE hCSpotter, int32_t nRejLevel);		// in the range of [+100, -100]

// Purpose: Train a voice tag
// hCSpotter(IN): a handle of the trainer
// lpszModelAddr(IN/OUT): the pointer of model buffer, it must be a DATA FALSH pointer
// nBufSize(IN): the size of model buffer
// nTagID(IN): the user specific ID, in the range of [0, 32767]
// nRejLevel(IN): rejection level, in the range of [0, 100]. The voice tag will be rejected if the quality is not good enough.
// pnUsedSize(OUT): the model size
// Return: Success or error code
CSPDLL_API int32_t CSpotterSD16_TrainWord(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t nRejLevel, int32_t *pnUsedSize);
CSPDLL_API int32_t CSpotterSD16_TrainWordForSpeaker(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t *pnUsedSize);

CSPDLL_API int32_t CSpotterSD16_DeleteWord(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t *pnUsedSize);

CSPDLL_API int32_t CSpotterSD16_GetCmdID(uint8_t *lpszModelAddr, int32_t nTagID);
CSPDLL_API int32_t CSpotterSD16_GetTagID(uint8_t *lpszModelAddr, int32_t nCmdID);

// Purpose: Check whether the added utterance exists or not
// hCSpotter(IN): a handle of the trainer
// lpszModelAddr(IN): the pointer of model buffer
// nBufSize(IN): the size of model buffer
// nSimChkLevel(IN): the similarity check level
// Return: Voice tag ID or error code
CSPDLL_API int32_t CSpotterSD16_SimilarityCheck(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nSimChkLevel);				// Deprecated
CSPDLL_API int32_t CSpotterSD16_SimilarityCheckWithRejLevel(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nRejLevel);	// in the range of [+100, -100]

// The default is 600. It is equal to the RMS amplitude and the wave amplitude is more than 4 times of that amount.
CSPDLL_API int32_t CSpotterSD16_SetBackgroundEnergyThreshd(CSP_HANDLE hCSpotter, int32_t nThreshold);

// The default is 0. The range is [-100, 100].
CSPDLL_API int32_t CSpotterSD16_SetEpdLevel(CSP_HANDLE hCSpotter, int32_t nEpdLevel);


//-----------------------------------------------------------------------------
//	Support SPI Flash (Optional)
//-----------------------------------------------------------------------------
CSPDLL_API CSP_HANDLE CSpotterSD16_Init_FromSPI(uint8_t *lpbyCYBase, uint8_t *lpbyMemPool, int32_t nMemSize, int32_t *pnErr);
CSPDLL_API int32_t CSpotterSD16_GetMemoryUsage_FromSPI(uint8_t *lpbyCYBase, int32_t bEnableSpeakerMode);
CSPDLL_API int32_t CSpotterSD16_AddUttrStart_FromSPI(CSP_HANDLE hCSpotter, int32_t nUttrID, uint8_t *lpszDataBuf, int32_t nBufSize);
CSPDLL_API int32_t CSpotterSD16_AddUttrStartForSpeaker_FromSPI(CSP_HANDLE hCSpotter);
CSPDLL_API int32_t CSpotterSD16_AddSample_FromSPI(CSP_HANDLE hCSpotter, int16_t *lpsSample, int32_t nNumSample);
CSPDLL_API int32_t CSpotterSD16_AddUttrEnd_FromSPI(CSP_HANDLE hCSpotter);
CSPDLL_API int32_t CSpotterSD16_DifferenceCheckWithRejLevel_FromSPI(CSP_HANDLE hCSpotter, int32_t nRejLevel);	// in the range of [+100, -100]
CSPDLL_API int32_t CSpotterSD16_TrainWord_FromSPI(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t nRejLevel, int32_t *pnUsedSize);
CSPDLL_API int32_t CSpotterSD16_TrainWordForSpeaker_FromSPI(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t *pnUsedSize);
CSPDLL_API int32_t CSpotterSD16_DeleteWord_FromSPI(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nBufSize, int32_t nTagID, int32_t *pnUsedSize);
CSPDLL_API int32_t CSpotterSD16_SimilarityCheckWithRejLevel_FromSPI(CSP_HANDLE hCSpotter, uint8_t *lpszModelAddr, int32_t nRejLevel);	// in the range of [+100, -100]
CSPDLL_API int32_t CSpotterSD16_GetCmdID_FromSPI(uint8_t *lpszModelAddr, int32_t nTagID);
CSPDLL_API int32_t CSpotterSD16_GetTagID_FromSPI(uint8_t *lpszModelAddr, int32_t nCmdID);

#ifdef __cplusplus
}
#endif

#endif // __CSPOTTERSD16TRAIN_API_H
