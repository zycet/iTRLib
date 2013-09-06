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

    void Calculate::Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

    void Calculate::Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

    void Calculate::Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] - SourceB[i];
        }
    }

    void Calculate::Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] - SourceB[i];
        }
    }

    void Calculate::Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * SourceB[i];
        }
    }

    void Calculate::Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * SourceB[i];
        }
    }

    void Calculate::Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] / SourceB[i];
        }
    }

    void Calculate::Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] / SourceB[i];
        }
    }

    void Calculate::Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + Offset;
        }
    }

    void Calculate::Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + Offset;
        }
    }

    void Calculate::Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * Scale;
        }
    }

    void Calculate::Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * Scale;
        }
    }

    void Calculate::Normal(S32* SourceA, S32 Length, S32* Result)
    {
        S32 temp = 0;
        for (S32 i = 0; i < Length; i++)
        {
            temp += SourceA[i] * SourceA[i];
        }
        for (S32 j = 0; j < Length; j++)
        {
            //Result[j] = SourceA[j]/
            //TODO:暂时没有sqrt
        }
    }

    void Calculate::Normal(F32* SourceA, S32 Length, F32* Result)
    {
        F32 temp = 0;
        for (S32 i = 0; i < Length; i++)
        {
            temp += SourceA[i] * SourceA[i];
        }
        for (S32 j = 0; j < Length; j++)
        {
            //Result[j] = SourceA[j]/
            //TODO:暂时没有sqrt
        }
    }

    void Calculate::Abs(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];

        }
    }

    void Calculate::Abs(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Opposite(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Opposite(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Sum(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[0] += SourceA[i];
        }
    }

    void Calculate::Sum(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[0] += SourceA[i];
        }
    }
    void Calculate::Product(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[0] *= SourceA[i];
        }
    }

    void Calculate::Product(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[0] *= SourceA[i];
        }
    }
} /* namespace itr_math */
