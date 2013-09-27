/*
 * FormatPPM.cpp
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#include "FormatPPM.h"
#include <sstream>
#include <math.h>
#include <assert.h>
using std::stringstream;

namespace itr_vision
{
    FormatPPM::FormatPPM()
    {
    }

    FormatPPM::~FormatPPM()
    {
    }

    IFormat::ConvertResult FormatPPM::GetInfo(U8* Data, S32 Length, ImageInfo& ImgInfo)
    {
        U8 head1, head2;
        S32 width, height;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        if ((head1 != 'P') || (head2 != '6'))
            return IFormat::FormatIllegal;
        if (Length != (width * height * 3 + 4))
            return IFormat::LengthIllegal;
        ImgInfo.Width = width;
        ImgInfo.Height = height;
        ImgInfo.ColorChannel = 3;
        ImgInfo.PixelSize = 3;
        return IFormat::Success;
    }

    IFormat::ConvertResult FormatPPM::ToImage(U8* Data, S32 Length, ImageARGB& Img)
    {
        U8 head1, head2;
        S32 width, height;
        S32 bit;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        str >> bit;
        bit=9;
        bit+=(width>1000)?4:((width>100)?3:(width>10?2:1));
        bit+=(height>1000)?4:((height>100)?3:(height>10?2:1));
        if ((head1 != 'P') || (head2 != '6'))
            return IFormat::FormatIllegal;
        if (Length != (width * height * 3 + bit))
            return IFormat::LengthIllegal;
        U8 r, g, b;
        U32 data;
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                str >> r >> g >> b;
                data = (r << 16) | (g << 8) | b;
                Img(j, i) = data;
            }
        }
        return IFormat::Success;
    }

    IFormat::ConvertResult FormatPPM::ToImage(U8* Data, S32 Length, ImageGray& Img)
    {
        char head1, head2;
        int width, height;
        int bit;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        str >> bit;
        bit=9;
        bit+=(width>1000)?4:((width>100)?3:(width>10?2:1));
        bit+=(height>1000)?4:((height>100)?3:(height>10?2:1));
        if ((head1 != 'P') || (head2 != '6'))
            return IFormat::FormatIllegal;
        if (Length != (width * height * 3 + bit))
            return IFormat::LengthIllegal;
        U8 r, g, b;
        S16 data;
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                str >> r >> g >> b;
                data = floor(0.299 * r + 0.587 * g + 0.114 * b);
                Img(j, i) = data;
            }
        }
        return IFormat::Success;
    }

    IFormat::ConvertResult FormatPPM::ToBinary(ImageARGB& Img, U8* Data, S32& Length)
    {
        if (Length < (Img.GetWidth() * Img.GetHeight() * 3 + 15))
            return IFormat::LengthIllegal;
        stringstream str;
        str << "P6" << '\n';
        str << Img.GetWidth() << ' ' << Img.GetHeight() << '\n';
        str<<255<<'\n';
        U32* data = Img.GetPixels();
        U8 r, g, b;
        for (int i = 0; i < Img.GetPixelsNumber(); ++i)
        {
            r = (*data) >> 16;
            g = ((*data) & 0xFF00) >> 8;
            b = (*data) & 0xFF;
            str << r << g << b;
            ++data;
        }
        return IFormat::Success;
    }
    IFormat::ConvertResult FormatPPM::ToBinary(ImageGray& Img, U8* Data, S32& Length)
    {
        if (Length < (Img.GetWidth() * Img.GetHeight() * 3 + 15))
            return IFormat::LengthIllegal;
        stringstream str;
        str << "P6" << '\n';
        str << Img.GetWidth() << ' ' << Img.GetHeight() << '\n';
        str<<255<<'\n';
        S16* data = Img.GetPixels();
        U8 p;
        for (int i = 0; i < Img.GetPixelsNumber(); ++i)
        {
            p = *data;
            str << p << p << p;
            ++data;
        }
        return IFormat::Success;
    }
} // namespace itr_vision
