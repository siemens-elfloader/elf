#include "..\inc\swilib.h"
#include "strings.h"

#define ECINPUT 3
#define ECOUTPUT 5
#define BUFSIZE 86383

const int minus11=-11;
char temp[12];
char otrais[128];
char treshais[128];
char speed[128];
char prognoze[128];
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
int traf=0;
GUI *ggui=0;
char s3[256];
char s4[256];
char s5[256];
int i;
int j;

#define wslen(ws) ws->wsbody[0]

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


void setstatus(char *status);

int sock;
int connect_state=0;
char buf[BUFSIZE+1];
int pbuf=0;


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

void create_connect(void)
{
  setstatus("connecting\n");
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
      closesocket(sock);
  }
}

void send_req(void)
{
  setstatus("send_req\n");
  char *str2=malloc(400);
  char *req_buf=malloc(strlen(str2)+800);
  sprintf(req_buf,"GET /index.xhtml?&city=3887 HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: wap.weather.mail.ru\n"
                    "Connection: Close\n"
                      "\n"
                        );
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

void Start(GUI *data)
{
  setstatus(" \n");
  SUBPROC((void *)create_connect);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

  
int Parsing()
{
  setstatus("parsing\n");//!
  char p1[]="+";
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
        temp[i]=s[i];
        i++;
        j++;
      }
      temp[j]=0;
    }
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
    char gatavs[256];
    sprintf(gatavs, "temp=%s, otrais=%s, treshais=%s, speed=%s, prognoze=%s", temp, otrais, treshais, speed, prognoze);
    WSHDR *ws=AllocWS(2000);
    utf8_2ws(ws,gatavs, 2000);
    EDIT_SetTextToEditControl(ggui, ECOUTPUT, ws);
    FreeWS(ws);
    mfree(s);
    DirectRedrawGUI();
      return 1;
  }
  return 0;
}

void OnRedraw(MAIN_GUI *data)
{       
  
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
#ifndef NEWSGOLD
    case RED_BUTTON:       
      
      return(1);
#endif
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
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);    
  void create_ed();
  SUBPROC((void *)create_ed);
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
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
          setstatus("Connected\n");
          //Если посылали запрос
          SUBPROC((void *)send_req);        
        }
        else
          {
          setstatus("Error\n");
          SUBPROC((void *)create_connect); 
          }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          setstatus("Reading\n");
          //Если посылали send
          SUBPROC((void *)get_answer);
        }
        else
        {
          SUBPROC((void *)create_connect);
          setstatus("Error\n");
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        if (connect_state) SUBPROC((void *)end_socket);
        setstatus("Working_Rec_info\n");
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SMS Latvia(Alfa) - (c)Evilfox");
}

int main()
{  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched(); 
  return 0;
}

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

void edchat_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC skk={0x0018, 0x0000,(int)"Menu"};
  if (cmd==7)
    SetSoftKey(data,&skk,SET_SOFT_KEY_N); 
}

int itemnum, wd_id;

void setstatus(char *status)
{
  if(ggui)
  { 
    WSHDR *ws=AllocWS(21);
    utf8_2ws(ws,status,20);
    EDIT_SetTextToEditControl(ggui, 1,ws);
    FreeWS(ws);
    DirectRedrawGUI();
  }
}

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  
  void create_ed(void);
  
  switch (msg->gbsmsg->submess)
  {
    
#ifndef NEWSGOLD
  case RED_BUTTON:
    
    CloseCSM(MAINCSM_ID);
    break;
#endif  
    
  case GREEN_BUTTON:
    setstatus("\n");
    SUBPROC((void *)create_connect);
    break;
  }
  if (msg->keys==0x18)
  {
    void MMenu();
    MMenu();
  }
  if (msg->keys==0x1)
  {
    CloseCSM(MAINCSM_ID);
  }
  return(0); 
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"SMS Latvia",LGP_NULL};

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
  0x40000000
};


void create_ed(void)
{
  
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(50);
  ConstructEditControl(&ec,1,0,0,12);
  AddEditControlToEditQend(eq,&ec,ma); 
  
  utf8_2ws(ws, "Number:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,16384);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  utf8_2ws(ws, "SMS text:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,16384);
  AddEditControlToEditQend(eq,&ec,ma); 
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
}

// menu



void traffic(GUI *data)
{
  char str[10];
  sprintf(str,"%d Kb",traf/1024);
  ShowMSG(1,(int)str);
}

void exit(GUI *data)
{
  CloseCSM(MAINCSM_ID);
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,0,0,icon,(int)"Menu",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[3]=
{
  {NULL,(int)"Send SMS", LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Traffic",  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Exit",     LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[3]={
  Start,
  traffic,
  exit
};

const SOFTKEY_DESC menu_sk1[]=
{
  {0x0018,0x0000,(int)"OK"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt1=
{
  (SOFTKEY_DESC *)menu_sk1,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt1,
  0,
  NULL,
  menuitems,
  menuprocs,
  3
};

void MMenu(void)
{
  patch_header(&menuhdr);
  CreateMenu(0,0,&tmenu,&menuhdr,0,3,0,0);
}
