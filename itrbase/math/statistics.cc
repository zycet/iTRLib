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

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
    Numerical* Statistics::numericalObj = NULL;
    Calculate* Statistics::calculateObj = NULL;

    Statistics::Statistics()
    {
        assert(numericalObj!=NULL);
        assert(calculateObj!=NULL);
    }

    Statistics::~Statistics()
    {
        // TODO Auto-generated destructor stub
    }

    bool Statistics::Max(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        Result = Source[0];
        for (S32 i = 0; i < Length - 1; i++)
        {
            if (Result <= Source[i])
                Result = Source[i];
        }
        return true;
    }

    bool Statistics::Max(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        Result = Source[0];
        for (S32 i = 0; i < Length - 1; i++)
        {
            if (Result <= Source[i])
                Result = Source[i];
        }
        return true;
    }

    bool Statistics::Min(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        Result = Source[0];
        for (S32 i = 0; i < Length - 1; i++)
        {
            if (Result >= Source[i])
                Result = Source[i];
        }
        return true;
    }

    bool Statistics::Min(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        Result = 0;
        for (S32 i = 0; i < Length; i++)
        {
            if (Result >= Source[i])
                Result = Source[i];
        }
        return true;
    }

    bool Statistics::Mean(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        S32 Sum =0;
        for (S32 i = 0; i < Length ; i++)
        {
           Sum =  Sum + Source[i];
        }
        Result = Sum / Length;
        return true;
    }

    bool Statistics::Mean(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        F32 Sum = 0;
        for (S32 i = 0; i < Length; i++)
        {
           Sum =  Sum + Source[i];
        }
        Result = Sum / Length;
        return true;
    }

    bool Statistics::Median(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        S32 M;
        Max(Source, Length, M);
        S32 m;
        Min(Source, Length, m);
        Result = (M + m) / 2;
        return true;
    }

    bool Statistics::Median(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        F32 M;
        Max(Source, Length, M);
        F32 m;
        Min(Source, Length, m);
        Result = (M + m) / 2;
        return true;
    }

    bool Statistics::RMS(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        F32 RMSsum = 0;
        for (S32 i = 0; i < Length; i++)
        {
            RMSsum = RMSsum + Source[i] * Source[i];
        }
        F32 r;
        numericalObj->Sqrt((RMSsum / Length), r);
        Result = r;
        return true;
    }

    bool Statistics::RMS(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        F32 RMSsum = 0;
        for (S32 i = 0; i < Length; i++)
        {
            RMSsum = RMSsum + Source[i] * Source[i];
        }
        numericalObj->Sqrt(RMSsum / Length, Result);
        return true;
    }

    bool Statistics::STD(S32* Source, S32 Length, S32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        S32 aver;
        Mean(Source, Length, aver);
        S32* temp=new S32[Length];
        calculateObj->Offset(Source,-aver,Length,temp);
        calculateObj->Multi(temp,temp,Length,temp);
        S32 rS32=0;
        calculateObj->AddSum(temp,Length,rS32);
        F32 rF32=rS32;
        numericalObj->Sqrt((rF32 / Length), rF32);
        Result=rS32;
        return true;
    }

    bool Statistics::STD(F32* Source, S32 Length, F32& Result)
    {
        assert(Source!=NULL);
        assert(Length>0);
        F32 aver;
        Mean(Source, Length, aver);
        F32 STDsum = 0;
        for (S32 i = 0; i < Length; i++)
        {
           STDsum = STDsum * STDsum + Source[i] * Source[i];
        }
        numericalObj->Sqrt(STDsum / Length, Result);
        return true;
    }
} // namespace itr_math
