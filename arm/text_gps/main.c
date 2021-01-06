#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "string_works.h"

#define ipc_my_name "IGPS_IPC"
#define ipc_myplg_name "IGPS_IPC_PLG"

IPC_REQ *ipc_recv,ipc_send;

extern const RECT DATA_AREA;
extern const int SHOW_COUNTRY;
extern const int SHOW_AREA;
extern const int SHOW_CITY;
extern const int SHOW_STREET;
extern const int SHOW_LON;
extern const int SHOW_LAT;

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
//==============================================================================
void GenerateString(){
    char sss[256];
    snprintf(sss, 255, "%s%s%s%s\nШир: %s Дол: %s", 
                locate.Street,
                SHOW_CITY    ? locate.City    : "", 
                SHOW_AREA    ? locate.Area    : "", 
                SHOW_COUNTRY ? locate.Country : "", 
                SHOW_LAT ? locate.Lat : "", 
                SHOW_LON ? locate.Lon : ""

         );

ShowMSG(1,(int)"plg");
    ascii2ws(ews, sss);
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
  
  
  
    if (msg->msg==MSG_IPC)
      {
        ipc_recv=(IPC_REQ*)msg->data0;
        if(ipc_recv)
    if(strcmp_nocase(ipc_recv->name_to,ipc_myplg_name)==0)
   {

 memcpy(&locate,ipc_recv->data,sizeof(LOCATE));
 GenerateString();
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
  return (1);
}
extern void kill_data(void *p, void (*func_p)(void *));
static void maincsm_oncreate(CSM_RAM *data){
  ews=AllocWS(256);
  

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm){
  FreeWS(ews);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"microGPS_text_plg");
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
