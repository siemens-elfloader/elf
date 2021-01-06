#ifndef _INTERNAL_IPC_H_
#define _INTERNAL_IPC_H_

#include "../inc/sieget_ipc.h"

// Запрос запущенной копии
enum IPC_CODE
{
  IPC_DOUBLEREQ,
  IPC_DOUBLERESP
};

#define IPC_REFRESH_LIST 1
#define IPC_SIEGET_INTERNAL 0xFADE

typedef struct
{
  int csm_id;
  enum IPC_CODE code;
} SIEGET_INTERNAL_IPC;

#endif
