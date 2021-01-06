#include "../inc/swilib.h"
#include "rect_patcher.h"

extern void kill_data(void *p, void (*func_p)(void *));
extern int strcmp_nocase(const char *s, const char *d);

const char *successed_extfile="";
volatile int main_gui_id;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  int ext;
  int small_png;
  int large_png;
  int elf;
  int altelf;
}ES;

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}


const char _percent_t[]="%t";
const char _empty_str[]="";

int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Add"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


ES *es=NULL;
int ES_num=0;

char **lines=NULL;
int lines_n=0;

void ParseLines()   // Теперь работаем только со строками
{
  ES *p=NULL;
  int cur_line=0;
  char *cline;
  p=es=malloc(sizeof(ES));
  ES_num=1;
  p->ext=-1;
  p->small_png=-1;
  p->large_png=-1;
  p->elf=-1;
  p->altelf=-1;
  for(int n=lines_n; cur_line<n; cur_line++)
  {
    cline=lines[cur_line];
    if (cline[0]==';') continue;   // Пропускаем комментарий
    if (cline[0]=='[')
    {
      p=es=realloc(es,(ES_num+1)*sizeof(ES));
      p+=ES_num;
      p->ext=cur_line;
      p->elf=-1;
      p->altelf=-1;
      p->small_png=-1;
      p->large_png=-1;
      ES_num++;
      continue;
    }
    if (!strncmp(cline,"RUN=",4))
    {
      p->elf=cur_line;
      continue;
    }
    if (!strncmp(cline,"SMALL=",6))
    {
      p->small_png=cur_line;
      continue;
    }
    if (!strncmp(cline,"BIG=",4))
    {
      p->large_png=cur_line;
      continue;
    }
    if (!strncmp(cline,"ALTRUN=",7))
    {
      p->altelf=cur_line;
      continue;
    }
  }
}

int ParseExtCfg(const char *fname)  // Разобьем файл на строки
{
  int f;
  unsigned int err;
  FSTATS fstat;
  char *buf, *p, *fl;
  int c;
  
  if (GetFileStats(fname,&fstat,&err)<0) return (-1);
  if ((f=fopen(fname,A_ReadOnly|A_BIN,P_READ,&err))==-1) return (-1);
  p=buf=malloc(fstat.size+1);
  buf[fread(f,buf,fstat.size,&err)]=0;
  fclose(f,&err);
  fl=p;
  for(;;)
  {
    c=*p;
    if (c=='\r' || c=='\n' || c==0)
    {
      char *cline;
      lines=realloc(lines,(lines_n+1)*sizeof(char *));
      cline=malloc(p-fl+1);
      memcpy(cline,fl,p-fl);
      cline[p-fl]=0;
      lines[lines_n]=cline;
      lines_n++;
      if (c=='\r' && *(p+1)=='\n') p++;
      fl=p+1;
      if (c==0) break;
    }
    p++;
  }
  mfree(buf);
  successed_extfile=fname;
  return 1;
}

  
int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
  else c-=8;
  c+=0x400;
  return (c); 
}


int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;
    else if (c==4) c=2;
    else if (c==6) c=10;
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16;
    else if (c==0x54) c=18;
    else if (c==0x56) c=11;
    else if (c==0x57) c=23;
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}

enum CFG_TYPES {
  EXT,
  RUN,
  SMALL,
  BIG,
  ALTRUN
};

int PasteLine(ES *p, int type)
{
  char **new_lines, **pp;
  int n=0, d;
  if (type==RUN)
    if ((d=p->ext)!=-1) n=d+1;
  if (type==SMALL || !n)
    if ((d=p->elf)!=-1) n=d+1;
  if (type==BIG || !n)
    if ((d=p->small_png)!=-1) n=d+1;
  if (type==ALTRUN || !n)
    if ((d=p->large_png)!=-1) n=d+1;
  if (!n) return (-1);
  new_lines=malloc((lines_n+1)*sizeof(char *));
  pp=lines;
  for (int i=0, d=0, k=lines_n+1; i<k; i++)
  {
    if (i!=n) new_lines[i]=pp[d++];
    else new_lines[i]=NULL;
  }
  for (int i=0; i<ES_num; i++)  // Подкорректируем ссылки на номера линий
  {
    ES *t=es+i;
    if ((d=t->ext)!=-1) 
      if (d>=n) t->ext=d+1;
    if ((d=t->small_png)!=-1) 
      if (d>=n) t->small_png=d+1;    
    if ((d=t->large_png)!=-1) 
      if (d>=n) t->large_png=d+1;
    if ((d=t->elf)!=-1) 
      if (d>=n) t->elf=d+1;
    if ((d=t->altelf)!=-1) 
      if (d>=n) t->altelf=d+1;    
  }
  lines=new_lines;
  lines_n++;
  mfree(pp);  
  return (n);
}

void DeleteLine(int n)
{
  int d;
  char **new_lines, **pp;
  for (int i=0; i<ES_num; i++)  // Подкорректируем ссылки на номера линий
  {
    ES *t=es+i;
    if ((d=t->ext)!=-1) 
    {
      if (d>n) t->ext=d-1;
      else if (d==n) t->ext=-1;
    }
    if ((d=t->small_png)!=-1) 
    {
      if (d>n) t->small_png=d-1;
      else if (d==n) t->small_png=-1;
    }  
    if ((d=t->large_png)!=-1) 
    {
      if (d>n) t->large_png=d-1;
      else if (d==n) t->large_png=-1;
    }
    if ((d=t->elf)!=-1) 
    {
      if (d>n) t->elf=d-1;
      else if (d==n) t->elf=-1;
    }
    if ((d=t->altelf)!=-1) 
    {
      if (d>n) t->altelf=d-1;
      else if (d==n) t->altelf=-1;
    }
  }
  mfree(lines[n]);
  new_lines=malloc((lines_n-1)*sizeof(char *));
  pp=lines;
  for (int i=0, k=lines_n-1; i<k; i++)
  {
    if (i<n) new_lines[i]=pp[i];
    else new_lines[i]=pp[i+1];
  }
  lines=new_lines;
  lines_n--;
  mfree(pp);
}

extern void open_select_file_gui(void *ed_gui);
void on_file_select(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,_percent_t,"SelectFile");
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      open_select_file_gui(item->user_pointer);
      break;
    }
  }   
}


void new_or_editext_locret(void){}

int new_or_editext_onkey(GUI *data, GUI_MSG *msg)
{
  char *s, tmp[132];
  int is_any_change=0;
  int n;
  int efocus;
  WSHDR *ws;
  ES *cur_es=EDIT_GetUserPointer(data);
  ES *p=NULL;
  char *cline;
  efocus=EDIT_GetFocus(data);
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==ENTER_BUTTON)
    {
      if (efocus==4 || efocus==6 ||
          efocus==8 || efocus==10)
      {
        EDIT_OpenOptionMenuWithUserItems(data,on_file_select,data,1);
        return (-1);
      }
    }
  }      
  if (msg->keys==0xFFF)
  {
    EDITCONTROL ec;
    ExtractEditControl(data,2,&ec);   // Extension
    ws=ec.pWS;
    s=tmp;
    *s++='[';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s++=']';
    *s=0;
    if (cur_es)  // Изменение 
    {
      if ((n=cur_es->ext)!=-1)
      {
        if (strcmp(tmp,lines[n]))
        {
          lines[n]=realloc(lines[n],strlen(tmp)+1);
          strcpy(lines[n],tmp);
          is_any_change=1;
        }
      }
    }
    else   // Добавление
    {
      if (ws->wsbody[0])
      {
        for (int i=0; i<ES_num; i++)
        {
          int index=es[i].ext;
          if (index!=-1)
          {
            if (strcmp_nocase(lines[index],tmp)==0)
            {
              ShowMSG(1,(int)"Extension already registered!");
              return (-1);
            }
          }
        }
        p=es=realloc(es,(ES_num+1)*sizeof(ES));
        p+=ES_num;
        lines=realloc(lines,(lines_n+1)*sizeof(char *));
        cline=malloc(strlen(tmp)+1);
        strcpy(cline,tmp);
        lines[lines_n]=cline;
        p->ext=lines_n;
        lines_n++;
        ES_num++;
        is_any_change=1;
      }
    }
      
    ExtractEditControl(data,4,&ec);   // RUN
    ws=ec.pWS;
    s=tmp;
    *s++='R';
    *s++='U';
    *s++='N';
    *s++='=';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s=0;
    if (cur_es)  // Изменение 
    {
      if ((n=cur_es->elf)!=-1)
      {
        if (ws->wsbody[0])
        {
          if (strcmp(tmp,lines[n]))
          {
            lines[n]=realloc(lines[n],strlen(tmp)+1);
            strcpy(lines[n],tmp);
            is_any_change=1;
          }
        }
        else
        {
          DeleteLine(n);
          is_any_change=1;         
        }
      }
      else
      {
        if (ws->wsbody[0])
        {
          n=PasteLine(cur_es,RUN);
          if (n!=-1)
          {
            lines[n]=malloc(strlen(tmp)+1);
            strcpy(lines[n],tmp);
            cur_es->elf=n;
            is_any_change=1;
          }
        }
      }
    }
    else   // Добавление
    {
      if (ws->wsbody[0])
      {
        lines=realloc(lines,(lines_n+1)*sizeof(char *));
        cline=malloc(strlen(tmp)+1);
        strcpy(cline,tmp);
        lines[lines_n]=cline;
        p->elf=lines_n;
        lines_n++;
        is_any_change=1;
      }
    }
    
    ExtractEditControl(data,6,&ec);   // SMALL
    ws=ec.pWS;
    s=tmp;
    *s++='S';
    *s++='M';
    *s++='A';
    *s++='L';
    *s++='L';
    *s++='=';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s=0;
    if (cur_es)  // Изменение 
    {
      if ((n=cur_es->small_png)!=-1)
      {
        if (ws->wsbody[0])
        {
          if (strcmp(tmp,lines[n]))
          {
            lines[n]=realloc(lines[n],strlen(tmp)+1);
            strcpy(lines[n],tmp);
            is_any_change=1;
          }
        }
        else
        {
          DeleteLine(n);
          is_any_change=1;        
        }
      }
      else
      {
        if (ws->wsbody[0])
        {
          n=PasteLine(cur_es,SMALL);
          if (n!=-1)
          {
            lines[n]=malloc(strlen(tmp)+1);
            strcpy(lines[n],tmp);
            cur_es->small_png=n;
            is_any_change=1;
          }
        }
      }
    }
    else   // Добавление
    {
      if (ws->wsbody[0])
      {
        lines=realloc(lines,(lines_n+1)*sizeof(char *));
        cline=malloc(strlen(tmp)+1);
        strcpy(cline,tmp);
        lines[lines_n]=cline;
        p->small_png=lines_n;
        lines_n++;
        is_any_change=1;
      }
    }
    
    ExtractEditControl(data,8,&ec);   // BIG
    ws=ec.pWS;
    s=tmp;
    *s++='B';
    *s++='I';
    *s++='G';
    *s++='=';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s=0;
    if (cur_es)  // Изменение 
    {
      if ((n=cur_es->large_png)!=-1)
      {
        if (ws->wsbody[0])
        {
          if (strcmp(tmp,lines[n]))
          {
            lines[n]=realloc(lines[n],strlen(tmp)+1);
            strcpy(lines[n],tmp);
            is_any_change=1;
          }
        }
        else
        {
          DeleteLine(n);
          is_any_change=1;        
        }
      }
      else
      {
        if (ws->wsbody[0])
        {
          n=PasteLine(cur_es,BIG);
          if (n!=-1)
          {
            lines[n]=malloc(strlen(tmp)+1);
            strcpy(lines[n],tmp);
            cur_es->large_png=n;
            is_any_change=1;
          }
        }
      }
    }
    else   // Добавление
    {
      if (ws->wsbody[0])
      {
        lines=realloc(lines,(lines_n+1)*sizeof(char *));
        cline=malloc(strlen(tmp)+1);
        strcpy(cline,tmp);
        lines[lines_n]=cline;
        p->large_png=lines_n;
        lines_n++;
        is_any_change=1;
      }
    }
    
    ExtractEditControl(data,10,&ec);   // ALTRUN
    ws=ec.pWS;
    s=tmp;
    *s++='A';
    *s++='L';
    *s++='T';
    *s++='R';
    *s++='U';
    *s++='N';
    *s++='=';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s=0;
    if (cur_es)  // Изменение 
    {
      if ((n=cur_es->altelf)!=-1)
      {
        if (ws->wsbody[0])
        {
          if (strcmp(tmp,lines[n]))
          {
            lines[n]=realloc(lines[n],strlen(tmp)+1);
            strcpy(lines[n],tmp);
            is_any_change=1;
          }
        }
        else
        {
          DeleteLine(n);
          is_any_change=1;
        }
      }
      else
      {
        if (ws->wsbody[0])
        {
          n=PasteLine(cur_es,ALTRUN);
          if (n!=-1)
          {
            lines[n]=malloc(strlen(tmp)+1);
            strcpy(lines[n],tmp);
            cur_es->altelf=n;
            is_any_change=1;
          }
        }
      }
    }
    else   // Добавление
    {
      if (ws->wsbody[0])
      {
        lines=realloc(lines,(lines_n+1)*sizeof(char *));
        cline=malloc(strlen(tmp)+1);
        strcpy(cline,tmp);
        lines[lines_n]=cline;
        p->altelf=lines_n;
        lines_n++;
        is_any_change=1;
      }
    }
    
    if (is_any_change)
    {
      int f;
      unsigned int err;
      char r='\r';
      void *gui;
      if ((f=fopen(successed_extfile,A_WriteOnly|A_BIN|A_Truncate|A_Create,P_WRITE,&err))!=-1)
      {
        for (int i=0; i<lines_n; i++)
        {
          fwrite(f,lines[i],strlen(lines[i]),&err);
          fwrite(f,&r,1,&err);
        }
        fclose(f,&err);
      }
      gui=FindGUIbyId(main_gui_id, NULL);
      if (gui)
      {
        Menu_SetItemCountDyn(gui, ES_num);
        RefreshGUI();
      }
    }
    return (1);
  }
  return (0);
}

void new_or_editext_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Save!"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

HEADER_DESC new_or_editext_hdr={0,0,0,0,NULL,(int)"Изменить",LGP_NULL};

INPUTDIA_DESC new_or_editext_desc =
{
  1,
  new_or_editext_onkey,
  new_or_editext_ghook,
  (void *)new_or_editext_locret,
  0,
  &menu_skt,
  {0,0,0,0},
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



void CreateEditOrNewExt(void *menugui, int index)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  ES *cur_es;
  char *s;
  int n;
  int c;
  int ect_type;
  
  if (index!=-1) cur_es=es+index;
  else cur_es=NULL;
  
  eq=AllocEQueue(ma,mfree_adr());    // Extension
  WSHDR *ews=AllocWS(128);
  wsprintf(ews,"%t","Extension:");  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);    //1
  
  CutWSTR(ews,0);
  ect_type=ECT_NORMAL_TEXT;
  if (cur_es)
  {
    if ((n=cur_es->ext)!=-1)
    {
      s=lines[n];
      s++;
      while((c=*s++)!=']')
      {
        if (!c) break;
        wsAppendChar(ews,char8to16(c));
      }
    }
    else
    {
      wsprintf(ews,"%t","Universal extension");
      ect_type=ECT_HEADER;
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ect_type,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   //2
  
  wsprintf(ews,"%t","RUN:");      // RUN
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //3
  
  CutWSTR(ews,0);
  if (cur_es)
  {
    if ((n=cur_es->elf)!=-1)
    {
      s=lines[n];
      s+=4;
      while((c=*s++))
      {
        wsAppendChar(ews,char8to16(c));
      }
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   //4
  
  wsprintf(ews,"%t","SMALL:");      // SMALL
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //5
  
  CutWSTR(ews,0);
  if (cur_es)
  {
    if ((n=cur_es->small_png)!=-1)
    {
      s=lines[n];
      s+=6;
      while((c=*s++))
      {
        wsAppendChar(ews,char8to16(c));
      }
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   //6
   
  wsprintf(ews,"%t","BIG:");      // BIG
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //7
  
  CutWSTR(ews,0);
  if (cur_es)
  {
    if ((n=cur_es->large_png)!=-1)
    {
      s=lines[n];
      s+=4;
      while((c=*s++))
      {
        wsAppendChar(ews,char8to16(c));
      }
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);    //8
  
  wsprintf(ews,"%t","ALTRUN:");      // ALTRUN
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);     //9
  
  CutWSTR(ews,0);
  if (cur_es)
  {
    if ((n=cur_es->altelf)!=-1)
    {
      s=lines[n];
      s+=7;
      while((c=*s++))
      {
        wsAppendChar(ews,char8to16(c));
      }
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);    //10
  
  FreeWS(ews);
  patch_header(&new_or_editext_hdr);
  patch_input(&new_or_editext_desc);
  CreateInputTextDialog(&new_or_editext_desc,&new_or_editext_hdr,eq,1,cur_es);  
}

int main_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  switch(msg->keys)
  {
  case 0x18:
    CreateEditOrNewExt(data, -1);
    return (-1);
    
  case 0x3D:
    CreateEditOrNewExt(data, i);
    return (-1);
  }
  return(0);
}

void main_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

void main_menu_iconhndl(void *data, int curitem, void *unk)
{
  int index;
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  {
    ws=AllocMenuWS(data,20);
    if ((index=es[curitem].ext)==-1)
      wsprintf(ws,_percent_t,"UNI_EXT");
    else
      wsprintf(ws,_percent_t,lines[index]);
  }
  SetMenuItemText(data,item,ws,curitem);
}

HEADER_DESC main_menuhdr={0,0,0,0,NULL,(int)"Extensions.cfg",LGP_NULL};

MENU_DESC main_menustruct=
{
  8,main_menu_onkey,main_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x10,
  main_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void maincsm_oncreate(CSM_RAM *data)
{
  int result;
  MAIN_CSM *csm=(MAIN_CSM*)data;
  
  if ((result=ParseExtCfg("4:\\ZBin\\etc\\extension.cfg"))<0)
    result=ParseExtCfg("0:\\ZBin\\etc\\extension.cfg");
  if (result>=0)
  {
    ParseLines();
    patch_header(&main_menuhdr);
    csm->gui_id=main_gui_id=CreateMenu(0,0,&main_menustruct,&main_menuhdr,0,ES_num,0,0);
  }
  else
  {
    CloseCSM(csm->csm.id);
  }
}

void maincsm_onclose(CSM_RAM *csm)
{
  mfree(es);
  for (int i=0; i!=lines_n; i++)  mfree(lines[i]);
  mfree(lines);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
  }
  return(1);
}

static unsigned short maincsm_name_body[140];
static const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ExtMan");
}

int main(const char *exename, const char *filename)
{
  MAIN_CSM main_csm;
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
}
