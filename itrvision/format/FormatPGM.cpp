/*
 * FormatPGM.cpp
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#include "FormatPGM.h"

namespace itr_vision
{
    FormatPGM::FormatPGM()
    {
    }

    FormatPGM::~FormatPGM()
    {
    }

    IFormat::ConvertResult FormatPGM::GetInfo(U8* Data, S32 Length, ImageInfo& ImgInfo)
    {
        U8 head1, head2;
        S32 width, height;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        if ((head1 != 'P') || (head2 != '5'))
            return IFormat::FormatIllegal;
        if (Length != (width * height + 4))
            return IFormat::LengthIllegal;
        ImgInfo.Width = width;
        ImgInfo.Height = height;
        ImgInfo.ColorChannel = 3;
        ImgInfo.PixelSize = 3;
        return IFormat::Success;
    }

    IFormat::ConvertResult FormatPGM::ToImage(U8* Data, S32 Length, ImageGray& Img)
    {
        U8 head1, head2;
        S32 width, height;
        S32 bit;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        str >> bit;

        if ((head1 != 'P') || (head2 != '5'))
            return IFormat::FormatIllegal;
        if (Length != (width * height + 4))
            return IFormat::LengthIllegal;
        U8 data;
        S16* img=Img.GetPixels();
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                str >> data;
                (*img) = data;
                ++img;
            }
        }
        return IFormat::Success;
    }

    IFormat::ConvertResult FormatPGM::ToBinary(ImageGray& Img, U8* Data, S32& Length)
    {
        stringstream str;
        str << "P6" << '\n';
        str << Img.GetWidth() << ' ' << Img.GetHeight() << '\n';
        S16* data = Img.GetPixels();
        U8 p;
        for (int i = 0; i < Img.GetPixelsNumber(); ++i)
        {
            p = *data++;
            str << p;
        }
    }
} // namespace itr_vision
