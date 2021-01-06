// Клавиатурные хуки ;)

int IdleMenuDrop=0;
int IsIdle(void)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4 ]))
    return(1);
  else
  return(0);
}



void showint(int i)
{
 char *s=malloc(32);
 sprintf(s,"%d",i);
 ShowMSG(1,(int)s);
}

int IDLE_KeyHook(int submsg, int msg)// Это хук, действующий на IDLE.
{  return (0);
}

int FastRun_KeyHook(int submsg, int msg)// Вызов панели FastRun
{
return(0);
}
