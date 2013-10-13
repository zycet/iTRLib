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
 * iohelper.cpp
 *  Created on: 2013-10-9
 *      Author: ghdawn
 */

#include "iohelper.h"
#include "itrbase.h"
#include "stdio.h"

void IOHelper::ReadFromFile(char* filename, ImageGray& img)
{
    //Read File
    FILE* file = fopen(filename, "rb+");
    assert(file!=NULL);
    assert(fseek(file, 0, SEEK_END)==0);
    U32 length = ftell(file);
    assert(length>0);
    fseek(file, 0, SEEK_SET);
    U8* bufferRead = new U8[length];
    MemoryClear(bufferRead, length);
    U32 len = fread(bufferRead, 1, length, file);
    assert(len==length);
    fclose(file);
    //Read Image
    itr_vision::FormatPGM FormatPPMObj;
    itr_vision::IFormat::ImageInfo imageInfo;
    assert(FormatPPMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
    img.Allocate(imageInfo.Width, imageInfo.Height);
    assert(FormatPPMObj.ToImage(bufferRead,length,img)==itr_vision::IFormat::Success);
    delete[] bufferRead;
}

void IOHelper::WriteToFile(char* filename, ImageGray& img)
{
    U8* bufferWrite = new U8[1024 * 1024];
    //Write Image
    S32 length2 = 1024 * 1024;
    itr_vision::FormatPPM FormatPPMObj;
    assert(FormatPPMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
    //Write File
    FILE* file2 = fopen(filename, "wb+");
    assert(file2!=NULL);
    assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
    fflush(file2);
    fclose(file2);
    delete[] bufferWrite;
}
