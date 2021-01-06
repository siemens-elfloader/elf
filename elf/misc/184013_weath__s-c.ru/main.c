#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

/*
//#define NEWSGOLD
#ifdef NEWSGOLD
 #define FONT 12
 char DEFAULT_DISC[]"4";
#else
 #define  FONT 7
 char DEFAULT_DISC[]="0";
#endif*/
 int FONT=11;// for NSG
// char DEFAULT_DISC[]="0";

#include "menu"


const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;



int y=0;
int x=0;
int ok=0;
int succ=0;
int mode;
long int traff;


CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);
int sock;
int connect_state;
char buf[16384];
char logbuf[16384];
int pbuf;
GBSTMR mytmr;

extern const unsigned int TID;




#define IPC_XTASK_NAME "XTask"
#define IPC_XTASK_IDLE 1
#define IPC_XTASK_SHOW_CSM 2

const char ipc_my_name[1]=" ";
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;




extern const unsigned int CLOUD_ICON_X;
extern const unsigned int CLOUD_ICON_Y;

extern const unsigned int FALL_ICON_X;
extern const unsigned int FALL_ICON_Y;

extern const unsigned int TEMP_ICON_X;
extern const unsigned int TEMP_ICON_Y;


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
  
  int pressure;
  int temp;
  int wind_min;
  int wind_max;
short wind_dir;
  
  int relwet;
  //int relvet_max;
  
  int heat;
}WEATHER;


WSHDR *dst;

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
if(*src>='0' && *src<='9')
*dest+=((*src)-'0');
if(*src>='A' && *src<='F')
 *dest+=((*src)-('A'-0xA));
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
    weath[j].pressure=atoi(pre);
    
    pre=strstr(fcstr[j],"TEMPERATURE max=")+17;
    weath[j].temp=atoi(pre);
    
    pre=strstr(fcstr[j],"WIND min=")+10;
    weath[j].wind_min=atoi(pre);
    
    pre=strstr(strstr(fcstr[j],"WIND min="),"max=")+5;
    weath[j].wind_max=atoi(pre);
    
    pre=strstr(fcstr[j],"direction=")+10;
    weath[j].wind_dir=atoi(pre);
    
    pre=strstr(fcstr[j],"RELWET max=")+12;
    weath[j].relwet=atoi(pre);
    
    pre=strstr(fcstr[j],"HEAT min=")+10;
    weath[j].heat=atoi(pre);
    
    
    
    

  }
         
         
 traff=*GetGPRSTrafficPointer()-traff;        
url_decode(town.name,strstr(buf,"sname=")+7);
}



void DrawWeather()
{ 
  //char cl_1[4]={128,128,128,25};
  //char cl_2[4]={128,128,128,65};
 
 // DrawRoundedFrame(0,0,131,175,3,3,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  DrawImg(0,ScreenH()-105,(int)"4:\\Zbin\\img\\weather\\bg.png");
  
  
  
  
  //DrawRoundedFrame(ScreenW()-40,ScreenH()-90,ScreenW()-5,ScreenH()-10,0,0,0,cl_2,cl_1);
  
  //DrawRoundedFrame(ScreenW()-23,ScreenH()-55-weath[y].temp,ScreenW()-21,ScreenH()-12,5,5,5,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
  
  WSHDR *ws = AllocWS(1024);
  char *todlist[4]=
  {
    "ночью",
    "утром",
    "днем",
    "вечером"
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
    "сев.",
    "сев.-вост.",
    "вост.",
    "юго-вост.",
    "южный",
    "юго-зап.",
    "зап.",
    "сев.-зап."
  };
  
  /*char *pics[11]=
  {
    "0:\\Zbin\\img\\weather\\clear.png",
    "0:\\Zbin\\img\\weather\\some_clouds.png",
    "0:\\Zbin\\img\\weather\\clouds.png",
    "0:\\Zbin\\img\\weather\\gloom.png",
    
    "0:\\Zbin\\img\\weather\\rain.png",
    "0:\\Zbin\\img\\weather\\heavy_rain.png",
    "0:\\Zbin\\img\\weather\\snow.png",
    "0:\\Zbin\\img\\weather\\snow_2.png",
    "0:\\Zbin\\img\\weather\\storm.png",
    "0:\\Zbin\\img\\weather\\n-a.png"
    "0:\\Zbin\\img\\weather\\null.png" 
  };*/
  
  char *pics[11]=
  {
    "4:\\Zbin\\netutils\\weather\\00.png",
    "4:\\Zbin\\netutils\\weather\\01.png",
    "4:\\Zbin\\netutils\\weather\\02.png",
    "4:\\Zbin\\netutils\\weather\\03.png",
    
    "4:\\Zbin\\netutils\\weather\\04.png",
    "4:\\Zbin\\netutils\\weather\\05.png",
    "4:\\Zbin\\netutils\\weather\\06.png",
    "4:\\Zbin\\netutils\\weather\\07.png",
    "4:\\Zbin\\netutils\\weather\\08.png",
    "4:\\Zbin\\netutils\\weather\\09.png",
    "4:\\Zbin\\netutils\\weather\\10.png" 
  };

  
  
  DrawImg(3,ScreenH()-123,(int)pics[weath[y].fallout]);
  DrawImg(22,ScreenH()-123,(int)pics[weath[y].cloudiness]);
  
  char *l="ожидается апокалипсис"; 
  
  /*if( y!=0) {DrawRoundedFrame(0,0,16,16,1,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));}
  if( y!=1) {DrawRoundedFrame(16,0,32,16,1,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));}
  if( y!=2) {DrawRoundedFrame(32,0,48,16,1,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));}
  if( y!=3) {DrawRoundedFrame(48,0,64,16,1,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));}
  DrawRoundedFrame(64,0,131,16,1,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));*/
     
    if(weath[y].fallout==4 && weath[y].rpower==0) l="Возможен дождь";
    if(weath[y].fallout==4 && weath[y].rpower==1) l="Дождь";
    
    if(weath[y].fallout==5 && weath[y].rpower==0) l="Возможен ливень";
    if(weath[y].fallout==5 && weath[y].rpower==0) l="Ливень";
    
    if(weath[y].fallout==6 && weath[y].rpower==0) l="Возможен снег";
    if(weath[y].fallout==6 && weath[y].rpower==0) l="Снег";
    
    if(weath[y].fallout==7 && weath[y].rpower==0) l="Возможен снег";
    if(weath[y].fallout==7 && weath[y].rpower==0) l="Снег";
    
    if(weath[y].fallout==8 && weath[y].spower==0) l="Возможна гроза";
    if(weath[y].fallout==8 && weath[y].spower==0) l="Гроза";
    
    if(weath[y].fallout==9 && weath[y].rpower==0) l="N/A";
    if(weath[y].fallout==10 && weath[y].rpower==0) l="Без осадков";
    
   
  
  wsprintf(ws,"%.2d\xB0%t,%.2d\xB0%t",town.lat,"Ш.",town.lon,"Д.");
  DrawString(ws,66,2,600,172,7,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  
TDate date; TTime time; 
GetDateTime(&date,&time); 
  wsprintf(ws,"< %i/4 %i.%02i, %t >",y+1,weath[y].day,weath[y].month,todlist[weath[y].tod]);
  //wsprintf(ws,"< %i/4 %t %t >",y+1,((weath[y].day!=date.day)?"Сегодня":"Завтра"),todlist[weath[y].tod]);
  DrawString(ws,2,5,129,172,FONT+1,34,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1)); 
  
 // wsprintf(ws," %i-%i\xB0\x43\r%i-%i %t \r%t\r%t\r%t%t %i-%i %t\n%t: %i-%i%%\n%t:%i\xB0",weath[y].temp,weath[y].temp+2,weath[y].pressure,weath[y].pressure+2,"мм.рт.ст",cloudness[weath[y].cloudiness],l, "Ветер:", wind[weath[y].wind_dir],weath[y].wind_min,weath[y].wind_min,"м/с","Влажность",weath[y].relwet,weath[y].relwet+5,"Комфорт",weath[y].heat);
 // DrawString(ws,20,ScreenH()-100,131,172,7,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1)); 
  
  wsprintf(ws,"%i-%i\xB0\x43 %t:%i\xB0",weath[y].temp,weath[y].temp+2,"Комфорт",weath[y].heat);
  DrawString(ws,20,ScreenH()-100,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==0)?3:1)); 
  
  wsprintf(ws,"%i-%i %t",weath[y].pressure,weath[y].pressure+2,"мм.рт.ст");
  DrawString(ws,20,ScreenH()-85,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==1)?3:1)); 
  
  wsprintf(ws,"%t ",cloudness[weath[y].cloudiness]);
  DrawString(ws,20,ScreenH()-70,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==2)?3:1)); 
  
  wsprintf(ws,"%t  ",l);
  DrawString(ws,20,ScreenH()-55,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==3)?3:1)); 
  
  wsprintf(ws,"%t%t %i-%i %t","Ветер:", wind[weath[y].wind_dir],weath[y].wind_min,weath[y].wind_max,"м/с");
  DrawString(ws,20,ScreenH()-40,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==4)?3:1)); 
  
  wsprintf(ws,"%t: %i-%i%%","Влажность",weath[y].relwet,(weath[y].relwet+5>100)?100:weath[y].relwet+5);
  DrawString(ws,20,ScreenH()-25,131,172,FONT,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex((x==5)?3:1)); 
  
  //wsprintf(ws,"-%s",town.name);
  //DrawString(ws,20,30,131,172,7,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1)); 
 
  
  FreeWS(ws);
  
  
}



void DrawWait()
{
  DrawImg(0,0,(int)"4:\\Zbin\\netutils\\weather\\wait.png");
  WSHDR *ws = AllocWS(1024);
    wsprintf(ws,"%s",logbuf);
    DrawString(ws,2,5,127,172,FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

void WrongTID()
{
  
  DrawImg(0,0,(int)"4:\\Zbin\\netutils\\weather\\wait.png"); 
  WSHDR *ws = AllocWS(1024);
    wsprintf(ws,"%t","Нулевой ID города");
    DrawString(ws,2,5,127,172,FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
}

void DrawCity()
{
  //DrawRoundedFrame(0,0,131,175,3,3,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  //DrawImg(0,ScreenH()-105,(int)"0:\\Zbin\\img\\weather\\bg.png");
   DrawImg(0,0,(int)"4:\\Zbin\\netutils\\weather\\wait.png");
 WSHDR *ws = AllocWS(1024); 
 
  wsprintf(ws,"%t\n%t:%i\n %t:%i\xB0\x43\n %t:%i\xB0\x43\n",town.name,"ID города",town.tid,"Долгота",town.lon,"Широта",town.lat);
  DrawString(ws,2,5,127,172,FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
 FreeWS(ws);
}

void OnRedraw(MAIN_GUI *data)
{       
   DrawRoundedFrame(0,0,131,175,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  
   if(TID==0) {WrongTID();}

   if(succ==0 && TID!=0) {  DrawWait();    }
   if(succ==1 && TID!=0 && mode==0) {  DrawWeather(); }
   if(succ==1 && TID!=0 && mode==1) {  DrawCity(); } 
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
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON: return(1);
      
    //case 1:  /*csm->gui_id=*/create_menu(); REDRAW(); break;
    //case 1: mode=!mode; REDRAW(); break;
    case '2': case UP_BUTTON:    x=(x+6)%7; REDRAW(); break;
    case '4': case LEFT_BUTTON:  y=(y+3)%4; REDRAW(); break;
    case '6': case RIGHT_BUTTON: y=(y+1)%4; REDRAW(); break;
    case '8': case DOWN_BUTTON:  x=(x+1)%7; REDRAW(); break;

    case '*': DrawCity(); break;
    
    
    case '#':{  gipc.name_to=ipc_xtask_name;
                gipc.name_from=ipc_my_name;
                gipc.data=0;
                GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);} break;
    
    case GREEN_BUTTON:  SUBPROC((void *)create_connect); break;
    
    default: REDRAW(); break;
    }
    
  }
  return(0);
}
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}
#else
extern void kill_data(void *p, void (*func_p)(void *));

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif

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
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
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
  MAINGUI_ID=csm->gui_id;
  
    //GBS_StartTimerProc(&mytmr,ONE_SECOND,do_start_connection);
  SUBPROC((void *)create_connect);
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
  GBS_DelTimer(&mytmr);
    FreeWS(dst);
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
          strcat(logbuf,"Connected\n"); REDRAW();
          //Если посылали запрос
          SUBPROC((void *)send_req);
          REDRAW();
        }
        else
        {
          strcat(logbuf,"Error, try again..\n"); SUBPROC((void *)create_connect); REDRAW();
        }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          strcat(logbuf,"Reading\n"); REDRAW();
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
        strcat(logbuf,"Receiving\n"); REDRAW();
        succ=1;
        //SaveXML();
        //ProcessXML();
        Parsing();
        connect_state=0;
        sock=-1;
        break;
      }
    }
    
  }
  
    char *pics[11]=
  {
    "4:\\Zbin\\netutils\\weather\\00.png",
    "4:\\Zbin\\netutils\\weather\\01.png",
    "4:\\Zbin\\netutils\\weather\\02.png",
    "4:\\Zbin\\netutils\\weather\\03.png",
    
    "4:\\Zbin\\netutils\\weather\\04.png",
    "4:\\Zbin\\netutils\\weather\\05.png",
    "4:\\Zbin\\netutils\\weather\\06.png",
    "4:\\Zbin\\netutils\\weather\\07.png",
    "4:\\Zbin\\netutils\\weather\\08.png",
    "4:\\Zbin\\netutils\\weather\\09.png",
    "4:\\Zbin\\netutils\\weather\\10.png" 
  };

  
  

  
 
  {

    //Нарисуем иконочку моего статуса
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui && succ==1) //И он существует
      {
        

        
#ifdef ELKA
	//	{
	void *canvasdata=BuildCanvas();
#else
	void *idata=GetDataOfItemByID(igui,2);
	if (idata)
	{
	  void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif
	
          //DrawCanvas(canvasdata,idle_x,idle_y,idle_x+(GetImgWidth(gps_icon)),idle_y+(GetImgHeight(gps_icon)),1); 
//DrawRoundedFrame(IDLEICON_X,IDLEICON_Y,IDLEICON_X+70,IDLEICON_Y+20,4,4,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));

  DrawImg(FALL_ICON_X,FALL_ICON_Y,(int)pics[weath[y].fallout]);
  DrawImg(CLOUD_ICON_X,CLOUD_ICON_Y,(int)pics[weath[y].cloudiness]);
  
          WSHDR *wsx = AllocWS(64);
          wsprintf(wsx,"%i\xB0\x43",weath[y].temp+1);
          DrawString(wsx,TEMP_ICON_X,TEMP_ICON_Y,TEMP_ICON_X+100,TEMP_ICON_Y+20,11,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
	  FreeWS (wsx);
        } }
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Weather Forecast");
  FreeWS(ws);
}


int main(char *exename, char *fname)
{
  traff=*GetGPRSTrafficPointer();
  InitConfig();
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();

  
  return 0;
}

