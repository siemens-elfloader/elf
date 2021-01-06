#ifndef _CODE_H_
  #define _CODE_H_


void init_font_lib(void);
void free_font_lib(void);
// GB2UC
void ascii2ws(WSHDR *ws, const char *s, int maxlen);

// UC2GB
void ws2ascii(WSHDR *ws, char *s, int maxlen);

#endif
