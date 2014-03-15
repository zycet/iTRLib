#include "crc.h"

CRC::CRC()
{
    //ctor
}

CRC::~CRC()
{
    //dtor
}
U16 CRC::BL_CRC16Encode(U8* Data, S32 BufferLen)
{
 U16 crc_gen = 0xa001;  /*1,1000,0000,0000,0101B*/
 U16 crc;
 S32 i, j;

 crc = 0xffff;
 if (BufferLen != 0)
 {
  for (i = 0; i < BufferLen; i++)
  {
   crc ^= (U16)(Data[i]);
   for (j = 0; j < 8; j++)
   {
    if ((crc & 0x01) == 0x01)
    {
     crc >>= 1;
     crc ^= crc_gen;
    }
    else
    {
     crc >>= 1;
    }
   }
  }
 }
 return crc;
}

