#include <math.h>
#include ".\..\Basic\Basic.h"
#include ".\BasicMath.h"
#include ".\..\DataStruct\DataStruct.h"
#include ".\Filter.h"

F32 Fsg(F32 x, F32 d)
{
	F32 temp1;
	F32 temp2;
	temp1 = BL_Sign(x + d);
	temp2 = BL_Sign(x - d);
	return (0.5 * (temp1 - temp2));

}

F32 Fal(F32 e, F32 a, F32 b)
{
	//U8 A[64*1024]={0};
	//A[0]=1;
	if (fabs(e) <= b)
		return (F32)(e / pow((F64)b, (F64)(a - 1.0)));
	else
		return (pow(fabs(e), a)) * BL_Sign(e);
}

F32 DFal(F32 e, F32 a, F32 b)
{
	if(fabs(e) <= b)
		return (1.0 / pow(b, (a - 1.0)));
	else
		return (a * BL_Sign(e) * pow(fabs(e), (a - 1.0)));
}

F32 Fhan(F32 x1, F32 x2, F32 r, F32 h)
{
	F32 d;
	F32 a, a0, a1, a2;
	F32 y;
	F32 output;
	d = r * h * h;
	a0 = h * x2;
	y = x1 + a0;
	a1 = sqrt(d * (d + 8.0 * fabs(y)));
	a2 = a0 + BL_Sign(y) * (a1 - d) / 2.0;
	a = (a0 + y) * Fsg(y, d) + a2 * (1.0 - Fsg(y, d));
	output = -r * (a / d) * Fsg(a, d) - r * BL_Sign(a) * (1.0 - Fsg(a, d));

	return output;
}

void TDFilterInit(TDFilterStruct* Obj)
{
	Obj->V1=0;
	Obj->V2=0;
	Obj->Aim=0;
	Obj->Tr = 10;
	Obj->Cycle = 0.01;
}

void TDFilterInit2(TDFilterStruct* Obj,F32 Tr,F32 Cycle)
{
	Obj->V1=0;
	Obj->V2=0;
	Obj->Aim=0;
	Obj->Tr = Tr;
	Obj->Cycle = Cycle;
}

void TDFilterInit3(TDFilterStruct* Obj,F32 Tr,F32 Cycle,F32 Aim)
{
	Obj->V1=Aim;
	Obj->V2=0;
	Obj->Aim=Aim;
	Obj->Tr = Tr;
	Obj->Cycle = Cycle;
}

void TDFilter(TDFilterStruct* Obj)
{
	F32 fh;
	fh = Fhan((Obj->V1 - Obj->Aim), Obj->V2, Obj->Tr, Obj->Cycle);
	Obj->V1 = Obj->V1 + Obj->Cycle * Obj->V2;
	Obj->V2 = Obj->V2 + Obj->Cycle * fh;
}

F32 FIRFilter(BL_QueueF32Struct* FIRFilterObj, F32 NewValue)
{
	S32 i = 0;
	F32 sum = 0;
	BL_QueueF32Insert(FIRFilterObj, NewValue);
	for(i = 0; i < FIRFilterObj->Count; i++)
	{
		sum += BL_QueueF32Read(FIRFilterObj, i);
	}
	return sum / FIRFilterObj->Count;
}

