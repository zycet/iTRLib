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
    Numerical* Matrix::numericalObj = NULL;
    Calculate* Matrix::calculateObj = NULL;

    /*
     * 初始化一个指定行列数的空矩阵(自动分配内存)
     */
    Matrix::Matrix(S32 Row, S32 Col)
    {
        assert(numericalObj!=NULL && calculateObj!=NULL);
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
        assert(numericalObj!=NULL && calculateObj!=NULL);
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
        assert(numericalObj!=NULL && calculateObj!=NULL);
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
        assert(numericalObj!=NULL && calculateObj!=NULL);
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

}
// namespace itr_math
