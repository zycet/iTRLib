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
//#include "iohelper.h"
#include "itralgorithm.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>
using std::endl;
using std::cout;
using std::vector;
using namespace std;
using namespace itr_algorithm;
using namespace itr_vision;
void SortMatch(vector<Point2D>& U,vector<Point2D>& V,int* Quality,int length);
void MakeBlocks(int width,int height,int border,int NumX,int NumY,int CubicNum,vector<RectangleF>& rect);
void lktest()
{
    //lktest2Img();
    //lktest3Img();
    lktest_Stereo();
}



void lktest2Img()
{
    printf("*****Begin KLT Tracking 2 Image Test!*****\n\n");
    itr_math::Matrix gray1, gray2;
    IOpnm::ReadPGMFile("SplineTest/1.pgm", gray1);
    IOpnm::ReadPGMFile("SplineTest/2.pgm", gray2);

    SelectKLTFeature select(gray1);
    int Amount = 1500;
    vector<CommFeaturePoint> flU(Amount), flV(Amount), flU2(Amount);

    RectangleF rect(16, 16, gray1.GetCol() - 16, gray1.GetRow() - 16);

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
            printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
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
            //printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
            ++feat;
        }
    }
    /*tracker.Compute(flV, flU2,Amount, false);
    for (int i = 0; i < flU.size(); ++i)
    {
        if ((flU[i] - flU2[i]).GetDistance() > 5)
            flV[i].Quality = -1;
        printf("%f,%f\n", (flU[i] - flU2[i]).GetDistance(), flV[i].Quality);
    }

    int i = 0;
    feat = flV.begin();
    i = 0;
    while (feat != flV.end())
    {
        if (feat->Quality >= 0)
        {
            Draw::Circle(gray2, feat->X, feat->Y, 3, 255);
            printf("Feature:%d at(%f,%f) with %f\n", i++, feat->X, feat->Y, feat->Quality);
        }
        ++feat;
    }
    */
    Matrix result;

    vector<Point2D> outU(Amount),outV(Amount);
    int count=0;
    ofstream o_file;
    o_file.open("SplineTest/CP.txt");
    for(int i=0; i<Amount; ++i)
    {
        if(flV[i].Quality>=0)
        {
            outU[i]=flU[i];
            outV[i]=flV[i];
            o_file << outU[i].X << " " << outU[i].Y << " " << outU[i].X - outV[i].X  << " " << flU[i].Quality <<endl;
            count++;
        }
    }
    Draw::Correspond(gray1, gray2, outU, outV, count, result);
    o_file.close();

    IOpnm::WritePGMFile("SplineTest/result1.pgm",gray1);
    //IOpnm::WritePGMFile("bin/debug/gray1.pgm",gray1);
    //IOpnm::WritePGMFile("bin/debug/gray2.pgm",gray2);
    printf("*****End KLT Tracking 2 Image Test!*****\n\n");

}

/****************************************************************************************/
/****************************************************************************************/
void lktest3Img()
{
    printf("*****Begin KLT Tracking 3 Image Test!*****\n\n");
    itr_math::Matrix gray1, gray2;
    IOpnm::ReadPGMFile("SplineTest/1.pgm", gray1);
    IOpnm::ReadPGMFile("SplineTest/2.pgm", gray2);

    SelectKLTFeature select(gray1);
    int Amount=1000;
    vector<CommFeaturePoint> flU1(Amount),flU2(Amount),flU3(Amount),flU4(Amount),flU5(Amount),flU6(Amount),flU7(Amount),flU8(Amount),flU9(Amount);
    vector<CommFeaturePoint> flU10(Amount),flU11(Amount),flU12(Amount),flU13(Amount),flU14(Amount),flU15(Amount),flU16(Amount);
    vector<CommFeaturePoint> flV1(Amount),flV2(Amount),flV3(Amount),flV4(Amount),flV5(Amount),flV6(Amount),flV7(Amount),flV8(Amount),flV9(Amount);
    vector<CommFeaturePoint> flV10(Amount),flV11(Amount),flV12(Amount),flV13(Amount),flV14(Amount),flV15(Amount),flV16(Amount);
    vector<CommFeaturePoint> flUArray[16];
    vector<CommFeaturePoint> flVArray[16];

    flUArray[0] = flU1;flVArray[0] = flV1;
    flUArray[1] = flU2;flVArray[1] = flV2;
    flUArray[2] = flU3;flVArray[2] = flV3;
    flUArray[3] = flU4;flVArray[3] = flV4;
    flUArray[4] = flU5;flVArray[4] = flV5;
    flUArray[5] = flU6;flVArray[5] = flV6;
    flUArray[6] = flU7;flVArray[6] = flV7;
    flUArray[7] = flU8;flVArray[7] = flV8;
    flUArray[8] = flU9;flVArray[8] = flV9;
    flUArray[9] = flU10;flVArray[9] = flV10;
    flUArray[10] = flU11;flVArray[10] = flV11;
    flUArray[11] = flU12;flVArray[11] = flV12;
    flUArray[12] = flU13;flVArray[12] = flV13;
    flUArray[13] = flU14;flVArray[13] = flV14;
    flUArray[14] = flU15;flVArray[14] = flV15;
    flUArray[15] = flU16;flVArray[15] = flV16;

    int border = 16;
    int w = (gray1.GetCol()-border*2)/4;
    int h = (gray1.GetRow()-border*2)/4;

    RectangleF rect1(border,border,w,h);RectangleF rect2(w+border,border,w,h);RectangleF rect3(2*w + border,border,w,h);RectangleF rect4(3*w+border,border,w,h);
    RectangleF rect5(border,h+border,w,h);RectangleF rect6(w+border,h+border,w,h);RectangleF rect7(2*w+border,h+border,w,h);RectangleF rect8(3*w+border,h+border,w,h);
    RectangleF rect9(border,2*h+border,w,h);RectangleF rect10(w+border,2*h+border,w,h);RectangleF rect11(2*w+border,2*h+border,w,h);RectangleF rect12(3*w+border,2*h+border,w,h);
    RectangleF rect13(border,3*h+border,w,h);RectangleF rect14(w+border,3*h+border,w,h);RectangleF rect15(2*w+border,3*h+border,w,h);RectangleF rect16(3*w+border,3*h+border,w,h);

    select.SelectGoodFeature(rect1, flUArray[0]);
    select.SelectGoodFeature(rect2, flUArray[1]);
    select.SelectGoodFeature(rect3, flUArray[2]);
    select.SelectGoodFeature(rect4, flUArray[3]);
    select.SelectGoodFeature(rect5, flUArray[4]);
    select.SelectGoodFeature(rect6, flUArray[5]);
    select.SelectGoodFeature(rect7, flUArray[6]);
    select.SelectGoodFeature(rect8, flUArray[7]);
    select.SelectGoodFeature(rect9, flUArray[8]);
    select.SelectGoodFeature(rect10, flUArray[9]);
    select.SelectGoodFeature(rect11, flUArray[10]);
    select.SelectGoodFeature(rect12, flUArray[11]);
    select.SelectGoodFeature(rect13, flUArray[12]);
    select.SelectGoodFeature(rect14, flUArray[13]);
    select.SelectGoodFeature(rect15, flUArray[14]);
    select.SelectGoodFeature(rect16, flUArray[15]);


    LKTracker tracker;
    tracker.Init(gray1, gray2);

    for(int i = 0; i < 16; i++)
    {
        tracker.Compute(flUArray[i],flVArray[i],Amount,true);
    }

    vector<CommFeaturePoint>::iterator feat;// = flU.begin();

///Debug
    if(true)
    {
        for(int j=0; j < 16; j++)
        {
            int i=0;
            feat = flUArray[j].begin();
            printf("\nIn first image, Region %d:\n", j);
            while (feat != flUArray[j].end())
            {
                Draw::Circle(gray1, feat->X, feat->Y, 3, 255);
                printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
                ++feat;
            }

            i=0;
            feat = flVArray[j].begin();
            printf("\nIn two image, Region %d:\n", j);
            while (feat != flVArray[j].end())
            {
                if (feat->Quality >= 0)
                {
                    //Draw::Circle(gray2, feat->X, feat->Y, 3, 255);
                }
                //printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
                ++feat;
            }
        }
    }

    Matrix result;

    vector<Point2D> outU(Amount*16),outV(Amount*16);
    int outQ[Amount*16];
    int count = 0;
    ofstream o_file;

    for(int j = 0; j < 16; j++)
    {
        for(int i=0; i<Amount; ++i)
        {
            if(flVArray[j][i].Quality >= 0)
            {
                outU[count]=flUArray[j][i];
                outV[count]=flVArray[j][i];
                outQ[count]=flUArray[j][i].Quality;
                //o_file << outU[count].X << " " << outU[count].Y << " " << outV[count].X << " " << outV[count].Y << " " << outQ[count] <<endl;
                count++;
            }
        }
    }
    ///Sort the match big -> small in terms of Quality value
    //SortMatch(outU,outV,outQ,count);
    /*o_file.open("long_16grid_100.txt");
    for(int i = 0;i<count;i++)
    {
        o_file << outU[i].X << " " << outU[i].Y << " " << outV[i].X << " " << outV[i].Y << " " << outQ[i] <<endl;
    }
    o_file.close();*/
    //Draw::Correspond(gray1, gray2, outU, outV, count, result);

    IOpnm::WritePGMFile("result_16.pgm",gray1);
    //IOpnm::WritePGMFile("bin/debug/gray1.pgm",gray1);
    //IOpnm::WritePGMFile("bin/debug/gray2.pgm",gray2);
    printf("*****End KLT Tracking 3 Image Test!*****\n\n");

}


void lktest_Stereo()
{
    itr_math::Matrix gray1, gray2;
    IOpnm::ReadPGMFile("SplineTest/1.pgm", gray1);
    IOpnm::ReadPGMFile("SplineTest/2.pgm", gray2);

    SelectKLTFeature select(gray1);
    int Amount=100;
    const int NumBlock = 2;
    const int NumX = 2;
    const int NumY = 1;
    int border = 16;

    vector<CommFeaturePoint> flUArray[NumBlock];
    vector<CommFeaturePoint> flVArray[NumBlock];

    for(int i = 0;i < NumBlock;i++)
    {
        vector<CommFeaturePoint> fluTemp(Amount);
        vector<CommFeaturePoint> flvTemp(Amount);
        flUArray[i] = fluTemp;
        flVArray[i] = flvTemp;
    }

    vector<RectangleF> rect;
    MakeBlocks(gray1.GetCol(),gray1.GetRow(),border,NumX,NumY,NumBlock,rect);
    for(int i = 0;i < NumBlock;i++)
    {
        select.SelectGoodFeature(rect[i],flUArray[i]);
    }

    LKTracker tracker;
    tracker.Init(gray1, gray2);

    for(int i = 0; i < NumBlock; i++)
    {
        tracker.Compute(flUArray[i],flVArray[i],Amount,true);
    }

    vector<CommFeaturePoint>::iterator feat;// = flU.begin();

///Debug
    if(true)
    {
        for(int j=0; j < NumBlock; j++)
        {
            int i=0;
            feat = flUArray[j].begin();
            //printf("\nIn first image, Region %d:\n", j);
            while (feat != flUArray[j].end())
            {
                Draw::Circle(gray1, feat->X, feat->Y, 2, 255);
                //printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
                ++feat;
            }

            i=0;
            feat = flVArray[j].begin();
            //printf("\nIn two image, Region %d:\n", j);
            while (feat != flVArray[j].end())
            {
                if (feat->Quality >= 0)
                {
                    //Draw::Circle(gray2, feat->X, feat->Y, 3, 255);
                }
                //printf("Feature #%d:  (%f,%f) with value of %f\n", i++, feat->X, feat->Y, feat->Quality);
                ++feat;
            }
        }
    }

    Matrix result;

    vector<Point2D> outU(Amount*NumBlock),outV(Amount*NumBlock);
    int outQ[Amount*NumBlock];
    int count = 0;
    ofstream o_file;

    for(int j = 0; j < NumBlock; j++)
    {
        for(int i=0; i<Amount; ++i)
        {
            if(flVArray[j][i].Quality >= 0)
            {
                outU[count]=flUArray[j][i];
                outV[count]=flVArray[j][i];
                outQ[count]=flUArray[j][i].Quality;
                //o_file << outU[count].X << " " << outU[count].Y << " " << outV[count].X << " " << outV[count].Y << " " << outQ[count] <<endl;
                count++;
            }
        }
    }

    /*o_file.open("long_16grid_100.txt");
    for(int i = 0;i<count;i++)
    {
        o_file << outU[i].X << " " << outU[i].Y << " " << outV[i].X << " " << outV[i].Y << " " << outQ[i] <<endl;
    }
    o_file.close();*/

    IOpnm::WritePGMFile("result_blk2.pgm",gray1);
}

void SortMatch(vector<Point2D>& U,vector<Point2D>& V,int* Quality,int length)
{
    int Qtemp;
    Point2D Utemp,Vtemp;
    for(int i = 0;i<length-1;i++)
    {
        int index = i;
        for(int j = i+1;j<length;j++)
        {
            if(Quality[j] >= Quality[index])
                index = j;
        }
        if(index != i)
        {
            Qtemp = Quality[i];
            Quality[i] = Quality[index];
            Quality[index] = Qtemp;

            Utemp = U[i];
            U[i] = U[index];
            U[index] = Utemp;

            Vtemp = V[i];
            V[i] = V[index];
            V[index] = Vtemp;
        }
    }
}

void MakeBlocks(int width,int height,int border,int NumX,int NumY,int CubicNum,vector<RectangleF>& rect)
{
    assert(CubicNum == NumX * NumY);
    int StartX = border;
    int StartY = border;
    int CubicWidth = (width - 2 * border)/NumX;
    int CubicHeight = (height - 2 * border)/NumY;

    for(int y = 0;y < NumY;y++)
    {
        for(int x = 0;x < NumX;x++)
        {
            int UpLeftX = StartX + x * CubicWidth;
            int UpLeftY = StartY + y * CubicHeight;
            RectangleF rectTemp(UpLeftX,UpLeftY,CubicWidth,CubicHeight);
            //cout << "i = " << ++i << endl;
            //cout << "x = " << UpLeftX << endl;
            //cout << "y = " << UpLeftY << endl;
            //cout << "width = " << UpLeftX + CubicWidth << endl;
            //cout << "height = " << UpLeftY+ CubicHeight << endl;
            rect.push_back(rectTemp);
        }
    }
}

void lkseq()
{
    /*
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

