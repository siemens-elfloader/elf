set iarmake="E:\Tool\IAR\common\bin\iarbuild.exe"

%iarmake% MssMD.ewp -build Release >log.log

..\..\tools\obexcopy.exe Release\exe\MssMD_nsg.elf Data\

pause