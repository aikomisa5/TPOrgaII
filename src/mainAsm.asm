global _enmascararASM

section .data
cantidad dd 0 ;cantidad de tama�o int, es decir 4 bytes
;resultadoPuntero dd 0 ;OJO! es un puntero, los punteros tienen tamano de 4 bytes
;lo declaramos asi porque vamos a setear los valores del vector resultado directo a la posicion de memoria
;que nos especifica el puntero que viene como argumento


unos times 128 db (255) ;32 valores de 1 byte seteados en 255
ceros times 128 db (0) ;32 valores de 1 byte seteados en 0

section .text

_enmascararASM:
  
  PUSH EBP
  MOV EBP,ESP  
  
  cargoCantidad:
  MOV EDX,[EBP+20] ;puntero a cantidad
  MOV [cantidad],EDX
  
  MOV EBX,0
  MOVDQU XMM7,[unos] ; cargamos unos a xmm7 para poder invertir la mascara luego.        

  ciclar:
  
  MOV EDX,[EBP+8] ;puntero a imagen A
  MOVDQU XMM6,[EDX+EBX]
 
  MOV EDX,[EBP+12] ;puntero a imagen B
  MOVDQU XMM5,[EDX+EBX]

  MOV EDX,[EBP+16] ;puntero a imagen Mascara
  MOVDQU XMM4,[EDX+EBX]
  
  PAND XMM5,XMM4 ;aplicamos mascara a vectorB
  PANDN XMM4,XMM7 ;invertimos mascara
  PAND XMM6,XMM4 ;aplicamos mascara a vectorA
  POR  XMM6,XMM5 ;merge a y b
  
  MOV EDX,[EBP+8] ;puntero a resultado
  MOVDQU [EDX + EBX], XMM6 ;COPIO EL RESULTADO AL VECTOR
                         ;EN LA POSICION INDICADA

  ADD EBX,4 ;nos desplazamos de a 32 bits 
  CMP EBX,[cantidad]
  JL ciclar
  
  MOV ESP,EBP
  POP EBP   
   
  ret