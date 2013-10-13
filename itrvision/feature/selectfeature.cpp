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

#include "selectseature.h"
#include <algorithm>
#include <string.h>
#include <math.h>
namespace itr_vision
{

    SelectFeature::SelectFeature(const ImageGray& Img, int WindowWidth) :
            img(Img)
    {
        bw = WindowWidth >> 1;
        mindist = 10;
        mineigen = 10;
        width = img.GetWidth();
        height = img.GetHeight();
        dx.Allocate(img.GetWidth(), img.GetHeight());
        dy.Allocate(img.GetWidth(), img.GetHeight());
        ConvoluteSquare conv;
        conv._KLTComputeSmoothedImage(Img, 0.7, img);
        // TODO 求微分
        conv._KLTComputeGradients(img,1,dx,dy);
    }

    void SelectFeature::fillMap(S32 x, S32 y, BOOL* featuremap)
    {
        int ix, iy;

        for (iy = y - mindist; iy <= y + mindist; iy++)
            for (ix = x - mindist; ix <= x + mindist; ix++)
                if (ix >= 0 && ix < width && iy >= 0 && iy < height)
                    featuremap[iy * width + ix] = 1;
    }

    SelectFeature::~SelectFeature()
    {
    }

    float SelectFeature::MinEigenvalue(float gxx, float gxy, float gyy)
    {
        itr_math::NumericalObj->Sqrt((gxx - gyy) * (gxx - gyy) + 4 * gxy * gxy, gxy);
        return (float) ((gxx + gyy - gxy) * 0.5f);
//        return (float) ((gxx + gyy - sqrt((gxx - gyy) * (gxx - gyy) + 4 * gxy * gxy)) *0.5f);/// 2.0f);
    }
    void SelectFeature::SelectGoodFeature(const RectangleS& rect, vector<FeaturePoint>& fl)
    {
        vector<FeaturePoint> featurelist(rect.Width * rect.Height);

        S32 bordy = rect.Y + rect.Height;
        S32 bordx = rect.X + rect.Width;
        S32 beginy = (rect.Y < bw) ? bw : rect.Y;
        S32 beginx = (rect.X < bw) ? bw : rect.X;
        if (bordy >= img.GetHeight() - bw)
            bordy = img.GetHeight() - bw;
        if (bordx >= img.GetWidth() - bw)
            bordx = img.GetWidth() - bw;
        S32 x, y, xx, yy;
        S32 gxx, gxy, gyy, gx, gy;
        vector<FeaturePoint>::iterator featptr = featurelist.begin();
        // 初始化特征列表
        {
            for (y = beginy; y < bordy; ++y)
                for (x = beginx; x < bordx; ++x)
                {
                    gxx = gxy = gyy = 0;
                    for (yy = y - bw; yy <= y + bw; ++yy)
                        for (xx = x - bw; xx <= x + bw; ++xx)
                        {
                            // TODO 改成指针形式的访问
                            gx = dx(yy, xx);
                            gy = dy(yy, xx);
                            gxx += gx * gx;
                            gxy += gx * gy;
                            gyy += gy * gy;
                        }
                    featptr->x = x;
                    featptr->y = y;
                    featptr->value = MinEigenvalue(gxx, gxy, gyy);
                    ++featptr;
                }
        }

        std::sort(featurelist.begin(), featurelist.end(), std::greater<FeaturePoint>());

        //增大最小间距
        {
            featptr = featurelist.begin();
            vector<FeaturePoint>::iterator flindex = fl.begin();
            BOOL *featuremap = new BOOL[img.GetHeight() * width]();
            memset(featuremap, 0, sizeof(featuremap));
            S32 value;
            while (featptr != featurelist.end())
            {
                x = featptr->x;
                y = featptr->y;
                value = featptr->value;
                if (featuremap[y * width + x] == 0 && value > mineigen)
                {
                    flindex->x = x;
                    flindex->y = y;
                    flindex->value = value;
                    fillMap(x, y, featuremap);
                    ++flindex;
                }
                if (flindex == fl.end())
                    break;
                ++featptr;
            }
            delete[] featuremap;
        }

    }

}
// namespace itr_vision
