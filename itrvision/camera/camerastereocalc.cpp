#include "camerastereocalc.h"
#include "alglib.h"
#define pi 3.1415926
namespace itr_vision
{

CameraStereoCalc::CameraStereoCalc()
{
    _exinfo.Equ.Init(4);//ctor
    InstallAngle=0;

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
//bool CameraStereoCalc::Calc( F32* DeepZero,F32 *x,F32*y,F32*x1,F32*y1,S32 matched_num)
{

    S32 num1=PointList0.size();
    S32 num2=PointList1.size();
    /// 匹配
    FeatureMatch domatch;
    S32 matched_num;
    domatch.FeatureMatchDo( PointList0, PointList1,matched_num);
    _exinfo.MatchPercent=matched_num*2/(num1+num2);
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

/// / //////////////////////////////////////////////////////////////////////
//    F32 *z,*resid_w,ang_x0,ang_y0,ang_x1,ang_y1;
//    Point2D point0,point1;
//    x=new F32[matched_num]();
//    y=new F32[matched_num]();
//    z=new F32[matched_num]();
//
//    resid_w=new F32[matched_num]();
//
//    x1=new F32[matched_num]();
//    y1=new F32[matched_num]();
//
//    F32 x_t[4];
//    F32 y_t[4];
//    F32 z_t[4];
//    F32 w_t[4];
//    S32 j=0;
///  //////////////////////////////////////////////////////////////////////////
    F32 cot_x1,cot_x2;
    Vector v_p(3),v_c(4);
    for(S32 i=0; i<matched_num; i++)
    {
        point0.X=x[i];
        point0.Y=y[i];
        point1.X=x1[i];
        point1.Y=y1[i];
        //printf("point0:%f\t%f\tpoint1:%f\t%f\n",point0.X,point0.Y,point1.X,point1.Y);

        CameraInterCalc0->CalcAng(point0,ang_x0, ang_y0);
        CameraInterCalc1->CalcAng(point1,ang_x1, ang_y1);

        //printf("angle: %f\t%f\n",ang_x0,ang_x1);

        itr_math::NumericalObj->Tan(ang_x0,cot_x1);
        itr_math::NumericalObj->Tan(ang_x1,cot_x2);
        cot_x1=1/cot_x1;
        cot_x2=1/cot_x2;

        z[i]=Distance/(abs(cot_x1-cot_x2));     ///求深度
        /// //////////////////////////////////////// 加误差，测试用
//        F32 for_rand;
//        itr_math::NumericalObj->Rand(for_rand);
//        z[i]+=for_rand;

  //      printf("z[i]: %f\n",z[i]);

        v_p[0]=x[i],v_p[1]=y[i],v_p[2]=1;
        CameraInterCalc0->CalcP2C(v_p,z[i],v_c);
        x[i]=v_c[0];
        y[i]=v_c[1];        /// 转化为相机0的坐标
        //printf("c pos: %f\t%f\n",x[i],y[i]);

        x[i]-=Distance/2;  /// 至此xyz转化为相机原点坐标
        //printf("final pos: %f\t%f\t%f\n",x[i],y[i],z[i]);
    }
    ///由坐标求平面方程
    /// ///////////////////////////////////////////////////
    //z[1]=10;  //野数据
    /// 初步拟合
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
        for(S32 i=0; i<4; i++)
        {
            x_t[i]=x[lable[i]];
            y_t[i]=y[lable[i]];
            z_t[i]=z[lable[i]];
            w_t[i]=1;
        }
        cof(x_t,y_t,z_t,w_t,4); /// 求 _exinfo.Equ;
        if(j==0)
        {
            best_plan=_exinfo.Equ;
            min_dis=100000000;
        }
        else
        {
            dis=0;
            for(S32 i=0; i<matched_num; i++)
            {
                dis+=getdistance(x[i],y[i],z[i],_exinfo.Equ);
            }
            if(dis<min_dis)
            {
                min_dis=dis;
                best_plan=_exinfo.Equ;
            }
        }
        j++;
    }while(j<10);

    _exinfo.Equ=best_plan;

    ///精确拟合
    for(S32 i=0; i<matched_num; i++)
    {  resid_w[i]=1;
    }
    F32 sigma,median_value;
        /// resid=x1;
        /// dev=y1;
    for(j=0; j<10; j++)
    {

        for(S32 i=0; i<matched_num; i++)
        {
            x1[i]=getdistance(x[i],y[i],z[i],_exinfo.Equ);
        }
        //计算权重

        itr_math::StatisticsObj->Median(x1,matched_num,median_value);
        sigma=1.4826*median_value;

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
    F32 varsum=0;
    for(S32 i=0; i<matched_num; i++)
     {
        varsum+=(x1[i]*x1[i]);
     }
    _exinfo.Var=varsum/matched_num;

    ///求得方程求0,0点z坐标
    *DeepZero=(-_exinfo.Equ[3])/_exinfo.Equ[2];

    if(InstallAngle)
    {
        F32 tmpcos,tmpsin,tmp_b,tmp_c;
        itr_math::NumericalObj->SinCos(InstallAngle,tmpsin,tmpcos);
        tmp_b=_exinfo.Equ[1]*tmpcos+_exinfo.Equ[2]*tmpsin;
        tmp_c=-_exinfo.Equ[1]*tmpsin+_exinfo.Equ[2]*tmpcos;
        _exinfo.Equ[1]=tmp_b;
        _exinfo.Equ[2]=tmp_c;
        *DeepZero=(-_exinfo.Equ[3])/_exinfo.Equ[2];
    }
    return (true);
}

F32 CameraStereoCalc::getdistance(F32 x,F32 y,F32 z,Vector p)
{
    return((p[0]*x+p[1]*y+p[2]*z+p[3])/sqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]));
}

void CameraStereoCalc::cof(F32*x,F32*y,F32 *z,F32*w,S32 length)
{
    double *M;  //最小二乘矩阵
    M=new double[4*length]();

    for(S32 j=0; j<length; j++)
    {
        M[j*4]=w[j]*x[j];
        M[j*4+1]=w[j]*y[j];
        M[j*4+2]=w[j]*z[j];
        M[j*4+3]=w[j];
    }
    //svd
    double V[16]={0};
    alglib::real_2d_array Marray,Varray,Uarray;
    alglib::real_1d_array Warray;
    Marray.setcontent(length,4,M);
    Varray.setcontent(4,4,V);
    alglib::rmatrixsvd(Marray,length,4,0,2,2,Warray,Uarray,Varray);

    for(S32 j=0; j<4; j++)
        _exinfo.Equ[j]=Varray(3,j);
}
 CameraStereoCalc::CalcExInfo CameraStereoCalc::GetCalcExInfo()
{
    return _exinfo;
}

}
