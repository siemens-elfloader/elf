#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "rect_patcher.h"
#include "swaper.h"
#include "xtask_ipc.h"
void maincsm_oncreate(CSM_RAM *data),restoregui();
extern void kill_data(void *p, void (*func_p)(void *));
void ClearNL();
const int minus11=-11; // стремная константа =)
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int show_daemons,dial_n;
CSM_RAM *under_idle;
extern const int elf_run_on,xtask_kill;
extern const char elf_run[];
extern const char UNDER_IDLE_CONSTR[];
extern const char *successed_config_filename;
extern const unsigned int CALL_BUTTON;
extern const int LONG_P;
CSM_DESC maincsm;



typedef struct
{
  void *next;
  WSHDR *name;
  void *p;
  int is_daemon;
} NAMELIST;

NAMELIST * volatile nltop;
NAMELIST *nl[32];



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
NAMELIST *get_nlitem(int curitem)
{
  NAMELIST *nl;
  nl=nltop;
  int i=0;
  while(nl)
  {
    if (i==curitem) break;
    i++;
    nl=nl->next;
  }
  return(nl);
}
void run()
{
  if(elf_run_on){
    WSHDR *ws=AllocWS(32);
    str_2ws(ws,elf_run,128);
    ExecuteFile(ws,0,0);
    FreeWS(ws);  
  }
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////Main Xtask Features//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
CSM_RAM *GetUnderIdleCSM(void)
{
  CSM_RAM *u;
  CSM_DESC *UnderIdleDesc;
  if (strlen((char *)UNDER_IDLE_CONSTR)==8)
  {
    UnderIdleDesc=(CSM_DESC *)strtoul((char *)UNDER_IDLE_CONSTR,0,0x10);
  }
  else
  {
    UnderIdleDesc=((CSM_RAM *)(FindCSMbyID(CSM_root()->idle_id))->prev)->constr;
    sprintf((char *)UNDER_IDLE_CONSTR,"%08X",UnderIdleDesc);
    SaveConfigData(successed_config_filename);
  }
  LockSched();
  u=CSM_root()->csm_q->csm.first;
  while(u && u->constr!=UnderIdleDesc) u=u->next;
  UnlockSched();
  return u;
}
int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}



char csm_text[32768];

const char percent_t[]="%t";

void ClearNL(void)
{
  int i;
  LockSched();
  nltop=0;
  UnlockSched();
  for(i=0;i<dial_n;i++){
    FreeWS(nl[i]->name);
  }
}

void AddNL(WSHDR *ws, int is_daemon)
{
  NAMELIST *nnl=malloc(sizeof(NAMELIST));
  nnl->name=ws;
  nnl->next=0;
  nnl->is_daemon=is_daemon;
  LockSched();
  if (!nltop)
  {
    nltop=nnl;
  }
  else
  {
    nnl->next=nltop;
    nltop=nnl;
  }
  UnlockSched();
}

char *find_name(CSM_RAM *csm)
{
  char s[40];
  char *p;
  static char u[40];

  CSM_DESC *desc=csm->constr;

  sprintf(s,"%08X ",desc);
  p=strstr(csm_text,s);
  
  if (p)
  {
    return(p+9);
  }
  else
  {
    sprintf(u,"Unknown %08X!",desc);
    return(u);
  }
}

int GetNumberOfDialogs(void)
{
  int count=0;
  int c;
  int i;
  CSM_RAM *icsm;
  WSHDR *ws;
  char ss[64];

  void *ircsm=FindCSMbyID(CSM_root()->idle_id);
  ClearNL();

  //Find new style daemons
  //if (show_daemons)
  //{
    icsm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next; //пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ CSM пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    while(((unsigned int)(icsm->constr)>>27)==0x15)
    {
      WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
      if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
      {
        ws=AllocWS(64);
        wstrcpy(ws,tws);
        AddNL(ws,1);
        nltop->p=icsm;
        count++;
      }
      icsm=icsm->next;
    }
 // }
  icsm=under_idle->next; //пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
  do
  {
    if (icsm==ircsm)
    {
      ws=AllocWS(40);
      wsprintf(ws,"Desktop");
      AddNL(ws,0);
      nltop->p=icsm;
      count++;
    }
    else
    {
      if (icsm->constr!=&maincsm)
      {
	WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
	char *s;
	if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
	{
	  ws=AllocWS(64);
	  wstrcpy(ws,tws);
	  AddNL(ws,0);
	  nltop->p=icsm;
	  count++;
	}
	else
	{
	  s=find_name(icsm);
#ifdef NEWSGOLD
	  if (!strncmp_nocase(s,"Java",4))
	  {
	    typedef struct
	    {
	      CSM_RAM csm;
	      int unk1;
	      int bearer;
	      int gui_id;
	      int unk2;
	      int param_R1;
	      int param_ZERO;
	    }JAVAINTERFACE_CSM;
	    int i=((JAVAINTERFACE_CSM *)icsm)->bearer;
	    int j=((JAVAINTERFACE_CSM *)icsm)->param_R1;
	    if (i==2) continue;
	    ws=AllocWS(64);
	    switch(i)
	    {
	    case 1:
	      wsprintf(ws,"Browser",j);
	      break;
	    case 2:
	      wsprintf(ws,"Jam %d",j);
	      break;
	    case 3:
	      switch(j)
	      {
	      case 2:
		wsprintf(ws,"Phone Java Application");
		break;
	      case 3:
		wsprintf(ws,"User Java Application");
		break;
	      default:
		wsprintf(ws,"Unknown Java (%d)",j);
		break;
	      }
	      break;
	    default:
	      //wsprintf(ws,"Unknown %d(%d) bearer",i,j);
              wsprintf(ws,"Java Application");
	      break;
	    }
	    goto L_ADD;
	  }
#else
          if (!strncmp_nocase(s,"Java",4))
	  {
	    typedef struct
	    {
	      CSM_RAM csm;
	      int bearer;
	      int gui_id;
	      int gui_id2;
	    }JAVAINTERFACE_CSM;
	    int i=((JAVAINTERFACE_CSM *)icsm)->bearer;
	    ws=AllocWS(64);
	    switch(i)
	    {
	    case 1:
	      wsprintf(ws,"Browser");
	      break;
	    case 0xF:
              wsprintf(ws,"User Java Application");
	      break;
            case 0x11:
#ifdef X75
              wsprintf(ws,"Java: %t",GetLastJavaApplication());
#else
              wsprintf(ws,"Java Application");
#endif
	      break; 
            case 18:
              wsprintf(ws,"E-mail client");
	      break; 
            default:
              //wsprintf(ws,"Unknown %d bearer",i);
              wsprintf(ws,"Java Application");
              break;
	    }
	    goto L_ADD;
	  }
#endif
	  if (strncmp(s,"!SKIP!",6))
	  {
	    ws=AllocWS(64);
	    i=0;
	    while((c=*s++)>=' ')
	    {
	      if (i<(sizeof(ss)-1)) ss[i++]=c;
	    }
	    ss[i]=0;
	    wsprintf(ws,percent_t,ss);
	  L_ADD:
	    AddNL(ws,0);
	    nltop->p=icsm;
	    count++;
	  }
	}
      }
    }
  }
  while((icsm=icsm->next));
  
  return(count);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int mode=0,cs=1;
int my_keyhook(int submsg, int msg)
{
  int scrH=ScreenH();
  int scrW=ScreenW();

  if((IsUnlocked()) && submsg==CALL_BUTTON)
  {
    if(mode==1)
    {
      if(msg==KEY_UP)
      {
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,CALL_BUTTON);
        return(0);
      }
      if(msg==KEY_DOWN)
      {
        mode=0;
        GBS_SendMessage(MMI_CEPID,KEY_UP,CALL_BUTTON);
        return(0);
      }
    }

    if(msg==KEY_UP)
    {
      cs=1;
      if(mode==2)
      {
        mode=0;
        return(2);
      }
    }
    else if(msg==(LONG_P?LONG_PRESS:KEY_DOWN) && cs)
    {
      

      if((msg==LONG_PRESS) && LONG_P)
        cs=0;
    }

    if(!IsUnlocked())
      return(2);

    if(LONG_P)
    {
      if(msg==LONG_PRESS)
      {
        mode=2;
        return(2);
      }
      if(msg==KEY_DOWN)
      {
        mode=1;
        return(2);
      }
    }
    else
      return(2);
  }
  return(0);
}

// Основная процедура. Она первой получает управление при старте эльфа.
int main(char *exename, char *fname)
{
  LockSched();
  if(xtask_kill){
  if(AddKeybMsgHook_end((void *)my_keyhook)){
   //comment
  }else{
    ShowMSG(1,(int)"Какой-то неубиваемый Хтаск твой... )");
  }
  }
  UnlockSched();
  int i;
  char temp[100];
  InitConfig();
  under_idle=GetUnderIdleCSM();
  dial_n=GetNumberOfDialogs();
   for(i=0;i<dial_n+1;i++)
  nl[i]=get_nlitem(i);  
  for(i=0;i<dial_n;i++){
  if (((CSM_RAM *)(nl[i]->p))->id!=CSM_root()->idle_id)
    CloseCSM(((CSM_RAM *)(nl[i]->p))->id);
  }
  run();
  ClearNL();
  return 1;
}
