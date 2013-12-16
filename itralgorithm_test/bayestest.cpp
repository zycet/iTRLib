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
 * bayestest.cpp
 *  Created on: 2013-10-22
 *      Author: ghdawn
 */

#include "bayestest.h"
#include "itrbase.h"
#include "itralgorithm.h"
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
using std::vector;
using std::ofstream;
using namespace itr_math;
using namespace itr_algorithm;

void printMatrix(Matrix &a)
{
    for (int i = 0; i < a.GetRow(); ++i)
    {
        for (int j = 0; j < a.GetCol(); ++j)
        {
            printf("%f ", a(i, j));
        }
        printf("\n");
    }
    printf("\n");
}


void NBCtest()
{
printf("*****Begin Naive Bayes Classifier Test!*****\n\n");
    itr_math::MathObjStandInit();
    FILE *fin = fopen("Debug/data", "r");
    int FeatureNum, n, m;
    fscanf(fin, "%d %d %d", &FeatureNum, &m, &n);
    Matrix dataPos(m, FeatureNum), dataNeg(n, FeatureNum);
    float temp[2];
    for (int i = 0; i < m; ++i)
    {
        fscanf(fin, "%f %f", temp, temp + 1);
//        printf("%f %f\n",temp[0],temp[1]);
        dataPos.CopyRowFrom(i+1, temp);
    }
    for (int i = 0; i < n; ++i)
    {
        fscanf(fin, "%f %f", temp, temp + 1);
//        printf("%f %f\n",temp[0],temp[1]);
        dataNeg.CopyRowFrom(i+1, temp);
    }
    printMatrix(dataPos);
    printMatrix(dataNeg);
    NaiveBayes nb(FeatureNum);
    nb.TrainPos(dataPos);
    nb.TrainNeg(dataNeg);

    F32 test[3] =
    { -0.5, 2, 1 };
    printf("%f\n", nb.Classify(test));
    printf("*****End Naive Bayes Classifier Test!*****\n\n");
}

