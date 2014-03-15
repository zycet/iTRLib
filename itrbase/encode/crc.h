#ifndef CRC_H
#define CRC_H
#include "../itrbase.h"
class CRC
{
    public:
        CRC();
        virtual ~CRC();
        U16 BL_CRC16Encode(U8* Data, S32 BufferLen);

    protected:
    private:
};

#endif // CRC_H
