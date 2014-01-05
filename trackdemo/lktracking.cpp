#include "lktracking.h"

lktracking::lktracking():
    FeatureNum(100),flU(FeatureNum),flV(FeatureNum),flU2(FeatureNum)
{
    x=new F32[FeatureNum];
    y=new F32[FeatureNum];
    debugcount=1;
}

void lktracking::Init(const Matrix &current,RectangleS &rect)
{
    tracker.Init(current);
    SelectFeature select(current);
    select.mindist=7;
    ransac.Init(&oper);
    FeatureNum=select.SelectGoodFeature(rect,flU);
}

bool lktracking::Go(const Matrix &current,RectangleS &rect,F32 &u,F32 &v)
{
    int start = clock() / 1000;
    tracker.AddNext(current);
    tracker.Compute(flU,flV,FeatureNum,true);
    tracker.Compute(flV,flU2,FeatureNum,false);


    for (int i = 0; i <FeatureNum; ++i)
    {
    printf("%f ",fabs((float)(flU[i] - flU2[i])));
        if (fabs(flU[i] - flU2[i]) > 10)
        {
            flV[i].value = -1;
        }
    }

    Matrix cor;
    Draw::Correspond(tracker.last->img[0],tracker.current->img[0],flU,flV,FeatureNum,cor);
    char file[20];
    sprintf(file,"bin/Debug/corr%d",debugcount++);
    IOpnm::WritePGMFile(file,cor);
    //计算矩形框速度
    S32 count=0,drop=0;
    for (unsigned int i = 0; i < FeatureNum; ++i)
    {
        if (flV[i].value == 0)
        {
            x[count] = flV[i].x - flU[i].x;
            y[count] = flV[i].y - flU[i].y;
            flU[count].x=flV[i].x;
            flU[count].y=flV[i].y;
            flU[count].value=flU[i].value;
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
    SelectFeature select(current);
    select.mindist = 6;
    FeatureNum=select.SelectGoodFeature(rect, flU,count);
    printf("Feature: %d\n",FeatureNum);
    printf("Track Time: %d",(clock() / 1000 - start));
    printf("\n*****End  Track !*****\n\n");
    return (count>0);
}

lktracking::~lktracking()
{
    delete[] x;
    delete[] y;
}
