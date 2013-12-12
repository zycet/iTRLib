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
 * math.h
 *  Created on: 2013-9-13
 *      Author: buaa
 */

#ifndef MATH_H_
#define MATH_H_

#define PI 3.14159265359
#define ANG2RAD(x) (x*0.01745329251)
#define RAD2ANG(x) (x*57.2957795131)

#include "numerical.h"
namespace itr_math
{
    extern Numerical* NumericalObj;
}
#include "calculate.h"
namespace itr_math
{
    extern Calculate* CalculateObj;
}
#include "statistics.h"
namespace itr_math
{
    extern Statistics* StatisticsObj;
}
#include "vector.h"
namespace itr_math
{
	extern Vector* VectorObj;
}
#include "matrix.h"
#include "geometry.h"
#include "transform2d.h"
#include "gaussiangenerate.h"
namespace itr_math
{
    void MathObjStandInit();
    void MathObjStandDeinit();
}

#endif // MATH_H_
