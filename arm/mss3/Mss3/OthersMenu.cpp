#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"
#include "PopupGUI.h"
#include "OthersMenu.h"

#include "TViewGUI.h"
#include "AFile.h"

#define OTH_MENU_ITEM_N 7

const HEADER_DESC oth_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};


void OpenArchive(void)
{
  //int len, c;
  char folder[128];
  unsigned int err;
  NativeExplorerData data;
  WSHDR *ws, wsn;
  unsigned short wsb[128];
  ws=CreateLocalWS(&wsn, wsb, 128);
  strcpy(folder, main_folder);
  //len=strlen(folder);
  //c=folder[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  folder[len]='\\';
  //  folder[len+1]=0;
  //}
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, FLDR_ARCHIVE);
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!isdir(folder, &err))
    return;
  str_2ws(ws, folder, 128);
  zeromem(&data,sizeof(NativeExplorerData));
  data.mode=0;
  data.dir_enum=0x26;
  data.path_to_file=ws;
  data.is_exact_dir=1;
  data.full_filename=ws;
  data.unk9=1;
  StartNativeExplorer(&data);
}

OthMenu::OthMenu()
{
  this->menu.flag=8;
  this->menu.flags2=0x10;
  this->menu.ghook=this->GHook;
  this->menu.itemproc=this->ItemProc;
  this->menu.items=NULL;
  this->menu.n_items=0;
  this->menu.onkey=this->OnKey;
  this->menu.proc3=NULL;
  this->menu.procs=NULL;
  this->menu.softkeys=softkeys;
  this->menu.softkeystab=&sel_menu_skt;
}

OthMenu::~OthMenu()
{
}

int OthMenu::OnKey(void *data, GUI_MSG *msg)
{
  OthMenu *oth=(OthMenu *)MenuGetUserPointer(data);
  int cur=GetCurMenuItem(data);
  if(msg->keys==1)
    return 1;
  if(msg->keys==0x3D || msg->keys==0x18)
  {
DO_OTH:
    switch(cur)
    {
    case 0:
      oth->OpenCfgFile();
      break;
    case 1:
      oth->OpenArchiveOTH();
      break;
    case 2:
      oth->MoveAllMss();
      break;
    case 3:
      oth->ExportTxtAll();
      break;
    case 4:
      oth->DelAllMss();
      break;
    case 5:
      oth->ShowHelp();
      break;
    case 6:
      oth->ShowAbout();
      break;
    }
    return 1;
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    cur=msg->gbsmsg->submess;
    if(cur>='1' && cur<='9')
    {
      cur-='1';
      if(cur<OTH_MENU_ITEM_N) goto DO_OTH;
    }
  }
  return 0;
}

void OthMenu::GHook(void *data, int cmd)
{
  OthMenu *oth=(OthMenu *)MenuGetUserPointer(data);
  if(cmd==0x3)
  {
    delete oth;
  }
  else if(cmd==0xA)
  {
    DisableIDLETMR();
  }
  else if (cmd==0x2)
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_OTHERS);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}

int OTH_ITEM_LGPS[OTH_MENU_ITEM_N]=
{
  LGP_NULL, //config
    LGP_NULL, //open archive
    LGP_NULL, //move all mss to archive
    LGP_NULL, //export all
    LGP_NULL, //del all mss
    LGP_NULL, //help
    LGP_NULL, //about
};

void OthMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  wsprintf(ws, PERCENT_T, OTH_ITEM_LGPS[curitem]);
  SetMenuItemText(data, item, ws, curitem);
}

int OthMenu::CreateOthMenu(DLG_CSM *dlg_csm)
{
  this->dlg_csm=dlg_csm;
  //patch_header(&oth_menuhdr);
  return CreateMenu(&this->menu, &oth_menuhdr, 0, OTH_MENU_ITEM_N, this);
}

void OthMenu::OpenCfgFile(void)
{
  extern const char *successed_config_filename;
  WSHDR *file=AllocWS(128);
  str_2ws(file, successed_config_filename, 128);
  ExecuteFile(file, 0, 0);
  FreeWS(file);
}


void OthMenu::OpenArchiveOTH(void)
{
  SUBPROC((void *)OpenArchive);
}

void OthMenu::MoveAllMss(void)
{
  SUBPROC((void *)SMSDATA->MoveAllToArchiveBG, SMSDATA);
}

void OthMenu::ShowAbout()
{
  char msg[128];
  sprintf(msg, "%s\nCompile at\n%s %s", CP_RIGHT, __DATE__, __TIME__);
  MyShowMsg::MyShow(0, msg);
}

#define HLP_BUF_SIZE (16*1024)
char help_buf[HLP_BUF_SIZE];

void OthMenu::ShowHelp()
{
  char filepath[128];
  AFile file;
  int len;
  WSHDR *ws;
  strcpy(filepath, main_folder);
  strcat(filepath, "help.txt");
  if ((file.FOpen(filepath, A_BIN+A_ReadOnly, P_READ)) != -1)
  {
    len=file.FRead(help_buf, HLP_BUF_SIZE);
    file.FClose();
    if(!len)
      goto HLP_DEFAUT;
    help_buf[len]='\0';
    ws=AllocWS(len);
#ifdef LANG_CN
    ascii_2ws(ws, help_buf, len);
#else
    wsprintf(ws, PERCENT_T, help_buf);
#endif
  }
  else
  {
HLP_DEFAUT:
    ws=AllocWS(256);
    wsprintf(ws, PERCENT_T, DEFAUT_HLP_STR);
  }
  WSHDR *hdr_t=AllocWS(32);
  wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_HELP);
  TViewGUI *tv=new TViewGUI;
  tv->CreateTViewGUI(ws, hdr_t);
}
/*
void OthMenu::ShowHelp()
{
  char filepath[128];
  CFile file;
  int fin;
  int len;
  WSHDR *ws;
  strcpy(filepath, main_folder);
  strcat(filepath, "help.txt");
  if((fin=file.FOpen(filepath, A_ReadOnly, P_READ))!=-1)
  {
    if((len=file.LSeek(fin, 0, S_END)))
    {
      char *buf=new char[len+4];
      file.LSeek(fin, 0, S_SET);
      if(file.FRead(fin, buf, len)!=len)
      {
	delete buf;
	goto HLP_FERR;
      }
      file.FClose(fin);
      buf[len]=0;
      ws=AllocWS(len);
      wsprintf(ws, PERCENT_T, buf);
      delete buf;
    }
    else
    {
HLP_FERR:
      file.FClose(fin);
      goto HLP_DEFAUT;
    }
  }
  else
  {
HLP_DEFAUT:
    ws=AllocWS(256);
    wsprintf(ws, PERCENT_T, DEFAUT_HLP_STR);
  }
  WSHDR *hdr_t=AllocWS(32);
  wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_HELP);
  TViewGUI *tv=new TViewGUI;
  tv->CreateTViewGUI(ws, hdr_t);
}
*/
void OthMenu::ExportTxtAll()
{
  SUBPROC((void *)SMSDATA->ExportAllToTextBG, SMSDATA);
}



void OthMenu::DelAllMss()
{
  SUBPROC((void*)SMSDATA->DeleteAllMssBG, SMSDATA);
}
