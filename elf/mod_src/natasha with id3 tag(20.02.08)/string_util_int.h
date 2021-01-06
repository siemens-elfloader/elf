#ifndef _STRING_UTIL_INT_H_
  #define _STRING_UTIL_INT_H_


void InitLng(int lngType); // 0 - RU; 1 - CZ/SK; 2 - Latvian (Baltic)

char* convUTF8_to_ANSI_STR_int(char *UTF8_str);
void ascii2ws_int(WSHDR *ws_dst, const char *src, int max_len);
void ws2ascii_int(WSHDR *ws_src, char *dst, int maxlen);

unsigned int char16to8_int(unsigned int c);
unsigned int char8to16_int(int c);

#endif


