#include "..\inc\swilib.h"
#include "main.h"
#include "langpack.h"

char *strtolower(char *src, char *dst, int sz)
{
 int sl = strlen(src)+1;
 int len = sz==-1?sl:sz;
 if(len>sl)len=sl;
   
 for(int ii=0;ii<len-1;ii++)
 {
   int ch = src[ii];
   
   if(ch>='A' && ch<='Z') ch=ch-'A'+'a';
   
   dst[ii]=ch;
 }
 dst[len-1]=0;
 return dst;
}

int EnumIni(int local, char *ininame, INIPROC proc)
{
  int res=0;
  char *buf;
  char *cfg;
  int ch;
  int p=0;
  char* name=malloc(MAX_INIBUF);
  char* value=malloc(MAX_INIBUF);
  
  unsigned int size_cfg;
  
  char* fn = ininame;
  int f;
  unsigned int err;
  if (name && value && fn && (f=fopen(fn,A_ReadOnly,0,&err))!=-1)
  {
    size_cfg=lseek(f,0,S_END,&err,&err);
    lseek(f,0,S_SET,&err,&err);
    cfg=buf=malloc(size_cfg+1);
    if (cfg)
    {
      buf[fread(f,buf,size_cfg,&err)]=0;
      do
      {
      L_NEXT:
        //Камент
        if (*buf==';')
        {
          while((ch=*buf++)>=32);
          if (!ch) goto L_EOF;
        }
        p=0;
        while((ch=*buf++)!='=')
        {
          if (!ch) goto L_EOF;
          if (ch<32) goto L_NEXT;
          if (p<MAX_INIBUF-1) name[p++]=ch;
        }
        name[p]=0;
        p=0;
        while((ch=*buf++)>=32)
        {
          if (p<MAX_INIBUF-1) value[p++]=ch;
        }
        value[p]=0;

        if(proc)
        proc(name, value);        
        
        if (!ch) break; //EOF
      }
      while (1);
     }
    L_EOF:
     mfree(cfg);
     fclose(f,&err);
     res=1;
  }
  else {WriteSPerr(SPerr3);extern const unsigned int SHOW_POPUP; if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Spkeys_er]);}
  if(name)mfree(name);
  if(value)mfree(value);
  return res;
}
