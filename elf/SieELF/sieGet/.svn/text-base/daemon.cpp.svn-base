/*******************************************************************************
  SieGetDaemon
*******************************************************************************/

#include "include.h"
#include "daemon.h"
#include "conf_loader.h"

char sieget_ipc_name[] = SIEGET_IPC_NAME;

void SieGetDaemon::onCreate()
{
  SetName(DAEMON_CSM_NAME);
  
  Lipc.name_to = sieget_ipc_name;
  Lipc.name_from = sieget_ipc_name;
  Lipc.data = &tint_ipc;
  tint_ipc.code = IPC_DOUBLEREQ;
  tint_ipc.csm_id = csm_id;
  GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_SIEGET_INTERNAL, &Lipc);
}

void MessageToHelper(SieGetDaemon * daemon, GBS_MSG * msg)
{
  daemon->onMessageHelper(msg);
  delete msg;
}

int SieGetDaemon::onMessage(GBS_MSG *msg)
{
  if (msg->msg==MSG_IPC ) // IPC
  {
    IPC_REQ *ipc;
    if (ipc = (IPC_REQ *)msg->data0)
      // Обработка IPC сообщений
      if(!stricmp(ipc->name_to, sieget_ipc_name))
        ProcessIPC(ipc->name_from, msg->submess, ipc->data);
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR) // HELPER
  {
    GBS_MSG *tmp_msg = new GBS_MSG;
    *tmp_msg = *msg;
    SUBPROC((void *)MessageToHelper, this, tmp_msg);
  }
  if(msg->msg == MSG_RECONFIGURE_REQ) // CONFIG 
  {
    extern const char * successed_config_filename;
    if (!stricmp(successed_config_filename,(char *)msg->data0))
    {
      InitConfig(); // Обновляем конфиг
      //lgp->Setup(); // Обновляем ленгпак
      icp->Setup(); // Обновляем иконки
    }
  }
  // Рисуем иконку на IDLE
  //#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM * data = FindCSMbyID(CSM_root()->idle_id);
  if(IsGuiOnTop(((int *)data)[DISPLACE_OF_IDLEGUI_ID/4]))
  {
    GUI * igui = GetTopGUI();
    if (igui)
    {
      void * CanvasData;
#ifdef ELKA
      {
        CanvasData = BuildCanvas();
#else
      void * idata = GetDataOfItemByID(igui,2);
      if (idata)
      {
        CanvasData = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
        DrawCanvas(CanvasData , CFG_IDLE_ICON_X,  CFG_IDLE_ICON_Y, 
               CFG_IDLE_ICON_X + GetImgWidth(DL_Handler->IsAnyDownloadActive()?IconPack::Active->data[IMG_Downloading]:IconPack::Active->data[IMG_Logo]), 
               CFG_IDLE_ICON_Y + GetImgHeight(DL_Handler->IsAnyDownloadActive()?IconPack::Active->data[IMG_Downloading]:IconPack::Active->data[IMG_Logo]), 1);
        DrawImg(CFG_IDLE_ICON_X,  CFG_IDLE_ICON_Y, DL_Handler->IsAnyDownloadActive()?IconPack::Active->data[IMG_Downloading]:IconPack::Active->data[IMG_Logo]);
  
      }
    }
  }
  return CSM_MSG_RESULT_CONTINUE;
}

void SieGetDaemon::onMessageHelper(GBS_MSG * msg) // HELPER
{
  if((int)msg->data0==ENIP_DNR_HOST_BY_NAME)
    ProcessDNR((int)msg->data1); // DNR
  else
    ProcessSocket((int)msg->data1, (int)msg->data0); // Socket
}

void SieGetDaemon::ProcessIPC(const char * from, int submsg, void * data) // IPC
{
  if (submsg==IPC_SIEGET_INTERNAL)
  {
    SIEGET_INTERNAL_IPC *int_ipc;
    if (int_ipc = (SIEGET_INTERNAL_IPC *)data)
    {
      switch(int_ipc->code)
      {
      case IPC_DOUBLEREQ:
        if (int_ipc->csm_id!=csm_id) // Не надо отвечать на свой запрос, а то от него другие дохнут
        {
          Lipc.name_to = sieget_ipc_name;
          Lipc.name_from = sieget_ipc_name;
          Lipc.data = &tint_ipc;
          tint_ipc.code = IPC_DOUBLERESP;
          tint_ipc.csm_id = csm_id;
          GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_SIEGET_INTERNAL, &Lipc);

          dialog->Show(NULL);
        }
        break;
      case IPC_DOUBLERESP:
        if (int_ipc->csm_id != csm_id) // Есть кто-то кроме нас
        {
          if(dialog->csm_id)
            dialog->Close();
          Close();
        }
        break;
      }
    }
  }
  if (submsg == SIEGET_GOTO_URL)
  {
    dialog->Show((char *)data); // Открываем диалог
  }
}

void SieGetDaemon::ProcessSocket(int id, int event)
{
  char * tmp_msg;
  Download * download = NULL;
  if (download = DL_Handler->GetDownloadbyID(id))
  {
    switch(event)
    {
    case ENIP_SOCK_CONNECTED: //Соединение через сокет установлено
      download->log->Print(LangPack::Active->data[LGP_SocketConnected], CLR_Grey);
      download->socket_state = SOCK_CONNECTED;
      download->onConnected();
      break;

    case ENIP_SOCK_DATA_READ: //Готовность данных к получению
      download->onDataRead();
      break;

    case ENIP_SOCK_REMOTE_CLOSED: //Соединение разорвано сервером
      download->log->Print(LangPack::Active->data[LGP_SocketRemoteClosed], CLR_Grey);
      download->onRemoteClose();
      break;

    case ENIP_SOCK_CLOSED: //Соединение разорвано клиентом
      download->log->Print(LangPack::Active->data[LGP_SocketClosed], CLR_Grey);
      download->socket_id = -1;
      download->onClose();
      break;

    case ENIP_BUFFER_FREE: //Буфер отпраки пуст
    case ENIP_BUFFER_FREE1:
      download->log->Print("Socket buffer free", CLR_Grey);
      //To be implemented...
      break;

    default:
      tmp_msg=new char[64];
      sprintf(tmp_msg, "Socket %d: [0x%X]", id, event);
      download->log->Print(tmp_msg, CLR_Grey);
      delete tmp_msg;
    }
  }
}

void SieGetDaemon::ProcessDNR(int DNR_ID)
{
  DNR * dnr = NULL;
  if(dnr = DNR_Handler->GetDNR(DNR_ID))
      dnr->SendReq();
}

void SieGetDaemon::onClose()
{
  delete this;
}

SieGetDaemon::SieGetDaemon()
{
  lgp = new LangPack;
  icp = new IconPack;
  DL_Handler = new DownloadHandler;
  DNR_Handler = new DNRHandler;
  dialog = new SieGetDialog();
}

extern "C"
{
  extern void kill_data(void *p, void (*func_p)(void *));
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

SieGetDaemon::~SieGetDaemon()
{
  GBS_DelTimer(&VibraTimer);
  delete lgp;
  delete icp;
  if(dialog->csm_id)
    dialog->Close();
  delete dialog;
  delete DNR_Handler;
  delete DL_Handler;
  SUBPROC((void *)Killer);
}
