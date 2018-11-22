#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int tamanioOriginal = 512;
	int tamanioAnterior = 512;
	int cantidadTests = atoi(argv[1]);

	for (int i = 1 ; i<=cantidadTests ; i++)
	{
		printf("Test %i @ %ix%i :: ",i, tamanioAnterior, tamanioAnterior);
		char comando[256];
		snprintf(comando, sizeof comando, "main.exe 1.rgb 2.rgb mask.rgb %i %i", tamanioAnterior, tamanioAnterior);
		system(comando);
		int nuevoTamanio = tamanioOriginal+100*i;
		if (i != cantidadTests)
		{
			remove("salida_c.rgb");
			remove("salida_asm.rgb");
		snprintf(comando, sizeof comando, "gm mogrify -depth 8 -size %ix%i -resize %ix%i! *.rgb", tamanioAnterior, tamanioAnterior,nuevoTamanio,nuevoTamanio);
		system(comando);
		}
		tamanioAnterior = nuevoTamanio;
	}

	return 0;
}


