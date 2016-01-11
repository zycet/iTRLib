//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_ISTANDARDEXCHANGEPROCESSOR_H
#define ITRLIB_ISTANDARDEXCHANGEPROCESSOR_H

#include "../platform/typedef.h"
#include <vector>

using std::vector;
namespace itr_protocol
{
    class StandardExchangePackage;

    class OnReceiveSEP
    {
    public:
        virtual S32 Do(const StandardExchangePackage &Package)
        { }
    };

    class IStandardExchangeProcessor
    {
    public:
        virtual U32 FillBuffer(const StandardExchangePackage &SEPackage, U8 *buffer)
        { }

        virtual U32 ProcessByte(U8 *buffer, S32 offset, S32 length)
        { }

        virtual void AddReceiveFun(OnReceiveSEP *fun)
        { }

        bool Enable;
    };
}

#endif //ITRLIB_ISTANDARDEXCHANGEPROCESSOR_H
