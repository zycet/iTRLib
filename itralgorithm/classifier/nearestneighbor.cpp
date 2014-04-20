#include "nearestneighbor.h"
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
namespace itr_algorithm
{
    void itr_algorithm::NearestNeighbor::Classify(vector<Vector> vectorlist1,vector<Vector> vectorlist2, Vector VectorEx,int featurenum)
    {
        int length1;
        int length2;
        float min1;
        float min2;
        int i;
        length1 = vectorlist1.size();
        length2 = vectorlist2.size();
        float *data1 = new float[length1];
        float *data2 = new float[length2];

        for (i = 0; i < length1; i++)
        {
            data1[i] = (vectorlist1[i]).ProductInner(VectorEx);

        }
        itr_math::StatisticsObj->Min(data1,length1,min1);
        for (i = 0; i < length2; i++)
        {
            data2[i] = (vectorlist2[i]).ProductInner(VectorEx);
        }
        itr_math::StatisticsObj->Min(data2,length2,min2);
        if(min1<min2)
        {
            featurenum = 1;
        }
        else
        {
            featurenum = 2;
        }

    }
}
