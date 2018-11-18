#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdlib>

int cantidad = 0;
char byte [8] ;
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
   	
   	char *a = (char *)argv[1];
	char *b = (char *)argv[2];
	char *mask = (char *)argv[3];
	char * d = (char *) argv[4];
  	int cant = atoi(d);
	//conversion a int con atoi
	//int cant = (int)argv[4];
    
	//llamada a metodo c
    enmascarar_c(a,b,mask,cant);
    
    printf("Cantidad de iteraciones cargadas en el contador: %d /n",contador);
    
    system("PAUSE");
    
    return 0;
    
}

// Implementacion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant){
	
	//Descomentar para probar realmente:
	cantidad = cant;
	
	//Descomentar solo para test lectura:
	//cantidad=11;
	
	//reservo espacio con malloc
	unsigned char * vectorA =  (unsigned char*)malloc(cantidad);
	unsigned char * vectorB =  (unsigned char*)malloc(cantidad);
	unsigned char * vectorMask =  (unsigned char*)malloc(cantidad);
	
	//abro los archivos rgb con FILE
	FILE * fpA = fopen (a, "rb");
	FILE * fpB = fopen (b, "rb");
	FILE * fpMask = fopen (mask, "rb");
	
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
		
		//one way..	
		unsigned char value = (vectorMask[i]);
		if (value ==  255 ){//0xFF 
			contador++;
			vectorA[i] = vectorB[i];
		}
	
	//alternativa segurn el profesor
	//*(vectorA+i) = 00;
	//vec = *(vectorA+i);
	//vec2 = &(vectorA+i);
	
	printf("El valor del caracter %d en hexa x (unsigned hexa integer)es: %x \n",i,vectorA[i]);
	
	//printf("El valor del caracter %d en c (char caracter) es: %c \n",i,*(vectorA+i));
	//printf("El valor del caracter %d en d (int con signo)es: %d \n",i,*(vectorA+i));
	//printf("El valor del caracter %d en s es: %s \n",i,*(vectorA+i));
	//printf("El valor del caracter %d en u (unsigned decimal integer) es: %u \n",i,*(vectorA+i));
	//printf("El valor del caracter %d en hexa x (unsigned hexa integer)es: %x \n",i,*(vectorA+i));
										
	}
	
	//fwrite(vectorA , 1 , cantidad , fpA);
		
   	fclose(fpA);
	fclose(fpB);	
	fclose(fpMask);

	free(vectorA);
	free(vectorB);
	free(vectorMask);
}


//Para usar como guia - No sirve
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
