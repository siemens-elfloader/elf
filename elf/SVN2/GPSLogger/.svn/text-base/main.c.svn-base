#include "..\inc\swilib.h"
#include "..\inc\gpslogger_ipc.h"
#include "minigps_logger.h"
#include "actions.h"
#include "conf_loader.h"
#include "csm_work.h"

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

unsigned int previousLength=0;

WSHDR *Out_WS;
GBSTMR mytmr;

#define UPDATE_TIME 216
#define EDLEGUI_ID (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
#define COLOR(x) (char *)(&(x))

// Импорт переменных из конфига
extern const          int Req_Clear_Cache;
extern const unsigned int TXT_X;
extern const unsigned int TXT_Y;
extern const unsigned int TXT_FONT;
extern const          int CENTER_TEXT;
extern const          char TXT_COLOR[];
extern const unsigned int TXT_ATTR;
extern const          int SHOW_IN;

#define SH_UNLOCK 0
#define SH_LOCK 1
#define SH_BOTH 2


void TimerProc()
{
    GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_GPSL_REFRESH);
    GBS_StartTimerProc(&mytmr,UPDATE_TIME,TimerProc);
}

void UpdateSett()
{
  InitConfig();
  if(Req_Clear_Cache)
  {
    KillRamNetCache();
    InitRamNetCache();
  }
}


int Get_String_Width(WSHDR *str)
{
  int i,wlen, pic_len=0;
  unsigned short *wschar;
  unsigned short symb;
  wlen = wstrlen(str);
  for(i=0;i<wlen;i++)
  {
    wschar = str->wsbody + i;
    symb = *wschar;
    pic_len += GetSymbolWidth(symb, TXT_FONT)+1;
  }
  return pic_len;
}


char IPC_me[]="GPSLogger";


// Перерисовка экрана
void RedrawScreen(CSM_RAM* data)
{
  int x_pos;
  char *xz;
  char action;
  xz= Get_Current_Location(&action);
  if(!xz)return;
  int is_unlocked = IsUnlocked();
  if(action)DoAction(action);
  
  if(!(SHOW_IN==SH_BOTH || (is_unlocked && SHOW_IN==SH_UNLOCK)||(!is_unlocked && SHOW_IN==SH_LOCK)))
  {
    mfree(xz);
    return;
  }
        
  if(IsGuiOnTop(EDLEGUI_ID)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует
    {
      void *canvasdata;

#ifdef ELKA
      {
#else      
      void *idata;
      idata=GetDataOfItemByID(igui,2);
      if (idata)
      {
#endif
        utf8_2ws(Out_WS, xz, 35);
        int len;
        len = Get_WS_width(Out_WS, TXT_FONT);     //Get_String_Width(Out_WS);
        if(CENTER_TEXT)
        {
          x_pos = sdiv(2, ScreenW() - len);
        }else x_pos = TXT_X;
       
#ifdef ELKA
	canvasdata=BuildCanvas();
#else
        canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif      
        if (previousLength>len)
          len=previousLength;
        
        previousLength=len;
        
        DrawCanvas(canvasdata,x_pos,TXT_Y,x_pos + len ,TXT_Y + GetFontYSIZE(TXT_FONT),1);
        DrawString(Out_WS,x_pos,TXT_Y,x_pos + len+1 ,TXT_Y + GetFontYSIZE(TXT_FONT)+1,TXT_FONT,TXT_ATTR,COLOR(TXT_COLOR),GetPaletteAdrByColorIndex(1));       
      }
    }
  }  
  mfree(xz);
}


int MyCSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  GPSL_IPC_MSG_UPD_TMO *updmsg;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (stricmp((char*)successed_config_filename,(char *)msg->data0)==0)
    {
      UpdateSett();
      ShowMSG(1,(int)"GPSLogger config updated!");
    }
  }
  
  if(msg->msg == MSG_IPC) 
  {
    if(msg->submess==IPC_GPSL_REFRESH)
    {
      void *icsm=FindCSMbyID(CSM_root()->idle_id);
      if (icsm) RedrawScreen(icsm);
      return 1;
    }
    IPC_REQ *ipc;
    if(ipc=(IPC_REQ*)msg->data0)
    {
      if(stricmp(ipc->name_to,IPC_me)==0)
      {
        switch(msg->submess)
        {
        case IPC_GPSL_UPD_TMO:
          
          updmsg = (GPSL_IPC_MSG_UPD_TMO*) ipc->data;
          //ShowMSG(1,(int)"TMO update received");
          Del_From_Cache(updmsg->cid, updmsg->lac);
          break;
        }
      }
    }
  }
  return(1);
}

int main(void)
{
  InitConfig();
  InitRamNetCache();
  Out_WS = AllocWS(256);
  GBS_StartTimerProc(&mytmr,UPDATE_TIME*10,TimerProc);
  PatchCSMQueue();
  return 0;
}
