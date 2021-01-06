#ifndef _STRING_H_
#define _STRING_H_

int strncmpNoCase(const char *s1,const char *s2,unsigned int n);
void str2bytes(char *bytes, char *str, int maxlen);
void str2ints(int *ints, char *str, int maxlen);
void str2num(char *str, int *num, int max, int min, int type);
void str2num_short(char *str, short *num, int max, int min, int type);
void str2num_char(char *str, char *num, int max, int min, int type);
int chr2num(char chr);

char *gotoRealPos(char *p);
char *strstrInQuote(char *pdata, const char *s);
char *strchrInQuote(char *pdata, char c);
char *gotoQuoteStart(char *pdata);
char *gotoQuoteEnd(char *pdata);
char *gotoNextNameQuote(char *pdata);
char *gotoStringEndByChr(char *p, char chr);
char *gotoMyStrStart(char *p);
char *gotoMyStrEnd(char *p);
void strnCopyWithEnd(char *dst, char *src, int n);
void cleanStrByChr(char *pdata, char chr);

#ifndef WINTEL_DEBUG
int getnumwidth(unsigned int num);
int str2hex(char *str, char *hex);
void uni2ws(WSHDR *ws, unsigned short *uni, int maxlen);
void hex2ws(WSHDR *ws, unsigned char *hex, int maxlen);
void uniFormatString2ws(WSHDR *ws, char *s);
int isUniFormat(char *s);
void ws2hex(WSHDR *ws, char *hex, int maxlen);
void bytes_2ws(WSHDR *ws, char *bytes, int maxlen);
void ints_2ws(WSHDR *ws, int *ints, int maxlen);
void ws2uni(WSHDR *ws, unsigned short *uni, int maxlen);
#endif

#endif

