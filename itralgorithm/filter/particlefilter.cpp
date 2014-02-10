#include "particlefilter.h"
#include <math.h>
using namespace itr_math;
ParticleFilter::ParticleFilter()
{
    //ctor
}

ParticleFilter::~ParticleFilter()
{
    //dtor
}

void ParticleFilter::Init(int ParticleNum,const Vector &x)
{
    particles=new Particle[ParticleNum];
    int i,j,dim=x.GetDim();
    F32 noise;
    for(i=0; i<ParticleNum; ++i)
    {
        particles[i].state.Init(dim);
        for(j=0;j<dim;++j)
        {
            NumericalObj->RandGaussian(noise);
            particles[i].state[j]=x[j]+noise;
        }
        particles[i].weight=1.0f/ParticleNum;
    }

    F_x.Init(dim);
    F_x.SetDiag(1);
    particleNum=ParticleNum;
}
void ParticleFilter::UpdateModel()
{
    for(int i=0; i<particleNum; ++i)
    {
        particles[i].state=F_x*particles[i].state;
    }
}

void ParticleFilter::UpdateMeasure(const Matrix& H,const Matrix& R,const Vector &z)
{
    F32 mu;
    F32 sum=0;
    int i;
    Vector temp(z.GetDim());
    Matrix Rinv(R);
    R.Inv(Rinv);
    for(i=0; i<particleNum; ++i)
    {
        temp=z-H*particles[i].state;
        mu=temp*(Rinv*temp);
        particles[i].weight=exp(-mu/(6.28));
        sum+=particles[i].weight;
    }
    sum=1.0/sum;
    for(i=0; i<particleNum; ++i)
    {
        particles[i].weight*=sum;
    }

}
void ParticleFilter::GetState(Vector &x)
{
    int i;
    x.Zero();
    for(i=0;i<particleNum;++i)
        x=x+particles[i].state*particles[i].weight;

}
void ParticleFilter::Selection()
{
    particles[0].weightsum=particles[0].weight;
    for(int i=1; i<particleNum; ++i)
    {
        particles[i].weightsum=particles[i].weight+particles[i-1].weightsum;
    }
}
