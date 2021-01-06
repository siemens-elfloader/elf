%1\..\tools\elf2vkp.exe %2\AppEx.elf %2\temp.vkp e:\FullFlash\lg8\%3.bin
copy /b %1\readme.txt+%2\temp.vkp+%1\config_%4.vkp %1\AppEx_%3.vkp
