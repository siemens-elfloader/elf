int strcmp_nocase(const char *s1,const char *s2);
char *MakeGlobalString(const char *first, int breakchar, const char *last);
void ascii2ws(WSHDR *ws, const char *s);
int char16to8(int c);
void utf82win(char*d,const char *s);
