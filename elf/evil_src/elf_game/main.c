#include "..\inc\swilib.h"
#include "strings.h"
#include "RANDOM.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
GUI *ggui=0;

#define wslen(ws) ws->wsbody[0]

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


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

char defend2[16];
int defend;
char hit_info[32];
int my_def_hp=5;
int enemy_def_hp=5;
int hp_my=5;
int hp2_my=5;
int hp_enemy=5;
int hp2_enemy=5;
char hp_info_my[16];
char hp_info_enemy[16];
int set_shoot;
char my_nick[]="Character: Player";
char enemy_nick[]="Character: Enemy";
char my_weapon[]="Weapon: pistol(1-3)";
char enemy_weapon[]="Weapon: pistol(1-3)";
char my_armor[]="Armor: none";
char enemy_armor[]="Armor: none";
char my_lvl[16];
int player_lvl=1;
char enemy_lvl[16];
int player_enemy_lvl=1;
char hp_info_enemy[16];
char my_def[]="Defend direction:";
char enemy_def[]="Attack direction:";
char left[]="left";
char right[]="right";
char center[]="center";
char Missed[]="Missed";
char Hit[]="Hit";
int power_hit;
int show_log;
int game_state;

GBSTMR mytmr;
//=====================ipc send======================//
const char ipc_my_name[]="Combats";
const char ipc_send_name[]="NatICQ";
const char percent_d[]="%d";

#define IPC_SENDMSG 5
#define IPC_GAME_DATA 24

typedef struct{
  unsigned long uin;
  char *msg;
}IPCssg;

typedef struct
{
  IPCssg IPCMsg;
  char data[16384];
}TPKT;

unsigned int UIN=315384924;
char send_data[64];
IPC_REQ tmr_gipc;
//====================ipc send=======================//
void SendGameEngade()
{
  sprintf(send_data, "0GAME:the %s wishes to play with you!", my_nick);
  sprintf((char *)ipc_send_name+6,percent_d,UIN);
  tmr_gipc.name_to=ipc_send_name;
  tmr_gipc.name_from=ipc_my_name;
  TPKT *send=malloc(sizeof(IPCssg)+strlen(send_data)+1);
  send->IPCMsg.uin=UIN;
  send->IPCMsg.msg=send_data;
  tmr_gipc.data=send;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SENDMSG,&tmr_gipc);
  game_state=1;
}

void Rebuild_to_defence()
{
  WSHDR *ws=AllocWS(21);
  utf8_2ws(ws,enemy_nick,20);
  EDIT_SetTextToEditControl(ggui, 1,ws);
  utf8_2ws(ws,enemy_weapon,20);
  EDIT_SetTextToEditControl(ggui, 2,ws);
  utf8_2ws(ws,enemy_armor,20);
  EDIT_SetTextToEditControl(ggui, 3,ws);
  utf8_2ws(ws,enemy_lvl,20);
  EDIT_SetTextToEditControl(ggui, 4,ws);
  utf8_2ws(ws,hp_info_enemy,20);
  EDIT_SetTextToEditControl(ggui, 5,ws);
  utf8_2ws(ws,enemy_def,20);
  EDIT_SetTextToEditControl(ggui, 6,ws);
  mfree(ws);
  DirectRedrawGUI();
  if(show_log==2)
  {
  ShowMSG(1,(int)"Attack now!");
  show_log=1;
  }
  else
  if(show_log==1)
  {
  ShowMSG(1,(int)"Attack now!");
  ShowMSG(1,(int)hit_info);
  }
  else
  {
    ShowMSG(1,(int)"2Shots in head! you're dead!");
    player_enemy_lvl++;
    sprintf(enemy_lvl, "LVL: %d", player_enemy_lvl);
    enemy_def_hp=enemy_def_hp+2;
    my_def_hp=my_def_hp+5;
    hp_my=my_def_hp;
    hp_enemy=enemy_def_hp;
    hp2_my=my_def_hp;
    hp2_enemy=enemy_def_hp;
    sprintf(hp_info_my, "HP: %d of %d \n", my_def_hp, my_def_hp);
    sprintf(hp_info_enemy, "HP: %d of %d \n", enemy_def_hp, enemy_def_hp);
    show_log=2;
    GBS_StartTimerProc(&mytmr, 216*2, Rebuild_to_defence);
  } 
}

void Rebuild_to_attack()
{
  WSHDR *ws=AllocWS(21);
  utf8_2ws(ws,my_nick,20);
  EDIT_SetTextToEditControl(ggui, 1,ws);
  utf8_2ws(ws,my_weapon,20);
  EDIT_SetTextToEditControl(ggui, 2,ws);
  utf8_2ws(ws,my_armor,20);
  EDIT_SetTextToEditControl(ggui, 3,ws);
  utf8_2ws(ws,my_lvl,20);
  EDIT_SetTextToEditControl(ggui, 4,ws);
  utf8_2ws(ws,hp_info_my,20);
  EDIT_SetTextToEditControl(ggui, 5,ws);
  utf8_2ws(ws,my_def,20);
  EDIT_SetTextToEditControl(ggui, 6,ws);
  mfree(ws);
  DirectRedrawGUI();
  if(show_log==2)
  {
  ShowMSG(1,(int)"Defend now!");
  show_log=1;
  }
  else
  if(show_log==1)
  {
  ShowMSG(1,(int)"Defend now!");
  ShowMSG(1,(int)hit_info);
  }
  else
  {
    ShowMSG(1,(int)"2Shots in head! enemy dead!");
    player_lvl++;
    sprintf(my_lvl, "LVL: %d", player_lvl);
    enemy_def_hp=enemy_def_hp+5;
    my_def_hp=my_def_hp+2;
    hp_my=my_def_hp;
    hp_enemy=enemy_def_hp;
    hp2_my=my_def_hp;
    hp2_enemy=enemy_def_hp;
    sprintf(hp_info_my, "HP: %d of %d \n", my_def_hp, my_def_hp);
    sprintf(hp_info_enemy, "HP: %d of %d \n", enemy_def_hp, enemy_def_hp);
    show_log=2;
    GBS_StartTimerProc(&mytmr, 216*2, Rebuild_to_attack);
  } 
}

void Shoot()
{
  EDITCONTROL ec;
  ExtractEditControl(ggui,  7, &ec);     
  char *shoot=ws2ascii(ec.pWS);
  if((!strcmp(shoot, left))||(!strcmp(shoot, right))||(!strcmp(shoot, center)))
  {
  defend=Random();
  if(defend<85) strcpy(defend2, left);
  else
  if(defend>170) strcpy(defend2, right);
  else
  strcpy(defend2, center);
  if(!strcmp(shoot, defend2))
  {
    defend=Random();
    if(defend<85) power_hit=1;
    else
    if(defend>170) power_hit=3;
    else
    power_hit=2;
    hp_my=hp_my-power_hit;
  }
  mfree(shoot);
  if(hp2_my==hp_my)
    strcpy(hit_info, Missed);
  else
  {
    sprintf(hit_info, "%s! -%dhp", Hit,power_hit);
//    strcpy(hit_info, Hit);
    hp2_my=hp_my;
  }
  set_shoot=1;
  if(hp_my>0)
  {
    sprintf(hp_info_my, "HP: %d of %d \n", hp_my, my_def_hp);
  }
  else
  {
//    sprintf(hp_info_my, "HP: %d of %d \n", my_def_hp, my_def_hp);
    show_log=0;
  }
  Rebuild_to_defence();
  }
  else
    ShowMSG(1,(int)"Wrong Command!");
}

void Defend()
{
  EDITCONTROL ec;
  ExtractEditControl(ggui,  7, &ec);     
  char *shoot=ws2ascii(ec.pWS);
  if((!strcmp(shoot, left))||(!strcmp(shoot, right))||(!strcmp(shoot, center)))
  {
  defend=Random();
  if(defend<85) strcpy(defend2, left);
  else
  if(defend<170) strcpy(defend2, right);
  else
  strcpy(defend2, center);
  if(!strcmp(shoot, defend2))
  {
    defend=Random();
    if(defend<85) power_hit=1;
    else
    if(defend>170) power_hit=3;
    else
    power_hit=2;
    hp_enemy=hp_enemy-power_hit;
  }
  mfree(shoot);
//  sprintf(hp_info_enemy, "HP: %d/20 \n", hp_enemy);
  if(hp2_enemy==hp_enemy)
    strcpy(hit_info, Missed);
  else
  {
    sprintf(hit_info, "%s! -%dhp", Hit,power_hit);
    hp2_enemy=hp_enemy;
  }
  set_shoot=0;
  if(hp_enemy>0)
  {
    sprintf(hp_info_enemy, "HP: %d of %d \n", hp_enemy, enemy_def_hp);
  }
  else
  {
//    sprintf(hp_info_enemy, "HP: %d of %d \n", enemy_def_hp, enemy_def_hp);
    show_log=0;
  }
  Rebuild_to_attack();
  }
  else
    ShowMSG(1,(int)"Wrong Command!");
}

void OnRedraw(MAIN_GUI *data)
{       
  
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
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
#ifndef NEWSGOLD
    case RED_BUTTON:       
      
      return(1);
#endif
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

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
  (void *)method7,	
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{
  Randomize();
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);    
  void create_ed();
  SUBPROC((void *)create_ed);
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

void ProcessData(char *DATA)
{
  int i=(int)DATA[0];
  /*
  char *test=malloc(16);
  sprintf(test, "%d", i);
  ShowMSG(1,(int)test);
  mfree(test);
  */
  if(i==48)
  {
    if(game_state==1)
    {
      WSHDR *ws=AllocWS(21);
      utf8_2ws(ws,"incoming Gamer",20);
      EDIT_SetTextToEditControl(ggui, 1,ws);
      ShowMSG(1,(int)"Incoming Gamer");
      FreeWS(ws);
    }
  }
}

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

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
	{
	  switch (msg->submess)
	  {
	  case IPC_GAME_DATA:
            {
            int l=strlen(ipc->data);
            char *GAME_DATA=malloc(l+1);
            memcpy(GAME_DATA,ipc->data,l);
            GAME_DATA[l]='\0';
            ProcessData(GAME_DATA);
            mfree(GAME_DATA);
            }
	    break;
          }
        }
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Combats elf - (c)Evilfox");
}

void put_hp()
{
  WSHDR *ws=AllocWS(50);
  utf8_2ws(ws,"HP: 5 of 5",20);
  EDIT_SetTextToEditControl(ggui, 5,ws);
  FreeWS(ws);
  DirectRedrawGUI();
}

int main()
{  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  sprintf(hp_info_enemy, "HP: 5 / 5 \n");
  sprintf(enemy_lvl, "LVL: 1");
  sprintf(my_lvl, "LVL: 1");
  show_log=1;
  return 0;
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

void edchat_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC skk={0x0018, 0x0000,(int)"Menu"};
  if (cmd==7)
    SetSoftKey(data,&skk,SET_SOFT_KEY_N); 
}

int itemnum, wd_id;

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  
  void create_ed(void);
  
  switch (msg->gbsmsg->submess)
  {
    
#ifndef NEWSGOLD
  case RED_BUTTON:
    
    CloseCSM(MAINCSM_ID);
    break;
#endif  
    
  case ENTER_BUTTON:
/*    if(!wait)
    {
    if(set_shoot==0)
    Shoot();
    else
      Defend();
    }*/
    if(game_state==0)
      SendGameEngade();
    break;
  case LEFT_BUTTON:
    break;
  case RIGHT_BUTTON:
    break;
  case UP_BUTTON:
    break;
  }
  if (msg->keys==0x18)
  {
    void MMenu();
    MMenu();
  }
  if (msg->keys==0x1)
  {
    CloseCSM(MAINCSM_ID);
  }
  return(0); 
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"Combats elf",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
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


void create_ed(void)
{
  
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(50);
  
  utf8_2ws(ws, "press center joy to start",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma); 
/*    
  utf8_2ws(ws, "Weapon: pistol(1-3)",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);

  utf8_2ws(ws, "Armor: none",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "LVL: 1",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);
  */
  ConstructEditControl(&ec,1,0,0,20);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,1,0,0,20);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,1,0,0,20);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,1,0,0,16);
  AddEditControlToEditQend(eq,&ec,ma); 
/*  
  utf8_2ws(ws, "Defend direction:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma); 
  */
  ConstructEditControl(&ec,1,0,0,20);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,3,0x40,0,10);
  AddEditControlToEditQend(eq,&ec,ma);    
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
}

// menu


void Shoot1(GUI *data)
{
  Shoot();
}

void About(GUI *data)
{
  ShowMSG(1,(int)"Combats_elf 0.1alfa (c)evilfox");
}

void exit(GUI *data)
{
  CloseCSM(MAINCSM_ID);
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,0,0,icon,(int)"Menu",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[2]=
{
  {NULL,(int)"About",    LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Exit",     LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[2]={
  About,
  exit
};

const SOFTKEY_DESC menu_sk1[]=
{
  {0x0018,0x0000,(int)"OK"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt1=
{
  (SOFTKEY_DESC *)menu_sk1,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt1,
  0,
  NULL,
  menuitems,
  menuprocs,
  2
};

void MMenu(void)
{
  patch_header(&menuhdr);
  CreateMenu(0,0,&tmenu,&menuhdr,0,2,0,0);
}
