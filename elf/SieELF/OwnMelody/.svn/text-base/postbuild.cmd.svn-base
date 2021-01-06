echo ; * Own melody for each entry in addressbook *>%1\header.txt
echo ; (c) Lost %date%>>%1\header.txt

%1\..\tools\elf2vkp.exe %2\OwnMelody.elf %2\temp.vkp e:\FullFlash\lg8\%3.bin
copy /b %1\header.txt+%2\readme.txt+%2\temp.vkp %1\OwnMelody_%3.vkp
