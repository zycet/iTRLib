//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_BITOPERATOR_H
#define ITRLIB_BITOPERATOR_H

#include "typedef.h"

U8 GetPartBit(U32 data, int begin, int len);

U32 SetPartBit(U32 data, U8 value, int begin, int len);

#endif //ITRLIB_BITOPERATOR_H
