#include "..\inc\swilib.h"

char *filename = 0;

#include "config\conf_loader.h"
#include "tbase_work\tbase.h"
#include "utils\parser.h"
#include "utils\prepatch.h"
#include "utils\fileman.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
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
  WSHDR *ws5;
  int i1;
}MAIN_GUI;


static void OnRedraw(MAIN_GUI *data){}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
#ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
#endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}
static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
  FreeWS(data->ws5);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
#ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
#endif
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{
 if (msg->gbsmsg->msg == KEY_DOWN && msg->gbsmsg->submess == RIGHT_SOFT) return(1);
 return(0);
}



extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void VPatcherMenu();

static void maincsm_oncreate(CSM_RAM *data)
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
  VPatcherMenu();
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  if (filename) mfree(filename);
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}


static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{

  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }

  return(1);
}


static const struct
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"VPatcher v0.7");
}


void Patching(char *filename, int p)
{
     SetPrePatchMode(PP_RMODE);
     ReadPatchLines(filename, p);
     SetPrePatchMode(PP_MMODE);
     ReadPatchLines(filename, p);
     PatchFunction(p);
     SetPrePatchMode(PP_RESET);
}

void apply_vp_item(GUI *data)
{
   if(filename[1] == ':')
    { 
     Patching(filename, APPLY_VP);
     ShowMSG(1,(int)"ВП применён!");
    }
   else ShowMSG(1,(int)"Выберите файл!");
}
void undo_vp_item(GUI *data)
{
   if(filename[1] == ':')
    { 
     Patching(filename, UNDO_VP);
     ShowMSG(1,(int)"ВП отменён!");
    }
   else ShowMSG(1,(int)"Выберите файл!");
}

void undo_rp_item(GUI *data)
{
   if(filename[1] == ':')
    { 
     Patching(filename, UNDO_RP);
     ShowMSG(1,(int)"РП отменён!");
    }
   else ShowMSG(1,(int)"Выберите файл!");
}



void tp_item(GUI *data)
{   
   if(filename[1] == ':')
    { 
     ReadPatchLines(filename, 3);
     ShowMSG(1,(int)"Тест пройден!");
    }
   else ShowMSG(1,(int)"Выберите файл!");
}


void options_item(GUI *data)
{     
    OpenConfig();
}

void about_item(GUI *data)
{     
    ShowMSG(1, (int)"(c)Dimadze\n(c)Danil e71\n(с)Z.Vova");
}

void exit_item(GUI *gui)
{
  MAIN_CSM *main_csm;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(MAINCSM_ID)))
  {
    GeneralFunc_flag1(main_csm->gui_id,0xFF);
    GeneralFuncF1(1);
  }
  else
  {
    GeneralFuncF1(1);
  }
}

const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)"VPatcher v0.7",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[]=
{
  {NULL,(int)"Применить ВП",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Отменить ВП",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Отменить РП",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Тест", LGP_NULL,0,NULL ,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Опции",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Авторы",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Выход",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[]={
  apply_vp_item,
  undo_vp_item,
  undo_rp_item,
  tp_item,
  options_item,
  about_item,
  exit_item
};

const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Выход"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  (SOFTKEY_DESC *)menu_sk,0
};


void ed1_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_CREATE) DisableIDLETMR();
  if (cmd==TI_CMD_FOCUS)  DisableIDLETMR(); 

}



int ed1_onkey(void *data, GUI_MSG *msg)
{
 if (msg->gbsmsg->submess == RIGHT_SOFT && msg->gbsmsg->msg == KEY_DOWN) exit_item((GUI *)data);
 return 0;
}


const MENU_DESC vpmenu=
{
  8,ed1_onkey,ed1_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x10,
  NULL,
  menuitems,
  menuprocs,
  7
};

void VPatcherMenu(void)
{
  patch_header(&menuhdr);
  CreateMenu(0,0,&vpmenu,&menuhdr,0,5,0,0);
}




extern const char patcher_folder[];


int ApplyPatchesFromFolder()
{
  DIR_ENTRY de;
  unsigned int err;
  unsigned int pathlen;
  char name[256];
  strcpy(name, patcher_folder);
  if (isdir(name, 0) != 1) return 0;
  pathlen=strlen(name);
  strcat(name,"*.vkp");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      name[pathlen]=0;
      strcat(name,de.file_name);
      Patching(name, APPLY_VP);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return 1;
}



int main(char *exename, char *fname)
{
#ifdef NEWSGOLD
#ifdef ELKA
 if (isNewSGold() == 2)
#else
 if (isNewSGold() == 1)
#endif
#else
 if (isNewSGold() == 0)
#endif
 {
  InitConfig();
  
  if (fname[1] != ':')
   {

    ApplyPatchesFromFolder();
    return 0;
   } else
     {
        filename =  malloc(strlen(fname)+1);
        strcpy(filename,fname);

        MAIN_CSM main_csm; 
        LockSched();
        UpdateCSMname();
        MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,&main_csm,0);
        UnlockSched();
        return 0;
     }
  }
   else 
    {
      ShowMSG(1, (int)"Ошибка платформы!");
      SUBPROC((void *)ElfKiller);
    }

  return 0;
}
