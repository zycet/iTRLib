#ifndef _FILTER_H
#define _FILTER_H

#include ".\..\Basic\Basic.h"

typedef struct _TDFilterStruct
{
	F32 V1;
	F32 V2;
	F32 Aim;
	F32 Tr;
	F32 Cycle;
} TDFilterStruct;

F32 Fsg(F32 x, F32 d);
F32 Fal(F32 e, F32 a, F32 b);
F32 DFal(F32 e, F32 a, F32 b);
F32 Fhan(F32 x1, F32 x2, F32 r, F32 h);
void TDFilterInit(TDFilterStruct* Obj);
void TDFilterInit2(TDFilterStruct* Obj,F32 Tr,F32 Cycle);
void TDFilterInit3(TDFilterStruct* Obj,F32 Tr,F32 Cycle,F32 Aim);
void TDFilter(TDFilterStruct* Obj);

#endif

