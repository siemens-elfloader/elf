#include "..\inc\swilib.h"
#include "conf_loader.h"

extern void kill_data(void *p, void (*func_p)(void *));

char mmenu_hdr_txt[32];

#pragma inline
void patch_header(const HEADER_DESC* headc)
{
  HEADER_DESC *head=(HEADER_DESC *)headc;
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

#pragma inline
void patch_input(const INPUTDIA_DESC* inpc)
{
  INPUTDIA_DESC *inp=(INPUTDIA_DESC *)inpc;
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

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
  int show_csm;
  int do_idle;
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

void AddNL(WSHDR *ws)
{
  NAMELIST *nnl=malloc(sizeof(NAMELIST));
  nnl->name=ws;
  nnl->next=0;
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
  CSM_RAM *icsm=under_idle->next; //Начало карусели
  ClearNL();
  WSHDR *ws;
  char ss[64];

  void *ircsm=FindCSMbyID(CSM_root()->idle_id);
  ClearNL();
  do
  {
    if (icsm==ircsm)
    {
      ws=AllocWS(40);
      wsprintf(ws,"IDLE Screen");
      AddNL(ws);
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
	  AddNL(ws);
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
              wsprintf(ws,"Java");
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
	    AddNL(ws);
	    nltop->p=icsm;
	    count++;
	  }
	}
      }
    }
  }
  while((icsm=icsm->next));
  {
//    char *s=GetLastJavaApplication();
//    if (s) sprintf(mmenu_hdr_txt,"%s",s);
//    else 
      sprintf(mmenu_hdr_txt,"XTask2.0: %d dialogs",count);
  }
  return(count);
}

void RotateCSMs(CSM_RAM *ucsm, void *selcsm)
{
  CSM_RAM *icsm; //Нижний CSM
  //CSM_RAM *ucsm; //Верхний CSM
  CSM_RAM *wcsm; //Перемещаемый CSM
  if (!selcsm) return;
  if (ucsm==selcsm) return; //Нужный уже выше чем надо
  do
  {
    icsm=under_idle;
//    ucsm=FindCSMbyID(my_csm_id);
    wcsm=(CSM_RAM *)ucsm->prev; //Получаем перемещаемый CSM
    ((CSM_RAM *)(wcsm->prev))->next=ucsm; //CSM перед перемещаемым теперь указывает на верхний CSM
    ucsm->prev=wcsm->prev; //prev верхнего CSM указывает на CSM перед перемещаемым
    //Теперь вставляем в нужное место перемещаемый CSM
    ((CSM_RAM *)(wcsm->next=icsm->next))->prev=wcsm;
    icsm->next=wcsm;
    wcsm->prev=icsm;
  }
  while(ucsm->prev!=selcsm);
  return;
}

void SwapCSMs(int no_no_gui, void *selcsm)
{
  extern WSHDR *ws_nogui;
  static const char my_color[]={0x00,0x00,0x00,0x32};

  if (GetNumberOfDialogs()<2) return; //Нечего сворачивать
  if (!selcsm) return;
  RotateCSMs(FindCSMbyID(my_csm_id),selcsm);
  if (no_no_gui) return; //
  //Теперь рисуем "Нет GUI" на всякий случай
  DrawRoundedFrame(0,0+YDISP,ScreenW()-1,ScreenH()-1,0,0,0,
			my_color,
			my_color);

//  DrawRoundedFrame(0,0+YDISP,ScreenW()-1,ScreenH()-1,0,0,0,
//			GetPaletteAdrByColorIndex(0),
//			GetPaletteAdrByColorIndex(20));
//  DrawString(ws_nogui,3,70,ScreenW()-4,ScreenH()-4,1,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
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
      ws=AllocMenuWS(data,nl->name->wsbody[0]);
      wstrcpy(ws,nl->name);
    }
    else
    {
      ws=AllocMenuWS(data,16);
      wsprintf(ws,"no name???");
    }
  }
  else
  {
    ws=AllocMenuWS(data,16);
    wsprintf(ws,"error!!!");
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

const HEADER_DESC bm_menuhdr={0,0,131,21,NULL,(int)"Bookmarks...",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Config"},
  {0x0001,0x0000,(int)"Close"},
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
  void *item=AllocMenuItem(data);

  s=bm_name(curitem);
  if (s)
  {
    if (strlen(s))
    {
      ws=AllocMenuWS(data,strlen(s));
      wsprintf(ws,percent_t,s);
    }
    else
    {
      ws=AllocMenuWS(data,10);
      wsprintf(ws,"Empty");
    }
  }
  else
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws,"error");
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
    case '#':
      i=((CSM_RAM *)(get_nlitem(GetCurMenuItem(data))->p))->id;
      if (i!=CSM_root()->idle_id) CloseCSM(i);
      return 0;
    case LEFT_SOFT:
      SwapCSMs(0,FindCSMbyID(CSM_root()->idle_id));
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    case ENTER_BUTTON:
      SwapCSMs(0,get_nlitem(GetCurMenuItem(data))->p);
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    }
  }
  return(0);
}

const HEADER_DESC mm_menuhdr={0,0,131,21,NULL,(int)mmenu_hdr_txt,LGP_NULL};
const SOFTKEY_DESC mm_menu_sk[]=
{
  {0x0018,0x0000,(int)"Idle"},
  {0x0001,0x0000,(int)"Back"},
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


typedef struct
{
  GUI gui;
  int show_csm;
}DUMMY_GUI;

void method0(DUMMY_GUI *data)
{
  if (data->show_csm)
  {
    RotateCSMs(FindCSMbyID(my_csm_id),FindCSMbyID(data->show_csm));
  }
  else
  {
    SwapCSMs(1,FindCSMbyID(CSM_root()->idle_id));
  }
  GeneralFuncF1(1);
}

void method1(DUMMY_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void method2(DUMMY_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void method3(DUMMY_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(DUMMY_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5(DUMMY_GUI *data, GUI_MSG *msg)
{
  return(0);
}

void method7(DUMMY_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM *)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  if (csm->do_idle)
  {
    DUMMY_GUI *main_gui=malloc(sizeof(DUMMY_GUI));
    zeromem(main_gui,sizeof(DUMMY_GUI));
    main_gui->gui.canvas=(void *)(&Canvas);
    main_gui->gui.flag30=2;
    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
    main_gui->show_csm=csm->show_csm;
    csm->gui_id=CreateGUI(main_gui);
  }
  else
  {
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
    csm->gui_id=CreateMenu(0,0,&mm_menu,&mm_menuhdr,1,GetNumberOfDialogs(),0,0);
  }
}

void maincsm_onclose(CSM_RAM *csm)
{
  ClearNL();
  my_csm_id=0;
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (
      ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))||
	(msg->msg==MSG_INCOMMING_CALL)
	)
  {
    csm->csm.state=-3;
  }
  if ((msg->msg==MSG_CSM_DESTROYED)&&(!csm->show_csm)) RefreshGUI();
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

void do_gui(int _do_idle, int show_csm)
{
  char dummy[sizeof(MAIN_CSM)];
  ((MAIN_CSM *)dummy)->do_idle=_do_idle;
  ((MAIN_CSM *)dummy)->show_csm=show_csm;
  InitConfig();
//  if (my_csm_id) CloseCSM(my_csm_id);
  if (!my_csm_id)
  {
//    CSM_RAM **p;
//    CSM_RAM *save;
//    p=&(CSM_root()->csm_q->current_msg_processing_csm);
//    save=*p;
//    *p=NULL;
    my_csm_id=CreateCSM(&maincsm,dummy,2);
//    *p=save;
  }
}
