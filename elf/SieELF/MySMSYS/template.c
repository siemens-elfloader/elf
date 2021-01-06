#include "..\inc\swilib.h"
#include "sms_dat.h"
#include "language.h"
#include "config_data.h"
#include "edGui.h"
#include "string_works.h"
#include "createMenu.h"
#include "rect_patcher.h"

typedef struct
{
  void *next;
  WSHDR *text;
}TPLIST;

TPLIST *tpltop=0;

TPLIST *AllocTP(void)
{
  TPLIST *tp=malloc(sizeof(TPLIST));
  zeromem(tp, sizeof(TPLIST));
  return tp;
}

void FreeTPL(void)
{
  TPLIST *tp;
  TPLIST *tp0;
  LockSched();
  tp=tpltop;
  tpltop=0;
  UnlockSched();
  while(tp)
  {
    tp0=tp->next;
    if(tp->text)
      FreeWS(tp->text);
    mfree(tp);
    tp=tp0;
  }
}

void AddToTPL(TPLIST *tp)
{
//  TPLIST *tp0;
  LockSched();
//  tp0=tpltop;
  tp->next=tpltop;
  tpltop=tp;
  UnlockSched();
}

TPLIST *GetTpByN(int n)
{
  int i=0;
  TPLIST *tp=tpltop;
  while(tp)
  {
    if(i==n)
      return tp;
    i++;
    tp=tp->next;
  }
  return 0;
}
//ansi //cn
//win1251 //en
int ReadTp(void)
{
  char folder[128], dir[128], filepath[128], buf[MAX_TEXT*2], *pp;
  WSHDR *ws, wsn;
  unsigned short wsb[MAX_TEXT];
  int len, c, res=0, fp, size, wlen;
  DIR_ENTRY de;
  unsigned int err;
  TPLIST *tp;
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, "Text\\");
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, "Template\\");
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!isdir(folder, &err))
    return -1;
  FreeTPL();
  ws=CreateLocalWS(&wsn, wsb, MAX_TEXT);
  strcpy(dir, folder);
  strcat(dir, "*.txt");
  if(FindFirstFile(&de, dir, &err))
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
      if((fp=fopen(filepath, A_BIN+A_ReadOnly, P_READ, &err))>=0)
      {
	if(fread(fp, buf, size, &err)==size)
	{
	  buf[size]=0;
	  //if(buf[0]==0xEF && buf[1]==0xBB && buf[2]==0xBF)
	  //  pp=buf+3;
	  //else 
	  pp=buf;
	  //utf8_2ws(ws, pp, MAX_TEXT);
	  ascii_2ws(ws, pp, MAX_TEXT);
	  tp=AllocTP();
	  wlen=(ws->wsbody[0]>0)?ws->wsbody[0]:1;
	  tp->text=AllocWS(wlen);
	  wstrcpy(tp->text, ws);
	  AddToTPL(tp);
	  res++;
	}
	fclose(fp, &err);
      }
    }while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  return res;
}

const int tplmenusoftkeys[]={0,1,2};
SOFTKEY_DESC tplmenu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB tplmenu_skt=
{
  tplmenu_sk,0
};

HEADER_DESC tplmenuhdr={0,0,0,0,NULL,(int)LGP_NULL,LGP_NULL};

int tplmenu_onkey(void *data, GUI_MSG *msg)
{
  if((msg->keys==0x18)||(msg->keys==0x3D))
  {
    TPLIST *tp;
    void *ed_gui;
    if((ed_gui=MenuGetUserPointer(data)) && GetMenuItemCount(data) && (tp=GetTpByN(GetCurMenuItem(data))))
    {
      WSHDR csloc, *wcs;
      EDITCONTROL ec;
      unsigned short csb[MAX_TEXT];
      int k=EDIT_GetCursorPos(ed_gui);
      USER_OP *uo=EDIT_GetUserPointer(ed_gui);
      int n=EDIT_GetFocus(ed_gui);
      if(n!=(uo->focus_n))
	return 1;
      if(k<=0)
	return 1;
      wcs=CreateLocalWS(&csloc,csb,MAX_TEXT);
      ExtractEditControl(ed_gui,n,&ec);
      wstrcpy(wcs, ec.pWS);
      wsInsert(wcs, tp->text, k-1, MAX_TEXT);
      EDIT_SetTextToEditControl(ed_gui, n, wcs);
      EDIT_SetCursorPos(ed_gui, k+wstrlen(tp->text));
    }
    return 1;
  }
  if(msg->keys==0x1)
    return 1;
  return 0;
}
void tplmenuitemhdl(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 32);
  TPLIST *tp=GetTpByN(curitem);
  if(tp)
    wstrcpy(ws, tp->text);
  else
    wsprintf(ws, PERCENT_T, lgp.LGP_ERR);
  SetMenuItemText(data, item, ws, curitem);
}

void tplmenu_ghook(void *data, int cmd)
{
  if(cmd==3)
  {
    FreeTPL();
  }
}

const MENU_DESC tplmenu=
{
  8,tplmenu_onkey,tplmenu_ghook,NULL,
  tplmenusoftkeys,
  &tplmenu_skt,
  0x10,//
  tplmenuitemhdl,
  NULL,//menuitems,
  NULL,//menuprocs,
  0
};

int CreateTplMenu(void *ed_gui)
{
  int n;
  if((n=ReadTp())==-1)
  {
    MsgBoxError(1, (int)lgp.LGP_ERR);
    return 0;
  }
  patch_header(&tplmenuhdr);
  return (CreateSLMenu(&tplmenu, &tplmenuhdr, 0, n, ed_gui));
}








