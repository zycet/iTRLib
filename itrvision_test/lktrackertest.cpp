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
void lktest()
{
    lktest2Img();
    lkseq();
}
/*void Ransac(S32 count, F32* x, S32& drop)
{
    S32 INF = 9999999;
    S32 M = 7;
    S32 N = count / M;
    if (N < 1)
        N = 1;
    F32 *data = new F32[N];
    F32 *result = new F32[M];
    F32 *error = new F32[M];
    int index, key;
    for (int i = 0; i < M; i++)
    {

        for (int j = 0; j < N; j++)
        {
            itr_math::NumericalObj->Rand(0, count, index);
            data[j] = x[index];
        }
        std::sort(data, data + N);
        result[i] = data[N / 2];
        for (int j = 0; j < count; ++j)
        {
            error[i] += fabs(x[j] - result[i]); //*(x[j]-result[i]);
        }
    }
    index = 0;
    key = error[0];
    for (int i = 1; i < M; i++)
    {
        if (key > error[i])
        {
            key = error[i];
            index = i;
        }
    }
    key = result[index];
    drop = 0;
    printf("error: ");
    for (int i = 0; i < count; ++i)
    {
        printf("%0.0f ", fabs(x[i] - key));
        if (fabs(x[i] - key) >= 1.5)
        {
            x[i] = INF;
            ++drop;
        }
    }
    cout << endl;
    delete[] error;
    delete[] data;
    delete[] result;
}*/
class DataOper:public Operator
{
    public:
        F32 GetError(F32 a, F32 b)
        {
            return fabs(a-b);
        }
        F32 GetValue(F32 *data, S32 N)
        {
            std::sort(data,data+N);
            return data[N/2];
        }
        bool Remain(F32 error)
        {
            return (fabs(error)<1.5);
        }
};

void printMatrix(Matrix a)
{
    for (int i = 0; i < a.GetRow(); ++i)
    {
        for (int j = 0; j < a.GetCol(); ++j)
        {
            printf("%f ", a(i, j));
        }
        printf("\n");
    }
}
void lkseq()
{
printf("*****Begin KLT Tracking Sequence Test!*****\n\n");
    char file[25];
    ImageGray gray;
//    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    IOHelper::ReadPGMFile("Debug/twinnings/imgs/img00000.pgm", gray);
    SelectFeature select(gray, 7);
    vector<FeaturePoint> flU(100), flV(100), flU2(100);
//    RectangleS rect(235, 265, 80, 80);
    RectangleS rect(126,165,73,53);
    select.mindist = 10;
    select.SelectGoodFeature(rect, flU);
    LKTracker tracker(gray);
    DataOper oper;
    Ransac ransac(oper);

    KalmanFilter kf(4);
    F32 data[16]= {2 ,0,-1,0,0,2,0,-1,1,0,0,0,0,1,0,0};
    kf.F_x.CopyRowFrom(1,data);
    kf.F_x.CopyRowFrom(2,data+4);
    kf.F_x.CopyRowFrom(3,data+8);
    kf.F_x.CopyRowFrom(4,data+12);
    Matrix H(2,4),R(2,2);
    R.MatEye(2.012306);
    H.CopyRowFrom(1,data+8);
    H.CopyRowFrom(2,data+12);
    printMatrix(H);
    printMatrix(kf.F_x);
    Vector z(2),X(4),v(2);
    kf.x[0]=rect.X;
    kf.x[1]=rect.Y;
    kf.x[2]=rect.X;
    kf.x[3]=rect.Y;
    for (int k = 1; k < 200; ++k)
    {
        sprintf(file, "Debug/twinnings/imgs/img%05d.pgm", k);
        IOHelper::ReadPGMFile(file, gray);
        int start = clock() / 1000;
        tracker.AddNext(gray);

        //正反误差滤波
        tracker.Compute(flU, flV, true);
        tracker.Compute(flV, flU2, false);
        for (int i = 0; i < flU.size(); ++i)
        {
            if (fabs(flU[i] - flU2[i]) > 9)
                flV[i].value = -1;
//            printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
        }

        //计算矩形框速度
        F32 *x = new F32[flV.size()], *y = new F32[flV.size()];
        S32 count = 0, drop;
        for (unsigned int i = 0; i < flV.size(); ++i)
        {
            if (flV[i].value >= 0)
            {
                x[count] = flV[i].x - flU[i].x;
                y[count] = flV[i].y - flU[i].y;
                ++count;
            }
            flU[i].value = -1;
        }
        cout << count << endl;
        //输出速度
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
        rect.X += x[(count - drop) / 2]; //(x / count + 0.5);
        ransac.Process(count, y, drop);
        std::sort(y, y + count);
        rect.Y += y[(count - drop) / 2]; //(y / count + 0.5);

        printf("X,Y:%d,%d \n", rect.X, rect.Y);
        z[0]=rect.X+0.0;
        z[1]=rect.Y+0.0;

        kf.UpdateModel();
        X=kf.UpdateMeasure(H,R,z);
        rect.X=X[0];
        rect.Y=X[1];
        printf("Esti: %.0f,%.0f,%.0f,%.0f\n",X[0],X[1],X[2],X[3]);
        cout<<endl;
        //输出速度
        {
            printf("X: ");
            for (int i = 0; i < count; i++)
                printf("%0.0f ", x[i]);
            cout << endl;
            printf("Y: ");
            for (int i = 0; i < count; i++)
                printf("%0.0f ", y[i]);
            cout << endl;
        }
        //std::cin.get();
        cout << (clock() / 1000 - start) << endl;

        //选择下一帧图像中的特征点
        SelectFeature select(gray, 7);
        select.mindist = 7;
        select.SelectGoodFeature(rect, flU);

        //输出处理
        sprintf(file, "Debug/output/%05d.pgm", k);
        for (unsigned int i = 0; i < flV.size(); ++i)
        {
            if (flV[i].value >= 0)
            {
                Draw::Circle(gray, flV[i].x, flV[i].y, 2, 255);
            }
        }
//        rect.X=rect.Y=0;
        delete[] x;
        delete[] y;
        Draw::Rectangle(gray, rect, 255);
        IOHelper::WritePGMFile(file, gray);
        cout<<endl;
        getchar();
    }
printf("*****Begin KLT Tracking Sequence Test!*****\n\n");
}

void lktest2Img()
{
   printf("*****Begin KLT Tracking 2 Image Test!*****\n\n");
    ImageGray gray1, gray2;
    IOHelper::ReadPGMFile("Debug/img0.pgm", gray1);
    IOHelper::ReadPGMFile("Debug/img1.pgm", gray2);
    SelectFeature select(gray1, 7);
    vector<FeaturePoint> flU(50), flV(100), flU2(100);
    RectangleS rect(0, 0, gray1.GetWidth(), gray1.GetHeight());
    select.SelectGoodFeature(rect, flU);
    LKTracker tracker(gray1, gray2);

    tracker.Compute(flU, flV, true);

    tracker.Compute(flV, flU2, false);
    for (int i = 0; i < flU.size(); ++i)
    {
        if (fabs(flU[i] - flU2[i]) > 5)
            flV[i].value = -1;
        printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
    }
    vector<FeaturePoint>::iterator feat = flU.begin();
    int i = 0;
    while (feat != flU.end())
    {
        Draw::Circle(gray1, feat->x, feat->y, 3, 255);
        printf("Feature:%d at(%d,%d) with %d\n", i++, feat->x, feat->y, feat->value);
        ++feat;
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

    ImageGray result;
    Draw::Correspond(gray1, gray2, flU, flV, result);
    IOHelper::WritePPMFile("Debug/result.ppm", result);
    IOHelper::WritePPMFile("Debug/gray1.ppm", gray1);
    IOHelper::WritePPMFile("Debug/gray2.ppm", gray2);
    printf("*****End KLT Tracking 2 Image Test!*****\n\n");
}
