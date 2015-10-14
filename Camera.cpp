/* 
 * File:   Camera.cpp
 * Author: michelle
 * 
 * Created on October 14, 2015, 12:12 PM
 */

#include "Camera.h"


Camera::Camera(Vec3<double> eye, Vec3<double> at, Vec3<double> up, 
        double _fovy, double _near, double _far, int _wp, int _hp) {
    Eye = eye;
    Center = at;
    Vec3<double> temp = Eye - Center;
    Up = up;
    fovy = _fovy;
    n = _near;
    f = _far;
    wp = _wp;
    hp = _hp;
    df = n;
    hm = 2*df*tan(fovy / 2);
    wm = (wp /  hp) * hm;
    Ze = (1 / temp.normalise()) * temp;
    Vec3<double> temp2 = Vec3<double>::crossProduct(up, Ze);
    Xe = (1 / temp2.normalise()) * temp2;
    Ye = Vec3<double>::crossProduct(Ze, Xe);
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

Ray camGetRay(double x, double y){
    Vec3<double> Dr;
    Dr = 
}

