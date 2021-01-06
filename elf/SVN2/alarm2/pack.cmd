@echo off
SET iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
SET zipprog=..\_SVN_Utility\zip.exe

%iarmake% config\config.ewp -build SGOLD
%iarmake% ring\ring.ewp -build SGOLD
%iarmake% ring\ring.ewp -build SGOLD_X75
%iarmake% daemon\daemon.ewp -build SGOLD

%iarmake% config\config.ewp -build NEWSGOLD
%iarmake% ring\ring.ewp -build NEWSGOLD
%iarmake% daemon\daemon.ewp -build NEWSGOLD

%iarmake% config\config.ewp -build ELKA
%iarmake% ring\ring.ewp -build ELKA
%iarmake% daemon\daemon.ewp -build ELKA

md alarm2
md alarm2\icons
copy Files\icons\* alarm2\icons\*
md daemons

copy ring\SGOLD\Exe\ring.elf alarm2\ring.elf
copy ring\SGOLD_X75\Exe\ring.elf alarm2\ring_x75.elf
copy config\SGOLD\Exe\config.elf alarm2\config.elf
copy daemon\SGOLD\Exe\daemon.elf daemons\alarm.elf
%zipprog% -rm sgold.zip alarm2
%zipprog% -rm sgold.zip daemons

md alarm2
md alarm2\icons
copy Files\icons\* alarm2\icons\*
md daemons

copy ring\NEWSGOLD\Exe\ring.elf alarm2\ring.elf
copy config\NEWSGOLD\Exe\config.elf alarm2\config.elf
copy daemon\NEWSGOLD\Exe\daemon.elf daemons\alarm.elf
%zipprog% -rm newsgold.zip alarm2
%zipprog% -rm newsgold.zip daemons

md alarm2
md alarm2\icons
copy Files\icons\* alarm2\icons\*
md daemons

copy ring\ELKA\Exe\ring.elf alarm2\ring.elf
copy config\ELKA\Exe\config.elf alarm2\config.elf
copy daemon\ELKA\Exe\daemon.elf daemons\alarm.elf
%zipprog% -rm elka.zip alarm2
%zipprog% -rm elka.zip daemons

rd /s /q settings
rd /s /q config\SGOLD
rd /s /q config\NEWSGOLD
rd /s /q config\ELKA
rd /s /q config\settings
del config\config.dep

rd /s /q ring\SGOLD
rd /s /q ring\SGOLD_X75
rd /s /q ring\NEWSGOLD
rd /s /q ring\ELKA
rd /s /q ring\settings
del ring\ring.dep

rd /s /q daemon\SGOLD
rd /s /q daemon\NEWSGOLD
rd /s /q daemon\ELKA
rd /s /q daemon\settings
del daemon\daemon.dep
