//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_COMBOPACKAGE_H
#define ITRLIB_COMBOPACKAGE_H

#include "../platform/typedef.h"
#include "standardexchangepackageserial.h"

namespace itr_protocol
{
    class ComboPackage
    {
    public:
        static const U32 HeaderLength = 8;
        static const U8 S0Default = 'C';
        static const U8 S1Default = 'P';

        ComboPackage();

        FormatErrorEnum readFrom(U8 *buffer, int offset, U32 length);

        int writeTo(U8 *buffer, int offset);

        U8 S0;
        U8 S1;
        U8 F0;
        U8 F1;
        U8 data[65535];
        U32 length;
    };
}

#endif //ITRLIB_COMBOPACKAGE_H
