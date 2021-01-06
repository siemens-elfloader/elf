#ifndef _SEARCH_H_
#define _SEARCH_H_

void procSearchResult(WSHDR* ws);
void searchForward(void);
void searchBackward(void);
void freeSearchStr(void);
extern char* searchstr;
extern int searchstrlen;
#endif
