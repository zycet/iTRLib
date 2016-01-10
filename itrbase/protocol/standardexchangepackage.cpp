//
// Created by ghdawn on 16-1-9.
//

#include "standardexchangepackage.h"
#include "../platform/platform.h"

namespace itr_protocol
{
    StandardExchangePackage::StandardExchangePackage()
    {
        keyword = 0;
        property = 0;
    }

    StandardExchangePackage::StandardExchangePackage(const itr_protocol::StandardExchangePackage &SEPackage)
    {
        property = SEPackage.property;
        keyword = SEPackage.keyword;
        data.assign(SEPackage.data.begin(), SEPackage.data.end());
    }

    StandardExchangePackage::StandardExchangePackage(U8 DataID)
    {
        property = 0;
        keyword = DataID;
    }

    StandardExchangePackage::StandardExchangePackage(U8 DataID, const vector<U8> &Data)
    {
        property = 0;
        keyword = DataID;
        data.assign(Data.begin(), Data.end());
    }

    U8 StandardExchangePackage::getPID()
    {
        return GetPartBit(property, 0, 4);
    }

    void StandardExchangePackage::setPID(U8 pid)
    {
        SetPartBit(property, pid, 0, 4);
    }

    U8 StandardExchangePackage::getSID()
    {
        return GetPartBit(property, 4, 6);
    }

    void StandardExchangePackage::setSID(U8 sid)
    {
        SetPartBit(property, sid, 4, 6);
    }

    U8 StandardExchangePackage::getTID()
    {
        return GetPartBit(property, 10, 6);
    }

    void StandardExchangePackage::setTID(U8 tid)
    {
        SetPartBit(property, tid, 10, 6);
    }

    U8 StandardExchangePackage::getDataID()
    {
        return keyword;
    }

    void StandardExchangePackage::setDataID(U8 dataID)
    {
        keyword = dataID;
    }

    S32 StandardExchangePackage::writeTo(U8 *buffer)
    {
        S32 n;
        *((U16 *) buffer) = property;
        n += 2;
        buffer[n] = keyword;
        n += 1;
        MemoryCopy(buffer + n, &data[0], data.size());
        n += data.size();
        return n;
    }

    S32 StandardExchangePackage::getLength()
    {

        return (S32) (HeaderLength + 1 + data.size());
    }

    FormatErrorEnum StandardExchangePackage::readFrom(U8 *buffer, int offset, int length)
    {
        if (length <= HeaderLength + 1)
            return LengthWrong;
        this->property = *((U16 *) (buffer + offset));
        this->keyword = buffer[offset + 2];
        this->data.assign(buffer + offset + 3, buffer + offset + length);
        return None;
    }

    U8 StandardExchangePackage::getDataLen() const
    {
        return (U8) data.size();
    }
}
