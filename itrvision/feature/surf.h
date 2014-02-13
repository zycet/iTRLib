#ifndef SURF_H
#define SURF_H

#include "itrbase.h"
#include "vectorfeaturepoint.h"
#include <vector>


using namespace itr_math;

namespace itr_vision
{
    /**
    * /brief 此类实现了SURF算法
    * /note 图像数据基于itr_math::Matrix类型,全部为单精度浮点计算.
    * /note 运算过程尽量基于itr_math::Calculate中的方法,从而实现了计算方式的可替代优化.
    * /note 后期会考虑进行对ARM-Neon的汇编优化.
    */
    class SURF
    {
        public:
            /**
            * /brief 完成对象构造后必须调用Init()才能正常工作.
            */
            SURF();
            /**
            * /brief 释放动态申请的内存
            */
            virtual ~SURF();
        protected:
        private:
        void getOrientation();
        void getDescriptor(bool bUpright = false);
        inline float gaussian(int x, int y, float sig);
        inline float gaussian(float x, float y, float sig);
        inline float haarX(int row, int column, int size);
        inline float haarY(int row, int column, int size);
        float getAngle(float X, float Y);

        Matrix Input;
        VectorFeaturePoint ipts;
        int index;
    };
}
#endif // SURF_H
