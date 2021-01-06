//Параметры оптимизации - максимальная оптимизация по скорости, при этом все флаги выключены. Иначе может быть кака
#include "mainmenu.h"
#include "..\inc\swilib.h"
#include "..\inc\xtask_ipc.h"
#include "conf_loader.h"
#include "language.h"
#include "main.h"
#include "playlists.h"

//#include "..\inc\MATH.h"
//#define PI 3.1415926535
extern const unsigned int IDLEICON_X,IDLEICON_Y,EnableIconOnIdle;
#ifdef X75
#define MAXVOLUME 14
#else
#define MAXVOLUME 4
#endif
int pisniashchozberigaetsia=0,identyfikator;
const char ipc_my_name[32]="Ivoplay";
GBSTMR RedrawTimer,TimeTimer,PlayerMenu,PlayNextTimer,Scroll;
int CanPlayNext=1;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;
int top,selected;
char spysok[2][255][128];//Максимальное количество песен - 255 (1 байт при сохранении)
int spysokselected[255];
long timelength[255];
int curskin=0;// Текущий скин
char ArrayOfSkins[100][20];//Скинов 100 максимум
int playlistmode=0;//0-запуск файла без параметрів, 1- зі списком ipl, 2 - з m3u, 3 - режим медіатеки, 4 - з мс
char LastPlaylist[256],playlistname[255];
int notplayed[255];//Масив. Отмечается, какая песня игралась, а какая нет (при случайном порядке)
char calbum[128]=" ",ctrack[128]=" ",cartist[128]=" "; //Теги
char NameOfCurentTrack[128]="";
int random=0,NumberOfSkins=0;
int timehms[3];//Time:hour,minute,second
int timesec=0,timemin=0,JaPerekliuchyvPisniu=0,NeedToStop=0,WhatToView=0;
int cp=0,NumberOfTracks=0,CurentVolume=4,playing=0,ringoff=0,pracuje=0;
int PLAY_ID=0xFFFF;
extern const char playerfolder[128],folder[128];
extern const char format_1[4],format_2[4],format_3[4],format_4[4];
extern const int Key1,Key2,Key3,Key4,Key5,Key6,Key7,Key8,Key9,Key0,KeyZ,KeyR;//Настройки клавиш. Лучше бы их в файл вынести, но пока так
extern const unsigned int RedrawTime;//Время перерисовки
extern const int entime;//А перерисовывать ли?
extern const unsigned int profile1,profile2,profile3,profile4,profile5,profile6,profile7,profile8;
const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
extern const int EnableHook;
int xdisp=1;
char PlaylistToSave[255];

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

typedef struct
{
  WSHDR *ws1;
  WSHDR *ws2;
}rr;
rr wss;

void CLOSECURENTCSM()
{
  CloseCSM(MAINCSM_ID);
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

/*typedef struct
{
  char *backgroundname;
  int progressbarconst;
  char *progressbarname;
  WSHDR *PLAYLIST;
  WSHDR *TRACK;
  WSHDR *NUMBEROFTRACKS;
  char *offname;
  char *randomname;
  char *plusname;
  char *minusname;
  char *stopname;
  char *playname;
  char *prevname;
  char *nextname;
}RedrawStruct;
RedrawStruct pisnia;*/



int spysokx1=1,spysoky1=50,spysokx2=132,spysoky2=176,spysokfont=8,spysoktextattribute=2,spysoktextcolor=1,spysoktextbackground=23;
int timex1=1,timey1=134,timex2=132,timey2=176,timefont=7,timetextattribute=2,timetextcolor=1,timetextbackground=23;
int songx1=1,songy1=67,songx2=132,songy2=176,songfont=7,songtextattribute=0,songtextcolor=1,songtextbackground=23;
int tracksx1=1,tracksy1=1,tracksx2=132,tracksy2=176,tracksfont=7,trackstextattribute=4,trackstextcolor=1,trackstextbackground=23;
int volumex=1,volumey=157;
int randomx=2,randomy=2;
int ringoffx=25,ringoffy=2;
int prevx=45,prevy=18;
int nextx=74,nexty=18;
int volpx=61,volpy=5;
int volmx=61,volmy=30;
int play_stopx=62,play_stopy=19;
int progressbarx1=2,progressbary1=165,progressbarx2=132,progressbarcolour=20;
int katalogbackgroundcolour=9,katalogfontcolour=1,katalogselectedcolour=14;
char name[256];
void readskinparamsfromfile()
{
  int f;
  char list[20000];
  sprintf(name,"%sskins\\%s\\params.txt",playerfolder,ArrayOfSkins[curskin]);
  unsigned int err;
  f=fopen(name, A_ReadOnly+A_MMCStream, P_READ, & err );
  if (f!=-1)
  {
  DIR_ENTRY de;
  FindFirstFile(&de,name,&err);
  fread(f,list,de.file_size,&err);
  char num[5];
  sprintf(num,pp);
  int i=0;
while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoky1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoky2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextbackground);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timex1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timey1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timex2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timey2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timefont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextbackground);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextbackground);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextbackground);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volumex);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volumey);
  i=i+2;
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&randomx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&randomy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&ringoffx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&ringoffy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&prevx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&prevy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&nextx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&nexty);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volpx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volpy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volmx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volmy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&play_stopx);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&play_stopy);
  i=i+2;
  sprintf(num,pp);
 while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarx1);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbary1);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarx2);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarcolour);
  i=i+2;
  sprintf(num,pp);
   while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}
  i=i+2;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogbackgroundcolour);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogfontcolour);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogselectedcolour);
  i=i+2;
  sprintf(num,pp);
  FindClose(&de,&err);
  }
  fclose(f,&err);
}

void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

void patch_header2(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

int sf_inp_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);
    ws_2str(ec.pWS,PlaylistToSave,255);
    SUBPROC((void *)SavePlaylist);
    return(1); //Close
  }
  return(0);
}

void sf_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)LG_SAVE};
  EDITCONTROL ec;
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
  }
}

void sf_inp_locret(void){}

HEADER_DESC sf_inp_hdr={0,0,0,0,NULL,(int)LG_ENTER_NAME,LGP_NULL};

INPUTDIA_DESC sf_inp_desc=
{
  1,
  sf_inp_onkey,
  sf_inp_ghook,
  (void *)sf_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void CreateSaveAsDialog(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  utf8_2ws(wss.ws2,PlaylistToSave,126);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,wss.ws2,128);
  AddEditControlToEditQend(eq,&ec,ma);
  
  patch_header2(&sf_inp_hdr);
  patch_input(&sf_inp_desc);
  CreateInputTextDialog(&sf_inp_desc,&sf_inp_hdr,eq,1,0);
}

void VporiadkuvatySpysok()
{
  for (int i=0;i<NumberOfTracks-1;i++)
  {
    for (int j=i+1;j<NumberOfTracks;j++)
    {
      if (strcmp(spysok[1][i],spysok[1][j])>0)
      {
        sprintf(name,spysok[0][i]);
        sprintf(spysok[0][i],spysok[0][j]);
        sprintf(spysok[0][j],name);
        sprintf(name,spysok[1][i]);
        sprintf(spysok[1][i],spysok[1][j]);
        sprintf(spysok[1][j],name);
      }
    }
  }
}
    
int GetKatalogfontcolour()
{
  return(katalogfontcolour);
}

char katalog[256][128];
int kataloglength,katalogcurent;
int katalogselected[256];
char curentfolder[255]="4:";
/*
char folders[128][128];
int kfolders;
char files[128][128];
int kfiles;

void VporiadkuvatyKatalog()
{
  if (kfiles>1)
  {
    for (int i=0;i<kfiles-1;i++)
    {
      for (int j=i+1;j<kfiles;j++)
      {
        if (strcmp(files[i],files[j])>0)
        {
          sprintf(name,files[i]);
          sprintf(files[i],files[j]);
          sprintf(files[j],name);
        }
      }
    }
  }
  if (kfolders>1)
  {
    for (int i=0;i<kfolders-1;i++)
    {
      for (int j=i+1;j<kfolders;j++)
      {
        if (strcmp(folders[i],folders[j])>0)
        {
          sprintf(name,folders[i]);
          sprintf(folders[i],folders[j]);
          sprintf(folders[j],name);
        }
      }
    }
  }
}
*/
void ZapovnytyTaVidsortuvatyKatalog(char *folder)
{
  DIR_ENTRY de;
  unsigned int err;
  char path[256];
  kataloglength=1;
  sprintf(katalog[0],"..");
  /*kfolders=0;
  kfiles=0;*/
  sprintf(path,"%s\\*",folder);
  katalogcurent=0;
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      char extension[3];
      char file_name[128];
      sprintf(file_name,de.file_name);
      if (IsFile(file_name))
      {
        sprintf(extension,"%c%c%c",file_name[strlen(file_name)-3],file_name[strlen(file_name)-2],file_name[strlen(file_name)-1]);
        if (((strcmp(extension,format_1))==0)||((strcmp(extension,format_2))==0)||((strcmp(extension,format_3))==0)||((strcmp(extension,format_4))==0))
        {
          sprintf(katalog[kataloglength],file_name);
          kataloglength++;
        }
      }
      else
      {
        sprintf(katalog[kataloglength],file_name);
        kataloglength++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  /*for (int i=1;i<kataloglength;i++)
  {
    if (IsFile(katalog[i]))
      {
        sprintf(files[kfiles],katalog[i]);
        kfiles++;
      }
      else
      {
        sprintf(folders[kfolders],katalog[i]);
        kfolders++;
      }
  }
  VporiadkuvatyKatalog();
  kataloglength=1+kfolders+kfiles;
  for (int i=1;i<kfolders+1;i++)
  {
    sprintf(katalog[i],folders[i+1]);
  }
  for (int i=kfolders+1;i<kataloglength;i++)
  {
    sprintf(katalog[i],files[i+1-kfolders]);
  }
  sprintf(name," %i %i",kfiles,kfolders);
  ShowMSG(1,(int)name);*/
  if (kataloglength>1) {katalogcurent=1;}
  
  if (kataloglength>2)
  {
    for (int i=1;i<kataloglength-1;i++)
    {
      for (int j=i+1;j<kataloglength;j++)
      {
        if (strcmp_nocase(katalog[i],katalog[j])>0)
        {
          sprintf(name,katalog[i]);
          sprintf(katalog[i],katalog[j]);
          sprintf(katalog[j],name);
        }
      }
    }
  }
}
    

const char color1[4]={0x50,0x00,0x00,0x20};
const char color2[4]={0x99,0x99,0x99,0x50};
GBSTMR MessageTimer;
int toview=0;
char *texttoview;
void ShowMess()
{
  if (toview)
  {
    int textfontsize=FONT_MEDIUM;
    DrawRectangle(0,0,132,176,0,color1,color1);
    DrawRectangle(10,10,120,166,0,GetPaletteAdrByColorIndex(1),color2);
    utf8_2ws(wss.ws1,texttoview,320);
    if ((Get_WS_width(wss.ws1,7))==0){wsprintf(wss.ws1,"%t",texttoview);}
    DrawString(wss.ws1,12,52,120,164,textfontsize,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),color2);
  }
}

void MessStop()
{
  if (toview)
  {
    toview=0;
    if (IsGuiOnTop(MAINGUI_ID)==1)
    {
      REDRAW();
    }
  }
}

void Message(char *text)
{
  toview=1;
  texttoview=text;
  GBS_StartTimerProc(&MessageTimer,1000,MessStop);
  if (IsGuiOnTop(MAINGUI_ID)==1)
    {
      REDRAW();
    }
}

char *GetFon()
{
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\fon.png");
  return(name);
}

int GetKatalogbackgroundcolour()
{
  return(katalogbackgroundcolour);
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  switch(WhatToView)
  {
case 0:
  if (IsUnlocked())
  {
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\background.png");
    DrawImg(0,0,(int)name);
    sprintf(name,"%sskins\\%s\\VOL%i.png",playerfolder,ArrayOfSkins[curskin],CurentVolume);
    DrawImg(volumex,volumey,(int)name);
    utf8_2ws(wss.ws1,playlistname,40);
    DrawString(wss.ws1,spysokx1,spysoky1,spysokx2,spysoky2,spysokfont,spysoktextattribute,
    GetPaletteAdrByColorIndex(spysoktextcolor),GetPaletteAdrByColorIndex(spysoktextbackground));
  //utf8_2ws(wss.ws1,NameOfCurentTrack,320);
  sprintf(name,"%s\r%s\r%s",ctrack,cartist,calbum);
  utf8_2ws(wss.ws1,name,320);
  if (name[0]!=' ')
  {
    wsprintf(wss.ws2,"%t\r%t\r%t",ctrack,cartist,calbum);
  }
  else
    {
      wsprintf(wss.ws2,pp);
    }
  if (Get_WS_width(wss.ws1,7)<Get_WS_width(wss.ws2,7))
  {
  DrawString(wss.ws2,songx1,songy1,songx2,songy2,songfont,songtextattribute,
    GetPaletteAdrByColorIndex(songtextcolor),GetPaletteAdrByColorIndex(songtextbackground));
  }
  else
  {
  DrawString(wss.ws1,songx1,songy1,songx2,songy2,songfont,songtextattribute,
    GetPaletteAdrByColorIndex(songtextcolor),GetPaletteAdrByColorIndex(songtextbackground));
  }
  wsprintf(wss.ws1,"%i%c%i",cp+1,'/',NumberOfTracks);
  DrawString(wss.ws1,tracksx1,tracksy1,tracksx2,tracksy2,tracksfont,trackstextattribute,
  GetPaletteAdrByColorIndex(trackstextcolor),GetPaletteAdrByColorIndex(trackstextbackground));  
    if (playing==1) {sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\stop.png");}
    else {sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\play.png");}
    DrawImg(play_stopx,play_stopy,(int)name);

  if (random==1) {
                   sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\random.png");
                   DrawImg(randomx,randomy,(int)name);
                 }
  if (ringoff!=0)
  {
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\off.png");
    DrawImg(ringoffx,ringoffy,(int)name);
  }
  else
   {
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\plus.png");
    if (CurentVolume<MAXVOLUME){DrawImg(volpx,volpy,(int)name);}
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\minus.png");
    if (CurentVolume>0) {DrawImg(volmx,volmy,(int)name);}
   }
    int y;
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\progressbar.png");
    if (timelength[cp]!=0)
    {
      if ((timemin*60+timesec)<=timelength[cp]) 
      {
        y=progressbarx1+((progressbarx2-progressbarx1-GetImgWidth((int)name))*(timemin*60+timesec))/timelength[cp];
      }
      else 
      {
        y=progressbarx2-progressbarx1-GetImgWidth((int)name);
      }
        DrawRectangle(progressbarx1,progressbary1+2,y-GetImgWidth((int)name),progressbary1-1+GetImgHeight((int)name),0,
        GetPaletteAdrByColorIndex(progressbarcolour),GetPaletteAdrByColorIndex(progressbarcolour));
        DrawImg(y,progressbary1+1,(int)name);
    }    
  if (entime==1)
  {if (timelength[cp]!=0)
  {
    wsprintf(wss.ws1,"%i:%i%i/%i:%i%i",timemin,timesec/10,timesec%10,timelength[cp]/60,(timelength[cp]%60)/10,(timelength[cp]%60)%10);
    DrawString(wss.ws1,timex1,timey1,timex2,timey2,timefont,timetextattribute,
    GetPaletteAdrByColorIndex(timetextcolor),GetPaletteAdrByColorIndex(timetextbackground));
  }
  else
  {
  wsprintf(wss.ws1,"%i:%i%i",timemin,timesec/10,timesec%10);
  DrawString(wss.ws1,timex1,timey1,timex2,timey2,timefont,timetextattribute,
  GetPaletteAdrByColorIndex(timetextcolor),GetPaletteAdrByColorIndex(timetextbackground));
  }
  }
   sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\prev.png");
   DrawImg(prevx,prevy,(int)name);
   sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\next.png");
   DrawImg(nextx,nexty,(int)name);
  }
  else
    {
      DrawRectangle(0,0,132,176,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
      TTime ktime;
      TDate date;
      GetDateTime(&date,&ktime);
      wsprintf(wss.ws1,"%i:%i%i",ktime.hour,ktime.min/10,ktime.min%10);
      DrawString(wss.ws1,0,88,132,176,FONT_LARGE_BOLD,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      utf8_2ws(wss.ws1,NameOfCurentTrack,320);
      DrawString(wss.ws1,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
    }
  break;
case 1:
  {
    DrawImg(0,0,(int)GetFon());
    int bottom;
    if (NumberOfTracks>9)
    {
    if((selected-4)>=0){top=selected-4;}else{top=0;}
    if (top+10<NumberOfTracks){bottom=NumberOfTracks;}
    bottom=top+9;
    if(bottom>NumberOfTracks)
    {
      while (bottom!=NumberOfTracks) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=NumberOfTracks;
    }
    int bkcolor=1;
    if (NumberOfTracks!=0)
    {
    for (int i=top;i<bottom;i++)
    {
      char t[256];
      int j;
      if (spysok[1][i][0]==0x1F)
      {
        j=28;
        sprintf(t,spysok[1][i]);
        t[0]=' ';
      }
      else
      {
        j=16;
        sprintf(t,pp_s,spysok[1][i]);
      }
      t[strlen(t)-4]=0;
      ////////////////////////
        int colour=katalogfontcolour;
        if (spysokselected[i]==1){colour=katalogselectedcolour;}
        utf8_2ws(wss.ws2,t,320);
        if (i!=selected)
        {
        utf8_2ws(wss.ws1,t,j);
        if ((Get_WS_width(wss.ws1,7))!=(Get_WS_width(wss.ws2,7)))
        {
          wsprintf(wss.ws2,"...");
          wstrcat(wss.ws1,wss.ws2);
          //utf8_2ws(wss.ws2,t,320);
          //if ((Get_WS_width(wss.ws1,7))>=(Get_WS_width(wss.ws2,7))){wss.ws1=wss.ws2;}
        }
        DrawString(wss.ws1,-4,(i-top)*15+22,106,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(23));
        }
        else
      {
        DrawScrollString(wss.ws2,-4,(i-top)*15+22,106,(i-top+1)*15+18,xdisp,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
      }
      ///////////////////////
    }
    for (int i=top;i<bottom;i++)
    {
      if (timelength[i]!=-1)
      {wsprintf(wss.ws1,"%i:%i%i",timelength[i]/60,(timelength[i]%60)/10,(timelength[i]%60)%10);}
      else
      {wsprintf(wss.ws1,"...");}
      if (i==selected)
      {
        bkcolor=katalogbackgroundcolour;
      }
      else
      {
        bkcolor=23;
      }
      DrawString(wss.ws1,96,(i-top)*15+22,130,(i-top+1)*15+21,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(bkcolor));
    }
    }
    wsprintf(wss.ws1,"%i%c%i",selected+1,'/',NumberOfTracks);
    DrawString(wss.ws1,1,3,128,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23)); 
    utf8_2ws(wss.ws1,playlistname,320);
    DrawString(wss.ws1,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,pt,LG_REMOVE);
    DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,pt,LG_ADD);
    DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    DrawLine(0,17,132,17,0,GetPaletteAdrByColorIndex(katalogfontcolour));
    DrawLine(92,17,92,0,0,GetPaletteAdrByColorIndex(katalogfontcolour));
  }break;
  case 2:
    {
      DrawRectangle(0,0,132,176,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
      utf8_2ws(wss.ws1,playlistname,320);
      DrawString(wss.ws1,1,3,130,40,7,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      utf8_2ws(wss.ws1,spysok[1][pisniashchozberigaetsia],100);
      DrawString(wss.ws1,1,40,130,80,7,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      DrawRectangle(0,80,132,100,0,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      DrawRectangle(0,80,132*(pisniashchozberigaetsia+1)/NumberOfTracks,100,0,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(12));
      wsprintf(wss.ws1,"%i%c%i",pisniashchozberigaetsia+1,'/',NumberOfTracks);
      DrawString(wss.ws1,0,84,132,100,7,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(12));
    }break;
case 3:
  {
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\fon.png");
    DrawImg(0,0,(int)name);
    int bottom;
    if (kataloglength>9)
    {
    if((katalogcurent-4)>=0){top=katalogcurent-4;}else{top=0;}
    if (top+10<kataloglength){bottom=kataloglength;}
    bottom=top+9;
    if(bottom>kataloglength)
    {
      while (bottom!=kataloglength) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=kataloglength;
    }
    for (int i=top;i<bottom;i++)
    {
      char t[256];
      int j;
      if (katalog[i][0]==0x1F)
      {
        j=34;
        sprintf(t,katalog[i]);
        t[0]=' ';
      }
      else
      {
        j=20;
        sprintf(t,pp_s,katalog[i]);
      }
      ////////////////////////
        
        utf8_2ws(wss.ws2,t,320);
      int colour;
      if (katalogselected[i]==1){colour=katalogselectedcolour;}else{colour=katalogfontcolour;};
        if (i!=katalogcurent)
        {
        utf8_2ws(wss.ws1,t,j);
        if ((Get_WS_width(wss.ws1,7))!=(Get_WS_width(wss.ws2,7)))
        {
          wsprintf(wss.ws2,"...");
          wstrcat(wss.ws1,wss.ws2);
          //utf8_2ws(wss.ws2,t,320);
          //if ((Get_WS_width(wss.ws1,7))>=(Get_WS_width(wss.ws2,7))){wss.ws1=wss.ws2;}
        }
        DrawString(wss.ws1,-4,(i-top)*15+22,130,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(23));
        }
        else
      {
        DrawScrollString(wss.ws2,-4,(i-top)*15+22,130,(i-top+1)*15+18,xdisp,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(23));
      }
      ///////////////////////
    }
    //utf8_2ws(wss.ws1,playlistname,320);
    //DrawString(wss.ws1,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(color),GetPaletteAdrByColorIndex(background));
    wsprintf(wss.ws1,pt,LG_SELECT);
    DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,"OK");
    DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    DrawLine(0,17,132,17,0,GetPaletteAdrByColorIndex(katalogfontcolour));
  }break;
  }
  ShowMess();
}

int xdispnapriamok=3;
void Scrolling()
{
  if (NumberOfTracks!=0)
  {
  char t[256];
  if (spysok[1][selected][0]==0x1F)
  {
    sprintf(t,spysok[1][selected]);
    t[0]=' ';
  }
  else
  {
    sprintf(t,pp_s,spysok[1][selected]);
  }
  t[strlen(t)-4]=0;
  utf8_2ws(wss.ws1,t,320);
  int colour=katalogfontcolour;
  if (spysokselected[selected]==1){colour=katalogselectedcolour;}
  int y=Get_WS_width(wss.ws1,7);
  if (y>110)
  {
    int ds=y-110;
    if ((xdisp>ds+3)||(xdisp==1)){xdispnapriamok=-xdispnapriamok;}
    xdisp+=xdispnapriamok;
  }
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==1))
  {
    GBS_StartTimerProc(&Scroll,35,Scrolling);
    if(!toview)
    {
      DrawScrollString(wss.ws1,-4,(selected-top)*15+22,106,(selected-top+1)*15+18,xdisp,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
    }
  }
  }
}

void ScrollingInFile()
{
  char t[256];
  if (katalog[katalogcurent][0]==0x1F)
  {
    sprintf(t,katalog[katalogcurent]);
    t[0]=' ';
  }
  else
  {
    sprintf(t,pp_s,katalog[katalogcurent]);
  }
  utf8_2ws(wss.ws1,t,320);
  int y=Get_WS_width(wss.ws1,7);
  if (y>136)
  {
    int ds=y-136;
    if ((xdisp>ds+3)||(xdisp==1)){xdispnapriamok=-xdispnapriamok;}
    xdisp+=xdispnapriamok;
  }
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==3))
  {
    GBS_StartTimerProc(&Scroll,35,ScrollingInFile);
    int colour;
    if (katalogselected[katalogcurent]==1){colour=katalogselectedcolour;}else{colour=katalogfontcolour;};
    if(!toview)
    {
      DrawScrollString(wss.ws1,-4,(katalogcurent-top)*15+22,130,(katalogcurent-top+1)*15+18,xdisp,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
    }
  }
}

void SaveOnlyPlaylistParams(char *playy)
{
  int f;
  char g[3];
  unsigned int err;
  g[0]=NumberOfTracks;
  g[1]=random;
  g[2]=cp;
  f=fopen(playy, A_ReadWrite/*+A_MMCStream*/, P_WRITE, & err );
  fwrite(f,g,3,&err);
  fclose(f,&err);
}

void SavePlaylist(void)
{
  int f;
  WhatToView=2;
  char s[1]="*";
  char g[5];
  char h[3];
  sprintf(h,"%c%c",0x0D,0x0A);
  unsigned int err;
  if((f=fopen(PlaylistToSave, A_WriteOnly+/*A_MMCStream+*/A_Create, P_WRITE, & err ))!=-1)
  {
    sprintf(g,"%c%c%c%c%c",NumberOfTracks,random,cp,0x0D,0x0A);
    fwrite(f,g,5,&err);
    for (pisniashchozberigaetsia=0;pisniashchozberigaetsia<NumberOfTracks;pisniashchozberigaetsia++)
    {
      fwrite(f,spysok[0][pisniashchozberigaetsia],strlen(spysok[0][pisniashchozberigaetsia]),&err);
      fwrite(f,s,1,&err);
      fwrite(f,spysok[1][pisniashchozberigaetsia],strlen(spysok[1][pisniashchozberigaetsia]),&err);
      fwrite(f,h,2,&err);
      if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==2)) {REDRAW();}
    }
    fclose(f,&err);
    playlistmode=1;
    const char *p=strrchr(LastPlaylist,'\\')+1;
    sprintf(playlistname,p);
    sprintf(LastPlaylist,PlaylistToSave);
    Message(WAS_SAVED);
  }
  else
  {
    fclose(f,&err);
    Message(LG_ERROR_CREATE_PLAYLIST);
  }
  pisniashchozberigaetsia=0;
  WhatToView=1;
  if (IsGuiOnTop(MAINGUI_ID)==1){REDRAW();}
}

int findmp3length(char *playy)
{
   #ifdef NEWSGOLD 
   return(0); 
   #else
   TWavLen wl;
   zeromem(&wl, sizeof(wl));
   wl.type=0x2000;
   wl.wfilename=AllocWS(128);
   str_2ws(wl.wfilename,playy,128); 
   GetWavLen(&wl); 
   return (wl.length/1000);
   #endif 
}

void timepp()
{
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    if (playing!=0)
      {
        if (timehms[2]!=ktime.sec)
          {
            timesec++;
            if(timesec==60)
              {
                timesec=0;
                timemin++;
              }
            if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0))
              {
                REDRAW();
              }
          }
        if ((entime)&&(playing==1)) {GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);}
      }
    else
      {
        timesec=0;
        timemin=0;
      }
    if (NeedToStop==1){Play_PauseResume();NeedToStop=0;}
    timehms[2]=ktime.sec;
}

void findtegs()
{
  int f;
  char file[128];
  unsigned int err;
  sprintf(name,"%s%s",spysok[0][cp],spysok[1][cp]);
  FSTATS stat; 
  f=fopen(name, A_ReadOnly+A_BIN, P_READ, &err); 
  GetFileStats(name, &stat, &err); 
  lseek(f,(stat.size-128), 0, &err, &err); 
  fread(f, file, 128, &err);
  fclose(f, &err);

  sprintf(calbum,pp);
  sprintf(ctrack,pp);
  sprintf(cartist,pp);
  if ((file[0]=='T')&&(file[1]=='A')&&(file[2]=='G'))
  {
  int i;
  for (i=3;(file[i]!=0)&&(i<33);i++)
    {
      sprintf(ctrack,"%s%c",ctrack,file[i]);
    }
  for (i=33;(file[i]!=0)&&(i<63);i++)
    {
      sprintf(cartist,"%s%c",cartist,file[i]);
    }
  for (i=63;(file[i]!=0)&&(i<93);i++)
    {
      sprintf(calbum,"%s%c",calbum,file[i]);
    }
  }
  if (strlen(ctrack)==0)
  {
    sprintf(ctrack,spysok[1][cp]);
    if (ctrack[0]==0x1F){ctrack[0]=' ';}
    ctrack[strlen(ctrack)-4]=0;
  }
  
  /*f=fopen("0:\\1.txt", A_WriteOnly+A_Create, P_WRITE, &err); 
  fwrite(f, file, 128, &err);
  fclose(f, &err);*/
  
}

void Play(char *fname)
{           DIR_ENTRY de;
            unsigned int err;
            char s[256];
            sprintf(s,fname);
            if(FindFirstFile(&de,s,&err))
{
  if (!IsCalling())
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=1;
#ifdef X75
    _sfo1.unk4=0x80000000;
    _sfo1.unk5=1;
    PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
    _sfo1.unk5=1;
    PLAY_ID=PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif      
    CanPlayNext=0;
      FreeWS(sndPath);
      FreeWS(sndFName);
      TTime ktime;
      TDate date;
      GetDateTime(&date,&ktime);
      timehms[2]=ktime.sec;
      if (ringoff==0){PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);}
      findtegs();
      if ((timelength[cp]==-1)||(timelength[cp]==0))
        {
          timelength[cp]=findmp3length(s);
        }
        else
        {
          timelength[cp]=timelength[cp];
        }
      sprintf(NameOfCurentTrack,"%s - %s - %s",ctrack,cartist,calbum);
      UpdateCSMname();
      if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)){REDRAW();}
    }
  }
}
       else 
       {
         PlayNext();
       }
   FindClose(&de,&err);
}

void LoadPlaylist(char *playy)
{
  int f,count=0;
  char list[20000];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  
  f=fopen(ddd, A_ReadOnly, P_READ, & err );
  DIR_ENTRY de;
  FindFirstFile(&de,ddd,&err);
  fread(f,list,de.file_size,&err);
  fclose(f,&err);
  FindClose(&de,&err);
  NumberOfTracks=list[0];
  random=list[1];
  cp=list[2];
  t[0]=list[5];
  count=5;
  
  for (int i=0;i<NumberOfTracks;i++)//Вот так грузится ipl
  {
  while (t[0]!='*')
  {
    sprintf(spysok[0][i],"%s%c",spysok[0][i],t[0]);
    count++;
    t[0]=list[count];
  }
  count++;t[0]=list[count];
  while (t[0]!=0x0D)
  {
    sprintf(spysok[1][i],"%s%c",spysok[1][i],t[0]);
    count++;
    t[0]=list[count];
  }
  count++;
  count++;
  t[0]=list[count];
  }
}

void LoadM3uPlaylist(char *playy)
{
  int f,count=0;
  char list[20000];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  
  f=fopen(ddd, A_ReadOnly+A_MMCStream, P_READ, & err );
  DIR_ENTRY de;
  FindFirstFile(&de,playy,&err);
  fread(f,list,de.file_size,&err);
  fclose(f,&err);
  t[0]=list[9];
  count=9;
  char temp[400]="";

  //А так м3у
  for (int i=0;(count<de.file_size);i++)
  {
    sprintf(temp,pp);//Обнуляем
  while (t[0]!=0x0D)
  {
    sprintf(temp,"%s%c",temp,t[0]);
    count++;
    t[0]=list[count];
  }
  count++;
  count++;
  
  
      char s[128];
      const char *p=strrchr(temp,'\\')+1;
      sprintf(spysok[1][i],p);
      strncpy(s,temp,p-temp);
      s[p-temp]='\0';
      sprintf(spysok[0][i],s,128);
      
  t[0]=list[count];
  NumberOfTracks=i+1;
  }
  FindClose(&de,&err);
}

int whattoplaynext()
{
  int neprograni=0;
  for (int i=0;i<NumberOfTracks;i++) {if (notplayed[i]==0){neprograni++;}}
  if (neprograni>0)
  {
    TTime time;
    TDate date;
    GetDateTime(&date,&time);
    int l=time.min*5+time.sec;//Типа случайно :)
    //while (neprograni<l){l=l-neprograni;}
    l=l%neprograni;
    neprograni=0;
    for (int i=0;i<NumberOfTracks;i++)
    {
      if (notplayed[i]==0)
      {
        neprograni++;
        if (l==neprograni)
        {
          notplayed[i]=cp;
          if (notplayed[cp]==0) 
          {
            notplayed[cp]=10000;
          }
          return(i);
        }
      }
    }
  }
  else 
  {
    for (int i=0;i<NumberOfTracks;i++){notplayed[i]=0;}
    return(whattoplaynext());
    //Все песни проиграны
  }
  return(255);
}

int whattoplayprev()
{
  if(notplayed[cp]!=10000)
  {
    return(notplayed[cp]);
  }
  else
  {
    return(whattoplaynext());
  }
}

void r()
{
  REDRAW();
}

void showvolume()
{
  sprintf(name,"%sskins\\%s\\VOL%i.png",playerfolder,ArrayOfSkins[curskin],CurentVolume);
  DrawImg(volumex,volumey,(int)name);
  //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\plus.png");
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)&&(IsUnlocked()))
  {
    REDRAW();
  }
  else
  {
    GBS_StartTimerProc(&RedrawTimer,262,r);
  }
}

void PlayNext()
{
  if ((CanPlayNext)&&(NumberOfTracks!=0))
  {
  if (random==0)
     {
       if (cp>NumberOfTracks-2)
        {
          cp=0;
        }
       else 
         {
           cp++;
         }
     }
  else 
    {
      cp=whattoplaynext();
    }
  char s[256];
  sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
  playing=1;
  JaPerekliuchyvPisniu=1;
  Play(s);
  }
  else
  {
    if (NumberOfTracks!=0)
    {
      GBS_StartTimerProc(&PlayNextTimer,30,PlayNext);
    }
  }
}

void PlayPrevious()
{
  if ((CanPlayNext)&&(NumberOfTracks!=0))
  {
  if (random==0)
   {
     if (cp<1) 
       {
         cp=NumberOfTracks-1;
       }
     else 
       {
         cp--;
       }
   }
  else
    {
      cp=whattoplayprev();
    }
    char s[256];
    sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
    playing=1;
    JaPerekliuchyvPisniu=1;
    Play(s);
  }
  else
  {
   if (NumberOfTracks!=0){GBS_StartTimerProc(&PlayNextTimer,30,PlayPrevious);}
  }
}

void Play_PauseResume()
{
  if (playing==1)
    {
      PlayMelody_PausePlayback(PLAY_ID);
      playing=2;
    }
  else
    {
      if (playing==0)
        {
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          playing=1;
          Play(s);
        }
      else
        {
          if (playing==2)
            {
              PlayMelody_ResumePlayBack(PLAY_ID);
              if (entime==1){GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);}
              playing=1;
            }
        }
    }
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)){REDRAW();}
}

void VolumeDown()
{
  ringoff=0;
  if (CurentVolume!=0)
    {
      CurentVolume--;
      PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
    }
  showvolume();
}

void VolumeMute()
{
  if (ringoff==0)
    {
      PlayMelody_ChangeVolume(PLAY_ID,0);
      ringoff=1;
      REDRAW();
    }
  else
    {
      PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
      ringoff=0;
      REDRAW();
    }
}

void VolumeUp()
{
  ringoff=0;
  if(CurentVolume!=MAXVOLUME)
    {
      CurentVolume++;
      PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
    }
  showvolume();
}
////////////////////////////////////////////////////
/*void OnRedraw2(MAIN_GUI *data) // OnRedraw
{
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\background.png");
  DrawImg(0,0,(int)name);
}*/

void onCreate2(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose2(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus2(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  WhatToView=0;
  DisableIDLETMR();
}

void onUnfocus2(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int PLAYERGUI_ID;
void CloseGUI()
{
  GeneralFunc_flag1 (PLAYERGUI_ID,1);
}

int MenuKeys(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if ((msg->gbsmsg->msg==KEY_DOWN))
  {
    switch(msg->gbsmsg->submess)
    {
    case '1':{WhatToDo(Key1);}break;
    case '2':{WhatToDo(Key2);}break;
    case '3':{WhatToDo(Key3);}break;
    case '4':{WhatToDo(Key4);}break;
    case '5':{WhatToDo(Key5);}break;
    case '6':{WhatToDo(Key6);}break;
    case '7':{WhatToDo(Key7);}break;
    case '8':{WhatToDo(Key8);}break;
    case '9':{WhatToDo(Key9);}break;
    case '0':{WhatToDo(Key0);}break;
    case '*':{WhatToDo(KeyZ);}break;
    case '#':{WhatToDo(KeyR);}break;
    case RED_BUTTON:CloseGUI();break;
    }
    GBS_StartTimerProc(&PlayerMenu,500,CloseGUI);
    REDRAW();
  }
  return(0);
}

#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}
#else
extern void kill_data(void *p, void (*func_p)(void *));
#endif

int method(void){return(0);}

const void * const gui_methods2[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate2,	//Create
  (void *)onClose2,	//Close
  (void *)onFocus2,	//Focus
  (void *)onUnfocus2,	//Unfocus
  (void *)MenuKeys,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	//Destroy
  #else
  (void *)kill_data,	//Destroy
  #endif
  (void *)method,
  (void *)method,
  0
};

const RECT Canvas={0,0,131,175};

void ShowPlayerMenu()
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods2;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  PLAYERGUI_ID=CreateGUI(main_gui);
  GBS_StartTimerProc(&PlayerMenu,500,CloseGUI);
}

////////////////////////
int press=0;//0-отпущена,1-нажата коротко,2-зажата

int my_keyhook(int submsg, int msg)
{
  if ((submsg!=0x14 && submsg!=0x15 &&  submsg!=0x27)||(EnableHook==2)||((!IsUnlocked())&&(EnableHook==1))) return(0);//Хук на кнопку гарнитуры и боковые кнопки
  switch(msg)
  {
    case(KEY_UP):
      {
        switch(submsg)
            {
           case 0x14: 
             if (press==1)
             {
               VolumeUp();
             }
             else 
             {
               if (press<5)
               {
                 PlayNext();
               }
             };break;//Верхня
           case 0x15: 
             if (press==1)
             {
               VolumeDown();
             }
             else 
             {
               if (press<5)
               {
                 PlayPrevious();
               }
             }
             break;//Нижня
           case 0x27: if (press==1){Play_PauseResume();}else {if (press>1){PlayNext();}};break;//Гарнітура
            }
      }
      break;    
  case(KEY_DOWN):press=1;break;
  case(LONG_PRESS):
    {
      press++;
      if (press==5)
      {
        if (submsg==0x14)
        {
          gipc.name_to=ipc_xtask_name;
          gipc.name_from=ipc_my_name;
          gipc.data=(void *)MAINCSM_ID;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
        }
        else
        {
          if (submsg==0x15)
          {
            if (IsUnlocked()){ShowPlayerMenu();}
          }
        }
      }
      
    }break;
  }
  return(2);
}

void SaveParams()
{
  int f;
  char h[2];
  sprintf(h,"%c%c",CurentVolume,curskin);
  unsigned int err;
  sprintf(name,"%sparams.txt",playerfolder);
  f=fopen(name, A_WriteOnly+A_MMCStream+A_Create, P_WRITE, & err );
  fwrite(f,h,2,&err);
  fclose(f,&err);
}

void WriteLastPlaylist()
{
  int f;
  char h[300];
  sprintf(h,"%c%c%c%s",random+1,(cp+1)%256,strlen(LastPlaylist),LastPlaylist);
  unsigned int err;
  sprintf(name,"%slastplaylist.cfg",playerfolder);
  if ((f=fopen(name, A_WriteOnly+A_Create, P_WRITE, & err ))!=-1)
  {
    fwrite(f,h,strlen(h),&err);
  }
  fclose(f,&err);
}

void ReadLastPlaylist()
{
  int f;
  char h[300];
  unsigned int err;
  sprintf(name,"%slastplaylist.cfg",playerfolder);
  if ((f=fopen(name, A_ReadOnly+A_MMCStream, P_READ, & err ))!=-1)
  {
    DIR_ENTRY de;
    FindFirstFile(&de,name,&err);
    if (de.file_size!=0)
    {
      fread(f,h,de.file_size,&err);
      random=h[0]-1;
      cp=h[1]-1;
      sprintf(LastPlaylist,pp);
      for (int i=0;i<h[2];i++)
      {
        sprintf(LastPlaylist,"%s%c",LastPlaylist,h[i+3]);
      }
    }
    FindClose(&de,&err);
  }
  fclose(f,&err);
}

void LoadParams()
{
  int f;
  char h[2];
  unsigned int err;
  sprintf(name,"%sparams.txt",playerfolder);
  f=fopen(name, A_ReadOnly+A_MMCStream, P_READ, & err );
  if (f>-1)
  {
    fread(f,h,2,&err);
    CurentVolume=h[0];
    curskin=h[1];
  }
  fclose(f,&err);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void WhatToDo(int param)
{
  switch (param)
  {
  case 1:if (playing!=0){PlayMelody_StopPlayback(PLAY_ID);
                         timemin=0;
                         timesec=0;
                         REDRAW();
                         playing=0;
                         break;
                        }
        else
  case 0:if (playing!=0){NeedToStop=1;}else{Play_PauseResume();}if (entime==1){GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);}break;
  case 2:VolumeUp();break;
  case 3:VolumeDown();break;
  case 4:{random=1-random;REDRAW();};break;
  case 5:{Cleaner();if (curskin!=0){curskin--;}else{curskin=NumberOfSkins-1;}readskinparamsfromfile();REDRAW();};break;
  case 6:{Cleaner();if (curskin!=NumberOfSkins-1){curskin++;}else{curskin=0;}readskinparamsfromfile();REDRAW();};break;
  case 7:PlayPrevious();break;
  case 8:PlayNext();break;
  case 9:{wsprintf(wss.ws1,"0:\\Zbin\\etc\\ivoplay.bcfg");ExecuteFile(wss.ws1,0,"");}break;
  case 10:{CreateMenuFindPlaylist();}break;
  case 11:VolumeMute();break;
  case 12:{gipc.name_to=ipc_xtask_name;
           gipc.name_from=ipc_my_name;
           gipc.data=0;
           GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
           if (IsUnlocked()) {KbdLock();}
          }break;
  case 13:CLOSECURENTCSM();break;
  case 15:ShowMainMenu();break;
  case 16:{gipc.name_to=ipc_xtask_name;
           gipc.name_from=ipc_my_name;
           gipc.data=0;
           GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
          }break;
  case 17:
    if (IsUnlocked()) 
    {
      KbdLock();
    }
    else 
  {
    KbdUnlock();
      int z;
      switch(GetProfile()+1)
      {
      case 1:z=profile1;break;
      case 2:z=profile2;break;
      case 3:z=profile3;break;
      case 4:z=profile4;break;
      case 5:z=profile5;break;
      case 6:z=profile6;break;
      case 7:z=profile7;break;
      case 8:z=profile8;break;
      }
      SetIllumination(0,1,z,0);
  }
  REDRAW();
  break;
  case 18:{wsprintf(wss.ws1,"4:\\Zbin\\etc\\ivoplay.bcfg");ExecuteFile(wss.ws1,0,"");}break;
  case 19:{if ((timemin==0)&&(timesec<5)){PlayPrevious();}else
                                                           {
                                                             char s[256];
                                                             sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
                                                             playing=1;
                                                             JaPerekliuchyvPisniu=1;
                                                             Play(s);
                                                           }
          }break;
  case 20:
    {
      char *s="ffff";
      sprintf(s,"%s:\r%s%s\r%s: %i:%i%i",LG_FULL_NAME,spysok[0][cp],spysok[1][cp],LG_FULL_TIME,timelength[cp]/60,(timelength[cp]%60)/10,(timelength[cp]%60)%10);
      Message(s);
    };break;
  case 21:
    {
      ShowPlayerMenu();
    }
  }
}

int IsFile(char *name)
{ int i;
i=0;
while(i<200){
if(name[i]==0)break;
if(name[i]=='.')return(1);  
i++; 
}
return(0);  
}

extern const char zir[]="*";

void CreatePlaylist(char *foldder)//Прочесываем папки рекурсивно
{
  DIR_ENTRY de;
  unsigned int err;
  char path[128];
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  NumberOfTracks=0;
  /*  
  strcat(name,zir);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      if (!IsFile(name)){CreatePlaylist(name);}
    }
    while(FindNextFile(&de,&err));
  }
*/
  char format[5];
  if (strlen(format_1)!=0)
  {
  sprintf(format,"*.%s",format_1);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  if (strlen(format_2)!=0)
  {
  sprintf(format,"*.%s",format_2);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }

  if (strlen(format_3)!=0)
  {
  sprintf(format,"*.%s",format_3);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  if (strlen(format_4)!=0)
  {
  sprintf(format,"*.%s",format_4);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  FindClose(&de,&err);
}

void findlisttime(void)
{
  char s[256];
  for (int i=1;(i<NumberOfTracks)&&(pracuje);i++)
  {
    sprintf(s,"%s%s",spysok[0][i],spysok[1][i]);
    if (timelength[i]==-1){timelength[i]=findmp3length(s);}
    if (WhatToView==1){REDRAW();}
  }
  sprintf(s,"%s%s",spysok[0][0],spysok[1][0]);
  timelength[0]=findmp3length(s);
  if (WhatToView==1){REDRAW();}
}

int longpress=0;
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
    if (!toview)
    {
    switch(WhatToView)
      {
      case 0:
      {
  if ((msg->gbsmsg->msg==KEY_DOWN)&&(IsUnlocked()))
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:
      {
        WhatToDo(13);
      }
    case LEFT_SOFT:if (playing!=0){
                                   WhatToDo(1);
                                   break;
                                  }
    case ENTER_BUTTON:
        WhatToDo(0);
          break;
    case '1':{WhatToDo(Key1);}break;
    case '2':{WhatToDo(Key2);}break;
    case '3':{WhatToDo(Key3);}break;
    case '4':{WhatToDo(Key4);}break;
    case '5':{WhatToDo(Key5);}break;
    case '6':{WhatToDo(Key6);}break;
    case '7':{WhatToDo(Key7);}break;
    case '8':{WhatToDo(Key8);}break;
    case '9':{WhatToDo(Key9);}break;
    case '0':{WhatToDo(Key0);}break;
    case '*':{WhatToDo(KeyZ);}break;
    case '#':{WhatToDo(KeyR);}break;
    case UP_BUTTON:
      ringoff=0;
      if (ringoff==1)
        {
          PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
        }
      else
        {
          if (CurentVolume!=MAXVOLUME)
              {
                CurentVolume++;
                PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
              }
        }
      REDRAW();
      break;
    case DOWN_BUTTON:
      ringoff=0;
      if (ringoff==1)
        {
          PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
        }
      else
        {
          if (CurentVolume!=0)
            {
              CurentVolume--;
              PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
            }
        }
      REDRAW();
      break;
    case LEFT_BUTTON:
      {
        PlayPrevious();
      }
      break;
    case RIGHT_BUTTON:
      {
        PlayNext();
      }
      break;
    case GREEN_BUTTON: 
      WhatToView=1;
      selected=cp;
      for (int i=0;i<256;i++){spysokselected[i]=0;}
      xdisp=1;
      xdispnapriamok=-3;
      GBS_StartTimerProc(&Scroll,50,Scrolling);
      REDRAW();
      break;
    case RIGHT_SOFT:
      {
        ShowMainMenu();
      }
      break;
    }
  }
  if (msg->gbsmsg->msg==KEY_UP){longpress=0;}
  if (msg->gbsmsg->msg==LONG_PRESS)
  {if (!IsUnlocked())
  {
      int z;
      switch(GetProfile()+1)
      {
      case 1:z=profile1;break;
      case 2:z=profile2;break;
      case 3:z=profile3;break;
      case 4:z=profile4;break;
      case 5:z=profile5;break;
      case 6:z=profile6;break;
      case 7:z=profile7;break;
      case 8:z=profile8;break;
      }
      SetIllumination(0,1,z,0);
      SetIllumination(0,1,0,2000);
  }
  else 
  {
    switch(msg->gbsmsg->submess)
    {
      case'*':
        {
          /*if (longpress!=1){WhatToDo(17);}
           longpress=1;*/
       }break;
    }
  }
    switch(msg->gbsmsg->submess)
    {
      case'#':
        {
          if (longpress!=1){WhatToDo(17);}
           longpress=1;
       }break;
    }
  }
    }break;
    
  case 1:
    {
  if ((msg->gbsmsg->msg==KEY_DOWN)&&(IsUnlocked()))
  {
      switch(msg->gbsmsg->submess)
    {
      case RED_BUTTON:
      {
        WhatToView=0;
        REDRAW();
      }break;
      case DOWN_BUTTON:
      {
        selected++;
        if(selected>NumberOfTracks-1){selected=0;}
        xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);
        REDRAW();
      }break;
    /*case '9':
      {
        backgroundselected++;
      }
      break;*/
      case '*':
      {
        switch(playlistmode)
        {
        case 0:
          {
            sprintf(PlaylistToSave,"%splaylists\\standart.ipl",playerfolder);
            CreateSaveAsDialog();
          };break;
        case 1:
          {
            sprintf(PlaylistToSave,LastPlaylist);
            CreateSaveAsDialog();
          };break;
        case 2:
          {
            sprintf(PlaylistToSave,"%splaylists\\%s.ipl",playerfolder,playlistname);
            CreateSaveAsDialog();
          };break;
        case 3:
          {
            sprintf(PlaylistToSave,"%splaylists\\%s.ipl",playerfolder,playlistname);
            CreateSaveAsDialog();
          };break;
        }
      }break;
    case '5':
      {
        spysokselected[selected]=1-spysokselected[selected];
        selected++;
        if(selected>NumberOfTracks-1){selected=0;}
        xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);
        REDRAW();
      }break;
    case '2':
      {
        int y=0;
        for (int i=0;(i<NumberOfTracks)&&(!y);i++){if(spysokselected[i]){y=1;}}
          if (!y)
          {
            int j=selected;
            selected--;
            if(selected<0){selected=NumberOfTracks-1;}
            sprintf(name,spysok[0][selected]);
            sprintf(spysok[0][selected],spysok[0][j]);
            sprintf(spysok[0][j],name);
            sprintf(name,spysok[1][selected]);
            sprintf(spysok[1][selected],spysok[1][j]);
            sprintf(spysok[1][j],name);
            long y=timelength[selected];
            timelength[selected]=timelength[j];
            timelength[j]=y;
            y=notplayed[selected];
            notplayed[selected]=notplayed[j];
            notplayed[j]=y;
            if (cp==j){cp=selected;}
            else
            {
              if (cp==selected){cp=j;}
            }
          }
          else
          {
            for (int i=0;i<NumberOfTracks;i++)
            {
              if(spysokselected[i])
              {
                int j=i;
                int t=i-1;
                if (t<0){t=NumberOfTracks-1;}
                sprintf(name,spysok[0][t]);
                sprintf(spysok[0][t],spysok[0][j]);
                sprintf(spysok[0][j],name);
                sprintf(name,spysok[1][t]);
                sprintf(spysok[1][t],spysok[1][j]);
                sprintf(spysok[1][j],name);
                long y=timelength[t];
                timelength[t]=timelength[j];
                timelength[j]=y;
                y=notplayed[t];
                notplayed[t]=notplayed[j];
                notplayed[j]=y;
                y=spysokselected[t];
                spysokselected[t]=spysokselected[j];
                spysokselected[j]=y;
                if (cp==j){cp=i;}
                else
                {
                  if (cp==t){cp=j;}
                }
              }
            }
          }
           xdisp=1;
           xdispnapriamok=-3;
           GBS_StartTimerProc(&Scroll,50,Scrolling);
           REDRAW();
      };break;
    case '8':
      {
        int y=0;
        for (int i=0;(i<NumberOfTracks)&&(!y);i++){if(spysokselected[i]){y=1;}}
          if (!y)
          {
            int j=selected;
            selected++;
            if(selected>NumberOfTracks-1){selected=0;}
            sprintf(name,spysok[0][selected]);
            sprintf(spysok[0][selected],spysok[0][j]);
            sprintf(spysok[0][j],name);
            sprintf(name,spysok[1][selected]);
            sprintf(spysok[1][selected],spysok[1][j]);
            sprintf(spysok[1][j],name);
            long y=timelength[selected];
            timelength[selected]=timelength[j];
            timelength[j]=y;
            y=notplayed[selected];
            notplayed[selected]=notplayed[j];
            notplayed[j]=y;
            if (cp==j){cp=selected;}
            else
            {
              if (cp==selected){cp=j;}
            }
          }
          else
          {
            for (int i=0;i<NumberOfTracks;i++)
            {
              if(spysokselected[i])
              {
                int j=i;
                int t=i+1;
                if (t>NumberOfTracks-1){t=0;}
                sprintf(name,spysok[0][t]);
                sprintf(spysok[0][t],spysok[0][j]);
                sprintf(spysok[0][j],name);
                sprintf(name,spysok[1][t]);
                sprintf(spysok[1][t],spysok[1][j]);
                sprintf(spysok[1][j],name);
                long y=timelength[t];
                timelength[t]=timelength[j];
                timelength[j]=y;
                y=notplayed[t];
                notplayed[t]=notplayed[j];
                notplayed[j]=y;
                y=spysokselected[t];
                spysokselected[t]=spysokselected[j];
                spysokselected[j]=y;
                if (cp==j){cp=i;}
                else
                {
                  if (cp==t){cp=j;}
                }
              }
            }
          }
           xdisp=1;
           xdispnapriamok=-3;
           GBS_StartTimerProc(&Scroll,50,Scrolling);
           REDRAW();
      };break;
    case UP_BUTTON:
      {
        selected--;
        if(selected<0){selected=NumberOfTracks-1;}
        xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);
        REDRAW();
      }break;
    case '0':Message(LG_PLAYLIST_HELP);break;
      case RIGHT_SOFT:
        {
          ZapovnytyTaVidsortuvatyKatalog(curentfolder);
          WhatToView=3;
          for (int i=0;i<256;i++){katalogselected[i]=0;}
          REDRAW();
        }break;
      case LEFT_SOFT:
      {
        if (NumberOfTracks!=1)
        {
        for (int i=selected;i<NumberOfTracks;i++)
        {
          sprintf(spysok[0][i],spysok[0][i+1]);
          sprintf(spysok[1][i],spysok[1][i+1]);
          timelength[i]=timelength[i+1];
          notplayed[i]=notplayed[i+1];
        }
        timelength[NumberOfTracks]=-1;
        sprintf(spysok[1][NumberOfTracks],pp);
        sprintf(spysok[0][NumberOfTracks],pp);
        if (cp==selected)
        {
        cp--;
        char s[256];
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
        }
        if (cp>selected){cp--;}
        if (selected!=0){selected--;}
        NumberOfTracks--;
        REDRAW();
        }
        else
        {
          Message(LG_CANT_REMOVE_LAST_FILE);
        }
      }break;
    case ENTER_BUTTON:
      {
        char s[256];
        cp=selected;
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
        WhatToView=0;
        REDRAW();
      }break;
    case '#':
      {
        char s[256];
        cp=selected;
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
      }break;
    }
  }
      }break;
  case 3:
    {
  if ((msg->gbsmsg->msg==KEY_DOWN)&&(IsUnlocked()))
  {
      switch(msg->gbsmsg->submess)
    {
      
      case RED_BUTTON:
      {
        WhatToView=1;
        REDRAW();
      }break;
      
      case UP_BUTTON:
      {
        katalogcurent--;
        if(katalogcurent<0){katalogcurent=kataloglength-1;}
        xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
        REDRAW();
      }break;
      
      case DOWN_BUTTON:
      {
        katalogcurent++;
        if(katalogcurent>kataloglength-1){katalogcurent=0;}
        xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
        REDRAW();
      }break;
      
    //case '9':ShowMSG(1,(int)curentfolder);break;
      
    case LEFT_SOFT:
      {
        if ((katalogcurent!=0)&&(IsFile(katalog[katalogcurent])))
        {
          katalogselected[katalogcurent]=1-katalogselected[katalogcurent];
          katalogcurent++;
          if(katalogcurent>kataloglength-1){katalogcurent=0;}
          xdisp=1;
          xdispnapriamok=-3;
          GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
          REDRAW();
        }
      }break;
      
    case RIGHT_SOFT:
      {
        for (int i=1;i<kataloglength;i++)
        {
          if (katalogselected[i]==1)
          {
            sprintf(spysok[0][NumberOfTracks],"%s\\",curentfolder);
            sprintf(spysok[1][NumberOfTracks],katalog[i]);
            NumberOfTracks++;
          }
        }
        SUBPROC((void *)findlisttime);
        for (int i=0;i<256;i++){katalogselected[i]=0;}
        Message(LG_ADDED);
      }break;
    
    case GREEN_BUTTON:
      {
        for (int i=1;i<kataloglength;i++)
        {
          if (IsFile(katalog[i]))
          {
            katalogselected[i]=1-katalogselected[i];
          }
        }
        REDRAW();
      }break;
      
    case ENTER_BUTTON:
      {
        if (katalogcurent!=0)
        {
          char t[255];
          sprintf(t,"%s\\%s",curentfolder,katalog[katalogcurent]);
          if(!IsFile(t))
          {
            sprintf(curentfolder,t);
            for (int i=0;i<256;i++){katalogselected[i]=0;}
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
            REDRAW();
          }
          else
          {
            //katalogselected[katalogcurent]=1-katalogselected[katalogcurent];
          }
        }
        else
        {
          int i;
          for (i=strlen(curentfolder);(curentfolder[i]!='\\')&&(i!=0);i--);
          curentfolder[i]=0;
          ZapovnytyTaVidsortuvatyKatalog(curentfolder);
          for (int i=0;i<256;i++){katalogselected[i]=0;}
          GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
          REDRAW();
        }
      }break;
      
    }
  }
    }
  break;
  }
    }
    else
    {
      if (msg->gbsmsg->msg==KEY_DOWN)
      {
        switch(msg->gbsmsg->submess)
        {
        case RED_BUTTON:case ENTER_BUTTON:case RIGHT_SOFT:
          {
            toview=0;
            REDRAW();
          }break;
        }
      }
    }
  return(0);
}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	//Destroy
  #else
  (void *)kill_data,	//Destroy
  #endif
  (void *)method,
  (void *)method,
  0
};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  wss.ws1=AllocWS(256);
  wss.ws2=AllocWS(256);
  /*
  pisnia.PLAYLIST=AllocWS(256);
  pisnia.TRACK=AllocWS(256);
  pisnia.NUMBEROFTRACKS=AllocWS(256);
 */
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void PersheShchoStuknuloVGolovu()
{
  gipc.name_from="Ivoplay";
  gipc.name_to="control_panel|remove_point|";
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
  GBS_DelTimer(&Scroll);
}

void maincsm_onclose(CSM_RAM *csm)
{
  WriteLastPlaylist();
  PlayMelody_StopPlayback(PLAY_ID);
  GBS_DelTimer(&RedrawTimer);
  GBS_DelTimer(&TimeTimer);
  GBS_DelTimer(&PlayerMenu);
  GBS_DelTimer(&PlayNextTimer);
  RemoveKeybMsgHook((void *)my_keyhook);
  SaveParams();
  Cleaner();
  if (playlistmode==1){SaveOnlyPlaylistParams(LastPlaylist);}
  FreeWS(wss.ws1);
  FreeWS(wss.ws2);
  pracuje=0;
  GBS_StartTimerProc(&Scroll,30,PersheShchoStuknuloVGolovu); 
  SUBPROC((void *)ElfKiller);
}
//////////////////////////
void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_my_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    GBS_SendMessage(MMI_CEPID,MSG_IPC,ktime.min*60+ktime.sec,&gipc);  
    //LockSched();
    //CloseCSM(MAINCSM_ID);
    //UnlockSched();
  }
  else
  {
  }
}
/////////////////////////////////



int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  
/////////////////////
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
        /*if ((ipc->name_to[0]=='I')&&(ipc->name_to[1]=='v'))
        {
          ShowMSG(1,(int)ipc->name_to);*/
          /*if (!strcmp("control_panel|punkt1",ipc->name_from))
          {
            Play_PauseResume();
            //ShowMSG(1,(int)ipc->name_to);
          }
        }*/
        if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
        {
          if (strcmp_nocase(ipc->name_from,"control_panel")==0)
          {
              gipc.name_to=ipc_xtask_name;
              gipc.name_from=ipc_my_name;
              gipc.data=(void *)MAINCSM_ID;
              GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
          }
	if ((msg->submess)!=-identyfikator)
	{
	  if (((msg->submess)!=identyfikator)&&((msg->submess)>0))
          {
            GBS_SendMessage(MMI_CEPID,MSG_IPC,-identyfikator,&gipc);  
          }
          else
          {
            if ((msg->submess)<0)
            {
              CloseCSM(MAINCSM_ID);
                int csm_id;
                if (((csm_id=(int)(gipc.data))!=-1)&&((playlistmode==3)||(playlistmode==4)))
                {
                  char *s="ffff";
                  sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
                  char *r=s;
                  gipc.name_to=r;
                  gipc.name_from="pLay";
                  gipc.data=(void *)csm_id;
                  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc); 
                }
            }
          }
        }
        else
        {
          if((ipc->name_from[0]=='p')&&(ipc->name_from[1]=='L')&&(ipc->name_from[2]=='a')&&(ipc->name_from[3]=='y'))
          {
            char u[256];
            for (int i=0;i<strlen(ipc->name_to);i++)
            {
              sprintf(u,"%s%c",u,ipc->name_to[i]);
            }
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,u,&err))
            {
              cp=NumberOfTracks;
              NumberOfTracks++;
              sprintf(playlistname,"Mixed");
              //playlistname=LG_MIXED;
      const char *o=strrchr(u,'\\')+1;
      sprintf(spysok[1][cp],o);
      strncpy(spysok[0][cp],u,o-u);
      spysok[0][cp][o-u]='\0';
      JaPerekliuchyvPisniu=1;
            Play(u);
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)MAINCSM_ID;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
      //ShowMSG(1,(int)u);
            }
            else
            {
              sprintf(playlistname,"Not found!");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        }
        }
      }
    }
            
            
/////////////////////
  
  
  
  if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      switch(msg->submess&0xFFFF)
      {
      case 4: 
        {
          CanPlayNext=1;
          timesec=0;
          timemin=0;
          if ((entime)&&(playing==1)) 
          {
            GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);
          }
        }break;
      case 5:
      case 7:
        {
            timesec=0;
            timemin=0;
            PLAY_ID=0;
            if (playing==1)
              {
                PlayNext();
              }
        }
        break;
        
      case 33: if (playing!=0) 
      {
        if (JaPerekliuchyvPisniu==0)
        {
          playing=0;
        }
        else 
        {
          JaPerekliuchyvPisniu=0;
        }
      }
        break;
      }
    }
  
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp(successed_config_filename,(char *)msg->data0)==0)
    {
      Message(LG_CONFIG_UPDATED);
      InitConfig();
    }
  }

 if (EnableIconOnIdle)
 {
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop((((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
	void *canvasdata=BuildCanvas();
        if (playing!=1) 
        {
          sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\stop.png");
        }
        else 
        {
          sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\play.png");
        }
	DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)name)-1,IDLEICON_Y+GetImgHeight((int)name)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)name);
      }
    }
 }
  return(1);
  
}

const struct
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

void UpdateCSMname(void)
{
  utf8_2ws((WSHDR *)(&MAINCSM.maincsm_name),NameOfCurentTrack,320);
  if (Get_WS_width((WSHDR *)(&MAINCSM.maincsm_name),7)==0)
  {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%t - %t - %t",ctrack,cartist,calbum);
  }
}

void skins()
{
  DIR_ENTRY de;
  NumberOfSkins=0;
  unsigned int err;
  char path[128];
  sprintf(path,"%sskins\\",playerfolder);
  strcpy(name,path);
  strcat(name,zir);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      sprintf(ArrayOfSkins[NumberOfSkins],de.file_name);
      NumberOfSkins++;
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

int main(char *exename, char *fname)
{
  if (!pracuje)
  {
    GBS_StartTimerProc(&PlayerMenu,250,JaLiuBLiuPYVo);
    pracuje=1;
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    identyfikator=ktime.min*60+ktime.sec;
  CheckDoubleRun();
  sprintf(LastPlaylist,fname);
  InitConfig();
  LoadParams();
  skins();
  readskinparamsfromfile();
  AddKeybMsgHook_end((void *)my_keyhook);
mitka:
  if ((LastPlaylist[0]=='0')||(LastPlaylist[0]=='4'))
  {
      char extension[3];
      sprintf(extension,"%c%c%c",LastPlaylist[strlen(LastPlaylist)-3],LastPlaylist[strlen(LastPlaylist)-2],LastPlaylist[strlen(LastPlaylist)-1]);
      if (strcmp_nocase(extension,"ipl")==0)
      {
      playlistmode=1;
      LoadPlaylist(LastPlaylist);
      const char *p=strrchr(LastPlaylist,'\\')+1;
      sprintf(playlistname,p);
      char s[256];
      sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
      playing=1;
      Play(s);
      }
      else 
    {
        if (((extension[0]=='M')||(extension[0]=='m'))&&((extension[2]=='u')||(extension[2]=='U')))
      {
          playlistmode=2;
          LoadM3uPlaylist(LastPlaylist);
          const char *p=strrchr(LastPlaylist,'\\')+1;
          sprintf(playlistname,p);
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          playing=1;
          Play(s);
      } else
      {
        if (strcmp_nocase(extension,"imy")==0)
          {
            playlistmode=3;
            char s[256];
            sprintf(s,LastPlaylist);
            NumberOfTracks=1;
            playing=1;
            s[strlen(s)-4]=0;
            s[0]='4';
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,s,&err))
            {
              CreatePlaylist(de.folder_name);
              VporiadkuvatySpysok();
              cp=0;
              while (strcmp(spysok[1][cp],de.file_name)!=0)
              {
                cp++;
              }
              const char *p=strrchr(de.folder_name,'\\')+1;
                          sprintf(playlistname,p);
            Play(s);
            }
            else
            {
              sprintf(playlistname,"Not found!    ");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        else
        {
          if (strcmp_nocase(extension,"new")==0)
          {
            Message(LG_CREATE_PLAYLIST_PLEASE);
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            playlistmode=0;
            WhatToView=3;
            for (int i=0;i<256;i++){katalogselected[i]=0;}
          }else
        {
          if ((strcmp_nocase(extension,format_1)==0)||(strcmp_nocase(extension,format_2)==0)||(strcmp_nocase(extension,format_3)==0)||(strcmp_nocase(extension,format_4)==0))
          {
            playlistmode=4;
            NumberOfTracks=1;
            playing=1;
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,LastPlaylist,&err))
            {
              CreatePlaylist(de.folder_name);
              VporiadkuvatySpysok();
              cp=0;
              while (strcmp(spysok[1][cp],de.file_name)!=0)
              {
                cp++;
              }
              const char *p=strrchr(de.folder_name,'\\')+1;
                          sprintf(playlistname,p);
            Play(LastPlaylist);
            }
            else
            {
              sprintf(playlistname,"Not found!    ");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        }
        }
      }
    }
  }else
  {
          ReadLastPlaylist();
          if ((LastPlaylist[0]=='0')||(LastPlaylist[0]=='4')){goto mitka;}
          else
          {
            Message(LG_CREATE_PLAYLIST_PLEASE);
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            playlistmode=0;
            WhatToView=3;
            for (int i=0;i<256;i++){katalogselected[i]=0;}
          }
  }
  for (int i=0;i<255;i++){notplayed[i]=0;timelength[i]=-1;}
  if (playlistname[0]==0x1F){playlistname[0]=' ';}
  if (playlistmode!=3) {playlistname[strlen(playlistname)-4]=0;}
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  SUBPROC((void *)findlisttime);
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  }
  else
  {
    for (int i=0;i<255;i++)
    {
      sprintf(spysok[0][i],pp);
      sprintf(spysok[1][i],pp);
    }
    NumberOfTracks=0;
    sprintf(LastPlaylist,fname);
      char extension[3];
      sprintf(extension,"%c%c%c",LastPlaylist[strlen(LastPlaylist)-3],LastPlaylist[strlen(LastPlaylist)-2],LastPlaylist[strlen(LastPlaylist)-1]);
      if (strcmp_nocase(extension,"ipl")==0)
      {
      playlistmode=1;
      LoadPlaylist(LastPlaylist);
      sprintf(playlistname,"media");
      //for (int i=strlen(LastPlaylist)-1;LastPlaylist[i]!='\\';i--){sprintf(playlistname,"%c%s",LastPlaylist[i],playlistname);}
      char s[256];
      sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
      playing=1;
      JaPerekliuchyvPisniu=1;
      Play(s);
      }
      else 
        if (((extension[0]=='M')||(extension[0]=='m'))&&((extension[2]=='u')||(extension[2]=='U')))
      {
          playlistmode=2;
          LoadM3uPlaylist(LastPlaylist);
          const char *p=strrchr(LastPlaylist,'\\')+1;
          sprintf(playlistname,p);
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          playing=1;
          JaPerekliuchyvPisniu=1;
          Play(s);
      }
  for (int i=0;i<255;i++){notplayed[i]=0;timelength[i]=-1;}
  if (playlistname[0]==0x1F){playlistname[0]=' ';}
  UpdateCSMname();
  SUBPROC((void *)findlisttime);
  }

  return 0;
}
