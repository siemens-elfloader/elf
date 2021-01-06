#include "..\inc\swilib.h"
#include "conf_loader.h"


#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

extern const int cfgx;
extern const int cfgy;
extern const char cfgcolor[];
extern const char cfgcvcolor[];
extern const int cfgfont;
extern const int cfgtext_attribute;
extern const int cfgupdate_time;
extern const char gps_dir[];
extern const char drun[];

char filename[128];
WSHDR *corr_name;
GBSTMR mytmr;

RAMNET GetNetParams()
{
  RAMNET Result;
  zeromem(&Result, sizeof(RAMNET));
  Result = *RamNet();
  return Result;
}

void Savenew()
{
  unsigned int errcode;
  volatile int hFile = -1;
  RAMNET Res = GetNetParams();
  sprintf(filename,"%s%u\\%u-%u.tmo",gps_dir,Res.lac,Res.ci,Res.lac);
  hFile = fopen(filename,A_WriteOnly+A_Create,P_WRITE,&errcode);
  if(hFile==-1)
  {
    char *dir=malloc(128);
    sprintf(dir,"%s%u",gps_dir,Res.lac);
    mkdir(dir, &errcode);
    mfree(dir);
    hFile = fopen(filename,A_WriteOnly+A_Create,P_WRITE,&errcode);
  }
  WSHDR *ws0 = AllocWS(128);
  wsprintf(ws0,"%t %u-%u",drun,Res.ci,Res.lac);
  unsigned int len = wstrlen(ws0);
  fwrite(hFile,ws0->wsbody,len*2+2,&errcode);
  unsigned int crc = (int)ws0->wsbody[0];
  void *temp;
  char *arr;
  temp = ws0->wsbody;
  arr = temp;
  for(int i=2;i<(len+1)*2;i++)
  {
    crc = crc ^ arr[i];
  }
  fwrite(hFile,&crc,2,&errcode);
  FreeWS(ws0);
  fclose(hFile,&errcode);
}

void load_name()
{
  unsigned int errcode;
  volatile int hFile=-1;
  RAMNET Res=GetNetParams();
  sprintf(filename,"%s%u\\%u-%u.tmo",gps_dir,Res.lac,Res.ci,Res.lac);
  hFile = fopen(filename,A_ReadOnly,P_READ,&errcode);
  if(hFile==-1)
  {
    wsprintf(corr_name,"new: %u-%u",Res.ci,Res.lac);
    Savenew();
  }
  else
  {
    int str_len = 0;
    fread(hFile,&str_len,2,&errcode);
    WSHDR *tmostr=AllocWS(str_len);
    errcode=0;
    lseek(hFile,0,0,&errcode,&errcode);
    fread(hFile,tmostr->wsbody,(str_len+1)*2,&errcode);

    if(errcode)
    {
      wsprintf(corr_name,"%t %u","error ", errcode);
    }
    else
    {
      str_len=wstrlen(tmostr)-2;
      wstrcpybypos(corr_name,tmostr,3,str_len);
    }
    FreeWS(tmostr);
    fclose(hFile, &errcode);
  }
}

void tmrproc()
{
  load_name();
  GBS_StartTimerProc(&mytmr,216*2,tmrproc);
}

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

void redraw()
{
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui&&IsUnlocked())
      {
#ifdef ELKA
        void *canvasdata = BuildCanvas();
          {
#else
        void *idata = GetDataOfItemByID(igui, 2);
        if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
            DrawCanvas(canvasdata,cfgx,cfgy,cfgx+Get_WS_width(corr_name,cfgfont),cfgy+GetFontYSIZE(cfgfont),1);
            DrawString(corr_name,cfgx,cfgy,ScreenW(),ScreenH(),
                       cfgfont,cfgtext_attribute,cfgcolor,cfgcvcolor);
          }
      }
    }
  }
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(0,(int)"MiniGPS config reloaded!");
      InitConfig();
    }
  }
  redraw();
  return(1);
}

IPC_REQ ipc={"ScrD","MiniGPS",(void*)redraw};

static void maincsm_oncreate(CSM_RAM *data)
{  
  corr_name=AllocWS(128);
  GBS_StartTimerProc(&mytmr,216*2,tmrproc);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&ipc); 
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  FreeWS(corr_name);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,1,&ipc); 
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
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
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MiniGPS");
}	

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  
  unsigned int err;  
  if(!isdir(gps_dir,&err)){
    mkdir(gps_dir,&err);
  }
  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
      
  return 0;
}
