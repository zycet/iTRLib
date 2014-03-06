#ifndef CAMERASTEREOCALC_H
#define CAMERASTEREOCALC_H

#include "itrbase.h"
#include "itralgorithm.h"
#include "../feature/feature.h"
#include "./cameraintercalc.h"
#include "math.h"
using namespace itr_math;

namespace itr_vision
{
/**
* \brief 此类用于进行立体视觉计算,可以得出两个相机所面对的共同平面离相机的距离.
* \note 此算法假设相机同向安装于一距离已知的刚体上,所图像所拍摄物品主要为一平面,其可估算出平面的方程.
*/
class CameraStereoCalc
{
public:
    /**
    * \brief 表示计算得出的附加信息
    */
    struct CalcExInfo
    {
        /**
        * \brief 特征点匹配度
        * \note 匹配点对数*2/总特征点数*100%
        */
        F32 MatchPercent;
        /**
        * \brief 平面方程的方差
        */
        F32 Var;
        /**
        * \brief 平面方程向量
        * \note Ax+By+Cz=1;Equ[0~3]=A,B,C.
        */
        Vector Equ;
    };
    CameraStereoCalc();
    virtual ~CameraStereoCalc();
    /**
    * \brief 初始化此算法所必须的参数
    * \param CameraInterCalc0 相机0的内参数
    * \param CameraInterCalc1 相机1的内参数
    * \param Distance 相机原点间距(单位:米)
    * \note x向前，y向右，z向下，相机0在前，相机1在后，主要坐标在两相机坐标中间。
    */
    void Init(CameraInterCalc* CameraInterCalc0,CameraInterCalc* CameraInterCalc1,F32 Distance);
    /**
    * \brief 使用两组特征点通过RANSAC计算平面方程
    * \param PointList1 特征点组1(图像坐标系)
    * \param PointList2 特征点组2(图像坐标系)
    * \param DeepZero 坐标X=0,Y=0处Z的值
    * \return 是否成功计算
    */
    bool Calc( std::vector<VectorFeaturePoint>& PointList0, std::vector<VectorFeaturePoint>& PointList1,F32* DeepZero);
    /**
    * \brief 在成功执行Calc后可通过此函数获得附加的计算结果信息
    */
    CalcExInfo GetCalcExInfo();
    /**
    * \brief 相机0的内参数
    */
    CameraInterCalc* CameraInterCalc0;
    /**
    * \brief 相机1的内参数
    */
    CameraInterCalc* CameraInterCalc1;
    /**
    * \brief 相机原点间距(单位:米)
    */
    F32 Distance;
    /**
    * \brief 相机Z轴安装角度(两相机必须使用共同的安装角度)
    * \note 单位:角度,使用右手坐标系.
    */
    F32 InstallAngle;
    F32 getdistance(F32 x,F32 y,F32 z,itr_math::Vector p);
protected:
private:
    struct CalcExInfo _exinfo;
    itr_math::Vector _plan;
    void cof(F32*x,F32*y,F32 *z,F32*w,S32 length);
    F32 median(F32 *a,S32 length);
};

}

#endif // CAMERASTEREO_H
