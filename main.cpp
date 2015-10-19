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

	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 10.0, 100.0, width, height);

	Esfera esfera(0,20,0, 50,1.0,0.0,0);

	Vec3<double> luz_posicao(40,120,20);
	Vec3<double> luz_rgb(1,1,1);
	Vec3<double> luz_ambiente(0.05,0.05,0.05);
	Luz luz(luz_posicao, luz_rgb);

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Ray r = cam.camGetRay(i, j);
			Vec3<double> normal;
			Vec3<double> pi;

			if(esfera.intersection(cam,r, normal, pi))
			{
				Vec3<double> cor = esfera.getColor();
				Vec3<double> vl = ( luz_posicao - pi );
				vl = vl.normalized();
				Vec3<double> rl = ((2*(vl.dot(normal)))*normal )- vl;
				Vec3<double> ve = (cam.getPos() - pi);
				//double reflexao = max(rl.dot(ve),0.0);
				//reflexao*=reflexao;

			
				double diffuse = max(normal.dot(vl), 0.0);
				cor = ((luz.getRgb()).cross2(cor) * (diffuse)) ;
				cor += luz_ambiente;
				//cor += ((luz.getRgb()).cross2(cor) * (reflexao));
				
				
                imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());


			}else
			{
				imgSetPixel3f(img, i, j, 0.0, 0.0, 0.0);
			}
		}
	}

	imgWriteBMP((char* )"teste.bmp", img);
	return 1;

}