#include "..\inc\swilib.h"
#include "conf_loader.h"

char csm_text[32768];
CSM_RAM *under_idle;
const CSM_DESC maincsm;

extern const unsigned int CSM_X;
extern const unsigned int CSM_Y;
extern const unsigned int CSM_FONT;
extern const char CSM_COLORS[];
extern const char CSM_FRAME_COLORS[];
extern const char begin_str[];
extern const int SHOW_DAEMONS;

extern void kill_data(void *p, void (*func_p)(void *));
#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

typedef struct
{
  void *next;
  WSHDR *name;
  void *p;
  int is_daemon;
//  int type; //0,idle screen  1,normarl
} NAMELIST;

NAMELIST * volatile nltop;

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
    nl=p->next;
    mfree(p);
  }
}


void AddNL(WSHDR *ws, int is_daemon)
{
  NAMELIST *nnl=malloc(sizeof(NAMELIST));
  nnl->name=ws;
  nnl->next=0;
  nnl->is_daemon=is_daemon;
//  nnl->type=type;
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

#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
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

void GetNumberOfDialogs(void)
{
  int c;
  int i;
  CSM_RAM *icsm;
  WSHDR *ws;
  char ss[64];

  void *ircsm=FindCSMbyID(CSM_root()->idle_id);
  ClearNL();
  
  if (SHOW_DAEMONS)
  {
    icsm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next;
    while(((unsigned int)(icsm->constr)>>27)==0x15)
    {
      WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
      if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
      {
        ws=AllocWS(64);
        wstrcpy(ws,tws);
        AddNL(ws,1);
        nltop->p=icsm;
      }
      icsm=icsm->next;      
    }
  }
  icsm=under_idle->next;
  do
  {
    if (icsm!=ircsm)
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
              wsprintf(ws,"Java");
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
	    //utf8_2ws(ws,ss,strlen(ss));
	    wsprintf(ws, "%t", ss);
	  L_ADD:
	    AddNL(ws,0);
	    nltop->p=icsm;
	  }
	}
      }
    }
  }
  while((icsm=icsm->next));
}

void draw_csm_name(GUI *igui)
{
	WSHDR *csmname=AllocWS(80);
	NAMELIST *nl;
	int i=0,len,font_high;
	nl=nltop;
	#ifdef ELKA
	void *canvasdata = BuildCanvas();
	#else
	void *idata = GetDataOfItemByID(igui, 2);
	void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
	#endif
	font_high=GetFontYSIZE(CSM_FONT);
	while (nl)
	{
		++i;
		wsprintf(csmname,begin_str,i);
		wstrcat(csmname,nl->name);
		len=get_string_width(csmname,CSM_FONT);
	  DrawCanvas(canvasdata,CSM_X,CSM_Y+(i-1)*(font_high+1),CSM_X+len+5,CSM_Y+(i)*(font_high+1),1);
	  DrawString(csmname, CSM_X, CSM_Y+(i-1)*(font_high+1),CSM_X+len+5, CSM_Y+(i)*(font_high+1),CSM_FONT,32,CSM_COLORS, CSM_FRAME_COLORS);
		nl=nl->next;
	}
	FreeWS(csmname);
}

#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strncmp_nocase(successed_config_filename,(char *)msg->data0,strlen(successed_config_filename))==0)
    {
      ShowMSG(1,(int)"CSMShow config updated!");
      InitConfig();
    }
  }
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
        GetNumberOfDialogs();
        draw_csm_name(igui);
      }
    }
  }
  return(1);
}

void open_csm_file(void)
{
  int f;
  int sz=0;
  unsigned int ul;
  extern const char csmlist_fname[];
  if ((f=fopen(csmlist_fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    sz=fread(f,csm_text,32767,&ul);
    fclose(f,&ul);
  }
  if (sz>=0) csm_text[sz]=0;
}

static void maincsm_oncreate(CSM_RAM *data)
{
  open_csm_file();
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

static void maincsm_onclose(CSM_RAM *csm)
{
  ClearNL(); 
  SUBPROC((void *)ElfKiller);
}

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
  sizeof(CSM_RAM),
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CSMShow");
}

int main(void)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  under_idle=(FindCSMbyID(csmr->idle_id))->prev;
  UnlockSched();
  return (0);
}
