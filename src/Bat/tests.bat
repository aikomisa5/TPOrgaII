nasm -f win32 -o mainAsm.o mainAsm.asm &&
gcc -Wall -c mainC.c &&
gcc -Wall -o main.exe mainAsm.o mainC.o