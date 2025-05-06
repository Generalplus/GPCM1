#define MaxDelay			2540

typedef struct
{
	short MaxLength;
	short EchoDelay;
	short EchoGain; // Max 1.0 = 0x7FFF
	short SGain;
	short index;
	short DelayBuf[MaxDelay];
} EchoV3_MEMORY_BLOCK;


void  F_EchoEffectV3_Init(EchoV3_MEMORY_BLOCK *Obj,short tDLY, short tGain_IDX);
void  F_EchoEffectV3_ChangeEchoPath(EchoV3_MEMORY_BLOCK *Obj, short delay, short gain, short sgain);
short F_EchoEffectV3_SampleProc(EchoV3_MEMORY_BLOCK *Obj,short SampleIn);
void  F_EchoEffectV3_FrameProc(EchoV3_MEMORY_BLOCK *Obj,short *PcmInBuf, long tSize);


const char * F_SimpleEchoV3_get_version(void);
