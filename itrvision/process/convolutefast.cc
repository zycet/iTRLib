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

#include "convolutefast.h"
#include "itrbase.h"
#include <math.h>
#include "../image/image.h"

namespace itr_vision
{
    ConvoluteFast::ConvoluteFast()
    {
        this->colN=0;
        this->rowN=0;
        this->filterN=0;
        this->calcBuffer=NULL;
    }


    ConvoluteFast::~ConvoluteFast()
    {
        if(this->calcBuffer!=NULL)
        {
            delete this->calcBuffer;
        }
    }

    void ConvoluteFast::Init(S32 FilterN, S32 ColN, S32 RowN)
    {
        assert(FilterN>0);
        assert(IS_ODD(FilterN));
        assert(ColN>=FilterN);
        assert(RowN>=FilterN);
        assert(this->calcBuffer==NULL);
        this->calcBuffer=new F32[RowN];
        this->colN=ColN;
        this->rowN=RowN;
        this->filterN=FilterN;
        this->temp=new Matrix(RowN,ColN);
    }


    void ConvoluteFast::Convolute(const Matrix &Input, F32 *Filter, Matrix &Output)
    {
        ConvoluteHoriz(Input,Filter,*temp);
        ConvoluteVert(*temp,Filter,Output);
    }

    void ConvoluteFast::ConvoluteHoriz(const Matrix &Input, F32 *Filter, Matrix &Output)
    {
        S32 r = (filterN -1)/2;
        F32 tempmal=0;
        F32* Finput =Input.GetData();
        S32 pos=0;
        for(S32 row =0; row<rowN ; row++)
        {
            for(S32 col =r; col<colN - r; col++)
            {
                itr_math::CalculateObj->MultiSum(Finput+pos+col-r, Filter, filterN, tempmal);
                Output[pos+col] =tempmal;
            }
            pos+= colN;
        }
    }

    void ConvoluteFast::ConvoluteVert(const Matrix &Input, F32 *Filter, Matrix &Output)
    {
        S32 r = (filterN -1)/2;
        F32 tempmal=0;
        S32 pos0=r*colN;
        S32 pos=pos0;
        for(S32 col=0; col<colN; col++)
        {
            pos = pos0+col;
            Input.CopyColTo(col, calcBuffer);
            for(S32 row =r; row<rowN-r; row++)
            {
                itr_math::CalculateObj->MultiSum(calcBuffer+row-r, Filter, filterN, tempmal);
                Output[pos] =tempmal;
                pos+=colN;
            }

        }
    }
} // namespace itr_image

