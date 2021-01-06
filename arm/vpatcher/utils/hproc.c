//������� "HIGH_PROC" ���������� ����������
#include "..\..\inc\swilib.h"
#include "hproc.h"



// ���������� GBS ���������� �������� "HIGH_PROC"
void proc_HPROC(void)
{
  GBS_MSG msg;
  if (GBS_RecActDstMessage(&msg))
  {
   if (msg.msg == HPROC_MSG)
    {
      if (msg.data0)
      {
	((void (*)(void *, int))(msg.data0))(msg.data1,msg.submess);
      }
    }
   if (msg.msg == HPROC_KILL)
    {
      if (msg.data0)
      {
	SUBPROC((void *)msg.data0);
      }
    }
      else
       {
         GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,msg.pid_from,msg.msg,msg.submess);
       }
  }
}


//�������� GBS �������� "HIGH_PROC"
void Create_HPROC()
{
  Kill_HPROC();
  static const char hp_name[]=HPROC_NAME;
  CreateGBSproc(HPROC_ID, hp_name, proc_HPROC, HPROC_PRIO, 0);
}

//����������� GBS �������� "HIGH_PROC"
void Kill_HPROC()
{
  KillGBSproc(HPROC_ID);
}

//����� �-�� � �������� � ���������� �����������
void Kill_HPROC_MSG(void *f)
{
  GBS_SendMessage(HPROC_ID, HPROC_KILL, 0, f);
}

//����� �-�� � �������� � ���������� �����������
void HIGHPROC(void *f,  void *p1, int p2)
{
  GBS_SendMessage(HPROC_ID,HPROC_MSG,p2,f,p1);
}
