set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% SMSCountReader.ewp -build Release_NEWSGOLD > build.log
copy .\Release_NEWSGOLD\EXE\SMSCountReader.elf SMSCountReader_NEWSGOLD.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_NEWSGOLD