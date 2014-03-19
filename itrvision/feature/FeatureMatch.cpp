#include "FeatureMatch.h"
using namespace itr_math;
namespace itr_vision
{
FeatureMatch::FeatureMatch()
{
    //ctor
}

FeatureMatch::~FeatureMatch()
{
    //dtor
}
void FeatureMatch::FeatureMatchDo(std::vector<VectorFeaturePoint>& vectorfeaturepoint1,std::vector<VectorFeaturePoint>&vectorfeaturepoint2,S32 &matchnum)
{
    S32 num1=vectorfeaturepoint1.size();
    S32 num2=vectorfeaturepoint2.size();
    if(num1<=0||num2<=0)
    {
        matchnum=0;
    }
    else
    {
        F32 *valuet;
        valuet=new F32[num1>num2?num1:num2];
        F32 resultM,resultC;
        S32 order;
        F32 dis_Ratio = 0.927;///最优匹配和次优匹配的比例,由于calculate函数中暂无求次小值函数
        F32 Min_angcos=0.9511;    ///匹配极限偏差，角度的余弦值Cos(pi/10);

        ///第一副图向第二副图匹配
        for(S32 i=0; i<num1; i++)
        {

            for(S32 j=0; j<num2; j++)           /// 通过两个特征向量内积，跟设定值比较来判断是否匹配，标准见下
            {
                valuet[j] = (vectorfeaturepoint1[i].Feature).ProductInner(vectorfeaturepoint2[j].Feature);
            }
            Max(valuet, num2, resultM, resultC, order);
            /// 判断标准： 特征向量夹角小于10度，并且最优匹配比次优匹配好0.927
            if(resultM>Min_angcos&&(resultC/resultM<dis_Ratio))
            {
                vectorfeaturepoint1[i].ID=order;
            }

            if(i>0&&vectorfeaturepoint1[i].ID!= -1)
                for(S32 j=0; j<i; j++)
                    if(vectorfeaturepoint1[j].ID!=-1&&vectorfeaturepoint1[i].X==vectorfeaturepoint1[j].X&&vectorfeaturepoint1[i].Y==vectorfeaturepoint1[j].Y)
                        vectorfeaturepoint1[i].ID= -1;
        }
        ///第二副向第一副匹配
        for(S32 i=0; i<num2; i++)
        {

            for(S32 j=0; j<num1; j++)
            {
                valuet[j] = vectorfeaturepoint2[i].Feature.ProductInner(vectorfeaturepoint1[j].Feature);
            }

            Max(valuet, num1, resultM, resultC, order);
            if(resultM>Min_angcos&&(resultC/resultM<dis_Ratio))
            {
                vectorfeaturepoint2[i].ID=order;
            }

            if(i>0&&vectorfeaturepoint2[i].ID!=-1)
                for(S32 j=0; j<i; j++)
                    if(vectorfeaturepoint2[j].ID!=-1&&vectorfeaturepoint2[i].X==vectorfeaturepoint2[j].X&&vectorfeaturepoint2[i].Y==vectorfeaturepoint2[j].Y)
                        vectorfeaturepoint2[i].ID=-1;
        }

        ///双向匹配
        matchnum =0;
        for(S32 i=0; i<num1; i++)
        {
            if(vectorfeaturepoint1[i].ID!=-1)
            {
                if(vectorfeaturepoint2[vectorfeaturepoint1[i].ID].ID==i)
                {
                    matchnum++;
                }
                else
                    vectorfeaturepoint1[i].ID= -1;
            }
        }
        delete[] valuet;
    }
}
void FeatureMatch::Max(F32* SourceA, S32 Length, F32& ResultM, F32& ResultC, S32 &Order) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    ResultM = SourceA[0];
    ResultC= SourceA[0];
    Order=0;
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > ResultM)
        {
            ResultC=ResultM;
            ResultM = SourceA[i];
            Order=i;
        }
    }
}
}
