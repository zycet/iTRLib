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
#include <time.h>
#include "itrbase.h"
#include "itrvision.h"

void ConvoluteSquareTest()
{/*
    //Read File
    FILE* file = fopen("Debug/table1.ppm", "rb+");
    assert(file!=NULL);
    assert(fseek(file, 0, SEEK_END)==0);
    U32 length = ftell(file);
    assert(length>0);
    fseek(file, 0, SEEK_SET);
    U8* buffer = new U8[length];
    U32 len = fread(buffer, 1, length, file);
    assert(len==length);
    fclose(file);
    //Read Image
    itr_vision::FormatPPM FormatPPMObj;
    itr_vision::IFormat::ImageInfo imageInfo;
    assert(FormatPPMObj.GetInfo(buffer, length, imageInfo)==itr_vision::IFormat::Success);
    itr_vision::ImageARGB imageARGB(imageInfo.Width, imageInfo.Height);
    assert(FormatPPMObj.ToImage(buffer,length,imageARGB)==itr_vision::IFormat::Success);

    //Convert Gray
    itr_vision::ImageGray imageGray(imageInfo.Width, imageInfo.Height);
    itr_vision::ImageFormatComvert(imageARGB, imageGray);
    itr_vision::ImageFormatComvert(imageGray, imageARGB, 0);
    itr_vision::ImageFormatComvert(imageARGB, imageGray);
    //Calc Gaussian Filter
    F32 sigma = 1;
    S32 n = itr_math::GaussianGenerate::SuggestLength(sigma);
    F32* filter = new F32[n];
    itr_math::GaussianGenerate::Generate(sigma, n, filter);
    //Convolute
    itr_vision::ImageGray imageGrayResult(imageInfo.Width, imageInfo.Height);
    itr_vision::ConvoluteSquare ConvoluteSquareObj(n, imageARGB.GetWidth(), imageARGB.GetHeight());
    ConvoluteSquareObj.Convolute(imageGray, filter, imageGrayResult);
    delete filter;
    //Write Image
    S32 length2 = length;
    assert(FormatPPMObj.ToBinary(imageGrayResult, buffer, length2)==itr_vision::IFormat::Success);
    //Write File
    FILE* file2 = fopen("Debug/table1_.ppm", "wb+");
    assert(file2!=NULL);
    assert(fwrite(buffer,1,length2,file2)==(U32)length2);
    fclose(file2);
    delete buffer;
  */
}

void ConvoluteSquareTest4Pro()
{/*
    //Calc Gaussian Filter
    const S32 N = 9;
    const F32 sigma = 1;
    F32 filter[N];
    itr_math::GaussianGenerate::Generate(sigma, N, filter);
    for (S32 i = 0; i < N; i++)
    {
        filter[i] = 1;
    }
    //Create Image
    //const S32 Width = 685;
    //const S32 Height = 494;
    const S32 Width = 200;
    const S32 Height = 200;
    itr_vision::ImageGray imageGray1(Width, Height);
    itr_vision::ImageGray imageGray2(Width, Height);
    S16* p = imageGray1.GetPixels();
    for (S32 i = 0; i < imageGray1.GetPixelsNumber(); i++)
    {
        p[i] = 1;
    }
    //Init ConvoluteSquare
    itr_vision::ConvoluteSquare ConvoluteSquareObj(N, Width, Height);
    //Calc Convolute
    clock_t startClock = clock();
    for (S32 i = 0; i < 10; i++)
    {
        ConvoluteSquareObj.Convolute(imageGray1, filter, imageGray2);
    }
    clock_t endClock = clock();
    double timeSpan = ((double) (endClock - startClock)) / CLOCKS_PER_SEC * 1000;
    PRINT_INFO(timeSpan);
    */
}

void FormatPPMTestPGMTest3()
{
/*
    //Read File
    FILE* file = fopen("Debug/table1.ppm", "rb+");
    assert(file!=NULL);
    assert(fseek(file, 0, SEEK_END)==0);
    U32 length = ftell(file);
    assert(length>0);
    fseek(file, 0, SEEK_SET);
    U8* bufferRead = new U8[length];
    U8* bufferWrite = new U8[1024 * 1024];
    MemoryClear(bufferRead, length);
    U32 len = fread(bufferRead, 1, length, file);
    assert(len==length);
    fclose(file);
    //Read Image
    itr_vision::FormatPPM FormatPPMObj;
    itr_vision::FormatPGM FormatPGMObj;
    itr_vision::IFormat::ImageInfo imageInfo;
    assert(FormatPPMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
    itr_vision::ImageGray imageGray(imageInfo.Width, imageInfo.Height);
    itr_vision::ImageARGB imageARGB(imageInfo.Width, imageInfo.Height);
    assert(FormatPPMObj.ToImage(bufferRead,length,imageARGB)==itr_vision::IFormat::Success);
    MemoryClear(bufferRead, length);
    //Write Image
    S32 length2 = 1024 * 1024;
    assert(FormatPGMObj.ToBinary(imageARGB, bufferWrite, length2)==itr_vision::IFormat::Success);
    //Write File
    FILE* file2 = fopen("Debug/table1_.pgm", "wb+");
    assert(file2!=NULL);
    assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
    fflush(file2);
    fclose(file2);
    delete[] bufferRead;
    */
}

