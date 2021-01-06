#include "..\..\inc\swilib.h"

//Процесс 'ELFPACK_MANAGER' (Бывший HELPER)
//Для некотрых операций, управлением ELFPACK'om 


#ifdef NEWSGOLD
#define EPC_PROCCEPID   0x440A
#else
#define EPC_PROCCEPID   0x4407
#endif

#define EPC_PROCNAME    "ELFPack Manager"
#define EPC_PROCPRIO    0x80

#define EPC_MSGFUNCRUN  0x0001 // SUBPROC
#define MSG_EPCLEARPNG  0x00EB // Очистить PNG-Кеш
#define MSG_EPLOADDAEM  0x00EC // Повторный запуск демонов
#define MSG_EPLOADEDLL  0x00ED // Повторный запуск EDL библиотек 
#define MSG_EPLOADLIBR  0x00EE // Повторная загрузка blib
#define MSG_EPRECONFIG  0x00EF // Реинициализация конфигурации

/* 0x00EB: GBS_SendMessage(EPC_PROCCEPID, MSG_EPCLEARPNG); */
/* 0x00EC: GBS_SendMessage(EPC_PROCCEPID, MSG_EPLOADDAEM); */
/* 0x00ED: GBS_SendMessage(EPC_PROCCEPID, MSG_EPLOADEDLL); */
/* 0x00EE: GBS_SendMessage(EPC_PROCCEPID, MSG_EPLOADLIBR); */
/* 0x00EF: GBS_SendMessage(EPC_PROCCEPID, MSG_EPRECONFIG); */


// Обработчик GBS сообщениий процесса "ELFPack Manager"
__arm void proc_EPC(void)
{
  GBS_MSG msg;
  if (GBS_RecActDstMessage(&msg))
  {
   int off = 0;
   if (msg.msg == EPC_MSGFUNCRUN)
    {
      if (msg.data0)
      {
	((void (*)(int, void *))(msg.data0))(msg.submess,msg.data1);
      }
    }
   
   
    if (msg.msg == MSG_EPCLEARPNG) 
    {
      extern void clear_cache();
      ShowMSG(1, (int)"EP 3.0:\nPNG Cashe Clear!");
      clear_cache();
      off = 1;
    }
   
   if (msg.msg == MSG_EPLOADEDLL) 
    {
      extern void LoadLibs();
      ShowMSG(1, (int)"EP 3.0:\nReLoadEDL!");
      LoadLibs();
      off = 1;
    }
   
    if (msg.msg == MSG_EPLOADDAEM) 
    {
      extern void LoadDaemons();
      ShowMSG(1, (int)"EP 3.0:\nReLoadDaems!");
      extern int subproc_daem;
      if (subproc_daem == 1)
      SUBPROC((void *)LoadDaemons);
      else LoadDaemons();
      off = 1;
    }
   
      if (msg.msg == MSG_EPLOADLIBR) 
    {
      extern void LoadLibrary();
      ShowMSG(1, (int)"EP 3.0:\nReLoadBLIB!");
      LoadLibrary();
      off = 1;
    }
   
   if (off == 0)
    {
      GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,msg.pid_from,msg.msg,msg.submess);
    }
  }
}


//Создание GBS Процесса "ELFPack Manager"
__arm void CreateEPC_PROC()
{
  extern unsigned int subproc_prio;
  CreateGBSproc(EPC_PROCCEPID, EPC_PROCNAME, proc_EPC, subproc_prio, 0);
}

//Уничтожение GBS Процесса "ELFPack Manager"
__arm void KillEPC_PROC()
{
  KillGBSproc(EPC_PROCCEPID);
}


//Вызов ф-ии в процессе с пониженным приоритетом
__arm void SUBPROC_impl(void *f, int p2, void *p1)
{
  GBS_SendMessage(EPC_PROCCEPID,EPC_MSGFUNCRUN,p2,f,p1);
}

#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC171 @ "SWILIB_FUNC171" = (int)SUBPROC_impl;
#pragma diag_default=Pe177
