#ifndef CAMERAINTERCALC_H
#define CAMERAINTERCALC_H

#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{
/*
    提供相机内参数描述及像素坐标与相机坐标间变换
*/
class CameraInterCalc
{
    public:
        /*
            初始化内部数据空间(定长矩阵)
        */
        CameraInterCalc();
        /*
            释放资源
        */
        virtual ~CameraInterCalc();
        /*
            对象内容复制
        */
        CameraInterCalc(const CameraInterCalc& other);
        /*
            通过设置焦距的方法生成矩阵
        */
        void SetPara(F32 F,F32 dX,F32 dY,F32 u0,F32 v0);
        /*
            通过设置归一化矩阵的方式生成矩阵
        */
        void SetPara(F32 Fu,F32 Fv,F32 u0,F32 v0);
        /*
            相机坐标到像素坐标的转换
        */
        BOOL CalcC2P(const Vector& CameraPoint,Vector& PixelPoint);
        /*
            像素坐标到相机坐标的转换(Z为相机坐标下的假定距离)
        */
        BOOL CalcP2C(const Vector& PixelPoint,F32 Z,Vector& CameraPoint);
        /*
            相机坐标到像素坐标的转换矩阵
        */
        Matrix MatC2P;
        /*
            像素坐标到相机坐标的转换矩阵
        */
        Matrix MatP2C;
    protected:
    private:
        BOOL isMatC2PAvailable;//在调用SetPara有效
        BOOL isMatP2CAvailable;//在调用CalcP2C时自动转换并使其有效(但在isMatC2PAvailable无效时亦无效)
};
}

#endif // CAMERAINTERCALC_H
