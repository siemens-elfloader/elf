#include "include.h"
#include "csm.h"

const int minus11=-11;
const char percent_t[] = "%t";

void csm_oncreate(CSM_RAM *data);
int csm_onmessage(CSM_RAM* data,GBS_MSG* msg);
void csm_onclose(CSM_RAM *data);

typedef struct
{
  unsigned int size;
  IMGHDR *img;
}IMG;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
  IMG img;
} MAIN_CSM;

typedef struct
{
  CSM_DESC csm;
  WSHDR csm_name;
  AbstractCSM *csm_class;
} EXTRA_CSM_DESC;

const EXTRA_CSM_DESC TEMPLATECSM =
{
  {
    csm_onmessage,
    csm_oncreate,
#ifdef NEWSGOLD
    0,
    0,
    0,
    0,
#endif
    csm_onclose,
sizeof(CSM_RAM),
    1,
    &minus11
  },
  {
    NULL,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  },
  NULL
};

void csm_oncreate(CSM_RAM *data)
{
  data->state=0;
  data->unk1=0;
  EXTRA_CSM_DESC *desc = (EXTRA_CSM_DESC *)data->constr;
  desc->csm_class->data = data;
  desc->csm_class->onCreate();
}

int csm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  EXTRA_CSM_DESC *desc = (EXTRA_CSM_DESC *)data->constr;
  return desc->csm_class->onMessage(msg);
}

void csm_onclose(CSM_RAM *data)
{
  LockSched();
  EXTRA_CSM_DESC *desc = (EXTRA_CSM_DESC *)data->constr;
  desc->csm_class->onClose();
  desc->csm_class->name = NULL;
  desc->csm_class->csm_id = 0;
  desc->csm_class->data = NULL;
  delete desc->csm_name.wsbody;
  delete desc;
  UnlockSched();
}

//============================   AbstractCSM   =========================================

void AbstractCSM::Close()
{
  if (csm_id)
    CloseCSM(csm_id);
}

void AbstractCSM::SetName(char *name)
{
  if (this->name)
    wsprintf(this->name, percent_t, name);
}

AbstractCSM::AbstractCSM()
{
  name = NULL;
  csm_id = 0;
}

//============================   DialogCSM   ===========================================

void DialogCSM::Create()
{
  char dummy[sizeof(MAIN_CSM)];
  EXTRA_CSM_DESC *desc = new EXTRA_CSM_DESC;
  memcpy(desc, &TEMPLATECSM, sizeof(EXTRA_CSM_DESC));
  desc->csm_name.wsbody = new unsigned short[desc->csm_name.maxlen+1];
  this->name = &(desc->csm_name);
  desc->csm_class = this;

  LockSched();
  this->csm_id = CreateCSM((CSM_DESC *)desc, dummy, 0);
  UnlockSched();
}

DialogCSM::~DialogCSM()
{
  if (csm_id)
    Close();
}

//============================   DaemonCSM   ===========================================

void DaemonCSM::Create()
{
  char dummy[sizeof(MAIN_CSM)];
  EXTRA_CSM_DESC *desc = new EXTRA_CSM_DESC;
  memcpy(desc, &TEMPLATECSM, sizeof(EXTRA_CSM_DESC));
  desc->csm_name.wsbody = new unsigned short[desc->csm_name.maxlen+1];
  this->name = &(desc->csm_name);
  desc->csm_class = this;

  CSM_RAM *save_cmpc;
  LockSched();
  save_cmpc = CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm = (CSM_RAM *)CSM_root()->csm_q->csm.first;
  this->csm_id = CreateCSM((CSM_DESC *)desc, dummy, 0);
  CSM_root()->csm_q->current_msg_processing_csm = save_cmpc;
  UnlockSched();
}

DaemonCSM::~DaemonCSM()
{
  if (csm_id)
    Close();
}

//=======================================================================================




