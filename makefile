raytracer: main.cpp image.o
	g++ -O2 -fopenmp -std=c++11 Camera.cpp Object.cpp Ray.cpp image.c main.cpp -o raytrace
