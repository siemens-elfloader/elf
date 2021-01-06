
#include "include.h"
#include "../inc/xtask_ipc.h"
#include "daemon.h"

char sieget_ipc_name[] = SIEGET_IPC_NAME;
char xtask_ipc_name[]= IPC_XTASK_NAME;

const char _req[] = "HEAD / HTTP/1.1\r\n"
"Host: rambler.ru\r\n"
"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\n"
"Connection: close\r\n"
"\r\n";

void SieGetDaemon::onCreate()
{
  SetName(DAEMON_CSM_NAME);

  tipc.name_to = sieget_ipc_name;
  tipc.name_from = sieget_ipc_name;
  tipc.data = &tint_ipc;
  tint_ipc.code = IPC_CODE_DOUBLEREQ;
  tint_ipc.csm_id = csm_id;
  GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_SIEGET_INTERNAL, &tipc);

  dialog->Create();

  //test_req->Start(_req, htonl(IP_ADDR(81,19,70,3)), 80);
  test_req->Start(_req, "rambler.ru", 80);
}

void MessageToHelper(SieGetDaemon *daemon, GBS_MSG *msg)
{
  daemon->onMessageHelper(msg);
  delete msg;
}

int SieGetDaemon::onMessage(GBS_MSG *msg)
{
  if (msg->msg==MSG_IPC )
  {
    IPC_REQ *ipc;
    if (ipc = (IPC_REQ *)msg->data0)
      // Обработка IPC сообщений
      if (!strcmp(ipc->name_to, SIEGET_IPC_NAME))
      {
        //Наше сообщение
        ProcessIPC(ipc->name_from, msg->submess, ipc->data);
      }
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    GBS_MSG *tmp_msg = new GBS_MSG;
    *tmp_msg = *msg;
    SUBPROC((void *)MessageToHelper, this, tmp_msg);
  }
  return CSM_MSG_RESULT_CONTINUE;
}

void SieGetDaemon::onMessageHelper(GBS_MSG *msg) // HELPER
{
  if ((int)msg->data0==ENIP_DNR_HOST_BY_NAME)
      ProcessDNR((int)msg->data1);
    else
    {
      ProcessSocket((int)msg->data1, (int)msg->data0);
    }
}

void SieGetDaemon::ProcessIPC(const char *from, int submsg, void *data)
{
  if (submsg==IPC_SIEGET_INTERNAL)
  {
    SIEGET_INTERNAL_IPC *int_ipc;
    if (int_ipc = (SIEGET_INTERNAL_IPC *)data)
      switch(int_ipc->code)
      {
      case IPC_CODE_DOUBLEREQ:
        if (int_ipc->csm_id!=csm_id) // Не надо отвечать на свой запрос, а то от него другие дохнут
        {
          tipc.name_to = sieget_ipc_name;
          tipc.name_from = sieget_ipc_name;
          tipc.data = &tint_ipc;
          tint_ipc.code = IPC_CODE_DOUBLERESP;
          tint_ipc.csm_id = csm_id;
          GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_SIEGET_INTERNAL, &tipc);

          if (!dialog->csm_id)
            dialog->Create();
          else
          {
            tipc2.name_to = xtask_ipc_name;
            tipc2.name_from = sieget_ipc_name;
            tipc2.data = (void *)dialog->csm_id;
            GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_XTASK_SHOW_CSM, &tipc2);
          }
        }
        break;
      case IPC_CODE_DOUBLERESP:
        if (int_ipc->csm_id!=csm_id) // Есть кто-то кроме нас
        {
          Close();
        }
      }
  }
}

void SieGetDaemon::ProcessSocket(int id, int event)
{
  char tmp[128];

  LockSched();
  Socket *sock = NULL;
  for (Socket *tsock = Socket::TopSocket; tsock && !sock; tsock = tsock->NextSocket)
    if (tsock->id==id)
      sock = tsock;
  UnlockSched();

  if (sock)
  {
    switch(event)
    {
    case ENIP_SOCK_CONNECTED: //Соединение через сокет установлено
      sock->state = SOCK_CONNECTED;
      sock->onConnected();
      break;

    case ENIP_SOCK_DATA_READ: //Готовность данных к получению
      sock->onDataRead();
      break;

    case ENIP_SOCK_REMOTE_CLOSED: //Соединение разорвано сервером
      sock->onRemoteClose();
      break;

    case ENIP_SOCK_CLOSED: //Соединение разрвано клиентом
      sock->id = -1;
      sock->onClose();
      break;

    case ENIP_BUFFER_FREE: //Буфер отпраки пуст
      //To be implemented...
      break;

    case ENIP_BUFFER_FREE1: //Буфер отпраки пуст (в чем разница? - хз)
      //To be implemented...
      break;

    default:
      sprintf(tmp, "Socket %d: [0x%X]", id, event);
      Log::Active->PrintLn(tmp);
    }
  }
}

void SieGetDaemon::ProcessDNR(int DNR_ID)
{
  char tmp[64];
  sprintf(tmp, "DNR %d", DNR_ID);
  Log::Active->PrintLn(tmp);

  LockSched();
  DNR *dnr = NULL;
  for (DNR *tdnr = DNR::DNRTop; tdnr && !dnr; tdnr = tdnr->DNRNext)
    if (tdnr->DNR_ID==DNR_ID)
      dnr = tdnr;
  UnlockSched();
  if (dnr)
    dnr->SendReq();
}

void SieGetDaemon::onClose()
{
  dialog->Close();
  delete this; // суицид
}


SieGetDaemon::SieGetDaemon()
{
  log = new Log();
  dialog = new SieGetDialog();
  test_req = new HttpHead();
  log->PrintLn("Daemon created!");
}

extern "C"
{
  extern void kill_data(void *p, void (*func_p)(void *));
}

void Killer(void){
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
  //  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

SieGetDaemon::~SieGetDaemon()
{
  delete dialog;
  delete log;
  delete test_req;
  SUBPROC((void *)Killer);
}

