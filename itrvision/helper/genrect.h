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
    /**
      * \brief 生成一定数量的矩形框，使得生成的矩形框将给定的矩形的巨大部分包含在内
      * \param rect 给定的矩形
      * \param rectR 生成的矩形组
      * \param num 生成矩形数量
      */
    static void genrectin(RectangleS rect,RectangleS rectR[],S32 num);

    /**
          * \brief 生成一定数量的矩形框，使得生成的矩形框位于给定矩形外部
          * \param rect 给定的矩形
          * \param rectR 生成的矩形组
          * \param num 生成矩形数量
          */
    static void genrectout(RectangleS rect,RectangleS rectR[],S32 num);

protected:
private:
};
}
#endif // GENRECT_H
