#include "lktracking.h"
using itr_math::Vector;
lktracking::lktracking():
    FeatureNum(100),frame1Feature(FeatureNum),frame2Feature(FeatureNum),fbFeature(FeatureNum)
{
    x=new F32[FeatureNum];
    y=new F32[FeatureNum];
    dist=new F32[FeatureNum];
    debugcount=1;
}

void lktracking::Init(const Matrix &current,RectangleS &rect)
{
    tracker.Init(current);
    SelectKLTFeature select(current);
    select.mindist=7;
    ransac.Init(&oper);
    FeatureNum=select.SelectGoodFeature(rect,frame1Feature);
}

void lktracking::ncc_filter(const Matrix  &input1,const Matrix  &input2)
{
    RectangleS rect;
    rect.Width=rect.Height=5;
    int i,length=rect.Width*rect.Height;
    F32 mean1,mean2;

    Matrix patch1(rect.Width,rect.Height),patch2(rect.Width,rect.Height);
    Vector v1(length,patch1.GetData());
    Vector v2(length,patch2.GetData());
    for (i = 0; i <FeatureNum; ++i)
    {
        rect.X=frame1Feature[i].X-2;
        rect.Y=frame1Feature[i].Y-2;
        Pick::Rectangle(input1,rect,patch1);
        rect.X=frame2Feature[i].X-2;
        rect.Y=frame2Feature[i].Y-2;
        Pick::Rectangle(input2,rect,patch2);
        itr_math::StatisticsObj->Mean(patch1.GetData(),length,mean1);
        itr_math::StatisticsObj->Mean(patch2.GetData(),length,mean2);
        itr_math::CalculateObj->Offset(v1.GetData(),-mean1,length,v1.GetData());
        itr_math::CalculateObj->Offset(v1.GetData(),-mean2,length,v2.GetData());
        itr_math::CalculateObj->Normalization(v1.GetData(),length,v1.GetData());
        itr_math::CalculateObj->Normalization(v2.GetData(),length,v2.GetData());
        dist[i]=v1*v2;
    }
    F32 median;
    itr_math::StatisticsObj->Median(dist,FeatureNum,median);
    for (i = 0; i <FeatureNum; ++i)
    {
        if(dist[i]>median)
        {
            frame2Feature[i].Quality=-LKTracker::NCCError;
        }
    }
}

void lktracking::pairdistance(const vector<Point2D> &feature,vector<F32> &dist)
{
    int n=feature.size(),k=0;
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
        {
            if(i==j)
            {
                dist[k]=0.1;
            }
            else
            {
                dist[k]=(feature[i]-feature[j]).GetDistance();
            }
            ++k;
        }
}

F32 lktracking::getScale(S32 pointcount)
{
    S32 n=pointcount*pointcount;
    vector<F32> pointDist1(n),pointDist2(n),distDiv(n);
    vector<Point2D> feature1(pointcount),feature2(pointcount);
    int i,j=0;
    for(i=0; i<FeatureNum; ++i)
    {
        for(i=0; i<FeatureNum; ++i)
        {
            if(frame2Feature[i].Quality>=0)
            {
                feature1[j]=frame1Feature[i];
                feature2[j]=frame2Feature[i];
                j++;
            }
        }
    }
    pairdistance(feature1,pointDist1);
    pairdistance(feature2,pointDist2);
    itr_math::CalculateObj->Div(&pointDist1[0],&pointDist2[0],n,&distDiv[0]);
    F32 median;
    itr_math::StatisticsObj->Median(&distDiv[0],n,median);
    itr_math::NumericalObj->Sqrt(median,median);

    return median;
}
void lktracking::fb_filter()
{
    int i;
    for (i = 0; i <FeatureNum; ++i)
    {
        dist[i]=(frame1Feature[i]-frame2Feature[i]).GetDistance();
    }
    F32 median;
    itr_math::StatisticsObj->Median(dist,FeatureNum,median);
    for (i = 0; i <FeatureNum; ++i)
    {
        if(dist[i]>median)
        {
            frame2Feature[i].Quality=-LKTracker::FBError;
        }
    }
}
bool lktracking::Go(const Matrix &current,RectangleS &rect,F32 &Vx,F32 &Vy)
{
    TimeClock clock;
    int i;
    clock.Tick();
    tracker.AddNext(current);
    tracker.Compute(frame1Feature,frame2Feature,FeatureNum,true);
    tracker.Compute(frame2Feature,fbFeature,FeatureNum,false);

    ///Filter
    if(FeatureNum>0)
    {
        fb_filter();
        ncc_filter(tracker.last->img[0],tracker.current->img[0]);
    }
    if(false)
    {
        ///特征点匹配关系输出
        Matrix cor;
        vector<Point2D> outU(FeatureNum),outV(FeatureNum);
        int count=0;
        for(i=0; i<FeatureNum; ++i)
        {
            if(frame2Feature[i].Quality>=0)
            {
                outU[count]=frame1Feature[i];
                outV[count]=frame2Feature[i];
                count++;
            }
        }
        Draw::Correspond(tracker.last->img[0],tracker.current->img[0],outU,outV,count,cor);
        char file[20];
        sprintf(file,"bin/Debug/corr%d",debugcount++);
        IOpnm::WritePGMFile(file,cor);
    }
    ///计算矩形框速度
    S32 drop=0,amount=0;
    for (i = 0; i < FeatureNum; ++i)
    {
        if (frame2Feature[i].Quality == 0)
        {
            x[amount] = frame2Feature[i].X - frame1Feature[i].X;
            y[amount] = frame2Feature[i].Y - frame1Feature[i].Y;
            frame1Feature[amount].X=frame2Feature[i].X;
            frame1Feature[amount].Y=frame2Feature[i].Y;
            frame1Feature[amount].Quality=frame1Feature[i].Quality;
            ++amount;
        }
    }
//    cout << "Points: "<<count << endl;
    if(amount>0)
    {
        //RANSAC
        ransac.Process(x,amount, drop);
        std::sort(x, x + amount);
        Vx=x[(amount - drop) / 2];

        ransac.Process(y,amount, drop);
        std::sort(y, y + amount);
        Vy=y[(amount - drop) / 2];

        F32 boxScale=1.0f;
        std::cout<<getScale(amount)<<std::endl;
        boxScale=getScale(amount);
        rect.X+=Vx-rect.Width*(boxScale-1)/2;
        rect.Y+=Vy-rect.Height*(boxScale-1)/2;
        rect.Width*=boxScale;
        rect.Height*=boxScale;
    }


    //选择下一帧图像中的特征点
    SelectKLTFeature select(current);
    select.mindist = 6;
    FeatureNum=select.SelectGoodFeature(rect, frame1Feature,amount);
    printf("Feature: %d\n",FeatureNum);
    printf("Track Time: %d",clock.Tick());
    printf("\n*****End  Track !*****\n\n");
    return (amount>0);
}

lktracking::~lktracking()
{
    delete[] x;
    delete[] y;
}
