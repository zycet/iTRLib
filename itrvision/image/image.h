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

namespace itr_vision
{
    /*
     * Alpha,Red,Green,Blue
     */
    struct ARGB
    {
            U8 A, R, G, B;
    };

    /*
     * A,R,G,B 4 Channel
     * PixelSize=4
     */
    union ColorARGB
    {
            U32 Value;
            ARGB Color;
    };

    /*
     * Gray 1 Channel
     * PixelSize=2
     */
    union ColorGray
    {
            U16 Value;
            S16 Gray;
    };

    class ImageARGB
    {
        public:
            ImageARGB(S32 Width, S32 Height);
            ImageARGB(S32 Width, S32 Height, void* Pixels);
            virtual ~ImageARGB();
            inline ColorARGB* GetPixels()
            {
                return pixels;
            }
            inline ColorARGB* GetPixel(S32 Y, S32 X)
            {
                assert(X < this->width);
                assert(Y < this->height);
                return &this->pixels[Y * this->width + X];
            }
            inline ColorARGB& operator[](int index)
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline ColorARGB operator[](int index) const
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline ColorARGB& operator()(int Y, int X)
            {
                assert(X < this->width);
                assert(Y < this->height);
                return this->pixels[Y * this->width + X];
            }
            inline ColorARGB operator()(int Y, int X) const
            {
                assert(X < this->width);
                assert(Y < this->height);
                return this->pixels[Y * this->width + X];
            }

            inline S32 GetWidth() const
            {
                return width;
            }
            inline S32 GetHeight() const
            {
                return height;
            }
            inline S32 GetPixelsNumber() const
            {
                return pixelsNumber;
            }
            inline S32 GetPixelsLength() const
            {
                return pixelsLength;
            }
            inline BOOL MatchWidthHeight(const ImageARGB& Img) const
            {
                return (this->width == Img.GetWidth() && this->height == Img.GetHeight());
            }
            inline BOOL MatchWidthHeight(S32 Width, S32 Height) const
            {
                return (this->width == Width && this->height == Height);
            }

        private:
            ColorARGB* pixels;
            S32 width;
            S32 height;
            S32 pixelsNumber;
            S32 pixelsLength;
            BOOL localData;
    };
    class ImageGray
        {
            public:
            ImageGray(S32 Width, S32 Height);
            ImageGray(S32 Width, S32 Height, void* Pixels);
                virtual ~ImageGray();
                inline ColorGray* GetPixels()
                {
                    return pixels;
                }
                inline ColorGray* GetPixel(S32 Y, S32 X)
                {
                    assert(X < this->width);
                    assert(Y < this->height);
                    return &this->pixels[Y * this->width + X];
                }
                inline ColorGray& operator[](int index)
                {
                    assert(index < this->pixelsNumber);
                    return this->pixels[index];
                }
                inline ColorGray operator[](int index) const
                {
                    assert(index < this->pixelsNumber);
                    return this->pixels[index];
                }
                inline ColorGray& operator()(int Y, int X)
                {
                    assert(X < this->width);
                    assert(Y < this->height);
                    return this->pixels[Y * this->width + X];
                }
                inline ColorGray operator()(int Y, int X) const
                {
                    assert(X < this->width);
                    assert(Y < this->height);
                    return this->pixels[Y * this->width + X];
                }

                inline S32 GetWidth() const
                {
                    return width;
                }
                inline S32 GetHeight() const
                {
                    return height;
                }
                inline S32 GetPixelsNumber() const
                {
                    return pixelsNumber;
                }
                inline S32 GetPixelsLength() const
                {
                    return pixelsLength;
                }
                inline BOOL MatchWidthHeight(const ImageARGB& Img) const
                {
                    return (this->width == Img.GetWidth() && this->height == Img.GetHeight());
                }
                inline BOOL MatchWidthHeight(S32 Width, S32 Height) const
                {
                    return (this->width == Width && this->height == Height);
                }

            private:
                ColorGray* pixels;
                S32 width;
                S32 height;
                S32 pixelsNumber;
                S32 pixelsLength;
                BOOL localData;
        };
} // namespace itr_image
#endif // IMAGE_H_
