Michelle Valente - Raytrace

Compilar:

cd Source
make

Executar:

./raytrace arquivo.rt5 forma_de_textura

Arquivo.rt5: escolher o arquivo da cena. Se for usar os
arquivos da pasta Cenas, nao esquecer de colocar o caminho para a pasta
forma_de_textura: Escolher 1 ou 0. 1: textura por interpolacao, 
				  0: textura encontrada linearmente. 

Exemplo de execucao:
./raytrace ../Cenas/sphere_espelho.rt5 1


Resultado:
	Arquivo sera salvo como final.bmp na pasta Source.
	A parta Resultados contem algumas das imagens encontradas.