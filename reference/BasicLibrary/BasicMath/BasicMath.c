#include <math.h>
#include ".\..\Basic\Basic.h"
#include "BasicMath.h"

F32 BL_Limit180(F32 Value)
{
	if(Value != Value)
	{
		return 0;
	}
	while(Value < -180)
	{
		Value += 360;
	}
	while(Value > 180)
	{
		Value -= 360;
	}
	return Value;
}

F32 BL_Limit360(F32 Value)
{
	if(Value != Value)
	{
		return 0;
	}
	while(Value < 0)
	{
		Value += 360;
	}
	while(Value > 360)
	{
		Value -= 360;
	}
	return Value;
}

F32 BL_LimitPI(F32 Value)
{
	if(Value != Value)
	{
		return 0;
	}
	while(Value < -PI)
	{
		Value += 2 * PI;
	}
	while(Value > PI)
	{
		Value -= 2 * PI;
	}
	return Value;
}

F32 BL_Limit2PI(F32 Value)
{
	if(Value != Value)
	{
		return 0;
	}
	while(Value < 0)
	{
		Value += 2 * PI;
	}
	while(Value > 2 * PI)
	{
		Value -= 2 * PI;
	}
	return Value;
}

