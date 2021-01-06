#include "../../inc/swilib.h"
#include "string_works.h"


int char16to8(int c) //unicode2win1251
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;
    else if (c==4) c=2;
    else if (c==6) c=10;
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16;
    else if (c==0x54) c=18;
    else if (c==0x56) c=11;
    else if (c==0x57) c=23;
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}

#ifdef LANG_CN

typedef struct
{
  unsigned short u;
  unsigned short a;
} TUNICODE2ANSI;

const TUNICODE2ANSI u2a[]=
{
  0x2014,'—',
  0x2018,'‘',
  0x201C,'“',
  0x201D,'”',
  0x2103,'℃',
  0x3001,'、',
  0x3002,'。',
  0xFF01,'！',
  0xFF08,'（',
  0xFF09,'）',
  0xFF0C,'，',
  0xFF1A,'：',
  0xFF1B,'；',
  0xFF1F,'？',
  0xFF5E,'～',
  0xFFE5,'￥',
  0,0
};

int unicode2ansi(int c) //
{
  int i;
  const TUNICODE2ANSI *p=u2a;
  if(c>=0x400 && c<0x1000)
  {
    int d;
    c-=0x400;
    c+=0xA791;
    d=c>>8;
    c=(c<<24)>>16;
    return (c|d);
  }
  else
  {
    while((i=p->u))
    {
      if(c==i)
	return p->a;
      p++;
    }
    return 0x2020;
  }
}
#ifdef NEWSGOLD
#define CODEMAP_ADDR 0xA1568200  //-0xA157A24F
#else
#define CODEMAP_ADDR 0xA0FA0200
#endif

void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)(CODEMAP_ADDR+32004);
  int i,j=0;
  unsigned short temp;
  for(i=1; i<=ws->wsbody[0]; i++)
  {
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00]<<8)>>8);
    }
    else if(temp>=0x400)
    {
      temp=unicode2ansi(temp);
      s[j++]=temp>>8;
      s[j++]=(temp<<8)>>8;
    }
    else
    {
      s[j++]=' ';
    }
    if(maxlen != 0 && j >= maxlen)
      break;
  }
  s[j] = 0;
}

void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)(CODEMAP_ADDR);
  char *p=(char *)s;
  unsigned char uc,uc2;
  ws->wsbody[0] = 0;
  while((uc=*p++) && (maxlen == 0 || p-s<=maxlen))
  {
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else
    {
      uc2=*p++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else
        wsAppendChar(ws, codemap[(uc-129)*127+(uc2-128)]);
    }
  }
}

#else

const unsigned short win2unicode[128]=
{
  0x0402,0x0403,0x201A,0x0453,0x201E,0x2026,0x2020,0x2021,
  0x20AC,0x2030,0x0409,0x2039,0x040A,0x040C,0x040B,0x040F,
  0x0452,0x2018,0x2019,0x201C,0x201D,0x2022,0x2013,0x2014,
  0x0020,0x2122,0x0459,0x203A,0x045A,0x045C,0x045B,0x045F,
  0x00A0,0x040E,0x045E,0x0408,0x00A4,0x0490,0x00A6,0x00A7,
  0x0401,0x00A9,0x0404,0x00AB,0x00AC,0x00AD,0x00AE,0x0407,
  0x00B0,0x00B1,0x0406,0x0456,0x0491,0x00B5,0x00B6,0x00B7,
  0x0451,0x2116,0x0454,0x00BB,0x0458,0x0405,0x0455,0x0457,
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F
};

unsigned int char8to16(int c)
{
  if (c>=128)
  {
    return(win2unicode[c-128]);
  }
  return(c);
}

#endif
void ws_2ascii(WSHDR *ws, char *str, int maxlen)
{
#ifdef LANG_CN
  ws2ascii(ws, str, maxlen);
#else
  unsigned short *p=ws->wsbody+1;
  int i=0;
  while((i<maxlen)&&(i<ws->wsbody[0]))
  {
    str[i]=char16to8(p[i]);
    i++;
  }
  str[i]=0;
#endif
}

void ascii_2ws(WSHDR *ws, const char *s, int maxlen)
{
#ifdef LANG_CN
  ascii2ws(ws, s, maxlen);
#else
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
#endif
}

#define wslen(ARG) (ARG->wsbody[0])

int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  while((pos<=l1)&&(pos<=l2))
  {
    cs=ws1->wsbody[pos];
    ds=ws2->wsbody[pos];
    if(cs<0x1000 && ds<0x1000)
    {
    	cs=char16to8(cs);
    	ds=char16to8(ds);
    	if(cs&0x40) cs&=0xDF;
    	if(ds&0x40) ds&=0xDF;
    }
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return(l1-l2);
}

int wstrncmp_nocase(WSHDR *ws1, WSHDR *ws2, int n)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  n++;
  while((pos<=l1)&&(pos<=l2)&&(pos<=n))
  {
    cs=ws1->wsbody[pos];
    ds=ws2->wsbody[pos];
    if(cs<0x1000 && ds<0x1000)
    {
    	cs=char16to8(cs);
    	ds=char16to8(ds);
    	if(cs&0x40) cs&=0xDF;
    	if(ds&0x40) ds&=0xDF;
    }
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return 0;
}

void wsInsert(WSHDR *ws, WSHDR *txt, int pos, int max) //start form 0;
{
  unsigned short *st;
  int cplen;	
  if((!ws)||(!txt)||(!wstrlen(txt)))
    return;
  if(pos>(ws->wsbody[0]))
    return;
  if((pos+(txt->wsbody[0]))>=max)
  {
    CutWSTR(ws, pos);
    wstrncat(ws, txt, max-pos); 
    return;
  }
  if(ws->wsbody[0]+txt->wsbody[0] >= max)
    cplen=max-(pos+txt->wsbody[0]);
  else
    cplen=ws->wsbody[0]-pos;
  st=malloc(cplen*sizeof(unsigned short));
  memcpy(st, ws->wsbody+pos+1, cplen*sizeof(unsigned short));
  memcpy(ws->wsbody+pos+1, txt->wsbody+1, (txt->wsbody[0])*sizeof(unsigned short));
  memcpy(ws->wsbody+1+pos+(txt->wsbody[0]), st, cplen*sizeof(unsigned short));
  ws->wsbody[0]=pos+(txt->wsbody[0])+cplen;
  mfree(st);
}

int num_2ws(WSHDR *ws, const char *num, int maxlen)
{
  int i=0, c;
  const char *p=num;
  unsigned short *ps=ws->wsbody+1;
  int max2;
  if( !ws || !num || !maxlen)
    return 0;
  max2=(maxlen < ws->maxlen)?maxlen:ws->maxlen;
  while(i<max2 && (c=*p++))
  {
    ps[i++]=c;
  }
  ps[i]=0;
  return (ws->wsbody[0]=i);
}

int ws_2num(WSHDR *ws, char *num, int maxlen)
{
  int i=0, c;
  int max2;
  unsigned short *ps=ws->wsbody+1;
  if( !ws || !num || !maxlen)
    return 0;
  max2=(ws->wsbody[0] < maxlen)?ws->wsbody[0]:maxlen;
  while(i<max2 && (c=*ps++))
  {
    num[i++]=c;
  }
  num[i]=0;
  return i;
}

int str2int(const char *str)
{
  int i, r=0, c, len, n;
  if(!str || !(len=strlen(str)))
    return 0;
  if(len>10) len=10;
  len--;
  for(i=len;i>=0;i--)
  {
    c=str[i];
    if(c<'0' || c>'9')
      break;
    n=len-i;
    c-='0';
    while(n)
    {
      c*=10;
      n--;
    }
    r+=c;
  }
  return r;
}
#ifdef MM
char *GotoCurChar(unsigned char *p, int c)
{
  int i;
  while((i=*p++))
  {
    if(i==c) return p;
  }
  return 0;
}

int IsHaveBigChar(unsigned char *p, int len)
{
  int c;
  unsigned char *pp=p;
  while((pp-p<len) && (c=*p++))
  {
    if(c>0x80) return 1;
  }
  return 0;
}

void NmlUtf8P_2SieUtf8P(char *utf8s)
{
  char *p;
  char *p1;
  char *p2=utf8s;
  while((p=GotoCurChar(p2, '\\')) || (p=GotoCurChar(p2, '/')))
  {
    if(*p==0x1F) continue;
    if(!(p1=GotoCurChar(p, '\\')))
    {
      if(!(p1=GotoCurChar(p, '/')))
	 p1=p+strlen(p);
    }
    if(IsHaveBigChar(p, p1-p))
    {
      //后移
      p1=p+strlen(p);
      while(p1>p)
      {
	*(p1+1)=*p1;
	p1--;
      }
      *p=0x1F;
    }
    p2=p;
  }
}

void SieUtf8P_2NmlUtf8P(char *s)
{
  //直接清理掉0x1F就行
  char *p=s;
  int c;
  char *p1;
  while((c=*p))
  {
    if(c==0x1F)
    {
      p1=p;
      while(*p1)
      {
	*p1=*(p1+1);
	p1++;
      }
    }
    p++;
  }
}
#endif
int IsWsSmall(WSHDR *ws)
{
  int i;
  if(!ws) return 0;
  for(i=0;i<ws->wsbody[0];i++)
  {
    if(ws->wsbody[i+1]>0x80) return 0;
  }
  return 1;
}

