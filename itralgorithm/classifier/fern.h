#ifndef FERN_H
#define FERN_H
#include"itrbase.h"
#include<vector>
using std::vector;
class Fern
{
    public:
        /** Default constructor */
        Fern();
        /** Default destructor */
        virtual ~Fern();
        Fern(S32 NFeat,S32 NComp,S32 Range);
        void Init(S32 NFeat,S32 NComp,S32 Range);
        F32 Classify(S32 *X);
        void Train(const itr_math::Matrix &img,bool flag);
    protected:
    private:
        void update(const vector<S32> &X,bool flag);

        vector< vector<S32> > comp;
        vector<S32> X;
        vector< vector<S32> > pos;
        vector< vector<S32> > neg;
        vector< vector<F32> > post;
        int ncomp;
        int nfeat;


};

#endif // FERN_H
