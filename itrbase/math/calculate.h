/*
 * calculate.h
 *
 *  Created on: 2013-9-5
 *      Author: buaa
 */

#ifndef CALCULATE_H_
#define CALCULATE_H_

#include "typedef.h"

namespace itr_math
{

    class Calculate
    {
        public:
            virtual void Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result);
            virtual void Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result);
            virtual void Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result);
            virtual void Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result);
            virtual void Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result);
            virtual void Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result);
            virtual void Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result);
            virtual void Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result);
            virtual void Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result);
            virtual void Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result);
            virtual void Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result);
            virtual void Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result);
            virtual void Normal(S32* SourceA, S32 Length, S32* Result);
            virtual void Normal(F32* SourceA, S32 Length, F32* Result);
            virtual void Abs(S32* SourceA, S32 Length, S32* Result);
            virtual void Abs(F32* SourceA, S32 Length, F32* Result);
            virtual void Opposite(S32* SourceA, S32 Length, S32* Result);
            virtual void Opposite(F32* SourceA, S32 Length, F32* Result);
            virtual void Sum(S32* SourceA, S32 Length, S32* Result);
            virtual void Sum(F32* SourceA, S32 Length, F32* Result);
            virtual void Product(S32* SourceA, S32 Length, S32* Result);
            virtual void Product(F32* SourceA, S32 Length, F32* Result);
            Calculate();
            virtual ~Calculate();
    };

} /* namespace itr_math */
#endif /* CALCULATE_H_ */
