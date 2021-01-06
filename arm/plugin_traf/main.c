#include "..\inc\swilib.h"
#include "conf_loader.h"
char *GetExt(char *fname){return strrchr(fname,'\\')+1;}
const int minus11=-11;
unsigned int DMAINCSM_ID=0;

typedef struct{
  int ID;
  char InitPLG;
  
  void (*OnCreate)();
  void (*OnRedraw)(); 
  void (*OnKey)(int mess, int key); 
  void (*OnClose)();  
    
  void *next;
}AI_PLG;

AI_PLG *net_plg;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
char elfname[128];
int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
    else c-=8;
  c+=0x400;
  return (c); 
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

char clrRed[]={0xFF,0x00,0x00,0x64};
char clrBlack[]={0x50,0x50,0x50,0x64};
char clrWhite[]={0xFF,0xFF,0xFF,0x64};
char transparent[]={0x00,0x00,0x00,0x00};

extern const RECT RC;
extern const unsigned int FONT;
extern const int ALIGN;
extern const char COLOR[4];
extern const char FORMAT[128];
extern const int POS;

extern const RECT RC2;
extern const unsigned int FONT2;
extern const int ALIGN2;
extern const char COLOR2[4];
extern const char FORMAT2[128];
extern const int ENA_NET,ENA_PROV,SZ,SZ2;
extern const char ERR2[128],ERR1[128];



int start_traf=0;
void DrawWindow (){
  char msg[256];
  WSHDR *ws=AllocWS(256),*ws2=AllocWS(256);
  
if(ENA_NET)
  {
int all_traf=(*GetGPRSTrafficPointer())/1024;
if(SZ==1)all_traf/=1024;
if(!IsGPRSEnabled())ascii2ws(ws,ERR1);
else if(!IsGPRSConnected())ascii2ws(ws,ERR2);
else 
{
  sprintf(msg,FORMAT,all_traf);
  ascii2ws(ws,msg);
}
  DrawString (ws, RC.x, RC.y, RC.x2, RC.y2, FONT, ALIGN, COLOR,0);
  }
  if(ENA_PROV)
  {
    int all_traf=(*GetGPRSTrafficPointer());
    int now=all_traf-start_traf;
    if(SZ2==1)now/=1024;
  if(!IsGPRSEnabled())ascii2ws(ws,ERR1);
  else if(!IsGPRSConnected())ascii2ws(ws,ERR2);
  else 
  {
      sprintf(msg,FORMAT2,now/1024);
      ascii2ws(ws,msg);
  }
  DrawString (ws, RC2.x, RC2.y, RC2.x2, RC2.y2, FONT2, ALIGN2, COLOR2,0);
  }
  

  FreeWS(ws2);
  FreeWS(ws);
}

void OnKey (int mess, int key){
  
  if (mess==KEY_DOWN)
  {
    switch (key)
    {

    }
  }
  
}




extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    InitConfig(elfname);
  }
  
  return (1); 
}

static void maincsm_oncreate(CSM_RAM *data)
{
  
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void Close (){
  net_plg->InitPLG=0;
  SUBPROC((void *)Killer);
}

static void maincsm_onclose(CSM_RAM *csm)
{  
  Close();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Info-Plugin traffic");
}

void CloseThisCSM (){
  CloseCSM(DMAINCSM_ID);
}


int main (char *exename, AI_PLG *plg)
{
  sprintf(elfname,GetExt(exename));
  start_traf=*GetGPRSTrafficPointer();
  if (plg!=NULL){
    InitConfig(elfname);
    net_plg=plg;
    CSM_RAM *save_cmpc;
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();  
    LockSched();
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
    DMAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    
    net_plg->OnRedraw=DrawWindow;
    net_plg->OnKey=OnKey;
    net_plg->OnClose=CloseThisCSM;
    net_plg->InitPLG=1;
    net_plg->ID=POS;
    
    UnlockSched(); 
  }
   else{
    ShowMSG(1, (int)"NULL pointer");
    CloseThisCSM();
  }
  
  return 0;
}
