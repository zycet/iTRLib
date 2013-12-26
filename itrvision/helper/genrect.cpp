#include "genrect.h"

namespace itr_vision
{

    RectangleS* genrectin(RectangleS rect,S32 num)
    {
        RectangleS rectpout[num];
        S32 off_max,
        S32 off_x,off_y;
        S32 n_w,n_h;
        itr_math::Numerical::Floor(0.1*rect.Width*rect.Height/(rect.Width+rect.Height), off_max);

        for(S32 i=0;i<num;i++)
        {
            itr_math::Numerical::Rand(-off_max, off_max,  off_x);
            itr_math::Numerical::Rand(-off_max, off_max,  off_y);
            rectpout[i].Width = rect.Width;     //不知道是否满足要求
            rectpout[i].Height = rect.Height;
           // Floor(off_x+rect.X+0.5*rect.Width-0.5*n_w, n_x);
            //(rectpout+i)->X = n_x;
            rectpout[i].X = off_x+rect.X+0.5*rect.Width-0.5*n_w;
            rectpout[i].Y = off_y+rect.Y+0.5*rect.Height-0.5*n_h;
        }
        return(rectpout);
    }

    RectangleS* genrectout(RectangleS rect,S32 num)
    {
        RectangleS rectpout[num];


        S32 off_x,off_y;
        S32 n_x,n_y,n_w,n_h;

        for(S32 i=0;i<num;i++)
        {
            itr_math::Numerical::Rand(rect.X-0.5*rect.Width,rect.X+1.5*rect.Width, off_x);
            if(off_x>rect.X&&off_x<rect.X+rect.Width)
            {
                n_x=off_x;
                itr_math::Numerical::Rand(0,rect.Height,off_y);
                if(off_y>0.5*rect.Height)
                {
                    n_y=rect.Y+rect.Height*1.5;
                }
                else
                    n_y=rect.Y-rect.Heitht*0.5;
                itr_math::Numerical::Floor(n_y,n_y);
            }
            else
            {
                if(off_x<=rect.X)
                    n_x=rect.X-0.5*rect.Width;
                else
                    n_x=rect.X+1.5*rect.Width;
                itr_math::Numerical::Floor(n_x,n_x);
                itr_math::Numerical::Rand(rect.Y-0.5*rect.Width,rect.Y+rect.Width*1.5,off_y);
                n_y=off_y;

            }
            n_w=rect.Width;
            n_h=rect.Height;

            rectpout[i].Width = n_w;
            rectpout[i].Height = n_h;
            rectpout[i].X =n_x;
            rectpout[i].Y = n_y;
        }
        return(rectpout);
    }

}
