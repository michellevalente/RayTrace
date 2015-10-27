#include <vector>
#include "Object.h"
#include "float.h"
#include "Vec3.h"
#include "image.h"
#define EPSILON	1.0e-3
#define MAX( a, b ) ( ( a > b ) ? a : b )
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

Esfera::Esfera(std::string material,double _raio, double px,double py, double pz){
	pos.set(px, py, pz);
	raio = _raio;
	mat = material;
}

bool Esfera::intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi, double& distance){

	
	Vec3<double> temp;
	temp = (r.Or - pos);
	double a = (r.Dr).dot(r.Dr);

	double b = (r.Dr*2).dot(temp);
	
	double c = (temp.dot(temp)) - (raio * raio);
	double delta = b*b - 4*a*c;
	
	if(delta >= 0)
	{
		double t1 = (-b - sqrt(delta))/(2*a);
		double t2 = (-b + sqrt(delta))/(2*a);
		double tm = min(t1,t2);
		if(tm > 0)
		{
			pi = r.Or + (tm * r.Dr) ;
			temp = pi - pos;
			normal = temp/temp.norm();
			double root = sqrt(delta);
			distance = MAX( ( ( -b + root ) / ( 2 * a ) ), ( ( -b - root ) / ( 2.0 * a ) )  );
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

Caixa::Caixa(std::string material, double xmin, double ymin, double zmin, double xmax, double ymax,
	double zmax){
	p1.set(xmin, ymin, zmin);
	p2.set(xmax, ymax, zmax);
	mat = material;
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

bool Caixa::intersection(Camera& cam,Ray& r, Vec3<double>& normal, Vec3<double>& pi,  double& distance)
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
	distance = -1;

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

Triangulo::Triangulo(std::string material, double p1x, double p1y, double p1z, double p2x, 
	double p2y, double p2z, double p3x, double p3y, double p3z, double _u1, double _v1,
	double _u2, double _v2, double _u3, double _v3)
{
	p1.set(p1x,p1y,p1z);
	p2.set(p2x,p2y,p2z);
	p3.set(p3x,p3y,p3z);
	mat = material;
	u1 = _u1;
	u2 = _u2;
	u3 = _u3;
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
}

bool Triangulo::intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi,  double& distance)
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
	distance = (cam.getEye() - pi).norm();

	if(l1 <= 1 && l1 >= 0 && l2 <= 1 && l2 >= 0 && l3 <= 1 && l3 >= 0 )
		return 1;
	else
		return 0;

	
}

void Triangulo::getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal)
{
	int w = imgGetWidth(textura);
	int h = imgGetHeight(textura);

	Vec3<double> e3 = p2 - p1;
	Vec3<double> e2 = p1 - p3;
	Vec3<double> e1 = p3 - p2;
	double a1 = normal.dot(e1.cross(pi - p2)) / 2;
	double a2 = normal.dot(e2.cross(pi - p3)) / 2;
	double a3 = normal.dot(e3.cross(pi - p1)) / 2;
	double at = a1 + a2 + a3;
	double l1 = a1 / at;
	double l2 = a2 / at;
	double l3 = a3/at;

	double u = l1 * u1 + l2 * u2 + l3 * u3;
	double v = l1 * v1 + l2 * v2 + l3 * v3;

	int i = ( (int)( u * ( w- 1 )  + 0.5) % w );
	int j = ( (int)( v * ( h- 1 )  + 0.5) % w );

	float r, g, b;
	imgGetPixel3f(textura, i, j, &r, &g, &b);
	cor.set(r,g,b);

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

	// Vec3<double> re = ((2*(vl.dot(normal)))*normal )- ve;

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
		double ksy, double ksz, double _coef_spec ,double _coef_reflexao,
		double _indice_refracao, double _opacidade, std::string _textura){
	nome = _nome;
	kd.set(kdx, kdy, kdz);
	ks.set(ksx,ksy,ksz);

	coef_spec = _coef_spec;
	coef_reflexao = _coef_reflexao;
	indice_refracao = _indice_refracao;
	opacidade = _opacidade;
	textura = _textura;
	if(_textura != "null")
	{
		char * file = const_cast<char*>(textura.c_str());
		std::cout << file << std::endl;
		t = imgReadBMP(file);
	}
		

}

void Caixa::getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal)
{
	int w = imgGetWidth(textura);
	int h = imgGetHeight(textura);
	int x = pi.getX();
	int y = pi.getY();
	int z = pi.getZ();
	int xmin = p1.getX();
	int ymin = p1.getY();
	int zmin = p1.getZ();
	int xmax = p2.getX();
	int ymax = p2.getY();
	int zmax = p2.getZ();
	double u = 0, v = 0;

	if( ( std::fabs( x - xmin ) < EPSILON ) || ( std::fabs( x - xmax ) < EPSILON ) )
	{
		u = (double)( y - ymin ) / ( ymax - ymin );
		v = (double)( z - zmin ) / ( zmax - zmin );
	}
	else if( ( std::fabs( y - ymin ) < EPSILON ) || ( std::fabs( y - ymax ) < EPSILON ) )
	{
		u = (double)( z - zmin ) / ( zmax - zmin ); 
		v = (double)( x - xmin ) / ( xmax - xmin );
	}
	else if( ( std::fabs( z - zmin ) < EPSILON ) || ( std::fabs( z - zmax ) < EPSILON ) )
	{
		u = (double) ( x - xmin ) / ( xmax - xmin );
		v = (double)( y - ymin ) / ( ymax - ymin );
	}

	int i = ( (int)( u * ( w- 1 )  + 0.5) % w );
	int j = ( (int)( v * ( h- 1 )  + 0.5) % w );

	float r, g, b;
	imgGetPixel3f(textura, i, j, &r, &g, &b);
	cor.set(r,g,b);
}

void Esfera::getTextura(Image * textura,Vec3<double>& pi, Vec3<double>& cor, Vec3<double>& normal)
{
	int w = imgGetWidth(textura);
	int h = imgGetHeight(textura);

	double phi = atan2( normal.getY(), normal.getX() );
	double theta = atan2( sqrt( ( normal.getX() * normal.getX() ) + ( normal.getY() * normal.getY() ) ), normal.getZ() );

	double u = ( 1 + phi / M_PI );
	double v = ( 1 - theta / M_PI );
	
	int i = ( (int)( u * ( w- 1 )  + 0.5) % w );
	int j = ( (int)( v * ( h- 1 )  + 0.5) % w );

	float r, g, b;
	imgGetPixel3f(textura, i, j, &r, &g, &b);
	cor.set(r,g,b);
}

Vec3<double> Object::getColor(Vec3<double>& pi, Luz * luz, Vec3<double>& normal, 
	Camera& cam, Material& mat, Vec3<double>& kd)
{
	Vec3<double> cor(0.0,0.0,0.0);

	double diffuse = calculateDiffuse(pi, *luz, normal);
	double spec = calculateSpec(pi, *luz, 
		normal, cam, mat.getKs(), mat.getCoefSpec());
	cor += ((luz->getRgb()).cross2(kd) * (diffuse)) ;
	cor += ((luz->getRgb()).cross2(mat.getKs()) * (spec));
	

	return cor;
}

Scene::Scene(double bx, double by, double bz, double lx, double ly, double lz, std::string imagem)
{
	background.set(bx, by, bz);
	luz_ambiente.set(lx, ly, lz);
	img = imagem; 
}