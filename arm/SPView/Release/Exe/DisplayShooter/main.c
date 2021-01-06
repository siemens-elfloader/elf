#include "..\inc\swilib.h"
#include "conf_loader.h"

const int minus11=-11;

extern const char SAVE_PATH[];
extern const int SHOT_BTN;
extern const int LONG_P;
extern const int ENA_LOCK;
extern const int ENA_MSG;
extern const char SHOT_MSG[];

char bmphdr[]= {0x42,0x4D,0x42,0x58,0x02,0x00,0x00,0x00,
                0x00,0x00,0x42,0x00,0x00,0x00,0x28,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,
                0x00,0x00,0x00,0x58,0x02,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,
                0x00,0x00,0xE0,0x07,0x00,0x00,0x1F,0x00,
                0x00,0x00};

int cs=1; //canshot
int mode;
//0 - норма
//1 - пора нажимать коротко
//2 - следующий 0

int hook(int submsg, int msg)
{
  int scrH=ScreenH();
  int scrW=ScreenW();

  if((IsUnlocked()|ENA_LOCK) && submsg==SHOT_BTN)
  {
    if(mode==1)
    {
      if(msg==KEY_UP)
      {
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,SHOT_BTN);
        return(0);
      }
      if(msg==KEY_DOWN)
      {
        mode=0;
        GBS_SendMessage(MMI_CEPID,KEY_UP,SHOT_BTN);
        return(0);
      }
    }

    if(msg==KEY_UP)
    {
      cs=1;
      if(mode==2)
      {
        mode=0;
        return(2);
      }
    }
    else if(msg==(LONG_P?LONG_PRESS:KEY_DOWN) && cs)
    {
      int f;
      unsigned int ul;
      unsigned int len=scrW*scrH*2;
      char *scrbuf=RamScreenBuffer();
      char *buf=malloc(len);
      for(int i=0; i<scrH; i++)
        memcpy(buf+i*scrW*2, scrbuf+len-(i+1)*scrW*2, scrW*2);

      TTime t;
      TDate d;
      GetDateTime(&d,&t);
      char curname[20];
      sprintf(curname, "%02d%02d%02d_%02d%02d%02d.bmp",
              d.year, d.month, d.day, t.hour, t.min, t.sec/*t.param*/);
  
      char fname[145];
      strcpy(fname, SAVE_PATH);
      strcat(fname, curname+2);
  
      if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
      {
        if(fwrite(f,bmphdr,66,&ul)!=66)goto del;
        if(fwrite(f,buf,len,&ul)!=len)goto del;
        fclose(f,&ul);
        if(ENA_MSG)
          ShowMSG(1, (int)SHOT_MSG);
        goto end;
      }

    del:
      ShowMSG(1, (int)"Error!");
      fclose(f,&ul);
      unlink(fname,&ul);

    end:
      mfree(buf);

      if((msg==LONG_PRESS) && LONG_P)
        cs=0;
    }

    if(!IsUnlocked())
      return(2);

    if(LONG_P)
    {
      if(msg==LONG_PRESS)
      {
        mode=2;
        return(2);
      }
      if(msg==KEY_DOWN)
      {
        mode=1;
        return(2);
      }
    }
    else
      return(2);
  }
  return(0);
}

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
      ShowMSG(1,(int)"DisplayShooter config updated!");
      InitConfig();
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
  AddKeybMsgHook((void *)hook);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  RemoveKeybMsgHook((void *)hook);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"DisplayShooter");
}

int main()
{
  int scrW=ScreenW();
  int scrH=ScreenH();
  bmphdr[18]=(scrW>> 0)&0xFF;
  bmphdr[19]=(scrW>> 8)&0xFF;
  bmphdr[20]=(scrW>>16)&0xFF;
  bmphdr[21]=(scrW>>24)&0xFF;
  bmphdr[22]=(scrH>> 0)&0xFF;
  bmphdr[23]=(scrH>> 8)&0xFF;
  bmphdr[24]=(scrH>>16)&0xFF;
  bmphdr[25]=(scrH>>24)&0xFF;
  
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return 0;
}
