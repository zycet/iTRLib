/**
*\ Rectangle 选择图像中的矩形存入新图

 */

#ifndef PICK_H_
#define PICK_H_
#include "itrbase.h"
#include "../itrvision.h"
using itr_math::RectangleS;
using itr_math::Matrix;

namespace itr_vision
{

    class Pick
    {
        public:
            static void Rectangle(const ImageARGB &ImgInput,RectangleS &rect,ImageARGB &ImgOutput);
            static void Rectangle(const Matrix &ImgInput,RectangleS &rect,Matrix &ImgOutput);
    };

} // namespace itr_vision
#endif // PICK_H_
