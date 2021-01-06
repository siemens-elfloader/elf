/*TODO
символы между английскими и русскими буквами*/
#include "main.h"


//PARAMETERS
extern const unsigned int col_bg;

//VARS
char idxn[250];
FileBuff fb;
PageBuff pb;
int sh,sw;
unsigned int err;
unsigned int fsize;

WSHDR *ws;
char w,h;

/*#ifdef DEBUG
int logf;
unsigned int ul;
char lbf[2000];
#endif
*/
#pragma inline
void patch_input(INPUTDIA_DESC* inp,int x,int y,int x2,int y2)
{
  inp->rc.x=x;
  inp->rc.y=y;
  inp->rc.x2=x2;
  inp->rc.y2=y2;
}

#pragma inline
void patch_header(HEADER_DESC* head,int x,int y,int x2,int y2)
{
  head->rc.x=x;
  head->rc.y=y;
  head->rc.x2=x2;
  head->rc.y2=y2;
}

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

extern "C" void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  FreeWS(ws);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void GUIRedraw(MAIN_GUI *data)
{
  DrawRoundedFrame(0,0,sw-1,sh-1,0,0,0,GetPaletteAdrByColorIndex(col_bg), GetPaletteAdrByColorIndex(col_bg));
  pb.DrawPage();
}

void GUICreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void GUIClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void GUIFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void GUIUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int GUIOnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN))//||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
      pb.Prev();
      break;
    case DOWN_BUTTON:
      pb.Next();
      break;
    case RIGHT_BUTTON:
      break;
    case LEFT_BUTTON:
      break;
    case LEFT_SOFT:
    case RIGHT_SOFT:
      return(1);
    }
  }
  DirectRedrawGUI();
  return(0);
}
void GUIDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  int idxf=fopen(idxn,A_BIN+A_ReadOnly,P_READ,&err);
  char bf1=0x32;
  char bf3[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  if (idxf>0)
  {
    char bf1;
    char bf3[25];
    fread(idxf,&bf1,1,&err);
    fread(idxf,bf3,25,&err);
    fclose(idxf,&err);
  }
//  idxf=fopen(idxn,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err);
  idxf=fopen(idxn,A_WriteOnly+A_Create+A_Truncate,P_WRITE,&err);
  if (idxf!=-1)
  {
    fwrite(idxf,&bf1,1,&err);
    unsigned long spos=fb.Pos();
    fwrite(idxf,&spos,4,&err);
    fwrite(idxf,bf3,25,&err);
    fclose(idxf,&err);
  }
  
  fb.FileCl();
  pb.Destroy();
 
  kill_data(data,mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)GUIRedraw,
  (void *)GUICreate,
  (void *)GUIClose,
  (void *)GUIFocus,
  (void *)GUIUnfocus,
  (void *)GUIOnKey,
  0,
  (void *)GUIDestroy,
  (void *)method8,
  (void *)method9,
  0
};

void maincsm_oncreate(CSM_RAM *data)
{
  ws=AllocWS(256);
  MAIN_GUI *main_gui=(MAIN_GUI *)malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  RECT Canvas={0,0,sw-1,sh-1};
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(RECT *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

const int minus11=-11;

const CSM_DESC maincsm=
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
};

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
} 


int main(char *elf, char *param)
{
  char dummy[sizeof(MAIN_CSM)];
  sh=ScreenH();
  sw=ScreenW();
  if ((!sh)||(!sw))
  {
    ShowMSG(1,(int)"Couldn't get screen size!");
    SUBPROC((void *)ElfKiller);
    return 0;
  }

#ifdef DEBUG
  logf=fopen("0:\\reader.txt",A_ReadWrite+A_TXT+A_Truncate+A_Create,P_READ+P_WRITE,&ul);
  sprintf(lbf,"sh-%u sw-%u\n",sh,sw);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif
  
  char *name=param;
  fsize=get_file_size(name);

#ifdef DEBUG
  sprintf(lbf,"size-%u\n",fsize);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif  
  
  if (!fb.FileSet(name))
  {
    ShowMSG(1,(int)"Couldn't open file!");
    SUBPROC((void *)ElfKiller);
    return 0;
  }
  
  extern void InitConfig();
  InitConfig();
  
  strcpy(idxn,name);
  for (int i=strlen(name);i>0;i--)
    if (idxn[i]=='.') {idxn[i]='_';break;}
  strcat (idxn,".idx");

#ifdef DEBUG
  sprintf(lbf,"idx-%s\n",idxn);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif  

  int idxf=fopen(idxn,A_BIN+A_ReadOnly,P_READ,&err);
  unsigned long spos=0;
  if (idxf!=-1)
  {
    char bf[4];
    fread(idxf,bf,1,&err);
    fread(idxf,bf,4,&err);
    spos=*((unsigned long *)&bf[0]);
    if (spos>fsize) spos=0;
    fclose(idxf,&err);
  }
#ifdef DEBUG
  sprintf(lbf,"idx pos-%u\n",spos);
  fwrite(logf,lbf,strlen(lbf),&ul);
#endif 
  pb.Init(spos);
  LockSched();
  CreateCSM(&maincsm,dummy,0);
  UnlockSched();
  return 0;
}
