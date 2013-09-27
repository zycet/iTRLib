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
 * gaussiangenerate.cc
 *  Created on: 2013-9-27
 *      Author: buaa
 */

#include "gaussiangenerate.h"
#include "itrbase.h"

namespace itr_vision
{
    void GaussianGenerate::Generate(F32 Sigma, S32 Length, F32* Data)
    {
        assert(Sigma>0);
        assert(IS_ODD(Length));
        assert(Data!=NULL);
        S32 r = Length >> 1;
        F32 value = 0;
        itr_math::NumericalObj->Sqrt(2 * PI, value);
        F32 base = 1 / (value * Sigma);
        F32 sigma2 = 1 / (GET_SQUARE(Sigma) * 2);
        for (S32 i = 0; i <= r; i++)
        {
            itr_math::NumericalObj->Exp(-GET_SQUARE(r-i) * sigma2, value);
            value *= base;
            Data[i] = Data[Length - 1 - i] = value;
        }
    }

    S32 GaussianGenerate::SuggestLength(F32 Sigma)
    {
        const F32 Sample = 3.5;
        S32 r =0;
        itr_math::NumericalObj->Round(Sample * Sigma,r);
        return (r * 2 + 1);
    }

} // namespace itr_image

