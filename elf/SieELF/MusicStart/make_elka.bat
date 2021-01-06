set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% MusicStart.ewp -build Release_ELKA > build.log
copy .\Release_ELKA\EXE\MusicStart.elf MusicStart_ELKA.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_ELKA