#include "..\inc\swilib.h"
#ifdef NEWSGOLD
#include "conf_loader.h"
#endif

#define RECONNECT_TIME (216*120)

extern void kill_data(void *p, void (*func_p)(void *));

int OldGPRSstatus=0; //0 - offline, 1 - connecting, 2 - connected

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

#ifdef NEWSGOLD
char binary_profile[0x204];
extern const int ENA_GPRSD;
//NAP_PARAM_CONT *nap_container;
#define DEFAULT_DISK "4"
#else
#define LINKMANAGER 0x40DD
#define LMAN_DISCONNECT_REQ 0x800C
#define LMAN_CONNECT_REQ 0x800A
#define DEFAULT_DISK "0"
#endif

/*
Del by Kibab - §Ò§Ú§ß§Ñ§â§ß§í§Ö §á§â§à§æ§Ú§Ý§Ú §Ü§à§ß§æ§Ú§Ô§å§â§Ú§â§å§ð§ä§ã§ñ
*/

GBSTMR mytmr;
void reconnect(void)
{
  void do_connect(void);
  SUBPROC((void *)do_connect);
}

#ifdef NEWSGOLD
void do_connect(void)
{
  REGSOCKCEPID_DATA rsc;
  LMAN_DATA lmd;
  NAP_PARAM_CONT nap_container;
  NAP_PARAM_CONT *nc;
  // §±§â§à§Ó§Ö§â§Ú§Þ, §Ó§Ü§Ý§ð§é§×§ß §Ý§Ú GPRS. §¦§ã§Ý§Ú §ß§Ö§ä - §Õ§Ñ§Ý§î§ß§Ö§Û§ê§Ú§Ö §Ú§Ù§Ó§â§Ñ§ë§Ö§ß§Ú§ñ §Ò§Ö§ã§Þ§í§ã§Ý§Ö§ß§ß§í
  if(!IsGPRSEnabled())
  {
    OldGPRSstatus=0;
    return;
  }
  OldGPRSstatus=1;
  if(!ENA_GPRSD)
  {
    return; // §¦§ã§Ý§Ú §ß§Ö §â§Ñ§Ù§â§Ö§ê§×§ß §Ü§à§ß§ß§Ö§Ü§ä, §Ó§í§ç§à§Õ§Ú§Þ
  }
  //§µ§ã§ä§Ñ§ß§Ñ§Ó§Ý§Ú§Ó§Ñ§Ö§Þ §ã§à§Ö§Õ§Ú§ß§Ö§ß§Ú§Ö
  rsc._0x0080=0x0080;
  rsc._0xFFFF=0xFFFF;
  rsc._0x0000=0x0000;
  RegisterCepidForSocketWork(&rsc);
  //nap_container=nc=malloc(sizeof(NAP_PARAM_CONT));
  nc=&nap_container;
  nc->len=sizeof(NAP_PARAM_CONT);
  nc->ctx_napdef=&(nc->napdef);
  nc->zero=0;
  FillProfile((char*)(&binary_profile)); // ADDED BY Kibab
  memcpy(&nc->napdef,binary_profile,sizeof(CTX_NAPDEF));
  lmd.zero=0;
  lmd.native_profile=NULL;
  lmd._1=1;
  lmd._4=4;
  lmd._0=0;
  lmd.NapParameterContainer=nc;
  RequestLMANConnect(&lmd);
  //  GBS_StartTimerProc(&mytmr,RECONNECT_TIME*2,reconnect);
}
#else
void do_connect(void)
{
  unsigned int cur_profile;
  unsigned int cur_cepid;
  cur_cepid=GBS_GetCurCepid();
  cur_profile=GetCurrentGPRSProfile();
  ActivateDialUpProfile(cur_cepid,cur_profile);
  RegisterCepIdForCurProfile(cur_cepid,cur_profile,1);
  GBS_SendMessage(LINKMANAGER,LMAN_CONNECT_REQ,0,0x80,0xFFFF);
}
#endif


#ifndef NEWSGOLD
void do_disconnect(void)
{
  GBS_SendMessage(LINKMANAGER,LMAN_DISCONNECT_REQ,0,0,0);
}
#endif


//void LogWriter(const char *s)
//{
/*  TTime t;
  TDate d;
  char ss[100];
  unsigned int ul;
  int f=fopen(DEFAULT_DISK":\\ZBin\\etc\\GprsD.log",A_ReadWrite+A_Create+A_Append,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    GetDateTime(&d,&t);
    sprintf(ss,"%02d:%02d %02d-%02d-%04d: ",
            t.hour,t.min,d.day,d.month,d.year);
    fwrite(f,ss,strlen(ss),&ul);
    fwrite(f,s,strlen(s),&ul);
    fwrite(f,"\r\n",2,&ul);
    fclose(f,&ul);
  }*/
//}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  //char s[100];  
#ifdef NEWSGOLD
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern char config_name[];
    if (strcmp(config_name,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"GprsD config updated!");
      InitConfig();
    }
  }
#endif
  
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    int m=(int)msg->data0;
    if (m==LMAN_CONNECT_CNF)
    {
      OldGPRSstatus=2;
      //strcpy(s,"Session started!");
      //LogWriter(s);
      //ShowMSG(1,(int)s);
    }
    else
    {
      if ((m==LMAN_DISCONNECT_IND)||(m==LMAN_CONNECT_REJ_IND))
      {
        //if (m==LMAN_DISCONNECT_IND) strcpy(s,"Session closed!");
        //else
          //strcpy(s,"Can't start session!");
        //LogWriter(s);
        //ShowMSG(1,(int)s);
	if (m==LMAN_CONNECT_REJ_IND)
	{
	  //§¦§ã§Ý§Ú §ß§Ö §å§Õ§Ñ§Ý§à§ã§î §ã§ä§Ñ§â§ä§à§Ó§Ñ§ä§î §ã§Ö§ã§ã§Ú§ð, §ä§à §á§â§à§Ò§å§Ö§Þ §Ö§ë§Ö §â§Ñ§Ù §á§à §ä§Ñ§Û§Þ§Ö§â§å
	  GBS_StartTimerProc(&mytmr,RECONNECT_TIME,reconnect);
	}
	else
	{
	  OldGPRSstatus=0;
	}
      }
    }
  }
  if ((!OldGPRSstatus)&&IsGPRSEnabled())
  {
    //§£§Ü§Ý§ð§é§Ú§Ý§Ú §Ø§à§á§à§â§Ö§Ù
    GBS_DelTimer(&mytmr);
    SUBPROC((void*)do_connect);
  }
  if (!IsGPRSEnabled()) 
  {
    GBS_DelTimer(&mytmr);
    OldGPRSstatus=0;
  }
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  SUBPROC((void*)do_connect);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
#ifndef NEWSGOLD
  SUBPROC((void *)do_disconnect);
#endif
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"GprsD");
}

int main()
{
  CSM_RAM *save_cmpc;
  MAIN_CSM main_csm;
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched(); 
#ifdef NEWSGOLD  
  InitConfig();
#endif  
  return 0;
}

