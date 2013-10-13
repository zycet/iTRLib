/*
 * scale.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef SCALE_H_
#define SCALE_H_

#include "itrbase.h"
#include "../image/image.h"

namespace itr_vision
{

    class Scale
    {
        public:
            Scale();
            virtual ~Scale();
            static S16 Interpolation(const ImageGray& src, F32 x, F32 y);
            static S32 Interpolation(const ImageARGB& src, F32 x, F32 y);
            static void Bilinear(const ImageGray& src, ImageGray& dst);
            static void Bilinear(const ImageARGB& src, ImageGray& dst);
            static void SubSampling(const ImageGray& src, ImageGray& dst, S32 scale);
            static void SubSampling(const ImageARGB& src, ImageARGB& dst, S32 scale);
    };

} /* namespace itr_vision */
#endif /* SCALE_H_ */
