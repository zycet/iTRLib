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
 * convolutesquare.cc
 *  Created on: 2013-9-27
 *      Author: buaa
 */

#include "convolutesquare.h"
#include "itrbase.h"
#include <math.h>

namespace itr_vision
{

    ConvoluteSquare::ConvoluteSquare()
    {
        sigma_last = -10.0f;
        Buffer=NULL;
    }
    ConvoluteSquare::ConvoluteSquare( S32 Width, S32 Height)
    {
        sigma_last = -10.0f;
        Buffer=new F32[Width*Height];
    }

    ConvoluteSquare::~ConvoluteSquare()
    {
        if(Buffer!=NULL)
        {
            delete Buffer;
        }
    }

    void ConvoluteSquare::_computeKernels(float sigma, ConvolutionKernel *gauss,
                                          ConvolutionKernel *gaussderiv)
    {
        const float factor = 0.01f; /* for truncating tail */
        int i;

        assert(MAX_KERNEL_WIDTH % 2 == 1);
        assert(sigma >= 0.0);

        /* Compute kernels, and automatically determine widths */
        {
            const int hw = MAX_KERNEL_WIDTH / 2;
            float max_gauss = 1.0f, max_gaussderiv = (float) (sigma * exp(-0.5f));

            /* Compute gauss and deriv */
            for (i = -hw; i <= hw; i++)
            {
                gauss->data[i + hw] = (float) exp(-i * i / (2 * sigma * sigma));
                gaussderiv->data[i + hw] = -i * gauss->data[i + hw];
            }

            /* Compute widths */
            gauss->width = MAX_KERNEL_WIDTH;
            for (i = -hw; fabs(gauss->data[i + hw] / max_gauss) < factor; i++, gauss->width -= 2)
                ;
            gaussderiv->width = MAX_KERNEL_WIDTH;
            for (i = -hw; fabs(gaussderiv->data[i + hw] / max_gaussderiv) < factor;
                    i++, gaussderiv->width -= 2)
                ;
        }

        /* Shift if width less than MAX_KERNEL_WIDTH */
        int offset=(MAX_KERNEL_WIDTH - gauss->width)>>1;
        for (i = 0; i < gauss->width; i++)
        {
            gauss->data[i] = gauss->data[i + offset ];
        }
        offset=(MAX_KERNEL_WIDTH - gaussderiv->width) >>1;
        for (i = 0; i < gaussderiv->width; i++)
        {
            gaussderiv->data[i] = gaussderiv->data[i + offset];
        }
        /* Normalize gauss and deriv */
        {
            const int hw = gaussderiv->width / 2;
            float den;

            den = 0.0;
            for (i = 0; i < gauss->width; i++)
            {
                den += gauss->data[i];
            }
            den=1.0/den;
            for (i = 0; i < gauss->width; i++)
            {
                gauss->data[i] *= den;
            }
            den = 0.0;
            for (i = -hw; i <= hw; i++)
            {
                den -= i * gaussderiv->data[i + hw];
            }
            den=1.0/den;
            for (i = -hw; i <= hw; i++)
            {
                gaussderiv->data[i + hw] *= den;
            }
        }

        sigma_last = sigma;
    }

    void ConvoluteSquare::_convolveImageHoriz(const Matrix &imgin, ConvolutionKernel kernel,
            Matrix &imgout)
    {
        F32 *ptrrow = imgin.GetData(); /* Points to row's first pixel */
        F32 *ptrout = imgout.GetData(), /* Points to next output pixel */
             *ppp;
        float sum;
        S32 radius = kernel.width >>1;
        S32 ncols = imgin.GetCol(), nrows = imgin.GetRow();
        S32 i, j, k;
        S32 uplimit;
        /* Kernel width must be odd */
        assert(kernel.width & 0x01 == 1);

        /* Must read from and write to different images */

        /* Output image must be large enough to hold result */
        assert(imgout.GetCol() >= imgin.GetCol());
        assert(imgout.GetRow() >= imgin.GetRow());

        /* For each row, do ... */
        for (j = 0; j < nrows; j++)
        {
            /* Zero leftmost columns */
            for (i = 0; i < radius; i++)
            {
                *ptrout++ = 0.0;
            }

            /* Convolve middle columns with kernel */
            uplimit=ncols-radius-radius;
            for (i=0; i < uplimit; i++)
            {
                ppp = ptrrow + i;
                sum = 0.0;
                for (k = kernel.width - 1; k >= 0; k--)
                {
                    sum += *ppp++ * kernel.data[k];
                }
                *ptrout++ = sum;
            }

            /* Zero rightmost columns */
            for (i=ncols-radius; i < ncols; i++)
            {
                *ptrout++ = 0.0;
            }
            ptrrow += ncols;
        }
    }

    /*********************************************************************
     * _convolveImageVert
     */

    void ConvoluteSquare::_convolveImageVert(const Matrix &imgin, ConvolutionKernel kernel,
            Matrix &imgout)
    {
        F32 *ptrcol = imgin.GetData(); /* Points to row's first pixel */
        F32 *ptrout = imgout.GetData(), /* Points to next output pixel */
             *ppp;
        S32 sum;
        S32 radius = kernel.width >>1;
        S32 ncols = imgin.GetCol(), nrows = imgin.GetRow();
        S32 i, j, k;
        S32 uplimits;
        /* Kernel width must be odd */
        assert(kernel.width & 0x01 == 1);

        /* Must read from and write to different images */
//        assert(imgin != imgout);
        /* Output image must be large enough to hold result */
        assert(imgout.GetCol() >= imgin.GetCol());
        assert(imgout.GetRow() >= imgin.GetRow());

        /* For each column, do ... */
        for (i = 0; i < ncols; i++)
        {

            /* Zero topmost rows */
            for (j = 0; j < radius; j++)
            {
                *ptrout = 0.0;
                ptrout += ncols;
            }

            /* Convolve middle rows with kernel */
            uplimits=nrows-radius-radius;
            for (j=0; j < uplimits; j++)
            {
                ppp = ptrcol + ncols * j;
                sum = 0.0;
                for (k = kernel.width - 1; k >= 0; k--)
                {
                    sum += *ppp * kernel.data[k];
                    ppp += ncols;
                }
                *ptrout = sum;
                ptrout += ncols;
            }

            /* Zero bottommost rows */
            for (j=nrows-radius; j < nrows; j++)
            {
                *ptrout = 0.0;
                ptrout += ncols;
            }

            ptrcol++;
            ptrout -= nrows * ncols - 1;
        }
    }

    void ConvoluteSquare::_KLTComputeSmoothedImage(const Matrix &img, float sigma, Matrix &smooth)
    {
        /* Output image must be large enough to hold result */
        assert(smooth.GetCol() >= img.GetCol());
        assert(smooth.GetRow() >= img.GetRow());

        /* Compute kernel, if necessary; gauss_deriv is not used */
        if (fabs(sigma - sigma_last) > 0.05)
        {
            _computeKernels(sigma, &gauss_kernel, &gaussderiv_kernel);
        }

        _convolveSeparate(img, gauss_kernel, gauss_kernel, smooth);
    }

    void ConvoluteSquare::_KLTComputeGradients(const Matrix &img, float sigma, Matrix &gradx,
            Matrix &grady)
    {
        if (fabs(sigma - sigma_last) > 0.05)
        {
            _computeKernels(sigma, &gauss_kernel, &gaussderiv_kernel);
        }

        _convolveSeparate(img, gaussderiv_kernel, gauss_kernel, gradx);
        _convolveSeparate(img, gauss_kernel, gaussderiv_kernel, grady);
    }

    void ConvoluteSquare::_convolveSeparate(const Matrix &imgin, ConvolutionKernel horiz_kernel,
                                            ConvolutionKernel vert_kernel, Matrix &imgout)
    {
        Matrix tmpimg;
        if(Buffer==NULL)
        {
            tmpimg.Init(imgin.GetRow(), imgin.GetCol());
        }
        else
        {
            tmpimg.Init(imgin.GetRow(), imgin.GetCol(),Buffer);
        }
        _convolveImageHoriz(imgin, horiz_kernel, tmpimg);
        _convolveImageVert(tmpimg, vert_kernel, imgout);
    }
} // namespace itr_image

