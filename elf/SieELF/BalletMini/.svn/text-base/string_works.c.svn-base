#include "../inc/swilib.h"
#include "string_works.h"

int debugA=A_Truncate;
unsigned int debug_ul;
int debug_file;

void debugv(char *file,int line,void *p, int sz)
{
  if ((debug_file=fopen("0:\\zbin\\balletmini\\debug.txt",A_ReadWrite+A_Create+debugA,P_READ+P_WRITE,&debug_ul))!=-1)
  {
    fwrite(debug_file,p,sz,&debug_ul);
    fclose(debug_file,&debug_ul);
    debugA=A_Append;
  }
}

void debugf(char *file,int line)
{
  if ((debug_file=fopen("0:\\zbin\\balletmini\\debug.txt",A_ReadWrite+A_Create+debugA,P_READ+P_WRITE,&debug_ul))!=-1)
  {
    char c[256];
    sprintf(c,"%s : %i\n",file,line);
    fwrite(debug_file,c,strlen(c),&debug_ul);
    fclose(debug_file,&debug_ul);
    debugA=A_Append;
  }
}

void debuf(void *p, int sz)
{
//  static char buf[1024];
//  static int buf_sz=0;
//  
//  if (buf_sz+sz<1024)
//  {
//    memcpy(&buf[buf_sz],p,sz);
//    buf_sz+=sz;
//    return;
//  }
//  if ((debug_file=fopen("0:\\zbin\\balletmini\\debug.txt",A_ReadWrite+A_Create+debugA,P_READ+P_WRITE,&debug_ul))!=-1)
//  {
//    fwrite(debug_file,p,sz,&debug_ul);
//    fclose(debug_file,&debug_ul);
//    buf_sz=0;
//    debugA=A_Append;
//    memcpy(&buf[buf_sz],p,sz);
//    buf_sz+=sz;
//  }
}

static unsigned int _rshort(char *p)
{
  unsigned int r=*p++;
  r<<=8;
  r|=*p;
  return r;
}

unsigned int _rshort2(char *p)
{
  unsigned int r=*p++;
  r<<=8;
  r|=*p;
  return r;
}

int strcmp_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

int omstrcmp(VIEWDATA *vd, unsigned int ps, unsigned int pd)
{
  int ls;
  char *s;
  int ld;
  char *d;
  if (ps>=vd->oms_size) return 1;
  if (pd>=vd->oms_size) return 1;
  ls=_rshort(s=vd->oms+ps);
  ld=_rshort(d=vd->oms+pd);
  if (ls!=ld) return 1;
  return memcmp(s+2,d+2,ls);
}

char *globalstr(const char *s)
{
  int l=strlen(s)+1;
  char *d=malloc(l);
  memcpy(d,s,l);
  return d;
}

void freegstr(char **ps)
{
  mfree(*ps);
  *ps=NULL;
}

char *replacegstr(char **ps, const char *s, int len)
{
  freegstr(ps);
  char *d=malloc(len+1);
  memcpy(d,s,len);
  d[len]=0;
  return *ps=d;
}

int char16to8(int c)
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

int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
    else c-=8;
  c+=0x400;
  return (c); 
}

void ascii2ws(WSHDR *ws, const char *s)
{
gb2ws(ws, s, strlen(s));
}

char *extract_omstr(VIEWDATA *vd, unsigned int pos)
{
  int n;
  char *s;
  char *d;
  if (pos>=vd->oms_size||pos==_NOREF) return NULL;
  n=_rshort(s=vd->oms+pos);
  d=malloc(n+1);
  memcpy(d,s+2,n);
  d[n]=0;
  return d;
}
/*
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
       {*d = 'E'; d++;}

    if (ub == 0xD1)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
         {*d = 'E'; d++;}

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

char symbols[]={0x0A,0x20,0x23,0x24,0x25,0x26,0x2B,0x2C,0x2F,0x3A,0x3B,0x3D,0x3F,0x40,0x7E,0x00};

int sfind8(char s,char *v)
{
  for (int i=0;i<strlen(v);i++)
    if (s==v[i])
      return i;
  return -1;
}

int char_win2utf8(char*d,const char *s) 
{                                       
  char hex[] = "0123456789abcdef";
  char *d0 = "%d0%";
  char *d1 = "%d1%";
  unsigned char b = *s, lb, ub;
  int r = 0, ab;
  if (sfind8(b,symbols)>=0)
  {
    *d = '%'; d++;
    *d = hex[(b>>4)&0xF]; d++;
    *d = hex[b     &0xF]; d++;
    r = 3;
  }
  if(b >= 0xC0 && b <= 0xFF)           
  {
    ab = 0x350;                        
    ab += b;
    ub = 0xC0 | ((ab>>6) & 0x1F);      
    lb = 0x80 | (ab & 0x3F);
    *d = '%'; d++;
    *d = hex[(ub>>4)&0xF]; d++;       
    *d = hex[ub     &0xF]; d++;
    *d = '%'; d++;
    *d = hex[(lb>>4)&0xF]; d++;
    *d = hex[lb     &0xF]; d++;
    r = 6;
  }
  else
      if(b == 0xA8)
      {
        memcpy(d, d0, 4);             
        d+=4;
        *d = '8'; d++;
        *d = '1'; d++;
        r = 6;
      }
      else
        if(b == 0xB8)
        {
        memcpy(d, d1, 4);
        d+=4;
        *d = '9'; d++;
        *d = '1'; d++;
        r = 6;
        }
  return r;
}

char * ToWeb(char *src,int special)                  
{
  int cnt = 0, i, j;
  char *ret;
  for(i = 0; src[i]; i++)                 
  {
    unsigned char c=src[i];
    if(c>=0x80) cnt+=2;
    if(special&&(sfind8(c,symbols)>=0)) cnt++;
  }
  ret = malloc(strlen(src) + cnt*3 + 1);  
  for(i = 0, j = 0; src[i]; i++)
  {
    unsigned char c=src[i];
    if(c>=0x80||(special&&(sfind8(c,symbols)>=0)))
      j += char_win2utf8(ret+j, src+i);   
    else
      ret[j++] = src[i];
  }
  ret[j] = 0;
  mfree(src);                             
  return ret;
}
*/
void oms2ws(WSHDR *ws, const char *text, int len)
{
  ws->wsbody[0]=0;
  int c;
  while((len--)>0)
  {
    c=*text++;
    if ((c&0xE0)==0xC0)
    {
      if (len>0)
      {
        c&=0x1F;
        c<<=6;
        c|=(*text++)&0x3F;
        len-=1;
      }
    }
    else
      if ((c&0xF0)==0xE0)
      {
        if (len>1)
        {
          c&=0x0F;
          c<<=12;
          c|=((*text++)&0x3F)<<6;
          c|=((*text++)&0x3F)<<0;
          len-=2;
        }
      }
    ws->wsbody[++(ws->wsbody[0])]=c;
  }
}
