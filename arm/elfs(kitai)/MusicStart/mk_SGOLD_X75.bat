set iarmake="D:\Program Files\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% MusicStart.ewp -build Release_SGOLD_X75 > build.log
copy .\Release_SGOLD_X75\EXE\MusicStart.elf MusicStart_SGOLD_X75.elf
del *.dep
del *.bak
rd /s /q .\settings
rd /s /q .\Release_SGOLD_X75