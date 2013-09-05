#include <Math.h>
#include <stdlib.h>
#include ".\..\Basic\Basic.h"
#include ".\..\BasicMath\BasicMath.h"
#include ".\..\DataStruct\DataStruct.h"
#include ".\PIDAlgorithm.h"

S32 CopyBuffer2PIDStruct(U8* Buffer,PIDParaStruct* PIDPara)
{
	S32 p=0;
	PIDPara->P=ASF32(&Buffer[p]);p+=4;
	PIDPara->I=ASF32(&Buffer[p]);p+=4;
	PIDPara->D=ASF32(&Buffer[p]);p+=4;
	PIDPara->PRegion=ASF32(&Buffer[p]);p+=4;
	PIDPara->PMult=ASF32(&Buffer[p]);p+=4;
	PIDPara->IRegion=ASF32(&Buffer[p]);p+=4;
	PIDPara->AllLimit=ASF32(&Buffer[p]);p+=4;
	PIDPara->PLimit=ASF32(&Buffer[p]);p+=4;
	PIDPara->ILimit=ASF32(&Buffer[p]);p+=4;
	PIDPara->DLimit=ASF32(&Buffer[p]);p+=4;
	return p;//p=4*10=40
}

S32 CopyPIDStruct2Buffer(PIDParaStruct* PIDPara,U8* Buffer)
{
	S32 p=0;
	ASF32(&Buffer[p])=PIDPara->P;p+=4;
	ASF32(&Buffer[p])=PIDPara->I;p+=4;
	ASF32(&Buffer[p])=PIDPara->D;p+=4;
	ASF32(&Buffer[p])=PIDPara->PRegion;p+=4;
	ASF32(&Buffer[p])=PIDPara->PMult;p+=4;
	ASF32(&Buffer[p])=PIDPara->IRegion;p+=4;
	ASF32(&Buffer[p])=PIDPara->AllLimit;p+=4;
	ASF32(&Buffer[p])=PIDPara->PLimit;p+=4;
	ASF32(&Buffer[p])=PIDPara->ILimit;p+=4;
	ASF32(&Buffer[p])=PIDPara->DLimit;p+=4;
	return p;
}


//Error=Target-Curr
//Diff=Curr(n)-Curr(n-1)
//Kp>0 Ki>0 Kd<0
//K=AllK
//T=1/Hz

void PIDStructInit(PIDParaStruct* PIDPara, F32 Limit,PIDDataStruct* PIDData)
{
	PIDPara->P=0;
	PIDPara->I=0;
	PIDPara->D=0;
	PIDPara->PMult=1;
	PIDPara->PRegion=0;
	PIDPara->AllLimit=Limit;
	PIDPara->PLimit=Limit;
	PIDPara->ILimit=Limit;
	PIDPara->DLimit=Limit;

	PIDData->P=0;
	PIDData->I=0;
	PIDData->D=0;
	PIDData->All=0;
	PIDData->LastAll=0;
	PIDData->Integral=0;
}

F32 PIDAlgorithm(PIDParaStruct* PIDPara, PIDDataStruct* Data, F32 Error, F32 Diff, F32 K, F32 T, bool IEnable)
{
	F32 temp;
	//分段P
	if(fabs(Error) < PIDPara->PRegion)
	{
		Data->P = Error * PIDPara->P;
	}
	else
	{
		Data->P = (Error-PIDPara->PRegion)*PIDPara->P*PIDPara->PMult+PIDPara->PRegion *PIDPara->P;
	}
	Data->P *= K;
	Data->P = BL_LimitF32(Data->P, -PIDPara->PLimit, PIDPara->PLimit);
	//区域限值I
	temp = PIDPara->I * K;
	if(fabs(Error) < PIDPara->IRegion && IEnable == True)
	{
		Data->Integral += Error * T;
	}
	Data->I = Data->Integral * temp;
	Data->I = BL_LimitF32(Data->I, -PIDPara->ILimit, PIDPara->ILimit);
	if(fabs(Error) < PIDPara->IRegion && IEnable == True)
	{
		if(temp != 0)
		{
			Data->Integral = Data->I / temp;
		}
		else
		{
			Data->Integral = 0;
		}
	}
	
	//限值D
	Data->D = Diff * PIDPara->D * K;
	Data->D = BL_LimitF32(Data->D, -PIDPara->DLimit, PIDPara->DLimit);
	//总限值
	Data->All = Data->P + Data->I + Data->D;
	Data->All = BL_LimitF32(Data->All, -PIDPara->AllLimit, PIDPara->AllLimit);
	return Data->All;
}

