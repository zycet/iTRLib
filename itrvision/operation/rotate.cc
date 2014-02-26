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
 * rotate.cc
 *  Created on: 2013-11-27
 *      Author: buaa
 */

#include "rotate.h"
#include "scale.h"

namespace itr_vision
{
void Rotate::rotate(const Matrix &ImgInput, RectangleS &rect, F32 ang, Matrix &ImgOutput)
{
    assert(rect.Width>0&&rect.Height>0);
    Point2D center(rect.Width/2,rect.Height/2);

    assert(center.X>0&&center.Y>0);
    Transform2D trans;
    trans.Reset();
    trans.Rotate(ang);

    S32 Inputw=ImgInput.GetCol();
    S32 Inputh=ImgInput.GetRow();

    Point2D pin,pout;
    S32 x0,y0;

    for(int i=0; i<rect.Width; i++)
    {
        for(int j=0; j<rect.Height; j++)
        {
            pin.X=i-center.X;
            pin.Y=j-center.Y;
            trans.Transform(pin,pout);

            x0=pout.X+center.X+rect.X;
            y0=pout.Y+center.Y+rect.X;

            if((x0>0&&x0<Inputw)&&(y0<Inputh&&y0>0))
            {
                ImgOutput(j,i)=Scale::Interpolation(ImgInput,y0,x0);
            }

            else
            {
                ImgOutput(j,i)=0;
            }
        }
    }
}

} // namespace itr_vision
