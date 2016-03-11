#include <math.h>
#include ".\..\Basic\Basic.h"
#include ".\BasicMath.h"
#include ".\VTrack.h"
#include ".\..\NavMath\NavMath.h"

F32 VTrackCalcSimple(F32 TarV,F32 TarVLast,F32 MaxA,F32 T)
{
	F32 d=TarV-TarVLast;
	F32 V=0;
	if(BL_ABS(d)<EPSINON)
	{
		V=TarV;
	}
	else if(d>0)
	{
		F32 dV=MaxA*T;
		if(d<dV)
		{
			V=TarV;
		}
		else
		{
			V=TarV+dV;
		}
	}
	else if(d<0)
	{
		F32 dV=-MaxA*T;
		if(d>dV)
		{
			V=TarV;
		}
		else
		{
			V=TarVLast+dV;
		}
	}
	return V;
}

void VTrackInit(VTrackParaDataStruct* VTrackParaData,F32 LimitV,F32 LimitA)
{
	VTrackParaStruct* VTrackPara=&VTrackParaData->VTrackPara;
	VTrackDataStruct* VTrackData=&VTrackParaData->VTrackData;
	VTrackPara->MaxA=LimitA;
	VTrackPara->MinA=-LimitA;
	VTrackPara->MaxV=LimitV;
	VTrackPara->MinV=-LimitV;
	VTrackPara->TrackK=1;
	VTrackPara->ZeroZone=0;
	VTrackPara->MinV=-LimitV;
	VTrackData->CurrV=0;
}

F32 VTrackCalc(VTrackParaDataStruct* VTrackParaData,F32 TarV,F32 T)
{
	VTrackParaStruct* VTrackPara=&VTrackParaData->VTrackPara;
	VTrackDataStruct* VTrackData=&VTrackParaData->VTrackData;
	F32 d=TarV-VTrackData->CurrV;
	if(BL_ABS(d)<EPSINON)
	{
		VTrackData->CurrV=TarV;
	}
	else if(d>0)
	{
		F32 dV=VTrackPara->MaxA*T;
		if(d<dV)
		{
			VTrackData->CurrV=TarV;
		}
		else
		{
			VTrackData->CurrV+=dV;
		}
	}
	else if(d<0)
	{
		F32 dV=VTrackPara->MinA*T;
		if(d>dV)
		{
			VTrackData->CurrV=TarV;
		}
		else
		{
			VTrackData->CurrV+=dV;
		}
	}
	VTrackData->CurrV=BL_LimitF32(VTrackData->CurrV, VTrackPara->MinV, VTrackPara->MaxV);
	return VTrackData->CurrV;
}

F32 STrackCalc(VTrackParaDataStruct* VTrackParaData,F32 dS,F32 T)
{
	VTrackParaStruct* VTrackPara=&VTrackParaData->VTrackPara;
	VTrackDataStruct* VTrackData=&VTrackParaData->VTrackData;
	F32 TarV=0;
	/*
	if(VTrackData->CurrV>0)
	{
		ZeroZone=-VTrackData->CurrV/VTrackPara->MinA;
	}
	if(VTrackData->CurrV<0)
	{
		ZeroZone=-VTrackData->CurrV/VTrackPara->MaxA;
	}*/
	dS=BL_ABSAdject(dS,-VTrackPara->ZeroZone);
	if(BL_ABS(dS)<EPSINON)
	{
		TarV=0;
	}
	else if(dS>0)
	{
		F32 temp=VTrackPara->TrackK*dS*VTrackPara->MaxA;
		TarV=sqrt(temp);
	}
	else
	{
		F32 temp=VTrackPara->TrackK*dS*VTrackPara->MinA;
		TarV=-sqrt(temp);
	}
	return VTrackCalc(VTrackParaData, TarV,T);
}

//导航系矢量位置跟踪
void STrackCalc2(VTrackParaDataStruct* VTrackParaDataN,VTrackParaDataStruct* VTrackParaDataE,F32 dSX,F32 dSY,F32 Yaw,F32* VX,F32* VY,F32 T)
{
	F32 dSN,dSE;
	F32 VN,VE;
	CoordRotate2D(dSX, dSY, -Yaw, &dSN, &dSE);
	VN=STrackCalc(VTrackParaDataN, dSN, T);
	VE=STrackCalc(VTrackParaDataE, dSE, T);
	CoordRotate2D(VN, VE, Yaw, VX, VY);
}

