#include "../inc/swilib.h"
#include "strings.h"
#define wslen(ws) ws->wsbody[0]

#define EZXML_BUFSIZE 1024

char *utf16_to_utf8(char **s, size_t *len)
{
    char *u;
    size_t l = 0, sl, max = *len;
    long c, c2;
    int b, be = 0;
    if (be == -1) return NULL; 
    u = malloc(max); zeromem(u, max);
        for (sl = 2; sl <= *len ; sl += 2) {
      c = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : 
	((long)(*s)[sl + 1] << 8) | (*s)[sl];  
      if (c >= 0xD800 && c <= 0xDFFF && (sl += 2) < *len - 1) { 
	c2 = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : 
	  ((long)(*s)[sl + 1] << 8) | (*s)[sl];  
            c = (((c & 0x3FF) << 10) | (c2 & 0x3FF)) + 0x10000;
        }
        while (l + 6 > max) u = realloc(u, max += EZXML_BUFSIZE);
        if (c < 0x80) u[l++] = c; 
        else { 
	  for (b = 0, c2 = c; c2; c2 /= 2) b++; 
	  b = (b - 2) / 5; 
	  u[l++] = (0xFF << (7 - b)) | (c >> (6 * b)); 
	  while (b) u[l++] = 0x80 | ((c >> (6 * --b)) & 0x3F); 
        }
    }
    *len = l;
    u = realloc(u, l+1);
    return u;
}

char *ws2utf8(WSHDR *ws)
{
   size_t len = wslen(ws)*2;
   char* body =  utf16_to_utf8((char**)ws,&len);
   body[len]='\0';
   return body;
}


char *hex[] = {
    "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07",
    "%08", "%09", "%0a", "%0b", "%0c", "%0d", "%0e", "%0f",
    "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17",
    "%18", "%19", "%1a", "%1b", "%1c", "%1d", "%1e", "%1f",
    "%20", "%21", "%22", "%23", "%24", "%25", "%26", "%27",
    "%28", "%29", "%2a", "%2b", "%2c", "%2d", "%2e", "%2f",
    "%30", "%31", "%32", "%33", "%34", "%35", "%36", "%37",
    "%38", "%39", "%3a", "%3b", "%3c", "%3d", "%3e", "%3f",
    "%40", "%41", "%42", "%43", "%44", "%45", "%46", "%47",
    "%48", "%49", "%4a", "%4b", "%4c", "%4d", "%4e", "%4f",
    "%50", "%51", "%52", "%53", "%54", "%55", "%56", "%57",
    "%58", "%59", "%5a", "%5b", "%5c", "%5d", "%5e", "%5f",
    "%60", "%61", "%62", "%63", "%64", "%65", "%66", "%67",
    "%68", "%69", "%6a", "%6b", "%6c", "%6d", "%6e", "%6f",
    "%70", "%71", "%72", "%73", "%74", "%75", "%76", "%77",
    "%78", "%79", "%7a", "%7b", "%7c", "%7d", "%7e", "%7f",
    "%80", "%81", "%82", "%83", "%84", "%85", "%86", "%87",
    "%88", "%89", "%8a", "%8b", "%8c", "%8d", "%8e", "%8f",
    "%90", "%91", "%92", "%93", "%94", "%95", "%96", "%97",
    "%98", "%99", "%9a", "%9b", "%9c", "%9d", "%9e", "%9f",
    "%a0", "%a1", "%a2", "%a3", "%a4", "%a5", "%a6", "%a7",
    "%a8", "%a9", "%aa", "%ab", "%ac", "%ad", "%ae", "%af",
    "%b0", "%b1", "%b2", "%b3", "%b4", "%b5", "%b6", "%b7",
    "%b8", "%b9", "%ba", "%bb", "%bc", "%bd", "%be", "%bf",
    "%c0", "%c1", "%c2", "%c3", "%c4", "%c5", "%c6", "%c7",
    "%c8", "%c9", "%ca", "%cb", "%cc", "%cd", "%ce", "%cf",
    "%d0", "%d1", "%d2", "%d3", "%d4", "%d5", "%d6", "%d7",
    "%d8", "%d9", "%da", "%db", "%dc", "%dd", "%de", "%df",
    "%e0", "%e1", "%e2", "%e3", "%e4", "%e5", "%e6", "%e7",
    "%e8", "%e9", "%ea", "%eb", "%ec", "%ed", "%ee", "%ef",
    "%f0", "%f1", "%f2", "%f3", "%f4", "%f5", "%f6", "%f7",
    "%f8", "%f9", "%fa", "%fb", "%fc", "%fd", "%fe", "%ff"
  };
void appendch(char *s, char ch)
{
s+=strlen(s);
*s++=ch;
*s='\0';
}

char *utf8_urlencode(char *s)
  {
    
    int len = strlen(s);
   int i;
    char *sbuf = malloc(len*10+100);
    for (i = 0; i < len; i++) {
      int ch = s[i];
      if ('A' <= ch && ch <= 'Z') {		// 'A'..'Z'
	       appendch(sbuf,(char)ch);
	
      } else if ('a' <= ch && ch <= 'z') {	// 'a'..'z'
	       appendch(sbuf,(char)ch);
      } else if ('0' <= ch && ch <= '9') {	// '0'..'9'
		       appendch(sbuf,(char)ch);
      } else if (ch == ' ') {			// space
	 	       appendch(sbuf,(char)'+');
      } else if (ch == '-' || ch == '_'		// unreserved
          || ch == '.' || ch == '!'
          || ch == '~' || ch == '*'
          || ch == '\'' || ch == '('
          || ch == ')') {
	       appendch(sbuf,(char)ch);
      } else if (ch <= 0x007f) {		// other ASCII
	       strcat(sbuf,hex[(unsigned char)(ch)]);
      } else if (ch <= 0x07FF) {		// non-ASCII <= 0x7FF
	       strcat(sbuf,hex[(unsigned char)(0xc0 | (ch >> 6))]);
	       strcat(sbuf,hex[(unsigned char)(0x80 | (ch & 0x3F))]);
      } else {					// 0x7FF < ch <= 0xFFFF
	       strcat(sbuf,hex[(unsigned char)(0xe0 | (ch >> 12))]);
	       strcat(sbuf,hex[(unsigned char)(0x80 | ((ch >> 6) & 0x3F))]);
	       strcat(sbuf,hex[(unsigned char)(0x80 | (ch & 0x3F))]);
      }
    }
    return sbuf;
}
