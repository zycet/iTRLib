//
// Created by ghdawn on 16-1-10.
//

#include "bytestream.h"

itr_container::ByteStream::ByteStream(void *data)
{

    dataHead = (U8 *) data;
    ptr = dataHead;
}

U8 itr_container::ByteStream::getU8()
{
    return *ptr++;
}

U16 itr_container::ByteStream::getU16()
{
    U16 result = *((U16 *) ptr);
    ptr += 2;
    return result;
}

U32 itr_container::ByteStream::getU32()
{
    U32 result = *((U32 *) ptr);
    ptr += 4;
    return result;
}

S8 itr_container::ByteStream::getS8()
{
    return (S8) *ptr++;
}

S16 itr_container::ByteStream::getS16()
{
    S16 result = *((S16 *) ptr);
    return result;
}

S32 itr_container::ByteStream::getS32()
{
    S32 result = *((S32 *) ptr);
    ptr += 4;
    return result;
}

F32 itr_container::ByteStream::getF32()
{
    F32 result = *((F32 *) ptr);
    ptr += 4;
    return result;
}

void itr_container::ByteStream::getU8Array(U8 *buffer, U32 length)
{
    while (length--)
    {
        *buffer++ = getU8();
    }
}

void itr_container::ByteStream::setU8Array(U8 *buffer, U32 length)
{
    while (length--)
    {
        setU8(*buffer++);
    }
}

void itr_container::ByteStream::setU8(U8 data)
{
    *ptr++ = data;
}

void itr_container::ByteStream::setU16(U16 data)
{
    *((U16 *) ptr) = data;
    ptr += 2;
}

void itr_container::ByteStream::setU32(U32 data)
{
    *((U32 *) ptr) = data;
    ptr += 4;
}

void itr_container::ByteStream::setS8(S8 data)
{
    *((S8 *) ptr) = data;
    ptr += 1;
}

void itr_container::ByteStream::setS16(S16 data)
{
    *((S16 *) ptr) = data;
    ptr += 2;
}

void itr_container::ByteStream::setS32(S32 data)
{
    *((S32 *) ptr) = data;
    ptr += 4;
}

void itr_container::ByteStream::setF32(F32 data)
{
    *((F32 *) ptr) = data;
    ptr += 4;
}

void itr_container::ByteStream::reset()
{
    ptr = dataHead;
}

int itr_container::ByteStream::getLength()
{
    return (int) (ptr - dataHead);
}

