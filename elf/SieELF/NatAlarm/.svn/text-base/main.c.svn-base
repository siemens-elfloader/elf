#include "..\inc\swilib.h"
#include "local_ipc.h"
#include "..\inc\xtask_ipc.h"
#include "main.h"
#include "language.h"
//0A34: 0xA05C7120   ; 28D: int RefreshAlarmClock()
#pragma swi_number=0x291
__swi __arm int RefreshAlarmClock();

GBSTMR mytmr;

const char ipc_my_name[]=IPC_TEXTINFO_NAME;
const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#define TMR_SECOND 216

void TimerProc(void)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}

const char _s[]="%s";

#pragma inline=forced
int toupper(int c)
{
  if((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmpNoCase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}


int get_file_size(char* fname)
{
  unsigned int err;
  FSTATS fs;
  if ((GetFileStats(fname,&fs,&err))==-1) return 0;
  return (fs.size);
}


/*------------------------------------------------------------------------*/
/*-------------------- Весь процесс отрисовки списка ---------------------*/
/*------------------------------------------------------------------------*/

int curpos=0;//позичия курсора
int curitem=0;//позиция итема под курсором
int edittime=0;//Если редактим время 
int timepos=0;//позиция 0-4
int editsnooze=0;
int snozeepos=0;

int days[7];
char *day[7]={"一","二","三","四","五","六","日"};
TTime alarm_time;
int snooze_time;
int alarm_active;
int auto_snooze;

char clrBlack[]={0x00,0x00,0x00,0x64};
char clrWhite[]={0xFF,0xFF,0xFF,0x64};
char transparent[]={0x00,0x00,0x00,0x00};
const int font=FONT_SMALL;
const char _t[]="%t";
const char _d[]="%d";


int scr_w,scr_h;


void PrintAbout()
{
  WSHDR *ws=AllocWS(128);
  wsprintf(ws,"NatAlarm v0.1fix\n(c)kluchnik\n%s at %s",__DATE__,__TIME__);
  DrawRoundedFrame(0,YDISP+1,ScreenW()-1,ScreenH()-1,0,0,0,clrWhite,clrBlack);
  DrawString(ws,0,(ScreenH()/2)-GetFontYSIZE(font),ScreenW()-1,ScreenH()-1,font,TEXT_ALIGNMIDDLE,clrWhite,0);
}


static void DrawSoftKeys(WSHDR *ws,char *right,char *left)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  
  LockSched();
  wsprintf(ws,_t,right);
  DrawString(ws,2,scr_h-1-GetFontYSIZE(font),scr_w,scr_h,font,0,clrWhite,0);

  CutWSTR(ws,32);
  wsprintf(ws,_t,left);
  DrawString(ws,(scr_w >> 1),scr_h-1-GetFontYSIZE(font),scr_w-2,scr_h-2,font,TEXT_ALIGNRIGHT,clrWhite,0);
  UnlockSched();
}

char *temp_chars; //Собственно файл
char **temp_lines; //Массив указателей на строки

void FreePD(void)
{
  if (temp_lines) mfree(temp_lines);
  if (temp_chars) mfree(temp_chars);
  temp_lines=NULL;
  temp_chars=NULL;
}

int LoadPD()
{
  FSTATS stat;
  char fn[256];
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
  FreePD();
  strcpy(fn,"1:\\system\\alarmclock.pd");
//  strcpy(fn,"0:\\alarmclock.pd");
  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;
  p=temp_chars=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<32)
    {
      if (pp&&(pp!=p))
      {
	temp_lines=realloc(temp_lines,(i+1)*sizeof(char *));
	temp_lines[i++]=pp;
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
}


void do_logwrite(char *text)
{
  int hFile;
  unsigned int io_error = 0;
  hFile = fopen("4:\\NatAlarm.txt",A_ReadWrite + A_Create + A_Append,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
  {
    fwrite(hFile, text, strlen(text), &io_error);
    fwrite(hFile, "\r\n", 2, &io_error);
    fclose(hFile, &io_error);
  }
  else
    ShowMSG(1,(int)"错误!");
//  mfree(text);
}


void GetTime(TTime *t,int time)
{
  time=time/60;
  int hour=time/60;
  int min=time%60;  
  t->hour=hour;
  t->min=min;
}

int SetAlarmTime(TTime *t)
{
  int i=0;
  i=t->hour*60*60;//hour;
  i+=t->min*60;//min  
  return i;
}

/*
unsigned int SetDays(char *s)
{
  unsigned int i=0;
  for(int k=6;k>=0;k--)
    i+=days[k]*10;
  
  return i;
}*/


void ParseSnoozeTime(char *s)
{
//  do_logwrite(s);
  int time=strtoul(s,0,10);
  snooze_time=time/60;
}

void ParseAlarmTime(char *s)
{ 
//    do_logwrite(s);
  int time=strtoul(s,0,10);//28500
  GetTime(&alarm_time,time);
}

void ParseDayInUse(char *s)
{
//  do_logwrite(s);
  //char *p=strrchr(s,'=')+1;
  char *p=malloc(1);
//  char *ss=malloc(32);
  *(p)=0;
  for(int i=0;i<7;i++)
  {
    *p=*(s+i);
    *(p+1)=0;
    days[i]=strtoul(p,0,10);
    //sprintf(ss,"p=%s days[%d]=%d",p,i,days[i]);
  //  do_logwrite(ss);
//    do_logwrite(&days[i]);
  }
  mfree(p);
  //mfree(ss);
}

void ParseAlarmActive(char *s)
{
//  do_logwrite(s);
  alarm_active=strtoul(s,0,10);
}

void ParseAutoSnooze(char *s)
{
//  do_logwrite(s);
  auto_snooze=strtoul(s,0,10);
}


void Parser()
{
  int i=LoadPD();
  if(!i) { ShowMSG(1,(int)"没有载入文件!"); return; }
  int j=0;
  char *s;
//  *(s)=0;
  while(j<i)
  {
    s=strrchr(temp_lines[j],'=')+1;
//    ShowMSG(1,(int)s);
    if(strstr(temp_lines[j],"snooze_time"))  ParseSnoozeTime(s);
    if(strstr(temp_lines[j],"days_in_use"))  ParseDayInUse(s);
    if(strstr(temp_lines[j],"alarm_time"))   ParseAlarmTime(s);    
    if(strstr(temp_lines[j],"alarm_active")) ParseAlarmActive(s);    
    if(strstr(temp_lines[j],"auto_snooze"))  ParseAutoSnooze(s);    
    j++;
  }
}


void SavePD()
{
  volatile int hFile;
  unsigned int io_error = 0;
  char fullname[128];
  snprintf(fullname,127,"1:\\system\\alarmclock.pd");
//  snprintf(fullname,127,"0:\\alarmclock.pd");
  unlink(fullname,&io_error);
  hFile = fopen(fullname,A_ReadWrite + A_Create +  A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  char *s=malloc(128);
  char *p=malloc(10);
  *(p)=0;
  *(s)=0;
  
//  for(int i=0;i<7;i++) if(days[i]>1) days[i]=0;
  
  if(hFile!=-1)
  {
    sprintf(s,"000024:T:snooze_time=%d\r\n",snooze_time*60);
    fwrite(hFile, s, strlen(s), &io_error);
    
//    do_logwrite(p);
    sprintf(p,"%d%d%d%d%d%d%d",days[0],days[1],days[2],days[3],days[4],days[5],days[6]);
  //  do_logwrite(p);
    snprintf(s,31,"000028:T:days_in_use=%s\r\n",p);   
    //do_logwrite(s);
    fwrite(hFile, s, strlen(s), &io_error);
    
    sprintf(p,"%d",SetAlarmTime(&alarm_time));
    sprintf(s,"0000%d:T:alarm_time=%d\r\n",20+strlen(p),SetAlarmTime(&alarm_time));    
    fwrite(hFile, s, strlen(s), &io_error);    
    
    sprintf(s,"000023:T:alarm_active=%d\r\n",alarm_active);
    fwrite(hFile, s, strlen(s), &io_error);
    
    sprintf(s,"000022:T:auto_snooze=%d\r\n",auto_snooze);
    fwrite(hFile, s, strlen(s), &io_error);
    
    fclose(hFile, &io_error);
//    ShowMSG(1,(int)"Saved!");
  }
  else ShowMSG(1,(int)"Can't save file!!!");
  mfree(s);
  mfree(p);
}

/*
000024:T:snooze_time=540
000028:T:days_in_use=1111111
000025:T:alarm_time=28500
000023:T:alarm_active=0
000022:T:auto_snooze=0
*/
/*
static DrawCheckBox(int x,int y,int flag)
{
  RECT rc;
  StoreXYXYtoRECT(&rc,x,y,x+15,y+15);
  DrawRectangle(rc.x,rc.y,rc.x2,rc.y2,0,clrBlack,transparent);
  if(flag)
  {
    DrawLine(rc.x+2,rc.y+2,rc.x2-2,rc.y2-2,0,clrWhite);
    DrawLine(rc.x2-2,rc.y+2,rc.x+2,rc.y2-2,0,clrWhite);
  }
}
*/


#ifdef ELKA
  int x2_cb=15;
#else
  int x2_cb=10;
#endif
  
static DrawCheckBox(int x,int y,int flag)
{
  RECT rc;

  StoreXYXYtoRECT(&rc,x,y,x+x2_cb,y+x2_cb);
  DrawRectangle(rc.x,rc.y,rc.x2,rc.y2,0,clrBlack,transparent);
  if(flag)
  {
    DrawLine(rc.x+2,rc.y+5,rc.x2-7,rc.y2-2,0,clrWhite);
    DrawLine(rc.x2-7,rc.y2-2,rc.x+x2_cb,rc.y-2,0,clrWhite);
  }
}

static DrawCursor(int x,int x2,int y)
{
  DrawLine(x,y,x2,y,0,clrWhite);  
}

void DrawDays(WSHDR *ws,int y)
{
  int i;
  int x=(scr_w-((x2_cb+5)*7))/2;  
  for(i=0,x;i<7;i++,x+=x2_cb+5)
  {
    wsprintf(ws,_t,day[i]);
    DrawString(ws,x-1,y-GetFontYSIZE(FONT_SMALL)-2,scr_w,y,FONT_SMALL,0,clrWhite,transparent);
    DrawCheckBox(x,y,days[i]==1?1:0);
  }
  x=(scr_w-((x2_cb+5)*7))/2;  
  if(curpos==4)
    DrawCursor(x+(curitem*(x2_cb+5)),x+(curitem*(x2_cb+5))+x2_cb,y+x2_cb+1);

 // wsprintf(ws,"%d %d %d %d %d %d %d",days[0],days[1],days[2],days[3],days[4],days[5],days[6]);
 // DrawString(ws,2,300,ScreenW()-1,320,font,0,clrBlack,transparent);
}

void DrawTimeAlarm(WSHDR *ws,int y)
{
  if(alarm_time.hour>24) alarm_time.hour=23;
  if(alarm_time.min>60)  alarm_time.min=0;
  wsprintf(ws,"%02d:%02d",alarm_time.hour,alarm_time.min);
  DrawString(ws,1,YDISP+y,scr_w,YDISP+y+GetFontYSIZE(FONT_LARGE),FONT_LARGE,TEXT_ALIGNMIDDLE,clrBlack,transparent);    
  if(curpos==0 && !edittime)
  {
    if(curitem==0)
      DrawCursor((scr_w/2)-(Get_WS_width(ws,FONT_LARGE)/2),scr_w/2-2, YDISP+y+GetFontYSIZE(FONT_LARGE));
    else
      DrawCursor(scr_w/2+4,(scr_w/2)+(Get_WS_width(ws,FONT_LARGE)/2), YDISP+y+GetFontYSIZE(FONT_LARGE));
  }
  else if(edittime)
  {
      int x=(scr_w/2)-(Get_WS_width(ws,FONT_LARGE)/2);
      int step=Get_WS_width(ws,FONT_LARGE)/4;
      DrawCursor(x+(step*timepos),x+(step*timepos)+step,YDISP+y+GetFontYSIZE(FONT_LARGE));
  }
}

void DrawTime(WSHDR *ws)
{
  TTime t;
  GetDateTime(NULL,&t);
  wsprintf(ws,"%02d:%02d:%02d",t.hour,t.min,t.sec);
  DrawString(ws,1,YDISP+3,scr_w-5,YDISP+2+GetFontYSIZE(FONT_SMALL),FONT_SMALL,TEXT_ALIGNRIGHT,clrBlack,transparent);    
}


void DrawSnoozeTime(WSHDR *ws,int y)
{
  wsprintf(ws,"%t %02d %t","自动再次提醒经过",snooze_time,"分钟");
  int yy=y+(GetFontYSIZE(FONT_SMALL)*2);
  DrawString(ws,1,yy,scr_w,y+(GetFontYSIZE(FONT_SMALL)*3),FONT_SMALL,TEXT_ALIGNMIDDLE,clrBlack,transparent);    
  if(curpos==3)
  {
    int symb=Get_WS_width(ws,FONT_LARGE)/wstrlen(ws);
    int x=(scr_w/2)+symb;

    if(!curitem)
      DrawCursor(x+(symb*curitem)+3,x+(symb*(curitem+1))-1,yy+GetFontYSIZE(FONT_SMALL)+1);
    else
      DrawCursor(x+(symb*curitem),x+(symb*(curitem+1))-4,yy+GetFontYSIZE(FONT_SMALL)+1);
  }
}

void DrawActive(WSHDR *ws,int y)
{
  wsprintf(ws,"%t","提示闹铃开启");
  int x=(scr_w/2)+(Get_WS_width(ws,FONT_SMALL)/2)+5;
  DrawString(ws,2,y,scr_w-5,y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,2,clrBlack,transparent);
#ifdef ELKA
  DrawCheckBox(x,y,alarm_active==1?1:0);         
  if(curpos==1) DrawCursor(x,x+x2_cb,y+x2_cb+1);
#else
  DrawCheckBox(x-2,y,alarm_active==1?1:0);         
  if(curpos==1) DrawCursor(x-2,x+x2_cb-2,y+x2_cb+1);
#endif
  
  y+=GetFontYSIZE(FONT_SMALL);
#ifdef ELKA
  DrawCheckBox(x,y+2,auto_snooze==1?1:0);
  if(curpos==2) DrawCursor(x,x+x2_cb,y+x2_cb+3);
#else
  DrawCheckBox(x-2,y,auto_snooze==1?1:0);
  if(curpos==2) DrawCursor(x-2,x+x2_cb-2,y+x2_cb+1);
#endif

  wsprintf(ws,"%t","自动再次提醒");
  DrawString(ws,2,y,scr_w-5,y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,2,clrBlack,transparent);  
}


static void DrawAlarm(WSHDR *ws)
{
  int font_y = GetFontYSIZE(FONT_SMALL);//16+2
  LockSched();
#ifdef ELKA
  int days_y=250;
  int active_y=150;
  int alarm_y=50;
#else
  int days_y=135;
  int active_y=65;
  int alarm_y=font_y+10;
#endif
  DrawTime(ws);
  DrawDays(ws,days_y);  
  DrawTimeAlarm(ws,alarm_y);
  DrawSnoozeTime(ws,active_y);
  DrawActive(ws,active_y);
  
/*
    char days[7];
TTime alarm_time;
TTime snooze_time;
int alarm_active;
int auto_snooze;
*/
  UnlockSched();    
}


void MoveCurItem(int i,int j)//j=0-right j=1-left
{
  switch(i)
  {
    case 0:
    {
      if(!edittime) curitem=!curitem;
      else
      {
        if(j)
        {
          if(timepos>0) timepos--; else timepos=3;
        }
        else
        {
          if(timepos<3) timepos++; else timepos=0;
        }
      }
    }
    break;
    case 1:
    case 2: curitem=0;        break;
    case 3: curitem=!curitem; break;
    case 4:
      if(j)
      {
        if(curitem>0) curitem--; else curitem=6;
      }
      else
      {
        if(curitem<6) curitem++; else curitem=0;
      }
      break;
  }
}

void EnterButton()
{
  switch(curpos)
  {
    case 0: edittime=!edittime;           REDRAW(); break;
    case 1: alarm_active=!alarm_active;   REDRAW(); break;
    case 2: auto_snooze=!auto_snooze;     REDRAW(); break;
    case 3: editsnooze=!editsnooze;       REDRAW(); break;
    case 4: days[curitem]=!days[curitem]; REDRAW(); break;
  }
}

void EditTime(int key)
{
 switch(timepos)
 {
   case 0:  //hours*10
     {
  //    int hour1=alarm_time.hour/10;
      int hour2=alarm_time.hour%10;
      if(key>=0 && key<=2)
      {      
        alarm_time.hour=hour2+(key*10);
      }
     }
     REDRAW();
     break;
   case 1:  //hours
     {
       if(key>=0 && key<=9)
       {
         int hour1=alarm_time.hour/10;       
         alarm_time.hour=(hour1*10)+key;
       }
     }
     REDRAW();
     break;
   case 2: //min*10
     {
      int hour2=alarm_time.min%10;
      if(key>=0 && key<=6)
      {      
        alarm_time.min=hour2+(key*10);
      }
     }  
     REDRAW();
     break;   
   case 3:
     {
       if(key>=0 && key<=9)
       {
         int hour1=alarm_time.min/10;       
         alarm_time.min=(hour1*10)+key;
       }
     }
     REDRAW();
     break;
   }
   MoveCurItem(curpos,0);
}

void EditSnooze(int key)
{
 switch(curitem)
 {
   case 0:  //hours*10
     {
  //    int hour1=alarm_time.hour/10;
      int hour2=snooze_time%10;
      if(key>=0 && key<=5)
      {
        snooze_time=hour2+(key*10);
      }
     }
     REDRAW();
     break;
   case 1:  //hours
     {
       if(key>=0 && key<=9)
       {
         int hour1=snooze_time/10;       
         snooze_time=(hour1*10)+key;
       }
     }
     REDRAW();
     break;
  }
  MoveCurItem(curpos,0);
}

char clrRed[]={0xFF,0x00,0x00,0x64};

GBSTMR tmr;
void MyRedraw()
{
  DirectRedrawGUI();
}


static void OnRedraw(MAIN_GUI *data)
{
 // DrawRoundedFrame(0,YDISP+1,scr_w,scr_h,0,0,0,clrBlack,clrBlack);  
  DrawRoundedFrame(0,YDISP+1,scr_w,scr_h,0,0,0,clrWhite,clrRed);
  LockSched();
//  for(int i=scr_h;i>YDISP;i-=50)
  //  DrawRoundedFrame(0,YDISP,scr_w,YDISP+scr_h-i,0,0,0,clrRed,clrRed);
  DrawSoftKeys(data->ws1,"更新","关闭");
  UnlockSched();
  DrawAlarm(data->ws1);
  GBS_StartTimerProc(&tmr, 216, MyRedraw);
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  GBS_DelTimer(&tmr);
  data->gui.state=0;
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI(); 
  int k=msg->gbsmsg->submess;
  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
     case UP_BUTTON:    edittime=0; curitem=0;  if(curpos>0) curpos--; else curpos=4;  break;
     case DOWN_BUTTON:  edittime=0; curitem=0;  if(curpos<4) curpos++; else curpos=0;  break;
     case RIGHT_BUTTON: MoveCurItem(curpos,0); break;
     case LEFT_BUTTON:  MoveCurItem(curpos,1); break;
     case ENTER_BUTTON: EnterButton(); break;
     case '*' : PrintAbout();        break;    
     case LEFT_SOFT:
          SavePD();
          RefreshAlarmClock();
          Parser();
          break;
      case GREEN_BUTTON:
          SavePD();
          break;
   /* case '#' :
      {
        WSHDR *ws;
        ws=AllocWS(150);
        extern const char *successed_config_filename;
        str_2ws(ws,successed_config_filename,128);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
      }
      break;      */
     case RIGHT_SOFT:     
           SavePD();
           RefreshAlarmClock();
           return (1);
     case RED_BUTTON:  return 1;
    }
  }

  if ((k>='0')&&(k<='9') && msg->gbsmsg->msg==KEY_DOWN)
  {
    if(curpos==0)
    {
      edittime=1;
      EditTime(k-'0');
    }
    
    if(curpos==3)
    {
      EditSnooze(k-'0');
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};


const RECT Canvas={0,0,0,0};
static void maincsm_oncreate(CSM_RAM *data)
{
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  for(int i=0;i<7;i++)
    days[i]=0;
  Parser();
  MAIN_CSM*csm=(MAIN_CSM*)data;
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  //patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  my_csm_id=csm->gui_id=CreateGUI(main_gui);  
//  CreateGUI(main_gui);   
}


//---------------------------------------------------------------------------//

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)
{
  FreePD();
  GBS_DelTimer(&tmr);
  SUBPROC((void *)ElfKiller);
}


static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}


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

void UpdateCSMname(void)
{
  gb2ws((WSHDR *)(&MAINCSM.maincsm_name),"闹钟",4);
}


int main(char *exename, char *fname)
{ 
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();

  return 0;
}
