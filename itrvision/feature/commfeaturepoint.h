#ifndef COMMFEATUREPOINT_H
#define COMMFEATUREPOINT_H

#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{
/*
    通用特征点表示类
*/
class CommFeaturePoint:public Point2D
{
public:
    /*
        建立空的特征点,需要执行Init后才可使用.
    */
    CommFeaturePoint();
    /*
        释放占用的资源
    */
    virtual ~CommFeaturePoint();
    /*
        对象深复制(要求特征维度一致)
    */
    CommFeaturePoint(const CommFeaturePoint& other);
    /*
        以全面的参数初始化特征点
    */
    void Init(Point2D Pos,S32 ID,F32 Dir,F32 Quality,F32 Value);
    /*
        面向一般特征点算法的特征点建立(光流,角点等),可继续添加类似方法.
    */
    void Init(Point2D Pos,F32 Quality,F32 Value);
    /*
        重载符，比较大小
    */
    inline bool operator>(CommFeaturePoint cfpoint)
    {
        return this->Quality>cfpoint.Quality;
    }
    inline bool operator<(CommFeaturePoint cfpoint)
    {
        return this->Quality<cfpoint.Quality;
    }
    /*
        用来进行区分或者反向索引的标示
    */
    S32 ID;
    /*
        用以指向附加数据
    */
    void* Tag;
    /*
        方向(采用角度制,从+X轴算起,指向+Y轴为正方向)
    */
    F32 Dir;
    /*
        质量,用于表示此特征点的有效性,各算法可采用不同设计,一般上值越大质量越高.
    */
    F32 Quality;
    /*
        如算法包含一个标量形式的用于区分的特征值可以使用此量
    */
    F32 Value;

    /*
        比较两个特征点的有效性。即比较Quality
    */
    bool operator<(const CommFeaturePoint& other) const;
    bool operator>(const CommFeaturePoint& other) const;
protected:
private:
};
}
#endif // COMMFEATUREPOINT_H
