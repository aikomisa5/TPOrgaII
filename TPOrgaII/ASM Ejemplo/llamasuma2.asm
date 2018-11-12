extern _printf
extern _suma2asm
global _main
section .data
texto db "7 + 8 = %d", 10, 0
section .text
_main:
push EBP ; guarda el stack frame anterior
mov EBP, ESP ; EBP apunta al frame actual
mov EBX, 7
mov ECX, 8
push ECX ; apila parametros para suma2asm
push EBX
call _suma2asm
add ESP, 8 ; Quita parametros de suma2asm
push EAX ; apila numero
push texto ; apila formato
call _printf ; llama a printf
add ESP, 8 ; quita los parametros de printf
pop EBP ; recupera el stack frame del llamador
ret