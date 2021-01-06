

int Games_GUI_ID;// ИД гуя игры 
const RECT Canvas={0,0,0,0}; 
int hf=1;
//IMGHDR *outim; 
int coordX =65;
int coordy =35;
  int cur_keys;
  int cur_display;
  int uin = 1;
  int temp_keys;
  int temp_display;  
int bond=1; //таймер живой
#define TMR_SECOND 216// секунда
char Illumination = 0;
char * block;
GBSTMR idle_timer;
GBSTMR time_timer;
GBSTMR sleep_timer;
GBSTMR touch_timer;

char Touch = 0; // Только что нажат левый софт ( если == 1)(в двойном нажатии для разблокировки)

int fore = 0;
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#define IPC_TEXTINFO_NAME "ScreenSaver"
#define IPC_UPDATE_STAT 1
#define IPC_XTASK_NAME "XTask"
#define IPC_XTASK_IDLE 1
#define IPC_XTASK_SHOW_CSM 2
#define IPC_XTASK_LOCK_SHOW 3
#define IPC_XTASK_UNLOCK_SHOW 4
#define IPC_CHECK_DOUBLERUN 2
#define IPC_CHECK_S 12
#define IPC_SHOW_MSG 3
const char ipc_my_name[32]=IPC_TEXTINFO_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;
void CheckDoubleRun(void);
int state = 4;
int tike = 0;
// 0-2 - заставки, 3 - меню игры, 4 - ... 

int cz = 0; // выбранный пункт меню



char *boxxes = " ";
int xx1 = 0;
int xx2 = -10;
int xx3 = 40;
int xx4 = 55;  //координаты солнца
int xx5 = 0;

//----------------------------------- контейнеры для картинок --------------------
                                                                          //

                                                                                 //
IMGHDR *FImage1;     //надписи на кнопках                                                           //
IMGHDR *FImage2;     //огоньки                                                            //
IMGHDR *FImage3;     //левая зеленая
IMGHDR *FImage3b;     //левая синяя                                                      //
IMGHDR *FImage4;     //картинка заставки   
IMGHDR *FImage5;     //правая зеленая
IMGHDR *FImage5b;     //правая синяя   
IMGHDR *FImage6;     //центр зеленая
IMGHDR *FImage6b;     //центр синяя   
IMGHDR *FImage7;     //линия
IMGHDR *FImage7b;     //линия
IMGHDR *FImage8;     //цифры
IMGHDR *FImage9;     //слайд
IMGHDR *FImage10;     //iconbar_png
IMGHDR *Dig0;     //цифры
IMGHDR *Dig1;     //цифры
IMGHDR *Dig2;     //цифры
IMGHDR *Dig3;     //цифры
IMGHDR *Dig4;     //цифры
IMGHDR *Dig5;     //цифры
IMGHDR *Dig6;     //цифры
IMGHDR *Dig7;     //цифры
IMGHDR *Dig8;     //цифры
IMGHDR *Dig9;     //цифры
IMGHDR *Dig10;     //цифры

//
//----------------------------------- контейнеры для картинок --------------------

