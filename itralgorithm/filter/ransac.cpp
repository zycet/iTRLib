#include "ransac.h"

namespace itr_algorithm
{
    Ransac::Ransac()
    {
        //ctor
        M=7;
        N=1;
    }
    Ransac::Ransac(Ransac::Operator *Oper)
    {
        oper=Oper;
    }
    void Ransac::Init(Ransac::Operator* Oper)
    {
        oper=Oper;
    }
    void Ransac::Process(S32 count, F32 *x, S32 &drop)
    {

        N = count / M;
        if (N < 1)
        {
            N = 1;
        }
        data = new F32[N];
        result = new F32[M];
        error = new F32[M];
        int index, key;
        for (int i = 0; i < M; i++)
        {
            //随机抽取N个数据
            for (int j = 0; j < N; j++)
            {
                itr_math::NumericalObj->Rand(0, count, index);
                data[j] = x[index];
            }

            result[i] =oper->GetValue(data,N);
            error[i]=0;
            for (int j = 0; j < count; ++j)
            {
                error[i] += oper->GetError(x[j] , result[i]); //*(x[j]-result[i]);
            }
        }
        index = 0;
        key = error[0];
        for (int i = 1; i < M; i++)
        {
            if (key > error[i])
            {
                key = error[i];
                index = i;
            }
        }
        key = result[index];
        drop = 0;
//        printf("error: ");
        for (int i = 0; i < count; ++i)
        {
//            printf("%0.0f ", fabs(x[i] - key));
            if (!oper->Remain(x[i] - key))
            {
                x[i] = INF;
                ++drop;
            }
        }
//        cout << endl;
        delete[] error;
        delete[] data;
        delete[] result;
    }

}
