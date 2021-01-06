#include "..\inc\swilib.h"
#include "..\inc\gpslogger_ipc.h"
#include "conf_loader.h"

const int minus11=-11; // стремная константа

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;

volatile int edit_gui_id=0;
volatile int menu_gui_id=0;

// Посылка IPC-сообщения об изменении файла
const char IPC_me[]="TMOEditor";
const char IPC_to[]=IPC_GPSL_NAME;

char filename[128];     // глобальная переменная для имени файла

extern const char minigps_dir[];
extern const char *successed_config_filename;
//===============================================================================================
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===============================================================================================

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int MakeFolderPath(char *path)
{
  int c, i=0;
  unsigned int err;
  char tmp[256], *s;
  strcpy(tmp,path);
  s=tmp;
  while((s=strchr(s,'\\')))
  {
    s++;
    c=*s;
    *s=0;
    i+=mkdir(tmp,&err);
    *s=c;
  }
  return (i);
}

int LaunchEditor();
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM*csm=(MAIN_CSM*)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  edit_gui_id=csm->gui_id=LaunchEditor();
}

extern void kill_data(void *p, void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==menu_gui_id)
    {
      if ((int)msg->data1==10)
      {
        GeneralFunc_flag1(csm->gui_id,1);        
      }
    }
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"TMOEditor config updated!");
      InitConfig();
    }
  } 
  return(1);
}

/*
const CSM_DESC maincsm=
{
  maincsm_onmessage,
  maincsm_oncreate,
  0,
  0,
  0,
  0,
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
};
*/

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
  WSHDR *ws=AllocWS(256);
  char *sh_fname = strrchr(filename,'\\');
  str_2ws(ws,sh_fname,126);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TMOEdit: %w",ws);
  FreeWS(ws);
}

int main(char *exename, char *fname)
{
  MAIN_CSM main_csm;
  if (fname)
  {
    if ((fname[0]>='0' && fname[0]<='9' && fname[1]==':') && strlen(fname)<128)
    {
      strcpy(filename,fname);     // сохраняем в глоб.перем.переданное имя
    }
  }
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,&main_csm,0);

  // Инициализация конфигурации
  InitConfig();
  return 0;
}

//---------------------------------------------------------------------------
// Сохранение текста в файл
//---------------------------------------------------------------------------

void GetCurFileName(char *s)
{
  RAMNET *Res = RamNet(); 
  sprintf(s,"%s\\%u\\%u-%u.tmo",minigps_dir,Res->lac,Res->ci,Res->lac);  
}


IPC_REQ IPC_TMO_Upd;
GPSL_IPC_MSG_UPD_TMO TMO_Upd_Message;

void Send_Update_Notify(unsigned int ci, unsigned int lac)
{
  IPC_TMO_Upd.name_to = IPC_to;
  IPC_TMO_Upd.name_from = IPC_me;
  TMO_Upd_Message.msg_version=1;
  TMO_Upd_Message.cid=ci;
  TMO_Upd_Message.lac=lac;
  IPC_TMO_Upd.data = &TMO_Upd_Message;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_GPSL_UPD_TMO,&IPC_TMO_Upd);  
}



int SaveText(WSHDR *tmostr)
{
  unsigned int errcode;
  volatile int hFile = -1;
  RAMNET *Res=RamNet();
  // Сохранение
  unsigned int len = tmostr->wsbody[0];
  if ((hFile=fopen(filename,A_Create+A_WriteOnly+A_Truncate+A_BIN,P_READ+P_WRITE,&errcode))==-1)
  {
    // Скорее всего потому, что нет директории
    MakeFolderPath(filename);
    hFile=fopen(filename,A_Create+A_WriteOnly+A_Truncate+A_BIN,P_READ+P_WRITE,&errcode);
  }
  fwrite(hFile,tmostr->wsbody,len*2+2,&errcode);
  unsigned int crc = tmostr->wsbody[0];
  void *temp;
  char *arr;
  temp = tmostr->wsbody;   
  arr = temp;
  for(int i=2;i<(len+1)*2;i++)
  {
    crc = crc ^ arr[i];
  }
  fwrite(hFile,&crc,2,&errcode);
  fclose(hFile,&errcode);
  //ShowMSG(1,(int)"Сохранено"); // ибо потом выход НАХ
  Send_Update_Notify(Res->ci, Res->lac);
  return 1;
}

void _SaveText(GUI *data)
{
  WSHDR *tmostr=MenuGetUserPointer(data);
  SaveText(tmostr);
}

void Settings(GUI *data)
{
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,127);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);    
}
void menup2(GUI *data)  // Покинуть редактор (вызов из меню)
{
  GeneralFuncF1(10);
}

void AboutDlg(GUI *data)
{
  char *str = "TMO-редактор v4.0(0xC604)\r\n(c) 2006 Kibab\r\n(r) Rst7/CBSIE";
  ShowMSG(2,(int)str);
}

int icon[]={0x3DB,0};
int about_icon[]={0x4DB,0};
int exit_icon[] = {0x315,0};
int save_icon[] = {0x50E,0};

HEADER_DESC menuhdr={0,0,131,21,NULL,(int)"Меню редактора",LGP_NULL};
int menusoftkeys[]={0,1,2};
MENUITEM_DESC menuitems[4]=
{
  {NULL,(int)"Сохранить",   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Настройки",   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Об эльфе...", LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Выход",       LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

MENUPROCS_DESC menuprocs[4]=
{
  _SaveText,
  Settings,
  AboutDlg,
  menup2
};

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  1,
  NULL,
  menuitems,
  menuprocs,
  4
};

//---------------------------------------------------------------------------
// Test edit dialog
//---------------------------------------------------------------------------
int inp_onkey(GUI *gui, GUI_MSG *msg)
{
  EDITCONTROL ec;
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
//  В этом куске, вообще говоря, нет смысла, ибо при запущенном XTask
// красная кнопка действует как "Назад"
  if(msg->gbsmsg->submess==RED_BUTTON)
  {
    return(1); // выходим без сохранения.
  }
  if(msg->gbsmsg->submess==GREEN_BUTTON)
  {
    ExtractEditControl(gui,1,&ec);    
    wstrcpy(tmostr,ec.pWS);
    if(SaveText(tmostr)) // сохраняемся
    {
      return(1); // Выходим
    }
  }
  if (msg->keys==0x18)
  {
    ExtractEditControl(gui,1,&ec);    
    wstrcpy(tmostr,ec.pWS);
    patch_header(&menuhdr);
    menu_gui_id=CreateMenu(0,0,&tmenu,&menuhdr,0,4,tmostr,0);
    return(-1); //do redraw
  }
  return(0); //Do standart keys
  //1: close
}


void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018, 0x0000,(int)"Меню"};
  
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
  if (cmd==2)
  {
    //Called after onCreate
  }
  if (cmd==3)
  {
    FreeWS(tmostr);    
  }    
  if (cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);    
  }
}

void inp_locret(void){}

INPUTDIA_DESC inp_desc=
{
  1,
  inp_onkey,
  inp_ghook,
  (void *)inp_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};


HEADER_DESC inp_hdr={0,0,131,21,/*icon*/NULL,(int)"TMOEdit",LGP_NULL};

#define MAX_TMO_LEN 256
int LaunchEditor(void)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *tmostr;

  int str_len = 0;
  unsigned int errcode = NULL;
  volatile int hFile = -1;
  
  tmostr=AllocWS(MAX_TMO_LEN);
  if (!(*filename))  // Имя не передано
  {
    GetCurFileName(filename);
  }
  if ((hFile=fopen(filename,A_ReadWrite+A_BIN,P_READ+P_WRITE,&errcode))!=-1)
  {
    fread(hFile,&str_len,2,&errcode);
    char *sh_fname = strrchr(filename,'\\');
    inp_hdr.lgp_id = (int)sh_fname;
    tmostr->wsbody[0]=str_len;   
    fread(hFile,tmostr->wsbody+1,str_len*2,&errcode);
    if(errcode)
    {
      wsprintf(tmostr,"%t %u (%t %s)","Ошибка I/O", errcode, "Файл", filename);          
    }
    fclose(hFile, &errcode);
  }
  else
  {
    wsprintf(tmostr,"%t","0 ");
    inp_hdr.lgp_id = (int)"//<New>";
  } 
  UpdateCSMname();
  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,tmostr,256);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_header(&inp_hdr);
  patch_input(&inp_desc);
  return CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,tmostr);
}
