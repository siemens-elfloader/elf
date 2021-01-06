#ifndef __MSIM_MSG_H__
#define __MSIM_MSG_H__
  extern void ChangeSIM(int SimNum);
  
  int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg);
  __arm void initMsg(void);
  void SendReply(int submess, void *data);
#endif
