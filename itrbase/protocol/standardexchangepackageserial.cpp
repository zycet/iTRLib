//
// Created by ghdawn on 16-1-10.
//

#include "standardexchangepackageserial.h"
#include "../encode/crc.h"

namespace itr_protocol
{
    void StandardExchangePackageSerial::init()
    {
        S0 = S0Default;
        S1 = S1Default;
    }
    StandardExchangePackageSerial::StandardExchangePackageSerial()
    {
        init();
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(const StandardExchangePackage &SEPackage)
            : StandardExchangePackage(
            SEPackage)
    {
        init();
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(U8 DataID) : StandardExchangePackage(DataID)
    {
        init();
    }

    StandardExchangePackageSerial::StandardExchangePackageSerial(U8 DataID, const vector<U8> &Data)
            : StandardExchangePackage(DataID, Data)
    {
        init();
    }

    S32 StandardExchangePackageSerial::WriteTo(U8 *buffer)
    {
        int n = 0;
        buffer[0] = S0;
        buffer[1] = S1;
        buffer[2] = getDataLen();
        n += HeaderLength;
        n += StandardExchangePackage::WriteTo(buffer + n);
        CRC crc;
        CRC16 = crc.BL_CRC16Encode(buffer, n);
        *((U16 *) (buffer + n)) = CRC16;
        return n + 2;
    }

    S32 StandardExchangePackageSerial::getLength()
    {
        return this->HeaderLength + StandardExchangePackage::getLength() + this->PlusLength + this->TailLength;
    }

    FormatErrorEnum StandardExchangePackageSerial::ReadFrom(U8 *buffer, int offset, int length)
    {
        if (length < HeaderLength + TailLength + PlusLength)
            return LengthWrong;
        buffer += offset;
        int dataLen = buffer[2];
        int allLen = HeaderLength + PlusLength + dataLen + TailLength;
        if (length < allLen)
            return LengthWrong;
        CRC crc;
        if (crc.BL_CRC16Encode(buffer, allLen) != 0)
            return CRCWrong;
        S0 = buffer[0];
        S1 = buffer[1];
        dataLen = buffer[2];
        return StandardExchangePackage::ReadFrom(buffer, HeaderLength, PlusLength + dataLen);
    }

}