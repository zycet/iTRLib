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

    ImageARGB Rotate::rotate(const ImageARGB& src, RectangleS &rect ,  F32 ang)
    {
        ImageARGB ta(rect.Width,rect.Height);
        Point2D  center(rect.X+rect.Width/2,rect.Y+rect.Height/2);

        Transform2D trans;      //旋转矩阵，旋转中心为原点
        trans.Rotate(ang);

        S32 srcw,srch;
        srcw=src.GetWidth();        //获取大图片的宽和高，用来判断是否超出图片范围
        srch=src.GetHeight();

        Point2D pin,pout;
        S32 x0,y0;
        for(int i=0;i<=rect.Width;i++)
        {
            for(int j=0;i<=rect.Height;j++)
            {
              pin.X=i-center.X;
              pin.Y=j-center.Y;
              trans.Transform(pin,pout);        //旋转坐标
              x0=pout.X+center.X;
              y0=pout.Y+center.Y;               //还原坐标
              if((x0>=0&&x0<=srcw)&&(y0<=srch&&y0>=0))
              {
                  ta[i,j]=src[x0+y0*srcw];      //出错了？重载运算符不是很明白。。。。。
              }
              else
              {
                  ta[i,j]=0;        //超出图片范围赋值0;
              }
            }
        }
        return(ta);
    }
} // namespace itr_vision
