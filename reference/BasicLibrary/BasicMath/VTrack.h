#ifndef __VTRACK__H
#define __VTRACK__H

#include ".\..\Basic\Basic.h"
#include "BasicMath.h"

typedef struct
{
	F32 CurrV;
}VTrackDataStruct;

typedef struct
{
	F32 MinV,MaxV;
	F32 MinA,MaxA;
	F32 TrackK,ZeroZone;
}VTrackParaStruct;

typedef struct
{
	VTrackParaStruct VTrackPara;
	VTrackDataStruct VTrackData;
}VTrackParaDataStruct;

F32 VTrackCalcSimple(F32 TarV,F32 TarVLast,F32 MaxA,F32 T);
void VTrackInit(VTrackParaDataStruct* VTrackParaData,F32 LimitV,F32 LimitA);
F32 VTrackCalc(VTrackParaDataStruct* VTrackParaData,F32 TarV,F32 T);
F32 STrackCalc(VTrackParaDataStruct* VTrackParaData,F32 dS,F32 T);
void STrackCalc2(VTrackParaDataStruct* VTrackParaDataN,VTrackParaDataStruct* VTrackParaDataE,F32 dSX,F32 dSY,F32 Yaw,F32* VX,F32* VY,F32 T);

#endif

