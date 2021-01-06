//#include "view.h"

void debugf(char *file,int line);
#define DEBUGF(void) debugf(__FILE__,__LINE__)
void debugv(char *file,int line,void *p, int sz);
#define DEBUGV(a,b) debugv(__FILE__,__LINE__,a,b)
#define DEBUGC(a) debugv(__FILE__,__LINE__,a,strlen(a))
#define DEBUGS(a,b) {static char c[512];sprintf(c,a,b);DEBUGV(c,strlen(c));}
unsigned int _rshort2(char *p);
int strcmp_nocase(const char *s, const char *d);
//int omstrcmp(VIEWDATA *vd, unsigned int ps, unsigned int pd);
char *globalstr(const char *s);
void freegstr(char **ps);
char *replacegstr(char **ps, const char *s, int len);
int char16to8(int c);
int char8to16(int c);
void ascii2ws(WSHDR *ws, const char *s);
//char *extract_omstr(VIEWDATA *vd, unsigned int pos);
int char_win2utf8(char*d,const char *s);
char * ToWeb(char *src,int special);
void oms2ws(WSHDR *ws, const char *text, int len);
void utf82win(char*d,const char *s);
