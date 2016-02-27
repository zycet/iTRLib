//
// Created by gaohan02 on 15-6-1.
//
#include <math.h>
#include "meanshift.h"

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

        for (int y = 0; y < rect.Height; y++)
            for (int x = 0; x < rect.Width; x++)
            {
                weight(y, x) = getweight(x, y);
                weightsum += weight(y, x);
            }
        weightsum = 1.0f / weightsum;
        weight.AllMul(weightsum);
        for (int y = 0; y < rect.Height; ++y)
        {
            for (int x = 0; x < rect.Width; ++x)
            {
                histq[img(rect.Y + y, rect.X + x)] += weight(y, x);
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
            for (int y = 0; y < rect.Height; ++y)
            {
                for (int x = 0; x < rect.Width; ++x)
                {
                    index = (S32) img(posy + y, posx + x);
                    histp[img(posy + y, posx + x)] += weight(y, x);
                }
            }
            Vector w(binCount);
            for (int k = 0; k < binCount; k++)
            {
                if (histp[k] != 0)
                    w[k] = sqrtf(histq[k] / histp[k]);
                else
                    w[k] = 0;
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
}
