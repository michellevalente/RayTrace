#include <iostream>
#include "Camera.h"
#include "Vec3.h"
#include "Object.h"
#include "image.h"

using namespace std;



int main(){

	const int width  = 400,
			  height = 400;

	Image * img = imgCreate (width, height, 3);

	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 30.0, 230.0, width, height);

	Vec3<double> luz_posicao(60,120,40);
	Vec3<double> luz_rgb(0.8,0.8,0.8);
	Vec3<double> luz_ambiente(0.1,0.1,0.1);
	Luz luz(luz_posicao, luz_rgb);
	int numObj = 3;
	Object* objects[numObj];
	Material material_caixa("yellow",0.7 ,0.7,0,1,1,1,50,0,1.1,0.4,"");
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
			Vec3<double> normal;
			Vec3<double> pi;
			bool obj = false;
			for(int k = 0; k < numObj; k++)
			{

				if((objects[k])->intersection(cam,r, normal, pi))
				{
					Vec3<double> cor;

					//material_esfera.getFinalColor(pi, cor,50);

					double diffuse = objects[k]->calculateDiffuse(pi, luz, normal);
					double spec = objects[k]->calculateSpec(pi, luz, 
						normal, cam, objects[k]->getMaterial().getKs(), objects[k]->getMaterial().getCoefSpec());

					cor = ((luz.getRgb()).cross2(objects[k]->getMaterial().getKd()) * (diffuse)) ;
					cor += luz_ambiente;
					cor += ((luz.getRgb()).cross2(objects[k]->getMaterial().getKs()) * (spec));
					
	                imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());
	                obj = true;
				}
			}
			if(obj == false)
				imgSetPixel3f(img, i, j, 0.4, 0.4, 0.4);
		}	
	}

	imgWriteBMP((char* )"teste.bmp", img);
	return 1;

}