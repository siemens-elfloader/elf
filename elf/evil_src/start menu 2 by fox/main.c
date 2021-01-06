#include "..\inc\swilib.h"


extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

CSM_DESC icsmd;

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


int y=27;
int y_d=27;
int y2;
int sub_on;
int subbed;
int sub_pos;
int main_pos;
int sub_menu_c;
int sub_y;
#define SCREENSIZE ScreenH()*ScreenW()/////////////////
#define HSIZE YDISP*ScreenW()///////////////////////
DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)//////////////////
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

IMGHDR img2;

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrwImg(&img2, 0, YDISP, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); ////////
  DrawImg(0,25,(int)"4:\\zbin\\my_menu\\bg.png");
  DrawImg(0,y,(int)"4:\\zbin\\my_menu\\cursor.png");
  DrawImg(0,y_d+1,(int)"4:\\zbin\\my_menu\\main_mn\\main_1.png");
  DrawImg(0,y_d+18,(int)"4:\\zbin\\my_menu\\main_mn\\main_2.png");
  DrawImg(0,y_d+35,(int)"4:\\zbin\\my_menu\\main_mn\\main_3.png");
  DrawImg(0,y_d+52,(int)"4:\\zbin\\my_menu\\main_mn\\main_4.png");
  DrawImg(0,y_d+69,(int)"4:\\zbin\\my_menu\\main_mn\\main_5.png");
  DrawImg(0,y_d+86,(int)"4:\\zbin\\my_menu\\main_mn\\main_6.png");
  DrawImg(0,y_d+103,(int)"4:\\zbin\\my_menu\\main_mn\\main_7.png");
  DrawImg(0,y_d+120,(int)"4:\\zbin\\my_menu\\main_mn\\main_8.png");
  DrawImg(0,y_d+137,(int)"4:\\zbin\\my_menu\\main_mn\\main_9.png");
  if(sub_on)
  {
    switch(main_pos)
    {
    case 1:
      DrawImg(50,y+10,(int)"4:\\zbin\\my_menu\\bg.png");
      DrawImg(50,y2,(int)"4:\\zbin\\my_menu\\cursor.png");
      DrawImg(52,y+11,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_1.png");
      DrawImg(52,y+28,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_2.png");
      DrawImg(52,y+45,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_3.png");
      DrawImg(52,y+62,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_4.png");
      DrawImg(52,y+79,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_5.png");
      DrawImg(52,y+96,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_6.png");
      DrawImg(52,y+113,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_7.png");
      DrawImg(52,y+130,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_8.png");
      DrawImg(52,y+147,(int)"4:\\zbin\\my_menu\\inet_menu\\inet_9.png");
      break;
    case 2:
      DrawImg(50,y+10,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_bg.png");
      DrawImg(50,y2,(int)"4:\\zbin\\my_menu\\cursor.png");
      DrawImg(52,y+11,(int)"4:\\zbin\\my_menu\\game_menu\\game_1.png");
      DrawImg(52,y+28,(int)"4:\\zbin\\my_menu\\game_menu\\game_2.png");
      DrawImg(52,y+45,(int)"4:\\zbin\\my_menu\\game_menu\\game_3.png");
      DrawImg(52,y+62,(int)"4:\\zbin\\my_menu\\game_menu\\game_4.png");
      DrawImg(52,y+79,(int)"4:\\zbin\\my_menu\\game_menu\\game_5.png");
      DrawImg(52,y+96,(int)"4:\\zbin\\my_menu\\game_menu\\game_6.png");
      break;
    case 4:
      DrawImg(50,y+10,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_bg.png");
      DrawImg(50,y2,(int)"4:\\zbin\\my_menu\\cursor.png");
      DrawImg(52,y+11,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_1.png");
      DrawImg(52,y+28,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_2.png");
      DrawImg(52,y+45,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_3.png");
      DrawImg(52,y+62,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_4.png");
      DrawImg(52,y+79,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_5.png");
      DrawImg(52,y+96,(int)"4:\\zbin\\my_menu\\soft_menu\\soft_6.png");
      break;
    case 6:
      DrawImg(50,y+10,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_bg.png");
      DrawImg(50,y2,(int)"4:\\zbin\\my_menu\\cursor.png");
      DrawImg(52,y+11,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_1.png");
      DrawImg(52,y+28,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_2.png");
      DrawImg(52,y+45,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_3.png");
      DrawImg(52,y+62,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_4.png");
      DrawImg(52,y+79,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_5.png");
      DrawImg(52,y+96,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_6.png");
      DrawImg(52,y+113,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_7.png");
      DrawImg(52,y+130,(int)"4:\\zbin\\my_menu\\msg_menu\\msg_8.png");
      break;
    case 8:
      DrawImg(50,y+10,(int)"4:\\zbin\\my_menu\\bg.png");
      DrawImg(50,y2,(int)"4:\\zbin\\my_menu\\cursor.png");
      DrawImg(52,y+11,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_1.png");
      DrawImg(52,y+28,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_2.png");
      DrawImg(52,y+45,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_3.png");
      DrawImg(52,y+62,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_4.png");
      DrawImg(52,y+79,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_5.png");
      DrawImg(52,y+96,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_6.png");
      DrawImg(52,y+113,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_7.png");
      DrawImg(52,y+130,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_8.png");
      DrawImg(52,y+147,(int)"4:\\zbin\\my_menu\\sett_menu\\sett_9.png");
      break;
    }
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  LockSched();
  short *p=malloc((SCREENSIZE-HSIZE)*sizeof(short)), *pp=RamScreenBuffer(); 
  pp+=HSIZE; 
  IMGHDR img={ScreenW(),(ScreenH()-YDISP),8,(char *)p};
  
  for(int i=0;i<SCREENSIZE-HSIZE;i++) 
    *p++=*pp++; 
  img2=img;
//  DrwImg(&img, 0, YDISP, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
  mfree(img.bitmap);
  UnlockSched();
  char* ramIconBar = RamIconBar();
  *ramIconBar = 0;
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  char* ramIconBar = RamIconBar();
  *ramIconBar = 1;
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

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
      wsprintf(elfname,(char*)"4:\\zbin\\weather\\weather.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\Zbin\\NatICQ\\NatICQ.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 3:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\Zbin\\NatICQ\\NatICQ2.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 4:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\Zbin\\siejc\\siejc.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 5:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\balletmini\\operamini.oms");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 6:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emailclient\\mailviewer.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 7:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F52E7", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 8:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\viskas kas nav elf\\java\\soft\\mig33.jar");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 9:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\utilities\\nrss.elf");
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
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\tank.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\mario.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 3:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\contra.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 4:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\scat.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 5:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\felix.nes");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 6:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\emul\\shining_force_2.gg");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    }
    break;
  case 3:
    {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\ZBin\\mc\\mc.elf");
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
      wsprintf(elfname,(char*)"4:\\Zbin\\utilities\\mrs_editor.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 2:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\zbin\\utilities\\ext_manager.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    case 3:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\Zbin\\utilities\\pandemonium.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;  
    case 4:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\Zbin\\utilities\\tw6.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;  
    case 5:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\viskas kas nav elf\\java\\master\\master.jar");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break; 
    case 6:
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\viskas kas nav elf\\java\\soft\\icqmobireg.jar");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      break;
    }
    break;
  case 5:
    {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5839", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
    }
    break;
  case 6:
    switch(sub_pos)
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
    }
    break;
  case 7:
    {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A19F8805", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
    }
    break;
  case 8:
    switch(sub_pos)
    {
    case 1:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5B65", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 2:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5D6B", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 3:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5E45", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 4:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F5FBD", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 5:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F60F9", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 6:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F620F", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 7:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F62C7", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 8:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F6421", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    case 9:
      {
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul( (char*)"A06F64FD", 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
      }
      break;
    }
    break;
  case 9:
    {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,(char*)"4:\\ZBIN\\utilities\\turnoff.elf");
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
    }
    break;
  }
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  DirectRedrawGUI();  
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {          
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT: 
      if(sub_on)
      {
        sub_on=0;
      }
      else
      return(1);
      break;
    case DOWN_BUTTON:
      {
        if(sub_on)
        {
          sub_pos++;
          y2=y2+17;
          if(y2>(sub_y-4+y)) 
          {
            sub_pos=1;
            y2=y+11;
          }
        }
        else
        {
          main_pos++;
          y=y+17;
          if(y>175) 
          {
            y=27;
            main_pos=1;
          }
        }
      }
        break;
     case UP_BUTTON:
       {
          if(sub_on)
          {
            sub_pos--;
            y2=y2-17;
            if(y2<y-1) 
            {
              sub_pos=sub_menu_c;
              y2=y+sub_y-8;
            }
          }
          else
          {
            main_pos--;
            y=y-17;
            if(y<24) 
            {
              y=153+9;
              main_pos=9;
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
          if((main_pos==3)||(main_pos==5)||(main_pos==7)||(main_pos==9))
          {
            Engade();
            return(1);
          }
          else
          {
          sub_menu_c=9;
          if(main_pos==6) sub_menu_c=8;
          if(main_pos==4) sub_menu_c=6;
          if(main_pos==2) sub_menu_c=6;
          sub_y=sub_menu_c*17;
          y2=y+11;
          sub_on=1;
          sub_pos=1;
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
     if (key==0x01) 
       {
         LockSched();
         char dummy[sizeof(MAIN_CSM)];
         UpdateCSMname();
         CreateCSM(&MAINCSM.maincsm,dummy,2);
         UnlockSched();
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
  
  return 0;
}
