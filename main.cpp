#include <iostream>
#include "Camera.h"
#include "Vec3.h"
#include "Object.h"
#include "image.h"

using namespace std;

int main(){
	// Image dimensions
	const int width  = 400,
			  height = 400;

	Image * img = imgCreate (width, height, 3);

	double image[width * height * 3];

    Vec3<double> eye(100, 40, 40 );
    Vec3<double> at(0, 0, 0);
    Vec3<double> up(0, 1, 0);

	Camera cam(eye, at,up, 90.0, 10.0, 100.0, width, height);

	Vec3<double> posicao_esfera(0,20,0);
	Esfera esfera(posicao_esfera, 50,1.0,0,0);

	Vec3<double> luz_posicao(40,120,20);
	Vec3<double> luz_rgb(1,1,1);
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
				Vec3<double> vl = ( luz_posicao- pi );
				vl = vl.normalized();
				double diffuse = normal.dot(vl);
				cout << "diffuse: " << diffuse << endl;
				//cor = (luz.getRgb()).cross2(cor) * diffuse;
				
                imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());


			}else
			{
				imgSetPixel3f(img, i, j, 0.0, 0.0, 0.0);
			}
		}
	}

	imgWriteBMP((char* )"teste.bpm", img);
	return 1;

}