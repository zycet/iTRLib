#ifndef TRACKER_H
#define TRACKER_H

#include "itrbase.h"
#include "itrvision.h"
using itr_math::Matrix;
bool kltTracker(const Matrix &gray,const Matrix &last,RectangleS &rect,F32 &u,F32 &v);

void Tracker();

#endif // TRACKER_H
