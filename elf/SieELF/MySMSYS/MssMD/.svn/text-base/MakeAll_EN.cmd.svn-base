set iarmake="E:\Tool\IAR\common\bin\iarbuild.exe"

%iarmake% MssMD.ewp -build Release_NEWSGOLD_LG3_EN >log.log
%iarmake% MssMD.ewp -build Release_ELKA_EN >>log.log
%iarmake% MssMD.ewp -build Release_S68_LG3_EN >>log.log

rd /s /q MssMD_EN
mkdir MssMD_EN

copy Release_NEWSGOLD_LG3_EN\exe\MssMD_nsg_lg3_en.elf MssMD_EN\
copy Release_ELKA_EN\exe\MssMD_elka_en.elf MssMD_EN\
copy Release_S68_LG3_EN\exe\MssMD_s68_lg3_en.elf MssMD_EN\

rd /s /q Release_NEWSGOLD_LG3_EN
rd /s /q Release_ELKA_EN
rd /s /q Release_S68_LG3_EN

rd /s /q settings
del *.dep
del *.ewd

pause