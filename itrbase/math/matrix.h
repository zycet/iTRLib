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
            //构造&析构
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
             * 回收自动分配的内存
             */
            virtual ~Matrix();

            //成员属性
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

            //数据转移
            //Data Copy
            /*
             * 将传入的数据复制至指定的矩形区域
             */
            void virtual CopyFrom(S32 RowOffset, S32 ColOffset, S32 RowNum, S32 ColNum, F32* Data);
            /*
             * 将传入的数据全部复制到矩阵中
             */
            void virtual CopyFrom(F32* Data);
            /*
             * 将指定的矩形区域复制到出来
             */
            void virtual CopyTo(S32 RowOffset, S32 ColOffset, S32 RowNum, S32 ColNum,
                    F32* Data) const;
            /*
             * 将全部数据复制出来
             */
            void virtual CopyTo(F32* Data) const;
            //Copy Row From
            /*
             * 将传入数据复制到指定行的部分区域
             */
            void virtual CopyRowFrom(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data);
            /*
             * 将传入数据复制到指定行
             */
            void virtual CopyRowFrom(S32 RowNo, F32* Data);
            //Copy Row To
            /*
             * 复制指定行的部分数据出来
             */
            void virtual CopyRowTo(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data) const;
            /*
             * 复制定制行数据处理
             */
            void virtual CopyRowTo(S32 RowNo, F32* Data) const;
            //Copy Col From
            /*
             * 将数据复制到指定列的部分区域
             */
            void virtual CopyColFrom(S32 ColNo, S32 RowOffset, S32 RowNum, F32* Data);
            /*
             * 将数据复制到指定列
             */
            void virtual CopyColFrom(S32 ColNo, F32* Data);
            //Copy Col To
            /*
             * 复制指定列的部分区域数据出来
             */
            void virtual CopyColTo(S32 ColNo, S32 RowOffset, S32 RowlNum, F32* Data) const;
            /*
             * 复制指定列的数据出来
             */
            void virtual CopyColTo(S32 ColNo, F32* Data) const;

            //初等变换
            //Add Row
            /*
             * 将RowNoAdd行加至RowNoResult行
             */
            void virtual AddRow(S32 RowNoAdd, S32 RowNoResult);
            /*
             * 将Data加至RowNoResult行
             */
            void virtual AddRow(F32* Data, S32 RowNoResult);
            //Sub Row
            /*
             * 将RowNoSub行减至RowNoResult行
             */
            void virtual SubRow(S32 RowNoSub, S32 RowNoResult);
            /*
             * 将Data减至RowNoResult行
             */
            void virtual SubRow(F32* Data, S32 RowNoResult);
            //Mul Row
            /*
             * 将RowNoResult行乘以K
             */
            void virtual MulRow(F32 K, S32 RowNoResult);
            //Swap Row
            /*
             * 交换RowNoA行和RowNoB行
             */
            void virtual SwapRow(S32 RowNoA, S32 RowNoB);
            //Add Col
            /*
             * 将ColNoAdd列加至ColNoResult行
             */
            void virtual AddCol(S32 ColNoAdd, S32 ColNoResult);
            /*
             * 将Data加至ColNoResult行
             */
            void virtual AddCol(F32* Data, S32 ColNoResult);
            //Sub Col
            /*
             * 将ColNoSub列减至ColNoResult行
             */
            void virtual SubCol(S32 ColNoSub, S32 ColNoResult);
            /*
             * 将Data减至ColNoResult行
             */
            void virtual SubCol(F32* Data, S32 ColNoResult);
            //Mul Col
            /*
             * 将ColNoResult列乘以K
             */
            void virtual MulCol(F32 K, S32 ColNoResult);
            //Swap Col
            /*
             * 交换ColNoA列和ColNoB列
             */
            void virtual SwapCol(S32 ColNoA, S32 ColNoB);

            //相关计算
            //Value Calc
            /*
             * 全部元素加上K
             */
            void virtual Add(F32 K);
            /*
             * 全部元素减去K
             */
            void virtual Sub(F32 K);
            /*
             * 全部元素乘以K
             */
            void virtual Mul(F32 K);
            //Vector Calc
            /*
             * 右乘向量并将结果存至VectorResult
             */
            void virtual Mul(const Vector& VectorMul, Vector& VectorResult);
            //Matrix Calc
            /*
             * 加上矩阵MatrixAdd
             */
            void virtual Add(const Matrix& MatrixAdd);
            /*
             * 减去矩阵MatrixSub
             */
            void virtual Sub(const Matrix& MatrixSub);
            /*
             * 乘以矩阵Matrix并将结果存至MatrixResult
             */
            void virtual Mul(const Matrix& MatrixMul, Matrix& MatrixResult);

            //Clear
            //Eye
            //bool checkDimRight(const Vector& vector) const;

        private:
            S32 row, col;
            F32* data;
            BOOL localData;
    };

} // namespace itr_math

#endif // MATRIX_H_
