//
// Created by ghdawn on 16-1-10.
//

#ifndef ITRLIB_BYTESTREAM_H
#define ITRLIB_BYTESTREAM_H

#include "../platform/typedef.h"

namespace itr_container
{
    class ByteStream
    {
    public:
        ByteStream(void *data);

        void reset();

        int getLength();

        U8 getU8();

        void getU8Array(U8 *buffer, U32 length);

        U16 getU16();

        U32 getU32();

        S8 getS8();

        S16 getS16();

        S32 getS32();

        F32 getF32();

        void setU8(U8 data);

        void setU8Array(U8 *buffer, U32 length);

        void setU16(U16 data);

        void setU32(U32 data);

        void setS8(S8 data);

        void setS16(S16 data);

        void setS32(S32 data);

        void setF32(F32 data);

    private:
        U8 *dataHead;
        U8 *ptr;
    };

}


#endif //ITRLIB_BYTESTREAM_H
