set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% MusicStart.ewp -build Release_NEWSGOLD > build.log
copy .\Release_NEWSGOLD\EXE\MusicStart.elf MusicStart_NEWSGOLD.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_NEWSGOLD