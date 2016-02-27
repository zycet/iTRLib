//
// Created by ghdawn on 16-2-27.
//

#include "colorconvert.h"

void ColorConvert::yuv420sp2rgb(S32 *rgb, U8 *yuv, S32 width, S32 height)
{
    int frameSize = width * height;
    int i, j;

    int yp, y, u, v, r, g, b;
    int y1192;

    U8 *pY = yuv;
    U8 *pUV;
    int result;
    for (i = 0, yp = 0; i < height; i++)
    {
        int uvp = frameSize + (i >> 1) * width;
        pUV = yuv + uvp;
        u = v = 0;
        for (j = 0; j < width; j++)
        {
            y = (0xff & ((int) *pY++)) - 16;
            y = (y < 0) ? 0 : y;
            if ((j & 1) == 0)
            {
                v = (0xff & *pUV++) - 128;
                u = (0xff & *pUV++) - 128;
            }
            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);
            if (r < 0) r = 0;
            else if (r > 262143) r = 262143;
            if (g < 0) g = 0;
            else if (g > 262143) g = 262143;
            if (b < 0) b = 0;
            else if (b > 262143) b = 262143;

            result = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00) | ((b >> 10) & 0xff);
            rgb[i * width + j] = result;
        }
    }
}

void ColorConvert::yuv420p2rgb(S32 *rgb, U8 *yuv, S32 width, S32 height)
{
    int frameSize = width * height;
    int i, j;

    int y, u, v, r, g, b;
    int y1192;

    U8 *pY = yuv;
    U8 *pU;
    U8 *pV;
    int result;
    for (i = 0; i < height; i++)
    {
        pV = yuv + frameSize + (i >> 1) * width;
        pU = yuv + frameSize + frameSize / 4 + (i >> 1) * width;

        u = v = 0;
        for (j = 0; j < width; j++)
        {
            y = (0xff & ((int) *pY++)) - 16;
            y = (y < 0) ? 0 : y;
            if ((j & 1) == 0)
            {
                v = (0xff & *pV++) - 128;
                u = (0xff & *pU++) - 128;
            }
            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);
            if (r < 0) r = 0;
            else if (r > 262143) r = 262143;
            if (g < 0) g = 0;
            else if (g > 262143) g = 262143;
            if (b < 0) b = 0;
            else if (b > 262143) b = 262143;

            result = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00) | ((b >> 10) & 0xff);
            rgb[i * width + j] = result;
        }
    }
}



