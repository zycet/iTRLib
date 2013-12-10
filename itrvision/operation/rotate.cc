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
namespace itr_vision
{
    void Rotate::rotate(const ImageGray& ImgInput, RectangleS &rect, F32 ang, ImageGray& ImgOutput)
    {
        assert(rect.Width>0&&rect.Height>0);
        Point2D  center(rect.X+rect.Width/2,rect.Y+rect.Height/2);
        assert(center.X>0&&center.Y>0);
        Transform2D trans;
        trans.Rotate(ang);

        S32 Inputw;
        Inputw=ImgInput.GetWidth();


        Point2D pin,pout;
        S32 x0,y0;
        for(int i=0;i<rect.Height;i++)
        {
            for(int j=0;j<rect.Width;j++)
            {
              pin.X=i-center.X;
              pin.Y=j-center.Y;
              trans.Transform(pin,pout);
              x0=pout.X+center.X;
              y0=pout.Y+center.Y;
              if((x0>=0&&x0<rect.Width)&&(y0<rect.Height&&y0>=0))
              {
                  ImgOutput(i,j)=ImgInput[x0+y0*Inputw];
              }
              else
              {
                  ImgOutput(i,j)=0;
              }
            }
        }
    }

    void Rotate::rotate(const ImageARGB& ImgInput, RectangleS &rect, F32 ang, ImageARGB& ImgOutput)
    {
        assert(rect.Width>0&&rect.Height>0);
        Point2D  center(rect.X+rect.Width/2,rect.Y+rect.Height/2);
        assert(center.X>0&&center.Y>0);
        Transform2D trans;
        trans.Rotate(ang);

        S32 Inputw;
        Inputw=ImgInput.GetWidth();

        Point2D pin,pout;
        S32 x0,y0;
        for(int i=0;i<rect.Height;i++)
        {
            for(int j=0;j<rect.Width;j++)
            {
              pin.X=i-center.X;
              pin.Y=j-center.Y;
              trans.Transform(pin,pout);
              x0=pout.X+center.X;
              y0=pout.Y+center.Y;
              if((x0>=0&&x0<rect.Width)&&(y0<rect.Height&&y0>=0))
              {
                  ImgOutput(i,j)=ImgInput[x0+y0*Inputw];
              }
              else
              {
                  ImgOutput(i,j)=0;
              }
            }
        }
    }
} // namespace itr_vision
