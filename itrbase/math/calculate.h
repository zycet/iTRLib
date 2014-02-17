
#ifndef CALCULATE_H_
#define CALCULATE_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class Calculate
{
public:
    Calculate();
    virtual ~Calculate();
    /**
    * \brief 两数组元素对应相加
    * \param SourceA 数组Ａ
    * \param SourceB 数组Ｂ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Add(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;
    /**
    * \brief 两数组元素对应相减
    * \param SourceA 数组Ａ
    * \param SourceB 数组Ｂ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Sub(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;
    /**
    * \brief 两数组元素对应相乘
    * \param SourceA 数组Ａ
    * \param SourceB 数组Ｂ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Multi(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;
    /**
    * \brief 两数组元素对应相除
    * \param SourceA 数组Ａ
    * \param SourceB 数组Ｂ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Div(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const;
    virtual void Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const;
    virtual void Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const;
    /**
    * \brief 数组中所有元素右移DivOrder位
    * \param SourceA 数组Ａ
    * \param DivOrder 右移位数
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void DivOrder(S16* SourceA, S32 DivOrder, S32 Length, S16* Result) const;
    virtual void DivOrder(S32* SourceA, S32 DivOrder, S32 Length, S32* Result) const;
    /**
    * \brief 数组中所有元素加Offset
    * \param SourceA 数组Ａ
    * \param Offset 加数
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Offset(S16* SourceA, S16 Offset, S32 Length, S16* Result) const;
    virtual void Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result) const;
    virtual void Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result) const;
    /**
    * \brief 数组中所有元素乘Scale
    * \param SourceA 数组Ａ
    * \param Scale 乘数
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Scale(S16* SourceA, S16 Scale, S32 Length, S16* Result) const;
    virtual void Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result) const;
    virtual void Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result) const;
    /**
    * \brief 归一化
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Normalization(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Normalization(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Normalization(F32* SourceA, S32 Length, F32* Result) const;
    /**
    * \brief 求数组中所有元素的绝对值
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Abs(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Abs(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Abs(F32* SourceA, S32 Length, F32* Result) const;
    /**
    * \brief 求数组中所有元素的相反数
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Opposite(S16* SourceA, S32 Length, S16* Result) const;
    virtual void Opposite(S32* SourceA, S32 Length, S32* Result) const;
    virtual void Opposite(F32* SourceA, S32 Length, F32* Result) const;
    /**
    * \brief 将数组中所有元素求和
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void AddSum(S16* SourceA, S32 Length, S16& Result) const;
    virtual void AddSum(S32* SourceA, S32 Length, S32& Result) const;
    virtual void AddSum(F32* SourceA, S32 Length, F32& Result) const;
    /**
    * \brief 将两个数组中对应元素元素相称并求和
    * \param SourceA 数组Ａ
    * \param SourceA 数组Ｂ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void MultiSum(S16* SourceA, S16* SourceB, S32 Length, S16& Result) const;
    virtual void MultiSum(S16* SourceA, F32* SourceB, S32 Length, S16& Result) const;
    virtual void MultiSum(S32* SourceA, S32* SourceB, S32 Length, S32& Result) const;
    virtual void MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const;
    /**
    * \brief 求数组中所有元素的连乘积
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Result 输出结果
    */
    virtual void Product(S16* SourceA, S32 Length, S16& Result) const;
    virtual void Product(S32* SourceA, S32 Length, S32& Result) const;
    virtual void Product(F32* SourceA, S32 Length, F32& Result) const;
    /**
    * \brief 将数组中所有元素统一赋值
    * \param SourceA 数组Ａ
    * \param Length 数组长度
    * \param Value 所赋值
    */
    virtual void Set(S16* SourceA, S16 Value, S32 Length) const;
    virtual void Set(S32* SourceA, S32 Value, S32 Length) const;
    virtual void Set(F32* SourceA, F32 Value, S32 Length) const;
    /**
      * \brief 求数组中的最大值
      * \param Length 数组长度
      * \param Result 数组中的最大值
      * \param Order 数组中的最大值所在位置
      */
    virtual void Max(S16* SourceA, S32 Length, S16& Result, S32& Order) const;
    virtual void Max(S32* SourceA, S32 Length, S32& Result, S32& Order) const;
    virtual void Max(F32* SourceA, S32 Length, F32& Result, S32& Order) const;
    virtual void Max(F32* SourceA, S32 Length, F32& Result) const;

    /**
      * \brief 求数组中的最小值
      * \param Length 数组长度
      * \param Result 数组中的最小值
      * \param Order 数组中的最小值所在位置
      */
    virtual void Min(S16* SourceA, S32 Length, S16& Result, S32& Order) const;
    virtual void Min(S32* SourceA, S32 Length, S32& Result, S32& Order) const;
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
    /**
      * \brief 判断两组向量是否相同
      * \param SourceA 向量1
      * \param SourceB 向量2
      * \param Length 向量维数
      * \param Error 阈值
      * \param IsSame 布尔输出两向量是否相同，0为相同1为不同
      */
    virtual void Compare(F32* SourceA, F32* SourceB, F32 Error,S32 Length,BOOL* IsSame) const;

};
} // namespace itr_math

#endif //* CALCULATE_H_
