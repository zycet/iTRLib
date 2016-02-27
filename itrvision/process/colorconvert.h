//
// Created by ghdawn on 16-2-27.
//

#ifndef ITRLIB_COLORCONVERT_H
#define ITRLIB_COLORCONVERT_H

#include <platform/typedef.h>

class ColorConvert
{
    static void yuv420p2rgb(S32 *rgb, U8 *yuv, S32 width, S32 height);

    static void yuv420sp2rgb(S32 *rgb, U8 *yuv, S32 width, S32 height);

};


#endif //ITRLIB_COLORCONVERT_H
