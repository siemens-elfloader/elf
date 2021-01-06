#include "swilib.h"
#include "..\conf_loader.h"
#include "../inc/cfg_items.h"
#include "bookmarks.c"


//---------- Обьявляем переменные ----------------
int NumOfItems;//Число итемов меню 
int Selected;
int y;
int i;
int x1;
int x2;
int y1;
int y2;
int frame_y;
int MenuActive;

// - - - - Переменные конфига - - - - - - - - - -
extern const unsigned int OFFSET;
extern const unsigned int LEN;
extern const unsigned int BEGIN;

extern const char BGPIC[128];

extern const char BM1PIC[128];//Путь к иконке
extern const char BM2PIC[128];
extern const char BM3PIC[128];
extern const char BM4PIC[128];
extern const char BM5PIC[128];
extern const char BM6PIC[128];
extern const char BM7PIC[128];
extern const char BM8PIC[128];
extern const char BM9PIC[128];
extern const char BM10PIC[128];
extern const char BM11PIC[128];
extern const char BM12PIC[128];
extern const char BM13PIC[128];
extern const char BM14PIC[128];
extern const char BM15PIC[128];
extern const char BMXPIC[128];

extern const char BM1FILE[128];//Путь к файлу
extern const char BM2FILE[128];
extern const char BM3FILE[128];
extern const char BM4FILE[128];
extern const char BM5FILE[128];
extern const char BM6FILE[128];
extern const char BM7FILE[128];
extern const char BM8FILE[128];
extern const char BM9FILE[128];
extern const char BM10FILE[128];
extern const char BM11FILE[128];
extern const char BM12FILE[128];
extern const char BM13FILE[128];
extern const char BM14FILE[128];
extern const char BM15FILE[128];

extern const int SELECTED;//Сюда сохраняем номер выделенного итема
extern const int DRAW_MODE;
extern const int EXIT_BUTTON;
// - - - - - - - - А вот и цвета - - - - - - - - - 
extern const char cfgPanBorderCol[4];
extern const char cfgPanBGCol[4];
extern const char cfgBookBorderCol[4];
extern const char cfgBookBGCol[4];
// - - - - - - - - - - - - - - -  - - - - - - - - - 
GBSTMR timer;

CSM_DESC icsmd;

void (*old_icsm_onClose)(CSM_RAM*);
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);

const int minus11=-11;
unsigned char scrH, scrW;
unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

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



void ClearMenu()
{
  scrH=ScreenH();
  scrW=ScreenW();
  NumOfItems = 0;
  Selected=SELECTED;
  MenuActive = 0;
  if(DRAW_MODE==0){x1=0;x2=0;}
  if(DRAW_MODE==1){x1=scrW-1;x2=(scrW-1);}
  if(DRAW_MODE==2){y1=0;y2=0;}
  if(DRAW_MODE==3){y1=scrH-1;y2=(scrH-1);}
  if((DRAW_MODE==0)||(DRAW_MODE==1))
  {
      y1=BEGIN;
      y2=BEGIN+LEN;//scrH-6;
  }
  if((DRAW_MODE==2)||(DRAW_MODE==3))
  {
    x1=BEGIN;
    x2=BEGIN+LEN;//scrW-1;
  }
}

void DrawPanel()
{
  void *canvasdata=BuildCanvas();
  if(DRAW_MODE==0){if (x2<21)x2+=7; else x2=21;}
  if(DRAW_MODE==1){if (x1>scrW-22)x1-=7; else x1=scrW-22;}
  if(DRAW_MODE==2){if (y2<21)y2+=7; else y2=21;}
  if(DRAW_MODE==3){if (y1>scrH-22)y1-=7; else y1=scrH-22;}
  
  DrawCanvas(canvasdata, x1, y1, x2, y2, 1);
  DrawRoundedFrame( x1, y1,x2, y2, 2, 2, 0, cfgPanBorderCol, cfgPanBGCol );
  GBS_StartTimerProc(&timer,25,DrawPanel);
  int z;
  if ( NumOfItems == 0 ) return; 
  y = 0; z=0;
  if(NumOfItems>((LEN)/(16+OFFSET))) i = Selected - ((LEN)/(16+OFFSET))+1; else i=0;
  if ( i < 0 ) i = 0;
  while ( i < NumOfItems )
  {
    const char *s;
    s=bm_pic(i);
    if ((s)&&(strlen(s)))s=bm_pic(i);
    else s=BMXPIC;
    if(((DRAW_MODE==0)&&(x2==21))||((DRAW_MODE==1)&&(x1==scrW-22)))
    {
      if ( i == Selected )
      {
       DrawRoundedFrame( x1+2, y + y1+2, x1+19, y + y1+19, 2, 2, 0, cfgBookBorderCol, cfgBookBGCol );
       DrawImg(x1+3, y+y1+3, (int)s);
      }
      else
      {
       DrawImg(x1+3, y+y1+3, (int)s);
      }
    }
    if(((DRAW_MODE==2)&&(y2==21))||((DRAW_MODE==3)&&(y1==scrH-22)))
    {
      if ( i == Selected )
      {
       DrawRoundedFrame( y +x1+2,  y1+2, y +x1+19,  y1+19, 2, 2, 0, cfgBookBorderCol, cfgBookBGCol );
       DrawImg(y+x1+3, y1+3, (int)s);
      }
      else
      {
       DrawImg(y+x1+3, y1+3, (int)s);
      }
    }
    i++;
    y += (16+OFFSET);
    z++;
    if ( z > ((LEN)/(16+OFFSET))-1 ) break;
  }
}

void CheckBookmarks()
{
  const char *s;
  s=bm_file(0);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(1);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(2);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(3);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(4);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(5);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(6);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(7);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(8);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(9);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(10);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(11);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(12);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(13);
  if ((s)&&(strlen(s)))NumOfItems+=1;
  s=bm_file(14);
  if ((s)&&(strlen(s)))NumOfItems+=1;
}
void ShowMenu()
{
  ClearMenu();
  CheckBookmarks();
  MenuActive=1;
}
void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  if(MenuActive)DrawPanel();
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
  GBS_DelTimer(&timer);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  CloseCSM(MAINCSM_ID);

}

static void EditConfig(void)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}


inline int MenuOnKey_1(unsigned char key )
{
  int Sel;
  Sel=Selected;
  switch ( key )
  {      
    case DOWN_BUTTON:
       case '8':
       Selected++;
       if(Selected >= NumOfItems)Selected=0;
       break;
       case UP_BUTTON:
       case '2':
       Selected--;
       if(Selected<0)Selected=NumOfItems-1; 
       break;
    case ENTER_BUTTON:
    case '5':
      RunBM(Sel);
      return (1);
    case '*':
      EditConfig();
      break;
  }
  if (key==EXIT_BUTTON)return (1); 
    
  return (0);
}

inline int MenuOnKey_2(unsigned char key )
{
  int Sel;
  Sel=Selected;
  switch ( key )
  {      
    case RIGHT_BUTTON:
       case '6':
       Selected++;
       if(Selected >= NumOfItems)Selected=0;
       break;
       case LEFT_BUTTON:
       case '4':
       Selected--;
       if(Selected<0)Selected=NumOfItems-1; 
       break;
    case ENTER_BUTTON:
    case '5':
      RunBM(Sel);
      return (1);
    case '*':
      EditConfig();
      break;
  }
  if (key==EXIT_BUTTON)return (1); 
    
  return (0);
}


int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  int i = 0;
  if ( msg->gbsmsg->msg == KEY_DOWN ) 
  {
    if((DRAW_MODE==0)||(DRAW_MODE==1))
    i = ( MenuOnKey_1( msg->gbsmsg->submess ) );
    else i = ( MenuOnKey_2( msg->gbsmsg->submess ) );
    REDRAW();
  }
  if ( msg->gbsmsg->msg == LONG_PRESS ) 
  {
    if((DRAW_MODE==0)||(DRAW_MODE==1))
    i = ( MenuOnKey_1( msg->gbsmsg->submess ) );
    else i = ( MenuOnKey_2( msg->gbsmsg->submess ) );
    REDRAW();
  }
  return(i);
}

#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}
#else
extern void kill_data(void *p, void (*func_p)(void *));

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif


int method8(void){return(0);}


int method9(void){return(0);}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	//Destroy
  #else
  (void *)kill_data,	//Destroy
  #endif
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,129,129};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
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

// Всё ясно из названия ;) оставить как есть
void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


void RewriteConfig()
{
  *((int *)&SELECTED)=Selected;

  #pragma segment="CONFIG_C"
  unsigned int ul;
  int f;
  extern const CFG_HDR cfghdr0; //first var in CONFIG
  void *cfg=(void*)&cfghdr0;
  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if ((f=fopen("4:\\ZBin\\etc\\FastRun.bcfg",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))==-1){
   f=fopen("0:\\ZBin\\etc\\FastRun.bcfg",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul);
  }
  fwrite(f,cfg,len,&ul);
  fclose(f,&ul);
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)RewriteConfig);
  SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM * csm = ( MAIN_CSM * ) data;
if ( ( msg->msg == MSG_GUI_DESTROYED ) && ( ( int )msg->data0 == csm->gui_id ) )
{
csm->csm.state = -3;
}
return(1);
}

// Инициализация структуры MAINCSM
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


// Основная процедура. Она первой получает управление при старте эльфа.
int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  ShowMenu();
  if (NumOfItems==0)
  {
    LockSched();
    EditConfig();
    UnlockSched();
    return 0;
  }
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  //UpdateCSMname();
  return 0;
}
