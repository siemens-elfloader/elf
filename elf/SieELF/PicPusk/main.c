#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

GBSTMR mytmr;
extern const unsigned int BUT_ENA;
extern const unsigned int but_X;
extern const unsigned int but_Y;

extern const unsigned int DATE_ENA;
extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const char DATE_FMT[16];

extern const unsigned int TIME_ENA;
extern const unsigned int time_X;
extern const unsigned int time_Y;
extern const char TIME_FMT[16];

extern const unsigned int color;
extern const unsigned int date_font;
extern const unsigned int time_font;

extern const unsigned int FRINGING_ENA;
extern const unsigned int FRINGING_color;

extern const char pic_path[];

WSHDR *ws1;

#define TMR_SECOND 216

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

const char ipc_my_name[]="PicPusk";
#define IPC_UPDATE_STAT 1

const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

void TimerProc(void)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
  GBS_StartTimerProc(&mytmr,TMR_SECOND,TimerProc);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"PicPusk config updated!");
    }
  }

  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {  
  if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
    {  
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
#ifdef ELKA

	void *canvasdata = BuildCanvas();
#else
	void *idata = GetDataOfItemByID(igui, 2);
	if (idata)
	{
	  void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
           if (BUT_ENA)
           {
             FSTATS fstats;
             unsigned int err;
             if (GetFileStats(pic_path,&fstats,&err)!=-1)
               {
                 DrawCanvas(canvasdata, but_X, but_Y, but_X + GetImgWidth((int)pic_path), but_Y + GetImgHeight((int)pic_path), 1);
	         DrawImg(but_X, but_Y, (int)pic_path);
               }
           }
           
           TDate date;
           TTime time;
           GetDateTime(&date, &time); 
           
	   char *mmonth[12]={"Янв","Фев","Мар","Апр","Май","Июн","Июл","Авг","Сен","Окт","Ноя","Дек"};
	   char *dday[7]={"Пн","Вт","Ср","Чт","Пт","Сб","Вс"};
           
           //char *mmonth[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	   //char *dday[7]={"Mon","Tue","Wen","Thu","Fri","Sat","Sun"};

           if (DATE_ENA)
           {           
            wsprintf(ws1, DATE_FMT, dday[GetWeek(&date)], date.day, mmonth[date.month-1]);
            DrawCanvas(canvasdata, date_X, date_Y, date_X+Get_WS_width(ws1, date_font)+1, date_Y+GetFontYSIZE(date_font), 1); 
            DrawString(ws1, date_X, date_Y, date_X+Get_WS_width(ws1, date_font)+1, date_Y+GetFontYSIZE(date_font), date_font,
                       FRINGING_ENA ? TEXT_OUTLINE : 0,
                       GetPaletteAdrByColorIndex(color), 
                       FRINGING_ENA ? GetPaletteAdrByColorIndex(FRINGING_color) : GetPaletteAdrByColorIndex(23)); 

           }
           
           if (TIME_ENA)
           {
            wsprintf(ws1, TIME_FMT, time.hour, time.min);
            DrawCanvas(canvasdata, time_X, time_Y, time_X+Get_WS_width(ws1, time_font)+1, time_Y+GetFontYSIZE(time_font), 1); 
            DrawString(ws1,time_X,time_Y,time_X+Get_WS_width(ws1, time_font)+1, time_Y+GetFontYSIZE(time_font),time_font,
                       FRINGING_ENA ? TEXT_OUTLINE : 0,
                       GetPaletteAdrByColorIndex(color), 
                       FRINGING_ENA ? GetPaletteAdrByColorIndex(FRINGING_color) : GetPaletteAdrByColorIndex(23));                       

           }
           
                     
#ifdef ELKA
#else
	}
#endif
      }
    }
  }

  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  ws1 = AllocWS(20);
  TimerProc();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  FreeWS(ws1);   
  GBS_DelTimer(&mytmr);  
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"PicPusk");
}


int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();  
  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched(); 

  return 0;
}
