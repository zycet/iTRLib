#include "nearestneighbor.h"
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
namespace itr_algorithm
{
    void NearestNeighbor::Train(Vector X,bool Class)
    {
        (Class)?pos.push_back(X):neg.push_back(X);
    }

    NearestNeighbor::NearestNeighbor()
    {
        oper=NULL;
    }

    NearestNeighbor::NearestNeighbor(Operator *Oper)
    {
        Init(oper);
    }
    void NearestNeighbor::Init(Operator *Oper)
    {
        oper=Oper;
    }

    S32 NearestNeighbor::Classify(Vector X)
    {
        float dis,min1=9999999,min2=9999999;

        if(oper==NULL)
        return -1;
        std::vector<Vector>::iterator i;
        for (i = pos.begin(); i != pos.end(); i++)
        {
            dis = oper->GetDis(*i,X);
            if(min1>dis)
            min1=dis;
        }

        for (i = neg.begin(); i != neg.end(); i++)
        {
            dis = oper->GetDis(*i,X);
            if(min2>dis)
            min2=dis;
        }
        return (min1>min2)?1:0;
   }
}
