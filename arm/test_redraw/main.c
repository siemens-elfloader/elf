#include "..\inc\swilib.h"
#include "conf_loader.h"

//-------------------------------------------------------------------------------

#pragma swi_number=0x8300
__swi __arm  int isSGoldX75();

#pragma swi_number=0x0301
__swi __arm  int EDL_load(char *fname);

#pragma swi_number=0x0302
__swi __arm  int EDL_unload(char *name, short version);

#pragma swi_number=0x0303
__swi __arm  int EDL_addlib(void *edl_struct);

#pragma swi_number=0x0304
__swi __arm  int EDL_remove(void *edl_struct);

#pragma swi_number=0x0305
__swi __arm  int EDL_use(char *name, short version, void *func_struct);

#pragma swi_number=0x0306
__swi __arm  int EDL_neitralize(char *name_check, short version_check, short count, int msg, char *name, short version,  void *func_struct);

#pragma swi_number=0x0307
__swi __arm  int isEDL_exist(char *name, short version);

#pragma swi_number=0x0308
__swi __arm  int isEDL_support(char platform, char *phone, short sw);

#pragma swi_number=0x0309
__swi __arm void *getEDL_baseAddr();

#pragma swi_number=0x030A
__swi __arm  int getEDL_curLibs();

#pragma swi_number=0x030B
__swi __arm  int getEDL_maxLibs();

#pragma swi_number=0x030C
__swi __arm  int SetSWIHookInRAMState();

#pragma swi_number=0x030D
__swi __arm void SetSWINumInCashe(short swinum);

#pragma swi_number=0x030E
__swi __arm  int RunSWIFromCashe(void *R0, ...);

#pragma swi_number=0x030F
__swi __arm  int SetSWIFunc(void *addrfunc, short swinum);

#pragma swi_number=0x0310
__swi __arm  int RepairSWIFunc(short swinum);

#pragma swi_number=0x0311
__swi __arm  int RepairSWILib();

#define DHS_FIRST_ITEM  (DHS_ITEM *)0xBAD0
#define DHS_LAST_ITEM   (DHS_ITEM *)0xBAD1
#define DHS_NULLITEM    (DHS_ITEM *)-1
#define DHS_ZERO         0
#define DHS_NULL        -1

#define DHS_LOCKDRAW     1
#define DHS_UNLOCKDRAW   0

#define DHS_UNLOCKDVALUE 0xDB6DB6DB





typedef struct{
  char   id_1;      // ID = 1
  char   cbyte;     // 0x00, 0x10
  char   zero;      // 0x00
  char   pen[4];    // Цвет PEN   (или int pen)
  char   brush[4];  // Цвет BRUSH (или int brush)
  RECT   rc;        // Координаты/Границы отображаемого текста 
  WSHDR *text;      // WSHDR (Сам текст)
#ifdef NEWSGOLD
  int    font;      // Шрифт текста 
#else
  short  font;      // Шрифт текста 
#endif
  short  align;     // Выравнивание текста  
  short  xdisp;     // Смещение текста по X
}DRWOBJ_01;

typedef struct{
  char   id_3;      // ID = 3
  char   cbyte;     // 0x00, 0x10
  char   zero;      // 0x00
  char   pen[4];    // Цвет PEN   (или int pen)
  char   brush[4];  // Цвет BRUSH (или int brush)
  RECT   rc;        // Координаты/Границы отображаемого текста 
  WSHDR *text;      // WSHDR (Сам текст)
#ifdef NEWSGOLD
  int    font;      // Шрифт текста 
#else
  short  font;      // Шрифт текста 
#endif
  short  align;     // Выравнивание текста  
  short  xdisp;     // Смещение текста по X
}DRWOBJ_03;

typedef struct{
  char   id_3;      // ID = 3
  char   cbyte;     // 0x00, 0x10
  char   zero;      // 0x00
  char   pen[4];    // Цвет PEN   (или int pen)
  char   brush[4];  // Цвет BRUSH (или int brush)
  RECT   rc;        // Координаты/Границы отображаемого текста 
  IMGHDR *img;  
  short  align;     // Выравнивание текста  
  short  xdisp;     // Смещение текста по X
  short  uuu;     // Смещение текста по X
}DRWOBJ_05;



typedef struct {
  void (*dh_proc)(LCDLAYER *);
  void  *prev;
  void  *next;
}DHS_ITEM;

typedef struct {
  DHS_ITEM *first;
  int       count;
  int       unlock;
}DHS_TOP;

#pragma swi_number=0x0319
__swi __arm  int DHS_addProc(void (*dh_proc)(LCDLAYER *));

#pragma swi_number=0x031A
__swi __arm  int DHS_removeProc(void (*dh_proc)(LCDLAYER *));

#pragma swi_number=0x031B
__swi __arm  void DHS_lockDraw(int lock);

#pragma swi_number=0x031C
__swi __arm  DHS_TOP *DHS_getBaseItem();

#pragma swi_number=0x031D
__swi __arm  int DHS_getStatusItem(void (*dh_proc)(LCDLAYER *));

#pragma swi_number=0x031E
__swi __arm  int DHS_workProcPrio(void (*dh_proc)(LCDLAYER *), int work);

#pragma swi_number=0x0F5
__swi __arm  LCDLAYER *Ram_LCD_Overlay_Layer();


//------------------------------------------------------------------------------------

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

//extern  int PushObjectOnLAYER(DRWOBJ_S*, LCDLAYER *);

void DrwImg(IMGHDR *img, LCDLAYER *layer, int x, int y, char *pen, char *brush) //Отрисовка IMGHDR
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  PushDRWOBJOnLAYER((DRWOBJ_S *)&drwobj, layer);
}

GBSTMR tmr;

int IsIDLE()
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return(1);
                                                           else return(0);
}

int ti = 0;

//extern void LCDRedrawLAYER(LCDLAYER *layer);

void MyDraw(LCDLAYER *layer)
{
  
    DHS_TOP *dhs_top = DHS_getBaseItem();
    WSHDR *ws = AllocWS(64);
    wsprintf(ws, "DHC: %d, ST: %d",  dhs_top->count,  DHS_getStatusItem(MyDraw));
    DRWOBJ_01 drw = {1, 0x10, 0, 255, 255, 255, 100, 0, 0, 0, 100, 2, 2, 132, 176, (WSHDR *)ws, 8, TEXT_OUTLINE, 0};
    PushDRWOBJOnLAYER((DRWOBJ_S *)&drw, layer);
    FreeWS(ws);
  
  
  
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
      ShowMSG(1,(int)"NSD config updated!");
      InitConfig();
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&tmr);
  DHS_lockDraw(0);
  DHS_removeProc(MyDraw);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"(c)Dimadze");
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
  DHS_addProc(MyDraw);
  return 0;
}
