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
using std::cout;
using std::vector;
using namespace itr_algorithm;
using namespace itr_vision;
void lktest()
{
    lktest2Img();
}



void lktest2Img()
{
   printf("*****Begin KLT Tracking 2 Image Test!*****\n\n");
    ImageGray input1, input2;
    IOHelper::ReadPGMFile("bin/debug/img00069.pgm", input1);
    IOHelper::ReadPGMFile("bin/debug/img00070.pgm", input2);
//    IOHelper::ReadPPMFile("Debug/twinnings/imgs/img00000.ppm", gray1);
//    IOHelper::ReadPPMFile("Debug/twinnings/imgs/img00000.ppm", gray2);
    Matrix gray1(input1.GetHeight(),input1.GetWidth()),gray2(input1.GetHeight(),input1.GetWidth());
    ConvertFormat::ImageGray2Matrix(input1,gray1);
    ConvertFormat::ImageGray2Matrix(input2,gray2);
    SelectKLTFeature select(gray1);
    int Amount=100;
    vector<CommFeaturePoint> flU(Amount), flV(Amount), flU2(Amount);
    RectangleS rect(0, 0, gray1.GetCol(), gray1.GetRow());
//    RectangleS rect(126,165,73,53);
    select.SelectGoodFeature(rect, flU);
    LKTracker tracker;
    tracker.Init(gray1, gray2);

    tracker.Compute(flU, flV, Amount,true);
    vector<CommFeaturePoint>::iterator feat = flU.begin();
///Debug
if(true)
{
int i=0;
 printf("\nIn first image:\n");
    while (feat != flU.end())
    {
        Draw::Circle(gray1, feat->X, feat->Y, 3, 255);
        printf("Feature #%d:  (%d,%d) with value of %d\n", i++, feat->X, feat->Y, feat->Quality);
        ++feat;
    }
    printf("\nIn Second image:\n");
    i=0;
    feat = flV.begin();
    while (feat != flV.end())
    {
        if (feat->Quality >= 0)
        {
            Draw::Circle(gray2, feat->X, feat->Y, 3, 255);
        }
        printf("Feature #%d:  (%d,%d) with value of %d\n", i++, feat->X, feat->Y, feat->Quality);
        ++feat;
    }
}
    tracker.Compute(flV, flU2,Amount, false);
    for (int i = 0; i < flU.size(); ++i)
    {
        if ((flU[i] - flU2[i]).GetDistance() > 5)
            flV[i].Quality = -1;
        printf("%d,%d\n", (flU[i] - flU2[i]).GetDistance(), flV[i].Quality);
    }

    int i = 0;
    feat = flV.begin();
    i = 0;
    while (feat != flV.end())
    {
        if (feat->Quality >= 0)
        {
            Draw::Circle(gray2, feat->X, feat->Y, 3, 255);
            printf("Feature:%d at(%d,%d) with %d\n", i++, feat->X, feat->Y, feat->Quality);
        }
        ++feat;
    }

    Matrix result;

    vector<Point2D> outU(Amount),outV(Amount);
    int count=0;
    for(i=0;i<Amount;++i)
    {
        if(flV[i].Quality>=0)
        {
            outU[i]=flU[i];
            outV[i]=flV[i];
            count++;
        }
    }
    Draw::Correspond(gray1, gray2, outU, outV, count,result);

    IOpnm::WritePGMFile("bin/debug/result.pgm",result);
    IOpnm::WritePGMFile("bin/debug/gray1.pgm",gray1);
    IOpnm::WritePGMFile("bin/debug/gray2.pgm",gray2);
    printf("*****End KLT Tracking 2 Image Test!*****\n\n");

}

void lkseq()
{/*
printf("*****Begin KLT Tracking Sequence Test!*****\n\n");
    char file[25];
    ImageGray gray,last;
    IOHelper::ReadPGMFile("Debug/green/pgm/cap000.pgm", gray);
    IOHelper::ReadPGMFile("Debug/green/pgm/cap000.pgm", last);
    //IOHelper::ReadPGMFile("Debug/david/imgs/img00001.ppm", gray);

///Mine
    RectangleS rect(235, 265, 80, 80);
    /// twinning
    //RectangleS rect(126,165,73,53);
    /// David
    //RectangleS rect(120,58,75,97);

    ///选取KLT特征
    S32 FeatureNum=150;
    vector<FeaturePoint> flU(FeatureNum), flV(FeatureNum), flU2(FeatureNum);
    SelectFeature select(gray);
    select.mindist = 7;
    LKTracker tracker(gray);

    ///随机一致性检测
    DataOper oper;
    Ransac ransac(oper);

    ///卡尔曼滤波用
    KalmanFilter kf(4);
    F32 data[16]= {1 ,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1};
    kf.F_x.CopyFrom(data);
    Matrix H(2,4),R(2,2);
    R.MatEye(5.012306);
    H.CopyFrom(data+8);
    printMatrix(H);
    printMatrix(kf.F_x);
    Vector z(2),X(4),v(2);
    kf.x[0]=rect.X;
    kf.x[1]=rect.Y;
    kf.x[2]=0;
    kf.x[3]=0;

    ///用于临时存放速度值，总特征点数及有效点数
    F32 *x = new F32[FeatureNum], *y = new F32[FeatureNum];
    S32 count = 0, drop=0;

    ConvoluteSquare conv;

    FeatureNum=select.SelectGoodFeature(rect, flU);
    ///主循环，对每一帧图像
    tracker.max_iterations=15;
    for (int k = 1; k < 200; ++k)
    {
        last=gray;
        sprintf(file, "Debug/green/cap%03d.pgm", k);
        printf("%s\n",file);
        IOHelper::ReadPGMFile(file, gray);
        conv._KLTComputeSmoothedImage(gray, 0.1 * tracker.windowWidth, gray);
        int start = clock() / 1000;
        tracker.AddNext(gray);

        //正反误差滤波
        tracker.Compute(flU, flV, FeatureNum,true);
//        for(int i=0;i<FeatureNum;++i)
//         cout<<flV[i].value<<endl;
        tracker.Compute(flV, flU2, FeatureNum, false);
        for (int i = 0; i <FeatureNum; ++i)
        {
            if (fabs(flU[i] - flU2[i]) > 9)
                flV[i].value = -1;
//            printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
        }
        ImageGray result;
        Draw::Correspond(last,gray,flU,flV,result);
        IOHelper::WritePPMFile("Debug/result.ppm",result);

        //计算矩形框速度
        count=0;
        for (unsigned int i = 0; i < FeatureNum; ++i)
        {

            if (flV[i].value == 0)
            {

                x[count] = flV[i].x - flU[i].x;
                y[count] = flV[i].y - flU[i].y;
                flU[count].x=flV[i].x;
                flU[count].y=flV[i].y;
                flU[count].value=flU[i].value;
                ++count;
            }

        }
        cout << "Points: "<<count << endl;

        //输出速度
        if(false)
        {
            printf("X: ");
             std::sort(x, x + count);
            for (int i = 0; i < count; i++)
                printf("%0.0f ", x[i]);
            cout << endl;
            std::sort(y, y + count);
            printf("Y: ");
            for (int i = 0; i < count; i++)
                printf("%0.0f ", y[i]);
            cout << endl;
        }
        //RANSAC
        //Ransac(count, x, drop);
        ransac.Process(count, x, drop);
        std::sort(x, x + count);
        rect.X += (S32)(x[(count - drop) / 2]+0.5); //(x / count + 0.5);
        z[0]=x[(count - drop) / 2];
        R(0,0)=drop+0.012306;
        ransac.Process(count, y, drop);
        std::sort(y, y + count);
        rect.Y += (S32)(y[(count - drop) / 2]+0.5); //(y / count + 0.5);
        z[1]=y[(count - drop) / 2];
        R(1,1)=drop+0.012306;
        printf("X,Y:%d,%d \n", rect.X, rect.Y);
//        z[0]=rect.X+0.0;
//        z[1]=rect.Y+0.0;

        kf.UpdateModel();
        X=kf.UpdateMeasure(H,R,z);
        rect.X=X[0];
        rect.Y=X[1];
        printf("Esti: %.0f,%.0f,%.0f,%.0f\n",X[0],X[1],X[2],X[3]);

        //输出速度
        if(false)
        {
            printf("X: ");
            for (int i = 0; i < count; i++)
                printf("%0.2f ", x[i]);
            cout << endl;
            printf("Y: ");
            for (int i = 0; i < count; i++)
                printf("%0.2f ", y[i]);
            cout << endl;
        }
        //std::cin.get();
        cout << (clock() / 1000 - start) << endl;


        //输出处理
        sprintf(file, "Debug/output/%05d.pgm", k);
        for (unsigned int i = 0; i < FeatureNum; ++i)
        {
            if (flV[i].value >= 0)
            {
                Draw::Circle(gray, flV[i].x, flV[i].y, 2, 255);
            }
        }
//        rect.X=rect.Y=0;

        Draw::Rectangle(gray, rect, 255);
        IOHelper::WritePGMFile(file, gray);

        //选择下一帧图像中的特征点
        SelectFeature select(gray);
        select.mindist = 5;
        //std::sort(flU.begin(),flU.end(),std::greater<FeaturePoint>());
        FeatureNum=select.SelectGoodFeature(rect, flU);

        cout<<"FeatureNum:"<<FeatureNum<<endl;
        cout<<endl;
        //getchar();
    }
    delete[] x;
    delete[] y;
printf("*****End KLT Tracking Sequence Test!*****\n\n");*/
}

