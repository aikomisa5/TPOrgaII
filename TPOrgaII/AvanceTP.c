#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdlib>

int cantidad = 0;
char byte [8] ;
//char myarray[4] = "abc";
char vec[750000];
int contador = 0;

// Prototipo de la funcion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

//argc -> entero -> contiene el número de argumentos que se han introducido.
//argv -> array -> array de punteros a caracteres.

int main(int argc, char *argv[]) {
	
	int i = 0;
    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    //return 0;
    
	printf("Program name %s\n", argv[0]);
 
   	if( argc == 5 ) {
      printf("Se ingresaron todos los argumentos \n");
   	}
   	else if ( argc<5){
      printf("Faltaron argumentos.\n");
   	}
   	else{
      printf("Se ingresaron argumentos de mas.\n");
   	}
   	
   	unsigned char *a = (char *)argv[1];
	unsigned char *b = (char *)argv[2];
	unsigned char *mask = (char *)argv[3];
	char * d = (char *) argv[4];
  	int cant = atoi(d);
	//int cant = (int)argv[4];
    
    enmascarar_c(a,b,mask,cant);
    
    printf("El contador es: %d /n",contador);
    
    system("PAUSE");
    
    return 0;
    
	//int c = suma2(4, 5);
	//printf("4 + 5 = %d\n", c);
}

// Implementacion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant){
	/*
	//tomo las rutas
	char * fileA [100] = &(a); 
	char fileB [100] = *(b);
	char fileMask [100] = *(mask);
	*/
	
	cantidad = cant;
	
	char * vectorA =  (char*)malloc(cantidad);
	char * vectorB =  (char*)malloc(cantidad);
	char * vectorMask =  (char*)malloc(cantidad);
	
	//strcpy(vec,vectorA);
	
	//reservo espacio para los vectores
	//a	= (char*)malloc(cantidad);
	//b 	= (char*)malloc(cantidad);
	//mask 	= (char*)malloc(cantidad);
	
	char aa [100];
	strcpy(aa,a);
	
	printf("El valor de a es: %s \n",aa);
	
	//abro los archivos
	FILE * fpA = fopen (a, "r+");
	FILE * fpB = fopen (b, "r+");
	FILE * fpMask = fopen (mask, "r+");
	
	//copio el dato de los archivos al espacio reservado
	fgets(vectorA, cantidad, fpA);
	fgets(vectorB, cantidad, fpB);
	fgets(vectorMask, cantidad, fpMask);
	
	printf("Imprimo el valor del vector: %s \n",vec);
	printf("Imprimo el valor del vector: %s \n",vectorA);
	printf("Imprimo el valor del vectorB: %s \n",vectorB);
	printf("Imprimo el valor del vectorM: %s \n",vectorMask);
	
	int i;
	int z = 0;
	for (i = 0; i<cantidad ; i++){
		/*if (i%8 == 0){
			
			//printf("El valor de byte es: %s \n" , byte);
			
			if (byte == "000000"){
			printf("MATCHEO 1 \n");
			}
			else if (byte == "00000000"){
			printf("MATCHEO 2\n");
			}
			
			char vacio[] = "";
			strcpy(byte,vacio);
			z=0;
		}
		
		byte[z] = *(vectorMask+i);
		
		printf("Valor de byte: %d \n",*(vectorMask+i));
		printf("Valor de ARRAY BYTE: %d \n", byte);
		
		z++;
		
		if (i == 10){
			system("PAUSE");
		}
		
		//if (*(vectorMask+i) == "000000"){
		//|| *(vectorMask+i) == "FFFFFF"){
		
		*/
		
	/*	int value = (int)*(vectorMask+i);
		if (value == 0){
			contador++;
			*(vectorA+i) = *(vectorB+i);
		}
	*/
	
	*(vectorA+i) = 00;
				
	}
	
	//fputs(vectorA,fpA);
	fwrite(vectorA , 1 , cantidad , fpA);

   	fclose(fpA);
	fclose(fpB);	
	fclose(fpMask);

	free(vectorA);
	free(vectorB);
	free(vectorMask);
}

/*
void crearSecuencia (int *vector, int inicial, int incremento, int cantidad){
	vector 	= (int*)malloc(sizeof(int) * cantidad);
	
	for (int i = 0; i< cantidad; i++){
		*(vector + i) = inicial;
		inicial += incremento;
		printf("Valor: %d \t",*(vector + i));
	}	
	printf("\n");
	
	free(vector);
}*/

//int suma2(int a, int b) {
//int c;
//c = a + b;
//return c;
//}
