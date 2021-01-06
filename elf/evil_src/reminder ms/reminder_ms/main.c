#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

const int minus11=-11;
int refresh;
////for read file
  int f;
  int fsize;
  int fsize1;
  int zane;
  unsigned int ul;
//////////////
extern const unsigned int date_X2;
extern const unsigned int date_Y2;
extern const unsigned int IDLEICON_X;
int IDLEICON_Y;
int hide;
int one_draw;
char one_txt[128];
extern const unsigned int IDLEICON_Y_C;
int IDLEICON_Y02;
int IDLEICON_Y03;
int IDLEICON_Y04;
int IDLEICON_Y05;
int IDLEICON_Y06;
int IDLEICON_Y07;
int IDLEICON_Y08;
char rms_path[64];
extern const char color[];
int janko;
int i;
int j;
int k;
int janis;
int janis1;
char timez[64];
int z;
int y;
int w;
extern const int APP_MODE;
int realtime1;
int realtime2;
int realtime3;
int realtime4;
int realtime5;
int realtime6;
int realtime7;
int realtime8;
int thetime;
int app_count;
int app_draw;
int date_X;
int date_Y;
int date_Y02;
int date_Y03;
int date_Y04;
int date_Y05;
int date_Y06;
int date_Y07;
int date_Y08;
int sndVolume = 6;
char diena[64];
char laiks[64];
char pirmais[64];
char otrais[64];
char treshais[64];
char ceturtais[64];
char piektais[64];
char sestais[64];
char septiitais[64];
char astotais[64];
extern const char todo[32];
extern const char no_zadach[32];
extern const char rms_file[64];
extern const char sound_wav[64];
extern const char iconpath[64];
char iconpath0[64];
char iconpath1[64];
char iconpath2[64];
char iconpath3[64];
char iconpath4[64];
char iconpath5[64];
char iconpath6[64];
char iconpath7[64];
char iconpath8[64];
char init_img_width[64];
extern const int HIDE_MODE;
//////////////////////////////////////
extern const int fullfont;
extern const char fontpath[64];
char lielims[128];
int font=1;
int align=0;
extern const unsigned int space;
void *canvasdata;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

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

void Play(const char *fname)
{
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
}

extern const unsigned int luki;

void init_pos()
{
  if((HIDE_MODE)||(APP_MODE))
    date_X=IDLEICON_X;
  else
  date_X=IDLEICON_X+GetImgWidth((int)init_img_width)+2;
  IDLEICON_Y02=IDLEICON_Y+GetImgHeight((int)lielims);
  IDLEICON_Y03=IDLEICON_Y02+GetImgHeight((int)lielims)+luki;
  IDLEICON_Y04=IDLEICON_Y03+GetImgHeight((int)lielims)+luki;
  IDLEICON_Y05=IDLEICON_Y04+GetImgHeight((int)lielims)+luki;
  IDLEICON_Y06=IDLEICON_Y05+GetImgHeight((int)lielims)+luki;
  IDLEICON_Y07=IDLEICON_Y06+GetImgHeight((int)lielims)+luki;
  IDLEICON_Y08=IDLEICON_Y07+GetImgHeight((int)lielims)+luki;
  date_Y=IDLEICON_Y_C;
  date_Y02=IDLEICON_Y+GetImgHeight((int)lielims)+luki;
  date_Y03=date_Y02+GetImgHeight((int)lielims)+luki;
  date_Y04=date_Y03+GetImgHeight((int)lielims)+luki;
  date_Y05=date_Y04+GetImgHeight((int)lielims)+luki;
  date_Y06=date_Y05+GetImgHeight((int)lielims)+luki;
  date_Y07=date_Y06+GetImgHeight((int)lielims)+luki;
  date_Y08=date_Y07+GetImgHeight((int)lielims)+luki;
}

void search(void);
TDate date;
TTime time;

void str2int()
{
  janis=0;
  if (laiks[0]=='1') janis=janis+1000;
  if (laiks[0]=='2') janis=janis+2000;
  if (laiks[1]=='1') janis=janis+100;
  if (laiks[1]=='2') janis=janis+200;
  if (laiks[1]=='3') janis=janis+300;
  if (laiks[1]=='4') janis=janis+400;
  if (laiks[1]=='5') janis=janis+500;
  if (laiks[1]=='6') janis=janis+600;
  if (laiks[1]=='7') janis=janis+700;
  if (laiks[1]=='8') janis=janis+800;
  if (laiks[1]=='9') janis=janis+900;
  if (laiks[3]=='1') janis=janis+10;
  if (laiks[3]=='2') janis=janis+20;
  if (laiks[3]=='3') janis=janis+30;
  if (laiks[3]=='4') janis=janis+40;
  if (laiks[3]=='5') janis=janis+50;
  if (laiks[3]=='6') janis=janis+60;
  if (laiks[3]=='7') janis=janis+70;
  if (laiks[3]=='8') janis=janis+80;
  if (laiks[3]=='9') janis=janis+90;
  if (laiks[4]=='1') janis=janis+1;
  if (laiks[4]=='2') janis=janis+2;
  if (laiks[4]=='3') janis=janis+3;
  if (laiks[4]=='4') janis=janis+4;
  if (laiks[4]=='5') janis=janis+5;
  if (laiks[4]=='6') janis=janis+6;
  if (laiks[4]=='7') janis=janis+7;
  if (laiks[4]=='8') janis=janis+8;
  if (laiks[4]=='9') janis=janis+9;
}

void str2int2()
{
  janis1=0;
  if (timez[0]=='1') janis1=janis1+1000;
  if (timez[0]=='2') janis1=janis1+2000;
  if (timez[1]=='1') janis1=janis1+100;
  if (timez[1]=='2') janis1=janis1+200;
  if (timez[1]=='3') janis1=janis1+300;
  if (timez[1]=='4') janis1=janis1+400;
  if (timez[1]=='5') janis1=janis1+500;
  if (timez[1]=='6') janis1=janis1+600;
  if (timez[1]=='7') janis1=janis1+700;
  if (timez[1]=='8') janis1=janis1+800;
  if (timez[1]=='9') janis1=janis1+900;
  if (timez[3]=='1') janis1=janis1+10;
  if (timez[3]=='2') janis1=janis1+20;
  if (timez[3]=='3') janis1=janis1+30;
  if (timez[3]=='4') janis1=janis1+40;
  if (timez[3]=='5') janis1=janis1+50;
  if (timez[3]=='6') janis1=janis1+60;
  if (timez[3]=='7') janis1=janis1+70;
  if (timez[3]=='8') janis1=janis1+80;
  if (timez[3]=='9') janis1=janis1+90;
  if (timez[4]=='1') janis1=janis1+1;
  if (timez[4]=='2') janis1=janis1+2;
  if (timez[4]=='3') janis1=janis1+3;
  if (timez[4]=='4') janis1=janis1+4;
  if (timez[4]=='5') janis1=janis1+5;
  if (timez[4]=='6') janis1=janis1+6;
  if (timez[4]=='7') janis1=janis1+7;
  if (timez[4]=='8') janis1=janis1+8;
  if (timez[4]=='9') janis1=janis1+9;
}

void get_dienu()
{
GetDateTime(&date, &time);
sprintf(diena, "%d.%d.%d", date.day, date.month, date.year);
if((time.hour>=10)&&(time.min>=10))
sprintf(laiks, "%d:%d", time.hour, time.min);
else
{
  if(time.hour>=10)
    sprintf(laiks, "%d:0%d", time.hour, time.min);
  else
  {
    if(time.min>=10)
      sprintf(laiks, "0%d:%d", time.hour, time.min);
    else
      sprintf(laiks, "0%d:0%d", time.hour, time.min);
  }
}
zane=1;
str2int();
thetime=janis;
search();
}

void reminder_file()
{
  if((zane==0)||(thetime==0))
    get_dienu();
  else
    search();
}

GBSTMR mytmr;

void get_dienu2()
{
GetDateTime(&date, &time);
sprintf(diena, "%d.%d.%d", date.day, date.month, date.year);
if((time.hour>=10)&&(time.min>=10))
sprintf(laiks, "%d:%d", time.hour, time.min);
else
{
  if(time.hour>=10)
    sprintf(laiks, "%d:0%d", time.hour, time.min);
  else
  {
    if(time.min>=10)
      sprintf(laiks, "0%d:%d", time.hour, time.min);
    else
      sprintf(laiks, "0%d:0%d", time.hour, time.min);
  }
}
str2int();
thetime=janis;
FSTATS stat;
GetFileStats(rms_path,&stat,&ul);
fsize1=stat.size;
if((fsize1!=fsize)||(thetime==0))
reminder_file();
else
{
if (app_draw==0) sprintf(iconpath0, "%snone.png", iconpath);  
if (app_draw>=1)
{
  if (thetime==realtime1) Play(sound_wav);
  if ((thetime>=realtime1)&&(HIDE_MODE))
  {
    if(hide==8)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=7;
     if(app_draw==1) app_draw=0;
    }
  }
  if (thetime>=realtime1)
    sprintf(iconpath1, "%scomplete.png", iconpath);
  else
    sprintf(iconpath1, "%sincomplete.png", iconpath);
}
if (app_draw>=2)
{
  if (thetime==realtime2) Play(sound_wav);
  if ((thetime>=realtime2)&&(HIDE_MODE))
  {
    if(hide==7)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=6;
     if(app_draw==2) app_draw=0;
    }
  }
  if (thetime>=realtime2)
    sprintf(iconpath2, "%scomplete.png", iconpath);
  else
    sprintf(iconpath2, "%sincomplete.png", iconpath);
}
if (app_draw>=3)
{
  if (thetime==realtime3) Play(sound_wav);
  if ((thetime>=realtime3)&&(HIDE_MODE))
  {
    if(hide==6)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=5;
     if(app_draw==3) app_draw=0;
    }
  }
  if (thetime>=realtime3)
    sprintf(iconpath3, "%scomplete.png", iconpath);
  else
    sprintf(iconpath3, "%sincomplete.png", iconpath);
}
if (app_draw>=4)
{
  if (thetime==realtime4) Play(sound_wav);
  if ((thetime>=realtime4)&&(HIDE_MODE))
  {
    if(hide==5)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=4;
     if(app_draw==4) app_draw=0;
    }
  }
  if (thetime>=realtime4)
    sprintf(iconpath4, "%scomplete.png", iconpath);
  else
    sprintf(iconpath4, "%sincomplete.png", iconpath);
}
if (app_draw>=5)
{
  if (thetime==realtime5) Play(sound_wav);
  if ((thetime>=realtime5)&&(HIDE_MODE))
  {
    if(hide==4)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=3;
     if(app_draw==5) app_draw=0;
    }
  }
  if (thetime>=realtime5)
    sprintf(iconpath5, "%scomplete.png", iconpath);
  else
    sprintf(iconpath5, "%sincomplete.png", iconpath);
}
if (app_draw>=6)
{
  if (thetime==realtime6) Play(sound_wav);
  if ((thetime>=realtime6)&&(HIDE_MODE))
  {
    if(hide==3)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=2;
     if(app_draw==6) app_draw=0;
    }
  }
  if (thetime>=realtime6)
    sprintf(iconpath6, "%scomplete.png", iconpath);
  else
    sprintf(iconpath6, "%sincomplete.png", iconpath);
}
if (app_draw>=7)
{
  if (thetime==realtime7) Play(sound_wav);
  if ((thetime>=realtime1)&&(HIDE_MODE))
  {
    if(hide==2)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     hide=1;
     if(app_draw==7) app_draw=0;
    }
  }
  if (thetime>=realtime7)
    sprintf(iconpath7, "%scomplete.png", iconpath);
  else
    sprintf(iconpath7, "%sincomplete.png", iconpath);
}
if (app_draw>=8)
{
  if (thetime==realtime8) Play(sound_wav);
  if ((thetime>=realtime1)&&(HIDE_MODE))
  {
    if(hide==1)
    {
     IDLEICON_Y=IDLEICON_Y-GetImgHeight((int)lielims);
     init_pos();
     app_draw=0;
    }
  }
  if (thetime>=realtime8)
    sprintf(iconpath8, "%scomplete.png", iconpath);
  else
    sprintf(iconpath8, "%sincomplete.png", iconpath);
}
refresh=1;
GBS_StartTimerProc(&mytmr, 216*60, get_dienu2);
}
}


void search()
{
  hide=8;
  FSTATS stat;
  GetFileStats(rms_path,&stat,&ul);
  f=fopen(rms_path,A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
  char p2[]="day";
  char *s,*s1,*s2;
  int len, m;
  if((s1=strstr(p,diena))>0)
  {
    s1+=strlen(diena);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1;
      s=malloc(len+1);
      strncpy(s,s1,len);
      s[len]='\0';
      i=1;
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime1=janis1;
      j=0;
      m=1;
      app_count=0;
      k=0;
      while(k<=8)
      {
        while((s[m]!=';')&&(m<=len))
        {
          m++;
        }
        if(m<len)
        {
        app_count++;
        }
        m=m+5;
        k++;
      }
      app_draw=app_count;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        pirmais[j]=s[i];
        i++;
        j++;
      }
      pirmais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime2=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        otrais[j]=s[i];
        i++;
        j++;
      }
      otrais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime3=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        treshais[j]=s[i];
        i++;
        j++;
      }
      treshais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime4=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        ceturtais[j]=s[i];
        i++;
        j++;
      }
      ceturtais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime5=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        piektais[j]=s[i];
        i++;
        j++;
      }
      piektais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime6=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        sestais[j]=s[i];
        i++;
        j++;
      }
      sestais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime7=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        septiitais[j]=s[i];
        i++;
        j++;
      }
      septiitais[j]='\0';
      }
      app_count--;
      i++;
      if(app_count>0)
      {
      z=i;
      y=0;
      w=5;
      while(w>0)
      {
        timez[y]=s[z];
        z++;
        y++;
        w--;
      }
      timez[y]='\0';
      str2int2();
      realtime8=janis1;
      }
      j=0;
      if(app_count>0)
      {
      while(s[i]!=';')
      {
        astotais[j]=s[i];
        i++;
        j++;
      }
      astotais[j]='\0';
      }
      mfree(s);
    }
  }
  mfree(p);
  janko=1;
  if ((time.hour==0)&&(time.min==0)) 
    GBS_StartTimerProc(&mytmr, 216*61, get_dienu2);
  else
  get_dienu2();
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"ReminderMS config updated!");
      FontPathFree();
      InitConfig();
      hide=8;
      IDLEICON_Y=IDLEICON_Y_C;
      sprintf(rms_path, "%sfile.mrs", rms_file);
      FontPathInit(font,(char *)fontpath, fullfont, 1);
      sprintf(lielims, "%s2135.png", fontpath);
      init_pos();
      GBS_StopTimer(&mytmr);
      reminder_file();
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //???? IdleGui ?? ????? ?????
    {
      if(refresh==1)
      {
      GUI *igui=GetTopGUI();
      if (igui) //? ?? ??????????
      {
        if(strlen(fontpath)>5)
        {
        if(janko==1)
        {
        canvasdata=BuildCanvas();
        ClearScreen();
        one_draw=1;
        if(!APP_MODE) PrintField(IDLEICON_X,date_Y-3-GetImgHeight((int)lielims), (char *)todo, align, font, space);
        if (app_draw==0)
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, no_zadach);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y, (char *)no_zadach, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)iconpath0)-1,IDLEICON_Y+GetImgHeight((int)iconpath0)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y,(int)iconpath0);
          }
        }
        if ((app_draw>=1)&&(hide>=8))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, pirmais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y, pirmais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)iconpath1)-1,IDLEICON_Y+GetImgHeight((int)iconpath1)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y,(int)iconpath1);
          }
        }
        if ((app_draw>=2)&&(hide>=7))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, otrais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y02, otrais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y02,IDLEICON_X+GetImgWidth((int)iconpath2)-1,IDLEICON_Y02+GetImgHeight((int)iconpath2)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y02,(int)iconpath2);
          }
        }
        if ((app_draw>=3)&&(hide>=6))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, treshais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y03, treshais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y03,IDLEICON_X+GetImgWidth((int)iconpath3)-1,IDLEICON_Y03+GetImgHeight((int)iconpath3)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y03,(int)iconpath3);
          }
        }
        if ((app_draw>=4)&&(hide>=5))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, ceturtais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y04, ceturtais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y04,IDLEICON_X+GetImgWidth((int)iconpath4)-1,IDLEICON_Y04+GetImgHeight((int)iconpath4)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y04,(int)iconpath4);
          }
        }
        if ((app_draw>=5)&&(hide>=4))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, piektais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y05, piektais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y05,IDLEICON_X+GetImgWidth((int)iconpath5)-1,IDLEICON_Y05+GetImgHeight((int)iconpath5)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y05,(int)iconpath5);
          }
        }
        if ((app_draw>=6)&&(hide>=3))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, sestais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y06, sestais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y06,IDLEICON_X+GetImgWidth((int)iconpath6)-1,IDLEICON_Y06+GetImgHeight((int)iconpath6)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y06,(int)iconpath6);
          }
        }
        if ((app_draw>=7)&&(hide>=2))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, septiitais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y07, septiitais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y07,IDLEICON_X+GetImgWidth((int)iconpath7)-1,IDLEICON_Y07+GetImgHeight((int)iconpath7)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y07,(int)iconpath7);
          }
        }
        if ((app_draw>=8)&&(hide>=1))
        {
          if(APP_MODE)
          {
            if(one_draw==1)
            {
            sprintf(one_txt, "%s%s", todo, astotais);
            PrintField(date_X,date_Y, one_txt, align, font, space);
            one_draw=0;
            }
          }
          else
          PrintField(date_X,date_Y08, astotais, align, font, space);
          if((!HIDE_MODE)&&(!APP_MODE))
          {
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y08,IDLEICON_X+GetImgWidth((int)iconpath8)-1,IDLEICON_Y08+GetImgHeight((int)iconpath8)-1,1);
          DrawImg(IDLEICON_X,IDLEICON_Y08,(int)iconpath8);
          }
        }
        refresh=0;
      }
      }
      }
      }
    }
    else
    refresh=1;
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  FontPathFree();
  GBS_StopTimer(&mytmr);
  extern void *ELF_BEGIN;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ReminderMS v0.6 - (c)Evilfox");
}

int main()
{
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int ENA_HELLO_MSG;
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"ReminderMS v0.6 (c)Evilfox");
  FontPathInit(font,(char *)fontpath, fullfont ,1);
  sprintf(lielims, "%s2135.png", fontpath);
  sprintf(init_img_width, "%scomplete.png", iconpath);
  hide=8;
  IDLEICON_Y=IDLEICON_Y_C;
  init_pos();
  app_draw=0;
  sprintf(rms_path, "%sfile.mrs", rms_file);
  reminder_file();
  return 0;
}
