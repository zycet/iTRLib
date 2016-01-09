//
// Created by ghdawn on 16-1-10.
//

#include "standardexchangepackageserial.h"
#include "../encode/crc.h"

namespace itr_protocol
{
    StandardExchangePackageSerial::StandardExchangePackageSerial()
    {
        S0 = S0Default;
        S1 = S1Default;
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(const StandardExchangePackage &SEPackage) : sep(
            SEPackage)
    {
        StandardExchangePackageSerial();
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(U8 DataID) : sep(DataID)
    {
        StandardExchangePackageSerial();
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(U8 DataID, const vector<U8> &Data) : sep(DataID, Data)
    {
        StandardExchangePackageSerial();
    }

    U8 StandardExchangePackageSerial::getDataLen()
    {
        return sep.data.size();
    }

    S32 StandardExchangePackageSerial::writeTo(U8 *buffer)
    {
        int n;
        buffer[0] = S0;
        buffer[1] = S1;
        buffer[2] = getDataLen();
        n += HeaderLength;
        n += sep.writeTo(buffer + n);
        CRC _crcthis;
        CRC16 = _crcthis.BL_CRC16Encode(buffer, n);
        *((U16 *) (buffer + n)) = CRC16;
    }
}