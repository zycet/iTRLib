#ifndef PARTICLEFILTER_H
#define PARTICLEFILTER_H
#include "itrbase.h"
using itr_math::Vector;
using itr_math::Matrix;
class ParticleFilter
{
    public:
        /** Default constructor */
        ParticleFilter();
        /** Default destructor */
        virtual ~ParticleFilter();

        void Init(int ParticleNum,const Vector &x);
        void UpdateModel();
        void UpdateMeasure(const Matrix& H,const Matrix& R,const Vector &z);
        void GetState(Vector &x);
        Matrix F_x;
    protected:
    private:


        void Selection();
        class Particle
        {
            public:
                Vector state;
                float weight;
                float weightsum;
        };
        Particle *particles;
        S32 particleNum;

};

#endif // PARTICLEFILTER_H
