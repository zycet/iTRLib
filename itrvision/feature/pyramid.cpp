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
 * pyramid.cpp
 *  Created on: 2013-10-13
 *      Author: ghdawn
 */

#include "pyramid.h"
#include "../operation/scale.h"
#include "../process/convolutesquare.h"
namespace itr_vision
{
Pyramid::Pyramid()
{
    level = 2;
    subsampling = 4;
    sigma = 1;
}
void Pyramid::Init(const Matrix &Img, int Subsampling, int Level)
{
    level = Level;
    subsampling = Subsampling;
    sigma = 0.9 * subsampling;
    //分配空间
    width[0] = Img.GetCol();
    height[0] = Img.GetRow();
    img[0].Init(height[0], width[0]);
    gradx[0].Init(height[0], width[0]);
    grady[0].Init(height[0], width[0]);
    Matrix tempimg(height[0], width[0]);
    int L;

    for (L = 1; L < level; ++L)
    {
        width[L] = width[L - 1] / subsampling;
        height[L] = height[L - 1] / subsampling;
        img[L].Init(height[L], width[L]);
        gradx[L].Init(height[L], width[L]);
        grady[L].Init(height[L], width[L]);
    }
    ConvoluteSquare conv;
    conv._KLTComputeSmoothedImage(Img, 0.7, img[0]);
    int subhalf = subsampling / 2;
    //int oldncols;
    for (L = 1; L < level; ++L)
    {
        conv._KLTComputeSmoothedImage(img[L - 1], sigma, tempimg);
        for (int y = 0 ; y < height[L] ; y++)
            for (int x = 0 ; x < width[L]  ; x++)
                img[L][y*width[L]+x] =
                    tempimg[(subsampling*y+subhalf)*width[L-1] +
                            (subsampling*x+subhalf)];
    }

    for (L = 0; L < level; ++L)
    {
        conv._KLTComputeGradients(img[L], 1, gradx[L], grady[L]);
    }
}

Pyramid::~Pyramid()
{
    // TODO Auto-generated destructor stub
}

} // namespace itr_vision
