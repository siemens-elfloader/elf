#ifndef _HISTORY_H_
  #define _HISTORY_H_

#include "naticq.h"

void Add2History(CLIST *CListEx, char *header, char *message);
void LogStatusChange(CLIST *CListEx);

#endif
