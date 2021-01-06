/*******************************************************************************
MD TouchFLO (c) mirrr
*******************************************************************************/

#include "swilib.h"

int main_cms_id;
char *char_settings;
int *int_settings;
char *char_skin;
int *int_skin;
int loadfilesize;

#include "ussd_process.h"
#include "conf_loader.h"
#include "fastrun.c"
#include "language.h"
#include "menus.c"
#include "keyhooks.c"
#include "SWILIB.C"

#define pi 3.14159265358
#ifdef NEWSGOLD
#define myMSG 0xDEAD
#else
#define myMSG 0x11E
#endif




//18.10 - 301

char *imgfile=0; // в эту переменную полностью загружается файл картинки перед распаковкой
int dir_4=0;     // если находит папку Zbin на диске 4:/ то устанавливается в 1

int NSG_MOD = 0;
int loadfilesize;
char *loadfiler(const char  *filename);
static void Killer(void);
static void maincsm_onclose(CSM_RAM *csm);
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);
extern void FreeCLIST(void);
extern void _lock(void);

int fir=1;
#pragma inline
#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

void UpdateScreen() // По сути работа функции заключается в проверке идла и включении своего гуи
{
    if(menulanch){//Если мы еще живы
      CSM_RAM *data=FindCSMbyID(CSM_root()->idle_id);
      if(IsGuiOnTop(idlegui_id)){ //Если IdleGui на самом верху
      GUI *igui=GetTopGUI();
      if (igui) DrawIdleMenu();
      if (fir>0) {GBS_StartTimerProc(&idle_timer, TMR_SECOND, UpdateScreen); fir--;}} else {GBS_StartTimerProc(&idle_timer, TMR_SECOND/15, UpdateScreen); fir=3;}
      if(ConfigUpdated) ConfigUpdated=0;
    }
}


void TimerA()// Перерисовка первой вкладки по таймеру
{
    if (menulanch){//Если мы еще живы
    TDate date;
    TTime time;
    int net_i;
    GetDateTime(&date,&time);
    if (timestamp != time.min  && currentIco == 0 ) {
     draw_all = 1;
     draw_net = 1;
     draw_body = 1;
     DirectRedrawGUI_ID(MENU_GUI_ID);timestamp = time.min;
     FindFiles("4:\\Pictures\\", 1,0);
     FindFiles("4:\\music\\", 1,1);
    }
    
    battery = *RamCap();
    net_data=RamNet();
    network = ((110-net_data->power)/2);
    if (network > 0)  net_i = 0;
    if (network > 6)  net_i = 1;
    if (network > 12)  net_i = 2;
    if (network > 18)  net_i = 3;
    if (network > 24)  net_i = 4;

    if (netstamp != net_i) {    
        draw_net = 1;
        DirectRedrawGUI_ID(MENU_GUI_ID);
        netstamp = net_i;    
    }
    keyup++; if (keyup>10) keyup = 10;
    GBS_StartTimerProc(&time_timer, TMR_SECOND, TimerA);
    }
}

void uppd() {
  ConfigUpdated=1;
  InitConfig();
  UpdateScreen();
}

void adr_progress() 
{
  if(menulanch)
  {//Если мы еще живы
    if (adr_down)
    {
	if((Adr_Cur<3|| CMC<6) && Adr_Cur<CMC && Adr_Cur<4) Adr_Cur++;
	else if(CMC>5) adressmv++;
	DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    }
    
    if (adr_up)
    {
	if((Adr_Cur>1 || adressmv==0) && Adr_Cur>0) Adr_Cur--;
	else  adressmv--;
	if(adressmv<=0) adressmv = 0;
	DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    }
    
    if (net_down)
    {
	if (Setzxn == 1) zxn--;
	Setzxn = 1;
	if (zxn<(-5)) zxn=-5;
	DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    }
    
    if (net_up)
    {
	if (Setzxn == 1) zxn++;
	Setzxn = 1;
	if (zxn>0) zxn = 0;
	DisableIconBar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
    }
  
    if(currentIco == 1 )  GBS_StartTimerProc(&adr_timer, TMR_SECOND/60, adr_progress);
    if(currentIco == 4 )  GBS_StartTimerProc(&adr_timer, TMR_SECOND/60, adr_progress);
  }
}


void freeIMG(IMGHDR *img)
{
  if (img->bpnum == 10) { mfree(img->bitmap); mfree(img);}
}


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg==MSG_USSD_RX || msg->msg==MSG_AUTOUSSD_RX)
  {ProcessUSSD(data,(GBS_USSD_MSG *)msg);}

 if(msg->msg == MSG_RECONFIGURE_REQ)  //сообщение о том что конфиг изменился
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0) uppd();
  }
    if(msg->msg == MSG_IPC){
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0)){
      if (strcmp_nocase(ipc->name_to,"IdleUpd")==0)
        switch (msg->submess)
        {case 0:
         UpdateScreen();
         break;
}}}
return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{ GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);}

static void Killer(void)
{ extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());}
static unsigned short maincsm_name_body[140];

static void maincsm_onclose(CSM_RAM *csm)
{/*
*/
menulanch=0;
freeIMG(FImage1);
freeIMG(FImage2);
freeIMG(FImage4);
freeIMG(FImage6);
freeIMG(FImage7);
freeIMG(FImage9);
freeIMG(FImage9a);
freeIMG(FImage9b);
freeIMG(FImage10);
freeIMG(FImage11);
freeIMG(Wall_0);
freeIMG(Wall_1);
freeIMG(Wall_2);

for (int i=0; i<9;  i++) freeIMG(Ico[i]);
for (int i=0; i<9;  i++) freeIMG(Clock[i]);
for (int i=0; i<44; i++) freeIMG(SetIco[i]);
for (int i=1; i<9;  i++) if (menu_ico_true[i]==1){ menu_ico_true[i]=0; freeIMG(menu_ico[i]);}
FreeWS(ussdws);
FreeWS(js);
FreeCLIST();

if(char_settings)mfree(char_settings);
if(char_skin)mfree(char_skin);
GBS_DelTimer(&idle_timer);
GBS_DelTimer(&key_timer);
GBS_DelTimer(&time_timer);
GBS_DelTimer(&adr_timer);
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
  sizeof(CSM_RAM),
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


static void UpdateCSMname(void)// Имя эльфа в таске
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MD TouchFLO (c)mirrr");
}
// ----------------------------------------------------------------------------




char *loadfiler(const char  *filename){ // Загрузить файл
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      lenta=loadfilesize;
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
  }
  return buf;
}




extern WSHDR *e_ws;
extern char *filename;



void loadwall() //загрузка обоины
{
  char *ImgFile;
  if (dir_4)  ImgFile = loadfile("4:\\Zbin\\HTC\\img\\wallpaper.jpg");
  else ImgFile = loadfile("0:\\Zbin\\HTC\\img\\wallpaper.jpg");
  FImage3=read_jpgimg(ImgFile,0);
  Wall_0 = CreateImgr(240, 56);  drawimg2img( FImage3,Wall_0, 0, 0, 0, 0,240, 56);
  Wall_1 = CreateImgr(240, 217); drawimg2img( FImage3,Wall_1, 0, 0, 0, 56,240, 243-56);
  Wall_2 = CreateImgr(240, 56);  drawimg2img( FImage3,Wall_2, 0, 0, 0, 240,240, 296-240);
  freeIMG(FImage3);
  mfree(ImgFile);
}

int main(const char *exename, const char *filenm)
{
  int_settings = malloc(100);
  Tlog ("start log --------------------------------------------------------------------------");
  GBS_StartTimerProc(&key_timer, TMR_SECOND/25, KeyRun);
  ussdws=AllocWS(256);
  InitConfig();
  dir_4 = isdir("4:\\Zbin\\HTC", 0);
  if (dir_4) Tlog ("Загружаюсь с 4:\\");
  else Tlog ("Загружаюсь с 0:\\");
  loadwall();

//Начальные настройки ====================================================================================================
    
    int sett_ok= 1;lenta=0;
    if (dir_4) {if(isfile ("4:\\Zbin\\HTC\\main.stt")) char_settings = loadfile("4:\\Zbin\\HTC\\main.stt");else sett_ok=0;}
    else  {if(isfile      ("0:\\Zbin\\HTC\\main.stt")) char_settings = loadfile("0:\\Zbin\\HTC\\main.stt");else sett_ok=0;}
    if (!sett_ok)char_settings = malloc(400);
    int_settings=(int*)(char*)char_settings;
    if (!sett_ok)
    {
      int_settings[22]=0; // Режим главного экрана по умолчанию? /0-большие часы, 1-маленькие часы, 2-аналоговые часы
      int_settings[23]=0; // Вести логи?
      int_settings[24]=0; // Отображать приветствие?
      int_settings[25]=9000; // Максимальное количество оперативки на телефоне
      if (dir_4) { savefile2("4:\\Zbin\\HTC\\main.stt",char_settings,400);}
      else       { savefile2("0:\\Zbin\\HTC\\main.stt",char_settings,400);}
      int_settings[24]=1; // Отображать приветствие?
    }
    
    main_mod=int_settings[22];

//Настройки скина ========================================================================================================

int skin_ok= 1;lenta=0;
if (dir_4) {if(isfile ("4:\\Zbin\\HTC\\skin.stt")) char_skin = loadfile("4:\\Zbin\\HTC\\skin.stt");else skin_ok=0;}
else       {if(isfile ("0:\\Zbin\\HTC\\skin.stt")) char_skin = loadfile("0:\\Zbin\\HTC\\skin.stt");else skin_ok=0;}

if (!skin_ok || lenta<399)char_skin = malloc(400);
int_skin=(int*)(char*)char_skin;
if (!skin_ok || lenta<399 || int_skin[0]!=-1){
int_skin[0]=-1;  // Версия конфига = -1
int_skin[1]=1;    // Отображать левую подкладку под часы?
int_skin[2]=1;    // Отображать правую подкладку под часы?
int_skin[3]=0;    // Установить режим главного экрана.	0-оба режима, 1-только большие часы, 2-только маленькие часы, 3-аналоговые часы
//-----------//------------//-------------//------------
int_skin[4]=0;  // Смещение X для подкладки левых часов
int_skin[5]=0;  // Смещение Y для подкладки левых часов
int_skin[6]=0;  // Смещение X для подкладки правых часов
int_skin[7]=0;  // Смещение Y для подкладки правых часов
int_skin[8]=0;  // Смещение X для 1 цифры
int_skin[9]=0;  // Смещение Y для 1 цифры
int_skin[10]=0;  // Смещение X для 2 цифры
int_skin[11]=0;  // Смещение Y для 2 цифры
int_skin[12]=0;  // Смещение X для 3 цифры
int_skin[13]=0;  // Смещение Y для 3 цифры
int_skin[14]=0;  // Смещение X для 4 цифры
int_skin[15]=0;  // Смещение Y для 4 цифры
int_skin[15]=0;  // Выравнивание для маленьких часов
int_skin[16]=0;  // Смещение X для маленьких часов
int_skin[17]=0;  // Смещение Y для маленьких часов
int_skin[18]=0;  // Левый  титл главной вкладки (0-дата, 1-провайдер, 2-оперативка, 3-)
int_skin[19]=1;  // Правый титл главной вкладки
int_skin[20]=0;  // Смещение X для курсора
int_skin[21]=0;  // Смещение Y для курсора
//-----------//------------//-------------//------------
int_skin[22]=0;  			// цвет фона иконбара
int_skin[23]=0;  			// цвет шрифта иконбара
int_skin[24]=0;  			// цвет фона футера
int_skin[25]=0;  			// цвет шрифта футера
int_skin[26]=0;  			// цвет общего фона (под обоиной)            !отображается если не задана картинка для курсора!
int_skin[27]=0;  			// цвет титла
int_skin[28]=0xffff0000;  	// цвет шрифта "ясный"
int_skin[29]=0xff0000ff;  	// цвет шрифта "средний"
int_skin[30]=0x0000ffff;  	// цвет шрифта "блеклый"
int_skin[31]=0; 			// цвет фона меню
int_skin[32]=0;  			// цвет обводки меню
int_skin[33]=0;  			// цвет пунктирных линий меню
int_skin[34]=0;  			// цвет пунктирных линий

int_skin[35]=0;  			// цвет фона почты
int_skin[36]=0;  			// цвет обводки почты
int_skin[37]=0;  			// цвет пунктирных линий почты
int_skin[38]=0;  			// цвет шрифта почты

int_skin[39]=0;  			// цвет шрифта "ясный" над курсором
int_skin[40]=0;  			// цвет шрифта "средний" над курсором
int_skin[41]=0;  			// цвет шрифта "блеклый" над курсором

int_skin[39]=0;  			// цвет курсора				                 !отображается если не задана картинка для курсора!
int_skin[40]=0;  			// цвет обводки курсора						 !отображается если не задана картинка для курсора!


if (dir_4) {savefile2("4:\\Zbin\\HTC\\skin.stt",char_skin,400 );}
else  	   {savefile2("0:\\Zbin\\HTC\\skin.stt",char_skin,400 );}

}
//========================================================================================================================



char *buffer; buffer = malloc(128);

Tlog ("load FImage*");

  if (dir_4) {
  FImage1=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\touch2.png",0);
  FImage2=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\kursor.png",0);
  FImage4=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\book.png",0);
  FImage5=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\clock.png",0);
  FImage6=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\fon1.png",0);
  FImage7=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\win.png",0);
  FImage8=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\touch1.png",0);
  FImage9=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\u-3.png",0);
  FImage9a=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\u-4.png",0);
  FImage9b=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\u-5.png",0);
  FImage11=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\inet.png",0);
  FImage10=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\win2.png",0);
}
  else {
  FImage1=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\touch2.png",0);
  FImage2=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\kursor.png",0);
  FImage4=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\book.png",0);
  FImage5=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\clock.png",0);
  FImage6=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\fon1.png",0);
  FImage7=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\win.png",0);
  FImage8=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\touch1.png",0);
  FImage9=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\u-3.png",0);
  FImage9a=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\u-4.png",0);
  FImage9b=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\u-5.png",0);
  FImage11=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\inet.png",0);
  FImage10=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\win2.png",0);
}

Tlog ("load FImage* - OK");




sprintf (buffer, "FImage1->w = %i", FImage1->w);
Tlog (buffer);
sprintf (buffer, "FImage1->h = %i", FImage1->h);
Tlog (buffer);
sprintf (buffer, "FImage1->bpnum = %i", FImage1->bpnum);
Tlog (buffer);
sprintf (buffer, "FImage2->w = %i", FImage2->w);
Tlog (buffer);
sprintf (buffer, "FImage2->h = %i", FImage2->h);
Tlog (buffer);
sprintf (buffer, "FImage2->bpnum = %i", FImage2->bpnum);
Tlog (buffer);
sprintf (buffer, "FImage3->w = %i", FImage3->w);
Tlog (buffer);
sprintf (buffer, "FImage3->h = %i", FImage3->h);
Tlog (buffer);
sprintf (buffer, "FImage3->bpnum = %i", FImage3->bpnum);
Tlog (buffer);
sprintf (buffer, "FImage4->w = %i", FImage4->w);
Tlog (buffer);
sprintf (buffer, "FImage4->h = %i", FImage4->h);
Tlog (buffer);
sprintf (buffer, "FImage4->bpnum = %i", FImage4->bpnum);
Tlog (buffer);
sprintf (buffer, "FImage5->w = %i", FImage5->w);
Tlog (buffer);
sprintf (buffer, "FImage5->h = %i", FImage5->h);
Tlog (buffer);
sprintf (buffer, "FImage5->bpnum = %i", FImage5->bpnum);
Tlog (buffer);
sprintf (buffer, "FImage6->w = %i", FImage6->w);
Tlog (buffer);
sprintf (buffer, "FImage6->h = %i", FImage6->h);
Tlog (buffer);
sprintf (buffer, "FImage6->bpnum = %i", FImage6->bpnum);
Tlog (buffer);


mfree(buffer);





Tlog ("trim Ico[*]");
Ico[0] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[0], 0, 0, 5, 0, 40, 37);
Ico[1] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[1], 0, 0, 52, 0, 87-52, 37);
Ico[2] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[2], 0, 0, 99, 0, 134-99, 37);
Ico[3] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[3], 0, 0, 151, 0, 186-151, 37);
Ico[4] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[4], 0, 0, 201, 0, 236-201, 37);
Ico[5] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[5], 0, 0, 246, 0, 281-246, 37);
Ico[6] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[6], 0, 0, 291, 0, 326-291, 37);
Ico[7] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[7], 0, 0, 343, 0, 378-343, 37);
Ico[8] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[8], 0, 0, 389, 0, 424-389, 37);
Ico[9] = CreateImgr(35, 37); drawimg2img( FImage8,Ico[9], 0, 0, 433, 0, 468-433, 37);

Tlog ("trim Ico[*] - OK");

Tlog ("delete FImage8");
if (FImage8->bpnum == 10) {mfree(FImage8);mfree(FImage8->bitmap);}
Tlog ("delete FImage8 - OK");

Tlog ("trim Clock[*]");
Clock[0] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[0], 0, 0, 0, 0, 40, 64);
Clock[1] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[1], 0, 0, 0, 65, 40, 64);
Clock[2] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[2], 0, 0, 0, 130, 40, 64);
Clock[3] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[3], 0, 0, 0, 195, 40, 64);
Clock[4] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[4], 0, 0, 0, 260, 40, 64);
Clock[5] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[5], 0, 0, 0, 325, 40, 64);
Clock[6] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[6], 0, 0, 0, 390, 40, 64);
Clock[7] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[7], 0, 0, 0, 455, 40, 64);
Clock[8] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[8], 0, 0, 0, 520, 40, 64);
Clock[9] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[9], 0, 0, 0, 585, 40, 64);
Tlog ("trim Clock[*] - OK");

Tlog ("delete FImage5");
if (FImage5->bpnum == 10) {mfree(FImage5);mfree(FImage5->bitmap);}
Tlog ("delete FImage5 - OK");
Tlog ("load SetIco[*]");
  if (dir_4) {
SetIco[0]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\1.png",0);
SetIco[1]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\2.png",0);
SetIco[2]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\3.png",0);
SetIco[3]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\4.png",0);
SetIco[4]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\5.png",0);
SetIco[5]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\6.png",0);
SetIco[6]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\8.png",0);
SetIco[7]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\9.png",0);
SetIco[8]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\10.png",0);
SetIco[9]=CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\SetICO\\11.png",0);
SetIco[11] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\1.png",0);
SetIco[12] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\2.png",0);
SetIco[13] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\3.png",0);
SetIco[14] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\4.png",0);
SetIco[15] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\5.png",0);
SetIco[16] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\6.png",0);
SetIco[17] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\7.png",0);
SetIco[18] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\8.png",0);
SetIco[19] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\9.png",0);
SetIco[20] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\10.png",0);
SetIco[21] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\11.png",0);
SetIco[22] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\12.png",0);
SetIco[23] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\13.png",0);
SetIco[24] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\14.png",0);
SetIco[25] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\15.png",0);
SetIco[26] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\16.png",0);
SetIco[27] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\17.png",0);
SetIco[28] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\18.png",0);
SetIco[29] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\19.png",0);
SetIco[30] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\20.png",0);
SetIco[31] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\21.png",0);
SetIco[32] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\22.png",0);
SetIco[33] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\23.png",0);
SetIco[34] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\24.png",0);
SetIco[35] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\25.png",0);
SetIco[36] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\26.png",0);
SetIco[37] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\27.png",0);
SetIco[38] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\28.png",0);

SetIco[41] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\41.png",0);
SetIco[42] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\42.png",0);
SetIco[43] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\43.png",0);
SetIco[44] = CreateIMGHDRFromPngFile("4:\\Zbin\\HTC\\img\\MenuIco\\44.png",0);
}


else
{
SetIco[0]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\1.png",0);
SetIco[1]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\2.png",0);
SetIco[2]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\3.png",0);
SetIco[3]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\4.png",0);
SetIco[4]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\5.png",0);
SetIco[5]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\6.png",0);
SetIco[6]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\8.png",0);
SetIco[7]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\9.png",0);
SetIco[8]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\10.png",0);
SetIco[9]=CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\SetICO\\11.png",0);
SetIco[11] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\1.png",0);
SetIco[12] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\2.png",0);
SetIco[13] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\3.png",0);
SetIco[14] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\4.png",0);
SetIco[15] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\5.png",0);
SetIco[16] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\6.png",0);
SetIco[17] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\7.png",0);
SetIco[18] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\8.png",0);
SetIco[19] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\9.png",0);
SetIco[20] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\10.png",0);
SetIco[21] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\11.png",0);
SetIco[22] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\12.png",0);
SetIco[23] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\13.png",0);
SetIco[24] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\14.png",0);
SetIco[25] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\15.png",0);
SetIco[26] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\16.png",0);
SetIco[27] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\17.png",0);
SetIco[28] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\18.png",0);
SetIco[29] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\19.png",0);
SetIco[30] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\20.png",0);
SetIco[31] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\21.png",0);
SetIco[32] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\22.png",0);
SetIco[33] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\23.png",0);
SetIco[34] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\24.png",0);
SetIco[35] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\25.png",0);
SetIco[36] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\26.png",0);
SetIco[37] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\27.png",0);
SetIco[38] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\28.png",0);

SetIco[41] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\41.png",0);
SetIco[42] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\42.png",0);
SetIco[43] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\43.png",0);
SetIco[44] = CreateIMGHDRFromPngFile("0:\\Zbin\\HTC\\img\\MenuIco\\44.png",0);
}

SetIco[10] = CreateImgr(183, 27); drawimg2img(SetIco[5],SetIco[10], 0, 0, 25, 1, 0, 0);
Tlog ("load SetIco[*] - OK");

js = AllocWS( 256 );

e_ws = AllocWS( 255 );
filename = malloc (255);

//==================================================================================================

LockSched();
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  main_cms_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  ConstructList();
  battery = *RamCap();
	net_data=RamNet();
	GBS_StartTimerProc(&idle_timer, TMR_SECOND/4, UpdateScreen);
  return (0);
}
