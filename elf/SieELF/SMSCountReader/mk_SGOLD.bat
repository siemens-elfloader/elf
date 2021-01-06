set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% SMSCountReader.ewp -build Release_SGOLD > build.log
copy .\Release_SGOLD\EXE\SMSCountReader.elf SMSCountReader_SGOLD.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_SGOLD