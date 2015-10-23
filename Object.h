#ifndef OBJET_H
#define	OBJET_H

#include "Vec3.h"
#include "Ray.h"
#include <math.h>
#include "Camera.h"
#include "image.h"


// class Scene{
// public:
// 	Scene();
// private:
// 	Vec3<double> background;
	
// };

class Luz{
public:
	Luz(Vec3<double>& p, Vec3<double>& cor){ posicao = p; rgb = cor; };
	Vec3<double> getRgb(){return rgb;};
	Vec3<double> getPos(){return posicao;};
private:
	Vec3<double> posicao;
	Vec3<double> rgb;
};

class Material{
public:
	Material(std::string _nome, double kdx,double kdy, double kdz, double ksx, 
		double ksy, double ksz, int _coef_spec ,int _coef_reflexao,
		double _indice_refracao, double _opacidade, std::string _textura);
	Vec3<double> getKd(){return kd;};
	Vec3<double> getKs(){return ks;};
	int getCoefSpec(){return coef_spec;};
	//Vec3<double> getFinalColor()
	void getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal, int raio);
	bool reflete(){if(coef_reflexao > 0.0) return 1; else return 0;}
private:
	std::string nome;
	Vec3<double> kd;
	Vec3<double> ks;
	int coef_spec;
	int coef_reflexao;
	int indice_refracao;
	double opacidade;
	std::string textura;

};

class Object{
public:
	Object(){};
    Object(const Object& orig);
    //virtual ~Object();
    virtual bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi) = 0;
    double calculateDiffuse(Vec3<double>& pi, Luz& luz, Vec3<double>& normal);
	double calculateSpec(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, 
	Camera& cam, Vec3<double> corSpec, double coef);
	virtual Material getMaterial() = 0;
	Vec3<double> getColor(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, Camera& cam);
private:
	
};

class Esfera: public Object{
public:
	//Esfera(double px, double py, double pz, double _raio, char * t);
	Esfera(double px,double py, double pz, double _raio, Material& material);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    //void getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal);
    Vec3<double> getPos(){return pos;};
    Material getMaterial(){return *mat;};

private:
	Vec3<double> pos;
	double raio;
	Image * text; 
	Material * mat;
};

class Caixa: public Object{
public:
	Caixa(double xmin, double ymin, double zmin, double xmax, double ymax,
	 double zmax, Material& material);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    Material getMaterial(){return *mat;};

private:
	Vec3<double> p1;
	Vec3<double> p2;
	Material * mat;
};

class Triangulo{
public:
	Triangulo(Vec3<double>& p1, Vec3<double>& p2, Vec3<double>& p3, double r, double g, double b);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    Vec3<double> getColor(){return cor;}
    //void getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal);
private:
	Vec3<double> p1;
	Vec3<double> p2;
	Vec3<double> p3;
	Vec3<double> cor;
};

#endif