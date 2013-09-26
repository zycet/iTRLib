/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * iformat.h
 *  Created on: 2013-9-25
 *      Author: buaa
 */

#ifndef IFORMAT_H_
#define IFORMAT_H_

#include "itrbase.h"
#include "image.h"

namespace itr_image
{

    class IFormat
    {
        public:
            enum ConvertResult
            {
                Success = 0,
                LengthIllegal=1,
                FormatIllegal=2
            };
            struct ImageInfo
            {
                    S32 Width;
                    S32 Height;
                    S32 PixelSize;
                    S32 ColorChannel;
            };
            IFormat();
            virtual ~IFormat();
            virtual ConvertResult GetInfo(const U8* Data, S32 Length, ImageInfo& ImgInfo)=0;
            virtual ConvertResult ToImage(const U8* Data, S32 Length, Image& Img)=0;
            virtual ConvertResult ToBinary(const Image& Img, U8* Data, S32& Length)=0;
    };

} // namespace itr_image
#endif // IFORMAT_H_
