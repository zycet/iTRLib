//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H
#define ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H

#include "standardexchangepackage.h"

namespace itr_protocol
{
    class StandardExchangePackageSerial : public StandardExchangePackage
    {
    public:
        static const int HeaderLength = 3;
        static const int PlusLength = StandardExchangePackage::HeaderLength + 1;
        //Prop DataID
        static const int TailLength = 2;
        static const U8 S0Default = 0xA5;
        static const U8 S1Default = 0x5A;
        U8 S0;
        U8 S1;

        U16 CRC16;

        void init();
        StandardExchangePackageSerial();

        StandardExchangePackageSerial(const StandardExchangePackage &SEPackage);

        StandardExchangePackageSerial(U8 DataID);

        StandardExchangePackageSerial(U8 DataID, const vector<U8> &Data);

        S32 getLength();

        S32 WriteTo(U8 *buffer);

        FormatErrorEnum ReadFrom(U8 *buffer, int offset, int length);
    };
}


#endif //ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H
