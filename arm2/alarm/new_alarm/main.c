#include "..\..\inc\swilib.h"
#include "..\alarm.h"

void check();
void start_ring();
void load_settings();

GBSTMR *restarttmr;

unsigned int hour[5];
unsigned int min[5];
unsigned int status[5];
unsigned int weekdays[5][7];
int show_icon=0;
int status_icon=0;
int X;
int Y;
int imgw;
int imgh;

GBSTMR mytmr;
TDate date;
TTime time;
TDate week;

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

#ifdef NO_PNG
typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w; 
  char h; 
  char Compr_Bits;  
}PICHDR;

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void DrawGPF(char *fname, int x, int y)
{
  volatile int hFile;
  PICHDR Pic_Header;
  unsigned int io_error = 0;
  hFile = fopen(fname, A_ReadOnly + A_BIN, P_READ, &io_error);
  if(!io_error)
  {
    fread(hFile, &Pic_Header, sizeof(Pic_Header), &io_error);
    unsigned int buf_size = lseek(hFile, 0, S_END, &io_error, &io_error) - sizeof(PICHDR);
    lseek(hFile, sizeof(PICHDR), S_SET, &io_error, &io_error); 
    char *pic_buffer = malloc((buf_size+3)&(~3));
    fread(hFile, pic_buffer, buf_size, &io_error);    
    fclose(hFile, &io_error);
    IMGHDR img;
    img.w = Pic_Header.w;
    img.h = Pic_Header.h;
    img.bpnum = Pic_Header.Compr_Bits;
    img.bitmap = pic_buffer;
    DrwImg(&img, x, y, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    mfree(pic_buffer);
  }
}

void getimgwh()
{
  volatile int hFile;
  PICHDR Pic_Header;
  unsigned int io_error = 0;
  hFile = fopen(icon, A_ReadOnly + A_BIN, P_READ, &io_error);
  if(!io_error)
  {
    fread(hFile, &Pic_Header, sizeof(Pic_Header), &io_error);
    fclose(hFile, &io_error);
    imgw=Pic_Header.w;
    imgh=Pic_Header.h;
  }
}
#else
void getimgwh()
{
  imgw=GetImgWidth((int)icon);
  imgh=GetImgHeight((int)icon);
}
#endif

void update_status()
{
  if (status[0] || status[1] || status[2] || status[3] || status[4])
  {
    status_icon=1;
  }
   else status_icon=0;
}

void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(64);
    fread(handle,data,60,&err);

status[0]=data[2];
hour[0]=data[3];
min[0]=data[4];
weekdays[0][0]=data[5];
weekdays[0][1]=data[6];
weekdays[0][2]=data[7];
weekdays[0][3]=data[8];
weekdays[0][4]=data[9];
weekdays[0][5]=data[10];
weekdays[0][6]=data[11];
status[1]=data[12];
hour[1]=data[13];
min[1]=data[14];
weekdays[1][0]=data[15];
weekdays[1][1]=data[16];
weekdays[1][2]=data[17];
weekdays[1][3]=data[18];
weekdays[1][4]=data[19];
weekdays[1][5]=data[20];
weekdays[1][6]=data[21];
status[2]=data[22];
hour[2]=data[23];
min[2]=data[24];
weekdays[2][0]=data[25];
weekdays[2][1]=data[26];
weekdays[2][2]=data[27];
weekdays[2][3]=data[28];
weekdays[2][4]=data[29];
weekdays[2][5]=data[30];
weekdays[2][6]=data[31];
status[3]=data[32];
hour[3]=data[33];
min[3]=data[34];
weekdays[3][0]=data[35];
weekdays[3][1]=data[36];
weekdays[3][2]=data[37];
weekdays[3][3]=data[38];
weekdays[3][4]=data[39];
weekdays[3][5]=data[40];
weekdays[3][6]=data[41];
status[4]=data[42];
hour[4]=data[43];
min[4]=data[44];
weekdays[4][0]=data[45];
weekdays[4][1]=data[46];
weekdays[4][2]=data[47];
weekdays[4][3]=data[48];
weekdays[4][4]=data[49];
weekdays[4][5]=data[50];
weekdays[4][6]=data[51];

show_icon=data[53];
X=data[54];
Y=data[55];

    mfree(data);
    fclose(handle,&err);
  }
  getimgwh();
  update_status();
}

void start_ring()
{
  WSHDR *ws;
  ws=AllocWS(64);
  str_2ws(ws,alarm_ring_elf,strlen(alarm_ring_elf)+1);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void alarm(int n)
{
  if (status[n])
  {
    TDate date;
    GetDateTime(&date, 0);
    char wd = GetWeek(&date);
    if (weekdays[n][wd])
      {
        GetDateTime(&date,&time);
        if (time.hour==hour[n])
          {
            if (time.min==min[n])
              {
                start_ring();
              }
          }
      }
  }
}

void start_check(void)
{
  for (int i=0;i<5;i++)
  {
    alarm(i);
  }
  
  GBS_StartTimerProc(&mytmr,216*60,start_check);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc=(IPC_REQ*)((msg)->data0);
    if (ipc)
    {
      if (strcmp_nocase(ipc->name_to,"alarm") == 0)
      {
        int time2 = msg -> submess;
        GBS_StartTimerProc(&restarttmr,216*60*time2,start_ring);
      }
    }
  }
  
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
          void *idata = GetDataOfItemByID(igui, 2);
          if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          if((IsUnlocked())&&(show_icon)&&(status_icon))
          {
            DrawCanvas(canvasdata, X, Y, X + imgh, Y + imgh, 1);
#ifdef NO_PNG
            DrawGPF(icon,X,Y);
#else
            DrawImg(X, Y, (int)icon);
#endif
          }
        }
      }
    }
  }
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    if (strcmp_nocase("alarm",(char *)msg->data0)==0)
    {
      load_settings();
    }
  }

  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  start_check();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"alarm");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  load_settings();
  UpdateCSMname();

  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}

