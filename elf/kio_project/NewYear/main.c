/*
TODO:
парсинг базы событий - пока обойдемся думаю мало у кого больше 512  слбытий
*/

//#define REDRW

#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"

#include "const.c"

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

char pt[]="%t";
char star[]="*";

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

void (*old_idle_ghook)(GUI *gui, int cmd);
void (*old_idle_redraw)(void *data);

volatile int hook_state=0;

#pragma inline
void patch_input(INPUTDIA_DESC* inp,int x,int y,int x2,int y2)
{
  inp->rc.x=x;
  inp->rc.y=y;
  inp->rc.x2=x2;
  inp->rc.y2=y2;
}

#pragma inline
void patch_header(HEADER_DESC* head,int x,int y,int x2,int y2)
{
  head->rc.x=x;
  head->rc.y=y;
  head->rc.x2=x2;
  head->rc.y2=y2;
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;


GBSTMR mytmr,checktmr,msuptmr;
WSHDR *ws;
char ws_sh=0;
int count=0;

TDate cal_d;
TTime cal_t;
TDate cal_ds;
TTime cal_ts;
TDate stp_d;
TTime stp_t;

CSM_DESC icsmd;

extern void kill_data(void *p, void (*func_p)(void *));

typedef struct 
{
  short year;
  short un1;
  char month;
  char day;
  short un2;
  char hour;
  char min;
  short un3;
}dates;


char days[12]={31,28,31,30,31,30,31,31,30,31,30,31};

char add_tx[256];
char add_day;
char add_sh=0;

void AdditionRead()
{
  unsigned int ul;
  add_tx[0]=0;
  char buff[1000];
  char buff2[100];
  char *it=(char*)&buff;
  if (strlen(cfg_msap)<=0) return;
  int fl=fopen(cfg_msap,A_ReadOnly+A_TXT,0,&ul);
  if (fl<0) return;
  TDate dt;
  GetDateTime(&dt,0);
  int l=1;
  while (l>0)
  {
    l=fread(fl,(void *)&buff,sizeof(buff)-1,&ul);
    buff[sizeof(buff)-1]=0;
    if (l<=0) break;
    sprintf(buff2,"%d.%d:",dt.day,dt.month);
    it=strstr(buff,buff2);
    if (!it) continue;
    it--;
    if ((*it)!='\n') continue;
    it+=1+strlen(buff2);
    char *p=strchr(it,'\n');
    add_day=dt.day;
    if (p)
    {
      p--; if (*p!='\r') p++;
      *p=0;
      strcpy(add_tx,it);
      break;
    }
    else
    {
      if (strlen(it)>255)
      {
        strncpy(add_tx,it,255);
        break;
      }
      else
      {
        int ln=strlen(it);
        strcpy(add_tx,it);
        l=fread(fl,(void *)&buff,sizeof(buff)-1,&ul);
        buff[sizeof(buff)-1]=0;
        if (l>0)
        {
          char *p=strchr(buff,'\n');
          if (p)
          {
            p--; if (*p!='\r') p++;
            *p=0;
          }
          strncat(add_tx,buff,255-ln);
        }
        break;
      }
    }
  }
  fclose(fl,&ul);
}


char CheckD(char lev, dates *t, dates *cal, char rep,char mas)
{
  switch (lev)
  {
  case 1:
    {
      if (cal->year > t->year) return 1;
      if ((cal->year==t->year)&&(CheckD(2,t,cal,rep,mas))) return 1;
      if (rep==1)
      {
        cal->year=t->year;
        if (CheckD(2,t,cal,rep,mas)) return 1;
        cal->year++;
        return 1;
      }
      if (rep>1) {cal->year=t->year; cal->month=0; CheckD(2,t,cal,rep,mas); return 1;}
      return 0;      
    } 
  case 2:
    {
      if (cal->month > t->month) return 1;
      if ((cal->month == t->month)&&(CheckD(3,t,cal,rep,mas))) return 1;
      if (rep==2)
      {
        cal->month=t->month;
        if (CheckD(3,t,cal,rep,mas)) return 1;
        if (cal->month>=12)
        {
          cal->month=0;
          cal->year++;
        }
        else cal->month++;
        return 1;
      }
      if (rep>2) {cal->year=t->year; cal->month=t->month; cal->day=0; CheckD(3,t,cal,rep,mas); return 1;}
      return 0;      
    } 
  case 3:
    {
      if (cal->day > t->day) return 1;
      if ((cal->day==t->day)&&(CheckD(4,t,cal,rep,mas))) return 1;
      if (rep==3)
      {
        cal->day=t->day;
        if (mas==0)
        {
          if (CheckD(4,t,cal,rep,mas)) return 1;
          if (cal->day>=(days[cal->month-1]+((cal->year%4)?0:1)))
          {
            cal->day=0;
            if (cal->month>=12)
            {
              cal->month=0;
              cal->year++;
            }
            else cal->month++;
          }
          else cal->day++;
          return 1;
        }
        else
        {
          TDate dt;
          dt.year=cal->year;
          dt.month=cal->month;
          dt.day=cal->day;
          char d=GetWeek(&dt);
          switch (d)
          {
          case 0: if((mas&1)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 1: if((mas&2)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 2: if((mas&4)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 3: if((mas&8)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 4: if((mas&16)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 5: if((mas&32)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          case 6: if((mas&64)&&(CheckD(4,t,cal,rep,mas))) return 1;break;
          }
          for (char b=0;b<8;b++)
          {
            switch (d)
            {
            case 0: if(mas&1) return 1;break;
            case 1: if(mas&2) return 1;break;
            case 2: if(mas&4) return 1;break;
            case 3: if(mas&8) return 1;break;
            case 4: if(mas&16) return 1;break;
            case 5: if(mas&32) return 1;break;
            case 6: if(mas&64) return 1;break;
            }
            if (cal->day>=(days[cal->month-1]+((cal->year%4)?0:1)))
            {
              cal->day=0;
              if (cal->month>=12)
              {
                cal->month=0;
                cal->year++;
              }
              else cal->month++;
            }
            else cal->day++;
            dt.day=cal->day;
            d=GetWeek(&dt);
          }
          return 0;
        }
      }
      return 0;      
    }
  case 4:
    {
      if (cal->hour > t->hour) return 1;
      if ((cal->hour==t->hour)&&(CheckD(5,t,cal,rep,mas))) return 1;
      return 0;      
    }
  case 5:
    {
      if (cal->min > t->min) return 1;
      return 0;      
    }
  }
  return 0;
}

void ReadCal()
{
  unsigned int ul;
#ifdef DEBUG
  int log=fopen("0:\\log.txt",A_ReadWrite+A_TXT+A_Truncate+A_Create,P_READ+P_WRITE,&ul);
#endif
  WSHDR *wst=AllocWS(200);
  dates tmp1,tmp1s,*tmp2,*tmp3,cur,end,tmp;
  end.year=3033;
  int i,j;
  int f;
  short buff[200];
  short len;
  tmp1.year=3033;
  tmp1.month=12;
  tmp1.day=31;
  tmp1.hour=23;
  tmp1.min=59;
  {
    TTime time;
    TDate date;
    GetDateTime(&date,&time);
    cur.year=date.year;
    cur.month=date.month;
    cur.day=date.day;
    cur.hour=time.hour;
    cur.min=time.min;
  }
  for (int p=0;p<2;p++)
  {
    i=j=0;
    do
    {
      if (p==0) sprintf((char*)&buff,"0:\\System\\apo\\app\\%02x\\%02x",i,j);
      else sprintf((char*)&buff,"0:\\System\\apo\\task\\%02x\\%02x",i,j);
      if ((f=fopen((char*)&buff,A_ReadOnly+A_BIN,0,&ul))!=-1)
      {
#ifdef DEBUG
  fwrite(log,(char*)&buff,strlen((char*)&buff),&ul);
  fwrite(log,"\n",strlen("\n"),&ul);
#endif

        int l=fread(f,buff,sizeof(buff),&ul);
        l/=2;
        short t=3;
        char e=0,en;
        do
        switch (buff[t])
        {
        case 0x11: //text
          { 
            t++;
            if(t%2)
            {
              if(buff[t]) break;
              else t++;
            }
            len=buff[t];
            t++;
            memcpy(wst->wsbody,&buff[t],len);
            t+=len/2;
            break;
          }
        //case 0x15: //alarm
        case 0x16: //start
          { 
            t++;
            if(t%2)
            {
              if (buff[t]) break;
              else t++;
            }
            tmp2=(dates *)&buff[t];
            t+=6;
            break;
          }
       case 0x1A: //stop
          { 
            t++;
            if(t%2)
            {
              if (buff[t]) break;
              else t++;
            }
            tmp3=(dates *)&buff[t];
            t+=6;
            break;
          }
        case 0x1b: //repeat
          {
            t++;
            if(t%2)
            {
              if (buff[t]) break;
              else t++;
            }
            t+=2;
            switch (buff[t])
            {
            case 'Y'://year
              e=1; t+=4; break;
            case 'M'://month
              e=2; t+=7; break;
            case 'D'://week 7 day
              e=3; en=0; t+=3; break;
            case 'W'://week 6 day
              {
                e=3;
                while (buff[t]!=' ') t++;
                t++;
                en=0;
                while (buff[t]>'2')
                {
                  switch (buff[t])
                  {
                  case 'M': //1
                    {
                      t++;
                      if (buff[t]=='O') en|=1;
                      break;
                    }
                  case 'T'://2,4
                    {
                      t++;
                      if (buff[t]=='U') en|=2;
                      else if (buff[t]=='H') en|=8;
                      break;
                    }
                  case 'W': //3
                    { 
                      t++;
                      if (buff[t]=='E') en|=4;
                      break;
                    }
                  case 'F'://5
                    { 
                      t++;
                      if (buff[t]=='R') en|=16; 
                      break;
                    }
                  case 'S'://6,7
                    {
                      t++;
                      if (buff[t]=='A') en|=32;
                      else if (buff[t]=='U') en|=64; 
                      break;
                    }
                  default: t++;
                  }   
                  t+=2;
                }
                if (en==127) en=0;
              } 
              break;
            }
            if (buff[t]>='1')
            {
              end.year=(buff[t]-0x30);
              t++;
              end.year*=10;
              end.year+=(buff[t]-0x30);
              t++;
              end.year*=10;
              end.year+=(buff[t]-0x30);
              t++;
              end.year*=10;
              end.year+=(buff[t]-0x30);
              t++;
              end.month=(buff[t]-0x30);
              t++;
              end.month*=10;
              end.month+=(buff[t]-0x30);
              t++;
              end.day=(buff[t]-0x30);
              t++;
              end.day*=10;
              end.day+=(buff[t]-0x30);
              end.hour=0;
              end.min=0;
            }
          }
        case 21: //Alert params
        default : t++;
        }
        while (t<l);
        fclose(f,&ul);
#ifdef DEBUG
  sprintf((char*)&buff,"%d.%d.%d %02d:%02d\n", tmp2->day,tmp2->month,tmp2->year,tmp2->hour,tmp2->min);
  fwrite(log,buff,strlen((char*)&buff),&ul);
  sprintf((char*)&buff,"%d.%d.%d %02d:%02d\n",end.day,end.month,end.year,end.hour,end.min);
  fwrite(log,buff,strlen((char*)&buff),&ul);
  sprintf((char*)&buff,"%d\n", en);
  fwrite(log,(char*)&buff,strlen((char*)&buff),&ul);
  fwrite(log,&wst->wsbody[1],wst->wsbody[0]*2,&ul);
  sprintf((char*)&buff,"\n", en);
  fwrite(log,(char*)&buff,strlen((char*)&buff),&ul);
        if (memcmp(tmp2,tmp3,sizeof(*tmp2))==0) 
        {
          fwrite(log,"Day++\n",7,&ul);
          tmp3->day++;
        }
  sprintf((char*)&buff,"%d.%d.%d %02d:%02d\n", tmp3->day,tmp3->month,tmp3->year,tmp3->hour,tmp3->min);
  fwrite(log,buff,strlen((char*)&buff),&ul);

#else
          if (memcmp(tmp2,tmp3,sizeof(*tmp2))==0) 
        {
          tmp3->day++;
        }
#endif

#ifndef DEBUG
       memcpy(&tmp,tmp2,sizeof(tmp));
        if (CheckD(1,&cur,tmp2,e,en))
        {
          if (CheckD(1,tmp2,&tmp1,0,0))
          {
            if (CheckD(1,tmp2,&end,0,0))
            {
              memcpy(&tmp1,tmp2,sizeof(tmp1));
              memcpy(&tmp1s,tmp3,sizeof(tmp1));
              memcpy(ws->wsbody,wst->wsbody,len);
            }
          }
          else if (CheckD(1,&cur,tmp3,e,en))
          {
            memcpy(tmp2,&tmp,sizeof(tmp));
            if (CheckD(1,tmp3,&tmp1,0,0))
            {
              if (CheckD(1,tmp2,&end,0,0))
              {
                memcpy(&tmp1,tmp2,sizeof(tmp1));
                memcpy(&tmp1s,tmp3,sizeof(tmp1));
                memcpy(ws->wsbody,wst->wsbody,len);
              }
            }
          }
        }
#else
        memcpy(&tmp,tmp2,sizeof(tmp));
        if (CheckD(1,&cur,tmp2,e,en))
        {
          fwrite(log,"1 etap\n",7,&ul);
          if (CheckD(1,tmp2,&tmp1,0,0))
          {
            fwrite(log,"2 etap\n",7,&ul);
            if (CheckD(1,tmp2,&end,0,0))
            {
              fwrite(log,"3 etap\n",7,&ul);
              memcpy(&tmp1,tmp2,sizeof(tmp1));
              memcpy(&tmp1s,tmp3,sizeof(tmp1));
              memcpy(ws->wsbody,wst->wsbody,len);
            }
          }
          else if (CheckD(1,&cur,tmp3,e,en))
          {
            memcpy(tmp2,&tmp,sizeof(tmp));
            fwrite(log,"1 etap2\n",8,&ul);
            if (CheckD(1,tmp3,&tmp1,0,0))
            {
              fwrite(log,"2 etap2\n",8,&ul);
              if (CheckD(1,tmp2,&end,0,0))
              {
                fwrite(log,"3 etap2\n",8,&ul);
                memcpy(&tmp1,tmp2,sizeof(tmp1));
                memcpy(&tmp1s,tmp3,sizeof(tmp1));
                memcpy(ws->wsbody,wst->wsbody,len);
              }
            }
          }
        }
#endif
      }
      j++;
      if (j==0x20){ j=0;i++;}
    }
    while (i<0x10);//(f!=-1); ////////////////////////////////ИСПРАВИТЬ!!!!!
  }
  cal_d.year=tmp1.year;
  cal_d.month=tmp1.month;
  cal_d.day=tmp1.day;
  cal_t.hour=tmp1.hour;
  cal_t.min=tmp1.min;
  cal_t.param=0;
  cal_ds.year=tmp1s.year;
  cal_ds.month=tmp1s.month;
  cal_ds.day=tmp1s.day;
  cal_ts.hour=tmp1s.hour;
  cal_ts.min=tmp1s.min;
  cal_ts.param=0;
  FreeWS(wst);
#ifdef DEBUG
  sprintf((char*)&buff,"%d.%d.%d %02d:%02d\n", cal_d.day,cal_d.month,cal_d.year,cal_t.hour,cal_t.min);
  fwrite(log,(char*)&buff,strlen((char*)&buff),&ul);
  fclose(log,&ul);
#endif
}

void Check(void);

void CheckAllow()
{
  if (count>0) count--;
  if (cfg_ss) Check();
};


void RedrawGUI(void)
{
  DirectRedrawGUI();
}

void CountTimer(TDate *date1,TTime *time1)
{
  TTime time;
  TDate date;
  GetDateTime(&date,&time);
  if (date.day>=add_day) SUBPROC((void *)AdditionRead);
  time1->param=cal_t.param-time.param;
  if (time1->param>60) {time1->param=cal_t.param-time.param+60; time.min++;};
  time1->min=cal_t.min-time.min;
  if (time1->min>60) {time1->min=cal_t.min-time.min+60; time.hour++;};
  time1->hour=cal_t.hour-time.hour;
  if (time1->hour>24) {time1->hour=cal_t.hour-time.hour+24; date.day++;};
  date1->day=cal_d.day-date.day;
  if (date1->day>31) {date1->day=cal_d.day-date.day+days[date.month-1]+((date.year%4)?0:1); date.month++;};//get number of day in munth
  date1->month=cal_d.month-date.month;
  if (date1->month>12) {date1->month=cal_d.month-date.month+12; date.year++;};
  date1->year=cal_d.year-date.year;
}

void CountTimerST(TDate *date1,TTime *time1)
{
  TTime time;
  TDate date;
  GetDateTime(&date,&time);
  time1->param=cal_ts.param-time.param;
  if (time1->param>60) {time1->param=cal_ts.param-time.param+60; time.min++;};
  time1->min=cal_ts.min-time.min;
  if (time1->min>60) {time1->min=cal_ts.min-time.min+60; time.hour++;};
  time1->hour=cal_ts.hour-time.hour;
  if (time1->hour>24) {time1->hour=cal_ts.hour-time.hour+24; date.day++;};
  date1->day=cal_ds.day-date.day;
  if (date1->day>31) {date1->day=cal_ds.day-date.day+days[date.month-1]+((date.year%4)?0:1); date.month++;};//get number of day in munth
  date1->month=cal_ds.month-date.month;
  if (date1->month>12) {date1->month=cal_ds.month-date.month+12; date.year++;};
  date1->year=cal_ds.year-date.year;
}


void method0(MAIN_GUI *data)
{
  DrawRoundedFrame(0,0,131,175,0,0,0,
		   GetPaletteAdrByColorIndex(cfg_tc),
		   GetPaletteAdrByColorIndex(cfg_tb));
  if (cfg_pic)
    DrawImg(cfg_px, cfg_py, cfg_pn);
  DrawString(ws,3,cfg_my,128,172,cfg_tf,cfg_ta,GetPaletteAdrByColorIndex(cfg_tc),GetPaletteAdrByColorIndex(23));

  TTime time,time1;
  TDate date,date1;
  CountTimer(&date1,&time1);
  GetDateTime(&date,&time);
  char ttext[256],tmp[256];
  if (cal_d.year<date.year)  
  {
    wsprintf(data->ws1,pt,tx_late);
    DrawString(data->ws1,3,cfg_tmy,128,172,cfg_tmf,cfg_tma,GetPaletteAdrByColorIndex(cfg_tmc),GetPaletteAdrByColorIndex(cfg_tmb));
    if (cal_d.year<date.year)
      SUBPROC((void *)ReadCal);
  }
  else
  {
    ttext[0]=0;
    if (strlen(tx_left)>0)
    {
      sprintf(tmp,"%s\n",tx_left);
      strcat(ttext,tmp);
    }
    if (date1.year>0)
    {
      sprintf(tmp,"%u %s\n",date1.year,tx_year);
      strcat(ttext,tmp);
    }
    if (date1.month>0)
    {
      sprintf(tmp,"%u %s\n",date1.month,tx_month);
      strcat(ttext,tmp);
    }
    if (date1.day>0)
    {
      sprintf(tmp,"%u %s\n",date1.day,tx_day);
      strcat(ttext,tmp);
    }
    if (cfg_sec)
      sprintf(tmp,"%02u:%02u:%02u\n",time1.hour,time1.min,time1.param);
    else
     sprintf(tmp,"%02u:%02u\n",time1.hour,time1.min,time1.param);
    strcat(ttext,tmp);
    wsprintf(data->ws1,pt,ttext);
    DrawString(data->ws1,3,cfg_tmy,128,172,cfg_tmf,cfg_tma,GetPaletteAdrByColorIndex(cfg_tmc),GetPaletteAdrByColorIndex(cfg_tmb));    
    if (cfg_tim)
    {
      if (cfg_sec)
        sprintf(tmp,"%02u:%02u:%02u\n",time.hour,time.min,time.param);
      else
        sprintf(tmp,"%02u:%02u\n",time.hour,time.min);
      wsprintf(data->ws1,pt,tmp);
      DrawString(data->ws1,3,cfg_cly,128,172,cfg_clf,cfg_cla,GetPaletteAdrByColorIndex(cfg_clc),GetPaletteAdrByColorIndex(cfg_clb));
    }
  }
  GBS_StartTimerProc(&mytmr,(cfg_upd*262)/10, RedrawGUI);
} 

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
    data->ws1=AllocWS(256);
    data->ws2=AllocWS(256);
    data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
//  GBS_StopTimer(&checktmr);
  GBS_StartTimerProc(&checktmr,2620, CheckAllow);
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  return(1);
}
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr); 
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  int t=msg->msg;
  if ((t!=0x95)&&(t!=0x98)&&(t!=0x99)&&(t!=0xa1)&&(t!=0x29))
    return(1);
  return(0);
}

const int minus11=-11;

unsigned short maincsm_name_body[140];

const struct
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

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"NewYear");
}

void Check(void)
{
  char dummy[sizeof(MAIN_CSM)];
  if(IsScreenSaver())
    {
      if (count==0)
      {
        count++;
        LockSched();
        CreateCSM(&MAINCSM.maincsm,dummy,0);
        UnlockSched();
      }
    }
}

void InitConfiguration()
{
  InitConfig();
  cal_d.year=3033;
  cal_d.month=12;
  cal_d.day=31;
  cal_t.hour=23;
  cal_t.min=59;
  cal_t.param=0;
  SUBPROC((void *)AdditionRead);
  SUBPROC((void *)ReadCal);
}

void RedrawMSGUI()
{
   GBS_SendMessage(MMI_CEPID, 0xfa, 0);
}

void RedrawMSGUI_SC()
{
   GBS_SendMessage(MMI_CEPID, 0xfa, 1);
}

#ifdef REDRW
void my_idle_redraw(void *data)
{
  old_idle_redraw(data);
  TTime time,time1;
  TDate date,date1;
  CountTimer(&date1,&time1);
  GetDateTime(&date,&time);
  WSHDR *wst=AllocWS(200);
  if (cal_d.year<date.year)  
  {
    CountTimerST(&date1,&time1);
    wsprintf(wst,pt,tx_late);
    if (cal_ds.year<date.year)
      SUBPROC((void *)ReadCal);
  }
  else
  {
    if (date1.day>0)
      wsprintf(wst,"%u.%02u.%02u\n",cal_d.day,cal_d.month,cal_d.year%100);
    else
      wsprintf(wst,"%02u:%02u\n",time1.hour,time1.min);
  }
  if (strlen(cfg_msap)>0)
  {
    DrawString(wst, cfg_mstx, cfg_msty, cfg_mstx + cfg_mstw,  cfg_msty + cfg_msth, cfg_mstf, cfg_msta,
               GetPaletteAdrByColorIndex(cfg_mstc), GetPaletteAdrByColorIndex(cfg_mstb));
    char buff[256];
    strcpy(buff,add_tx+add_sh);
    if (cfg_mssc>0)
    {
      strcat(buff,star);
      strncat(buff,add_tx,add_sh);
      add_sh+=cfg_mssc;
      if (add_sh>=strlen(add_tx)+1) add_sh=0;
    }
    wsprintf(wst,pt,buff);
    DrawString(wst, cfg_msax, cfg_msay, cfg_msax + cfg_msaw,  cfg_msay + cfg_msah, cfg_msaf, cfg_msaa,
                GetPaletteAdrByColorIndex(cfg_msac), GetPaletteAdrByColorIndex(cfg_msab));
  }
  else DrawString(wst, cfg_mstx, cfg_msty, cfg_mstx + cfg_mstw,  cfg_msty + cfg_msth, cfg_mstf, cfg_msta,
               GetPaletteAdrByColorIndex(cfg_mstc), GetPaletteAdrByColorIndex(cfg_mstb));
  DrawString(ws, cfg_msx, cfg_msy, cfg_msx + cfg_msw,  cfg_msy + cfg_msh, cfg_msf, cfg_msa,
              GetPaletteAdrByColorIndex(cfg_msc), GetPaletteAdrByColorIndex(cfg_msb));
  FreeWS(wst);
  if (cfg_mssc>0) GBS_StartTimerProc(&msuptmr,(262/100)*cfg_msst, RedrawMSGUI_SC);
}

void my_idle_ghook(GUI *gui, int cmd)
{
  static void *methods[16];
  void **m=GetDataOfItemByID(gui,4);
  if (hook_state==1)
  {
    //Цепляем метод onRedraw
    if (m)
    {
      if (m[1])
      {
	memcpy(methods,m[1],sizeof(methods));
	old_idle_redraw=(void (*)(void *))(methods[0]);
	methods[0]=(void *)my_idle_redraw;
	m[1]=methods;
	hook_state=2; //Запрос поиска
      }
    }
  }
  old_idle_ghook(gui, cmd);
}
#endif

void *GetCanvas(CSM_RAM* data)
{
  unsigned char fShow;
  switch (cfg_ms)
  {
  case 1:
    fShow = !IsUnlocked();
    break;
  case 2:
    fShow = IsUnlocked();
    break;
  case 3:
    fShow = 1;
    break;
  default:
    fShow = 0;
  }
  void *canvasdata = 0;
  if (IsGuiOnTop(idlegui_id) && fShow) //Если IdleGui на самом верху
  {
    GUI *igui = GetTopGUI();
    if (igui) //И он существует
    {
#ifdef REDRW
      if (hook_state==0)
      {
        static INPUTDIA_DESC my_idle;
        memcpy(&my_idle,igui->definition,sizeof(INPUTDIA_DESC));
        old_idle_ghook=my_idle.global_hook_proc;
        my_idle.global_hook_proc=my_idle_ghook;
        igui->definition=&my_idle;
        hook_state=1;
      }
#endif
      void *idata = GetDataOfItemByID(igui, 2);
      if (idata)
        canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
      else GBS_StartTimerProc(&msuptmr,/*262*/100, RedrawMSGUI);
    }
    else GBS_StartTimerProc(&msuptmr,/*262*/100, RedrawMSGUI);
  }
  return canvasdata;
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;

  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    ShowMSG(1,(int)"NewYear\nConfig updated!");
    InitConfiguration();
  }

  char buff[256];
  if ((msg->msg==0xfa)&&(msg->submess)&&(cfg_mssc>0))
  {
    void *canvasdata = GetCanvas(data);
    if (canvasdata)
    {
      WSHDR *wst=AllocWS(200);
      DrawCanvas(canvasdata, cfg_msx, cfg_msy, cfg_msx + cfg_msw, cfg_msy + cfg_msh, 1);
      if ((strlen(cfg_msap)>0)&&(strlen(add_tx)>0))
      {
        strcpy(buff,add_tx+add_sh);
        strcat(buff,star);
        strncat(buff,add_tx,add_sh);
        add_sh+=cfg_mssc;
        if (add_sh>=strlen(add_tx)+1) add_sh=0;
        DrawCanvas(canvasdata, cfg_msax, cfg_msay, cfg_msax + cfg_msaw, cfg_msay + cfg_msah, 1);
        wsprintf(wst,pt,buff);
        DrawString(wst, cfg_msax, cfg_msay, cfg_msax + cfg_msaw,  cfg_msay + cfg_msah, cfg_msaf, cfg_msaa,
                         GetPaletteAdrByColorIndex(cfg_msac), GetPaletteAdrByColorIndex(cfg_msab));
      }
      
      unsigned short *p;
      if (wstrlen(ws)>0)
      {
        char l=1;
        p=&(ws->wsbody[ws_sh+1]);
//        p+=ws_sh/2;
        for (int i=1;i<=ws->wsbody[0]-ws_sh;i++) {wst->wsbody[l]=*p;p++;l++;}
        wst->wsbody[l]=star[0];
        wst->wsbody[0]=l;
      }
      wstrncat(wst,ws,ws_sh);
      ws_sh+=cfg_mssc;
      if (ws_sh>=wstrlen(ws)+1) ws_sh=0;
      DrawString(wst, cfg_msx, cfg_msy, cfg_msx + cfg_msw,  cfg_msy + cfg_msh, cfg_msf, cfg_msa,
                       GetPaletteAdrByColorIndex(cfg_msc), GetPaletteAdrByColorIndex(cfg_msb));
      FreeWS(wst);
    }
   if ((cfg_mssc>0)&&(canvasdata)) GBS_StartTimerProc(&msuptmr,(262/100)*cfg_msst, RedrawMSGUI_SC);
   return 0;
  }
 
  csm_result = old_icsm_onMessage(data, msg); //Вызываем старый обработчик событий

  if (cfg_ss) Check();
   
  void *canvasdata = GetCanvas(data);
  if (canvasdata)
  {
#ifdef DEBUG
      unsigned int ul;
      int log=fopen("0:\\log3.txt",A_ReadWrite+A_BIN+A_Truncate+A_Create,P_READ+P_WRITE,&ul);
      char buff[1000];
      if (canvasdata)
      {
        sprintf((char*)&buff,"%u\n%s\n",canvasdata,canvasdata);
        fwrite(log,(char*)&buff,strlen((char*)&buff),&ul);
      }
      else fwrite(log,"NULL",4,&ul);
      fclose(log,&ul);
#endif
    TTime time,time1;
    TDate date,date1;
    CountTimer(&date1,&time1);
    GetDateTime(&date,&time);
    WSHDR *wst=AllocWS(200);
    if (cal_d.year<date.year)  
    {
      CountTimerST(&date1,&time1);
      wsprintf(wst,pt,tx_late);
      if (cal_ds.year<date.year)
      SUBPROC((void *)ReadCal);
    }

    DrawCanvas(canvasdata, cfg_mstx, cfg_msty, cfg_mstx + cfg_mstw, cfg_msty + cfg_msth, 1);
    DrawCanvas(canvasdata, cfg_msx, cfg_msy, cfg_msx + cfg_msw, cfg_msy + cfg_msh, 1);

    if ((strlen(cfg_msap)>0)&&(strlen(add_tx)>0))
    {
      DrawCanvas(canvasdata, cfg_msax, cfg_msay, cfg_msax + cfg_msaw, cfg_msay + cfg_msah, 1);
      strcpy(buff,add_tx+add_sh);
      if (cfg_mssc>0)
      {
        strcat(buff,star);
        strncat(buff,add_tx,add_sh);
        add_sh+=cfg_mssc;
        if (add_sh>=strlen(add_tx)+1) add_sh=0;
      }
      wsprintf(wst,pt,buff);
      DrawString(wst, cfg_msax, cfg_msay, cfg_msax + cfg_msaw,  cfg_msay + cfg_msah, cfg_msaf, cfg_msaa,
                   GetPaletteAdrByColorIndex(cfg_msac), GetPaletteAdrByColorIndex(cfg_msab));
    }

    if (cal_d.year>=date.year)  
    {
      if (date1.day>0)
        wsprintf(wst,"%u.%02u.%02u\n",cal_d.day,cal_d.month,cal_d.year%100);
      else
        wsprintf(wst,"%02u:%02u\n",time1.hour,time1.min);
    }
    DrawString(wst, cfg_mstx, cfg_msty, cfg_mstx + cfg_mstw,  cfg_msty + cfg_msth, cfg_mstf, cfg_msta,
                  GetPaletteAdrByColorIndex(cfg_mstc), GetPaletteAdrByColorIndex(cfg_mstb));

//  wstrcpy(wst,add_tx+add_sh);
    if (cfg_mssc>0)
    {
      unsigned short *p;
      if (wstrlen(ws)>0)
      {
        char l=1;
        p=&(ws->wsbody[ws_sh+1]);
//        p+=ws_sh/2;
        for (int i=1;i<=ws->wsbody[0]-ws_sh;i++) {wst->wsbody[l]=*p;p++;l++;}
        wst->wsbody[l]=0x2a;
        wst->wsbody[0]=l;
      }
      wstrncat(wst,ws,ws_sh);
      ws_sh+=cfg_mssc;
      if (ws_sh>=wstrlen(ws)+1) ws_sh=0;
      DrawString(wst, cfg_msx, cfg_msy, cfg_msx + cfg_msw,  cfg_msy + cfg_msh, cfg_msf, cfg_msa,
                    GetPaletteAdrByColorIndex(cfg_msc), GetPaletteAdrByColorIndex(cfg_msb));
    }
    else DrawString(ws, cfg_msx, cfg_msy, cfg_msx + cfg_msw,  cfg_msy + cfg_msh, cfg_msf, cfg_msa,
                    GetPaletteAdrByColorIndex(cfg_msc), GetPaletteAdrByColorIndex(cfg_msb));
    FreeWS(wst);
    if (cfg_mssc>0) GBS_StartTimerProc(&msuptmr,(262/100)*cfg_msst, RedrawMSGUI_SC);
  }
  return(csm_result);
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&checktmr);
  FreeWS(ws);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

int main(void)
{  
  ws=AllocWS(256);
  InitConfiguration();
  if (cfg_mes) ShowMSG(1,(int)"NewYear was started!");
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsmd.onClose=MyIDLECSM_onClose;
  icsm->constr=&icsmd;
  UnlockSched();
//  Check();
  return 0;
}
