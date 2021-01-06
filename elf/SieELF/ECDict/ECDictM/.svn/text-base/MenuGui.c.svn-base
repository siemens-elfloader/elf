#include "..\..\inc\swilib.h"
#include "dict.h"
#include "rect_patcher.h"

int start_index=9;
int old_start_index=9;
const int gmenusoftkeys[]={0,1,2};
const SOFTKEY_DESC gmenu_sk[]=
{
  {0x0018,0x0000,(int)"ÊäÈë"},
  {0x0001,0x0000,(int)"ÍË³ö"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB gmenu_skt=
{
  gmenu_sk,0
};

HEADER_DESC gmenuhdr={0,0,0,0,NULL,(int)"Ó¢ºº×Öµä",LGP_NULL};

#define GMENU_ITEM_N 20


int estr2ws(WSHDR *ws, const char *str, int maxlen)
{
  int i=0, c;
  const char *p=str;
  unsigned short *ps=ws->wsbody+1;
  int max2;
  if( !ws || !str || !maxlen)
    return 0;
  max2=(maxlen < ws->maxlen)?maxlen:ws->maxlen;
  while(i<max2 && (c=*p++))
  {
    ps[i++]=c;
  }
  ps[i]=0;
  return (ws->wsbody[0]=i);
}

int ws2estr(WSHDR *ws, char *str, int maxlen)
{
  int i=0, c;
  int max2;
  unsigned short *ps=ws->wsbody+1;
  if( !ws || !str || !maxlen)
    return 0;
  max2=(ws->wsbody[0] < maxlen)?ws->wsbody[0]:maxlen;
  while(i<max2 && (c=*ps++))
  {
    str[i++]=c;
  }
  str[i]=0;
  return i;
}

int ShowDetial(int eindex);
int DoInput(void *menugui);
int gmenu_onkey(void *data, GUI_MSG *msg)
{
  if(msg->keys==1) return 1;
  if(msg->keys==0x3D)
  {
    ShowDetial(start_index+GetCurMenuItem(data));
  }
  else if(msg->keys==0x18)
  {
    DoInput(data);
  }
  return 0;
}

void gmenu_ghook(void *data, int cmd)
{
  if(cmd==0xA)
  {
    DisableIDLETMR();
  }
/*  else if(cmd==0x5)
  {
    GetCPUClock();
    if(old_start_index!=start_index)
    {
      old_start_index=start_index;
      SetCursorToMenuItem(data, 0);
      Menu_SetItemCountDyn(data, (wordcount-start_index < GMENU_ITEM_N)?(wordcount-start_index):GMENU_ITEM_N);
      REDRAW();
    }
  }*/
}

void gmenu_itemhndl(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMLMenuItem(data);
  WSHDR *ws1=AllocMenuWS(data, 150);
  WSHDR *ws2=AllocMenuWS(data, 150);
  if((start_index+curitem)<wordcount)
  {
    estr2ws(ws1, index[start_index+curitem], 150);
    construct_entry_text(ws2, index[start_index + curitem], 0, 1/*fw_phoneticÏÔÊ¾Òô±ê*/, 1);
  }
  else
  {
    wsprintf(ws1, "error!");
    CutWSTR(ws2, 0);
  }
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

int SearchCallBack(void *data, WSHDR* searchstr) //return Cursor
{
  char word[128];
  int pos;
//  GetCPUClock(); //de
  ws2estr(searchstr, word, 127);
  if((pos=lookup(word))>=0)
  {
    start_index=pos;
    old_start_index=start_index;
    SetCursorToMenuItem(data, 0);
    Menu_SetItemCountDyn(data, (wordcount-start_index < GMENU_ITEM_N)?(wordcount-start_index):GMENU_ITEM_N);
    REDRAW();
    return 0;
  }
  return 0;
}

const ML_MENU_DESC gmenu=
{
  8,gmenu_onkey,gmenu_ghook,NULL,
  gmenusoftkeys,
  &gmenu_skt,
  0x10010,//0x11,
  gmenu_itemhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  2 //line
};

int CreateMenuGui(void)
{
  void *ma=malloc_adr();
  void *gui=GetMultiLinesMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, &gmenu);
  SetMenuItemCount(gui, (wordcount-start_index < GMENU_ITEM_N)?(wordcount-start_index):GMENU_ITEM_N);
  //MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, 0);
  SetMenuSearchCallBack(gui, SearchCallBack);
  patch_header(&gmenuhdr);
  SetHeaderToMenu(gui, &gmenuhdr, ma);
  return (CreateGUI(gui));
}

//--------------------send sms----------------------

IPC_REQ mss_ipc=
{
  "MySMSYS",
  "MySMSYS",
  NULL
};

#define SMSYS_IPC_SEND_WS 0x88 //»ùÓÚwsÐÂ½¨¶ÌÐÅ,data=ws

int SendMySMS(WSHDR *ws)
{
  WSHDR *data;
  if(!ws || !ws->wsbody[0]) return 0;
  data=AllocWS(ws->wsbody[0]);
  wstrcpy(data, ws);
  LockSched();
  mss_ipc.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SEND_WS,&mss_ipc);
  UnlockSched();
  return 1;
}

//--------------------Create a Edit GUI from Show Words----------------------------
#define MAX_UNICODE_STR 512

int s_index=9;

int sd_onkey(GUI *gui, GUI_MSG *msg)
{
  int keys=msg->keys;
  //right 0x27
  //left 0x28
  //up 0x26
  //down 0x25
  WSHDR *ws, wsn;
  unsigned short wsb[MAX_UNICODE_STR];
  if(keys==1) return 1;
  ws=CreateLocalWS(&wsn, wsb, MAX_UNICODE_STR);
  if(keys==0x27 || keys==0x25)
  {
    if(s_index<wordcount)
    {
      s_index++;
      construct_entry_text(ws, index[s_index], 1, 1/*fw_phoneticÏÔÊ¾Òô±ê*/, 1);
      EDIT_SetTextToEditControl(gui, 1, ws);
      REDRAW();
    }
  }
  else if(keys==0x28 || keys==0x26)
  {
    if(s_index>9)
    {
      s_index--;
      construct_entry_text(ws, index[s_index], 1, 1/*fw_phoneticÏÔÊ¾Òô±ê*/, 1);
      EDIT_SetTextToEditControl(gui, 1, ws);
      REDRAW();
    }
  }
  else if(keys==0x5)
  {
    EDITCONTROL ec;
    ExtractEditControl(gui, 1, &ec);
    if(SendMySMS(ec.pWS)) return 1;
  }
  return 0;
}

void sd_locret(void){}

const INPUTDIA_DESC sd_desc=
{
  1,
  sd_onkey,
  NULL,
  (void *)sd_locret,
  0,
  &gmenu_skt,
  {0,0,0,0},
  FONT_MEDIUM,
  100,
  101,
  0,
  0,
  0x40000000
};


const HEADER_DESC sdhdr={0,0,0,0,NULL,(int)"Ó¢ºº×Öµä",LGP_NULL};

int ShowDetial(int eindex)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws, wsn;
  unsigned short wsb[MAX_UNICODE_STR];
  EDITCONTROL ec;
  s_index=eindex;
  if(eindex>=wordcount) return 0;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma, mfree_adr());
  ws=CreateLocalWS(&wsn, wsb, MAX_UNICODE_STR);
  construct_entry_text(ws, index[eindex], 1, 1/*fw_phoneticÏÔÊ¾Òô±ê*/, 1);
  ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, MAX_UNICODE_STR);
  AddEditControlToEditQend(eq, &ec, ma);
  patch_input(&sd_desc);
  patch_header(&sdhdr);
  return (CreateInputTextDialog(&sd_desc, &sdhdr, eq, 1, 0));
}

//--------------------Input Gui---------------------

int ip_onkey(GUI *data, GUI_MSG *msg)
{
  if(msg->keys==1 || msg->keys==0x5) return 1; //green button
  if(msg->keys==0x1A) //left soft
  {
    EDITCONTROL ec;
    char word[128];
    int pos;
    void *menugui=EDIT_GetUserPointer(data);
    ExtractEditControl(data, 1, &ec);
    if(!ec.pWS->wsbody[0]) return 1;
    ws2estr(ec.pWS, word, 127);
    if((pos=lookup(word))>=0)
    {
      start_index=pos;
      if(menugui)
      {
	SetCursorToMenuItem(menugui, 0);
	Menu_SetItemCountDyn(menugui, (wordcount-start_index < GMENU_ITEM_N)?(wordcount-start_index):GMENU_ITEM_N);
      }
    }
    return 1;
  }
  return 0;
}

const INPUTDIA_DESC ip_desc=
{
  1,
  ip_onkey,
  NULL,
  (void *)sd_locret,
  0,
  &gmenu_skt,
  {0,0,0,0},
  FONT_MEDIUM,
  100,
  101,
  0,
  0,
  0x40000000
};

int DoInput(void *menugui)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws, wsn;
  unsigned short wsb[MAX_UNICODE_STR];
  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma, mfree_adr());
  ws=CreateLocalWS(&wsn, wsb, MAX_UNICODE_STR);
  CutWSTR(ws, 0);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, MAX_UNICODE_STR);
  AddEditControlToEditQend(eq, &ec, ma);
  patch_input(&ip_desc);
  patch_header(&sdhdr);
  return (CreateInputTextDialog(&ip_desc, &sdhdr, eq, 1, menugui));
}

//--------------------CSM-------------------


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

unsigned int MAIN_CSM_ID=0;
void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;  
  if(LoadDictIndex() && OpenDict())
  {
    csm->gui_id=CreateMenuGui();
  }
  else csm->csm.state=-3;
}

void maincsm_onclose(CSM_RAM *csm)
{
  UnloadDictIndex();
  CloseDict();
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
  }
  return(1);
}

unsigned short maincsm_name_body[140];
const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "%t", "Ó¢ºº´Êµä");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAIN_CSM_ID=CreateCSM(&MAINCSM.maincsm, dummy, 0);
  UnlockSched(); 
  return 0;
}




