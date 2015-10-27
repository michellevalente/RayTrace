/* 
 * File:   Ray.h
 * Author: michelle
 *
 * Created on October 14, 2015, 12:40 PM
 */

#ifndef RAY_H
#define	RAY_H

#include "Vec3.h"

class Ray {
public:
    Ray(Vec3<double> _Dr, Vec3<double> _Or );
    virtual ~Ray();

    Vec3<double> Or;
    Vec3<double> Dr;
};

#endif	/* RAY_H */

