#include "detection.h"


Detection::Detection(const Matrix &current,RectangleS &rect,S32 num):
    patch(rect.Height,rect.Width),FeatureNum(16*16),nbc(FeatureNum),
    dataPos(num,FeatureNum),dataNeg(num,FeatureNum),sample(16,16)
{
    Num=num;
    Range=15;
    Train(current,rect);
}
void Detection::Train(const Matrix &current,RectangleS &rect)
{
    RectangleS rects[20]=RectangleS(100,100,300,300);
    GenRect::genrectin(rect,rects,Num);
    Matrix img(current);
    conv._KLTComputeSmoothedImage(current,1.5,img);
    for(int i=0; i<Num; ++i)
    {
        Pick::Rectangle(img,rects[i],patch);
        Scale::Bilinear(patch,sample);
        dataPos.CopyRowFrom(i,sample.GetData());
    }
    nbc.TrainPos(dataPos);

    GenRect::genrectout(rect,rects,Num);
    for(int i=0; i<Num; ++i)
    {
        Pick::Rectangle(img,rects[i],patch);
        Scale::Bilinear(patch,sample);
        dataNeg.CopyRowFrom(i,sample.GetData());
    }
    nbc.TrainNeg(dataNeg);
}
bool Detection::Go(const Matrix &current,RectangleS &rect)
{
    int start = clock() / 1000;
    RectangleS  recttmp(rect.X,rect.Y,rect.Width,rect.Height);
    Matrix img(current);
    conv._KLTComputeSmoothedImage(current,1.5,img);
    F32 result=-100,best=-99999;
    F32 x,y;
    for(int i=rect.X-Range; i<rect.X+Range; i+=1)
        for(int j=rect.Y-Range; j<rect.Y+Range; j+=1)
        {
            recttmp.X=i;
            recttmp.Y=j;
            Pick::Rectangle(img,recttmp,patch);
            Scale::Bilinear(patch,sample);
            result=nbc.Classify(sample.GetData());
            if(best<result)
            {
                best=result;
                x=i;
                y=j;
            }
        }
    if(best<0)
        return false;
    rect.X=x;
    rect.Y=y;
    Train(current,rect);
    printf("Detect:%f,%f; %f\n",x,y,best);
    printf("Detection Time: %d",(clock() / 1000 - start));
    printf("\n*****End  Detection !*****\n\n");
    return true;
}
