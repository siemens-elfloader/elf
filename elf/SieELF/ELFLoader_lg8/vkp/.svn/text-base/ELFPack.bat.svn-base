elf2vkp.exe ..\%1\exe\ELFLoader.elf ELFLoader.tmp %2
echo %1 >version.tmp
date /T >date.tmp
copy /b name+version.tmp+copyright+date.tmp+swi+ELFLoader.tmp .\%1\ELFLoader_%1.vkp
del *.tmp
attrib -R -A -S -H ..\%1 /S /D
RD /S /Q ..\%1
RD /S /Q ..\settings