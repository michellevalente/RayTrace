#ifndef OBJET_H
#define	OBJET_H

#include "Vec3.h"
#include "Ray.h"
#include <math.h>
#include "Camera.h"
#include "image.h"


class Scene{
public:
	Scene(double bx, double by, double bz, double lx, double ly, double lz, std::string imagem);
	Vec3<double> getLuz(){return luz_ambiente;};
	Vec3<double> getBackground(){return background;};
private:
	Vec3<double> background;
	Vec3<double> luz_ambiente;
	std::string img;
};

class Luz{
public:
	Luz(double px, double py, double pz, double cx, double cy, double cz){ posicao.set(px,py,pz); rgb.set(cx, cy, cz); };
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
	std::string getNome(){return nome;};
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
	virtual std::string getMaterial() = 0;
	Vec3<double> getColor(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, Camera& cam, Material& mat);
private:
	
};

class Esfera: public Object{
public:
	//Esfera(double px, double py, double pz, double _raio, char * t);
	Esfera(std::string material, double _raio, double px,double py, double pz);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    //void getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal);
    Vec3<double> getPos(){return pos;};
    std::string getMaterial(){return mat;};

private:
	Vec3<double> pos;
	double raio;
	Image * text; 
	std::string mat;
};

class Caixa: public Object{
public:
	Caixa(std::string material, double xmin, double ymin, double zmin, double xmax, double ymax,
	 double zmax);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi);
    std::string getMaterial(){return mat;};

private:
	Vec3<double> p1;
	Vec3<double> p2;
	std::string mat;
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