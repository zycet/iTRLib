//
// Created by ghdawn on 16-1-10.
//

#include "standardexchangeprotocolserial.h"

namespace itr_protocol
{
    U32 StandardExchangeProtocolSerial::FillBuffer(const StandardExchangePackage &SEPackage, U8 *buffer)
    {

    }

    void StandardExchangeProtocolSerial::ProcessByte(U8 *buffer, S32 offset, S32 length)
    {

    }

    void StandardExchangeProtocolSerial::AddReceiveFun(OnReceiveAction *fun)
    {
        receiveList.push_back(fun);
    }
}