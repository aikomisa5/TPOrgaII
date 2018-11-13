#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdlib>

int cantidad = 0;
char byte [8] ;
//char myarray[4] = "abc";
int vec[1000];
int vec2[100];
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
   	
   	unsigned char *a = (unsigned char *)argv[1];
	unsigned char *b = (unsigned char *)argv[2];
	unsigned char *mask = (unsigned char *)argv[3];
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
	
	//cantidad = cant;
	cantidad=10;
	
	unsigned char * vectorA =  (unsigned char*)malloc(cantidad);
	unsigned char * vectorB =  (unsigned char*)malloc(cantidad);
	unsigned char * vectorMask =  (unsigned char*)malloc(cantidad);
	
	//abro los archivos
	FILE * fpA = fopen (a, "r+");
	FILE * fpB = fopen (b, "r+");
	FILE * fpMask = fopen (mask, "r+");
	
	if (fpA==NULL){
        printf("file A doesnt exist!");
        //return 1;
    }
    if (fpB==NULL){
        printf("file B doesnt exist!");
        //return 1;
    }
    if (fpMask==NULL){
        printf("file Mask doesnt exist!");
        //return 1;
    }
	
	//copio el dato de los archivos al espacio reservado
	fgets(vectorA, cantidad, fpA);
	fgets(vectorB, cantidad, fpB);
	fgets(vectorMask, cantidad, fpMask);
	
	printf("Imprimo el valor del vectorA: %s \n",vectorA);
	//printf("Imprimo el valor del vectorB: %s \n",vectorB);
	//printf("Imprimo el valor del vectorM: %s \n",vectorMask);
	
	
	//int z = 0;
	int i;
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
	
	//*(vectorA+i) = 00;
	//vec = *(vectorA+i);
	//vec2 = &(vectorA+i);
	
	printf("El valor del caracter %d en c es: %c \n",i,*(vectorA+i));
	printf("El valor del caracter %d en d es: %d \n",i,*(vectorA+i));
	//printf("El valor del caracter %d en s es: %s \n",i,*(vectorA+i));
	printf("El valor del caracter %d en u es: %u \n",i,*(vectorA+i));
	printf("El valor del caracter %d en x es: %x \n",i,*(vectorA+i));
										
	}
	
	//fputs(vectorA,fpA);
	//fwrite(vectorA , 1 , cantidad , fpA);
	
	printf("Array elements are\n");
	for(i=0;i<10;i++)
		printf("Decimal: %d, Hex: %X\n",vec[i],vec[i]);
	
	printf("Array2 elements are\n");
	for(i=0;i<10;i++)
		printf("Decimal: %d, Hex: %X\n",vec2[i],vec2[i]);	
	
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
