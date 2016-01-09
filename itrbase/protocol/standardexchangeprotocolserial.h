//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_STANDARDEXCHANGEPROTOCOLSERIAL_H
#define ITRLIB_STANDARDEXCHANGEPROTOCOLSERIAL_H

#include "istandardexchangeprocessor.h"

namespace itr_protocol
{
    class StandardExchangeProtocolSerial : public IStandardExchangeProcessor
    {
        U32 FillBuffer(const StandardExchangePackage &SEPackage, U8 *buffer);

        void ProcessByte(U8 *buffer, S32 offset, S32 length);

        void AddReceiveFun(OnReceiveAction *fun);
    };
}


#endif //ITRLIB_STANDARDEXCHANGEPROTOCOLSERIAL_H
