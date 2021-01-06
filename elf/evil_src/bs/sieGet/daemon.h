#ifndef _DAEMON_H_
#define _DAEMON_H_

#include "include.h"
#include "csm.h"
#include "../inc/sieget_ipc.h"
#include "internal_ipc.h"
#include "dialog.h"

#include "socket.h"
#include "dns.h"
#include "inet.h"

#include "iconpack.h"

#define DAEMON_CSM_NAME "SieGetD"

class SieGetDaemon: public DaemonCSM
{
public:
  virtual void onCreate();
  virtual int onMessage(GBS_MSG *msg);
  void onMessageHelper(GBS_MSG *msg);
  virtual void onClose();

  void ProcessIPC(const char *from, int submsg, void *data);
  void ProcessSocket(int id, int event); // HELPER
  void ProcessDNR(int DNR_ID); // HELPER

  SieGetDaemon();
  ~SieGetDaemon();

  SieGetDialog * dialog;
  
  LangPack * lgp;
  IconPack * icp;

  DownloadHandler * DL_Handler;
  DNRHandler * DNR_Handler;
  
private:
  IPC_REQ Lipc;  //Для внутренней связи
  SIEGET_INTERNAL_IPC tint_ipc;
};

#endif
