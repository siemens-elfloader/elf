#ifndef _HISTORY_H_
  #define _HISTORY_H_

#include "naticq.h"

void Add2History(CLIST *CListEx, char *header, char *message, int direction);
void LogStatusChange(CLIST *CListEx);
int GetHistory(CLIST *t, int bufsize);

#endif
