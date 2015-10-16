/* 
 * File:   Camera.cpp
 * Author: michelle
 * 
 * Created on October 14, 2015, 12:12 PM
 */

#include "Camera.h"


Camera::Camera(Vec3<double>& eye, Vec3<double>& at, Vec3<double>& up, 
        double _fovy, double _near, double _far, double _wp, double _hp) {
    Eye = eye;
    Center = at;
    Up = up;
    Vec3<double> temp = Eye - Center;
    fovy = _fovy;
    n = _near;
    f = _far;
    wp = _wp;
    hp = _hp;
    df = n;
    hm = 2*df*tan(fovy / 2.0);
    wm = (wp /  hp) * hm;
    Ze = (1 / (temp.norm())) * temp;
    Vec3<double> temp2 = Vec3<double>::cross(up, Ze);
    Xe = (1 / (temp2.norm())) * temp2;
    Ye = Vec3<double>::cross(Ze, Xe);
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

Ray Camera::camGetRay(double x, double y){
    Vec3<double> Dr ;
    Vec3<double> Or= Eye;

    Dr = (-df*(Ze.normalized()) )+ (hm*(y/hp - 0.5) * (Ye.normalized())) + (wm*(x/wp -0.5)* (Xe.normalized()));
    Ray r(Dr, Or);

    return r;
     
}

