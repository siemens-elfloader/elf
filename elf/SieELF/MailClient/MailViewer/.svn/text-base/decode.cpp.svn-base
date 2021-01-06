#include "..\..\inc\swilib.h"
#include "base64.h"
#include "sf_mime.h"
#include "decode.h"
#include "leak_debug.h"

char *br = "<br>", *zerostr = "";

extern int strncmp_nocase(const char *s1,const char *s2,unsigned int n);

#pragma inline 
int is_space(int c)
{ 
  return (c==' '?NULL:1);
}

#pragma inline
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}


#define MIN(A,B) A<B?A:B

char * base64_decode(const char *str, size_t *size)
{
  char *output, *ou;
  unsigned int pr[6];
  int n;
  int doit;
  size_t _sf_b64_len;
  const char *s;
  int len;
  
  if(str == NULL)
    str = "";
  
  s=str;
  len=size?*size:strlen(str);
  ou = output = debug_malloc(len+1, "base64_decode (alloc)");
  if(output == NULL)
    return NULL;
  
  if(size)
    *size = 0;
  
  
  doit = 1;
  
  do
  {
    n = 0;
    while(n < 4)
    {
      if ((str-s)>=len)
      {
        doit=0;
        break;
      }
      unsigned int ch;
      ch = _sf_uc_bi[*(unsigned char *)str];
      if(ch < B64_UNUSED)
      {
        pr[n] = ch;
        n++;
        str++;
      }
      else
        if(ch == B64_UNUSED)
        {
          str++;
	}
        else
        {
          doit = 0;
          break;
        }
    }
    
    if(doit == 0 && n < 4)
    {
      pr[n+2] = pr[n+1] = pr[n]='\0';
    }
    
    *(ou+0) = (pr[0] << 2) | (pr[1] >> 4);
    *(ou+1) = (pr[1] << 4) | (pr[2] >> 2);
    *(ou+2) = (pr[2] << 6) | (pr[3] >> 0);
    
    ou = ou+((n * 3) >> 2);
  }
  while(doit);
  
  _sf_b64_len = (ou - output);
  if(size)
    *size = _sf_b64_len;
  
  *ou = '\0';	/* NUL-terminate */
  return (debug_realloc(output,_sf_b64_len+1, "base64_decode (realloc)"));
}

void utf8_2_gb(char *gb,const char *utf8, int maxlen)
{
	WSHDR *ws=AllocWS(maxlen);
	utf8_2ws(ws, utf8, maxlen);
	ws2gb(ws, gb, maxlen);
	FreeWS(ws);
}
void utf82gb(char *gb,const char *utf8)
{
	utf8_2_gb(gb,utf8,strlen(utf8));
}

#pragma inline
int char_to_hex(int c)
{
  if (c>='0' && c<='9') return c-'0';
  if (c>='A' && c<='F') return c-'A'+10;
  if (c>='a' && c<='f') return c-'a'+10;
  return -1;
}

char * quoted_printable_decode(const char *str, size_t *size)
{
  char *buf;
  char *s, *d;
  register int n;
  register int len;
  int c;
  
  if(!str) return 0;
  
  /*
  * Allocate sufficient space to hold decoded string.
  */
  d=(char *)str;
  len=size?*size:strlen(str);
  s=buf=debug_malloc(len + 1, "quoted_printable_decode (1)");
  if(!buf)
    
    /* ENOMEM? */
    return 0;

  for(; *str && (str - d)<len; str++)
  {
    //if(*str == '_')
    //{
    //  *s++ = ' ';
    //  continue;
    //}
    if(*str == '=')
    {
      *s = '\0';
      n = *++str; 
      if(n == '\0')
      {
        str--;
        break;
      }
      if(str[1] == '\0')
        break;
      
      if ((c=char_to_hex(n))!=-1)  *s=c;
      else if (n=='\r' || n=='\n')
      {
        while(str[1] == '\n' || str[1] == '\r') str++;
        continue;
      }
      else 
      {
        *s++ = '=';
        *s++ = n;
        continue;
      }      
      *s <<= 4;                   
      n = *++str;
      
      if ((c=char_to_hex(n))!=-1)  *s|=c;
      else if (n=='\r' || n=='\n')
      {
        *s++ = n;
        continue;
      }
      else 
      {
        *s = '_';
        continue;
      }       
      s++;     
      continue;
    }
    *s++ = *str;
  }
  
  *s = '\0';

//  if(_sf_qp_buf)
//    mfree(_sf_qp_buf);
  if(size) *size = (s - buf);
  return (debug_realloc(buf,(s-buf)+1, "quoted_printable_decode (1)"));
}


#define ENCODED_WORD_BEGIN	"=?"
#define ENCODED_WORD_END	"?="

const char kw[] = 
{
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,184,164,165,166,167,168,169,170,171,172,173,174,175,
  176,177,178,168,180,181,182,183,184,185,186,187,188,189,190,191,
  254,224,225,246,228,229,244,227,245,232,233,234,235,236,237,238,
  239,255,240,241,242,243,230,226,252,251,231,248,253,249,247,250,
  222,192,193,214,196,197,212,195,213,200,201,202,203,204,205,206,
  207,223,208,209,210,211,198,194,220,219,199,216,221,217,215,218
};

char iw[] = {
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
  192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
  208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
  224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
  240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
  176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191
};

/* cp1251 to Unicode table */
static const unsigned short cp1251_ucs_table[] = {
 0x0402, 0x0403, 0x201a, 0x0453, 0x201e, 0x2026, 0x2020, 0x2021, 
 0x20ac, 0x2030, 0x0409, 0x2039, 0x040a, 0x040c, 0x040b, 0x040f, 
 0x0452, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014, 
 0x003f, 0x2122, 0x0459, 0x203a, 0x045a, 0x045c, 0x045b, 0x045f, 
 0x00a0, 0x040e, 0x045e, 0x0408, 0x00a4, 0x0490, 0x00a6, 0x00a7, 
 0x0401, 0x00a9, 0x0404, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x0407, 
 0x00b0, 0x00b1, 0x0406, 0x0456, 0x0491, 0x00b5, 0x00b6, 0x00b7, 
 0x0451, 0x2116, 0x0454, 0x00bb, 0x0458, 0x0405, 0x0455, 0x0457, 
 0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
 0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e, 0x041f, 
 0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 
 0x0428, 0x0429, 0x042a, 0x042b, 0x042c, 0x042d, 0x042e, 0x042f, 
 0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 
 0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e, 0x043f, 
 0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 
 0x0448, 0x0449, 0x044a, 0x044b, 0x044c, 0x044d, 0x044e, 0x044f
}; 

char *strreplace(char *s, char *r, char *w)
{
  //§á§à§ã§é§Ú§ä§Ñ§Ö§Þ §ã§Ü§à§Ý§î§Ü§à §Þ§Ö§ã§ä§Ñ §ß§Ñ§Õ§à §á§à§Õ §Ò§å§æ§Ö§â
  int n_r = strlen(r);
  int n_w = strlen(w);
  int d_ptr = 0;
  char *next_br, *prev_br=s;
  while(next_br = strstr_nocase(prev_br, r))
  {
    d_ptr += next_br - prev_br + n_w;
    prev_br = next_br + n_r;
  }
  d_ptr += strlen(s) - (prev_br - s);

  char *d = (char*) debug_malloc(d_ptr+1, "strreplace (1)");

  d_ptr = 0;
  prev_br = s;
  while(next_br = strstr_nocase(prev_br, r))
  {
    memcpy(d+d_ptr, prev_br, next_br-prev_br);
    d_ptr += next_br-prev_br;
    memcpy(d+d_ptr, w, n_w);
    d_ptr += n_w;
    prev_br = next_br + n_r;
  }
  int len = strlen(s) - (prev_br-s);
  if (len > 0) memcpy(d+d_ptr, prev_br, len);
  d_ptr += strlen(s) - (prev_br - s);
  d[d_ptr] = 0;

  return(d);
}
int unicode2win(int code)
{
  if (code<128) return (code);
  for(unsigned int i = 0; i < 128; i++)
   if (cp1251_ucs_table[i] == code) return 0x80 + i;
  return '_';
}

void strip_special(char *s)
{
  int n = strlen(s);

  //§ã§ð§Õ§Ñ §Þ§í §Ò§å§Õ§Ö§Þ §Ò§â§à§ã§Ñ§ä§î §Ü§à§ã§ä§Ú
  char *d = (char*) debug_malloc(n+1, "strip_special (1)");
  char *buf = d;
  for(int i = 0; i < n; i++)
  {
    if(s[i] == '&' && s[i+1] == '#')
    {
      int c = 0;
      for(i+=2; s[i] != ';'; i++)
      {
        c*=10;
        c+= s[i] - '0';
      }
      *d++ = unicode2win(c);
    } else
    {
      *d++ = s[i];
    }
  }
  *d = 0;
  strcpy(s,buf);
  debug_mfree(buf, "strip_special (1)");
}

void strip_html(char *s)
{
  int d_ptr = 0;
  char *script, *script_end, *s1, *s2;
  const char *valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$-_.+!*'(),%;:@&=/?~#";

  s1 = strreplace(s, "\r\n\r\n", br);
  s2 = s1;
  s1 = strreplace(s2, "<br />", br);
  debug_mfree(s2, "strip_html (11)"); s2 = s1;
  s1 = strreplace(s2, "<wbr />", zerostr);
  debug_mfree(s2, "strip_html (12)"); s2 = s1;
  s1 = strreplace(s2, "\r\r", br);
  debug_mfree(s2, "strip_html (13)"); s2 = s1;
  s1 = strreplace(s2, "\n\n", br);
  debug_mfree(s2, "strip_html (14)"); s2 = s1;
  s1 = strreplace(s2, "</ul>\n", "</ul><br>");
  debug_mfree(s2, "strip_html (15)"); s2 = s1;
  s1 = strreplace(s2, "</ul>\r", "</ul><br>");
  debug_mfree(s2, "strip_html (16)"); s2 = s1;
  s1 = strreplace(s2, "<li>", br);
  debug_mfree(s2, "strip_html (17)"); s2 = s1;
  s1 = strreplace(s2, "</li>", br);
  debug_mfree(s2, "strip_html (1)"); s2 = s1;
  s1 = strreplace(s2, "</ol>\r", "</ol><br>");
  debug_mfree(s2, "strip_html (18)"); s2 = s1;
  s1 = strreplace(s2, "</ol>\n", "</ol><br>");
  debug_mfree(s2, "strip_html (19)"); s2 = s1;
  s1 = strreplace(s2, "<br><br>", br);
  debug_mfree(s2, "strip_html (20)"); s2 = s1;
  //§©§Ñ§Þ§Ö§ß§Ú§Þ §ã§ã§í§Ý§Ü§Ú
  char *a = strstr(s1, "<a "), *hrf, *he, *ea, *ss, *st1, *st2, *rpl;
  int n;
  while(a)  //§±§à§Ü§Ñ §Ö§ã§ä§î §ä§Ö§Ô§Ú <a ...
  {
    he = hrf = strstr(a, "href=");  //§ß§Ñ§ç§à§Õ§Ú§Þ §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§î §ß§Ñ §Ñ§Õ§â§Ö§ã
    if(hrf)
    {
      if(hrf[5] == '\"')            //§ã§Þ§à§ä§â§Ú§Þ §Ü§Ñ§Ü §à§æ§à§â§Þ§Ý§Ö§ß§Ñ §ã§ã§í§Ý§Ü§Ñ
        he = strstr(hrf+6, "\""); //§Ó §Ü§Ñ§Ó§í§é§Ü§Ñ§ç
      else
        if(hrf[5] == '\'')          //§Ó §Ñ§á§à§ã§ä§â§à§æ§Ñ§ç
          he = strstr(&hrf[5], "\'");
        else
          for(he = hrf+5; *he && strchr(valid, *he); he++);//§Ú§Ý§Ú §Ò§Ö§Ù §ß§Ú§é§Ö§Ô§à
      ss = strstr(he, ">")+1;       //§Ú§ë§Ö§Þ §Ü§à§ß§Ö§è §à§ä§Ü§â§í§Ó§Ñ§ð§ë§Ö§Ô§à §ä§Ö§Ô§Ñ
      ea = strstr(he, "</a>");      //§Ú §ß§Ñ§é§Ñ§Ý§à §Ù§Ñ§Ü§â§í§Ó§Ñ§ð§ë§Ö§Ô§à
      rpl = strstr(he, "<a ");
      if(rpl && ea > rpl)
      {
        a = rpl;
        continue;
      }

      if(ss && ea)                  //§Ö§ã§Ý§Ú §ß§Ö §ß§Ñ§ê§Ý§Ú - §Ü§à§ã§ñ§Ü
      {
        st1 = (char*)debug_malloc(he-hrf-5, "strip_html (a1)"); //§Ó§í§Õ§Ö§Ý§ñ§Ö§Þ §á§Ñ§Þ§ñ§ä§î §á§à§Õ §á§â§à§Þ§Ö§Ø§å§ä§à§é§ß§í§Ö §ã§ä§â§à§Ü§Ú
        st2 = (char*)debug_malloc(ea-ss+1,  "strip_html (a2)");
        rpl = (char*)debug_malloc(ea-a+5,   "strip_html (a3)");
        
        memcpy(st1, hrf+6, he-hrf-6); st1[he-hrf-6] = 0; //§Ü§à§á§Ú§â§å§Ö§Þ §Ú§ç §ä§å§Õ§Ñ
        memcpy(st2, ss, ea-ss);       st2[ea-ss]    = 0;
        memcpy(rpl, a, ea-a+4);       rpl[ea-a+4]   = 0; //§é§ä§à §Ò§å§Õ§Ö§Þ §Ù§Ñ§Þ§Ö§ß§ñ§ä§î

        ss = (char*)debug_malloc(strlen(st1) + strlen(st2) + 6, "strip_html (a4)");
        memset(ss, 0, strlen(st1) + strlen(st2) + 6);
        if(strcmp(st1, st2))
          snprintf(ss, strlen(st1) + strlen(st2) + 5, " %s {%s} ", st2, st1); // §ß§Ñ §é§ä§à §Ù§Ñ§Þ§Ö§ß§ñ§Ö§Þ
        else
          snprintf(ss, strlen(st1) + strlen(st2) + 5, " {%s} ", st2, st1); // §ß§Ñ §é§ä§à §Ù§Ñ§Þ§Ö§ß§ñ§Ö§Þ

        n = a-s1;                                        //§¯§Ñ§Û§Õ§×§Þ §ã§Þ§Ö§ë§Ö§ß§Ú§Ö, §à§ä§Ü§å§Õ§Ñ §á§Ý§ñ§ã§Ñ§ä§î §Õ§Ñ§Ý§î§ê§Ö
        s2 = strreplace(s1, rpl, ss);                    //§³§à§Ò§ã§ä§Ó§Ö§ß§ß§à §Ù§Ñ§Þ§Ö§ß§Ñ
        debug_mfree(s1, "strip_html (a4)"); s1 = s2;     //§ñ§Ó§Ü§Ú-§á§Ñ§â§à§Ý§Ú §á§à§Þ§Ö§ß§ñ§Ý§Ú§ã§î
        a = s1 + n;                                      //§Õ§Ñ§Ý§î§ê§Ö §Ú§ã§Ü§Ñ§ä§î §à§ä§ã§ð§Õ§Ñ

        debug_mfree(ss,  "strip_html (a4)");             //§Ó§ã§Ö§Þ §ã§á§Ñ§ã§Ú§Ò§à, §Ó§ã§Ö §ã§Ó§à§Ò§à§Õ§ß§í
        debug_mfree(rpl, "strip_html (a3)");
        debug_mfree(st2, "strip_html (a2)");
        debug_mfree(st1, "strip_html (a1)");
      }
    }
    if(ss) a = s1;
    a = strstr(a+1, "<a ");
  }

  for(int i = 0, j = 0; s1[i]; i++)
  {
    if(s1[i] != '\r' && s1[i] != '\n')
      s1[j++] = s1[i];
    if(!s1[i+1]) s1[j] = 0;
  }

  while(script = strstr_nocase(s1, "<script"))
  {
    script_end =  strstr_nocase(s1, "</script>");
    if(!script_end) break;
    script_end += strlen("</script>");
    strcpy(script, script_end);
  }

  while(script = strstr_nocase(s1, "<style"))
  {
    script_end =  strstr_nocase(s1, "</style>");
    if(!script_end) break;
    script_end += strlen("</style>");
    strcpy(script, script_end);
  }

  s2 = s1;
  s1 = strreplace(s2, br, "\r\n");
  debug_mfree(s2, "strip_html (21)"); s2 = s1;
  s1 = strreplace(s2, "<p>", "\r\n");
  debug_mfree(s2, "strip_html (23)"); s2 = s1;
  s1 = strreplace(s2, "<blockquote", "\r\n<blockquote");
  debug_mfree(s2, "strip_html (24)"); s2 = s1;
  s1 = strreplace(s2, "/blockquote>", "/blockquote>\r\n");
  debug_mfree(s2, "strip_html (25)"); s2 = s1;
  s1 = strreplace(s2, "</td>", " ");
  debug_mfree(s2, "strip_html (26)"); s2 = s1;
  s1 = strreplace(s2, "</tr>", "\r\n");
  debug_mfree(s2, "strip_html (27)"); s2 = s1;
  s1 = strreplace(s2, "&quote;", "\"");
  debug_mfree(s2, "strip_html (28)"); s2 = s1;
  s1 = strreplace(s2, "&nbsp;", " ");
  debug_mfree(s2, "strip_html (29)"); s2 = s1;
  s1 = strreplace(s2, "&lt;", "<");
  debug_mfree(s2, "strip_html (30)"); s2 = s1;
  s1 = strreplace(s2, "&gt;", ">");
  debug_mfree(s2, "strip_html (31)"); s2 = s1;
  s1 = strreplace(s2, "&amp;", "&");
  debug_mfree(s2, "strip_html (32)"); s2 = s1;
  s1 = strreplace(s2, "&copy;", "(c)");
  debug_mfree(s2, "strip_html (33)");


  //§ã§ð§Õ§Ñ §Þ§í §Ò§å§Õ§Ö§Þ §Ò§â§à§ã§Ñ§ä§î §Ü§à§ã§ä§Ú
  char *d = (char*) debug_malloc(strlen(s)+1, "strip_html (1)");

  //§à§ä§æ§Ú§Ý§î§ä§â§å§Ö§Þ html - §â§Ö§Ù§å§Ý§î§ä§Ñ§ä §Ù§Ñ§Ó§Ö§Õ§à§Þ§à §Þ§Ö§ß§î§ê§Ö§Û §Õ§Ý§Ú§ß§í
  char *r = s1;

  d_ptr = 0;
  while(*r)
  {
   for(;*r && *r != '<'; r++)
    d[d_ptr++] = *r;
   for(;*r && *r != '>'; r++);
   if(*r) r++;
  }
  d[d_ptr] = 0;


  //§Ó§Ö§â§ß§×§Þ §Þ§à§Õ§Ú§æ§Ú§è§Ú§â§à§Ó§Ñ§ß§ß§å§ð §ã§ä§â§à§Ü§å §Ó §Ú§ã§ç§à§Õ§ß§í§Û §Ò§å§æ§Ö§â
  strcpy(s,d);
  debug_mfree(d, "strip_html (2)");
  debug_mfree(s1, "strip_html (3)");
  strip_special(s);
}

int get_charset(char *charset)
{
  if (!strncmp_nocase(charset,"GB2312",12))
    return GB2312;
  
  if (!strncmp_nocase(charset,"UTF-8",5))
    return UTF_8;

  return GB2312;
}

char *unmime_header(const char *encoded_str, int default_charset)
{
  const char *p = encoded_str;
  const char *eword_begin_p, *encoding_begin_p, *text_begin_p, *eword_end_p;

  char charset[32];
  int encoding;
  char *conv_str;
  char *outbuf;
  char *out_str;
  size_t out_len;
  size_t decoded_len;
  
  out_len=strlen(encoded_str) * 2;
  outbuf = (char*) debug_malloc(out_len, "unmime_header (1)");
  zeromem(outbuf,out_len);
  
  while (*p != '\0')
  {
    char *decoded_text = NULL;
    int len;
    
    eword_begin_p = strstr(p, ENCODED_WORD_BEGIN);
    if (!eword_begin_p)
    {
      char * curbuf = (char*) debug_malloc(strlen(p)+1, "unmime_header (2)");

      switch(default_charset)
      {
      default:
      case GB2312:
        strcpy(curbuf,p);
        break;
      case UTF_8:
        utf82gb(curbuf,p);
        break;
      }

      strcat(outbuf, curbuf);
      debug_mfree(curbuf, "unmime_header (1)");
      //strcat(outbuf, p);
      break;
    }

    encoding_begin_p = strchr(eword_begin_p + 2, '?');
    if (!encoding_begin_p)
    {
      strcat(outbuf, p);
      break;
    }
    
    text_begin_p = strchr(encoding_begin_p + 1, '?');
    if (!text_begin_p) 
    {
      strcat(outbuf, p);
      break;
    }
    
    eword_end_p = strstr(text_begin_p + 1, ENCODED_WORD_END);
    if (!eword_end_p)
    {
      strcat(outbuf, p);
      break;
    }
    
    if (p == encoded_str)
    {
      strncat(outbuf, p, eword_begin_p - p);
      p = eword_begin_p;
    }
    else
    {
      /* ignore spaces between encoded words */
      const char *sp;
      for (sp = p; sp < eword_begin_p; sp++) 
      {
        if (!is_space(*sp)) 
        {
          strncat(outbuf, p, eword_begin_p - p);
          p = eword_begin_p;
          break;
        }
      }
    }
    len = MIN(sizeof(charset) - 1, encoding_begin_p - (eword_begin_p + 2));
    strncpy(charset, eword_begin_p + 2, len);
    charset[len] = '\0';
    encoding = toupper(*(encoding_begin_p + 1));
    if (encoding == 'B')
    {
      decoded_len=eword_end_p - (text_begin_p + 1);
      decoded_text = base64_decode(text_begin_p + 1,&decoded_len);
    }
    else if (encoding == 'Q') 
    {
      decoded_len=eword_end_p - (text_begin_p + 1);
      decoded_text = quoted_printable_decode(text_begin_p + 1,&decoded_len);
    }
    else
    {
      strncat(outbuf, p, eword_end_p + 2 - p);
      p = eword_end_p + 2;
      continue;
    }
    switch(get_charset(charset))
    {
    case GB2312:
      conv_str=(char*) debug_malloc(strlen(decoded_text)+1, "unmime_header (6)");
      strcpy(conv_str,decoded_text);
      break;
    case UTF_8:
      conv_str=(char*) debug_malloc(strlen(decoded_text)+1, "unmime_header (5)");
      utf82gb(conv_str,decoded_text);
      break;
    }
    strcat(outbuf, conv_str);
    debug_mfree(conv_str, "unmime_header (2)");
    debug_mfree(decoded_text, "unmime_header (3)");
    p = eword_end_p + 2;
  }
  out_str = outbuf;
  out_len = strlen(outbuf);
    
  return debug_realloc(out_str, out_len + 1, "unmime_header (1)");
}
