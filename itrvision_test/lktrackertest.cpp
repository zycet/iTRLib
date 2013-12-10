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
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
using std::endl;
using std::cout;
using std::vector;
void lktest()
{
    lktest2Img();
    lkseq();
}
void lkseq()
{
    char file[25];
    ImageGray gray;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    SelectFeature select(gray, 7);
    vector<FeaturePoint> flU(100), flV(100), flU2(100);
    RectangleS rect(210, 240, 100, 150);
    select.mindist=5;
    select.SelectGoodFeature(rect, flU);
    LKTracker tracker(gray);

    for (int k = 1; k < 200; ++k)
    {
        sprintf(file, "Debug/green/cap%03d.pgm", k);
        IOHelper::ReadPGMFile(file, gray);
        int start = clock() / 1000;
        tracker.AddNext(gray);
        tracker.Compute(flU, flV, true);
        tracker.Compute(flV, flU2, false);
        for (int i = 0; i < flU.size(); ++i)
        {
            if (fabs(flU[i] - flU2[i]) > 5)
                flV[i].value = -1;
//            printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
        }
        F32 x = 0, y = 0;
        S32 count = 0;
        for (unsigned int i = 0; i < flV.size(); ++i)
        {
            if (flV[i].value >= 0)
            {
                x += flV[i].x - flU[i].x;
                y += flV[i].y - flU[i].y;
                ++count;
            }
            flU[i].value = -1;
        }
        //cout<<count<<endl;
        cout << (clock() / 1000 - start) << endl;
        rect.X += (x / count);
        rect.Y += (y / count);
        printf("%d,%d\n", rect.X, rect.Y);
        SelectFeature select(gray, 7);
        select.mindist=5;
        select.SelectGoodFeature(rect, flU);
        sprintf(file, "Debug/output/%05d.pgm", k);
        for (unsigned int i = 0; i < flV.size(); ++i)
        {
            if (flV[i].value >= 0)
            {
                Draw::Circle(gray, flV[i].x, flV[i].y, 2, 255);
            }
        }
//        rect.X=rect.Y=0;
        Draw::Rectangle(gray, rect, 255);
        IOHelper::WritePGMFile(file, gray);

        //flV.clear();
        flU2.clear();
        cout<<flV.size()<<endl;
    }

}
void lktest2Img()
{
    ImageGray gray1, gray2;
    IOHelper::ReadPGMFile("Debug/img0.pgm", gray1);
    IOHelper::ReadPGMFile("Debug/img1.pgm", gray2);
    SelectFeature select(gray1, 7);
    vector<FeaturePoint> flU(100), flV(100), flU2(100);
    RectangleS rect(0, 0, gray1.GetWidth(), gray1.GetHeight());
    select.SelectGoodFeature(rect, flU);
    LKTracker tracker(gray1, gray2);
    vector<FeaturePoint>::iterator feat = flU.begin();
    int i = 0;
    while (feat != flU.end())
    {
        Draw::Circle(gray1, feat->x, feat->y, 3, 255);
        printf("Feature:%d at(%d,%d) with %d\n", i++, feat->x, feat->y, feat->value);
        ++feat;
    }
    tracker.Compute(flU, flV, true);
    tracker.Compute(flV, flU2, false);
    for (int i = 0; i < flU.size(); ++i)
    {
        if (fabs(flU[i] - flU2[i]) > 5)
            flV[i].value = -1;
        printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
    }
    feat = flV.begin();
    i = 0;
    while (feat != flV.end())
    {
        if (feat->value >= 0)
        {
            Draw::Circle(gray2, feat->x, feat->y, 3, 255);
            printf("Feature:%d at(%d,%d) with %d\n", i++, feat->x, feat->y, feat->value);
        }
        ++feat;
    }
    IOHelper::WritePPMFile("Debug/gray1.ppm", gray1);
    IOHelper::WritePPMFile("Debug/gray2.ppm", gray2);
}
