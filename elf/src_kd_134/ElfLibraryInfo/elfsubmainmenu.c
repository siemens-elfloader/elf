#include "C:/arm/inc/swilib.h"
#include "elfsubmainmenu.h"

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

static const SOFTKEY_DESC immenu_sk_elf[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

#define ELF_NUM 3
static const SOFTKEYSTAB immenu_skt_elf={immenu_sk_elf,0};
extern const int fontsize;
extern void patch_header(HEADER_DESC* head);
extern void patch_input(INPUTDIA_DESC* inp);
static const char percent_t[]="%t";
int elf_imsk[]={0,1,2};

#ifdef ELKA
int elf_icon[]={0x0FE,0};
int info_icon[]={0x156,0};
#else
#ifdef NEWSGOLD
int elf_icon[]={0x5FD,0};
int info_icon[]={0x17D,0};
#else
int elf_icon[]={0xFA0,0};
int info_icon[]={0xFA0,0};
#endif
#endif

void immenu_ghookElf(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const char * const imenutextsES[ELF_NUM]={"Автор","Информация","Где скачать"};

void imenuitemhandlerES(void *data, int curitem, void *unk)
{
 WSHDR *ws;
 void *item=AllocMenuItem(data);
 ws=AllocMenuWS(data,strlen(imenutextsES[curitem]));
 wsprintf(ws,imenutextsES[curitem]);
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,0);
    break;
  case 1:
    SetMenuItemIconArray(data,item,0);
    break;
    }
  SetMenuItemText(data, item, ws, curitem);
}

//====Объект EDITCONTROL========================================================

void inp_locret(void){}
WSHDR *ews;
int info_onkey(GUI *gui, GUI_MSG *msg){if (msg->keys==0x18){return(-1);}return(0);}
void info_ghook(GUI *gui, int cmd){if(cmd==0xA){DisableIDLETMR();}if(cmd==0x03){FreeWS(ews);ews = NULL;}}

SOFTKEYSTAB hinfo_skt={immenu_sk_elf,0};

INPUTDIA_DESC info_desc=
{
  1,
  info_onkey,
  info_ghook,
  (void *)inp_locret,
  0,
  &hinfo_skt,
  {0,22,131,176},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};

HEADER_DESC info_help={0,0,131,21,NULL,(int)"Справка",LGP_NULL};
HEADER_DESC info_info={0,0,131,21,info_icon,(int)"Информация",LGP_NULL};
HEADER_DESC info_about={0,0,131,21,NULL,(int)"Об эльфе...",LGP_NULL};

void  ELIAbout(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"ElfLibraryInfo\n\n(c)VedaN and\nKIBER-DEMON\n\nБиблиотека эльфов.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_about,eq,1,0);
}

//Adinf=========================================================================

int E1_ID;

void  E1A(GUI *data){ShowMSG(1,(int)"(c) cbn");};

void  E1I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Монитор изменений ");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};

HEADER_DESC imenuhdrE1={0,0,131,21,elf_icon,(int)"Adinf:",0x7FFFFFFF};
void  E1D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE1,eq,1,0);
};


static const MENUPROCS_DESC menuprocsE1[ELF_NUM]={E1A,E1I,E1D};
static int immenu_keyhookE1(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE1[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE1=
{
  8,immenu_keyhookE1,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E1()
{
  patch_header(&imenuhdrE1);
  E1_ID = CreateMenu(0,0,&itmenuE1,&imenuhdrE1,0,ELF_NUM ,0,0);
};

//Analyzer======================================================================

int E2_ID;

void  E2A(GUI *data){ShowMSG(1,(int)"(c) vGamBIT (r) Jhellico");};

void  E2I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Анализатор используемых функций в эльфе(как в Smelter'e).");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};

HEADER_DESC imenuhdrE2={0,0,131,21,elf_icon,(int)"Analyzer:",0x7FFFFFFF};
void  E2D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE2,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE2[ELF_NUM]={E2A,E2I,E2D};


static int immenu_keyhookE2(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE2[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE2=
{
  8,immenu_keyhookE2,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E2()
{
  patch_header(&imenuhdrE2);
  E2_ID = CreateMenu(0,0,&itmenuE2,&imenuhdrE2,0,ELF_NUM ,0,0);
};

//BlibInfo======================================================================

int E3_ID;

void  E3A(GUI *data){ShowMSG(1,(int)"(c) Kren");};

void  E3I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Показывает, какие функции в файле swi.blib присутствуют дополнительно к библиотеке, установленной патчем.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};

HEADER_DESC imenuhdrE3={0,0,131,21,elf_icon,(int)"BLIBinfo:",0x7FFFFFFF};
void  E3D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE3,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE3[ELF_NUM]={E3A,E3I,E3D};


static int immenu_keyhookE3(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE3[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE3=
{
  8,immenu_keyhookE3,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E3()
{
  patch_header(&imenuhdrE2);
  E3_ID = CreateMenu(0,0,&itmenuE3,&imenuhdrE3,0,ELF_NUM ,0,0);
};

//BogoMIPS======================================================================

int E4_ID;

void  E4A(GUI *data){ShowMSG(1,(int)"(c) Rst7");};


void  E4I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Измеряет на какой частоте работает телефон в данный момент.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};

HEADER_DESC imenuhdrE4={0,0,131,21,elf_icon,(int)"BogoMIPS:",0x7FFFFFFF};
void  E4D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"svn://cbsie.dyndns.info");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE4,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE4[ELF_NUM]={E4A,E4I,E4D};


static int immenu_keyhookE4(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE4[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE4=
{
  8,immenu_keyhookE4,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E4()
 {patch_header(&imenuhdrE4);
 E4_ID = CreateMenu(0,0,&itmenuE4,&imenuhdrE4,0,ELF_NUM ,0,0);
};

//BV============================================================================

int E5_ID;

void  E5A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};

void  E5I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Открытие изображений встроенным браузером.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE5={0,0,131,21,elf_icon,(int)"BV:",0x7FFFFFFF};

void  E5D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE5,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE5[ELF_NUM]={E5A,E5I,E5D};

static int immenu_keyhookE5(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE5[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE5=
{
  8,immenu_keyhookE5,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E5()
 {patch_header(&imenuhdrE4);
 E5_ID = CreateMenu(0,0,&itmenuE5,&imenuhdrE5,0,ELF_NUM ,0,0);
};

//CallAlert=====================================================================

int E6_ID;

void  E6A(GUI *data){ShowMSG(1,(int)"(c) Stasilok");};

void  E6I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Моргает всеми возможными фонарями при вызове.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE6={0,0,131,21,elf_icon,(int)"CallAlert:",0x7FFFFFFF};
void  E6D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE6,eq,1,0);
};


static const MENUPROCS_DESC menuprocsE6[ELF_NUM]={E6A,E6I,E6D};


static int immenu_keyhookE6(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE6[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE6=
{
  8,immenu_keyhookE6,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E6()
 {patch_header(&imenuhdrE6);
 E6_ID = CreateMenu(0,0,&itmenuE6,&imenuhdrE6,0,ELF_NUM ,0,0);
};

//CallCenter====================================================================

int E7_ID;

void  E7A(GUI *data){ShowMSG(1,(int)"(c) Rst7");};

void  E7I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф-менеджер по звонкам.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE7={0,0,131,21,elf_icon,(int)"CallCenter:",0x7FFFFFFF};
void  E7D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE7,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE7[ELF_NUM]={E7A,E7I,E7D};

static int immenu_keyhookE7(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE7[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE7=
{
  8,immenu_keyhookE7,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E7()
 {patch_header(&imenuhdrE7);
 E7_ID = CreateMenu(0,0,&itmenuE7,&imenuhdrE7,0,ELF_NUM ,0,0);
};

//CPUD==========================================================================

int E8_ID;

void  E8A(GUI *data){ShowMSG(1,(int)"(c) NForce");};
void  E8I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф задаёт частоту, которая вам нужна: 52,104,208 Mhz.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE8={0,0,131,21,elf_icon,(int)"CPUD:",0x7FFFFFFF};
void  E8D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE8,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE8[ELF_NUM]={E8A,E8I,E8D};

static int immenu_keyhookE8(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE8[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE8=
{
  8,immenu_keyhookE8,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E8()
 {patch_header(&imenuhdrE8);
 E8_ID = CreateMenu(0,0,&itmenuE8,&imenuhdrE8,0,ELF_NUM ,0,0);
};

//CpuNapryag====================================================================

int E9_ID;

void  E9A(GUI *data){ShowMSG(1,(int)"(c) Nicckk");};

void  E9I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Берет загрузку проца и рисует на IDLE сопоставленные ей картинки.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE9={0,0,131,21,elf_icon,(int)"CpuNapryag:",0x7FFFFFFF};
void  E9D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE9,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE9[ELF_NUM]={E9A,E9I,E9D};

static int immenu_keyhookE9(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE9[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE9=
{
  8,immenu_keyhookE9,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E9()
 {patch_header(&imenuhdrE9);
 E9_ID = CreateMenu(0,0,&itmenuE9,&imenuhdrE9,0,ELF_NUM ,0,0);
};

//DPU===========================================================================

int E10_ID;

void  E10A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};

void  E10I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф задаёт любую комбинацию для блокировки/разблокировки клавиатуры.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE10={0,0,131,21,elf_icon,(int)"DPU:",0x7FFFFFFF};
void  E10D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE10,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE10[ELF_NUM]={E10A,E10I,E10D};
static int immenu_keyhookE10(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE10[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE10=
{
  8,immenu_keyhookE10,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E10()
 {patch_header(&imenuhdrE10);
 E10_ID = CreateMenu(0,0,&itmenuE10,&imenuhdrE10,0,ELF_NUM ,0,0);
};

//DropCall======================================================================

int E11_ID;

void  E11A(GUI *data){ShowMSG(1,(int)"(c) VoVkA");};
void  E11I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Сброс звонка по достижении определённого времени.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE11={0,0,131,21,elf_icon,(int)"DropCall:",0x7FFFFFFF};

void  E11D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE11,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE11[ELF_NUM]={E11A,E11I,E11D};

static int immenu_keyhookE11(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE11[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE11=
{
  8,immenu_keyhookE11,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E11()
 {patch_header(&imenuhdrE11);
 E11_ID = CreateMenu(0,0,&itmenuE11,&imenuhdrE11,0,ELF_NUM ,0,0);
};

//FreeSpaced====================================================================

int E12_ID;

void  E12A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};
void  E12I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t," Через заданный интервал времени проверяет свободное место на диске.При переполнение диска выводит соответствующее сообщение.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE12={0,0,131,21,elf_icon,(int)"FreeSpaced:",0x7FFFFFFF};
void  E12D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE12,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE12[ELF_NUM]={E12A,E12I,E12D};

static int immenu_keyhookE12(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE12[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE12=
{
  8,immenu_keyhookE12,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E12()
 {patch_header(&imenuhdrE12);
 E12_ID = CreateMenu(0,0,&itmenuE12,&imenuhdrE12,0,ELF_NUM ,0,0);
};

//JavaSwitcher==================================================================

int E13_ID;

void  E13A(GUI *data){ShowMSG(1,(int)"(c) truhlik");};

void  E13I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Переключение файла main.fs для включения/выключения 2 java.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE13={0,0,131,21,elf_icon,(int)"JavaSwitcher:",0x7FFFFFFF};
void  E13D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE13,eq,1,0);
};


static const MENUPROCS_DESC menuprocsE13[ELF_NUM]={E13A,E13I,E13D};

static int immenu_keyhookE13(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE13[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE13=
{
  8,immenu_keyhookE13,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E13()
 {patch_header(&imenuhdrE13);
 E13_ID = CreateMenu(0,0,&itmenuE13,&imenuhdrE13,0,ELF_NUM ,0,0);
};

//JoyVibra======================================================================

int E14_ID;

void  E14A(GUI *data){ShowMSG(1,(int)"(c) Nicckk");};
void  E14I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Телефон вибрирует при нажатии на джойстик.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE14={0,0,131,21,elf_icon,(int)"JoyVibra:",0x7FFFFFFF};

void  E14D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE14,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE14[ELF_NUM]={E14A,E14I,E14D};

static int immenu_keyhookE14(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE14[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE14=
{
  8,immenu_keyhookE14,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E14()
 {patch_header(&imenuhdrE14);
 E14_ID = CreateMenu(0,0,&itmenuE14,&imenuhdrE14,0,ELF_NUM ,0,0);
};

//LightControl==================================================================

int E15_ID;

void  E15A(GUI *data){ShowMSG(1,(int)"(c) ad (r) Kibab, Pavel81, Bombus");};
void  E15I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Держит включенной подсветку кнопок при запущенной ява, выключает при блокировке кнопок или выходе из ява.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};

HEADER_DESC imenuhdrE15={0,0,131,21,elf_icon,(int)"LightControl:",0x7FFFFFFF};
void  E15D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"patches.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE15,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE15[ELF_NUM]={E15A,E15I,E15D};

static int immenu_keyhookE15(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE15[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE15=
{
  8,immenu_keyhookE15,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E15()
 {patch_header(&imenuhdrE15);
 E15_ID = CreateMenu(0,0,&itmenuE15,&imenuhdrE15,0,ELF_NUM ,0,0);
};

//LogSms========================================================================

int E16_ID;

void  E16A(GUI *data){ShowMSG(1,(int)"(c) Rst7");};
void  E16I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Все входящие смс записывает в лог-файл.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE16={0,0,131,21,elf_icon,(int)"LogSms:",0x7FFFFFFF};

void  E16D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE16,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE16[ELF_NUM]={E16A,E16I,E16D};

static int immenu_keyhookE16(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE16[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE16=
{
  8,immenu_keyhookE16,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E16()
 {patch_header(&imenuhdrE16);
 E16_ID = CreateMenu(0,0,&itmenuE16,&imenuhdrE16,0,ELF_NUM ,0,0);
};

//MapView=======================================================================

int E17_ID;

void  E17A(GUI *data){ShowMSG(1,(int)"(c) Captain_SISka");};
void  E17I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Просмотрщик карт практически неограниченного размера с рядом доп. функций.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE17={0,0,131,21,elf_icon,(int)"MapView:",0x7FFFFFFF};
void  E17D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE17,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE17[ELF_NUM]={E17A,E17I,E17D};

static int immenu_keyhookE17(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE17[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE17=
{
  8,immenu_keyhookE17,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E17()
 {patch_header(&imenuhdrE17);
 E17_ID = CreateMenu(0,0,&itmenuE17,&imenuhdrE17,0,ELF_NUM ,0,0);
};

//RT============================================================================

int E18_ID;

void  E18A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};
void  E18I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Переворачивает экран вверх ногами.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE18={0,0,131,21,elf_icon,(int)"RT:",0x7FFFFFFF};
void  E18D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE18,eq,1,0);
};
static const MENUPROCS_DESC menuprocsE18[ELF_NUM]={E18A,E18I,E18D};
static int immenu_keyhookE18(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE18[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE18=
{
  8,immenu_keyhookE18,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E18()
 {patch_header(&imenuhdrE18);
 E18_ID = CreateMenu(0,0,&itmenuE18,&imenuhdrE18,0,ELF_NUM ,0,0);
};

//smd2bin=======================================================================

int E19_ID;

void  E19A(GUI *data){ShowMSG(1,(int)"(c) cbn");};
void  E19I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Сеговский конвертер из smd в bin.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE19={0,0,131,21,elf_icon,(int)"smd2bin:",0x7FFFFFFF};
void  E19D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cx75planet.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE19,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE19[ELF_NUM]={E19A,E19I,E19D};

static int immenu_keyhookE19(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE19[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE19=
{
  8,immenu_keyhookE19,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E19()
 {patch_header(&imenuhdrE19);
 E19_ID = CreateMenu(0,0,&itmenuE19,&imenuhdrE19,0,ELF_NUM ,0,0);
};

//Stime=========================================================================

int E20_ID;

void  E20A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};
void  E20I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Этот эльф просто выводит время, дату и день недели.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE20={0,0,131,21,elf_icon,(int)"Stime:",0x7FFFFFFF};
void  E20D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE20,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE20[ELF_NUM]={E20A,E20I,E20D};

static int immenu_keyhookE20(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE20[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE20=
{
  8,immenu_keyhookE20,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E20()
 {patch_header(&imenuhdrE20);
 E20_ID = CreateMenu(0,0,&itmenuE20,&imenuhdrE20,0,ELF_NUM ,0,0);
};

//ElfLibraryInfo================================================================

int E21_ID;

void  E21A(GUI *data){ShowMSG(1,(int)"(c) VedaN, KIBER-DEMON");};
void  E21I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Библиотека эльфов");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE21={0,0,131,21,elf_icon,(int)"ElfLibraryInfo:",0x7FFFFFFF};
void  E21D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE21,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE21[ELF_NUM]={E21A,E21I,E21D};


static int immenu_keyhookE21(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE21[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE21=
{
  8,immenu_keyhookE21,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E21()
 {patch_header(&imenuhdrE21);
 E21_ID = CreateMenu(0,0,&itmenuE21,&imenuhdrE21,0,ELF_NUM ,0,0);
};

//CSM===========================================================================

int E22_ID;
void  E22A(GUI *data){ShowMSG(1,(int)"(c) feanor");};
void  E22I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Счётчик диалогов и память занятая ui.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE22={0,0,131,21,elf_icon,(int)"CSM:",0x7FFFFFFF};
void  E22D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE21,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE22[ELF_NUM]={E22A,E22I,E22D};

static int immenu_keyhookE22(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocsE22[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC itmenuE22=
{
  8,immenu_keyhookE22,immenu_ghookElf,NULL,
  elf_imsk,
  &immenu_skt_elf,
  1,
  imenuitemhandlerES,
  NULL, 
  NULL, 
  ELF_NUM
};

void E22()
 {patch_header(&imenuhdrE22);
 E22_ID = CreateMenu(0,0,&itmenuE22,&imenuhdrE22,0,ELF_NUM ,0,0);
};

//ELFsGlue======================================================================

int E23_ID;
void  E23A(GUI *data){ShowMSG(1,(int)"(c) feanor");};
void  E23I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Счётчик диалогов и память занятая ui.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE23={0,0,131,21,elf_icon,(int)"CSM:",0x7FFFFFFF};
void  E23D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE23,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE23[ELF_NUM]={E23A,E23I,E23D};
static int immenu_keyhookE23(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE23[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE23={8,immenu_keyhookE23,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E23()
 {patch_header(&imenuhdrE23);
 E23_ID = CreateMenu(0,0,&itmenuE23,&imenuhdrE23,0,ELF_NUM ,0,0);
};

//ElfStart======================================================================

int E24_ID;
void  E24A(GUI *data){ShowMSG(1,(int)"(c) kluchnik");};
void  E24I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Запуск эльфа по заданной клавише.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE24={0,0,131,21,elf_icon,(int)"ElfStart:",0x7FFFFFFF};
void  E24D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE24,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE24[ELF_NUM]={E24A,E24I,E24D};
static int immenu_keyhookE24(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE24[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE24={8,immenu_keyhookE24,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E24()
 {patch_header(&imenuhdrE24);
 E24_ID = CreateMenu(0,0,&itmenuE24,&imenuhdrE24,0,ELF_NUM ,0,0);
};

//FAV===========================================================================

int E25_ID;
void  E25A(GUI *data){ShowMSG(1,(int)"(c) Win98");};
void  E25I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Фед антивирус.Эльф видет вирусов и до последствий");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE25={0,0,131,21,elf_icon,(int)"FAV:",0x7FFFFFFF};
void  E25D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE25,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE25[ELF_NUM]={E25A,E25I,E25D};
static int immenu_keyhookE25(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE25[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE25={8,immenu_keyhookE25,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E25()
 {patch_header(&imenuhdrE25);
 E25_ID = CreateMenu(0,0,&itmenuE25,&imenuhdrE25,0,ELF_NUM ,0,0);
};

//FFSaver=======================================================================

int E26_ID;
void  E26A(GUI *data){ShowMSG(1,(int)"(c) Rst7/CBSIE");};
void  E26I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Сохраняет FullFlash на карту памяти.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE26={0,0,131,21,elf_icon,(int)"FFSaver:",0x7FFFFFFF};
void  E26D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"patches.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE26,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE26[ELF_NUM]={E26A,E26I,E26D};
static int immenu_keyhookE26(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE26[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE26={8,immenu_keyhookE26,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E26()
 {patch_header(&imenuhdrE26);
 E26_ID = CreateMenu(0,0,&itmenuE26,&imenuhdrE26,0,ELF_NUM ,0,0);
};

//FreeRAM=======================================================================

int E27_ID;
void  E27A(GUI *data){ShowMSG(1,(int)"(c) cbn");};
void  E27I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Находит свободные блоки памяти и собирает по ним статистику.С каждым вызовом данные уточняются.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE27={0,0,131,21,elf_icon,(int)"FreeRAM:",0x7FFFFFFF};
void  E27D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE27,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE27[ELF_NUM]={E27A,E27I,E27D};

static int immenu_keyhookE27(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE27[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE27={8,immenu_keyhookE27,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E27()
 {patch_header(&imenuhdrE27);
 E27_ID = CreateMenu(0,0,&itmenuE27,&imenuhdrE27,0,ELF_NUM ,0,0);
};

//GprsD=========================================================================

int E28_ID;
void  E28A(GUI *data){ShowMSG(1,(int)"(c) Rst7/CBSIE");};
void  E28I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф-демон для поддержания gprs-сессии, нужен для таких эльфов как NATIICQ и SieJC.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE28={0,0,131,21,elf_icon,(int)"GprsD:",0x7FFFFFFF};
void  E28D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE28,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE28[ELF_NUM]={E28A,E28I,E28D};

static int immenu_keyhookE28(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE28[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE28={8,immenu_keyhookE28,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E28()
 {patch_header(&imenuhdrE28);
 E28_ID = CreateMenu(0,0,&itmenuE28,&imenuhdrE28,0,ELF_NUM ,0,0);
};

//GPSLogger=====================================================================

int E29_ID;
void  E29A(GUI *data){ShowMSG(1,(int)"(c) Kibab");};
void  E29I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Замена патча miniGPS.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE29={0,0,131,21,elf_icon,(int)"GPSLogger:",0x7FFFFFFF};
void  E29D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE29,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE29[ELF_NUM]={E29A,E29I,E29D};

static int immenu_keyhookE29(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE29[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE29={8,immenu_keyhookE29,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E29()
 {patch_header(&imenuhdrE29);
 E29_ID = CreateMenu(0,0,&itmenuE29,&imenuhdrE29,0,ELF_NUM ,0,0);
};

//MissedEvents==================================================================

int E30_ID;
void  E30A(GUI *data){ShowMSG(1,(int)"(c) Andrey_ua\n(r) KreN, Rst7");};
void  E30I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф, показывающий иконку и количество пропущенных звонков и сообщений.Также показывает номер и иконку профиля.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE30={0,0,131,21,elf_icon,(int)"MissedEvents:",0x7FFFFFFF};
void  E30D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE30,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE30[ELF_NUM]={E30A,E30I,E30D};

static int immenu_keyhookE30(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE30[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE30={8,immenu_keyhookE30,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E30()
 {patch_header(&imenuhdrE30);
 E30_ID = CreateMenu(0,0,&itmenuE30,&imenuhdrE30,0,ELF_NUM ,0,0);
};

//PTable========================================================================

int E31_ID;
void  E31A(GUI *data){ShowMSG(1,(int)"(c) Vedan");};
void  E31I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Периодическая система химических элементов Д.И.Менделеева.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE31={0,0,131,21,elf_icon,(int)"PTable:",0x7FFFFFFF};
void  E31D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE31,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE31[ELF_NUM]={E31A,E31I,E31D};

static int immenu_keyhookE31(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE31[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE31={8,immenu_keyhookE31,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E31()
 {patch_header(&imenuhdrE31);
 E31_ID = CreateMenu(0,0,&itmenuE31,&imenuhdrE31,0,ELF_NUM ,0,0);
};

//NATICQ========================================================================

int E32_ID;
void  E32A(GUI *data){ShowMSG(1,(int)"(C) by Rst7/CBSIE\nKren\nKibab\nShadow\nSeklth");};
void  E32I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"ICQ клиент.Работает через доп. сервер.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE32={0,0,131,21,elf_icon,(int)"NATICQ:",0x7FFFFFFF};
void  E32D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE32,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE32[ELF_NUM]={E32A,E32I,E32D};

static int immenu_keyhookE32(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE32[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE32={8,immenu_keyhookE32,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E32()
 {patch_header(&imenuhdrE32);
 E32_ID = CreateMenu(0,0,&itmenuE32,&imenuhdrE32,0,ELF_NUM ,0,0);
};

//SieJC=========================================================================

int E33_ID;
void  E33A(GUI *data){ShowMSG(1,(int)"(c) Kibab,\nAd,\nBorman99");};
void  E33I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Jabber-клиент для телефонов Siemens с установленным эльфпаком.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE33={0,0,131,21,elf_icon,(int)"SieJC:",0x7FFFFFFF};
void  E33D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"perk11.info/elf/");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE33,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE33[ELF_NUM]={E33A,E33I,E33D};

static int immenu_keyhookE33(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE33[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE33={8,immenu_keyhookE33,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E33()
 {patch_header(&imenuhdrE33);
 E33_ID = CreateMenu(0,0,&itmenuE33,&imenuhdrE33,0,ELF_NUM ,0,0);
};

//StopWatch=====================================================================

int E34_ID;
void  E34A(GUI *data){ShowMSG(1,(int)"(c) kernel");};
void  E34I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф-секундомер.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE34={0,0,131,21,elf_icon,(int)"StopWatch:",0x7FFFFFFF};
void  E34D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE34,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE34[ELF_NUM]={E34A,E34I,E34D};

static int immenu_keyhookE34(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE34[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE34={8,immenu_keyhookE34,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E34()
 {patch_header(&imenuhdrE34);
 E34_ID = CreateMenu(0,0,&itmenuE34,&imenuhdrE34,0,ELF_NUM ,0,0);
};

//eTimer========================================================================

int E35_ID;
void  E35A(GUI *data){ShowMSG(1,(int)"(c) kernel");};
void  E35I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф-таймер.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE35={0,0,131,21,elf_icon,(int)"eTimer:",0x7FFFFFFF};
void  E35D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE35,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE35[ELF_NUM]={E35A,E35I,E35D};

static int immenu_keyhookE35(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE35[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE35={8,immenu_keyhookE35,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E35()
 {patch_header(&imenuhdrE35);
 E35_ID = CreateMenu(0,0,&itmenuE35,&imenuhdrE35,0,ELF_NUM ,0,0);
};

//AccessoryMon==================================================================

int E36_ID;
void  E36A(GUI *data){ShowMSG(1,(int)"(c) vGamBIT\n(r) MasterMind, -shadow-");};
void  E36I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Показывает какой аксессуар подключен к телефону.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE36={0,0,131,21,elf_icon,(int)"AccessoryMon:",0x7FFFFFFF};
void  E36D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE36,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE36[ELF_NUM]={E36A,E36I,E36D};

static int immenu_keyhookE36(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE36[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE36={8,immenu_keyhookE36,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E36()
 {patch_header(&imenuhdrE36);
 E36_ID = CreateMenu(0,0,&itmenuE36,&imenuhdrE36,0,ELF_NUM ,0,0);
};

//ConfManager==================================================================

int E37_ID;
void  E37A(GUI *data){ShowMSG(1,(int)"(c) Nicckk");};
void  E37I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Меняет конфиги эльфов.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE37={0,0,131,21,elf_icon,(int)"ConfManager:",0x7FFFFFFF};
void  E37D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE37,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE37[ELF_NUM]={E37A,E37I,E37D};

static int immenu_keyhookE37(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE37[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE37={8,immenu_keyhookE37,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E37()
 {patch_header(&imenuhdrE37);
 E37_ID = CreateMenu(0,0,&itmenuE37,&imenuhdrE37,0,ELF_NUM ,0,0);
};

//Count==================================================================

int E38_ID;
void  E38A(GUI *data){ShowMSG(1,(int)"(c) ?");};
void  E38I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Счётчик нажатий клавиш.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE38={0,0,131,21,elf_icon,(int)"Count:",0x7FFFFFFF};
void  E38D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE38,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE38[ELF_NUM]={E38A,E38I,E38D};

static int immenu_keyhookE38(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE38[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE38={8,immenu_keyhookE38,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E38()
 {patch_header(&imenuhdrE38);
 E38_ID = CreateMenu(0,0,&itmenuE38,&imenuhdrE38,0,ELF_NUM ,0,0);
};

//iBlock==================================================================

int E39_ID;
void  E39A(GUI *data){ShowMSG(1,(int)"(c) Druid");};
void  E39I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Необходимая часть для некоторых версий XTask'а.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE39={0,0,131,21,elf_icon,(int)"iBlock:",0x7FFFFFFF};
void  E39D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE39,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE39[ELF_NUM]={E39A,E39I,E39D};

static int immenu_keyhookE39(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE39[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE39={8,immenu_keyhookE39,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E39()
 {patch_header(&imenuhdrE38);
 E39_ID = CreateMenu(0,0,&itmenuE39,&imenuhdrE39,0,ELF_NUM ,0,0);
};

//ImgIDLE==================================================================

int E40_ID;
void  E40A(GUI *data){ShowMSG(1,(int)"(c) kluchnik");};
void  E40I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Выводит на гл.экран картинки заданные в конфиге.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE40={0,0,131,21,elf_icon,(int)"iBlock:",0x7FFFFFFF};
void  E40D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE40,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE40[ELF_NUM]={E40A,E40I,E40D};

static int immenu_keyhookE40(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE40[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE40={8,immenu_keyhookE40,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E40()
 {patch_header(&imenuhdrE40);
 E40_ID = CreateMenu(0,0,&itmenuE40,&imenuhdrE40,0,ELF_NUM ,0,0);
};

//ChangeCap=====================================================================

int E41_ID;
void  E41A(GUI *data){ShowMSG(1,(int)"(c) Geka");};
void  E41I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"При нажатии на эльф, отображаемая зарядка батареи везде станет 0%.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE41={0,0,131,21,elf_icon,(int)"ChangeCap:",0x7FFFFFFF};
void  E41D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE41,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE41[ELF_NUM]={E41A,E41I,E41D};

static int immenu_keyhookE41(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE41[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE41={8,immenu_keyhookE41,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E41()
 {patch_header(&imenuhdrE41);
 E41_ID = CreateMenu(0,0,&itmenuE41,&imenuhdrE41,0,ELF_NUM ,0,0);
};

//XShed=========================================================================

int E42_ID;
void  E42A(GUI *data){ShowMSG(1,(int)"(c) Nicckk");};
void  E42I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Выводит на гл.экран расписание пар-уроков.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE42={0,0,131,21,elf_icon,(int)"XShed:",0x7FFFFFFF};
void  E42D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE42,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE42[ELF_NUM]={E42A,E42I,E42D};

static int immenu_keyhookE42(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE42[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE42={8,immenu_keyhookE42,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E42()
 {patch_header(&imenuhdrE42);
 E42_ID = CreateMenu(0,0,&itmenuE42,&imenuhdrE42,0,ELF_NUM ,0,0);
};

//Watch=========================================================================

int E43_ID;
void  E43A(GUI *data){ShowMSG(1,(int)"(c) Hutch");};
void  E43I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Рисует время ASCII кодами.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE43={0,0,131,21,elf_icon,(int)"Watch:",0x7FFFFFFF};
void  E43D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE43,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE43[ELF_NUM]={E43A,E43I,E43D};

static int immenu_keyhookE43(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE43[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE43={8,immenu_keyhookE43,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E43()
 {patch_header(&imenuhdrE43);
 E43_ID = CreateMenu(0,0,&itmenuE43,&imenuhdrE43,0,ELF_NUM ,0,0);
};

//VibAtConnect==================================================================

int E44_ID;
void  E44A(GUI *data){ShowMSG(1,(int)"(c) -shadow-");};
void  E44I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Вибра в момент соединения.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE44={0,0,131,21,elf_icon,(int)"VibAtConnect:",0x7FFFFFFF};
void  E44D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE44,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE44[ELF_NUM]={E44A,E44I,E44D};

static int immenu_keyhookE44(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE44[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE44={8,immenu_keyhookE44,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E44()
 {patch_header(&imenuhdrE44);
 E44_ID = CreateMenu(0,0,&itmenuE44,&imenuhdrE44,0,ELF_NUM ,0,0);
};

//VOC===========================================================================

int E45_ID;
void  E45A(GUI *data){ShowMSG(1,(int)"(c) Dimens+");};
void  E45I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Вешает регулировку на боковые клавиши(cx-m75 и s65), и при изм. громкости отображает индикатор.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE45={0,0,131,21,elf_icon,(int)"VOC:",0x7FFFFFFF};
void  E45D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE45,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE45[ELF_NUM]={E45A,E45I,E45D};

static int immenu_keyhookE45(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE45[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE45={8,immenu_keyhookE45,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E45()
 {patch_header(&imenuhdrE45);
 E45_ID = CreateMenu(0,0,&itmenuE45,&imenuhdrE45,0,ELF_NUM ,0,0);
};

//VCMD==========================================================================

int E46_ID;
void  E46A(GUI *data){ShowMSG(1,(int)"(c) NagLost");};
void  E46I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф представляющий замену голосовым командам.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE46={0,0,131,21,elf_icon,(int)"VCMD:",0x7FFFFFFF};
void  E46D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE46,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE46[ELF_NUM]={E46A,E46I,E46D};

static int immenu_keyhookE46(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE46[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE46={8,immenu_keyhookE46,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E46()
 {patch_header(&imenuhdrE46);
 E46_ID = CreateMenu(0,0,&itmenuE46,&imenuhdrE46,0,ELF_NUM ,0,0);
};

//Translate=====================================================================

int E47_ID;
void  E47A(GUI *data){ShowMSG(1,(int)"(c) snemeis");};
void  E47I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф переводит слова через интернет.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE47={0,0,131,21,elf_icon,(int)"Translate:",0x7FFFFFFF};
void  E47D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE47,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE47[ELF_NUM]={E47A,E47I,E47D};

static int immenu_keyhookE47(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE47[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE47={8,immenu_keyhookE47,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E47()
 {patch_header(&imenuhdrE47);
 E47_ID = CreateMenu(0,0,&itmenuE47,&imenuhdrE47,0,ELF_NUM ,0,0);
};

//Clock=========================================================================

int E48_ID;
void  E48A(GUI *data){ShowMSG(1,(int)"(c) The_ZeN");};
void  E48I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Смесь аналоговых часов от snemeis и цифровых часов от Geka.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE48={0,0,131,21,elf_icon,(int)"Clock:",0x7FFFFFFF};
void  E48D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE48,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE48[ELF_NUM]={E48A,E48I,E48D};

static int immenu_keyhookE48(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE48[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE48={8,immenu_keyhookE48,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E48()
 {patch_header(&imenuhdrE48);
 E48_ID = CreateMenu(0,0,&itmenuE48,&imenuhdrE48,0,ELF_NUM ,0,0);
};

//Command=======================================================================

int E49_ID;
void  E49A(GUI *data){ShowMSG(1,(int)"(c) cbn");};
void  E49I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Командный интерпретатор MS-DOS.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE49={0,0,131,21,elf_icon,(int)"Command:",0x7FFFFFFF};
void  E49D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE49,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE49[ELF_NUM]={E49A,E49I,E49D};

static int immenu_keyhookE49(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE49[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE49={8,immenu_keyhookE49,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E49()
 {patch_header(&imenuhdrE49);
 E49_ID = CreateMenu(0,0,&itmenuE49,&imenuhdrE49,0,ELF_NUM ,0,0);
};

//DisplayShooter================================================================

int E50_ID;
void  E50A(GUI *data){ShowMSG(1,(int)"(c) DJ");};
void  E50I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Делает скриншот экрана и сохраняет в заданную папку.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE50={0,0,131,21,elf_icon,(int)"DisplayShooter:",0x7FFFFFFF};
void  E50D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.siemens-club.org");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE50,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE50[ELF_NUM]={E50A,E50I,E50D};

static int immenu_keyhookE50(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE50[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE50={8,immenu_keyhookE50,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E50()
 {patch_header(&imenuhdrE50);
 E50_ID = CreateMenu(0,0,&itmenuE50,&imenuhdrE50,0,ELF_NUM ,0,0);
};
//Unrar=========================================================================
int E51_ID;
void  E51A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E51I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Распаковшик архивов RAR");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE51={0,0,131,21,elf_icon,(int)"Unrar:",0x7FFFFFFF};
void  E51D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE51,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE51[ELF_NUM]={E51A,E51I,E51D};

static int immenu_keyhookE51(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE51[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE51={8,immenu_keyhookE51,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E51()
 {patch_header(&imenuhdrE50);
 E51_ID = CreateMenu(0,0,&itmenuE51,&imenuhdrE51,0,ELF_NUM ,0,0);
};

//Unzip=========================================================================
int E52_ID;
void  E52A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E52I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Распаковшик архивов ZIP");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE52={0,0,131,21,elf_icon,(int)"Unrar:",0x7FFFFFFF};
void  E52D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE52,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE52[ELF_NUM]={E52A,E52I,E52D};

static int immenu_keyhookE52(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE52[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE52={8,immenu_keyhookE52,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E52()
 {patch_header(&imenuhdrE50);
 E52_ID = CreateMenu(0,0,&itmenuE52,&imenuhdrE52,0,ELF_NUM ,0,0);
};

//Un7z==========================================================================
int E53_ID;
void  E53A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E53I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Распаковшик архивов 7Z");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE53={0,0,131,21,elf_icon,(int)"Un7z:",0x7FFFFFFF};
void  E53D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE53,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE53[ELF_NUM]={E53A,E53I,E53D};

static int immenu_keyhookE53(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE53[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE53={8,immenu_keyhookE53,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E53()
 {patch_header(&imenuhdrE53);
 E53_ID = CreateMenu(0,0,&itmenuE53,&imenuhdrE53,0,ELF_NUM ,0,0);
};

//Dendy=========================================================================
int E54_ID;
void  E54A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E54I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Nintendo (Денди) эмулятор elf.Открывает ромы из zip, rar, 7z архивов (по одному рому на архив!)Архивы переименуйте в расширение понятное NESу, например .nes ");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE54={0,0,131,21,elf_icon,(int)"Dendy:",0x7FFFFFFF};
void  E54D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE54,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE54[ELF_NUM]={E54A,E54I,E54D};

static int immenu_keyhookE54(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE54[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE54={8,immenu_keyhookE54,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E54()
 {patch_header(&imenuhdrE54);
 E54_ID = CreateMenu(0,0,&itmenuE54,&imenuhdrE54,0,ELF_NUM ,0,0);
};

//Sega==========================================================================
int E55_ID;
void  E55A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E55I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"SEGA эмулятор популярной приставки. Для SGOLD, NEWSGOLD, SGOLD3.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE55={0,0,131,21,elf_icon,(int)"Sega:",0x7FFFFFFF};
void  E55D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE55,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE55[ELF_NUM]={E55A,E55I,E55D};

static int immenu_keyhookE55(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE55[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE55={8,immenu_keyhookE55,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E55()
 {patch_header(&imenuhdrE55);
 E55_ID = CreateMenu(0,0,&itmenuE55,&imenuhdrE55,0,ELF_NUM ,0,0);
};

//Tetris========================================================================
int E56_ID;
void  E56A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E56I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Всем известная игра,где надо упорядоченно расставлять фигуры.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE56={0,0,131,21,elf_icon,(int)"Tetris:",0x7FFFFFFF};
void  E56D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE56,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE56[ELF_NUM]={E56A,E56I,E56D};

static int immenu_keyhookE56(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE56[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE56={8,immenu_keyhookE56,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E56()
 {patch_header(&imenuhdrE56);
 E56_ID = CreateMenu(0,0,&itmenuE56,&imenuhdrE56,0,ELF_NUM ,0,0);
};

//Baloons=======================================================================
int E57_ID;
void  E57A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E57I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Игра в которой надо выбирать одноцветные блоки,вследствие чего они исчезают.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE57={0,0,131,21,elf_icon,(int)"Baloons:",0x7FFFFFFF};
void  E57D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE57,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE57[ELF_NUM]={E57A,E57I,E57D};

static int immenu_keyhookE57(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE57[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE57={8,immenu_keyhookE57,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E57()
 {patch_header(&imenuhdrE57);
 E57_ID = CreateMenu(0,0,&itmenuE57,&imenuhdrE57,0,ELF_NUM ,0,0);
};


//Sokoban=======================================================================
int E58_ID;
void  E58A(GUI *data){ShowMSG(1,(int)"(c) (с)bn ");};
void  E58I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"В этой игре надо бегать человечком и расставлять ящики по своим местам.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE58={0,0,131,21,elf_icon,(int)"Sokoban:",0x7FFFFFFF};
void  E58D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE58,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE58[ELF_NUM]={E58A,E58I,E58D};

static int immenu_keyhookE58(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE58[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE58={8,immenu_keyhookE58,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E58()
 {patch_header(&imenuhdrE58);
 E58_ID = CreateMenu(0,0,&itmenuE58,&imenuhdrE58,0,ELF_NUM ,0,0);
};

//IvoPlay=======================================================================
int E59_ID;
void  E59A(GUI *data){ShowMSG(1,(int)"(c) Ivo ");};
void  E59I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Плеер с 'горячей' сменой скинов, умеет выводить время и прогрессбар при проигрывании.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE59={0,0,131,21,elf_icon,(int)"IvoPlay:",0x7FFFFFFF};
void  E59D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE59,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE59[ELF_NUM]={E59A,E59I,E59D};

static int immenu_keyhookE59(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE59[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE59={8,immenu_keyhookE59,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E59()
 {patch_header(&imenuhdrE59);
 E59_ID = CreateMenu(0,0,&itmenuE59,&imenuhdrE59,0,ELF_NUM ,0,0);
};

//SPlayer=======================================================================
int E60_ID;
void  E60A(GUI *data){ShowMSG(1,(int)"(c) DemonGloom,\nMr. Anderstand,\nBlind007. ");};
void  E60I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Плеер с поддержкой скинов и легкого их конфигурирования.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE60={0,0,131,21,elf_icon,(int)"SPlayer:",0x7FFFFFFF};
void  E60D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE60,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE60[ELF_NUM]={E60A,E60I,E60D};

static int immenu_keyhookE60(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE60[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE60={8,immenu_keyhookE60,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E60()
 {patch_header(&imenuhdrE60);
 E60_ID = CreateMenu(0,0,&itmenuE60,&imenuhdrE60,0,ELF_NUM ,0,0);
};

//WavPlayer=====================================================================
int E61_ID;
void  E61A(GUI *data){ShowMSG(1,(int)"(c) SuDex ");};
void  E61I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Плеер, заточенный под воспроизведение WAV, но способный проигрывать и МР3 на СХ/М75.");
  ConstructEditControl(&ec,1,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE61={0,0,131,21,elf_icon,(int)"SPlayer:",0x7FFFFFFF};
void  E61D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE61,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE61[ELF_NUM]={E61A,E61I,E61D};

static int immenu_keyhookE61(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE61[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE61={8,immenu_keyhookE61,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E61()
 {patch_header(&imenuhdrE61);
 E61_ID = CreateMenu(0,0,&itmenuE61,&imenuhdrE61,0,ELF_NUM ,0,0);
};

//MailWeather===================================================================
int E62_ID;
void  E62A(GUI *data){ShowMSG(1,(int)"(c) Evilfox ");};
void  E62I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Через задаваемые пользователем интервалы выводит на главный информацию о текущей температуре и погоде, погода берется с сайта http://wap.weather.mail.ru/index.xhtml?&city=3887 ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE62={0,0,131,21,elf_icon,(int)"MailWeather:",0x7FFFFFFF};
void  E62D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"e71.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE62,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE62[ELF_NUM]={E62A,E62I,E62D};

static int immenu_keyhookE62(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE62[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE62={8,immenu_keyhookE62,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E62()
 {patch_header(&imenuhdrE62);
 E62_ID = CreateMenu(0,0,&itmenuE62,&imenuhdrE62,0,ELF_NUM ,0,0);
};

//ТА============================================================================
int E63_ID;
void  E63A(GUI *data){ShowMSG(1,(int)"(c) feanor ");};
void  E63I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Показывает сколько метров до ближайшей вышки вашего опсоса. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE63={0,0,131,21,elf_icon,(int)"ТА:",0x7FFFFFFF};
void  E63D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"e71.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE63,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE63[ELF_NUM]={E63A,E63I,E63D};

static int immenu_keyhookE63(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE63[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE63={8,immenu_keyhookE63,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E63()
 {patch_header(&imenuhdrE63);
 E63_ID = CreateMenu(0,0,&itmenuE63,&imenuhdrE63,0,ELF_NUM ,0,0);
};

//Tamagochi=====================================================================
int E64_ID;
void  E64A(GUI *data){ShowMSG(1,(int)"(c) Anisan ");};
void  E64I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф-Тамагочи. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE64={0,0,131,21,elf_icon,(int)"Tamagochi:",0x7FFFFFFF};
void  E64D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.allsiemens.com");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE64,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE64[ELF_NUM]={E64A,E64I,E64D};

static int immenu_keyhookE64(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE64[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE64={8,immenu_keyhookE64,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E64()
 {patch_header(&imenuhdrE64);
 E64_ID = CreateMenu(0,0,&itmenuE64,&imenuhdrE64,0,ELF_NUM ,0,0);
};

//GFleet========================================================================
int E65_ID;
void  E65A(GUI *data){ShowMSG(1,(int)"(c) cbn ");};
void  E65I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Demo-видео морских сражений. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE65={0,0,131,21,elf_icon,(int)"GFleet:",0x7FFFFFFF};
void  E65D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"cbn.narod.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE65,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE65[ELF_NUM]={E65A,E65I,E65D};

static int immenu_keyhookE65(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE65[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE65={8,immenu_keyhookE65,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E65()
 {patch_header(&imenuhdrE65);
 E65_ID = CreateMenu(0,0,&itmenuE65,&imenuhdrE65,0,ELF_NUM ,0,0);
};

//InstJar=======================================================================
int E66_ID;
void  E66A(GUI *data){ShowMSG(1,(int)"(c) Nicckk ");};
void  E66I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Альтернативная установка ява-приложений. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE66={0,0,131,21,elf_icon,(int)"InstJar:",0x7FFFFFFF};
void  E66D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE66,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE66[ELF_NUM]={E66A,E66I,E66D};

static int immenu_keyhookE66(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE66[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE66={8,immenu_keyhookE66,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E66()
 {patch_header(&imenuhdrE66);
 E66_ID = CreateMenu(0,0,&itmenuE66,&imenuhdrE66,0,ELF_NUM ,0,0);
};

//KeyTest=======================================================================
int E67_ID;
void  E67A(GUI *data){ShowMSG(1,(int)"(c) feanor ");};
void  E67I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Возвращает код нажатой клавиши в Нех и Dес. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE67={0,0,131,21,elf_icon,(int)"KeyTest:",0x7FFFFFFF};
void  E67D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE67,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE67[ELF_NUM]={E67A,E67I,E67D};

static int immenu_keyhookE67(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE67[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE67={8,immenu_keyhookE67,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E67()
 {patch_header(&imenuhdrE67);
 E67_ID = CreateMenu(0,0,&itmenuE67,&imenuhdrE67,0,ELF_NUM ,0,0);
};

//KeypadLight===================================================================
int E68_ID;
void  E68A(GUI *data){ShowMSG(1,(int)"(c) feanor ");};
void  E68I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Отключает подсветку клавиатуры. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE68={0,0,131,21,elf_icon,(int)"KeypadLight:",0x7FFFFFFF};
void  E68D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE68,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE68[ELF_NUM]={E68A,E68I,E68D};

static int immenu_keyhookE68(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE68[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE68={8,immenu_keyhookE68,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E68()
 {patch_header(&imenuhdrE68);
 E68_ID = CreateMenu(0,0,&itmenuE68,&imenuhdrE68,0,ELF_NUM ,0,0);
};

//Light=========================================================================
int E69_ID;
void  E69A(GUI *data){ShowMSG(1,(int)"(c) feanor ");};
void  E69I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Тест работы с подсветкой через раму. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE69={0,0,131,21,elf_icon,(int)"Light:",0x7FFFFFFF};
void  E69D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE69,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE69[ELF_NUM]={E69A,E69I,E69D};

static int immenu_keyhookE69(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE69[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE69={8,immenu_keyhookE69,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E69()
 {patch_header(&imenuhdrE69);
 E69_ID = CreateMenu(0,0,&itmenuE69,&imenuhdrE69,0,ELF_NUM ,0,0);
};

//McKey=========================================================================
int E70_ID;
void  E70A(GUI *data){ShowMSG(1,(int)"(c) vGamBIT \n(r) feanor ");};
void  E70I(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"Эльф эмулирует нажатия клавиш в телефоне. Делает это циклично, по написанному макросу. ");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_info,eq,1,0);
};
HEADER_DESC imenuhdrE70={0,0,131,21,elf_icon,(int)"McKey:",0x7FFFFFFF};
void  E70D(GUI *data)
{
  ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,percent_t,"forum.s-c.ru");
  ConstructEditControl(&ec,3,0x40,ews,512);  
  AddEditControlToEditQend(eq,&ec,ma); 
  CreateInputTextDialog(&info_desc,&imenuhdrE70,eq,1,0);
};

static const MENUPROCS_DESC menuprocsE70[ELF_NUM]={E70A,E70I,E70D};

static int immenu_keyhookE70(void *data, GUI_MSG *msg)
{if ((msg->keys==0x18)||(msg->keys==0x3D)){((void (*)(void))(menuprocsE70[GetCurMenuItem(data)]))();}return(0);}
static const MENU_DESC itmenuE70={8,immenu_keyhookE70,immenu_ghookElf,NULL,elf_imsk,&immenu_skt_elf,1,imenuitemhandlerES,NULL,NULL,ELF_NUM};

void E70()
 {patch_header(&imenuhdrE70);
 E70_ID = CreateMenu(0,0,&itmenuE70,&imenuhdrE70,0,ELF_NUM ,0,0);
};
