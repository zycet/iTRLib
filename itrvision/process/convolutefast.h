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
 * convolutefast.h
 *  Created on: 2014-1-19
 *      Author: buaa
 */

#ifndef CONVOLUTEFAST_H_
#define CONVOLUTEFAST_H_

#include "itrbase.h"
#include "../image/image.h"

using itr_math::Matrix;

namespace itr_vision
{
    class ConvoluteFast
    {
        public:
            ConvoluteFast();
            virtual ~ConvoluteFast();
            void Init(S32 FilterN, S32 ColN, S32 RowN);
            void Convolute(const Matrix &Input, F32 *Filter, Matrix &Output);
            void ConvoluteHoriz(const Matrix &Input, F32 *Filter, Matrix &Output);
            void ConvoluteVert(const Matrix &Input, F32 *Filter, Matrix &Output);
        private:
            S32 colN,rowN;
            S32 filterN;
            //F32* rowBuffer;
            F32* calcBuffer;
            Matrix* temp;
    };

} // namespace itr_image
#endif // CONVOLUTESQUARE_H_
