#include "camerastereocalc.h"
#define pi 3.1415926
namespace itr_vision
{

CameraStereoCalc::CameraStereoCalc()
{
    _exinfo.Equ.Init(3);//ctor
    this->InstallAngle=0;
    _plan.Init(4);
}

CameraStereoCalc::~CameraStereoCalc()
{
    //dtor
}
void CameraStereoCalc::Init(CameraInterCalc* CameraInterCalc0,CameraInterCalc* CameraInterCalc1,F32 Distance)
{
    this->Distance=Distance;
    this->CameraInterCalc0=CameraInterCalc0;
    this->CameraInterCalc1=CameraInterCalc1;
}
bool CameraStereoCalc::Calc( std::vector<VectorFeaturePoint>& PointList0, std::vector<VectorFeaturePoint>& PointList1,F32* DeepZero)
{
    S32 num1=PointList0.size();

    /// 匹配
    FeatureMatch domatch;
    S32 matched_num;
    domatch.FeatureMatchDo( PointList0, PointList1,matched_num);

    if(matched_num<4)
        return (false);

    ///由内参数求坐标
    F32 *x,*x1,*y1,*y,*z,*resid_w,ang_x0,ang_y0,ang_x1,ang_y1;
    Point2D point0,point1;
    x=new F32[matched_num]();
    y=new F32[matched_num]();
    z=new F32[matched_num]();
    resid_w=new F32[matched_num]();
    x1=new F32[matched_num]();
    y1=new F32[matched_num]();

    F32 x_t[4];
    F32 y_t[4];
    F32 z_t[4];
    F32 w_t[4];
    S32 j=0;
    for(S32 i=0; i<num1; i++)
    {
        if(PointList0[i].ID!=-1)
        {
            x[j]=PointList0[i].X;                   /// 像素坐标
            y[j]=PointList0[i].Y;
            x1[j]=PointList1[PointList0[i].ID].X;
            y1[j]=PointList1[PointList0[i].ID].Y;
            j++;
        }
    }
    F32 cot_x1,cot_x2;
    Vector v_p(3),v_c(4);
    for(S32 i=0; i<matched_num; i++)
    {
        point0.X=x[i];
        point0.Y=y[i];
        point1.X=x1[i];
        point1.Y=y1[i];
        CameraInterCalc0->CalcAng(point0,ang_x0, ang_y0);
        CameraInterCalc1->CalcAng(point1,ang_x1, ang_y1);

        itr_math::NumericalObj->Tan(ang_x0,cot_x1);
        itr_math::NumericalObj->Tan(ang_x1,cot_x2);
        cot_x1=1/cot_x1;
        cot_x2=1/cot_x2;

        z[i]=Distance/(abs(cot_x1-cot_x2));     ///求深度
        v_p[0]=x[i],v_p[1]=y[i],v_p[2]=1;
        CameraInterCalc0->CalcP2C(v_p,z[i],v_c);
        x[i]=v_c[0];
        y[i]=v_c[1];
        x[i]-=Distance/2;  /// 至此xyz转化为相机原点坐标
    }
    ///由坐标求平面方程
    // 初步拟合
    j=0;
    F32 p;
    S32 lable[4],q;
    Vector best_plan(4);
    F32 min_dis,dis;
    do          /// RANSAC begin:
    {
        //pick 4 points
        for(S32 i=0; i<4; i++)
        {
            itr_math::NumericalObj->Rand(p);
            itr_math::NumericalObj->Floor(p*matched_num,q);
            if(q==matched_num)
            {
                itr_math::NumericalObj->Rand(p);
                itr_math::NumericalObj->Floor(p*matched_num,q);
            }
            if(i>0)
            {
                for(S32 z=0; z<i; z++)
                    if(q==lable[z])
                    {
                        q=-1;
                        i--;
                    }
            }
            if(q!=-1)
                lable[i]=q;
        }
        //
        for(S32 i=0; i<4; i++)
        {
            x_t[i]=x[lable[i]];
            y_t[i]=y[lable[i]];
            z_t[i]=z[lable[i]];
            w_t[i]=1;
        }
        cof(x_t,y_t,z_t,w_t,4); // _plan;
        if(j==0)
        {
            best_plan=_plan;
            min_dis=100000000;
        }
        else
        {
            dis=0;
            for(S32 i=0; i<matched_num; i++)
            {
                dis+=getdistance(x[i],y[i],z[i],_plan);
            }
            if(dis<min_dis)
            {
                min_dis=dis;
                best_plan=_plan;
            }
        }
        j++;
    }while(j<10);
    _plan=best_plan;

    //精确拟合
    for(S32 i=0; i<matched_num; i++)
    {  resid_w[i]=1;
    }
    F32 sigma;
        // resid=x1;
        //dev=y1;
    for(j=0; j<10; j++)
    {
        for(S32 i=0; i<matched_num; i++)
        {
            x1[i]=getdistance(x[i],y[i],z[i],_plan);
        }
        //计算权重
        sigma=1.4826*median(x1,matched_num);
        for(S32 i=0; i<matched_num; i++)
        {
            y1[i]=x1[i]/sigma;
            if(resid_w[i]>0)
            {
                itr_math::NumericalObj->Exp((-(y1[i]*y1[i])/2),resid_w[i]);
                resid_w[i]/=sqrt(2*pi)*sigma;
            }
            if(x1[i]>5)
                resid_w[i]=0;
        }
        cof(x,y,z,resid_w,matched_num);
    }


    ///求得方程求0,0点z坐标
    for(S32 i=0;i<3; i++)
        _exinfo.Equ[i]=_plan[i]/(-_plan[3]);
    *DeepZero=(-_plan[3])/_plan[2];

    return (true);
}

F32 CameraStereoCalc::getdistance(F32 x,F32 y,F32 z,Vector p)
{
    return((p[0]*x+p[1]*y+p[2]*z+p[3])/sqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]));
}
F32 CameraStereoCalc::median(F32 *a,S32 length)
{
    F32 tmp;
    F32 *n;
    bool *flag;
    S32 num;
    n=new F32[length/2]();
    flag=new bool[length]();
    for(S32 i=0;  i<length; i++)
        flag[i]=true;
    S32 k;
    for(S32 i=0; i<length/2+1; i++)
    {
        k=i;
        while(!flag[k])
        {
            k++;
        }
        tmp=a[k];
        num=k;
        for(S32 j=0; j<length; j++)
        {
            if(flag[j])
            if(tmp<a[j])
            {
                tmp=a[j];
                num=j;
            }
        }
        n[i]=tmp;
        flag[num]=false;
    }
    tmp=n[length/2];
    delete[] n;
    delete[] flag;
    return (tmp);
}
void CameraStereoCalc::cof(F32*x,F32*y,F32 *z,F32*w,S32 length)
{

}
 CameraStereoCalc::CalcExInfo CameraStereoCalc::GetCalcExInfo()
{
    return _exinfo;
}

}
