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
 * selectfeature.cpp
 *  Created on: 2013-10-3
 *      Author: ghdawn
 */

#include "selectkltfeature.h"
#include <algorithm>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../helper/helper.h"
#include "../process/convolutesquare.h"
namespace itr_vision
{

    SelectKLTFeature::SelectKLTFeature(const Matrix &Img)
    {
        windowWidth=7;
        bw = windowWidth >> 1;
        mindist = 5;
        mineigen = 1;
        width = Img.GetCol();
        height = Img.GetRow();
        img.Init(height, width);
        dx.Init(height, width);
        dy.Init(height, width);
        ConvoluteSquare conv;
        conv._KLTComputeSmoothedImage(Img, 0.1f * windowWidth, img);
        conv._KLTComputeGradients(img, 1.0f, dx, dy);
        featuremap = new BOOL[height* width]();

    }
    SelectKLTFeature::SelectKLTFeature(S32 width,S32 height)
    {
        img.Init(height, width);
        dx.Init(height, width);
        dy.Init(height, width);
        featuremap = new BOOL[height* width]();
    }
    void SelectKLTFeature::AddImage(const Matrix &Img)
    {
        ConvoluteSquare conv;
        conv._KLTComputeSmoothedImage(Img, 0.1f * windowWidth, img);
        conv._KLTComputeGradients(img, 1.0f, dx, dy);
    }
    void SelectKLTFeature::fillMap(S32 x, S32 y, BOOL *featuremap)
    {
        int ix, iy;

        for (iy = y - mindist; iy <= y + mindist; iy++)
            for (ix = x - mindist; ix <= x + mindist; ix++)
                if (ix >= 0 && ix < width && iy >= 0 && iy < height)
                {
                    featuremap[iy * width + ix] = 1;
                }
    }

    SelectKLTFeature::~SelectKLTFeature()
    {
        delete[] featuremap;
    }

    float SelectKLTFeature::minEigenvalue(F32 gxx, F32 gxy, F32 gyy)
    {
        itr_math::NumericalObj->Sqrt((gxx - gyy) * (gxx - gyy) + 4 * gxy * gxy, gxy);
        return (float) ((gxx + gyy - gxy) * 0.5f);
//        return (float) ((gxx + gyy - sqrt((gxx - gyy) * (gxx - gyy) + 4 * gxy * gxy)) *0.5f);/// 2.0f);
    }
    S32 SelectKLTFeature::SelectGoodFeature(const RectangleF &rect, vector<CommFeaturePoint> &featureOutput,S32 start)
    {

        S32 bord = 24,ImgWidth=img.GetCol();
        S32 beginy = (rect.Y < bord) ? bord : rect.Y;
        S32 beginx = (rect.X < bord) ? bord : rect.X;
        if (beginy >= img.GetRow() - bord)
        {
            beginy = img.GetRow() - bord;
        }
        if (beginx >= ImgWidth - bord)
        {
            beginx = ImgWidth - bord;
        }
        S32 bordy = beginy + rect.Height;
        S32 bordx = beginx + rect.Width;
        bordy = (bordy < bord) ? bord :bordy;
        bordx = (bordx < bord) ? bord : bordx;
        if (bordy >= img.GetRow() - bord)
        {
            bordy = img.GetRow() - bord;
        }
        if (bordx >= ImgWidth - bord)
        {
            bordx = ImgWidth - bord;
        }
        vector<CommFeaturePoint> featurelist((bordx-beginx)*(bordy-beginy));
        S32 x, y, xx, yy;
        S32 gxx, gxy, gyy, gx, gy;
        S32 npoints=0;

        vector<CommFeaturePoint>::iterator featptr = featurelist.begin();
        // 初始化特征列表
        {
            S32 index;
            for (y = beginy; y < bordy; ++y)
                for (x = beginx; x < bordx; ++x)
                {
                    gxx = gxy = gyy = 0;
                    for (yy = y - bw; yy <= y + bw; ++yy)
                        for (xx = x - bw; xx <= x + bw; ++xx)
                        {
                            // TODO 改成指针形式的访问
                            index=yy*ImgWidth+ xx;
                            gx = dx[index];
                            gy = dy[index];
                            gxx += gx * gx;
                            gxy += gx * gy;
                            gyy += gy * gy;
                        }
                    featptr->X = x;
                    featptr->Y = y;
                    featptr->Quality = minEigenvalue(gxx, gxy, gyy);
                    ++featptr;
                    ++npoints;
                }
        }

        std::sort(featurelist.begin(), featurelist.begin()+npoints, std::greater<CommFeaturePoint>());

        --mindist;

        int pcount=0;
        //增大最小间距
        {
            memset(featuremap, 0, sizeof(featuremap));
            featptr = featurelist.begin();
            vector<CommFeaturePoint>::iterator flindex = featureOutput.begin();
            while(pcount<start)
            {
                fillMap(flindex->X,flindex->Y,featuremap);
                ++pcount;
                ++flindex;
            }
            S32 quality;
            while (npoints>0 && flindex<featureOutput.end())
            {
                x = featptr->X;
                y = featptr->Y;
                quality = featptr->Quality;
                if (featuremap[y * width + x] == 0 && quality >= mineigen)
                {
                    flindex->X = x;
                    flindex->Y = y;
                    flindex->Quality = quality;
                    fillMap(x, y, featuremap);
                    ++flindex;
                    ++pcount;
                }
                 ++featptr;
                --npoints;
            }

        }
        return pcount;
    }


}
// namespace itr_vision
