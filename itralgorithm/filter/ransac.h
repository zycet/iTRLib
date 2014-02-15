#ifndef RANSAC_H
#define RANSAC_H

#include "itrbase.h"
namespace itr_algorithm
{
    template <class InputType,class ResultType>
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
                    virtual F32 GetError(InputType a, ResultType b)=0;
                    virtual ResultType GetValue(InputType *data, S32 N)=0;
                    virtual bool Remain(InputType a, ResultType b)=0;
            };

            Ransac();
            /**
            * \brief 初始化
            * \param 计算时需要用到的算子
            */
            Ransac(Ransac<InputType,ResultType>::Operator *oper);
            void Init(Ransac<InputType,ResultType>::Operator *oper);

            /**
            * \brief 执行随机一致性检测
            * \param 待检测的对象数组
            * \param 传入对象长度
            * \param 输出用，被过滤掉的对象个数
            */
            ResultType Process( InputType *x, S32 N,S32 &drop);

            static const S32 INF = 9999999;
            S32 Times,Number;

        private:
            InputType *data;
            ResultType *result;
            F32 *error;
            Ransac<InputType,ResultType>::Operator *oper;

    };

    template <class InputType,class ResultType>
    Ransac<InputType,ResultType>::Ransac()
    {
        //ctor
        Times=7;
        Number=1;
    }
    template <class InputType,class ResultType>
    Ransac<InputType,ResultType>::Ransac(Ransac<InputType,ResultType>::Operator *Oper)
    {
        oper=Oper;
    }
    template <class InputType,class ResultType>
    void Ransac<InputType,ResultType>::Init(Ransac<InputType,ResultType>::Operator *Oper)
    {
        oper=Oper;
    }

    template <class InputType,class ResultType>
    ResultType Ransac<InputType,ResultType>::Process(InputType *x, S32 count, S32 &drop)
    {

        data = new InputType[Number];
        result = new ResultType[Times];
        error = new F32[Times];
        ResultType key;
        int index;
        for (int i = 0; i < Times; i++)
        {
            //随机抽取N个数据
            for (int j = 0; j < Number; j++)
            {
                itr_math::NumericalObj->Rand(0, count, index);
                data[j] = x[index];
            }

            result[i] =oper->GetValue(data,Number);
            error[i]=0;
            for (int j = 0; j < count; ++j)
            {
                error[i] += oper->GetError(x[j] , result[i]); //*(x[j]-result[i]);
            }
        }
        index = 0;
        key = error[0];
        for (int i = 1; i < Times; i++)
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
            if (!oper->Remain(x[i] , key))
            {
                x[i] = INF;
                ++drop;
            }
        }
//        cout << endl;
        delete[] error;
        delete[] data;
        delete[] result;
        return key;
    }

}
#endif // RANSAC_H
