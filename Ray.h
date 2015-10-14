/* 
 * File:   Ray.h
 * Author: michelle
 *
 * Created on October 14, 2015, 12:40 PM
 */

#ifndef RAY_H
#define	RAY_H

class Ray {
public:
    Ray();
    Ray(const Ray& orig);
    virtual ~Ray();
private:
    Vec3<double> Or;
    Vec3<double> Dr;
};

#endif	/* RAY_H */

