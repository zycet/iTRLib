#ifndef GENRECT_H
#define GENRECT_H

#include "itrbase.h"
#include "../itrvision.h"


namespace itr_vision
{
class GenRect
{
    public:
        RectangleS* genrectin(RectangleS rect,S32 num);

        RectangleS* genrectout(RectangleS rect,S32 num);

    protected:
    private:
};
}
#endif // GENRECT_H
