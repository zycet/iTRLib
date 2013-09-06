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
            Calculate();
            virtual ~Calculate();
    };

} /* namespace itr_math */
#endif /* CALCULATE_H_ */
