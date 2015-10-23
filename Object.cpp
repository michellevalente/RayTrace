#include "Object.h"
#include "float.h"
#include "Vec3.h"
#define EPSILON	1.0e-3
double min(double n1, double n2){
	if(n1 < n2)
		return n1;
	else
		return n2;
}

// Esfera::Esfera(double px,double py, double pz, double _raio, char* t){
// 	pos.set(px, py, pz);
// 	raio = _raio;
// 	text = imgReadBMP(t);
// 	textura = 1;

// }

Esfera::Esfera(double px,double py, double pz, double _raio, Material& material){
	pos.set(px, py, pz);
	raio = _raio;
	mat = &material;
}

bool Esfera::intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi){

	Vec3<double> temp;
	temp = (r.Or - pos);
	double a = (r.Dr).dot(r.Dr);

	double b = (r.Dr*2).dot(temp);
	
	double c = (temp.dot(temp)) - (raio * raio);
	double delta = b*b - 4*a*c;
	
	if(delta > 0)
	{
		double t1 = (-b - sqrt(delta))/(2*a);
		double t2 = (-b + sqrt(delta))/(2*a);
		double tm = min(t1,t2);
		if(tm > 0)
		{
			pi = r.Or + (tm * r.Dr) ;
			temp = pi - pos;
			normal = temp/temp.norm();
			return 1;

		}

	}

    return 0;
	
}

// void Esfera::getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal)
// {
// 	if(textura == 0)
// 		corFinal = cor;
// 	else
// 	{
// 		char estrela[256] = "estrela.bmp";
// 		text = imgReadBMP(estrela);	
// 		int w = imgGetWidth(text);
		
// 		int h = imgGetHeight(text);

// 		double x = pi.getX() ;
// 		double y = pi.getY() ;
// 		double z = pi.getZ() ;

// 		double phi = atan(y/x);
// 		double theta = sqrt(x*x + y*y) / z;
// 		double u = 1 + phi / M_PI;
// 		double v = 1 - theta / M_PI;
// 		int i = v * (h - 1);
// 		int j = u * (w - 1);

// 		float r, g, b;
// 		std::cout << "teste1" << std::endl;
// 		std::cout << "x: "<< x  << " y: " << y << "z: " << z << std::endl;
// 		std::cout << "i: "<< i  << " j: " << j << std::endl;
// 		imgGetPixel3f(text, i, j, &r, &g, &b);
// 		corFinal.set(r,g,b);
		
		
		
		
// 	}
// }

Caixa::Caixa(double xmin, double ymin, double zmin, double xmax, double ymax,
	double zmax, Material& material){
	p1.set(xmin, ymin, zmin);
	p2.set(xmax, ymax, zmax);
	mat = &material;
}

void getNormalBox(Vec3<double>& pi, Vec3<double>& p1, Vec3<double>& p2, Vec3<double>& normal)
{
	if( fabs( pi.getX() - p1.getX() ) < EPSILON )
	{
		normal.set(-1.0,0.0,0.0);
	}
	else if( fabs( pi.getX() - p2.getX() ) < EPSILON )
	{
		normal.set(1.0,0.0,0.0);
	}
	else if( fabs(  pi.getY() - p1.getY()  ) < EPSILON )
	{
		normal.set(0.0,-1.0,0.0);		
	}
	else if( fabs( pi.getY() - p2.getY() ) < EPSILON )
	{
		normal.set(0.0,1.0,0.0);
	}
	else if( fabs(  pi.getZ() - p1.getZ()  ) < EPSILON )
	{	
		normal.set(0.0,0.0,-1.0);
	}
	else if( fabs(  pi.getZ() - p2.getZ()  ) < EPSILON )
	{
		normal.set(0.0,0.0,1.0);
		
	}
	else
	{
		normal.set(0.0,0.0,0.0);
		
	}
}

bool Caixa::intersection(Camera& cam,Ray& r, Vec3<double>& normal, Vec3<double>& pi)
{
	double dx = r.Dr.getX();
	double dy = r.Dr.getY();
	double dz = r.Dr.getZ();
	double xmin = p1.getX();
	double ymin = p1.getY();
	double zmin = p1.getZ();
	double xmax = p2.getX();
	double ymax = p2.getY();
	double zmax = p2.getZ();

	int x, y, z;
	double distance = -1;

	if( r.Dr.getX() > EPSILON || -(1.0f)*r.Dr.getX() > EPSILON )
	{
		if(dx > 0)
		{
			x = xmin;
			distance = (xmin - r.Or.getX()) / r.Dr.getX();
		}

		if(dx < 0)
		{
			x = xmax;
			distance = ( xmax - r.Or.getX() ) / r.Dr.getX();
		}

		if(distance > 0)
		{
			y = r.Or.getY() + distance * r.Dr.getY();
			z = r.Or.getZ() + distance * r.Dr.getZ();
			if( y >= ymin && y <= ymax && z >= zmin && z <= zmax)
			{
				pi = r.Or + distance * r.Dr;
				getNormalBox(pi,p1,p2,normal);
				return true;
			}
		}
	}

	if( r.Dr.getY() > EPSILON || -(1.0f)*r.Dr.getY() > EPSILON )
	{
		if(dy > 0)
		{
			y = ymin;
			distance = (ymin - r.Or.getY()) / r.Dr.getY();
		}

		if(dy < 0)
		{
			y = ymax;
			distance = ( ymax - r.Or.getY() ) / r.Dr.getY();
		}

		if(distance > 0)
		{
			x = r.Or.getX() + distance * r.Dr.getX();
			z = r.Or.getZ() + distance * r.Dr.getZ();
			if( x >= xmin && x <= xmax && z >= zmin && z <= zmax)
			{
				pi = r.Or + distance * r.Dr;
				getNormalBox(pi,p1,p2,normal);
				return true;
			}
		}
	}
	if( r.Dr.getZ() > EPSILON || -(1.0f)*r.Dr.getZ() > EPSILON )
	{
		if(dz > 0)
		{
			z = zmin;
			distance = (zmin - r.Or.getZ()) / r.Dr.getZ();
		}

		if(dz < 0)
		{
			z = zmax;
			distance = ( zmax - r.Or.getZ() ) / r.Dr.getZ();
		}

		if(distance > 0)
		{
			y = r.Or.getY() + distance * r.Dr.getY();
			x = r.Or.getX() + distance * r.Dr.getX();
			if( y >= ymin && y <= ymax && x >= xmin && x <= xmax)
			{
				pi = r.Or + distance * r.Dr;
				getNormalBox(pi,p1,p2,normal);
				return true;
			}
		}
	}
    return false; 
}

Triangulo::Triangulo(Vec3<double>& _p1, Vec3<double>& _p2, Vec3<double>& _p3, double r, double g, double b)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	cor.set(r,g,b);
}

bool Triangulo::intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi)
{
	Vec3<double> e3 = p2 - p1;
	Vec3<double> e2 = p1 - p3;
	Vec3<double> e1 = p3 - p2;
	Vec3<double> normal2 = e3.cross(e1);
	// normal = (p2 - p1).cross(p3 - p2) / ((p2 - p1).cross(p3 - p2)).norm();
	double ti = (p1 - cam.getEye()).dot(normal2) / (r.Dr.dot(normal2));
	pi = cam.getEye() + ti * r.Dr;

	

	// if(normal2.dot(e3.cross(pi - p1)) > 0)
	// 	return 1;
	// else
	// 	return 0;

	normal = (e3.cross(e1)).normalized();
	double a1 = normal.dot(e1.cross(pi - p2)) / 2;
	double a2 = normal.dot(e2.cross(pi - p3)) / 2;
	double a3 = normal.dot(e3.cross(pi - p1)) / 2;
	double at = a1 + a2 + a3;
	double l1 = a1 / at;
	double l2 = a2 / at;
	double l3 = a3/at;
	if(l1 <= 1 && l1 >= 0 && l2 <= 1 && l2 >= 0 && l2 <= 1 && l2 >= 0 )
		return 1;
	else
		return 0;

	
}

double Object::calculateDiffuse(Vec3<double>& pi, Luz& luz, Vec3<double>& normal)
{
	Vec3<double> vl = ( luz.getPos() - pi );
	vl = vl.normalized();

	double diffuse = normal.dot(vl);
	if(diffuse < 0)
		return 0.0;
	else
		return diffuse;

}

double Object::calculateSpec(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, 
	Camera& cam, Vec3<double> corSpec, double coef)
{
	Vec3<double> vl = ( luz.getPos() - pi );
	vl = vl.normalized();
	Vec3<double> rl = ((2*(vl.dot(normal)))*normal )- vl;

	Vec3<double> ve = (cam.getEye() - pi );
	ve =ve.normalized();
	Vec3<double> cor_spec(1.0,1.0,1.0);
	double spec = rl.dot(ve);
	if(spec > 0){
		spec = pow(spec, coef);
		return spec;
	}
	else
		return 0.0;
}

Material::Material(std::string _nome, double kdx,double kdy, double kdz, double ksx, 
		double ksy, double ksz, int _coef_spec ,int _coef_reflexao,
		double _indice_refracao, double _opacidade, std::string _textura){
	nome = _nome;
	kd.set(kdx, kdy, kdz);
	ks.set(ksx,ksy,ksz);

	coef_spec = _coef_spec;
	coef_reflexao = _coef_reflexao;
	indice_refracao = _indice_refracao;
	opacidade = _opacidade;
	textura = _textura;

}

Vec3<double> Object::getColor(Vec3<double>& pi, Luz& luz, Vec3<double>& normal, Camera& cam)
{
	double diffuse = calculateDiffuse(pi, luz, normal);
	double spec = calculateSpec(pi, luz, 
		normal, cam, getMaterial().getKs(), getMaterial().getCoefSpec());
	Vec3<double> cor ;
	cor = ((luz.getRgb()).cross2(getMaterial().getKd()) * (diffuse)) ;
	//cor += luz_ambiente;
	cor += ((luz.getRgb()).cross2(getMaterial().getKs()) * (spec));

	return cor;
}




char estrela[256] = "mundo.bmp";
Image * text = imgReadBMP(estrela);	
void Material::getFinalColor(Vec3<double>& pi, Vec3<double>& corFinal, int raio)
{
	int w = imgGetWidth(text);
	int h = imgGetHeight(text);

	double x = pi.getX() ;
	double y = pi.getY() ;
	double z = pi.getZ() ;	

	double phi = atan2(y,x) + M_PI;
	double theta = atan(sqrt((x*x + y*y))/z) + M_PI/2;
	
	//double u = phi / (2*M_PI);
	//double v = theta / M_PI;

	double u = 1 + phi / M_PI;
	double v = 1 - theta / M_PI;

	int i = v * (h - 1);
	int j = u * (w - 1);

	float r, g, b;
	imgGetPixel3f(text, j, i, &r, &g, &b);
	corFinal.set(r,g,b);
		
		
	
}