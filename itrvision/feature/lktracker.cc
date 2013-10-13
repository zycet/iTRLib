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
#include <stdio.h>

namespace itr_vision
{
    LKTracker::LKTracker(const ImageGray& Img1, const ImageGray& Img2)
    {
        windowWidth = 7;
        minDet = 10;
        level = 2;
        stopth = 0.1f;
        max_residue = 10;
        pyramid1.Init(Img1, 4, 2);
        pyramid2.Init(Img2, 4, 2);
        S32 length = windowWidth * windowWidth;

        Dx = new S32[length]();
        Dy = new S32[length]();
        Dt = new S32[length]();
        Sum = new S32[length]();
    }

    LKTracker::~LKTracker()
    {
        delete[] Dt;
        delete[] Dx;
        delete[] Dy;
        delete[] Sum;
    }

    void LKTracker::_ComputeDt(Point2D& U, Point2D& V, S32 L, S32 hw, S32* dt)
    {
        S32 y, x, g1, g2;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; x <= hw; ++x)
            {
                g1 = Scale::Interpolation(pyramid1.img[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(pyramid2.img[L], V.Y + y, V.X + x);
                *dt++ = g1 - g2;
            }
    }
    void LKTracker::_ComputeGrad(Point2D& U, Point2D& V, S32 L, S32 hw, S32* dx, S32* dy)
    {
        S32 y, x, g1, g2;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; x <= hw; ++x)
            {
                g1 = Scale::Interpolation(pyramid1.gradx[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(pyramid2.gradx[L], V.Y + y, V.X + x);
                *dx++ = g1 + g2;
                g1 = Scale::Interpolation(pyramid1.grady[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(pyramid2.grady[L], V.Y + y, V.X + x);
                *dy++ = g1 + g2;
            }
    }
    void LKTracker::_ComputeGrad2(Point2D& U, S32 L, S32 hw, S32* dx, S32* dy)
    {
        S32 y, x;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; x <= hw; ++x)
            {
                *dx++ = Scale::Interpolation(pyramid1.gradx[L], U.Y + y, U.X + x);
                *dy++ = Scale::Interpolation(pyramid1.grady[L], U.Y + y, U.X + x);
            }
    }
    S32 LKTracker::_ComputeSum(S32* a, S32* b, S32* sum, S32 length)
    {
        S32 result;
        itr_math::CalculateObj->Multi(a, b, length, sum);
        itr_math::CalculateObj->AddSum(sum, length, result);
        return result;
    }
    S32 LKTracker::_SumDiff(S32 *a, S32 length)
    {
        int ans = 0;
        while (length--)
            ans += *a++;
        return ans;
    }
    LKTracker::TrackResult LKTracker::Compute(Point2D& U, Point2D& V, int L, bool Forward)
    {
        S32 hw = windowWidth >> 1;
        S32 length = windowWidth * windowWidth;

        F32 det, speedx = 1, speedy = 1;
        S32 gxx, gxy, gyy, ex, ey;
        LKTracker::TrackResult result = Tracked;
//        _ComputeGrad2(U, L, hw, Dx, Dy);
        for (int i = 0; i < 10 && (fabs(speedx) > stopth || fabs(speedy) > stopth); ++i)
        {
            if (U.X - hw < 0 || U.Y - hw < 0 || V.X - hw < 0 || V.Y - hw < 0
                    || U.X + hw >= pyramid1.width[L] || U.Y + hw >= pyramid1.height[L]
                    || V.X + hw >= pyramid1.width[L] || V.Y + hw >= pyramid1.height[L])
            {
                result = OOB;
                break;
            }

            _ComputeGrad(U, V, L, hw, Dx, Dy);
            _ComputeDt(U, V, L, hw, Dt);
            gxx = _ComputeSum(Dx, Dx, Sum, length);
            gxy = _ComputeSum(Dx, Dy, Sum, length);
            gyy = _ComputeSum(Dy, Dy, Sum, length);
            ex = _ComputeSum(Dx, Dt, Sum, length);
            ey = _ComputeSum(Dy, Dt, Sum, length);
            det = gxx * gyy - gxy * gxy;
            if (det < minDet)
            {
                result = SmallDet;
                break;
            }
            det = 1 / det;
            speedx = (gyy * ex - gxy * ey) * det;
            speedy = (gxx * ey - gxy * ex) * det;
            V.X += speedx;
            V.Y += speedy;
        }
        _ComputeDt(U, V, L, hw, Dt);
        if (_SumDiff(Dt, length) / (length) > max_residue)
            result = LARGE_RESIDUE;
        // TODO  大残差的解决
        return result;
    }

    void LKTracker::Compute(vector<FeaturePoint>& fl, bool Forward)
    {
        vector<FeaturePoint>::iterator feat = fl.begin();
        Point2D U, V;
        S32 l, i;
        LKTracker::TrackResult result;
        int subsampling = pyramid1.GetSubsampling();
        while (feat != fl.end())
        {
            for (i = 0; i < level; ++i)
            {
                U.X = (feat->x) / subsampling;
                U.Y = (feat->y) / subsampling;
            }
            V.X = U.X;
            V.Y = U.Y;
            for (l = level - 1; l >= 0; --l)
            {
                U.X *= subsampling;
                U.Y *= subsampling;
                V.X *= subsampling;
                V.Y *= subsampling;
                result = Compute(U, V, l, Forward);
                if (result != Tracked)
                    break;
            }
            if (result != Tracked)
            {
                feat->value = -1;
            }
            feat->x = V.X;
            feat->y = V.Y;
            ++feat;
        }
    }

} // namespace itr_vision

