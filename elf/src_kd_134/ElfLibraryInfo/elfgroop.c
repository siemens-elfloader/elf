#include "C:/arm/inc/swilib.h"
#include "elfsubmainmenu.h"
#include "elfgroop.h"
#include "main.h"
int Sys_ID,Int_ID,Gam_ID,Uti_ID,Mlt_ID;
//==============================================================================
//KIBER-DEMON
void  Adinf(GUI *data){E1();};//Сист
void  Analyzer(GUI *data){E2();};//Сист
void  BLIBinfo(GUI *data){E3();};//Сист
void  BogoMIPS(GUI *data){E4();};//Сист
void  BV(GUI *data){E5();};//Сист
void  CallAlert(GUI *data){E6();};//Сист
void  CallCenter(GUI *data){E7();};//Сист
void  CPUD(GUI *data){E8();};//Сист
void  CpuNapryag(GUI *data){E9();};//Сист
void  DPU(GUI *data){E10();};//Сист
void  DropCall(GUI *data){E11();};//Сист
void  FreeSpaced(GUI *data){E12();};//Сист
void  JavaSwitcher(GUI *data){E13();};//Сист
void  JoyVibra(GUI *data){E14();};//Сист
void  LightControl(GUI *data){E15();};//Сист
void  LogSms(GUI *data){E16();};//Сист
void  MapView(GUI *data){E17();};
void  RT(GUI *data){E18();};//Сист
void  smd2bin(GUI *data){E19();};
void  Stime(GUI *data){E20();};
void  ElfLibraryInfo(GUI *data){E21();};
//VEDAN
void  CSM(GUI *data){E22();};
void  ElfsGlue(GUI *data){E23();};
void  ElfStart(GUI *data){E24();};
void  FAV(GUI *data){E25();};
void  FFSaver(GUI *data){E26();};
void  FreeRAM(GUI *data){E27();};
void  GprsD(GUI *data){E28();};
void  GPSLogger(GUI *data){E29();};
void  MissedEvents(GUI *data){E30();};
void  PTable(GUI *data){E31();};
void  NATICQ(GUI *data){E32();};
void  SieJC(GUI *data){E33();};
//KIBER-DEMON
void  StopWatch(GUI *data){E34();};
void  eTimer(GUI *data){E35();};
void  AccessoryMon(GUI *data){E36();};
void  ConfManager(GUI *data){E37();};
void  Count(GUI *data){E38();};
void  iBlock(GUI *data){E39();};
void  ImgIDLE(GUI *data){E40();};
void  ChangeCap(GUI *data){E41();};
void  XShed(GUI *data){E42();};
void  Watch(GUI *data){E43();};
void  VibAtConnect(GUI *data){E44();};
void  VOC(GUI *data){E45();};
void  VCMD(GUI *data){E46();};
void  Translate(GUI *data){E47();};
void  Clock(GUI *data){E48();};
void  Command(GUI *data){E49();};
void  DisplayShooter(GUI *data){E50();};
//VEDAN: 9.11.07
void  Unrar(GUI *data){E51();};
void  Unzip(GUI *data){E52();};
void  Un7z(GUI *data){E53();};
void  Dendy(GUI *data){E54();};
void  Sega(GUI *data){E55();};
void  Tetris(GUI *data){E56();};
void  Baloons(GUI *data){E57();};
void  Sokoban(GUI *data){E58();};
void  IvoPlay(GUI *data){E59();};
void  SPlayer(GUI *data){E60();};
void  WavPlayer(GUI *data){E61();};
//KIBER-DEMON: 26.11.07
void  MailWeather(GUI *data){E62();};
void  TA(GUI *data){E63();};
void  Tamagochi(GUI *data){E64();};
void  GFleet(GUI *data){E65();};
void  InstJar(GUI *data){E66();};
void  KeyTest(GUI *data){E67();};
void  KeypadLight(GUI *data){E68();};
void  Light(GUI *data){E69();};
void  McKey(GUI *data){E70();};

#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

//Общее-------------------------------------------------------------------------

void ALL_ghook(void *data, int cmd){if (cmd==0x0A){DisableIDLETMR();}}

static const SOFTKEY_DESC immenu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

int SYSsoftkeys[]={0,1,2};
static const SOFTKEYSTAB immenu_skt={immenu_sk,0};
int GRsoftkeys[]={0,1,2};

#ifdef ELKA
int g_sys_icon[]={0x120,0};
int g_int_icon[]={0x2C7,0};
int g_gam_icon[]={0x3CA,0};
int g_uti_icon[]={0x2C9,0};
int g_mlt_icon[]={0x04D,0};
#else
#ifdef NEWSGOLD
int g_sys_icon[]={0x148,0};
int g_int_icon[]={0x22C,0};
int g_gam_icon[]={0x3E9,0};
int g_uti_icon[]={0x22E,0};
int g_mlt_icon[]={0x062,0};
#else
int g_sys_icon[]={0xFA0,0};
int g_int_icon[]={0xFA0,0};
int g_gam_icon[]={0xFA0,0};
int g_uti_icon[]={0xFA0,0};
int g_mlt_icon[]={0xFA0,0};
#endif
#endif

//Системные---------------------------------------------------------------------

#define SYS_NUM 15
HEADER_DESC ALL={0,0,131,21,g_sys_icon,(int)"Системные:",0x7FFFFFFF};
static const MENUPROCS_DESC MP1[SYS_NUM]=
{
AccessoryMon,
Adinf,
Analyzer,
BogoMIPS,
BV,
CPUD,
CSM,
DPU,
DropCall,
FreeRAM,
JavaSwitcher,
LightControl,
RT,
TA,
VibAtConnect,
};

static int immenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(MP1[GetCurMenuItem(data)]))();
  }
  return(0);
}

MENUITEM_DESC SYSitems[SYS_NUM]=
{
{g_sys_icon,(int)"AccessoryMon",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"Adinf",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"Analyzer",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"BogoMIPS",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"BV",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"CPUD",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"CSM",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}, 
{g_sys_icon,(int)"DPU",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"DropCall",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"FreeRAM",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"JavaSwitcher",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"LightControl",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"RT",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"TA",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_sys_icon,(int)"VibAtConnect",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}  
};

static const MENU_DESC itmenu=
{
  8,immenu_keyhook,ALL_ghook,NULL,
  GRsoftkeys,
  &immenu_skt,
  1,
  NULL,
  SYSitems, 
  MP1, 
  SYS_NUM
};

void Sys()
{
  patch_header(&ALL);
  Sys_ID = CreateMenu(0,0,&itmenu,&ALL,0,SYS_NUM ,0,0);
};

//Утилиты-----------------------------------------------------------------------

#define UTI_NUM 38
HEADER_DESC UTI={0,0,131,21,g_uti_icon,(int)"Утилиты:",0x7FFFFFFF};

static const MENUPROCS_DESC MP2[UTI_NUM]=
{
BLIBinfo,  
CallCenter,  
CallAlert,
ChangeCap,
Clock,
Command,
ConfManager,
Count,
CpuNapryag,
GPSLogger,
ElfLibraryInfo,
ElfStart,
eTimer,
FAV,
FreeSpaced,
iBlock,
ImgIDLE,
InstJar,
JoyVibra,
KeypadLight,
KeyTest,
Light,
LogSms,
MapView,
McKey,
MissedEvents,
PTable,
Stime,
StopWatch,
smd2bin,
Translate,
VCMD,
VOC,
Un7z,
Unzip,  
Unrar,
Watch,
XShed,
};

static int I_K2(void *data, GUI_MSG *msg){if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(MP2[GetCurMenuItem(data)]))();}return(0);}

MENUITEM_DESC UTI_I[UTI_NUM]=
{
{g_uti_icon,(int)"BLIBinfo",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"CallCenter",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"CallAlert",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"ChangeCap",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Clock",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Command",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"ConfManager",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Count",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"CpuNapryag",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"GPSLogger",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"ElfLibraryInfo",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"ElfStart",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"eTimer",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"FAV",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"FreeSpaced",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"iBlock",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"ImgIDLE",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"InstJar",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"JoyVibra",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"KeypadLight",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"KeyTest",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Light",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"LogSms",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"MapView",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"McKey",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"MissedEvents",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"PTable",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Stime",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"StopWatch",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"smd2bin",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Translate",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"VCMD",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"VOC",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Un7z",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Unzip",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Unrar",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"Watch",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_uti_icon,(int)"XShed",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

static const MENU_DESC I2=
{
  8,I_K2,ALL_ghook,NULL,
  GRsoftkeys,
  &immenu_skt,
  1,
  NULL,
  UTI_I, 
  MP2, 
  UTI_NUM
};

void Uti()
{
  patch_header(&UTI);
  Uti_ID = CreateMenu(0,0,&I2,&UTI,0,UTI_NUM ,0,0);
};

//Интернет----------------------------------------------------------------------

#define INE_NUM 4
HEADER_DESC INE={0,0,131,21,g_int_icon,(int)"Интернет:",0x7FFFFFFF};

static const MENUPROCS_DESC MP5[INE_NUM]=
{
GprsD,
MailWeather,
NATICQ,
SieJC
};

static int I_K5(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(MP5[GetCurMenuItem(data)]))();
  }
  return(0);
}

MENUITEM_DESC INE_I[INE_NUM]=
{
{g_int_icon,(int)"GprsD",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_int_icon,(int)"MailWeather",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_int_icon,(int)"NATICQ",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_int_icon,(int)"SieJC",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

static const MENU_DESC I5=
{
  8,I_K5,ALL_ghook,NULL,
  GRsoftkeys,
  &immenu_skt,
  1,
  NULL,
  INE_I, 
  MP5, 
  INE_NUM
};

void Int()
{
  patch_header(&INE);
  Int_ID = CreateMenu(0,0,&I5,&INE,0,INE_NUM ,0,0);
};

//Игры--------------------------------------------------------------------------

#define GAM_NUM 6
HEADER_DESC GAM={0,0,131,21,g_gam_icon,(int)"Игры:",0x7FFFFFFF};

static const MENUPROCS_DESC MP7[GAM_NUM]=
{
Baloons,
Dendy,
Tetris,
Sega,
Sokoban,
Tamagochi
};

static int I_K7(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(MP7[GetCurMenuItem(data)]))();
  }
  return(0);
}

MENUITEM_DESC GAM_I[GAM_NUM]=
{
{g_gam_icon,(int)"Baloons",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_gam_icon,(int)"Dendy",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_gam_icon,(int)"Tetris",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_gam_icon,(int)"Sega",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_gam_icon,(int)"Sokoban",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_gam_icon,(int)"Tamagochi",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

static const MENU_DESC I7=
{
  8,I_K7,ALL_ghook,NULL,
  GRsoftkeys,
  &immenu_skt,
  1,
  NULL,
  GAM_I, 
  MP7, 
  GAM_NUM
};

void Gam()
{
  patch_header(&GAM);
  Gam_ID = CreateMenu(0,0,&I7,&GAM,0,GAM_NUM ,0,0);
};

//Мультимедиа-------------------------------------------------------------------

#define MUL_NUM 4
HEADER_DESC MUL={0,0,131,21,g_mlt_icon,(int)"Мультимедиа:",0x7FFFFFFF};

static const MENUPROCS_DESC MP6[MUL_NUM]=
{
GFleet,
IvoPlay,
SPlayer,
WavPlayer,
};

static int I_K6(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(MP6[GetCurMenuItem(data)]))();
  }
  return(0);
}

MENUITEM_DESC MUL_I[MUL_NUM]=
{
{g_mlt_icon,(int)"GFleet",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_mlt_icon,(int)"IvoPlay",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_mlt_icon,(int)"SPlayer",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{g_mlt_icon,(int)"WavPlayer",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

static const MENU_DESC I6=
{
  8,I_K6,ALL_ghook,NULL,
  GRsoftkeys,
  &immenu_skt,
  1,
  NULL,
  MUL_I, 
  MP6, 
  MUL_NUM
};

void Mlt()
{
  patch_header(&GAM);
  Mlt_ID = CreateMenu(0,0,&I6,&MUL,0,MUL_NUM ,0,0);
};
