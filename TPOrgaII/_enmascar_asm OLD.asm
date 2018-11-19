global _enmascarar_asm
;%include "io.inc"

section .data
vectorA dd 0
vectorB dd 0
vectorMask dd 0
cantidad dd 0
vectorResultado dq 0

unos times 64 db (255)
;variable db 255

section .text

_enmascarar_asm:
  
  PUSH EBP
  MOV EBP,ESP  
   
  MOV EDX,[ESP+8] ;puntero a imagen A
  MOV [vectorA],EDX
  MOV EDX,[ESP+12] ;puntero a imagen B
  MOV [vectorB],EDX
  MOV EDX,[ESP+16] ;puntero a imagen C
  MOV [vectorMask],EDX
  MOV EDX,[ESP+20] ;puntero a cantidad
  MOV [cantidad],EDX
  MOV EDX,[ESP+24] ;puntero a resultado
  MOV [vectorResultado],EDX
   
  MOV ECX, [cantidad]
  ;to delete
  MOV ECX,1
  MOVQ MM7,[unos]
   
     
  MOV EBX,0  
  LOOPER:
   
  MOVQ MM0,[vectorMask+EBX]
  MOVQ MM1,[vectorA+EBX]
  MOVQ MM2,[vectorB+EBX]  
  MOVQ MM3,[vectorResultado+EBX]
  
  ;PAND MM1,MM0 ;aplicamos mascara a vectorA
  ;PANDN MM0,MM7 ;invertimos mascara
  ;PAND MM2,MM0 ;aplicamos mascara a vectorB
  ;PXOR MM3,MM3 ;inicializamos vector resultado en 0
  ;POR  MM3,MM1 ;cargamos vectorA en vector resultado
  ;POR  MM3,MM2 ;cargamos vectorB en vector resultado
  MOVQ [vectorResultado+EBX], MM1 
  ADD EBX,64
  LOOP LOOPER
  MOV ESP,EBP
  POP EBP   
   
  ret