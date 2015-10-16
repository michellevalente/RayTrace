/* 
 * File:   Ray.cpp
 * Author: michelle
 * 
 * Created on October 14, 2015, 12:40 PM
 */

#include "Ray.h"

Ray::Ray(Vec3<double> _Dr, Vec3<double> _Or ) {
	Dr = _Dr;
	Or = _Or;
}

Ray::Ray(const Ray& orig) {
}

Ray::~Ray() {
}

