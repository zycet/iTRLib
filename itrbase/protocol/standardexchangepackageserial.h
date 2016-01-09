//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H
#define ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H

#include "standardexchangepackage.h"

namespace itr_protocol
{
    class StandardExchangePackageSerial
    {
    public:
        static const int HeaderLength = 3;
        static const int PlusLength = StandardExchangePackage::HeaderLength + 1;
        //Prop DataID
        static const int TailLength = 2;
        static const U8 S0Default = 0xA5;
        static const U8 S1Default = 0x5A;
        StandardExchangePackage sep;
        U8 S0;
        U8 S1;

        U16 CRC16;

        StandardExchangePackageSerial();

        StandardExchangePackageSerial(const StandardExchangePackage &SEPackage);

        StandardExchangePackageSerial(U8 DataID);

        StandardExchangePackageSerial(U8 DataID, const vector<U8> &Data);

        U8 getDataLen();

        S32 writeTo(U8 *buffer);
    };
}


#endif //ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H
