@echo off

set iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"

%iarmake% mc.ewp -build SGold1
%iarmake% mc.ewp -build NewSGold
%iarmake% mc.ewp -build ELKA
