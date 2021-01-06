#define IPC_FASTRUN_NAME "MD_TouchFlo"
#define IPC_UPDATE_STAT 10
#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
#define SCREENSIZE ScreenH()*ScreenW()
#define HSIZE YDISP*ScreenW()

unsigned int err;

int X_isfile (const char *names){ //cуществует ли файл?
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

int *GUI_ID_STR;// ИД гуя
int MENU_GUI_ID;// ИД гуя меню

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
#define TMR_SECOND 216// секунда
GBSTMR idle_timer; //проверка идла
GBSTMR key_timer;
GBSTMR time_timer;
GBSTMR adr_timer;
extern const int FR_CALL_BUTTON;// Кнопка активации панели FastRun
extern const int FR_EXIT_BUTTON;// Кнопка закрытия панели FastRun
//int Run;
extern const int IDLE_CALL_BUTTON;// Кнопка активации панели FastRun
extern const int IDLE_EXIT_BUTTON;// Кнопка закрытия панели FastRun
int mode_enter;
int idle_pic_size;
int fr_pic_size;
int ConfigUpdated;
int adr_up = 0;
int adr_down = 0;
int net_up = 0;
int net_down = 0;
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
//int EFFECT = 4;
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
const char co21[4]={212,212,212,252};
const char co22[4]={72,72,72,252};
const char co22v[4]={215,215,215,70};
const char co22z[4]={215,215,215,50};
const char co22x[4]={235,235,235,30};
const char co22s[4]={235,235,235,20};
const char co23[4]={0,0,0,98};
const char co24[4]={50,50,50,255};
const char co24mod[4]={40,40,40,255};
const char co25[4]={0,0,0,56};
const char co25sd[4]={0,0,0,76};
const char co25mod[4]={20,20,20,255};
const char co25mod2[4]={20,20,20,70};
const char co25zer[4]={0,0,0,0};
const char co26[4]={90,180,255,255};
const char co27[4]={0,0,0,95};
const char co27a[4]={0,0,0,20};
const char co122[4]={20,20,20,252};
const char co123[4]={99,90,95,255};
const char co124[4]={80,10,40,255};
const char co125[4]={240,80,140,255};
const char co126[4]={240,240,240,255};
const char co126x[4]={240,240,240,6};
const char co126y[4]={240,240,240,13};
const char co127[4]={2,0,0,255};
const char co25black[4]={0,0,0,255};
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



