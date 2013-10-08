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
 * tracker.cc
 *  Created on: 2013-9-29
 *      Author: ghdawn
 */

#include "lktracker.h"

namespace itr_vision
{

    LKTracker::LKTracker(const ImageGray& img1, const ImageGray& img2)
    {
        int width = img1.GetWidth();
        int height=img1.GetHeight();
        I[0].Allocate(width, height);
        I[1](width >> 1, height >> 1);
        I[2](width >> 2, height >> 2);
        J[0].Allocate(width, height);
        J[1](width >> 1, height >> 1);
        J[2](width >> 2, height >> 2);
        GeneratePyramidal(img1, I, 3);
        GeneratePyramidal(img2, J, 3);
    }

    LKTracker::~LKTracker()
    {
        // TODO Auto-generated destructor stub
    }

    void LKTracker::GeneratePyramidal(const ImageGray& img, ImageGray py[], S32 length)
    {
        --length;
        MemoryCopy(py[0].GetPixels(),img.GetPixels(),img.GetPixelsNumber());
        for (; length > 0; --length)
            Scale::Bilinear(img, py[length]);
    }

} // namespace itr_vision
