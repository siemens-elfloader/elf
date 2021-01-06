enum {WIN_1251, KOI8_R, ISO_8859_5, UTF_8};

char * base64_decode(const char *str, size_t *size);
char * quoted_printable_decode(const char *str, size_t *size);
void koi2win(char*d,const char *s);
void iso885952win(char*d,const char *s);
void utf82win(char*d,const char *s);
void strip_html(char *s);
int get_charset(char *charset);
char *unmime_header(const char *encoded_str, int default_charset);
extern char *strstr_nocase(const char *s1, const char *s2);
