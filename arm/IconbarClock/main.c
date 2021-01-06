#include "C:\ARM_ALL\inc\swilib.h"
#include "conf_loader.h"

#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);
#pragma segment="ELFBEGIN"

const int minus11=-11;
int bts;
IMGHDR *icons[11];
char *map;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

extern const unsigned int ICON_N, NULL_ICON_N;

const char mypng[124]=
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x08, 0x03, 0x00, 0x00, 0x00, 0x28, 0xCB, 0x34, 
	0xBB, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66, 0x74, 0x77, 0x61, 0x72, 
	0x65, 0x00, 0x41, 0x64, 0x6F, 0x62, 0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 
	0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x00, 0x06, 0x50, 0x4C, 0x54, 0x45, 0xFF, 0xFF, 
	0xFF, 0x00, 0x00, 0x00, 0x55, 0xC2, 0xD3, 0x7E, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41, 0x54, 
	0x78, 0xDA, 0x62, 0x60, 0x00, 0x08, 0x30, 0x00, 0x00, 0x02, 0x00, 0x01, 0x4F, 0x6D, 0x59, 0xE1, 
	0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

#pragma inline=forced

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if(strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      extern const int ena_req;
      if(ena_req) ShowMSG(1,(int)"Конфиг IconbarClock обновлен!");
      InitConfig();
    }
  }
  return (1);
}

unsigned int oldHandlerAddr;
unsigned int* handlerAddr;
typedef void (*func)(short* num);


#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
TTime time;

static void addIconBar(short* num)
{
  void *icsm;
  extern const int ena_gui;
  if(ena_gui)
  {
    icsm=FindCSMbyID(CSM_root()->idle_id);
    if (icsm)
    {
      if (IsGuiOnTop(idlegui_id(icsm)))
      {
        if(ena_gui==2) return;
      }
      else
        if(ena_gui==1) return;
    }
    else
      if(ena_gui==1) return;
  }
  int t[5]={0,0,10,0,0}, c;
  TDate dt;
  TTime tm;
  GetDateTime(&dt,&tm);
  IMGHDR *ic=GetPITaddr(ICON_N);
  if((tm.hour!=time.hour)||(tm.min!=time.min)||(ic->bitmap!=map))
  {
    time=tm;
    t[0]=time.hour/10;
    t[1]=time.hour;
    while(t[1]>=10)
    {
      t[1]-=10;
    }
    t[3]=time.min/10;
    t[4]=time.min;
    while(t[4]>=10)
    {
      t[4]-=10;
    }
    ic->h=icons[0]->h;
    ic->w=icons[t[0]]->w+icons[t[1]]->w+icons[t[2]]->w+icons[t[3]]->w+icons[t[4]]->w;
    mfree(ic->bitmap);
    map=malloc(ic->h*ic->w*bts);
    zeromem(map, ic->h*ic->w*bts);
    for(int i=0; i<ic->h; i++)
    {
      c=i*ic->w*bts;
      for(int j=0; j<5; j++)
      {
        memcpy(map+c, icons[t[j]]->bitmap+i*icons[t[j]]->w*bts, icons[t[j]]->w*bts);
        c+=icons[t[j]]->w*bts;
      }
      ic->bitmap=map;
    }
  }
  AddIconToIconBar(ICON_N,num);
  AddIconToIconBar(NULL_ICON_N,num);
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  for(int i=0; i<11; i++)
  {
    if(icons[i])
    {
      mfree(icons[i]->bitmap);
      mfree(icons[i]);
    }
  }
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;

struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
  ICONBAR_H iconbar_handler;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(CSM_RAM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  },
  {
    "IconBar"
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"IconbarClock");
}

void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr = (int)addIconBar;
}

int main()
{  
  InitConfig();
  char fl[64];
  for(int i=0; i<11; i++)
  {
  zeromem(fl, 64);
  extern const char ICON_PATH[];
  if(ICON_PATH[strlen(ICON_PATH)-1]=='\\') sprintf(fl, "%s%x.png", ICON_PATH, i);
  else sprintf(fl, "%s\\%x.png", ICON_PATH, i);
  icons[i]=CreateIMGHDRFromPngFile(fl, 0);
  if(!icons[i])
  {
  ShowMSG(1,(int)"загружены не все пнг!!!");
  for(int j=0; j<i; j++)
  {
  if(icons[j])
  {
  mfree(icons[j]->bitmap);
  mfree(icons[j]);
  }
  }
  return 0;
  }
  }
  switch(icons[0]->bpnum)
  {
  case 0x5:
  case 0x85:
  bts=1;
  break;
  case 0x8:
  case 0x88:
  bts=2;
  break;
  case 0xA:
  case 0x8A:
  bts=4;
  break;
  default:
  ShowMSG(1,(int)"Ошибка!!!");
  for(int i=0; i<11; i++)
  {
  if(icons[i])
  {
  mfree(icons[i]->bitmap);
  mfree(icons[i]);
  }
  }
  return 0;
  }
  //bts=4;
  zeromem(fl, 64);
  extern const int disk;
  switch (disk)
  {
  case 0:
  sprintf(fl,"0:\\ZBin\\img\\%d.png",ICON_N);
  break;
  case 1:
  sprintf(fl,"4:\\ZBin\\img\\%d.png",ICON_N);
  break;
  }
  int f;
  unsigned int ul;
  if ((f=fopen(fl,A_ReadOnly+A_BIN,P_READ,&ul))!=-1) fclose(f,&ul);
  else
  {
  if ((f=fopen(fl,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
  {
  fwrite(f,mypng,124,&ul);
  fclose(f,&ul);
  fclose(f,&ul);
  }
  else
  {
  ShowMSG(1,(int)"Ошибка!!!");
  for(int j=0; j<11; j++)
  {
  if(icons[j])
  {
  mfree(icons[j]->bitmap);
  mfree(icons[j]);
  }
  }
  return 0;
  }
  }
  // IMGHDR *ic=GetPITaddr(ICON_N);
  // ic->h=icons[0]->h;
  // ic->w=icons[0]->w*4+icons[10]->w;
  //mfree(ic->bitmap);
  //ic->bitmap=map;
  // map=malloc(ic->h*ic->w*bts);
  // zeromem(map, ic->h*ic->w*bts);
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname();
  SetIconBarHandler();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int ena_msg;
  if (ena_msg) ShowMSG(1,(int)"IconbarClock установлен!");
  return 0;
}
