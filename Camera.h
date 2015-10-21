/* 
 * File:   Camera.h
 * Author: michelle
 *
 * Created on October 14, 2015, 12:12 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "Vec3.h"
#include "Ray.h"
#include <math.h>

class Camera {
public:
    Camera(double eyex,double eyey, double eyez, double atx, double aty, 
        double atz,double upx, double upy, double upz, double _fovy, 
        double _near, double _far, double _wp, double _hp);
    Camera(const Camera& orig);
    virtual ~Camera();
    Ray camGetRay(double x, double y);
    Vec3<double> getPos(){return Center;};
    Vec3<double> getEye(){return Eye;};
     
private:

     /* Definição da câmera */ 
    Vec3<double> Eye, Center, Up;
    float fovy;
    float n, f;
    float wp,hp;
    
    /*  Parametros derivados */
    float df, wm, hm;
    Vec3<double> Xe, Ye, Ze;
    
};

#endif	/* CAMERA_H */

