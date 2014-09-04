#include "nearestneighbor.h"
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
namespace itr_algorithm
{
    void NearestNeighbor::Train(Vector &X,bool Class)
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

    void NearestNeighbor::Classify(Vector &X,F32 &min1,F32 &min2)
    {
        float dis;
        min1=9999999,min2=9999999;

        if(oper==NULL)
        return ;
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
   }

   F32  NearestNeighbor::Classify(Vector &X)
   {
        F32 dis1,dis2;
        Classify(X,dis1,dis2);
        return dis1<dis2?dis1:-dis2;
   }
}
