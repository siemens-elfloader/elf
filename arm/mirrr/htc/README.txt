---------------------------------------------------------------------------
ТАЙМЕРЫ
---------------------------------------------------------------------------

key_timer     -     таймер плавного перемещения ползунка навигации по вкладкам, вызывает KeyRun()
time_timer    -     переодически (раз в 30 секунд) проверяет минуты на изменения и перерисовывает, вызывает TimerA()
adr_timer     -      используется для более плавного листания в "адреске" и на вкладке "интернет", вызывает adr_progress()
idle_timer     -      проверяет, на идле ли мы, запускает UpdateScreen() из него вызывается RunMenuPanel()

---------------------------------------------------------------------------
УДАЛЕНИЕ ТАЙМЕРОВ
---------------------------------------------------------------------------

MenuOnUnfocus:
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);

maincsm_onclose:
	GBS_DelTimer(&idle_timer);
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);

MenuOnKey, MenuOnRedraw (при блокировке):
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);

RunMenuPanel (при запуске ГУИ):
	GBS_DelTimer(&idle_timer);
---------------------------------------------------------------------------
START ТАЙМЕРОВ
---------------------------------------------------------------------------

MenuOnClose:
	idle_timer

MenuOnFocus:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
	GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);

KeyRun:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);

MenuOnRedraw:(при разблокировке)
GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);

MenuOnKey:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
	GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);
	GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);

UpdateScreen:
	GBS_StartTimerProc(&idle_timer, TMR_SECOND, UpdateScreen);

TimerA:
	GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);

adr_progress:
	GBS_StartTimerProc(&adr_timer, TMR_SECOND/60, adr_progress);

main:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/25, KeyRun);
	GBS_StartTimerProc(&idle_timer, TMR_SECOND/4, UpdateScreen);


