#ifndef _ENCODE_H
#define _ENCODE_H

void ascii2ws(WSHDR *ws, const char *s);
void koi2ws(WSHDR *ws, const char *s);
void dos2ws(WSHDR *ws, const char *s);
void dos2utf8(const char* s);
int utf82win(char* utf8);

#endif
