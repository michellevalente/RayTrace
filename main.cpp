#include <iostream>
#include <fstream>
#include <vector>
#include "Camera.h"
#include "Vec3.h"
#include "Object.h"
#include "image.h"
#define maxdepth 3

using namespace std;

Scene * scene;
Camera * cam;
vector<Material *> mat;
vector<Luz *> luz;
vector<Object *> objects;

int findMaterial(std::string nome)
{
	for(int i = 0; i < mat.size(); i++)
	{
		if(mat[i]->getNome() == nome)
			return i;
	}
}

void readRt5(std::string file)
{
	ifstream in(file);
	string line;
	in >> line >> line;

	while(in >> line)  
	{
		if(line == "SCENE")
		{
			double rf, gf, bf, rl, gl, bl;
			string textura;
			in >> rf >> gf >> bf >> rl >> gl >> bl >> textura;
			Scene * s= new Scene(rf,gf,bf,rl,gl,bl,textura);
			scene = s;
		}
		if(line == "CAMERA")
		{
			double eyex, eyey,  eyez,  atx,  aty, 
        	 atz, upx,  upy,  upz,  fovy, 
             near,  far,  wp,  hp ;
             in >> eyex >> eyey >> eyez >> atx >> aty >> atz >> upx >> 
             upy >> upz >> fovy >> near >> far >> wp >> hp;

             Camera * camera = new Camera(eyex, eyey,  eyez,  atx,  aty, 
        	 atz, upx,  upy,  upz,  fovy, 
             near,  far,  wp,  hp);
             cam = camera;
		}

		if(line == "MATERIAL")
		{
			string nome, textura;
			double kdx, kdy,  kdz,  ksx, 
			 ksy,  ksz,  coef_spec , coef_reflexao,
			 indice_refracao,  opacidade; 

			 in >> nome >> kdx >> kdy >> kdz>> ksx >> ksy >> ksz >> 
			 coef_spec >> coef_reflexao >> indice_refracao >> opacidade >> textura;

			 Material * material = new Material(nome,kdx, kdy,  kdz,  ksx, 
			 ksy,  ksz,  coef_spec , coef_reflexao,
			 indice_refracao,  opacidade, textura );

			 mat.push_back(material);
		}
		if(line == "LIGHT")
		{
			double px,  py,  pz,  r,  g,  b;
			in >> px >>  py >>  pz >>  r >>  g >>  b;

			Luz * l = new Luz( px,  py,  pz,  r,  g,  b);
			luz.push_back(l);
		}

		if(line == "SPHERE")
		{
			string mat;
			double raio,  px, py,  pz;
			in >> mat >> raio >> px >> py >> pz;
			Esfera * e = new Esfera(mat, raio, px, py, pz);
			objects.push_back(e);

		}
		if(line == "BOX")
		{
			std::string material;
			double xmin,  ymin,  zmin,  xmax,  ymax,  zmax;
			in >> material >> xmin >>  ymin >> zmin >> xmax >> ymax >> zmax;
			Caixa * c = new Caixa(material, xmin,  ymin,  zmin,  xmax,  ymax,  zmax);
			objects.push_back(c);
		}
	}


}
bool sombra(Vec3<double>& pi, vector<Luz*>& luz, int obj)
{
	Vec3<double> normal, pi2;
	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 30.0, 230.0, 400, 400);

	int sombra = 0;
	
	for(int k = 0 ; k < luz.size(); k++)
	{
		Ray r(luz[k]->getPos() - pi, pi);
		for(int i = 0; i < objects.size(); i++)
		{
			if(i != obj)
				if((objects[i])->intersection(cam,r, normal, pi2))
					sombra++;
		}
	}
	

	if(sombra == luz.size())
		return true;
	else
		return false;
}

Vec3<double> shade(Vec3<double>& pi, Vec3<double>& normal, int obj, int depth)
{

	int idx = findMaterial(objects[obj]->getMaterial());
	Vec3<double> cor = objects[obj]->getColor(pi,luz, normal, *cam, *mat[idx]);
	double fs;
	if(sombra(pi, luz, obj))
		fs = 0.0;
	else
		fs = 1.0;
	cor *= fs;
	Vec3<double> luz_ambiente(0.1,0.1,0.1);
	cor += luz_ambiente;

	if(depth >= maxdepth)
		return cor;

	// if(objects[obj]->getMaterial().reflete())
	// 	cout << "reflete" << endl;
	return cor;
}

Vec3<double> trace(Ray& r, int depth)
{
	double maxDistance = 100000000000;
	int closest = -1;

	Vec3<double> normal, pi;
	for(int i = 0; i < objects.size();i++)
	{
		if((objects[i])->intersection(*cam,r, normal, pi))
		{
			return shade(pi, normal, i, depth);
		}
	}

	// if(closest != -1)
	// {
	// 	return shade(pi, normal,objects, numObj, closest, depth);
	// }
	// else
		return scene->getBackground();
}


int main(){
	
	readRt5("../../cenasSimplesRT4/pool.rt5");
	int width = cam->getW();
	int height = cam->getH();
	Image * img = imgCreate (width, height, 3);
	

	for(int i = 0; i < height; i++)
	{

		for(int j = 0; j < width; j++)
		{
			Ray r = cam->camGetRay(i, j);
			Vec3<double> cor = trace(r,0);
			imgSetPixel3f(img, i, j, cor.getX(), cor.getY(), cor.getZ());
		}	
	}

	imgWriteBMP((char* )"teste.bmp", img);
	return 1;

}