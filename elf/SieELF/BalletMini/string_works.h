#ifndef _STRING_WORKS_H_
#define _STRING_WORKS_H_

#include "view.h"

#define _safe_free(x) { if (x) mfree(x); (x) = NULL; }

void debugf(char *file,int line);
void debugv(char *file,int line,void *p, int sz);
void debuf(void *p, int sz);
#define DEBUGF(void) debugf(__FILE__,__LINE__)
#define DEBUGV(a,b) debugv(__FILE__,__LINE__,a,b)
#define DEBUGC(a) debugv(__FILE__,__LINE__,a,strlen(a))
#define DEBUGS(a,b) {static char c[128];sprintf(c,a,b);DEBUGV(c,strlen(c));}
#define DEBUFC(a) debuf(a,strlen(a))
#define DEBUFV(a,b) debuf(a,b)
#define DEBUFS(a,b) {static char c[128];sprintf(c,a,b);debuf(c,strlen(c));}
#define DEBUFF(void) {static char c[128];sprintf(c,"%s : %i\n",__FILE__,__LINE__);debuf(c,strlen(c));}

unsigned int _rshort2(char *p);
int strcmp_nocase(const char *s, const char *d);
int omstrcmp(VIEWDATA *vd, unsigned int ps, unsigned int pd);
char *globalstr(const char *s);
void freegstr(char **ps);
char *replacegstr(char **ps, const char *s, int len);
int char16to8(int c);
int char8to16(int c);
void ascii2ws(WSHDR *ws, const char *s);
char *extract_omstr(VIEWDATA *vd, unsigned int pos);
int char_win2utf8(char*d,const char *s);
char * ToWeb(char *src,int special);
void oms2ws(WSHDR *ws, const char *text, int len);
void utf82win(char*d,const char *s);

#endif /* _STRING_WORKS_H_ */
