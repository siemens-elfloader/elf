#include "..\inc\swilib.h"
#include "../inc/cfg_items.h"
#include "conf_loader.h"
// В swilib.h комментируем // строку #define NEWSGOLD если не S75


// Внешние функции вызываются при:
extern int OnStart(void); // Старте приложения. Возвращает 0 или 1 для выхода.
extern void OnCreate(); // Создании окна
extern void OnClose(); // Закрытии окна
extern void OnExit(); // Выходе
extern void OnRedraw(); // Перерисовке экрана
extern int OnKey(); // Нажатии клавиши. Возвращает 0 или 1 для выхода.
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

extern const unsigned int shrift;
//extern const unsigned int tm;
extern const char picg[];
extern const unsigned int game;

int tm=1;
int tmr=2;
int dvig=0;
int dvig1=80;
int dvig2=160;
int yr=0;
int ns=0;
int ns1=0;
int ns2=0;
int life=3;
int dvig_ogr=330;
int dvig1_ogr=330;
int dvig2_ogr=330;
char pic12_v[128];
char pic13_v[128];
char pic14_v[128];
char pic1[128];
char pic2[128];
char pic3[128];
char pic1_v[128];
char pic2_v[128];
char pic3_v[128];
char sound1[128];
char sound2[128];
char sound3[128];
char pic12[128];
char pic13[128];
char pic14[128];
char pic15[128];
char pic16[128];
int ots=3;
int otsp=0;

char st[]="%s";

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
}MAIN_GUI;
  int i1;

  typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void Play(const char *fname)
{
  extern const unsigned int volume;
  if (!IsCalling())
  {
  FSTATS fstats;
  unsigned int err;
  if (GetFileStats(fname,&fstats,&err)!=-1)
  {
  PLAYFILE_OPT _sfo1;
  WSHDR* sndPath=AllocWS(128);
  WSHDR* sndFName=AllocWS(128);
  char s[128];
  const char *p=strrchr(fname,'\\')+1;
  str_2ws(sndFName,p,128);
  strncpy(s,fname,p-fname);
  s[p-fname]='\0';
  str_2ws(sndPath,s,128);
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=1;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=volume;
  #ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  #ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  _sfo1.unk5=1;
  PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #endif
  #endif
  FreeWS(sndPath);
  FreeWS(sndFName);
  }
  }
}





GBSTMR timer,timer1;

  void timer_proc(void)
{ 
  REDRAW();
  GBS_StartTimerProc(&timer,20,timer_proc);
  dvig=dvig+tm+4;
  dvig1=dvig1+tm+4;
  dvig2=dvig2+tm+4;
  yr=yr+tmr;
  ns=ns+1;
  ++ns1;
  ++ns2;
}

  void otschet(void)
{ 
  
 
  
  REDRAW();
  GBS_StartTimerProc(&timer1,200,otschet);
  --ots;
  ++otsp;
  if (ots==0)
  {
  GBS_StopTimer(&timer1);
  GBS_StartTimerProc(&timer,30,timer_proc);
  }
  
}

 

void Log(int dummy, char *txt)
{
  unsigned int ul;
  char text[128];
  sprintf(text,"%slog",picg);
  int f=fopen(text,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    lseek(f, 0, 0, &ul, &ul);
    fwrite(f,txt,strlen(txt),&ul);
    fclose(f,&ul);
  }
  mfree(txt);
}



int x=30;
int y=120;
void drawimg()
{
 char pic11[128];
 sprintf(pic11,"%scar.png",picg);
 DrawImg(x,y,(int)pic11); //(int)"0:\\ZBin\\Ainfo\\pb.png"
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{               
             InitConfig();   
                
                //--(Разные интервалы)---
                
                if (ns1>80 && ns1<200)
                {
                  dvig_ogr=330;
                  dvig1_ogr=400;
                  dvig2_ogr=450;
                }
                if (ns1>201 && ns1<400)
                {
                  dvig_ogr=400;
                  dvig1_ogr=330;
                  dvig2_ogr=400;
                }
                if (ns1>500 && ns1<800)
                {
                  dvig_ogr=370;
                  dvig1_ogr=450;
                  dvig2_ogr=400;
                }
                if (ns1>801 && ns1<1000)
                {
                  dvig_ogr=330;
                  dvig1_ogr=330;
                  dvig2_ogr=420;
                }
                if (ns1>1001 && ns1<1250)
                {
                  dvig_ogr=420;
                  dvig1_ogr=330;
                  dvig2_ogr=330;
                }
                if (ns1>1251 && ns1<1500)
                {
                  dvig_ogr=330;
                  dvig1_ogr=430;
                  dvig2_ogr=370;
                }
                if (ns1>=1500) ns1=0;
           //------------Проверка на одновременное появленние-----------
                if ((dvig>0)&&(dvig<130)&&(dvig1>0)&&(dvig1<130)&&(dvig2>0)&&(dvig2<130))
                    dvig=dvig+330;
                     
            //----------Меняем машины на полосах------------------- 
                if (ns2>=0)
                {
                  if ((dvig>0)&&(dvig<130))
                  sprintf(pic12_v,st,pic12);
                  if ((dvig1>0)&&(dvig1<130))
                  sprintf(pic13_v,st,pic13);
                  if ((dvig2>0)&&(dvig2<130))
                  sprintf(pic14_v,st,pic14);  
                }
                if (ns2>=200)
                {
                  if ((dvig>0)&&(dvig<130))
                  sprintf(pic12_v,st,pic15);
                  if ((dvig1>0)&&(dvig1<130))
                  sprintf(pic13_v,st,pic14);
                  if ((dvig2>0)&&(dvig2<130))
                  sprintf(pic14_v,st,pic16);  
                }
                if (ns2>=400)
                {
                  if ((dvig>0)&&(dvig<130))
                  sprintf(pic12_v,st,pic13);
                  if ((dvig1>0)&&(dvig1<130))
                  sprintf(pic13_v,st,pic12);
                  if ((dvig2>0)&&(dvig2<130))
                  sprintf(pic14_v,st,pic15);  
                }
                if (ns2>=600)
                {
                  if ((dvig>0)&&(dvig<130))
                  sprintf(pic12_v,st,pic14);
                  if ((dvig1>0)&&(dvig1<130))
                  sprintf(pic13_v,st,pic16);
                  if ((dvig2>0)&&(dvig2<130))
                  sprintf(pic14_v,st,pic12);  
                }
                if (ns2==800)
                   {
                    ns2=0;
                    Play(sound1);
                   }
         
     //------------Усложнение игры при наборе n-го кол-ва очков---------------------------- 
                if (game==1)
                {
                  if (ns>100){ tm=2; tmr=3;}
                  if (ns>600){ tm=3; tmr=4;}
                  if (ns>1200){ tm=4; tmr=5;}
                  if (ns>2000){ tm=5; tmr=6;}
                  if (ns>3000){ tm=6; tmr=6;}
                  if (ns>4000){ tm=7; tmr=6;}
                 
                }
     //-------------------------Дорога-----------------------------           
            

  DrawImg(0,yr,(int)pic1_v);
  DrawImg(0,yr-240,(int)pic3_v);
  DrawImg(0,yr-480,(int)pic2_v);
  
  
  //WSHDR *ws = AllocWS(256); // Создаём юникод-строку
  wsprintf(data->ws1, "Balls\n%d",ns); // Пихаем в неё текст
  DrawString(data->ws1,1,40,80,70,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));// Отрисовываем
  wsprintf(data->ws1, "Life\n%   d",life); // Пихаем в неё текст
  DrawString(data->ws1,3,10,80,38,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(data->ws1, "P: %d",tm); // Пихаем в неё текст
  DrawString(data->ws1,3,70,80,110,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  
  if (((x>29 && x<50)&&(dvig>260&&dvig<310)) || ((x>55 && x<80)&&(dvig1>260&&dvig1<310))
     || ((x>80 && x<90)&&(dvig2>260&&dvig2<310)))
   {
     Play(sound2);
     --life;
      dvig=0;
      dvig1=80;
      dvig2=160;
      x=30;
      y=120;
    }
      else
    
    { //------------------Рисуем
      
    if (dvig<=dvig_ogr)
             {                  
              DrawImg(30,dvig-170,(int)pic12_v);
              }
               else
             {     
              dvig=0;                          
             } 
    
       if  (dvig1<=dvig1_ogr)
            {
            
             DrawImg(57,dvig1-170,(int)pic13_v); 
            }
           else
            {  
              dvig1=0;
            } 
        if  (dvig2<=dvig2_ogr)
            {
          
             DrawImg(84,dvig2-170,(int)pic14_v); 
            }
           else
            {
              dvig2=0;
            } 
        if  (yr>=480)
            {
              yr=0;
            }
    }
   DrawRoundedFrame(0,0,131,157,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(23));
  DrawRoundedFrame(0,157,131,175,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(1));
 
  wsprintf(data->ws1, "Exit"); // Пихаем в неё текст
  DrawString(data->ws1,109,160,131,175,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  wsprintf(data->ws1,"Menu");
  DrawString(data->ws1,3,160,80,175,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  if ((otsp>=0)&&(otsp<=2))
  {
  wsprintf(data->ws1,"%d",ots);  
  DrawString(data->ws1,60,50,130,130,1,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if (game==1)//------------Тип игры
  { 
  if (life==0)
      {
      GBS_StopTimer(&timer);
      
         //--------Чтение из файла
           unsigned int err;
           int f;
           int record=0;
           char *mem;
           char text[128];
           sprintf(text,"%slog",picg);
           f=fopen(text,A_ReadOnly+A_BIN,P_READ,&err);
       if(f!=-1)  //проверка на существование
             {
              mem=malloc(1000);
              lseek(f, 0, 0, &err, &err);//курсор в начало файла
              fread(f, mem, 1000, &err);//чтение из файла
              sscanf(mem,"%d",&record); //-----перевод из чар в инт 
              mfree(mem);
             }
             
             fclose(f, &err);
         
      if (record<ns)
      {
      char *s=malloc(100);
      sprintf(s,"%d\r",ns);
      SUBPROC((void *)Log,0,s);
      }
      wsprintf(data->ws1,"%t","Вы проиграли");  
      DrawString(data->ws1,30,80,130,130,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
      }
   }
  if (game==0)    //Игра до 1500 очков
    {
    if (life==0)
      {
        GBS_StopTimer(&timer);
        wsprintf(data->ws1,"%t","Вы проиграли");  
        DrawString(data->ws1,30,80,130,130,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      if (ns>=1500)
        {
         GBS_StopTimer(&timer);
         wsprintf(data->ws1,"%t","Вы выиграли");
         DrawString(data->ws1,30,80,130,130,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
    }
      
  
  //FreeWS(ws);// Освобождаем память
  drawimg(); //----------Рисуем свою тачку
  
  
}


//void method0(MAIN_GUI *data){}
void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{  
  //GBS_StartTimerProc(&timer,200,timer_proc);
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256); 
  sprintf(pic1,"%sroad.png",picg);
  sprintf(pic2,"%sroad1.png",picg);
  sprintf(pic3,"%sroad2.png",picg);
  sprintf(pic12,"%scar1.png",picg);
  sprintf(pic13,"%sbike.png",picg); 
  sprintf(pic14,"%scar2.png",picg);
  sprintf(pic15,"%scar3.png",picg);
  sprintf(pic16,"%scar4.png",picg);
  
  //sprintf(pic12_v,"%s",pic12);
  //sprintf(pic13_v,"%s",pic13);
  //sprintf(pic14_v,"%s",pic14);
  sprintf(sound1,"%ssound.mid",picg);
  sprintf(sound2,"%sbum.wav",picg);
  sprintf(sound3,"%sexit.mid",picg);
  sprintf(pic1_v,st,pic1);
  sprintf(pic2_v,st,pic1);
  sprintf(pic3_v,st,pic3);
  data->gui.state=1;}
void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (ns>=1)
  {
  GBS_StopTimer(&timer);
  GBS_DelTimer(&timer);
  GBS_DelTimer(&timer1);
  }
  Play(sound3);
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;}
void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{ 
  data->gui.state=2;
}
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return; data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
      
    case '4':
      if (x>=31)
      x=x-9; 
      break;
    case '6': 
      if (x<=83)
      x=x+9;
      break;
       case '2':
         if (game==0)
         {
             if (tm<5)
             {
             ++tm;
             ++tmr;
             }
         }
      break;
    case '8':
      if (game==0)
         {
           if (tm>1)
           {
           --tm;
           --tmr;
           }
         }
      break;
    /* case '5':
     
      break;*/
       case '*':
         if (ns>1)
        GBS_StopTimer(&timer); 
      break;
       case '#':
         if (game==1)
           {
         if (life!=0)
             {
           if (otsp>=2)
           GBS_StartTimerProc(&timer,30,timer_proc);
        else
                     {
                      Play(sound1);
                      GBS_StartTimerProc(&timer1,30,otschet);
                     }
             }
           }
         if (game==0)
           {
         if (life!=0)
             {
           if ((otsp>=2)&&(ns<1500)) //если вы выграли, чтоб не подолжать движение на решетку
           GBS_StartTimerProc(&timer,30,timer_proc);
        else
                   {
                     Play(sound1);
                     GBS_StartTimerProc(&timer1,30,otschet);
                   }
             }
           }             
      break;
      case '0':
         {     
       if (ns>=1)
         GBS_StopTimer(&timer);
         life=3;
         dvig=0;
         dvig1=80;
         dvig1=160;
         x=30;
         y=120;
         ns=0;
         otsp=-1;
         ots=4;
         tm=1;
         tmr=2;
         Play(sound1);
         GBS_StartTimerProc(&timer1,30,otschet);
         }
      break;
    
      case LEFT_SOFT:
      {
	void TestMenu(void);
	TestMenu();
      }
      break;
     }
  }
   if (msg->gbsmsg->msg==LONG_PRESS) //Долгое нажатие
  {
    switch(msg->gbsmsg->submess)
     {
    
    case '4':
      if (x>=31)
      x=x-9; 
      break;
    case '6':
      if (x<=83)
      x=x+9;
     }
   }
  
  return(0);
}
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{ 
  mfree_adr(data);
}//  mfree_adr(data);
#else
extern void kill_data(void *p, void (*func_p)(void *));

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif
int method8(void){return(0);} // Пустая ф-я
int method9(void){return(0);} // Пустая ф-я


const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	
    #else
  (void *)kill_data,	
    #endif
  (void *)method8,
  (void *)method9,
  0
};


const RECT Canvas={0,0,131,175};




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

void Killer(void){
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  //OnExit();
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
 //((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  //OnClose();
  //mfree(screen);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){  
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
     csm->csm.state=-3; 
  return(1);
}

const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"E-Racer");
}

int main(char *exename, char *fname){
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}
//---------------------------------------------------------------------------
// Test menu
//---------------------------------------------------------------------------
void menup1(GUI *data)
{
           unsigned int err;
           int f;
           int record=0;
           char *mem;
           char text[128];
           char str_text[]="%d";
           char str_text1[]="%t\n  %d";
           sprintf(text,"%slog",picg);
           f=fopen(text,A_ReadOnly+A_BIN,P_READ,&err);
       if(f!=-1)  //проверка на существование
             {
              mem=malloc(1000);
              lseek(f, 0, 0, &err, &err);//курсор в начало файла
              fread(f, mem, 1000, &err);//чтение из файла
              sscanf(mem,str_text,&record); //-----перевод из чар в инт 
              mfree(mem);
             }
             DrawRoundedFrame(0,0,131,175,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(1));
            WSHDR *ws_txt=AllocWS(256);
            wsprintf(ws_txt,str_text1,"Рекорд",record);
            DrawString(ws_txt,45,50,100,175,shrift,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
            FreeWS(ws_txt);  
            fclose(f, &err);
}
void menup2(GUI *data)
{
  
        WSHDR *ws;
        ws=AllocWS(150);
        extern const char *successed_config_filename;
        str_2ws(ws,successed_config_filename,128);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
}

void menup3(GUI *data)
{     
     
      ShowMSG(1,(int)"E-Racer, v0.7b");
      
}
#ifdef NEWSGOLD
int icon[]={0x5b,0};
#else
int icon[]={0xFA0,0};
#endif
const HEADER_DESC menuhdr={0,0,131,21,icon,(int)"E-Racer",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[3]=
{
  {NULL,(int)"Рекорд",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Настройки",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Об эльфе",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[3]={
  menup1,
  menup2,
  menup3
};

const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  (SOFTKEY_DESC *)menu_sk,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  menuitems,
  menuprocs,
  3
};

void TestMenu(void)
{
  CreateMenu(0,0,&tmenu,&menuhdr,0,3,0,0);
}

