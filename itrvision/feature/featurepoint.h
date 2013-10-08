/*
 * featurepoint.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef FEATUREPOINT_H_
#define FEATUREPOINT_H_
#include "itrbase.h"
class FeaturePoint
{
    public:
        S32 x, y;
        S32 value;
        inline bool operator<(const FeaturePoint &b) const
        {
            return value < b.value;
        }
        inline bool operator>(const FeaturePoint& b) const
        {
            return value > b.value;
        }
};

#endif /* FEATUREPOINT_H_ */
