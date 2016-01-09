//
// Created by ghdawn on 16-1-10.
//

#include "standardexchangeprotocolserial.h"
#include "standardexchangepackageserial.h"
namespace itr_protocol
{
    U32 StandardExchangeProtocolSerial::FillBuffer(const StandardExchangePackage &SEPackage, U8 *buffer)
    {
        StandardExchangePackageSerial seps(SEPackage);
        return seps.writeTo(buffer);
    }

    void StandardExchangeProtocolSerial::ProcessByte(U8 *buffer, S32 offset, S32 length)
    {

    }

    void StandardExchangeProtocolSerial::AddReceiveFun(OnReceiveAction *fun)
    {
        receiveList.push_back(fun);
    }
}