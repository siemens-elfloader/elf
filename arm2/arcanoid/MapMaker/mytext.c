#include "..\inc\swilib.h"
#include "rename.h"
#include "efm.h"

extern PSEARCH psearch;


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

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


#define icon 0
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};
int menusoftkeys[]={0,1,2};
SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};
volatile int edit_id;

extern WSHDR *e_ws;


int editmode;
int curpos;





extern void Tlog(char *string);
extern char lgn[128];




void insline(void) {}
void delline(void) {}
void splitline(void) {}
void joinlines(void) {}
void instime(void) {}
void insdate(void) {}
void paste(void) {}
void clearclipb(void) {}

void* edmenu_HNDLS[8]=
{
  (void *)insline,
  (void *)delline,
  (void *)splitline,
  (void *)joinlines,
  (void *)instime,
  (void *)insdate,
  (void *)paste,
  (void *)clearclipb
};

MENUITEM_DESC edmenu_ITEMS[8]=
{
  {NULL,(int)"Insert line"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Delete line"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Split line"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Join lines"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Insert time"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Insert date"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Paste"          ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Clear clipboard",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

HEADER_DESC edmenu_HDR={0,0,0,0,icon,(int)"Special...",LGP_NULL};

MENU_DESC edmenu_STRUCT=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  edmenu_ITEMS,
  (MENUPROCS_DESC*)&edmenu_HNDLS,
  8
};


char editline[256]; //Ѕуфер дл€ редактировани€ строки


extern int fm_nav_type;
extern int IsRename;
extern int rename_cur;
int rename_pos; //текуща€ позици€

extern int Getcurpos();


extern FINFO *finfo; //динамически малоченный массив типа FILEINFO
extern int fp_list_counter;
extern int fm_cur_ypos;


#define PARAMS_MAX_SIZE 50
extern int params[PARAMS_MAX_SIZE];
#define PARAMS_MC_MFONTSIZE       params[2]

extern void Refresh(int type);

extern WSHDR *search_name;

int ed_inp_onkey(GUI *data, GUI_MSG *msg)
{
  int k=msg->gbsmsg->submess;
  if (msg->keys==0xFFF)
  {
    editmode=0xFFF; //ѕризнак меню
    patch_header(&edmenu_HDR);
    edit_id=CreateMenu(0,0,&edmenu_STRUCT,&edmenu_HDR,0,8,0,0);
    return(1); //«акрываем лавочку
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if(k==LEFT_SOFT)
    {
      
      editmode=k;IsRename=0;
      rename_cur=0;
      rename_pos=0;
      fm_nav_type=0;
      if(!psearch.ename || !psearch.active)
      {
        char fname[512];
        char dest_fname[512];
        GetFullfname(fname,finfo[Getcurpos()].name);
        GetFullfname(dest_fname,editline);
        if(Rename(fname,dest_fname)<0) ShowMSG(1,(int)"unknown error 1");
      }
      else
      {
        
      }
      psearch.ename=0;
      Refresh(1);
      return(1);
    }
    if(k==GREEN_BUTTON)
    {
      psearch.ename=0;
      editmode=k;IsRename=0;
      rename_cur=0;
      rename_pos=0;
      fm_nav_type=0;
      return(1);
    }
  }
  return 0;
}

extern void RedrawScreen();


extern int char16to8(int c);

void ed_inp_redraw(void *data)
{
  if(psearch.ename) DrawRoundedFrame(0,psearch.yend_pos,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(7)); //фон
  
  RedrawScreen(); //redraw while renaming
  
  
  
}




void ed_inp_locret(void){}


int e_check=1;
void ed_inp_ghook(GUI *data, int cmd)
{
  //static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Menu"};
  static void *methods[16];
  EDITCONTROL ec;
  
  if(e_check) //пихаем в форму текущее им€
  {
    WSHDR *ws=AllocWS(256);
    str_2ws(ws,editline,256);
    EDIT_SetTextToFocused(data,ws);
    e_check=0;
    FreeWS(ws);
  }
  
  int ecp;
  if (cmd==2)
  {
    //Called after onCreate
    void **m=GetDataOfItemByID(data,4);
    memcpy(methods,m[1],sizeof(methods));
    methods[0]=(void *)ed_inp_redraw;
    m[1]=methods;
  }
  if (cmd==7)
  {
    if (!editmode)
    {
      //EDIT_SetCursorPos(data,curpos+1);
      editmode=0xFFFFFFFF;
    }
    ecp=EDIT_GetCursorPos(data);
    rename_pos=ecp-1; //реальна€ позици€
    //SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
    ws_2str(ec.pWS,editline,256);
    
    rename_cur=0;
    for(int i=0;i<rename_pos;i++) //получаем точную длину символов в написанной строке
    {
      int cur_sw = GetSymbolWidth(editline[i],PARAMS_MC_MFONTSIZE);
      rename_cur+=cur_sw;
    }
    wstrcpy(search_name,ec.pWS);
    wstrcpy(e_ws,ec.pWS);
  }
}

HEADER_DESC ed_inp_hdr={0,0,0,0,icon,(int)"Edit text",LGP_NULL};

INPUTDIA_DESC ed_inp_desc=
{
  1,
  ed_inp_onkey,
  ed_inp_ghook,
  (void *)ed_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};




void CreateEditDialog()
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  editmode=0;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,e_ws,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  
  rename_cur=0;
  rename_pos=0;
  
  //e_ws=AllocWS(128);
  //patch_header(&ed_inp_hdr);
  //patch_input(&ed_inp_desc);
  edit_id=CreateInputTextDialog(&ed_inp_desc,&ed_inp_hdr,eq,1,0);
}

void StartRename(char *src_name)
{
  e_check=1;
  CutWSTR(e_ws,256);
  wsprintf(e_ws,"");
  strcpy(editline,src_name);
  IsRename=1;
  fm_nav_type=2;
  CreateEditDialog();
}


void EnterSearchSymbols()
{
  e_check=0;
  psearch.ename=1;
  CutWSTR(e_ws,256);
  //strcpy(editline,src_name);
  CreateEditDialog();
  
}

