rmdir /q /s .git
rmdir /q /s .vs
rmdir /q /s x64
rmdir /q /s Debug
del *.gitattributes
del *.gitignore
del *.md
del *.vcxproj
del *.vcxproj.filters
del *.vcxproj.user
del *.sln
del *.txt
del delte_junk_files.bat

mkdir files
move *.c files
move *.r files
move *.h files

cd files

gcc -std=c11 -c *.c
gcc -std=c11 *.o -o prog.exe
del *.o
pause

cls
@echo start of the program

"prog.exe"

pause
