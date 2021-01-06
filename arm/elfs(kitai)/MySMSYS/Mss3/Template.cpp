#include "include.h"
#include "File.h"
#include "CreateMenu.h"
#include "Template.h"
/*
SOFTKEY_DESC tpl_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB tpl_menu_skt=
{
  tpl_menu_sk,0
};
*/
const HEADER_DESC tpl_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

TplMenu::TplMenu()
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
  this->tpltop=NULL;
}

TplMenu::~TplMenu()
{
  FreeTPList();
}

TPLIST *TplMenu::AllocTPList(void)
{
  TPLIST *tpl=new TPLIST;
  zeromem(tpl, sizeof(TPLIST));
  return tpl;
}

void TplMenu::AddToTPList(TPLIST *tpl)
{
  LockSched();
  tpl->next=tpltop;
  this->tpltop=tpl;
  UnlockSched();
}

void TplMenu::FreeTPList(void)
{
  TPLIST *tp;
  TPLIST *tp0;
  LockSched();
  tp=this->tpltop;
  this->tpltop=0;
  UnlockSched();
  while(tp)
  {
    tp0=tp->next;
    if(tp->text)
      FreeWS(tp->text);
    delete tp;
    tp=tp0;
  }
}

int TplMenu::ReadTpl(void)
{
  char folder[128], dir[128], filepath[128], buf[MAX_TEXT*2], *pp;
  WSHDR *ws, wsn;
  unsigned short wsb[MAX_TEXT];
  int len, /*c,*/ res=0, fp, size, wlen;
  DIR_ENTRY de;
  TPLIST *tp;
  strcpy(folder, main_folder);
  //len=strlen(folder);
  //c=folder[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  folder[len]='\\';
  //  folder[len+1]=0;
  //}
  if(!IsDir(folder))
    MkDir(folder);
  strcat(folder, "Text\\");
  if(!IsDir(folder))
    MkDir(folder);
  strcat(folder, "Template\\");
  if(!IsDir(folder))
    return -1;
  ws=CreateLocalWS(&wsn, wsb, MAX_TEXT);
  strcpy(dir, folder);
  strcat(dir, "*.txt");
  if(FindFirstFile(&de, dir))
  {
    do
    {
      strcpy(filepath, de.folder_name);
      len=strlen(filepath);
      if(filepath[len-1]!='\\' && filepath[len-1]!='/')
      {
	filepath[len++]='\\';
	filepath[len]='\0';
      }
      strcat(filepath, de.file_name);
      size=(de.file_size<(MAX_TEXT*2))?de.file_size:(MAX_TEXT*2);
      if((fp=FOpen(filepath, A_BIN+A_ReadOnly, P_READ))>=0)
      {
	if(FRead(fp, buf, size)==size)
	{
	  buf[size]=0;
	  pp=buf;
	  ascii_2ws(ws, pp, MAX_TEXT);
	  tp=AllocTPList();
	  wlen=(ws->wsbody[0]>0)?ws->wsbody[0]:1;
	  tp->text=AllocWS(wlen);
	  wstrcpy(tp->text, ws);
	  AddToTPList(tp);
	  res++;
	}
	FClose(fp);
      }
    }while(FindNextFile(&de));
  }
  FindClose(&de);
  return res;
}

TPLIST *TplMenu::GetTpl(int n)
{
  int i=0;
  TPLIST *tp=this->tpltop;
  while(tp)
  {
    if(i==n)
      return tp;
    i++;
    tp=tp->next;
  }
  return 0;
}

int TplMenu::OnKey(void *data, GUI_MSG *msg)
{
  TplMenu *tpm=(TplMenu *)MenuGetUserPointer(data);
  if(msg->keys==0x1)
    return 1;
  if((msg->keys==0x18)||(msg->keys==0x3D))
  {
    TPLIST *tpl;
    void *ed_gui;
    if(tpm && (tpl=tpm->GetTpl(GetCurMenuItem(data))) && (ed_gui=tpm->edgui))
    {
      WSHDR csloc, *wcs;
      EDITCONTROL ec;
      int i;
      unsigned short csb[MAX_TEXT];
      int pos=EDIT_GetCursorPos(ed_gui);
      if(EDIT_GetFocus(ed_gui)!=3 || !tpl->text)
	return 1;
      wcs=CreateLocalWS(&csloc,csb,MAX_TEXT);
      ExtractEditControl(ed_gui,3,&ec);
      wstrcpy(wcs, ec.pWS);
      for(i=tpl->text->wsbody[0];i>0;i--)
      {
	wsInsertChar(wcs, tpl->text->wsbody[i], pos);
      }
      EDIT_SetTextToEditControl(ed_gui, 3, wcs);
      EDIT_SetCursorPos(ed_gui, pos+tpl->text->wsbody[0]);
    }
    return 1;
  }
  return 0;
}

void TplMenu::GHook(void *data, int cmd)
{
  TplMenu *tpm=(TplMenu *)MenuGetUserPointer(data);
  if(cmd==3)
  {
    delete tpm;
  }
  else if (cmd==0x2)
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_TEMPLATE);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}

void TplMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 32);
  TplMenu *tpm=(TplMenu *)MenuGetUserPointer(data);
  TPLIST *tpl=tpm->GetTpl(curitem);
  if(tpl)
    wstrcpy(ws, tpl->text);
  else
    wsprintf(ws, PERCENT_T, LGP->lgp.LGP_ERR);
  SetMenuItemText(data, item, ws, curitem);
}

int TplMenu::CreateTplMenu(void *edgui)
{
  this->edgui=edgui;
  //patch_header(&tpl_menuhdr);
  return CreateMenu(&this->menu, &tpl_menuhdr, 0, this->ReadTpl(), this);
}


