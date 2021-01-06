#include "..\inc\swilib.h"
#include "..\inc\xtask_ipc.h"
#include "init.h"
#include "conf_loader.h"


extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

CSM_DESC icsmd;
int MAINCSM_ID;
//============================config definitions
extern const char path[128];
extern char LinkCounters[10];
//============================config definitions

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

unsigned short maincsm_name_body[140];
const int minus11=-11;

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


int y=70;
int sub_x;
int start_anim;
int main_add;
int y_b;
int y_d;
int y2;
int sub_on;
int subbed;
int sub_pos;
int main_pos;
int sub_menu_c;
int sub_y;
int wap_browser();
int my_stuff();
int develop();
IMGHDR screen={0,0,8,""};

GBSTMR anime;
int inam;

void animating()
{
  inam=1;
  if(y_b!=70) 
  {
    y=y-3; y_d=y_d-3; y_b=y_b-3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating);
  }
  else
    if(main_add<=60)
    {
      main_add++;
      DirectRedrawGUI();
      GBS_StartTimerProc(&anime, 3, animating);
    }
  else
  {
    inam=0;
    DirectRedrawGUI();
  }
}

int dont_do;

void animating2()
{
  dont_do=1;
  inam=1;
  if(main_add>43)
  {
    main_add--;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating2);
  }
  else
  if(y_b!=160) 
  {
    y=y+3; y_d=y_d+3; y_b=y_b+3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating2);
  }
  else
    CloseCSM(MAINCSM_ID);
}

void animating3()
{
  inam=1;
  if((sub_x<79)&&(start_anim))
  {
    sub_x=sub_x+3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating3);
  }
  else
  if(sub_x>45)
  {
    start_anim=0;
    sub_x=sub_x-3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating3);
  }
  else
  {
    sub_x=45;
    inam=0;
    DirectRedrawGUI();
  }
}

void animating4()
{
  inam=1;
  if((sub_x<79)&&(!start_anim))
  {
    sub_x=sub_x+3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating4);
  }
  else
  if(sub_x>18)
  {
    start_anim=1;
    sub_x=sub_x-3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&anime, 3, animating4);
  }
  else
  {
    inam=0;
    start_anim=0;
    sub_on=0;
    DirectRedrawGUI();
  }
}

int tentimes;
int plus;

void animating7()
{
  inam=1;
  tentimes--;
  if(plus) y2++; else y2--;
  DirectRedrawGUI();
  if(tentimes) GBS_StartTimerProc(&anime, 3, animating7);
  else
    inam=0;
}

void animating8()
{
  inam=1;
  tentimes--;
  if(plus) y++; else y--;
  DirectRedrawGUI();
  if(tentimes) GBS_StartTimerProc(&anime, 3, animating8);
  else
    inam=0;
}

void DrwImg2(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void DoScreen()
{
    int ScrH=ScreenH();
    int ScrW=ScreenW();
    char *ms=RamScreenBuffer();
    screen.w=ScrW;
    screen.h=ScrH;
    screen.bitmap=malloc(ScrW*ScrH*2);
    memcpy(screen.bitmap, ms, ScrW*ScrH*2);
}

void ClockDraw()
{
    WSHDR *ws=AllocWS(64);
    TTime time;
    GetDateTime(NULL, &time);
    wsprintf(ws, "%02d:%02d:%02d", time.hour, time.min, time.sec);  
    void *canvasdata = BuildCanvas();
    DrawCanvas(canvasdata,126-Get_WS_width(ws,11),162,130,162+GetFontYSIZE(11)+3,1);
    DrawString(ws,128-Get_WS_width(ws,11),162,130,162+GetFontYSIZE(11)+3,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
}

GBSTMR min_ref;

void refresher()
{
  DirectRedrawGUI();
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  GBS_DelTimer(&min_ref);
  DrwImg2(&screen, 0, 0, NULL, NULL);
  if(!start_anim)
  {
  DrawImg(main_add,y_b-1,(int)"0:\\zbin\\my_menu\\main_add.png");
  DrawImg(0,y_b-1,(int)"0:\\zbin\\my_menu\\bg.png");
  DrawImg(0,y,(int)"0:\\zbin\\my_menu\\cursor.png");
  DrawImg(1,y_d-1,(int)"0:\\zbin\\my_menu\\main_list.png");
  DrawImg(0,157,(int)"0:\\zbin\\my_menu\\anime_bg.PNG");
  }
  if(sub_on)
  {
    switch(main_pos)
    {
    case 1:
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\inet_bg.png");
      DrawImg(sub_x,y2,(int)"0:\\zbin\\my_menu\\cursor.png");
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\inet_list.png");
      break;
    case 2:
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\game_bg.png");
      DrawImg(sub_x,y2,(int)"0:\\zbin\\my_menu\\cursor.png");
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\game_list.png");
      break;
    case 4:
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\soft_bg.png");
      DrawImg(sub_x,y2,(int)"0:\\zbin\\my_menu\\cursor.png");
      DrawImg(sub_x,y+3,(int)"0:\\zbin\\my_menu\\soft_list.png");
      break;
    }
  }
  if(start_anim)
  {
  DrawImg(main_add,y_b-1,(int)"0:\\zbin\\my_menu\\main_add.png");
  DrawImg(0,y_b-1,(int)"0:\\zbin\\my_menu\\bg.png");
  DrawImg(0,y,(int)"0:\\zbin\\my_menu\\cursor.png");
  DrawImg(1,y_d-1,(int)"0:\\zbin\\my_menu\\main_list.png");
  DrawImg(0,157,(int)"0:\\zbin\\my_menu\\anime_bg.PNG");
  }
  ClockDraw();
  GBS_StartTimerProc(&min_ref, 216, refresher);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  mfree(screen.bitmap);
//  GBS_DelTimer(&anime);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
//  char* ramIconBar = RamIconBar();
//  *ramIconBar = 1;
  
  CloseCSM(MAINCSM_ID);
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

GBSTMR mytmr;
void to_do()
{
  develop();
}

const char ipc_my_name[]="StartMenu";
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

void Engade()
{
  switch(main_pos)
  {
  case 1:
    switch(sub_pos)
    {
    case 1:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\naticq\\naticq.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\Zbin\\siejc\\siejc.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 3:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\Zbin\\utilities\\nrss.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 4:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\Zbin\\balletmini\\BalletMini.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 5:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\EMailClient\\mailviewer.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 6:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\applications\\mig33 beta\\mig33 beta.jar");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 7:
      {
/*      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A0427CC0", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);*/
        wap_browser();
      }
      break;
    case 8:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\daemons\\SieGet_NSG.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    }
    break;
  case 2:
    switch(sub_pos)
    {
    case 1:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\gameboy color\\Resident Evil Gaiden.gbc");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\gameboy color\\Metal Gear Solid.gbc");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 3:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\gameboy color\\Yu-Gi-Oh Dark Duel Stories.gbc");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 4:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\gamegear\\Shining_force_2.gg");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 5:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\nes\\battle_city.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 6:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\games\\nes\\scat.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    }
    break;
  case 3:
    {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\ZBin\\mc\\mc.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
    }
    break;
  case 4:
    switch(sub_pos)
    {
    case 1:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\Zbin\\utilities\\master.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\utilities\\pandemonium.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    }
    break;
  case 5:
    {
      my_stuff();
    }
    break;
  case 6:
    {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\daemons\\smsman.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
  /*  switch(sub_pos)
    {
    case 1:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5359", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 2:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5537", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 3:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5365", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 4:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F537D", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 5:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F53c5", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 6:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5585", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 7:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5421", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 8:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5731", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    }*/
    break;
  case 7:
    {
      GBS_StartTimerProc(&mytmr, 40, to_do);
      RefreshGUI();
      RefreshGUI();
      //develop();
    }
    break;
  case 8:
    {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\zbin\\utilities\\emenu.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
    }
    break;
  case 9:
    {
/*      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"0:\\ZBIN\\utilities\\turnoff.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);*/
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_OFFE,&gipc);
    }
    break;
  }
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{ 
  if (((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))&&(inam==0))
  {
 //   DirectRedrawGUI();  
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT: 
      if(sub_on)
        animating4();
      else
        animating2();
      break;
    case DOWN_BUTTON:
      {
        if(sub_on)
        {
          sub_pos++;
          y2=y2+10;
          if(y2>(sub_y-4+y)) 
          {
            sub_pos=1;
            y2=y+4;
          }
          else
          {
            y2=y2-10;
            tentimes=10;
            plus=1;
            animating7();
          }
        }
        else
        {
          main_pos++;
          y=y+10;
          if(y>156) 
          {
            y=70;
            main_pos=1;
          }
          else
          {
            y=y-10;
            tentimes=10;
            plus=1;
            animating8();
          }
        }
        DirectRedrawGUI();
      }
        break;
     case UP_BUTTON:
       {
          if(sub_on)
          {
            sub_pos--;
            y2=y2-10;
            if(y2<y-1) 
            {
              sub_pos=sub_menu_c;
              y2=y+sub_y-6;
              DirectRedrawGUI();
            }
            else
            {
              y2=y2+10;
              plus=0;
              tentimes=10;
              animating7();
            }
          }
          else
          {
            main_pos--;
            y=y-10;
            if(y<67) 
            {
              y=150;
              main_pos=9;
              DirectRedrawGUI();
            }
            else
            {
              y=y+10;
              plus=0;
              tentimes=10;
              animating8();
            }
          }
        }
        break;
    case ENTER_BUTTON:
      {
        if(sub_on)
        {
          Engade();
          sub_on=0;
          return(1);
        }
        else
        {
/*          if((main_pos==3)||(main_pos==5)||(main_pos==6)||(main_pos==7)||(main_pos==8)||(main_pos==9))
          {
            Engade();
            return(1);
          }*/
          if(LinkCounters[main_pos-1]=='0') {Engade(); return(1);}
          else
          {
            sub_menu_c=LinkCounters[main_pos-1];
/*          sub_menu_c=8;
          if(main_pos==6) sub_menu_c=8;
          if(main_pos==4) sub_menu_c=2;
          if(main_pos==2) sub_menu_c=6;*/
            sub_y=sub_menu_c*10;
            y2=y+4;
            sub_on=1;
            sub_pos=1;
            start_anim=1;
            sub_x=18;
            animating3();
          }
        }
      }
      break;
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

extern void kill_data(void *p,void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};


#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ElfKiller);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Fox menu");
}


void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(!IsScreenSaver()))
  {

  }
  return (csm_result);
}  

int my_keyhook(int key, int m)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==KEY_DOWN)&&(!IsScreenSaver()))
     if (key==UP_BUTTON) 
       {
         sub_on=0;
         DoScreen();
         LockSched();
         char dummy[sizeof(MAIN_CSM)];
         UpdateCSMname();
         MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
         UnlockSched();
         if(!dont_do) y=y+90;
         y_b=160;
         y_d=160;
         dont_do=0; 
         main_add=43;
//         sub_pos=1;
//         main_pos=1;
         animating();
       }
  
  return 0;
}

int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onClose=MyIDLECSM_onClose;  
  icsm->constr=&icsmd;  
  
  AddKeybMsgHook((void *)my_keyhook);

  UnlockSched();
  sub_pos=1;
  main_pos=1;
  InitConfig();
  InitFiles();
  return 0;
}
