//
// Created by ghdawn on 16-1-10.
//

#include "combopackage.h"
#include "../container/bytestream.h"

namespace itr_protocol
{
    ComboPackage::ComboPackage()
    {
        this->S0 = S0Default;
        this->S1 = S1Default;
        this->F0 = 0;
        this->F1 = 0;
    }

    FormatErrorEnum ComboPackage::readFrom(U8 *buffer, int offset, U32 len)
    {
        if (len <= HeaderLength)
            return LengthWrong;
        int n = 0;
        buffer += offset;
        itr_container::ByteStream bs(&buffer);
        S0 = bs.getU8();
        S1 = bs.getU8();
        F0 = bs.getU8();
        F1 = bs.getU8();
        length = bs.getU32();
        bs.getU8Array(data, length);
        return None;
    }

    int ComboPackage::writeTo(U8 *buffer, int offset)
    {
        itr_container::ByteStream bs(&buffer);
        bs.setU8(S0);
        bs.setU8(S1);
        bs.setU8(F0);
        bs.setU8(F1);
        bs.setU32(length);
        bs.setU8Array(data, length);
        return bs.getLength();
    }
}
