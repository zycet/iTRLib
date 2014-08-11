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
 * naivebayes.h
 *  Created on: 2013-10-18
 *      Author: ghdawn
 */

#ifndef NAIVEBAYES_H_
#define NAIVEBAYES_H_

#include "itrbase.h"
#include "./classifier.h"

#include <vector>
using std::vector;
using itr_math::Matrix;
namespace itr_algorithm
{

    class GaussianNaiveBayes
    {
        public:
            GaussianNaiveBayes();
            GaussianNaiveBayes(S32 featureNum);
            void Init(S32 FeatureNum);
            void TrainPos(const Matrix &input);
            void TrainNeg(const Matrix &input);
            F32 Classify(F32 *Data);
            float LearnRate;
            virtual ~GaussianNaiveBayes();
        private:
            bool initpos,initneg;
            int featureNum;
            float *muPos,*muNeg;
            float *sigmaPos,*sigmaNeg;
            static const F32 INFMIN=1e-20;
    };

} // namespace itr_algorithm
#endif // NAIVEBAYES_H_
