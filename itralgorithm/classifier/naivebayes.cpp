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
    /*
     * 输入矩阵的每一行是一组数据
     * 所以
     * 有多少特征就有多少列，
     * 有多少组数据就有多少行。
     */

    itr_algorithm::NaiveBayes::NaiveBayes(int FeatureNum)
    {
        featureNum = FeatureNum;
        muPos = new F32[FeatureNum]();
        muNeg = new F32[FeatureNum]();
        sigmaPos = new F32[FeatureNum]();
        sigmaNeg = new F32[FeatureNum]();
        LearnRate = 0.8f;
        initpos = false;
        initneg = false;
    }

    void itr_algorithm::NaiveBayes::TrainPos(const Matrix& input)
    {
        int length = input.GetRow();
        F32* data = new F32[length];
        F32 mu, sigma;

        if (!initpos)
        {
            for (int i = 0; i < featureNum; i++)
            {
                input.CopyColTo(i, data);
                itr_math::StatisticsObj->Mean(data, length, muPos[i]);
                itr_math::StatisticsObj->Variance(data, length, sigmaPos[i]);
            }
            initpos = true;
        }
        else
        {
            for (int i = 0; i < featureNum; i++)
            {
                input.CopyColTo(i, data);
                itr_math::StatisticsObj->Mean(data, length, mu);
                itr_math::StatisticsObj->Variance(data, length, sigma);

                itr_math::NumericalObj->Sqrt(
                        LearnRate * sigmaPos[i] * sigmaPos[i] + (1 - LearnRate) * sigma * sigma
                                + LearnRate * (1 - LearnRate) * (mu - muPos[i]) * (mu - muPos[i]),
                        sigmaPos[i]);
                muPos[i] = LearnRate * muPos[i] + (1 - LearnRate) * mu;
            }

        }
    }

    void itr_algorithm::NaiveBayes::TrainNeg(const Matrix& input)
    {
        int length = input.GetRow();
        F32* data = new F32[length];
        F32 mu, sigma;

        if (!initneg)
        {
            for (int i = 0; i < featureNum; i++)
            {
                input.CopyColTo(i, data);
                itr_math::StatisticsObj->Mean(data, length, muNeg[i]);
                itr_math::StatisticsObj->Variance(data, length, sigmaNeg[i]);
            }
            initneg = true;
        }
        else
        {
            for (int i = 0; i < featureNum; i++)
            {
                input.CopyColTo(i, data);
                itr_math::StatisticsObj->Mean(data, length, mu);
                itr_math::StatisticsObj->Variance(data, length, sigma);

                itr_math::NumericalObj->Sqrt(
                        LearnRate * sigmaNeg[i] * sigmaNeg[i] + (1 - LearnRate) * sigma * sigma
                                + LearnRate * (1 - LearnRate) * (mu - sigmaNeg[i])
                                        * (mu - sigmaNeg[i]), sigmaNeg[i]);
                muNeg[i] = LearnRate * muNeg[i] + (1 - LearnRate) * mu;
            }

        }
    }

    F32 itr_algorithm::NaiveBayes::Classify(F32* Data)
    {
        F32 result = 0;
        F32 p, n;
        for (int i = 0; i < featureNum; ++i)
        {
            p = itr_math::GaussianGenerate::PDF(muPos[i], sigmaPos[i], Data[i]);
            n = itr_math::GaussianGenerate::PDF(muNeg[i], sigmaNeg[i], Data[i]);
            itr_math::NumericalObj->Log(p + INFMIN, p);
            itr_math::NumericalObj->Log(n + INFMIN, n);
            result += (p - n);
        }
        return result;
    }

    itr_algorithm::NaiveBayes::~NaiveBayes()
    {
        delete[] muPos;
        delete[] muNeg;
        delete[] sigmaPos;
        delete[] sigmaNeg;
    }

} // namespace itr_algorithm

