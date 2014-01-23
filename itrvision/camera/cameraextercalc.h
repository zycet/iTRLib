#ifndef CAMERAEXTERCALC_H
#define CAMERAEXTERCALC_H

#include "itrbase.h"
#include "../feature/feature.h"
#include "camera.h"

using namespace itr_math;

namespace itr_vision
{
/*
    相机外参数描述与计算类
*/
class CameraExterCalc
{
    public:
        /*
            定长数据初始化
        */
        CameraExterCalc();
        /*
            回收资源
        */
        virtual ~CameraExterCalc();
        /*
            数据复制
        */
        CameraExterCalc(const CameraExterCalc& other);
        /*
            使用两组特征点通过RANSAC计算单应性矩阵(H,V)
        */
        BOOL CalcHV(CommFeaturePoint* PointList1,S32 List1Num,CommFeaturePoint* PointList2,S32 List2Num);
        /*
            通过给定的相机内参数和深度参数D计算运动参数(R,T,N)
        */
        BOOL CalcMotion(CameraInterCalc& CameraInterPara,F32 D);
        Matrix H;
        Vector V;
        Vector R;
        Vector T;
        Vector N;
    protected:
    private:
};
}
#endif // CAMERAEXTERCALC_H
