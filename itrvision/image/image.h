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
 * image.h
 *  Created on: 2013-9-25
 *      Author: buaa
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "itrbase.h"

namespace itr_image
{
    /*
     * A,R,G,B 4 Channel
     * PixelSize=4
     * PixelType=0
     */
    union ColorARGB
    {
            U32 Value;
            U8 A, R, G, B;
    };

    /*
     * Gray 1 Channel
     * PixelSize=2
     * PixelType=1
     */
    union ColorGray
    {
            U16 Value;
            S16 Gray;
    };

    class Image
    {
        public:
            Image(S32 Width, S32 Height, S32 PixelSize, S32 PixelType);
            Image(S32 Width, S32 Height, S32 PixelSize, S32 PixelType, void* Pixels);
            virtual ~Image();
            inline U8* GetPixels() const
            {
                return pixels;
            }
            inline U8* GetPixel(S32 Y, S32 X) const
            {
                S32 offset = Y * this->width + X;
                offset *= this->pixelSize;
                return (pixels + offset);
            }
            inline S32 GetWidth() const
            {
                return width;
            }
            inline S32 GetHeight() const
            {
                return height;
            }
            inline S32 GetPixelSize() const
            {
                return pixelSize;
            }
            inline S32 GetPixelType() const
            {
                return pixelType;
            }
            inline S32 GetPixelsNumber() const
            {
                return pixelsNumber;
            }
            inline S32 GetPixelsLength() const
            {
                return pixelsLength;
            }
            inline BOOL MatchWidthHeight(const Image& Img) const
            {
                return (this->width == Img.GetWidth() && this->height == Img.GetHeight());
            }
            inline BOOL MatchWidthHeight(S32 Width, S32 Height) const
            {
                return (this->width == Width && this->height == Height);
            }
            BOOL CovertTypeTo(Image& ImgOutput) const;

        private:
            U8* pixels;
            S32 width;
            S32 height;
            S32 pixelSize;
            S32 pixelType;
            S32 pixelsNumber;
            S32 pixelsLength;
            BOOL localData;
    };

} // namespace itr_image
#endif // IMAGE_H_
