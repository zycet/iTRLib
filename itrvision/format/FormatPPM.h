/*
 * FormatPPM.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef FORMATPPM_H_
#define FORMATPPM_H_

#include "iformat.h"

namespace itr_vision
{
    class FormatPPM: public itr_vision::IFormat
    {
        public:
            FormatPPM();
            virtual ~FormatPPM();
            virtual ConvertResult GetInfo(U8* Data, S32 Length, ImageInfo& ImgInfo)=0;
            virtual ConvertResult ToImage(U8* Data, S32 Length, ImageARGB& Img)=0;
            virtual ConvertResult ToImage(U8* Data, S32 Length, ImageGray& Img)=0;
            virtual ConvertResult ToBinary(ImageARGB& Img, U8* Data, S32& Length)=0;
            virtual ConvertResult ToBinary(ImageGray& Img, U8* Data, S32& Length)=0;
    };
} // namespace itr_vision

#endif // FORMATPPM_H_
