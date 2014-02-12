#include "lktracking.h"

lktracking::lktracking():
    FeatureNum(100),flU(FeatureNum),flV(FeatureNum),flU2(FeatureNum)
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
    FeatureNum=select.SelectGoodFeature(rect,flU);
}

bool lktracking::Go(const Matrix &current,RectangleS &rect,F32 &u,F32 &v)
{
    TimeClock clock;
    int i;
    clock.Tick();
    tracker.AddNext(current);
    tracker.Compute(flU,flV,FeatureNum,true);
    tracker.Compute(flV,flU2,FeatureNum,false);


    ///FB Filter
    if(FeatureNum>0)
    {
        for (i = 0; i <FeatureNum; ++i)
        {
            dist[i]=(flU[i]-flV[i]).GetDistance();
        }
        F32 median;
        itr_math::StatisticsObj->Median(dist,FeatureNum,median);
        for (i = 0; i <FeatureNum; ++i)
        {
            if(dist[i]>median)
            {
                flV[i].Quality=-LKTracker::FBError;
            }
        }
    }
    if(false)
    {
        ///特征点匹配关系输出
        Matrix cor;
        vector<Point2D> outU(FeatureNum),outV(FeatureNum);
        int count=0;
        for(i=0; i<FeatureNum; ++i)
        {
            if(flV[i].Quality>=0)
            {
                outU[i]=flU[i];
                outV[i]=flV[i];
                count++;
            }
        }
        Draw::Correspond(tracker.last->img[0],tracker.current->img[0],outU,outV,count,cor);
        char file[20];
        sprintf(file,"bin/Debug/corr%d",debugcount++);
        IOpnm::WritePGMFile(file,cor);
    }
    ///计算矩形框速度
    S32 drop=0,count=0;
    for (i = 0; i < FeatureNum; ++i)
    {
        if (flV[i].Quality == 0)
        {
            x[count] = flV[i].X - flU[i].X;
            y[count] = flV[i].Y - flU[i].Y;
            flU[count].X=flV[i].X;
            flU[count].Y=flV[i].Y;
            flU[count].Quality=flU[i].Quality;
            ++count;
        }
    }
//    cout << "Points: "<<count << endl;
    if(count>0)
    {
        //RANSAC
        ransac.Process(count, x, drop);
        std::sort(x, x + count);
        u=x[(count - drop) / 2];
        rect.X+=u;
        ransac.Process(count, y, drop);
        std::sort(y, y + count);
        v=y[(count - drop) / 2];
        rect.Y+=v;
    }
    //选择下一帧图像中的特征点
    SelectKLTFeature select(current);
    select.mindist = 6;
    FeatureNum=select.SelectGoodFeature(rect, flU,count);
    printf("Feature: %d\n",FeatureNum);
    printf("Track Time: %d",clock.Tick());
    printf("\n*****End  Track !*****\n\n");
    return (count>0);
}

lktracking::~lktracking()
{
    delete[] x;
    delete[] y;
}
