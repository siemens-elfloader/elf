#include "..\inc\swilib.h"
#include "strings.h"

#define ECINPUT 4
#define ECOUTPUT 2
#define ECOUTPUT2 3
#define BUFSIZE 86383

const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
int traf=0;
GUI *ggui=0;
int f;
int i;
int l;
int k;
int day;
int fsize;
unsigned int ul;
char repeat[64];
char p1[32];
char p2[32];
char dayname[32];
int spacing;
int laadeeja;

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
      sa.ip=htonl(IP_ADDR(212,112,175,163));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      laadeeja=1;
      connect_state=1;
    }
    else
      closesocket(sock);
  }
}

void send_req(void)
{
  char *req_buf=malloc(256);
  sprintf(req_buf,"GET /content/blogcategory/29/29/ HTTP/1.1\n"
          "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: www.6tv.lv\n"
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
  setstatus("Downloading\n");
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

void remaking(void);

void Parsing()
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\programma.txt",&stat,&ul);
    hFile = fopen("4:\\programma.txt",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, buf, strlen(buf), &io_error);
      fclose(hFile, &io_error);
    }
   if(laadeeja==1) SUBPROC((void *)remaking); 
   else
     ShowMSG(1,(int)"Downloaded");
}

void opening()
{
  FSTATS stat;
  GetFileStats("4:\\programma.txt",&stat,&ul);
  if(stat.size>0)
  {
  f=fopen("4:\\programma.txt",A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  }
  else
    ShowMSG(1,(int)"Failed");
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
  if(day==1) 
  {
//    sprintf(dayname, "PIRMDIENA");
    sprintf(p1, "PIRMDIENA");
  }
  if(day==2) 
  {
//    sprintf(dayname, "OTRDIENA");
    sprintf(p1, "OTRDIENA");
  }
  if(day==3) 
  {
//    sprintf(dayname, "TRESDIENA");
    sprintf(p1, "TRESDIENA");
  }
  if(day==4) 
  {
//    sprintf(dayname, "CETURTDIENA");
    sprintf(p1, "CETURTDIENA");
  }
  if(day==5) 
  {
//    sprintf(dayname, "PIEKTDIENA");
    sprintf(p1, "PIEKTDIENA");
  }
  if(day==6) 
  {
//    sprintf(dayname, "SESTDIENA");
    sprintf(p1, "SESTDIENA");
  }
  if(day==7) 
  {
//    sprintf(dayname, "SVETDIENA");
    sprintf(p1, "SVETDIENA");
  }
  if(day==1) sprintf(p2, "OTRDIENA");
  if(day==2) sprintf(p2, "TRESDIENA");
  if(day==3) sprintf(p2, "CETURTDIENA");
  if(day==4) sprintf(p2, "PIEKTDIENA");
  if(day==5) sprintf(p2, "SESTDIENA");
  if(day==6) sprintf(p2, "SVETDIENA");
  if(day==7) sprintf(p2, "<br /></font>");
  char *s,*s1,*s2;
  int len;
  if((s1=strstr(p,p1))>0)
  {
    s1+=strlen(p1);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1;
      s=malloc(len+1);
      strncpy(s,s1,len);
      s[len]='\0';
//      WSHDR *ws01=ascii2ws(s);
//      EDIT_SetTextToEditControl(ggui, ECINPUT,ws01);
//      FreeWS(ws01);
//      DirectRedrawGUI();
//      mfree(s);
    }
  }
  i=0;
  len=0;
  while(s[i]!='<')
  {
    dayname[len]=s[i];
    len++;
    i++;
  }
  dayname[len]='\0';
//  sprintf(dayname, "%s", p1);
  i=0;
  l=0;
  k=0;
  len=strlen(s);
  char *texts=malloc(10000);
  while(i<len)
  {
    if(s[i]==':') 
    {
      i++;
      if((s[i]=='0')||(s[i]=='1')||(s[i]=='2')||(s[i]=='3')||(s[i]=='4')||(s[i]=='5')) k++;
    }
    i++;
  }
  i=0;
//  char *test=malloc(256);
//  sprintf(test, "%d", k);
//  ShowMSG(1,(int)test);
//  mfree(test);

//  if((day==1)||(day==6)||(day==7)) k=k-1;
//  else k=k-2;
L1:
  while(s[i]!=':')
  {
    i++;
  }
//  i++;
//  if((s[i]!='0')||(s[i]!='1')||(s[i]!='2')||(s[i]!='3')||(s[i]!='4')||(s[i]!='5')) goto L1;
  i=i-2;
  while(s[i]!='<')
  {
    texts[l]=s[i];
    l++;
    i++;
  }
  texts[l]=p[15];
  l++;
  spacing=6;
  while(spacing!=0)
  {
    texts[l]='=';
    l++;
    spacing--;
  }
  texts[l]=p[15];
  l++;
  texts[l]='\0';
  k--;
  if(k!=0) goto L1;
  mfree(s);
  WSHDR *ws2=ascii2ws(p1);
  EDIT_SetTextToEditControl(ggui, ECOUTPUT,ws2);
  FreeWS(ws2);
  DirectRedrawGUI();
  WSHDR *ws=ascii2ws(dayname);
  EDIT_SetTextToEditControl(ggui, ECOUTPUT2,ws);
  FreeWS(ws);
  DirectRedrawGUI();
  WSHDR *ws01=ascii2ws(texts);
  EDIT_SetTextToEditControl(ggui, ECINPUT,ws01);
  FreeWS(ws01);
  DirectRedrawGUI();
  mfree(texts);
  mfree(p);
  ShowMSG(1,(int)p1);
}

void remaking2()
{
  int rem2_len;
// char rem2_txt=malloc(rem2_len+1);
//  strcpy(rem2_txt, buf);
  rem2_len=strlen(buf)-20;
  i=0;
  while(i<rem2_len)
  {
    i++;
    if(buf[i]==':')
    {
      i--;
      if((buf[i]=='0')||(buf[i]=='1')||(buf[i]=='2')||(buf[i]=='3')||(buf[i]=='4')||(buf[i]=='5')||(buf[i]=='6')||(buf[i]=='7')||(buf[i]=='8')||(buf[i]=='9'))
      {
        i=i-1;
      }
      if((buf[i]=='0')||(buf[i]=='1')||(buf[i]=='2'))
      {
      i=i-1;
      if(buf[i]!='>')
      {
        buf[i]='<';
        i=i+6;
      }
      else i=i+6;
      }
      else i=i+6;
    }
  }
  Parsing();
}

void remaking()
{
  laadeeja=0;
  FSTATS stat;
  GetFileStats("4:\\programma.txt",&stat,&ul);
  if(stat.size>0)
  {
  f=fopen("4:\\programma.txt",A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  }
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
  i=0;
  l=0;
  while(i<fsize)
  {
    while((p[i]!=0xC4)&&(p[i]!=0xC5)/*&&(p[i]!=0x45)*/&&(i<fsize))
    {
      buf[l]=p[i];
      l++;
      i++;
    }
    if(p[i]==0xC4)
    {
    i++;
    if (p[i]==0x81) buf[l]='a';
    else
    if (p[i]==0x8C) buf[l]='c';
    else
    if (p[i]==0x93) buf[l]='e';
    else
    if (p[i]==0xA3) buf[l]='g';
    else
    if (p[i]==0xAB) buf[l]='i';
    else
    if (p[i]==0x92) buf[l]='E';
    else
    if (p[i]==0xB7) buf[l]='k';
    else
    if (p[i]==0xBC) buf[l]='l';
    else
    {
      i--;
      buf[l]=p[i];
      i++;
      l++;
      buf[l]=p[i];
    }
    }
    else
      if(p[i]==0xC5)
      {
        i++;
    if (p[i]==0x86) buf[l]='n';
    else
    if (p[i]==0xA1) buf[l]='s';
    else
    if (p[i]==0xAB) buf[l]='u';
    else
    if (p[i]==0xBE) buf[l]='z';
    else
    if (p[i]==0xA0) buf[l]='S';
    else
    {
      i--;
      buf[l]=p[i];
      i++;
      l++;
      buf[l]=p[i];
    }
      }
    /*
    else
      if(p[i]==0x45)
      {
        i++;
        if (p[i]==0xC5) buf[l]='S';
        else
    {
      i--;
      buf[l]=p[i];
      i++;
      l++;
      buf[l]=p[i];
    }
      }
    */
    i++;
    l++;
  }
  mfree(p);
  remaking2();
//  Parsing();
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
  day=1;
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
          setstatus("Sending\n");
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
//        setstatus("Receiving\n");
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Tw6 Programma (c)Evilfox");
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
//    setstatus("\n");
//    SUBPROC((void *)create_connect);
    break;

  case RIGHT_BUTTON:
    if(day<=6)
    {
      day++;
    opening();
    }
    break;
    
    case LEFT_BUTTON:
    if(day>=2)
    {
      day--;
    opening();
    }
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

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"Tw6 Programma",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Opcijas"},
  {0x0001, 0x0000, (int)"Aizvert"},
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
  
//  utf8_2ws(ws, "PIRMDIENA",20);
//  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
//  AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,20);
  AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,20);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  ConstructEditControl(&ec,3,0x40,0,9920);
  AddEditControlToEditQend(eq,&ec,ma);  
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,LEFT_SOFT);
}

// menu

void download(GUI *data)
{
  setstatus(" \n");
  SUBPROC((void *)create_connect);
//  SUBPROC((void *)remaking);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

void open1(GUI *data)
{
  day=1;
  SUBPROC((void *)opening);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

void Get_about(GUI *data)
{
  ShowMSG(1,(int)"(c)Evilfox");
}

void exit(GUI *data)
{
  CloseCSM(MAINCSM_ID);
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,0,0,icon,(int)"Menu",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[4]=
{
  {NULL,(int)"Download New",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Open Programm",        LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"About",        LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Exit",        LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[4]={
  download,
  open1,
  Get_about,
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
  4
};

void MMenu(void)
{
  patch_header(&menuhdr);
  CreateMenu(0,0,&tmenu,&menuhdr,0,4,0,0);
}
