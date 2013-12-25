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
 * image.cc
 *  Created on: 2013-9-25
 *      Author: buaa
 */

#include "itrbase.h"
#include "image.h"

namespace itr_vision
{
    ImageARGB::ImageARGB()
    {
        pixels = NULL;
        width = 0;
        height = 0;
    }
    ImageARGB::ImageARGB(S32 Width, S32 Height)
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
    }

    ImageARGB::ImageARGB(S32 Width, S32 Height, void *Pixels)
    {
        assert(Width>0);
        assert(Height>0);
        assert(Pixels!=NULL);
        this->pixels = static_cast<U32 *>(Pixels);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(U32);
        this->localData = false;
    }

    ImageARGB::~ImageARGB()
    {
        if (this->localData == true)
        {
            delete[] this->pixels;
        }
    }

    ImageGray::ImageGray()
    {
        width = 0;
        height = 0;
        pixels = NULL;
    }
    ImageGray::ImageGray(S32 Width, S32 Height)
    {
        assert(Width>0);
        assert(Height>0);
        this->pixels = new S16[Width * Height]();
        assert(this->pixels!=NULL);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(S16);
        this->localData = true;
    }

    ImageGray::ImageGray(S32 Width, S32 Height, void *Pixels)
    {
        assert(Width>0);
        assert(Height>0);
        assert(Pixels!=NULL);
        this->pixels = static_cast<S16 *>(Pixels);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(S16);
        this->localData = false;
    }

    ImageGray::ImageGray(const ImageGray &Img)
    {
        new(this)ImageGray(Img.GetWidth(),Img.GetHeight(),Img.GetPixels());
    }

    ImageGray &ImageGray::operator =(const ImageGray &Img)
    {
        new(this)ImageGray(Img.GetWidth(),Img.GetHeight(),Img.GetPixels());
        return *this;
    }
    ImageGray::~ImageGray()
    {
        if (this->localData == true)
        {
            delete[] this->pixels;
        }
    }

    void ImageFormatComvert(const ImageARGB &Input, ImageGray &Output)
    {
        assert(Input.MatchWidthHeight(Output.GetWidth(),Output.GetHeight()));
        S32 pixelsNumber = Input.GetPixelsNumber();
        U8 *input = (U8 *) Input.GetPixels();
        S16 *output = Output.GetPixels();
        S32 offset = 0;
        for (int i = 0; i < pixelsNumber; i++)
        {
            output[i] = (input[offset + 0] + input[offset + 1] + input[offset + 1]
                         + input[offset + 2]) >> 2;
            offset += 4;
        }
    }

    void ImageFormatComvert(const ImageGray &Input, ImageARGB &Output, S32 DivOrder)
    {
        assert(Input.MatchWidthHeight(Output.GetWidth(),Output.GetHeight()));
        S32 pixelsNumber = Input.GetPixelsNumber();
        S16 *input = Input.GetPixels();
        U8 *output = (U8 *) Output.GetPixels();
        S32 offset = 0;
        U8 value;
        for (int i = 0; i < pixelsNumber; i++)
        {
            value = GET_IN_RANGE(GET_ABS((input[i]>>DivOrder)),0,255);
            output[offset + 1] = output[offset + 2] = output[offset + 3] = value;
            offset += 4;
        }
    }
} // namespace itr_image


