#ifndef _NAVMATH_H
#define _NAVMATH_H

#define EarthR 6371004

void CalcXY(F32 Ang, F32 Dis, F32* X, F32* Y);
void CalcAngDis(F32 X, F32 Y, F32* Ang, F32* Dis);
//水平极坐标旋转(dAng表示向量旋转的角度(顺时针))
void CoordRotate2D(F32 X, F32 Y, F32 dAng, F32* X2, F32* Y2);
//计算两点水平距离c->a
F32 TwoPointsHorDistance(F64 cLon, F64 cLat, F64 aLon, F64 aLat);
F32 TwoPointsCourseAngle(F64 P1Lo, F64 P1La, F64 P2Lo, F64 P2La);
F32 LineErrorCalc(F32 TargetYaw,F32 LineYaw, F32 dXY);
//计算当前点沿航线方向到目标点的距离
F32 LineDistanceCalc(F32 TargetYaw,F32 LineYaw, F32 dXY);
//纬度到米
F32 LatDegreeToMeter(F64 dLat);
//经度到米
F32 LonDegreeToMeter(F64 lat, F64 dLon);
U16 AltToU16(F64 Alt);
F32 AltToF32(U16 Alt);

#endif

