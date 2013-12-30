#ifndef DETECTION_H
#define DETECTION_H

#include "itrbase.h"
#include "itralgorithm.h"
#include "itrvision.h"
using namespace itr_algorithm;
using namespace itr_vision;
using itr_math::Matrix;

class Detection
{
    public:
        /** Default constructor */
        Detection(const Matrix &current,RectangleS &rect,S32 num);
        void Go(const Matrix &current,RectangleS &rect,F32 &x,F32 &y);
    protected:
    private:
    S32 Num;
    Matrix patch;
    S32 FeatureNum;
    Matrix dataPos,dataNeg,sample;
    NaiveBayes nbc;
    ConvoluteSquare conv;
};

#endif // DETECCTION_H
