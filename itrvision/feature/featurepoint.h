/*
 * featurepoint.h
 *
 *  Created on: 2013-9-27
 *      Author: ghdawn
 */

#ifndef FEATUREPOINT_H_
#define FEATUREPOINT_H_

class FeaturePoint
{
    public:
        int x, y;
        int value;
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
