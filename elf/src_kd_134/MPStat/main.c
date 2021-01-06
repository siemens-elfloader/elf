#include "D:\ARM_ALL\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

const int minus11=-11;

extern const unsigned int text_x;
extern const unsigned int text_y;
extern const char text_mp_off[128];
extern const char text_mp_on[128];
extern const unsigned int img_x;
extern const unsigned int img_y;
extern const char img_mp_off[128];
extern const char img_mp_on[128];
extern const char fontpatch[128];
extern const int fullfont;
extern const int align;
extern const unsigned int space;
void *canvasdata;
int font=1;

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

void InfoMP()
{
  //Метод с функцией
  canvasdata=BuildCanvas();
  extern const int ena_img;
  extern const int ena_text;
  extern const int type_txt;
  extern const unsigned int font_txt;
  extern const char color[4];
  extern const char frame_color[4];
  char xz[32];
  WSHDR *ws_txt=AllocWS(256);
  //При вкл MP
  if(GetPlayStatus()==2)
  {
    //Картинка
    if(ena_img)
    {
      DrawImg(img_x,img_y,(int)img_mp_on);
    }
    //Текст
    if(ena_text)
    {
      switch(type_txt)
      {
      case 0:
        wsprintf(ws_txt,"%s",text_mp_on);
        DrawString(ws_txt,text_x,text_y,ScreenW(),ScreenH(),font_txt,TEXT_OUTLINE,color,frame_color);
        break;
      case 1:
        sprintf(xz,"%s",text_mp_on);
        PrintField(text_x,text_y,xz,align,font,space);
        break;
      }
    }
  }
  //При выкл MP
  else
  {
    //Картинка
    if(ena_img)
    {
      DrawImg(img_x,img_y,(int)img_mp_off);
    }
    //Текст
    if(ena_text)
    {
      switch(type_txt)
      {
      case 0:
        wsprintf(ws_txt,"%s",text_mp_off);
        DrawString(ws_txt,text_x,text_y,ScreenW(),ScreenH(),font_txt,TEXT_OUTLINE,color,frame_color);
        break;
      case 1:
        sprintf(xz,"%s",text_mp_off);
        PrintField(text_x,text_y,xz,align,font,space);
        break;
      }
    }
  }
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      extern const int ena_req;
      if(ena_req) ShowMSG(1,(int)"Конфиг MPStat обновлен!");
      FontPathFree();
      InitConfig();
      FontPathInit(font,(char *)fontpatch, fullfont);
    }
  }
  extern const int show_in;
  unsigned int show;
  switch (show_in)
  {
  case 0:
    show=!IsUnlocked();
    break;
  case 1:
    show=IsUnlocked();
    break;
  default:
    show=1;
    break;
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)&& show) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if(igui) //И он существует
    {
      InfoMP();
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  FontPathFree();
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MPStat - (c) KIBER-DEMON");
}

int main()
{
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
  FontPathInit(font,(char *)fontpatch,fullfont);
  extern const int ena_msg;
  if(ena_msg) ShowMSG(1,(int)"MPStat установлен!");
  return 0;
}
