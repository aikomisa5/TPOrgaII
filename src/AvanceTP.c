#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototipo de la funcion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascararASM(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

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
	if (argc < 6)
	{
		printf("Faltaron argumentos.\n");
		return 1;
	}
	
	char *a = (char *)argv[1];
	char *b = (char *)argv[2];
	char *mask = (char *)argv[3];
	int ancho = atoi(argv[4]);
	int alto = atoi(argv[5]);
	int cant = ancho * alto * 3;

	//Inicializamos los buffers
	unsigned char *vectorAC = malloc(cant);
	unsigned char *vectorAAsm = malloc(cant);
	unsigned char *vectorB = malloc(cant);
	unsigned char *vectorMask = malloc(cant);
	

	//Abrir los archivos
	//abro los archivos rgb con FILE
	FILE *fpA = fopen(a, "rb");
	FILE *fpB = fopen(b, "rb");
	FILE *fpMask = fopen(mask, "rb");	

	if (fpA == NULL)
	{
		printf("No existe el archivo A");
		return 1;
	}
	if (fpB == NULL)
	{
		printf("No existe el arhivo B");
		return 1;
	}
	if (fpMask == NULL)
	{
		printf("No existe la mascara");
		return 1;
	}

	//Cargamos los buffers
	fread(vectorAC, sizeof *vectorAC, cant, fpA);
	fseek(fpA, 0, SEEK_SET);
	fread(vectorAAsm, sizeof *vectorAAsm, cant, fpA);
	fread(vectorB, sizeof *vectorB, cant, fpB);
	fread(vectorMask, sizeof *vectorMask, cant, fpMask);
	fclose(fpA);
	fclose(fpB);
	fclose(fpMask);


	// medir el tiempo inicial
	clock_t inicioC = clock();
	enmascarar_c(vectorAC, vectorB, vectorMask, cant);
	// medir el tiempo final
	clock_t finC = clock();
	double tiempoC = (double)(finC - inicioC) * 1000 / CLOCKS_PER_SEC;

	// medir el tiempo inicial
	clock_t inicioAsm = clock();
	enmascararASM(vectorAAsm, vectorB, vectorMask, cant);
	// medir el tiempo final
	clock_t finAsm = clock();
	double tiempoAsm = (double)(finAsm - inicioAsm) * 1000 / CLOCKS_PER_SEC;

	//Cargar resultados en archivos
	guardarResultadoEnArchivo("salida_c.rgb",vectorAC,cant);
	guardarResultadoEnArchivo("salida_asm.rgb",vectorAAsm,cant);
	

	//Liberar buffers
	free(vectorAC);
	free(vectorAAsm);
	free(vectorB);
	free(vectorMask);

	//imprimir resultados
	printf("%i B, C: %f ms, ASM: %f ms\n", cant, tiempoC, tiempoAsm);
	return 0;
}

// Implementacion
void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{
	int i;
	for (i = 0; i < cant; i++)
	{
		a[i] = mask[i] ? b[i] : a[i];
	}
}
