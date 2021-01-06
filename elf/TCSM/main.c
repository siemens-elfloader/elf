#include "..\inc\swilib.h"

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

__root int xxx=123;
volatile static int yyy;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

//#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
#define RGB8(R,G,B) (B+(G<<2)+(R<<5))

/*const unsigned short img1_bmp[]={
 0x00,0x00,0x00,
 RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
 RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
 RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
 RGB16(31,63,0),RGB16(31,63,0),RGB16(31,63,0),
 0x00,0x00,0x00
};*/

unsigned char img1_bmp[128*128];

const IMGHDR img1=
{
  128,
  128,
  5,
  (char *)img1_bmp
};

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

void Play(const char *fname)
{
  PLAYFILE_OPT _sfo1;
  WSHDR* sndPath=AllocWS(128);
  WSHDR* sndFName=AllocWS(128);
  char s[128];
  int i;
  const char *p=strrchr(fname,'\\')+1;
  str_2ws(sndFName,p,128);
  strncpy(s,fname,p-fname);
  str_2ws(sndPath,s,128);
//  if ((!IsCalling())&&Is_Sounds_Enabled)
  {
    char *s=malloc(100);
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=6;
#ifdef NEWSGOLD
    _sfo1.unk6=1;
    _sfo1.unk7=1;
    _sfo1.unk9=2;
    i=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
    i=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
    sprintf(s,"%08X\r\n",i);
    SUBPROC((void *)Log,0,s);
  }
  FreeWS(sndPath);
  FreeWS(sndFName);
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void method0(MAIN_GUI *data)
{
  int i;
  int c;
  DrawRoundedFrame(0,0,131,175,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(20));
  c=data->i1;
  i=0;
  do
  {
    img1_bmp[i++]=c;
    if (i&127) c++;
  }
  while(i<(128*128));
  DrwImg((IMGHDR *)&img1,2,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  wsprintf(data->ws1,"Redraw number %d",++data->i1);
  DrawString(data->ws1,5,30,121,100,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  wsprintf(data->ws2,"MSG:%08X %08X",msg->gbsmsg->msg,msg->gbsmsg->submess);
  DrawString(data->ws2,5,45,131,55,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    case '5':
      Play("4:\\ZBin\\NatICQ\\Sounds\\sndStartup.wav");
      break;
    case '6':
      Play("4:\\ZBin\\NatICQ\\Sounds\\sndMsgSent.wav");
      break;
    case '8':
      {
	void TestMenu(void);
	TestMenu();
      }
      break;
    case '0':
      ShowMSG(1,(int)"Нажали '0'");
      break;
    }
  }
//  method0(data);
  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
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
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ELF_KILLER);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_PLAYFILE_REPORT)
  {
    char *s=malloc(100);
    sprintf(s,"%08X %08X %08X\r\n",msg->submess,msg->data0,msg->data1);
    SUBPROC((void *)Log,0,s);
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TCSM");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

//---------------------------------------------------------------------------
// Test menu
//---------------------------------------------------------------------------
void menup1(GUI *data)
{
      ShowMSG(1,(int)"Тестовое сообщение 1");
}

void menup2(GUI *data)
{
      ShowMSG(1,(int)"Тестовое сообщение 2");
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,131,21,icon,(int)"Заголовок меню",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[2]=
{
  {NULL,(int)"Пункт 1",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Пункт 2",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[2]={
  menup1,
  menup2
};

const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  (SOFTKEY_DESC *)menu_sk,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  menuitems,
  menuprocs,
  2
};

void TestMenu(void)
{
  CreateMenu(0,0,&tmenu,&menuhdr,0,2,0,0);
}


