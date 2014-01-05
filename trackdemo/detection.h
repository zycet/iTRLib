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
        bool Go(const Matrix &current,const RectangleS &rect,F32 &x,F32 &y);
    protected:
    private:
    void Train(const Matrix &current,RectangleS &rect);
    S32 Num;
    Matrix patch;
    S32 FeatureNum;
    Matrix dataPos,dataNeg,sample;
    NaiveBayes nbc;
    ConvoluteSquare conv;
};

#endif // DETECCTION_H
