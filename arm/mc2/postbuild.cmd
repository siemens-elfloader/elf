SET obextool="Q:\Soft\Obex\obexcopy.exe"
SET mc="SGold_X75\Exe\mc"
SET tripper="..\Tools\tripper.exe"
rem %obextool% %elf_file% \Data\mc.elf
rem %obextool% %elf_file% \MMCard\ZBin\mc\mc.elf
%tripper% %mc%.elf
move /Y %mc%_new.elf %mc%.elf

copy /Y %mc%.elf E:\
