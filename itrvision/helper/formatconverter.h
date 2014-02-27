#ifndef FORMATCONVERTER_H
#define FORMATCONVERTER_H

#include "itrbase.h"

using itr_math::Matrix;

namespace itr_vision
{

/**
* \brief 此类用于将相机采集的各种Raw进行转换
*/
class FormatConverter
{
public:
    enum RawFormat
    {
        RawMono8,
        RawMono16,
        RawYUV444,
        RawYUV422,
        RawYUV411,
        RawYUV420,
        RawRGB24,
        RawRGB48,
        RawBGR24,
        RawRGBA32,
        RawBGRA32,
        RawBayer8RGGB,
        RawBayer8GBRG,
        RawBayer8GRBG,
        RawBayer8BGGR,
        RawBayer16RGGB,
        RawBayer16GBRG,
        RawBayer16GRBG,
        RawBayer16BGGR,
    };
    /**
    * /brief 表示图像色彩通道
    */
    enum ColorChannel
    {
        R,//Red
        G,//Green
        B,//Blue
        A,//Alpha
        Y,//Y
        U,//Cb
        V,//Cr
        M,//Gray
        H,//Hue
        S,//Chroma
        L,//Brightness
    };
    /**
    * /brief 此函数用于将Raw格式转换为Matrix
    * /param Raw 待转换的原始采用数据
    * /param Length 待转换的原始采样数据长度
    * /param Format 待转换的原始采样数据格式
    * /param Channel 转换的目标输出色彩通道
    * /param Mat 转换输出的矩阵对象,需提前完成容量分配,图像转换尺寸依赖其大小.
    * /note 转换后的数据范围为0~1
    */
    static bool Raw2Matrix(U8* Raw,S32 Length,RawFormat Format,ColorChannel Channel,Matrix& Mat);
protected:
private:
};
}

#endif // RAWCONVERTER_H
