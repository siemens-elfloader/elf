SET UTILS=E:\Rainmaker\Siemens\Programming\IAR\Security\!Utils

copy Sec.vkp Sec.vkp.bak

%UTILS%\elf2vkp.exe Sec.elf Sec.vkp %UTILS%\S75sw47.bin
