#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "rect_patcher.h"
#include "swaper.h"

extern void kill_data(void *p, void (*func_p)(void *));

char mmenu_hdr_txt[32];

int show_daemons;
//extern int mode;
extern CSM_RAM *under_idle;

extern const char BM1NAME[32];
extern const char BM1FILE[128];
extern const char BM2NAME[32];
extern const char BM2FILE[128];
extern const char BM3NAME[32];
extern const char BM3FILE[128];
extern const char BM4NAME[32];
extern const char BM4FILE[128];
extern const char BM5NAME[32];
extern const char BM5FILE[128];
extern const char BM6NAME[32];
extern const char BM6FILE[128];
extern const char BM7NAME[32];
extern const char BM7FILE[128];
extern const char BM8NAME[32];
extern const char BM8FILE[128];
extern const char BM9NAME[32];
extern const char BM9FILE[128];

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

typedef struct
{
  void *next;
  WSHDR *name;
  void *p;
  int is_daemon;
} NAMELIST;

NAMELIST * volatile nltop;

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
    sprintf(u,"未知 %08X!",desc);
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
  if (show_daemons)
  {
    icsm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next; //?????? ???????????? CSM ???????
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
  }
  icsm=under_idle->next;
  do
  {
    if (icsm==ircsm)
    {
      ws=AllocWS(40);
      wsprintf(ws,percent_t,"进入待机界面");
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
	      wsprintf(ws,percent_t,"浏览器");
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
	      wsprintf(ws,percent_t,"浏览器");
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
              wsprintf(ws,percent_t,"电子邮件服务");
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
  sprintf(mmenu_hdr_txt,"XTask3.0 : %d个任务",count);
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


void mm_menu_iconhndl(void *data, int curitem, void *unk)
{
  NAMELIST *nl;
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  nl=get_nlitem(curitem);
  if (nl)
  {
    if (nl->name)
    {
      ws=AllocMenuWS(data,nl->name->wsbody[0]+2);
      wstrcpy(ws,nl->name);
      if (nl->is_daemon)
      {
        wsInsertChar(ws,0x0002,1);
        wsInsertChar(ws,0xE008,1);
      }
    }
    else
    {
      ws=AllocMenuWS(data,16);
      wsprintf(ws,percent_t,"无名???");
    }
  }
  else
  {
    ws=AllocMenuWS(data,16);
    wsprintf(ws,percent_t,"错误!!!");
  }
  SetMenuItemText(data,item,ws,curitem);
}

const char *bm_name(int bm)
{
  switch(bm)
  {
  case 0: return BM1NAME;
  case 1: return BM2NAME;
  case 2: return BM3NAME;
  case 3: return BM4NAME;
  case 4: return BM5NAME;
  case 5: return BM6NAME;
  case 6: return BM7NAME;
  case 7: return BM8NAME;
  case 8: return BM9NAME;
  }
  return(0);
}

const char *bm_file(int bm)
{
  switch(bm)
  {
  case 0: return BM1FILE;
  case 1: return BM2FILE;
  case 2: return BM3FILE;
  case 3: return BM4FILE;
  case 4: return BM5FILE;
  case 5: return BM6FILE;
  case 6: return BM7FILE;
  case 7: return BM8FILE;
  case 8: return BM9FILE;
  }
  return(0);
}

int RunBM(int bm)
{
  const char *s=bm_file(bm);
  if (s)
  {
    if (strlen(s))
    {
      WSHDR *ws;
      ws=AllocWS(150);
      str_2ws(ws,s,128);
      ExecuteFile(ws,0,0);
      FreeWS(ws);
      return(1);
    }
  }
  return(0);
}

const HEADER_DESC bm_menuhdr={0,0,131,21,NULL,(int)"快速启动...",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"配置"},
  {0x0001,0x0000,(int)"关闭"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

void bm_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A) DisableIDLETMR();
}
int bm_menu_onkey(void *data, GUI_MSG *msg);
void bm_menu_iconhndl(void *data, int curitem, void *unk);

const MENU_DESC bm_menu=
{
  8,bm_menu_onkey,bm_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x10,//0x11,
  bm_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int bm_menu_onkey(void *data, GUI_MSG *msg)
{
  int i;
  i=GetCurMenuItem(data);
  if (msg->keys==0x18)
  {
    //    GeneralFunc_F1(1);
//    ShowMSG(1,(int)"Under construction!");
    extern const char *successed_config_filename;
    WSHDR *ws;
    ws=AllocWS(150);
    str_2ws(ws,successed_config_filename,128);
    ExecuteFile(ws,0,0);
    FreeWS(ws);
    GeneralFunc_flag1(((MAIN_CSM*)FindCSMbyID(my_csm_id))->gui_id,1);
    return(1);
  }
  if (msg->keys==0x3D)
  {
    if (RunBM(i))
    {
      GeneralFunc_flag1(((MAIN_CSM*)FindCSMbyID(my_csm_id))->gui_id,1);
      return(1);
    }
    return(-1);
  }
  return(0);
}


void bm_menu_iconhndl(void *data, int curitem, void *unk)
{
  const char *s;
  WSHDR *ws;
  int l;
  void *item=AllocMenuItem(data);

  s=bm_name(curitem);
  if (s)
  {
    if ((l=strlen(s)))
    {
      ws=AllocMenuWS(data,l);
      wsprintf(ws,percent_t,s);
    }
    else
    {
      s=bm_file(curitem);
      if (s)
      {
        if (strlen(s))
        {
          char *p=strrchr(s,'\\');
          if (p)
          {
            unsigned int pos;
            ws=AllocWS((l=strlen(p+1)));
            str_2ws(ws,p+1,l);
            if ((pos=wstrrchr(ws,ws->wsbody[0],'.'))!=0xFFFF)
            {
              CutWSTR(ws,pos-1);
            }
          }
          else goto L_EMPTY;
        }
        else goto L_EMPTY;
      }
      else
      {
      L_EMPTY:
        ws=AllocMenuWS(data,10);
        wsprintf(ws,percent_t,"空白");
      }
    }
  }
  else
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws,percent_t,"错误");
  }
//  SetMenuItemIconArray(data,item,S_ICONS);
  SetMenuItemText(data,item,ws,curitem);
//  SetMenuItemIcon(data,curitem,GetIconIndex(t));
}

void ShowBMmenu(void)
{
  patch_header(&bm_menuhdr);
  CreateMenu(0,0,&bm_menu,&bm_menuhdr,0,9,0,0);
}

int mm_menu_onkey(void *data, GUI_MSG *msg)
{
  MAIN_CSM *csm=MenuGetUserPointer(data);
  NAMELIST *nl=get_nlitem(GetCurMenuItem(data));
  int i;
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    i=msg->gbsmsg->submess;
    {
      if (i=='0')
      {
        ShowBMmenu();
        return(-1);
      }
      if ((i>='1')&&(i<='9'))
      {
        if (RunBM(i-'1')) return 1;
	return(-1);
      }
    }
    switch(i)
    {
#ifdef ELKA
    case LEFT_BUTTON:
      i=((CSM_RAM *)(nl->p))->id;
      if (i!=CSM_root()->idle_id) CloseCSM(i);
      return 0;
#else
    case '#':
      i=((CSM_RAM *)(nl->p))->id;
      if (i!=CSM_root()->idle_id) CloseCSM(i);
      return 0;
#endif
    case '*':
      show_daemons=!show_daemons;
      RefreshGUI();
      return 0;      
    case LEFT_SOFT:
      CSMtoTop(CSM_root()->idle_id,-1);
      return(1); //?????????? ????? GeneralFunc ??? ???. GUI -> ???????? GUI
    case ENTER_BUTTON:
      if (!nl->is_daemon)
      {
	CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
      }
      return(1);
    case RIGHT_SOFT:
      return(1); //?????????? ????? GeneralFunc ??? ???. GUI -> ???????? GUI
    }
  }
  return(0);
}

const HEADER_DESC mm_menuhdr={0,0,131,21,NULL,(int)mmenu_hdr_txt,LGP_NULL};
const SOFTKEY_DESC mm_menu_sk[]=
{
  {0x0018,0x0000,(int)"待机界面"},
  {0x0001,0x0000,(int)"返回"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB mm_menu_skt=
{
  mm_menu_sk,0
};

void mm_menu_ghook(void *data, int cmd)
{
  int i,j;
  if (cmd==9)
  {
    ClearNL();
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
    i=GetCurMenuItem(data);
    Menu_SetItemCountDyn(data,j=GetNumberOfDialogs());
    if (i>=j) SetCursorToMenuItem(data,j-1);
  }
}

const MENU_DESC mm_menu=
{
  8,mm_menu_onkey,mm_menu_ghook,NULL,
  menusoftkeys,
  &mm_menu_skt,
  0x10,//0x11,
  mm_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM *)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  int f;
  int sz=0;
  unsigned int ul;
  extern const char csmlist_fname[128];
  if ((f=fopen(csmlist_fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    sz=fread(f,csm_text,32767,&ul);
    fclose(f,&ul);
  }
  if (sz>=0) csm_text[sz]=0;
  patch_header(&mm_menuhdr);
  csm->gui_id=CreateMenu(0,0,&mm_menu,&mm_menuhdr,1,GetNumberOfDialogs(),csm,0);
}

void maincsm_onclose(CSM_RAM *csm)
{
  ClearNL();
  my_csm_id=0;
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_CSM_DESTROYED)
  {
    RefreshGUI();
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    //if (csm->show_csm==-1) RefreshGUI();
  }
  if (msg->msg==MSG_INCOMMING_CALL)
  {
    csm->csm.state=-3;
  }
  return(1);
}

const int minus11=-11;

const CSM_DESC maincsm=
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
};

void ShowMenu(void)
{
  MAIN_CSM main_csm;
  InitConfig();
  if (!my_csm_id)
  {
//    main_csm.show_csm=-1;
    my_csm_id=CreateCSM(&maincsm,&main_csm,2);
  }
}
