/*
	基础数学库
	BUAA 张以成
	2012-8-24
*/
#ifndef __BASICMATH_H
#define __BASICMATH_H
#ifndef PI
#define PI 3.141592656//三角常数
#endif
#define ANG2RAD 0.0174532925//角度转换为弧度
#define RAD2ANG 57.295779469//弧度转换为角度
#define EPSINON	0.00001//高阶小量

#include ".\..\Basic\Basic.h"
#include ".\Matrix.h"
#include ".\Filter.h"
#include ".\LinearFitting.h"
#include ".\VTrack.h"

F32 BL_Sign (F32 Value);
F32 BL_Limit180(F32 Value);
F32 BL_Limit360(F32 Value);
F32 BL_LimitPI(F32 Value);
F32 BL_Limit2PI(F32 Value);

#endif

