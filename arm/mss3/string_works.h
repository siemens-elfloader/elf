
void ws_2ascii(WSHDR *ws, char *str, int maxlen);
void ascii_2ws(WSHDR *ws, const char *s, int maxlen);
int wstrncmp_nocase(WSHDR *ws1, WSHDR *ws2, int n);
int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2);
void wsInsert(WSHDR *ws, WSHDR *txt, int pos, int max); //start form 0;
int num_2ws(WSHDR *ws, const char *num, int maxlen);
int ws_2num(WSHDR *ws, char *num, int maxlen);
int str2int(const char *str);

