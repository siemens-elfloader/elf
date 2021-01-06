@echo off

set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"

%iarmake% SieHelpMan.ewp -build Release_SGOLD > build.log

copy siehelpman_SGOLD.elf SieHelpMan.elf
..\obextool\obexsetup.exe
..\obextool\obexcopy.exe siehelpman.elf \Data\ZBin\utilities\
del *.elf
del *.dep
rd /s /q .\settings
rd /s /q .\Release_SGOLD
