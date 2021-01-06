#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "string_works.h"

#define BUFFSIZE 0x200

extern const RECT DATA_AREA;
extern const int SHOW_COUNTRY;
extern const int SHOW_AREA;
extern const int SHOW_CITY;
extern const int SHOW_STREET;
 const int SHOW_LON;
 const int SHOW_LAT;

typedef struct{
  char
    Lat[32],
    Lon[32],
    Country[32],
    Area[32],
    City[32],
    Street[32];
}LOCATE;
LOCATE locate;

WSHDR *ews;
int sock;
int connect_state;
char *buf=0;
int pbuf=0;
RAMNET *ramnet;
unsigned short old_ci=0;
unsigned int old_gprs_state[2]={0,0};

GBSTMR update_tmr;
GBSTMR reconnect_tmr;

void create_connect(void);

void do_start_connection(void){
  if (old_ci!=ramnet[0].ci){
    SUBPROC((void *)create_connect);
  }else{
    GBS_DelTimer(&update_tmr);
    GBS_StartTimerProc(&update_tmr, (216*60), do_start_connection); 
  }
}

void StartGPRS(void){
  GPRS_OnOff(1,1);
  GBS_StartTimerProc(&reconnect_tmr,216*60,do_start_connection);
}

void create_connect(void){
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;

  GBS_DelTimer(&reconnect_tmr);
  
  if (!IsGPRSEnabled()){
    StartGPRS();
    if (!old_gprs_state[1]){
      old_gprs_state[0] = 0;
      old_gprs_state[1] = 1;
    }
    return;
  }else{
    if (!old_gprs_state[1]){
      old_gprs_state[0] = 1;
      old_gprs_state[1] = 1;
    }    
  }
  
  sock=socket(1,1,0);
  if (sock!=-1){
    sa.family=1;
    sa.port=htons(80);
    sa.ip=htonl(IP_ADDR(78,24,218,208));
    if (connect(sock,&sa,sizeof(sa))!=-1){
      connect_state=1;
      REDRAW();
    }else{
      closesocket(sock);
      sock=-1;
      GBS_StartTimerProc(&reconnect_tmr,216*60,do_start_connection);
    }
  }else{
    //Не осилили создания сокета, закрываем GPRS-сессию
    GPRS_OnOff(0,1);
    // и через 30 секунд запускаем жопорез
    GBS_StartTimerProc(&reconnect_tmr, 216*60, StartGPRS);    
  }
}

char req_buf[100];
void send_req(void){
  char *p=((char*)ramnet)-11;
  char cc1=*p;
  char cc2=*(p+1);
  char nc=*(p+2);

  snprintf(req_buf,99, "GET /w/g.php?mcc=%i&mnc=%i&lac=%i&ci=%i"
    " HTTP/1.0\r\nHost: igps.boba.su\r\n\r\n",
    (cc1&0x0F)*100+(cc1>>4)*10+(cc2&0x0F),
    (nc&0x0F)*10+(nc>>4),
    ramnet[0].lac,
    ramnet[0].ci
  );  
 
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;

  if (!buf){
    buf=malloc(BUFFSIZE);
    pbuf=0;
  }
}

void end_socket(void){
  if (sock>=0){
    shutdown(sock,2);
    closesocket(sock);
    buf[pbuf]=0;
    // выключаем жопорез, если он изначально был выключен
    if (!old_gprs_state[0]){
      GPRS_OnOff(0,1);
    }
  }
}

void get_answer(void){
  int i=recv(sock,buf+pbuf,BUFFSIZE-1-pbuf,0);
  pbuf+=i;
  if ((i<0)||(pbuf>=BUFFSIZE-1)){
    end_socket();
  }
}

//==============================================================================
void GenerateString(){
    char sss[128];
    snprintf(sss, 127, "%s%s%s%s%s%s", 
                locate.Street,
                SHOW_CITY    ? locate.City    : "", 
                SHOW_AREA    ? locate.Area    : "", 
                SHOW_COUNTRY ? locate.Country : "", 
                SHOW_LAT ? locate.Lat : "", 
                SHOW_LON ? locate.Lon : ""

         );
    ascii2ws(ews, sss);
}

char *valuetag(char *src,char *dst, int maxlen){
 if (!src) return 0;
 if (!*src) return src;
 int c=0;
// dst=dst+strlen(dst);
 while (*src!='\n' && *src!='"' && *src!=0 && c < maxlen){
  *dst++=*src++;
  c++;
 }
 *dst=0;
 return src;
}

char * findtag(char *src, char *tag){
 char *s;
 if (s=strstr(src,tag))
  return s+strlen(tag);
 return s;
}

void Parsing(){
  if ((!buf)||(!pbuf)) return; 
  if (!strstr(buf,"200 OK")) return;
  
  char *tag=0;  
  //Улица
  locate.Street[0]=0;
  if(tag=findtag(buf,"STREET:")){
    valuetag(tag, locate.Street, sizeof(locate.Street)-1);
  }

  //Город
  locate.City[0]='\n';
  if (tag=findtag(buf,"CITY:")){
    valuetag(tag, locate.City+1, sizeof(locate.City)-2);
  }

  //Область
  locate.Area[0]='\n';
  if (tag=findtag(buf,"AREA:")){
    valuetag(tag, locate.Area+1, sizeof(locate.Area)-2);
  }

  //Страна
  locate.Country[0]='\n';
  if (tag=findtag(buf,"COUNTRY:")){
    valuetag(tag, locate.Country+1, sizeof(locate.Country)-2);
  }
  //Долгота
  locate.Lon[0]=0;
  if(tag=findtag(buf,"LON:")){
    valuetag(tag, locate.Lon, sizeof(locate.Lon)-1);
  }  //широта
  locate.Lat[0]=0;
  if(tag=findtag(buf,"LAT:")){
    valuetag(tag, locate.Lat, sizeof(locate.Lat)-1);
  }
  mfree(buf);
  buf=0;
    
  if (tag) GenerateString();
}

//==============================================================================

const int minus11=-11;

typedef struct{
  CSM_RAM csm;
}MAIN_CSM;



int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg){
  if(msg->msg == MSG_RECONFIGURE_REQ) {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){
      InitConfig();
      GenerateString();
      ShowMSG(1,(int)"microGPS config updated!");
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);    
  if (icsm&&IsGuiOnTop(idlegui_id)&&!IsScreenSaver()/*&&IsUnlocked()*/){ //Если IdleGui на самом верху
    GUI *igui=GetTopGUI();
    if (igui){ //И он существует
#ifdef ELKA
                {
//      void *canvasdata=BuildCanvas();
#else
      void *idata=GetDataOfItemByID(igui,2);
      if (idata){
//        void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif        
        DrawString(ews, DATA_AREA.x, DATA_AREA.y, DATA_AREA.x2, DATA_AREA.y2, FONT_SMALL,
	           0x20 + (1 << 1),GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(1));
      }
    }  
  }    
  if (msg->msg==MSG_HELPER_TRANSLATOR){
    if ((int)msg->data1==sock){
      //Если наш сокет
      switch((int)msg->data0){
        case ENIP_SOCK_CONNECTED:
          if (connect_state==1){
            //Если посылали запрос
            SUBPROC((void *)send_req);
          }
          break;
        case ENIP_SOCK_DATA_READ:
          if (connect_state==2){
            //Если посылали send
            SUBPROC((void *)get_answer);
          }
          break;
        case ENIP_SOCK_REMOTE_CLOSED:
          //Закрыт со стороны сервера
          if (connect_state)
            SUBPROC((void *)end_socket);
          break;
        case ENIP_SOCK_CLOSED:
          //Закрыт вызовом closesocket
          SUBPROC((void *)Parsing);
          GBS_DelTimer(&update_tmr);
          GBS_StartTimerProc(&update_tmr, (216*60)*10, do_start_connection); 
          old_ci=ramnet[0].ci;
          old_gprs_state[1] = 0;
          connect_state=0;
          sock=-1;
          break;
      }
    }
  }
  return (1);
}
extern void kill_data(void *p, void (*func_p)(void *));
static void maincsm_oncreate(CSM_RAM *data){
  ews=AllocWS(128);
  ramnet=RamNet();
  do_start_connection();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm){
  mfree(buf);
  FreeWS(ews);
  GBS_DelTimer(&update_tmr);
  GBS_DelTimer(&reconnect_tmr);
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct{
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

static void UpdateCSMname(void){
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"microGPS");
}

int main(){
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

  return 0;
}
