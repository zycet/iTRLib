#ifndef FEATUREMATCH_H
#define FEATUREMATCH_H
#include "itrbase.h"
#include "../itrvision.h"

using itr_math::Point2D;

using itr_vision::VectorFeaturePoint;
namespace itr_vision
{
class FeatureMatch
{
public:
    FeatureMatch();
    virtual ~FeatureMatch();
    /**
      * \brief 特征向量匹配函数
      * \param vectorfeaturepoint1[] 特征点1
      * \param vectorfeaturepoint2[] 特征点2
      * \param num1 特征点长度1
      * \param num2 特征点长度2
      * \param matchnum 匹配的ID
      * \param pos1[] 坐标1
      * \param pos2[] 坐标2
      */
    void FeatureMatchDo(VectorFeaturePoint vectorfeaturepoint1[],S32 num1,
                        VectorFeaturePoint vectorfeaturepoint2[],S32 num2,S32 matchnum,Point2D pos1[],Point2D pos2[]);
protected:
private:
};
}
#endif // FEATUREMATCH_H
