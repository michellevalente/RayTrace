#include "Object.h"

double min(double n1, double n2){
	if(n1 < n2)
		return n1;
	else
		return n2;
}

Esfera::Esfera(Vec3<double>& p, double _raio, double r, double g, double b){
	pos = p;
	raio = _raio;
	cor.set(r,g,b);
}

bool Esfera::intersection(Camera& cam, Ray& r, Vec3<double>& normal, Vec3<double>& pi){
	Vec3<double> temp;
	
	double a = (r.Dr).dot(r.Dr);
	temp = r.Dr * 2;
	double b = temp.dot(r.Or - pos);
	temp = (r.Or - pos);
	double temp2 = temp.norm();
	double c = (temp2 * temp2) - (raio * raio);
	double delta = b*b - 4*a*c;
	
	if(delta > 0)
	{
		double t1 = (-b - sqrt(delta))/2*a;
		double t2 = (-b + sqrt(delta))/2*a;
		double tm = min(t1,t2);
		if(tm > 0)
		{
			pi = r.Or + (tm * r.Dr) ;
			temp = pi - pos;
			normal = (1.0/(temp.norm())) * temp ;
			return 1;

		}

	}
	else
	{
		normal.set(0,0,0);
	}
	return 0;
}

Vec3<double> Esfera::getColor()
{
	return cor;
}