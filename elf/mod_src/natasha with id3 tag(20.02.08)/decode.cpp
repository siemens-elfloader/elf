#include "..\..\inc\swilib.h"
#include "base64.h"
#include "sf_mime.h"
#include "decode.h"


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
  ou = output = malloc(len+1);
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
  return (realloc(output,_sf_b64_len+1));
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
  s=buf=malloc(len + 1);
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
  return (realloc(buf,(s-buf)+1));
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

void koi2win(char*d,const char *s)
{
  int c;
  while((c=*s++))
  {
    *d++=c>=128?kw[c-128]:c;
  }
  *d=c;
}

void iso885952win(char*d,const char *s)
{
  int c;
  while((c=*s))
  {
    if(c>=128)
      *d=iw[c-128];
    else *d=c;
    s++;
    d++;
  }
  *d=c;
}

void utf82win(char*d,const char *s)
{
  int ds = 2;
  for (; *s; s+=ds)
  {
    unsigned char ub = *s, lb = *(s+1);
    ds = 1;
    if (ub == 0xD0)
      if (lb != 0x81)
        {*d = lb + 48; d++;}
      else
        {*d = 'Ё'; d++;}

    if (ub == 0xD1)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
        {*d = 'ё'; d++;}

    if (ub == 0xE2)
      if (lb == 0x80)
        if ((unsigned char)*(s+2) == 0x94)
          {*d = '-'; d++; ds = 3;}

    if(!(ub & 0x80))
    {
      *d = ub;
      d++;
    }
    else
      for(ds = 0; ub&0x80; ub <<= 1, ds++);
  }
  *d = 0;
}

int unicode2win(int code)
{
  if (code<128) return (code);
  for(unsigned int i = 0; i < 128; i++)
   if (cp1251_ucs_table[i] == code) return 0x80 + i;
  return '_';
}

char *strreplace(char *s, char *r, char *w)
{
  //посчитаем сколько места надо под буфер
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

  char *d = (char*) malloc(d_ptr+1);

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

void strip_special(char *s)
{
  int n = strlen(s);

  //сюда мы будем бросать кости
  char *d = (char*) malloc(n+1);
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
  mfree(buf);
}

void strip_html(char *s)
{
  int d_ptr = 0;
  char *script, *script_end, *s1, *s2;

  s1 = strreplace(s, "\r\n\r\n", "<br>");

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
  s1 = strreplace(s2, "<br>", "\r\n");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "<br />", "\r\n");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "<p>", "\r\n");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "<blockquote", "\r\n<blockquote");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "/blockquote>", "/blockquote>\r\n");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "</td>", " ");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "</tr>", "\r\n");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&quote;", "\"");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&nbsp;", " ");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&lt;", "<");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&gt;", ">");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&amp;", "&");
  mfree(s2); s2 = s1;
  s1 = strreplace(s2, "&copy;", "(c)");
  mfree(s2);

  //сюда мы будем бросать кости
  char *d = (char*) malloc(strlen(s)+1);

  //отфильтруем html - результат заведомо меньшей длины
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


  //вернём модифицированную строку в исходный буфер
  strcpy(s,d);
  mfree(d);
  mfree(s1);
  strip_special(s);
}

int get_charset(char *charset)
{
  if (!strncmp_nocase(charset,"windows-1251",12))
    return WIN_1251;
  
  if (!strncmp_nocase(charset,"koi8-r",6))
    return KOI8_R; 
  
  if (!strncmp_nocase(charset,"ISO-8859-5",10))
    return ISO_8859_5;
  
  if (!strncmp_nocase(charset,"UTF-8",5))
    return UTF_8;

  return WIN_1251;
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
  outbuf = (char*) malloc(out_len);
  zeromem(outbuf,out_len);
  
  while (*p != '\0')
  {
    char *decoded_text = NULL;
    int len;
    
    eword_begin_p = strstr(p, ENCODED_WORD_BEGIN);
    if (!eword_begin_p)
    {
      char * curbuf = (char*) malloc(strlen(p)+1);

      switch(default_charset)
      {
      default:
      case WIN_1251:
        strcpy(curbuf,p);
        break;
      case KOI8_R:
        koi2win(curbuf,p);
        break;
      case ISO_8859_5:
        iso885952win(curbuf,p);
        break;
      case UTF_8:
        utf82win(curbuf,p);
        break;
      }

      strcat(outbuf, curbuf);
      mfree(curbuf);
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
    case WIN_1251:
      strcat(outbuf, decoded_text);
      p = eword_end_p + 2;
      continue;
    case KOI8_R:
      conv_str=(char*) malloc(strlen(decoded_text)+1);
      koi2win(conv_str,decoded_text);
      break;
    case ISO_8859_5:
      conv_str=(char*) malloc(strlen(decoded_text)+1);
      iso885952win(conv_str,decoded_text);
      break;
    case UTF_8:
      conv_str=(char*) malloc(strlen(decoded_text)+1);
      utf82win(conv_str,decoded_text);
      break;
    }
    strcat(outbuf, conv_str);
    mfree(conv_str);
    mfree(decoded_text);
    p = eword_end_p + 2;
  }
  out_str = outbuf;
  out_len = strlen(outbuf);
    
  return realloc(out_str, out_len + 1);
}
