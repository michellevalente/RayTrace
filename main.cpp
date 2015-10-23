#include <iostream>
#include "Camera.h"
#include "Vec3.h"
#include "Object.h"
#include "image.h"
#define maxdepth 3

using namespace std;

bool sombra(Vec3<double> pi, Luz luz, Object ** objects, int numobj, int obj)
{
	Vec3<double> normal, pi2;
	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 30.0, 230.0, 400, 400);
	Ray r(luz.getPos() - pi, pi);
	for(int i = 0; i < numobj; i++)
	{
		if(i != obj)
			if((objects[i])->intersection(cam,r, normal, pi2))
				return true;
	}

	return false;
}

Vec3<double> shade(Vec3<double>& pi, Vec3<double>& normal, Camera& cam, Luz& luz, Object ** objects, int numObj, int obj, Vec3<double> luz_ambiente, int depth)
{
	Vec3<double> cor = objects[obj]->getColor(pi,luz, normal, cam);
	double fs;
	if(sombra(pi, luz, objects, numObj, obj))
		fs = 0.0;
	else
		fs = 1.0;
	cor *= fs;
	cor += luz_ambiente;

	if(depth >= maxdepth)
		return cor;

	if(objects[obj]->getMaterial().reflete())
		cout << "reflete" << endl;
	return cor;
}

Vec3<double> trace(Camera& cam, Luz& luz, Vec3<double> luz_ambiente, Object ** objects, int numObj, Ray& r, int depth)
{
	double maxDistance = 100000000000;
	int closest = -1;
	Vec3<double> background(0.4,0.4,0.4);
	Vec3<double> normal, pi;
	for(int i = 0; i < numObj;i++)
	{
		if((objects[i])->intersection(cam,r, normal, pi))
		{
			double distance = (pi - cam.getEye()).norm();
			if(distance < maxDistance){
				maxDistance = distance;
				closest = i;
			}
		}
	}

	if(closest != -1)
	{
		return shade(pi, normal, cam, luz, objects, numObj, closest, luz_ambiente, depth);
	}
	else
		return background;
}


int main(){

	const int width  = 400,
			  height = 400;

	Image * img = imgCreate (width, height, 3);

	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 30.0, 230.0, width, height);

	Vec3<double> luz_posicao(40,120,0);
	Vec3<double> luz_rgb(0.8,0.8,0.8);
	Vec3<double> luz_ambiente(0.1,0.1,0.1);
	Luz luz(luz_posicao, luz_rgb);
	int numObj = 3;
	Object* objects[numObj];
	Material material_caixa("yellow",0.7 ,0.7,0,1,1,1,40,0,1.1,0.4,"");
	Material material_esfera("blue",0.0 ,0,1.0,1,1,1,50,0,1.1,0.4,"");

	objects[0] = new Caixa(-80,-50,-50,50,-45,50,material_caixa);
	objects[1] = new Caixa(-80, -50, -60,50, 50, -50,material_caixa);
	objects[2] = new Esfera(0,20,0, 25, material_esfera);
	// Vec3<double> p1(30. , 0. , 0.);
	// Vec3<double> p2(0. , 0. ,0.);
	// Vec3<double> p3(0.  , 0. , 3.);
	// Triangulo triangulo(p1,p2,p3,1.0,0.0,0.0);
	

	for(int i = 0; i < height; i++)
	{

		for(int j = 0; j < width; j++)
		{
			Ray r = cam.camGetRay(i, j);
			Vec3<double> cor = trace(cam, luz, luz_ambiente, objects,numObj, r,0);
			imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());
		}	
	}

	imgWriteBMP((char* )"teste.bmp", img);
	return 1;

}