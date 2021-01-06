#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"
#include "..\SmartAlerts.h"


#define TMR_SECOND (1300/6)
extern const char sound[];
extern const char mstyle[];
extern const char vname[];
extern const char name1[];
extern const char callnum[];
extern const char smsnum[];
extern const char content[];
extern const char mname[];
extern const int smsstyle;
extern const char recname[];



unsigned int files[8];
unsigned int smss[8];
unsigned int calls[8];
unsigned int amenus[11];
unsigned int miss[6];
unsigned int bmenus[4];

unsigned int hour[5];
unsigned int min[5];
unsigned int status[5];
unsigned int weekdays[5][7];
unsigned int day[7][24];
unsigned int weeks[8];
unsigned int other[8];
unsigned int name2[8];
int show_icon=0;
int status_icon=0;
int X;
int Y;
int imgw;
int imgh;

TDate date; 
TTime time; 
TDate week;
GBSTMR mytmr;
GBSTMR tmr_vibra;
GBSTMR *xtmr=NULL;

int count;
int fb,fa,missfix=0;
volatile int _count;

void getimgwh()
{
  imgw=GetImgWidth((int)icon);
  imgh=GetImgHeight((int)icon);
}

void update_status()
{
  if (status[0] || status[1] || status[2] || status[3] || status[4])
  {
    status_icon=1;
  }
   else status_icon=0;
}

void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(512);
    fread(handle,data,512,&err);

      
show_icon=data[1];
X=data[2];
Y=data[3]*256+data[4];
//5
for(int i=0;i<5;i++)
{
  status[i]=data[i+5];
  hour[i]=data[i+10];
  min[i]=data[i+15];
  files[i]=data[i+20];
  calls[i]=data[i+25];
  smss[i]=data[i+30];
}

//20
for(int i=0;i<35;i++)
{
weekdays[i/7][i%7]=data[i+20];
}
//55
for(int i=0;i<168;i++)
{
day[i/24][i%24]=data[i+55];
}
//223
for(int i=0;i<8;i++)
{
 name2[i]=data[i+223];
 weeks[i]=data[i+231];
 amenus[i]=data[i+239];
 files[i]=data[i+247];
 calls[i]=data[i+255];
 smss[i]=data[i+263];
 other[i]=data[i+271];
}

amenus[8]=data[279];
amenus[9]=data[280];
amenus[10]=data[281];


bmenus[0]=data[282];
bmenus[1]=data[283];
bmenus[2]=data[284];
bmenus[3]=data[285];

miss[0]=data[286];
miss[1]=data[287];
miss[2]=data[288];
miss[3]=data[289];
miss[4]=data[290];
miss[5]=data[291];

//end=data[511];

    mfree(data);
    fclose(handle,&err);
  }
  getimgwh();
  update_status();
}

void start_ring()
{
  WSHDR *ws;
  ws=AllocWS(64);
  str_2ws(ws,ring,strlen(ring)+1);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void Play(const char *fpath, const char *fname)
{
  WSHDR* sndPath=AllocWS(64);
  WSHDR* sndFName=AllocWS(64);

  wsprintf(sndPath, fpath);
  wsprintf(sndFName, fname);
  
    if(fpath==0)
    {
    FSTATS fstats;
    unsigned int err; 
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      char s[64];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,64);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,64);
    }
    }

    PLAYFILE_OPT _sfo1;
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=other[4];
#ifdef NEWSGOLD
    _sfo1.unk6=1;
    _sfo1.unk7=1;
    _sfo1.unk9=2;
    PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
    _sfo1.unk4=0x80000000;
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif 
    
  FreeWS(sndPath);
  FreeWS(sndFName);
}


void start_(void)
{
  void stop_(void);
  if(!name2[4]||!bmenus[0]||(*RamCap()>bmenus[1]))
  {
  	if (other[1])
		SetIllumination(0, 1, other[7]+1, 0);
	if (other[2])
		SetIllumination(1, 1, other[7]+1, 0);   
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, other[7]+1, 0);
#else
	if (other[3])
		SetIllumination(4, 1, other[7]+1, 0);
#endif
  
  if (other[0]) SetVibration(other[6]);
  }
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_);
}

void stop_(void)
{
  	if (other[1])
		SetIllumination(0, 1, 0, 0);
	if (other[2])
		SetIllumination(1, 1, 0, 0);
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, 0, 0);
#else
	if (other[3])
		SetIllumination(4, 1, 0, 0);
#endif
  if (other[0]) SetVibration(0);
  if (--_count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_);
  }
}

void alarm(int n)
{
  if (status[n])
  {
    TDate date;
    GetDateTime(&date, 0);
    char wd = GetWeek(&date);
    if (weekdays[n][wd])
      {
        GetDateTime(&date,&time);
        if (time.hour==hour[n])
          {
            if (time.min==min[n])
              {
                start_ring();
              }
          }
      }
  }
}

char* Opendata(char *recname)
{
  char *buf;
  int f;
  unsigned int fsize;  
  unsigned int err;
  f=fopen(recname,A_ReadOnly+A_BIN,P_READ,&err);
  fsize=lseek(f,0,S_END,&err,&err);
  if (fsize<=0)
  {
    fclose(f,&err);
  }
  lseek(f,0,S_SET,&err,&err);
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  buf[fsize]=0;
  fclose(f,&err);
  return (buf);
}

void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode,int x)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=x; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
}

void sendsms(void)
{
  WSHDR* smstemp=NULL;
  smstemp=AllocWS(1024);
  if(smsstyle==0)
  {
       utf8_2ws(smstemp,content,210);
       if(strlen(smsnum)>0)
       SendSMS(smstemp,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
  }
  else
  {
     char *s;
     s=Opendata((char *)recname);
     if(strstr(recname,"txt"))
     {
      utf8_2ws(smstemp,s,210);
      if(strlen(smsnum)>0)
      SendSMS(smstemp,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
      else
      ShowMSG(1,(int)"没有短信号码!");
     }  
     else if(strstr(recname,"tmo"))
     {
      copy_unicode_2ws(smstemp,(unsigned short *)(s+2),280);
      if(strlen(smsnum)>0)
      SendSMS(smstemp,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
      else
      ShowMSG(1,(int)"没有短信号码!");
      }
  }
  FreeWS(smstemp);
}

int monthcount(int num)
{
GetDateTime(&date,&time); 
int daycount;  
switch(num)
{
  case 1:
    daycount=31;
    break;
  case 2:
    if((date.year/4==0&&date.year/100!=0)||(date.year/100==0&&date.year/400==0))
    daycount=29;
    else
    daycount=28;
    break;
  case 3:
    daycount=31;
    break;
  case 4:
    daycount=30;
    break;
  case 5:
    daycount=31;
    break;
  case 6:
    daycount=30;
    break;
  case 7:
    daycount=31;
    break;
  case 8:
    daycount=31;
    break;
  case 9:
    daycount=30;
    break;
  case 10:
    daycount=31;
    break;
  case 11:
    daycount=30;
    break;
  case 12:
    daycount=31;
    break;
}

return daycount;
}

void Check()
{
GetDateTime(&date,&time);
 if (!IsCalling())
 {

     if(name2[0])
     {
        for (int i=0;i<5;i++)
        {
          alarm(i);
        }
      }

        if(name2[7])
        {
          int sum=0;
          if(date.month > smss[4])
          {
            for(int i=0;(date.month-smss[4]-i)>0;i++)       
            sum=sum+monthcount(smss[4]+i);
          }
          
          if(!smss[0]||(smss[2]/(sum+date.day-smss[5]+1)>=1))
          {
          if((time.hour==smss[6]||
              (
               smss[1]&&
                 (
                  !smss[3]||
                    (
                     (time.hour-smss[6])%smss[3]==0
                    )
                 )
              ))
             &&time.min==smss[7])
          {
            sendsms();
          }
          }
        } 
  
  
   if(name2[1])
   {
     if ((time.hour>=amenus[3])&&(time.hour<=amenus[4]))
        {              
         if(time.min==amenus[5])
	 { 
               if(amenus[1]&&((GetProfile()+1)!=amenus[9]))
               {
                   char w[5];
                   sprintf(w, "%d.%s",time.hour,mstyle);
                   Play(sound,w);
               }
               else if(amenus[0]&&((GetProfile()+1)!=amenus[9]))
               {
                   Play(0,vname);
               }
               else
               {
		   PlaySound(1,0,0,amenus[6],0);
               }
                   _count=other[5];
                   start_();
	  }
          else if(time.min==amenus[7])
	  { 
                  PlaySound(1,0,0,amenus[8],0);
                  _count=other[5];
                  start_();
          }
        }
       }
  
        if(name2[5])
        {
          int sum=0;
          if(date.month > smss[4])
          {
            for(int i=0;(date.month-smss[4]-i)>0;i++)       
            sum=sum+monthcount(smss[4]+i);
          }
          if(!files[0]||(files[2]/(sum+date.day-files[5]+1)>=1))
          {
          if((time.hour==files[6]||
              (
               files[1]&&
                 (
                  !files[3]||
                    (
                     (time.hour-files[6])%files[3]==0
                    )
                 )
               )
              )&&
              time.min==files[7])
           {
           if(strcmp(name1,"r")==0)
           RebootPhone();
           else
           runFile((char*)name1);
           }
          }
        }
        
        if(name2[6])
        {
          int sum=0;
          if(date.month > smss[4])
          {
            for(int i=0;(date.month-smss[4]-i)>0;i++)       
            sum=sum+monthcount(smss[4]+i);
          }
          if(!calls[0]||(calls[2]/(sum+date.day-calls[5]+1)>=1))
          {
          if((time.hour==calls[6]||
              (
               calls[1]&&
                 (
                  !calls[3]||
                    (
                     (time.hour-calls[6])%calls[3]==0
                    )
                 )
              )
              )&&
              time.min==calls[7])
           {
            if(strlen(callnum)>0)
            MakeVoiceCall(callnum,0x10,0x2FFF);
           }
          }
        }
     
        if (name2[4])
        {
           if (*RamCap()==100&&fb!=bmenus[3])
           {
           PlaySound(1,0,0,bmenus[2],0);
           fb++;
           }
           else if(*RamCap()!=100)
                fb=0;
           
           if(bmenus[0]&&(*RamCap()==bmenus[1])&&fa!=1)
           { 
           char bnum[50];  
           sprintf(bnum,"电量已经只有%d％了",bmenus[1]);
           ShowMSG(1,(int)bnum);
           fa=1;
           }
           else if(*RamCap()>bmenus[1])
                fa=0;
        }
        
        if(name2[3])
        {
          if ((time.hour>=miss[2])&&(time.hour<=miss[3]))
          {
          if(time.min%miss[5]==0)
          {
          #ifdef NEWSGOLD          
	    if (GetMissedEventCount(0))
          #else
            if (GetMissedCallsCount()||HasNewSMS()) 
          #endif
          {
            if(!missfix)
            {
              missfix=1;
            }  
            else
            {  
            if(!miss[0])
            {
             if(miss[1])
             Play(0,mname); 
             else
             PlaySound(1,0,0,miss[4],0);
            }
             _count=other[5];
             start_();
            }
          }
          else
          {
            missfix=0;
          }
          }
          }
        }
 }
 if(name2[2])
 {
  if(time.min==weeks[7])
  {
   int a1,a2;
   a1=GetWeek(&date);
   a2=time.hour;
   
   for(;a1>0;a1--)
   {
   if(weeks[a1])
     break;
   } 
   
   if(day[a1][a2]<9&&day[a1][a2]!=0)
     SetProfile(day[a1][a2]-1);
  }
 }

GBS_StartTimerProc(&mytmr,13000,Check);
}

void start()
{ 
GBS_StartTimerProc(&mytmr,13000,Check); 
} 

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

const int minus11=-11;

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&tmr_vibra);
  //GBS_DelTimer(xtmr);
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
    }

    if (strcmp_nocase("smartalerts",(char *)msg->data0)==0)
    {
      load_settings();
    }
    
   // if (strcmp_nocase("close",(char *)msg->data0)==0)
   // {
     // SUBPROC((void *)Killer);
     // return(1);
    //}
    
  }

  if (msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc=(IPC_REQ*)((msg)->data0);
    if (ipc)
    {
      if (strcmp_nocase("smartalerts",(char *)ipc->name_to)==0)
      {
         int time2 =msg->submess;
        GBS_StartTimerProc(&xtmr,13000*time2,start_ring);
      }
    }
  }
  
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    if (IsGuiOnTop(idlegui_id))
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
          if((name2[0])&&(IsUnlocked())&&(show_icon)&&(status_icon))
          {
            DrawCanvas(canvasdata, X, Y, X + imgh, Y + imgh, 1);
            DrawImg(X, Y, (int)icon);
          }
        }
      }
    }
  }
  
  return(1);
}  

static void maincsm_oncreate(CSM_RAM *data)
{
  start();
}

static void maincsm_onclose(CSM_RAM *csm)
{
  //GBS_DelTimer(&mytmr);
  //GBS_DelTimer(&tmr_vibra);
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM_d =
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
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"smartalerts");
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig(); 
  load_settings();
  UpdateCSMname();
  LockSched(); 
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM_d.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}
