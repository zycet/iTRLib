#include "calculateneon.h"

namespace itr_math
{

CalculateNeon::CalculateNeon()
{
    assert(NumericalObj!=NULL);
}

CalculateNeon::~CalculateNeon()
{

}

void CalculateNeon::Add(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + SourceB[i];
    }
}

void CalculateNeon::Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + SourceB[i];
    }
}

void CalculateNeon::Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + SourceB[i];
    }
}

void CalculateNeon::Sub(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] - SourceB[i];
    }
}

void CalculateNeon::Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] - SourceB[i];
    }
}

void CalculateNeon::Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] - SourceB[i];
    }
}

void CalculateNeon::Multi(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * SourceB[i];
    }
}

void CalculateNeon::Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * SourceB[i];
    }
}

void CalculateNeon::Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    F32* endSource;
    S32 qNum;
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);

    asm volatile
    (
        "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
        "vld1.32  {d2,d3}, [%1]! \n\t"//q1 = f1
        "vmul.f32 q2, q0, q1     \n\t"//q2 = q0*q1
        "vst1.32 {d4,d5}, [%2]!  \n\t"//fr = q2
        : "+r"(SourceA), "+r"(SourceB), "+r"(Result)
        : "0"(SourceA),"1"(SourceB),"2"(Result),
        : "q0", "q1", "q2", "memory"
    );
    endSource=SourceA+Length;
    while(SourceA<=endSource)
    {
        (*Result)=(*SourceA)*(*SourceB);
        Result++;
        SourceA++;
        SourceB++;
    }
}

void CalculateNeon::Div(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] / SourceB[i];
    }
}

void CalculateNeon::Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] / SourceB[i];
    }
}

void CalculateNeon::Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] / SourceB[i];
    }
}

void CalculateNeon::DivOrder(S16* SourceA, S32 DivOrder, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(DivOrder>=0);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] >> DivOrder;
    }
}

void CalculateNeon::DivOrder(S32* SourceA, S32 DivOrder, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(DivOrder>=0);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] >> DivOrder;
    }
}

void CalculateNeon::Offset(S16* SourceA, S16 Offset, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void CalculateNeon::Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void CalculateNeon::Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void CalculateNeon::Scale(S16* SourceA, S16 Scale, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void CalculateNeon::Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void CalculateNeon::Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void CalculateNeon::Normalization(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void CalculateNeon::Normalization(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void CalculateNeon::Normalization(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void CalculateNeon::Abs(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void CalculateNeon::Abs(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void CalculateNeon::Abs(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void CalculateNeon::Opposite(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void CalculateNeon::Opposite(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void CalculateNeon::Opposite(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void CalculateNeon::AddSum(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void CalculateNeon::AddSum(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void CalculateNeon::AddSum(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void CalculateNeon::MultiSum(S16* SourceA, S16* SourceB, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i] * SourceB[i];
    }
}

void CalculateNeon::MultiSum(S16* SourceA, F32* SourceB, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    F32 value = 0;
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        value += SourceA[i] * SourceB[i];
    }
    Result = value;
}

void CalculateNeon::MultiSum(S32* SourceA, S32* SourceB, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i] * SourceB[i];
    }
}

void CalculateNeon::MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i] * SourceB[i];
    }
}

void CalculateNeon::Product(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void CalculateNeon::Product(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void CalculateNeon::Product(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void CalculateNeon::Set(S16* SourceA, S16 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void CalculateNeon::Set(S32* SourceA, S32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void CalculateNeon::Set(F32* SourceA, F32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void CalculateNeon::Compare(F32* SourceA, F32* SourceB, F32 Error,S32 Length,BOOL* IsSame) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    assert(Error > 0);
    (*IsSame)=true;
    F32 error;
    for (S32 i = 0; i < Length; i++)
    {
        error=SourceA[i]-SourceB[i];
        if(error>Error||error<-Error)
        {
            (*IsSame)=false;
            return;
        }
    }
}

}
