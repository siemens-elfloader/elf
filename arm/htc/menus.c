// Меню
#include "string_works.h"
//#include "swilib.h"
//#include "menus.h"
//#include "fastrun.c"
//#include "keys.h"

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

MAIN_GUI *zerro_gui;
static IPC_REQ chips;





extern DrwPngImg(IMGHDR *img, int x, int y);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
extern char *coloc;
extern void TimerA();
extern void adr_progress();
extern int dir_4;
extern int ConstructList(void);
extern int Play5(int sm0);
extern int Play6(int sm0, int numberx);
static void Killer(void);
extern void _lock(void);
extern void loadwall();
extern WSHDR * number_call[5];
extern FLIST *fltop;
extern FLIST *AddToFList(const char* full_name, const char *name, int is_folder);
extern void FindFiles(char *str, int type, int numberx);
char * char_call;
char *loadfile(char *filename);
char CNumber[256];
int CCursor=0;
int CZerro=0;
int CCursorCount=0;
int CCursorVisible=1;
int doc=0;
int run_inbox=0;
int SubMenuCursor=1; //позиция курсора в опциях меню пуска
  int doc2=0;
int CMC = 6;
int Adr_Cur = 0;
//===============================
TDate date; TTime time;
int sett[100];
 MAIN_GUI *super_gui;
/*
 *  24 - Отображение приветствия, выключается при создании конфига
 *
 */









#ifndef NO_LOG
void Tlog (char *string)
{
 if(int_settings[23]==1){
  int logfile;

  if (dir_4) logfile=fopen("4:\\zbin\\HTC\\htc.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  else logfile=fopen("0:\\zbin\\HTC\\htc.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  char *data=malloc(4096);
  GetDateTime(&date,&time);
  sprintf(data,"<%d:%02d:%02d/%02d-%02d-%04d> - %s\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);}
}
#endif

int isfile (const char *names){
int f;
unsigned int err;
 f = fopen(names, A_ReadOnly, P_READ, &err );
   fclose(f,&err);
 if ( f==-1 ) return 0;
 else return 1;

}

IMGHDR *FImage1=0;                                                                 // бекграунд меню
IMGHDR *FImage2=0;                                                                 //
IMGHDR *FImage3=0;                                                                 //
IMGHDR *FImage4=0;                                                                 //
IMGHDR *FImage5=0;                                                                 //
IMGHDR *FImage6=0;                                                                 //
IMGHDR *FImage7=0;                                                                 //
IMGHDR *FImage8=0;                                                                 //
IMGHDR *FImage9=0;                                                                 //
IMGHDR *FImage9a=0;
IMGHDR *FImage9b=0;
IMGHDR *FImage10=0;                                                                 //
IMGHDR *FImage11=0;                                                                 //
IMGHDR *Wall_0=0;                                                                 //
IMGHDR *Wall_1=0;                                                                 //
IMGHDR *Wall_2=0;                                                                 //
IMGHDR *Ico[10];
IMGHDR *BigIco[10];
IMGHDR *SetIco[50];
IMGHDR *Clock[10];

//===============================
int xxl = 0;    //смещение
int aLeft = 0;  //нажат кнопка влево
int zLeft = 1;   //если 1 - последнй была нажата кнопка "влево", если 0 - то "вправо".
int aRight = 0;  //нажата кнопка вправо
int omenu = 0;   // перерисовывать только меню
int  menulanch = 1;
int  dovodka = 0;
int  currentIco = 0; // текущая иконка
int  prewIco = 0; // предыдущая иконка
int n =2;
int uskor=0;
int pres  = 0;
int zzz = 0;
int SetCursor = 0;
int zxinet = 0;
int zxn = 0;
int  Setzxn = 0;
int zxmain = 1;
int zxmainzerro = 0;
int SetExitMenu = 0;
int zxmain_Y = 1;
int zxmain_in = 0;
int zxmain_X = 0;
int focus_on = 1;
int supermod = 0;
int StartMenu = 10;
int StartSubMenu = 11;
int StartInMenu = 12;
int NumberMenu = 13;
int run_exit = 0;
int menu1 = 1;
int menu2 = 2;
int menu3 = 3;
int menu4 = 4;
int menu5 = 5;
int menu6 = 6;
int menu7 = 7;
int menu8 = 8;
int menu9 = 9;
int show_popup = 0; // отображать всплывающие сообщения
int show_ussd = 0;
int timestamp = 0;  // сюда записывается предыдущее значение времени для последующей проверки на изменение.
int netstamp = 0;  // сюда записывается предыдущее значение сетки для последующей проверки на изменение.
int keyup = 1; //клавиша была отпущена после длинного нажатия
int redrawcount = 0;
int menu_dir[20];
int menu_state;
int signal1 = 0;
int net_sdvig_w = 4;
int net_sdvig_h = 3;
int bat_sdvig_w = -25;
int bat_sdvig_h = 1;
int bt_sdvig_w = 0;
int bt_sdvig_h = 0;
int snd_sdvig_w = 0;
int snd_sdvig_h = 0;
int battery = 0;
int network = 0;
RAMNET *net_data;
int draw_all=0; //перерисовать подложку под меню Пуск
int draw_net=0; //перерисовывать только иконбар
int draw_body=1; //перерисовывать все, кроме иконбара
int itemcount = 0; //всего пунктов в меню
int firstrun=0;
int adressmv=0;
int eya = 1;
int dodiWall=0;
//-------------------------------
char *menu_name[9];
int menu_name_true[9];
char *menu_action[9];
int menu_action_true[9];
int main_mod=0;   //тип отображения главного дисплея (по длинной вверх/вниз)
int menu_type[9];
IMGHDR *menu_ico[9];
int menu_ico_true[9];
WSHDR * js;
WSHDR *ussdws;

//================================= НАСТРОЙКИ TouchFLO =============================================
void KeyRun();
void RunMenuPanel();
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


void savesett(){
if (dir_4) {savefile2("4:\\Zbin\\HTC\\main.stt",char_settings,400 );}
else  {savefile2("0:\\Zbin\\HTC\\main.stt",char_settings,400 );}
}

void DrawIdleMenu()
{RunMenuPanel();}

void MenuOnCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
//IPC_REQ shell_ipc={"XTask","Shell", (void *)MENU_GUI_ID};
//	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&shell_ipc);
}

void MenuOnClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  //FastRunMenuActive=0;
  data->gui.state=0;
}

#include "drawmod.h"
#include "draw.h"
#include "input.h"

void MenuOnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{


SetExitMenu = 0;
  data->gui.state=2;
  DisableIDLETMR();// это чтобы эльф не выкл. через 2 минуты
  focus_on = 1;
  currentIco = 0;
  xxl = 21;
  zLeft=1;
  DisableIconBar(1);
  draw_net = 1; draw_body = 1;
  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
  GBS_StartTimerProc(&time_timer, TMR_SECOND, TimerA);
}

void MenuOnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
 // GeneralFunc_flag1(MENU_GUI_ID,1);// Если гуй не наверху, то мы его убиваем нах
  //if (data->gui.state!=2) return;
  //data->gui.state=1;
          SetCursor = 0;
          zxn = 0;
		  zxmain_Y = 1;
          supermod = 0;
          zxmainzerro = 0;
          focus_on = 0;
		  if (show_ussd == 1) {show_ussd = 0; freeUSSD();}

GBS_DelTimer(&key_timer);
GBS_DelTimer(&time_timer);
GBS_DelTimer(&adr_timer);
LoadPD();
Parser();
FSTATS statist;
if (dir_4) {GetFileStats("4:\\Zbin\\HTC\\img\\wallpaper.jpg", &statist, 0);}
else {GetFileStats("0:\\Zbin\\HTC\\img\\wallpaper.jpg", &statist, 0);}
if (!dodiWall) {dodiWall = statist.size;}
if (statist.size != dodiWall) {
dodiWall = statist.size;
DisableIconBar(1);
if (Wall_0->bpnum == 10)mfree(Wall_0->bitmap);mfree(Wall_0);
if (Wall_1->bpnum == 10)mfree(Wall_1->bitmap);mfree(Wall_1);
if (Wall_2->bpnum == 10)mfree(Wall_2->bitmap);mfree(Wall_2);
loadwall();
}}




//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

void KeyRun()  //обработка для перемещения по вкладкам
{if(menulanch){//Если мы еще живы
   if (aLeft == 1 && xxl<=234) currentIco = 8;
   if (aLeft == 1 && xxl<=209) currentIco = 7;
   if (aLeft == 1 && xxl<=182) currentIco = 6;
   if (aLeft == 1 && xxl<=157) currentIco = 5;
   if (aLeft == 1 && xxl<=130) currentIco = 4;
   if (aLeft == 1 && xxl<=104) currentIco = 3;
   if (aLeft == 1 && xxl<=78) currentIco = 2;
   if (aLeft == 1 && xxl<=51) currentIco = 1;
   if (aLeft == 1 && xxl<=24) currentIco = 0;
   if (aRight == 1 && xxl>=0) currentIco = 1;
   if (aRight == 1 && xxl>=26) currentIco = 2;
   if (aRight == 1 && xxl>=53) currentIco = 3;
   if (aRight == 1 && xxl>=80) currentIco = 4;
   if (aRight == 1 && xxl>=106) currentIco = 5;
   if (aRight == 1 && xxl>=132) currentIco = 6;
   if (aRight == 1 && xxl>=159) currentIco = 7;
   if (aRight == 1 && xxl>=184) currentIco = 8;
   if (aRight == 1 && xxl>=211) currentIco = 9;
   dovodka = 0;
  if (aLeft == 1) { if (uskor<8) uskor++; xxl=xxl-(2+uskor/2);  if (xxl<-1) xxl = -1; if (xxl>235) xxl = 235; omenu = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);}
  else if (aRight == 1) { if (uskor<8) uskor++; xxl=xxl+(2+uskor/2);  if (xxl<-1) xxl = -1; if (xxl>235) xxl = 235; omenu = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);}
  else {
    if (xxl!=-1 && xxl!=25 && xxl!=52 && xxl!=79 && xxl!=105 && xxl!=131 && xxl!=158 && xxl!=183 && xxl!=210 && xxl!=235){
      if (xxl>-2 && xxl<236){
        if (zLeft) xxl--; else xxl++;
        dovodka = 1;
   if (zLeft == 1 && xxl<235) currentIco = 8;
   if (zLeft == 1 && xxl<210) currentIco = 7;
   if (zLeft == 1 && xxl<183) currentIco = 6;
   if (zLeft == 1 && xxl<158) currentIco = 5;
   if (zLeft == 1 && xxl<131) currentIco = 4;
   if (zLeft == 1 && xxl<105) currentIco = 3;
   if (zLeft == 1 && xxl<79) currentIco = 2;
   if (zLeft == 1 && xxl<52) currentIco = 1;
   if (zLeft == 1 && xxl<25) currentIco = 0;

   if (zLeft == 0 && xxl>-1) currentIco = 1;
   if (zLeft == 0 && xxl>25) currentIco = 2;
   if (zLeft == 0 && xxl>52) currentIco = 3;
   if (zLeft == 0 && xxl>79) currentIco = 4;
   if (zLeft == 0 && xxl>105) currentIco = 5;
   if (zLeft == 0 && xxl>131) currentIco = 6;
   if (zLeft == 0 && xxl>158) currentIco = 7;
   if (zLeft == 0 && xxl>183) currentIco = 8;
   if (zLeft == 0 && xxl>210) currentIco = 9;

    if (xxl!=-1 && xxl!=25 && xxl!=52 && xxl!=79 && xxl!=105 && xxl!=131 && xxl!=158 && xxl!=183 && xxl!=210 && xxl!=235){
      if (xxl>-2 && xxl<236){
        if (zLeft) xxl--; else xxl++;
}}
GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
}}
draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
}}}

void remanse(){
char *menu_pach;
char *menu_pach_file;
char *prev_pach;
menu_pach = malloc (255);
prev_pach = malloc (255);
//============== ЗАГРУЗКА ТЕКУЩЕГО ПУТИ ================================
if (dir_4) sprintf(menu_pach, "4:\\zbin\\htc\\menus");
else sprintf(menu_pach, "0:\\zbin\\htc\\menus");
for (int i=1; i< (menu_state+1); i++){
sprintf(menu_pach, "%s\\%i.menu",menu_pach, menu_dir[i]);
}
//============== ЗАГРУЗКА ПРЕДЫДУЩЕГО ПУТИ ================================
if (dir_4) sprintf(prev_pach, "4:\\zbin\\htc\\menus");
else sprintf(prev_pach, "0:\\zbin\\htc\\menus");
for (int i=1; i< (menu_state); i++){
sprintf(prev_pach, "%s\\%i.menu",prev_pach, menu_dir[i]);
}
//============== ОПРЕДЕЛЕНИЕ ДОСТУПНЫХ ПУНКТОВ =========================
menu_pach_file = malloc (255);
itemcount = 0;
for (int i=1; i<9; i++)menu_type[i]= 0;

for (int i=1; i<9; i++){
sprintf(menu_pach_file, "%s\\%i.menu", menu_pach, i);
if (isfile(menu_pach_file)) menu_type[i]= 1;
else if (isdir(menu_pach_file, 0)) menu_type[i]= 2;
else break;
itemcount=i;
}
//============== ОЧИСТКА НАЗВАНИЙ ПУНКТОВ ==============================
for (int i=0; i<9; i++){
if (menu_name_true[i]==1){
menu_name_true[i]=0;
mfree(menu_name[i]);};
}
//============== ЗАГРУЗКА НАЗВАНИЙ ПУНКТОВ =============================
sprintf(menu_pach_file, "%s\\%i.name", prev_pach, menu_dir[menu_state]);
if (menu_state>0 && isfile(menu_pach_file))
{menu_name_true[0]=1;
menu_name[0] = loadfile (menu_pach_file);
menu_name[0][lenta-1]=0;
//=========================
menu_name[0][lenta-1]=0;
}else menu_name_true[0]=0;
//============================= =
for (int i=1; i<9; i++){
sprintf(menu_pach_file, "%s\\%i.name", menu_pach, i);
if (menu_type[i]>0 && isfile(menu_pach_file))
{menu_name_true[i]=1;
menu_name[i] = loadfile (menu_pach_file);
menu_name[i][lenta-1]=0;
}else menu_name_true[i]=0;
}
//============== ОЧИСТКА ACTION ПУНКТОВ ==============================
for (int i=1; i<9; i++){if (menu_action_true[i]==1){menu_action_true[i]=0;mfree( menu_action[i]);};}
//============== ЗАГРУЗКА ACTION ПУНКТОВ =============================
for (int i=1; i<9; i++){
sprintf(menu_pach_file, "%s\\%i.menu", menu_pach, i);
if (menu_type[i]>0 && isfile(menu_pach_file))
{menu_action_true[i]=1;
menu_action[i] = loadfile (menu_pach_file);
menu_action[i][lenta-1]=0;
}else menu_action_true[i]=0;
}
//============== ОЧИСТКА ИКОНОК ПУНКТОВ ==============================
for (int i=1; i<9; i++){
if (menu_ico_true[i]==1){
menu_ico_true[i]=0;
mfree(menu_ico[i]->bitmap);
mfree(menu_ico[i]);}
}
//============== ЗАГРУЗКА ИКОНОК ПУНКТОВ =============================
for (int i=1; i<9; i++){
sprintf(menu_pach_file, "%s\\%i.png", menu_pach, i);
if (menu_type[i]>0 && isfile(menu_pach_file)){menu_ico[i] = CreateIMGHDRFromPngFile(menu_pach_file,0);if (menu_ico[i]->bpnum == 10) menu_ico_true[i]=1;}
else menu_ico_true[i]=0;
}
mfree (menu_pach);mfree (prev_pach);
}
int RunAction(const char *s);
void RunBrowser(){RunAction (BM1PIC_FR);}
int RunAction(const char *s)//bm-номер закладки, mode-тип (0-FastRun, 1-IDLE)
{
 if((s)&&strlen(s))
 {


 if (s[0]==':'){
	 //run system enter
	 if (s[1]=='m' || s[1]=='M'){//messages
	 }
	 if (s[1]=='r' || s[1]=='R'){//reboot
	 }
	 if ((s[1]=='b' || s[1]=='B')&& (s[2]=='r' || s[2]=='R'))RunBrowser();//browser


	 if (s[1]=='h' || s[1]=='H'){//help
	 }
	 if (s[1]=='q' || s[1]=='Q'){//quithtc
	 }
	 if (s[1]=='m' || s[1]=='M'){//exit
	 }
	 if (s[1]=='p' || s[1]=='P'){//picoff
	 }
	 if (s[1]=='a' || s[1]=='A'){//about
	 }
	 if (s[1]=='f' || s[1]=='F'){//filemanager
	 }
     if (s[1]=='n' || s[1]=='N'){//none
     }
	 if ((s[1]=='b' || s[1]=='B')&& (s[4]=='k' || s[4]=='K')){//book
     }
	return(0);
	 }
  if ((s[2]=='\\')&&((s[(strlen(s))-3]=='.')||//Проверяем строку на наличие символов '\\' и '.'
     (s[(strlen(s))-4]=='.')||(s[(strlen(s))-5]=='.')))

      {
        WSHDR *ws;
        ws=AllocWS(150);
        str_2ws(ws,s,128);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
        return(1);
      }
  if ((s[2]!='\\')&&(s[(strlen(s))-3]!='.')&&
     (s[(strlen(s))-4]!='.')&&(s[(strlen(s))-5]!='.')&&
     (s[0]!='a')&&(s[0]!='A')&&(s[1]!='0'))

      {

        unsigned int* addr = (unsigned int*)GetFunctionPointer((char*)s);
        if (addr)
        {
          typedef void (*voidfunc)();
          #ifdef NEWSGOLD
            voidfunc pp=(voidfunc)*(addr+4);
          #else
            voidfunc pp=(voidfunc)addr;
          #endif
            SUBPROC((void*)pp);
        }
      }
  if ((s[2]!='\\')&&(s[(strlen(s))-3]!='.')&&
     (s[(strlen(s))-4]!='.')&&(s[(strlen(s))-5]!='.')&&
     ((s[0]=='a')||(s[0]=='A'))&&(s[1]=='0'))

      {
        int entry;
        sscanf(s,"%08X",&entry);
        SUBPROC((void*)entry);
      }
 }
 return(0);
}


int Cont_list(void *ed_gui, int n);
int Cont_list2( int n);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                            //
//                                                                                                                            //
//                                                                                                                            //
//                                                    M E N U O N K E Y                                                       //
//                                                                                                                            //
//                                                                                                                            //
//                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int MenuOnKey(MAIN_GUI *data, GUI_MSG *msg)
{
if (int_settings[24]==1) {int_settings[24]=0; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);}
if (show_ussd == 1) {show_ussd = 0; draw_net = 1; draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID); freeUSSD();} else {
	  if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
  {

}
//================================================================================================================================ supermod == 0
if (supermod == 0){
	if (IsUnlocked()) {


if (msg->gbsmsg->msg==LONG_PRESS)// Если клавиша нажата
{
switch(msg->gbsmsg->submess)
{
case LEFT_SOFT:
if (eya){
DisableIconBar(1);
supermod = StartMenu;
for (int i=0;i<20; i++) menu_dir[i]=0;
menu_state = 0;
draw_all = 1;
remanse();}
draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
return(0);
}}



//-----------------------------------------------------------------------
  if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
  {
    DisableIconBar(1);
      switch(msg->gbsmsg->submess)
      {
        case LEFT_BUTTON:
          DisableIconBar(1);
          SetCursor = 0;
          zxn = 0;
          Setzxn = 0;
          aLeft=1;aRight=0;zLeft=1;pres =1;
          GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
        return(0);

        case RIGHT_BUTTON:
          DisableIconBar(1);
          SetCursor = 0;
          zxn = 0;
          Setzxn = 0;
          aRight=1;aLeft=0;zLeft=0;pres =1;
          GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
          return(0);
      }

  }
//-----------------------------------------------------------------------

 if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {
uskor =0;pres =0;  zzz=0;
    switch(msg->gbsmsg->submess)
    {
     case LEFT_SOFT:  if (run_inbox==1) {RunAction(BM7PIC_FR); run_inbox=0;}
     case RIGHT_SOFT:
if (run_exit==1) {
  DisableIconBar(0);
  IdleMenuActive=0;
  menulanch = 0;
  CloseCSM(main_cms_id);
return(2);
  }





     case RIGHT_BUTTON: {aRight=0;return(0);}
     case LEFT_BUTTON:  {aLeft=0;return(0);}
    }
  }
}


//-----------------------------------------------------------------------
  if (msg->gbsmsg->msg==LONG_PRESS) { // Если длинное зажатие

     switch(msg->gbsmsg->submess)
      {

  case RIGHT_SOFT:
chips.name_to="XTask4";
chips.name_from="Shell";
chips.data=0;
GBS_SendMessage(MMI_CEPID,MSG_IPC,778,&chips);
run_exit=1;
  return(0);

  case '#':
  DisableIconBar(1);

if (keyup > 1) {
if (IsUnlocked())
    {
	KbdLock();
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);
	currentIco = 0;
	xxl = 0;

	}
else KbdUnlock();
  keyup = 0;
draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
  GBS_StartTimerProc(&time_timer, TMR_SECOND, TimerA);
  }

  return(0);

}

  	}


  	if (IsUnlocked()){
 //================================== mod = 0 =========================================================
  if (currentIco == 0){

if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
{switch(msg->gbsmsg->submess){

  case LEFT_SOFT:
   run_inbox=1;
  return(0);
  //====================
  case UP_BUTTON:
  DisableIconBar(1);
  if (zxmainzerro == 0) {zxmainzerro = 0;zxmain = 0;}
  else {
       zxmain--;
       if (zxmain<1) zxmainzerro = 0;
       }
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
  //====================
  case RIGHT_SOFT:
  DisableIconBar(1);
  currentIco = 9;
  xxl = 211;
  zLeft=0;
  dovodka = 1;
  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
 draw_body = 1; DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
  //====================
  case DOWN_BUTTON:
  DisableIconBar(1);
  if (zxmainzerro == 0) {zxmainzerro = 1; zxmain = 1;}
  else {
       zxmain++;
       if (zxmain>2) zxmain = 2;
  }
 draw_body = 1; DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
  //====================
case '1':
case '2':
case '3':
case '4':
case '5':
case '6':
case '7':
case '8':
case '9':
case '0':
case '*':
CZerro=0;
CCursorCount=0; CCursor=0;CNumber[0]=msg->gbsmsg->submess;CNumber[1]=0;
DisableIconBar(1);
supermod = NumberMenu;
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);

}}
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {

   switch(msg->gbsmsg->submess)
      {


   case ENTER_BUTTON:
   if (zxmain == 1 && zxmainzerro>0) ShowCallList(0, 0);
   if (zxmain == 2 && zxmainzerro>0) RunAction(BM8FILE_FR);
  return(0);



   case 11:
   ShowCallList(2, 0);
  return(0);

      }
   }

  if (msg->gbsmsg->msg==LONG_PRESS)// Если клавиша длинно зажата
  {

   switch(msg->gbsmsg->submess)
      {
   case DOWN_BUTTON:
zxmain=0; zxmainzerro = 0; main_mod=1; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
int_settings[22]=1;savesett();
  return(0);
   case UP_BUTTON:
zxmain=0; zxmainzerro = 0; main_mod=0; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
int_settings[22]=0;savesett();
  return(0);


      }
   }
}
  //================================== mod = 1 =========================================================
  if (currentIco == 1){
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {

   switch(msg->gbsmsg->submess)
      {


  //====================
  case RIGHT_SOFT:
  DisableIconBar(1);
 ShowMSG(1,(int)filename);
  wsprintf (e_ws, " Введите сюда что-то");
  sprintf (filename, " Сюда нужно вводить плавно");
  CreateSaveAsDialog();

  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

  case LEFT_SOFT:
  DisableIconBar(1);
  doc = OpenNativeAddressbook(0, 0, 0, 0);
  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

  case ENTER_BUTTON:
  DisableIconBar(1);
char_call=malloc(128);
ws_2str(number_call[Adr_Cur], char_call, wstrlen (number_call[Adr_Cur]));
if(char_call[0]!='*' && char_call[0]!='#') MakeVoiceCall(char_call,0x10, 0x20C0);
else MakeVoiceCall(char_call,0x10,0x2FFF);
mfree(char_call);
draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

   case GREEN_BUTTON:
  DisableIconBar(1);
char_call=malloc(128);
ws_2str(number_call[Adr_Cur], char_call, wstrlen (number_call[Adr_Cur]));
if(char_call[0]!='*' && char_call[0]!='#') MakeVoiceCall(char_call,0x10, 0x20C0);
else MakeVoiceCall(char_call,0x10,0x2FFF);
mfree(char_call);
draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
      }
   }

     if ((msg->gbsmsg->msg==KEY_DOWN))// Если клавиша нажата
  {
   switch(msg->gbsmsg->submess)
      {
  case DOWN_BUTTON:
		if((Adr_Cur<3|| CMC<6) && Adr_Cur<CMC && Adr_Cur<4) Adr_Cur++;
		else if(CMC>5) adressmv++;
	    DisableIconBar(1); draw_body = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
		adr_down=1; adr_up=0;
		GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
  return(0);

  case UP_BUTTON:
	    if((Adr_Cur>1 || adressmv==0) && Adr_Cur>0) Adr_Cur--;
		else  adressmv--;
		if(adressmv<=0) adressmv = 0;
	    DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
		adr_up=1; adr_down=0;
		GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
  return(0);
}}


       if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {
   switch(msg->gbsmsg->submess)
      {
  case DOWN_BUTTON:
  case UP_BUTTON:
	adr_down=0;adr_up=0;
  return(0);


	  }
  }
}
//================================== mod = 4 =========================================================
  if (currentIco == 4){
  if (msg->gbsmsg->msg==KEY_DOWN )// Если клавиша нажата
  {

   switch(msg->gbsmsg->submess)
      {

  case ENTER_BUTTON:
  if (zxn == 0 && Setzxn==1) RunAction(BM1PIC_FR);

  case UP_BUTTON:
  		if (Setzxn == 1) zxn++;
		Setzxn = 1;
		if (zxn>0) zxn = 0;
	    DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  	net_down=0;  net_up=1; 	GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
  return(0);

  case DOWN_BUTTON:
 		if (Setzxn == 1) zxn--;
		Setzxn = 1;
		if (zxn<(-5)) zxn=-5;
	    DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  	net_down=1;  net_up=0; 	GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
  return(0);
      }
   }

   if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {

   switch(msg->gbsmsg->submess)
      {
  case UP_BUTTON:
  case DOWN_BUTTON:
  	net_down=0;  net_up=0;
  return(0);
      }
   }
}
//================================== mod = 8 =========================================================
  if (currentIco == 8){
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {
   switch(msg->gbsmsg->submess)
      {
  case UP_BUTTON:
  DisableIconBar(1);
  if (SetCursor == 0) SetCursor = 1;
  else SetCursor--;
  if (SetCursor < 1) SetCursor = 5;

  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

  case DOWN_BUTTON:
  DisableIconBar(1);
    if (SetCursor == 0) SetCursor = 1;
  else SetCursor++;
   if (SetCursor >5) SetCursor = 1;

  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

   case ENTER_BUTTON:

   if (SetCursor == 1) RunAction(BM8PIC_FR);
   if (SetCursor == 2) RunAction(BM9FILE_FR);
   if (SetCursor == 3) RunAction(BM9PIC_FR);
   if (SetCursor == 4) RunAction(BM10FILE_FR);
   if (SetCursor == 5) RunAction(BM10PIC_FR);

  return(0);
      }
   }
}
}
}
//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == StartMenu
if (supermod == StartMenu){
	if (IsUnlocked()) {

	if ((msg->gbsmsg->msg==KEY_DOWN))// Если клавиша нажата
  {
    DisableIconBar(1);
   switch(msg->gbsmsg->submess)
      {

        case LEFT_SOFT:
        case '*':
        case '#':
        case '0':
		if (run_inbox==0){
  DisableIconBar(1);
supermod = 0;
SetExitMenu = 1;
 zxmain_Y = 1; zxmain_X = 0;
  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);

        return(0);
}}}



	if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {
    DisableIconBar(1);
   switch(msg->gbsmsg->submess)
      {

case LEFT_BUTTON:
    DisableIconBar(1);

	if (menu_state>0){
		zxmain_Y = menu_dir[menu_state];
		menu_dir[menu_state] = 0;
		menu_state--;
		remanse();
		SetExitMenu = 1;
		draw_all=1;
		}
	else{
		supermod = 0;
		SetExitMenu = 1;
		zxmain_Y = 1; zxmain_X = 0;
		}

	draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    return(0);

case RIGHT_SOFT:
    DisableIconBar(1);
	if (zxmain_Y) {supermod = StartSubMenu; SubMenuCursor=0;
	draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);}
    return(0);
//------------------------------------------

case ENTER_BUTTON:
    DisableIconBar(1);
	if (menu_state<20 && menu_type[zxmain_Y]==2) {

	menu_state++;
	menu_dir[menu_state] = zxmain_Y;
	remanse();
	SetExitMenu = 1;
	draw_all = 1;
	zxmain_Y = 1;
	}

	else if (menu_type[zxmain_Y]==1) {
    if (menu_action_true[zxmain_Y]!=0) RunAction(menu_action[zxmain_Y]);
	Tlog (menu_action[zxmain_Y]);
	supermod = 0;
    SetExitMenu = 1;
    zxmain_Y = 1; zxmain_X = 0;
	}


    draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    return(0);

//------------------------------------------

case UP_BUTTON:
   DisableIconBar(1);
   if (itemcount>0){
   zxmain_Y--;
   if (zxmain_Y<1) zxmain_Y = itemcount;
   draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);}
   return(0);

//------------------------------------------

case DOWN_BUTTON:
   DisableIconBar(1);
   if (itemcount>0){
   zxmain_Y++;
   if (zxmain_Y>itemcount) zxmain_Y = 1;
   draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);}
   return(0);
}}


if (msg->gbsmsg->msg==KEY_UP){switch(msg->gbsmsg->submess){// Если клавиша отпущена
	case LEFT_SOFT:  if (run_inbox==1) {run_inbox=0;}
}}




}}
//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == StartSubMenu
if (supermod == StartSubMenu){
	if (IsUnlocked()) {

	if ((msg->gbsmsg->msg==KEY_DOWN))// Если клавиша нажата
  {
    DisableIconBar(1);
   switch(msg->gbsmsg->submess)
      {
        case LEFT_SOFT:
		case LEFT_BUTTON:
        case '*':
        case '#':
        case '0':
  DisableIconBar(1);
supermod = 0;
SetExitMenu = 1;
 zxmain_Y = 1; zxmain_X = 0;
  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
        return(0);

        case RIGHT_SOFT:
  DisableIconBar(1);
supermod = StartMenu;
  draw_all=1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
        return(0);
}}



	if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {
    DisableIconBar(1);
   switch(msg->gbsmsg->submess)
      {

//------------------------------------------

case ENTER_BUTTON:
    DisableIconBar(1);
	if (menu_state<20 && menu_type[zxmain_Y]==2) {

	menu_state++;
	menu_dir[menu_state] = zxmain_Y;
	remanse();
	SetExitMenu = 1;
	draw_all = 1;
	zxmain_Y = 1;
	}

	else if (menu_type[zxmain_Y]==1) {
    if (menu_action_true[zxmain_Y]!=0) RunAction(menu_action[zxmain_Y]);
	Tlog (menu_action[zxmain_Y]);
	supermod = 0;
    SetExitMenu = 1;
    zxmain_Y = 1; zxmain_X = 0;
	}


    draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    return(0);

//------------------------------------------

case UP_BUTTON:
   DisableIconBar(1);
SubMenuCursor--; if (SubMenuCursor<0) SubMenuCursor=3;
   draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
      return(0);

//------------------------------------------

case DOWN_BUTTON:
   DisableIconBar(1);
SubMenuCursor++; if (SubMenuCursor>3) SubMenuCursor=0;
   draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
   return(0);
}}

}}

//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == NumberMenu
if (supermod == NumberMenu){
	if (IsUnlocked()) {
if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
{DisableIconBar(1);
   switch(msg->gbsmsg->submess)
      {
 //------------------------------------------

case LEFT_SOFT:
DisableIconBar(1);
supermod = 0;
SetExitMenu = 1;
 zxmain_Y =1; zxmain_X = 3;
  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);

        return(0);

case RIGHT_SOFT:
  if (CCursor > 1) {
CCursorCount--; CCursor--; CNumber[CCursor]=0;
draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
return(0);
  } else {
 DisableIconBar(1);
supermod = 0;
SetExitMenu = 1;
 zxmain_Y = 1; zxmain_X = 0;
  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
}}}


if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
{switch(msg->gbsmsg->submess){

case GREEN_BUTTON:
if(CNumber[0]!='*' && CNumber[0]!='#') MakeVoiceCall(CNumber,0x10, 0x20C0);
else MakeVoiceCall(CNumber,0x10,0x2FFF);
return(0);




case '1':
case '2':
case '3':
case '4':
case '5':
case '6':
case '7':
case '8':
case '9':
case '0':
case '*':
case '#':
  if (CCursorCount<78){
CNumber[CCursor]=msg->gbsmsg->submess;CCursorCount++; CCursor++;CNumber[CCursor]=0;
DisableIconBar(1);
if (CNumber[0]=='0' && CZerro==0) CNumber[0]='+';
if (CNumber[0]=='+' && CNumber[1]=='0') {CNumber[0]='0';CNumber[1]=0;CCursorCount=1; CCursor=1; CZerro=1;}
draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);

 }
}}


}}
//===================================================================================================
}
  return(0);
  }


//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//======================================================================================
//======================================================================================       Конец Функций МЕНЮ
//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =













//=======================================================================================


void MenuOnDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{ extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}
int method8(void){return(0);}
int method9(void){return(0);}


const void * const gui_methods_3[11]={
  (void *)MenuOnRedraw,  //Redraw
  (void *)MenuOnCreate,  //Create
  (void *)MenuOnClose,	  //Close
  (void *)MenuOnFocus,	  //Focus
  (void *)MenuOnUnfocus, //Unfocus
  (void *)MenuOnKey,     //OnKey
  0,
  (void *)MenuOnDestroy, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void RunMenuPanel()
{
   // if(!IsNoJava())
	draw_net = 1; draw_body = 1;
    MAIN_GUI *menu_gui=malloc(sizeof(MAIN_GUI));
    zeromem(menu_gui,sizeof(MAIN_GUI));
    menu_gui->gui.canvas=(void *)(&Canvas);
    menu_gui->gui.methods=(void *)gui_methods_3;
    menu_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
    MENU_GUI_ID=CreateGUI(menu_gui);
/**/	GUI_ID_STR= &MENU_GUI_ID;
  chips.name_to="XTask4";
  chips.name_from="Shell";
  chips.data=GUI_ID_STR;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,777,&chips);

    DisableIconBar(1);
    lanchPD=1;
    Tlog ("Запущен гуи");
}


