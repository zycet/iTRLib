#include "lktracking.h"

lktracking::lktracking():
    FeatureNum(100),flU(FeatureNum),flV(FeatureNum),flU2(FeatureNum)
{
    x=new F32[FeatureNum];
    y=new F32[FeatureNum];
}

void lktracking::Init(const Matrix &current,RectangleS &rect)
{
    tracker.Init(current);
    SelectFeature select(current);
    select.mindist=7;
    ransac.Init(&oper);
    FeatureNum=select.SelectGoodFeature(rect,flU);
}

bool lktracking::Go(const Matrix &current,const RectangleS &rect,F32 &u,F32 &v)
{
    int start = clock() / 1000;
    tracker.AddNext(current);
    tracker.Compute(flU,flV,FeatureNum,true);
    tracker.Compute(flV,flU2,FeatureNum,false);
    for (int i = 0; i <FeatureNum; ++i)
    {
        if (fabs(flU[i] - flU2[i]) > 9)
        {
            flV[i].value = -1;
        }
    }
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
    if(count==0)
        return false;
    //RANSAC
    ransac.Process(count, x, drop);
    std::sort(x, x + count);
//    rect.X += (S32)(x[(count - drop) / 2]+0.5); //(x / count + 0.5);
    u=x[(count - drop) / 2];
    ransac.Process(count, y, drop);
    std::sort(y, y + count);
//    rect.Y += (S32)(y[(count - drop) / 2]+0.5); //(y / count + 0.5);
    v=y[(count - drop) / 2];
    printf("X,Y:%d,%d \n", rect.X, rect.Y);

      //std::cin.get();


    //选择下一帧图像中的特征点
    SelectFeature select(current);
    select.mindist = 7;
    //std::sort(flU.begin(),flU.end(),std::greater<FeaturePoint>());
    FeatureNum=select.SelectGoodFeature(rect, flU);
    printf("Track Time: %d",(clock() / 1000 - start));
    printf("\n*****End  Track !*****\n\n");
    return true;
}

lktracking::~lktracking()
{
    delete[] x;
    delete[] y;
}
