global _suma2asm
section .data
section .text
_suma2asm:
push EBP ; guarda stack frame llamador
mov EBP, ESP ; EBP apunta al frame actual
; EBP+4 direccion de retorno
; EBP+8 parametro a
; EBP+12 parametro b
sub ESP, 4 ; espacio para local c en EBP-4
mov EAX, [EBP+8]
add EAX, [EBP+12]
mov [EBP-4], EAX ; el valor de retorno ya esta en EAX
mov ESP, EBP ; restaura ESP
pop EBP ; restaura EBP
ret