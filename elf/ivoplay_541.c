#include "..\inc\swilib.h"
#include "../inc/xtask_ipc.h"
#include "conf_loader.h"
//#include "..\inc\MATH.h"
//#define PI 3.1415926535

GBSTMR fv,play,red,chas,keyhooktmr;
const char ipc_my_name[32]="Ivoplay";
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;
char spysok[2][255][256];
int deliting=0,curskin=0;
char charofskins[10][255];
int playlistmode=0,temp=0;
char fff[256],playlistname[255];
int notplayed[255],illumusic;
char calbum[128]=" ",ctrack[128]=" ",cvykon[128]=" ";
char ttt[128]="";
int random=0,kskins=0;
int vysota=1;
int timehms[3];
//int tms[250]
int timesec=0,timemin=0;
int cp=0,kilkist=0,cv=4,playing=0,ringoff=0;
int PLAY_ID;
extern const char folder[128];
extern const int keyboard;
extern const int screen;
extern const int wav;
extern const unsigned int dttt;
extern const int entime;
const int minus11=-11;
//static const char pt[]="%t";
//static const char dd[]="\\";
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
//#define MSG_GUI_DESTROYED 152

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
  int i1;
}MAIN_GUI;

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  //{void *canvasdata=BuildCanvas(); 
  //DrawCanvas(canvasdata, 0, 0, 131, 175, 1);}
  char name[256];
  sprintf(name,"%s%s",charofskins[curskin],"\\background.png");
  DrawImg(0,0,(int)name);
  
  //sprintf(name,"%s%s",spysok[0][cp],spysok[1][cp]);
  sprintf(name,"%s%s",charofskins[curskin],"\\random.png");
  if (random==1) {DrawImg(2,2,(int)name);}
  WSHDR* ws=AllocWS(128);
  //wsprintf(ws,"%t\r%t\r%t",calbum,ctrack,cvykon);
  //wsprintf(ws,name);
  wsprintf(ws,"%s",playlistname);
  DrawString(ws,1,50,132,176,8,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
    
  if (entime==1)
  {wsprintf(ws,"\r\r\r\r\r\r\r%i:%i",timemin,timesec);
  DrawString(ws,1,50,132,176,7,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));}

  wsprintf(ws,"\r\r%s",ttt);
  
  DrawString(ws,1,50,132,176,7,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%i%c%i",cp+1,'/',kilkist);
  sprintf(name,"%s%s",charofskins[curskin],"\\prev.png");
  DrawImg(45,18,(int)name);
  sprintf(name,"%s%s",charofskins[curskin],"\\next.png");
  DrawImg(74,18,(int)name);
  
  if (playing==0) {sprintf(name,"%s%s",charofskins[curskin],"\\play.png");DrawImg(62,19,(int)name);}
  else {sprintf(name,"%s%s",charofskins[curskin],"\\stop.png");DrawImg(62,19,(int)name);}
  
  DrawString(ws,1,1,130,176,7,4,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
  sprintf(name,"%s%s",charofskins[curskin],"\\volume.png");
  DrawImg(0,156,(int)name);
  int i;
  sprintf(name,"%s%s",charofskins[curskin],"\\vol.png");
  if (ringoff==0)
  {for (i=0;i<cv;i++)
  {DrawImg(i*9+1,157,(int)name);}
  sprintf(name,"%s%s",charofskins[curskin],"\\plus.png");
  if (cv<14){DrawImg(61,5,(int)name);}
  sprintf(name,"%s%s",charofskins[curskin],"\\minus.png");
  if (cv>0) {DrawImg(61,30,(int)name);}
  }
  else{
    sprintf(name,"%s%s",charofskins[curskin],"\\off.png");
    DrawImg(25,2,(int)name);
  }
}

void SaveOnlyPlaylistParams(char *playy)
{
  int f;
  char g[5];
  char h[3];
  char m[256];
  sprintf(m,playy);
  sprintf(h,"%c%c",0x0D,0x0A);
  unsigned int err;
  f=fopen(m, A_ReadWrite+A_MMCStream, P_WRITE, & err );
  sprintf(g,"%c%c%c%c%c",kilkist,random,cp,0x0D,0x0A);
  fwrite(f,g,5,&err);
  fclose(f,&err);
}

void SavePlaylist(char *playy)
{
  int f;
  char s[1]="*";
  char g[5];
  char h[3];
  char m[256];
  sprintf(m,playy);
  sprintf(h,"%c%c",0x0D,0x0A);
  unsigned int err;
  f=fopen(m, A_WriteOnly+A_MMCStream+A_Create, P_WRITE, & err );
  sprintf(g,"%c%c%c%c%c",kilkist,random,cp,0x0D,0x0A);
  fwrite(f,g,5,&err);
  for (int i=0;i<kilkist;i++)
  {
  fwrite(f,spysok[0][i],strlen(spysok[0][i]),&err);
  fwrite(f,s,1,&err);
  fwrite(f,spysok[1][i],strlen(spysok[1][i]),&err);
  fwrite(f,h,2,&err);
  }
  fclose(f,&err);
}


void LoadPlaylist(char *playy)
{
  //ShowMSG(1,(int)"Please, wait");
  int f;
  char g[5];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  f=fopen(ddd, A_ReadOnly+A_MMCStream, P_READ, & err );
  fread(f,g,5,&err);
  kilkist=g[0];
  random=g[1];
  cp=g[2];
  fread(f,t,1,&err);
  for (int i=0;i<kilkist;i++)
  {
  while (t[0]!='*')
  {
    sprintf(spysok[0][i],"%s%c",spysok[0][i],t[0]);
    fread(f,t,1,&err);
  }
  fread(f,t,1,&err);
  while (t[0]!=0x0D)
  {
    sprintf(spysok[1][i],"%s%c",spysok[1][i],t[0]);
    fread(f,t,1,&err);
  }
  fread(f,t,1,&err);
  fread(f,t,1,&err);
  }
  fclose(f,&err);
}
/*
void LoadPlaylist(char *playy)
{
  //ShowMSG(1,(int)"Please, wait");
  int f,count=0;
  char list[32768];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  f=fopen(ddd, A_ReadOnly+A_MMCStream, P_READ, & err );
  fread(f,list,32767,&err);
  kilkist=list[0];
  t[0]=list[3];
  count=3;
  for (int i=0;i<kilkist;i++)
  {
  while (t[0]!='*')
  {
    sprintf(spysok[0][i],"%s%c",spysok[0][i],t[0]);
    count++;
    t[0]=list[count];
  }
  count++;
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
  fclose(f,&err);
}
*/

void r()
{
  REDRAW();
}

void find(char *ffile)
{
  int i;
  char file[3200];
  sprintf(file,ffile);
  int znaishov=0;
  sprintf(calbum," ");
  sprintf(ctrack," ");
  sprintf(cvykon," ");
  for (i=0;((i<3200)&&(znaishov!=3));i++)
  {
    
  /*  if ((file[i]=='T')&&(file[i+1]=='A')&&(file[i+2]=='L')&&(file[i+3]=='B')) {i=i+11;znaishov++;
  while ((file[i]!=0)&&(file[i]!='T')&&(file[i+1]!='A')) {i++;sprintf(calbum,"%s%c",calbum,file[i]);}}
  
  if ((file[i]=='T')&&(file[i+1]=='I')&&(file[i+2]=='T')&&(file[i+3]=='2')) {i=i+11;znaishov++;
  while ((file[i]!=0)&&(file[i]!='T')&&(file[i+1]!='A')) {sprintf(ctrack,"%s%c",ctrack,file[i]);i++;}}
  
  if ((file[i]=='T')&&(file[i+1]=='P')&&(file[i+2]=='E')&&(file[i+3]=='1')) {i=i+11;znaishov++;
  while ((file[i]!=0)&&(file[i]!='T')&&(file[i+1]!='A')) {sprintf(cvykon,"%s%c",cvykon,file[i]);i++;}}
  */
    //ShowMSG(1,(int)"OK");
    if ((file[i]=='T')&&(file[i+1]=='A')&&(file[i+2]=='L')&&(file[i+3]=='B')) {i=i+11;znaishov++;
  for (int j=i;j<i+10;j++) {sprintf(calbum,"%s%c",calbum,file[j]);}}
  
  }
  REDRAW();
}

void findtegs()
{
  int f;
  char file[3200];
  char name[256];
  unsigned int err;
  sprintf(name,"%s%s",spysok[0][cp],spysok[1][cp]);
  f=fopen(name,A_ReadOnly+A_MMCStream, P_READ, & err );
  fread(f,file,3200,&err);
  fclose(f,&err);
  ShowMSG(2,(int)name);
  find(file);
  
  
  //f=fopen(name,A_WriteOnly+A_MMCStream+A_Create, P_WRITE, & err );
  //fwrite(f,file,3200,&err);
  //fclose(f,&err);
  
  
}


int whattoplaynext()
{
  int neprograni=0;
  for (int i=0;i<255;i++) {if (notplayed[i]==0){neprograni++;}}
  if (neprograni>0)
  {
    TTime time;
    TDate date;
    GetDateTime(&date,&time);
    int l=time.min*5+time.sec;
    while (neprograni<l){l=l-neprograni;}
    neprograni=0;
    for (int i=0;i<255;i++) {if (notplayed[i]==0){neprograni++;if (l==neprograni){return(i);}}}
  }
  else 
  {
    for (int i=0;i<kilkist;i++){notplayed[i]=0;}
    return(whattoplaynext());
    //Всі пісні програно
  }
  return(255);
}

void showvolume()
{
    char name[256];  
    sprintf(name,"%s%s",charofskins[curskin],"\\volume.png");
    DrawImg(0,156,(int)name);
    int i;
    sprintf(name,"%s%s",charofskins[curskin],"\\vol.png");
    for (i=0;i<cv;i++)
    {DrawImg(i*9+1,157,(int)name);}
    GBS_StartTimerProc(&red,262,r);
}

void timepp()
{
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    if (playing==1){if (timehms[2]!=ktime.sec){timesec++;if(timesec==60){timesec=0;timemin++;}if (IsGuiOnTop(MAINGUI_ID)==1){REDRAW();}}GBS_StartTimerProc(&chas,dttt,timepp);}else{timesec=0;timemin=0;}
    timehms[2]=ktime.sec;
}

void Play(const char *fname)
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
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
      sprintf(ttt,spysok[1][cp]);REDRAW();
      notplayed[cp]=1;
      FreeWS(sndPath);
      FreeWS(sndFName);
      timesec=0;
      timemin=0;
      TTime ktime;
      TDate date;
      GetDateTime(&date,&ktime);
      timehms[2]=ktime.sec;
      if (entime==1){GBS_StartTimerProc(&chas,dttt,timepp);}
    }
  }
}

void keyhookplaynext()
{
{if (random==0){if (cp>kilkist-2) {cp=0;}else {cp++;}}else {cp=whattoplaynext();}
     char s[256];sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);playing=1;Play(s);}
}

void keyhookvoidvolmm()
{
  ringoff=0;
if (cv!=0){cv--;ChangeVolume(cv);}showvolume();
}

void keyhookmutem1()
{if (ringoff==0){ChangeVolume(0);ringoff=1;REDRAW();}else{ChangeVolume(cv);ringoff=0;REDRAW();};}

void keyhookvoidvolpp()
{
  ringoff=0;
if(cv!=14){cv++;ChangeVolume(cv);}showvolume();
}

int my_keyhook(int submsg, int msg)
{
  if (submsg!=0x14 && submsg!=0x15 && submsg!=0x27) return(0);
  switch(msg)
  {
    case(KEY_DOWN):
      {switch(submsg)
  {
  case 0x14: GBS_StartTimerProc(&keyhooktmr,27,keyhookvoidvolpp);break;//Верхня
  case 0x15: GBS_StartTimerProc(&keyhooktmr,27,keyhookvoidvolmm);break;//Нижня
  case 0x27: GBS_StartTimerProc(&keyhooktmr,27,keyhookplaynext);break;//Гарнітура
  }}break;
  case(LONG_PRESS):
    {switch(submsg)
  {
  case 0x14: {
  GBS_StartTimerProc(&keyhooktmr,36,keyhookplaynext);
    }break;//Верхня
  case 0x15: break;//Нижня   
  case 0x27: GBS_StartTimerProc(&keyhooktmr,37,keyhookmutem1);break;//Гарнітура
  };}break;
  }
  return(2);
}

void SaveParams()
{
  int f;
  char h[128];
  sprintf(h,"%c%c%s",cv,strlen(charofskins[curskin]),charofskins[curskin]);
  unsigned int err;
  f=fopen("0:\\Zbin\\Ivoplay\\params.txt", A_WriteOnly+A_MMCStream+A_Create, P_WRITE, & err );
  fwrite(f,h,strlen(h),&err);
  fclose(f,&err);
}

void LoadParams()
{
  int f;
  char h[2];
  unsigned int err;
  f=fopen("0:\\Zbin\\Ivoplay\\params.txt", A_ReadOnly+A_MMCStream, P_READ, & err );
  if (f>-1)
  {
    char p[1];
    sprintf(charofskins[curskin],p);
    fread(f,h,2,&err);
    cv=h[0];
    int y=h[1];
    for (int i=0;i<y;i++) {fread(f,h,1,&err);sprintf(charofskins[curskin],"%s%c",charofskins[curskin],h[0]);}
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

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:{Play("0:\\Zbin\\Ivoplay\\stop.imy");
                     GBS_DelTimer(&play);
                     GBS_DelTimer(&red);
                     GBS_DelTimer(&chas);
                     GBS_DelTimer(&fv);
                     GBS_DelTimer(&keyhooktmr);
                     RemoveKeybMsgHook((void *)my_keyhook);
                     SaveParams();
                     if (playlistmode==1){SaveOnlyPlaylistParams(fff);}
                     return(1);
                    }
    case ENTER_BUTTON:case'5':case LEFT_SOFT:{if (playing==1){playing=0;Play("0:\\Zbin\\Ivoplay\\stop.imy");}
else{char s[256];sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);playing=1;Play(s);}};break;
case'*':keyhookmutem1();break;
    case 0x14:case UP_BUTTON:case'2':ringoff=0;if (ringoff==1){ChangeVolume(cv);}else{if (cv!=14){cv++;ChangeVolume(cv);}}REDRAW();break;
    case 0x15:case DOWN_BUTTON:case'8':ringoff=0;if (ringoff==1){ChangeVolume(cv);}else{if (cv!=0){cv--;ChangeVolume(cv);}}REDRAW();;break;
    case LEFT_BUTTON:case'4':{if (random==0){if (cp<1) {cp=kilkist-1;}else {cp--;}}else{cp=whattoplaynext();}
     char s[256];sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);playing=1;Play(s);};break;
    case 0x27:case RIGHT_BUTTON:case'6':{if (random==0){if (cp>kilkist-2) {cp=0;}else {cp++;}}else {cp=whattoplaynext();}
     char s[256];sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);playing=1;Play(s);};break;
     case'0':{WSHDR* ws=AllocWS(128);wsprintf(ws,"0:\\ZBin\\etc\\ivoplay.bcfg");ExecuteFile(ws,0,"");FreeWS(ws);}break;
    case GREEN_BUTTON: if (playlistmode==0){playlistmode=1;sprintf(fff,"%s%s",folder,"\\playlist.ipl");SavePlaylist(fff);}break;
    case '3':{random=1-random;REDRAW();};break;
    case '7':{if (curskin!=kskins-1){curskin++;}else{curskin=0;}REDRAW();};break;
    case '9':{if (curskin!=0){curskin--;}else{curskin=kskins-1;}REDRAW();};break;
    //case RIGHT_SOFT:{findtegs();}break;
    case'#':{
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
      if (IsUnlocked())
      {
        KbdLock();
      }
    }break;
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case'#':{
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
      if (IsUnlocked()) {KbdLock();}
      }
    }
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

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif

int method8(void){return(0);}

int method9(void){return(0);}

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
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

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
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

void si(znach,delay)
{
  if (screen==1) {SetIllumination(0,1,znach,delay);}
  if (keyboard==1) {SetIllumination(1,1,znach,delay);}
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      switch(msg->submess&0xFFFF)
      {
      case 4:ChangeVolume(cv);break;
      case 5:case 7:
        {
            timesec=0;
            timemin=0;
            PLAY_ID=0;
            if (playing==1){
            if (random==0){if (cp>kilkist-2) {cp=0;}else {cp++;}}else {cp=whattoplaynext();}
            char s[256];sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);Play(s);}
        }
        break;
        
      case 31:si(0,800);break;
      case 32:si(100,100);break;
      //case 33: if (playing!=0) {playing=0;} break;
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
      ShowMSG(1,(int)"Config updated!");
      InitConfig();
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Ivoplay");
  FreeWS(ws);
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

void stvspysku(char *foldder)
{
  DIR_ENTRY de;
  unsigned int err;
  char name[256];
  char path[128];
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  
  strcat(name,zir);
  
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      if (!IsFile(name)){stvspysku(name);}
    }
    while(FindNextFile(&de,&err));
  }

  
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  strcat(name,"*.mp3");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][kilkist],de.file_name);
      sprintf(spysok[0][kilkist],path);
      kilkist++;
    }
    while(FindNextFile(&de,&err));
  }
  
  
  if (wav==1)
  {
    
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  strcat(name,"*.wav");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][kilkist],de.file_name);
      sprintf(spysok[0][kilkist],path);
      kilkist++;
    }
    while(FindNextFile(&de,&err));
  }
  
  }
  
  
  
  FindClose(&de,&err);
}


void skins()
{
  DIR_ENTRY de;
  unsigned int err;
  char name[256];
  char path[128];
  sprintf(path,"0:\\Zbin\\Ivoplay\\skins\\");
  strcpy(name,path);
  
  strcat(name,zir);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(charofskins[kskins],"%s%s",path,de.file_name);
      kskins++;
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}


int main(char *exename, char *fname)
{
  sprintf(fff,fname);
  InitConfig();
  LoadParams();
  skins();
  curskin=0;
  char t[128];
  sprintf(t,folder);
  AddKeybMsgHook_end((void *)my_keyhook);
  ///////////////////////
  //stvspysku(t);
  ////////////////////////
  if (strlen(fname)>5) {
    playlistmode=1;LoadPlaylist(fname);
      
      const char *p=strrchr(fname,'\\')+1;
      sprintf(playlistname,p);
      char s[256];
      sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
      playing=1;
      Play(s);
  
  }else{
    stvspysku(t);
    sprintf(playlistname,"No playlist");
  }
  for (int i=0;i<kilkist;i++){notplayed[i]=0;}
  for (int i=kilkist;i<255;i++){notplayed[i]=1;}
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}
