global _enmascarar_asm
;%include "io.inc"

section .data
vectorA db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
vectorB db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
vectorMask db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
cantidad dd 0 ;cantidad de tamaño int, es decir 4 bytes
vectorResultadoPuntero dd 0 ;OJO! es un puntero, los punteros tienen tamano de 4 bytes
;lo declaramos asi porque vamos a setear los valores del vector resultado directo a la posicion de memoria
;que nos especifica el puntero que viene como argumento
;se declara diferente a vectorA, vectorB, vectorMask, porque aca en ningun momento necesitamos setear algo
;directamente en las posiciones de memoria de dichos vectores, sino que lo unico que necesitamos son leer los
;valores. No olvidar que lo que viene como argumento son punteros
;Y en realidad vectorA, vectorB y vectorMask son etiquetas que apuntan a una posicion de memoria, y para lo
;unico que sirve es para saber donde esta el valor inicial, y a partir de ahi nos vamos desplazando de a 1 byte
;al fin y al cabo acá vectorA,vectorB,vectorMask actuarian como punteros

unos times 64 db (255) ;64 valores de 1 byte seteados en 255
ceros times 64 db (0) ;64 valores de 1 byte seteados en 0
;variable db 255

section .text

_enmascarar_asm:
  
  PUSH EBP
  MOV EBP,ESP  
  
  cargoA: 
  MOV EDX,[ESP+8] ;puntero a imagen A
  ;MOV [vectorA],EDX 
  MOV EBX,0
  MOV ECX,[cantidad]
  iterarSobreA:
  MOV AL,[EDX+EBX]
  MOV [vectorA+EBX],AL
  ADD EBX,1 
  LOOP iterarSobreA
  
  cargoB:
  MOV EDX,[ESP+12] ;puntero a imagen B
  ;MOV [vectorB],EDX
  MOV EBX,0 ;reinicializo EBX el cual quedo con el valor de cantidad
  MOV ECX,[cantidad] ;reinicializo ECX, el cual quedo en 0
  iterarSobreB:
  MOV AL,[EDX+EBX]
  MOV [vectorB+EBX],AL
  ADD EBX,1 
  LOOP iterarSobreB
    
  cargoMask:
  MOV EDX,[ESP+16] ;puntero a imagen C
  ;MOV [vectorMask],EDX
  MOV EBX,0 ;reinicializo EBX el cual quedo con el valor de cantidad
  MOV ECX,[cantidad] ;reinicializo ECX, el cual quedo en 0
  iterarSobreMask:
  MOV AL,[EDX+EBX]
  MOV [vectorMask+EBX],AL
  ADD EBX,1 
  LOOP iterarSobreMask
    
  cargoCantidad:
  MOV EDX,[ESP+20] ;puntero a cantidad
  MOV [cantidad],EDX
  
  guardoPunteroAVectorResultado:
  MOV EDX,[ESP+24] ;puntero a resultado
  MOV [vectorResultadoPuntero],EDX 
  
  MOV ECX, [cantidad]
  
  ;to delete
  MOV ECX,1 ;OJO! BORRAR ANTES DE COMPILAR
  
  ;No borrar
  MOVQ MM7,[unos]        
  MOV EBX,0  ;inicializo EBX
  
  LOOPER:
   
  MOVQ MM0,[vectorMask+EBX]
  MOVQ MM1,[vectorA+EBX]
  MOVQ MM2,[vectorB+EBX]  
  ;MOVQ MM3,[vectorResultadoPuntero+EBX] ;en definitiva esto esta cargando todos ceros porque el vector al que apunta el puntero esta vacio
  MOVQ MM3,[ceros] ;en cada iteracion cargamos ceros en MM3
  
  ;PAND MM1,MM0 ;aplicamos mascara a vectorA
  ;PANDN MM0,MM7 ;invertimos mascara
  ;PAND MM2,MM0 ;aplicamos mascara a vectorB
  
  ;PXOR MM3,MM3 ;inicializamos vector resultado en 0 NO LO NECESITAMOS MAS!
  
  ;POR  MM3,MM1 ;cargamos vectorA en vector resultado
  ;POR  MM3,MM2 ;cargamos vectorB en vector resultado
  
  
  ;MOVQ [vectorResultado+EBX], MM1 ;No usar
  ;ADD EBX,1 ;No usar
  MOVQ [vectorResultadoPuntero+EBX], MM1 ;seteamos 64 bits a partir de la posicion en memoria vectorResultadoPuntero+EBX
  ADD EBX,64 ;nos desplazamos de a 64 bits porque los registro MMX son de tamano 64 bits
  LOOP LOOPER
  MOV ESP,EBP
  POP EBP   
   
  ret