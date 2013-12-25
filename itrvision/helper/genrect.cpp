#include "genrect.h"

namespace itr_vision
{
//BOOL Numerical::Rand(S32 low, S32 high, S32 &Result)const//RectangleS(S32 X, S32 Y, S32 Width, S32 Height);
    RectangleS* genrectin(RectangleS rect,S32 num)
    {
        RectangleS* rectpout[num];

        S32 off_max,
        S32 off_x,off_y;
        S32 n_x,n_y,n_w,n_h;
        Floor(0.1*rect.Width*rect.Height/(rect.Width+rect.Height), off_max);

        for(S32 i=0;i<num;i++)
        {
            Rand(-off_max, off_max, S32& off_x);
            Rand(-off_max, off_max, S32& off_y);
            (rectpout+i)->Width = rect.Width;     //不知道是否满足要求
            (rectpout+i)->Height = rect.Height;
            (rectpout+i)->X = off_x+rect.X+0.5*rect.Width-0.5*n_w;
            (rectpout+i)->Y = off_y+rect.Y+0.5*rect.Height-0.5*n_h;
        }
        return(rectpout);
    }

    RectangleS* genrectout(RectangleS rect,S32 num)
    {
        RectangleS* rectpout[num];

       // S32 off_max,
       // S32 off_x,off_y;
        //S32 n_x,n_y,n_w,n_h;
        //Floor(0.1*rect.Width*rect.Height/(rect.Width+rect.Height), off_max);

        for(S32 i=0;i<num;i++)
        {
            Rand(rect.X-rect.Width,rect.X+2*rect.Width,S32& off_x);
            Rand(-off_max, off_max, S32& off_y);
            (rectpout+i)->Width = rect.Width;     //不知道是否满足要求
            (rectpout+i)->Height = rect.Height;
            (rectpout+i)->X = off_x-0.5*n_w;
            (rectpout+i)->Y = off_y-0.5*n_h;
        }
        return(rectpout);
    }

}
