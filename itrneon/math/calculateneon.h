#ifndef CALCULATENEON_H
#define CALCULATENEON_H

#include "itrbase.h"

namespace itr_math
{
class CalculateNeon:public Calculate
{
public:
    CalculateNeon();
    virtual ~CalculateNeon();
    virtual void Add(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;

    virtual void Sub(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;

    virtual void Multi(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;

    virtual void Div(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;

    virtual void DivOrder(S16* SourceA, S32 DivOrder, S32 Length, S16* Result) const;
    virtual void DivOrder(S32* SourceA, S32 DivOrder, S32 Length, S32* Result) const;

    virtual void Offset(S16* SourceA, S16 Offset, S32 Length, S16* Result) const;
    virtual void Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result) const;
    virtual void Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result) const;

    virtual void Scale(S16* SourceA, S16 Scale, S32 Length, S16* Result) const;
    virtual void Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result) const;
    virtual void Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result) const;

    virtual void Normalization(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Normalization(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Normalization(F32* SourceA, S32 Length, F32* Result) const;

    virtual void Abs(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Abs(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Abs(F32* SourceA, S32 Length, F32* Result) const;

    virtual void Opposite(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Opposite(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Opposite(F32* SourceA, S32 Length, F32* Result) const;

    virtual void AddSum(S16* SourceA, S32 Length, S16& Result) const;
    virtual void AddSum(S32* SourceA, S32 Length, S32& Result) const;
    virtual void AddSum(F32* SourceA, S32 Length, F32& Result) const;

    virtual void MultiSum(S16* SourceA, S16* SourceB, S32 Length, S16& Result) const;
    virtual void MultiSum(S16* SourceA, F32* SourceB, S32 Length, S16& Result) const;
    virtual void MultiSum(S32* SourceA, S32* SourceB, S32 Length, S32& Result) const;
    virtual void MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const;

    virtual void Product(S16* SourceA, S32 Length, S16& Result) const;
    virtual void Product(S32* SourceA, S32 Length, S32& Result) const;
    virtual void Product(F32* SourceA, S32 Length, F32& Result) const;

    virtual void Set(S16* SourceA, S16 Value, S32 Length) const;
    virtual void Set(S32* SourceA, S32 Value, S32 Length) const;
    virtual void Set(F32* SourceA, F32 Value, S32 Length) const;

    virtual void Compare(F32* SourceA, F32* SourceB, F32 Error,S32 Length,BOOL* IsSame) const;

    virtual void Max(F32* SourceA, S32 Length, F32& Result) const;
    virtual void Min(F32* SourceA, S32 Length, F32& Result) const;
    virtual void Min(F32* SourceA, S32 Length, F32& Result, S32& Order) const;
    /**
      * \brief 求两个向量的一次距离
      * \param SourceA 向量1
      * \param SourceB 向量2
      * \param Length 向量维数
      * \param Result 向量1，2的一次距离和
      */
    virtual void Single_dis(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const;
    /**
      * \brief 求两个向量的二次距离
      * \param SourceA 向量1
      * \param SourceB 向量2
      * \param Length 向量维数
      * \param Result 向量1，2的二次距离和
      */
    virtual void Double_dis(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const;
protected:
private:
};
}

#endif // CALCULATENEON_H
