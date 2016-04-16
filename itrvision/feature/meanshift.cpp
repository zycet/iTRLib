//
// Created by gaohan02 on 15-6-1.
//
#include <math.h>
#include "meanshift.h"
#include "../itrvision.h"

using itr_math::Matrix;
using itr_math::Vector;
using itr_math::RectangleF;

namespace itr_vision
{
    const int MeanShift::IMG_GRAY = 256;
    const int MeanShift::IMG_RGB = 4096;

    float MeanShift::getweight(int x, int y)
    {
        float a = x - halfx, b = y - halfy;
        float dis = a * a + b * b;
        dis /= radius;
        if (dis >= 1)
            return 0.0f;
        else
            return 1 - dis;
    }

    void MeanShift::Init(const Matrix &img, const RectangleF &rect, int binCount)
    {
        halfx = rect.Width / 2;
        halfy = rect.Height / 2;
        radius = halfx * halfx + halfy * halfy;
        float weightsum = 0;
        weight.Init(rect.Height, rect.Width);
        histq.Init(binCount);
        F32 *pweight = weight.GetData();
        for (int y = 0; y < rect.Height; y++)
            for (int x = 0; x < rect.Width; x++)
            {
                *pweight = getweight(x, y);
                weightsum += *pweight;
                ++pweight;
            }
        weightsum = 1.0f / weightsum;
        weight.AllMul(weightsum);
        F32 *pimg;
        pweight = weight.GetData();
        for (int y = 0; y < rect.Height; ++y)
        {
            pimg = img.GetData() + (S32) rect.Y * img.GetCol() + (S32) rect.X;
            for (int x = 0; x < rect.Width; ++x)
            {
                histq[*pimg++] += *pweight++;
            }
        }
        this->binCount = binCount;

    }

    void MeanShift::Go(const Matrix &img, RectangleF &rect)
    {
        F32 deltax = 1, deltay = 1, sum = 0;
        float ncc = 1;
        int iter = 0;
        int index;
        float posy = rect.Y, posx = rect.X;
        while ((deltax * deltax + deltay * deltay > 0.1) && (iter < 20))
        {
            iter++;
            sum = 0;
            deltax = deltay = 0;
            Vector histp(binCount);
            F32 *pweight = weight.GetData();
            for (int y = 0; y < rect.Height; ++y)
            {
                for (int x = 0; x < rect.Width; ++x)
                {
                    index = (S32) img(posy + y, posx + x);
                    histp[index] += *pweight++;
                }
            }
            Vector w(binCount);
            F32 *phistp = histp.GetData(), *phistq = histq.GetData(), *pw = w.GetData();
            for (int k = 0; k < binCount; k++)
            {
                if (*phistp != 0)
                    *pw = sqrtf(*phistq / *phistp);
                else
                    *pw = 0;
                ++pw;
                ++phistp;
                ++phistq;
            }
            for (int y = 0; y < rect.Height; ++y)
            {
                for (int x = 0; x < rect.Width; ++x)
                {
                    index = (S32) img(posy + y, posx + x);
                    sum += w[index];
                    deltax += w[index] * (x - halfx);
                    deltay += w[index] * (y - halfy);
                }
            }
            deltax /= sum;
            deltay /= sum;
            posx += deltax;
            posy += deltay;

        }

        rect.X = posx;
        rect.Y = posy;
//        printf("%f %f\n", posx, posy);
    }

    void MeanShift::ChangeFormat(U8 *pic, Matrix &img, int encoderwidth, int encoderheight)
    {
        Matrix img_origin(encoderheight, encoderwidth);
        S32 *pimgI = (S32 *) img_origin.GetData();
        itr_vision::ColorConvert::yuv420p2rgb(pimgI, pic, encoderwidth, encoderheight);
        itr_vision::Scale::SubSampling(img_origin, img, img.GetCol()/encoderwidth );
        pimgI = (S32 *) img.GetData();
        F32 *pimgF = (F32 *) img.GetData();
        for (int i = 0; i < encoderheight; i++)
        {
            for (int j = 0; j < encoderwidth; j++)
            {
                U8 r, g, b;
                r = (U8) ((*pimgI & 0xff0000) >> 16);
                g = (U8) ((*pimgI & 0xff00) >> 8);
                b = (U8) (*pimgI & 0xff);
                int a = ((r & 0xf0) << 4) | ((g & 0xf0)) | ((b & 0xf0) >> 4);
                img(i, j) = a;
                *pimgF = (F32) a;
                pimgF++;
                pimgI++;
            }
        }
    }
}
