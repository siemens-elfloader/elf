cd %~dp0
echo %1

elf2vkp.exe ..\tmp\multisim.elf a %2
date /T >d
time /T >dt
@echo set /A rr=text > b.bat
@echo %1>ver
;@echo copy 1.txt+ver+sp.txt+d+2sg.txt+a /b multisim_%%rr%%.vkp >>b.bat

copy 1.txt+ver+sp.txt+d+sp.txt+dt+2sg.txt+a /b ..\vkp\multisim_%1.vkp 

del d
del dt
del a
del b.bat

cd ..\tmp

del /Q *.*
