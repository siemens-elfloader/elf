#include "..\inc\swilib.h"
//#include "conf_loader.h"
#include "rect_patcher.h"
#include "swaper.h"
#include "main.h"


NAMELIST * volatile nltop;

int number_reald;  // Number of real dialogs
int number_nsd;  // Number of new style dialogs
extern int show_daemons;
extern CSM_RAM *under_idle;
extern int tasks;

const int SHOW_IDLESCREEN=1;

const CSM_DESC maincsm;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
//  int show_csm;
//  int do_idle;
}MAIN_CSM;

int my_csm_id;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
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
  LockSched();
  NAMELIST *nl=nltop;
  nltop=0;
  UnlockSched();
  while(nl)
  {
    NAMELIST *p=nl;
    FreeWS(nl->name);
    zeromem(nl->icon_path, 64);
    nl=p->next;
    mfree(p);
  }
}

void AddNL(WSHDR *ws, int is_daemon)
{
  NAMELIST *nnl=malloc(sizeof(NAMELIST));
  //if(!nnl->icon_path)
  //Search_icon(ws, nnl);
  nnl->name=ws;
  nnl->next=0;
  nnl->is_daemon=is_daemon;
  
 // strcpy(nnl->icon_path, path_name);
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
  number_nsd=0;
  if (show_daemons)
  {
    icsm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next; //������ ������������ CSM �������
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
        number_nsd++;         // count new style dialogs
      }
      icsm=icsm->next;
    }
  }
  icsm=under_idle->next; //������ ��������
  do
  {
    if (icsm==ircsm)
    {
      if (SHOW_IDLESCREEN)
      {
        ws=AllocWS(40);
        wsprintf(ws,"IDLE Screen");
        AddNL(ws,0);
        nltop->p=icsm;
        count++;
      }
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
		wsprintf(ws,"Phone Java");
		break;
	      case 3:
		wsprintf(ws,"User Java");
		break;
	      default:
		wsprintf(ws,"Unknown Java (%d)",j);
		break;
	      }
	      break;
	    default:
	      wsprintf(ws,"Unknown %d(%d) bearer",i,j);
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
              wsprintf(ws,"User Java");
	      break;
            case 0x11:
#ifdef X75
              wsprintf(ws,"Java: %t",GetLastJavaApplication());
#else
              wsprintf(ws,"Java");
#endif
	      break; 
            case 18:
              wsprintf(ws,"E-mail client");
	      break; 
            default:
              wsprintf(ws,"Unknown %d bearer",i);
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
  number_reald=count-number_nsd;
  tasks=count-1;
  return(count);
}

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

