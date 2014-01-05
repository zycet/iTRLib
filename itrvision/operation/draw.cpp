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
 * draw.cpp
 *  Created on: 2013-10-9
 *      Author: ghdawn
 */

#include "draw.h"
namespace itr_vision
{
    void Draw::Circle(itr_math::Matrix &Img, S32 x, S32 y, S32 r, S16 color)
    {
        int i, j;
        int width = Img.GetCol();
        int height = Img.GetRow();
        for (i = -r; i < r; i++)
        {
            j = sqrt(r * r - i * i);
            Img((j + y + height) % height, (i + x + width) % width) = color;
            Img((-j + y + height) % height, (i + x + width) % width) = color;
            Img((i + y + height) % height, (j + x + width) % width) = color;
            Img((i + y + height) % height, (-j + x + width) % width) = color;
        }
    }
    void Draw::Circle(ImageARGB &Img, S32 x, S32 y, S32 r, U32 color)
    {
        int i, j;
        int width = Img.GetWidth();
        int height = Img.GetHeight();
        for (i = -r; i < r; i++)
        {
            j = sqrt(r * r - i * i);
            Img((j + y + height) % height, (i + x + width) % width) = color;
            Img((-j + y + height) % height, (i + x + width) % width) = color;
            Img((i + y + height) % height, (j + x + width) % width) = color;
            Img((i + y + height) % height, (-j + x + width) % width) = color;
        }
    }

    void Draw::LineOffset(Matrix &Img, S32 X, S32 Y, S32 offsetx, S32 offsety, S16 color)
    {
        float l = sqrt(offsetx * offsetx + offsety * offsety);
        float x = X, y = Y;
//        printf("X:(%d,%d)\nU:(%d,%d)\n",X,Y,offsetx,offsety);
        for (int i = 0; i < l; ++i)
        {
            x += (offsetx / l);
            y += (offsety / l);
//                printf("%f,%f  ",x,y);
            Img((int) y, (int) x) = color;
        }
    }
    void Draw::LineOffset(ImageARGB &Img, S32 x, S32 y, S32 offsetx, S32 offsety, U32 color)
    {
        int i, j;
        if (offsetx == 0)
        {
            if (offsety >= 0)
            {
                for (i = 0; i <= offsety; i++)
                {
                    Img(y + i, x) = color;
                }
            }
            else
            {
                for (i = 0; i >= offsety; i--)
                {
                    Img(y + i, x) = color;
                }
            }
        }
        else
        {
            j = offsety / offsetx;
            if (offsetx >= 0)
            {
                for (i = 0; i <= offsetx; i++)
                {
                    Img(y + i * j, x + i) = color;
                }
            }
            else
            {
                for (i = 0; i >= offsetx; i--)
                {
                    Img(y + i * j, x + i) = color;
                }
            }

        }
    }
    void Draw::Line(Matrix &Img, S32 beginx, S32 beginy, S32 endx, S32 endy, S16 color)
    {
        int i, j;
        i = endx - beginx;
        j = endy - beginy;
        LineOffset(Img, beginx, beginy, i, j, color);
    }
    void Draw::Line(ImageARGB &Img, S32 beginx, S32 beginy, S32 endx, S32 endy, U32 color)
    {
        int i, j;
        i = endx - beginx;
        j = endy - beginy;
        LineOffset(Img, beginx, beginy, i, j, color);
    }
    void Draw::Cross(Matrix &bmp, S32 x, S32 y, S32 scale, S16 color)
    {
        LineOffset(bmp, x, y, 0, scale, color);
        LineOffset(bmp, x, y, 0, -scale, color);
        LineOffset(bmp, x, y, scale, 0, color);
        LineOffset(bmp, x, y, -scale, 0, color);
    }
    void Draw::Cross(ImageARGB &bmp, S32 x, S32 y, S32 scale, U32 color)
    {
        LineOffset(bmp, x, y, 0, scale, color);
        LineOffset(bmp, x, y, 0, -scale, color);
        LineOffset(bmp, x, y, scale, 0, color);
        LineOffset(bmp, x, y, -scale, 0, color);
    }
    void Draw::Rectangle(Matrix &Img, RectangleS rect, S16 color)
    {
        LineOffset(Img, rect.X, rect.Y, rect.Width, 0, color);
        LineOffset(Img, rect.X, rect.Y, 0, rect.Height, color);
        LineOffset(Img, rect.X + rect.Width, rect.Y, 0, rect.Height, color);
        LineOffset(Img, rect.X, rect.Y + rect.Height, rect.Width, 0, color);
    }
    void Draw::Rectangle(ImageARGB &Img, RectangleS rect, U32 color)
    {
        LineOffset(Img, rect.X, rect.Y, rect.Width, 0, color);
        LineOffset(Img, rect.X, rect.Y, 0, rect.Height, color);
        LineOffset(Img, rect.X + rect.Width, rect.Y, 0, rect.Height, color);
        LineOffset(Img, rect.X, rect.Y + rect.Height, rect.Width, 0, color);
    }

    void Draw::Correspond(const Matrix &Img1, const Matrix &Img2,
                          const vector<FeaturePoint> &feature1, const vector<FeaturePoint> &feature2,S32 FeatureNum,
                          Matrix &Result)
    {
        Result.Init(Img1.GetRow() , Img1.GetCol()* 2 + 10);
        int offset = Img1.GetCol() + 10;
        for (int i = 0; i < Img1.GetCol(); i++)
            for (int j = 0; j < Img1.GetRow(); j++)
            {
                Result(j, i) = Img1(j, i);
                Result(j, i + offset) = Img2(j, i);
            }
        for (int i = 0; i < FeatureNum; i++)
        {
            if (feature2[i].value >= 0)
            {
                Line(Result, feature1[i].x, feature1[i].y, feature2[i].x + offset, feature2[i].y,
                255);
                Circle(Result,feature1[i].x, feature1[i].y,2,255);
                Circle(Result,feature2[i].x + offset, feature2[i].y,2,255);
            }
        }
    }
} // namespace itr_vision
