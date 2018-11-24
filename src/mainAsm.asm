global _enmascararASM

section .data
cantidad dd 0 ;cantidad de tama�o int, es decir 4 bytes
;resultadopuntero dd 0 ;ojo! es un puntero, los punteros tienen tamano de 4 bytes
;lo declaramos asi porque vamos a setear los valores del vector resultado directo a la posicion de memoria
;que nos especifica el puntero que viene como argumento

unos times 128 db (255) ;32 valores de 1 byte seteados en 255

section .text

_enmascararASM:
  
  push ebp
  mov ebp,esp  
  
  cargoCantidad:
  mov edx,[ebp+20] ;puntero a cantidad
  mov [cantidad],edx
  mov ebx,0
  movdqu xmm7,[unos] ; cargamos unos a xmm7 para poder invertir la mascara luego.

  ciclar:  
  mov edx,[ebp+8] ;puntero a imagen a
  movdqu xmm6,[edx+ebx]
  mov edx,[ebp+12] ;puntero a imagen b
  movdqu xmm5,[edx+ebx]
  mov edx,[ebp+16] ;puntero a imagen mascara
  movdqu xmm4,[edx+ebx]
  mov edx,[ebp+8] ;puntero a resultado
  pand xmm5,xmm4 ;aplicamos mascara a vectorb
  pandn xmm4,xmm7 ;invertimos mascara
  pand xmm6,xmm4 ;aplicamos mascara a vectora
  por  xmm6,xmm5 ;merge a y b  
  movdqu [edx + ebx], xmm6 ;copio el resultado al vector en la posicion indicada

  add ebx,16 ;nos desplazamos de a 128 bits 
  cmp ebx,[cantidad]
  jl ciclar
  
  mov esp,ebp
  pop ebp   
   
  ret