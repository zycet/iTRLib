#ifndef TRACKER_H
#define TRACKER_H

#include "itrbase.h"
#include "itrvision.h"
using itr_math::Matrix;
bool kltTracker(const Matrix &gray,const Matrix &last,RectangleS &rect,F32 &u,F32 &v);

void Tracker();

bool Detection(const Matrix &current,RectangleS &rect,F32 &x,F32 &y);

#endif // TRACKER_H
