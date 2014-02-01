#include "commfeaturepoint.h"
#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{

CommFeaturePoint::CommFeaturePoint():Point2D()
{
    //ctor
    ID =0;
    Tag =NULL;
    Dir =0;
    Quality=0;
    Value=0;
}
/*
void CommFeaturePoint::Init(Point2D Pos,S32 ID,F32 Dir,F32 Quality,F32 Value)
{

}
void CommFeaturePoint::Init(Point2D Pos,F32 Quality,F32 Value)
{

}*/
CommFeaturePoint::~CommFeaturePoint()
{
    //dtor
}

CommFeaturePoint::CommFeaturePoint(const CommFeaturePoint& other)
{
    //copy ctor
    ID =other.ID;
    Tag =other.Tag;
    Dir =other.Dir;
    Quality=other.Quality;
    Value=other.Value;
}

}
