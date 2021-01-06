#ifndef _CSM_H_
#define _CSM_H_

#include "include.h"

// Константы результата onMessage()
#define CSM_MSG_RESULT_CONTINUE 1
#define CSM_MSG_RESULT_STOP 0

class AbstractCSM
{
public:
  virtual void onCreate() = 0;
  virtual int onMessage(GBS_MSG *msg) = 0;
  virtual void onClose() = 0;

  virtual void Create() = 0;
  void Close();
  void SetName(char *name);

  AbstractCSM();

  WSHDR *name;
  int csm_id;
  CSM_RAM *data;
};

class DialogCSM: public AbstractCSM
{
public:
  virtual void Create();
  ~DialogCSM();
};

class DaemonCSM: public AbstractCSM
{
public:
  virtual void Create();
  ~DaemonCSM();
};

#endif
