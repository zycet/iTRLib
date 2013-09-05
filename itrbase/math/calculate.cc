/*
 * calculate.cpp
 *
 *  Created on: 2013-9-5
 *      Author: buaa
 */

#include "calculate.h"

namespace itr_math
{
    Calculate::Calculate()
    {
    }

    Calculate::~Calculate()
    {
    }

    void Calculate::Add(S32* SourceA,S32* SourceB, S32 Length,
            S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

    void Calculate::Add(F32* SourceA,F32* SourceB, S32 Length,
            F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

} /* namespace itr_math */
