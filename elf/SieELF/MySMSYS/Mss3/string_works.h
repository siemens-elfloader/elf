#ifndef _STRING_WORKS_H_
#define _STRING_WORKS_H_

#define MATCH_FAIL 0
#define MATCH_NML 1
#define MATCH_FETION 2

void ws_2ascii(WSHDR *ws, char *str, int maxlen);
void ascii_2ws(WSHDR *ws, const char *s, int maxlen);
int wstrncmp_nocase(WSHDR *ws1, WSHDR *ws2, int n);
int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2);
void wsInsert(WSHDR *ws, WSHDR *txt, int pos, int max); //start form 0;
int num_2ws(WSHDR *ws, const char *num, int maxlen);
int ws_2num(WSHDR *ws, char *num, int maxlen);
int str2int(const char *str);
int IsWsSmall(WSHDR *ws);
int IsNum(WSHDR *num);
int w_charcmp_nocase(unsigned short *t1, unsigned short *t2, int len);
unsigned short *wstrstr(WSHDR *wstr, WSHDR *ws);
int NumberMatch(const char *num1, const char *num2);
void StrClearChr(char *str, int chr);
#endif
