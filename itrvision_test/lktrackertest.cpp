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
 * lktrackertest.cpp
 *  Created on: 2013-10-9
 *      Author: ghdawn
 */

#include "lktrackertest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <stdio.h>
#include <vector>
using std::vector;
void lktest()
{
    ImageGray  gray1, gray2;
    IOHelper::ReadFromFile("Debug/img0.pgm", gray1);
    IOHelper::ReadFromFile("Debug/img1.pgm", gray2);
    SelectFeature select(gray1, 7);
    vector<FeaturePoint> fl(100);
    RectangleS rect(0, 0, gray1.GetWidth(), gray1.GetHeight());
    select.SelectGoodFeature(rect, fl);
    LKTracker tracker(gray1, gray2);
    vector<FeaturePoint>::iterator feat = fl.begin();
    int i = 0;
    while (feat != fl.end())
    {
        Draw::Circle(gray1, feat->x, feat->y, 2, 255);
        printf("Feature:%d at(%d,%d) with %d\n", i++, feat->x, feat->y, feat->value);
        ++feat;
    }
    tracker.Compute(fl, true);
    feat = fl.begin();
    i = 0;
    while (feat != fl.end())
    {
        if (feat->value > 0)
        {
            Draw::Circle(gray2, feat->x, feat->y, 2, 255);
            printf("Feature:%d at(%d,%d) with %d\n", i++, feat->x, feat->y, feat->value);
        }
        ++feat;
    }
    IOHelper::WriteToFile("Debug/gray1.ppm", gray1);
    IOHelper::WriteToFile("Debug/gray2.ppm", gray2);
}
