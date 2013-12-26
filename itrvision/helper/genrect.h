#ifndef GENRECT_H
#define GENRECT_H

#include "itrbase.h"
#include "../itrvision.h"

using itr_math::RectangleS;


namespace itr_vision
{
class GenRect
{
    public:
       static void genrectin(RectangleS rect,RectangleS rectR[],S32 num);

       static void genrectout(RectangleS rect,RectangleS rectR[],S32 num);

    protected:
    private:
};
}
#endif // GENRECT_H
