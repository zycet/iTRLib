#include "commfeaturepoint.h"
#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{

CommFeaturePoint::CommFeaturePoint():Point2D()
{
    //ctor
    this->ID =0;
    this->Tag =NULL;
    this->Dir =0;
    this->Quality=0;
    this->Value=0;
}

void CommFeaturePoint::Init(Point2D Pos,S32 ID,F32 Dir,F32 Quality,F32 Value)
{
    this->SetXY(Pos.X, Pos.Y);
    this->ID =ID;
    this->Dir=Dir;
    this->Quality=Quality;
    this->Value=Value;
}
void CommFeaturePoint::Init(Point2D Pos,F32 Quality,F32 Value)
{
    this->SetXY(Pos.X, Pos.Y);
    // this->Point2D(Pos);
    this->ID =0;
    this->Dir=0;
    this->Quality=Quality;
    this->Value=Value;
}
CommFeaturePoint::~CommFeaturePoint()
{
    //dtor
}

CommFeaturePoint::CommFeaturePoint(const CommFeaturePoint &other)
{
    //copy ctor
    this->SetXY(other.X,other.Y);
    this->ID =other.ID;
    this->Tag =other.Tag;
    this->Dir =other.Dir;
    this->Quality=other.Quality;
    this->Value=other.Value;
}

}
