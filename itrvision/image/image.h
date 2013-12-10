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

    class ImageARGB
    {
        public:
            ImageARGB();
            ImageARGB(S32 Width, S32 Height);
            ImageARGB(S32 Width, S32 Height, void* Pixels);
            ImageARGB(const ImageARGB& Img);
            virtual ~ImageARGB();
            inline bool Allocate(S32 Width, S32 Height)
            {
                if (pixels == NULL)
                {
                    assert(Width>0);
                    assert(Height>0);
                    this->pixels = new U32[Width * Height]();
                    assert(this->pixels!=NULL);
                    this->width = Width;
                    this->height = Height;
                    this->pixelsNumber = Width * Height;
                    this->pixelsLength = Width * Height * sizeof(U32);
                    this->localData = true;
                    return true;
                }
                else
                    return false;
            }
            inline U32* GetPixels() const
            {
                return pixels;
            }
            inline U32* GetPixel(S32 Y, S32 X) const
            {
                assert(X < this->width);
                assert(Y < this->height);
                return &this->pixels[Y * this->width + X];
            }
            inline U32& operator[](int index)
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline U32 operator[](int index) const
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline U32& operator()(int Y, int X)
            {
                if (X < 0)
                    X = 0;
                if (Y < 0)
                    Y = 0;
                if (Y >= height)
                    Y = height - 1;
                if (X >= width)
                    X = width - 1;
                assert(X < this->width);
                assert(Y < this->height);
                return this->pixels[Y * this->width + X];
            }
            inline U32 operator()(int Y, int X) const
            {
                if (X < 0)
                    X = 0;
                if (Y < 0)
                    Y = 0;
                if (Y >= height)
                    Y = height - 1;
                if (X >= width)
                    X = width - 1;
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
            U32* pixels;
            S32 width;
            S32 height;
            S32 pixelsNumber;
            S32 pixelsLength;
            BOOL localData;
    };
    class ImageGray
    {
        public:
            ImageGray();
            ImageGray(S32 Width, S32 Height);
            ImageGray(S32 Width, S32 Height, void* Pixels);
            ImageGray(const ImageGray& Img);
            virtual ~ImageGray();
            inline BOOL Allocate(S32 Width, S32 Height)
            {
                if (pixels == NULL)
                {
                    pixels = new S16[Width * Height]();
                    assert(this->pixels!=NULL);
                    this->width = Width;
                    this->height = Height;
                    this->pixelsNumber = Width * Height;
                    this->pixelsLength = Width * Height * sizeof(S16);
                    this->localData = true;
                    return true;
                }
                else
                    return false;
            }
            inline S16* GetPixels() const
            {
                return pixels;
            }
            inline S16* GetPixel(S32 Y, S32 X) const
            {
                assert(X < this->width);
                assert(Y < this->height);
                return &this->pixels[Y * this->width + X];
            }
            ImageGray& operator=(const ImageGray& Img);
            inline S16& operator[](int index)
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline S16 operator[](int index) const
            {
                assert(index < this->pixelsNumber);
                return this->pixels[index];
            }
            inline S16& operator()(int Y, int X)
            {
                // TODO 待商议
                if (X < 0)
                    X = 0;
                if (Y < 0)
                    Y = 0;
                if (Y >= height)
                    Y = height - 1;
                if (X >= width)
                    X = width - 1;
                assert(X < this->width);
                assert(Y < this->height);
                return this->pixels[Y * this->width + X];
            }
            inline S16 operator()(int Y, int X) const
            {
                // TODO 待商议
                if (X < 0)
                    X = 0;
                if (Y < 0)
                    Y = 0;
                if (Y >= height)
                    Y = height - 1;
                if (X >= width)
                    X = width - 1;
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
            inline BOOL MatchWidthHeight(const ImageGray& Img) const
            {
                return (this->width == Img.GetWidth() && this->height == Img.GetHeight());
            }
            inline BOOL MatchWidthHeight(S32 Width, S32 Height) const
            {
                return (this->width == Width && this->height == Height);
            }

        private:
            S16* pixels;
            S32 width;
            S32 height;
            S32 pixelsNumber;
            S32 pixelsLength;
            BOOL localData;
    };

    void ImageFormatComvert(const ImageARGB& Input, ImageGray& Output);
    void ImageFormatComvert(const ImageGray& Input, ImageARGB& Output, S32 DivOrder);
} // namespace itr_image
#endif // IMAGE_H_
