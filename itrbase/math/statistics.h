/**
*\Max 求长为length的数组的最大值
*\Min 求长为length的数组的最小值
*\Mean 求长为length的数组的平均值
*\Median 求长为length的数组的中位数
*\RMS 求长为length的数组的均方根
*\Vatiance 求长为length的数组的方差
 */

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
    virtual bool Max(S32* Source, S32 Length, S32& Result) const;
    virtual bool Max(F32* Source, S32 Length, F32& Result) const;
    virtual bool Min(S32* Source, S32 Length, S32& Result) const;
    virtual bool Min(F32* Source, S32 Length, F32& Result) const;
    virtual bool Mean(S32* Source, S32 Length, S32& Result) const;
    virtual bool Mean(F32* Source, S32 Length, F32& Result) const;
    virtual bool Median(S32* Source, S32 Length, S32& Result) const;
    virtual bool Median(F32* Source, S32 Length, F32& Result) const;
    virtual bool RMS(S32* Source, S32 Length, S32& Result) const;
    virtual bool RMS(F32* Source, S32 Length, F32& Result) const;
    virtual bool Variance(S32* Source, S32 Length, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Result) const;
    virtual bool Variance(S32* Source, S32 Length, S32& Mean, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Mean, F32& Result) const;
};

} // namespace itr_math

#endif //statistics STATISTICS_H_
