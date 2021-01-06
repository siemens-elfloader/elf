//#define NEWSGOLD

#include "..\..\inc\swilib.h"
#include "conf_loader.h"

const char p_u[]="%u";
const char p_x[]="%x";

extern const int cfg_st;
extern const unsigned int cfg_s1;
extern const unsigned int cfg_s2;
extern const unsigned int cfg_p;
extern const int cfg_lk;
extern const unsigned int cfg_bg;
extern const unsigned int cfg_tx;
extern const char cfg_test[81];
extern const int cfg_kh;

extern const char pic[];
extern const char sound[];
extern const char wait[];
extern const char font[];
extern const char atr[];
extern const char colour[];
extern const char keyc[];
extern const char item[];
extern const char sounds[];
extern const char pics[];
extern const char fonts[];
extern const char colours[];
extern const char colours24[];
extern const char keycs[];
extern const char options[];
extern const char exit[];
extern const char rgba[];
extern const char test[];

extern int cfg_path;

#pragma inline
void patch_input(INPUTDIA_DESC* inp,int x,int y,int x2,int y2)
{
  inp->rc.x=x;
  inp->rc.y=y;
  inp->rc.x2=x2;
  inp->rc.y2=y2;
}

#pragma inline
void patch_header(HEADER_DESC* head,int x,int y,int x2,int y2)
{
  head->rc.x=x;
  head->rc.y=y;
  head->rc.x2=x2;
  head->rc.y2=y2;
}

int edit=0;
WSHDR *ws;
unsigned int mell=0;
int grp=-1;
GBSTMR ptmr;
char locked=0;
char sh,sw;
unsigned short maincsm_name_body[140];
char lng=0;
unsigned char cl_r=0,cl_g=0,cl_b=0,cl_a=0;

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

extern void kill_data(void *p, void (*func_p)(void *));

int my_keyhook(int submsg, int msg);

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  FreeWS(ws);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void create_ed();
void DispMenu(void);

void PPause()
{
  PlaySound(0,0,0,mell,0);
  locked=0;
  DirectRedrawGUI();
}

void PlaySound_1(int mell)
{
  if (cfg_st)
  {
    if (cfg_lk) locked=1;
    if (cfg_s1!=2000) PlaySound(0,0,0,cfg_s1,0);
    if (cfg_s2!=2000) PlaySound(0,0,0,cfg_s2,0);
    if (mell!=2000) GBS_StartTimerProc(&ptmr,(cfg_p*262)/100, PPause);
  }
  else PlaySound(0,0,0,mell,0);
}
 

void method0(MAIN_GUI *data)
{
  if (grp==-1) {GeneralFuncF1(1);return;}
  DrawRoundedFrame(0,0,sw-1,sh-1,0,0,0,
		   GetPaletteAdrByColorIndex(cfg_bg),
		   GetPaletteAdrByColorIndex(cfg_bg));
  if (grp==1)
  {
    short h=GetImgHeight(mell);
    short w=GetImgWidth(mell);
    int y,x;
    if (w<=sw-2) x=sw/2 -w/2 -1;
    else x=sw-w-1;
    if (h+15<=sh-2) y=sh/2 -h/2 -1+15;
    else y=sh-h-1;
    DrawRoundedFrame(x,y,w+1+x,h+1+y,0,0,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    DrawImg(x+1,y+1, mell);
    
    wsprintf(data->ws1,"%t:%3u %3xh %3ux%u",pic,mell,mell,w,h);
    DrawString(data->ws1,1,3,sw-2,sh-1,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));

  }
  else if (grp==2)
  {
    wsprintf(data->ws1,"%t: %3u %3xh",sound,mell,mell);
    DrawString(data->ws1,1,3,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    if (locked)
    {
      wsprintf(data->ws1,"%t",wait);
      DrawString(data->ws1,2,20,sw-2,sh-5,SMALL_FONT,2,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    }
  }
  else if (grp==3)
  {
    wsprintf(data->ws1,"%t: %u %t: %u",font,mell,atr,locked);
    DrawString(data->ws1,1,3,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));    
    wsprintf(data->ws1,"%t",cfg_test);
    DrawString(data->ws1,1,20,sw-2,sh-3,mell,locked,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));    
  }
  else if (grp==4)
  {
    unsigned int t=cl_a+0x100*(cl_b+0x100*(cl_g+0x100*cl_r));
    wsprintf(data->ws1,"%t(DEC): %u\n%t(HEX): %08x",colour,t,colour,t);
    DrawString(data->ws1,1,3,sw-2,sh-3,SMALL_FONT+((mell==0)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));    
    wsprintf(data->ws1,"DEC:");
    DrawString(data->ws1,0,43,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,"%t",rgba);
    DrawString(data->ws1,25,29,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_u,cl_r);
    DrawString(data->ws1,25,43,sw-2,sh-3,SMALL_FONT+((mell==1)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_u,cl_g);
    DrawString(data->ws1,50,43,sw-2,sh-3,SMALL_FONT+((mell==2)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_u,cl_b);
    DrawString(data->ws1,75,43,sw-2,sh-3,SMALL_FONT+((mell==3)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_u,cl_a);
    DrawString(data->ws1,100,43,sw-2,sh-3,SMALL_FONT+((mell==4)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));

    wsprintf(data->ws1,"HEX:");
    DrawString(data->ws1,0,58,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_x,cl_r);
    DrawString(data->ws1,25,58,sw-2,sh-3,SMALL_FONT+((mell==1)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_x,cl_g);
    DrawString(data->ws1,50,58,sw-2,sh-3,SMALL_FONT+((mell==2)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_x,cl_b);
    DrawString(data->ws1,75,58,sw-2,sh-3,SMALL_FONT+((mell==3)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    wsprintf(data->ws1,p_x,cl_a);
    DrawString(data->ws1,100,58,sw-2,sh-3,SMALL_FONT+((mell==4)?1:0),0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
    char dest[4];
    setColor(cl_r,cl_g,cl_b,cl_a,(char*)&dest);
    wsprintf(data->ws1,"%t",test);
    DrawString(data->ws1,0,74,sw-2,sh-3,SMALL_FONT,2,(char*)&dest,GetPaletteAdrByColorIndex(23));
    DrawRoundedFrame(0,90,sw-1,sh-1,0,0,0,GetPaletteAdrByColorIndex(0),(char*)&dest);
 
  }
  else if (grp==5)
  {
    wsprintf(data->ws1,"%t: %u",colour,mell);
    DrawString(data->ws1,1,3,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));    
    wsprintf(data->ws1,"%t",test);
    DrawString(data->ws1,0,22,sw-2,sh-3,SMALL_FONT,2,GetPaletteAdrByColorIndex(mell),GetPaletteAdrByColorIndex(23));
    DrawRoundedFrame(0,40,sw-1,sh-1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(mell));
  }
  else if (grp==6)
  {
    wsprintf(data->ws1,"%t: %3u %3xh",keyc,mell,mell);
    DrawString(data->ws1,1,3,sw-2,sh-3,SMALL_FONT,0,GetPaletteAdrByColorIndex(cfg_tx),GetPaletteAdrByColorIndex(23));
  }
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  DispMenu();
  {
    data->ws1=AllocWS(256);
    data->ws2=AllocWS(256);
    data->gui.state=1;
  }
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

void Check(char plus,char play)
{
  if (grp==4)
  {
    switch (mell){
    case 1: cl_r+=plus*2 -1;break;
    case 2: cl_g+=plus*2 -1;break;
    case 3: cl_b+=plus*2 -1;break;
    case 4: cl_a+=plus*2 -1;break;
    }
    if (mell==4)
    {
      if (cl_a>200) cl_a=100;
      else
      if (cl_a>100) cl_a=0;
    }
  }
  else 
  {
  if (plus==1)
  {
    if (++mell==0) mell--;
    else
      if (grp==1)
      {
        short h=GetImgHeight(mell);
        short w=GetImgWidth(mell);
        unsigned short tmell=mell;
        if ((!w)||(w==0xff)||(h==0xff)||(!h))
        while ((tmell-mell<1000)&&(tmell))
        {
          tmell++;
          h=GetImgHeight(tmell);
          if ((!h)||(h==0xff)) continue;
          w=GetImgWidth(tmell);
          if ((w)&&(w!=0xff)) { mell=tmell;  break;}
        }
        if (mell!=tmell) {mell--; ShowMSG(1,(int)"Couldn't find valid image, closer than 1000!");}
      }
  }
  else if (plus==0)
    if (mell>0)
    {
      mell--;
      if (grp==1)
      {
        short h=GetImgHeight(mell);
        short w=GetImgWidth(mell);
        unsigned short tmell=mell;
        if ((!w)||(w==0xff)||(h==0xff)||(!h))
        while ((mell-tmell<1000)&&(tmell))
        {
          tmell--;
          h=GetImgHeight(tmell);
          if ((!h)||(h==0xff)) continue;
          w=GetImgWidth(tmell);
          if ((w)&&(w!=0xff)) { mell=tmell;  break;}
        }
        if (mell!=tmell) {mell--; ShowMSG(1,(int)"Couldn't find valid image, closer than 1000!");}
      }
    }
  if ((grp==2)&&(play)) PlaySound_1(mell);
  }
}

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  if (grp==6)
  {
    if (cfg_kh==0)
      if (msg->gbsmsg->msg==KEY_UP)
        mell=msg->gbsmsg->submess;
    DirectRedrawGUI();
    if (msg->gbsmsg->msg==LONG_PRESS)
    {
      if (msg->gbsmsg->submess==RIGHT_SOFT)
      {
        if (cfg_kh!=0)
          RemoveKeybMsgHook((void *)my_keyhook);
        grp=1;
        DispMenu();
      }
      else if (msg->gbsmsg->submess==LEFT_SOFT)
        create_ed();
    }
    return 0;
  }
  
  if (msg->gbsmsg->submess==RED_BUTTON)
  {
    return(1); //Закрываем лавочку
  }
  
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    lng=1;
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
      if (grp==3) {if (++locked==0) locked--; break;}
    case DOWN_BUTTON:
      Check(1,0);
      break;
    case LEFT_BUTTON:
      if (grp==3) {if (locked>0) locked--; break;}
    case UP_BUTTON:
      Check(0,0);
      break;
    }
  }

  if ((msg->gbsmsg->msg==KEY_DOWN)||((msg->gbsmsg->msg==KEY_UP)&&(lng)))
  {
    lng=0;
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
      if (grp==3) {if (++locked==0) locked--; break;}
      if (grp==4) {if (++mell==5) mell=0; break;}
    case DOWN_BUTTON:
      if ((grp==4)&&(mell==0)) {mell=1; break;}
      if ((grp!=2)||(!locked)) Check(1,1);
      break;
    case LEFT_BUTTON: 
      if (grp==3) {if (locked>0) locked--; break;}
      if (grp==4) {if (mell>0) mell--; else mell=4; break;}
    case UP_BUTTON:
      if ((grp==4)&&(mell==0)) {mell=4; break;}
      if ((grp!=2)||(!locked)) Check(0,1);
      break;
    case LEFT_SOFT:
      create_ed();
      break;
    case RIGHT_SOFT:
      {
        if ((cfg_st)&&(grp==2)) {locked=0;PlaySound_1(2000);}
        if (grp==3)locked=0;
//        grp=0;
        DispMenu();
      }break;
    case ENTER_BUTTON:
      if ((grp!=2)||(!locked)) Check(2,1);
    }
  }
  DirectRedrawGUI();
  return(0);
}
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
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
  ws=AllocWS(256);
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

void maincsm_onclose(CSM_RAM *csm)
{
  if ((cfg_st)&&(!grp)) {locked=0;PlaySound_1(2000);}
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const int minus11=-11;

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"IWatch");
}

void DrawGUI()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
}

int main()
{
  InitConfig();
  sh=ScreenH();
  sw=ScreenW();
/*  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  CreateCSM(&maincsm,dummy,0);
*/  
//   UnlockSched();
  DrawGUI();
//  DispMenu();
  return 0;
}

void ed1_locret(void){}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  int k=msg->gbsmsg->submess;
  if (k==RED_BUTTON)
  {
   return(1); //Закрываем лавочку
  }
  if(k==RIGHT_SOFT)
  {
    if (grp==6) return(1); 
    if (grp!=4)
    {
      mell=edit;
      if (grp==2) PlaySound_1(mell);
    }
    else
    {
      switch (mell)
      {
      case 0:
        {
          cl_a=edit&0xFF;
          edit>>=8;
          cl_b=edit&0xFF;
          edit>>=8;
          cl_g=edit&0xFF;
          edit>>=8;
          cl_r=edit;
        }
        break;
      case 1: cl_r=edit;break;
      case 2: cl_g=edit;break;
      case 3: cl_b=edit;break;
      case 4: cl_a=edit;break;
      }
    }
    return(1);
  }
  return(0); //Do standart keys
  //1: close
}

void ed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  int i,j;
  char ss[16];
  i=EDIT_GetFocus(data);
  ExtractEditControl(data,i,&ec);
  wstrcpy(ws,ec.pWS);
  ws_2str(ws,ss,15);
  j=0;
  if (i==1)
  {
    i=0;
    while ((ss[i]!=0)&&(i<15)) j=j*10+ss[i++]-0x30;
    wstrcpy(ws,ec.pWS);
    ExtractEditControl(data,3,&ec);
    wsprintf(ec.pWS,"%08x",j);
    StoreEditControl(data,3,&ec);
  }
  else if (i==3)
    {
      i=0;
      while ((ss[i]!=0)&&(i<15))
      {
        j*=16;
        if ((0x30<=ss[i])&&(ss[i]<=0x39)) j+=ss[i]-0x30;
        else if ((0x41<=ss[i])&&(ss[i]<=0x46)) j+=ss[i]-0x37;
        else if ((0x61<=ss[i])&&(ss[i]<=0x66)) j+=ss[i]-0x57;
        else j=0;
        i++;
      }
      ExtractEditControl(data,1,&ec);
      wsprintf(ec.pWS,"%u",j);
      StoreEditControl(data,1,&ec);
    }
  edit=j;
}

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)item,LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0,
};

void create_ed()
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  int scr_w,head_h;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  if (grp!=4)
  {
    wsprintf(ws,"%d ",mell);
    ConstructEditControl(&ec,6,0x40,ws,10);//6,0x40
    AddEditControlToEditQend(eq,&ec,ma);
    wsprintf(ws,"HEX:");
    ConstructEditControl(&ec,1,0x40,ws,10);//1
    AddEditControlToEditQend(eq,&ec,ma);
    wsprintf(ws,"%x ",mell);
    ConstructEditControl(&ec,3,0x40,ws,10);//3,0x40 16
    AddEditControlToEditQend(eq,&ec,ma);
  }
  else
  {
    unsigned long t;
    switch (mell)
    {
    case 0:
      {
        t=cl_a+0x100*(cl_b+0x100*(cl_g+0x100*cl_r));
      }break;
    case 1: t=cl_r;break;
    case 2: t=cl_g;break;
    case 3: t=cl_b;break;
    case 4: t=cl_a;break;
    }
    wsprintf(ws,"%u ",t);
    ConstructEditControl(&ec,6,0x40,ws,10);//6,0x40
    AddEditControlToEditQend(eq,&ec,ma);
    wsprintf(ws,"HEX:");
    ConstructEditControl(&ec,1,0x40,ws,10);//1
    AddEditControlToEditQend(eq,&ec,ma);
    wsprintf(ws,"%08x ",t);
    ConstructEditControl(&ec,3,0x40,ws,10);//3,0x40 16
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  scr_w=ScreenW();
  head_h=HeaderH();
  patch_header(&ed1_hdr,0,0,scr_w-1,head_h);
  patch_input(&ed1_desc,0,head_h+1,scr_w-1,ScreenH()-SoftkeyH()-1);
  CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

void Snds(void)
{
  InitConfig();
  locked=0;
  grp=2;
  GeneralFuncF1(1);
}

void Grps(void)
{
  InitConfig();
  grp=1;
  GeneralFuncF1(1);
}

void Fonts()
{
  InitConfig();
  grp=3;
  GeneralFuncF1(1);
}

void RGB()
{
  mell=0;
  InitConfig();
  grp=4;
  GeneralFuncF1(1);
}

void RGB24()
{
  InitConfig();
  grp=5;
  GeneralFuncF1(1);
}


int my_keyhook(int submsg, int msg)
{
  if (msg==KEY_UP)
  {
    mell=submsg;
    DirectRedrawGUI();
  }
  return(2);
}

void KeyC()
{
  InitConfig();
  grp=6;
  if (cfg_kh==1)
    AddKeybMsgHook((void*)my_keyhook);
  else if (cfg_kh==2)
    AddKeybMsgHook_end((void*)my_keyhook);
  GeneralFuncF1(1);
}

void Options()
{
  InitConfig();
  wsprintf(ws,"%d:\\ZBin\\etc\\IWatch.bcfg",cfg_path);
  ExecuteFile(ws,0,0);
}

void Exits(void)
{
  grp=-1;
  /*  SUBPROC((void *)ElfKiller);*/
  GeneralFuncF1(1);
}

HEADER_DESC menuhdr={0,0,131,21,NULL,(int)"IWatch",LGP_NULL};
int menusoftkeys[]={0,1,2};

MENUITEM_DESC menuitems[8]=
{
  {NULL,(int)sounds,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)pics,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)fonts,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)colours,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)colours24,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)keycs,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)options,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)exit,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *menuprocs[8]={(void *)Snds, (void *) Grps, (void *) Fonts, (void *) RGB, (void *) RGB24, (void *) KeyC, (void *) Options, (void *) Exits };

MENU_DESC tmenu=
{
  0,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  8,
  NULL,
  menuitems,
  menuprocs,
  8
};

void DispMenu(void)
{
  menuhdr.rc.x2=sw-1;
  CreateMenu(0,0,&tmenu,&menuhdr,0,8,0,0);
}
