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

Vec3<double> shade(Scene scene, Vec3<double>& pi, Vec3<double>& normal, Camera& cam, Luz& luz, Object ** objects, int numObj, int obj, int depth)
{
	Vec3<double> cor = objects[obj]->getColor(pi,luz, normal, cam);
	double fs;
	if(sombra(pi, luz, objects, numObj, obj))
		fs = 0.0;
	else
		fs = 1.0;
	cor *= fs;
	cor += scene.getLuz();

	if(depth >= maxdepth)
		return cor;

	if(objects[obj]->getMaterial().reflete())
		cout << "reflete" << endl;
	return cor;
}

Vec3<double> trace(Camera& cam, Luz& luz, Scene scene, Object ** objects, int numObj, Ray& r, int depth)
{
	double maxDistance = 100000000000;
	int closest = -1;

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
		return shade(scene, pi, normal, cam, luz, objects, numObj, closest, depth);
	}
	else
		return scene.getBackground();
}


int main(){
	
	Scene scene(0,0.4,0.4,0.2,0.2,0.2,"");
	Camera cam(50, 70, 400, 0, 0, 150, 0, 1, 0, 90, 1, 100, 400, 400);
	Material blue("blue", 0.0, 0.2, 1, 0.2, 0.3, 1.0,  5,  0,  0,  1,  "");
	Material yellow("yellow", 0.8, 0.8, 0,   0.9, 0.9, 0.1,  5,  0,  0,  1,  "");
	Material shine_black("shine_black",  0, 0, 0,   1, 1, 1,  500,  0.6,  0,  1,  "");
	Material black("black", 0, 0, 0,   0, 0 ,0,  500,  0,  0,  1,  "");
	

	int width = cam.getW();
	int height = cam.getH();
	Image * img = imgCreate (width, height, 3);
	
	Luz luz(0, 400, 0, 0.8, 0.8, 0.8);
	int numObj = 4;
	Object* objects[numObj];
	objects[0] = new Esfera(blue, 50,100,0,150);
	objects[1] =  new Esfera(yellow,50,-100, 0, 150);
	objects[2] =new Caixa(shine_black,-300, -150, -250,   350, 200, -170);
	objects[3] =new Caixa( black,     -310, -160, -201,   360, 210, -171);
	
	// objects[3] = new Caixa()


	for(int i = 0; i < height; i++)
	{

		for(int j = 0; j < width; j++)
		{
			Ray r = cam.camGetRay(i, j);
			Vec3<double> cor = trace(cam, luz, scene, objects,numObj, r,0);
			imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());
		}	
	}

	imgWriteBMP((char* )"teste.bmp", img);
	return 1;

}