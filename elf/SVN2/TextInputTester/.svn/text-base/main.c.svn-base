#include "..\inc\swilib.h"

void Log(int dummy, char *txt)
{
  unsigned int ul;
  int f=fopen("4:\\log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
    fclose(f,&ul);
  }
  mfree(txt);
}


static const char percent_t[]="%t";

int icon[]={0x58,0};
const int minus11=-11;

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
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
  EDITCONTROL ec;
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==GREEN_BUTTON)
    {
/*      EDIT_RemoveEditControl(data,1,&ec);
      PrepareEditControl(&ec);
      wsprintf(ews,percent_t,"Добавленное поле");
      ConstructEditControl(&ec,3,0x40,ews,256);
      EDIT_InsertEditControl(data,10,&ec);
      EDIT_SetFocus(data,10);
      EDIT_SetCursorPos(data,3);*/
/*      ExtractEditControl(data,EDIT_GetFocus(data),&ec);
      wstrcpy(ews,ec.pWS);
      wsAppendChar(ews,0xE12B);
      EDIT_SetTextToFocused(data,ews);      */
      ExtractEditControl(data,3,&ec);
      WSHDR *sw=AllocWS(ec.pWS->wsbody[0]);
      wstrcpy(sw,ec.pWS);
//      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,2); //С редактированием
//      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,6); //Сразу в бой с окошком
//      SendSMS(sw,"+380636038122",0x4209,MSG_SMS_RX-1,6);
      return(-1);
    }
  }
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

GBSTMR mytmr;

void *edit_data;

void TestTimerProc(void)
{
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
  if (edit_data)
  {
    wsprintf(ws1,"%08x",EDIT_IsBusy(edit_data));
    DrawString(ws1,20,0,100,22,
	     FONT_SMALL,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
  }
  GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
}


void ed1_ghook(GUI *data, int cmd)
{
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
  EDITCONTROL ec;
  int i;
  if (cmd==2)
  {
    //Create
    edit_data=data;
    GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
  }
  if (cmd==3)
  {
    edit_data=NULL;
    GBS_DelTimer(&mytmr);
  }
  if (cmd==7)
  {
    //OnRun
//    SetSoftKey(data,&sk,1);
    ExtractEditControl(data,3,&ec);
    wstrcpy(ews,ec.pWS);
  }
  if (cmd==0x0D)
  {
    //onCombo
    if ((i=EDIT_GetItemNumInFocusedComboBox(data)))
    {
      wsprintf(ews,"%t%d","Пункт: ",i);
    }
    else
    {
      ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
      wstrcpy(ews,ec.pWS);
    }
    EDIT_SetTextToFocused(data,ews);
  }
}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"Редактор",LGP_NULL};

INPUTDIA_DESC ed1_desc=
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
  0x40000000 // Поменять местами софт-кнопки
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,"%08X ",ed1_desc._0x40000000);
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Обычная строка:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Медвед!!!");
  ConstructEditControl(&ec,3,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Строка с номером телефона:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"123456789*#");
  ConstructEditControl(&ec,2,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Число (фикс. кол. цифр):");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"3");
  ConstructEditControl(&ec,5,0x40,ews,5);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Число (произв. кол. цифр):");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"123");
  ConstructEditControl(&ec,6,0x40,ews,5);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"ComboBox:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"item1");
  ConstructComboBox(&ec,7,0x40,ews,10,0,3,1);
  AddEditControlToEditQend(eq,&ec,ma);

  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

int create_menu(void);
int create_menu2(void);

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  csm->gui_id=create_ed();
//  csm->gui_id=create_menu();
//  csm->gui_id=create_menu2();
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
      /*if (ed1_desc._0x40000000)
      {
	ed1_desc._0x40000000<<=1;
	csm->gui_id=create_ed();
      }
      else*/
      {
	csm->csm.state=-3;
      }
    }
  }
  if ((msg->msg==MSG_SMS_RX)||(msg->msg==(MSG_SMS_RX-1)))
  {
    char *s=malloc(100);
    sprintf(s,"%08X %08X %08X %08X\r\n",msg->msg,msg->submess,msg->data0,msg->data1);
    SUBPROC((void *)Log,0,s);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TextInputTester");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

//=-----
// Тест меню
//=-----
const int S_ICONS[]={0x162,0x232,0x22F,0x17A,0x195,0x231,0x185,0x22C,
0x24C, //message
0x185, //Unknown
0x0 //Конец списка
};

char hdrtxt[32];

HEADER_DESC contactlist_menuhdr={0,0,131,21,NULL,(int)hdrtxt,LGP_NULL};
int menusoftkeys[]={0,1,2};
/*SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};*/

void contactlist_menu_ghook(void *data, int cmd);
int contactlist_menu_onkey(void *data, GUI_MSG *msg);
void contactlist_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC contactlist_menu=
{
  8,contactlist_menu_onkey,contactlist_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  contactlist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int create_menu(void)
{
  int i=256;
//  wsprintf(ews,percent_t,"Медвед!");
  return(CreateMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i,0,0));
}

void contactlist_menu_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data,10);
  wsprintf(ws,"%d",curitem);
  SetMenuItemIconArray(data,item,S_ICONS);
  SetMenuItemText(data,item,ws,curitem);
  SetMenuItemIcon(data,curitem,curitem&7);
}

void contactlist_menu_ghook(void *data, int cmd)
{
}

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{
  int c;
  int l;
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    c=msg->gbsmsg->submess;
    if ((c>='0')&&(c<='9'))
    {
      l=strlen(hdrtxt);
      if (l<31) hdrtxt[l]=c;
      RefreshGUI();
      return(-1);
    }
  }
  if (msg->keys==0x18)
  {
//    GeneralFunc_F1(1);
    ShowMSG(1,(int)"Under construction!");
    return(-1);
  }
  if (msg->keys==0x3D)
  {
//    GeneralFunc_F1(1);
    return(-1);
  }
  return(0);
}


int menu2_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x3D)
  {
//    GeneralFunc_F1(1);
    return(-1);
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int c=msg->gbsmsg->submess;
    if ((c>='0')&&(c<='9'))
    {
      Menu_SetItemCountDyn(data,c-'0');
      return(-1);
    }
  }
  return(0);
}

void menu2_ghook(void *data, int cmd)
{
}

/*
extern int CreateMultiLinesMenu(int dummy,int dummy2,const ML_MENU_DESC *,const HEADER_DESC *,int to_item,int n);
extern void SetMLMenuItemText(void *data,void *item,WSHDR *ws1,WSHDR *ws2,int unk0or1,int n);
extern void *AllocMLMenuItem(void *data);
*/

void menu2_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  WSHDR *ws1=AllocMenuWS(data,30);
  WSHDR *ws2=AllocMenuWS(data,30);
  wsprintf(ws1,"Line 1 %d zzzz1234zzzz56789",curitem);
  wsprintf(ws2,"Line 2 %d zzzz\n",curitem);
  wsAppendChar(ws2,0xE116);
  wsAppendChar(ws2,0xE117);
  SetMenuItemIconArray(data,item,S_ICONS+(curitem&7));
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

static const ML_MENU_DESC menu2=
{
  8,
  menu2_onkey,
  menu2_ghook,
  NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  menu2_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  2
};

int create_menu2(void)
{
  wsprintf(ews,percent_t,"Меню2!");
  return(CreateMultiLinesMenu(0,0,&menu2,&contactlist_menuhdr,0,10));
}

