#ifndef NEARESTNRIGHBOR_H_
#define NEARESTNRIGHBOR_H_

#include "itrbase.h"
#include <iostream>
#include "./classifier.h"

#include <vector>

using itr_math::Vector;
namespace itr_algorithm
{

    class NearestNeighbor
    {
        public:
        class Operator
        {
        public:
           virtual F32 GetDis(Vector& v1,Vector& v2)=0;
        };

        F32 Classify(Vector &X);
        void Classify(Vector &X,F32 &dis1,F32 &dis2);
        void Train(Vector &X,bool Class);

        NearestNeighbor();
        NearestNeighbor(Operator *oper);
        void Init(Operator *oper);
        std::vector<Vector> pos,neg;
        private:
        Operator *oper;
    };

}
#endif
