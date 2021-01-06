#ifndef _CODE_H_
#define _CODE_H_

extern int codetype;

int getCodeType(char* str);
void str2ws_unicode(WSHDR* ws, char* str, int len);
void ws2str_unicode(char* str, WSHDR* ws, int *len);
char * unicodeSwitch(char *str, int len, int *rlen, int *llen);
char * gb2unicode(char *str, int len, int *rlen, int *llen);
char * utf82unicode(char *str, int len, int *rlen, int *llen);
char * unicode2gb(char *str, int *len);
char * unicode2utf8(char *str, int *len);

#endif
