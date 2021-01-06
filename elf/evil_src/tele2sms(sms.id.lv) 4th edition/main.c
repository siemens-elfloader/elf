#include "..\inc\swilib.h"
#include "strings.h"

#define ECINPUT 3
#define ECOUTPUT 5
#define BUFSIZE 86383

const int minus11=-11;
char Cookies[128];
char Dyna[128];
char Vultus[128];
char Thymbra[128];
char Tonsor[128];
char Rememdium[128];
char Edificium[128];
char Abeo[128];
char Quilibet[128];
char Synagoga[128];
char Silva[128];
char Code[128];
int janis;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
int traf=0;
GUI *ggui=0;

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

void get_answer(void);

void send_req(void)
{
  setstatus("send_req\n");
  char *str2=malloc(400);
  char *req_buf=malloc(strlen(str2)+800);
  sprintf(req_buf,"GET /send/ HTTP/1.1\n"
          "Referer: http://sms.id.lv/\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: sms.id.lv\n"
                    "Connection: Keep-Alive\n"
                      "\n"
                        );
  mfree(str2);
  send(sock,req_buf,strlen(req_buf),0);
  janis=1;
  get_answer();
  mfree(req_buf);
}

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
      sa.ip=htonl(IP_ADDR(85,254,196,154));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
      closesocket(sock);
  }
}

void send_req2(void)
{
  setstatus("send_req2\n");
//  EDITCONTROL ec;
//  ExtractEditControl(ggui,  ECINPUT, &ec);     
 // char *str1=ws2ascii(ec.pWS);
  char *str2=malloc(300);
//  mfree(str1);
  char *req_buf=malloc(strlen(str2)+800);
  sprintf(str2, "to=25524191&sms=chau+kaa+iet+ko+labu+dari&queue=on&dyna=%s&%s&%s&%s&%s&%s&%s&%s&%s&%s&single=insec&static=%s", Dyna,Vultus,Thymbra,Tonsor,Rememdium,Edificium,Abeo,Quilibet,Synagoga,Silva,Code);
  sprintf(req_buf,"POST /send/index.php HTTP/1.1\n"
          "Referer: http://sms.id.lv/send/\n"
            "Accept-Language: en-us\n"
              "Content-Type: application/x-www-form-urlencoded\n"
                "Accept-Encoding: gzip, deflate\n"
                  "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                    "Host: sms.id.lv\n"
                      "Content-Length: %d\n"
                        "Connection: Keep-Alive\n"
                          "Cache-Control: no-cache\n"
                            "Cookie: PHPSESSID=%s\n"
                              "\n"
                                "%s\n",
                                strlen(str2), Cookies,str2
                                  );
  mfree(str2);
  send(sock,req_buf,strlen(req_buf),0);
  WSHDR *ws3=ascii2ws(req_buf);
  EDIT_SetTextToEditControl(ggui, ECOUTPUT, ws3);
  FreeWS(ws3);
  janis=2;
  get_answer();
  mfree(req_buf);
}

void create_connect2(void)
{
//  setstatus("connecting2\n");
//  SOCK_ADDR sa;
//  connect_state=0;
  pbuf=0;
  send_req2();
//  sock=socket(1,1,0);
//  if (sock!=-1)
//  {
//    sa.family=1;
//    sa.port=htons(80);
//      sa.ip=htonl(IP_ADDR(85,254,196,154));
//    if (connect(sock,&sa,sizeof(sa))!=-1)
//    {
//      connect_state=4;
//    }
//    else
//      closesocket(sock);
//  }
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


void dyna_recieve()
{
  setstatus("dyna_recieve\n");
  char p1_2[]="eras=1";
  char p2_2[]="VALUE=";
  char p8_2[]="value=";
  char p3_2[]="'";
  char p4_2[]="\"";
  char *s_2,*s1_2,*s2_2, *s3_3;
  int len_2;
  if((s1_2=strstr(buf,p1_2))>0)
  {
    s1_2+=strlen(p1_2);
    if((s2_2=strstr(s1_2,p2_2))>0)
    {
      len_2=33;
      s_2=malloc(len_2+100);
      strncpy(s_2,s2_2+6,len_2);
      s3_3=malloc(100);
      if((s2_2=strstr(s_2,p3_2))>0)
      {
        strncpy(s3_3,s_2+1,32);
      }
      else
      {
        if((s2_2=strstr(s_2,p4_2))>0)
      {
        strncpy(s3_3,s_2+1,32);
      }
      else
        strncpy(s3_3,s_2+1,32);
      }
      s3_3[32]='\0';
      strcpy(Dyna, s3_3);
      mfree(s3_3);
      mfree(s_2);
    }
    else
    {
    if((s2_2=strstr(s1_2,p8_2))>0)
    {
      len_2=33;
      s_2=malloc(len_2+100);
      strncpy(s_2,s2_2+6,len_2);
      s3_3=malloc(100);
      if((s2_2=strstr(s_2,p3_2))>0)
      {
        strncpy(s3_3,s_2+1,32);
      }
      else
      {
        if((s2_2=strstr(s_2,p4_2))>0)
      {
        strncpy(s3_3,s_2+1,32);
      }
      else
        strncpy(s3_3,s_2+1,32);
      }
      s3_3[32]='\0';
      strncpy(Dyna, s3_3, 32);
      mfree(s3_3);
      mfree(s_2);
    }
    }
  }
  create_connect2();
}

void Start(GUI *data)
{
  setstatus(" \n");
  SUBPROC((void *)create_connect);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

void Remake()
{
  setstatus("remake\n");
  char first[20];
  int i=0;
  int j=0;
  char *ho;
  char homo[]="\"sec";
  while(Vultus[i]!='"')
  {
    first[i]=Vultus[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Vultus,homo);
  ho+=strlen(homo);
  sprintf(Vultus, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Thymbra[i]!='"')
  {
    first[i]=Thymbra[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Thymbra,homo);
  ho+=strlen(homo);
  sprintf(Thymbra, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Tonsor[i]!='"')
  {
    first[i]=Tonsor[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Tonsor,homo);
  ho+=strlen(homo);
  sprintf(Tonsor, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Rememdium[i]!='"')
  {
    first[i]=Rememdium[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Rememdium,homo);
  ho+=strlen(homo);
  sprintf(Rememdium, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Edificium[i]!='"')
  {
    first[i]=Edificium[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Edificium,homo);
  ho+=strlen(homo);
  sprintf(Edificium, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Abeo[i]!='"')
  {
    first[i]=Abeo[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Abeo,homo);
  ho+=strlen(homo);
  sprintf(Abeo, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Quilibet[i]!='"')
  {
    first[i]=Quilibet[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Quilibet,homo);
  ho+=strlen(homo);
  sprintf(Quilibet, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Synagoga[i]!='"')
  {
    first[i]=Synagoga[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Synagoga,homo);
  ho+=strlen(homo);
  sprintf(Synagoga, "sec%s=%s", ho, first);
  i=0;
  j=0;
  while(Silva[i]!='"')
  {
    first[i]=Silva[i];
     i++;
     j++;
  }
  first[j]=0;
  ho=strstr(Silva,homo);
  ho+=strlen(homo);
  sprintf(Silva, "sec%s=%s", ho, first);
  dyna_recieve();
}

  
int Parsing()
{
  setstatus("parsing\n");//!
  char p1[]="PHPSESSID=";
  char p2[]="; path=/";
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
      strcpy(Cookies, s);
      mfree(s);
    }
  }
  char p1_3[]="type=\"hidden\" value=\"";
  char p2_3[]="\">";
  char *s_3,*s1_3,*s2_3, *buf2;
  int len_3;
  if((s1_3=strstr(buf,p1_3))>0)
  {
    s1_3+=strlen(p1_3);
    if((s2_3=strstr(s1_3,p2_3))>0)
    {
      buf2=strstr(s1_3,p2_3);
      buf2+=strlen(p2_3);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Vultus, s_3);
      mfree(s_3);
    }
  }
  char p1_4[]="value=\"";
  char p2_4[]="\">";
  char p1_45[]="value=\"code";
  char p2_45[]="\"";
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Thymbra, s_3);
      mfree(s_3);
      DirectRedrawGUI();
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Tonsor, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Rememdium, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Edificium, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Abeo, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Quilibet, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Synagoga, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_4))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_4))>0)
    {
      buf2=strstr(buf2,p2_4);
      buf2+=strlen(p2_4);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Silva, s_3);
      mfree(s_3);
    }
  }
  if((s1_3=strstr(buf2,p1_45))>0)
  {
    s1_3+=strlen(p1_4);
    if((s2_3=strstr(s1_3,p2_45))>0)
    {
      buf2=strstr(buf2,p2_45);
      buf2+=strlen(p2_45);
      len_3=s2_3-s1_3;
      s_3=malloc(len_3+1);
      strncpy(s_3,s1_3,len_3);
      s_3[len_3]='\0';
      strcpy(Code, s_3);
      mfree(s_3);
      Remake();
//      char *gatavs=malloc(400);
//      sprintf(gatavs, "%s", Code);
//      WSHDR *ws2=ascii2ws(gatavs);
//      mfree(gatavs);
//      EDIT_SetTextToEditControl(ggui, ECOUTPUT, ws2);
//      FreeWS(ws2);
//      DirectRedrawGUI();
      return 1;
    }
  }
  setstatus("Error\n");
  return 0;
}
//      char *gatavs=malloc(400);
//      sprintf(gatavs, "%s, %s, %s, %s, %s, %s, %s, %s, %s", Vultus, Thymbra, Tonsor, Rememdium, Edificium, Abeo, Quilibet, Synagoga, Silva);
//      WSHDR *ws2=ascii2ws(gatavs);
//      mfree(gatavs);
//      EDIT_SetTextToEditControl(ggui, ECOUTPUT, ws2);
//      FreeWS(ws2);
//      DirectRedrawGUI();
//      Remake();
//      return 1;
//  setstatus("Error\n");
//  return 0;

int Parsing2()
{
  setstatus("parsing2\n");
  char p1z[]="magenta";
  char p2z[]="</span>";
  char *sz,*s1z,*s2z;
  int lenz;
  if((s1z=strstr(buf,p1z))>0)
  {
    s1z+=strlen(p1z);
    if((s2z=strstr(s1z,p2z))>0)
    {
      lenz=s2z-s1z;
      sz=malloc(lenz+1);
      strncpy(sz,s1z,lenz);
      sz[lenz]='\0';
  char *gatavs2=malloc(100);
  WSHDR *ws2=ascii2ws(sz);
  mfree(gatavs2);
  EDIT_SetTextToEditControl(ggui, ECINPUT, ws2);
  FreeWS(ws2);
  DirectRedrawGUI();
  return 1;
    }
  }
  return 0;
}

void get_answer()
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
      if(janis==1)
      {
      Parsing();
      }
      if(janis==2)
      {
        Parsing2();
      }
    }
  }
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
        if (connect_state==4)
        {
          setstatus("Connected_2\n");
          //Если посылали запрос
          SUBPROC((void *)send_req2);        
        }
        else
          {
          setstatus("Error\n");
          SUBPROC((void *)create_connect); 
          }
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
        if (connect_state==5)
        {
          setstatus("Reading_2\n");
          //Если посылали send
          SUBPROC((void *)get_answer);
        }
        else
        {
          SUBPROC((void *)create_connect);
          setstatus("Error\n");
        }
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
        
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
//        if(janis==1)
//        {
//        if (connect_state) SUBPROC((void *)end_socket);
//        setstatus("Working_Rec_info\n");
//       connect_state=3;
//        Parsing();
//        sock=-1;
//        }
//        else
//        {
        if(janis==2)
        {
        if (connect_state) SUBPROC((void *)end_socket);
        setstatus("Working_Rec_info\n");
        connect_state=3;
        Parsing2();
        sock=-1;
        }
//        }
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
