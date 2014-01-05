#ifndef RANSAC_H
#define RANSAC_H

#include "itrbase.h"
namespace itr_algorithm
{
    class Ransac
    {
        public:
            /** Default constructor */
            class Operator
            {
                public:
                    virtual F32 GetError(F32 a, F32 b)=0;
                    virtual F32 GetValue(F32 *data, S32 N)=0;
                    virtual bool Remain(F32 error)=0;
            };
            Ransac();
            Ransac(Ransac::Operator *oper);
            void Init(Ransac::Operator *oper);
            void Process(S32 count, F32 *x, S32 &drop);
            Ransac::Operator *oper;
            static const S32 INF = 9999999;

        private:
            F32 *data;
            F32 *result;
            F32 *error;
            S32 M,N;
    };


}
#endif // RANSAC_H
