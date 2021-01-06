/*******************************************************************************
MD TouchFLO (c) mirrr
*******************************************************************************/
void UpdateScreen();
#include "swilib.h"
int main_cms_id;
char *char_settings;
int *int_settings;
char *char_skin;
int inExit=0;
int int_skin[40];
char *colors[40];
int   lui_bob=0;
#include "string_works.h"
#include "MString.h"
#include "ussd_process.h"
#include "conf_loader.h"
#include "fastrun.c"
#include "language.h"

#include "pdusms_sie.c"

#define pi 3.14159265358
#ifdef NEWSGOLD
#define myMSG 0xDEAD
#else
#define myMSG 0x11E
#endif


MString  *sms_text[40];
MString  *sms_num[40];
MString  *sms_time[40];

MString *a=NULL;
MString *b=NULL;

SMS_DATA   IN_SMSD, ch_SMSD;
char SMS_SND[128];
int isvib[8], issnd[8], v_p[8], v_c[8], svol[8];


#include "menus.c"
#include "keyhooks.c"
#include "SWILIB.C"

//18.10 - 301

char *imgfile=0; // в эту переменную полностью загружается файл картинки перед распаковкой
int dir_4=0;     // если находит папку Zbin на диске 4:/ то устанавливается в 1

int NSG_MOD = 0;

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
if (igui) DrawIdleMenu();GBS_StartTimerProc(&idle_timer, TMR_SECOND/2, UpdateScreen);
} else {GBS_StartTimerProc(&idle_timer, TMR_SECOND/8, UpdateScreen); fir=3;}
if(ConfigUpdated) ConfigUpdated=0;
}}


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

if (IsUnlocked())  GBS_StartTimerProc(&time_timer, TMR_SECOND*15, TimerA);
 tiper++;
 if (tiper>2) if(supermod != NumberMenu)  {
	KbdLock();
	GBS_DelTimer(&key_timer);
	GBS_DelTimer(&time_timer);
	GBS_DelTimer(&adr_timer);
	currentIco = rasp9[0];
	xxl = 0;DirectRedrawGUI_ID(MENU_GUI_ID);}

}
}

void uppd() {
ConfigUpdated=1;
InitConfig();
UpdateScreen();
}

void adr_progress() {
if(menulanch){//Если мы еще живы
if (adr_down){
		if((Adr_Cur<3|| CMC<6) && Adr_Cur<CMC && Adr_Cur<4) Adr_Cur++;
		else if(CMC>5) adressmv++;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
	  }
if (adr_up){
	    if((Adr_Cur>1 || adressmv==0) && Adr_Cur>0) Adr_Cur--;
		else  adressmv--;
		if(adressmv<=0) adressmv = 0;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
	  }
if (net_down){
		if (Setzxn == 1) zxn--;
		Setzxn = 1;
		if (zxn<(-5)) zxn=-5;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
	  }
if (net_up){
		if (Setzxn == 1) zxn++;
		Setzxn = 1;
		if (zxn>0) zxn = 0;
	    DIconbar(1); draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
	  }

	if(currentIco == 1 && (adr_down ||  adr_up))  if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/60, adr_progress);
	if(currentIco == 4 && (net_down ||  net_up) )  if (IsUnlocked())  GBS_StartTimerProc(&adr_timer, TMR_SECOND/60, adr_progress);
}}


void freeIMG(IMGHDR *img)
{
  if (img->bpnum == 10) { mfree(img->bitmap); mfree(img);}
}


/*
void Incom_SMS(){
ShowMSG (1, (int)"Получено СМС!");
}
*
 typedef struct
{
	int type;
	char SMS_CENTER[32];
	char Number[32];
	char Time[32];
	int tm[6];
	short sig;
	char cnt, n;
	WSHDR *name;
	WSHDR *SMS_TEXT;
}SMS_DATA;
*
*
MString  sms_text[40];
MString  sms_num[40];
MString  sms_time[40];
*
* SMS_DATA sms_y[30];
*/




//wstrlen (WSHDR *wshdr);ws_2str(WSHDR *ws, char *str, unsigned int size);




void Incom_SMS()//GBS_MSG *msg)
{
	if(IN_SMSD.SMS_TEXT) FreeWS(IN_SMSD.SMS_TEXT);
	IN_SMSD.SMS_TEXT=NULL;
	for(int i=0; i<scnt.all; i++){ if(SMSD[i].SMS_TEXT) FreeWS(SMSD[i].SMS_TEXT); SMSD[i].SMS_TEXT=NULL;}
	if(SMSD)	{mfree(SMSD); SMSD=NULL;}
	GetSMSData(&IN_SMSD, IncommingPDU()); //получаем данные смс
          if((!IN_SMSD.SMS_TEXT)||(IN_SMSD.n!=1)) return; //нихрена не получили (
          if(IN_SMSD.type!=TYPE_IN) return;     // не входящая
         read_smsdat(); allsms++; if (allsms>39) allsms=39;
            char *stext=(char *)malloc(wstrlen (IN_SMSD.SMS_TEXT)+1);
         ws_2str(IN_SMSD.SMS_TEXT, stext, wstrlen (IN_SMSD.SMS_TEXT));
         stext[wstrlen (IN_SMSD.SMS_TEXT)]=0;

     /* for (int i=39; i>0;i--)
         {
         *sms_text[i]=*sms_text[i-1];
         *sms_num[i]=*sms_num[i-1];
         *sms_time[i]=*sms_time[i-1];
         }
         *sms_text[0]=*stext;
         *sms_num[0]=*IN_SMSD.Number;
         *sms_time[0]=*IN_SMSD.Time;*/
}
/**********************************************************************************************/
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg==MSG_USSD_RX || msg->msg==MSG_AUTOUSSD_RX)
  {ProcessUSSD(data,(GBS_USSD_MSG *)msg);}

 if(msg->msg == MSG_RECONFIGURE_REQ)  //сообщение о том что конфиг изменился
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0) uppd();
  }


if(msg->msg == 0x6106)
{
Incom_SMS();//msg);
}



//--------------------------------------------


if (msg->msg==MSG_IPC)
{
  IPC_REQ *ipc;
 if ((ipc=(IPC_REQ*)msg->data0))
 {
 if(strstr(ipc->name_to, "MD TouchFlo")==0)
 {
 if (strcmp(ipc->name_from,"XTask4")==0)
{
switch (msg->submess)
{
    case 777:
    inExit=1; UpdateScreen();
    supermod = ExitMenu; GTY=2;
    DIconbar(1); draw_body = 1; DirectRedrawGUI_ID(MENU_GUI_ID);
    return(1);
}}}}}



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



//------------------------------------------
	if(IN_SMSD.SMS_TEXT) FreeWS(IN_SMSD.SMS_TEXT);
	IN_SMSD.SMS_TEXT=NULL;
	for(int i=0; i<scnt.all; i++)
	{
		if(SMSD[i].SMS_TEXT) FreeWS(SMSD[i].SMS_TEXT);
		SMSD[i].SMS_TEXT=NULL;
	}
	if(SMSD)
	{
		mfree(SMSD);
		SMSD=NULL;
	}
//------------------------------------------





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

for (int i=0; i<10;  i++) freeIMG(Ico[i]);
for (int i=0; i<11;  i++) freeIMG(PIco[i]);
for (int i=0; i<10;  i++) freeIMG(Clock[i]);
for (int i=0; i<45; i++) freeIMG(SetIco[i]);
for (int i=1; i<10;  i++) if (menu_ico_true[i]==1){ menu_ico_true[i]=0; freeIMG(menu_ico[i]);}
FreeWS(ussdws);
FreeWS(js);
FreeCLIST();
mfree(filename );
mfree(seytitle);
mfree(seytext);
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
  MString SID;
  MString INTSID;

  SID=BM3FILE_FR; SID=SID+"wallpaper.jpg";
  ImgFile = loadfile(SID.stri);

FImage3=read_jpgimg(ImgFile,0);
if (FImage3->bpnum == 10){
Wall_0 = CreateImgr(240, 30);  drawimg2img( FImage3,Wall_0, 0, 0, 0, 26,240, 56-26);
Wall_1 = CreateImgr(240, 189); drawimg2img( FImage3,Wall_1, 0, 0, 0, 56,240, 243-56); //189
Wall_2 = CreateImgr(240, 53);  drawimg2img( FImage3,Wall_2, 0, 0, 0, 243,240, 296-243);//56
}
else{
Wall_0 = CreateImgr(1, 1);
Wall_1 = CreateImgr(1, 1);
Wall_2 = CreateImgr(1, 1);
}
freeIMG(FImage3);

mfree(ImgFile);
}


char *Get_Param_Value(char *ch, char *req)
{
 if(!strstr(ch, req)) return NULL;
  char *n_displace = strstr(ch, req);     	// начало строки с именем параметра
  char *eq=n_displace + strlen(req);      	// плюс длинна параметра
  char *zpt= strchr(n_displace,',');      	// конец параметра
  if(!zpt)zpt=ch+strlen(ch);			  	// конец строки (если мы не нашли конец нашего параметра)
  int len;								  	// длинна?
  char *val;							  	// возвращаем значение
    len=zpt-eq-2;							// да, длинна
    val=(char *)malloc(len+1);				// выделяем место
    //for(int i=0;i<len;i++) val[i]=*(eq+i+1);// копирование, но как то по дебильному, есть же функции..
    strncpy(val,eq+1,len);
  val[len]=0x0;								// записываем 0 в конец
  return val;								// возвращаем значение
}

char alu(char a1){
if(a1=='0') return 0x00;
if(a1=='1') return 0x11;
if(a1=='2') return 0x22;
if(a1=='3') return 0x33;
if(a1=='4') return 0x44;
if(a1=='5') return 0x55;
if(a1=='6') return 0x66;
if(a1=='7') return 0x77;
if(a1=='8') return 0x88;
if(a1=='9') return 0x99;
if(a1=='a' || a1=='A') return 0xaa;
if(a1=='b' || a1=='B') return 0xbb;
if(a1=='c' || a1=='C') return 0xcc;
if(a1=='d' || a1=='D') return 0xdd;
if(a1=='e' || a1=='E') return 0xee;
if(a1=='f'  || a1=='F') return 0xff;
return 0x00;
}


void colp(char *temp, char *conf){
temp[0]=alu(conf[0]);
temp[1]=alu(conf[1]);
temp[2]=alu(conf[2]);
temp[3]=alu(conf[3]);
}




void start_set(){
  chips.name_to="XTask";
chips.name_from="Shell";
chips.data=0;
GBS_SendMessage(MMI_CEPID,MSG_IPC,1,&chips);
 lui_bob=0;UpdateScreen();DisableIconBar(1);
int_settings = (int *)malloc(100);
InitConfig();
dir_4 = isdir("4:\\Zbin\\HTC", 0);
      


      lui_bob=1;UpdateScreen();DisableIconBar(1);REDRAW();
loadwall();
//Начальные настройки ====================================================================================================

int sett_ok= 1;lenta=0;
if (dir_4) {if(isfile ("4:\\Zbin\\HTC\\main.stt")) char_settings = loadfile("4:\\Zbin\\HTC\\main.stt");else sett_ok=0;}
else  {if(isfile      ("0:\\Zbin\\HTC\\main.stt")) char_settings = loadfile("0:\\Zbin\\HTC\\main.stt");else sett_ok=0;}
if (!sett_ok)char_settings = (char *)malloc(400);
int_settings=(int*)(char*)char_settings;
if (!sett_ok){
int_settings[22]=0; // Режим главного экрана по умолчанию? /0-большие часы, 1-маленькие часы, 2-аналоговые часы
int_settings[23]=0; // Вести логи?
int_settings[24]=0; // Отображать приветствие?
int_settings[25]=9000; // Максимальное количество оперативки на телефоне
if (dir_4) { savefile2("4:\\Zbin\\HTC\\main.stt",char_settings,400);}
else       { savefile2("0:\\Zbin\\HTC\\main.stt",char_settings,400);}
int_settings[24]=1; // Отображать приветствие?
}


//Настройки скина ========================================================================================================
  MString SID;
  MString INTSID;

  SID=BM3FILE_FR; SID=SID+"skin.stt";  if(isfile (SID.stri)) char_skin = loadfile(SID.stri);

/*CfgVer="0.1" Версия конфига;
LeftBook="1"; Отображать левую подкладку под часы?
RightBook="1" Отображать правую подкладку под часы?
MMode="0" Режим главного экрана. 0-все, 1-большие часы, 2-маленькие часы, 3-аналоговые часы(в разработке)
LBookX="0" Смещение X для подкладки левых часов
LBookY="0" Смещение Y для подкладки левых часов
RBookX="0" Смещение X для подкладки правых часов
RBookY="0" Смещение Y для подкладки правых часов
Clock1X="0" Смещение X для 1 цифры
Clock1Y="0" Смещение Y для 1 цифры
Clock2X="0" Смещение X для 2 цифры
Clock2Y="0" Смещение Y для 2 цифры
Clock3X="0" Смещение X для 3 цифры
Clock3Y="0" Смещение Y для 3 цифры
Clock4X="0" Смещение X для 4 цифры
Clock4Y="0" Смещение Y для 4 цифры
SClockAlign="3" Выравнивание для маленьких часов
SClockX="0" Смещение X для маленьких часов
SClockY="0" Смещение Y для маленьких часов
LTitle="0" Левый титл главной вкладки (0-дата, 1-провайдер, 2-оперативка..)
RTitle="1" Правый титл главной вкладки
CursorX="0" Смещение X для кур.
CursorY="0" Смещение Y для кур.
IcoCursorX="0" Смещение X для кур.
IcoCursorY="0" Смещение Y для кур.
Line="0" Тип разд. линий
---
"RGBA"

BarColor="000f" цвет фона иконбара
FBarColor="ffff" цвет шрифта иконбара и иконок
BBarColor="fff4" дополнительный цвет иконок
FootColor="000f" цвет фона футера
FFootColor="cccc" цвет шрифта футера
BackClolor="000f" цвет общего фона (под обоиной)
FSClockColor="ccc8" цвет маленьких часов
TitleColor1="2224" цвет титла
TitleColor2="4444" цвет обводки титла
FTitleColor="ccc8" цвет шрифта титла
FAlarmColorOff="ccc4" цвет шрифта отключеного будильника
FAlarmColorOn="ccc7" цвет шрифта будильника
LineColor="9994" цвет пунктирных линий
ColoColor="0809" цвет кружка с кол-вом сообщений
---
FontColor1="eeef" цвет шрифта "ясный"
FontColor2="aaa6" цвет шрифта "блеклый"
FontColor3="cccc" цвет шрифта "средний"
FontColor4="eeef" цвет шрифта "ясный" над кур.
FontColor5="bbb6" цвет шрифта "блеклый" над кур.
FontColor6="dddf" цвет шрифта "средний" над кур.
---
CurColor1="0000" цвет кур.
CurColor2="0000" цвет обводки кур.
---
MenuColor1="000f" цвет фона меню
MenuColor2="555f" цвет обводки меню
MenuColor3="444f" цвет пунктирных линий меню
FMenuColor="cccc" цвет шрифта меню
FMenuColor2="8886" цвет стрелок и верхних надписей меню
---
MailColor1="dddf" цвет фона почты
MailColor2="666f" цвет обводки почты
MailLineColor="666f" цвет пунктирных линий почты
FMailColor1="222f" цвет шрифта почты
FMailColor2="444f" цвет шрифта сообщения почты
*/


int_skin[0]=-1;  // Версия конфига = -1
int_skin[1]=1;    // Отображать левую подкладку под часы?
int_skin[2]=1;    // Отображать правую подкладку под часы?
int_skin[3]=0;    // Установить режим главного экрана.	0-оба режима, 1-только большие часы, 2-только маленькие часы, 3-аналоговые часы
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
int_skin[16]=3;  // Выравнивание для маленьких часов
int_skin[17]=0;  // Смещение X для маленьких часов
int_skin[18]=0;  // Смещение Y для маленьких часов

int_skin[19]=0;  // Левый  титл главной вкладки (0-дата, 1-провайдер, 2-оперативка, 3-)
int_skin[20]=1;  // Правый титл главной вкладки
int_skin[21]=0;  // Смещение X для курсора
int_skin[22]=0;  // Смещение Y для курсора
int_skin[23]=0;  // Смещение X для иконки курсора
int_skin[24]=0;  // Смещение Y для иконки курсора



char *bobik;
if(strstr(char_skin,"LeftBook=")){ bobik=Get_Param_Value(char_skin,   "LeftBook="); if (bobik){sscanf(bobik,"%i",&int_skin[1]);mfree(bobik);}}
if(strstr(char_skin,"RightBook=")){ bobik=Get_Param_Value(char_skin,   "RightBook="); if (bobik){sscanf(bobik,"%i",&int_skin[2]);mfree(bobik);}}
if(strstr(char_skin,"MMode=")){ bobik=Get_Param_Value(char_skin,   "MMode="); if (bobik){sscanf(bobik,"%i",&int_skin[3]);mfree(bobik);}}
if(strstr(char_skin,"LBookX=")){ bobik=Get_Param_Value(char_skin,   "LBookX="); if (bobik){sscanf(bobik,"%i",&int_skin[4]);mfree(bobik);}}
if(strstr(char_skin,"LBookY=")){ bobik=Get_Param_Value(char_skin,   "LBookY="); if (bobik){sscanf(bobik,"%i",&int_skin[5]);mfree(bobik);}}
if(strstr(char_skin,"RBookX=")){ bobik=Get_Param_Value(char_skin,   "RBookX="); if (bobik){sscanf(bobik,"%i",&int_skin[6]);mfree(bobik);}}
if(strstr(char_skin,"RBookY=")){ bobik=Get_Param_Value(char_skin,   "RBookY="); if (bobik){sscanf(bobik,"%i",&int_skin[7]);mfree(bobik);}}
if(strstr(char_skin,"Clock1X=")){ bobik=Get_Param_Value(char_skin,   "Clock1X="); if (bobik){sscanf(bobik,"%i",&int_skin[8]);mfree(bobik);}}
if(strstr(char_skin,"Clock1Y=")){ bobik=Get_Param_Value(char_skin,   "Clock1Y="); if (bobik){sscanf(bobik,"%i",&int_skin[9]);mfree(bobik);}}
if(strstr(char_skin,"Clock2X=")){ bobik=Get_Param_Value(char_skin,   "Clock2X="); if (bobik){sscanf(bobik,"%i",&int_skin[10]);mfree(bobik);}}
if(strstr(char_skin,"Clock2Y=")){ bobik=Get_Param_Value(char_skin,   "Clock2Y="); if (bobik){sscanf(bobik,"%i",&int_skin[11]);mfree(bobik);}}
if(strstr(char_skin,"Clock3X=")){ bobik=Get_Param_Value(char_skin,   "Clock3X="); if (bobik){sscanf(bobik,"%i",&int_skin[12]);mfree(bobik);}}
if(strstr(char_skin,"Clock3Y=")){ bobik=Get_Param_Value(char_skin,   "Clock3Y="); if (bobik){sscanf(bobik,"%i",&int_skin[13]);mfree(bobik);}}
if(strstr(char_skin,"Clock4X=")){ bobik=Get_Param_Value(char_skin,   "Clock4X="); if (bobik){sscanf(bobik,"%i",&int_skin[14]);mfree(bobik);}}
if(strstr(char_skin,"Clock4Y=")){ bobik=Get_Param_Value(char_skin,   "Clock4Y="); if (bobik){sscanf(bobik,"%i",&int_skin[15]);mfree(bobik);}}
if(strstr(char_skin,"SClockAlign=")){ bobik=Get_Param_Value(char_skin,   "SClockAlign="); if (bobik){sscanf(bobik,"%i",&int_skin[16]);mfree(bobik);}}
if(strstr(char_skin,"SClockX=")){ bobik=Get_Param_Value(char_skin,   "SClockX="); if (bobik){sscanf(bobik,"%i",&int_skin[17]);mfree(bobik);}}
if(strstr(char_skin,"SClockY=")){ bobik=Get_Param_Value(char_skin,   "SClockY="); if (bobik){sscanf(bobik,"%i",&int_skin[18]);mfree(bobik);}}
if(strstr(char_skin,"LTitle=")){ bobik=Get_Param_Value(char_skin,   "LTitle="); if (bobik){sscanf(bobik,"%i",&int_skin[19]);mfree(bobik);}}
if(strstr(char_skin,"RTitle=")){ bobik=Get_Param_Value(char_skin,   "RTitle="); if (bobik){sscanf(bobik,"%i",&int_skin[20]);mfree(bobik);}}
if(strstr(char_skin,"CursorX=")){ bobik=Get_Param_Value(char_skin,   "CursorX="); if (bobik){sscanf(bobik,"%i",&int_skin[21]);mfree(bobik);}}
if(strstr(char_skin,"CursorY=")){ bobik=Get_Param_Value(char_skin,   "CursorY="); if (bobik){sscanf(bobik,"%i",&int_skin[22]);mfree(bobik);}}
if(strstr(char_skin,"IcoCursorX=")){ bobik=Get_Param_Value(char_skin,   "IcoCursorX="); if (bobik){sscanf(bobik,"%i",&int_skin[23]);mfree(bobik);}}
if(strstr(char_skin,"IcoCursorY=")){ bobik=Get_Param_Value(char_skin,   "IcoCursorY="); if (bobik){sscanf(bobik,"%i",&int_skin[24]);mfree(bobik);}}

if(strstr(char_skin,"BBarColor=")){ bobik=Get_Param_Value(char_skin,   "BBarColor="); if (bobik){colp(colors[0],bobik); mfree(bobik);}}
if(strstr(char_skin,"BarColor=")){ bobik=Get_Param_Value(char_skin,   "BarColor="); if (bobik){colp(colors[1],bobik); mfree(bobik);}}
if(strstr(char_skin,"FBarColor=")){ bobik=Get_Param_Value(char_skin,   "FBarColor="); if (bobik){colp(colors[2],bobik); mfree(bobik);}}
if(strstr(char_skin,"FootColor=")){ bobik=Get_Param_Value(char_skin,   "FootColor="); if (bobik){colp(colors[3],bobik); mfree(bobik);}}
if(strstr(char_skin,"FFootColor=")){ bobik=Get_Param_Value(char_skin,   "FFootColor="); if (bobik){colp(colors[4],bobik); mfree(bobik);}}
if(strstr(char_skin,"BackClolor=")){ bobik=Get_Param_Value(char_skin,   "BackClolor="); if (bobik){colp(colors[5],bobik); mfree(bobik);}}
if(strstr(char_skin,"TitleColor1=")){ bobik=Get_Param_Value(char_skin,   "TitleColor1="); if (bobik){colp(colors[6],bobik); mfree(bobik);}}

if(strstr(char_skin,"FontColor1=")){ bobik=Get_Param_Value(char_skin,   "FontColor1="); if (bobik){colp(colors[7],bobik); mfree(bobik);}}
if(strstr(char_skin,"FontColor2=")){ bobik=Get_Param_Value(char_skin,   "FontColor2="); if (bobik){colp(colors[8],bobik); mfree(bobik);}}
if(strstr(char_skin,"FontColor3=")){ bobik=Get_Param_Value(char_skin,   "FontColor3="); if (bobik){colp(colors[9],bobik); mfree(bobik);}}

if(strstr(char_skin,"FontColor4=")){ bobik=Get_Param_Value(char_skin,   "FontColor4="); if (bobik){colp(colors[13],bobik); mfree(bobik);}}
if(strstr(char_skin,"FontColor5=")){ bobik=Get_Param_Value(char_skin,   "FontColor5="); if (bobik){colp(colors[14],bobik); mfree(bobik);}}
if(strstr(char_skin,"FontColor6=")){ bobik=Get_Param_Value(char_skin,   "FontColor6="); if (bobik){colp(colors[15],bobik); mfree(bobik);}}

if(strstr(char_skin,"MenuColor1=")){ bobik=Get_Param_Value(char_skin,   "MenuColor1="); if (bobik){colp(colors[10],bobik); mfree(bobik);}}
if(strstr(char_skin,"MenuColor2=")){ bobik=Get_Param_Value(char_skin,   "MenuColor2="); if (bobik){colp(colors[11],bobik); mfree(bobik);}}
if(strstr(char_skin,"MenuColor3=")){ bobik=Get_Param_Value(char_skin,   "MenuColor3="); if (bobik){colp(colors[12],bobik); mfree(bobik);}}
lui_bob=2;UpdateScreen();DisableIconBar(1);REDRAW();
if(strstr(char_skin,"LineColor=")){ bobik=Get_Param_Value(char_skin,   "LineColor="); if (bobik){colp(colors[16],bobik); mfree(bobik);}}
if(strstr(char_skin,"MailColor1=")){ bobik=Get_Param_Value(char_skin,   "MailColor1="); if (bobik){colp(colors[17],bobik); mfree(bobik);}}
if(strstr(char_skin,"MailColor2=")){ bobik=Get_Param_Value(char_skin,   "MailColor2="); if (bobik){colp(colors[18],bobik); mfree(bobik);}}
if(strstr(char_skin,"MailLineColor=")){ bobik=Get_Param_Value(char_skin,   "MailLineColor="); if (bobik){colp(colors[19],bobik); mfree(bobik);}}
if(strstr(char_skin,"FMailColor1=")){ bobik=Get_Param_Value(char_skin,   "FMailColor1="); if (bobik){colp(colors[20],bobik); mfree(bobik);}}
if(strstr(char_skin,"FMailColor2=")){ bobik=Get_Param_Value(char_skin,   "FMailColor2="); if (bobik){colp(colors[21],bobik); mfree(bobik);}}
if(strstr(char_skin,"CurColor1=")){ bobik=Get_Param_Value(char_skin,   "CurColor1="); if (bobik){colp(colors[22],bobik); mfree(bobik);}}
if(strstr(char_skin,"CurColor2=")){ bobik=Get_Param_Value(char_skin,   "CurColor2="); if (bobik){colp(colors[23],bobik); mfree(bobik);}}

if(strstr(char_skin,"TitleColor2=")){ bobik=Get_Param_Value(char_skin,   "TitleColor2="); if (bobik){colp(colors[24],bobik); mfree(bobik);}}
if(strstr(char_skin,"FTitleColor=")){ bobik=Get_Param_Value(char_skin,   "FTitleColor="); if (bobik){colp(colors[25],bobik); mfree(bobik);}}
if(strstr(char_skin,"FSClockColor=")){ bobik=Get_Param_Value(char_skin,   "FSClockColor="); if (bobik){colp(colors[26],bobik); mfree(bobik);}}
if(strstr(char_skin,"FAlarmColorOff=")){ bobik=Get_Param_Value(char_skin,   "FAlarmColorOff="); if (bobik){colp(colors[27],bobik); mfree(bobik);}}
if(strstr(char_skin,"FAlarmColorOn=")){ bobik=Get_Param_Value(char_skin,   "FAlarmColorOn="); if (bobik){colp(colors[28],bobik); mfree(bobik);}}
if(strstr(char_skin,"FMenuColor=")){ bobik=Get_Param_Value(char_skin,   "FMenuColor="); if (bobik){colp(colors[29],bobik); mfree(bobik);}}
if(strstr(char_skin,"FMenuColor2=")){ bobik=Get_Param_Value(char_skin,   "FMenuColor2="); if (bobik){colp(colors[30],bobik); mfree(bobik);}}
if(strstr(char_skin,"ColoColor=")){ bobik=Get_Param_Value(char_skin,   "ColoColor="); if (bobik){colp(colors[31],bobik); mfree(bobik);}}
lui_bob=3;UpdateScreen();DisableIconBar(1);REDRAW();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  SID=BM3FILE_FR; SID=SID+"touch2.png";      FImage1=CreateIMGHDRFromPngFile(SID.stri,0);   //очищаем после порезки ниже
  SID=BM3FILE_FR; SID=SID+"kursor.png";        FImage2=CreateIMGHDRFromPngFile(SID.stri,0);
  SID=BM3FILE_FR; SID=SID+"book.png";           FImage4=CreateIMGHDRFromPngFile(SID.stri,0);
  lui_bob=4;UpdateScreen();DisableIconBar(1);REDRAW();
  SID=BM3FILE_FR; SID=SID+"clock.png";          FImage5=CreateIMGHDRFromPngFile(SID.stri,0);   //очищаем после порезки ниже
  SID=BM3FILE_FR; SID=SID+"fon1.png";           FImage6=CreateIMGHDRFromPngFile(SID.stri,0);
  SID=BM3FILE_FR; SID=SID+"win.png";             FImage7=CreateIMGHDRFromPngFile(SID.stri,0);
  
  SID=BM3FILE_FR; SID=SID+"touch1.png";      FImage8=CreateIMGHDRFromPngFile(SID.stri,0);   //очищаем после порезки ниже
  SID=BM3FILE_FR; SID=SID+"u-3.png";            FImage9=CreateIMGHDRFromPngFile(SID.stri,0);
  SID=BM3FILE_FR; SID=SID+"u-4.png";            FImage9a=CreateIMGHDRFromPngFile(SID.stri,0);
  lui_bob=5;UpdateScreen();DisableIconBar(1);REDRAW();
  SID=BM3FILE_FR; SID=SID+"u-5.png";            FImage9b=CreateIMGHDRFromPngFile(SID.stri,0);
  SID=BM3FILE_FR; SID=SID+"inet.png";             FImage11=CreateIMGHDRFromPngFile(SID.stri,0);
  SID=BM3FILE_FR; SID=SID+"win2.png";           FImage10=CreateIMGHDRFromPngFile(SID.stri,0);

for (int i=0;i<6;i++){INTSID=(i+1); SID=BM3FILE_FR;  SID=SID+"SetICO\\"; SID=SID+INTSID+".png";  SetIco[i]=CreateIMGHDRFromPngFile(SID.stri,0); }
for (int i=6;i<10;i++){INTSID=(i+2); SID=BM3FILE_FR;  SID=SID+"SetICO\\"; SID=SID+INTSID+".png";  SetIco[i]=CreateIMGHDRFromPngFile(SID.stri,0); }
lui_bob=6;UpdateScreen();DisableIconBar(1);REDRAW();
for (int i=11;i<39;i++){INTSID=(i-10); SID=BM3FILE_FR;  SID=SID+"MenuIco\\"; SID=SID+INTSID+".png";  SetIco[i]=CreateIMGHDRFromPngFile(SID.stri,0); }
for (int i=41;i<45;i++){INTSID=(i); SID=BM3FILE_FR;  SID=SID+"MenuIco\\"; SID=SID+INTSID+".png";  SetIco[i]=CreateIMGHDRFromPngFile(SID.stri,0); }




if (FImage1->bpnum == 10)
{// режем нижнюю ленту
PIco[0] = CreateImgr(57, FImage1->h); drawimg2img( FImage1,PIco[0], 0, 0, 0, 0, 57, FImage1->h);
PIco[1] = CreateImgr(44, FImage1->h); drawimg2img( FImage1,PIco[1], 0, 0, 57, 0, 44, FImage1->h);
PIco[2] = CreateImgr(48, FImage1->h); drawimg2img( FImage1,PIco[2], 0, 0, 101, 0, 48, FImage1->h);
PIco[3] = CreateImgr(50, FImage1->h); drawimg2img( FImage1,PIco[3], 0, 0, 149, 0, 50, FImage1->h);
PIco[4] = CreateImgr(45, FImage1->h); drawimg2img( FImage1,PIco[4], 0, 0, 199, 0, 45, FImage1->h);
PIco[5] = CreateImgr(45, FImage1->h); drawimg2img( FImage1,PIco[5], 0, 0, 244, 0, 45, FImage1->h);
PIco[6] = CreateImgr(46, FImage1->h); drawimg2img( FImage1,PIco[6], 0, 0, 289, 0, 46, FImage1->h);
PIco[7] = CreateImgr(46, FImage1->h); drawimg2img( FImage1,PIco[7], 0, 0, 335, 0, 46, FImage1->h);
PIco[8] = CreateImgr(46, FImage1->h); drawimg2img( FImage1,PIco[8], 0, 0, 381, 0, 46, FImage1->h);
PIco[9] = CreateImgr(41, FImage1->h); drawimg2img( FImage1,PIco[9], 0, 0, 427, 0, 41, FImage1->h);
PIco[10] = CreateImgr(FImage1->w-468, FImage1->h); drawimg2img( FImage1,PIco[10], 0, 0, 468, 0, FImage1->w-468, FImage1->h);
mfree(FImage1);mfree(FImage1->bitmap);
}

lui_bob=7;UpdateScreen();DisableIconBar(1);REDRAW();


if (FImage8->bpnum == 10)
{// режем иконки для курсора нижней ленты
Ico[0] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[0], 0, 0, 5, 0, 35, FImage8->h);
Ico[1] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[1], 0, 0, 52, 0, 35, FImage8->h);
Ico[2] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[2], 0, 0, 99, 0, 35, FImage8->h);
Ico[3] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[3], 0, 0, 151, 0, 35, FImage8->h);
Ico[4] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[4], 0, 0, 201, 0, 35, FImage8->h);
Ico[5] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[5], 0, 0, 246, 0, 35, FImage8->h);
Ico[6] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[6], 0, 0, 291, 0, 35, FImage8->h);
Ico[7] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[7], 0, 0, 343, 0, 35, FImage8->h);
Ico[8] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[8], 0, 0, 389, 0, 35, FImage8->h);
Ico[9] = CreateImgr(35, FImage8->h); drawimg2img( FImage8,Ico[9], 0, 0, 433, 0, 35, FImage8->h);
mfree(FImage8);mfree(FImage8->bitmap);
}
lui_bob=8;UpdateScreen();DisableIconBar(1);REDRAW();

if (FImage5->bpnum == 10)
{ // режем часы
for (int i=0; i<10;i++) {Clock[i] = CreateImgr(40, 65); drawimg2img( FImage5,Clock[i], 0, 0, 0, 65*i, 40, 64);}
mfree(FImage5);mfree(FImage5->bitmap);}

lui_bob=9;UpdateScreen();DisableIconBar(1);REDRAW();

SetIco[10] = CreateImgr(183, 27); drawimg2img(SetIco[5],SetIco[10], 0, 0, 25, 1, 0, 0);
//================================== END
  if (!MD6) DisableIconBar(0);
  lui_bob=10; UpdateScreen();REDRAW();

}










int main(const char *exename, const char *filenm)
{
a = new MString;
b = new MString;
*a="ыыы)";
//ShowMSG(1,(int)a->stri);
delete a;
delete b;

//MString  *sms_text;
//MString  *sms_num;
//MString  *sms_time;

for (int i=0;i<40;i++){
sms_text[i]= new MString;
sms_num[i]= new MString;
sms_time[i]= new MString;
}

for (int i=0;i<40;i++) {colors[i]=(char *)malloc(4*sizeof(char));colors[i][3]=0x00;}//создали таблицу цветов
//start_set();

ussdws=AllocWS(256);
js = AllocWS( 256 );
e_ws = AllocWS( 255 );
filename = (char *)malloc (255);
seytitle= (char *)malloc (255); strcpy(seytitle,"     ");
seytext= (char *)malloc (255); strcpy(seytext,"     ");
//==================================================================================================
SUBPROC((void*)start_set);  
         LockSched();
         CSMROOT *csmr;
         CSM_RAM *save_cmpc;
         CSM_RAM main_csm;
         UpdateCSMname();
         csmr=CSM_root();
         save_cmpc=csmr->csm_q->current_msg_processing_csm;
         csmr->csm_q->current_msg_processing_csm=(CSM_RAM *)csmr->csm_q->csm.first;
         main_cms_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
         csmr->csm_q->current_msg_processing_csm=save_cmpc;
         UnlockSched();



         ConstructList();
         battery = *RamCap();
         net_data=RamNet();

         char *rules1=(char *)malloc(128);
         strcpy(rules1, BM4PIC_FR); FindFiles(rules1, 1,0);
         strcpy(rules1, BM3PIC_FR); FindFiles(rules1, 1,1);
         mfree(rules1);

       
         if (IsUnlocked())  GBS_StartTimerProc(&key_timer, TMR_SECOND/25, KeyRun);
         read_smsdat();
         return (0);
}
