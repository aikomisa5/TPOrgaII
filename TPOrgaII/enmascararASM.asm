global _enmascararASM
;%include "io.inc"

section .data
;vectorA db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
;vectorB db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
;vectorMask db 0 ;lo utilizamos como vector de valores de tamaño de 1 byte
cantidad dd 0 ;cantidad de tamaño int, es decir 4 bytes
;resultadoPuntero dd 0 ;OJO! es un puntero, los punteros tienen tamano de 4 bytes
;lo declaramos asi porque vamos a setear los valores del vector resultado directo a la posicion de memoria
;que nos especifica el puntero que viene como argumento
;se declara diferente a vectorA, vectorB, vectorMask, porque aca en ningun momento necesitamos setear algo
;directamente en las posiciones de memoria de dichos vectores, sino que lo unico que necesitamos son leer los
;valores. No olvidar que lo que viene como argumento son punteros
;Y en realidad vectorA, vectorB y vectorMask son etiquetas que apuntan a una posicion de memoria, y para lo
;unico que sirve es para saber donde esta el valor inicial, y a partir de ahi nos vamos desplazando de a 1 byte
;al fin y al cabo acá vectorA,vectorB,vectorMask actuarian como punteros

unos times 32 db (255) ;64 valores de 1 byte seteados en 255
ceros times 32 db (0) ;64 valores de 1 byte seteados en 0
;variable db 255

section .text

_enmascararASM:
  
  PUSH EBP
  MOV EBP,ESP  
  
  cargoCantidad:
  MOV EDX,[EBP+20] ;puntero a cantidad
  MOV [cantidad],EDX
  
  MOV EBX,0
  
  ciclar:
  
  cargoA: 
  MOV EDX,[EBP+8] ;puntero a imagen A
  MOVD XMM6,dword[EDX+EBX]
    
  cargoB:
  MOV EDX,[EBP+12] ;puntero a imagen B
  MOVD XMM5,dword[EDX+EBX]
    
  cargoMask:
  MOV EDX,[EBP+16] ;puntero a imagen C
  MOVD XMM4,dword[EDX+EBX]
       
  ;No borrar
  MOVD XMM7,[unos]        
   
  ;MOVQ MM0,[vectorMask+EBX]
  ;MOVQ MM1,[vectorA+EBX]
  ;MOVQ MM2,[vectorB+EBX]  
  ;MOVQ MM3,[vectorResultadoPuntero+EBX] ;en definitiva esto esta cargando todos ceros porque el vector al que apunta el puntero esta vacio
  MOVD XMM3,[ceros] ;en cada iteracion cargamos ceros en MM3
  
  PAND XMM6,XMM4 ;aplicamos mascara a vectorA
  PANDN XMM4,XMM7 ;invertimos mascara
  PAND XMM5,XMM4 ;aplicamos mascara a vectorB
  ;PXOR MM3,MM3 ;inicializamos vector resultado en 0 NO LO NECESITAMOS MAS!
  POR  XMM3,XMM6 ;cargamos vectorA en vector resultado
  POR  XMM3,XMM5 ;cargamos vectorB en vector resultado

  copiarResultado:

  MOV EDX,[EBP+24] ;puntero a resultado
  MOVD [EDX + EBX], XMM3 ;COPIO EL RESULTADO AL VECTOR
                      ;EN LA POSICION INDICADA
                      
  ADD EBX,4 ;nos desplazamos de a 32 bits 
  CMP EBX,[cantidad]
  JL ciclar
  
  exit:
  
  MOV ESP,EBP
  POP EBP   
   
  ret