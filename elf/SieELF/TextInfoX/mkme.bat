set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\COMMON\BIN\iarbuild.exe"

%iarmake% TextInfoX.ewp -build Release_ELKA >log.log

..\tripper\tripper.exe Release_ELKA\exe\TextInfoX.elf TextInfoX_elka_tripped.elf
..\obextool\obexcopy.exe TextInfoX_elka_tripped.elf Data\ZBin\Daemons\

rd /s /q Release_ELKA
rd /s /q settings
del *.dep