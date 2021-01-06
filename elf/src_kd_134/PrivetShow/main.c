#include "D:\ARM_ALL\inc\swilib.h"
#include "D:\ARM_ALL\inc\cfg_items.h"
#include "conf_loader.h"

extern void kill_data(void *p, void (*func_p)(void *));
static unsigned short maincsm_name_body[140];
const int minus11=-11;
extern const unsigned int icon_x;
extern const unsigned int icon_y;
extern const char icon_patch[128];
extern const char text_patch[128];
extern const char sound_patch[128];
extern const unsigned int def_vol;
unsigned int volume=6;
extern const int ena_pic;
extern const int ena_msg;
extern const int ena_snd;
extern const int ena_hel;
//#pragma inline=forced
extern const unsigned int REFRESH;

extern const char path[64];
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
extern const unsigned int PNG;
CSM_RAM *under_idle;
int str1;

int PLAY_ID=0;
unsigned int NEXT_PLAY_FUNK=0;

void Play(const char *fpath, const char *fname)
{
  WSHDR* sndPath=AllocWS(128);
  WSHDR* sndFName=AllocWS(128);
  wsprintf(sndPath,fpath);
  wsprintf(sndFName, fname);
  PLAYFILE_OPT _sfo1;
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=1;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=volume;
  #ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PLAY_ID=PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  #ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #endif
  #endif 
  FreeWS(sndPath);
  FreeWS(sndFName);
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
  GBSTMR mytmr;
  void start()
  {
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *canvasdata=BuildCanvas();
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
  extern const char *successed_config_filename;
  if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
  {
  ShowMSG(1,(int)"PrivetShow config updated!");
  InitConfig();
  }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)/*&&IsUnlocked()*/)
  {
  GUI *igui=GetTopGUI();
  if (igui)
  {
  void *canvasdata=BuildCanvas();
  }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  GBS_StopTimer(&mytmr);
  Play(sound_patch,"PrivetShow.wav");
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"PrivetShow - (c) KIBER-DEMON");
}


int main()
{
  InitConfig();
  UpdateCSMname();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  if (ena_pic)
  DrawImg(icon_x,icon_y,(int)icon_patch);
  if (ena_msg)
  ShowMSG(1,(int)text_patch);
  if (ena_snd)
  Play(sound_patch,"PrivetShow.wav");
  volume=def_vol;
  unsigned char*mPtr=(unsigned char*)0xA0000000;
  mPtr+=0x210;
  char model[5];
  char n=0;
  for(;n<5;n++)
  {
  if (*(mPtr+n)==0x00)
  {  
  *(model+n)='\0';
  break;
  }
  else 
  *(model+n)=*(mPtr+n);
  }
  char *mobile=malloc(256);
  sprintf(mobile,"Загрузка %s",model);
  ShowMSG(1,(int)mobile);
  if (ena_hel)
  ShowMSG(1,(int)"PrivetShow - (c) KIBER-DEMON");
  return 0;
}

