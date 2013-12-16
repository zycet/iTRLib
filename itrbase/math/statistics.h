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
 * statistics.h
 *  Created on: 2013-9-14
 *      Author: zhouyi
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class Statistics
{
public:
    Statistics();
    virtual ~Statistics();
    virtual bool Max(S32* Source, S32 Length, S32& Result) const;
    virtual bool Max(F32* Source, S32 Length, F32& Result) const;
    virtual bool Min(S32* Source, S32 Length, S32& Result) const;
    virtual bool Min(F32* Source, S32 Length, F32& Result) const;
    virtual bool Mean(S32* Source, S32 Length, S32& Result) const;
    virtual bool Mean(F32* Source, S32 Length, F32& Result) const;
    virtual bool Median(S32* Source, S32 Length, S32& Result) const;
    virtual bool Median(F32* Source, S32 Length, F32& Result) const;
    virtual bool RMS(S32* Source, S32 Length, S32& Result) const;
    virtual bool RMS(F32* Source, S32 Length, F32& Result) const;
    virtual bool Variance(S32* Source, S32 Length, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Result) const;
    virtual bool Variance(S32* Source, S32 Length, S32& Mean, S32& Result) const;
    virtual bool Variance(F32* Source, S32 Length, F32& Mean, F32& Result) const;
};

} // namespace itr_math

#endif //statistics STATISTICS_H_
