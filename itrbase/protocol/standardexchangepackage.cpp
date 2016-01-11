//
// Created by ghdawn on 16-1-9.
//

#include "standardexchangepackage.h"
#include "../platform/platform.h"
#include "../container/bytestream.h"

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
        property = (U16) SetPartBit(property, pid, 0, 4);
    }

    U8 StandardExchangePackage::getSID()
    {
        return GetPartBit(property, 4, 6);
    }

    void StandardExchangePackage::setSID(U8 sid)
    {
        property = (U16) SetPartBit(property, sid, 4, 6);
    }

    U8 StandardExchangePackage::getTID()
    {
        return GetPartBit(property, 10, 6);
    }

    void StandardExchangePackage::setTID(U8 tid)
    {
        property = (U16) SetPartBit(property, tid, 10, 6);
    }

    U8 StandardExchangePackage::getDataID()
    {
        return keyword;
    }

    void StandardExchangePackage::setDataID(U8 dataID)
    {
        keyword = dataID;
    }

    S32 StandardExchangePackage::WriteTo(U8 *buffer)
    {
        itr_container::ByteStream bs(buffer);
        bs.setU16(property);
        bs.setU8(keyword);
        bs.setU8Array(&data[0], data.size());
        return bs.getLength();
    }

    S32 StandardExchangePackage::getLength()
    {

        return (S32) (HeaderLength + 1 + data.size());
    }

    FormatErrorEnum StandardExchangePackage::ReadFrom(U8 *buffer, int offset, int length)
    {
        if (length <= HeaderLength + 1)
            return LengthWrong;
        itr_container::ByteStream bs(buffer + offset);
        this->property = bs.getU16();
        this->keyword = bs.getU8();
        for (int i = 0; i < length - 3; ++i)
        {
            data.push_back(bs.getU8());
        }
        return None;
    }

    U8 StandardExchangePackage::getDataLen() const
    {
        return (U8) data.size();
    }
}
