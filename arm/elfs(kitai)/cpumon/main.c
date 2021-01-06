#include "..\inc\swilib.h"
#include "conf_loader.h"


#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

#define MIN_WIDTH 30
#define MIN_HEIGHT 10
#define MIN_UPTIME 1
#define START_DELAY (20 * 216)

#define MAX(a,b) (a)>(b)?(a):(b)

#define CLOCK_26     26
#define CLOCK_52     52
#define CLOCK_104    104
#define CLOCK_208    208

#define RGB16(R, G, B) (((B>>3)&0x1F) | ((G<<3)&0x7E0) | ((R<<8)&0xF800))

extern const RECT position;

extern const int cfgShowIn;
extern const int cfgStTxt;
extern const unsigned int cfgUpTime;
#ifdef NEWSGOLD
extern const char cfgLoad208[4];
extern const char cfgLoad104[4];
extern const char cfgLoad52[4];
#else
extern const char cfgLoad104[4];
extern const char cfgLoad52[4];
extern const char cfgLoad26[4];
#endif


unsigned int uiUpdateTime, uiWidth, uiHeight;

unsigned short* img1_bmp;

IMGHDR img1;

unsigned char* loads;
unsigned char* clocks;

GBSTMR mytmr;

WSHDR *ws1;

unsigned int hhh;
int cop;


const char ipc_my_name[]="CpuMon";
#define IPC_UPDATE_STAT 1

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

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

void RereadSettings()
{
  InitConfig();
  
 //========================
  uiUpdateTime = MAX(((262*cfgUpTime)/ 10),MIN_UPTIME);
  uiWidth  = MAX(position.x2-position.x+1,MIN_WIDTH);
  uiHeight = MAX(position.y2-position.y+1,MIN_HEIGHT);
  
  img1_bmp = malloc(2 * uiWidth * uiHeight);
  zeromem(img1_bmp, 2 * uiWidth * uiHeight);
  img1.w = uiWidth;
  img1.h = uiHeight;
  img1.bpnum = 8;
  img1.bitmap = (char*) img1_bmp;

  loads = malloc(uiWidth);
  zeromem(loads, uiWidth);

  clocks = malloc(uiWidth);
  zeromem(clocks, uiWidth);
}

void FreeMem()
{
  mfree(img1_bmp);
  img1_bmp=0;
  mfree(loads);
  loads=0;
  mfree(clocks);
  clocks=0;
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
  SetPropTo_Obj5(&drwobj, &rc, 0, img);
  SetColor(&drwobj, pen, brush);
  DrawObject(&drwobj);
}


const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

void TimerProc(void)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}


unsigned int ClocksColour(unsigned int clock)
{
  switch (clock)
  {
#ifdef NEWSGOLD
  case CLOCK_52:
    return (RGB16(cfgLoad52[0],cfgLoad52[1],cfgLoad52[2]));
  case CLOCK_104:
    return (RGB16(cfgLoad104[0],cfgLoad104[1],cfgLoad104[2]));
  case CLOCK_208:
    return (RGB16(cfgLoad208[0], cfgLoad208[1], cfgLoad208[2]));
#else
  case CLOCK_26:
    return (RGB16(cfgLoad26[0],cfgLoad26[1],cfgLoad26[2]));
  case CLOCK_52:
    return (RGB16(cfgLoad52[0],cfgLoad52[1],cfgLoad52[2]));
  case CLOCK_104:
    return (RGB16(cfgLoad104[0],cfgLoad104[1],cfgLoad104[2]));
#endif
  default:
    return (/*RGB16(0, 0, 0)*/ 0xFFFF);
  }
}



static int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  unsigned int fShow;
  void *icsm;

  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    if (strcmp_nocase((char*)successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"CPUMon config updated!");
      FreeMem();
      RereadSettings();
    }
  }
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
          if (ipc->name_from==ipc_my_name) 
          {
            //Накапливаем значения
#ifdef NEWSGOLD
            if (!getCpuUsedTime_if_ena())
            {
              StartCpuUsageCount();
            }
#endif
            loads[hhh]  = uiHeight * GetCPULoad() / 100;
            clocks[hhh] = GetCPUClock()/* / 26*/;
            hhh++;
            if (hhh >= uiWidth)
            {
              hhh = 0;
              cop = 1;
            }
            GBS_StartTimerProc(&mytmr, uiUpdateTime, TimerProc);
          }
        }
      }
    }
  }
  switch (cfgShowIn)
  {
  case 0:
    fShow = !IsUnlocked();
    break;
  case 1:
    fShow = IsUnlocked();
    break;
  default:
    fShow = 1;
    break;
  }
  
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)) && fShow) //Если IdleGui на самом верху
    {
      GUI *igui = GetTopGUI();
      if (igui) //И он существует
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
        void *idata = GetDataOfItemByID(igui, 2);
        if (idata)
        {
          void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          DrawCanvas(canvasdata, position.x, position.y, position.x2, position.y2, 1);
          //рисуем нашу требуху
          int h = hhh;
          for(unsigned int x = 0; x < uiWidth; x++)
          {
            for(unsigned int y = 0; y < uiHeight; y++)
            {
              if (y < loads[h])
                img1_bmp[x + (uiHeight - 1 - y) * uiWidth] = ClocksColour(clocks[h]);
              else
                img1_bmp[x + (uiHeight - 1 - y) * uiWidth] = 0xE000; //RGB16(21, 42, 21);
            }
            if (++h >= uiWidth)    h = 0;
          }
          DrwImg((IMGHDR *)&img1, position.x, position.y, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(1));
          if (!cop && cfgStTxt)
            DrawString(ws1, 0, position.y-(GetFontYSIZE(FONT_SMALL)+3), ScreenW()-1, ScreenH()-1, FONT_SMALL, 0x20,
                       GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(1));
        }
      }
    }
  }
  return(1);
}


static void maincsm_oncreate(CSM_RAM *data)
{
  ws1=AllocWS(100);
  wsprintf(ws1,"%t","CPUMon (C)BoBa,Rst7");
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  FreeMem();
  FreeWS(ws1);
  SUBPROC((void *)ElfKiller);
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

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
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CpuMon");
}


int main(void)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  RereadSettings();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return (0);
}
