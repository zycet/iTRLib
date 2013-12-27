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
 * DetectionTest.cpp
 *  Created on: 2013-12-18
 *      Author: ghdawn
 */
#include "lktrackertest.h"
#include "iohelper.h"
#include "itralgorithm.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>
using std::endl;
using std::cin;
using std::cout;
using std::vector;
void DetectionTest()
{
/*    printf("*****Begin Detection Sequence Test!*****\n\n");
    char file[25];

    Matrix img;
    IOHelper::ReadPGMFile("Debug/green/pgm/cap000.pgm", img);
    //IOHelper::ReadPGMFile("Debug/david/imgs/img00001.ppm", gray);
    Matrix gray(img.GetCol(),img.GetRow());
    Matrix sample(30,30);
    ConvoluteSquare conv;
    conv._KLTComputeSmoothedImage(img, 2, gray);
    ///Mine
    RectangleS rect(235, 265, 80, 80);
    /// twinning
    //RectangleS rect(126,165,73,53);
    /// David
    //RectangleS rect(120,58,75,97);

    RectangleS rectNeg(rect.X, rect.Y, rect.Width, rect.Height);
    RectangleS rectPos(rect.X, rect.Y, rect.Width, rect.Height);

    S32 FeatureNum=sample.GetCol()*sample.GetRow();
    F32 data[8000];
    itr_algorithm::NaiveBayes nbc(FeatureNum);

    Matrix dataPos(4,FeatureNum),dataNeg(4,FeatureNum);
    Matrix patch(rect.Width,rect.Height);
    itr_vision::Pick::Rectangle(gray,rect,patch);
    itr_vision::Scale::Bilinear(patch,sample);
    IOHelper::WritePPMFile("Debug/0.ppm", sample);

    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataPos.CopyRowFrom(1,data);

    rectPos.X+=2;
    itr_vision::Pick::Rectangle(gray,rectPos,patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataPos.CopyRowFrom(2,data);

    rectPos.X-=4;
    itr_vision::Pick::Rectangle(gray,rectPos,patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataPos.CopyRowFrom(3,data);

    rectPos.Y+=2;
    itr_vision::Pick::Rectangle(gray,rectPos,patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataPos.CopyRowFrom(4,data);

    nbc.TrainPos(dataPos);


    rectNeg.X=rect.X+rect.Width;
    itr_vision::Pick::Rectangle(gray,rectNeg,patch);
    IOHelper::WritePPMFile("Debug/1.ppm", patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataNeg.CopyRowFrom(1,data);

    rectNeg.X=rect.X-rect.Width;
    itr_vision::Pick::Rectangle(gray,rectNeg,patch);
    IOHelper::WritePPMFile("Debug/2.ppm", patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataNeg.CopyRowFrom(2,data);

    rectNeg.X=rect.X;
    rectNeg.Y=rect.Y+rect.Height;
    itr_vision::Pick::Rectangle(gray,rectNeg,patch);
    IOHelper::WritePPMFile("Debug/3.ppm", patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataNeg.CopyRowFrom(3,data);

    rectNeg.Y=rect.Y-rect.Height;
    itr_vision::Pick::Rectangle(gray,rectNeg,patch);
    IOHelper::WritePPMFile("Debug/4.ppm", patch);
    itr_vision::Scale::Bilinear(patch,sample);
    for(int i=0; i<FeatureNum; ++i)
    {
        data[i]=sample[i];
    }
    dataNeg.CopyRowFrom(4,data);

    nbc.TrainNeg(dataNeg);

    ///主循环，对每一帧图像
    int width=gray.GetCol();
    int height=gray.GetRow();
    F32 result,best;
    int x,y;

    for (int k = 1; k < 200; ++k)
    {
        sprintf(file, "Debug/green/cap%03d.pgm", k);
        printf("%s\n",file);
        IOHelper::ReadPGMFile(file, img);
        conv._KLTComputeSmoothedImage(img, 2, gray);
        int start = clock() / 1000;
        best=-9999999;
        for(int i=rectPos.X-50; i<rectPos.X+50; i+=2)
            for(int j=rectPos.Y-50; j<rectPos.Y+50; j+=2)
            {
                rect.X=i;
                rect.Y=j;
                itr_vision::Pick::Rectangle(gray,rect,patch);
                itr_vision::Scale::Bilinear(patch,sample);
                IOHelper::WritePPMFile("Debug/5.ppm", sample);
//                getchar();
                for(int i=0; i<FeatureNum; ++i)
                {
                    data[i]=sample[i];
                }
                result=nbc.Classify(data);
                // printf("i,j:%d,%d,%.3f\n",i,j,result);
                if(best<result)
                {
                    best=result;
                    x=i;
                    y=j;
                }
            }
        printf("Final X,Y:%d %d\n at %.3f\n\n",x,y,best);
        rectPos.X=x;
        rectPos.Y=y;
        itr_vision::Pick::Rectangle(gray,rectPos,patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        itr_vision::Draw::Rectangle(gray,rectPos,255);

        itr_vision::Pick::Rectangle(gray,rect,patch);
        itr_vision::Scale::Bilinear(patch,sample);
        IOHelper::WritePPMFile("Debug/0.ppm", sample);

        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataPos.CopyRowFrom(1,data);

        rectPos.X+=2;
        itr_vision::Pick::Rectangle(gray,rectPos,patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataPos.CopyRowFrom(2,data);

        rectPos.X-=4;
        itr_vision::Pick::Rectangle(gray,rectPos,patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataPos.CopyRowFrom(3,data);

        rectPos.Y+=2;
        itr_vision::Pick::Rectangle(gray,rectPos,patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataPos.CopyRowFrom(4,data);

        nbc.TrainPos(dataPos);


        rectNeg.X=rect.X+rect.Width;
        itr_vision::Pick::Rectangle(gray,rectNeg,patch);
        IOHelper::WritePPMFile("Debug/1.ppm", patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataNeg.CopyRowFrom(1,data);

        rectNeg.X=rect.X-rect.Width;
        itr_vision::Pick::Rectangle(gray,rectNeg,patch);
        IOHelper::WritePPMFile("Debug/2.ppm", patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataNeg.CopyRowFrom(2,data);

        rectNeg.X=rect.X;
        rectNeg.Y=rect.Y+rect.Height;
        itr_vision::Pick::Rectangle(gray,rectNeg,patch);
        IOHelper::WritePPMFile("Debug/3.ppm", patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataNeg.CopyRowFrom(3,data);

        rectNeg.Y=rect.Y-rect.Height;
        itr_vision::Pick::Rectangle(gray,rectNeg,patch);
        IOHelper::WritePPMFile("Debug/4.ppm", patch);
        itr_vision::Scale::Bilinear(patch,sample);
        for(int i=0; i<FeatureNum; ++i)
        {
            data[i]=sample[i];
        }
        dataNeg.CopyRowFrom(4,data);

        nbc.TrainNeg(dataNeg);
        rectPos.X=x;
        rectPos.Y=y;
        sprintf(file, "Debug/output/cap%03d.pgm", k);
        IOHelper::WritePPMFile(file,gray);
        IOHelper::WritePPMFile("Debug/6.ppm", patch);
    }
    printf("*****End Detection Sequence Test!*****\n\n");*/
}
