#include "vectorfeaturepoint.h"

#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{

VectorFeaturePoint::VectorFeaturePoint()
{
    //ctor
    this->Feature.Init(128);
    this->LevelNo =0;
    this->ID =0;
    this->Tag =NULL;
    this->Dir =0;
    this->Quality=0;
    this->Scale=0;
    this->Value=0;
}

VectorFeaturePoint::~VectorFeaturePoint()
{
    //dtor
}

VectorFeaturePoint::VectorFeaturePoint(const VectorFeaturePoint &other):Feature(other.Feature)
{
    //copy ctor
    this->LevelNo =other.LevelNo;
    this->ID =other.ID;
    this->Tag =other.Tag;
    this->Dir =other.Dir;
    this->Quality=other.Quality;
    this->Scale=other.Scale;
    this->Value=other.Value;
    this->X=other.X;
    this->Y=other.Y;
}
void VectorFeaturePoint::Init(Point2D Pos,S32 ID,F32 Dir,F32 Quality,F32 Value,S32 FeatureDim,S32 LevelNo,F32 Scale)
{
    this->SetXY(Pos.X, Pos.Y);
    this->ID =ID;
    this->Dir=Dir;
    this->Quality=Quality;
    this->Value=Value;
    this->Feature.Init(FeatureDim);
    this->LevelNo=LevelNo;
    this->Scale=Scale;
}
void VectorFeaturePoint::Init(Point2D Pos,F32 Dir,S32 FeatureDim,S32 LevelNo,F32 Scale)
{
    this->SetXY(Pos.X, Pos.Y);
    this->Dir=Dir;
    this->Feature.Init(FeatureDim);
    this->LevelNo=LevelNo;
    this->Scale=Scale;
}
}
