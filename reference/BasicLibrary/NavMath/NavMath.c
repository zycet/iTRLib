#include <math.h>
#include ".\..\Basic\Basic.h"
#include ".\..\BasicMath\BasicMath.h"
#include ".\..\DataStruct\DataStruct.h"
#include ".\NavMath.h"

void CalcXY(F32 Ang, F32 Dis, F32* X, F32* Y)
{
	Ang = Ang * ANG2RAD;
	*X = Dis * cos(Ang);
	*Y = Dis * sin(Ang);
}

void CalcAngDis(F32 X, F32 Y, F32* Ang, F32* Dis)
{
	if(fabs(X) < EPSINON && fabs(Y) < EPSINON)
	{
		*Ang = 0;
		*Dis = 0;
		return;
	}
	*Dis = sqrt(X * X + Y * Y);
	*Ang = atan2(Y, X) * RAD2ANG;
}

//水平极坐标旋转(dAng表示向量反向旋转的角度(逆时针))
void CoordRotate2D(F32 X, F32 Y, F32 dAng, F32* X2, F32* Y2)
{
	F32 c,s;
	dAng*=ANG2RAD;
	c=cos(dAng);
	s=sin(dAng);
	*X2=+c*X+s*Y;
	*Y2=-s*X+c*Y;
	/*
	F32 A = 0, L = 0;
	CalcAngDis(X, Y, &A, &L);
	A += dAng;
	CalcXY(A, L, X2, Y2);
	*/
}

/*
	假设地球是一个标准球体，半径为R,并且假设东经为正，西经为负，北纬为正，南纬为负，
	则 A(x,y)的坐标可表示为（R*cosy*cosx,R*cosy*sinx,R*siny）
	B(a,b)可表示为(R*cosb*cosa,R*cosb*sina,R*sinb)
	于是，AB对于球心所张的角的余弦大小为
	cosb*cosy*(cosa*cosx+sina*sinx)+sinb*siny=cosb*cosy*cos(a-x)+sinb*siny
	因此AB两点的球面距离为
	R*{arccos[cosb*cosy*cos(a-x)+sinb*siny]}
	cos(a-x) = Ca_c
	cosb = Calat
	sinb = Salat
	cosy = Cclat
	siny = Sclat
*/
//计算两点水平距离c->a
F32 TwoPointsHorDistance(F64 cLon, F64 cLat, F64 aLon, F64 aLat)
{
	F32 temp;
	F64 temp2;
	F64 Cclat, Sclat, Calat, Salat, Ca_c;
	Ca_c = cos(((double)aLon - (double)cLon) * ANG2RAD);
	Cclat = cos((double)cLat * ANG2RAD);
	Sclat = sin((double)cLat * ANG2RAD);
	Calat = cos((double)aLat * ANG2RAD);
	Salat = sin((double)aLat * ANG2RAD);
	temp2 = Calat * Cclat * Ca_c + Salat * Sclat;
	if(temp2 < -1)
		temp2 = -1;
	if(temp2 > 1)
		temp2 = 1;
	temp = (F32)( EarthR * acos(temp2));
	return temp;
}

F32 TwoPointsCourseAngle(F64 P1Lo, F64 P1La, F64 P2Lo, F64 P2La)
{
	F64 temp_n = 0, temp_e = 0;
	F64 angle = 0;
	F64 Len;
	temp_n = P2La - P1La;
	temp_e = (P2Lo - P1Lo) * cos((double)P1La * ANG2RAD);
	Len = sqrt(temp_n * temp_n + temp_e * temp_e);
	angle = 0;
	if(Len > 0)
	{
		angle = acos(BL_LimitF32(temp_n / Len, -0.9999, 0.9999)); //与N轴的夹角
		if(temp_e >= 0)
		{
			angle = angle * RAD2ANG;
		}
		else
		{
			angle = 360.0 - angle * RAD2ANG;
		}
	}
	angle = BL_Limit360(angle);
	return angle;
}

// 计算 侧偏距	TargetYaw 为当前点到目标航点的航向角  LineYaw为当前航段的航向角，dXY为当前点到目标 点的距离
//在航线左侧为正
F32 LineErrorCalc(F32 TargetYaw,F32 LineYaw, F32 dXY)
{

   	F32 lerror;  //侧偏距
   	F32 temp;  //临时变量
 
   	temp = TargetYaw -LineYaw;
   
   	if(temp > 180.0)
   	{
   	    temp =-(360.0-temp);
   	}
   	if(temp<-180.0)
   	{
   	    temp=360.0+temp;
   	}
   	lerror = dXY * sin(temp*ANG2RAD);// 计算侧偏距   
   	return lerror;
}

//计算当前点沿航线方向到目标点的距离
F32 LineDistanceCalc(F32 TargetYaw,F32 LineYaw, F32 dXY)
{
	F32 lerror;  //侧偏距
   	F32 temp;  //临时变量
 
   	temp = TargetYaw-LineYaw;
   
   	if(temp > 180.0)
   	{
   	    temp =-(360.0-temp);
   	}
   	if(temp<-180.0)
   	{
   	    temp=360.0+temp;
   	}
   	lerror = dXY*cos(temp*ANG2RAD);// 计算侧偏距   
   	return lerror;
}

//纬度到米
F32 LatDegreeToMeter(F64 dLat)
{
	return (dLat * ANG2RAD * EarthR);
}

//经度到米
F32 LonDegreeToMeter(F64 lat, F64 dLon)
{
	return (dLon  * ANG2RAD * EarthR * cos(lat * ANG2RAD));
}

U16 AltToU16(F64 Alt)
{
	return (U16)((Alt+1000)*5);
}

F32 AltToF32(U16 Alt)
{
	return (Alt*0.2-1000);
}

