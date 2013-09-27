/*
 * scale.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef SCALE_H_
#define SCALE_H_

#include "itrbase.h"
#include "../itrvision.h"

namespace itr_vision
{

    class Scale
    {
        public:
            Scale();
            virtual ~Scale();
            static S32 Interpolation(const ImageGray& src, F32 x, F32 y);
            static void Bilinear(const ImageGray& src, ImageGray& dst);
            static void DownSampling(const ImageGray& src, ImageGray& dst,U32 scale);
    };

} /* namespace itr_vision */
#endif /* SCALE_H_ */
