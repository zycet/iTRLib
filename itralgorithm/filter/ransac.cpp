#include "ransac.h"

namespace itr_algorithm
{
    Ransac::Ransac()
    {
        //ctor
        M=7;
        N=1;
    }
    void Ransac::Process(S32 count, F32 *x, S32 &drop)
    {
        S32 INF = 9999999;
        S32 M = 7;
        S32 N = count / M;
        if (N < 1)
        {
            N = 1;
        }
        F32 *data = new F32[N];
        F32 *result = new F32[M];
        F32 *error = new F32[M];
        int index, key;
        for (int i = 0; i < M; i++)
        {
            //随机抽取N个数据
            for (int j = 0; j < N; j++)
            {
                itr_math::NumericalObj->Rand(0, count, index);
                data[j] = x[index];
            }
            std::sort(data, data + N);
            result[i] = data[N / 2];
            for (int j = 0; j < count; ++j)
            {
                error[i] += fabs(x[j] - result[i]); //*(x[j]-result[i]);
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
        printf("error: ");
        for (int i = 0; i < count; ++i)
        {
            printf("%0.0f ", fabs(x[i] - key));
            if (fabs(x[i] - key) >= 1.5)
            {
                x[i] = INF;
                ++drop;
            }
        }
        cout << endl;
        delete[] error;
        delete[] data;
        delete[] result;
    }

}
