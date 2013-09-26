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
    Image::Image(S32 Width, S32 Height, S32 PixelSize, S32 PixelType)
    {
        assert(Width>0);
        assert(Height>0);
        assert(PixelSize>0);
        this->pixels = new U8[Width * Height * pixelSize];
        assert(this->pixels!=NULL);
        this->width = Width;
        this->height = Height;
        this->pixelSize = PixelSize;
        this->pixelType = PixelType;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * pixelSize;
        this->localData = true;
    }

    Image::Image(S32 Width, S32 Height, S32 PixelSize, S32 PixelType, void* Pixels)
    {
        assert(Width>0);
        assert(Height>0);
        assert(PixelSize>0);
        assert(Pixels!=NULL);
        this->pixels = static_cast<U8*>(Pixels);
        this->width = Width;
        this->height = Height;
        this->pixelSize = PixelSize;
        this->pixelType = PixelType;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * pixelSize;
        this->localData = false;
    }

    Image::~Image()
    {
        if (this->localData == true)
        {
            delete this->pixels;
        }
    }

    BOOL Image::CovertTypeTo(Image& ImgOutput) const
    {
        assert(this->MatchWidthHeight(ImgOutput));
        if (this->GetPixelType() == 0 && ImgOutput.GetPixelType() == 1)
        {
            assert(false);

        }
        else if (this->GetPixelType() == 1 && ImgOutput.GetPixelType() == 0)
        {
            assert(false);
        }
        else
        {
            return false;
        }
        return true;
    }

} // namespace itr_image
