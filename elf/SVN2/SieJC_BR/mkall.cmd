@echo off
set iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
%iarmake% SieJC.ewp -build Release
%iarmake% SieJC.ewp -build Release_SGOLD
%iarmake% SieJC.ewp -build Release_SGOLD_X75
%iarmake% SieJC.ewp -build Release_ELKA