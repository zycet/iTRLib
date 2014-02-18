#include "cameraextercalc.h"
#define resid_MAX_2 64
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
            * \brief 使用两组特征点通过RANSAC计算单应性矩阵(H)
            */
    BOOL CameraExterCalc::CalcH(VectorFeaturePoint *PointList1,S32 List1Num,VectorFeaturePoint *PointList2,S32 List2Num)
    {
        Calculate CalculateObj;
        Numerical NumericalObj;
        //筛选最优 H 时所用
        Matrix best_H(3,3);
        Vector pos_2s(3),pos_1(3);
        F32 red_counter=0,tmp_red=0,best_counter=0, best_red=0;
        F32 risde;
        //bucketing
        S32 List1Num_q;
        NumericalObj.Round(List1Num/4,List1Num_q);
        S32 bucket_counter[16]={0};
        S32 bucket[16][List1Num_q];
        //
        F32 tempvalue_u[List1Num],tempvalue_v[List1Num];
        S32 tempID[List1Num];
        S32 matched_num=0;
        for(S32 i=0; i<List1Num; i++)
        {
            if(PointList1[i].ID!=-1)
            {
                tempID[matched_num]=i;
                tempvalue_u[matched_num]=PointList1[i].X;
                tempvalue_v[matched_num]=PointList1[i].Y;
                matched_num++;
            }
        }
        F32 U,V;
        CalculateObj.Max(tempvalue_u,matched_num,U);
        CalculateObj.Max(tempvalue_v,matched_num,V);

        for(S32 i=0; i<matched_num; i++)
        {
            if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=V/4)
            {
                bucket_counter[0]++;
                bucket[0][bucket_counter[0]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=V/2)
            {
                bucket_counter[1]++;
                bucket[1][bucket_counter[1]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/4&&tempvalue_v[i]<=3*V/4)
            {
                bucket_counter[2]++;
                bucket[2][bucket_counter[2]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/4)
            {
                bucket_counter[3]++;
                bucket[3][bucket_counter[3]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=V/4)
            {
                bucket_counter[4]++;
                bucket[4][bucket_counter[4]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=V/2)
            {
                bucket_counter[5]++;
                bucket[5][bucket_counter[5]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/2&&tempvalue_v[i]<=3*V/4)
            {
                bucket_counter[6]++;
                bucket[6][bucket_counter[6]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=U/2)
            {
                bucket_counter[7]++;
                bucket[7][bucket_counter[7]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=V/4)
            {
                bucket_counter[8]++;
                bucket[8][bucket_counter[8]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=V/2)
            {
                bucket_counter[9]++;
                bucket[9][bucket_counter[9]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=3*U/4&&tempvalue_v[i]<=3*V/4)
            {
                bucket_counter[10]++;
                bucket[10][bucket_counter[10]]=i;
                continue;
            }
            else
            if(tempvalue_u[i]<=3*U/4)
            {
                bucket_counter[11]++;
                bucket[11][bucket_counter[11]]=i;
                continue;
            }
            else
            if(tempvalue_v[i]<=V/4)
            {
                bucket_counter[12]++;
                bucket[12][bucket_counter[12]]=i;
                continue;
            }
            else
            if(tempvalue_v[i]<=V/2)
            {
                bucket_counter[13]++;
                bucket[13][bucket_counter[13]]=i;
                continue;
            }
            else
            if(tempvalue_v[i]<=3*V/4)
            {
                bucket_counter[14]++;
                bucket[14][bucket_counter[14]]=i;
                continue;
            }
            else
            {
                bucket_counter[15]++;
                bucket[15][bucket_counter[15]]=i;
                continue;
            }
        }
        F32 ratio[16]={0};
        ratio[0]=bucket_counter[0]/matched_num;
        for(S32 i=1; i<16; i++)
        {
            ratio[i]=ratio[i-1] + bucket_counter[i]/matched_num;
        }
        //RANSAC,calculate H
        S16 b[4]={0};
        S32 c[4]={0};
        F32 p,wght,u1,v1,u2,v2;
        S32 q,tmp_k;
        for(S32 i=0; i<10; i++)
        {
            //pick 4 buckets
            for(S32 j=0; j<4; j++)
            {
                NumericalObj.Rand(p);
                for(S32 k=0; k<16; k++)
                {
                    if(k==0)
                    {
                        if(p<ratio[0])
                        {
                            q=1;
                            break;
                        }
                    }
                    else
                    {
                        if(ratio[k-1]<p&&ratio[k]>=p)
                        {
                            if(bucket_counter[k]>0)
                                q=k;
                            else
                            {
                                tmp_k =k;
                                while(bucket_counter[tmp_k]==0)
                                    tmp_k--;
                                q=tmp_k;
                            }
                            break;
                        }
                    }
                }
                if(j>0)
                {
                    for(S32 z=0; z<j; z++)
                    {
                        if(q==b[z])
                        {
                            NumericalObj.Rand(p);
                            for(S32 k=0; k<16; k++)
                            {
                                if(k==0)
                                {
                                    if(p<ratio[0])
                                    {
                                        q=1;
                                        break;
                                    }
                                }
                                else
                                {
                                    if(ratio[k-1]<p&&ratio[k]>=p)
                                    {
                                        if(bucket_counter[k]>0)
                                            q=k;
                                        else
                                        {
                                            tmp_k =k;
                                            while(bucket_counter[tmp_k]==0)
                                                tmp_k--;
                                            q=tmp_k;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                b[j]=q;
            }
            //pick 4 feature point
            for(S32 j=0; j<4; j++)
            {
                NumericalObj.Rand(p);
                NumericalObj.Ceil(p*bucket_counter[b[j]],q);
                c[j]=tempID[bucket[b[j]][q]];
            }
            //matrix
            Matrix M(8,9);
            M.Set(0);
            for(S32 j=0; j<4; j++)
            {
                u1 = PointList1[c[j]].X;
                v1 = PointList1[c[j]].Y;
                u2 = PointList2[PointList1[c[j]].ID].X;
                v2 = PointList2[PointList1[c[j]].ID].Y;
                wght = PointList2[PointList1[c[j]].ID].Quality;
                M(2*j,3)=-u1*wght;
                M(2*j,4)=-v1*wght;
                M(2*j,5)=-wght;
                M(2*j,6)=u1*v2*wght;
                M(2*j,7)=v1*v2*wght;
                M(2*j,8)=v2*wght;
                M(2*j+1,0)=-u1*wght;
                M(2*j+1,1)=-v1*wght;
                M(2*j+1,2)=-wght;
                M(2*j+1,6)=u1*u2*wght;
                M(2*j+1,7)=v1*u2*wght;
                M(2*j+1,8)=u2*wght;
            }
            //svd
            Matrix V(9,9);
            Vector S(9);
            M.Svdcmp(S,V);
            for(S32 j=0; j<3; j++)
                for(S32 k=0; k<3; k++)
                    H(j,k)=M(j*3+k,8);
            //參差量
            red_counter=0,tmp_red=0;
            for(S32 j=0; j<matched_num; j++)
            {
                pos_1[0]=tempvalue_u[j];
                pos_1[1]=tempvalue_v[j];
                pos_1[2]=1;
                pos_2s=H*pos_1;
                pos_2s[0]/=pos_2s[2];
                pos_2s[1]/=pos_2s[2];
                pos_2s[0]-=PointList2[PointList1[tempID[j]].ID].X;
                pos_2s[1]-=PointList2[PointList1[tempID[j]].ID].Y;
                CalculateObj.MultiSum(pos_2s.GetData(),pos_2s.GetData(),2,risde);

                if(j==c[0]||j==c[1]||j==c[2]||j==c[4])
                    risde=0;
                if(risde<resid_MAX_2)   //与王论文相比 risde 未开方
                    red_counter++;
                tmp_red+=risde;
            }
            if(i==0)
            {
                best_H=H;
                best_counter=red_counter;
                best_red=tmp_red;
            }
            else
            {
                if((red_counter>best_counter)||((red_counter==best_red)&&(tmp_red<best_red)))
                {
                    best_red = tmp_red;
                    best_counter = red_counter;
                    best_H = H;
                }
            }
        }//end of RANSAC
        H=best_H;
        return true;
    }
            /**
            * \brief 通过给定的相机内参数和深度参数D计算运动参数(R,T,N)
            * \param CameraInterPara 相机内参数
            * \param D 深度(单位:米)
            * \note 此计算步骤需已完成单应性矩阵计算(既已成功调用CalcHV())
            */
    BOOL CalcMotion(CameraInterCalc &CameraInterPara,F32 D);
}
