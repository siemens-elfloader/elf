@echo off

set iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"

%iarmake% mc.ewp -build SGold > build.log
%iarmake% mc.ewp -build SGold_X75 >> build.log
%iarmake% mc.ewp -build NewSGold >> build.log
%iarmake% mc.ewp -build ELKA >> build.log
