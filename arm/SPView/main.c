#include "../inc/swilib.h"
#include "menu.h"
#include "rect_patcher.h"
#include "../inc/siemens_unicode.h"

extern void kill_data(void *p, void (*func_p)(void *));

unsigned int pic_id=0;
char MAIN_FOLDER[256]; //откуда запустился эльф

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

HEADER_DESC gui_hdr={0,0,0,0, NULL, 0, LGP_NULL};
  
void update_header(GUI* gui)
{
  static char gui_hdr_text[64];
  sprintf(gui_hdr_text, "Pic ID:%d  %dx%d", pic_id, GetImgWidth(pic_id), GetImgHeight(pic_id));
  gui_hdr.lgp_id=(int)gui_hdr_text; 
  //((int*)GetDataOfItemByID(gui, 2))[13]=(int)gui_hdr_text;
}

void gui_redraw(void *data)
{ 
  int y_bg=
#ifdef ELKA
24;
#else
0;
#endif
  int x1=(ScreenW()-GetImgWidth(pic_id))/2;
  int y1=(ScreenH()-GetImgHeight(pic_id)+y_bg+HeaderH()-SoftkeyH())/2;
  DrawImg(x1, y1, pic_id);
  
  DrawRectangle(x1-1, y1-1, x1+GetImgWidth(pic_id), y1+GetImgHeight(pic_id), 1,GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23));
}

int guisoftkeys[]={0,1,2};

SOFTKEY_DESC gui_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"LGP_DOIT_PIC"}
};

SOFTKEYSTAB gui_skt=
{
  gui_sk,0
};

void gui_locret(void){}
#define MAX_PATH 65536
int gui_onkey(GUI *data, GUI_MSG *msg)
{
  //EDITCONTROL ec;
  //char str[128];
  if (msg->keys==0xFFF)
  {
    /*ExtractEditControl(data,1,&ec);
    ws_2str(ec.pWS,str,127);*/
    CreateOptionsMenu();
  }
  if(msg->keys==0xFF0)
  {
      return 1;
  }
  int style=msg->gbsmsg->msg;
  int key=msg->gbsmsg->submess;
  if(style==KEY_DOWN || style==LONG_PRESS)
  {
    switch(key)
    {
        case LEFT_BUTTON: 
        if(pic_id)
          while(!GetPITaddr(--pic_id)&&(pic_id));
        goto REDRAW;
        case DOWN_BUTTON:
         if(pic_id)
          while(!GetPITaddr(--pic_id)&&(pic_id));
        goto REDRAW;  
          
        case RIGHT_BUTTON: case UP_BUTTON:
          while(pic_id<MAX_PATH&&!GetPITaddr(++pic_id));
        goto REDRAW;

    }
    REDRAW:
    update_header(data);
    RefreshGUI();
  }
  return(0); //Do standart keys
  //1: close
}

void gui_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Меню"};
  //static SOFTKEY_DESC sk_exit={0x0FF0,0x0000,(int)"Закрыть"};
  if (cmd==TI_CMD_CREATE)
  {
    /*EDIT_SetFocus(data,2);
    EDIT_SetCursorPos(data,2);*/
    static void *methods[16];
    void **m=GetDataOfItemByID(data,4);
    memcpy(methods,m[1],sizeof(methods));
    //    old_inp_redraw=methods[0];
    methods[0]=(void *)gui_redraw;
    m[1]=methods;
  }
  if(cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
    update_header(data);
  }
  if(cmd==TI_CMD_REDRAW)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    //SetSoftKey(data, &sk_exit, (SET_SOFT_KEY_N==0) ? 1 : 0);
  }
}

INPUTDIA_DESC gui_desc =
{
  1,
  gui_onkey,
  gui_ghook,
  (void *)gui_locret,
  0,
  &gui_skt,
  {0,0,0,0},
  FONT_SMALL,
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
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};
char hdr[64];

int create_gui_ed(void)
{
  void *ma=malloc_adr();
  void *eq;  

  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  WSHDR *ews=AllocWS(1);
  ConstructEditControl(&ec, ECT_HEADER, ECF_DISABLE_NUM , ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
    
  patch_header(&gui_hdr);
  patch_input(&gui_desc);
  
  
  
  FreeWS(ews);
  return CreateInputTextDialog(&gui_desc, &gui_hdr,eq,1,0);    
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM*csm=(MAIN_CSM*)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=create_gui_ed();
}

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
  }
  return(1);
}


const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SPView");
}

int main(const char *exename, const char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  char *path=strrchr(exename, '\\');
  path++;
  int lenght=path-exename;
  memcpy(MAIN_FOLDER, exename, lenght);
  if(fname)
  {
    //load_lang
  }
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
}

//вывод бля, такие вещи надо на си++ писать....
