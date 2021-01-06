// Меню
//#include "swilib.h"
//#include "menus.h"
//#include "fastrun.c"
//#include "keys.h"
int countcall=0;
WSHDR * ucall[4];
int scall[4];

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

MAIN_GUI *zerro_gui;
static IPC_REQ chips;





extern int DrwPngImg(IMGHDR *img, int x, int y);

extern char *coloc;
extern void TimerA();
extern void adr_progress();
extern int dir_4;
extern int ConstructList(void);
extern int Play5(int sm0, int cursor);
extern int Play6(int sm0, int numberx, int cursor);
static void Killer(void);
extern void _lock(void);
extern void loadwall();
extern WSHDR * number_call[5];
extern WSHDR * number_call1[5];
extern WSHDR * number_call2[5];
extern WSHDR * number_call3[5];

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
int xxxl=-20;
int allsms=0;
//===============================
TDate date; TTime time;
int sett[100];
 MAIN_GUI *super_gui;
/*
 *  24 - Отображение приветствия, выключается при создании конфига
 *
 */



   void DIconbar(int yui){
           if(MD6 || lui_bob<10) DisableIconBar(yui);
   }





#ifndef NO_LOG
void Tlog (char *string)
{
 if(int_settings[23]==1){
  int logfile;

  if (dir_4) logfile=fopen("4:\\zbin\\HTC\\htc.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  else logfile=fopen("0:\\zbin\\HTC\\htc.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  char *data=(char *)malloc(4096);
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
IMGHDR *PIco[11];
int ust9[11];  // список видимости вкладок
int rasp9[11]; // список всех отображаемых вкладок
int xxc9[11];  // точки останова для прокрутки
int stop9[11]; // список всех активных точек останова для прокрутки
int stop8=0;   // последняя точка останова
int serv=0;    //количество активных вкладок
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
int zxmain = 0;
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
int ExitMenu = 14;
int CallMenu = 15;
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
int GTY=2;
int  playdrawmod=1;
int extblock=0;    // после каждой перерисовки, сюда заносится состояние клавиатурной блокировки,
                                    // чтобы определить, что пользователь разблокировал слайдером;                                          0-разблокирована, 1 - заблокирована.
int tiper=0; // счетчик, сбрасывается при нажатии кнопки, необходим для автоблокировки клавы.
int sey=0; //всплывающее сообщение
char *seytitle=0;
char *seytext=0;
//-------------------------------
char *menu_name[9];
int menu_name_true[9];
char *menu_action[9];
int menu_action_true[9];

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

void suboff(){
  CloseCSM(main_cms_id);
  if(GTY==3) RebootPhone();
}

void MenuOnClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (GetCPUClock()>100)  SetCpuClockLow(2);
MENU_GUI_ID=0;// ИД гуя меню
  //FastRunMenuActive=0;
  data->gui.state=0;
  UpdateScreen() ;
}

#include "drawmod.h"
#include "draw.h"
#include "input.h"

void MenuOnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  if (GetCPUClock()<200)  SetCpuClockTempHi(2);
if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  SetExitMenu = 0;
  data->gui.state=2;
  DisableIDLETMR();// это чтобы эльф не выкл. через 2 минуты

  focus_on = 1;
  currentIco = rasp9[0];
  xxl = 21;
  zLeft=1;
  DIconbar(1);
  draw_net = 1; draw_body = 1;
  if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
  if (IsUnlocked())  GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);
  if(!inExit){}inExit=0;
}

void MenuOnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
           if (GetCPUClock()>100)  SetCpuClockLow(2);
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
  MString SID;
  SID=BM3FILE_FR;  SID=SID+"wallpaper.jpg";
  GetFileStats(SID.stri, &statist, 0);
GBS_StartTimerProc(&idle_timer, TMR_SECOND/2, UpdateScreen); 
if (!dodiWall) {dodiWall = statist.size;}
if (statist.size != dodiWall) {
dodiWall = statist.size;
DIconbar(1);
if (Wall_0->bpnum == 10)mfree(Wall_0->bitmap);mfree(Wall_0);
if (Wall_1->bpnum == 10)mfree(Wall_1->bitmap);mfree(Wall_1);
if (Wall_2->bpnum == 10)mfree(Wall_2->bitmap);mfree(Wall_2);
loadwall();
}}




//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//====================================================================================== = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

void KeyRun()  //обработка для перемещения по вкладкам
{
if(menulanch){//Если мы еще живы
if (GetCPUClock()<200)  SetCpuClockTempHi(2);
if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  if(xxl>stop8) xxl = stop8;
   if (aLeft == 1 && xxl<=234 ) currentIco = rasp9[8];
   if (aLeft == 1 && xxl<=209) currentIco = rasp9[7];
   if (aLeft == 1 && xxl<=182) currentIco = rasp9[6];
   if (aLeft == 1 && xxl<=157) currentIco = rasp9[5];
   if (aLeft == 1 && xxl<=130) currentIco = rasp9[4];
   if (aLeft == 1 && xxl<=104) currentIco = rasp9[3];
   if (aLeft == 1 && xxl<=78) currentIco = rasp9[2];
   if (aLeft == 1 && xxl<=51) currentIco = rasp9[1];
   if (aLeft == 1 && xxl<=24) currentIco = rasp9[0];
   if (aRight == 1 && xxl>=0) currentIco = rasp9[1];
   if (aRight == 1 && xxl>=26) currentIco = rasp9[2];
   if (aRight == 1 && xxl>=53) currentIco = rasp9[3];
   if (aRight == 1 && xxl>=80) currentIco = rasp9[4];
   if (aRight == 1 && xxl>=106) currentIco = rasp9[5];
   if (aRight == 1 && xxl>=132) currentIco = rasp9[6];
   if (aRight == 1 && xxl>=159) currentIco = rasp9[7];
   if (aRight == 1 && xxl>=184) currentIco = rasp9[8];
   if (aRight == 1 && xxl>=211) currentIco = rasp9[9];
   dovodka = 0;
  if (aLeft == 1) { if (uskor<8) uskor++; xxl=xxl-(2+uskor/2);  if (xxl<-1) xxl = -1; if (xxl>235) xxl = 235; omenu = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);}
  else if (aRight == 1) { if (uskor<8) uskor++; xxl=xxl+(2+uskor/2);  if (xxl<-1) xxl = -1; if (xxl>235) xxl = 235; omenu = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);}
  else {
    if (xxl!=-1 && xxl!=25 && xxl!=52 && xxl!=79 && xxl!=105 && xxl!=131 && xxl!=158 && xxl!=183 && xxl!=210 && xxl!=235){
      if (xxl>=-1 && xxl<=stop8){
        if (zLeft) xxl--; else xxl++;
        dovodka = 1;
     if(xxl>stop8) xxl = stop8;
   if (zLeft == 1 && xxl<235) currentIco = rasp9[8];
   if (zLeft == 1 && xxl<210) currentIco = rasp9[7];
   if (zLeft == 1 && xxl<183) currentIco = rasp9[6];
   if (zLeft == 1 && xxl<158) currentIco = rasp9[5];
   if (zLeft == 1 && xxl<131) currentIco = rasp9[4];
   if (zLeft == 1 && xxl<105) currentIco = rasp9[3];
   if (zLeft == 1 && xxl<79) currentIco = rasp9[2];
   if (zLeft == 1 && xxl<52) currentIco = rasp9[1];
   if (zLeft == 1 && xxl<25) currentIco = rasp9[0];

   if (zLeft == 0 && xxl>-1) currentIco = rasp9[1];
   if (zLeft == 0 && xxl>25) currentIco = rasp9[2];
   if (zLeft == 0 && xxl>52) currentIco = rasp9[3];
   if (zLeft == 0 && xxl>79) currentIco = rasp9[4];
   if (zLeft == 0 && xxl>105) currentIco = rasp9[5];
   if (zLeft == 0 && xxl>131) currentIco = rasp9[6];
   if (zLeft == 0 && xxl>158) currentIco = rasp9[7];
   if (zLeft == 0 && xxl>183) currentIco = rasp9[8];
   if (zLeft == 0 && xxl>210) currentIco = rasp9[9];

    if (xxl!=-1 && xxl!=25 && xxl!=52 && xxl!=79 && xxl!=105 && xxl!=131 && xxl!=158 && xxl!=183 && xxl!=210 && xxl!=235){
      if (xxl>=-1 && xxl<=stop8){
        if (zLeft) xxl--; else xxl++;
          if(xxl>stop8) xxl = stop8;
}}
if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
}} else  {if (GetCPUClock()<200)  SetCpuClockTempHi(2); if (GetCPUClock()<200)  SetCpuClockTempHi(2);}
draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
}}}

void remanse(){
char *menu_pach;
char *menu_pach_file;
char *prev_pach;
menu_pach = (char *)malloc (255);
prev_pach = (char *)malloc (255);
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
menu_pach_file = (char *)malloc (255);
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
//==============================
menu_name[0][lenta-1]=0;
}else menu_name_true[0]=0;
//==============================
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


//====================================================================================================
//=======================================                    RunAction                    ============
//====================================================================================================

int RunAction(const char *s);
//---------------------------------------------------
void RunBrowser(){RunAction (BM1PIC_FR);}
//---------------------------------------------------
void RunExit(){
  GTY=2;
 DIconbar(1);
 UpdateScreen();
 supermod = ExitMenu;
 SetExitMenu = 1;
 zxmain_Y = 1;  zxmain_X = 0;
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
}
//---------------------------------------------------
 void Quit(){
DIconbar(0);
IdleMenuActive=0;
menulanch = 0;
chips.name_to="XTask4";
chips.name_from="Shell";
chips.data=0;
GBS_SendMessage(MMI_CEPID,MSG_IPC,778,&chips);
run_exit=1;
CloseCSM(main_cms_id);
}
//---------------------------------------------------
void boot(){
Quit();
RebootPhone();
}
//---------------------------------------------------
 void settings(){
if (isfile("4:\\ZBin\\etc\\MD_TouchFLO.bcfg")) RunAction ("4:\\ZBin\\etc\\MD_TouchFLO.bcfg");
else  RunAction ("0:\\ZBin\\etc\\MD_TouchFLO.bcfg");
}
//---------------------------------------------------
void show0(){
strcpy(seytitle,"Ошибка!");
strcpy(seytext,"Произошла неизвестная ошибка, попробуйте переустановить приложение.");
sey=2;
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
}
//---------------------------------------------------
void show1(const char *s){
  strcpy(seytitle,"Сообщение:");
strcpy(seytext, s);
//sprintf(seytext,"%d", s);
sey=2;
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
}
//---------------------------------------------------
void sound1(){
int *Ring=(int*)RamRingtoneStatus(); 
if (*Ring==1) Ringtones_SetState(0); 
else Ringtones_SetState(1);
draw_net = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
}
//---------------------------------------------------
int RunAction(const char *s)//bm-номер закладки, mode-тип (0-FastRun, 1-IDLE)
{
 if((s)&&strlen(s))
 { if (s[0]==':'){
	 //run system enter
	 if (s[1]=='m' || s[1]=='M'){} //messages
	 if ((s[1]=='s' || s[1]=='S')&& (s[2]=='e' || s[2]=='E')){settings();return(0);}		//settings
     if ((s[1]=='s' || s[1]=='S')&& (s[2]=='h' || s[2]=='H')){show1(s+6);return(0);}		//show
     if ((s[1]=='s' || s[1]=='S')&& (s[2]=='o' || s[2]=='O')){sound1();return(0);}			//sound
	 if ((s[1]=='e' || s[1]=='E')&& (s[2]=='r' || s[2]=='R')){show0();return(0);}			//error
	 if ((s[1]=='e' || s[1]=='E')&& (s[2]=='x' || s[2]=='X')){RunExit(); return(0);}		//exit    
	 if ((s[1]=='r' || s[1]=='R')&& (s[2]=='e' || s[2]=='E')){boot();return(2);}			//reboot
	 if ((s[1]=='b' || s[1]=='B')&& (s[2]=='r' || s[2]=='R')){RunBrowser();return(0);}		//browser
	 if ((s[1]=='h' || s[1]=='H')&& (s[2]=='e' || s[2]=='E')){return(0);}					//help
	 if ((s[1]=='q' || s[1]=='Q')&& (s[2]=='u' || s[2]=='U')){Quit();return(2);}			//quithtc
	 if ((s[1]=='a' || s[1]=='A')&& (s[2]=='b' || s[2]=='B')){return(0);}					//about
	 if ((s[1]=='f' || s[1]=='F')&& (s[2]=='m' || s[2]=='M')){return(0);}					//fmg
	 if ((s[1]=='b' || s[1]=='B')&& (s[4]=='k' || s[4]=='K')){return(0);}					//book
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
        return(0);
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
 } else show1("Неизвестная команда!\nПроверьте правильность ввода команды..");
 return(0);
}
//====================================================================================================
//====================================================================================================
//====================================================================================================

int Cont_list(void *ed_gui, int n);
int Cont_list2( int n);




void callselect(){
         countcall=0;
         if(number_call[Adr_Cur]){countcall++; ucall[countcall-1]=number_call[Adr_Cur]; scall[countcall-1]=0;}
         if(number_call1[Adr_Cur]){countcall++; ucall[countcall-1]=number_call1[Adr_Cur]; scall[countcall-1]=1;}
         if(number_call2[Adr_Cur]){countcall++; ucall[countcall-1]=number_call2[Adr_Cur]; scall[countcall-1]=2;}
         if(number_call3[Adr_Cur]){countcall++; ucall[countcall-1]=number_call3[Adr_Cur]; scall[countcall-1]=3;}
         supermod =CallMenu;
         GTY=2;
         DIconbar(1);
         SetExitMenu = 1;
         zxmain_Y = 1;  zxmain_X = 0;
         draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
}








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                            //
//                                                                                                                            //
//                                                                                                                            //
//                                                    M E N U O N K E Y                                             //
//                                                                                                                            //
//                                                                                                                            //
//                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int MenuOnKey(MAIN_GUI *data, GUI_MSG *msg)
{
tiper=0;     GBS_DelTimer(&idle_timer);  //убиваем таймер проверки
if (int_settings[24]==1) {int_settings[24]=0; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);} else
if (msg->gbsmsg->msg==KEY_DOWN && sey>0) {sey=0; show_ussd = 0; draw_net = 1; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);} else
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
DIconbar(1);
playdrawmod=1;
supermod = StartMenu;
for (int i=0;i<20; i++) menu_dir[i]=0;
menu_state = 0;
draw_all = 1;
remanse();}
draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
return(0);

        case RIGHT_BUTTON:
        case LEFT_BUTTON:
         if (xxl==xxxl){ aLeft=0;aRight=0;correctDraw();}
         else xxxl=xxl;
        return(0);




}}



//-----------------------------------------------------------------------

  if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
  {
    DIconbar(1);
      switch(msg->gbsmsg->submess)
      {
        case LEFT_BUTTON:
          DIconbar(1);
          SetCursor = 0;
          zxn = 0;
          Setzxn = 0;
          aLeft=1;aRight=0;zLeft=1;pres =1;
          if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
        return(0);

        case RIGHT_BUTTON:
          DIconbar(1);
          SetCursor = 0;
          zxn = 0;
          Setzxn = 0;
          aRight=1;aLeft=0;zLeft=0;pres =1;
          if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
          return(0);
      }

  }
//-----------------------------------------------------------------------

 if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {
uskor =0;pres =0;  zzz=0;
    switch(msg->gbsmsg->submess)
    {
     case LEFT_SOFT:  if (run_inbox==1 &&  currentIco == 0) {RunAction(BM7PIC_FR); run_inbox=0;}
                                           if (run_inbox==1 &&  currentIco == 1) {DIconbar(1);  doc = OpenNativeAddressbook(0, 0, 0, 0);   draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);run_inbox=0;}
                                           if (run_inbox==1 &&  currentIco == 2) {RunAction(BM11FILE_FR); run_inbox=0;}
                                           if (run_inbox==1 &&  currentIco == 2) {RunAction(":browser"); run_inbox=0;}
     return(0);




     case RIGHT_BUTTON:
     case LEFT_BUTTON:  {aLeft=0;aRight=0;  if (GetCPUClock()>100)  SetCpuClockLow(2);return(0);}
    }
  }
}


//-----------------------------------------------------------------------
  if (msg->gbsmsg->msg==LONG_PRESS) { // Если длинное зажатие

     switch(msg->gbsmsg->submess)
      {

  case '#':
  DIconbar(1);

if (keyup == 1) {
if (IsUnlocked())
    {
	KbdLock();
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);
	currentIco = rasp9[0];
	xxl = 0;

	}
else KbdUnlock();
  keyup = 0;
    focus_on = 1;
  currentIco = rasp9[0];
  xxl = 21;
  zLeft=1;


  focus_on = 1;
  currentIco = rasp9[0];
  xxl = 21;
  zLeft=1;
  draw_net = 1; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
  if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
  if (IsUnlocked())  GBS_StartTimerProc(&time_timer, TMR_SECOND*30, TimerA);
  //======================================================================================================================================================
  }

  return(0);

}
}
if (msg->gbsmsg->msg==KEY_UP) { // Если длинное зажатие

     switch(msg->gbsmsg->submess)
      {

  case '#':
keyup = 1;
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
  DIconbar(1);
  if (zxmainzerro == 0) {zxmainzerro = 0;zxmain = 0;}
  else {
       zxmain--;
       if (zxmain<1) zxmainzerro = 0;
       }
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
  //====================
  case RIGHT_SOFT:
  DIconbar(1);
  currentIco = rasp9[9];
  xxl = 211;
  zLeft=0;
  dovodka = 1;
  if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
 draw_body = 1; DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);
  //====================
  case DOWN_BUTTON:
  DIconbar(1);
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
DIconbar(1);
supermod = NumberMenu;
 draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);

}}
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {

   switch(msg->gbsmsg->submess)
      {


   case ENTER_BUTTON:
   if (zxmain == 1 && zxmainzerro>0) ShowCallList(0, 0);
   if (zxmain == 2 && zxmainzerro>0) RunAction(BM7FILE_FR);
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
zxmain=0; zxmainzerro = 0; int_settings[22]=1; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
int_settings[22]=1;savesett();
  return(0);
   case UP_BUTTON:
zxmain=0; zxmainzerro = 0; int_settings[22]=0; draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
int_settings[22]=0;savesett();
  return(0);


      }
   }
}
  //================================== mod = 1 =========================================================
  if (currentIco == 1){

  if (msg->gbsmsg->msg==KEY_DOWN )// Если клавиша нажата
  {

   switch(msg->gbsmsg->submess)
      {

                 case LEFT_SOFT:
                  run_inbox=1;
                  return(0);
}}


  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
  {

   switch(msg->gbsmsg->submess)
      {


  //====================
  case RIGHT_SOFT:/*
  DIconbar(1);
 ShowMSG(1,(int)filename);
  wsprintf (e_ws, " Введите сюда что-то");
  sprintf (filename, " Сюда нужно вводить плавно");
  CreateSaveAsDialog();

  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  */
  return(0);



  case ENTER_BUTTON:
  case GREEN_BUTTON:
  DIconbar(1);
char_call=(char *)malloc(128);
if(number_call[Adr_Cur] && !number_call1[Adr_Cur] && !number_call2[Adr_Cur] && !number_call3[Adr_Cur]){ws_2str(number_call[Adr_Cur], char_call, wstrlen (number_call[Adr_Cur]));}
else if(!number_call[Adr_Cur] && number_call1[Adr_Cur] && !number_call2[Adr_Cur] && !number_call3[Adr_Cur]){ws_2str(number_call1[Adr_Cur], char_call, wstrlen (number_call1[Adr_Cur]));}
else if(!number_call[Adr_Cur] && !number_call1[Adr_Cur] && number_call2[Adr_Cur] && !number_call3[Adr_Cur]){ws_2str(number_call2[Adr_Cur], char_call, wstrlen (number_call2[Adr_Cur]));}
else if(!number_call[Adr_Cur] && !number_call1[Adr_Cur] && !number_call2[Adr_Cur] && number_call3[Adr_Cur]){ws_2str(number_call3[Adr_Cur], char_call, wstrlen (number_call3[Adr_Cur]));}
else {callselect(); return(0);}
if(char_call[0]!='*' && char_call[0]!='#') MakeVoiceCall(char_call,0x10, 0x20C0); else MakeVoiceCall(char_call,0x10,0x2FFF);
mfree(char_call);draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
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
	    DIconbar(1); draw_body = 1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
		adr_down=1; adr_up=0;
		if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
                  if (GetCPUClock()<200)  SetCpuClockTempHi(2);if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  return(0);

  case UP_BUTTON:
	    if((Adr_Cur>1 || adressmv==0) && Adr_Cur>0) Adr_Cur--;
		else  adressmv--;
		if(adressmv<=0) adressmv = 0;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
		adr_up=1; adr_down=0;
		if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
if (GetCPUClock()<200)  SetCpuClockTempHi(2);if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  return(0);
}}


       if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {
   switch(msg->gbsmsg->submess)
      {
  case DOWN_BUTTON:
  case UP_BUTTON:
	adr_down=0;adr_up=0;  GBS_DelTimer(&adr_timer); if (GetCPUClock()>100)  SetCpuClockLow(2);
  return(0);


	  }
  }
}

//================================== mod = 2 =========================================================
  if (currentIco == 2){
  if (msg->gbsmsg->msg==KEY_DOWN )// Если клавиша нажата
  {

   switch(msg->gbsmsg->submess)
      {

                 case LEFT_SOFT:
                  run_inbox=1;
                  return(0);
}}}


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
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  	net_down=0;  net_up=1; 	if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
          if (GetCPUClock()<200)  SetCpuClockTempHi(2);
         if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  return(0);

  case DOWN_BUTTON:
 		if (Setzxn == 1) zxn--;
		Setzxn = 1;
		if (zxn<(-5)) zxn=-5;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  	net_down=1;  net_up=0; 	if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/5, adr_progress);
         if (GetCPUClock()<200)  SetCpuClockTempHi(2);
         if (GetCPUClock()<200)  SetCpuClockTempHi(2);
  return(0);
      }
   }

   if (msg->gbsmsg->msg==KEY_UP)// Если клавиша отпущена
  {

   switch(msg->gbsmsg->submess)
      {
  case UP_BUTTON:
  case DOWN_BUTTON:
  	net_down=0;  net_up=0; GBS_DelTimer(&adr_timer);
         if (GetCPUClock()>100)  SetCpuClockLow(2);

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
  DIconbar(1);
  if (SetCursor == 0) SetCursor = 1;
  else SetCursor--;
  if (SetCursor < 1) SetCursor = 5;

  draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return(0);

  case DOWN_BUTTON:
  DIconbar(1);
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
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {
                                             case LEFT_SOFT:
                                             case '*':
                                             case '#':
                                             case '0':
                                                      if (run_inbox==0){
                                                               DIconbar(1);
                                                               supermod = 0;
                                                               SetExitMenu = 1;
                                                               zxmain_Y = 1; zxmain_X = 0;
                                                               draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);

                                                               return(0);
                                                      }
                                    }
                           }

                           if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
                           {
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {

                                             case LEFT_BUTTON:
                                                      DIconbar(1);
                                                      if (menu_state>0){
                                                               zxmain_Y = menu_dir[menu_state];
                                                               menu_dir[menu_state] = 0;
                                                               menu_state--;
                                                               remanse();
                                                               SetExitMenu = 1;
                                                               draw_all=1;
                                                               playdrawmod=1;
                                                      }
                                                      else{
                                                               supermod = 0;
                                                               SetExitMenu = 1;
                                                               zxmain_Y = 1; zxmain_X = 0;
                                                      }

                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case RIGHT_SOFT:
                                                      DIconbar(1);
                                                      if (zxmain_Y) {playdrawmod=1;supermod = StartSubMenu; SubMenuCursor=0; draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);}
                                                      return(0);


                                             case ENTER_BUTTON:
                                                      DIconbar(1);
                                                      if (menu_state<20 && menu_type[zxmain_Y]==2) {
                                                               menu_state++;
                                                               menu_dir[menu_state] = zxmain_Y;
                                                               remanse();
                                                               SetExitMenu = 1;
                                                               draw_all = 1;
                                                               zxmain_Y = 1;
                                                               playdrawmod=1;
                                                      }
                                                      else if (menu_type[zxmain_Y]==1) {
                                                               if (menu_action_true[zxmain_Y]!=0) RunAction(menu_action[zxmain_Y]);
                                                               Tlog (menu_action[zxmain_Y]);
                                                               supermod = 0;
                                                               SetExitMenu = 1;
                                                               zxmain_Y = 1; zxmain_X = 0;playdrawmod=1;
                                                      }
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case UP_BUTTON:
                                                      DIconbar(1);
                                                      if (itemcount>0){
                                                               zxmain_Y--;
                                                               if (zxmain_Y<1) zxmain_Y = itemcount;
                                                               draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      }
                                                      return(0);

                                             case DOWN_BUTTON:
                                                      DIconbar(1);
                                                      if (itemcount>0){
                                                               zxmain_Y++;
                                                               if (zxmain_Y>itemcount) zxmain_Y = 1;
                                                               draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      }
                                                      return(0);
                                    }
                           }


                           if (msg->gbsmsg->msg==KEY_UP){
                                    switch(msg->gbsmsg->submess){// Если клавиша отпущена
                                             case LEFT_SOFT:  if (run_inbox==1) {run_inbox=0;}
                                    }

                           }
                  }
         }
//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == StartSubMenu
         if (supermod == StartSubMenu){
                  if (IsUnlocked()) {

                           if ((msg->gbsmsg->msg==KEY_DOWN))// Если клавиша нажата
                           {
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {
                                             case LEFT_SOFT:
                                             case LEFT_BUTTON:
                                             case '*':
                                             case '#':
                                             case '0':
                                                      DIconbar(1);
                                                      supermod = 0;
                                                      SetExitMenu = 1;
                                                      zxmain_Y = 1; zxmain_X = 0;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                     return(0);

                                             case RIGHT_SOFT:
                                                      DIconbar(1);
                                                      playdrawmod=1;
                                                      supermod = StartMenu;
                                                      draw_all=1;draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                     return(0);
                                    }
                           }



                           if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
                           {
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {
                                             case ENTER_BUTTON:
                                                      DIconbar(1);
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

                                             case UP_BUTTON:
                                                      DIconbar(1);
                                                      SubMenuCursor--; if (SubMenuCursor<0) SubMenuCursor=3;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case DOWN_BUTTON:
                                                      DIconbar(1);
                                                      SubMenuCursor++; if (SubMenuCursor>3) SubMenuCursor=0;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);
                                    }
                           }
                  }
         }

//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == NumberMenu

         if (supermod == NumberMenu){
                  if (IsUnlocked()) {

                           if ((msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
                           {
                                    DIconbar(1);
                                if(CCursor <= 1){
                                    switch(msg->gbsmsg->submess)
                                    {
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
                                                      DIconbar(1);
                                                      supermod = 0;
                                                      SetExitMenu = 1;
                                                      zxmain_Y = 1;  zxmain_X = 0;
                                                      draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
                                    }
                                    switch(msg->gbsmsg->submess)
                                    {
                                             case '1':  return RunAction(GK1);
                                             case '2': return RunAction(GK2);
                                             case '3': return RunAction(GK3);
                                             case '4': return RunAction(GK4);
                                             case '5': return RunAction(GK5);
                                             case '6': return RunAction(GK6);
                                             case '7': return RunAction(GK7);
                                             case '8': return RunAction(GK8);
                                             case '9': return RunAction(GK9);
                                             case '0': return RunAction(GK10);
                                             case '*':  return RunAction(GK11);
                                    }
                                }
                           }
                           //==============================================================

                           if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))// Если клавиша нажата или зажата
                           {
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                   {


                                    case LEFT_SOFT:
                                             DIconbar(1);
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
                                                      DIconbar(1);
                                                      supermod = 0;
                                                      SetExitMenu = 1;
                                                      zxmain_Y = 1; zxmain_X = 0;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                             }
                           }
                           }


                           if (msg->gbsmsg->msg==KEY_DOWN)// Если клавиша нажата
                           {
                                    switch(msg->gbsmsg->submess){

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
                                                               DIconbar(1);
                                                               //if (CNumber[0]=='+' && CZerro==0) CNumber[0]='0';
                                                               if (CNumber[0]=='0' && CNumber[1]=='0') {CNumber[0]='+';CNumber[1]=0;CCursorCount=1; CCursor=1; CZerro=1;}
                                                               draw_body = 1;  DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      }
                                    }
                           }
                  }
         }
//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == ExitMenu
         if (supermod == ExitMenu){
                  if (IsUnlocked()) {
                           if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS)) {// Если клавиша нажата или зажата
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {
                                              //------------------------------------------
                                             case ENTER_BUTTON:
                                             case LEFT_SOFT:
                                             case '5':
                                                      DIconbar(0);
                                                      IdleMenuActive=0;
                                                      menulanch = 0;
                                                      chips.name_to="XTask4";
                                                      chips.name_from="Shell";
                                                      chips.data=0;
                                                      GBS_SendMessage(MMI_CEPID,MSG_IPC,778,&chips);
                                                      run_exit=1;
                                                      return(0);

                                             case RIGHT_SOFT:
                                                      DIconbar(1);
                                                      supermod = 0;
                                                      SetExitMenu = 1;
                                                      zxmain_Y =1; zxmain_X = 3;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);


                                             case UP_BUTTON:
                                             case '2':
                                                      DIconbar(1);
                                                      GTY--; if(GTY<2) GTY=4;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case DOWN_BUTTON:
                                             case '8':
                                                      GTY++; if(GTY>4) GTY=2;
                                                      DIconbar(1);
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);


                                    }
                           }

                           if ((msg->gbsmsg->msg==KEY_DOWN)) {// Если клавиша нажата
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {

                                            case LEFT_BUTTON:
                                                      supermod =0;
                                                      DIconbar(1);
                                                      SetCursor = 0;
                                                      zxn = 0;
                                                      Setzxn = 0;
                                                      aLeft=1;aRight=0;zLeft=1;pres =1;
                                                      if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
                                                      return(0);

                                            case RIGHT_BUTTON:
                                                      supermod =0;
                                                      DIconbar(1);
                                                      SetCursor = 0;
                                                      zxn = 0;
                                                      Setzxn = 0;
                                                      aRight=1;aLeft=0;zLeft=0;pres =1;
                                                      if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
                                                      return(0);
                                    }
                           }


                           if (msg->gbsmsg->msg==KEY_UP)// Если клавиша нажата
                           {
                                    switch(msg->gbsmsg->submess){

                                             case ENTER_BUTTON:
                                             case LEFT_SOFT:
                                             case '5':
                                                      CloseCSM(main_cms_id);
                                                      if(GTY==3) RebootPhone();
                                                      if(GTY==4) SwitchPhoneOff();
                                                      return(2);
                                    }
                           }

                  }
         }
//================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>supermod == CallMenu
         if (supermod == CallMenu){
                  if (IsUnlocked()) {
                           if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))  {// Если клавиша нажата или зажата
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {
                                              //------------------------------------------
                                             case ENTER_BUTTON:
                                             case LEFT_SOFT:
                                             case '5':
                                             case GREEN_BUTTON:
                                                      DIconbar(1);
                                                      char_call=(char *)malloc(128);
                                                      ws_2str(ucall[GTY-2], char_call, wstrlen (ucall[GTY-2]));
                                                      if(char_call[0]!='*' && char_call[0]!='#') MakeVoiceCall(char_call,0x10, 0x20C0); else MakeVoiceCall(char_call,0x10,0x2FFF);
                                                      mfree(char_call);draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case RIGHT_SOFT:
                                                      DIconbar(1);
                                                      supermod = 0;
                                                      SetExitMenu = 1;
                                                      zxmain_Y =1; zxmain_X = 3;
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);


                                             case UP_BUTTON:
                                             case '2':
                                                      DIconbar(1);
                                                      GTY--; if(GTY<2) GTY=(1+countcall);
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                             case DOWN_BUTTON:
                                             case '8':
                                                      GTY++; if(GTY>(1+countcall)) GTY=2;
                                                      DIconbar(1);
                                                      draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
                                                      return(0);

                                    }
                           }

                           if ((msg->gbsmsg->msg==KEY_DOWN)) {// Если клавиша нажата
                                    DIconbar(1);
                                    switch(msg->gbsmsg->submess)
                                    {

                                            case LEFT_BUTTON:
                                                      supermod =0;
                                                      DIconbar(1);
                                                      SetCursor = 0;
                                                      zxn = 0;
                                                      Setzxn = 0;
                                                      aLeft=1;aRight=0;zLeft=1;pres =1;
                                                      if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
                                                      return(0);

                                            case RIGHT_BUTTON:
                                                      supermod =0;
                                                      DIconbar(1);
                                                      SetCursor = 0;
                                                      zxn = 0;
                                                      Setzxn = 0;
                                                      aRight=1;aLeft=0;zLeft=0;pres =1;
                                                      if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/65, KeyRun);
                                                      return(0);
                                    }
                           }
                  }
         }
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
{ //extern void kill_data(void *p, void (*func_p)(void *));
  //kill_data(&data,(void (*)(void *))mfree_adr);
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
{DIconbar(1);
    Parser();
    draw_net = 1; draw_body = 1;
    MAIN_GUI *menu_gui=(MAIN_GUI *)malloc(sizeof(MAIN_GUI));
    zeromem(menu_gui,sizeof(MAIN_GUI));
    menu_gui->gui.canvas=(RECT *)(void *)(&Canvas);
    menu_gui->gui.methods=(void *)gui_methods_3;
    menu_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
    DIconbar(1);
    MENU_GUI_ID=CreateGUI(menu_gui);
/**/	GUI_ID_STR= &MENU_GUI_ID;
  chips.name_to="XTask4";
  chips.name_from="Shell";
  chips.data=GUI_ID_STR;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,777,&chips);

    DIconbar(1);
    lanchPD=1;
    //GBS_DelTimer(&idle_timer);  //убиваем таймер проверки
    Tlog ("Запущен гуи");
}


