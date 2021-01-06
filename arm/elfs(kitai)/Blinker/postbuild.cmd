SET obextools=%windir%
SET elf_file=%1\%3

%obextools%\obexdel.exe %2\%3
%obextools%\obexcopy.exe %elf_file% %2\%3