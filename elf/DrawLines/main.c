#include "..\inc\swilib.h"
#include "conf_loader.h"

void *canvasdata;

extern const int ENA_HELLO_MSG;
extern const int cfgShowIn;

extern const RECT pos1;
extern const RECT pos2;
extern const RECT pos3;
extern const RECT pos4;
extern const RECT pos5;
extern const RECT pos6;
extern const RECT pos7;
extern const RECT pos8;
extern const RECT pos9;
extern const RECT pos10;

extern const char color1[];
extern const char color2[];
extern const char color3[];
extern const char color4[];
extern const char color5[];
extern const char color6[];
extern const char color7[];
extern const char color8[];
extern const char color9[];
extern const char color10[];

extern const char color_obv1[];
extern const char color_obv2[];
extern const char color_obv3[];
extern const char color_obv4[];
extern const char color_obv5[];
extern const char color_obv6[];
extern const char color_obv7[];
extern const char color_obv8[];
extern const char color_obv9[];
extern const char color_obv10[];

extern const unsigned int x_round1;
extern const unsigned int y_round1;
extern const unsigned int x_round2;
extern const unsigned int y_round2;
extern const unsigned int x_round3;
extern const unsigned int y_round3;
extern const unsigned int x_round4;
extern const unsigned int y_round4;
extern const unsigned int x_round5;
extern const unsigned int y_round5;
extern const unsigned int x_round6;
extern const unsigned int y_round6;
extern const unsigned int x_round7;
extern const unsigned int y_round7;
extern const unsigned int x_round8;
extern const unsigned int y_round8;
extern const unsigned int x_round9;
extern const unsigned int y_round9;
extern const unsigned int x_round10;
extern const unsigned int y_round10;

#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}

MAIN_CSM;

int IDLECSM_ID=-1;
  
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

int checkGui(int id)
{
 int retval = 0; 
 if (IsGuiOnTop(id)) 
 {
    GUI* igui = GetTopGUI();
    if (igui)
    {
#ifdef ELKA
      canvasdata = BuildCanvas();
      retval = 1;
#else
      void *idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
        canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
        retval = 1;
      }
#endif
    }  
 }
 return retval;
}


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  unsigned char fShow;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"DrawLines config updated!");
      InitConfig();
    }
  }
  
    switch (cfgShowIn)
    {
      case 0:
        fShow = !IsUnlocked();
      break;
      case 1:
        fShow = IsUnlocked();
      break;
      default:
        fShow = 1;
      break;
    }
  
 //icsm=FindCSMbyID(CSM_root()->idle_id);
  
  //if (IsGuiOnTop(idlegui_id)&&fShow/*0&&GetTypeUSSD()!=2*/&&!IsScreenSaver()) //Если IdleGui на самом верху
    /*{  
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
#ifdef ELKA

	canvasdata = BuildCanvas();
#else
	void *idata = GetDataOfItemByID(igui, 2);
	if (idata)
	{
	  canvasdata
            = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          */
  if(msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,"IdleUpd")==0 && fShow)
      {
        switch (msg->submess)
        {
        case 0:
          {
            canvasdata = BuildCanvas();
            icsm=FindCSMbyID(CSM_root()->idle_id);
            if (icsm && checkGui(idlegui_id(icsm)))
            {
          //тупо но работает :-D
          if((pos1.x+pos1.y+pos1.x2+pos1.y2)!=0)
          {
            //DrawRectangle(pos1.x, pos1.y, pos1.x2, pos1.y2,0,color_obv1,color1);
            DrawRoundedFrame(pos1.x, pos1.y, pos1.x2, pos1.y2,x_round1, y_round1,0,color_obv1,color1);
            
            if((pos2.x+pos2.y+pos2.x2+pos2.y2)!=0)
            {
              //DrawRectangle(pos2.x, pos2.y, pos2.x2, pos2.y2,0,color_obv2,color2);
              DrawRoundedFrame(pos2.x, pos2.y, pos2.x2, pos2.y2,x_round2, y_round2,0,color_obv2,color2);
            
              if((pos3.x+pos3.y+pos3.x2+pos3.y2)!=0)
              {
                //DrawRectangle(pos3.x, pos3.y, pos3.x2, pos3.y2,0,color_obv3,color3);
                DrawRoundedFrame(pos3.x, pos3.y, pos3.x2, pos3.y2,x_round3, y_round3,0,color_obv3,color3);
              
                if((pos4.x+pos4.y+pos4.x2+pos4.y2)!=0)
                {//DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush);
                  //DrawRectangle(pos4.x, pos4.y, pos4.x2, pos4.y2,0,color_obv4,color4);
                  DrawRoundedFrame(pos4.x, pos4.y, pos4.x2, pos4.y2,x_round4, y_round4,0,color_obv4,color4);
                  if((pos5.x+pos5.y+pos5.x2+pos5.y2)!=0)
                  {
                    //DrawRectangle(pos5.x, pos5.y, pos5.x2, pos5.y2,0,color_obv5,color5);
                    DrawRoundedFrame(pos5.x, pos5.y, pos5.x2, pos5.y2,x_round5, y_round5,0,color_obv5,color5);
                
                    if((pos6.x+pos6.y+pos6.x2+pos6.y2)!=0)
                    {
                     // DrawRectangle(pos6.x, pos6.y, pos6.x2, pos6.y2,0,color_obv6,color6);
                      DrawRoundedFrame(pos6.x, pos6.y, pos6.x2, pos6.y2,x_round6, y_round6,0,color_obv6,color6);
                
                      if((pos7.x+pos7.y+pos7.x2+pos7.y2)!=0)
                      {
                       // DrawRectangle(pos7.x, pos7.y, pos7.x2, pos7.y2,0,color_obv7,color7);
                        DrawRoundedFrame(pos7.x, pos7.y, pos7.x2, pos7.y2,x_round7, y_round7,0,color_obv7,color7);
                        
                        if((pos8.x+pos8.y+pos8.x2+pos8.y2)!=0)
                        {
                          //DrawRectangle(pos8.x, pos8.y, pos8.x2, pos8.y2,0,color_obv8,color8);
                          DrawRoundedFrame(pos8.x, pos8.y, pos8.x2, pos8.y2,x_round8, y_round8,0,color_obv8,color8);
                        
                          if((pos9.x+pos9.y+pos9.x2+pos9.y2)!=0)
                          {
                           // DrawRectangle(pos9.x, pos9.y, pos9.x2, pos9.y2,0,color_obv9,color9);
                            DrawRoundedFrame(pos9.x, pos9.y, pos9.x2, pos9.y2,x_round9, y_round9,0,color_obv9,color9);
                       
                            if((pos10.x+pos10.y+pos10.x2+pos10.y2)!=0)
                            {
                              //DrawRectangle(pos10.x, pos10.y, pos10.x2, pos10.y2,0,color_obv10,color10);
                              DrawRoundedFrame(pos10.x, pos10.y, pos10.x2, pos10.y2,x_round10, y_round10,0,color_obv10,color10);
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
//#ifdef ELKA
//#else
	}
//#endif
      }
    }
  }
            

  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void Killer(void)
{
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"DrawLines");
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
  extern const int ENA_HELLO_MSG;
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"DrawLines установлен!");  
  return 0;
}
