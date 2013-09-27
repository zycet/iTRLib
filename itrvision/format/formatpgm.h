/*
 * FormatPGM.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef FORMATPGM_H_
#define FORMATPGM_H_

#include "iformat.h"
#include <sstream>
#include <math.h>
#include <assert.h>
using std::stringstream;
#include "itrbase.h"

namespace itr_vision
{
    class FormatPGM: public itr_vision::IFormat
    {
        public:
            FormatPGM();
            virtual ~FormatPGM();
            virtual ConvertResult GetInfo(U8* Data, S32 Length, ImageInfo& ImgInfo)=0;
            virtual ConvertResult ToImage(U8* Data, S32 Length, ImageARGB& Img)=0;
            virtual ConvertResult ToImage(U8* Data, S32 Length, ImageGray& Img)=0;
            virtual ConvertResult ToBinary(ImageARGB& Img, U8* Data, S32& Length)=0;
            virtual ConvertResult ToBinary(ImageGray& Img, U8* Data, S32& Length)=0;
    };
} // namespace itr_vision
#endif // FORMATPGM_H_
