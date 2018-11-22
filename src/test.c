#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funciones auxiliares
void guardarResultadoEnArchivo(char *nombreArchivo, unsigned char *buffer, int cant){
	FILE *fpFile = fopen(nombreArchivo, "wb");
	if (!fpFile)
	{
		printf("No se pudo crear archivo de destino \"%s\"\n", nombreArchivo);
	}
	fwrite(buffer, 1, cant, fpFile);
	fclose(fpFile);
}

int main(int argc, char *argv[])
{
	
	int tamanio = 512;
	int cantidadTests = atoi(argv[1]);

	for (int i = 1 ; i<=cantidadTests ; i++){
		printf("Test %i @%ix%i: ",i, tamanio, tamanio);
		char comando[256];
		snprintf(comando, sizeof comando, "main.exe 1.rgb 2.rgb mask.rgb %i %i", tamanio, tamanio);
		system(comando);
		int nuevoTamanio =tamanio+(100*i);
		remove("salida_c.rgb");
		remove("salida_asm.rgb");
		snprintf(comando, sizeof comando, "gm mogrify -depth 8 -size %ix%i -resize %ix%i! *.rgb", tamanio, tamanio,nuevoTamanio,nuevoTamanio);
		system(comando);
		tamanio = nuevoTamanio;
	}

	return 0;
}


