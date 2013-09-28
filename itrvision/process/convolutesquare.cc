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
 * convolutesquare.cc
 *  Created on: 2013-9-27
 *      Author: buaa
 */

#include "convolutesquare.h"
#include "itrbase.h"
#include "../image/image.h"

namespace itr_vision
{
    ConvoluteSquare::ConvoluteSquare(S32 FilterDim, S32 Width, S32 Height)
    {
        assert(FilterDim>0);
        assert(IS_ODD(FilterDim));
        assert(Width>=FilterDim);
        assert(Height>=FilterDim);
        this->multBufferS16 = new S16[FilterDim];
        this->imageBufferS16 = new S16[Width * Height];
        this->width = Width;
        this->height = Height;
        this->filterDim = FilterDim;
        this->r = FilterDim >> 1;
    }

    ConvoluteSquare::~ConvoluteSquare()
    {
        delete this->multBufferS16;
        delete this->imageBufferS16;
    }

    void FillMultBufferRow(S16* Data, S32 Width, S32 X, S32 Y, S32 R, S16* Buffer)
    {
        S32 offset = Y * Width + X - R;
        MemoryCopy(Buffer, &Data[offset], sizeof(S16) * (R * 2 + 1));
    }

    void FillMultBufferCol(S16* Data, S32 Width, S32 X, S32 Y, S32 R, S16* Buffer)
    {
        S32 offset = (Y - R) * Width + X;
        S32 d = R * 2 + 1;

        for (S32 i = 0; i < d; i++)
        {
            Buffer[i] = Data[offset];
            offset += Width;
        }
    }

    void ConvoluteSquare::Convolute(const ImageGray& Input, F32* Filter, ImageGray& Output)
    {
        assert(Input.MatchWidthHeight(width,height));
        assert(Output.MatchWidthHeight(width,height));
        assert(Filter!=NULL);
        //S16* input = Input.GetPixels();
        S16* output = Output.GetPixels();
        S16* tempP = NULL;
        S16 value = 0;
        for (S32 y = 0; y < height; y++)
        {
            for (S32 x = r; x < width - r; x++)
            {
                tempP = Input.GetPixel(y, x - r);
                //FillMultBufferRow(input, width, x, y, r, multBufferS16);
                itr_math::CalculateObj->MultiSum(tempP, Filter, filterDim, value);
                imageBufferS16[y * width + x] = value;
            }
        }
        for (S32 y = r; y < height - r; y++)
        {
            for (S32 x = r; x < width - r; x++)
            {
                FillMultBufferCol(imageBufferS16, width, x, r, r, multBufferS16);
                itr_math::CalculateObj->MultiSum(multBufferS16, Filter, filterDim, value);
                output[y * width + x] = value;
            }
        }
    }
} // namespace itr_image
