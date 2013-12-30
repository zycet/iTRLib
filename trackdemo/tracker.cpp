#include "tracker.h"

#include "itralgorithm.h"
#include "algorithm"
#include "iostream"
#include "stdio.h"
using namespace itr_vision;

using namespace itr_algorithm;
using std::cout;
using std::endl;


void printMatrix(Matrix a)
{
    for (int i = 0; i < a.GetRow(); ++i)
    {
        for (int j = 0; j < a.GetCol(); ++j)
        {
            printf("%f ", a(i, j));
        }
        printf("\n");
    }
}


class DataOper:public Operator
{
    public:
        F32 GetError(F32 a, F32 b)
        {
            return fabs(a-b);
        }
        F32 GetValue(F32 *data, S32 N)
        {
            std::sort(data,data+N);
            return data[N/2];
        }
        bool Remain(F32 error)
        {
            return (fabs(error)<1.5);
        }
};

S32 FeatureNum=150;
F32 x[150];
F32 y[150];

void Tracker()
{
    printf("*****Begin Tracking Test!*****\n\n");
    itr_math::MathObjStandInit();
    char path[50]="bin/Debug/09_carchase/pgm/%05d.pgm";
    char file[50]="bin/Debug/09_carchase/pgm/00001.pgm";
    Matrix current,last;
    IOpnm::ReadPGMFile(file, current);
    IOpnm::ReadPGMFile(file, last);

    ///读取初始位置
    RectangleS rect(0, 0, 0, 0);
    FILE *InitInfo=fopen("bin/Debug/09_carchase/init.txt","r");
    fscanf(InitInfo,"%d,%d,%d,%d",&rect.X,&rect.Y,&rect.Width,&rect.Height);
    rect.Width-=rect.X;
    rect.Height-=rect.Y;

    ///卡尔曼滤波用
    KalmanFilter kf(4);
    F32 data[16]= {1 ,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1};
    kf.F_x.CopyFrom(data);
    Matrix H(2,4),R(2,2);
    R.MatEye(5.012306);
    H.CopyFrom(data+8);
    printMatrix(H);
    printMatrix(kf.F_x);
    Vector z(2),X(4),v(2);
    kf.x[0]=rect.X;
    kf.x[1]=rect.Y;
    kf.x[2]=0;
    kf.x[3]=0;

    F32 _x,_y,_u=0,_v=0;
    Detection(current,rect,_x,_y);
    for(int k=2; k<200; ++k)
    {
        sprintf(file, path, k);
        printf("%s\n",file);
        last=current;
        IOpnm::ReadPGMFile(file, current);
        //kltTracker(current,last,rect,_u,_v);
        rect.X+=_u;
        rect.Y+=_v;
        Detection(current,rect,_x,_y);
        rect.X=_x;
        rect.Y=_y;
        Draw::Rectangle(current,rect,255);
        sprintf(file,"bin/Debug/output/%05d.pgm",k);
        IOpnm::WritePGMFile(file,current);
    }

    printf("*****End Tracking Test!*****\n\n");
}

const int Num=10;
bool Detection(const Matrix &current,RectangleS &rect,F32 &x,F32 &y)
{
    printf("\n*****Begin  Detection !*****\n\n");
    static bool flag=false;
    static RectangleS rects[Num]=RectangleS(100,100,300,300);
    static Matrix patch(rect.Height,rect.Width);
    static S32 FeatureNum=rect.Height*rect.Width;
    static Matrix dataPos(Num,FeatureNum),dataNeg(Num,FeatureNum),sample(30,30);
    NaiveBayes nbc(FeatureNum);
    if(!flag)
    {
        GenRect::genrectin(rect,rects,Num);
        for(int i=0; i<Num; ++i)
        {
            Pick::Rectangle(current,rects[i],patch);
            Scale::Bilinear(patch,sample);
            dataPos.CopyRowFrom(i,sample.GetData());
        }
        nbc.TrainPos(dataPos);

        GenRect::genrectout(rect,rects,Num);
        for(int i=0; i<Num; ++i)
        {
            Pick::Rectangle(current,rects[i],patch);
            Scale::Bilinear(patch,sample);
            dataNeg.CopyRowFrom(i,sample.GetData());
        }
        nbc.TrainNeg(dataNeg);
        flag=true;
        return true;
    }
    RectangleS  recttmp(rect.X,rect.Y,rect.Width,rect.Height);
    F32 result=-100,best=-100;
    for(int i=rect.X-10; i<rect.X+10; i+=1)
        for(int j=rect.Y-10; j<rect.Y+10; j+=1)
        {
            recttmp.X=i;
            recttmp.Y=j;
            Pick::Rectangle(current,recttmp,patch);
            Scale::Bilinear(patch,sample);
            result=nbc.Classify(sample.GetData());
            if(best<result)
            {
                best=result;
                x=i;
                y=j;
            }
        }
    printf("Detect:%f,%f\n",x,y);
    printf("\n*****End  Detection !*****\n\n");
    return true;
}
bool kltTracker(const Matrix &current,const Matrix &last,RectangleS &rect,F32 &u,F32 &v)
{
    printf("*****Begin  Tracking !*****\n\n");

    ///存储KLT特征

    static vector<FeaturePoint> flU(FeatureNum);
    static vector<FeaturePoint> flV(FeatureNum);
    static vector<FeaturePoint> flU2(FeatureNum);

    Matrix gray(current);
    ///随机一致性检测
    DataOper oper;
    Ransac ransac(oper);

    ///用于临时存放速度值

    static S32 count = 0, drop=0;

    ConvoluteSquare conv;

    //static LKTracker tracker(last);
    LKTracker tracker(last,current);
    tracker.max_iterations=15;

    ///选择图像中的特征点
    SelectFeature select(last);
    select.mindist = 7;
    FeatureNum=select.SelectGoodFeature(rect, flU,count/5);

    cout<<"FeatureNum:"<<FeatureNum<<endl;

    conv._KLTComputeSmoothedImage(gray, 0.1 * tracker.windowWidth, gray);
    int start = clock() / 1000;
    //tracker.AddNext(gray);
    ///正反误差滤波
    tracker.Compute(flU, flV, FeatureNum,true);
    tracker.Compute(flV, flU2, FeatureNum, false);

    for (int i = 0; i <FeatureNum; ++i)
    {
        if (fabs(flU[i] - flU2[i]) > 8)
        {
            flV[i].value = -1;
        }
    }
    Matrix result;
    Draw::Correspond(last,gray,flU,flV,result);
    IOpnm::WritePPMFile("bin/Debug/result.ppm",result);

    ///计算矩形框速度
    count=0;
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

    cout << "Points: "<<count << endl;

    if( count==0)
    {
        return false;
    }

    ///RANSAC
    ransac.Process(count, x, drop);
    std::sort(x, x + count);
    u=x[(count - drop) / 2];

    ransac.Process(count, y, drop);
    std::sort(y, y + count);
    v=y[(count - drop) / 2];

    printf("u,v:%f,%f \n", u, v);
    cout << "Tracking Time: "<<(clock() / 1000 - start) << endl;
    ///输出速度
    if(false)
    {
        printf("X: ");
        for (int i = 0; i < count; i++)
        {
            printf("%0.2f ", x[i]);
        }
        cout << endl;
        printf("Y: ");
        for (int i = 0; i < count; i++)
        {
            printf("%0.2f ", y[i]);
        }
        cout << endl;
        for (unsigned int i = 0; i < FeatureNum; ++i)
        {
            if (flV[i].value >= 0)
            {
                Draw::Circle(gray, flV[i].x, flV[i].y, 2, 255);
            }
        }
    }

    cout<<endl;
    printf("*****End  Tracking !*****\n\n");
    return true;
}

