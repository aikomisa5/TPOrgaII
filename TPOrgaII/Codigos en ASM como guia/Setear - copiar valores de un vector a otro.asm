%include "io.inc"

section .data

vector db 1,2,3,4,5
vectorResultado db 0
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    
    MOV EDX,vector ;copio puntero de vector a EDX
    MOV EBX,0 ;inicializo EBX en 0 para desplazarme sobre el vector
    MOV ECX,5 ;inicializo ECX con la cantidad de valores, para poder iterar x veces
    LOPEAR:
    MOV AL,[EDX+EBX] ;copio el valor que se encuentra en la posicion EBX del vector en el registro de 8 bits AL
    MOV [vectorResultado+EBX],AL ;copio el valor de AL en la posicion EBX del vectorResultado
    ADD EBX,1     ;incremento EBX en 1 para desplazarme y leer valores de a 1 byte
    LOOP LOPEAR 
    
    ret