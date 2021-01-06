#include "..\inc\swilib.h"
#include "strings.h"
#include "conf_loader.h"

#define ECINPUT 3
#define ECOUTPUT 5
#define ECOUTPUT2 7
#define ECOUTPUT3 9
#define ECOUTPUT4 11
#define ECOUTPUT5 13
#define ECOUTPUT6 15
#define ECOUTPUT7 17
#define ECOUTPUT8 19

const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
GUI *ggui=0;
////for read file
int f;
int fsize;
unsigned int ul;
int i;
int j;
int y;
int u;
int ex;
int ex1;
int len_ex;
int save_m;
int beg_len;
int kil;
extern const char rms_file[64];
char rms_path[64];

char app1[64];
char app2[64];
char app3[64];
char app4[64];
char app5[64];
char app6[64];
char app7[64];
char app8[64];

char day_1[64];
char day_1_1[256];
//char fails[10000];
///////

#define wslen(ws) ws->wsbody[0]

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
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

void Check_if_is_file()
{
  volatile int hFile;
  unsigned int io_error = 0;
  FSTATS stat;
  GetFileStats(rms_path,&stat,&ul);
  if(stat.size<7)
  {
    char *text=malloc(256);
    sprintf(text, "rms_the_begin_of_the_file");
    hFile = fopen(rms_path,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, text, strlen(text), &io_error);
      fclose(hFile, &io_error);
    }
    mfree(text);
  }
}

void day_extractor()
{
  ex=0;
  ex1=0;
  len_ex=strlen(day_1_1);
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app1[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app1[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app2[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app2[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app3[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app3[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app4[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app4[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app5[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app5[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app6[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app6[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app7[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app7[ex]='\0';
  ex=0;
  ex1++;
  while((day_1_1[ex1]!=';')&&(ex1<len_ex))
  {
    app8[ex]=day_1_1[ex1];
    ex++;
    ex1++;
  }
  app8[ex]='\0';
  WSHDR *ws01=ascii2ws(app1);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT,ws01);
      FreeWS(ws01);
      DirectRedrawGUI();
      WSHDR *ws02=ascii2ws(app2);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT2,ws02);
      FreeWS(ws02);
      DirectRedrawGUI();
      WSHDR *ws03=ascii2ws(app3);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT3,ws03);
      FreeWS(ws03);
      DirectRedrawGUI();
      WSHDR *ws04=ascii2ws(app4);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT4,ws04);
      FreeWS(ws04);
      DirectRedrawGUI();
      WSHDR *ws05=ascii2ws(app5);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT5,ws05);
      FreeWS(ws05);
      DirectRedrawGUI();
      WSHDR *ws06=ascii2ws(app6);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT6,ws06);
      FreeWS(ws06);
      DirectRedrawGUI();
      WSHDR *ws07=ascii2ws(app7);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT7,ws07);
      FreeWS(ws07);
      DirectRedrawGUI();
      WSHDR *ws08=ascii2ws(app8);
      EDIT_SetTextToEditControl(ggui, ECOUTPUT8,ws08);
      FreeWS(ws08);
      DirectRedrawGUI();
}
    

void open_file(void)
{
  FSTATS stat;
  GetFileStats(rms_path,&stat,&ul);
  if(stat.size>0)
  {
  f=fopen(rms_path,A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  }
  else
    ShowMSG(1,(int)"Failed");
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
  EDITCONTROL ec;
  ExtractEditControl(ggui,  ECINPUT, &ec);     
  char *p1=ws2ascii(ec.pWS);
  char p2[]="day";
  char *s,*s1,*s2;
  int len, len2;
  if(strlen(p1)>0)
  {
  if((s1=strstr(p,p1))>0)
  {
    s1+=strlen(p1);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1;
      if(len>8)
      {
      s=malloc(len+1);
      strncpy(s,s1,len);
      s[len]='\0';
      char *s_r=malloc(256);
      sprintf(s_r, "%s%s", p1,s);
      i=0;
      j=0;
      while(s_r[i]!=';')
      {
        day_1[j]=s_r[i];
        j++;
        i++;
      }
      day_1[j]='\0';
      WSHDR *ws01=ascii2ws(day_1);
      EDIT_SetTextToEditControl(ggui, ECINPUT,ws01);
      FreeWS(ws01);
      DirectRedrawGUI();
      i++;
      j=0;
      len2=strlen(s_r)-2;
      while(i!=len2)
      {
        day_1_1[j]=s_r[i];
        j++;
        i++;
      }
      day_1_1[j]='\0';
//      WSHDR *ws02=ascii2ws(day_1_1);
//      EDIT_SetTextToEditControl(ggui, ECOUTPUT,ws02);
//      FreeWS(ws02);
//      DirectRedrawGUI();
      day_extractor();
      mfree(s);
      mfree(s_r);
      ShowMSG(1,(int)"Found!!");
      }
    }
  }
  else
  {
    char *nonez=malloc(20);
    sprintf(nonez, "00:00 to do");
    WSHDR *ws02=ascii2ws(nonez);
    EDIT_SetTextToEditControl(ggui, ECOUTPUT,ws02);
    FreeWS(ws02);
    mfree(nonez);
    DirectRedrawGUI();
    ShowMSG(1,(int)"Not Found, Creating!");
  }
  mfree(p);
  mfree(p1);
  }
  else
  {
    mfree(p);
    mfree(p1);
    ShowMSG(1,(int)"Please input date!!");
  }
}

void save_file(void)
{
  volatile int hFile;
  unsigned int io_error = 0;
//////////////get file properties
  FSTATS stat;
  GetFileStats(rms_path,&stat,&ul);
  if(stat.size>0)
  {
  f=fopen(rms_path,A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  }
  else
    ShowMSG(1,(int)"Failed");
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
////////////get file properties1
  EDITCONTROL ec;
  ExtractEditControl(ggui,  ECINPUT, &ec);     
  char *p1=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT, &ec);     
  char *apz1=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT2, &ec);     
  char *apz2=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT3, &ec);     
  char *apz3=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT4, &ec);     
  char *apz4=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT5, &ec);     
  char *apz5=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT6, &ec);     
  char *apz6=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT7, &ec);     
  char *apz7=ws2ascii(ec.pWS);
  ExtractEditControl(ggui,  ECOUTPUT8, &ec);     
  char *apz8=ws2ascii(ec.pWS);
  char *str2=malloc(640);
  if(strlen(apz1)>=5) sprintf(str2, "%s;", apz1);
  if(strlen(apz2)>=5) sprintf(str2, "%s%s;", str2, apz2);
  if(strlen(apz3)>=5) sprintf(str2, "%s%s;", str2, apz3);
  if(strlen(apz4)>=5) sprintf(str2, "%s%s;", str2, apz4);
  if(strlen(apz5)>=5) sprintf(str2, "%s%s;", str2, apz5);
  if(strlen(apz6)>=5) sprintf(str2, "%s%s;", str2, apz6);
  if(strlen(apz7)>=5) sprintf(str2, "%s%s;", str2, apz7);
  if(strlen(apz8)>=5) sprintf(str2, "%s%s;", str2, apz8);
  mfree(apz1);
  mfree(apz2);
  mfree(apz3);
  mfree(apz4);
  mfree(apz5);
  mfree(apz6);
  mfree(apz7);
  mfree(apz8);
  char p2[]="day";
  char *s,*s1,*s2;
  int len, len_beg, h, len_end, len_end2;
  if((strlen(p1)>=8)&&(strlen(str2)>5))
  {
  if((s1=strstr(p,p1))>0)
  {
    s1+=strlen(p1);
    if((s2=strstr(s1,p2))>0)
    {
      len_beg=p-s1;
      len_beg=-(len_beg);
      if(save_m==2) len_beg=len_beg-strlen(p1)-3;
      char *txt_beg=malloc(len_beg+1);
      h=0;
      while(h<len_beg)
      {
        txt_beg[h]=p[h];
        h++;
      }
      txt_beg[h]='\0';
      len=s2-s1;
      h=0;
      len_end=len_beg+len;
      if(save_m==2) len_end=len_end+strlen(p1)+3;
      len_end2=fsize-len_end;
      s=malloc(len_end2+1);
      while(len_end<fsize)
      {
        s[h]=p[len_end];
        len_end++;
        h++;
      }
      s[h]='\0';
      char *text=malloc(strlen(p)+100);
      if(save_m==1)
      sprintf(text, "%s;%s  %s", txt_beg, str2, s);
      if (save_m==2)
      sprintf(text, "%s%s", txt_beg, s);
      hFile = fopen(rms_path,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
      if(hFile!=-1)
      {
        fwrite(hFile, text, strlen(text), &io_error);
        fclose(hFile, &io_error);
      }
      mfree(s);
      mfree(str2);
      mfree(txt_beg);
      mfree(p);
      mfree(p1);
      mfree(text);
      if(save_m==2)
        ShowMSG(1,(int)"Deleted data!");
      else
      ShowMSG(1,(int)"Saved new data!");
    }
  }
  else
  {
    char *text2=malloc(strlen(p1)+strlen(str2)+10);
    sprintf(text2, "%s;%s  day",  p1,str2);
    hFile = fopen(rms_path,A_ReadWrite + A_Create + A_Append + A_BIN,P_READ+P_WRITE, &io_error);
    if(hFile!=-1)
    {
      fwrite(hFile, text2, strlen(text2), &io_error);
      fclose(hFile, &io_error);
    }
    mfree(text2);
    mfree(p1);
    mfree(str2);
    mfree(p);
    ShowMSG(1,(int)"Added new day!");
  }
  }
  else
  {
    mfree(p);
    mfree(p1);
    mfree(str2);
    ShowMSG(1,(int)"Intput date and app.!!");
  }
}

void OnRedraw(MAIN_GUI *data)
{       
  
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
#ifndef NEWSGOLD
    case RED_BUTTON:       
      
      return(1);
#endif
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

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
  (void *)method7,	
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);    
  void create_ed();
  SUBPROC((void *)create_ed);
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MRS Editor 0.5 - (c)Evilfox");
}

int main()
{
  InitConfig();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched(); 
  sprintf(rms_path, "%sfile.mrs", rms_file);
  Check_if_is_file();
  return 0;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

void edchat_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC skk={0x0018, 0x0000,(int)"Menu"};
  if (cmd==7)
    SetSoftKey(data,&skk,SET_SOFT_KEY_N); 
}

int itemnum, wd_id;

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  
  void create_ed(void);
  
  switch (msg->gbsmsg->submess)
  {
    
#ifndef NEWSGOLD
  case RED_BUTTON:
    
    CloseCSM(MAINCSM_ID);
    break;
#endif  
    
  case GREEN_BUTTON:
//      SUBPROC((void *)open_file);
    break;
  }
  if (msg->keys==0x18)
  {
    void MMenu();
    MMenu();
  }
  if (msg->keys==0x1)
  {
    CloseCSM(MAINCSM_ID);
  }
  return(0); 
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"MRS Editor 0.6",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};


void create_ed(void)
{
  
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(50);
  ConstructEditControl(&ec,1,0,0,12);
  AddEditControlToEditQend(eq,&ec,ma); 
  
  utf8_2ws(ws, "Day.month.year:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,10);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  utf8_2ws(ws, "Appointments1:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments2:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments3:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments4:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments5:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments6:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments7:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  utf8_2ws(ws, "Appointments8:",20);
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma);   
  
  ConstructEditControl(&ec,3,0x40,0,255);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
}

// menu

void search(GUI *data)
{
    SUBPROC((void *)open_file);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

void save(GUI *data)
{
  save_m=1;
    SUBPROC((void *)save_file);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}

void delet(GUI *data)
{
  save_m=2;
    SUBPROC((void *)save_file);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}


void about(GUI *data)
{
  ShowMSG(1,(int)"MRS Editor 0.6 (c)Evilfox");
}

void exit(GUI *data)
{
  CloseCSM(MAINCSM_ID);
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,0,0,icon,(int)"Menu",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[5]=
{
  {NULL,(int)"Search",   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Save",     LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Delete",   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"About",    LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Exit",     LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[5]={
  search,
  save,
  delet,
  about,
  exit
};

const SOFTKEY_DESC menu_sk1[]=
{
  {0x0018,0x0000,(int)"OK"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt1=
{
  (SOFTKEY_DESC *)menu_sk1,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt1,
  0,
  NULL,
  menuitems,
  menuprocs,
  5
};

void MMenu(void)
{
  patch_header(&menuhdr);
  CreateMenu(0,0,&tmenu,&menuhdr,0,5,0,0);
}
