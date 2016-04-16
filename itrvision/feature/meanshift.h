//
// Created by gaohan02 on 15-6-1.
//

#ifndef EXP_MEANSHIFT_H
#define EXP_MEANSHIFT_H
#include "itrbase.h"
namespace itr_vision
{
    class MeanShift
    {
    public:
        static const int IMG_GRAY;
        static const int IMG_RGB;

        void Init(const itr_math::Matrix &img, const itr_math::RectangleF &rect, int binCount);

        void Go(const itr_math::Matrix &img, itr_math::RectangleF &rect);

        void ChangeFormat(itr_math::Matrix &img);
    private:
        float getweight(int x, int y);

        itr_math::Matrix weight;
        itr_math::Vector histq;
        int halfx, halfy;
        float radius;
        int binCount;


    };

}
#endif //EXP_MEANSHIFT_H
