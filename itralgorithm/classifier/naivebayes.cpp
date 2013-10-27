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
 * naivebayes.cpp
 *  Created on: 2013-10-18
 *      Author: ghdawn
 */

#include "naivebayes.h"
#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
namespace itr_algorithm
{
    NaiveBayes::NaiveBayes(const vector<Domain>& domain):_domain(domain)
    {
//        this->_domain = domain;
        m = n = 0;
        pTrue = new int*[domain.size()];

        for (int i = 0; i < domain.size(); ++i)
        {
            pTrue[i] = new int[domain[i].count];
        }
        pFalse = new int*[domain.size()];
        for (int i = 0; i < domain.size(); ++i)
        {
            pFalse[i] = new int[domain[i].count];
        }
    }

    NaiveBayes::~NaiveBayes()
    {
        // TODO Auto-generated destructor stub
    }
    void itr_algorithm::NaiveBayes::Train(vector<TrainingData>& Data, bool Flag)
    {
        if (Flag)
        {
            for (int i = 0; i < Data.size(); ++i)
            {
                F32 *p = (Data[i]).GetData();
                S32 dim = Data[i].GetDim();
                for (int j = 0; j < dim; ++j)
                {
                    pTrue[j][(_domain[j].Calc(*p))]++;
                    ++p;
                }
            }
            m = Data.size();
        }
        else
        {
            for (int i = 0; i < Data.size(); ++i)
            {
                F32 *p = (Data[i]).GetData();
                S32 dim = Data[i].GetDim();
                for (int j = 0; j < dim; ++j)
                {
                    pFalse[j][(_domain[j].Calc(*p))]++;
                    ++p;
                }
            }
            n = Data.size();
        }
    }

    S32 NaiveBayes::Classify(S32* Data, S32 length)
    {
        float rTrue = 1, rFalse = 1;
        for (int i = 0; i < length; ++i)
        {
            rTrue *= (pTrue[i][(_domain[i].Calc(Data[i]))] + 1) / (float) (m + _domain[i].count);
            rFalse *= (pFalse[i][(_domain[i].Calc(Data[i]))] + 1) / (float) (m + _domain[i].count);
        }
        if (rTrue > rFalse)
            return 1;
        else
            return 0;
    }

} // namespace itr_algorithm

