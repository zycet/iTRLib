#include ".\..\Basic\Basic.h"
#include ".\..\NavMath\NavMath.h"
#include ".\CameraCtrl.h"

void CameraCtrlInit(CameraCtrlStruct* CameraCtrl)
{
	CameraCtrl->Type=CCEquTime;
	CameraCtrl->IntervalTime=10;
	CameraCtrl->IntervalDistance=100;
	CameraCtrl->HoldTime=1;
	CameraCtrl->LastTick=0;
	CameraCtrl->LastPos[0]=0;
	CameraCtrl->LastPos[1]=0;
	CameraCtrl->HoldCounter=0;
	CameraCtrl->Mode=CCModeDisable;
}

F32 CameraCtrlValue(CameraCtrlStruct* CameraCtrl)
{
	if(CameraCtrl->HoldCounter<=0)
		return -1;
	else 
		return 1;
}

bool CameraCtrlOnce(CameraCtrlStruct* CameraCtrl)
{
	if(CameraCtrl->HoldCounter<=0)
	{
		CameraCtrl->HoldCounter=CameraCtrl->HoldTime;
		return True;
	}
	else
	{
		return False;
	}
}

bool CameraCtrlSetMode(CameraCtrlStruct* CameraCtrl,U8 Mode)
{
	CameraCtrl->InWorking=(Mode!=CCModeDisable);
	if(Mode==CCModeOnce)
	{
		return CameraCtrlOnce(CameraCtrl);
	}
	else
	{
		CameraCtrl->LastTick=0;
		CameraCtrl->LastPos[0]=0;
		CameraCtrl->LastPos[1]=0;
		CameraCtrl->HoldCounter=0;
		CameraCtrl->Mode=Mode;	
		return False;
	}
}

bool CameraCtrlProcess(CameraCtrlStruct* CameraCtrl,U32 Tick,F32 T,F64 Lon,F64 Lat)
{
	bool toShoot=False,shooted=False;
	if(CameraCtrl->Mode==CCModeLoop)
	{
		if(CameraCtrl->Type==CCEquTime)
		{
			if((Tick-CameraCtrl->LastTick)*T>=CameraCtrl->IntervalTime)
			{
				toShoot=True;
			}
		}
		else if(CameraCtrl->Type==CCEquTime)
		{
			if(TwoPointsHorDistance(Lon, Lat, CameraCtrl->LastPos[0], CameraCtrl->LastPos[1])>CameraCtrl->IntervalDistance)
			{
				toShoot=True;
			}
		}
	}
	if(toShoot==True)
	{
		shooted=CameraCtrlOnce(CameraCtrl);
		CameraCtrl->LastTick=Tick;
		CameraCtrl->LastPos[0]=Lon;
		CameraCtrl->LastPos[1]=Lat;
	}
	CameraCtrl->HoldCounter-=T;
	if(CameraCtrl->HoldCounter<0)
		CameraCtrl->HoldCounter=0;
	return shooted;
}

