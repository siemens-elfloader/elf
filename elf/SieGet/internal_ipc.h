#ifndef _INTERNAL_IPC_H_
#define _INTERNAL_IPC_H_

#include "../inc/sieget_ipc.h"

// Запрос запущенной копии
#define IPC_CODE_DOUBLEREQ 0
#define IPC_CODE_DOUBLERESP 1

#define IPC_SIEGET_INTERNAL 0xFADE

typedef struct
{
  int csm_id;
  int code;
} SIEGET_INTERNAL_IPC;

#endif
