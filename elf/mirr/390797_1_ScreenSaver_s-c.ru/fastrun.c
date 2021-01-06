//////////////////// Обьявляем переменные /////////////////////////

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
#define SCREENSIZE ScreenH()*ScreenW()
#define HSIZE YDISP*ScreenW()

int X_isfile (const char *names){
int f;
unsigned int err;
 f = fopen(names, A_ReadOnly, P_READ, &err ); 
   fclose(f,&err); 
 if ( f==-1 ) return 0; 
 else return 1;

}
int menustartX, menustartY, menuendX, menuendY;
int isKursor=0;
int isPodlojka=0;
int isBM1 = 0;
int isBM2 = 0;
int isBM3 = 0;
int isBM4 = 0;
int isBM5 = 0;
int isBM6 = 0;
int isBM7 = 0;
int isBM8 = 0;
int isBM9 = 0;
int isBM10 = 0;
int isBM11 = 0;
int isBM12 = 0;
int isBM13 = 0;
int isBM14 = 0;
int isBM15 = 0;

int menuMod = 0;  // 0 - менюшка, 1 - подтверждение удаления, 2 - меню редактирования, 
//3 - меню выбора иконки, 4 - меню выбора файла закладки. 5 - регистрация, 6 - О нас, 

int selected_d=0;
int DISK_d=0;


char * BM1PIC_ID;
char * BM2PIC_ID;
char * BM3PIC_ID;
char * BM4PIC_ID;
char * BM5PIC_ID;
char * BM6PIC_ID;
char * BM7PIC_ID;
char * BM8PIC_ID;
char * BM9PIC_ID;
char * BM10PIC_ID;
char * BM11PIC_ID;
char * BM12PIC_ID;
char * BM13PIC_ID;
char * BM14PIC_ID;
char * BM15PIC_ID;





  int lot =1; //
const int minus11=-11;

const char ipc_my_name[]=IPC_FASTRUN_NAME;

const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

int FASTRUNMENU_GUI_ID;// ИД гуя
int MENU_GUI_ID;// ИД гуя меню
int EMENU_GUI_ID;// ИД гуя eменю
int CONFMenuActive=0;
extern const char *successed_config_filename;
extern const char FILE_EMENU[128];
extern const int IDLE_GORIZO;
int IDLE_GORIZ;
extern unsigned int SOUND_11;
extern const int K1;
extern const int L1;
extern const int M1;
extern const int N1;
extern const int P1;
extern const int R1;
int redrawmenuX=0;
 int K;
 int L;
 int M;
 int N;
 int P;
 int R;
int lanchPD=0;
  int hFile = -1;
extern  const char PIC_ID_KUR1[128];
extern  const char PIC_ID_KUR[128];
extern void kill_data(void *p, void (*func_p)(void *));






 int book_1=8960; 
 int icon_1=9132;
 int book_2=9304; 
 int icon_2=9476;
 int book_3=9648; 
 int icon_3=9820;
 int book_4=9992; 
 int icon_4=10164;
 int book_5=10336; 
 int icon_5=10508;
 int book_6=10680; 
 int icon_6=10852;
 int book_7=11024; 
 int icon_7=11196;
 int book_8=11368; 
 int icon_8=11540;
 int book_9=11712; 
 int icon_9=11884;
 int book_10=12056; 
 int icon_10=12228;
 int book_11=12400; 
 int icon_11=12572;
 int book_12=12744; 
 int icon_12=12916;
 int book_13=13088; 
 int icon_13=13260;
 int book_14=13432; 
 int icon_14=13604;
 int book_15=13776; 
 int icon_15=13948;






//CSM_DESC icsmd;

//GUI *igui;
#define TMR_SECOND 216// секунда
GBSTMR idle_timer;
GBSTMR idle_timer2;
extern const int FR_CALL_BUTTON;// Кнопка активации панели FastRun
extern const int FR_EXIT_BUTTON;// Кнопка закрытия панели FastRun
//int Run;
extern const int IDLE_CALL_BUTTON;// Кнопка активации панели FastRun
extern const int IDLE_EXIT_BUTTON;// Кнопка закрытия панели FastRun
int mode_enter;
int idle_pic_size;
int fr_pic_size;
int ConfigUpdated;
 int IDLE_PIC_SIZE=16;
extern const int FR_PIC_SIZE;
extern const int ENA_FR_LONGPRESS;
extern const int ENA_IDLE_LONGPRESS;
extern const char colo[4];
extern IMGHDR * ScreenShot();
char *coloc;
extern const unsigned int LEN_ID;
extern const unsigned int LEN;
extern const unsigned int BEGIN;
extern const int DRAW_MODE;
extern const int IDLE_ENA;
extern const int FASTRUN_ENA;
//эффекты иконки --------------------
extern const int EFFECT;    //эффект "Свечение","Тень","Смазывание краев","ДЭ 1","ДЭ 2"
extern const unsigned int PAR1_ID; //"Размытость"
extern const unsigned int PAR2_ID;  //"Повторитель"
extern const unsigned int PAR3_ID;  //"Расширить картинку"

IMGHDR *ferdinand;
//эффекты иконки ^ ------------------

 unsigned int TEXT_FONT = 9;
int FR_KEYHOOK_ENA;
int IDLE_KEYHOOK_ENA;

char* percent_t="%t";
char *exen;
int NumOfItems_idle;// Число итемов меню 
int Selected_idle;// Позиция курсора
int NumOfItems_fr;
int Selected_fr;
int FastRunMenuActive;// Флаг активности меню
int IdleMenuActive;
extern const unsigned int xx1;
extern const unsigned int yy1;
unsigned int x1;
unsigned int y1;


unsigned char scrH, scrW;
int x1_fr;
int x2_fr;
int y1_fr;
int y2_fr;


void EditConfig()
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

int lenta;
extern const char cfgPanBorderCol1[4];
extern const char cfgPanBGCol1[4];
char cfgPanBorderCol[4];
char cfgPanBGCol[4];
extern const char cfgBookBorderCol[4];
extern const char cfgBookBGCol[4];
extern const char cfgPanBGCol_ID_ena[4];
extern const char cfgPanBGCol_ID_dis[4];
extern const char cfgBookBorderCol_ID[4];
extern const char cfgBookBGCol_ID[4];
const char cfg1_ID[4]={255,255,255,42};
const char cfg2_ID[4]={00,16,41,28};
const char co22[4]={00,00,20,252};
const char co23[4]={90,95,99,255};
const char co24[4]={10,40,80,255};
const char co25[4]={80,140,240,255};
const char co26[4]={90,180,255,255};
const char co27[4]={0,0,2,255};

const char co122[4]={20,00,00,252};
const char co123[4]={99,90,95,255};
const char co124[4]={80,10,40,255};
const char co125[4]={240,80,140,255};
const char co126[4]={255,90,180,255};
const char co127[4]={2,0,0,255};

const char cfg222_ID[4]={56,156,241,33};
const char cfg333_ID[4]={46,146,241,45};

const char cfg2222_ID[4]={241,56,156,33};
const char cfg3333_ID[4]={241,46,146,45};

extern const char BM1PIC_ID2[128];
extern const char BM2PIC_ID2[128];
extern const char BM3PIC_ID2[128];
extern const char BM4PIC_ID2[128];
extern const char BM5PIC_ID2[128];
extern const char BM6PIC_ID2[128];
extern const char BM7PIC_ID2[128];
extern const char BM8PIC_ID2[128];
extern const char BM9PIC_ID2[128];
extern const char BM10PIC_ID2[128];
extern const char BM11PIC_ID2[128];
extern const char BM12PIC_ID2[128];
extern const char BM13PIC_ID2[128];
extern const char BM14PIC_ID2[128];
extern const char BM15PIC_ID2[128];


extern const char BM_FOLDER_ID[128];
extern const char BM1FILE_ID[128];
extern const char BM2FILE_ID[128];
extern const char BM3FILE_ID[128];
extern const char BM4FILE_ID[128];
extern const char BM5FILE_ID[128];
extern const char BM6FILE_ID[128];
extern const char BM7FILE_ID[128];
extern const char BM8FILE_ID[128];
extern const char BM9FILE_ID[128];
extern const char BM10FILE_ID[128];
extern const char BM11FILE_ID[128];
extern const char BM12FILE_ID[128];
extern const char BM13FILE_ID[128];
extern const char BM14FILE_ID[128];
extern const char BM15FILE_ID[128];


extern const char BM1PIC_FR[128];
extern const char BM2PIC_FR[128];
extern const char BM3PIC_FR[128];
extern const char BM4PIC_FR[128];
extern const char BM5PIC_FR[128];
extern const char BM6PIC_FR[128];
extern const char BM7PIC_FR[128];
extern const char BM8PIC_FR[128];
extern const char BM9PIC_FR[128];
extern const char BM10PIC_FR[128];
extern const char BM11PIC_FR[128];
extern const char BM12PIC_FR[128];
extern const char BM13PIC_FR[128];
extern const char BM14PIC_FR[128];
extern const char BM15PIC_FR[128];

extern const char BM1FILE_FR[128];
extern const char BM2FILE_FR[128];
extern const char BM3FILE_FR[128];
extern const char BM4FILE_FR[128];
extern const char BM5FILE_FR[128];
extern const char BM6FILE_FR[128];
extern const char BM7FILE_FR[128];
extern const char BM8FILE_FR[128];
extern const char BM9FILE_FR[128];
extern const char BM10FILE_FR[128];
extern const char BM11FILE_FR[128];
extern const char BM12FILE_FR[128];
extern const char BM13FILE_FR[128];
extern const char BM14FILE_FR[128];
extern const char BM15FILE_FR[128];

//////////////////////////////////////////////////////////

int savefile2(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite32(f,buf,size,&err); 
  fclose(f,&err); 
  return i;
}

//------------------------------------------------------------------------------
char *loadfile2(char *filename){ // Загрузить файл, распак-ть
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      lenta=loadfilesize;
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
  } return buf;
}


//=============================================================================================================
int saveconf(){
  int *iteg;
  char *strokata;

if (DISK_d == 4)  strokata = loadfile2("4:\\ZBin\\etc\\FastRun_Imperial.bcfg");
else   strokata = loadfile2("0:\\ZBin\\etc\\FastRun_Imperial.bcfg");
if (x1<256) {strokata[7316]=x1; strokata[7317]=0;} 
if (y1<400) {if (y1<256) {strokata[7320]=y1; strokata[7321]=0;} else {strokata[7320]=y1-255; strokata[7321]=1;}}


iteg =(int *)&strokata[14288];
*iteg=K;
iteg=(int *)&strokata[14384];
*iteg=M;
strokata[14480]=P;
strokata[6880]=IDLE_GORIZ;

iteg=(int *)&strokata[14384];
*iteg=M;

iteg=(int *)&strokata[14432];
*iteg=N;

iteg=(int *)&strokata[14336];
*iteg=L;

if (DISK_d == 4) savefile2("4:\\ZBin\\etc\\FastRun_Imperial.bcfg", strokata, lenta);
else savefile2("0:\\ZBin\\etc\\FastRun_Imperial.bcfg", strokata, lenta);

  return 0;
}

int no( int f){
if (!f) return 2; else return 0;
}
//=================================================================== BOOKS&ICONS
int books(int bm)
{
  switch(bm)
  {
  case 0: return book_1;
  case 1: return book_2;
  case 2: return book_3;
  case 3: return book_4;
  case 4: return book_5;
  case 5: return book_6;
  case 6: return book_7;
  case 7: return book_8;
  case 8: return book_9;
  case 9: return book_10;
  case 10: return book_11;
  case 11: return book_12;
  case 12: return book_13;
  case 13: return book_14;
  case 14: return book_15;
  }
  return(0);
}

int icons(int bm)
{
  switch(bm)
  {
  case 0: return icon_1;
  case 1: return icon_2;
  case 2: return icon_3;
  case 3: return icon_4;
  case 4: return icon_5;
  case 5: return icon_6;
  case 6: return icon_7;
  case 7: return icon_8;
  case 8: return icon_9;
  case 9: return icon_10;
  case 10: return icon_11;
  case 11: return icon_12;
  case 12: return icon_13;
  case 13: return icon_14;
  case 14: return icon_15;
  }
  return(0);
}
//=============================================================================================================
void uppd();
int saveconf2(){
  char *strokata;
  char *impresso = malloc (127);
  char *impresso2 = malloc (127);  
  char *nimnogo = "\x00";
if (DISK_d == 4)  strokata = loadfile2("4:\\ZBin\\etc\\FastRun_Imperial.bcfg");
else   strokata = loadfile2("0:\\ZBin\\etc\\FastRun_Imperial.bcfg");

for (int i=Selected_idle; i<15; i++) {
impresso = &strokata[icons(i)];
impresso2 = &strokata[icons(i+1)];
strcpy (impresso, impresso2);
}
impresso = &strokata[icons(14)];
strcpy (impresso, nimnogo);

for (int i=Selected_idle; i<15; i++) {
impresso = &strokata[books(i)];
impresso2 = &strokata[books(i+1)];
strcpy (impresso, impresso2);
}
impresso = &strokata[books(14)];
strcpy (impresso, nimnogo);


if (DISK_d == 4) savefile2("4:\\ZBin\\etc\\FastRun_Imperial.bcfg", strokata, lenta);
else savefile2("0:\\ZBin\\etc\\FastRun_Imperial.bcfg", strokata, lenta); 
uppd();
  return 0;
}


