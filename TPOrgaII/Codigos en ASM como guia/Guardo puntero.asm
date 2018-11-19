%include "io.inc"

section .data

vector db 1,2,3,4,5
vectorResultado db 0
puntero dd 0
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
   
    MOV EDX,vectorResultado ;copio puntero a vectorResultado en EDX
    MOV [puntero],EDX ;ACA!!!!!
    MOV EBX,0 ;inicializo EBX
    MOV ECX,5 ;inicializo ECX para cantidad de iteraciones
    MOV AL,0 ;incializo AL para hacer los set al vector
    LOPEAR:
    MOV [EDX+EBX],AL ;seteo en la posicion i del vectorResultado el valor de AL de 8 bits, es decir 1 byte
    ADD EBX,1 ;incremento EBX para desplazarme de a 1 byte
    ADD AL,1  ;incremento AL solo para setear un valor distinto del inicial
    LOOP LOPEAR
    
    ret