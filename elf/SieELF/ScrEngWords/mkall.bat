set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\COMMON\BIN\iarbuild.exe"

%iarmake% ScrEngWords.ewp -build Release_NEWSGOLD >log.log
%iarmake% ScrEngWords.ewp -build Release >>log.log
%iarmake% ScrEngWords.ewp -build Release_SGOLD >>log.log

..\tools\tripper.exe Release_NEWSGOLD\exe\ScrEngWords.elf ScrEngWords_NEWSGOLD_tripped.elf
..\tools\tripper.exe Release\exe\ScrEngWords.elf ScrEngWords_ELKA_tripped.elf
..\tools\tripper.exe Release_SGOLD\exe\ScrEngWords.elf ScrEngWords_SGOLD_tripped.elf


rd /s /q Release_NEWSGOLD
rd /s /q Release
rd /s /q Release_SGOLD
rd /s /q settings

..\tools\7z.exe a ScrEngWords.zip *.elf CET4.txt CET6.txt
del *.dep
del *.elf

pause