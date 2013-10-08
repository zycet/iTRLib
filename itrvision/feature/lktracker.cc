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

namespace itr_vision
{
    LKTracker::LKTracker(const ImageGray& img1, const ImageGray& img2)
    {
        width[0] = img1.GetWidth();
        height[0] = img1.GetHeight();
        I[0].Allocate(width[0], height[0]);
        J[0].Allocate(width[0], height[0]);
        for (int L = 1; L < 3; ++L)
        {
            width[L] = width[L - 1] >> 1;
            height[L] = height[L - 1] >> 1;
            I[L].Allocate(width[L], height[L]);
            J[L].Allocate(width[L], height[L]);
        }
        GeneratePyramidal(img1, I, 3);
        GeneratePyramidal(img2, J, 3);
        windowWidth = 9;
    }

    LKTracker::~LKTracker()
    {
        // TODO Auto-generated destructor stub
    }

    void LKTracker::_ComputeDt(Point2D& U, Point2D& V, int L, int hw, S32* dt)
    {
        S32 y, x, g1, g2;
        for (y = -hw; y <= hw; ++y)
            for (x = -hw; y <= hw; ++x)
            {
                g1 = Scale::Interpolation(I[L], U.Y + y, U.X + x);
                g2 = Scale::Interpolation(J[L], V.Y + y, V.X + x);
                *dt=g1-g2;
                ++dt;
            }
    }
    LKTracker::TrackResult LKTracker::Compute(Point2D& U, Point2D& V, int L, bool Forward)
    {
        S32 hw = windowWidth >> 1;
        S32 *dt = new S32[width[L] * height[L]]();
        S32 *dx = new S32[width[L] * height[L]]();
        S32 *dy = new S32[width[L] * height[L]]();

        for (int i = 0; i < 10; ++i)
        {
            if (U.X - hw < 0 || U.Y - hw < 0 || V.X - hw < 0 || V.Y - hw < 0 || U.X + hw >= width[L]
                    || U.Y + hw >= height[L] || V.X + hw >= width[L] || V.Y + hw >= height[L])
            {
                return OOB;
            }
            _ComputeDt(U, V, L, hw, dt);

        }
        return Tracked;
    }

    void LKTracker::GeneratePyramidal(const ImageGray& img, ImageGray py[], S32 length)
    {
        --length;
        MemoryCopy(py[0].GetPixels(), img.GetPixels(), img.GetPixelsNumber());
        for (; length > 0; --length)
            Scale::Bilinear(img, py[length]);
    }

} // namespace itr_vision
