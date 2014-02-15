#include "cameraextercalc.h"

namespace itr_vision
{
    CameraExterCalc::CameraExterCalc()
    {
        //ctor
    }

    CameraExterCalc::~CameraExterCalc()
    {
        //dtor
    }

    CameraExterCalc::CameraExterCalc(const CameraExterCalc &other)
    {
        //copy ctor
        this->H=other.H;
        this->V=other.V;
        this->R=other.R;
        this->T=other.T;
        this->N=other.N;
    }
    /**
            * \brief 使用两组特征点通过RANSAC计算单应性矩阵(H,V)
            */
    BOOL CameraExterCalc::CalcHV(VectorFeaturePoint *PointList1,S32 List1Num,VectorFeaturePoint *PointList2,S32 List2Num)
    {
        S32 bucket_counter[16]={0};
        S32 bucket[16];
        F32 tempvalue_u[List1Num],tempvalue_v[List1Num];
        S32 matched_num=0;
        for(S32 i=0; i<List1Num; i++)
        {
            if(PointList1[i].ID!=-1)
            {
                matched_num++;
                tempvalue_u[i]=PointList1[i].X;
                tempvalue_v[i]=PointList1[i].Y;
            }
        }
        F32 U,V;
        Calculate CalculateObj;
        CalculateObj.Max(tempvalue_u,List1Num,U);
        CalculateObj.Max(tempvalue_v,List1Num,V);

        for(S32 i=0; i<List1Num; i++)
        {
            if(PointList1[i].ID!=-1)
            {
                if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=V/4)
                {
                    bucket_counter[0]++;
                    bucket[0]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=V/2)
                {
                    bucket_counter[1]++;
                    bucket[1]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=3*V/4)
                {
                    bucket_counter[2]++;
                    bucket[2]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/4)
                {
                    bucket_counter[3]++;
                    bucket[3]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=V/4)
                {
                    bucket_counter[4]++;
                    bucket[4]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=V/2)
                {
                    bucket_counter[5]++;
                    bucket[5]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=3*V/4)
                {
                    bucket_counter[6]++;
                    bucket[6]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=U/2)
                {
                    bucket_counter[7]++;
                    bucket[7]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=V/4)
                {
                    bucket_counter[8]++;
                    bucket[8]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=V/2)
                {
                    bucket_counter[9]++;
                    bucket[9]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=3*V/4)
                {
                    bucket_counter[10]++;
                    bucket[10]=i;
                    continue;
                }
                else
                if(tempvalue_u[i]<=3*U/4)
                {
                    bucket_counter[11]++;
                    bucket[11]=i;
                    continue;
                }
                else
                if(tempvalue_v[i]<=V/4)
                {
                    bucket_counter[12]++;
                    bucket[12]=i;
                    continue;
                }
                else
                if(tempvalue_v[i]<=V/2)
                {
                    bucket_counter[13]++;
                    bucket[13]=i;
                    continue;
                }
                else
                if(tempvalue_v[i]<=3*V/4)
                {
                    bucket_counter[14]++;
                    bucket[14]=i;
                    continue;
                }
                else
                {
                    bucket_counter[15]++;
                    bucket[15]=i;
                    continue;
                }
            }
        }
        F32 ratio[16]={0};
        ratio[0]=bucket_counter[0]/matched_num;
        for(S32 i=1; i<16; i++)
        {
            ratio[i]=ratio[i-1] + bucket_counter[i]/matched_num;
        }
    }
            /**
            * \brief 通过给定的相机内参数和深度参数D计算运动参数(R,T,N)
            * \param CameraInterPara 相机内参数
            * \param D 深度(单位:米)
            * \note 此计算步骤需已完成单应性矩阵计算(既已成功调用CalcHV())
            */
    BOOL CalcMotion(CameraInterCalc &CameraInterPara,F32 D);
}
