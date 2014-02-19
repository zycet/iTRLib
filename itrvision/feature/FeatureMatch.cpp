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
void FeatureMatch::FeatureMatchDo(VectorFeaturePoint vectorfeaturepoint1[],S32 num1,
                                  VectorFeaturePoint vectorfeaturepoint2[],S32 num2,S32 matchnum,Point2D pos1[],Point2D pos2[])
{

    F32 valuet[num1>num2?num1:num2];
    F32 result_ang;
    S32 order;
    Calculate CalculateObj;
    Numerical NumericalObj;
    //dis_Ratio = 0.6;//最优匹配和次优匹配的比例,由于calculate函数中暂无求次小值函数，暂时不实现。？？？？？？？？？？？？？？？？？？
    F32 Max_ang;    //匹配极限偏差，角度的余弦值
    NumericalObj.Cos(18,Max_ang);

    //第一副图向第二副图匹配
    for(S32 i=0; i<num1; i++)
    {

        for(S32 j=0; j<num2; j++)
        {
            valuet[j] = vectorfeaturepoint1[i].Feature.ProductInner(vectorfeaturepoint2[j].Feature);
        }
        CalculateObj.Min(valuet, num2, result_ang,order);
        if(result_ang<Max_ang)
        {
            vectorfeaturepoint1[i].ID=order;
        }
        else
        {
            vectorfeaturepoint1[i].ID= -1;
        }
        if(i>0&&vectorfeaturepoint1[i].ID!= -1)
            for(S32 j=0; j<i; j++)
                if(vectorfeaturepoint1[j].ID!=-1&&vectorfeaturepoint1[i].X==vectorfeaturepoint1[j].X&&vectorfeaturepoint1[i].Y==vectorfeaturepoint1[j].Y)
                    vectorfeaturepoint1[i].ID= -1;
    }
    //第二副向第一副匹配
    for(S32 i=0; i<num2; i++)
    {

        for(S32 j=0; j<num1; j++)
        {
            valuet[j] = vectorfeaturepoint2[i].Feature.ProductInner(vectorfeaturepoint1[j].Feature);
        }
        CalculateObj.Min(valuet, num1, result_ang,order);
        if(result_ang<Max_ang)
        {
            vectorfeaturepoint2[i].ID=order;
        }
        else
        {
            vectorfeaturepoint2[i].ID=-1;
        }
        if(i>0&&vectorfeaturepoint2[i].ID!=-1)
            for(S32 j=0; j<i; j++)
                if(vectorfeaturepoint2[j].ID!=-1&&vectorfeaturepoint2[i].X==vectorfeaturepoint2[j].X&&vectorfeaturepoint2[i].Y==vectorfeaturepoint2[j].Y)
                    vectorfeaturepoint2[i].ID=-1;
    }

    //双向匹配
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
    //匹配结果
    /*S32 tempcounter =0;
    for(S32 i=0; i<num1; i++)
    {
        if(match1[i])
        {
            pos1[tempcounter].SetXY(vectorfeaturepoint1[i].X, vectorfeaturepoint1[i].Y);
            pos2[tempcounter].SetXY(vectorfeaturepoint2[match1order[i]].X, vectorfeaturepoint2[match1order[i]].Y);
            tempcounter++;
        }
    }*/
}
}
