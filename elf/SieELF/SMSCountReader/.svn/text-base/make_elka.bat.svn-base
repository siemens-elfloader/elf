set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% SMSCountReader.ewp -build Release_ELKA > build.log
copy .\Release_ELKA\EXE\SMSCountReader.elf SMSCountReader_ELKA.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_ELKA