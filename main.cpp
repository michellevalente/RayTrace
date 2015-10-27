#include <iostream>
#include <fstream>
#include <vector>
#include "Camera.h"
#include "Vec3.h"
#include "Object.h"
#include "image.h"
#include "Timer.h"
#define maxdepth 10
#define EPSILON	1.0e-1

using namespace std;

Scene * scene;
Camera * cam;
vector<Material *> mat;
vector<Luz *> luz;
vector<Object *> objects;

//Vec3<double> trace(Ray& r, int depth);
Vec3<double> trace(Ray& r, int depth, bool linear = false);


float mix(const float &a, const float &b, const float &mix)
{
return b * mix + a * (1 - mix);
} 

int findMaterial(std::string nome)
{
	for(int i = 0; i < mat.size(); i++)
	{
		if(mat[i]->getNome() == nome)
			return i;
	}
	return -1;
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

		if(line == "TRIANGLE")
		{
			std::string material;
			double p1x,  p1y,  p1z,  p2x, 
			 p2y,  p2z,  p3x,  p3y, 
			 p3z, u1, u2, u3, v1, v2, v3;
			 in >> material >> p1x >> p1y >> p1z >> p2x >> p2y >> p2z >> p3x
			 >> p3y >> p3z >> u1 >> v1 >> u2 >> v2 >> u3 >> v3;
			 Triangulo * t = new Triangulo(material,p1x,  p1y,  p1z,  p2x, 
			 p2y,  p2z,  p3x,  p3y, p3z, u1, v1, u2, v2, u3, v3 );
			 objects.push_back(t);
		}
	}


}
bool sombra(Vec3<double>& pi, Luz * luz, int obj)
{
	Vec3<double> normal, pi2;
	Camera cam(100,40,40,0,0,0,0,1,0,90.0, 30.0, 230.0, 400, 400);

	int sombra = 0;
	double distance;
	double max_distance = (luz->getPos() - pi).norm();

	Ray r(luz->getPos() - pi, pi);
	for(int i = 0; i < objects.size(); i++)
	{
		if(i != obj)
			if((objects[i])->intersection(cam,r, normal, pi2, distance))
				sombra++;
	}

	

	if(sombra > 0)
		return true;
	else
		return false;
}



Vec3<double> shade(Vec3<double>& pi, Vec3<double>& normal, int obj, int depth, Ray r, bool linear = false)
{
	int idx = findMaterial(objects[obj]->getMaterial());
	Vec3<double> kd;

	if(mat[idx]->getTextura() == "null")
		kd = mat[idx]->getKd();
	else
		objects[obj]->getTextura(mat[idx]->getFileTextura(), pi, kd, normal, linear);

	Vec3<double> cor; 
	Vec3<double> cor2;
	
	for(int i = 0 ; i < luz.size(); i++)
	{
		Vec3<double> temp = luz[i]->getPos() - pi;
		double L = (temp).norm();
		if(L > 0.0)
		{
			if(!sombra(pi, luz[i], obj)){
				Vec3<double> cor3 = objects[obj]->getColor(pi,*luz[i], normal, *cam, *mat[idx], kd);
				cor2 += cor3;
			}
			
		}
	}

	cor += cor2;

	if(depth >= maxdepth)
		return cor;

	if(mat[idx]->reflete())
	{
		Vec3<double> v = (cam->getEye() - pi).normalized();
		Vec3<double> rr = 2* ((v.dot(normal)) * normal) - v;
		pi = pi + EPSILON * rr;
		Ray r2(rr, pi);
		Vec3<double> rColor = trace(r2,depth + 1, linear);
		cor += mat[idx]->getK() * rColor;
	}

	if(mat[idx]->transparente())
	{
		// Vec3<double> v = (cam->getEye() - pi).normalized();
		// Vec3<double> vt = (v.dot(normal) * normal) - v;	
		// double s = vt.norm();
		// double st = 1 * s / mat[idx]->getN();
		// double ct = sqrt(1 - st * st);
		// Vec3<double> rt = st * vt.normalized() + ct * (-1* normal);
		pi = pi + EPSILON * r.Dr;

		Ray r2(r.Dr, pi);
		Vec3<double> tColor = trace(r2,depth + 1,linear);
		cor += (1 - mat[idx]->getO()) * tColor;
	}

	//if (depth == 1)
		return (cor + scene->getLuz().cross2(kd));
	return cor;
}

Vec3<double> trace(Ray& r, int depth, bool linear )
{
	double closest = 1234567;
	int id_closest = -1;
	double distance;
	Vec3<double> normal, pi;
	Vec3<double> closest_normal, closest_pi;

	for(int i = 0; i < objects.size();i++)
	{
		//if (i == obj)
		//	continue;
		if((objects[i])->intersection(*cam,r, normal, pi, distance))
		{
			if(distance > EPSILON && distance < closest)
			{
				closest = distance;
				id_closest = i;
				closest_normal = normal;
				closest_pi = pi;
			}
		}
	}

	if(id_closest != -1)
	{
		return shade(closest_pi, closest_normal, id_closest, depth,r, linear);
	}
	else
		return scene->getBackground();
}

double getMaior(Vec3<double> cor)
{
	if(cor.getX() > cor.getY() && cor.getX() > cor.getZ())
		return cor.getX();
	if(cor.getZ() > cor.getY() && cor.getZ() > cor.getX())
		return cor.getZ();
	else
		return cor.getY();
}

int main(int argc, char ** argv){
	
	if(argc < 3)
	{
		cout << "Entrar arquivo e tipo de textura" << endl;
		return 0;
	}
	int linear = atoi(argv[2]);
	readRt5(argv[1]);
	int width = cam->getW();
	int height = cam->getH();
	Image * img = imgCreate (width, height, 3);
	float * buf = imgGetData(img);
	Timer t;
	#pragma omp parallel for
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			Ray r = cam->camGetRay(i, j);
			Vec3<double> cor = trace(r,1,linear);
			int pos = (j*width*3) + (i*3);
			if(cor.getX() > 1 || cor.getY() > 1 || cor.getZ() > 1)
			{
				double maior = getMaior(cor);
				cor /= maior;
			}
			buf[pos + 0] = cor.getX();
			buf[pos + 1] = cor.getY();
			buf[pos + 2] = cor.getZ();		
		}	
	}
	double t2 = t.elapsed();
	cout << t2 << endl;
	imgWriteBMP((char* )"novo3.bmp", img);
	return 1;

}