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
#include <vector>
using std::vector;
using std::ofstream;
using namespace itr_math;
using namespace itr_algorithm;
void NBCtest()
{
    FILE* fin = fopen("Debug/data", "r");
    int n, m;
    fscanf(fin, "%d %d", &m, &n);
    vector<TrainingData> data(m, 2);
    float temp[3];
    for (int i = 0; i < m; ++i)
    {
        fscanf(fin, "%f %f %f", temp, temp + 1, temp + 2);
        data[i].SetData(temp, 1);
    }
    vector<Domain> domain(2);
    domain[0].Init(1, 2, 2);
    domain[1].Init(-3, 3, 7);
    NaiveBayes nb(domain);
    nb.Train(data, true);
    for (int i = 0; i < m; ++i)
    {
        fscanf(fin, "%f %f %f", temp, temp + 1, temp + 2);
        data[i].SetData(temp, 1);
    }
    nb.Train(data,false);
    int test[3]={1,-1,1};
    printf("%d\n",nb.Classify(test,2));
}
