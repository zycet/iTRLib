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
        float key;
        inline bool operator<(const FeaturePoint &b) const
        {
            return key < b.key;
        }
        inline bool operator>(const FeaturePoint& b) const
        {
            return key > b.key;
        }
};

#endif /* FEATUREPOINT_H_ */
