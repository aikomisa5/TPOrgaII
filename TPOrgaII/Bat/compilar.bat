nasm -f win32 -o enmascarar_asm.obj _enmascar_asm.asm
gcc -Wall -c AvanceTP.c
gcc -Wall -o avance.exe enmascarar_asm.obj AvanceTP.o
./avance.exe c.rgb l.rgb mask.rgb 750000