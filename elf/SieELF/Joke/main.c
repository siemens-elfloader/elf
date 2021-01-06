#include "..\inc\swilib.h"
#include "conf_loader.h"

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

extern const char realpass[32];
extern const char warning_str[128];
extern const char top_warning_str[128];
extern const char gui_bg_color[4];
extern const char gui_warning_color[4];
extern const unsigned int gui_warning_font;
extern const char password_color[4];
extern const unsigned int password_font;
extern const char sk_color[4];
extern const RECT top_str_pos;
extern const char top_bg_color[4];
extern const char top_str_color[4];
extern const unsigned int top_str_font;
extern const unsigned int hot_key;

unsigned int MAINCSM_GUI_ID=0;
unsigned int MAINGUI_ID=0;
int is_gui_started=0;
char password[32]="\0";
int pwd=0;
int is_wrong_pass=0;
//char utf8_str[32]="冰哥的手机你玩不懂";
WSHDR *ws_sh;
int screenw;
int screenh;

extern void kill_data(void *p, void (*func_p)(void *));


#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
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

void soft_key(void)
{
  char utf8_clear[]="确定";
	char utf8_exit[]="删除";
	WSHDR *wsl = AllocWS(16);
  WSHDR *wsr = AllocWS(16);
  utf8_2ws(wsr,utf8_exit,strlen(utf8_exit));
  utf8_2ws(wsl,utf8_clear,strlen(utf8_clear));
  DrawString(wsr,screenw-get_string_width(wsr,FONT_MEDIUM)-4,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,FONT_MEDIUM,32,sk_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsl,2,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,FONT_MEDIUM,32,sk_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsr);
  FreeWS(wsl);
}

void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DrawRectangle(0,0,screenw,screenh,0,gui_bg_color,gui_bg_color);
  WSHDR *ws = AllocWS(128);
  char show_pass[32]="\0";
  int i;
  soft_key();
  for(i=0;i<pwd;i++)
  {
    show_pass[i]='*';
    show_pass[i+1]='\0';
  }
  //char utf8_s[]="赶紧输入密码，手机要爆炸了！";
  utf8_2ws(ws,warning_str,strlen(warning_str));
  DrawString(ws,0,0,screenw,screenh,gui_warning_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_warning_color,GetPaletteAdrByColorIndex(23)); 
  wsprintf(ws, "Password:\n%s",show_pass);
  DrawString(ws,0,screenh/2,screenw,screenh,password_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,password_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  int i=msg->gbsmsg->submess;
  SetIllumination(0, 1, 10, 0);
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if ((i>='0')&&(i<='9')&&pwd<=31)
    {
      password[pwd]=i;
      pwd++;
      if(pwd!=31)
        password[pwd]=0;
    }
    if(i==RIGHT_SOFT)
    {
      if(pwd)
      {
        pwd--;
        password[pwd]=0;
      }
    }
    if(i==LEFT_SOFT)
    {
      if(strlen(password)==strlen(realpass))
      {
        if(strncmp(password,realpass,strlen(password)))
        {
          MsgBoxError(1,(int)"Wrong Password!");
          is_wrong_pass=1;
        }
        is_wrong_pass=0;
      }
      else
      {
        MsgBoxError(1,(int)"Wrong Password!");
        is_wrong_pass=1;
      }
      pwd=0;
      password[0]='\0';
      is_gui_started=0;
      KbdUnlock();
      return(1);
    }
  }
  return(0);
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
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

void maincsm_onclose_GUI(CSM_RAM *csm)
{
}

int maincsm_onmessage_GUI(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM *)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const RECT Canvas={0,0,0,0};
void maincsm_oncreate_GUI(CSM_RAM *data)
{
  //if(!is_gui_started)
  //{
  MAIN_CSM *csm=(MAIN_CSM *)data;
    MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
    zeromem(main_gui,sizeof(MAIN_GUI));	
    patch_rect((RECT*)&Canvas,0,0,screenw,screenh);
    main_gui->gui.canvas=(void *)(&Canvas);
    main_gui->gui.flag30=2;
    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
  //  MAINGUI_ID=CreateGUI(main_gui);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  //}
}

const int minus11=-11;


const CSM_DESC maincsm=
{
  maincsm_onmessage_GUI,
  maincsm_oncreate_GUI,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose_GUI,
  sizeof(MAIN_CSM),
  1,
  &minus11
};

void StarGUI_CSM(void)
{
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_GUI_ID=CreateCSM(&maincsm,dummy,2);
  UnlockSched();
}

int hot_key_mode=0;

int my_keyhook(int submsg, int msg)
{
  if((is_wrong_pass)&&(!is_gui_started))
  {
    if(submsg==hot_key)
    {
      switch(msg)
      {
          case KEY_DOWN:
            if(hot_key_mode==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,hot_key);
              return KEYHOOK_NEXT;
            }
            hot_key_mode=0;
            return KEYHOOK_BREAK;
          case KEY_UP:
            if(hot_key_mode==0)
            {
              hot_key_mode=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,hot_key);
              return KEYHOOK_BREAK;
            }
            if (hot_key_mode==2)
            {
              hot_key_mode=0;
              return KEYHOOK_NEXT;
            }
            hot_key_mode=0;
            return KEYHOOK_BREAK;
          case LONG_PRESS:
            hot_key_mode=1;
            StarGUI_CSM();
            //is_gui_started=1;
            break;
      }
    }
  }
  return KEYHOOK_NEXT;
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  //#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]) 
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Joke config updated!");
      InitConfig();
    }
  }
  if(!IsUnlocked())
  {
    if(!is_gui_started)
      StarGUI_CSM();
    is_gui_started=1;
  }
  else
  {
    if(is_wrong_pass)
    {
      utf8_2ws(ws_sh,top_warning_str,strlen(top_warning_str));
      DrawRectangle(top_str_pos.x,top_str_pos.y,top_str_pos.x2,top_str_pos.y2,0,top_bg_color,top_bg_color);
      DrawString(ws_sh,top_str_pos.x,top_str_pos.y,top_str_pos.x2,top_str_pos.y2,top_str_font,32,top_str_color,GetPaletteAdrByColorIndex(23));
    }
  }
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void maincsm_onclose(CSM_RAM *csm)
{
  extern void *ELF_BEGIN;
  FreeWS(ws_sh);
  RemoveKeybMsgHook((void *)my_keyhook);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static unsigned short maincsm_name_body[140];
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Joke");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  screenw=ScreenW()-1;
  screenh=ScreenH()-1;
  ws_sh=AllocWS(128);
  LockSched();
  
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();  
  return 0;
}
