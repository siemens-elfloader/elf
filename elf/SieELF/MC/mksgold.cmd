@echo off

set iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"

%iarmake% mc.ewp -build SGold_X75
