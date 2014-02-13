#ifndef BLOCK_H
#define BLOCK_H
#include "itrbase.h"
namespace itr_vision
{
    class Block
    {
        public:
            S32 x,y;
            S32 Area;
            S32 No;

            Block()
            {
                x=y=0;
                Area=0;
                No=0;
            }

            inline bool operator<(const Block &block) const
            {
                return this->Area < block.Area;
            }

            inline bool operator>(const Block &block) const
            {
                return this->Area > block.Area;
            }
    };
}
#endif // BLOCK_H
