//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_COMBOPROTOCOL_H
#define ITRLIB_COMBOPROTOCOL_H

#include <vector>
#include "../platform/typedef.h"

using std::vector;
namespace itr_protocol
{
    class onReceive
    {
    public:
        virtual S32 Do(U8 F0, U8 F1, U8 *data, U32 length)
        { }
    };

    class ComboProtocol
    {
    public:
        U32 processByte(U8 *buffer, int offset, int length);

        void addReceiveFun(onReceive *);

        vector<onReceive *> receiveList;
    };


}

#endif //ITRLIB_COMBOPROTOCOL_H
