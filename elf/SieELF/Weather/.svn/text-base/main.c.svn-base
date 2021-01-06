#include "..\inc\swilib.h"
#include "..\inc\pnglist.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
WSHDR *ews;

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};
const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};

#pragma inline
unsigned int char8to16(int c)
{
  if (c>=128)
  {
    //Win->Dos
    c=wintranslation[c-128];
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

void ascii2ws_add(WSHDR *ws, const char *s)
{
  char c;
  //CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

#define TOTAL_ICONS 17

char * S_ICONS[TOTAL_ICONS];

static const char * const icons_names[TOTAL_ICONS]=
{
  "1.png",//ясно
  "2.png",//малооблачно
  "3.png",//облачно
  "3.png",//пасмурно
  "4.png",//дождь
  "5.png",//ливень
  "6.png",//снег
  "7.png",//снег
  "8.png",//гроза
  "0.png",//нет данных
  "10.png",//без осадков, картинки нету
  //ночь
  "9.png",//ясно
  "a.png",//малооблачно
  "b.png",//облачно
  "b.png",//пасмурно
  "c.png",//дождь
  "d.png"//снег
};

extern const char ICON_PATH[];

char *MakeGlobalString(const char *first, int breakchar, const char *last)
{
  int l;
  char *p;
  p=malloc((l=strlen(first))+strlen(last)+2);
  strcpy(p,first);
  if (first[strlen(first)-1]!=breakchar) p[l++]=breakchar;
  strcpy(p+l,last);
  return p;
}

void setup_ICONS(void)
{
  int i=0;
  do
  {
    if (!S_ICONS[i]) S_ICONS[i]=MakeGlobalString(ICON_PATH,'\\',icons_names[i]);
    i++;
  }
  while(i<TOTAL_ICONS);
  return;
}

void free_ICONS(void)
{
  int i=0;
  do
  {
    mfree((void*)S_ICONS[i]);
    S_ICONS[i]=0;
    i++;
  }
  while(i<TOTAL_ICONS);
  return;
}

int sock;
int connect_state;
char buf[16384];
char logbuf[1024];
int pbuf;

extern const unsigned int TID;

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

typedef struct
{
  int tid;
  char name[40];
  int lat;
  int lon;
}TOWN_ID;

typedef struct
{
  int day;
  int month;
  int year;
  int hour;
  short tod;
  int wday;
  int predict;
  
  short cloudiness;
  short fallout;
  short rpower;
  short spower;
  
  int pressure_min;
  int pressure_max;
  int temp_min;
  int temp_max;
  int wind_min;
  int wind_max;
  short wind_dir;
  
  int relwet_min;
  int relwet_max;
  
  int heat_min;
  int heat_max;
}WEATHER;

WEATHER weath[4];
TOWN_ID town;

void url_decode(char* dest,char* src)
{
 while(*src!='"')
 {
  if(*src=='%')
   {
     src++;
     *dest=0;
     if(*src>='0' && *src<='9')
      {
        *dest=(*src)-'0';
        *dest<<=4;
      }
     if(*src>='A' && *src<='F')
      {
        *dest=(*src)-('A'-0xA);
        *dest<<=4;
      }
     src++;
     if(*src>='0' && *src<='9') *dest+=((*src)-'0');
     if(*src>='A' && *src<='F') *dest+=((*src)-('A'-0xA));
     dest++;
   }
  src++;
  }
 *(dest)=0;
}

int atoi(char *attr)
{
  int ret=0;
  int neg=1;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else { if ( attr[k]=='-') {neg=-1;} else {return(ret*neg);}}
  }
}

void create_connect(void)
{
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    sa.ip=htonl(IP_ADDR(212,48,138,18));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      REDRAW();
    }
    else
      closesocket(sock);
  }
}


char req_buf[256];

void send_req(void)
{
  sprintf(req_buf,"GET /xml/%i_1.xml"
          " HTTP/1.0\r\nHost: informer.gismeteo.ru\r\n\r\n",TID);
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==16383)
    end_socket();
  else
  {
    i=recv(sock,buf+i,16383-i,0);
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

void Parsing()
{
  strcat(logbuf,"Parsing\n"); REDRAW();
  char *fcstr[4];    
  char *pre;
  
  pre=strstr(buf,"latitude=")+10;        
  town.lat=atoi(pre);
      
  pre=strstr(buf,"longitude=")+11;
  town.lon=atoi(pre);
       
  pre=strstr(buf,"index=")+7;
  town.tid=atoi(pre);
  
  url_decode(town.name,strstr(buf,"sname=")+7);
           
  fcstr[0]=strstr(buf," <FORE");
  fcstr[1]=strstr(fcstr[0]+1," <FORE");
  fcstr[2]=strstr(fcstr[1]+1," <FORE");
  fcstr[3]=strstr(fcstr[2]+1," <FORE");
    
  for (int j=0; j<4; j++)
  {
    pre=strstr(fcstr[j],"day=")+5;
    weath[j].day=atoi(pre);
    
    pre=strstr(fcstr[j],"month=")+7;
    weath[j].month=atoi(pre);
    
    pre=strstr(fcstr[j],"hour=")+6;
    weath[j].hour=atoi(pre);
    
    pre=strstr(fcstr[j],"tod=")+5;
    weath[j].tod=atoi(pre);
    
    pre=strstr(fcstr[j],"predict=")+9;
    weath[j].predict=atoi(pre);
    
    pre=strstr(fcstr[j],"weekday=")+9;
    weath[j].wday=atoi(pre);

    pre=strstr(fcstr[j],"cloudiness=")+12;
    weath[j].cloudiness=atoi(pre);
    
    pre=strstr(fcstr[j],"precipitation=")+15;
    weath[j].fallout=atoi(pre);
    
    pre=strstr(fcstr[j],"rpower=")+7;
    weath[j].rpower=atoi(pre);
    
    pre=strstr(fcstr[j],"spower=")+7;
    weath[j].spower=atoi(pre);

    pre=strstr(fcstr[j],"PRESSURE max=")+14;
    weath[j].pressure_max=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"PRESSURE max="),"min=")+5;
    weath[j].pressure_min=atoi(pre);    

    pre=strstr(fcstr[j],"TEMPERATURE max=")+17;
    weath[j].temp_max=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"TEMPERATURE max="),"min=")+5;
    weath[j].temp_min=atoi(pre);    
    
    
    pre=strstr(fcstr[j],"WIND min=")+10;
    weath[j].wind_min=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"WIND min="),"max=")+5;
    weath[j].wind_max=atoi(pre);
    
    pre=strstr(fcstr[j],"direction=")+10;
    weath[j].wind_dir=atoi(pre);
    
    pre=strstr(fcstr[j],"RELWET max=")+12;
    weath[j].relwet_max=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"RELWET max="),"min=")+5;
    weath[j].relwet_min=atoi(pre); 
    
    
    pre=strstr(fcstr[j],"HEAT min=")+10;
    weath[j].heat_min=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"HEAT min="),"max=")+5;
    weath[j].heat_max=atoi(pre);    
  }

    void ShowWeather(void);
    ShowWeather();
}


void DrawWait()
{
  WSHDR *ws = AllocWS(1024);
    wsprintf(ws,"%s",logbuf);
    DrawString(ws,2,YDISP+5,ScreenW()-1,ScreenH()-1,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

void OnRedraw(MAIN_GUI *data)
{       
  DrawRoundedFrame(1 ,YDISP, ScreenW()-1, ScreenH()-1, 0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  DrawWait();
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT: 
#ifndef NEWSGOLD
    case RED_BUTTON:       
#endif
      return(1);
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

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
  (void *)method7,	
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);    

  SUBPROC((void *)create_connect);
  ews=AllocWS(16384);
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  free_ICONS();
  FreeWS(ews);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
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
          strcat(logbuf,"Connected\n");
          REDRAW();
          //Если посылали запрос
          SUBPROC((void *)send_req);
          REDRAW();
        }
        else
        {
          strcat(logbuf,"Error, try again..\n"); 
          SUBPROC((void *)create_connect); 
          REDRAW();
        }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          strcat(logbuf,"Reading\n"); 
          REDRAW();
          //Если посылали send
          SUBPROC((void *)get_answer);
          REDRAW();
        }
        else
        {
          strcat(logbuf,"Error, try again..\n"); SUBPROC((void *)create_connect); REDRAW();
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        if (connect_state) SUBPROC((void *)end_socket);
        strcat(logbuf,"Receiving\n"); 
        REDRAW();
        connect_state=3;
        Parsing();
        sock=-1;
        break;
      }
    }
    
  }
  return(1);
}

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Weather Forecast");
}

int main()
{
  InitConfig();
  if (TID)
  {  
    setup_ICONS();
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();
    LockSched();
    MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }
  else
  {
    LockSched();
    ShowMSG(1,(int)"Please setup Town ID!");
    UnlockSched();
  }    
  return 0;
}

//---------------------------- Edit Control -----------------------------------
#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

typedef struct
{
  DYNPNGICONLIST dpl;
  char *fname;
  int uni_n;
}DYNPNGILIST_MY;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

void edchat_ghook(GUI *data, int cmd)
{
  DYNPNGILIST_MY *t=EDIT_GetUserPointer(data);
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==3)
  {
    while (t)
    {
      DYNPNGILIST_MY *d;
      d=t;
      t=t->dpl.next;
      mfree(d->dpl.img->bitmap);
      mfree(d->dpl.img);
      mfree(d->fname);
      mfree(d);
    }    
  }
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=(DYNPNGICONLIST *)t;
    DisableIDLETMR();
  }
}

int itemnum, wd_id;

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  void ShowWeather(void);
  switch (msg->gbsmsg->submess)
  {
  case LEFT_SOFT:
  case RIGHT_SOFT:
#ifndef NEWSGOLD
  case RED_BUTTON:
#endif
      CloseCSM(MAINCSM_ID);
      break;
      
  case RIGHT_BUTTON:
        itemnum++;
        if (itemnum==4) itemnum=3;
        GeneralFunc_flag1(wd_id,1);
        ShowWeather();        
      break;
  case LEFT_BUTTON:
        itemnum--;
        if (itemnum==-1) itemnum=0;
        GeneralFunc_flag1(wd_id,1);
        ShowWeather();       
      break;
  case '*':
    if (connect_state==3)
      {
        char s[128];
        sprintf(s,"%s\nID города:%i\nДолгота:%i\xB0\nШирота:%i\xB0",town.name,town.tid,town.lon,town.lat);
        ShowMSG(0, (int)s);
      }    
    break;
  }

  return(0); //Do standart keys
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)town.name,LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x00000002
};

int AddPicIfNotExist(DYNPNGILIST_MY **top, char *fname)
{
  DYNPNGILIST_MY *t, *p;
  IMGHDR *img;
  int n=0;
  t=(DYNPNGILIST_MY *)top;
  while((p=t->dpl.next))
  {
    t=p;
    if (!strcmp_nocase(t->fname, fname)) return t->uni_n;
    n++;
  }
  // Не нашли в кэше, пробуем добавить
  img=CreateIMGHDRFromPngFile(fname,0);
  if (!img) return (-1);
  // Получилось создать картинку
  n+=FIRST_UCS2_BITMAP;
  t=t->dpl.next=malloc(sizeof(DYNPNGILIST_MY));
  t->uni_n=n;
  t->dpl.next=0;
  t->dpl.icon=GetPicNByUnicodeSymbol(n);
  t->dpl.img=img;
  t->fname=malloc(strlen(fname)+1);
  strcpy(t->fname,fname);
  return (n);
}

#define wslen(ws) ws->wsbody[0]
void ShowWeather(void)
{
  char *todlist[4]=
  {
    "ночь",
    "утро",
    "день",
    "вечер"
  };  
  
  char *cloudness[4]=
  {
    "Ясно",
    "Малооблачно",
    "0блачно",
    "Пасмурно"
  };
  
  char *wind[8]=
  {
    " сев.",
    " сев.-вост.",
    " вост.",
    " юго-вост.",
    " южный",
    " юго-зап.",
    " зап.",
    " сев.-зап."
  };

  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  void *ma=malloc_adr();
  void *eq;
  
  DYNPNGILIST_MY *top=0;
  int pic_n;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  char s[128];
  if (town.tid)
  {
    CutWSTR(ews,0);
    sprintf(s,"< %i/4 %i.%02i, %s >", itemnum+1, weath[itemnum].day,weath[itemnum].month,todlist[weath[itemnum].tod]);
    ascii2ws_add(ews, s);
    
    extern const unsigned int FONT_SIZE_DATE;
    extern const unsigned int FONT_DATE_COLOR;
    
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,FONT_DATE_COLOR);
    SetFontToEditCOptions(&ec_options,FONT_SIZE_DATE);
    ConstructEditControl(&ec,ECT_READ_ONLY,0x40,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);  
    AddEditControlToEditQend(eq,&ec,ma);
    
    extern const unsigned int FONT_SIZE_DATA;
    extern const unsigned int FONT_DATA_COLOR;  
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,FONT_DATA_COLOR);
    SetFontToEditCOptions(&ec_options,FONT_SIZE_DATA);
        
    CutWSTR(ews,0);
    pic_n= weath[itemnum].tod ? AddPicIfNotExist(&top,S_ICONS[weath[itemnum].cloudiness]) : AddPicIfNotExist(&top,S_ICONS[weath[itemnum].cloudiness+11]);
    if (pic_n!=-1)
    {
      wsAppendChar(ews,pic_n);
      wsAppendChar(ews,' ');
    }    

    pic_n=-1;
    if (weath[itemnum].tod) pic_n=AddPicIfNotExist(&top,S_ICONS[weath[itemnum].fallout]);
      else
      {
       if (weath[itemnum].fallout==4||weath[itemnum].fallout==5||weath[itemnum].fallout==8) pic_n=AddPicIfNotExist(&top,S_ICONS[15]);
       if (weath[itemnum].fallout==6||weath[itemnum].fallout==7) pic_n=AddPicIfNotExist(&top,S_ICONS[16]);
      }
    
    if (pic_n!=-1) wsAppendChar(ews,pic_n);
    wsAppendChar(ews,'\n');
    
    char *l="Нет данных\n";
    if(weath[itemnum].fallout==4 && weath[itemnum].rpower==0) l="Возможен дождь\n";
    if(weath[itemnum].fallout==4 && weath[itemnum].rpower==1) l="Дождь\n";
    
    if(weath[itemnum].fallout==5 && weath[itemnum].rpower==0) l="Возможен ливень\n";
    if(weath[itemnum].fallout==5 && weath[itemnum].rpower==1) l="Ливень\n";
    
    if(weath[itemnum].fallout==6 && weath[itemnum].rpower==0) l="Возможен снег\n";
    if(weath[itemnum].fallout==6 && weath[itemnum].rpower==1) l="Снег\n";
    
    if(weath[itemnum].fallout==7 && weath[itemnum].rpower==0) l="Возможен снег\n";
    if(weath[itemnum].fallout==7 && weath[itemnum].rpower==1) l="Снег\n";
    
    if(weath[itemnum].fallout==8 && weath[itemnum].spower==0) l="Возможна гроза\n";
    if(weath[itemnum].fallout==8 && weath[itemnum].spower==1) l="Гроза\n";
    
    if(weath[itemnum].fallout==9) l="Нет данных\n";
    if(weath[itemnum].fallout==10) l="Без осадков\n";   
    
    
    sprintf(s,"%i-%i\xB0\x43\n%s: %i-%i\xB0\n",weath[itemnum].temp_min,weath[itemnum].temp_max,"Комфорт",weath[itemnum].heat_min, weath[itemnum].heat_max);
    ascii2ws_add(ews, s); 
    
    sprintf(s,"%i-%i %s\n",weath[itemnum].pressure_min,weath[itemnum].pressure_max,"мм.рт.ст");
    ascii2ws_add(ews, s);
    
    sprintf(s,"%s\n",cloudness[weath[itemnum].cloudiness]);
    ascii2ws_add(ews, s);
    
    ascii2ws_add(ews, l);
    
    sprintf(s,"%s%s %i-%i %s\n","Ветер:", wind[weath[itemnum].wind_dir],weath[itemnum].wind_min,weath[itemnum].wind_max,"м/с");
    ascii2ws_add(ews, s);
    
    sprintf(s,"%s: %i-%i%%\n","Влажность",weath[itemnum].relwet_min,weath[itemnum].relwet_max);
    ascii2ws_add(ews, s);
    
    //
    //sprintf(s, "-------------------");
    //ascii2ws_add(ews, s);
    ConstructEditControl(&ec,ECT_READ_ONLY,0x40,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);     
  }
  else
  {
    CutWSTR(ews,0);
    sprintf(s,"Информация о погоде в городе с ID %i отсутствует!", TID);
    ascii2ws_add(ews, s);
    
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,2);//красный
    SetFontToEditCOptions(&ec_options,4);
    ConstructEditControl(&ec,ECT_READ_ONLY,0x00,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);  
    AddEditControlToEditQend(eq,&ec,ma);    
  }
    
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,top);
}
