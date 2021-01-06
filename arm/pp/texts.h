#include "..\inc\swilib.h"






void patch_inputT(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

void patch_header2T(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

SOFTKEY_DESC menu_skT[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)"blabla"}
};

SOFTKEYSTAB menu_sktT=
{
  menu_skT,0
};

int edit_type;
//extern void Edit_endproc(int type,char *dest);

int sf_inp_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);
    char dest[128];
    ws_2str(ec.pWS,dest,127);
   // Edit_endproc(edit_type,dest);
    strcpy(name,dest);

    RedrawScreen();
    return(1); //Close
  }
  return(0);
}

void sf_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Сохранить"};
  EDITCONTROL ec;
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
  }
}

void sf_inp_locret(void){}

HEADER_DESC sf_inp_hdr={0,0,0,0,NULL,(int)"Введите имя",LGP_NULL};

INPUTDIA_DESC sf_inp_desc=
{
  1,
  sf_inp_onkey,
  sf_inp_ghook,
  (void *)sf_inp_locret,
  0,
  &menu_sktT,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

extern const char perc_t[];
void CreateTextEditDialog(int type,char *src,int maxlen)
{
  WSHDR *e_ws=AllocWS(256);
  edit_type = type;
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  
  //utf8_2ws(e_ws,src,126);
  wsprintf(e_ws,"%s",src);
  ConstructEditControl(&ec,3,0x40,e_ws,maxlen);
  AddEditControlToEditQend(eq,&ec,ma);
  
  
  patch_header2T(&sf_inp_hdr);
  patch_inputT(&sf_inp_desc);
  CreateInputTextDialog(&sf_inp_desc,&sf_inp_hdr,eq,1,0);
}












