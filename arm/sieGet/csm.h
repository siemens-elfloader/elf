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

typedef struct
{
  CSM_RAM csm;
  int gui_id;
} MAIN_CSM;

#ifdef NEWSGOLD
typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;
#endif

typedef struct
{
  CSM_DESC csm;
  WSHDR csm_name;
#ifdef NEWSGOLD
  ICONBAR_H iconbar_handler;
#endif
  AbstractCSM *csm_class;
} EXTRA_CSM_DESC;

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
  EXTRA_CSM_DESC *desc;
};

#endif
