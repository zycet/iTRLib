#ifndef CAMERAINTERCALC_H
#define CAMERAINTERCALC_H

#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{
    /**
    * \brief 提供相机内参数描述及像素坐标与相机坐标间变换.
    * \note 像素坐标系定义:原点在图像右上角,X轴向右,Y轴向下.
    * \note 相机坐标系定义:原点在光轴中央,X轴向右,Y轴向上.
    */
    class CameraInterCalc
    {
        public:
            /**
            * \brief 初始化标准的相机内参数矩阵
            */
            CameraInterCalc();
            /**
            * \brief 释放
            */
            virtual ~CameraInterCalc();
            /**
            * \brief 对象Clone构造函数
            */
            CameraInterCalc(const CameraInterCalc &other);
            /**
            * \brief 通过设置焦距的方法生成矩阵
            * \param F 焦距(单位:米)
            * \param dX 水平方向物理单位分辨率(单位:米/像素)
            * \param dY 垂直方向物理单位分辨率(单位:米/像素)
            * \param u0 水平半幅图像的像素数(单位:像素)
            * \param v0 垂直半幅图像的像素数(单位:像素)
            */
            void SetPara(F32 F,F32 dX,F32 dY,F32 u0,F32 v0);
            /**
            * \brief 通过设置视场夹角的方法生成矩阵
            * \param degX 水平方向视场夹角(单位:角度)
            * \param degY 垂直方向向视场夹角(单位:角度)
            * \param u0 水平半幅图像的像素数(单位:像素)
            * \param v0 垂直半幅图像的像素数(单位:像素)
            */
            void SetPara(F32 degX,F32 degY,F32 u0,F32 v0);
            /**
            * \brief 相机坐标到像素坐标的转换
            * \param CameraPoint 输入的相机坐标系向量([x,y,z],单位:米)
            * \param PixelPoint 输出的像素坐标系([u,v,1],单位:像素)
            */
            BOOL CalcC2P(const Vector &CameraPoint,Vector &PixelPoint);
            /**
            * \brief 像素坐标到相机坐标的转换
            * \param PixelPoint 输入的像素坐标系([u,v,1],单位:像素)
            * \param Z 为相机坐标下的假定距离
            * \param CameraPoint 输出的相机坐标系向量([x,y,z],单位:米)
            */
            BOOL CalcP2C(const Vector &PixelPoint,F32 Z,Vector &CameraPoint);
            /**
            * \note 相机坐标到像素坐标的转换矩阵
            */
            Matrix MatC2P;
            /**
            * \note 像素坐标到相机坐标的转换矩阵
            */
            Matrix MatP2C;
        protected:
        private:
            /**
            * \note 在调用SetPara后有效
            */
            BOOL isMatC2PAvailable;
            /**
            * \note 在调用CalcP2C时自动转换并使其有效(但在isMatC2PAvailable无效时亦无效)
            */
            BOOL isMatP2CAvailable;
    };
}

#endif // CAMERAINTERCALC_H
