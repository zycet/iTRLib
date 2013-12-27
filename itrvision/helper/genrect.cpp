#include "genrect.h"

namespace itr_vision
{

    void GenRect::genrectin(RectangleS rect,RectangleS rectR[],S32 num)
    {
        S32 off_max,off_x,off_y;

        itr_math::Numerical Numerical0;
        Numerical0.Floor(0.1*rect.Width*rect.Height/(rect.Width+rect.Height), off_max);

        for(S32 i=0;i<num;i++)
        {
            Numerical0.Rand(-off_max, off_max,  off_x);
            Numerical0.Rand(-off_max, off_max,  off_y);
            rectR[i].Width = rect.Width;
            rectR[i].Height = rect.Height;
            rectR[i].X = off_x+rect.X;
            rectR[i].Y = off_y+rect.Y;
        }

    }

    void GenRect::genrectout(RectangleS rect,RectangleS rectR[],S32 num)
    {
        itr_math::Numerical Numerical0;
        S32 off_x,off_y;
        S32 n_x,n_y,n_w,n_h;

        for(S32 i=0;i<num;i++)
        {
            Numerical0.Rand(rect.X-0.5*rect.Width,rect.X+1.5*rect.Width, off_x);
            if(off_x>rect.X&&off_x<rect.X+rect.Width)
            {
                n_x=off_x;
                Numerical0.Rand(0,rect.Height,off_y);
                if(off_y>0.5*rect.Height)
                {
                    n_y=rect.Y+rect.Height*1.5;
                }
                else
                    n_y=rect.Y-rect.Height*0.5;
                Numerical0.Floor(n_y,n_y);
            }
            else
            {
                if(off_x<=rect.X)
                    n_x=rect.X-0.5*rect.Width;
                else
                    n_x=rect.X+1.5*rect.Width;
                Numerical0.Floor(n_x,n_x);
                Numerical0.Rand(rect.Y-0.5*rect.Height,rect.Y+rect.Height*1.5,off_y);
                n_y=off_y;

            }
            n_w=rect.Width;
            n_h=rect.Height;

            rectR[i].Width = n_w;
            rectR[i].Height = n_h;
            rectR[i].X =n_x-0.5*n_w;
            rectR[i].Y = n_y-0.5*n_h;
        }

    }

}
