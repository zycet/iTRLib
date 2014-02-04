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

    //dis_Ratio = 0.6;//最优匹配和次优匹配的比例
    F32 Max_ang = 18;   //匹配极限偏差，角度制
    F32 valuet1[num2];
    F32 valuet2[num1];
    F32 result_min,result_ang;
    bool match1[num1];
    bool match2[num2];
    Calculate CalculateObj;
    Numerical NumericalObj;
    //第一副图向第二副图匹配
    for(S32 i=0; i<num1; i++)
    {

        for(S32 j=0; j<num2; j++)
        {
            valuet1[j] = vectorfeaturepoint1[i].Feature.ProductInner(vectorfeaturepoint2[j].Feature);
        }
        CalculateObj.Min(valuet1, num2, result_min);//需要索引啊！即最小值对应的编号。
        NumericalObj.Acos(result_min,result_ang);
        if(result_ang<Max_ang)
            match1[i]=true;
        else
            match1[i]=false;
        if(i>0)
            for(S32 j=0;j<i;j++)
                if(match1[i]&&vectorfeaturepoint1[i].X==vectorfeaturepoint1[j].X&&vectorfeaturepoint1[i].Y==vectorfeaturepoint1[j].Y)
                    match1[i]=false;
    }
    //第二副向第一副匹配
    for(S32 i=0; i<num2; i++)
    {

        for(S32 j=0; j<num1; j++)
        {
            valuet2[j] = vectorfeaturepoint2[i].Feature.ProductInner(vectorfeaturepoint1[j].Feature);
        }
        CalculateObj.Min(valuet2, num1, result_min);//需要索引啊！即最小值对应的编号。
        NumericalObj.Acos(result_min,result_ang);
        if(result_ang<Max_ang)
            match2[i]=true;
        else
            match2[i]=false;
        if(i>0)
            for(S32 j=0;j<i;j++)
                if(match2[i]&&vectorfeaturepoint2[i].X==vectorfeaturepoint2[j].X&&vectorfeaturepoint2[i].Y==vectorfeaturepoint2[j].Y)
                    match2[i]=false;
    }
    //双向匹配

    //匹配结果

}
}
