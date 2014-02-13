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

    void fb_filter();
    void ncc_filter(const Matrix  &input1,const Matrix  &input2);
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
    vector<CommFeaturePoint> flU;
    vector<CommFeaturePoint> flV;
    vector<CommFeaturePoint> flU2;
    DataOper oper;
    Ransac ransac;
    ConvoluteSquare conv;

    F32 *x,*y,*dist;
    LKTracker tracker;
};

#endif // LKTRACKING_H
