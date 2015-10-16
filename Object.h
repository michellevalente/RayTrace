#ifndef OBJET_H
#define	OBJET_H

#include "Vec3.h"
#include "Ray.h"
#include <math.h>
#include "Camera.h"
// class Object{
// public:
// 	Object();
//     Object(const Object& orig);
//     virtual ~Object();
//     virtual Vec3<double> intersection();
// private:

// };

class Esfera{
public:
	Esfera(Vec3<double>& p, double _raio, double r, double g, double b);
	// Esfera(const Esfera& orig);
 //    virtual ~Esfera();
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

#endif