#include "..\inc\swilib.h"
#include "conf_loader.h"
extern const unsigned int Time1;
extern const unsigned int EnTimer2;
extern const unsigned int Time2;
extern const unsigned int EnTimer3;
extern const unsigned int Time3;
extern const char pp[]="";
extern const char pip[]="%i:%i%i:%i%i";
extern const char ppi[]="%i.%i";
//#define _MAX ((ScreenH()-1)/30) 
int vidsotok[3][10][100];//3
int temp=1;
char time[3][10][10];
char pidpys[10][10]={"dB","cpu\r%","mV","bat\r%","°C"};
int nowshowing=0;
#define network 0
#define proc 1
#define Voltage 2
#define Percent 3
#define temperature 4
const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

const char percent_i[]="%i";

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

char colour_light[4]={0xF0,0xF0,0xF0,0x64};
char black[4]={0x00,0x00,0x00,0x64};
char red[4]={0xFF,0x00,0x00,0x64};
char free[4]={0xFF,0xFF,0xFF,0x00};

int curent[3]={0,0,0};
void OnRedraw(MAIN_GUI *data)
{ 
  int vertikal=5;
  int x=20;
#ifdef ELKA
  DisableIconBar(1);  
  vertikal+=5;
  x+=15;
#endif
  int scr_w,scr_h;
  int h=30,w=2;
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  DrawRectangle(0,0,scr_w,scr_h,0,colour_light,colour_light);
  WSHDR *ws = AllocWS(256);
  int min=vidsotok[temp-1][nowshowing][0];
  int max=vidsotok[temp-1][nowshowing][0];
  for (int i=1;i<100;i++)
  {
    if (vidsotok[temp-1][nowshowing][i]>max) {max=vidsotok[temp-1][nowshowing][i];}
    if (vidsotok[temp-1][nowshowing][i]<min) {min=vidsotok[temp-1][nowshowing][i];}
  }

  //////////////////////////

  DrawLine(x,6,x,scr_h-h,0,black);
  DrawLine(x-3,6+3,x,6,0,black);
  DrawLine(x+3,6+3,x,6,0,black);
  
  DrawLine(x,scr_h-h,scr_w-w,scr_h-h,0,black);
  DrawLine(scr_w-w-3,scr_h-h-3,scr_w-w,scr_h-h,0,black);
  DrawLine(scr_w-w-3,scr_h-h+3,scr_w-w,scr_h-h,0,black);
  
  for (int i=0;i<(scr_w/30);i++)
  {
    DrawLine(x+33*i,scr_h-h-3,x+33*i,scr_h-h+3,0,black);
    wsprintf(ws,time[temp-1][i]);
    DrawString(ws,x+33*i-x,scr_h-h+4+8*(i%2),x+33*i+x,scr_h-h+5+20,FONT_NUMERIC_SMALL,TEXT_ALIGNMIDDLE,black,free);
//    DrawString(ws,20+33*i-20 , 156+4+8*(i%2) ,(Get_WS_width(ws,FONT_NUMERIC_SMALL)*i)+3,(GetFontYSIZE(FONT_NUMERIC_SMALL)*i)+3,FONT_NUMERIC_SMALL,TEXT_ALIGNMIDDLE,black,free);
  }
  
  for (int i=0;i<(scr_h/27);i++)
  {
    DrawLine(x-3,30+21*i,x+3,30+21*i,0,black);
    if (nowshowing==4)
    {
      wsprintf(ws,ppi,(max-i*(max-min)/vertikal)/10,(max-i*(max-min)/vertikal)%10);
    }
    else
    {
      wsprintf(ws, percent_i,max-i*(max-min)/vertikal);
    }
    DrawString(ws,0,30+21*i-3,x-5,30+21*i+GetFontYSIZE(FONT_NUMERIC_SMALL),FONT_NUMERIC_SMALL,TEXT_ALIGNRIGHT,black,colour_light);
   //DrawString(ws,0,30+21*i-3,Get_WS_width(ws,FONT_NUMERIC_SMALL),(GetFontYSIZE(FONT_NUMERIC_SMALL)*i)+3,FONT_NUMERIC_SMALL,TEXT_ALIGNLEFT,black,colour_light);
  }
  
  wsprintf(ws, pidpys[nowshowing]);
  DrawString(ws,0,1,Get_WS_width(ws,FONT_SMALL),GetFontYSIZE(FONT_SMALL),FONT_SMALL,TEXT_ALIGNRIGHT,black,free);

///////////////////////////////
  
  for (int i=1;i<100;i++)
   {
     //DrawLine(20+(i-1),135-105*(vidsotok[temp-1][nowshowing][i-1]-min)/(max-min),20+i,135-105*(vidsotok[temp-1][nowshowing][i]-min)/(max-min),0,black);
     DrawLine(x+(i-1),(scr_h-40)-(scr_h-70)*(vidsotok[temp-1][nowshowing][i-1]-min)/(max-min),x+i
                       ,(scr_h-40)-(scr_h-70)*(vidsotok[temp-1][nowshowing][i]-min)/(max-min),0,black);
   }
   //wsprintf(ws, "%i %s %i",csmids[i],name,csmes[i]->state);
   //DrawString(ws,22,5+i*16,130,140,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
  DrawRectangle(x+curent[temp-1]-1,/*156*/scr_h-15,x+curent[temp-1],/*9*/0,0,red,red);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1; 
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
#ifdef ELKA
  DisableIconBar(0);
#endif
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
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case '1':temp=1;REDRAW();break;
    case '2':if (EnTimer2) {temp=2;REDRAW();}break;
    case '3':if (EnTimer3) {temp=3;REDRAW();}break;
    case '4':nowshowing--;if (!nowshowing){nowshowing=4;}REDRAW();break;
    case '6':nowshowing=(nowshowing+1)%5;REDRAW();break;
    case RED_BUTTON: return(1);
    }
    
  }
  return(0);
}
extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,	
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  (void *)kill_data,	
  (void *)method8,
  (void *)method8,
  0
};

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

GBSTMR Nettimer1,Nettimer2,Nettimer3;

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&Nettimer1);
  GBS_DelTimer(&Nettimer2);
  GBS_DelTimer(&Nettimer3);
  SUBPROC((void *)ElfKiller);
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

void GetNet1()
{
  RAMNET *rn=RamNet();
  vidsotok[0][0][curent[0]]=rn->power;
  vidsotok[0][1][curent[0]]=GetCPULoad();
  vidsotok[0][2][curent[0]]=GetAkku(0,2);
  vidsotok[0][3][curent[0]]=*RamCap();
  vidsotok[0][4][curent[0]]=(GetAkku(1,3)-0xAAA+15);
  if (curent[0]%33==0)
  {
    TTime ttime;
    TDate date;
    GetDateTime(&date,&ttime);
    sprintf(time[0][curent[0]/33],pip,ttime.hour,ttime.min/10,ttime.min%10,ttime.sec/10,ttime.sec%10);
  }
  curent[0]=(curent[0]+1)%100;
  GBS_StartTimerProc(&Nettimer1,Time1*262/10,GetNet1);
  if ((IsGuiOnTop(MAINGUI_ID))&&(temp==1)) {REDRAW();}
}

void GetNet2()
{
  RAMNET *rn=RamNet();
  vidsotok[1][0][curent[1]]=rn->power;
  vidsotok[1][1][curent[1]]=GetCPULoad();
  vidsotok[1][2][curent[1]]=GetAkku(0,2);
  vidsotok[1][3][curent[1]]=*RamCap();
  vidsotok[1][4][curent[1]]=(GetAkku(1,3)-0xAAA+15);
  if (curent[1]%33==0)
  {
    TTime ttime;
    TDate date;
    GetDateTime(&date,&ttime);
    sprintf(time[1][curent[1]/33],pip,ttime.hour,ttime.min/10,ttime.min%10,ttime.sec/10,ttime.sec%10);
  }
  curent[1]=(curent[1]+1)%100;
  GBS_StartTimerProc(&Nettimer2,Time2*262/10,GetNet2);
  if ((IsGuiOnTop(MAINGUI_ID))&&(temp==2)) {REDRAW();}
}

void GetNet3()
{
  RAMNET *rn=RamNet();
  vidsotok[2][0][curent[2]]=rn->power;
  vidsotok[2][1][curent[2]]=GetCPULoad();
  vidsotok[2][2][curent[2]]=GetAkku(0,2);
  vidsotok[2][3][curent[2]]=*RamCap();
  vidsotok[2][4][curent[2]]=(GetAkku(1,3)-0xAAA+15);
  if (curent[2]%33==0)
  {
    TTime ttime;
    TDate date;
    GetDateTime(&date,&ttime);
    sprintf(time[2][curent[2]/33],pip,ttime.hour,ttime.min/10,ttime.min%10,ttime.sec/10,ttime.sec%10);
  }
  curent[2]=(curent[2]+1)%100;
  GBS_StartTimerProc(&Nettimer3,Time3*262/10,GetNet3);
  if ((IsGuiOnTop(MAINGUI_ID))&&(temp==3)) {REDRAW();}
}

int main(char *exename, char *fname)
{
  InitConfig();
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  //WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Battery");
//  FreeWS(ws);
  GBS_StartTimerProc(&Nettimer1,100,GetNet1);
  if (EnTimer2) {GBS_StartTimerProc(&Nettimer2,100,GetNet2);}
  if (EnTimer3) {GBS_StartTimerProc(&Nettimer3,100,GetNet3);}
  return 0;
}
