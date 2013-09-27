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
 * processtest.cc
 *  Created on: 2013-9-27
 *      Author: buaa
 */

#include "processtest.h"
#include <stdio.h>
#include "itrbase.h"
#include "itrvision.h"

void ConvoluteSquareTest()
{
    //Calc Gaussian Filter
    F32 sigma = 1;
    S32 n = itr_vision::GaussianGenerate::SuggestLength(sigma);
    F32* filter = new F32[n];
    itr_vision::GaussianGenerate::Generate(sigma, n, filter);

    //Read File
    FILE* file = fopen("/home/buaa/itrvision/itrvision_test/Debug/table1.ppm", "rb+");
    assert(file!=NULL);
    assert(fseek(file, 0, SEEK_END)==0);
    U32 length = ftell(file);
    assert(length>0);
    fseek(file, 0, SEEK_SET);
    U8* buffer = new U8[length];
    U32 len=fread(buffer, 1, length, file);
    assert(len==length);
    fclose(file);
    //Convert Image
    itr_vision::FormatPPM FormatPPMObj;
    itr_vision::IFormat::ImageInfo imageInfo;
    assert(FormatPPMObj.GetInfo(buffer, length, imageInfo)==itr_vision::IFormat::Success);
    itr_vision::ImageARGB imageARGB(imageInfo.Width, imageInfo.Height);
    assert(FormatPPMObj.ToImage(buffer,length,imageARGB)==itr_vision::IFormat::Success);

    delete buffer;

    //itr_vision::ConvoluteSquare ConvoluteSquareObj(n,);
}
