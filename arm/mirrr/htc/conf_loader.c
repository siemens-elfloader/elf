#include "swilib.h"
#define CFG_UINT 1
#define CFG_STR_UTF8 2
#define CFG_INT 3
#define CFG_STR_WIN1251 4
#define CFG_CBOX 5
#define CFG_STR_PASS 6
#define CFG_COORDINATES 7
#define CFG_COLOR 8
#define CFG_LEVEL 9
#define CFG_UTF8_STRING 10
#define CFG_CHECKBOX 11
#define CFG_TIME 12   
#define CFG_DATE 13  
#define CFG_RECT 14  
typedef struct
{
  int type;
  char name[32];
  unsigned int min;
  unsigned int max;
}CFG_HDR;
typedef struct
{
  char cbox_text[32];
}CFG_CBOX_ITEM;
void InitConfig();
extern int DISK_d;
const char *successed_config_filename="";
#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=(char *)malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    if (fread(f,buf,len,&ul)==len)
    {
      memcpy(cfg,buf,len);
      fclose(f,&ul);
    }
    else
    {
      fclose(f,&ul);
      goto L_SAVENEWCFG;
    }
  }
  else
  {
  L_SAVENEWCFG:
    if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,cfg,len,&ul)!=len) result=-1;
      fclose(f,&ul);
    }
    else
      result=-1;
  }
  mfree(buf);
  if (result>=0) successed_config_filename=fname;
  return(result);
}


extern const int vklad1;
extern const int vklad2;
extern const int vklad3;
extern const int vklad4;
extern const int vklad5;
extern const int vklad6;
extern const int vklad7;
extern const int vklad8;
extern const int vklad9;
extern int ust9[11];  // список видимости вкладок
extern int rasp9[11]; // список всех отображаемых вкладок
extern int xxc9[11];  // точки останова для прокрутки
extern int stop9[11]; // список всех активных точек останова для прокрутки
extern int stop8;   // последняя точка останова
extern int serv;    //количество активных вкладок

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\MD_TouchFLO.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\MD_TouchFLO.bcfg");
    DISK_d = 0;
  }
  else DISK_d = 4;

ust9[0]=1;
ust9[1]=vklad1;
ust9[2]=vklad2;
ust9[3]=vklad3;
ust9[4]=vklad4;
ust9[5]=vklad5;
ust9[6]=vklad6;
ust9[7]=vklad7;
ust9[8]=vklad8;
ust9[9]=vklad9;
ust9[10]=0;

xxc9[0]=-1;
xxc9[1]=25;
xxc9[2]=52;
xxc9[3]=79;
xxc9[4]=105;
xxc9[5]=131;
xxc9[6]=158;
xxc9[7]=183;
xxc9[8]=210;
xxc9[9]=235;

serv=0;
for(int i=0;i<10;i++){rasp9[i]=0; stop9[i]=0; if (ust9[i]){ rasp9[serv]=i; serv++; stop8=xxc9[serv-1];}}



}
