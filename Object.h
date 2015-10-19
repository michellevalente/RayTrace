#ifndef OBJET_H
#define	OBJET_H

#include "Vec3.h"
#include "Ray.h"
#include <math.h>
#include "Camera.h"

class Object{
public:
	Object(){};
    Object(const Object& orig);
    virtual ~Object();
    virtual Vec3<double> intersection() = 0;
private:

};

class Esfera{
public:
	Esfera(double px, double py, double pz, double _raio, double r, 
		double g, double b);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    Vec3<double> getColor();

private:
	Vec3<double> pos;
	double raio;
	Vec3<double> cor;
};

class Luz{
public:
	Luz(Vec3<double>& p, Vec3<double>& cor){ posicao = p; rgb = cor; };
	Vec3<double> getRgb(){return rgb;};
	Vec3<double> getPos(){return posicao;};
private:
	Vec3<double> posicao;
	Vec3<double> rgb;
};

class Caixa{
public:
	Caixa(double xmin, double ymin, double zmin, double xmax, double ymax,
	 double zmax, double r, double g, double b);
    bool intersection(Ray& r, Vec3<double>& normal, Vec3<double>& pi, float &t);
    Vec3<double> getColor();

private:
	Vec3<double> p1;
	Vec3<double> p2;
	Vec3<double> cor;
};

#endif