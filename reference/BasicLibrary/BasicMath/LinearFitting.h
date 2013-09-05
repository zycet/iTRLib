#ifndef __LINEARFITTING_H
#define __LINEARFITTING_H

#include ".\..\Basic\Basic.h"
#include "BasicMath.h"
#include ".\Matrix.h"

struct  _LinearFitting2Struct
{
	S32 SectionNum;
	VEC* VECs;
};
typedef struct _LinearFitting2Struct LinearFitting2Struct;

void LinearFitting2Init(LinearFitting2Struct* LF2S, S32 SectionNum);
void LinearFitting2Set(LinearFitting2Struct* LF2S,F32 K0,F32 K1,F32 K2);
F32 LinearFitting2Size(LinearFitting2Struct* LF2S);
F32 LinearFitting2(LinearFitting2Struct* LF2S, F32 X);
F32 LinearFitting2WithScale(LinearFitting2Struct* LF2S, F32 X, F32 X1, F32 X2, F32 Y1, F32 Y2);

#endif

