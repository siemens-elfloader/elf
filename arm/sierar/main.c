#include "C:\arm\inc\swilib.h"
#include "rect_patcher.h"
#include "funcs.c"
//#include <math.h>
#include "main.h"
//#include "externs.h"
#define HEADER 2560
#define TAB 4
#define IMG 0x01
int lines=0;
int pos=0;
IMGHDR *not_found;
struct
{
  int x,y,width,height,font;
}field;
int images[5][2];
int num_images;

char *Buf;
char *Str;

char *GetExt(char *fname){return strrchr(fname,'.')+1;}
char *GetFileName(char *fname){return strrchr(fname,'\\')+1;}

void DrawAllImg();
void DrawText(char *str);

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  WSHDR *ws5;
  int i1;
}MAIN_GUI;



static void OnRedraw(MAIN_GUI *data)
{
  DrawText(Str);
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
#ifdef ELKA//Если елка,то отключаем иконбар
DisableIconBar(1);
#endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->ws5=AllocWS(256);
  data->gui.state=1;
  
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    for(int i=0;i<num_images;i++)
  {
//    mfree(images[i]);
  }
    mfree(Buf);
    mfree(Str);
  data->gui.state=0;
  FreeWS(data->ws1);//освобождаем память
  FreeWS(data->ws5);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
char ss[64];

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case '4':if(field.x<0){field.x+=GetSymbolWidth(0,field.font);}break;
    case '6':field.x-=GetSymbolWidth(0,field.font);break;
    case '2':if(field.y<0){field.y+=GetFontYSIZE(field.font);}break;
    case '8':field.y-=GetFontYSIZE(field.font);break;
    case '0':sprintf(ss,"x:%d y:%d",images[0][0],images[0][1]);ShowMSG(1,(int)ss);break;
    case '1':break;
    }
    DirectRedrawGUI();
  }
  
 return(0); 
}



extern void kill_data(void *p, void (*func_p)(void *));//Эта функция убивает эльф и освобождает память

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)//Вызывается при открытии эльфа,делаем что нужно
{
  //тут хитрые махинации для получения ид гуя чтобы мона было с ним манипулировать
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем памчть если нужно и т.п.
{
  mfree(not_found);
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//тут вообщем протекают все сообщения поступаемые из эльфа так сказать:)
{
  //сообщение о реконфигурации например,ипц и т.д. и т.п.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }

  return(1);
}


static const struct//это структура цсм,разбираться не надо:)
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


void UpdateCSMname(void)//ну собственно имя эльфа передаваемое хтаску
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SieDoc Viewer");
}

int ReadBytes(char *fname,char *Buf,int size)
{
  unsigned int err=0;
  int f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err);
  if(f!=-1)
  {
    lseek(f,HEADER,S_SET,&err,&err);
    int sz=fread(f,Buf,size,&err);
    fclose(f,&err);
    return sz;
  }
  else return 0;
}

void DrawText(char *str)
{
  WSHDR *text=AllocWS(strlen(str));
  wsprintf(text,str);
  DrawRectangle(0,0,239,319,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  DrawString(text,field.x,field.y,field.width,field.height,field.font,0,GetPaletteAdrByColorIndex(1),NULL);
  DrawAllImg();
  FreeWS(text);
}

void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}


void AddImage(int x,int y)
{
  num_images++;
  //*images=realloc(*images,num_images);
  images[num_images][0]=x;
  images[num_images][1]=y;
}
void DrawAllImg()
{
  for(int i=0;i<num_images;i++)
  {
    DrwImg(not_found,images[i][0],images[i][1]);
  }
}
void GetTextFromDoc(char *fname)
{
  FSTATS fs;
  GetFileStats(fname,&fs,0);
  if(fs.size*2<GetFreeRamAvail()-500*1024)
  {
  Buf=realloc(Buf,fs.size);
  Str=realloc(Buf,fs.size);
  int sz=ReadBytes(fname,Buf,fs.size);
  for(int b=0,i=0;i<512;i++,b++)
  {
     switch(Buf[i])
    {
    case '\t':for(int n=b;b<n+TAB;b++)Str[b]=' ';b--;pos++;continue;
    case '\n':case '\r':Str[b]=Buf[i];lines++;pos=0;continue;
 //   case IMG:AddImage((pos+1)*GetSymbolWidth(0,field.font),(lines+1)*GetFontYSIZE(field.font));pos++;continue;
    default:Str[b]=Buf[i];pos++;continue;
    }
    
  }    



  }
  //dos2win(Str,Str);

}



int main(char *exename, char *fname)//exename-путь запускаемого эльфа, fname параметр передаваемый эльфу
{

  MAIN_CSM main_csm;
  LockSched();
  not_found=CreateIMGHDRFromPngFile("0:\\1.png", 2);
  UpdateCSMname();//обновляем имя для хтаска
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
  UnlockSched();
  field.x=0;
  field.y=0;
  field.font=9;
  field.width=239*10;
  field.height=319*10;
  Buf=malloc(1);
  Str=malloc(1);
  //*images=malloc(1);
  GetTextFromDoc(fname);
  return 0;
  }
