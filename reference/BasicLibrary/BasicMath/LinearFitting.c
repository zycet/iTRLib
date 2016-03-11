#include <stdlib.h>
#include ".\..\Basic\Basic.h"
#include "BasicMath.h"
#include ".\Matrix.h"
#include "LinearFitting.h"

void LinearFitting2Init(LinearFitting2Struct* LF2S, S32 SectionNum)
{
	S32 i;
	LF2S->SectionNum = SectionNum;
	LF2S->VECs = malloc(sizeof(VEC) * SectionNum);
	for(i = 0; i < SectionNum; i++)
	{
		BL_VecAllocate(&LF2S->VECs[i], 3);
	}
}

void LinearFitting2Set(LinearFitting2Struct* LF2S,F32 K0,F32 K1,F32 K2)
{
	S32 i;
	for(i = 0; i < LF2S->SectionNum; i++)
	{
		LF2S->VECs[i].Data[0]=K0;
		LF2S->VECs[i].Data[1]=K1;
		LF2S->VECs[i].Data[2]=K2;
	}
}

F32 LinearFitting2Size(LinearFitting2Struct* LF2S)
{
	if(LF2S->SectionNum != 0)
		return 1.0 / LF2S->SectionNum;
	return 0;
}

F32 LinearFitting2(LinearFitting2Struct* LF2S, F32 X)
{
	S32 n;
	F32 size = LinearFitting2Size(LF2S);
	if(X < 0)
		return 0;
	if(X > 1)
		return 0;
	if(size <= 0)
		return 0;
	n = (S32)(X / size);
	if(n>=LF2S->SectionNum)
		n=LF2S->SectionNum-1;
	return BL_VecCalcEq(&LF2S->VECs[n], X);
}

F32 LinearFitting2WithScale(LinearFitting2Struct* LF2S, F32 X, F32 X1, F32 X2, F32 Y1, F32 Y2)
{
	F32 Y;
	if(X2 <= X1)
		return 0;
	X = (X - X1) / (X2 - X1);
	Y = LinearFitting2(LF2S, X);
	Y = Y * (Y2 - Y1) + Y1;
	return Y;
}

