#ifndef _CAMERACTRL_H
#define _CAMERACTRL_H

#include ".\..\Basic\Basic.h"

#define CCEquTime 0
#define CCEquDistance 1
#define CCModeDisable 0
#define CCModeLoop 1
#define CCModeOnce 2

typedef struct
{
	//Para
	U8 Type;//0=EquTime,1=EquDistance
	F32 IntervalTime;
	F32 IntervalDistance;
	F32 HoldTime;
	//State
	U32 LastTick;
	F64 LastPos[2];
	F32 HoldCounter;
	bool InWorking;
	//Mode
	U8 Mode;
}CameraCtrlStruct;

void CameraCtrlInit(CameraCtrlStruct* CameraCtrl);
F32 CameraCtrlValue(CameraCtrlStruct* CameraCtrl);
bool CameraCtrlSetMode(CameraCtrlStruct* CameraCtrl,U8 Mode);
bool CameraCtrlProcess(CameraCtrlStruct* CameraCtrl,U32 Tick,F32 T,F64 Lon,F64 Lat);

#endif

