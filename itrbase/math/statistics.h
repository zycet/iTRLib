
#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class Statistics
{
public:
    Statistics();
    virtual ~Statistics();
    /**
      * \brief 求数组中的最大值
      * \param Length 数组长度
      * \param Result 数组中的最大值
      */
    virtual bool Max(S32* Source, S32 Length, S32& Result) const;
    virtual bool Max(F32* Source, S32 Length, F32& Result) const;
    /**
      * \brief 求数组中的最小值
      * \param Length 数组长度
      * \param Result 数组中的最小值
      */
    virtual bool Min(S32* Source, S32 Length, S32& Result) const;
    virtual bool Min(F32* Source, S32 Length, F32& Result) const;
    /**
      * \brief 求数组的平均值
      * \param Length 数组长度
      * \param Result 数组平均值
      */
    virtual bool Mean(S32* Source, S32 Length, S32& Result) const;
    virtual bool Mean(F32* Source, S32 Length, F32& Result) const;
    /**
      * \brief 求数组中的中位数
      * \param Length 数组长度
      * \param Result 数组的中位数
      */
    virtual bool Median(S32* Source, S32 Length, S32& Result) const;
    virtual bool Median(F32* Source, S32 Length, F32& Result) const;
     /**
      * \brief 求数组中的第k大的数，会改变输入数组的顺序
      * \param Length 数组长度
      * \param Result 数组中的第k大的数值
      */
    virtual void MaxKth(S32* Source, S32 Length, S32& Result, S32& Order) const;
    virtual void MaxKth(F32* Source, S32 Length, F32& Result, S32& Order) const;
    virtual S32 SelectKth(S32 *data,int left,int right,int k);
    virtual F32 SelectKth(F32 *data,int left,int right,int k);

    /**
      * \brief 求数组中的均方根
      * \param Length 数组长度
      * \param Result 数组的均方根
      */
    virtual bool RMS(S32* Source, S32 Length, S32& Result) const;
    virtual bool RMS(F32* Source, S32 Length, F32& Result) const;
    /**
      * \brief 求数组中的方差
      * \param Length 数组长度
      * \param Result 数组的方差
      */
    virtual bool Variance(S32* Source, S32 Length, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Result) const;
    virtual bool Variance(S32* Source, S32 Length, S32& Mean, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Mean, F32& Result) const;
};

} // namespace itr_math

#endif //statistics STATISTICS_H_
