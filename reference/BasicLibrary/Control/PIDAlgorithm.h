#ifndef _PIDALGORITHM_H
#define _PIDALGORITHM_H

#include ".\..\Basic\Basic.h"
#include ".\..\BasicMath\BasicMath.h"
#include ".\..\DataStruct\DataStruct.h"

typedef struct
{
	F32 P, I, D;
	F32 PRegion, PMult, IRegion;
	F32 AllLimit, PLimit,ILimit, DLimit;
} PIDParaStruct;

typedef struct
{
	F32 P, I, D;
	F32 All, LastAll, Integral;
} PIDDataStruct;

S32 CopyBuffer2PIDStruct(U8* Buffer,PIDParaStruct* PIDPara);
S32 CopyPIDStruct2Buffer(PIDParaStruct* PIDPara,U8* Buffer);
void PIDStructInit(PIDParaStruct* PIDPara, F32 Limit,PIDDataStruct* PIDData);
F32 PIDAlgorithm(PIDParaStruct* PIDPara, PIDDataStruct* Data, F32 Error, F32 Diff, F32 K, F32 T, bool IEnable);

#endif

