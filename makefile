raytracer: main.cpp image.o
	g++ -std=c++11 Camera.cpp Object.cpp Ray.cpp image.c main.cpp -o raytrace
