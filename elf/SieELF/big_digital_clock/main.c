#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#pragma segment="CONFIG_C"
#define UPDATE_TIME 100

#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
//#define RGB16(R, G, B) ((B & 0x1F) | ((G & 0x3F) << 5) | ((R & 0x1F) << 11))
CSM_DESC icsmd;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

const int minus11=-11;

extern void kill_data(void *p, void (*func_p)(void *));

#ifdef NEWSGOLD
#pragma swi_number=0x0B1
__swi __arm void DrawColorPicWithCanvas(int x, int y, int icon, const char *color1);
#else
#pragma swi_number=0x0B1
__swi __arm void DrawColorPicWithCanvas(int x, int y, int icon, const char *color1,const char *color2);
#endif

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);

extern const unsigned int cfgX;
extern const unsigned int cfgY;

extern const unsigned int cfgIcon1;
unsigned int Icons[11];
unsigned int Iconssec[10];
TDate date; 
TTime time; 
unsigned char iCurrIcon, iOldIcon;
unsigned char fChanged = 0;
unsigned char picmin1, picmin2;
unsigned char pichour1, pichour2;
unsigned char picsec1, picsec2;
unsigned char min,sec,hour;
extern const unsigned int cfgShowIn;
extern const char cfgcolor1[];
extern const char cfgcolor2[];
extern const unsigned int gap;
extern const int free_space;
#ifdef ELKA
#else
extern const unsigned int cfgIconsec;
extern const int cfgsec;
extern const unsigned int cfgsecondX;
extern const unsigned int cfgsecondY;
#endif

IMGHDR img1;
GBSTMR update_tmr;
int fShow;
//unsigned short format;
/*
DrwImg(IMGHDR *img, int x, int y, int *pen, int *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
  SetPropTo_Obj5(&drwobj, &rc, 0, img);
  SetColor(&drwobj, pen, brush);
  DrawObject(&drwobj);
}
*/
void GetCurrentIcon(void)
{
  switch (cfgShowIn)
  {
  case 0:
    fShow = !IsUnlocked();
    break;
  case 1:
    fShow = IsUnlocked();
    break;
  case 2:
    fShow = 1;
  }
  GetDateTime(&date,&time);
  hour = time.hour;  
	min = time.min;
	#ifdef ELKA
	#else
  if (cfgsec)            
  {                      
    sec = time.sec;      
    picsec1=sec/10;      
    picsec2=sec%10;      
  }
  #endif
  pichour1=hour/10;                     
  pichour2=hour%10; 
  picmin1=min/10;   
  picmin2=min%10;   
	GBS_StartTimerProc(&update_tmr, UPDATE_TIME, GetCurrentIcon);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

void createicon(void);
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Big Digital Clock config updated!");
      InitConfig();
      createicon();
    }
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsUnlocked())                                                                  
    {                                                                                  
      if (IsGuiOnTop(idlegui_id(icsm)))                                                      
      {                                                                                
        GUI *igui=GetTopGUI();                                                         
        if (igui)                                                                      
        {                                                                              
          if(fShow)                                                                    
          {
//            #ifdef ELKA                                                                 
            {                                                                   
//              void *canvasdata = BuildCanvas();                                 
//            #else                                                                       
//            void *idata = GetDataOfItemByID(igui, 2);                           
//            if (idata)                                                          
//            {                                                                   
//              void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];  
//            #endif                                                                      
#ifdef ELKA
              int img_wide;                                                                   
              if (Icons[pichour1])                                                            
              {                                                                               
                DrawColorPicWithCanvas(cfgX, cfgY, Icons[pichour1],cfgcolor1);                                         
                img_wide=GetImgWidth(Icons[pichour1])+free_space;                             
              }                                                                               
              if (Icons[pichour2]) DrawColorPicWithCanvas(cfgX+img_wide, cfgY, Icons[pichour2],cfgcolor1);             
              DrawColorPicWithCanvas(cfgX+2*img_wide, cfgY, Icons[10],cfgcolor1);                                                    
              int img_wide_doc=GetImgWidth(Icons[10])+free_space;                             
              if (Icons[picmin1]) DrawColorPicWithCanvas(cfgX+2*img_wide+img_wide_doc, cfgY, Icons[picmin1],cfgcolor1);
              if (Icons[picmin2]) DrawColorPicWithCanvas(cfgX+3*img_wide+img_wide_doc, cfgY, Icons[picmin2],cfgcolor1);              
#else
              int img_wide;                                                                   
              if (Icons[pichour1])                                                            
              {                                                                               
                DrawColorPicWithCanvas(cfgX, cfgY, Icons[pichour1],cfgcolor1,cfgcolor2);                                         
                img_wide=GetImgWidth(Icons[pichour1])+free_space;                             
              }                                                                               
              if (Icons[pichour2]) DrawColorPicWithCanvas(cfgX+img_wide, cfgY, Icons[pichour2],cfgcolor1,cfgcolor2);             
              DrawColorPicWithCanvas(cfgX+2*img_wide, cfgY, Icons[10],cfgcolor1,cfgcolor2);                                                    
              int img_wide_doc=GetImgWidth(Icons[10])+free_space;                             
              if (Icons[picmin1]) DrawColorPicWithCanvas(cfgX+2*img_wide+img_wide_doc, cfgY, Icons[picmin1],cfgcolor1,cfgcolor2);
              if (Icons[picmin2]) DrawColorPicWithCanvas(cfgX+3*img_wide+img_wide_doc, cfgY, Icons[picmin2],cfgcolor1,cfgcolor2);              
              if (cfgsec)                                                                                    
              {                                                                               
                if (Iconssec[picsec1]) DrawColorPicWithCanvas(cfgsecondX, cfgsecondY, Iconssec[picsec1],cfgcolor1,cfgcolor2);
                if (Iconssec[picsec2]) DrawColorPicWithCanvas(cfgsecondX+7, cfgsecondY, Iconssec[picsec2],cfgcolor1,cfgcolor2);               
              }
#endif                                                                       
            }
          }
        }                                                                              
      }                                                                                
    }
  }
  return(1);
}


static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&update_tmr);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Big Digtal Clock");
}

void createicon(void)
{
  Icons[0] = cfgIcon1;           
	Icons[1] = cfgIcon1+1;       
  Icons[2] = cfgIcon1+2;       
  Icons[3] = cfgIcon1+3;       
  Icons[4] = cfgIcon1+4;       
  Icons[5] = cfgIcon1+5;       
  Icons[6] = cfgIcon1+6;       
  Icons[7] = cfgIcon1+7;       
  Icons[8] = cfgIcon1+8;       
  Icons[9] = cfgIcon1+9;       
  Icons[10] = cfgIcon1+11;
  #ifdef ELKA
  #else 
  Iconssec[0] = cfgIconsec;    
  Iconssec[1] = cfgIconsec+1;  
  Iconssec[2] = cfgIconsec+2;  
  Iconssec[3] = cfgIconsec+3;  
  Iconssec[4] = cfgIconsec+4;  
  Iconssec[5] = cfgIconsec+5;  
  Iconssec[6] = cfgIconsec+6;  
  Iconssec[7] = cfgIconsec+7;  
  Iconssec[8] = cfgIconsec+8;  
  Iconssec[9] = cfgIconsec+9;
  #endif
} 
  
int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  createicon();
  UpdateCSMname();
  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  
  GBS_StartTimerProc(&update_tmr, UPDATE_TIME, GetCurrentIcon);
  return 0;
}
