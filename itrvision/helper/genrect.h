#ifndef GENRECT_H
#define GENRECT_H

#include "../image/image.h"
#include "itrbase.h"
#include "../itrvision.h"


namespace itr_vision
{
class GenRect
{
    public:
        RectangleS genrectin(const ImageGray ImageIn,RectangleS rect);//BOOL Numerical::Rand(S32 low, S32 high, S32 &Result) const
        RectangleS genrectout(const ImageGray ImageIn,RectangleS rect);//RectangleS(S32 X, S32 Y, S32 Width, S32 Height);
    protected:
    private:
};
}
#endif // GENRECT_H
