#ifndef SURF_H
#define SURF_H

#include <vector>
#include "itrbase.h"
#include "./feature.h"
#include "../process/process.h"

using namespace itr_math;

namespace itr_vision
{
static const S32 SURF_OCTAVES = 5;
static const S32 SURF_INTERVALS = 4;
static const S32 SURF_INIT_SAMPLE = 2;
static const F32 SURF_THRESHOLD = 0.0004f;
static const S32 SURF_Filter_Map [SURF_OCTAVES][SURF_INTERVALS] = {{0,1,2,3}, {1,3,4,5}, {3,5,6,7}, {5,7,8,9}, {7,9,10,11}};
static const F64 SURF_Gauss25 [7][7] =
{
    {0.02546481,	0.02350698,	0.01849125,	0.01239505,	0.00708017,	0.00344629,	0.00142946},
    {0.02350698,	0.02169968,	0.01706957,	0.01144208,	0.00653582,	0.00318132,	0.00131956},
    {0.01849125,	0.01706957,	0.01342740,	0.00900066,	0.00514126,	0.00250252,	0.00103800},
    {0.01239505,	0.01144208,	0.00900066,	0.00603332,	0.00344629,	0.00167749,	0.00069579},
    {0.00708017,	0.00653582,	0.00514126,	0.00344629,	0.00196855,	0.00095820,	0.00039744},
    {0.00344629,	0.00318132,	0.00250252,	0.00167749,	0.00095820,	0.00046640,	0.00019346},
    {0.00142946,	0.00131956,	0.00103800,	0.00069579,	0.00039744,	0.00019346,	0.00008024}
};
/**
* \brief 此类实现了SURF算法
* \note 图像数据基于itr_math::Matrix类型,全部为单精度浮点计算.
* \note 运算过程尽量基于itr_math::Calculate中的方法,从而实现了计算方式的可替代优化.
* \note 后期会考虑进行对ARM-Neon的汇编优化.
*/
class SURF
{
public:
    /**
    * \brief 完成对象构造后必须调用Init()才能正常工作.
    */
    SURF();
    /**
    * \brief 释放动态申请的内存
    */
    virtual ~SURF();
    /**
    * \brief 初始化SURF类,内部数据,只有成功调用此函数后才能正常工作.
    * \param Width 图像宽度
    * \param Height 图像高度
    * \param OctaveNum 八度数
    * \param IntervalNum 间隔数
    * \param InitSample 初始采样
    * \param Threshold 过滤阀值
    */
    void Init(S32 Width,S32 Height,S32 OctaveNum,S32 IntervalNum,S32 InitSample,F32 Threshold);
    /**
    * \brief 处理图像并生成特征点
    * \param Img 待处理图像
    * \param FeaturePointList 特征点列表(生成的特征点会储存在内)
    * \return 找到的特征点数量
    */
    S32 Process(const Matrix& Img,std::vector<VectorFeaturePoint>& FeaturePointList);
    /**
    * \brief 过滤阀值
    */
    F32 Threshold;

    std::vector<BoxHessian*> OctaveList;
private:
    BOOL IsExtremum(S32 r, S32 c, BoxHessian *t, BoxHessian *m, BoxHessian *b);
    void MakeFeaturePoint(S32 r, S32 c, BoxHessian *t, BoxHessian *m, BoxHessian *b,VectorFeaturePoint &vfp);
    void GetOrientation(VectorFeaturePoint& Point);
    void GetDescriptor(VectorFeaturePoint& Point);
    F32 HaarX(S32 row, S32 column, S32 s);
    F32 HaarY(S32 row, S32 column, S32 s);
    //std::vector<BoxHessian*> OctaveList;
    Matrix IntImg;
    S32 OctaveNum;
    S32 IntervalNum;
    S32 InitSample;
};
}
#endif // SURF_H
