#include "..\inc\swilib.h"
#include "language.h"
#include "main.h"
#include "swilibPlus.h"

int tc = A_Truncate;

void Log(char *txt)
{
  unsigned int ul;
  int f=fopen("4:\\NoteMan\\log",A_ReadWrite+A_Create+tc+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
    fwrite(f," \n",2,&ul);
    fclose(f,&ul);
  }
  tc = A_Append;
}

CSM_DESC icsmd;
int id_ed;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
const int minus11=-11;

//-----------------------------------------//

const char per_t[]="%t";
const char per_s[]="%s";
const char empty_str[]="";

//-----------------------------------------//

int TabIcons[13];
char hdr_txt[64];
int readonly=0;
int draw_id;
int total_char=0;
char dir[128];//="0:\\mark";
char ndir[128];

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

//------------------------------------------//

unsigned int char16to8(unsigned int c);
void win1251_2ws(WSHDR *ws, const char *s);
void ascii2ws(WSHDR *ws, const char *s);
void koi2ws(WSHDR *ws, const char *s);

unsigned short maincsm_name_body[140];

EDITCONTROL ec;

volatile int prev_itemcount;
volatile MNU *mnutop;
volatile MNU_dir *mnu_dir;
char tabs_num=0;
GBSTMR mytmr;
int my_csm_id=0;
unsigned int err;


//------------------------------------------//

void mess(char *s)
{
  ShowMSG(1,(int)s);
}

void messd(unsigned long i)
{
  char *s=malloc(64);
  sprintf(s,"%d",i);
  ShowMSG(1,(int)s);
  mfree(s);
}

int get_file_size(char* fname)
{
  unsigned int err;
  FSTATS fs;
  if ((GetFileStats(fname,&fs,&err))==-1) return 0;
  return (fs.size);
}


//------------------------------------------//


int strcmp_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}


//------------------------------------------//

void xmfree(char *fr)
{
  if(fr) mfree(fr);
}

void FreeFold(void)
{
  LockSched();
  MNU_dir *md=(MNU_dir *)mnu_dir;
  mnu_dir=0;
  UnlockSched();
  while(md)
  {
    MNU_dir *md_prev;
    md_prev=md;
    md=md->next;      
    xmfree(md_prev->name);
    mfree(md_prev);
  }
  tabs_num=0;
}

void AddFold(char *filename)
{
  MNU_dir *pr;
  MNU_dir *fl;
  MNU_dir *fn=malloc(sizeof(MNU_dir));  
  fn->name=malloc(strlen(filename)+1);
  strcpy(fn->name,filename);  
  fn->item=tabs_num++;
  fn->next=0;
  fl=(MNU_dir *)mnu_dir;
  if(fl)
  {
    pr=(MNU_dir *)&mnu_dir;
    pr=fl;
    fl=fl->next;    
    fn->next=fl;
    pr->next=fn;
  }
  else
    mnu_dir=fn;    
}

MNU_dir *FindMNU_dirtByNS(int *i)
{
  MNU_dir *fl=(MNU_dir*)&mnu_dir;
  int f=0;
  while(fl)
   {
     //if(!(*i)) return(fl);
     //(*i)--;   
     if((*i)==f++) return(fl);     
     fl=fl->next;
   }
  return(fl);
}

MNU_dir *FindMNU_dirtByN(int n)
{
  MNU_dir *fl;
  fl=FindMNU_dirtByNS(&n); if (fl) return(fl);
  return fl;
}

char * GetFoldName(int is)
{ 
  int i=is+1;
  MNU_dir *fl=FindMNU_dirtByN(i);  
  if(strlen(fl->name))return fl->name;  
  return "Note0";
}

int GetFListN2()
{
  int i=0;
  MNU *fl=(MNU*)&mnutop;
  while((fl=fl->next)) i++;
  return (i);
}

void FreeMrk(void)
{
  LockSched();
  MNU *fl=(MNU *)mnutop;
  mnutop=0;
  UnlockSched();
  while(fl)
  {
    MNU *fl_prev;
    fl_prev=fl;
    fl=fl->next;
    xmfree(fl_prev->filename);
    xmfree(fl_prev->name);   
    xmfree(fl_prev->text);
    mfree(fl_prev);
  }
}

int num=0;

MNU *Add(char *filename,const char *text,int is_first)
{
  MNU *pr;
  MNU *fl;
  MNU *fn=malloc(sizeof(MNU)); 
  fn->filename=malloc(strlen(filename)+1);
  strcpy(fn->filename,filename);    
  
  fn->text=malloc(strlen(text)+1);
  strcpy(fn->text,text);
 
  fn->name=malloc(32);    
  strncpy(fn->name,fn->text,32);
 
  
  fn->is_first=is_first; 
  fn->FNAME=strtoul(filename,0,16);  
  fn->item=(!is_first)?num++:-1;
  prev_itemcount++;
  
  fn->next=0;
  fl=(MNU *)mnutop;
  if(fl)
  {
    pr=(MNU *)&mnutop;
    pr=fl;
    fl=fl->next;    
    fn->next=fl;
    pr->next=fn;
  }
  else
    mnutop=fn;  
return fn;
}

void ws2str(WSHDR *ws,char *s)
{
  int i;
  for(i=0;i<ws->wsbody[0];i++) *(s+i)=char16to8(ws->wsbody[i+1]);
  *(s+i)=0;
}

static const char *LoadTEXT(char *path)
{
  unsigned int err; 
  int f; 
  char *buf;
  int sz=get_file_size(path);
  if((f = fopen(path,A_ReadOnly+A_BIN,P_READ,&err ))!=-1)
  {
    buf=malloc(sz); 
    buf[fread(f,buf,sz,&err)]=0;        
  }
  fclose(f,&err); 
 return buf;
}

unsigned int *errr;
int current_tab=0;
char *curdir[4]={"Note0","Note1","Note2","Note3"};

void MarkFoider()
{
  FreeFold();      
  DIR_ENTRY de;
  unsigned int err;
  char *path=malloc(256);
  sprintf(path,per_s,dir); 
  char *ptr=path+strlen(path)+1;
  sprintf(path,"%s*",dir);
  if(FindFirstFile(&de,path,&err))
  {
    do{
      if (de.file_attr&FA_DIRECTORY)
      {           		
        strcpy(ptr,de.file_name);
        AddFold(de.file_name);        
      }  
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  mfree(path);
}

void LoadMark()
{
  FreeMrk();  
  num=0;
  prev_itemcount=0; 
  Add((char*)empty_str,"Создать новую запись",1);
  DIR_ENTRY de;
  unsigned int err;
  char *path=malloc(256);
  char *fname=GetFoldName(current_tab);
   sprintf(ndir,"%s%s",dir,fname);//curdir[current_tab]
  //if(!(current_tab(ndir,errr)))
  {
  //  mkdir(ndir,errr);
  //  SetFileAttrib(ndir,FA_HIDDEN,errr);
  }
  sprintf(path,per_s,ndir); 
  char *ptr=path+strlen(path)+1;
  strcat(path,"\\*.mrk");
  if(FindFirstFile(&de,path,&err))
  {
    do{
      strcpy(ptr,de.file_name);
      Add(de.file_name,LoadTEXT(path),0);     
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  mfree(path);
}

//------------------- Т9 ------------------//

//Ключи для поиска по T9
static const char table_T9Key[256]=
"11111111111111111111111111111111"
"10001**0***0000*012345678900***0"
"0222333444555666777788899991*110"
"122233344455566677778889999111*1"
"11111111111111111111111111111111"
"11111111311111111111111131111111"
"22223333444455566677778888899999"
"22223333444455566677778888899999";


char T9Key[32];
char _sk_r[16];
char main_hdr_txt[64];
char t9find=0;
MNU *FindNOTEyNS(int *i,int si)
{
  MNU *t=(MNU *)mnutop; 
  char *s,*d; 
  int c;
  while(t)
  {
   s=T9Key;
   d=t->name;
   while(c=*s++)
   {
    if(c!=table_T9Key[*d++]) goto L_NOT9;
   }
   if(t->is_first==si)
    {
      if(!(*i)) return(t);
      (*i)--;
    }
 L_NOT9:
    t=t->next;
  }
  return(t);
}

MNU *FindFLISTtByN(int n)
{
  MNU *fl;
  if(!t9find)
    fl=FindNOTEyNS(&n,1); if ((!n)&&(fl)) return(fl);
  fl=FindNOTEyNS(&n,0); if ((!n)&&(fl)) return(fl);
  return fl;
}

void ClearT9Key(void)
{
  zeromem(T9Key,sizeof(T9Key));
}

int CountNOTE(void)
{
  int l=-1;
  if(!t9find)
    FindNOTEyNS(&l,1);
  FindNOTEyNS(&l,0);
  l=-1-l;
  return l;
}


//----------------------------------//


void utf82win(char*d,const char *s)
 {
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 0xD0)
    {  
      *d = (lb != 0x81)?lb + 48:'Ё'; d++;	   
    }
    else
      if (ub == 0xD1)
      {
        *d =(lb != 0x91)? lb + 112:'И'; d++;
      }
      else	  		
      {
        *d = ub;
        d++;
        s--;
      }
  }
  *d = 0;
}


void fn_prepare( char* dst, char* src)
{
  int len = strlen(dst);
  utf82win(dst, src); 
  len = strlen(dst);
  int jj = 0;
  for(int ii = 0; ii < len; ii++)
  {
    int ch = dst[ii];
    if (ch == 0x1F) continue;
    dst[jj++] = ch;
  }
 dst[jj] = 0;
}

void UpdateHeader(void)
{
  if ((t9find=strlen(T9Key)))
  {
    strcpy(main_hdr_txt,"Ввод T9:");
    strcat(main_hdr_txt,T9Key);
    strcpy(_sk_r,"<C");
  }
  else
  {      
    strcpy(main_hdr_txt,GetFoldName(current_tab)/*"Заметки"*/);
    fn_prepare( main_hdr_txt, main_hdr_txt);
    strcpy(_sk_r,"Выход");
  }
}

void AddT9Key(int chr)
{
  int l=strlen(T9Key);
  if(l<(sizeof(T9Key)-1))
  {
    T9Key[l]=chr;
  }
}

void BackSpaceT9(void)
{
  int l=strlen(T9Key);
  if(l)T9Key[--l]=0;  
}

static void RecountMenuNOTE(void *data)
{  
  UpdateHeader();

  int i=CountNOTE(); 
  if(i!=prev_itemcount)
  {
    prev_itemcount=i;
    current_tab=GetCursorTab(data);
    
    void *m_gui=GetGuiByTab(data, current_tab); 
    if (m_gui)
    {         
      int cur=GetCurMenuItem(m_gui);    
      if(cur>=prev_itemcount) SetCursorToMenuItem(m_gui, 0);
      Menu_SetItemCountDyn(m_gui, prev_itemcount);
    }      
  }
  if (IsGuiOnTop(MAINGUI_ID)) RefreshGUI();
}

//------------------------Создаем список--------------------------//

void bm_menu_iconhnd(void *data, int curitem, void *unk);
int MLHico;   //иконка заголовка
HEADER_DESC bm_menuhdr={0,0,0,0,&MLHico,(int)main_hdr_txt,LGP_NULL};
const int menusoftkeys[]={0,1,2};

const SOFTKEY_DESC menu_sk2[]=
{
  {0x0004,0x0000,(int)"Удалить"},
  {0x0001,0x0000,(int)_sk_r},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt2=
{
  menu_sk2,0
};

int item=0;

void bm_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
};

MNU *FindByN(int n)
{
  MNU *fl;
  int i=0;
  int j=0;
  int k=GetFListN2();
  fl=(MNU *)mnutop;
  j=k-n-1;
  for(i=0; i<j && (fl) ;i++)fl=fl->next; 
  return fl;
}

void DelItem(MNU *fl)
{  
  if(!fl->is_first)
  {
    char *s=malloc(256);
    unsigned int err;
    sprintf(s,"%s\\%s",ndir,fl->filename);
    fl->is_first=2;
    unlink(s,&err);
    //mess("File deleted");
    mfree(s);  
  }
}

MNU *changefile;
int bm_menu_onkey2(void *data, GUI_MSG *msg)
{
 int i=GetCurMenuItem(data); 
 int k=msg->gbsmsg->submess;
 MNU *fl=FindFLISTtByN(i);
 if(msg->keys==0x3D)
 {
   if(fl)
   {
    if(strlen(T9Key))
    {
      ClearT9Key();
      RecountMenuNOTE(data);
    }
    readonly=0;
    DrawText(NULL,fl);
   }
   return (-1);
 } 

 if (msg->gbsmsg->msg==KEY_DOWN)
 {
   if(k==LEFT_BUTTON||k==RIGHT_BUTTON)
   {
     if(k==RIGHT_BUTTON)   
     {if((++current_tab)>=tabs_num)current_tab=0;}  
     else
     {if((--current_tab)<=-1)current_tab=tabs_num-1;}
     LoadMark();
     RecountMenuNOTE(data);
   }
   if(k=='*') RecountMenuNOTE(data);; 
   if(k=='#'||k==LEFT_SOFT)         
   {   
     DelItem(fl);
     RecountMenuNOTE(data);
     return(-1);
   } 

    int key=msg->gbsmsg->submess;
    if((key>='0')&&(key<='9'))
    {
      AddT9Key(key);
      RecountMenuNOTE(data);
      return(-1);
    }
    
   if(key==GREEN_BUTTON)
    {
     RecountMenuNOTE(data);
     return(-1);
    }
  }
  
  if (msg->keys==1 || msg->keys==RED_BUTTON)
  {
    if (strlen(T9Key))
    {
      BackSpaceT9();
      RecountMenuNOTE(data);
      return(-1);
    }
  }
return 0;
}


void menu_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMenuItem(data);
  MNU *fl=FindFLISTtByN(curitem);
  WSHDR *ws;
  if(fl)
  {
  ws=AllocMenuWS(data,strlen(fl->name)+1);
  ascii2ws(ws,fl->name);
  }
  else
  {
    ws=AllocMenuWS(data,32);
    ascii2ws(ws,"ошибка");
  }
  SetMenuItemText(data,item,ws,curitem);
}


const MENU_DESC menu=
{
  8,bm_menu_onkey2,bm_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt2,
  0x11,
  menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int create()
{  
  prev_itemcount=CountNOTE();    
  UpdateHeader();
  patch_header(&bm_menuhdr);  
  return(id_ed=CreateMenu(0,0,&menu,&bm_menuhdr,0,prev_itemcount,0,0));
}

//==============================================================================
//Табы//////////////////////////////////////////////////////////////////////////
//==============================================================================

int TabGuiOnKey(void *gui, GUI_MSG *msg)
{ 
  return 0;
}

void TabGuiGHook(void *gui, int cmd)
{  
 
  if (cmd==TI_CMD_CREATE)
    {
   
    }
  
  else if (cmd==TI_CMD_DESTROY)
    {
    }
 
 else if(cmd==0x18)
   {  
     current_tab=GetCursorTab(gui);
     void *m_gui=GetGuiByTab(gui, current_tab);     
     if (m_gui)
     {         
       int cur=GetCurMenuItem(m_gui);       
       if(cur>=prev_itemcount) SetCursorToMenuItem(m_gui, 0);
       Menu_SetItemCountDyn(m_gui, prev_itemcount);
     }    
     void **methods=((GUI *)gui)->methods;
     ((void (*)(void *))methods[0])(gui);     
    
   }
}

const TABGUI_DESC TabGui=
{
  8,
  TabGuiOnKey,
  TabGuiGHook,
  NULL,
  NULL,
  NULL
};

//==============================================================

//--------------------------------Редактор--------------------------------//

HEADER_DESC disk_prop_hdr={0,0,0,0,0,(int)hdr_txt,LGP_NULL};

char *cmp;

MNU *FindFileByName(char *name)
{
  MNU *fl;
  int km=GetFListN2();
  for(int k=0;k<km;k++)//Ищем имя файла
  {
    fl=FindFLISTtByN(k);
    if(strcmp(cmp,fl->filename)==0) break;
   }
  return fl;
}


int edit_onkey(GUI *data, GUI_MSG *msg)
{
  int k=msg->gbsmsg->submess;
  MNU *fl=FindFileByName(cmp);//Ищем запись по имени файла;
  MNU *nw;
  unsigned long num=0;
  unsigned int err;
  char *ss;
  WSHDR *ws;
  int last_name=0; 
  if(msg->keys==0xFFF && readonly==1)//Если нажали "Сохранить" и у нас режим редактирования
  {
    EDITCONTROL ec;    
    ExtractEditControl(data,1,&ec);	
    ws=ec.pWS;
    void *data=FindGUIbyId(id_ed,NULL);
    if(fl->is_first)//Если нажали "Создать заметку"
    {
      int k=GetFListN2();
      for(int t=0;t<k;t++)
      {
        nw=FindFLISTtByN(t);
        num=nw->FNAME;
        if(num>last_name)
          last_name=num;
      }
      num=last_name+1;      
      sprintf(nw->filename,"%02X.mrk",num);
      nw->text=malloc(ws->wsbody[0]);
      ws2str(ws,nw->text);
      SaveMark(nw->filename,nw->text);
      
      readonly=0;
      Add(nw->filename,nw->text,0);
      RecountMenuNOTE(data);
      GeneralFuncF1(1);
    }
    else
    {
     ss=malloc(256);
     sprintf(ss,"%s\\%s",ndir,fl->filename);
     unlink(ss,&err);
     fl->text=malloc(ws->wsbody[0]);
     ws2str(ws,fl->text); 
     SaveMark(fl->filename,fl->text);
     strncpy(fl->name,fl->text,32);
     readonly=0;
     RecountMenuNOTE(data);
     GeneralFuncF1(1);
     DrawText(NULL,fl);
    }
  }
 
 if(msg->gbsmsg->msg==KEY_DOWN)
 {
   if((k==UP_BUTTON && readonly==0) && item!=0)
    {
      GeneralFunc_flag1(draw_id,1);
      int y=fl->FNAME;
      int num=0;
      int km=GetFListN2();     
      if(y>1) y--;
      else 
      {        
       for(int t=0;t<km;t++)
        {          
          nw=FindFLISTtByN(t);
          num=nw->FNAME;
          if(num>y)y=num;
        }
      }
      for(int k=0;k<km;k++)
      {       
       fl=FindFLISTtByN(k);       
       if(y==fl->FNAME) break;
      }
      DrawText(NULL,fl); 
    }
   
   if((k==DOWN_BUTTON && readonly==0) && item!=0)
    {
      GeneralFunc_flag1(draw_id,1);
      int y=fl->FNAME;
      int num;
      int last=0;      
      int km=GetFListN2();
      for(int t=0;t<km;t++)
        {          
          nw=FindFLISTtByN(t);
          num=nw->FNAME;
          if(num>last)last=num;
        }
      nw=FindFLISTtByN(1);
      if(y<last)
        y++;
      else 
        y=nw->FNAME;
      
      for(int k=0;k<km;k++)
      {       
       fl=FindFLISTtByN(k);       
       if(y==fl->FNAME) break;
      }
      DrawText(NULL,fl); 
    }
   
   if(k==GREEN_BUTTON)
   {
     GeneralFunc_flag1(draw_id,1);  
     readonly=!readonly; 
     DrawText(NULL,fl);
   }
 }
return(0);
}

const SOFTKEY_DESC sk[];
SOFTKEYSTAB skt={ sk,0 };

void edit_ghook(GUI *gui, int cmd)
{ 
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Сохранить"};
  
  if(cmd==0xA)
  {
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }  
  if(cmd==0x03)
  {
    void *data=FindGUIbyId(id_ed,NULL);
    RecountMenuNOTE(data);
  }  
  if(cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);
  }
};


INPUTDIA_DESC edit_desc=
{
  1,
  edit_onkey,
  edit_ghook,
  0,
  0,
  &skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};
 
//------------------------------------//

static void SaveMark(char *name,char *text)//Сохраняем в каталог
{
  unsigned int err;
  int f;
  char *p=malloc(strlen(ndir)+64);
  sprintf(p,"%s\\%s",ndir,name);
  SetFileAttrib(p,0,errr);
  if((f=fopen(p,A_Create+A_ReadWrite+A_BIN+A_Truncate,P_WRITE,&err))!=-1)
   {
    fwrite(f,text,strlen(text),&err);
    //ShowMSG(1,(int)LG_FILESAVE);
   }
 // else 
 //   ShowMSG(1,(int)LG_NOTSAVE);
  //SetFileAttrib(p,FA_READONLY,errr);
  fclose(f,&err);
}

//------------------------------------//

int DrawText(int _null,MNU *fn)//собственно эдитконтроль
{
  ClearT9Key();
  EDITC_OPTIONS ec_options;
  void *ma=malloc_adr();
  void *eq=AllocEQueue(ma, mfree_adr());
  WSHDR *ws=AllocWS(strlen(fn->text));
  MNU *fl;
  int km=GetFListN2();
  for(item=0;item<km;item++)//Ищем имя файла
  {
    fl=FindFLISTtByN(item);
    if(fn->FNAME == fl->FNAME) break;
  }
  cmp=malloc(strlen(fl->filename));
  strcpy(cmp,fl->filename);
  
  if(fl->is_first==1) sprintf(hdr_txt,"%s","Новая запись");
  else
    if(!readonly) 
      sprintf(hdr_txt,"%d. %s",item,fl->name);//Если открываем для просмотра в режим реадонли,то выводим в заголовке дату
    else 
      sprintf(hdr_txt,"%d. %s", item,"Редактирование");//Иначе просто слово Заметки:)

  if(fl->is_first!=1) 
    ascii2ws(ws,fl->text);//Если открываем запись,то выводим текст
  else 
    readonly=1;//Если создаем,то сразу открываем редактирование

  ConstructEditControl(&ec,readonly?ECT_NORMAL_TEXT|ECF_DEFAULT_BIG_LETTER:ECT_READ_ONLY,0x40,ws,16384);//16 кило думаю хватит :)
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,4);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  patch_header(&disk_prop_hdr);
  patch_input(&edit_desc);      

  FreeWS(ws);
  return draw_id=CreateInputTextDialog(&edit_desc,&disk_prop_hdr,eq,1,0);
}

//-------------------------------------------------------------------------------------//

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  /**/
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *main_gui;

  patch_header(&bm_menuhdr);
  UpdateHeader();
  prev_itemcount=CountNOTE();
  
  if (tabs_num==1) 
    {
      main_gui=GetMenuGUI(ma, mf);
      SetGUIDefinition(main_gui, &menu);
      SetHeaderToMenu(main_gui, &bm_menuhdr, ma);
      csm->gui_id=CreateGUI(main_gui);
      create();
    }
  else 
  {
    main_gui=GetTabGUI(ma, mf);
    SetGUIDefinition(main_gui, &TabGui);    
    for (int i=0; i<tabs_num; i++)
    {
      void *m_gui=GetMenuGUI(ma, mf);
      SetMenuToGUI(m_gui, &menu);
      SetHeaderToMenu(m_gui, &bm_menuhdr, ma);
      SetGUIToTabGUI(main_gui,i,&TabIcons[i],m_gui); 
    }
    csm->gui_id=CreateGUI(main_gui);
    UpdateTab1stItem(main_gui, 0);
  }
  MAINGUI_ID=csm->gui_id;
  /**/
//  csm->gui_id=create();
}

void Killer(void)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeMrk();
  FreeFold();
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    csm->csm.state=-3;         
  return(1);
}

unsigned short maincsm_name_body[140];

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


WSHDR *ws_name;
void UpdateCSMname(void)
{ 
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"NoteMan");
}

int maincsm_id;
typedef struct
{
  char Icon[128];
}TItem;

TItem It[10];

void Load(char *sub)
{
  unsigned int err;
  int fill;
  char *mem;
  int size;
  int i;
  char *str;
  int j;

   fill = fopen( sub , A_ReadOnly + A_BIN, P_READ, & err );
   if ( fill==-1 )
   {
   // ShowMSG(1,(int)"Can't open iconfile :(");
    fclose( fill, & err );
    return;
   }
  mem=malloc(get_file_size(sub));
  str=malloc(256);  
  int count=2;
  if ((mem!=0)&&(str!=0))
   {
    size=fread(fill,mem,get_file_size(sub),&err);
    i=0;
    while (i<size)
    {
      j=0;
      while (((*(mem+i)!='\r')&&((*(mem+i)!='\n')))&&(i<size)){*(str+j)=*(mem+i); j++;i++;}
      *(str+j)=0;
      int lstr=strlen(str);
      if ((*str!=';')&&(lstr))
      {
        strcpy(It[count].Icon,str);
        //if(str[2]!=':')  sprintf(sf,"%s%s",dir,str);  else  
        //char *sf=(char*)malloc(lstr);
       // sf 
        int TR=(int)It[count].Icon;
        if(count>2)
        {          
          TabIcons[count]=TR;
        }
        else        
          MLHico=TR; 
       // mfree(sf);       
       count++;
      }
      i++;
    }
  }
  mfree(mem);
  
  fclose(fill,&err);
}

int main(char *exename, char *fname)
{ 
  zeromem(TabIcons,sizeof(TabIcons));
  strcpy(dir,exename);
  for(int i=strlen(dir);dir[i]!='\\';i--) dir[i]=0;
  
  char *sub=(char*)malloc(128);   
  sprintf(sub,"%sicon.ini",dir);
  Load(sub);  
  mfree(sub);
  
  
  MarkFoider();  
  LoadMark();  
  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
 return 0;
}

//-----------------------Edit chat---------------------------//


typedef struct
{
  unsigned short u;
  char dos;
  char win;
  char koi8;
} TUNICODE2CHAR;

const TUNICODE2CHAR unicode2char[]=
{
  // CAPITAL Cyrillic letters (base)
  0x410,0x80,0xC0,0xE1, // А
  0x411,0x81,0xC1,0xE2, // Б
  0x412,0x82,0xC2,0xF7, // В
  0x413,0x83,0xC3,0xE7, // Г
  0x414,0x84,0xC4,0xE4, // Д
  0x415,0x85,0xC5,0xE5, // Е
  0x416,0x86,0xC6,0xF6, // Ж
  0x417,0x87,0xC7,0xFA, // З
  0x418,0x88,0xC8,0xE9, // И
  0x419,0x89,0xC9,0xEA, // Й
  0x41A,0x8A,0xCA,0xEB, // К
  0x41B,0x8B,0xCB,0xEC, // Л
  0x41C,0x8C,0xCC,0xED, // М
  0x41D,0x8D,0xCD,0xEE, // Н
  0x41E,0x8E,0xCE,0xEF, // О
  0x41F,0x8F,0xCF,0xF0, // П
  0x420,0x90,0xD0,0xF2, // Р
  0x421,0x91,0xD1,0xF3, // С
  0x422,0x92,0xD2,0xF4, // Т
  0x423,0x93,0xD3,0xF5, // У
  0x424,0x94,0xD4,0xE6, // Ф
  0x425,0x95,0xD5,0xE8, // Х
  0x426,0x96,0xD6,0xE3, // Ц
  0x427,0x97,0xD7,0xFE, // Ч
  0x428,0x98,0xD8,0xFB, // Ш
  0x429,0x99,0xD9,0xFD, // Щ
  0x42A,0x9A,0xDA,0xFF, // Ъ
  0x42B,0x9B,0xDB,0xF9, // Ы
  0x42C,0x9C,0xDC,0xF8, // Ь
  0x42D,0x9D,0xDD,0xFC, // Э
  0x42E,0x9E,0xDE,0xE0, // Ю
  0x42F,0x9F,0xDF,0xF1, // Я
  // CAPITAL Cyrillic letters (additional)
  0x402,'_',0x80,'_', // _ .*.*
  0x403,'_',0x81,'_', // _ .*.*
  0x409,'_',0x8A,'_', // _ .*.*
  0x40A,'_',0x8C,'_', // _ .*.*
  0x40C,'_',0x8D,'_', // _ .*.*
  0x40B,'_',0x8E,'_', // _ .*.*
  0x40F,'_',0x8F,'_', // _ .*.*
  0x40E,0xF6,0xA1,'_', // Ў ...*
  0x408,0x4A,0xA3,0x4A, // _ .*.*
  0x409,0x83,0xA5,0xBD, // _ .*..
  0x401,0xF0,0xA8,0xB3, // Ё
  0x404,0xF2,0xAA,0xB4, // Є
  0x407,0xF4,0xAF,0xB7, // Ї
  0x406,0x49,0xB2,0xB6, // _ .*..
  0x405,0x53,0xBD,0x53, // _ .*.*
  // SMALL Cyrillic letters (base)
  0x430,0xA0,0xE0,0xC1, // а
  0x431,0xA1,0xE1,0xC2, // б
  0x432,0xA2,0xE2,0xD7, // в
  0x433,0xA3,0xE3,0xC7, // г
  0x434,0xA4,0xE4,0xC4, // д
  0x435,0xA5,0xE5,0xC5, // е
  0x436,0xA6,0xE6,0xD6, // ж
  0x437,0xA7,0xE7,0xDA, // з
  0x438,0xA8,0xE8,0xC9, // и
  0x439,0xA9,0xE9,0xCA, // й
  0x43A,0xAA,0xEA,0xCB, // к
  0x43B,0xAB,0xEB,0xCC, // л
  0x43C,0xAC,0xEC,0xCD, // м
  0x43D,0xAD,0xED,0xCE, // н
  0x43E,0xAE,0xEE,0xCF, // о
  0x43F,0xAF,0xEF,0xD0, // п
  0x440,0xE0,0xF0,0xD2, // р
  0x441,0xE1,0xF1,0xD3, // с
  0x442,0xE2,0xF2,0xD4, // т
  0x443,0xE3,0xF3,0xD5, // у
  0x444,0xE4,0xF4,0xC6, // ф
  0x445,0xE5,0xF5,0xC8, // х
  0x446,0xE6,0xF6,0xC3, // ц
  0x447,0xE7,0xF7,0xDE, // ч
  0x448,0xE8,0xF8,0xDB, // ш
  0x449,0xE9,0xF9,0xDD, // щ
  0x44A,0xEA,0xFA,0xDF, // ъ
  0x44B,0xEB,0xFB,0xD9, // ы
  0x44C,0xEC,0xFC,0xD8, // ь
  0x44D,0xED,0xFD,0xDC, // э
  0x44E,0xEE,0xFE,0xC0, // ю
  0x44F,0xEF,0xFF,0xD1, // я
  // SMALL Cyrillic letters (additional)
  0x452,'_',0x90,'_', // _ .*.*
  0x453,'_',0x83,'_', // _ .*.*
  0x459,'_',0x9A,'_', // _ .*.*
  0x45A,'_',0x9C,'_', // _ .*.*
  0x45C,'_',0x9D,'_', // _ .*.*
  0x45B,'_',0x9E,'_', // _ .*.*
  0x45F,'_',0x9F,'_', // _ .*.*
  0x45E,0xF7,0xA2,'_', // ў ...*
  0x458,0x6A,0xBC,0x6A, // _ .*.*
  0x491,0xA3,0xB4,0xAD, // _ .*..
  0x451,0xF1,0xB8,0xA3, // ё
  0x454,0xF3,0xBA,0xA4, // є
  0x457,0xF5,0xBF,0xA7, // ї
  0x456,0x69,0xB3,0xA6, // _ .*..
  0x455,0x73,0xBE,0x73, // _ .*.*
  0x0A0,'_',0xA0,0x20, // space .*..
  0x0A4,'_',0xA4,0xFD, // ¤   .*..
  0x0A6,'_',0xA6,'_', // ¦   .*.*
  0x0B0,0xF8,0xB0,0x9C, // °
  0x0B7,0xFA,0xB7,0x9E, // ·
  // 0x2022,,0x95,0x95, //    .*..
  // 0x2116,0xFC,0xB9,0x23, // №   ...*
  // 0x2219,,0xF9,0x9E, //    .*..
  // 0x221A,0xFB,,0x96, // v   ..*.
  // 0x25A0,0xFE,,0x94, // ¦
  0x0000,0,0,0
};

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};
const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};
const char koi8translation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0xF1,0xF3,0x5F,'i' ,0xF5,0xF0,0x63,0xF2,0x3C,0xBF,0xA3,0x52,0xF4,
  0xF8,0x2B,0x5F,0xF0,0xF2,0xE7,'I' ,0xF4,0xF1,0xFC,0xF3,0x3E,0x5F,0x83,0x5F,0xF5,
  
  0xEE,0xA0,0xA1,0xE6,0xA4,0xA5,0xE4,0xA3,0xE5,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,
  0xAF,0xEF,0xE0,0xE1,0xE2,0xE3,0xA6,0xA2,0xEC,0xEB,0xA7,0xE8,0xED,0xE9,0xE7,0xEA,
  0x9E,0x80,0x81,0x96,0x84,0x85,0x94,0x83,0x95,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,
  0x8F,0x9F,0x90,0x91,0x92,0x93,0x86,0x82,0x9C,0x9B,0x87,0x98,0x9D,0x99,0x97,0x9A
};

#pragma inline
unsigned int char16to8(unsigned int c)
{
  const TUNICODE2CHAR *p=unicode2char;
  unsigned int i;
  if (c<128) return(c);
  while((i=p->u))
  {
    if (c==i)
    {
      return(p->win);
    }
    p++;
  }
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}

unsigned int char8to16(int c, int type)
{
  if (c>=128)
  {
    switch(type)
    {
    case 1:
      //Win->Dos
      c=wintranslation[c-128];
      break;
    case 2:
      //Koi8->Dos
      c=koi8translation[c-128];
      break;
    }
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

/*
void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c,1));
  }
}*/
unsigned int win2unicode(int letter)
{
  if (letter<168) goto L_ENG;
  if (letter==168) goto L_BIG_YO;
  letter-=168;
  if (letter<24) goto L_UKR;
  if (letter>87) goto L_ENG;
//L_RUS:
  letter-=8;
  goto L_ADD_400;
L_UKR:
  switch(letter)
  {
  case 0x02:
    letter=0x04;
    break;
  case 10:
    letter=6;
    break;
  case 11:
    letter=0x56;
    break;
  case 16:
    letter=0x51;
    break;
  case 18:
    letter=0x54;
    break;
  case 23:
    letter=0x57;
    break;
  default:
    goto L_ENG;
  }
  goto L_ADD_400;
L_BIG_YO:
  letter=0x01;
L_ADD_400:
  return (letter+0x400);
  
L_ENG: return (letter);
}


void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    total_char++;
    wsAppendChar(ws,win2unicode(c));
  }
}

void koi2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    total_char++;
    wsAppendChar(ws,char8to16(c,2));
  }
}

void win1251_2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    total_char++;
    wsAppendChar(ws,char16to8(c));
  }
}

/*
//------------------------- Translit -------------------------//

unsigned int translit(int c)
{//rus 192-255 en 65-90 97-123
 switch(c)
 {
  case 'А': c='A'; break;
  case 'Б': c='B'; break;
  case 'В': c='V'; break;
  case 'Г': c='G'; break;
  case 'Д': c='D'; break;
  case 'Е': c='E'; break;
  case 'Ё': c='E'; break;
  case 'Ж': c='J'; break;
  case 'З': c='Z'; break;
  case 'И': c='I'; break;
  case 'К': c='K'; break;
  case 'Л': c='L'; break;
  case 'М': c='M'; break;
  case 'Н': c='N'; break;
  case 'О': c='O'; break;
  case 'П': c='P'; break;
  case 'Р': c='R'; break;
  case 'С': c='S'; break;
  case 'Т': c='T'; break;
  case 'У': c='Y'; break; 
  case 'Ф': c='F'; break;
  case 'Х': c='H'; break;
  case 'Ц': c='C'; break;
  case 'Э': c='E'; break;
  case 'Ю': c='U'; break;
  
  case 'а': c='A'+32; break;
  case 'б': c='B'+32; break;
  case 'в': c='V'+32; break;
  case 'г': c='G'+32; break;
  case 'д': c='D'+32; break;
  case 'е': c='E'+32; break;
  case 'ё': c='E'+32; break;
  case 'ж': c='J'+32; break;
  case 'з': c='Z'+32; break;
  case 'и': c='I'+32; break;
  case 'к': c='K'+32; break;
  case 'л': c='L'+32; break;
  case 'м': c='M'+32; break;
  case 'н': c='N'+32; break;
  case 'о': c='O'+32; break;
  case 'п': c='P'+32; break;
  case 'р': c='R'+32; break;
  case 'с': c='S'+32; break;
  case 'т': c='T'+32; break;
  case 'у': c='Y'+32; break; 
  case 'ф': c='F'+32; break;
  case 'х': c='H'+32; break;
  case 'ц': c='C'+32; break;
  case 'э': c='e'; break;
  case 'ю': c='u'; break;
 default: return c;
 }
 return c;
}

void rus2en(WSHDR *en,char *rus)
{
 char c;
 char *s=malloc(strlen(rus));
 CutWSTR(en,0);
 while((c=*rus++))
 {
    wsAppendChar(en,translit(c));
 }
}
*/
