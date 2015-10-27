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
	Luz(double px, double py, double pz, double cx, double cy, double cz){
	 posicao.set(px,py,pz); 
	 rgb.set(cx, cy, cz); 
	};
	Vec3<double> getRgb(){return rgb;};
	Vec3<double> getPos(){return posicao;};
	void print()
	{
		std::cout << "X: " << posicao.getX() << " Y: " << posicao.getY() << " Z: " << posicao.getZ() << std::endl;
		std::cout << "R: " << rgb.getX() << " G: " << rgb.getY() << " B: " << rgb.getZ() << std::endl;
	}
private:
	Vec3<double> posicao;
	Vec3<double> rgb;
};

class Material{
public:
	Material(std::string _nome, double kdx,double kdy, double kdz, double ksx, 
		double ksy, double ksz, double _coef_spec ,double _coef_reflexao,
		double _indice_refracao, double _opacidade, std::string _textura);
	Vec3<double> getKd(){return kd;};
	Vec3<double> getKs(){return ks;};
	int getCoefSpec(){return coef_spec;};	
	bool reflete(){if(coef_reflexao > 0.0) return 1; else return 0;}
	std::string getNome(){return nome;};
	std::string getTextura(){return textura;};
	Image * getFileTextura(){return t;};
	bool transparente(){if(opacidade  < 1.0) return 1; else return 0;}
	double getK(){return coef_reflexao;};
	double getN(){return indice_refracao;};
    double getO(){return opacidade;};
private:
	std::string nome;
	Vec3<double> kd;
	Vec3<double> ks;
	double coef_spec;
	double coef_reflexao;
	double indice_refracao;
	double opacidade;
	std::string textura;
	Image * t;

};

class Object{
public:
	Object(){};
    Object(const Object& orig);
    //virtual ~Object();
    virtual bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi, double& distance) = 0;
    double calculateDiffuse(Vec3<double>& pi, Luz& luz, Vec3<double>& normal);
	double calculateSpec(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, 
	Camera& cam, Vec3<double> corSpec, double coef);
	virtual std::string getMaterial() = 0;
	Vec3<double> getColor(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, 
	Camera& cam, Material& mat, Vec3<double>& kd);
	virtual void getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal,bool linear = false) = 0;
private:
	
};

class Esfera: public Object{
public:
	//Esfera(double px, double py, double pz, double _raio, char * t);
	Esfera(std::string material, double _raio, double px,double py, double pz);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi,  double& distance);
    //void getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal);
    Vec3<double> getPos(){return pos;};
    std::string getMaterial(){return mat;};
    void getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal,  bool linear = false);

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
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi,  double& distance);
    std::string getMaterial(){return mat;};
    void getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal,  bool linear = false);

private:
	Vec3<double> p1;
	Vec3<double> p2;
	std::string mat;
};

class Triangulo: public Object{
public:
	Triangulo(std::string material, double p1x, double p1y, double p1z, double p2x, 
	double p2y, double p2z, double p3x, double p3y, double p3z, double _u1, double _v1,
	double _u2, double _v2, double _u3, double _v3);
    bool intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi, double& distance);
    std::string getMaterial(){return mat;};
    void getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal,  bool linear = false);
private:
	Vec3<double> p1;
	Vec3<double> p2;
	Vec3<double> p3;
	double u1, u2, u3, v1, v2, v3;
	std::string mat;
};

#endif