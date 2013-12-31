#include "detection.h"


Detection::Detection(const Matrix &current,RectangleS &rect,S32 num):
    patch(rect.Height,rect.Width),FeatureNum(30*30),nbc(),
    dataPos(num,FeatureNum),dataNeg(num,FeatureNum),sample(30,30)
{
    Num=num;
    RectangleS rects[20]=RectangleS(100,100,300,300);
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

}

void Detection::Go(const Matrix &current,RectangleS &rect,F32 &x,F32 &y)
{
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
}
