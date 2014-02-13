#ifndef RANSAC_H
#define RANSAC_H

#include "itrbase.h"
namespace itr_algorithm
{
    template <class T>
    class Ransac
    {
        public:
            /**
            * \brief 为RANSAC的过程提供计算方法的算子类
            * 提供了计算一致性时需要的方法，例如判断两个对象之间的误差，对应误差是否保留等功能
            */
            class Operator
            {
                public:
                    virtual F32 GetError(T a, T b)=0;
                    virtual T GetValue(T *data, S32 N)=0;
                    virtual bool Remain(F32 error)=0;
            };

            Ransac();
            /**
            * \brief 初始化
            * \param 计算时需要用到的算子
            */
            Ransac(Ransac<T>::Operator *oper);
            void Init(Ransac<T>::Operator *oper);

            /**
            * \brief 执行随机一致性检测
            * \param 待检测的对象数组
            * \param 传入对象长度
            * \param 输出用，被过滤掉的对象个数
            */
            void Process( T *x, S32 N,S32 &drop);

            static const S32 INF = 9999999;

        private:
            T *data;
            T *result;
            F32 *error;
            Ransac<T>::Operator *oper;
            S32 M,N;
    };

    template <class T>
    Ransac<T>::Ransac()
    {
        //ctor
        M=7;
        N=1;
    }
    template <class T>
    Ransac<T>::Ransac(Ransac<T>::Operator *Oper)
    {
        oper=Oper;
    }
    template <class T>
    void Ransac<T>::Init(Ransac<T>::Operator *Oper)
    {
        oper=Oper;
    }

    template <class T>
    void Ransac<T>::Process(T *x, S32 count, S32 &drop)
    {

        N = count / M;
        if (N < 1)
        {
            N = 1;
        }
        data = new T[N];
        result = new T[M];
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
#endif // RANSAC_H
