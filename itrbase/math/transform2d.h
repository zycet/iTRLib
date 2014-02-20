#ifndef TRANSFORM2D_H_
#define TRANSFORM2D_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
/**
 * brief 2D仿射变换器
 * note 初始化后按需求调用偏移、缩放、旋转后调用变换函数对目标坐标进行转换
 */
class Transform2D
{
public:
    Transform2D();
    virtual ~Transform2D();
    /**
     * brief 返回内部变换矩阵（3*3）
     */
    inline Matrix& GetTransformMatrix()
    {
        return transformMatrix;
    }
    /**
     * brief 重置为初始状态
     */
    void Reset();
    /**
     * brief 直角坐标偏移
     * param X 横向偏移
     * param Y 纵向偏移
     */
    void Offset(F32 X, F32 Y);
    /**
     * brief 直角坐标缩放
     * param KX 横向缩放
     * param KY 纵向缩放
     * note 系数为1表示不缩放，大于1放到，小于1缩小(负数则镜像)
     */
    void Scale(F32 KX, F32 KY);
    /**
     * brief 旋转
     * param Angle 旋转角度
     * note（右手坐标系，逆时针为正，角度制）
     */
    void Rotate(F32 Angle);
    /**
     * brief 反转矩阵使其可以进行反向变换
     */
    void Inv();

    /**
     * brief 2元向量坐标变换
     * param Input 输入
     * param Output 输出
     * note Input&Output维度均需为3(齐次坐标）
     */
    void Transform(const Vector& Input, Vector& Output);
    /**
     * brief 2D点坐标变换
     * param Input 输入
     * param Output 输出
     */
    void Transform(const Point2D& Input, Point2D& Output);
    /**
     * brief 2D坐标变换
     * param InputX 输入X
     * param InputY 输出Y
     * param OutputX 输入X
     * param OutputY 输出Y
     */
    void Transform(F32 InputX, F32 InputY, F32& OutputX, F32& OutputY);

private:
    Matrix transformMatrix;
    Matrix tempMatrix;
    Vector inputVector;
    Vector outputVector;
    Numerical numericalObj;
    void Reset(Matrix& Mat);
};

} // namespace itr_math
#endif // TRANSFORM2D_H_
