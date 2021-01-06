---------------------------------------------------------------------------
�������
---------------------------------------------------------------------------

key_timer     -     ������ �������� ����������� �������� ��������� �� ��������, �������� KeyRun()
time_timer    -     ������������ (��� � 30 ������) ��������� ������ �� ��������� � ��������������, �������� TimerA()
adr_timer     -      ������������ ��� ����� �������� �������� � "�������" � �� ������� "��������", �������� adr_progress()
idle_timer     -      ���������, �� ���� �� ��, ��������� UpdateScreen() �� ���� ���������� RunMenuPanel()

---------------------------------------------------------------------------
�������� ��������
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

MenuOnKey, MenuOnRedraw (��� ����������):
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);

RunMenuPanel (��� ������� ���):
	GBS_DelTimer(&idle_timer);
---------------------------------------------------------------------------
START ��������
---------------------------------------------------------------------------

MenuOnClose:
	idle_timer

MenuOnFocus:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
	GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);

KeyRun:
	GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);

MenuOnRedraw:(��� �������������)
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


