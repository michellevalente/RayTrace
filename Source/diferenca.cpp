#include <cstdio>
#include "image.h"

int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		printf("Entre com o nome das duas imagens\n");
	}
	Image * img1 = imgReadBMP(argv[1]);
	Image * img2 = imgReadBMP(argv[2]);
	
	imgDif(img1, img2, 1);
	imgWriteBMP("diferenca.bmp",img1 );
	imgDestroy(img1);
	imgDestroy(img2);
	// imgDestroy(dif);

	return 0;
}