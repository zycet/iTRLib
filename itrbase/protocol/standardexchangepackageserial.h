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
        static const int HeaderLength = 3;

        static const int PlusLength = StandardExchangePackage.HeaderLength + BasePackage.HeaderLength;//Prop DataID

        static const int TailLength = 2;


        U8 S0 = StandardExchangeProtocolSerial.S0Default;


        U8 S1 = StandardExchangeProtocolSerial.S1Default;


        byte DataLen;

        U16 CRC16;
    };
}


#endif //ITRLIB_STANDARDEXCHANGEPACKAGESERIAL_H
