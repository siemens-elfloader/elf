#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

long int cpu_usage;
char cable[128];
int veidi;
int calculate_sec;
int TempLow;
GBSTMR calcul;
int TempUp;
int Accum;
int charge_time;
char show_info[64];
int calculate_sec2;
int var_cpu;
////////font
extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const char fontpath[64];
int font=1;
int align=0;
int space=1;
void *canvasdata;
///////font


CSM_RAM *under_idle;

void calculate(void);

void writefile2()
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\discharge_calculated.txt",&stat,&ul);
    char *text=malloc(256);
    sprintf(text, "total cpu usage: %d; calculate sec:%d", cpu_usage,calculate_sec2);
    hFile = fopen("4:\\discharge_calculated.txt",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, text, strlen(text), &io_error);
      fclose(hFile, &io_error);
    }
    mfree(text);
}

int ten_time;
int ten_time_cpu;

void calculate_discharge(void);

void get_ten_times()
{
  if(ten_time<10)
  {
    ten_time++;
    ten_time_cpu=ten_time_cpu+GetCPULoad();
    GBS_StartTimerProc(&calcul, 216, get_ten_times);
  }
  else
  {
    ten_time_cpu=ten_time_cpu / 10;
  calculate_discharge();
  }
}

void calculate_discharge()
{
  sprintf(show_info, "Recharged");
  *cable=GetAccessoryType();
  if(strlen(cable)==0)
  {
    sprintf(show_info, "Calculating Discharge");
    if(*RamCap()>=5)
    {
      ten_time=0;
      calculate_sec2=calculate_sec2+10;
      cpu_usage=cpu_usage+ten_time_cpu;
      ten_time_cpu=0;
      get_ten_times();
//      GBS_StartTimerProc(&calcul, 216*10, calculate_discharge);
    }
    else
    {
//      var_cpu=(cpu_usage/(calculate_sec2/10));
      writefile2();
    }
  }
  else
    GBS_StartTimerProc(&calcul, 216*10, calculate_discharge);
}

void writefile1()
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\charge_calculated.txt",&stat,&ul);
    char *text=malloc(256);
    sprintf(text, "calculate sec:%d; Accum charge:%d", calculate_sec,Accum);
    hFile = fopen("4:\\charge_calculated.txt",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, text, strlen(text), &io_error);
      fclose(hFile, &io_error);
    }
    mfree(text);
}

void calculate()
{
  *cable=GetAccessoryType();
  if(strlen(cable)>0)
  {
  switch(veidi)
  {
  case 0:
    calculate_sec=0;
    veidi=1;
    TempLow=*RamCap();
    GBS_StartTimerProc(&calcul, 216, calculate);
    sprintf(show_info, "Calculating recharge");
    break;
  case 1:
    calculate_sec++;
    if(*RamCap()>=95) veidi=2;
    GBS_StartTimerProc(&calcul, 216, calculate);
    break;
  case 2:
    veidi=3;
    TempUp=*RamCap();
    Accum=TempUp-TempLow;
//    charge_time=calculate_sec/Accum;
    writefile1();
    calculate_discharge();
    break;
  case 3:
    GBS_StartTimerProc(&calcul, 216, calculate_discharge);
    break;
  }
  }
  else
  {
    veidi=0;
    sprintf(show_info, "No Charger");
      GBS_StartTimerProc(&calcul, 216, calculate);
  }
}

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Extended battery config updated");
      FontPathFree();
      InitConfig();
      FontPathInit(font,(char *)fontpath, 0);
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //???? IdleGui ?? ????? ?????
    {
      GUI *igui=GetTopGUI();
      if (igui) //? ?? ??????????
      {
        canvasdata=BuildCanvas();   
        PrintField(date_X,date_Y, show_info, align, font, space);
      }
    }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  GBS_DelTimer(&calcul);
  FontPathFree();
  extern void *ELF_BEGIN;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Extended battery (c)Evilfox");
}

int main()
{
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int ENA_HELLO_MSG;
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"Extended battery (c)Evilfox");  
  FontPathInit(font,(char *)fontpath, 0);
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\charge_calculated.txt",&stat,&ul);
  if(stat.size>2)
  calculate_discharge();
  else
  calculate();
  return 0;
}
