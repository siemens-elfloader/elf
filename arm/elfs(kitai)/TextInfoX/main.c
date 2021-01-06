#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "TextInfoX.h"
#include "local_ipc.h"

#define TMR_SECOND 216
extern void kill_data(void *p, void (*func_p)(void *));

const char ipc_my_name[]=IPC_TEXTINFO_NAME;
unsigned int fShow;
CSM_DESC icsmd;

WSHDR *ws;
#define WS_MAXLEN 32


typedef struct{
  int enabled;
  RECT rc;
  WSHDR *ws;
  char pen[4];
  unsigned short font;
  unsigned short type;
  WSHDR wsh;
  unsigned short wsbody[WS_MAXLEN+1]; 
  unsigned int draw_flag;
  char fr_cl[4];
} TInfo;

TInfo InfoData[13];
 
GBSTMR mytmr;
const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};


// ----------------------------------------------------------------------------
#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

void InitInfoData(void);
void TimerProc(void)
{
  InitInfoData();
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

void FillInfoData(TInfo *Info,int x_start,int y_start, int font,const char *color,int draw_flag,const char *fr_cl)
{  
  Info->rc.x=x_start;
  Info->rc.y=y_start;
  Info->rc.x2=x_start+Get_WS_width(Info->ws,font)+1;//徨?+1 礤镳噔桦?疣犷蜞弪 钺忸潢
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  Info->draw_flag=draw_flag;
  memcpy(Info->fr_cl,fr_cl,4);
}
  
int wsprintf_bytes(WSHDR *ws, unsigned int bytes)
{
  	//char *str;
	if (bytes<=1024)
		return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
	 //str=BYTES_SG;
	else 
	{
		bytes>>=10;
		return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
		//str=KBYTES_SG;
	}  
}

const char weekdays[7][16]=
{
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};

const char weekdays1[7][16]=
{
	"Mon.",
	"Tues.",
	"Wed.",
	"Thurs.",
	"Fri.",
	"Sat.",
	"Sun."
};

const char weekdays2[7][16]=
{
	"星期一",
	"星期二",
	"星期三",
	"星期四",
	"星期五",
	"星期六",
	"星期日"
};

const char LUNAR_MONTH_TAB[12][8]=
{
	"正月",
	"二月",
	"三月",
	"四月",
	"五月",
	"六月",
	"七月",
	"八月",
	"九月",
	"十月",
	"十一月",
	"腊月",
};

const char LUNAR_DATE_TAB[31][8]=
{
	"初一",
	"初二",
	"初三",
	"初四",
	"初五",
	"初六",
	"初七",
	"初八",
	"初九",
	"初十",
	"十一",
	"十二",
	"十三",
	"十四",
	"十五",
	"十六",
	"十七",
	"十八",
	"十九",
	"二十",
	"二十一",
	"二十二",
	"二十三",
	"二十四",
	"二十五",
	"二十六",
	"二十七",
	"二十八",
	"二十九",
	"三十",
	"三十一",
};

TTime t_time;
TDate t_date;
TDate lunar_date;
//char utf8_temp[20];

void InitInfoData(void)
{
  RAMNET *net_data;
  int c;
  //int Free;
  //int Total;
  //unsigned int err;
  if (fShow)
  {
    if(NET_ENA)
    {
      InfoData[0].enabled=1;
      net_data=RamNet();
      c=(net_data->ch_number>=255)?'=':'-';
      wsprintf(InfoData[0].ws,NET_FMT,c,net_data->power);
      FillInfoData(&InfoData[0],NET_X,NET_Y,NET_FONT,NET_COLORS,
                   NET_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   NET_FRINGING_COLORS);
    }
    else
    {
      InfoData[0].enabled=0;
    }
    
    if (TEMP_ENA)
    {
      InfoData[1].enabled=1;
      c=GetAkku(1,3)-0xAAA+15;
      //char temp[20];
      //sprintf(utf8_temp, TEMP_FMT, c/10, c%10);
      //utf8_2ws(InfoData[1].ws, utf8_temp, 20);
      wsprintf(InfoData[1].ws,TEMP_FMT,c/10,c%10);
      FillInfoData(&InfoData[1],TEMP_X,TEMP_Y,TEMP_FONT,TEMP_COLORS,
                   TEMP_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   TEMP_FRINGING_COLORS);
    }
    else
    {
      InfoData[1].enabled=0;
    }
    
    if (VOLT_ENA)
    {
      InfoData[2].enabled=1;
      c=GetAkku(0,9);
      wsprintf(InfoData[2].ws,VOLT_FMT,c/1000,(c%1000)/10);
      FillInfoData(&InfoData[2],VOLT_X,VOLT_Y,VOLT_FONT,VOLT_COLORS,
                   VOLT_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   VOLT_FRINGING_COLORS);
    }
    else
    {
      InfoData[2].enabled=0;
    }
    
    if (CAP_ENA)
    {
      InfoData[3].enabled=1;
      c=*RamCap();
      wsprintf(InfoData[3].ws,CAP_FMT,c);
      FillInfoData(&InfoData[3],ACCU_X,ACCU_Y,ACCU_FONT,ACCU_COLORS,
                   ACCU_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   ACCU_FRINGING_COLORS);
    }
    else
    {
      InfoData[3].enabled=0;
    }
    
    if (CPU_ENA)
    {
      InfoData[4].enabled=1;
      c=GetCPULoad();
      wsprintf(InfoData[4].ws,CPU_FMT,c);
      FillInfoData(&InfoData[4],CPU_X,CPU_Y,CPU_FONT,CPU_COLORS,
                   CPU_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   CPU_FRINGING_COLORS);
    }
    else
    {
      InfoData[4].enabled=0;
    }
  
    if (GPRS_ENA)
    {
      InfoData[5].enabled=1;
      RefreshGPRSTraffic();
      c=*GetGPRSTrafficPointer();
      wsprintf_bytes(InfoData[5].ws,c);
      FillInfoData(&InfoData[5],GPRS_X,GPRS_Y,GPRS_FONT,GPRS_COLORS,
                   GPRS_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   GPRS_FRINGING_COLORS);
    }
    else
    {
      InfoData[5].enabled=0;
    }
    
    if (RAM_ENA)
    {
      InfoData[6].enabled=1;
      c=GetFreeRamAvail();
      wsprintf_bytes(InfoData[6].ws,c);
      FillInfoData(&InfoData[6],RAM_X,RAM_Y,RAM_FONT,RAM_COLORS,
                   RAM_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   RAM_FRINGING_COLORS);  
    }
    else
    {
      InfoData[6].enabled=0;
    }
    
    if (WEEK_ENA)
    {
    	InfoData[7].enabled=1;
    	c=GetWeek(&t_date);
    	switch(WEEK_STYLE)
    	{
    		case 0:
    			str_2ws(InfoData[7].ws, weekdays[c], 16);
    			break;
    		case 1:
    			str_2ws(InfoData[7].ws, weekdays1[c], 16);
    			break;
    		case 2:
    			gb2ws(InfoData[7].ws, weekdays2[c], 16);
    	}
    	//str_2ws(InfoData[7].ws, &weekdays[c][0], 16);
    	FillInfoData(&InfoData[7],WEEK_X,WEEK_Y,WEEK_FONT,WEEK_COLORS,WEEK_FRINGING_ENA ? TEXT_OUTLINE : 0,WEEK_FRINGING_COLORS);
    }
    else
    {
    	InfoData[7].enabled=0;
    }
    
    if (DATE_ENA)
    {
    	InfoData[8].enabled=1;
    	GetDateTime(&t_date,&t_time);
    	switch(DATE_STYLE)
    	{
    		case 0:
    			wsprintf(InfoData[8].ws, "%02d.%02d.%d", t_date.day, t_date.month, t_date.year);
    			break;
    		case 1:
    			wsprintf(InfoData[8].ws, "%02d/%02d/%d", t_date.month, t_date.day, t_date.year);
    			break;
    		case 2:
    			wsprintf(InfoData[8].ws, "%02d/%02d/%d", t_date.day, t_date.month, t_date.year);
    			break;
    		case 3:
    			wsprintf(InfoData[8].ws, "%d.%02d.%02d", t_date.year, t_date.month, t_date.day);
    			break;
    		case 4:
    			wsprintf(InfoData[8].ws, "%d-%02d-%02d", t_date.year, t_date.month, t_date.day);
    	}
    	//wsprintf(InfoData[8].ws, "%d-%02d-%02d", t_date.year, t_date.month, t_date.day);
    	FillInfoData(&InfoData[8],DATE_X,DATE_Y,DATE_FONT,DATE_COLORS,DATE_FRINGING_ENA ? TEXT_OUTLINE : 0,DATE_FRINGING_COLORS);
    }
    else
    {
    	InfoData[8].enabled=0;
    }
    
    if (TIME_ENA)
    {
    	InfoData[9].enabled=1;
    	GetDateTime(&t_date,&t_time);
    	wsprintf(InfoData[9].ws, "%02d:%02d", t_time.hour, t_time.min);
    	FillInfoData(&InfoData[9],TIME_X,TIME_Y,TIME_FONT,TIME_COLORS,TIME_FRINGING_ENA ? TEXT_OUTLINE : 0,TIME_FRINGING_COLORS);
    }
    else
    {
    	InfoData[9].enabled=0;
    }
    if (LUNAR_DATE_ENA)
    {
    	InfoData[10].enabled=1;
    	GetDateTime(&t_date, &t_time);
    	GetLunarDate(&t_date, &lunar_date);
    	if(LUNAR_DATE_STYLE)
    		wsprintf(InfoData[10].ws, "%02d", lunar_date.day);
    	else
    		wsprintf(InfoData[10].ws, "%t", LUNAR_DATE_TAB[(lunar_date.day-1)]);
    	FillInfoData(&InfoData[10],LUNAR_DATE_X,LUNAR_DATE_Y,LUNAR_DATE_FONT,LUNAR_DATE_COLORS,LUNAR_DATE_FRINGING_ENA ? TEXT_OUTLINE : 0,LUNAR_DATE_FRINGING_COLORS);
    }
    else
    {
    	InfoData[10].enabled=0;
    }
    if (LUNAR_YEAR_ENA)
    {
    	InfoData[11].enabled=1;
    	GetLunarDate(&t_date, &lunar_date);
    	wsprintf(InfoData[11].ws, "%t%t", GetLunarYearID(lunar_date.year),"年");
    	FillInfoData(&InfoData[11],LUNAR_YEAR_X,LUNAR_YEAR_Y,LUNAR_YEAR_FONT,LUNAR_YEAR_COLORS,LUNAR_YEAR_FRINGING_ENA ? TEXT_OUTLINE : 0,LUNAR_YEAR_FRINGING_COLORS);
    }
    else
    {
    	InfoData[11].enabled=0;
    }
    if (LUNAR_MONTH_ENA)
    {
    	InfoData[12].enabled=1;
    	GetDateTime(&t_date, &t_time);
    	GetLunarDate(&t_date, &lunar_date);
    	if(LUNAR_MONTH_STYLE)
    		wsprintf(InfoData[12].ws, "%02d", lunar_date.month);
    	else
    		wsprintf(InfoData[12].ws, "%t", LUNAR_MONTH_TAB[(lunar_date.month-1)]);
    	FillInfoData(&InfoData[12],LUNAR_MONTH_X,LUNAR_MONTH_Y,LUNAR_MONTH_FONT,LUNAR_MONTH_COLORS,LUNAR_MONTH_FRINGING_ENA ? TEXT_OUTLINE : 0,LUNAR_MONTH_FRINGING_COLORS);
    }
    else
    {
    	InfoData[12].enabled=0;
    }
/*    if (FLEX0_ENA)
    {
      InfoData[7].enabled=1;
      c=GetFreeFlexSpace(0,&err) / 1024;
      if (!cfgMB0) c=c;
      else
        c=c/1024;
      wsprintf(InfoData[7].ws,FLEX0_FMT,c);
      FillInfoData(&InfoData[7],FLEX0_X,FLEX0_Y,FLEX0_FONT,FLEX0_COLORS,
                   FLEX0_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   FLEX0_FRINGING_COLORS);
    }
    else
    {
      InfoData[7].enabled=0;
    }
    if (FLEX4_ENA)
    {
      InfoData[8].enabled=1;
      c=GetFreeFlexSpace(4,&err) / 1024;
      if (!cfgMB4) c=c;
        else
          c=c/1024;
      wsprintf(InfoData[8].ws,FLEX4_FMT,c);
      FillInfoData(&InfoData[8],FLEX4_X,FLEX4_Y,FLEX4_FONT,FLEX4_COLORS,
                   FLEX4_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   FLEX4_FRINGING_COLORS);
    }
    else
    {
      InfoData[8].enabled=0;
    }
    if (PER0_ENA)
    {
      InfoData[9].enabled=1;
      Free=GetFreeFlexSpace(0,&err);
      Total=GetTotalFlexSpace(0,&err);
      c=(long long)Free*100/Total;
      wsprintf(InfoData[9].ws,PER0_FMT,c);
      FillInfoData(&InfoData[9],PER0_X,PER0_Y,PER0_FONT,PER0_COLORS,
                   PER0_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   PER0_FRINGING_COLORS);
    }
    else
    {
      InfoData[9].enabled=0;
    }
    if (PER4_ENA)
    {
      InfoData[10].enabled=1;
      Free=GetFreeFlexSpace(4,&err);
      Total=GetTotalFlexSpace(4,&err);
      c=(long long)Free*100/Total;
      wsprintf(InfoData[10].ws,PER4_FMT,c);
      FillInfoData(&InfoData[10],PER4_X,PER4_Y,PER4_FONT,PER4_COLORS,
                   PER4_FRINGING_ENA ? TEXT_OUTLINE : 0,
                   PER4_FRINGING_COLORS);
    }
    else
    {
      InfoData[10].enabled=0;
    }*/
  }
}

// ----------------------------------------------------------------------------
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"TextInfo配置更新!");
      InitConfig();
      InitInfoData();
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
#ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
#endif
          GBS_StartTimerProc(&mytmr, REFRESH*TMR_SECOND/10, TimerProc);
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
    if (IsGuiOnTop(idlegui_id(icsm)) && fShow) //篷腓 IdleGui 磬 襦祛?忮瘐
    {
      GUI *igui=GetTopGUI();
      if (igui) //?铐 耋耱怏弪
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
          for (int i=0; i<(sizeof(InfoData)/sizeof(TInfo)); i++)
          {
            if (InfoData[i].enabled)
            {
              DrawCanvas(canvasdata, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 1);
              DrawString(InfoData[i].ws, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 
                         InfoData[i].font,
                         InfoData[i].draw_flag,
                         InfoData[i].pen,
                         InfoData[i].draw_flag ? InfoData[i].fr_cl : GetPaletteAdrByColorIndex(23));
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
  for (int i=0;i<(sizeof(InfoData)/sizeof(TInfo)); i++)
  {
    InfoData[i].ws=CreateLocalWS(&InfoData[i].wsh,InfoData[i].wsbody,WS_MAXLEN+1);
  }  
  TimerProc();
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TextInfoX");
}
// ----------------------------------------------------------------------------

int main(void)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
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
