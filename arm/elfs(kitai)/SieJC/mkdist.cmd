@echo off
SET zipprog=..\_SVN_Utility\zip.exe
%zipprog% -j SieJC.zip Release\exe\SieJC.elf
%zipprog% -j SieJC_ELKA.zip Release_ELKA\exe\SieJC.elf
%zipprog% -j SieJC_SGOLD.zip Release_SGOLD\exe\SieJC.elf
%zipprog% -j SieJC_X75.zip Release_SGOLD_X75\exe\SieJC.elf