@echo off

rem Rebuild at first
rem call mkall.cmd

set tripper=..\tools\tripper.exe
set szip=..\..\tools\7z.exe

rmdir /S /Q Publish

mkdir Publish\mc_newSGold
mkdir Publish\mc_ELKA
mkdir Publish\mc_SGold
rem mkdir Publish\mc_SGold2
mkdir Publish\Sources

%tripper% NewSGold\Exe\mc.elf
move /Y NewSGold\Exe\mc_new.elf NewSGold\Exe\mc.elf
%tripper% ELKA\Exe\mc.elf
move /Y ELKA\Exe\mc_new.elf ELKA\Exe\mc.elf
%tripper% SGold1\Exe\mc.elf
move /Y SGold1\Exe\mc_new.elf SGold1\Exe\mc.elf
rem %tripper% SGold2\Exe\mc.elf
rem move /Y SGold2\Exe\mc_new.elf SGold2\Exe\mc.elf

copy /y /b NewSGold\Exe\mc.elf Publish\mc_NewSGold\
copy /y /b ELKA\Exe\mc.elf Publish\mc_ELKA\
copy /y /b SGold1\Exe\mc.elf Publish\mc_SGold\
rem copy /y /b SGold2\Exe\mc.elf Publish\mc_SGold2\

copy /y /b Files\mckeys.cfg Publish\mc_NewSGold\
copy /y /b Files\mckeys.cfg Publish\mc_ELKA\
copy /y /b Files\mckeys.cfg Publish\mc_SGold\
rem copy /y /b Publish\mckeys.cfg Publish\mc_SGold2\

copy /y /b Langs\*.mclg Publish\mc_NewSGold\
copy /y /b Langs\*.mclg Publish\mc_ELKA\
copy /y /b Langs\*.mclg Publish\mc_SGold\
rem copy /y /b Langs\*.mclg Publish\mc_SGold2\

copy /y /b Files\*.mccs Publish\mc_NewSGold\
copy /y /b Files\*.mccs Publish\mc_ELKA\
copy /y /b Files\*.mccs Publish\mc_SGold\
rem copy /y /b Files\*.mccs Publish\mc_SGold2\

copy /y /b Files\*.txt Publish\mc_NewSGold\
copy /y /b Files\*.txt Publish\mc_ELKA\
copy /y /b Files\*.txt Publish\mc_SGold\
rem copy /y /b Files\*.txt Publish\mc_SGold2\

copy /y /b *.asm Publish\Sources\
copy /y /b *.c Publish\Sources\
copy /y /b *.dep Publish\Sources\
copy /y /b *.ewd Publish\Sources\
copy /y /b *.ewp Publish\Sources\
copy /y /b *.eww Publish\Sources\
copy /y /b *.sln Publish\Sources\
copy /y /b *.vcproj Publish\Sources\
copy /y /b *.xcl Publish\Sources\
copy /y /b *.cmd Publish\Sources\
mkdir Publish\Sources\Inc
copy /y /b Inc\*.h Publish\Sources\Inc
mkdir Publish\Sources\ZLib\minizip
copy /y /b ZLib\*.h Publish\Sources\ZLib
copy /y /b ZLib\*.c Publish\Sources\ZLib
copy /y /b ZLib\minizip\*.h Publish\Sources\ZLib\minizip
copy /y /b ZLib\minizip\*.c Publish\Sources\ZLib\minizip
mkdir Publish\Sources\Files
copy /y /b Files\*.cfg Publish\Sources\Files
copy /y /b Files\*.mccs Publish\Sources\Files
copy /y /b Files\*.txt Publish\Sources\Files
mkdir Publish\Sources\Langs
copy /y /b Langs\*.mclg Publish\Sources\Langs

cd Publish

%szip% a mc_NewSGold.zip mc_NewSGold
%szip% a mc_ELKA.zip mc_ELKA
%szip% a mc_SGold.zip mc_SGold
rem %szip% a mc_SGold2.zip mc_SGold2
%szip% a -mx9 Sources.7z Sources

pause