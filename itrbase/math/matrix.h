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
 * matrix.h
 *  Created on: 2013-9-14
 *      Author: zhouyi
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
    class Matrix
    {
        public:
            /*
             * 设置数值计算对象(此函数需要在进行所有计算前调用)
             */
            inline static void SetNumericalObj(Numerical* NumericalObj)
            {
                numericalObj = NumericalObj;
            }
            /*
             * 设置批量计算对象(此函数需要在进行所有计算前调用)
             */
            inline static void SetCalculateObj(Calculate* CalculateObj)
            {
                calculateObj = CalculateObj;
            }
            //**********构造&析构**********
            /*
             * 初始化一个指定行列数的空矩阵(自动分配内存)
             */
            Matrix(S32 Row, S32 Col);
            /*
             * 初始化一个指定行列数的矩阵(以传入的指针为数据区)
             */
            Matrix(S32 Row, S32 Col, F32* Data);
            /*
             * 初始化一个指定阶数的方阵(自动分配内存)
             */
            Matrix(S32 RowCol);
            /*
             * 初始化完全一样的矩阵(Clone)
             */
            Matrix(const Matrix& Mat);
            /*
             * 回收自动分配的内存
             */
            virtual ~Matrix();

            //**********成员属性**********
            /*
             * 获取行数
             */
            inline virtual S32 GetRow() const
            {
                return row;
            }
            /*
             * 获取列数
             */
            inline virtual S32 GetCol() const
            {
                return col;
            }
            /*
             * 获取数据地址
             */
            inline virtual F32* GetData() const
            {
                return data;
            }
            /*
             * 是否为初始化自动分配的本地数据
             */
            inline virtual BOOL IsLocalData() const
            {
                return localData;
            }

            //**********数据转移**********
            /*
             * 将传入的数据复制至指定的矩形区域
             */
            inline void virtual CopyFrom(S32 RowOffset, S32 ColOffset, S32 RowNum, S32 ColNum,
                    F32* Data)
            {
                assert((RowOffset + RowNum) <= row && (ColOffset + ColNum) <= col);
                assert(Data!=NULL);
                for (S32 i = 0; i < ColNum; i++)
                    MemoryCopy(data + (RowOffset - 1) * col + ColOffset + i * row, Data,
                            RowNum * sizeof(F32));
            }
            /*
             * 将传入的数据全部复制到矩阵中
             */
            inline void virtual CopyFrom(F32* Data)
            {
                assert(Data!=NULL);
                MemoryCopy(data, Data, row * col * sizeof(F32));
            }
            /*
             * 将指定的矩形区域复制到出来
             */
            inline void virtual CopyTo(S32 RowOffset, S32 ColOffset, S32 RowNum, S32 ColNum,
                    F32* Data) const
            {
                assert((RowOffset+RowNum) <= row && (ColOffset + ColNum)<=col);
                assert(Data!=NULL);
                for (S32 i = 0; i < col; i++)
                    MemoryCopy(Data, data + (RowOffset - 1) * col + ColOffset + i * row,
                            RowNum * sizeof(F32));
            }
            /*
             * 将全部数据复制出来
             */
            inline void virtual CopyTo(F32* Data) const
            {
                assert(Data!=NULL);
                MemoryCopy(Data, data, row * col * sizeof(F32));
            }
            //Copy Row From
            /*
             * 将传入数据复制到指定行的部分区域
             */
            inline void virtual CopyRowFrom(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data)
            {
                assert(RowNo <= row && ColOffset+ColNum <= col);
                assert(Data!=NULL);
                MemoryCopy(data + (RowNo - 1) * col + ColOffset, Data, ColNum * sizeof(F32));
            }
            /*
             * 将传入数据复制到指定行
             */
            inline void virtual CopyRowFrom(S32 RowNo, F32* Data)
            {
                assert(RowNo <= row);
                assert(Data!=NULL);
                MemoryCopy(data + (row - 1) * col, Data, col * sizeof(F32));
            }
            //Copy Row To
            /*
             * 复制指定行的部分数据出来
             */
            inline void virtual CopyRowTo(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data) const
            {
                assert(RowNo <= row && ColOffset+ColNum<=col);
                assert(Data !=NULL);
                MemoryCopy(Data, data + (RowNo - 1) * col + ColOffset, ColNum * sizeof(F32));
            }
            /*
             * 复制定制行数据处理
             */
            inline void virtual CopyRowTo(S32 RowNo, F32* Data) const
            {
                assert(RowNo <= row);
                assert(Data!=NULL);
                MemoryCopy(Data, data + (row - 1) * col, col * sizeof(F32));
            }
            //Copy Col From
            /*
             * 将数据复制到指定列的部分区域
             */
            inline void virtual CopyColFrom(S32 ColNo, S32 RowOffset, S32 RowNum, F32* Data);
            /*
             * 将数据复制到指定列
             */
            inline void virtual CopyColFrom(S32 ColNo, F32* Data);
            //Copy Col To
            /*
             * 复制指定列的部分区域数据出来
             */
            inline void virtual CopyColTo(S32 ColNo, S32 RowOffset, S32 RowlNum, F32* Data) const;
            /*
             * 复制指定列的数据出来
             */
            inline void virtual CopyColTo(S32 ColNo, F32* Data) const;

            //**********数据访问**********
            /*
             * 写入单个元素(一维线性访问)
             */
            inline F32& operator[](int index)
            {
                assert(index < row * col);
                return data[index];
            }
            /*
             * 读取单个元素(一维线性访问)
             */
            inline F32 operator[](int index) const
            {
                assert(index < row * col);
                return data[index];
            }
            /*
             * 写入单个元素(Y=行数,X=列数)
             */
            inline F32& operator()(int Y, int X)
            {
                assert(X < col);
                assert(Y < row);
                return data[Y * col + X];
            }
            /*
             * 读取单个元素(Y=行数,X=列数)
             */
            inline F32 operator()(int Y, int X) const
            {
                assert(X < col);
                assert(Y < row);
                return data[Y * col + X];
            }

            //**********数据操作**********
            /*
             * 设置所有元素为0
             */
            inline void virtual Clear();
            /*
             * 设置所有元素为K
             */
            inline void virtual Set(F32 K);
            /*
             * 设置主对角线元素为K
             */
            void virtual SetDiag(F32 K);
            /*
             * 设置主对角线元素为Data
             */
            void virtual SetDiag(F32* Data);
            /*
             * 将主对角线元素放至Data
             */
            void virtual GetDiag(F32* Data) const;

            //**********维数匹配**********
            /*
             * 检查维数与Mat是否一致
             */
            inline void virtual MatchDim(const Matrix& Mat) const;
            /*
             * 检查维数是否为Row,Col
             */
            inline void virtual MatchDim(int Row, int Col) const;
            /*
             * 检查维数是否可右乘Mat
             */
            inline void virtual MatchMul(const Matrix& Mat) const;
            /*
             * 检查维数是否可右乘行向量Vec
             */
            inline void virtual MatchRightMulRow(const Vector& Vec) const;
            /*
             * 检查维数是否可右乘列向量Vec
             */
            inline void virtual MatchRightMulCol(const Vector& Vec) const;
            /*
             * 检查维数是否可左乘行向量Vec
             */
            inline void virtual MatchLeftMulRow(const Vector& Vec) const;
            /*
             * 检查维数是否可左乘列向量Vec
             */
            inline void virtual MatchLeftMulCol(const Vector& Vec) const;

            //**********初等变换**********
            /*
             * 将RowNoAdd行加至RowNoResult行
             */
            void virtual AddRow(S32 RowNoAdd, S32 RowNoResult);
            /*
             * 将Data加至RowNoResult行
             */
            void virtual AddRow(F32* Data, S32 RowNoResult);
            /*
             * 将RowNoSub行减至RowNoResult行
             */
            void virtual SubRow(S32 RowNoSub, S32 RowNoResult);
            /*
             * 将Data减至RowNoResult行
             */
            void virtual SubRow(F32* Data, S32 RowNoResult);
            /*
             * 将RowNoResult行乘以K
             */
            void virtual MulRow(F32 K, S32 RowNoResult);
            //Swap Row
            /*
             * 交换RowNoA行和RowNoB行
             */
            void virtual SwapRow(S32 RowNoA, S32 RowNoB);
            /*
             * 将ColNoAdd列加至ColNoResult行
             */
            void virtual AddCol(S32 ColNoAdd, S32 ColNoResult);
            /*
             * 将Data加至ColNoResult行
             */
            void virtual AddCol(F32* Data, S32 ColNoResult);
            /*
             * 将ColNoSub列减至ColNoResult行
             */
            void virtual SubCol(S32 ColNoSub, S32 ColNoResult);
            /*
             * 将Data减至ColNoResult行
             */
            void virtual SubCol(F32* Data, S32 ColNoResult);
            /*
             * 将ColNoResult列乘以K
             */
            void virtual MulCol(F32 K, S32 ColNoResult);
            /*
             * 交换ColNoA列和ColNoB列
             */
            void virtual SwapCol(S32 ColNoA, S32 ColNoB);

            //**********常量相关计算**********
            /*
             * 全部元素加上K
             */
            void virtual Add(F32 K);
            /*
             * 全部元素乘以K
             */
            void virtual Mul(F32 K);

            //**********向量相关计算**********
            /*
             * 左乘行向量
             */
            void virtual LeftMulRow(const Vector& Vec, Matrix& MatResult) const;
            /*
             * 左乘列向量
             */
            void virtual LeftMulCol(const Vector& Vec, Matrix& MatResult) const;
            /*
             * 右乘行向量
             */
            void virtual RightMulRow(const Vector& Vec, Matrix& MatResult) const;
            /*
             * 左乘行向量
             */
            void virtual RightMulCol(const Vector& Vec, Matrix& MatResult) const;

            //**********矩阵相关计算**********
            /*
             * 加上矩阵MatrixAdd
             */
            void virtual Add(const Matrix& Mat);
            /*
             * 减去矩阵MatrixSub
             */
            void virtual Sub(const Matrix& Mat);
            /*
             * 右乘矩阵Mat并将结果存至MatResult
             */
            void virtual Mul(const Matrix& Mat, Matrix& MatResult) const;
            /*
             * 求矩阵逆并将结果放至MatResult
             */
            void virtual Inv(Matrix& MatResult) const;

            /*
             * 求矩阵转置并将结果放至MatResult
             */
            void virtual Tran(Matrix& MatResult) const;

            /*
             * 求矩阵行列式值
             */
            F32 virtual Det() const;

        private:
            S32 row, col;
            F32* data;
            BOOL localData;
            static Numerical* numericalObj;
            static Calculate* calculateObj;
    };

} // namespace itr_math

#endif // MATRIX_H_
