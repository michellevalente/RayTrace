#include "Object.h"

double min(double n1, double n2){
	if(n1 < n2)
		return n1;
	else
		return n2;
}

Esfera::Esfera(double px,double py, double pz, double _raio, double r, double g, double b){
	pos.set(px, py, pz);
	raio = _raio;
	cor.set(r,g,b);
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

Vec3<double> Esfera::getColor()
{
	return cor;
}

Caixa::Caixa(double xmin, double ymin, double zmin, double xmax, double ymax,
	double zmax, double r, double g, double b){
	p1.set(xmin, ymin, zmin);
	p2.set(xmax, ymax, zmax);
	cor.set(r,g,b);

}

Vec3<double> Caixa::getColor()
{
	return cor;
}

bool Caixa::intersection(Ray& r, Vec3<double>& normal, Vec3<double>& pi, float &t)
{
	double x, y, z;
	double dist = -1.0;

	if( r.Dr.getX() > 0 )
	{
		x = p1.getX();
		dist = ( ( p1.getX() - r.Or.getX() ) / r.Dr.getX() );
	}
	else
	{
		x = p2.getX();
		dist = ( ( p2.getX() - r.Or.getX() ) / r.Dr.getX() );
	}

	if( dist > 0 )
	{
		y = ( r.Or.getY() + ( dist * r.Dr.getY() ) ); 
		z = ( r.Or.getZ() + ( dist * r.Dr.getZ() ) ); 
        if( ( y >= p1.getY() ) && ( y <= p2.getY() ) && ( z >= p1.getZ() ) && ( z <= p2.getZ() ) ){
           if(dist < t){
				t = dist;
				return true;
		   }
		}
	}
	

	if( r.Dr.getY() > 0 )
	{
		y = p1.getY();
		dist = ( ( p1.getY() - r.Or.getY() ) / r.Dr.getY() );
	}
	else
	{
		y = p2.getY();
		dist = ( ( p1.getY() - r.Or.getY() ) / r.Dr.getY() );
	}
	
	if( dist > 0.0 )
	{
		x = ( r.Or.getX() + ( dist * r.Dr.getX() ) ); 
		z = ( r.Or.getZ() + ( dist * r.Dr.getZ() ) ); 
	    if( ( x >= p1.getX() ) && ( x <= p2.getX() ) && ( z >= p1.getZ() ) && ( z <= p2.getZ() ) ){
		   if(t > dist){
				t = dist;
				return true;
		   }
		}
	}

	
	if( r.Dr.getZ() > 0 )
	{
		z = p1.getZ();
		dist = ( (p1.getZ() - r.Or.getZ() ) / r.Dr.getZ() );
	}
	else
	{
		z = p2.getZ();
		dist = ( ( p2.getZ() - r.Or.getZ() ) / r.Dr.getZ() );
	}

	if( dist > 0 )
	{
		x = ( r.Or.getX() + ( dist * r.Dr.getX() ) ); 
		y = ( r.Or.getY() + ( dist * r.Dr.getY() ) ); 
	    if( ( x >= p1.getX() ) && ( x <= p2.getX() ) && ( y >= p1.getY() ) && ( y <= p2.getY() ) )	{
			if( t > dist){
				t =  dist;

				return true;
			}
		}
	}
	
	return false;
}