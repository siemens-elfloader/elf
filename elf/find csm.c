//���������� CSM_ID �������������� �������� csm ������� ����� ������ � �������
GBSTMR timer;
GUI *datagui;
CSM_RAM *csm
char s[40]; //���� �������� �������� csm ��� �������� ������� ����� ������������ � ���������/������� ��������� � �������
char s1[40]; //������ ������. � �� ��������� ��� ��������� ���������� csm � ������
void taimer()
{
  int c,j;
//����� ���� ������� ���� csm. ����� ������-�� ������� � ��� ����... � ����� ��� ��� ����� �����...
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
      //����� ����� �� ������ ���� csm �������
      sprintf(s1,"%s - active",CSM_ID);
      }
    }
	else
	{
    //����� ����� �� ������ ���� csm ���������
    sprintf(s1,"%s - notactive",CSM_ID);
    }
  }
  else
  {
	//�� �� ����
	sprintf(s1,"%s - notactive",CSM_ID);
  } 
  UpdateCSMname();
  GBS_StartTimerProc(&timer,50,taimer);
}