echo ; * Собственная мелодия для каждого в адреске * * Own melody for each entry in addressbook *>%2\header.txt
echo ; (c) Lost %date%>>%2\header.txt

%1\..\elfloader\elf2vkp.exe %2\OwnMelody.elf %2\temp.vkp D:\Mobile\FullFlash\%3
copy /b %2\header.txt+%2\readme.txt+%2\temp.vkp %2\OwnMelody.vkp
del %2\temp.vkp %2\header.txt %2\OwnMelody.elf