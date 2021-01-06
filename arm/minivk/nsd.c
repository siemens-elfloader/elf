#include "..\inc\swilib.h"
#include "main.h"
#include "nsd.h"
#include "gui.h"
#include "internet.h"
extern int is_gprs_online,DNR_ID,DNR_TRIES,sock,connect_state,receive_mode;

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
   if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
      is_gprs_online=0;
      return(1);

    case LMAN_CONNECT_CNF:
      is_gprs_online=1;
      return(1);

    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      switch((int)msg->data0)
      {
      //Если наш сокет
      case ENIP_SOCK_CONNECTED:
        //Если посылали запрос
        free_buffers();
        if (connect_state==1)
        {
          receive_mode=0;
          connect_state=2;
          SUBPROC((void *)send_req);
        }
        break;

      case ENIP_SOCK_DATA_READ:
        //Если посылали send
        if (connect_state>=2)
        {
          SUBPROC((void *)get_answer);
        }
        break;

      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
	//Досылаем очередь
	SUBPROC((void *)send_answer,0,0);
	break;

      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        sprintf(logmsg,"Remote closed!");
        goto ENIP_SOCK_CLOSED_ALL;

      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        sprintf(logmsg,"Local closed!");
      ENIP_SOCK_CLOSED_ALL:
        //SMART_REDRAW();
	switch(connect_state)
	{
	case -1:
	  connect_state=0;
          //work
	  SUBPROC((void*)free_socket);
	  break;
	case 0:
	  break;
	default:
	  connect_state=-1;
	  SUBPROC((void*)end_socket);
	  break;
	}
        break;
      }
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
 
}


int my_keyhook(int key, int m)
{
  if(m==KEY_UP)
     if (key==KEY_START&&!gui_mode) 
       {
         create_connect();
         Create_GUI();
       }
  
  return 0;
}

static void Killer(void)
{
  RemoveKeybMsgHook((void *)my_keyhook);  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}


static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMDname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"nsd");
}

void Create_NSD()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMDname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();  
  gui_mode=0;
  AddKeybMsgHook((void *)my_keyhook);
}
