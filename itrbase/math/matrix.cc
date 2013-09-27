/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * matrix.cc
 *  Created on: 2013-9-14
 *      Author: zhouyi
 */

#include <stddef.h>
#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
    /*
     * 初始化一个指定行列数的空矩阵(自动分配内存)
     */
    Matrix::Matrix(S32 Row, S32 Col)
    {
        assert(NumericalObj!=NULL && CalculateObj!=NULL);
        assert(Row>0 && Col>0);
        data = new F32[Row * Col];
        assert(data!=NULL);
        row = Row;
        col = Col;
        localData = true;
    }
    /*
     * 初始化一个指定行列数的矩阵(以传入的指针为数据区)
     */
    Matrix::Matrix(S32 Row, S32 Col, F32* Data)
    {
        assert(NumericalObj!=NULL && CalculateObj!=NULL);
        assert(Row>0 && Col>0);
        data = Data;
        assert(data != NULL);
        row = Row;
        col = Col;
        localData = false;
    }
    /*
     * 初始化一个指定阶数的方阵(自动分配内存)
     */
    Matrix::Matrix(S32 RowCol)
    {
        assert(NumericalObj!=NULL && CalculateObj!=NULL);
        assert(RowCol>0);
        data = new F32[RowCol * RowCol];
        assert(data!=NULL);
        row = RowCol;
        col = RowCol;
        localData = true;
    }
    /*
     * 初始化完全一样的矩阵(Clone)
     */
    Matrix::Matrix(const Matrix& Mat)
    {
        assert(NumericalObj!=NULL && CalculateObj!=NULL);
        data = new F32[Mat.GetRow() * Mat.GetCol()];
        assert(data!=NULL);
        row = Mat.GetRow();
        col = Mat.GetCol();
        localData = true;
    }
    /*
     * 回收自动分配的内存
     */
    Matrix::~Matrix()
    {
        if (localData == true)
        {
            delete data;
        }
    }
    //**********初等变换**********
    /*
     * 将RowNoAdd行加至RowNoResult行
     */
    void Matrix::AddRow(S32 RowNoAdd, S32 RowNoResult)
    {
        assert(RowNoAdd <= row && RowNoResult <= row);
        CalculateObj->Add(data + (RowNoAdd - 1) * col, data + (RowNoResult - 1) * col, col,
                data + (RowNoResult - 1) * col);
    }
    /*
     * 将Data加至RowNoResult行
     */
    void Matrix::AddRow(F32* Data, S32 RowNoResult)
    {
        assert(Data!=NULL);
        assert(RowNoResult <= row);
        CalculateObj->Add(Data, data + (RowNoResult - 1) * col, col,
                data + (RowNoResult - 1) * col);
    }
    /*
     * 将RowNoSub行减至RowNoResult行
     */
    void Matrix::SubRow(S32 RowNoSub, S32 RowNoResult)
    {
        assert(RowNoSub <= row && RowNoResult <= row);
        CalculateObj->Sub(data + (RowNoResult - 1) * col, data + (RowNoSub - 1) * col, col,
                data + (RowNoResult - 1) * col);
    }
    /*
     * 将Data减至RowNoResult行
     */
    void Matrix::SubRow(F32* Data, S32 RowNoResult)
    {
        assert(Data!=NULL);
        assert(RowNoResult <= row);
        CalculateObj->Sub(data + (RowNoResult - 1) * col, Data, col,
                data + (RowNoResult - 1) * col);
    }
    /*
     * 将RowNoResult行乘以K
     */
    void Matrix::MulRow(F32 K, S32 RowNoResult)
    {
        assert(RowNoResult <= row);
        CalculateObj->Multi(K, data + (RowNoResult - 1) * col, col, data + (RowNoResult - 1) * col);
    }
    //Swap Row
    /*
     * 交换RowNoA行和RowNoB行
     */
    void Matrix::SwapRow(S32 RowNoA, S32 RowNoB)
    {
        assert(RowNoA <= row);
        assert(RowNoB <= row);
        MemorySwap(data + (RowNoA - 1) * col, data + (RowNoB - 1) * col, col);
    }
    /*
     * 将ColNoAdd列加至ColNoResult列
     */
    void Matrix::AddCol(S32 ColNoAdd, S32 ColNoResult)
    {
        assert(ColNoAdd<=col);
        assert(ColNoResult<=col);
        for (S32 i = 0; i < row; i++)
            data[i * col + ColNoResult] = data[i * col + ColNoAdd] + data[i * col + ColNoResult];
    }
    /*
     * 将Data加至ColNoResult列
     */
    void Matrix::AddCol(F32* Data, S32 ColNoResult)
    {
        assert(Data!=NULL);
        assert(ColNoResult<=col);
        for (S32 i = 0; i < row; i++)
            data[i * col + ColNoResult] = Data[i] + data[i * col + ColNoResult];
    }
    /*
     * 将ColNoSub列减至ColNoResult列
     */
    void Matrix::SubCol(S32 ColNoSub, S32 ColNoResult)
    {
        assert(ColNoSub<col);
        assert(ColNoResult<col);
        for (S32 i = 0; i < row; i++)
            data[i * col + ColNoResult] = data[i * col + ColNoResult] - data[i * col + ColNoSub];
    }
    /*
     * 将Data减至ColNoResult列
     */
    void Matrix::SubCol(F32* Data, S32 ColNoResult)
    {
        assert(Data!=NULL);
        assert(ColNoResult<=col);
        for (S32 i = 0; i < row; i++)
            data[i * col + ColNoResult] = data[i * col + ColNoResult] - Data[i];
    }
    /*
     * 将ColNoResult列乘以K
     */
    void Matrix::MulCol(F32 K, S32 ColNoResult)
    {
        assert(ColNoResult < col);
        for (S32 i = 0; i < row; i++)
            data[i * col + ColNoResult] = data[i * col + ColNoResult] * K;
    }
    /*
     * 交换ColNoA列和ColNoB列
     */
    void Matrix::SwapCol(S32 ColNoA, S32 ColNoB)
    {
        assert(ColNoA<=col);
        assert(ColNoB<=col);
        F32 temp;
        for (S32 i = 0; i < row; i++)
        {
            temp = data[i * col + ColNoB];
            data[i * col + ColNoB] = data[i * col + ColNoA];
            data[i * col + ColNoA] = temp;
        }
    }
    //**********常量相关计算**********
    /*
     * 全部元素加上K
     */
    void Matrix::Add(F32 K)
    {
        for (S32 i = 0; i < col; i++)
        {
            CalculateObj->Add(K, data + i * col, col, data + i * col);
        }
    }
    /*
     * 全部元素乘以K
     */
    void Matrix::Mul(F32 K)
    {
        for (S32 i = 0; i < col; i++)
        {
            CalculateObj->Multi(K, data + i * col, col, data + i * col);
        }
    }
    //**********矩阵相关计算**********
    /*
     * 用于抽取矩阵中的某列
     */
    void Matrix::ColFill(F32* Data, S32 Offset, S32 Interval, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = Data[Offset + Interval * i];
        }
    }
    /*
     * 加上矩阵MatrixAdd
     */
    void Matrix::Add(const Matrix& Mat)
    {
        CalculateObj->Add(this->data, Mat.GetData(), this->row * this->col, this->data);
    }
    /*
     * 减去矩阵MatrixSub
     */
    void Matrix::Sub(const Matrix& Mat)
    {
        CalculateObj->Sub(this->data, Mat.GetData(), this->row * this->col, this->data);
    }
    /*
     * 右乘矩阵Mat并将结果存至MatResult
     */
    void Matrix::Mul(const Matrix& Mat, Matrix& MatResult) const
    {
        assert(this->col == Mat.row);
        assert(this->row == MatResult.row);
        assert(Mat.col == MatResult.col);
        F32* tempVect = new F32[Mat.row];
        F32* tempVectAns = new F32[MatResult.row];
        for (S32 i = 0; i < Mat.col; i++)
        {
            MatResult.ColFill(Mat.GetData(), i, Mat.col, Mat.row, tempVect);
            for (S32 k = 0; k < MatResult.row; k++)
                CalculateObj->MultiSum(data + k * row, tempVect, Mat.row, tempVectAns[k]);
            MatResult.CopyColFrom(i, tempVectAns);
        }
    }
    //**********矩阵运算符重载*********
    Matrix Matrix::operator*(const Matrix& Mat) const
    {
        assert(Mat.row == col);
        Matrix MatResult(row, Mat.col);
        Mul(Mat, MatResult);
        return MatResult;
    }

    Matrix Matrix::operator+(const Matrix& Mat) const
    {
        assert(row == Mat.row);
        assert(col == Mat.col);
        Matrix Result(row, col);
        Result = *this;
        Result.Add(Mat);
        return Result;
    }
    Matrix Matrix::operator-(const Matrix& Mat) const
    {
        assert(row == Mat.row);
        assert(col == Mat.col);
        Matrix Result(row, col);
        Result = *this;
        Result.Sub(Mat);
        return Result;
    }
    void Matrix::operator=(const Matrix& Mat)
    {
        assert(row == Mat.row);
        assert(col == Mat.col);
        this->CopyTo(Mat.data);
    }
    /*
     * 求矩阵逆并将结果放至MatResult
     */
    //void virtual Inv(Matrix& MatResult) const;

    /*
     * 求矩阵转置并将结果放至MatResult
     */
    //void virtual Tran(Matrix& MatResult) const;

    /*
     * 求矩阵行列式值
     */
    //F32 virtual Det() const;
}
// namespace itr_math
