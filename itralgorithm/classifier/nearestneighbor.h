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
        void Classify(std::vector<Vector> vectorlist1,std::vector<Vector> vectorlist2, Vector VectorEx,int featurenum);

        private:


    };

}
#endif
