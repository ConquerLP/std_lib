rmdir /q /s .git
rmdir /q /s .vs
rmdir /q /s x64
del *.gitattributes
del *.gitignore
del *.md
del *.vcxproj
del *.vcxproj.filters
del *.vcxproj.user
del *.sln
del *.txt
del RUN_ME.bat

mkdir files
move *.c files
move *.r files
move *.h files

cd files
gcc -std=c11 -S def.c
gcc -std=c11 -S basic.c
gcc -std=c11 -S object.c
gcc -std=c11 -S std_lib_math.c
gcc -std=c11 -S vector.c
gcc -std=c11 -S list.c
gcc -std=c11 -S string.c
gcc -std=c11 -S array.c
gcc -std=c11 -S filemanager.c 
gcc -std=c11 -S template.c
gcc -std=c11 -S main.c 

mkdir assembly
move *.S assembly

gcc -std=c11 -c def.c
gcc -std=c11 -c basic.c
gcc -std=c11 -c object.c
gcc -std=c11 -c std_lib_math.c
gcc -std=c11 -c vector.c
gcc -std=c11 -c list.c
gcc -std=c11 -c string.c
gcc -std=c11 -c array.c
gcc -std=c11 -c filemanager.c 
gcc -std=c11 -c template.c
gcc -std=c11 -c main.c 
gcc -std=c11 def.o basic.o object.o std_lib_math.o vector.o list.o string.o array.o filemanager.o template.o main.o -o prog.exe
pause

cls
@echo start of the program

"prog.exe"

pause
