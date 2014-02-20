#ifndef VECTORFEATUREPOINT_H
#define VECTORFEATUREPOINT_H

#include "itrbase.h"
#include "commfeaturepoint.h"

using namespace itr_math;

namespace itr_vision
{
/**
* breif 适用于SIFT&SURF等算法的向量特征点
*/
class VectorFeaturePoint:public CommFeaturePoint
{
public:
    /**
    * brief 初始化空的对象
    */
    VectorFeaturePoint();
    /**
    * brief 释放占用的资源
    */
    virtual ~VectorFeaturePoint();
    /**
    * brief 复制对象(要求向量维数一致)
    * param other 复制结果
    */
    VectorFeaturePoint(const VectorFeaturePoint &other);
    /**
    * brief 以全面的参数初始化特征点
    */
    void Init(Point2D Pos,S32 ID,F32 Dir,F32 Quality,F32 Value,S32 FeatureDim,S32 LevelNo,F32 Scale);
    /**
    * brief 以常用参数初始化特征点
    */
    void Init(Point2D Pos,F32 Dir,S32 FeatureDim,S32 LevelNo,F32 Scale);
    /**
    * brief 向量形式的用于区分的特征值可以使用此量
    */
    Vector Feature;
    /**
    * brief 所在层数
    */
    S32 LevelNo;
    /**
    * brief 尺度系数
    */
    F32 Scale;
protected:
private:
};

}

#endif // VECTORFEATUREPOINT_H
