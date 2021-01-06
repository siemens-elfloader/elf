#include "Z:\home\kostett\IAR\ARM\INC\swilib.h"
#include "conf_loader.h"
#include "siemens_unicode.h"

GBSTMR timer;

///! Добавить кейхук! - 010311:doneALPHA/WG - 020311:doneSTABLE - 130311:testedGOVNO!!11 - 190311:doneSTABLE
///! Дописать конфиг! - 010311:doneALPHA/WB - 010311:doneFIX/WG - 020311:doneSTABLE - 200311:doneADDED
///! Переделка значений ТА в интервал! - Нахххуй надо..
///! Впилить оралку! - 020111:doneALPHA - 200311:doneREMAKED
///! Прикручен не вечно работающий таймер, а только при активностии - 130311:doneSTABLE
///! Консольный дебаг - 130311:doneSTABLE
///! Несколько LAC/CI - 

static void UpdateCSMname();
void timerproc();
unsigned int KEYON_TYPE,KEYOFF_TYPE;
int enable;
extern const unsigned int BCFG_KEYON_TYPE,BCFG_ON_BTN,BCFG_KEYOFF_TYPE,BCFG_OFF_BTN;
extern const int BCFG_ON_MSG_ENA,BCFG_OFF_MSG_ENA,BCFG_DEBUG_ENA;
WSHDR *ws14; 
extern const char BCFG_TSKNAME_NAME[64];

IPC_REQ gipc;
char text[128];

void print()
{     
  gipc.name_to= "Console";
  gipc.name_from=text;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
};

void utf82win(char*d,const char *s)
{
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 0xD0)
    {
                     if(lb == 0x81){*d = 0xA8;}//\u0401
		else if(lb == 0x86){*d = 0xB2;}//\u0406
		else if(lb == 0x87){*d = 0xAF;}//\u0407
		else if(lb == 0x84){*d = 0xAA;}//\u0404
	  else {*d = lb + 48;}
    } else
    if (ub == 0xD1)
    {
                     if(lb == 0x91){*d = 0xB8;}//\u0451
		else if(lb == 0x96){*d = 0xB3;}//\u0456
		else if(lb == 0x97){*d = 0xBF;}//\u0457
		else if(lb == 0x94){*d = 0xBA;}//\u0454
	        else {*d = lb + 112;}
    } else
    if (ub == 0xD2)
    {
//        if(lb == 0x91){*d = 0xB4;}//\u0491
//        if(lb == 0x90){*d = 0xA5;}//\u0490
        if(lb == 0x91){*d = 0xE3;}//\u0491->\u0433
        if(lb == 0x90){*d = 0xC3;}//\u0490->\u0413
    } else
    {
      *d = ub;
      s--;
    }
      d++;
  }
  *d = 0;
}


void ConfigParse(void)
{
  switch (BCFG_KEYON_TYPE) 
  {
    case 0:
      KEYON_TYPE=0x193;
      break;
    case 1:
      KEYON_TYPE=0x195;
      break;
  };
  switch (BCFG_KEYOFF_TYPE)
  {
    case 0:
      KEYOFF_TYPE=KEY_DOWN;
      break;
    case 1:
      KEYOFF_TYPE=LONG_PRESS;
      break;
  };
};

//--------------[Тру кейхук, выдран из ElfStart (с) kluchnik, проиндусен мной]-------------------
//Тру потому что не следит за нажатиями, а перехватывает у телефона. В гуястых эльфах юзать не рекомендую, лучше использовать метод OnKey.
//Ибо тогда при открытом гуе остальные эльфы навроде этого перехватывать навряд ли смогут...
int mode;
// 0 - no press
// 1 - long press REDBUT
int mode_red;
// 0 - no press
// 1 - long press ENTER_BUTTON
// 2 - disable KEY_UP process
int mode_enter;
int flagen;

int my_keyhook(int key, int type) 
{
  if (key==BCFG_ON_BTN)
    {
      switch(type)
      {
      case KEY_DOWN:
          if (KEYON_TYPE==KEY_DOWN)
          {
            flagen=1;
            return(2);
          }
          else
          {
            if (mode_enter==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,BCFG_ON_BTN);
              return (0);
            }
            mode_enter=0;
            return (2);
          }        
        case KEY_UP:
          if (KEYON_TYPE)
          {
            if (flagen)
            {
              extern const unsigned int BCFG_REFRESHTIME;
              GBS_StartTimerProc(&timer,BCFG_REFRESHTIME,timerproc);
              enable=1;
              if (BCFG_DEBUG_ENA)
              {
                sprintf(text,"keyhook 1 done: ON");
                print();
              };
              if (BCFG_ON_MSG_ENA) 
              {
                char* m = malloc(128+5+strlen("слежение ON"));
                sprintf(m,"%s:\nслежение ON", BCFG_TSKNAME_NAME);
                char *ansi_m = m;
                utf82win(ansi_m, ansi_m);
                ShowMSG(1,(int)ansi_m);
              };
              UpdateCSMname();
              flagen=0;
            };
            if (mode_enter==0)
            {
              mode_enter=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,BCFG_ON_BTN);
              return (2);
            }
            if (mode_enter==2)
            {
              mode_enter=0;
              return (0);
            }
            mode_enter=0;
            return (2);
          }          
        case LONG_PRESS:
          if (KEYON_TYPE==LONG_PRESS)
          {
            mode_enter=1;
            flagen=1;
          }
         break;
      }
    }

  if (key==BCFG_OFF_BTN)
    {
      switch(type)
      {
        case KEY_DOWN:
          if (KEYOFF_TYPE==KEY_DOWN)
          {
            flagen=1;
            return(2);
          }
          else
          {
            if (mode_enter==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,BCFG_OFF_BTN);
              return (0);
            }
            mode_enter=0;
            return (2);
          } 
          
        case KEY_UP:
          if (KEYOFF_TYPE)
          {
            if (flagen)
            {
              GBS_StopTimer(&timer);
              enable=0;
              if (BCFG_DEBUG_ENA)
              {
                sprintf(text,"keyhook 2 done: OFF");
                print();
              };
              if (BCFG_OFF_MSG_ENA) 
              {
                char* m = malloc(128+5+strlen("слежение OFF"));
                sprintf(m,"%s:\nслежение OFF", BCFG_TSKNAME_NAME);
                char *ansi_m = m;
                utf82win(ansi_m, ansi_m);
                ShowMSG(1,(int)ansi_m);
              };
              UpdateCSMname();
              flagen=0;
            };
            if (mode_enter==0)
            {
              mode_enter=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,BCFG_OFF_BTN);
              return (2);
            }
            if (mode_enter==2)
            {
              mode_enter=0;
              return (0);
            }
            mode_enter=0;
            return (2);
          }
          
        case LONG_PRESS:
          if (KEYOFF_TYPE==LONG_PRESS)
          {
            flagen=1;
          }
         break;
      }
    }
  return(0);
}

void DoOnFound()
{
  extern const int BCFG_FOUND_MSG_ENA;
  if (BCFG_FOUND_MSG_ENA) 
  {
    char* m = malloc(128+5+strlen("БC найдена!"));
    sprintf(m,"%s:\nБC найдена!", BCFG_TSKNAME_NAME);
    char *ansi_m = m;
    utf82win(ansi_m, ansi_m);
    ShowMSG(1,(int)ansi_m);
  };
  extern const int BCFG_TYPE;
  if (BCFG_TYPE)
  {
    switch(BCFG_TYPE)
    {
    case 1:
      ws14=AllocWS(256);
      char start[128];
      extern const char BCFG_START_FILE[128];
      strcpy(start,BCFG_START_FILE);
      str_2ws(ws14,start,strlen(start)+1);
      ExecuteFile(ws14,0,0);
      FreeWS(ws14);
#ifndef NEWSGOLD
    case 2:
      AlarmClockRing();
#endif
    };
  };
};

void timerproc(void)
{
      
  RAMNET *rn=RamNet();
  unsigned int cur_lac=rn->lac;
  unsigned int cur_ci=rn->ci;

  extern const int BCFG_ENA_1ST_NET, BCFG_ENA_2ND_NET, BCFG_ENA_3RD_NET, BCFG_ENA_4TH_NET, BCFG_ENA_5TH_NET;
  
  if (BCFG_ENA_1ST_NET)
  {
    extern const unsigned int BCFG_LAC,BCFG_CI;
    
    if (BCFG_DEBUG_ENA)
    {
      sprintf(text,"CUR %d:%d\nBCFG1 %d:%d",cur_lac,cur_ci,BCFG_LAC,BCFG_CI);
      print();
    };
    
    if ((cur_lac==BCFG_LAC) && (cur_ci==BCFG_CI))
    {
      
      if (BCFG_DEBUG_ENA)
      {
        sprintf(text,"BS #1 found!");
        print();
      };
      
      DoOnFound();
    };
  };
  if (BCFG_ENA_2ND_NET)
  {
    extern const unsigned int BCFG_LAC2,BCFG_CI2;
    
    if (BCFG_DEBUG_ENA)
    {
      sprintf(text,"CUR %d:%d\nBCFG2 %d:%d",cur_lac,cur_ci,BCFG_LAC2,BCFG_CI2);
      print();
    };
    
    if ((cur_lac==BCFG_LAC2) && (cur_ci==BCFG_CI2))
    {
      
      if (BCFG_DEBUG_ENA)
      {
        sprintf(text,"BS #2 found!");
        print();
      };
      
      DoOnFound();
    };
  };
  if (BCFG_ENA_3RD_NET)
  {
    extern const unsigned int BCFG_LAC3,BCFG_CI3;
    
    if (BCFG_DEBUG_ENA)
    {
      sprintf(text,"CUR %d:%d\nBCFG3 %d:%d",cur_lac,cur_ci,BCFG_LAC3,BCFG_CI3);
      print();
    };
    
    if ((cur_lac==BCFG_LAC3) && (cur_ci==BCFG_CI3))
    {
      
      if (BCFG_DEBUG_ENA)
      {
        sprintf(text,"BS #3 found!");
        print();
      };
      
      DoOnFound();
    };
  };
  if (BCFG_ENA_4TH_NET)
  {
    extern const unsigned int BCFG_LAC4,BCFG_CI4;
    
    if (BCFG_DEBUG_ENA)
    {
      sprintf(text,"CUR %d:%d\nBCFG4 %d:%d",cur_lac,cur_ci,BCFG_LAC4,BCFG_CI4);
      print();
    };
    
    if ((cur_lac==BCFG_LAC4) && (cur_ci==BCFG_CI4))
    {
      
      if (BCFG_DEBUG_ENA)
      {
        sprintf(text,"BS #4 found!");
        print();
      };
      
      DoOnFound();
    };
  };
  if (BCFG_ENA_5TH_NET)
  {
    extern const unsigned int BCFG_LAC5,BCFG_CI5;
    
    if (BCFG_DEBUG_ENA)
    {
      sprintf(text,"CUR %d:%d\nBCFG5 %d:%d",cur_lac,cur_ci,BCFG_LAC5,BCFG_CI5);
      print();
    };
    
    if ((cur_lac==BCFG_LAC5) && (cur_ci==BCFG_CI5))
    {
      
      if (BCFG_DEBUG_ENA)
      {
        sprintf(text,"BS #5 found!");
        print();
      };
      
      DoOnFound();
    };
  };
  
  UpdateCSMname();
  extern const unsigned int BCFG_REFRESHTIME;
  GBS_StartTimerProc(&timer,BCFG_REFRESHTIME*216,timerproc);
};

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      char* m = malloc(128+5+strlen("конфиг\nобновлен!"));
      sprintf(m,"%s:\nконфиг\nобновлен!", BCFG_TSKNAME_NAME);
      char *ansi_m = m;
      utf82win(ansi_m, ansi_m);
      ShowMSG(1,(int)ansi_m);
      InitConfig();
      ConfigParse();
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
  AddKeybMsgHook((void *)my_keyhook);
  timerproc();
  GBS_StopTimer(&timer);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  RemoveKeybMsgHook((void *)my_keyhook);
  GBS_DelTimer(&timer);
  SUBPROC((void *)Killer);
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
  extern const unsigned char BCFG_TSKNAME_COLOR_ON[4],BCFG_TSKNAME_COLOR_OFF[4];
  if (enable)
  {
    int r = BCFG_TSKNAME_COLOR_ON[0];
    int g = BCFG_TSKNAME_COLOR_ON[1];
    int b = BCFG_TSKNAME_COLOR_ON[2];
    int a = BCFG_TSKNAME_COLOR_ON[3];
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%c%c%c%t",UTF16_INK_RGBA,(r<<8 | g),(b<<8) | a,BCFG_TSKNAME_NAME);
  };
  if (!enable)
  {
    int r = BCFG_TSKNAME_COLOR_OFF[0];
    int g = BCFG_TSKNAME_COLOR_OFF[1];
    int b = BCFG_TSKNAME_COLOR_OFF[2];
    int a = BCFG_TSKNAME_COLOR_OFF[3];
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%c%c%c%t",UTF16_INK_RGBA,(r<<8 | g),(b<<8) | a,BCFG_TSKNAME_NAME); //(r) feanor
  };
}

int main(void)
{
  InitConfig();
  ConfigParse();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int BCFG_HELLOMSG;
  if (BCFG_HELLOMSG) 
  {
    char* m = malloc(128+5+strlen("\nзапущен!\n(c) kostett"));
    sprintf(m,"%s:\nзапущен!\n(c) kostett", BCFG_TSKNAME_NAME);
    char *ansi_m = m;
    utf82win(ansi_m, ansi_m);
    ShowMSG(1,(int)ansi_m);
  }
  return 0;
}
