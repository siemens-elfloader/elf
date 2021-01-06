@echo off
SET iarmake="D:\Pasha\ARM_Embedded_Workbench\Embedded Workbench 4.0 Evaluation\common\bin\iarbuild.exe"

%iarmake% MNUEdit.ewp -build Release
%iarmake% MNUEdit.ewp -build Release_NEWSGOLD
%iarmake% MNUEdit.ewp -build Release_ELKA
%iarmake% MNUEdit.ewp -build Release_EN
%iarmake% MNUEdit.ewp -build Release_NEWSGOLD_EN
%iarmake% MNUEdit.ewp -build Release_ELKA_EN

copy Release\Exe\MNUEdit.elf MNUEdit_SGOLD.elf
copy Release_NEWSGOLD\Exe\MNUEdit.elf MNUEdit_NSG.elf
copy Release_ELKA\Exe\MNUEdit.elf MNUEdit_ELKA.elf
copy Release_EN\Exe\MNUEdit.elf MNUEdit_SGOLD_EN.elf
copy Release_NEWSGOLD_EN\Exe\MNUEdit.elf MNUEdit_NSG_EN.elf
copy Release_ELKA_EN\Exe\MNUEdit.elf MNUEdit_ELKA_EN.elf
