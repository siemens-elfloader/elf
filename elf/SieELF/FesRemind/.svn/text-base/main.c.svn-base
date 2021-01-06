#include "swilib.h"
#include "conf_loader.h"
#include "FesRemind.h"
#include "sieapi.h"

extern void kill_data(void *p, void (*func_p)(void *));

static char zhName[] = "节日提醒";
int FirstRun = 1,cnt = 0;
static int AppNum;
char nTime[7];
unsigned int fShow;
char **start_Time,**end_Time;

CSM_DESC icsmd;
TTime t_time;
TDate t_date;

typedef struct{
  int enabled;
  RECT rc;
  WSHDR *ws;
  char pen[4];
  unsigned short font;
  unsigned short type;
  unsigned int draw_flag;
  char fr_cl[4];
  int enaScroll;
  int scroll_pos;
} TInfo;

TInfo InfoData[6];
GBSTMR mytmr;
const IPC_REQ my_ipc={
  IPC_FESREMIND_NAME,
  IPC_FESREMIND_NAME,
  NULL
};


// ----------------------------------------------------------------------------
#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

//搜索自定义节日操作
static int FindBirName(WSHDR* ws,const char *source,const char *sub)
{
  char *p = strstr(source,sub);
  if (p) 
  {
    char *pa = strchr(p,0x0A);
    char findname[30];
    strncpy(findname,p+7,pa - p - 7);
    wsprintf(ws,"%t%t%t","【",findname,"】");
    return 1;
  }
  else
  {
    return 0;}
}

void FindApp(char *source,char *search,char **result)
{
  for (int j=0;j < AppNum;j++)
  {
    char *s = strstr(source,search);
    if (s)
    {
      int c,il=0;
      s+= strlen(search);
      while((c=*s++) != 0x0A)
      {
        if (il < 59) result[j][il++]=c;
      }
      result[j][il] = 0;
      source = s;
    }
  }
}

//搜索更新时间
int GetUpdateTime(char *source,char *time1,char *time2)
{
  int d;
  d = source[0] - 48;
  switch(d){
  case 0:
    time1 = 0;
    time2 = 0;
    break;
  case 1:
    strncpy(time1,source+1,6);
    time1[6] = 0;
    time2 = 0;
    break;
  case 2:
    time1 = 0;
    strncpy(time2,source+1,6);
    time2[6] = 0;
    break;
  case 3:
    strncpy(time1,source+1,6);
    time1[6] = 0;
    strncpy(time2,source+7,6);
    time2[6] = 0;
  }
  return d;
}

//搜索当日自定义事件数量
static int getAppNum(char *source,char *search)
{
  int is = 0;
  while (is < 20)
  {
    char *p = strstr(source,search);
    if (p)
    {
      is++;
      source = p + strlen(search);
    }
    else return is;
  }
}

void InitInfoData(void);
void TimerProc(void)
{
  char oDian[7] = "00h00m";
  GetDateTime(&t_date,&t_time);
  sprintf(nTime,"%02dh%02dm",t_time.hour,t_time.min); 
  cnt++;
  if (FirstRun == 1) InitInfoData();
  else if (cnt == 35)
  {
    int k = 0;
    cnt = 0;
    for(int ii = 0;ii < AppNum;ii++)
    {
      if (start_Time[ii])  k += (strncmp(nTime,start_Time[ii],6) == 0);
      if (end_Time[ii])    k += (strncmp(nTime,end_Time[ii],6) == 0);
    }
    k += (strcmp(nTime,oDian) == 0);
    if (k > 0)  InitInfoData();
  }
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

void FillInfoData(TInfo *Info,int style,int x_start,int y_start, int font,const char *color,int draw_flag,const char *fr_cl)
{
  int width =Get_WS_width(Info->ws,font);
  int scrwth = ScreenW();
  switch(style)
  {
    case 0:
      Info->rc.x = x_start;
      if (x_start + width + 1 < scrwth)
      {
        Info->rc.x2 = x_start + width + 1;
        Info->enaScroll = 0;
      }
      else
      {
        Info->rc.x2 = scrwth - x_start;
        Info->enaScroll = width;
        Info->scroll_pos = 1;
      }
      break;
      
    case 1:
      if (width < scrwth)
      {
        Info->rc.x = (scrwth-width)/2 - 1;
        Info->rc.x2 = (scrwth + width)/2;
        Info->enaScroll = 0;
      }
      else
      {
        Info->rc.x = 4;
        Info->rc.x2 = scrwth - 4;
        Info->enaScroll = width;
        Info->scroll_pos = 1;
      }
      break;
      
    case 2:      
      if (width < (x_start -2 ))
      {
        Info->rc.x = x_start - width - 1;
        Info->enaScroll = 0;
      }
      else
      {
        Info->rc.x = scrwth - x_start;
        Info->enaScroll = width;
        Info->scroll_pos = 1;
      }
      Info->rc.x2 = x_start;
  }
  Info->rc.y=y_start;
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  Info->draw_flag=draw_flag;
  memcpy(Info->fr_cl,fr_cl,4);
}
  

const char weekdays1[7][5]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
const char weekdays2[7][8]={"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
const char jDay[24][9]={
                        "【小寒】","【大寒】","【立春】","【雨水】","【惊蛰】","【春分】",
                        "【清明】","【谷雨】","【立夏】","【小满】","【芒种】","【夏至】",
                        "【小暑】","【大暑】","【立秋】","【处暑】","【白露】","【秋分】",
                        "【寒露】","【霜降】","【立冬】","【小雪】","【大雪】","【冬至】"}; 

void InitInfoData(void)
{
  if (fShow)
  {
    char *FestaData = LoadFileBuf(BIRS_FILE);
    char toDay[8];
    char str_App[300];
    sprintf(toDay,"AP%02d.%02d",t_date.month,t_date.day);
    AppNum = getAppNum(FestaData,toDay);
    if (AppNum)
      {
        char **apps = (char **)malloc(sizeof(char *) * AppNum);
        start_Time = (char **)malloc(sizeof(char *) * AppNum);
        end_Time = (char **)malloc(sizeof(char *) * AppNum);
        for (int i = 0;i < AppNum;i++)
        {
          apps[i] = (char *)malloc(sizeof(char) * 70);
          start_Time[i] = (char *)malloc(sizeof(char) * 7);
          end_Time[i] = (char *)malloc(sizeof(char) * 7);
        }
        
        FindApp(FestaData,toDay,apps);
        
        for (int i = 0;i < AppNum;i++)
        {
          int ts = GetUpdateTime(apps[i],start_Time[i],end_Time[i]);
          char *sd;
          switch (ts)
          {
            case 0:
              sd = apps[i] + 2;
              break;
            case 1:
              if (strncmp(nTime,start_Time[i],6) >= 0) sd = apps[i] + 8;
              else  sd = 0;
              break;
            case 2:
              if (strncmp(end_Time[i],nTime,6) > 0)  sd = apps[i] + 8;
              else sd = 0;
              break;
            case 3:
              if ((strncmp(nTime,start_Time[i],6) >= 0) && (strncmp(end_Time[i],nTime,6) > 0))
                sd = apps[i] + 14;
              else  sd = 0;
          }
          if (sd) strcat(str_App,sd);
          if (apps[i]) mfree(apps[i]);
         }
        if(apps) mfree(apps);
        if (str_App)
        {
          InfoData[5].enabled = 1;
          wsprintf(InfoData[5].ws,_percent_t,str_App);
          FillInfoData(&InfoData[5],1,APP_X,APP_Y,FontType(APP_FONT),APP_CS, TEXT_OUTLINE,APP_CB);
        }
        else InfoData[5].enabled = 0;
      }
    else InfoData[5].enabled = 0;

      if (TEXT_ENA)
         {
           InfoData[0].enabled=1;
           wsprintf(InfoData[0].ws,_percent_t,TEXT_FMT);
           FillInfoData(&InfoData[0],TEXT_XT,TEXT_X,TEXT_Y,FontType(TEXT_FONT),TEXT_CS, TEXT_OUTLINE,TEXT_CB);
         }
       else
         {
           InfoData[0].enabled=0;
         }
 
       TDate pLdate;
       int f = GetLunarDate(&t_date, &pLdate);    
       if (CYEAR_ENA)
         {
           int d = GetLunarYearID(pLdate.year);
           int e = GetLunarAnimal(pLdate.year);   
    	   InfoData[1].enabled=1;
           wsprintf(InfoData[1].ws,"%t%t",d,e);
    	   FillInfoData(&InfoData[1],CYEAR_XT,CYEAR_X,CYEAR_Y,FontType(CYEAR_FONT),CYEAR_CS,TEXT_OUTLINE,CYEAR_CB);
         }
       else
         {
    	   InfoData[1].enabled=0;
         }

       if (CDATE_ENA)
         {
    	    InfoData[2].enabled=1;
            if ((f == 0) || (f >= pLdate.month)) 
               wsprintf(InfoData[2].ws,"%t%t%t",cMName[pLdate.month],cOName[1],cDName[pLdate.day]);
            if (f == pLdate.month - 1)
               wsprintf(InfoData[2].ws,"%t%t%t%t",cOName[2],cMName[f],cOName[1],cDName[pLdate.day]);
            if ((f !=  0) && (f < pLdate.month - 1))
               wsprintf(InfoData[2].ws,"%t%t%t",cMName[pLdate.month - 1],cOName[1],cDName[pLdate.day]);
    	    FillInfoData(&InfoData[2],CDATE_XT,CDATE_X,CDATE_Y,FontType(CDATE_FONT),CDATE_CS,TEXT_OUTLINE,CDATE_CB);
         }
       else
         {
            InfoData[2].enabled=0;
         }

       if (BIR_ENA)
         {
            char oDay[7],nDay[7];
            WSHDR *wsBir1 = AllocWS(10); 
            WSHDR *wsBir2 = AllocWS(20); 
            WSHDR *wsBir3 = AllocWS(5);
            sprintf(oDay,"L%02d.%02d:",pLdate.month,pLdate.day);
            sprintf(nDay,"N%02d.%02d:",t_date.month,t_date.day);
            
            int bir1 = FindBirName(wsBir1,FestaData,oDay);
            int bir2 = FindBirName(wsBir2,FestaData,nDay);
            int bir3 = LunarHolId(t_date);
            if (bir3)  gb2ws(wsBir3, &jDay[bir3 - 1][0], 9);
            
            if (bir1 + bir2 + bir3)
            {
              wsprintf(InfoData[3].ws,_percent_t,"今日");
              if (bir1) wstrncat(InfoData[3].ws,wsBir1,wstrlen(wsBir1));
              if (bir2) wstrncat(InfoData[3].ws,wsBir2,wstrlen(wsBir2));
              if (bir3) wstrncat(InfoData[3].ws,wsBir3,wstrlen(wsBir3));
              InfoData[3].enabled = 1;
              FillInfoData(&InfoData[3],OBIR_XT,OBIR_X,OBIR_Y,FontType(OBIR_FONT),OBIR_CS,TEXT_OUTLINE,OBIR_CB);
            }
            else InfoData[3].enabled = 0;
            
            FreeWS(wsBir1);
            FreeWS(wsBir2);
            FreeWS(wsBir3);
         }
       else
         {
            InfoData[3].enabled = 0;
         }
       
       if (WEEK_ENA)
         {
            InfoData[4].enabled=1;
            int c=GetWeek(&t_date);
            switch(WEEK_STYLE)
              {
    	         case 0:
    		    str_2ws(InfoData[4].ws, &weekdays1[c][0], 5);
    		    break;
    	         case 1:
    		    gb2ws(InfoData[4].ws, &weekdays2[c][0], 8);
               }
             FillInfoData(&InfoData[4],WEEK_XT,WEEK_X,WEEK_Y,FontType(WEEK_FONT),WEEK_COLORS,TEXT_OUTLINE,WEEK_FRINGING_COLORS);
         }
       else
         {
            InfoData[4].enabled=0;
         }
      FirstRun = 0;
      FreeFileBuf(FestaData);
  }
}

// ----------------------------------------------------------------------------

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"'节日提醒'配置更新!");
      FirstRun = 1;
      InitInfoData();
    }
  }
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,IPC_FESREMIND_NAME)==0)
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
          GBS_StartTimerProc(&mytmr, TMR_SECOND, TimerProc);
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
    if (IsGuiOnTop(idlegui_id(icsm)) && fShow)
    {
      GUI *igui=GetTopGUI();
      if (igui)
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
              if (i == 5)
              {
                DrawCanvas(canvasdata, InfoData[i].rc.x - 2, InfoData[i].rc.y -2, InfoData[i].rc.x2 + 2, InfoData[i].rc.y2 + 2, 1);
                DrawRoundedFrame(InfoData[i].rc.x - 2, InfoData[i].rc.y - 2, InfoData[i].rc.x2 + 2, InfoData[i].rc.y2 + 2, 2, yrnd, fstyle, frmmain_color, frmbg_color);
              }
              else DrawCanvas(canvasdata, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 1);
              if (InfoData[i].enaScroll)
              {
                DrawScrollString(InfoData[i].ws, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2,
                                 InfoData[i].scroll_pos, InfoData[i].font, InfoData[i].draw_flag, InfoData[i].pen, InfoData[i].fr_cl);
                if(InfoData[i].enaScroll < (InfoData[i].scroll_pos + 60))  InfoData[i].scroll_pos = 1;
                else InfoData[i].scroll_pos += SPEED;
              }
              else
              {
                DrawString(InfoData[i].ws, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2,
                           InfoData[i].font, InfoData[i].draw_flag, InfoData[i].pen, InfoData[i].fr_cl);
              }
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
    if (i == 3) InfoData[i].ws = AllocWS(35);
    else
      if (i == 5) InfoData[i].ws = AllocWS(300);
      else InfoData[i].ws = AllocWS(12);
  }
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  for (int i=0;i<(sizeof(InfoData)/sizeof(TInfo)); i++)
  {
    FreeWS(InfoData[i].ws);
  }
  for (int i = 0;i < AppNum;i++)
  {
    if (start_Time[i]) mfree(start_Time[i]);
    if (end_Time[i]) mfree(end_Time[i]);
  }
  if (start_Time)  mfree(start_Time);
  if (end_Time)  mfree(end_Time);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),_percent_t,(zhName));
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
