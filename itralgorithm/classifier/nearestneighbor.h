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
           virtual F32 GetDis(const Vector& v1,const Vector& v2)=0;
        };

        S32 Classify(Vector X);
        void Train(Vector X,bool Class);

        NearestNeighbor();
        NearestNeighbor(Operator *oper);
        void Init(Operator *oper);
        private:
        std::vector<Vector> pos,neg;
        Operator *oper;
    };

}
#endif
