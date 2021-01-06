#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "define.h"
#include "gui.h"
#include "dict.h"
#include "rect_patcher.h"
#include <stdbool.h>

//================= extern vars and funcs from dict.c ========================/

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;

//config
extern const unsigned int cfg_floatwin;
extern const unsigned int cfg_fw_delay;


char **index = NULL;
bool m_f_err = false;           //memory or file error;
#define TMR_SECOND 216
GBSTMR  timer;
bool wanna_quit = false;
bool fw_showing = false;
unsigned long global_time = 0;
unsigned long last_key_time = 0;
const int minus11 = -11;
unsigned int floatwin;
int screenh;
int screenw;


void Killer(void)
{
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	CloseDict();
	UnloadDictIndex();
  GBS_DelTimer(&timer);
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_oncreate(CSM_RAM *data)
{
  screenh=ScreenH();
  screenw=ScreenW();
	MAIN_CSM *csm=(MAIN_CSM*)data;  
	csm->gui_id=create_gui();
  floatwin = cfg_floatwin;
  LoadDictIndex();
  OpenDict();
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

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

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"ECDict config updated!");
      InitConfig();
    }
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
  	if ((int)msg->data0==csm->gui_id)
  	{
  		csm->csm.state=-3;
  	}
  }
  if( wanna_quit )
  {
    csm->csm.state=-3;
  }
  return(1);
}

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
	unsigned short csmname1[] = {0x82F1, 0x6C49, 0x8BCD, 0x5178, 0}; //"英汉词典"
	copy_unicode_2ws((WSHDR *)(&MAINCSM.maincsm_name), csmname1);
}

void TimeCounterProc(void)
{
    global_time ++;
    
    if( !fw_showing && (global_time-last_key_time)>=cfg_fw_delay )
    {
        GBS_SendMessage(MMI_CEPID, KEY_DOWN, 99);           //暂时先用键码99做刷新。。
    }
    GBS_StartTimerProc(&timer, TMR_SECOND/10, TimeCounterProc);
}

int main()
{
	char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  
	LockSched();
	CreateCSM(&MAINCSM.maincsm, dummy, 0);
	UnlockSched(); 
	
	GBS_StartTimerProc(&timer, TMR_SECOND, TimeCounterProc);
	return 0;
}
