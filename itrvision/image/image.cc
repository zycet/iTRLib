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
    ImageARGB::ImageARGB(S32 Width, S32 Height)
    {
        assert(Width>0);
        assert(Height>0);
        this->pixels = new U32[Width * Height];
        assert(this->pixels!=NULL);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(U32);
        this->localData = true;
    }

    ImageARGB::ImageARGB(S32 Width, S32 Height, void* Pixels)
    {
        assert(Width>0);
        assert(Height>0);
        assert(Pixels!=NULL);
        this->pixels = static_cast<U32*>(Pixels);
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
            delete this->pixels;
        }
    }

    ImageGray::ImageGray(S32 Width, S32 Height)
    {
        assert(Width>0);
        assert(Height>0);
        this->pixels = new S16[Width * Height];
        assert(this->pixels!=NULL);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(S16);
        this->localData = true;
    }

    ImageGray::ImageGray(S32 Width, S32 Height, void* Pixels)
    {
        assert(Width>0);
        assert(Height>0);
        assert(Pixels!=NULL);
        this->pixels = static_cast<S16*>(Pixels);
        this->width = Width;
        this->height = Height;
        this->pixelsNumber = Width * Height;
        this->pixelsLength = Width * Height * sizeof(S16);
        this->localData = false;
    }

    ImageGray::~ImageGray()
    {
        if (this->localData == true)
        {
            delete this->pixels;
        }
    }
} // namespace itr_image
