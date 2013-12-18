/*
 * scale.cpp
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#include "scale.h"

namespace itr_vision
{

    Scale::Scale()
    {
        // TODO Auto-generated constructor stub

    }

    Scale::~Scale()
    {
        // TODO Auto-generated destructor stub
    }

    S16 Scale::Interpolation(const ImageGray &src, F32 y, F32 x)
    {
        const int FACTOR = 2048;
        const int BITS = 22;
        int x0, y0;
        int u, v, u_1, v_1;
        x0 = (int) (x);
        y0 = (int) (y);
        u = (x - x0) * FACTOR;
        v = (y - y0) * FACTOR;
        u_1 = FACTOR - u;
        v_1 = FACTOR - v;
        int result = (src(y0, x0) * u_1 + src(y0, x0 + 1) * u) * v_1
                     + (src(y0 + 1, x0) * u_1 + src(y0 + 1, x0 + 1) * u) * v;
        return (S16) (result >> BITS);
    }

    void Scale::Bilinear(const ImageGray &src, ImageGray &dst)
    {
        int width = dst.GetWidth(), height = dst.GetHeight();
        float fw = float(src.GetWidth()) / width;
        float fh = float(src.GetHeight()) / height;
        float x, y;
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                x = i * fw;
                y = j * fh;
                dst(j, i) = Interpolation(src, y, x);
            }
        }
    }

    void Scale::SubSampling(const ImageGray &src, ImageGray &dst, S32 scale)
    {
        assert(dst.MatchWidthHeight(src.GetWidth() / scale, src.GetHeight() / scale));
        for (int j = 0; j < dst.GetHeight(); ++j)
        {
            for (int i = 0; i < dst.GetWidth(); ++i)
            {
                dst(j, i) = src(j * scale, i * scale);
            }
        }
    }

    S32 Scale::Interpolation(const ImageARGB &src, F32 y, F32 x)
    {
        const int FACTOR = 2048;
        const int BITS = 22;
        int x0, y0;
        int u, v, u_1, v_1;
        x0 = (int) (x);
        y0 = (int) (y);
        u = (x - x0) * FACTOR;
        v = (y - y0) * FACTOR;
        u_1 = FACTOR - u;
        v_1 = FACTOR - v;
        int result = (src(y0, x0) * u_1 + src(y0, x0 + 1) * u) * v_1
                     + (src(y0 + 1, x0) * u_1 + src(y0 + 1, x0 + 1) * u) * v;
        return result >> BITS;
    }

    void Scale::Bilinear(const ImageARGB &src, ImageGray &dst)
    {
        int width = dst.GetWidth(), height = dst.GetHeight();
        float fw = float(src.GetWidth()) / width;
        float fh = float(src.GetHeight()) / height;
        float x, y;
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                x = i * fw;
                y = j * fh;
                dst(j, i) = Interpolation(src, y, x);
            }
        }
    }
    void Scale::SubSampling(const ImageARGB &src, ImageARGB &dst, S32 scale)
    {
        assert(dst.MatchWidthHeight(src.GetWidth() / scale, src.GetHeight() / scale));
        for (int j = 0; j < dst.GetHeight(); ++j)
        {
            for (int i = 0; i < dst.GetWidth(); ++i)
            {
                dst(j, i) = src(j * scale, i * scale);
            }
        }
    }

} /* namespace itr_vision */
