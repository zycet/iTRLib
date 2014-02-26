/*
 * scale.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef SCALE_H_
#define SCALE_H_

#include "itrbase.h"

using itr_math::Matrix;
namespace itr_vision
{

class Scale
{
public:
    Scale();
    virtual ~Scale();
    static S16 Interpolation(const Matrix &src, F32 x, F32 y);

    static void Bilinear(const Matrix &src, Matrix &dst);

    static void SubSampling(const Matrix &src, Matrix &dst, S32 scale);

};

} /* namespace itr_vision */
#endif /* SCALE_H_ */
