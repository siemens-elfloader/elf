#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

void Log(int dummy, char *txt)
{
  unsigned int ul;
  int f=fopen(DEFAULT_DISK":\\BLIB.log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
    fclose(f,&ul);
  }
  mfree(txt);
}


//static const char percent_t[]="%t";

const int minus11=-11;

const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

WSHDR *ews;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ed1_locret(void){}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void ed1_ghook(GUI *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

const HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"BLIB info",LGP_NULL};

const INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000002 // Поменять местами софт-кнопки
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  int i=0;
  int j=0;
  int a;
  EDITCONTROL ec;
  WSHDR *tws=AllocWS(256);
  CutWSTR(ews,0);
  do
  {
    if (((void **)AddrLibrary())[j]!=(*(void ***)LIB_TOP())[j])
    {
      if ((a=(*(int **)LIB_TOP())[j])!=-1)
      {
	wsprintf(tws,"%03X/%04d: %08X\n",j,j,a);
	i++;
	wstrcat(ews,tws);
      }
    }
    j++;
  }
  while(j<4096);
  wsprintf(tws,"Total %d functions",i);
  wstrcat(ews,tws);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_NORMAL_STR,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(tws);
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

int create_menu(void);

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(16384);
  csm->gui_id=create_ed();
//  csm->gui_id=create_menu();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      {
	csm->csm.state=-3;
      }
    }
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
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

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BLIBinfo");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  if (*(void **)LIB_TOP())
  {
    UpdateCSMname();
    CreateCSM(&MAINCSM.maincsm,dummy,0);
  }
  else
  {
    ShowMSG(1,(int)"BLIB not loaded!");
    SUBPROC((void *)Killer);
  }
  UnlockSched();
  return 0;
}

