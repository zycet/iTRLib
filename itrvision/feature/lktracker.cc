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
#include <math.h>
namespace itr_vision
{
    LKTracker::LKTracker(const ImageGray& img1, const ImageGray& img2)
    {
        width[0] = img1.GetWidth();
        height[0] = img1.GetHeight();
        I[0].Allocate(width[0], height[0]);
        J[0].Allocate(width[0], height[0]);
        gradx1[0].Allocate(width[0], height[0]);
        gradx2[0].Allocate(width[0], height[0]);
        int L;
        // TODO 增加求微分的部分
        for (L = 1; L < 3; ++L)
        {
            width[L] = width[L - 1] >> 1;
            height[L] = height[L - 1] >> 1;
            I[L].Allocate(width[L], height[L]);
            J[L].Allocate(width[L], height[L]);
            gradx1[L].Allocate(width[L], height[L]);
            gradx2[L].Allocate(width[L], height[L]);
            grady1[L].Allocate(width[L], height[L]);
            grady2[L].Allocate(width[L], height[L]);
        }
        for(L=0;L<3;++L)
        {
            Gradient::Gradientx(I[L],gradx1[L]);
            Gradient::Gradienty(I[L],grady1[L]);
            Gradient::Gradientx(J[L],gradx2[L]);
            Gradient::Gradienty(J[L],grady2[L]);
        }
        GeneratePyramidal(img1, I, 3);
        GeneratePyramidal(img2, J, 3);
        windowWidth = 9;
        minDet = 1;
        level = 3;
        stopth = 0.1f;
    }

    LKTracker::~LKTracker()
    {
        // TODO Auto-generated destructor stub
    }

    void LKTracker::_ComputeDt(Point2D& U, Point2D& V, S32 L, S32 hw, S32* dt)
    {
        S32 y, x, g1, g2;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; y <= hw; ++x)
            {
                g1 = Scale::Interpolation(I[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(J[L], V.Y + y, V.X + x);
                *dt = g1 - g2;
                ++dt;
            }
    }
    void LKTracker::_ComputeGrad(Point2D& U, Point2D& V, S32 L, S32 hw, S32* dx, S32* dy)
    {
        S32 y, x, g1, g2;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; y <= hw; ++x)
            {
                g1 = Scale::Interpolation(gradx1[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(gradx2[L], V.Y + y, V.X + x);
                *dx++ = g1 + g2;
                g1 = Scale::Interpolation(grady1[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(grady2[L], V.Y + y, V.X + x);
                *dy++ = g1 + g2;
                // TODO 计算两幅图的微分和
            }
    }

    S32 LKTracker::_ComputeSum(S32* a, S32* b, S32* sum, S32 length)
    {
        S32 result;
        itr_math::CalculateObj->Multi(a, b, length, sum);
        itr_math::CalculateObj->AddSum(sum, length, result);
        return result;
    }

    LKTracker::TrackResult LKTracker::Compute(Point2D& U, Point2D& V, int L, bool Forward)
    {
        S32 hw = windowWidth >> 1;
        S32 length = width[L] * height[L];
        S32 *dt = new S32[length]();
        S32 *dx = new S32[length]();
        S32 *dy = new S32[length]();
        S32 *sum = new S32[length]();
        F32 det, speedx, speedy;
        S32 gxx, gxy, gyy, ex, ey;

        for (int i = 0; i < 10 && (fabs(speedx) > stopth || fabs(speedy) > stopth); ++i)
        {
            if (U.X - hw < 0 || U.Y - hw < 0 || V.X - hw < 0 || V.Y - hw < 0 || U.X + hw >= width[L]
                    || U.Y + hw >= height[L] || V.X + hw >= width[L] || V.Y + hw >= height[L])
            {
                return OOB;
            }
            _ComputeDt(U, V, L, hw, dt);
            _ComputeGrad(U, V, L, hw, dx, dy);
            gxx = _ComputeSum(dx, dx, sum, length);
            gxy = _ComputeSum(dx, dy, sum, length);
            gyy = _ComputeSum(dy, dy, sum, length);
            ex = _ComputeSum(dx, dt, sum, length);
            ey = _ComputeSum(dy, dt, sum, length);
            det = gxx * gyy - gxy * gxy;
            if (det < minDet)
                return SmallDet;
            det = 1 / det;
            speedx = (gyy * ex - gxy * ey) * det;
            speedy = (gxx * ey - gxy * ex) * det;
            V.X += speedx;
            V.Y += speedy;
        }
        // TODO  大残差的解决
        return Tracked;
    }

    void LKTracker::Compute(vector<FeaturePoint>& fl, bool Forward)
    {
        vector<FeaturePoint>::iterator feat = fl.begin();
        Point2D U, V;
        S32 l;
        LKTracker::TrackResult result;
        while (feat != fl.end())
        {
            U.X = (feat->x) >> level;
            U.Y = (feat->y) >> level;
            V.X = U.X;
            V.Y = U.Y;
            for (l = level - 1; l >= 0; --l)
            {
                U.X *= 2;
                U.Y *= 2;
                V.X *= 2;
                V.Y *= 2;
                result = Compute(U, V, l, Forward);
                if (result != Tracked)
                    break;
            }
            if (result != Tracked)
            {
                feat->value = -1;
            }
            ++feat;
        }
    }

    void LKTracker::GeneratePyramidal(const ImageGray& img, ImageGray py[], S32 length)
    {
        --length;
        MemoryCopy(py[0].GetPixels(), img.GetPixels(), img.GetPixelsNumber());
        for (; length > 0; --length)
            Scale::Bilinear(img, py[length]);
    }

} // namespace itr_vision
