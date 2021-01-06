#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "print.h"

#define BUFSIZE 86383

const int minus11=-11;

extern const int fullfont;
extern const int msg;
extern const char fontpath[64];
char lielims[64];
int font=1;
int align=0;
int space=1;
void *canvasdata;
char temp[64];
char vejsh[64];
char temp2[64];
char vejsh2[64];
char icon_name[64];
char s_icon1[64];
extern const char icopath[64];
extern const char soundpath[64];
char ikona[64];
char vpils[16]="Ventspils Now";
extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const unsigned int weather_X;
extern const unsigned int weather_Y;
extern const unsigned int minimum;
extern const unsigned int maximum;
extern const int ENA_TALK;
int date_Y2;
int date_Y3;
int date_Y4;
int k;
int l;
int y;
int tt;
int lenght;
int talk_len;
char zime[16];
char temp_talk[4];
char check_temp[4];
char sound1[64];
char sound2[64];
char sound3[64];
char sound4[64];
int sndVolume = 6;

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

int sock;
int connect_state=0;
char buf[BUFSIZE+1];
int pbuf=0;
int traf=0;
GBSTMR mytmr;
GBSTMR mytmr2;

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
      sa.ip=htonl(IP_ADDR(194,8,25,206));
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

void send_req(void)
{
  char *req_buf=malloc(500);
  sprintf(req_buf,"GET /wap/weatherr.php?city=ventspils HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: www.118.lv\n"
                    "Connection: Close\n"
                      "\n"
                        );
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

void GetWavkaLength(char *fname) //?????
{
  unsigned int ul;
  FSTATS stat;
  GetFileStats(fname,&stat,&ul);
  lenght=stat.size;
  lenght=lenght/825;
}

void play_forth()
{
  Play(sound4);
}


void play_third()
{
  Play(sound3);
  GetWavkaLength(sound3);
  GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_forth);
}

void play_second()
{
  if(strlen(zime)!=3) Play(sound2);
  GetWavkaLength(sound2);
  if(strlen(zime)!=3) GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_third);
  else play_third();
}

TDate date;
TTime time;

void get_talk()
{
  GetDateTime(&date, &time);
  tt=0;
  sprintf(zime, "nav");
  talk_len=strlen(temp);
  if(talk_len==2)
  {
    if(temp[0]!='0')
    {
    temp_talk[0]=temp[0];
    sprintf(zime, "plus");
    }
  }
  if(talk_len==3)
  {
    if(temp[0]=='-')
    {
      sprintf(zime, "minus");
      temp_talk[0]=temp[1];
    }
    else
    {
      temp_talk[0]=temp[0];
      temp_talk[1]=temp[1];
      sprintf(zime, "minus");
    }
  }
  if(talk_len==4)
  {
    temp_talk[0]=temp[1];
    temp_talk[1]=temp[2];
    sprintf(zime, "minus");
  }
  sprintf(sound1, "%stemp.wav", soundpath);
  sprintf(sound2, "%s%s.wav", soundpath, zime);
  sprintf(sound3, "%s%s.wav", soundpath, temp_talk);
  sprintf(sound4, "%sgradus.wav", soundpath);
  GetDateTime(&date, &time);
  if((ENA_TALK)&&(minimum<time.hour)&&(maximum>time.hour))
  {
    if(talk_len==2)
    {
      if(temp_talk[0]!=check_temp[0])
      {
      Play(sound1);
      strcpy(check_temp, temp_talk);
      GetWavkaLength(sound1);
      GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_second);
      }
    }
    else
    {
    if(talk_len==3)
    {
      if(temp_talk[1]!=check_temp[1])
      {
      Play(sound1);
      strcpy(check_temp, temp_talk);
      GetWavkaLength(sound1);
      GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_second);
      }
    }
    else
    {
    if(talk_len==4)
    {
      if(temp_talk[2]!=check_temp[2])
      {
      Play(sound1);
      strcpy(check_temp, temp_talk);
      GetWavkaLength(sound1);
      GBS_StartTimerProc(&mytmr2, 22*lenght+70,play_second);
      }
    }
    }
  }
  }
}

int Parsing()
{
  char p1[]="<p>Paslaik: ";
  char p2[]="<br/>";
  char *s,*s1,*s2;
  int len, i ,j;
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
      while(s[i]!=',')
      {
        temp[i]=s[i];
        i++;
      }
      temp[i]='\0';
      sprintf(temp2, "Temp: %s", temp);
      get_talk();
      i++;
      while(i<len)
      {
        vejsh[j]=s[i];
        j++;
        i++;
      }
      vejsh[j]='\0';
      sprintf(vejsh2, "Wind: %s", vejsh);
      mfree(s);
    }
  }
  char p1_1[]="http://www.118.lv/images/icons/weather/";
  char p2_1[]=".gif";
  char *s_icon;
  if((s1=strstr(buf,p1_1))>0)
  {
    s1+=strlen(p1_1);
    if((s2=strstr(s1,p2_1))>0)
    {
      len=s2-s1;
      s_icon=malloc(len+1);
      strncpy(s_icon,s1,len);
      s_icon[len]='\0';
      strcpy(icon_name, s_icon);
      k=0;
      l=0;
      y=0;
      while(k<len)
      {
        if(s_icon[k]=='_')
          l=k;
        k++;
      }
      if(l>0)
      l++;
      while(l<len)
      {
        s_icon1[y]=s_icon[l];
        l++;
        y++;
      }
      s_icon1[y]='\0';
      sprintf(ikona, "%s%s.png", icopath, s_icon);
      mfree(s_icon);
      GBS_StartTimerProc(&mytmr, 216*1200, start_again);
      return 1;
    }
  }
  return 0;
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"VentspilsW config updated!");
      FontPathFree();
      InitConfig();
      FontPathInit(1,(char *)fontpath,fullfont);
      sprintf(lielims, "%s2135.png", fontpath);
      date_Y2=date_Y+GetImgHeight((int)lielims)+4;
      date_Y3=date_Y2+GetImgHeight((int)lielims);
      date_Y4=date_Y3+GetImgHeight((int)lielims);
      SUBPROC((void *)create_connect);
    }
  }
  
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
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
          SUBPROC((void *)get_answer);
        }
        else
        {
          SUBPROC((void *)create_connect);
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        if (connect_state) SUBPROC((void *)end_socket);
        connect_state=3;
        Parsing();
        sock=-1;
        GBS_StartTimerProc(&mytmr, 12960*60, start_again);
        break;
      }
    }
  }
  

  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&GetTypeUSSD()!=2&&!IsScreenSaver())
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
	canvasdata=BuildCanvas();
        if(IsGPRSConnected())
        {
        PrintField(date_X,date_Y, vpils, align, font, space);
        PrintField(date_X,date_Y2, temp2, align, font, space);
        PrintField(date_X,date_Y3, s_icon1, align, font, space);
        PrintField(date_X,date_Y4, vejsh2, align, font, space);
        DrawCanvas(canvasdata,weather_X,weather_Y,weather_X+GetImgWidth((int)ikona)-1,weather_Y+GetImgHeight((int)ikona)-1,1);
        DrawImg(weather_X,weather_Y,(int)ikona);
      }
      }
    }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  FontPathFree();
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&mytmr2);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"VentspilsW");
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
  FontPathInit(1,(char *)fontpath,fullfont);
  if(msg)
    ShowMSG(1,(int)"VentspilsW (c)Evilfox");
  sprintf(lielims, "%s2135.png", fontpath);
  date_Y2=date_Y+GetImgHeight((int)lielims)+4;
  date_Y3=date_Y2+GetImgHeight((int)lielims);
  date_Y4=date_Y3+GetImgHeight((int)lielims);
  start_again();
  return 0;
}
