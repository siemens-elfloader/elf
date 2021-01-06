@echo off
if exist %SYSTEMROOT%\System32\obexdel.exe obexdel %2
if exist %SYSTEMROOT%\System32\obexcopy.exe obexcopy %1 %2
@echo on