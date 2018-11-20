#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipo de la funcion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant, unsigned char *resultado);

int main(int argc, char *argv[])
{

	int i = 0;
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	printf("Program name %s\n", argv[0]);

	if (argc == 5)
	{
		printf("Se ingresaron todos los argumentos \n");
	}
	else if (argc < 5)
	{
		printf("Faltaron argumentos.\n");
	}
	else
	{
		printf("Se ingresaron argumentos de mas.\n");
	}

	char *a = (char *)argv[1];
	char *b = (char *)argv[2];
	char *mask = (char *)argv[3];
	char *d = (char *)argv[4];
	int cant = atoi(d);

	printf("\n\nCantidad de bytes a procesar: %d\n", cant);
	printf("Ruta a imagen 1:  %s\n", a);
	printf("Ruta a imagen 2:  %s\n", b);
	printf("Ruta a mascara :  %s\n", mask);
	printf("cantidad :  %d\n\n", cant);

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
	FILE *fpResultadoC = fopen("salida_c.rgb", "wb");
	FILE *fpResultadoASM = fopen("salida_asm.rgb", "wb");
	if (!fpResultadoC)
	{
		printf("No se pudo crear archivo de destino\n");
	}
	if (!fpResultadoASM)
	{
		printf("No se pudo crear archivo de destino\n");
	}

	if (fpA == NULL)
	{
		printf("file A doesnt exist!");
	}
	if (fpB == NULL)
	{
		printf("file B doesnt exist!");
	}
	if (fpMask == NULL)
	{
		printf("file Mask doesnt exist!");
	}

	//Cargamos los buffers
	fread(vectorAC, sizeof *vectorAC, cant, fpA);
	fread(vectorAAsm, sizeof *vectorAAsm, cant, fpA);
	fread(vectorB, sizeof *vectorB, cant, fpB);
	fread(vectorMask, sizeof *vectorMask, cant, fpMask);

	// medir el tiempo inicial

	enmascarar_c(vectorAC, vectorB, vectorMask, cant);
	// medir el tiempo final

	// medir el tiempo inicial
	//enmascarar_asm(vectorA, vectorB, vectorMask, cant, resultadoASM);
	// medir el tiempo final

	//Cargar resultados en archivos
	fwrite(vectorAC, 1, cant, fpResultadoC);
	fwrite(vectorAAsm, 1, cant, fpResultadoASM);
	//Cerrar Archivos
	fclose(fpA);
	fclose(fpB);
	fclose(fpMask);
	fclose(fpResultadoC);
	fclose(fpResultadoASM);

	//Liberar buffers
	free(vectorAC);
	free(vectorAAsm);
	free(vectorB);
	free(vectorMask);
	system("PAUSE");

	return 0;
}

// Implementacion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{

	int i;
	for (i = 0; i < cant; i++)
	{
		a[i] = mask[i] ? a[i] : b[i];
	}

	printf("iteraciones hechas :  %d\n\n", i);
}
