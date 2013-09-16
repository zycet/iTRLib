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
 * statistics.cc
 *  Created on: 2013-9-14
 *      Author: zhouyi
 */

#include "statistics.h"

namespace itr_math
{

    Statistics::Statistics(const Numerical& numericalObj, const Calculate& calculateObj)
    {
        this->numericalObj = numericalObj;
        this->calculateObj = calculateObj;
    }

    Statistics::~Statistics()
    {
        // TODO Auto-generated destructor stub
    }

    bool Statistics::Max(S32* Source, S32 Length, S32& Result)
    {
        Result = Source[0];
        for (S32 i = 0; i <= Length; i++)
        {
            if (Result <= Source[i])
                Result = Source[i];
        }
        return true;
    }

    bool Statistics::Max(F32* Source, F32 Length, F32& Result)
    {
        Result = Source[0];
        for (S32 i = 0; i <= Length; i++)
        {
            if (Result <= Source[i])
                Result = Source[i];
        }
        return true;
    }
} // namespace itr_math
