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

    void Rotate::Update(Point2D point,F32 &xmax,F32 &xmin,F32 &ymax,F32 &ymin )
    {
        if (xmax<point.X)
        {
            xmax=point.X;
        }
        else if(xmin>point.X)
        {
            xmin=point.X;
        }
        if (ymax<point.Y)
        {
            ymax=point.Y;
        }
    }
    void Rotate::rotate(const Matrix &imgInput, RectangleS &rect, F32 ang, Matrix &imgOutput)
    {
        assert(rect.Width>0&&rect.Height>0);
        Point2D center(rect.Width/2,rect.Height/2);

        F32 xmax,xmin,ymax,ymin;
        Point2D pin,pout;
        Transform2D trans;
        trans.Reset();
        trans.Rotate(ang);

        pin.SetXY(-center.X,-center.Y);
        trans.Transform(pin,pout);
        xmax=xmin=pout.X;
        ymax=ymin=pout.Y;

        pin.SetXY(-center.X+0,rect.Height-center.Y);
        trans.Transform(pin,pout);
        Update(pout,xmax,xmin,ymax,ymin);

        pin.SetXY(-center.X+rect.Width,0-center.Y);
        trans.Transform(pin,pout);
        Update(pout,xmax,xmin,ymax,ymin);

        pin.SetXY(-center.X+rect.Width,rect.Height-center.Y);
        trans.Transform(pin,pout);
        Update(pout,xmax,xmin,ymax,ymin);
        imgOutput.Init(ymax-ymin,xmax-xmin);

        S32 x0,y0;

        for(int j=0; j<imgOutput.GetRow(); j++)
        {
            for(int i=0; i<imgOutput.GetCol(); i++)
            {
                pin.X=i-imgOutput.GetCol()/2;
                pin.Y=j-imgOutput.GetRow()/2;
                trans.Transform(pin,pout);

                x0=pout.X+center.X+rect.X;
                y0=pout.Y+center.Y+rect.Y;
                if((x0>=0&&x0<imgInput.GetCol())&&(y0<imgInput.GetRow()&&y0>=0))
                {
                    imgOutput(j,i)=itr_vision::Scale::Interpolation(imgInput,y0,x0);
                }
                else
                {
                    imgOutput(j,i)=0;
                }

            }
        }

    }

} // namespace itr_vision
