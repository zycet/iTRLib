#include "fern.h"
#include <math.h>
Fern::Fern()
{

}

Fern::Fern(S32 NFeat,S32 NComp,S32 Range)
{
    Init(NFeat, NComp, Range);
}

void Fern::Init(S32 NFeat,S32 NComp,S32 Range)
{
    nfeat=NFeat;
    ncomp=NComp;
    for (int i = 0; i<nfeat; i++)
    {
        post.push_back(vector<F32>(pow(2.0,ncomp), 0));
        pos.push_back(vector<int>(pow(2.0,ncomp), 0));
        neg.push_back(vector<int>(pow(2.0,ncomp), 0));
        comp.push_back(vector<int>(2*ncomp,0));
        X.push_back(0);
    }
      for(int j=0; j<nfeat; j++)
        for(int i=0; i<ncomp; i++)
        {
            itr_math::NumericalObj->Rand(0,Range,comp[j][2*i]);
            itr_math::NumericalObj->Rand(0,Range,comp[j][2*i+1]);
        }

}
Fern::~Fern()
{
    //dtor
}

void Fern::update(const vector<S32> &X,bool flag)
{
    int x;
    for(int i=0; i<nfeat; i++)
    {
        x=X[i];
        (flag)?pos[i][x]++:neg[i][x]++;
        post[i][x]=(pos[i][x]>0)?(F32)pos[i][x]/(pos[i][x]+neg[i][x]):0;
    }
}

F32 Fern::Classify(int *X)
{
    F32 vote=0;
    for(int i=0; i<nfeat; i++)
    {
        vote+=post[i][X[i]];
    }
    return vote/nfeat;
}

void Fern::Train(const itr_math::Matrix &img,bool flag)
{
    for(int j=0; j<nfeat; j++)
    {
        X[j]=0;
        for(int i=0; i<ncomp; i++)
        {
            X[j]<<=1;
            if(img[comp[j][2*i]]<img[comp[j][2*i+1]])
            {
                X[j]++;
            }
        }
    }
    update(X,flag);
}
