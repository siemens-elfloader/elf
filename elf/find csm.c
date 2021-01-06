//переменная CSM_ID идентифицирует название csm которое нужно искать в очереди
GBSTMR timer;
GUI *datagui;
CSM_RAM *csm
char s[40]; //сюда копируем названия csm при переборе которое затем сравнивается с названием/адресом введенным в конфиге
char s1[40]; //просто строка. я ее использую для индикации активности csm в хтаске
void taimer()
{
  int c,j;
//здесь Идет перебор всех csm. можно вообще-то сделать и без него... я делал его для своих целей...
 csm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next;
  do{
      CSM_DESC *desc=csm->constr;
      sprintf(s,"%08X",desc);
  }while((csm=csm->next)&&(s!=CSM_ID));
  c=strcmp(s,CSM_ID);
  if((CSM_root()->csm_q->current_msg_processing_csm==csm))
  {
    if(c==0)
	{
      datagui=GetTopGUI(); 
      if (datagui) 
      {
      //делай здесь че хочешь пока csm активен
      sprintf(s1,"%s - active",CSM_ID);
      }
    }
	else
	{
    //делай здесь че хочешь пока csm НЕактивен
    sprintf(s1,"%s - notactive",CSM_ID);
    }
  }
  else
  {
	//ТА ЖЕ ЛАЖА
	sprintf(s1,"%s - notactive",CSM_ID);
  } 
  UpdateCSMname();
  GBS_StartTimerProc(&timer,50,taimer);
}