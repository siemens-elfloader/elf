Inc Revision - счетчик ревизий для IAR'a

(C) Vedan

Сделал счетчик ля тех кто делает эльфы и кому нужно считать количество компиляций.

Настройка:

   Project 
-> Options 
-> Build Actions 
-> В вкладку   Pre-build command line 
   вписываете  
               $PROJ_DIR$\inc_revision.bat

При компиляции, IAR вызывает  inc_revision.bat, который запускает inc_revision.exe, который прибавляет ревизии.
Подключаем к IAR'у 

#include "revision.h"   

и юзаем оттуда 

#define ELF_REVISION

13/07/2008
www.grafx75.net.ru