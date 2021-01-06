@echo off
SET iarmake="c:\Program Files\IAR Systems\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"
SET zipprog=..\_SVN_Utility\zip.exe

%iarmake% alarm_cfg_editor\alarm_cfg_editor.ewp -build SGOLD
%iarmake% alarm_cfg_editor\alarm_cfg_editor.ewp -build SL65
%iarmake% alarm_ring\alarm_ring.ewp -build SGOLD
%iarmake% alarm_ring\alarm_ring.ewp -build SGOLD_X75
%iarmake% new_alarm\new_alarm.ewp -build SGOLD

%iarmake% alarm_cfg_editor\alarm_cfg_editor.ewp -build NEWSGOLD
%iarmake% alarm_ring\alarm_ring.ewp -build NEWSGOLD
%iarmake% new_alarm\new_alarm.ewp -build NEWSGOLD

%iarmake% alarm_cfg_editor\alarm_cfg_editor.ewp -build ELKA
%iarmake% alarm_ring\alarm_ring.ewp -build ELKA
%iarmake% new_alarm\new_alarm.ewp -build ELKA

copy alarm_ring\SGOLD\Exe\alarm_ring.elf alarm_ring.elf
copy alarm_ring\SGOLD_X75\Exe\alarm_ring.elf alarm_ring_x75.elf
copy alarm_cfg_editor\SGOLD\Exe\alarm_cfg_editor.elf alarm_cfg_editor.elf
copy alarm_cfg_editor\SL65\Exe\alarm_cfg_editor.elf alarm_cfg_editor_sl65.elf
copy new_alarm\SGOLD\Exe\new_alarm.elf new_alarm.elf
%zipprog% -j sgold.zip alarm_ring.elf
%zipprog% -j sgold.zip alarm_ring_x75.elf
%zipprog% -j sgold.zip alarm_cfg_editor.elf
%zipprog% -j sgold.zip alarm_cfg_editor_sl65.elf
%zipprog% -j sgold.zip new_alarm.elf
del alarm_ring.elf
del alarm_ring_x75.elf
del alarm_cfg_editor.elf
del alarm_cfg_editor_sl65.elf
del new_alarm.elf

copy alarm_ring\NEWSGOLD\Exe\alarm_ring.elf alarm_ring.elf
copy alarm_cfg_editor\NEWSGOLD\Exe\alarm_cfg_editor.elf alarm_cfg_editor.elf
copy new_alarm\NEWSGOLD\Exe\new_alarm.elf new_alarm.elf
%zipprog% -j newsgold.zip alarm_ring.elf
%zipprog% -j newsgold.zip alarm_cfg_editor.elf
%zipprog% -j newsgold.zip new_alarm.elf
del alarm_ring.elf
del alarm_cfg_editor.elf
del new_alarm.elf

copy alarm_ring\ELKA\Exe\alarm_ring.elf alarm_ring.elf
copy alarm_cfg_editor\ELKA\Exe\alarm_cfg_editor.elf alarm_cfg_editor.elf
copy new_alarm\ELKA\Exe\new_alarm.elf new_alarm.elf
%zipprog% -j elka.zip alarm_ring.elf
%zipprog% -j elka.zip alarm_cfg_editor.elf
%zipprog% -j elka.zip new_alarm.elf
del alarm_ring.elf
del alarm_cfg_editor.elf
del new_alarm.elf
