@echo off

rem Rebuild at first
rem call mkall.cmd

set tripper=..\tools\tripper.exe
set szip=..\..\tools\7z.exe

rmdir /S /Q Publish

mkdir Publish\mc_newSGold
mkdir Publish\mc_ELKA
mkdir Publish\mc_SGold
mkdir Publish\mc_SGold_X75
mkdir Publish\Sources

%tripper% NewSGold\Exe\mc.elf
move /Y NewSGold\Exe\mc_new.elf NewSGold\Exe\mc.elf
%tripper% ELKA\Exe\mc.elf
move /Y ELKA\Exe\mc_new.elf ELKA\Exe\mc.elf
%tripper% SGold\Exe\mc.elf
move /Y SGold\Exe\mc_new.elf SGold\Exe\mc.elf
%tripper% SGold_X75\Exe\mc.elf
move /Y SGold_X75\Exe\mc_new.elf SGold_X75\Exe\mc.elf

copy /y /b NewSGold\Exe\mc.elf Publish\mc_NewSGold\
copy /y /b ELKA\Exe\mc.elf Publish\mc_ELKA\
copy /y /b SGold\Exe\mc.elf Publish\mc_SGold\
copy /y /b SGold_X75\Exe\mc.elf Publish\mc_SGold_X75\

copy /y /b Files\mckeys.cfg Publish\mc_NewSGold\
copy /y /b Files\mckeys.cfg Publish\mc_ELKA\
copy /y /b Files\mckeys.cfg Publish\mc_SGold\
copy /y /b Files\mckeys.cfg Publish\mc_SGold_X75\

mkdir Publish\mc_NewSGold\Languages\
copy /y /b Languages\*.mclg Publish\mc_NewSGold\Languages
mkdir Publish\mc_ELKA\Languages\
copy /y /b Languages\*.mclg Publish\mc_ELKA\Languages
mkdir Publish\mc_SGold\Languages\
copy /y /b Languages\*.mclg Publish\mc_SGold\Languages
mkdir Publish\mc_SGold_X75\Languages\
copy /y /b Languages\*.mclg Publish\mc_SGold_X75\Languages

mkdir Publish\mc_NewSGold\Skins\
copy /y /b Skins\*.mccs Publish\mc_NewSGold\Skins
mkdir Publish\mc_ELKA\Skins\
copy /y /b Skins\*.mccs Publish\mc_ELKA\Skins
mkdir Publish\mc_SGold\Skins\
copy /y /b Skins\*.mccs Publish\mc_SGold\Skins
mkdir Publish\mc_SGold_X75\Skins\
copy /y /b Skins\*.mccs Publish\mc_SGold_X75\Skins

copy /y /b Files\*.txt Publish\mc_NewSGold\
copy /y /b Files\*.cfg Publish\mc_NewSGold\
copy /y /b Files\*.txt Publish\mc_ELKA\
copy /y /b Files\*.cfg Publish\mc_ELKA\
copy /y /b Files\*.txt Publish\mc_SGold\
copy /y /b Files\*.cfg Publish\mc_SGold\
copy /y /b Files\*.txt Publish\mc_SGold_X75\
copy /y /b Files\*.cfg Publish\mc_SGold_X75\

mkdir Publish\mc_NewSGold\Images\
copy /y /b Images\*.png Publish\mc_NewSGold\Images\
mkdir Publish\mc_NewSGold\Images\ext
copy /y /b Images\ext\*.png Publish\mc_NewSGold\Images\ext
mkdir Publish\mc_NewSGold\Images\app
copy /y /b Images\app\*.png Publish\mc_NewSGold\Images\app

mkdir Publish\mc_ELKA\Images\
copy /y /b Images_Elka\*.png Publish\mc_ELKA\Images\
mkdir Publish\mc_ELKA\Images\ext
copy /y /b Images_Elka\ext\*.png Publish\mc_ELKA\Images\ext
mkdir Publish\mc_ELKA\Images\app
copy /y /b Images_Elka\app\*.png Publish\mc_ELKA\Images\app

mkdir Publish\mc_SGold\Images\
copy /y /b Images\*.png Publish\mc_SGold\Images\
mkdir Publish\mc_SGold\Images\ext
copy /y /b Images\ext\*.png Publish\mc_SGold\Images\ext
mkdir Publish\mc_SGold\Images\app
copy /y /b Images\app\*.png Publish\mc_SGold\Images\app

mkdir Publish\mc_SGold_X75\Images\
copy /y /b Images\*.png Publish\mc_SGold_X75\Images\
mkdir Publish\mc_SGold_X75\Images\ext
copy /y /b Images\ext\*.png Publish\mc_SGold_X75\Images\ext
mkdir Publish\mc_SGold_X75\Images\app
copy /y /b Images\app\*.png Publish\mc_SGold_X75\Images\app

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
mkdir Publish\Sources\Languages
copy /y /b Languages\*.mclg Publish\Sources\Languages
mkdir Publish\Sources\Images
copy /y /b Images\*.png Publish\Sources\Images
mkdir Publish\Sources\Images\ext
copy /y /b Images\ext\*.png Publish\Sources\Images\ext
mkdir Publish\Sources\Images\app
copy /y /b Images\app\*.png Publish\Sources\Images\app
mkdir Publish\Sources\Images_Elka
copy /y /b Images_Elka\*.png Publish\Sources\Images_Elka
mkdir Publish\Sources\Images_Elka\ext
copy /y /b Images_Elka\ext\*.png Publish\Sources\Images_Elka\ext
mkdir Publish\Sources\Images_Elka\app
copy /y /b Images\app\*.png Publish\Sources\Images_Elka\app

cd Publish

%szip% a mc_NewSGold.zip mc_NewSGold
%szip% a mc_ELKA.zip mc_ELKA
%szip% a mc_SGold.zip mc_SGold
%szip% a mc_SGold_X75.zip mc_SGold_X75
%szip% a -mx9 Sources.7z Sources

pause