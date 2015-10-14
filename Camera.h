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

class Camera {
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
    Ray camGetRay(double x, double y);
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

