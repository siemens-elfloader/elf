#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "strings.h"
#include "print.h"
#include "strings2.h"

#define BUFSIZE 86383

const int minus11=-11;

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

TDate date;
TTime time;

int refresh2;
int janis1;
int lenght;
char zime_t[6];
GBSTMR mytmr2;
GBSTMR mytmr3;
int first_time;
int janko;
char temp[12];
char otrais[128];
char treshais[128];
char speed[128];
char prognoze[128];
char s3[256];
char s4[256];
char s5[256];
char first[128];
char second[128];
char ICON[128];
char graadi[3];
int i;
int j;
int gg;
int refresh3;
char tempq[16];
int sock;
int connect_state=0;
char buf[BUFSIZE+1];
int pbuf=0;
int traf=0;
int date_Xz;
int date_Yz;
char zime[2];
char tempq2[6];
extern const int fullfont;
extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const unsigned int weather_X;
extern const unsigned int weather_Y;
extern const unsigned int date_X2;
extern const unsigned int date_Y2;
extern const unsigned int date_X3;
extern const unsigned int date_Y3;
extern const unsigned int date_X4;
extern const unsigned int date_Y4;
extern const unsigned int date_X5;
extern const unsigned int date_Y5;
extern const char color[];
extern const unsigned int refresh;
//extern const unsigned int font;
extern const int ENA_HELLO_MSG;
extern const int show_temp;
extern const int show_speed;
extern const int show_prognoze;
extern const int show_otrais;
extern const int show_treshais;
extern const char treshajam[128];
extern const char otrajam[128];
extern const char str[128];
extern const char pilseeta[64];
extern const char weather_img_path[64];
int ccc;
extern const unsigned int ccc1;
extern const unsigned int ccc2;
extern const int IKONA;
extern const int chekeris1;
extern const int chekeris2;
extern const int chekeris3;
extern const int chekeris4;
extern const int chekeris5;
/////////////////////pngfont start
extern const char fontpath[64];
char lielims[128];
char fontpath2[64];
int font=1;
extern const int align1;
extern const int align2;
extern const int align3;
extern const int align4;
extern const int align5;
extern const unsigned int space;
void *canvasdata;
char sound1[64];
char sound2[64];
char sound3[64];
char sound4[64];
extern const unsigned int sndVolume;
extern const unsigned int minimum;
extern const unsigned int maximum;
extern const int ENA_TALK;
extern const char soundpath[64];
/////////////////pngfont end
GBSTMR mytmr;

void start_again(void);

void create_connect(void)
{
  SOCK_ADDR sa;
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
      sa.ip=htonl(IP_ADDR(194,67,45,236));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
    {
      closesocket(sock);
      GBS_StartTimerProc(&mytmr, 12960, start_again);
    }
  }
  else
  GBS_StartTimerProc(&mytmr, 12960, start_again);
}

void start_again()
{
  if(IsGPRSConnected())
  {
  SUBPROC((void *)create_connect);
  }
  else
  GBS_StartTimerProc(&mytmr, 2160, start_again);
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

void send_req(void)
{
  char *str2=malloc(400);
  char *req_buf=malloc(strlen(str2)+800);
  sprintf(req_buf,"GET /index.xhtml?&city=%s HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: wap.weather.mail.ru\n"
                    "Connection: Close\n"
                      "\n"
                        , pilseeta);
  mfree(str2);
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
  mfree(req_buf);
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    connect_state=0;
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==BUFSIZE)
    end_socket();
  else
  {
    traf+=i=recv(sock,buf+i,BUFSIZE-i,0);
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}

void GetWavkaLength(char *fname)
{
  unsigned int ul;
  FSTATS stat;
  GetFileStats(fname,&stat,&ul);
  lenght=stat.size;
  lenght=lenght/825;
}

void hour_talk(void);

void play_forth()
{
  Play(sound4);
  if((ENA_TALK)&&(first_time==0))
  GBS_StartTimerProc(&mytmr3, 216*60, hour_talk);
}


void play_third()
{
  Play(sound3);
  GetWavkaLength(sound3);
  GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_forth);
}

void play_second()
{
//  if(strlen(zime)!=3) 
  Play(sound2);
  GetWavkaLength(sound2);
//  if(strlen(zime)!=3) 
  GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_third);
//  else play_third();
}

void play_first()
{
  Play(sound1);
        GetWavkaLength(sound1);
        GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_second);
}

void hour_talk()
{
  first_time=1;
  GetDateTime(&date, &time);
  if((time.min==2)&&(ENA_TALK)&&(minimum<=time.hour)&&(maximum>=time.hour))
  {
        Play(sound1);
        GetWavkaLength(sound1);
        GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_second);
        GBS_StartTimerProc(&mytmr3, 216*60, hour_talk);
      }
  else
    GBS_StartTimerProc(&mytmr3, 216*60, hour_talk);
}

str2int()
{
  janis1=0;
  if (temp[1]=='1') janis1=janis1+10;
  if (temp[1]=='2') janis1=janis1+20;
  if (temp[1]=='3') janis1=janis1+30;
  if (temp[1]=='4') janis1=janis1+40;
  if (temp[1]=='5') janis1=janis1+50;
  if (temp[1]=='6') janis1=janis1+60;
  if (temp[1]=='7') janis1=janis1+70;
  if (temp[1]=='8') janis1=janis1+80;
  if (temp[1]=='9') janis1=janis1+90;
  if (temp[2]=='1') janis1=janis1+1;
  if (temp[2]=='2') janis1=janis1+2;
  if (temp[2]=='3') janis1=janis1+3;
  if (temp[2]=='4') janis1=janis1+4;
  if (temp[2]=='5') janis1=janis1+5;
  if (temp[2]=='6') janis1=janis1+6;
  if (temp[2]=='7') janis1=janis1+7;
  if (temp[2]=='8') janis1=janis1+8;
  if (temp[2]=='9') janis1=janis1+9;
  sprintf(graadi, "%d", janis1);
}

void save_to_file()
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\debug_weather.txt",&stat,&ul);
    hFile = fopen("4:\\debug_weather.txt",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, buf, strlen(buf), &io_error);
      fclose(hFile, &io_error);
    }
}

void Parsing()
{
  GetDateTime(&date, &time);
//  char search_n_destroy[]="EMPTY";
  int dstart;
  int isi=0;
  int zzz=10;
//  strstr(buf, search_n_destroy)=dstart;
  while((buf[isi]!='E')&&(buf[isi+1]!='M')&&(buf[isi+2]!='P')&&(buf[isi+3]!='T')&&(buf[isi+4]!='Y'))
  {
    isi++;
  }
  dstart=isi+6;
  while(zzz>10)
  {
    buf[dstart]=0x20;
    dstart++;
    zzz--;
  }
  save_to_file();
  char p1[]="/>&#032;";
  char p2[]="<br/>";
  char p3[]=",";
  char *s,*s1,*s2;
  int len;
  if((s1=strstr(buf,p1))>0)
  {
    s1+=strlen(p1);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1;
      s=malloc(len+1);
      strncpy(s,s1,len);
      s[len]='\0';
      i=0;
      j=0;
      while(s[i]!='&')
      {
        i++;
      }
      i=i-3;
      WSHDR *ws=AllocWS(256);
      char *teast2=malloc(16);
      strncpy(teast2, s1+i, 3);
      teast2[3]='\0';
      utf8_2ws(ws,teast2, 256);
      convWS_to_ANSI(ws, temp);
      gg=strlen(temp);
      mfree(teast2);
      if(temp[2]=='0') 
      {
        sprintf(graadi, "0");
        sprintf(zime_t, "rovno");
      }
      else
      {
        sprintf(zime_t, "plus");
        if(temp[0]=='+')
         sprintf(zime, " ");
        if(temp[1]=='+')
        {
          sprintf(zime, " ");
        }
        if(temp[0]=='-')
        {
         sprintf(zime, "-");
         sprintf(zime_t, "minus");
        }
        if(temp[1]=='-')
        {
          sprintf(zime, "-");
          sprintf(zime_t, "minus");
        }
        str2int();
      }
      FreeWS(ws);
      if(graadi[0]=='0') sprintf(tempq, "%s", graadi);
      else
      sprintf(tempq, "%s%s", zime,graadi);
      ShowMSG(1,(int)"1st done");
    }
  if((s1=strstr(s,p3))>0)
  {
    s1+=strlen(p3);
    strcpy(s3, s1);
    i=7;
    j=0;
    while(s1[i]!=',')
    {
      otrais[j]=s1[i];
      i++;
      j++;
    }
    otrais[j]=0;
    ShowMSG(1,(int)"2nd done");
  }
  if((s1=strstr(s3,p3))>0)
  {
    s1+=strlen(p3);
    strcpy(s4, s1); 
    i=7;
    j=0;
    while(s1[i]!=',')
    {
      treshais[j]=s1[i];
      i++;
      j++;
    }
    treshais[j]=0;
    ShowMSG(1,(int)"3rd done");
  }
  if((s1=strstr(s4,p3))>0)
  {
    s1+=strlen(p3);
    strcpy(s5, s1); 
    i=4;
    j=0;
    while(s1[i]!=',')
    {
      speed[j]=s1[i];
      i++;
      j++;
    }
    speed[j]=0;
    ShowMSG(1,(int)"4th done");
  }
  if((s1=strstr(s5,p3))>0)
  {
    s1+=strlen(p3);
    i=strlen(s1)+1;
    s1[i]=0;
    i=5;
    j=0;
    while(s1[i]!='0')
    {
      prognoze[j]=s1[i];
      i++;
      j++;
    }
    prognoze[j]=0;
    mfree(s);
    ShowMSG(1,(int)"5th done");
  }
  char p1_3[]="/img/pict_weather_";
  char p2_3[]=".gif";
  char *s_3,*s1_3,*s2_3;
  int len_3;
  janko=1;
  if((s1_3=strstr(buf,p1_3))>0)
  {
    s1_3+=strlen(p1_3);
    if((s2_3=strstr(s1_3,p2_3))>0)
    {
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      sprintf(ICON, "%s%s%s%s", weather_img_path, "pict_weather_", s_3, ".png");
      mfree(s_3);
      janko=1;
      refresh2=1;
      sprintf(sound1, "%stemp.wav", soundpath);
      sprintf(sound2, "%s%s.wav", soundpath, zime_t);
//      if(temp[2]=='0') sprintf(sound3, "%s0.wav", soundpath);
//      else
        sprintf(sound3, "%s%s.wav", soundpath, graadi);
      if((janis1==1)||(janis1==21)||(janis1==31)||(janis1==41)) sprintf(sound4, "%sgradus.wav", soundpath);
      else
      {
        if((janis1==2)||(janis1==3)||(janis1==4)||(janis1==22)||(janis1==23)||(janis1==24)||(janis1==32)||(janis1==33)||(janis1==34)||(janis1==42)||(janis1==43)||(janis1==44)) sprintf(sound4, "%sgradusa.wav", soundpath);
      else
      {
        sprintf(sound4, "%sgradusov.wav", soundpath);
      }
      }
      if((ENA_TALK)&&(minimum<=time.hour)&&(maximum>=time.hour))
      {
        GBS_StartTimerProc(&mytmr2, 216*10,play_first);
      }
      if((first_time==0)&&(ENA_TALK)) GBS_StartTimerProc(&mytmr3, 216*60, hour_talk);
    GBS_StartTimerProc(&mytmr, 12960*refresh, start_again);
    }
  }
  }
  else
  {
    ShowMSG(1,(int)"wrong data");
    GBS_StartTimerProc(&mytmr, 12960*5, start_again);
  }
}

void Draw(void *canv)
{
  char *tempera=malloc(256);
  sprintf(tempera, "%s%sC", str, tempq);
  if(chekeris1==0)
        {
 PrintField(date_X,date_Y, tempera, align1, font, space);
          }
      else
      {
        if((chekeris1==1)&&(IsUnlocked()))
        {
  PrintField(date_X,date_Y, tempera, align1, font, space);
        }
        else
          if((chekeris1==2)&&(!IsUnlocked()))
          {
 PrintField(date_X,date_Y, tempera, align1, font, space);
          }
  mfree(tempera);
}
}

void Draw2(void *canv)
{
  WSHDR *ws=AllocWS(256);
  char *teast2=malloc(256);
  utf8_2ws(ws,speed, 256);
  convWS_to_ANSI(ws, teast2);
  if(chekeris2==0)
  {
  PrintField(date_X2,date_Y2, teast2, align2, font, space);
  }
      else
      {
        if((chekeris2==1)&&(IsUnlocked()))
        {
 PrintField(date_X2,date_Y2, teast2, align2, font, space);
        }
        else
          if((chekeris2==2)&&(!IsUnlocked()))
          {
  PrintField(date_X2,date_Y2, teast2, align2, font, space);
          }
      }
  FreeWS(ws);
  mfree(teast2);
}

void Draw3(void *canv)
{
  WSHDR *ws=AllocWS(256);
  char *teast=malloc(256);
  utf8_2ws(ws,prognoze, 256);
  convWS_to_ANSI(ws, teast);
  if(chekeris3==0)
  {
  PrintField(date_X3,date_Y3, teast, align3, font, space);
//  PrintText(date_X3, date_Y3, teast, align3, font, space, 1, 1, 40, 50);
  }
      else
      {
        if((chekeris3==1)&&(IsUnlocked()))
        {
  PrintField(date_X3,date_Y3, teast, align3, font, space);
        }
        else
          if((chekeris3==2)&&(!IsUnlocked()))
          {
  PrintField(date_X3,date_Y3, teast, align3, font, space);
      }
      }
  FreeWS(ws);
  mfree(teast);
}

void Draw4(void *canv)
{
  char *tempera=malloc(256);
  sprintf(tempera, "%s%s", otrajam, otrais);
  if(chekeris4==0)
  {
  PrintField(date_X4,date_Y4, tempera, align4, font, space);
  }
      else
      {
        if((chekeris4==1)&&(IsUnlocked()))
        {
  PrintField(date_X4,date_Y4, tempera, align4, font, space);
        }
        else
          if((chekeris4==2)&&(!IsUnlocked()))
          {
  PrintField(date_X4,date_Y4, tempera, align4, font, space);
          }
      }
  mfree(tempera);
}

void Draw5(void *canv)
{
  char *tempera=malloc(256);
  sprintf(tempera, "%s%s", treshajam, treshais);
  if(chekeris5==0)
  {
  PrintField(date_X5,date_Y5, tempera, align5, font, space);
  }
      else
      {
        if((chekeris5==1)&&(IsUnlocked()))
        {
  PrintField(date_X5,date_Y5, tempera, align5, font, space);
        }
        else
          if((chekeris5==2)&&(!IsUnlocked()))
          {
  PrintField(date_X5,date_Y5, tempera, align5, font, space);
          }
      }
  mfree(tempera);
}

#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MailWeather config updated!");
      InitConfig();
      FontPathFree();
      strcpy(fontpath2, fontpath);
      FontPathInit(font,fontpath2, fullfont, 1);
      sprintf(lielims, "%s2135.png", fontpath2);
      first_time=1;
      GBS_DelTimer(&mytmr);
      GBS_DelTimer(&mytmr2);
      GBS_DelTimer(&mytmr3);
      SUBPROC((void *)create_connect);
    }
  }

  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //Если посылали запрос
          SUBPROC((void *)send_req);        
        }
        else
          {
          SUBPROC((void *)create_connect); 
          }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          //Если посылали send
          SUBPROC((void *)get_answer);
        }
        else
        {
          SUBPROC((void *)create_connect);
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        if (connect_state) SUBPROC((void *)end_socket);
        connect_state=3;
        Parsing();
        sock=-1;
        break;
      }
    }
  }
  
  
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver())
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
        canvasdata=BuildCanvas();
      if((janko==1)&&(refresh2==1))
      {
      ClearScreen();
      if(show_temp)
      Draw(canvasdata);
      if(show_speed)
      Draw2(canvasdata);
      if(show_prognoze)
      Draw3(canvasdata);
      if(show_otrais)
        Draw4(canvasdata);
      if(show_treshais)
      Draw5(canvasdata); 
      if(IKONA)
      {
      DrawCanvas(canvasdata,weather_X,weather_Y,weather_X+GetImgWidth((int)ICON)-1,weather_Y+GetImgHeight((int)ICON)-1,1);
      DrawImg(weather_X,weather_Y,(int)ICON);
      }
      refresh2=0;
      }
      }
    }
    else
      refresh2=1;

  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
//  AddKeybMsgHook((void *)my_keyhook);
}

static void Killer(void)
{
//  RemoveKeybMsgHook((void *)my_keyhook); 
  FontPathFree();
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&mytmr2);
  GBS_DelTimer(&mytmr3);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MailWeather v2.3 (c)evilfox");
}

char elf_path[256];

int main(char *filename)
{
  char *s;
  int len;
  extern const char *successed_config_filename;
  WSHDR *ws;
  
  InitConfig();
  s=strrchr(filename,'\\');
  len=(s-filename)+1;
  strncpy(elf_path,filename,len);
  elf_path[len]=0;
  if(strlen(fontpath)==0)
  {
    LockSched();
    ShowMSG(1,(int)"Please config!");
    ws=AllocWS(150);
    str_2ws(ws,successed_config_filename,128);
    ExecuteFile(ws,0,0);
    UnlockSched();
    SUBPROC((void *)Killer);
    return 0;
  }
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched(); 
  if(ENA_HELLO_MSG)
  ShowMSG(1,(int)"MailWeather v2.3 (c)evilfox");
  FontPathInit(font,(char *)fontpath, fullfont, 1);
  start_again();
  return 0;
}
