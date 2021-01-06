unsigned int char8to16(int c);
unsigned int char16to8(unsigned int c);
void ascii2ws(WSHDR *ws, const char *s);
char *MakeGlobalString(const char *first, int breakchar, const char *last);
int strcmp_nocase(const char *s, const char *d);
int convWS_to_ANSI(WSHDR *ws, char *buf);
