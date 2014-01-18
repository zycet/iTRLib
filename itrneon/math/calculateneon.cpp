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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vld1.32  {d2,d3}, [%1]! \n\t"//q1 = f1
            "vadd.f32 q2, q0, q1     \n\t"//q2 = q0+q1
            "vst1.32 {d4,d5}, [%2]!  \n\t"//fr = q2
            : "+r"(SourceA), "+r"(SourceB), "+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=(*SourceA)+(*SourceB);
        Result++;
        SourceA++;
        SourceB++;
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vld1.32  {d2,d3}, [%1]! \n\t"//q1 = f1
            "vsub.f32 q2, q0, q1     \n\t"//q2 = q0-q1
            "vst1.32 {d4,d5}, [%2]!  \n\t"//fr = q2
            : "+r"(SourceA), "+r"(SourceB), "+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=(*SourceA)-(*SourceB);
        Result++;
        SourceA++;
        SourceB++;
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
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vld1.32  {d2,d3}, [%1]! \n\t"//q1 = f1
            "vmul.f32 q2, q0, q1     \n\t"//q2 = q0*q1
            "vst1.32 {d4,d5}, [%2]!  \n\t"//fr = q2
            : "+r"(SourceA), "+r"(SourceB), "+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vld1.32  {d2,d3}, [%1]! \n\t"//q1 = f1
          //  "vdiv.f32 q2, q0, q1     \n\t"//q2 = q0/q1??????????????????
            "vst1.32 {d4,d5}, [%2]!  \n\t"//fr = q2
            : "+r"(SourceA), "+r"(SourceB), "+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=(*SourceA)/(*SourceB);
        Result++;
        SourceA++;
        SourceB++;
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    asm volatile
    (
        "vdup.32 q1,%0 \n\t"
        :"+r"(Offset)
        :
        :"q1","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vadd.f32 q2, q0, q1     \n\t"//q2 = q0+q1
            "vst1.32 {d4,d5}, [%1]!  \n\t"//fr = q2
            : "+r"(SourceA),"+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=(*SourceA)+Offset;
        Result++;
        SourceA++;
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    asm volatile
    (
        "vdup.32 q1,%0 \n\t"
        :"+r"(Scale)
        :
        :"q1","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vmul.f32 q2, q0, q1     \n\t"//q2 = q0*q1
            "vst1.32 {d4,d5}, [%1]!  \n\t"//fr = q2
            : "+r"(SourceA),"+r"(Result)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=(*SourceA)*Scale;
        Result++;
        SourceA++;
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
    F32 k=1;
    MultiSum(SourceA, SourceA, Length, k);
    asm volatile
    (
        "vld1.f32 d1,[%0] \n\t"
        "vrsqrte.f32 d0,d1  \n\t"
        "vmov.32 %1,d0[0] \n\t"
        :"+r"(k)
        :
        :"q0","memory"
    );
    Scale( SourceA, k, Length, Result);
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vabs.f32 q1, q0     \n\t"//q1 = abs(q0)
            "vst1.32 {d2,d3}, [%1]!  \n\t"//fr = q1
            : "+r"(SourceA), "+r"(Result)
            :
            : "q0", "q1", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=GET_ABS(*SourceA);
        Result++;
        SourceA++;
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vneg.f32 q1, q0     \n\t"//q1 = abs(q0)
            "vst1.32 {d2,d3}, [%1]!  \n\t"//fr = q1
            : "+r"(SourceA), "+r"(Result)
            :
            : "q0", "q1", "memory"
        );
    }
    while(SourceA<endSource)
    {
        (*Result)=-(*SourceA);
        Result++;
        SourceA++;
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    Result = 0;
    asm volatile
    (
        "vdup.32 q1,%0 \n\t"
        :"+r"(Result)
        :
        :"q1","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vadd.f32 q1, q0, q1     \n\t"//q1 +=q0;
            : "+r"(SourceA)
            :
            : "q0", "q1", "memory"
        );
    }
    while(SourceA<endSource)
    {
        Result+=(*SourceA);
        SourceA++;
    }
    asm volatile
    (
        "vld1.f32 d4,[%0] \n\t"// load last few sum
        "vadd.f32 s0,s4,s5 \n\t"
        "vadd.f32 s1,s6,s7 \n\t"
        "vadd.f32 s2,s0,s8 \n\t"
        "vadd.f32 s4,s1,s2 \n\t"   //sum
        "vmov.32 %0,d2[0] \n\t"//sum to Result
        :"+r"(Result)
        :
        :"q0","q1","q2","memory"
    );
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

}

void CalculateNeon::MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vld1.32  {d4,d5}, [%1]! \n\t"//q2 = f1
            "vmla.f32 q1, q0, q2     \n\t"//q1 += q2*q0
            : "+r"(SourceA),"+r"(SourceB)
            :
            : "q0", "q1", "q2", "memory"
        );
    }
    while(SourceA<endSource)
    {
        Result +=(*SourceA)*(*SourceB);
        SourceA++;
        SourceB++;
    }
    asm volatile
    (
        "vld1.f32 d4,[%0] \n\t"//q2
        "vadd.f32 s0,s4,s5 \n\t"
        "vadd.f32 s1,s6,s7 \n\t"
        "vadd.f32 s2,s0,s8 \n\t"
        "vadd.f32 s4,s1,s2 \n\t"//sum
        "vmov.32 %0,d2[0] \n\t"//k q1
        :"+r"(Result)
        :
        :"q0","q1","q2","memory"
    );
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    asm volatile
    (
        "vdup.32 q1,%0 \n\t"
        :"+r"(Result)
        :
        :"q1","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d0,d1}, [%0]! \n\t"//q0 = f0
            "vmul.f32 q1, q1, q0     \n\t"//q1 = q1*q0
            : "+r"(SourceA)
            :
            : "q0", "q1", "memory"
        );
    }
    while(SourceA<endSource)
    {
        Result *=(*SourceA);
        SourceA++;
    }
    asm volatile
    (
        "vld1.f32 d4,[%0] \n\t"//q2
        "vmul.f32 s0,s4,s5 \n\t"
        "vmul.f32 s1,s6,s7 \n\t"
        "vmul.f32 s2,s0,s8 \n\t"
        "vmul.f32 s4,s1,s2 \n\t"
        "vmov.32 %0,d2[0] \n\t"//k q1
        :"+r"(Result)//,"+r"(k)
        :
        :"q0","q1","q2","memory"
    );
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
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    asm volatile
    (
        "vdup.32 q0,%0 \n\t"
        :"+r"(Value)
        :
        :"q0","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vst1.32 {d0,d1}, [%0]!  \n\t"
            : "+r"(SourceA)
            :
            : "q0", "memory"
        );
    }
    while(SourceA<endSource)
    {
        *SourceA = Value;
        SourceA++;
    }
}

void CalculateNeon::Compare(F32* SourceA, F32* SourceB, F32 Error,S32 Length,BOOL* IsSame) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    assert(Error > 0);
    (*IsSame)=true;
    F32* endSource=SourceA+Length;
    S32 qNum=Length>>2;
    F32 err=1;
    asm volatile
    (
        "vdup.32 q0,%0 \n\t"
        "vdup.32 q3,%0 \n\t"
        :"+r"(Error)
        :
        :"q0","q3","memory"
    );
    for(S32 i=0; i<qNum; i++)
    {
        asm volatile
        (
            "vld1.32  {d2,d3}, [%0]! \n\t"//q1 = fa
            "vld1.32  {d4,d5}, [%1]! \n\t"//q2 = fb
            "vsub.f32 q1, q1, q2     \n\t"//q1 = q1-q2
            "vacgt.f32 q2, q0,q1      \n\t"//
            "vmul.f32 q3, q3,q2      \n\t"//
            : "+r"(SourceA),"+r"(SourceB)
            :
            : "q0", "q1","q2","q3", "memory"
        );
    }
    asm volatile
    (
        "vdup.32 q0,%0 \n\t"
        "vdup.32 q3,%0 \n\t"
        "vmul.f32 s12,s12,s13 \n\t"
        "vmul.f32 s14,s14,s15 \n\t"
        "vmul.f32 s12,s12,s14 \n\t"
        :"+r"(err)
        :
        :"q3","memory"
    );
    if(err!=0)
     {
         while(SourceA<endSource)
        {
            err=*(SourceA)-*(SourceB);
            SourceA++;
            SourceB++;
            if(err>Error||err<-Error)
            {
                (*IsSame)=false;
                return;
            }
        }
    }
    else
    {
         (*IsSame)=false;
          return;
    }

}

}
