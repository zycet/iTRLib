/*
 * featurepoint.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef FEATUREPOINT_H_
#define FEATUREPOINT_H_
#include "itrbase.h"
#include <math.h>
namespace itr_vision
{
    class FeaturePoint
    {
        public:
            S32 x, y;
            S32 value;
            FeaturePoint()
            {
                x = y = value = -1;
            }
            FeaturePoint(S32 X, S32 Y, S32 Value)
            {
                x = X;
                y = Y;
                value = Value;
            }
            inline S32 operator-(const FeaturePoint &b) const
            {
                return fabs(x - b.x) + fabs(y - b.y);
            }
            inline bool operator<(const FeaturePoint &b) const
            {
                return value < b.value;
            }
            inline bool operator>(const FeaturePoint& b) const
            {
                return value > b.value;
            }
    };
}
#endif /* FEATUREPOINT_H_ */
