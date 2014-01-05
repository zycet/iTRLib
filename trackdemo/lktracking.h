#ifndef LKTRACKING_H
#define LKTRACKING_H

#include "itrbase.h"
#include "itralgorithm.h"
#include "itrvision.h"
#include "algorithm"
using namespace itr_algorithm;
using namespace itr_vision;
using itr_math::Matrix;

class lktracking
{
    public:
        /** Default constructor */
        lktracking();
        void Init(const Matrix &current,RectangleS &rect);
        bool Go(const Matrix &current,RectangleS &rect,F32 &u,F32 &v);
        /** Default destructor */
        virtual ~lktracking();
        S32 debugcount;
    protected:
    private:


class DataOper:public Ransac::Operator
{
    public:
        F32 GetError(F32 a, F32 b)
        {
            return fabs(a-b);
        }
        F32 GetValue(F32 *data, S32 N)
        {
            std::sort(data,data+N);
            return data[N/2];
        }
        bool Remain(F32 error)
        {
            return (fabs(error)<1.5);
        }
};
    S32 FeatureNum;
    vector<FeaturePoint> flU;
    vector<FeaturePoint> flV;
    vector<FeaturePoint> flU2;
    DataOper oper;
    Ransac ransac;
    ConvoluteSquare conv;

    F32 *x,*y;
    LKTracker tracker;
};

#endif // LKTRACKING_H
