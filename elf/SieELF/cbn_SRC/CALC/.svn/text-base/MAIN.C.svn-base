#include "C:\ARM\swilib.h"
const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int 
 prew=0, act=0, bt=0,
 ty = 20, ty1 = 140, tp=0;
long int  res=0, resprew=0, c = 0;
char znprew=' ', zn=' ';


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


void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrawRoundedFrame(10,26,122,92,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(20));
  
  
  DrawRoundedFrame(13,29,119,73,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(0));
  WSHDR *ws = AllocWS(256); 

  wsprintf(ws, "                 exit"); 
  DrawString(ws,3,76,128,90,3,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  FreeWS(ws);
  
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
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
}


void printres(int tpx, int tpy, int tpx1, int tpy1, int oldd, int newd, int d)
{
   WSHDR *ws = AllocWS(256); 
   if(d==1)
  wsprintf(ws, "%d\r\n",oldd); 
  else
   wsprintf(ws, "%c\r\n",oldd); 
  DrawString(ws,tpx,tpy,tpx1,tpy1,3,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  if(d==1)
  wsprintf(ws, "%d\r\n",newd); 
  else
  wsprintf(ws, "%c\r\n",newd); 
  DrawString(ws,tpx,tpy,tpx1,tpy1,3,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
  FreeWS(ws); 
}


void result(int action)
{
   printres(10,43,43,175,znprew,zn,0);
   resprew=res;
   switch(action)
    {  
    case 0:
      res=c;
      break;
    case 1:
        res+=c;
      break;
    case 2:
        res-=c;
      break;
    case 3:
        res*=c;
        break;
    case 4:
       res/=c;
      break;
    }
   if(c==0)  res=resprew;
          printres(3,35,128,175,resprew,res,1);
           c=0;
           //a=0;          
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    
          
     int bt=msg->gbsmsg->submess;
    if((bt>=48)&&(bt<=57)&&(c<10000000))
     c=c*10+bt-48; 
    else 
    switch(bt)
    {
    case RIGHT_SOFT:
      return(1); 
      break;
    case RIGHT_BUTTON:
           result(act);
           act=1;
           znprew=zn;
           zn='+';
           printres(10,43,43,175,znprew,zn,0);
        break;
     case LEFT_BUTTON:
           result(act);
           act=2;
              znprew=zn;
           zn='-';
         printres(10,43,43,175,znprew,zn,0);
        break;        
      case UP_BUTTON:
           result(act);
           act=3;
              znprew=zn;
           zn='*';
          printres(10,43,43,175,znprew,zn,0);
        break;    
//         case DOWN_BUTTON:
//           result(act);
//           act=4;
//            znprew=zn;
//           zn='/';
//           printres(10,43,43,175,znprew,zn,0);
//        break;   
    case ENTER_BUTTON:  
           result(act);
           act=0;
           zn='=';
          printres(10,43,43,175,znprew,zn,0); 
         break;
    
    }
  }
printres(3,55,128,175,prew,c,1);

prew=c;
  return(0);
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

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
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

// Функция, которая устанавливает название этого CSM для X-Task.
void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"elfcalc");
  FreeWS(ws);
}


// Основная процедура. Она первой получает управление при старте эльфа.
int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}
