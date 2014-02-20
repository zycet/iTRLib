#ifndef MATRIX_H_
#define MATRIX_H_

#include "../platform/platform.h"
#include "math.h"
#include <stdio.h>

namespace itr_math
{
/**
 * 矩阵所有操作参数均为先行号(Row=Y=Height)后列号(Col=X=Width)
 * 矩阵初始化只支持以下几种形式，不支持初始化直接等于另一个矩阵。
 * eg:Matrix a = Source (不允许这样用)
 */
class Matrix
{
public:
    //**********构造&析构**********
    /**
    * /brief 初始化一个指定行列数的空矩阵(自动分配内存)
    * /param Row 行数
    * /param Col 列数
    */
    Matrix(S32 Row, S32 Col);
    /**
    * /brief 初始化一个指定行列数的矩阵(以传入的指针为数据区，不分配本地内存)
    * /param Row 行数
    * /param Col 列数
    * /param Data 数据
    */
    Matrix(S32 Row, S32 Col, F32* Data);
    /**
    * /brief 初始化一个指定阶数的方阵(自动分配内存)
    * /param RowCol 行列数
    */
    Matrix(S32 RowCol);
    /**
    * /brief 初始化完全一样的矩阵(Clone)
    * /param Mat 被复制的矩阵
    */
    Matrix(const Matrix& Mat);
    /**
    * /brief 用于初始化列表的空构造函数(Clone)
    * /note 在构造后需手动调用Init函数
    */
    Matrix();
    /**
     * /brief 回收自动分配的内存
     */
    virtual ~Matrix();

    //**********后初始化函数**********
    /**
    * /brief 初始化一个指定行列数的空矩阵(自动分配内存，只能在无参数构造对象后调用)
    * /param Row 行数
    * /param Col 列数
    */
    void Init(S32 Row, S32 Col);
    /**
    * /brief 初始化一个指定行列数的空矩阵(自动分配内存，只能在无参数构造对象后调用)
    * /param Row 行数
    * /param Col 列数
    * /param Data 数据指针
    */
    void Init(S32 Row, S32 Col, F32* Data);
    /**
    * /brief 初始化完全一样的矩阵(Clone)
    * /param Mat 被复制的矩阵
    */
    void Init(S32 RowCol);
    //**********初等变换**********
    /**
    * /brief 将RowPosSource行加RowPosTarget行
    * /param RowPosSource 加数行
    * /param RowPosTarget 被加行
    */
    void virtual AddRow(S32 RowPosSource, S32 RowPosTarget);
    /**
    * /brief 将Data加RowPosTarget行
    * /param Data 加数
    * /param RowPosTarget 被加行
    */
    void virtual AddRow(F32* Data, S32 RowPosTarget);
    /**
    * /brief 将RowPosSource减至RowPosTarget行
    * /param RowPosSource 减数行
    * /param RowPosTarget 被减行
    */
    void virtual SubRow(S32 RowPosSource, S32 RowPosTarget);
    /**
    * /brief 将Data减至RowPosTarget行
    * /param Data 减数
    * /param RowPosTarget 被减行
    */
    void virtual SubRow(F32* Data, S32 RowPosTarget);
    /**
    * /brief 将K乘RowPosTarget行
    * /param K  乘数
    * /param RowPosTarget 被乘行
    */
    void virtual MulRow(F32 K, S32 RowPosTarget);
    /**
    * /brief 交换两行数据
    * /param RowNoA 行A
    * /param RowNoB 行B
    */
    void virtual SwapRow(S32 RowNoA, S32 RowNoB);
    /**
    * /brief 将RowPosSource列加RowPosTarget列
    * /param RowPosSource 加数列
    * /param RowPosTarget 被加列
    */
    void virtual AddCol(S32 ColPosSource, S32 ColPosTarget);
    /**
    * /brief 将Data加RowPosTarget列
    * /param Data 加数
    * /param RowPosTarget 被加列
    */
    void virtual AddCol(F32* Data, S32 ColPosTarget);
    /**
    * /brief 将RowPosSource减至RowPosTarget列
    * /param RowPosSource 减数列
    * /param RowPosTarget 被减列
    */
    void virtual SubCol(S32 ColPosSource, S32 ColPosTarget);
    /**
    * /brief 将Data减至RowPosTarget列
    * /param Data 减数
    * /param RowPosTarget 被减列
    */
    void virtual SubCol(F32* Data, S32 ColPosTarget);
    /**
    * /brief 将K乘RowPosTarget列
    * /param K  乘数
    * /param RowPosTarget 被乘列
    */
    void virtual MulCol(F32 K, S32 ColPosTarget);
    /**
    * /brief 交换两列数据
    * /param RowNoA 列A
    * /param RowNoB 列B
    */
    void virtual SwapCol(S32 ColNoA, S32 ColNoB);

    //**********常量相关计算**********
    /**
    * /brief 全部元素加K
    * /param K 加数
    */
    void virtual AllAdd(F32 K);
    /**
    * /brief 全部元素乘K
    * /param K 乘数
    */
    void virtual AllMul(F32 K);

    //**********矩阵相关计算**********

    /**
    * /brief 加上矩阵Mat
    * /param Mat 加上的矩阵
    */
    void virtual Add(const Matrix& Mat);
    /**
    * /brief 减去矩阵Mat
    * /param Mat 减去的矩阵
    */
    void virtual Sub(const Matrix& Mat);
    /**
    * /brief 右乘矩阵Mat
    * /param Mat 右乘的矩阵
    * /param MatResult 输出矩阵
    */
    void virtual Mul(const Matrix& Mat, Matrix& MatResult) const;

    Matrix virtual operator*(const Matrix& Mat) const;
    Matrix virtual operator+(const Matrix& Mat) const;
    Matrix virtual operator-(const Matrix& Mat) const;
    Matrix virtual operator=(const Matrix& Mat);
    //**********向量相关计算**********
    Vector virtual operator*(const Vector& vec) const;
    //**********常用操作**********
    /**
    * /brief 抽取矩阵中的某列
    * /param Data 指针
    * /param Offset 抽取的列位置
    * /param Interval 列数
    * /param Length 行数
    */
    void virtual ColExtract(F32* Data, S32 Offset, S32 Interval, S32 Length, F32* Result);
    /******************************
    *******Advanced Function*******
    *******************************/

    /**
    * /brief 求矩阵的逆
    * /param MatResult 所得结果
    */
    BOOL virtual Inv(Matrix& MatResult) const;
    /**
    * /brief
    */
    Matrix virtual Inv() const;
    /**
    * /brief 求矩阵的行列式
    * /param det 所得结果
    */
    void Det(F32 &reslut);
    /**
     * /brief求矩阵SVD(奇异值分解）A=U*S*Vt A(n*m)
     * /param w(n) :存储奇异值，最少为一个，最多为n个非零值，w即为S的对角矩阵
     * /param v:存储向量V，注意不是V的转置
     * /param 注意：生成的U替换为A，即改变原矩阵。
     */

    void Svdcmp(Vector &w, Matrix &v) ;
    /**
     * /brief 求矩阵广义逆,注意：只能用于方阵，且原始数据改变（变为U，见SVD），不可用。
                matrix.cc中的 #define tol  0.00001 代表精度
     * /param MatResult 所得的结果
     */
    void virtual pinv(Matrix &MatResult) const;
    /*
     * 求矩阵转置并将结果放至MatResult
     */

    /**
    * /brief 求矩阵的转置
    * /param MatResult 所得结果
    */

    void virtual Tran(Matrix& MatResult) const;
    /**
    * /brief 求矩阵的转置
    */
    Matrix virtual Tran() const;
    /**
    * /brief 求矩阵的迹
    * /param K 矩阵的迹
    */
    void virtual Tr(F32 K)
    {
        K=0;
        for (S32 i = 0; i < row&&i<col; i++)
            K+=data[i * row + i];
    }
    //**********内联函数**********
    /**
    * /brief 获取行数
    */
    inline virtual S32 GetRow() const
    {
        return row;
    }
    /**
    * /brief 获取列数
    */
    inline virtual S32 GetCol() const
    {
        return col;
    }
    /**
    * /brief 获取数据地址
    */
    inline virtual F32* GetData() const
    {
        return data;
    }
    /**
    * /brief 是否为初始化自动分配的本地数据
    */
    inline virtual BOOL IsLocalData() const
    {
        return localData;
    }

    //**********数据转移**********
    /**
    * /brief 将传入的数据复制至this矩阵中的指定的矩形区域
    * /param RowPos 插入位置的行数
    * /param ColPos 插入位置的列数     (即往this矩阵写入的起点）
    * /param Width 插入矩阵的宽度      （！！！要求该宽度等于传入数据的col)
    * /param Height 插入矩阵的高度
    */
    inline void virtual CopyFrom(S32 RowPos, S32 ColPos, S32 Width, S32 Height, F32* Data)
    {
        assert(RowPos >= 0 && RowPos < row);
        assert(ColPos >= 0 && ColPos < col);
        assert(RowPos + Height <= row);
        assert(ColPos + Width <= col);
        assert(Data!=NULL);
        for (S32 i = 0; i < Height; i++)
        {
            MemoryCopy(data +   col* (RowPos+i) + ColPos, Data + i * Width, Width * sizeof(F32));
        }
    }
    /**
    * /brief 将传入的数据全部复制进this矩阵中
    * /param Data 指针
    */
    inline void virtual CopyFrom(F32* Data)
    {
        assert(Data!=NULL);
        MemoryCopy(data, Data, row * col * sizeof(F32));
    }
    /**
    * /brief 将指定的矩形区域(给定的其他矩阵)复制到this矩阵中来
    * /param RowPos 复制起始位置的行数
    * /param ColPos 复制起始位置的列数 （行数和列数就是复制的起点）
    * /param Width 复制的宽度—— ！！！！该宽度等于给定矩阵的col
    * /param Height 复制的高度
    */
    inline void virtual CopyTo(S32 RowPos, S32 ColPos, S32 Width, S32 Height,
                               F32* Data) const
    {
        assert(RowPos >= 0 && RowPos < row);
        assert(ColPos >= 0 && ColPos < col);
        assert(RowPos + Height <= row);
        assert(ColPos + Width <= col);
        assert(Data!=NULL);
        for (S32 i = 0; i < Height; i++)
        {
            MemoryCopy(Data + i * Width, data +  col * (RowPos+i) + ColPos, Width * sizeof(F32));
        }
    }
    /**
    * /brief 将矩阵全部数据复制到给定的数组（指针）
    * /param Data 指针
    */
    inline void virtual CopyTo(F32* Data) const
    {
        assert(Data!=NULL);
        MemoryCopy(Data, data, row * col * sizeof(F32));
    }
    /**
    * /brief 将传入数据复制到指定行的部分区域
    * /param RowPos 复制到的行的位置
    * /param ColPos 复制到的列的位置
    * /param ColNum 复制的列数
    */
    inline void virtual CopyRowFrom(S32 RowPos, S32 ColPos, S32 ColNum, F32* Data)
    {
        assert(RowPos >= 0 && RowPos < row);
        assert(ColPos >= 0 && ColPos < col);
        assert(ColNum >= 0 && ColNum + ColPos <= col);
        assert(Data!=NULL);
        MemoryCopy(data + RowPos * col + ColPos , Data, ColNum * sizeof(F32));
    }
    /**
    * /brief 将传入数据复制到指定行
    * /param RowPos 复制到的行的位置
    */
    inline void virtual CopyRowFrom(S32 RowPos, F32* Data)
    {
        assert(RowPos >= 0);
        assert(RowPos < row);
        assert(Data!=NULL);
        MemoryCopy(data + RowPos * col, Data, col * sizeof(F32));
    }
    /**
    * /brief 复制指定行的部分数据出来
    * /param RowPos 复制到的行的位置
    * /param ColPos 复制到的列的位置
    * /param ColNum 复制的列数
    */
    inline void virtual CopyRowTo(S32 RowPos, S32 ColPos, S32 ColNum, F32* Data) const
    {
        assert(RowPos >= 0 && RowPos < row);
        assert(ColPos >= 0 && ColPos < col);
        assert(ColNum + ColPos <= col);
        assert(Data !=NULL);
        MemoryCopy(Data, data + RowPos * col + ColPos, ColNum * sizeof(F32));
    }
    /**
    * /brief 复制指定行数据处理
    * /param RowPos 复制到的行的位置
    */
    inline void virtual CopyRowTo(S32 RowPos, F32* Data) const
    {
        assert(RowPos >= 0);
        assert(RowPos < row);
        assert(Data!=NULL);
        MemoryCopy(Data, data + RowPos * col, col * sizeof(F32));
    }
    /**
    * /brief 将数据复制到指定列的部分区域
    * /param RowPos 复制到的行的位置
    * /param ColPos 复制到的列的位置
    * /param RowNum 复制的行数
    */
    inline void virtual CopyColFrom(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data)
    {
        assert(ColPos >= 0 && ColPos < col);
        assert(RowPos >= 0 && RowPos < row);
        assert(RowPos + RowNum <= row);
        assert(Data!=NULL);
        S32 pos=RowPos*col+ColPos;
        for (S32 i = 0; i < RowNum; i++)
        {
            data[pos]=Data[i];
            pos+=col;
        }
    }
    /**
    * /brief 将数据复制到指定列
    * /param ColPos 复制到的列的位置
    */
    inline void virtual CopyColFrom(S32 ColPos, F32* Data)
    {
        assert(ColPos >= 0 && ColPos < col);
        assert(Data != NULL);
        S32 pos=ColPos;
        for (S32 i = 0; i < row; i++)
        {
            data[pos]=Data[i];
            pos+=col;
        }
    }
    /**
    * /brief 复制指定列的部分区域数据出来
    * /param RowPos 复制到的行的位置
    * /param ColPos 复制到的列的位置
    * /param RowNum 复制的行数
    */
    inline void virtual CopyColTo(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data) const
    {
        assert(ColPos >= 0 && ColPos < col);
        assert(RowPos >= 0 && RowPos < row);
        assert(RowPos + RowNum <= row);
        assert(Data!=NULL);
        S32 pos=RowPos*col+ColPos;
        for (S32 i = 0; i < RowNum; i++)
        {
            Data[i]=data[pos];
            pos+=col;
        }
    }
    /**
    * /brief 将数据复制到指定列
    * /param ColPos 复制到的列的位置
    */
    inline void virtual CopyColTo(S32 ColPos, F32* Data) const
    {
        assert(ColPos >= 0 && ColPos < col);
        assert(Data != NULL);
        S32 pos=ColPos;
        for (S32 i = 0; i < row; i++)
        {
            Data[i]=data[pos];
            pos+=col;
        }
    }

    //**********数据访问**********
    /**
     * /brief 写入单个元素(一维线性访问)
     */
    inline F32& operator[](S32 index)
    {
        assert(index >=0);
        assert(index < row * col);
        return data[index];
    }
    /**
    * /brief 读取单个元素(一维线性访问)
    */
    inline F32 operator[](S32 index) const
    {
        assert(index >=0);
        assert(index < row * col);
        return data[index];
    }
    /**
    * /brief 写入单个元素(Y=行数,X=列数),且会自动执行限位。
    */
    inline F32& operator()(S32 Y, S32 X)
    {
        if(X<0)
            X=0;
        if(X>=col)
            X=col-1;
        if(Y<0)
            Y=0;
        if(Y>=row)
            Y=row-1;
        return data[Y * col + X];
    }
    /*
     * 读取单个元素(Y=行数,X=列数),且会自动执行限位。
     */
    inline F32 operator()(S32 Y, S32 X) const
    {
        if(X<0)
            X=0;
        if(X>=col)
            X=col-1;
        if(Y<0)
            Y=0;
        if(Y>=row)
            Y=row-1;
        return data[Y * col + X];
    }

    //**********数据操作**********
    /*
     * 设置所有元素为K
     */
    inline void virtual Set(F32 K)
    {
        for (S32 i = 0; i < row * col; i++)
            data[i] = K;
    }
    /*
     * 设置所有元素为0
     */
    inline void virtual Clear()
    {
        Set(0);
    }
    /*
     * 设置主对角线元素为K
     */
    inline void virtual SetDiag(F32 K)
    {
        for (S32 i = 0; i < row; i++)
            data[i * row + i] = K;
    }
    /*
     * 设置主对角线元素为Data
     */
    inline void virtual SetDiag(F32* Data)
    {
        assert(Data!=NULL);
        for (S32 i = 0; i < row; i++)
            data[i * row + i] = Data[i];
    }
    /*
     * 将主对角线元素放至Data
     */
    inline void virtual GetDiag(F32* Data) const
    {
        assert(Data!=NULL);
        for (S32 i = 0; i < row; i++)
            Data[i] = data[i * row + i];
    }

    //**********维数匹配**********
    /*
     * 检查维数与Mat是否一致
     */
    inline BOOL virtual MatchDim(const Matrix& Mat) const
    {
        if (Mat.row == row && Mat.col == col)
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否为Row,Col
     */
    inline BOOL virtual MatchDim(S32 Row, S32 Col) const
    {
        if (Row == row && Col == col)
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否可右乘Mat
     */
    inline BOOL virtual MatchMul(const Matrix& Mat) const
    {
        if (col == Mat.row)
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否可右乘行向量Vec
     */
    inline BOOL virtual MatchRightMulRow(const Vector& Vec) const
    {
        if (col == Vec.GetDim())
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否可右乘列向量Vec
     */
    inline BOOL virtual MatchRightMulCol(const Vector& Vec) const
    {
        if (col == 1&&row==Vec.GetDim())
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否可左乘行向量Vec
     */
    inline BOOL virtual MatchLeftMulRow(const Vector& Vec) const
    {
        if (row == Vec.GetDim())
            return true;
        else
            return false;
    }
    /*
     * 检查维数是否可左乘列向量Vec
     */
    inline BOOL virtual MatchLeftMulCol(const Vector& Vec) const
    {
        if (row == 1&&col==Vec.GetDim())
            return true;
        else
            return false;
    }

    inline BOOL CompMatrix(Matrix& Mat)
    {
        BOOL r;
        r=MatchDim(Mat);
        if(r==false)
            return false;
        itr_math::CalculateObj->Compare(GetData(),Mat.GetData(),1,col*row,&r);
        return r;
    }

private:
    S32 row, col;
    F32* data;
    BOOL localData;
};

} // namespace itr_math

#endif // MATRIX_H_
