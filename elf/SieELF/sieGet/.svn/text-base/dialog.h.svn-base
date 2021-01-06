#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "include.h"
#include "csm.h"
#include "list.h"
#include "url_input.h"
#include "langpack.h"

#define DIALOG_CSM_NAME "SieGet"

class SieGetDialog: public DialogCSM
{
public:
  virtual void onCreate();
  virtual int onMessage(GBS_MSG *msg);
  virtual void onClose();
  void Show(char * _url);
  void ProcessIPC(const char * from, int submsg, void * data);
  
  SieGetDialog();
  ~SieGetDialog();
  List * list;
  static SieGetDialog * Active;
  
  void RefreshList();
private:
  IPC_REQ Xipc; // Для связи с XTASK
  char * url;
};

#endif
