#include "..\inc\swilib.h"
#include "..\inc\pnglist.h"

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

const int minus11=-11;
unsigned short maincsm_name_body[140];
extern void kill_data(void *p, void (*func_p)(void *));
int show_pic=0;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
}MAIN_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int get_number_of_png()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl;
  int i=0;
  if ((pl=ptop->pltop))
  {
    while (pl)
    {
      pl=pl->next;
      i++;
    }
  }
  return (i);
}

PNGLIST* find_pic_by_n(int n)
{
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl;
  if ((pl=ptop->pltop))
  {
    int i=0;
    while(i!=n && pl)
    {
      pl=pl->next;
      i++;
    }
    return (pl);
  }
  else return (0);
}

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void clear_cache()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl;
  LockSched();
  pl=ptop->pltop;
  ptop->pltop=0;
  UnlockSched();
  while(pl)
  {
    PNGLIST *pl_prev;
    pl_prev=pl;
    pl=pl->next;
    mfree(pl_prev->pngname);
    if(pl_prev->img)
    {
      mfree(pl_prev->img->bitmap);
      mfree(pl_prev->img);
    }
    mfree(pl_prev);
  }
  show_pic=0;
  REDRAW();
}

void clear_bitmap()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  char *bitmap;
  if ((bitmap=ptop->bitmap))
  {
    LockSched();
    zeromem(bitmap,20000/8*2);
    UnlockSched();
  }
}
  
unsigned int total_size()
{
  unsigned int n=0;
  unsigned int img_w, img_h;
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl=ptop->pltop;
  while (pl)
  {
    n+=sizeof(PNGLIST);
    n+=(strlen(pl->pngname)+1);
    if(pl->img)
    {
      img_w=pl->img->w;
      img_h=pl->img->h;
      n+=sizeof(IMGHDR);
      switch (pl->img->bpnum)
      {
      case 1:
        n+=((img_w&7?((img_w>>3)+1):(img_w>>3))*img_h);
        break;
        
      case 5:
        n+=(img_w*img_h);
        break;
        
      case 8:
        n+=(2*img_w*img_h);
        break;
      }
    }
    pl=pl->next;
  }
  return (n);
}


int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

void test_locret(void){}


int test_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char str[128];
  if (msg->keys==0xFFF)
  {
    ExtractEditControl(data,2,&ec);
    ws_2str(ec.pWS,str,127);
    GetPITaddr((int)str);
    return (1);
  }
  return(0); //Do standart keys
  //1: close
}

void test_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Test"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==2)
  {
    EDIT_SetFocus(data,2);
    EDIT_SetCursorPos(data,2);
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

HEADER_DESC test_hdr={0,0,0,0,NULL,(int)"Test",LGP_NULL};

INPUTDIA_DESC test_desc =
{
  1,
  test_onkey,
  test_ghook,
  (void *)test_locret,
  0,
  &menu_skt,
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


void create_test_pic(void)
{
  void *ma=malloc_adr();
  void *eq;  

  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  WSHDR *ews=AllocWS(128);
  wsprintf(ews,"%t","Path File:");  
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
  
  str_2ws(ews,"0:\\.png",127);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);  
    
  patch_header(&test_hdr);
  patch_input(&test_desc);
  FreeWS(ews);
  CreateInputTextDialog(&test_desc,&test_hdr,eq,1,0);    
  
}

int get_string_width(WSHDR *ws, int font)
{
  return (Get_WS_width(ws, font)+1);
}

void OnRedraw(MAIN_GUI *data)
{
  int x=ScreenW();
  int y=ScreenH();
  
  PNGLIST* current;
  DrawRoundedFrame(0,YDISP+0,x-1,y-1,0,0,0,
                   GetPaletteAdrByColorIndex(0),
                   GetPaletteAdrByColorIndex(20));

  wsprintf(data->ws1,"Opened:%u",get_number_of_png());
  DrawString(data->ws1,3,YDISP+3,get_string_width(data->ws1, FONT_SMALL)+3,YDISP+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    
  if (!show_pic)
    wsprintf(data->ws1,"Top Pic");
  else
  {
    if (show_pic<0) show_pic=(get_number_of_png()-1);
    if (show_pic>(get_number_of_png()-1)) show_pic=0;
    wsprintf(data->ws1,"Cache %u",show_pic);
  }
  DrawString(data->ws1,x-4-get_string_width(data->ws1, FONT_SMALL),YDISP+3,x-4,YDISP+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  current=find_pic_by_n(show_pic);

  int width=x-2-1;
  int height=y-2-29+YDISP; 
    
  if (current)
  {
    wsprintf(data->ws1,"%s",current->pngname);
    DrawString(data->ws1,3,YDISP+GetFontYSIZE(FONT_SMALL),x-4,YDISP+GetFontYSIZE(FONT_SMALL)*2,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
    DrawRoundedFrame(1,YDISP+GetFontYSIZE(FONT_SMALL)*2+1,x-2,y-2,0,0,0,
                     GetPaletteAdrByColorIndex(0),
                     GetPaletteAdrByColorIndex(20));
    
    if (current->img)
    {
      width=(current->img->w>=width)?0:(width-current->img->w)/2;
      height=(current->img->h>=height)?0:29+(height-current->img->h)/2; 
      DrwImg(current->img,width,height,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    }      
  }
  wsprintf(data->ws1,"%u B",total_size());
  DrawString(data->ws1,2,y-GetFontYSIZE(FONT_SMALL)-1,x-1,y-1,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
}


void OnCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void OnClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void OnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void OnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    case '0':
      show_pic=0;
      break;
    case '1':
      clear_bitmap();
      clear_cache();
      break;
      
    case LEFT_BUTTON:
    case '4':
      show_pic--;
      break;
    case RIGHT_BUTTON:
    case '6':
      show_pic++;
      break;
      
    case '7':
      create_test_pic();
      break;
      
    }
  }
  return (0);
  
}


int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)OnCreate,	//Create
  (void *)OnClose,	//Close
  (void *)OnFocus,	//Focus
  (void *)OnUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data, //method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  Canvas.x2=ScreenW()-1;
  Canvas.y2=ScreenH()-1;
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Png_ext_test");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
}
