#ifndef CAMERAEXTERCALC_H
#define CAMERAEXTERCALC_H

#include "itrbase.h"
#include "../feature/feature.h"
#include "camera.h"
#include "itralgorithm.h"
#include "math.h"

using namespace itr_math;
using namespace itr_algorithm;
namespace itr_vision
{
/**
* \brief 相机外参数描述与计算类
* \note 实现通过特征点匹配计算单应性矩阵(H)
* \note 实现通过相机与深度信息计算运动矩阵(R,T,N,V)
*/
class CameraExterCalc
{
public:
    /**
    * \brief 内部定长数据初始化
    */
    CameraExterCalc();
    /**
    * \brief 回收资源
    */
    virtual ~CameraExterCalc();
    /**
    * \brief 对象Clone构造函数
    */
    CameraExterCalc(const CameraExterCalc &other);
    /**
    * \brief 使用两组特征点通过RANSAC计算单应性矩阵(H)
    * \param PointList1 特征点组1
    * \param List1Num 特征点组1长度
    * \param PointList2 特征点组2
    * \param List2Num 特征点组2长度
    */
    BOOL CalcH(VectorFeaturePoint *PointList1,S32 List1Num,VectorFeaturePoint *PointList2,S32 List2Num,S32 matched_num);

    /**
    * \brief 通过给定的相机内参数和深度参数D计算运动参数(R,T,N,V)
    * \param CameraInterPara 相机内参数
    * \param D 深度(单位:米)
    * \note 此计算步骤需已完成单应性矩阵计算(既已成功调用CalcHV())
    */
    BOOL CalcMotion(CameraInterCalc &CameraInterPara,F32 D);

    /**
    * \brief 单应性矩阵H[3*3]
    */
    Matrix H;
    /**
    * \brief 单应性向量V[3]={up,vp,1}
    */
    Matrix V;
    /**
    * \note 转动矩阵（两列3*3*2）
    */
    Matrix R;
    /**
    * \note 平移向量（两列3*2）
    */
    Matrix t;
    /**
    * \note 平面的单位法向量（两列3*2）
    */
    Matrix N;
protected:
private:
};
}
#endif // CAMERAEXTERCALC_H
