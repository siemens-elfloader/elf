#include "\ARM\inc\swilib.h"
#include "conf_loader.h"

#define isElka() (isnewSGold()==2)
#define UNI_YDISP (isElka()?24:0)

typedef struct
{
  int flag; //0, 8, 16 хз
  int (*onKey)(GUI *gui, GUI_MSG *msg);
  void (*global_hook_proc)(GUI *gui, int cmd);
  void *locret; //0
  const int *softkeys;
  const SOFTKEYSTAB *softkeystab;
  int unkflag; //1
  int lgp_null;
  const int *icons; //&x52A
  int pos; //0 (pos?)
  int font; //4
  int textcolor; //0x64
  int _101;
  int timeout; //0-forever
} MSG_BOX;

typedef struct
{
  int *icon_inact;
  int *icon_big;
  int lgp_id;
  void (*run)();
} NATMENU_ITEM_DESC;

int(*MsgBox)(int _1, int, MSG_BOX*, int lgp_id);
void(*AddHeader)(GUI*,HEADER_DESC*,void* malloc_adr);
int m; //коэффициент для формулы = isnewSGold

#pragma inline
void patch_header(const HEADER_DESC* headc)
{
  HEADER_DESC *head=(HEADER_DESC *)headc;
  head->rc.x=0;
  head->rc.y=UNI_YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+UNI_YDISP;
}

void ElfKiller()
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

CSM_DESC icsmd;

//int (*oldIcsmOnMessage)(CSM_RAM*,GBS_MSG*);
void (*oldIcsmOnClose)(CSM_RAM*);

//----------------MMenu----------------
int MHico;
HEADER_DESC MHeader={0, 0, 0, 0, &MHico, 0, LGP_NULL};
int MSoftKeys[]={0,1,2};

SOFTKEY_DESC Msk[]=
{
  {0x0018,0x0000,(int)""},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB Mskt=
{
  Msk,0
};

GBSTMR tmr;
NATMENU_ITEM_DESC *items;
short hs[]={56,101,159,204};
int pic_n=0;
int pos=4;
#define TIME 262/5

void PickNumTmr()
{
  pic_n++;
  if(pic_n>4)
    pic_n=0;
  DirectRedrawGUI();
  GBS_StartTimerProc(&tmr, TIME, PickNumTmr);
}

void UpdateHeader(GUI* gui)
{
  MHico=*items[pos].icon_inact-11-m; //Значек заголовка
  ((int*)GetDataOfItemByID(gui, 2))[13]=items[pos].lgp_id; //Текст заголовка
}

void TmrReset()
{
  GBS_DelTimer(&tmr);
  pic_n=0;
  GBS_StartTimerProc(&tmr, TIME, PickNumTmr);
}

void (*OOnRedraw)(GUI *data);
void NOnRedraw(GUI *data)
{
  OOnRedraw(data); //Сначала старый OnRedraw

  for(int i=0;i<12;i++)
  {
    if(i==pos)continue;
/* --==Формула==--
 * x= 3m+2+(36m+5)j 
 * y=31m-2+(28m+2)i
 */
    int x=3*m+2+(36*m+5)*(i%3);
    int y=31*m-2+(28*m+2)*(i/3);
    int pic=*items[i].icon_inact;
    DrawImg(x,y,pic);
  }
  if(m==2)
    DrawImg(pos%3*(77)+1,hs[pos/3],items[pos].icon_big[pic_n]);
  else
    DrawImg(3*m+2+(36*m+5)*(pos%3),31*m-2+(28*m+2)*(pos/3),items[pos].icon_big[pic_n]);
}

const void * NGuiMeths[11];

void MGHook(GUI *gui, int cmd)
{
  switch(cmd)
  {
  case 1://Создание: подмена onRedraw + добавление хедера
    {
      AddHeader(gui,&MHeader,malloc_adr());
      memcpy(NGuiMeths,gui->methods,11*sizeof(void*));
      gui->methods=(void*)NGuiMeths;
      OOnRedraw=(void(*)(GUI*))NGuiMeths[0];//(gui->methods[0]);
      NGuiMeths[0]=(void*)NOnRedraw;
    }
    break;
  case 5://Получение фокуса (?)
    TmrReset();
    break;
  case 6://Потеря фокуса
    UpdateHeader(gui);
    GBS_DelTimer(&tmr);//Экономим ресурсы (типо)
    break;
  }
}

int MOnKey(GUI *gui, GUI_MSG *msg)
{
  int key=msg->gbsmsg->submess;
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(pos==0 && (key==LEFT_BUTTON | key==UP_BUTTON))
    {
      pos=11;
      goto end;
    }
    if(pos==11 && (key==RIGHT_BUTTON | key==DOWN_BUTTON))
    {
      pos=0;
      goto end;
    }
    switch(key)
    {
    case ENTER_BUTTON:
      goto run;
    case LEFT_BUTTON:
      pos--;
      break;
    case RIGHT_BUTTON:
      pos++;
      break;
    case UP_BUTTON:
      pos-=3;
      break;
    case DOWN_BUTTON:
      pos+=3;
      break;
    case RIGHT_SOFT:
      GBS_DelTimer(&tmr);
      return(0);
    case '*':
      pos=9;
      goto run;
    case '0':
      pos=10;
      goto run;
    case '#':
      pos=11;
      goto run;
    default:
      if(key>='1' && key<='9')
      {
        pos=key-1-'0';
        goto run;
      }
      else
        return(0);
    }
    if(pos<0)
      pos+=11;
    if(pos>11)
      pos-=11;

  end:
    UpdateHeader(gui);
    TmrReset();
    RefreshGUI();
    return(0);
  run:
    items[pos].run();
    return(0);
  }
  return(0);
}

MSG_BOX MMenu=
{
  0,
  MOnKey,
  MGHook,
  0,
  MSoftKeys,
  &Mskt,
  1,
  LGP_NULL,
  0,
  0,
  0,
  0x64,
  0x65,
  0
};
//-----------------CSM-----------------
const int minus11=-11;
unsigned short maincsm_name_body[140];
int MCSMid;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

__thumb void MOnCreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  MHico=*items[4].icon_inact-11-m;
  csm->gui_id=MsgBox(0,0,&MMenu,LGP_NULL);
}

__thumb int MOnMsg(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    csm->csm.state=-3;
  return(1);
}

void MOnClose(CSM_RAM *csm)
{
  GBS_DelTimer(&tmr);
  pos=4;
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  MOnMsg,
  MOnCreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  MOnClose,
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
//-------------------------------------

/*int newIcsmOnMessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
    InitConfig();

  return oldIcsmOnMessage(data,msg);
}*/

GBSTMR errtmr;
GUI * errgui;

#pragma swi_number=0x37
__swi __arm void Ringtones_SetState(unsigned char state);

void ErrTmr()
{
  if(errgui==NULL)
    errgui=GetTopGUI();
  if(errgui==GetTopGUI())
  {
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
    GBS_StartTimerProc(&errtmr, 262/3, ErrTmr);
  }
  else
    Ringtones_SetState(0);
}

int hook(int submsg, int msg)
{
  if (IsUnlocked() && submsg==ENTER_BUTTON && msg==KEY_DOWN)
    if (IsGuiOnTop(((int *)FindCSMbyID(CSM_root()->idle_id))[DISPLACE_OF_IDLEGUI_ID/4]))
    {
      if(FindCSMbyID(MCSMid))
        CloseCSM(MCSMid);
      char dummy[sizeof(MAIN_CSM)];
      LockSched();
      MCSMid=CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
      return(2);
    }
  return (0);
}

void newIcsmOnClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  RemoveKeybMsgHook((void *)hook);
  seqkill(data,oldIcsmOnClose,&ELF_BEGIN,SEQKILLER_ADR());
}

__thumb unsigned int GetBLAddr(unsigned int adr)
{
  short _1_11=((short*)adr)[0];
  int _1=(_1_11&0x7FF)<<11|(_1_11&0x0400?0xFFC00000:0);
  short _2=((short*)adr)[1]&0x7FF;
  return(unsigned int)(adr+_1*2+_2*2+4+(_1_11>>12&1));
}

void main()
{
  unsigned int adr;

  //Нахожу функцию MsgBox
  #pragma swi_number=0x8050
  __swi __arm unsigned int MsgBoxOkCancel_adr();
  adr=MsgBoxOkCancel_adr()+7; //Тут лежит инструкция "B MsgBox"
  MsgBox=(int(*)(int,int,MSG_BOX*,int))(adr+(short)((*(short*)adr|0xF800))*2+5);

  //Нахожу функцию AddHeader
  #pragma swi_number=0x8152
  __swi __arm unsigned int CreateMenu_adr();
  AddHeader=(void(*)(GUI*,HEADER_DESC*,void*))GetBLAddr(GetBLAddr(CreateMenu_adr()+33)+123);

  //Нахожу таблицу пунктов NativeMenu
  #pragma swi_number=0x8061
  __swi __arm unsigned int ShowNativeMenu_adr();
  adr=GetBLAddr(GetBLAddr(ShowNativeMenu_adr()+1)+9)+23;
  items=*(void**)((adr&0xFFFFFFFD)+*(char*)adr*4+4);
  
  m=isnewSGold();

  patch_header(&MHeader);
  MHeader.lgp_id=items[4].lgp_id;

  wsprintf((WSHDR*)&MAINCSM.maincsm_name,"%t","Главное меню");

  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  oldIcsmOnClose=icsmd.onClose;
  icsmd.onClose=newIcsmOnClose;
  icsm->constr=&icsmd;
  AddKeybMsgHook((void *)hook);
  UnlockSched();

  #pragma swi_number=0x8060
  __swi __arm void* ShowMainMenu_adr();
  static GBSTMR mmtmr;
  Ringtones_SetState(1);
  GBS_StartTimerProc(&mmtmr, 262*5, (void(*)())ShowMainMenu_adr());
  GBS_StartTimerProc(&errtmr, 262*5+262/3, ErrTmr);
}
