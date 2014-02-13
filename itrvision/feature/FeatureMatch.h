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
        *特征向量匹配函数
        *输入：vectorfeaturepoint1[],vectorfeaturepoint2[],已知的两组特征点
        *     num1,num2,两组特征点的长度。
        *
        *输出：vectorfeaturepoint ID
        */
        void FeatureMatchDo(VectorFeaturePoint vectorfeaturepoint1[],S32 num1,
            VectorFeaturePoint vectorfeaturepoint2[],S32 num2,S32 matchnum,Point2D pos1[],Point2D pos2[]);
    protected:
    private:
};
}
#endif // FEATUREMATCH_H
