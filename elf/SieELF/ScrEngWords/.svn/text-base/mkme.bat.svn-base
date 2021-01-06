set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\COMMON\BIN\iarbuild.exe"

%iarmake% ScrEngWords.ewp -build Release_NEWSGOLD >log.log

..\tools\tripper.exe Release_NEWSGOLD\exe\ScrEngWords.elf ScrEngWords_NEWSGOLD_tripped.elf
..\tools\obexcopy.exe ScrEngWords_NEWSGOLD_tripped.elf Data\ZBin\

rd /s /q Release_NEWSGOLD
rd /s /q settings
del *.dep

pause