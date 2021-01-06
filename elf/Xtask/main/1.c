
extern void do_gui(int, int);

// -1 - XTask GUI present
// 0 - XTask GUI absent
// 1 - IBUT longpressed, ready for exit
int mode;

// 0 - no press
// 1 - long press REDBUT
int mode_red;

// 0 - no press
// 1 - long press ENTER_BUTTON
// 2 - disable KEY_UP process
int mode_enter;
int BUTTON=0x11;//Нужная клавиша в HEX
int my_keyhook(int submsg, int msg)
{
#ifdef USE_ONE_KEY
#ifdef ELKA
  if (submsg!=POC_BUTTON) return(0);
#else
  if (submsg!=INTERNET_BUTTON) return(0);
#endif
 if (my_csm_id)
  { if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
    { CloseCSM(my_csm_id);
    }
    if (msg==KEY_UP)
    {
      GBS_SendMessage(MMI_CEPID,KEY_UP,BUTTON);//INTERNET_BUTTON
    }
    return(2);
  }
  switch(msg)
  {
  case KEY_DOWN: break;
  case KEY_UP:
    if (IsUnlocked()||ENA_LOCK)
    { do_gui(0,0); } break;
  case LONG_PRESS:  break;
  }
  return(1);
#else
  if (submsg!=BUTTON) return(0);
  if (my_csm_id)
  {
    if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
    {
      CloseCSM(my_csm_id);
    }
    return(0);
  }
  switch(msg)
  {
  case KEY_DOWN:
  mode_enter=1;
    if (IsUnlocked()||ENA_LOCK)
    {
      do_gui(0,0);
    }
    mode=0;
    break;
  case KEY_UP:
    if (mode_enter==0)
    { mode_enter=2;
      GBS_SendMessage(MMI_CEPID,KEY_UP,BUTTON);//INTERNET_BUTTON
      return (2);
    }
    if (mode_enter==2)
    {
      mode_enter=0;
      return (0);
    }
    mode_enter=0;
    return (2);      
  case LONG_PRESS:
    mode_enter=1;
    if (IsUnlocked()||ENA_LOCK)
    {
      do_gui(0,0);
    }
    mode=0;
    break;
  }
  return(2);
#endif
