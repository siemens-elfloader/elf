================================================================
=========== КЛАВИАТУРНЫЕ МАКРОСЫ for Sie_ELF platform ==========
=========== KEYBOARD MACROSES    for Sie_ELF platform ==========
================================================================

Эмуляция нажатий клавиш/Key press emulation
Нажмите любую клавишу для останова/Press any key to stop

Параметр - путь к текстовому файлу или макрос(автоопределение)
Parameter is a path to file or macro string(auto) 

Конфиг/Config:

show title - показывать надпись MAC во время выполнения макроса(требует доработки т.к. глючит: вывод всегда идёт в один и тот же layer :( )
CPU wait threshold,% - 
ShowNativeMenu() address - 


Макрос - последовательность символов:
Macro is a sequence of symbols:

	0-9*# 09*#
	@ GREEN_BUTTON зелёная кнопка
	! RED_BUTTON  красная
	+ ENTER_BUTTON джойстик
	L LEFT_SOFT левая софт
	R RIGHT_SOFT правая
	J Internet button/Pocket button (если есть)
	[ VOL+ боковые кнопки/side buttons
	] VOL-
	
  % случайная цифровая клавиша/random numeric key(0-9)
  $ случайная цифровая клавиша/random numeric key(2-9)
  < > ^ V
или
  l r y d 
    джойстик влево вправо вверх вниз/joy left right up down

  ~ Long Press prefix/Длинное нажатие
	_ down prefix/Нажать кнопку
	| up prefix/Отпустить кнопку

  .
  пробел/spacebar
    pause(0.2 sec)
	P pause(1 sec)
	W ждать окончания ресурсоёмкого события/wait for cpu-loading event
                                                           	
	; 
  перевод строки\newline 
          разделители(игнорируются)/delimiters(ignored)

  `0:\apps\opera.jar` запустить файл/run file

  (1234) пауза 1234 миллисек/pause 1234 msec

  N native menu(требуется указать адрес ShowMativeMenu() в /you must enter address ShowMativeMenu() in  macro.bcfg) 
  

------------------- (с)&(r)'s ----------------------------------
----------------------------------------------------------------

(c) Captain_SISka 2007
mailto:s0d@mail.ru?subject=siemens 


(a) /Anti-Respects/ создателям MMORPG RFONline & собственной лени ...








