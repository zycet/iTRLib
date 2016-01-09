//
// Created by ghdawn on 16-1-9.
//

#ifndef ITRLIB_STANDARDEXCHANGEPACKAGE_H
#define ITRLIB_STANDARDEXCHANGEPACKAGE_H

#include "../platform/typedef.h"
#include <vector>

using std::vector;
namespace itr_protocol
{
    class StandardExchangePackage
    {
    public:
        static const int HeaderLength = 2;
        U16 property;
        U8 keyword;
        vector<U8> data;

        U8 getPID();

        void setPID(U8 pid);

        U8 getSID();

        void setSID(U8 sid);

        U8 getTID();

        void setTID(U8 tid);

        U8 getDataID();

        void setDataID(U8 dataID);

        StandardExchangePackage();

        StandardExchangePackage(const itr_protocol::StandardExchangePackage &SEPackage);

        StandardExchangePackage(U8 DataID);

        StandardExchangePackage(U8 DataID, const vector<U8> &Data);

        virtual S32 writeTo(U8 *buffer);

        S32 getLength();

    };
}

#endif //ITRLIB_STANDARDEXCHANGEPACKAGE_H
