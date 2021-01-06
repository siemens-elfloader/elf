#include "..\inc\swilib.h"
#include "string_works.h"
#include "conf_loader.h"

extern const char fname[128],name[2],lang[3];
extern const int sizex,sizey,zoom,frmt,map_type,color;
#define BUFFSIZE 0x20000
#define ipc_my_name "IGPS_IPC"
#define ipc_myplg_name "IGPS_IPC_PLG"
const char *key="ABQIAAAAqV2OGt7lLeOqPjzPlWRjDBQtQh0ezKOPW00oHzqZrcnTyszRtRTn0Uj75S3FLNMnfvKIsHobfsjW7A";
IPC_REQ *ipc_recv,ipc_send;
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
unsigned int old_gprs_state[2]={0,0};

int sock;
int connect_state;
char *buf=0;
int pbuf=0;


GBSTMR reconnect_tmr;

void create_connect(void);

void do_start_connection(void){
    SUBPROC((void *)create_connect);
}

void StartGPRS(void){
  GPRS_OnOff(1,1);
  do_start_connection();
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
      sa.ip=htonl(IP_ADDR(74,125,77,99));
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
char *maptype[10]={"roadmap","mobile","satellite", "terrain", "hybrid"};
char *clr[3]={"red","green","blue"};
char *format[3]={"png","jpg","gif"};
char req_buf[512];
void send_req(void){
  snprintf(req_buf,511, "GET /staticmap?maptype=%s&format=%s&center=%s,%s&zoom=%d&size=%dx%d&key=%s&markers=%s,%s,%s%s&hl=%s"
    " HTTP/1.0\r\nHost: maps.google.com\r\n\r\n",
maptype[map_type],
format[frmt],
locate.Lat,
locate.Lon,
zoom,
sizex,
sizey,
key,
locate.Lat,
locate.Lon,
clr[color],
name,
lang
);  
send(sock,req_buf,strlen(req_buf),0);
connect_state=2;
 if (!buf){
    buf=malloc(BUFFSIZE);
    pbuf=0;
  }
}

void end_socket(void){
 // if(type_data==MAP)
    
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
       if ((i<0)){
     end_socket();
   }
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
  char sz[32];
  //Улица
  locate.Street[0]=0;
  if(tag=findtag(buf,"Content-Length:")){
    valuetag(tag, sz, sizeof(sz)-1);
  }
  int sizeofimg=StrToInt(sz,0);
  int headsize=pbuf-sizeofimg;
  char *bf=malloc(sizeofimg);
  memcpy(bf, buf+headsize,sizeofimg);
  char filename[256];
  sprintf(filename,"%s.",fname,format[frmt]);
  int f = fopen("0:\\map.png",A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
  fwrite(f,bf,sizeofimg,0);
  fclose(f,0);
  mfree(bf);
  mfree(buf);
  buf=0;
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
    }
  }
      if (msg->msg==MSG_IPC)
      {
        ipc_recv=(IPC_REQ*)msg->data0;
        if(ipc_recv)
    if(strcmp_nocase(ipc_recv->name_to,ipc_myplg_name)==0)
   {

 memcpy(&locate,ipc_recv->data,sizeof(LOCATE));
 do_start_connection();
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

          break;
      }
    }
  }
  return (1);
}
extern void kill_data(void *p, void (*func_p)(void *));
static void maincsm_oncreate(CSM_RAM *data){
  
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm){
  mfree(buf);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"microGPS_map_plg");
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
    ipc_send.name_to=ipc_my_name;
  ipc_send.name_from=ipc_myplg_name;
  ipc_send.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&ipc_send); 
  return 0;
}
