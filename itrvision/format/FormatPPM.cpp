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
        // TODO Auto-generated constructor stub

    }

    FormatPPM::~FormatPPM()
    {
        // TODO Auto-generated destructor stub
    }

    IFormat::ConvertResult FormatPPM::GetInfo(U8* Data, S32 Length, ImageInfo& ImgInfo)
    {
        char head1, head2;
        int width, height;
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
        char head1, head2;
        int width, height;
        int bit;
        stringstream str;
        str << Data;
        str >> head1 >> head2;
        str >> width >> height;
        str >> bit;
        if ((head1 != 'P') || (head2 != '6'))
            return IFormat::FormatIllegal;
        if (Length != (width * height * 3 + 4))
            return IFormat::LengthIllegal;
        char r, g, b;
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
        if ((head1 != 'P') || (head2 != '6'))
            return IFormat::FormatIllegal;
        if (Length != (width * height * 3 + 4))
            return IFormat::LengthIllegal;
        char r, g, b;
        S16 data;
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                str>>r>>g>>b;
                data=floor(0.299*r+0.587*g+0.114*b);
                Img(j, i) = data;
            }
        }
        return IFormat::Success;
    }

} /* namespace itr_vision */
