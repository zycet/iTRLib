#ifndef BOXHESSIAN_H
#define BOXHESSIAN_H

#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{
/**
* \brief 此类使用盒式积分滤波器的方法快速求出积分图像的Hessian值
*/
class BoxHessian
{
public:
    /**
    * \brief 初始化基本数据,需后续调用Init()才可正常使用.
    */
    BoxHessian();
    /**
    * \brief 回收资源
    */
    virtual ~BoxHessian();
    /**
    * \brief 返回Hessian值数组.
    */
    F32* GetHessianData() const;
    /**
    * \brief 返回Laplacian值数组.
    */
    U8* GetLaplacianData() const;
    /**
    * \brief 返回初始的宽度
    */
    S32 GetWidth() const;
    /**
    * \brief 返回初始的高度
    */
    S32 GetHeight() const;
    /**
    * \brief 初始化BoxHessian滤波器
    * \param Width 处理的图像宽度
    * \param Height 处理的图像高度
    * \param Step 滤波器步进值
    * \param FilterLength 滤波器长度
    * \note 只有此函数成功执行后才可正在运行
    */
    void Init(S32 Width,S32 Height,S32 Step,S32 FilterLength);
    /**
    * \brief 计算输入图像的Hessian与Laplacian值
    * \param Img 待处理的输入图像
    * \note 只有此函数成功执行后才可正在运行
    */
    void Calc(const Matrix& Img);
    /**
    * \brief 返回指定位置的Hessian值
    * \param RowPos 行位置
    * \param ColPos 列位置
    */
    F32 GetHessian(S32 RowPos,S32 ColPos) const;
    /**
    * \brief 返回指定位置的Hessian值(在指定尺度下)
    * \param RowPos 行位置
    * \param ColPos 列位置
    * \param Scale 指定的尺度
    */
    F32 GetHessian(S32 RowPos,S32 ColPos,BoxHessian* Scale) const;
    /**
    * \brief 返回指定位置的Laplacian值
    * \param RowPos 行位置
    * \param ColPos 列位置
    */
    U8 GetLaplacian(S32 RowPos,S32 ColPos) const;
    /**
    * \brief 返回指定位置的Laplacian值(在指定尺度下)
    * \param RowPos 行位置
    * \param ColPos 列位置
    * \param Scale 指定的尺度
    */
    U8 GetLaplacian(S32 RowPos,S32 ColPos,BoxHessian* Scale) const;
    /**
    * \brief 滤波步进值
    */
    S32 Step;
    /**
    * \brief 滤波器长度
    */
    S32 FilterLength;

    F32* Hessian;
    U8* Laplacian;
private:
    S32 Width,Height;
    //F32* Hessian;
    //U8* Laplacian;
};
}

#endif // BOXHESSIAN_H
