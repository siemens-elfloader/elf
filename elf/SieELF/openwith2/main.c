#include "E:\ARM\new11\inc\swilib.h"
char filetostart[128];

extern const char BM1NAME[32];//закладки
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
extern const char BM9FILE[128];//

extern void InitConfig();
const char percent_t[]="%t";

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline
void patch_header(const HEADER_DESC* headc)
{
  HEADER_DESC *head=(HEADER_DESC *)headc;
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
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
  case 9: return "Reg ext";
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
  case 9: return DEFAULT_DISK":\\Zbin\\utilities\\reg_ext.elf";
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
      ExecuteFile(ws,0,filetostart);
      FreeWS(ws);
      return(1);
    }
  }
  return(0);
}

const HEADER_DESC bm_menuhdr={0,0,131,21,NULL,(int)"Open with...",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)""},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

void bm_menu_ghook(void *data, int cmd){}
int bm_menu_onkey(void *data, GUI_MSG *msg);
void bm_menu_iconhndl(void *data, int curitem, int *unk);

const MENU_DESC bm_menu=
{
  8,(void *)bm_menu_onkey,(void*)bm_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0,//0x11,
  (void *)bm_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int bm_menu_onkey(void *data, GUI_MSG *msg)
{
  int i;
  i=GetCurMenuItem(data);
  if (msg->keys==0x15)// '#'
  {
      WSHDR *ws;
      ws=AllocWS(150);
      str_2ws(ws,DEFAULT_DISK":\\Zbin\\utilities\\CfgEdit.elf",128);
      ExecuteFile(ws,0,DEFAULT_DISK":\\ZBin\\etc\\openwith2.bcfg");
      FreeWS(ws);
    return(-1);
  }
  if (msg->keys==0x3D)
  {
    if (RunBM(i))
    {
      return(1);
    }
    return(-1);
  }
  return(0);
}


void bm_menu_iconhndl(void *data, int curitem, int *unk)
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
  SetMenuItemText(data,item,ws,curitem);
}

void ShowBMmenu(void)
{
  patch_header(&bm_menuhdr);
  CreateMenu(0,0,&bm_menu,&bm_menuhdr,0,10,0,0);
}

int main(char *exename, char *fname)
{
  InitConfig();
  strcpy(filetostart,fname);
  ShowBMmenu();
}
