set iarmake="E:\Tool\IAR\common\bin\iarbuild.exe"

%iarmake% MssMD.ewp -build Release >log.log
%iarmake% MssMD.ewp -build Release_ELKA >>log.log
%iarmake% MssMD.ewp -build Release_S68 >>log.log

rd /s /q MssMD_CN
mkdir MssMD_CN

copy Release\exe\MssMD_nsg.elf MssMD_CN\
copy Release_ELKA\exe\MssMD_elka.elf MssMD_CN\
copy Release_S68\exe\MssMD_s68.elf MssMD_CN\

rd /s /q Release
rd /s /q Release_ELKA
rd /s /q Release_S68

rd /s /q settings
del *.dep
del *.ewd

pause