#include "include.h"
#include "MyIpcMessage.h"

const IPC_REQ IPC1=
{
  IPC_NAME,
  IPC_NAME,
  NULL
};

static IPC_REQ IPC2=
{
  IPC_NAME,
  IPC_NAME,
  NULL
};
/*
void MyIpcMessage::SendIpc(int submess)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submess,&IPC1);
}

void MyIpcMessage::SendIpc(int submess, void *data)
{
  LockSched();
  IPC2.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submess,&IPC2);
  UnlockSched();
}
*/
void SendMyIpc(int submess)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submess,&IPC1);
}

void SendMyIpc(int submess, void *data)
{
  LockSched();
  IPC2.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submess,&IPC2);
  UnlockSched();
}
