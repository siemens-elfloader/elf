set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\COMMON\BIN\iarbuild.exe"
set zip="D:\Program Files\7-Zip\7z.exe"

%iarmake% TextInfoX.ewp -build Release >log.log
%iarmake% TextInfoX.ewp -build Release_ELKA >>log.log
%iarmake% TextInfoX.ewp -build Release_SGOLD >>log.log

..\tripper\tripper.exe Release\exe\TextInfoX.elf TextInfoX_newsgold_tripped.elf
..\tripper\tripper.exe Release_ELKA\exe\TextInfoX.elf TextInfoX_elka_tripped.elf
..\tripper\tripper.exe Release_SGOLD\exe\TextInfoX.elf TextInfoX_sgold_tripped.elf

%zip% a TextInfoX_tripped.zip *.elf

rd /s /q Release
rd /s /q Release_ELKA
rd /s /q Release_SGOLD
rd /s /q settings
del *.dep
del *.elf