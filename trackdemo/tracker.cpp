#include "tracker.h"
#include "itrbase.h"
#include "itrvision.h"
#include "itralgorithm.h"
#include "algorithm"
#include "iostream"
#include "stdio.h"
using namespace itr_vision;
using itr_math::Matrix;
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

void kltTracker()
{
printf("*****Begin KLT Tracking Test!*****\n\n");

    itr_math::MathObjStandInit();
    char path[50]="bin/Debug/09_carchase/pgm/%05d.pgm";
    char file[50]="bin/Debug/09_carchase/pgm/00001.pgm";
    Matrix gray,last;
    IOpnm::ReadPGMFile(file, gray);
    IOpnm::ReadPGMFile(file, last);

    ///读取初始位置
    RectangleS rect(0, 0, 0, 0);
    FILE* InitInfo=fopen("bin/Debug/09_carchase/init.txt","r");
    fscanf(InitInfo,"%d,%d,%d,%d",&rect.X,&rect.Y,&rect.Width,&rect.Height);
    rect.Width-=rect.X;
    rect.Height-=rect.Y;
    ///存储KLT特征
    S32 FeatureNum=150;
    vector<FeaturePoint> flU(FeatureNum), flV(FeatureNum), flU2(FeatureNum);


    ///随机一致性检测
    DataOper oper;
    Ransac ransac(oper);

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

    ///用于临时存放速度值，总特征点数及有效点数
    F32 *x = new F32[FeatureNum], *y = new F32[FeatureNum];
    S32 count = 0, drop=0;

    ConvoluteSquare conv;

    ///主循环，对每一帧图像
    LKTracker tracker(gray);
    tracker.max_iterations=15;
    for (int k = 1; k < 200; ++k)
    {
        //选择图像中的特征点
        SelectFeature select(gray);
        select.mindist = 5;
        //std::sort(flU.begin(),flU.end(),std::greater<FeaturePoint>());
        FeatureNum=select.SelectGoodFeature(rect, flU);

        cout<<"FeatureNum:"<<FeatureNum<<endl;
        last=gray;
        sprintf(file, path, k);
        printf("%s\n",file);
        IOpnm::ReadPGMFile(file, gray);
        conv._KLTComputeSmoothedImage(gray, 0.1 * tracker.windowWidth, gray);
        int start = clock() / 1000;
        tracker.AddNext(gray);

        //正反误差滤波
        tracker.Compute(flU, flV, FeatureNum,true);
//        for(int i=0;i<FeatureNum;++i)
//         cout<<flV[i].value<<endl;
        tracker.Compute(flV, flU2, FeatureNum, false);
        for (int i = 0; i <FeatureNum; ++i)
        {
            if (fabs(flU[i] - flU2[i]) > 15)
                flV[i].value = -1;
//            printf("%d,%d\n", flU[i] - flU2[i], flV[i].value);
        }
        Matrix result;
        Draw::Correspond(last,gray,flU,flV,result);
        IOpnm::WritePPMFile("bin/Debug/result.ppm",result);

        //计算矩形框速度
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

        //输出速度
        if(false)
        {
            printf("X: ");
             std::sort(x, x + count);
            for (int i = 0; i < count; i++)
                printf("%0.0f ", x[i]);
            cout << endl;
            std::sort(y, y + count);
            printf("Y: ");
            for (int i = 0; i < count; i++)
                printf("%0.0f ", y[i]);
            cout << endl;
        }
        //RANSAC
        //Ransac(count, x, drop);
        ransac.Process(count+1, x, drop);
        std::sort(x, x + count);
        rect.X += (S32)(x[(count - drop) / 2]+0.5); //(x / count + 0.5);
        z[0]=x[(count - drop) / 2];
        R(0,0)=0.012306;
        ransac.Process(count+1, y, drop);
        std::sort(y, y + count);
        rect.Y += (S32)(y[(count - drop) / 2]+0.5); //(y / count + 0.5);
        z[1]=y[(count - drop) / 2];
        R(1,1)=0.012306;
        printf("X,Y:%d,%d \n", rect.X, rect.Y);
//        z[0]=rect.X+0.0;
//        z[1]=rect.Y+0.0;

        kf.UpdateModel();
        X=kf.UpdateMeasure(H,R,z);
       // rect.X=X[0];
      //  rect.Y=X[1];
        printf("Esti: %.0f,%.0f,%.0f,%.0f\n",X[0],X[1],X[2],X[3]);

        //输出速度
        if(false)
        {
            printf("X: ");
            for (int i = 0; i < count; i++)
                printf("%0.2f ", x[i]);
            cout << endl;
            printf("Y: ");
            for (int i = 0; i < count; i++)
                printf("%0.2f ", y[i]);
            cout << endl;
        }
        //std::cin.get();
        cout << (clock() / 1000 - start) << endl;


        //输出处理

        for (unsigned int i = 0; i < FeatureNum; ++i)
        {
            if (flV[i].value >= 0)
            {
                Draw::Circle(gray, flV[i].x, flV[i].y, 2, 255);
            }
        }
//        rect.X=rect.Y=0;

        Draw::Rectangle(gray, rect, 255);
        sprintf(file, "bin/Debug/output/%05d.pgm", k);
        IOpnm::WritePGMFile(file, gray);


        cout<<endl;
        //getchar();
    }
    delete[] x;
    delete[] y;
printf("*****End KLT Tracking Test!*****\n\n");
}

