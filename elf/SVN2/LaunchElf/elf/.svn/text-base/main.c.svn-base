#include "..\..\inc\swilib.h"
#include <stdbool.h>
#include "lgp.h"
#include "elf.h"

//------------------------      ETC           --------------------------------//

int S_ICONS[3];

enum MY_ICONS {
  ICON_ELF,
  ICON_SHORTCUT,
  ICON_ADDNEW
};

typedef struct
{
  void *next;
  shortcut  a;
}MYLIST;

typedef struct
{
  void *next;
  char full_name[16];
  char short_name[16];
  char elf_path[128];
}MYLIST2;

typedef struct
{
  void *next;
  char shortcut_name[16];
}MYLIST3;

unsigned short maincsm_name_body[140];
extern void kill_data(void *p, void (*func_p)(void *));

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

const int minus11=-11;

#define MYMAGIC 0x7FFE

MYLIST* shortcuts=0;
MYLIST2* shortcut_names=0;
MYLIST3* fast_run_shortcuts=0;

WSHDR *ews;
int shcutpos=0;
int list_menu_id;
int prev_lmenu_itemcount;

//--------------------------       GUI         -------------------------------//
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

static HEADER_DESC menuhdr = {0, 0, 0, 0, NULL, (int)LGP_ELFNAME, LGP_NULL};
static const int menusoftkeys[] = {0,1,2};

static SOFTKEY_DESC menu_sk[]=
{
  {0x0018, 0x0000, (int)txt_null},
  {0x0001, 0x0000, (int)LGP_SAVE},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

static SOFTKEY_DESC menu_sk2[]=
{
  {0x0018, 0x0000, (int)txt_null},
  {0x0001, 0x0000, (int)LGP_CLOSE},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const SOFTKEYSTAB menu_skt2 =
{
  menu_sk2, 0
};

////////////////////////////////////////////////////////////////////////////////

void list_menu_ghook(void *data, int cmd);
int list_menu_onkey(void *data, GUI_MSG *msg);
void list_menu_iconhndl(void *data, int curitem, void *unk);

static const ML_MENU_DESC list_menu=
{
  8,list_menu_onkey,list_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11, //+0x400
  list_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1  //Добавночных строк
};
//-----------------------         LaunchElf             --------------------------//

MYLIST* FindShortcutByNum(int num){
  MYLIST* l=shortcuts;
  int i=1;
  if (l && num) while(l->next){
    l=l->next;
    if (i==num) return l;
    i++;
  }
  return l;
}
MYLIST2* FindShortcutNameByNum(int num){
  MYLIST2* l=shortcut_names;
  int i=1;
  if (l && num) while(l->next){
    l=l->next;
    if (i==num) return l;
    i++;
  }
  return l;
}
MYLIST3* FindFRShortcutByNum(int num){
  MYLIST3* l=fast_run_shortcuts;
  int i=1;
  if (l && num) while(l->next){
    l=l->next;
    if (i==num) return l;
    i++;
  }
  return l;
}
int FindShortcutNumByName(char* name)
{
  MYLIST* l=shortcuts;
  int i=0;
  if (l) while(l->next){
    if (strcmp(l->a.name,name)==0)
      return i;
    l=l->next;
    i++;
  }
  return -1;
}
MYLIST* FindShortcutByName(char* name)
{
  int a = FindShortcutNumByName(name);
  if (a!=-1)
    return FindShortcutByNum(a);
  else
    return 0;
}

int GetShortcutsCount(){
  MYLIST* l=shortcuts;
  if (!l)
    return 0;
  int i=1;
  while(l=l->next)
    i++;
  return i;
}
int GetShortcutNamesCount(){
  MYLIST2* l=shortcut_names;
  if (!l)
    return 0;
  int i=1;
  while(l=l->next)
    i++;
  return i;
}
int GetFRShortcutsCount(){
  MYLIST3* l=fast_run_shortcuts;
  if (!l)
    return 0;
  int i=1;
  while(l=l->next)
    i++;
  return i;
}

void FreeShortcuts(){
    MYLIST* l = shortcuts;
    while(l){
      MYLIST* b = l->next;
      mfree(l);
      l=b;
    }
}
void FreeShortcutNames(){
    MYLIST2* l = shortcut_names;
    while(l){
      MYLIST2* b = l->next;
      mfree(l);
      l=b;
    }
}
void FreeFRShortcuts(){
    MYLIST3* l = fast_run_shortcuts;
    while(l){
      MYLIST3* b = l->next;
      mfree(l);
      l=b;
    }
}

int GetElfCount()
{
  int i = 0;
  MYLIST *l=shortcuts;
  while (l){
    if ((l->a.lgp_full_name == MYMAGIC) || (l->a.lgp_short_name == MYMAGIC))
      i++;
    l=l->next;
  }
  return i;
}

int LoadSettings(){
  int isok = 0;
  volatile int hFile=0;
  unsigned int io_error = 0;
  int len=0;
  FSTATS fstat;
  char* data=0;
  if (GetFileStats(shortcuts_filename,&fstat,&io_error)!=-1)
  {
    if ((hFile=fopen(shortcuts_filename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
    {
      len=fstat.size;
      if (len>sizeof(shortcut)+1){
        data=malloc(len+1);
        fread(hFile,data,len,&io_error);
        
        FreeShortcuts();
        int i=0;
        shortcut* table = (shortcut*)data;
        MYLIST *b;
        while ((i<200)&&(strcmp(table[i-1].name,shortcuts_last_name)!=0))
        {
          MYLIST *l = malloc(sizeof(MYLIST));
          l->next=0;
          memcpy(&(l->a),&(table[i]),sizeof(shortcut));
          if (i)
            b->next=l;
          else
            shortcuts=l;
          b=l;
          i++;
        }
        isok++;
        mfree(data);
      }
      fclose(hFile,&io_error);
    }
  }
  if (GetFileStats(shortcut_names_filename,&fstat,&io_error)!=-1)
  {
    if ((hFile=fopen(shortcut_names_filename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
    {
      len=fstat.size;
      if (len>sizeof(MYLIST2)){
        data=malloc(len+1);
        fread(hFile,data,len,&io_error);
        
        FreeShortcutNames();
        int i=0;
        MYLIST2 *b;
        int a = GetElfCount();
        while ((i<200)&&(i<a))
        {
          MYLIST2 *l = malloc(sizeof(MYLIST2));
          l->next=0;
          memcpy(l->full_name,data+i*160,16);
          memcpy(l->short_name,data+i*160+16,16);
          memcpy(l->elf_path,data+i*160+32,128);
          if (i)
            b->next=l;
          else
            shortcut_names=l;
          b=l;
          i++;
        }
        isok++;
        mfree(data);
      }
      fclose(hFile,&io_error);
    }
  }
  if (GetFileStats(fast_run_filename,&fstat,&io_error)!=-1)
  {
    if ((hFile=fopen(fast_run_filename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
    {
      len=fstat.size;
      if (len>sizeof(MYLIST3)){
        data=malloc(len+1);
        fread(hFile,data,len,&io_error);
        
        FreeFRShortcuts();
        int i=0;
        MYLIST3 *b;
        while ((i<200)&&(strcmp(data+(i-1)*16,fast_run_last_name)!=0))
        {
          MYLIST3 *l = malloc(sizeof(MYLIST3));
          l->next=0;
          memcpy(l->shortcut_name,data+i*16,16);
          if (i)
            b->next=l;
          else
            fast_run_shortcuts=l;
          b=l;
          i++;
        }
        isok++;
        mfree(data);
      }
      fclose(hFile,&io_error);
    }
  }
  if (isok==3)
    return 1;
  else
    return 0;
}

void free_old_names(void* table2)
{
  int i = 0;
  shortcut* table = table2;
  while((i<250) && (strcmp(table[i].name,shortcuts_last_name)!=0) && (table[i].name[0]!=0))
    {
      if (((int)(table[i].lgp_full_name) < 0) || ((int)(table[i].lgp_short_name) < 0))
      {
        mfree((char*)(table[i].lgp_full_name));
        return;
      }
      i++;
    }
}

void SaveAlarmConfig(){
  void** table_point=(void**)FreeRAM()+0x1C;
  if ((*table_point)==0){
    ShowMSG(1,(int)LGP_NOTINSTALLED);
    return;
  }
  volatile int hFile;
  unsigned int io_error = 0;
  int len=0;
  char* data=0;
  char* names=malloc(GetElfCount()*160+1);
  free_old_names(*table_point);
  FSTATS fstat;
  GetFileStats(shortcuts_filename,&fstat,&io_error);
  if ((hFile=fopen(shortcuts_filename,A_WriteOnly+A_BIN,P_WRITE,&io_error))!=-1){
    len=GetShortcutsCount()*sizeof(shortcut);
    if (fstat.size>len)
      len = fstat.size;
    data=malloc(len);
    memset(data,0,len);
    
    len=0;
    MYLIST *l=shortcuts;
    while (l){
      memcpy(data+len,&(l->a),sizeof(shortcut));
      len+=sizeof(shortcut);
      l=l->next;
    }
    if (fstat.size>len)
      len = fstat.size;
    memcpy(*table_point,data,len);//сохраняем в рам
    fwrite(hFile, data, len, &io_error);
    mfree(data);
    fclose(hFile,&io_error);
  }
  GetFileStats(shortcut_names_filename,&fstat,&io_error);
  if ((hFile=fopen(shortcut_names_filename,A_WriteOnly+A_BIN+A_Create,P_WRITE,&io_error))!=-1){
    int a = GetElfCount();
    memset(names,0,a*160+1);
    
    int i = 0;
    len=0;
    MYLIST2 *l=shortcut_names;
    while (l && (i<a)){
      memcpy(names+len,l->full_name,16);
      memcpy(names+len+16,l->short_name,16);
      memcpy(names+len+32,l->elf_path,128);
      len+=160;
      l=l->next;
    }
    
    i = 0;
    int count = 0;
    shortcut* table = *table_point;
    while((i<250) && (strcmp(table[i].name,shortcuts_last_name)!=0) && (table[i].name[0]!=0))
    {
      if ((table[i].lgp_full_name == MYMAGIC) || (table[i].lgp_short_name == MYMAGIC))
      {
        table[i].lgp_full_name = (int)(names+count*160);
        table[i].lgp_short_name = (int)(names+count*160+16);
        table[i].lgp_comment_msg = (int)(names+count*160+32);
        table[i].pointer = *(table_point+2);
        count ++;
      }
      i++;
    }
    fwrite(hFile, names, len, &io_error);
    fclose(hFile,&io_error);
  }
  GetFileStats(fast_run_filename,&fstat,&io_error);
  if ((hFile=fopen(fast_run_filename,A_WriteOnly+A_BIN,P_WRITE,&io_error))!=-1){
    len=GetFRShortcutsCount()*16;
    if (fstat.size>len)
      len = fstat.size;
    data=malloc(len);
    memset(data,0,len);
    
    len=0;
    MYLIST3 *l=fast_run_shortcuts;
    while (l){
      memcpy(data+len,l->shortcut_name,16);
      len+=16;
      l=l->next;
    }
    if (fstat.size>len)
      len = fstat.size;
    memcpy(*(table_point+1),data,len);//сохраняем в рам
    fwrite(hFile, data, len, &io_error);
    mfree(data);
    fclose(hFile,&io_error);
  }
}
extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

void AddNewELF(){
  MYLIST* l=malloc(sizeof(MYLIST));
  memset(l,0,sizeof(MYLIST));
  l->a.pointer=(void*)0xFFFFFFFF;//TODO: найти какой-то loopback на всякий случай
  l->a.get_status=0;
  l->a.unk_1=0x578;//хз что такое, но так работает
  l->a.lgp_full_name=MYMAGIC;
  l->a.unk_2=0x7FFF;
  l->a.lgp_short_name=MYMAGIC;
  l->a.unk_3=0x7FFF;
  l->a.unk_4=0x7FFF;
  l->a.lgp_comment_msg=0x7FFF;
  int b = GetElfCount();
  int c = GetShortcutsCount();
  int d = GetFRShortcutsCount();
  int numelf=0;
  if (b)
  {
    char* str = FindShortcutByNum(c-5)->a.name+9;
    if (str)
    while ((*str!=0) && (*str=='0'))
      str++;
    numelf = strtoul(str,0,10)+1;
  }
  sprintf(l->a.name,"STUP_ZELF%06d",numelf);
  
  if (c>4)
  {
    MYLIST* nl=FindShortcutByNum(c-5);
    l->next = nl->next;
    nl->next = l;
    
    MYLIST2* l2=malloc(sizeof(MYLIST2));
    memset(l2,0,sizeof(MYLIST2));
    sprintf(l2->full_name,LGP_NEWELFNAME,b+1);
    sprintf(l2->short_name,LGP_NEWELFNAME,b+1);
    sprintf(l2->elf_path,newelfpath);
    l2->next = 0;
    
    if (b)
    {
      MYLIST2* nl2=FindShortcutNameByNum(b-1);
      nl2->next = l2;
    }
    else
      shortcut_names=l2;
    
    MYLIST3* l3=malloc(sizeof(MYLIST3));
    memcpy(l3->shortcut_name,l->a.name,16);
    
    MYLIST3* nl3=FindFRShortcutByNum(d-4);
    l3->next = nl3->next;
    nl3->next = l3;
  }
  else
    ShowMSG(1,(int)LGP_ADDERROR);
}

/*TODO:
void AddNewShortcut()
{
}*/

int GetElfNumByFRnum(int num){
  int zeroelf = GetFRShortcutsCount() - 3 - GetElfCount();//позиция первого эльфа в массиве быстрого запуска
  return num - zeroelf;
}
int GetShortcutNumByElfNum(int num){
  int zeroelf = GetShortcutsCount() - 4 - GetElfCount();//позиция первого эльфа в массиве шорткатов
  return num + zeroelf;
}

void DelFRShortcut(int numindex){
  int a = GetElfNumByFRnum(numindex);
  int b = GetElfCount();
  int d = GetFRShortcutsCount();
  int zeroelf = d - 3 - b;
  if ((numindex<d-3) && (d>4) && (numindex>0))
  {
    if (numindex>=zeroelf)
    {
      MYLIST* p = FindShortcutByNum(GetShortcutNumByElfNum(a)-1);
      MYLIST* l = p->next;
      p->next = l->next;
      mfree(l);
      if (numindex==zeroelf)
      {
        MYLIST2* p2 = shortcut_names;
        shortcut_names = p2->next;
        mfree(p2);
      }
      else
      {
        MYLIST2* p2 = FindShortcutNameByNum(a-1);
        MYLIST2* l2 = p2->next;
        p2->next = l2->next;
        mfree(l2);
      }
    }
    
    MYLIST3* p3 = FindFRShortcutByNum(numindex-1);
    MYLIST3* l3 = p3->next;
    p3->next = l3->next;
    mfree (l3);
  }
  else if ((!numindex) && (d>4))
  {
    MYLIST3* p3 = fast_run_shortcuts;
    fast_run_shortcuts = p3->next;
    mfree(p3);
  }
  else
    ShowMSG(1,(int)"невозможно удаление последних элементов");
}

//------------------          EDIT ALARM GUI           -----------------------//

void ed_ghook(GUI *data, int cmd)
{
  int i;
  EDITCONTROL ec;
  if (cmd==TI_CMD_REDRAW)
  {
    i=EDIT_GetFocus(data);
    ExtractEditControl(data,i,&ec);
    
    MYLIST3* l3 = FindFRShortcutByNum(shcutpos);
    MYLIST* l = FindShortcutByName(l3->shortcut_name);
    bool iself = (l->a.lgp_full_name==MYMAGIC) || (l->a.lgp_short_name==MYMAGIC);
    if (iself)
    {
      MYLIST2* l2 = FindShortcutNameByNum(GetElfNumByFRnum(shcutpos));
      if (i==2)
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,l2->full_name,16);
        ws_2str(ews,l2->short_name,16);
      }
      else if (i==4)
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,l2->elf_path,128);
      }
    }
    else
    {
      if (i==2)
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,l3->shortcut_name,16);
        
        MYLIST* l = FindShortcutByName(l3->shortcut_name);
        EDITCONTROL ec2;
        ExtractEditControl(data,3,&ec2);
        if (l)
          wsprintf(ec2.pWS,percent_t,l->a.lgp_full_name);
        else
          wsprintf(ec2.pWS,percent_t,0x7FFF);
        StoreEditControl(data ,3, &ec2);
      }
    }
  }
}

extern void open_select_file_gui(void *ed_gui, int type);

void on_utf8ec(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,percent_t,LGP_SELECTFILE);
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      open_select_file_gui(item->user_pointer, 1);
      break;
    }
  }   
}

/*void restore(){
        MYLIST *l=FindSettingsByNum(alarm_num);
        memcpy(l,backup, sizeof(MYLIST));
        mfree(backup);
}*/

int ed_onkey(GUI *data, GUI_MSG *msg)
{
  int l,i;
  if (msg->keys==0xFFF)  // OK
  {
    return (1);    
  }
  if (msg->keys==0xFFE)  // Back
  {
    return (0xFF);
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    l=msg->gbsmsg->submess;
    i=EDIT_GetFocus(data);
      if ((l==ENTER_BUTTON) && (i==4)){
        EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,1);
        return (-1);
      }
      /*else if ((l==ENTER_BUTTON) && (i==2)){//TODO: список с шорткатами
        EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,1);
        return (-1);
      }*/
      else if (l==RIGHT_SOFT)//выход с сохранением
      {
        int a = EDIT_GetCursorPos(data);
        if (a==1){
          //mfree(backup);
          return 1;
        }
      }
      else if (l==RED_BUTTON)//выход без сохранения
      {
        //restore();
        return (1);
      }
  }
  return(0); //Do standart keys
  //1: close
}

void ed_locret(void){}

INPUTDIA_DESC ed_desc=
{
  1,
  ed_onkey,
  ed_ghook,
  (void *)ed_locret,
  0,
  &menu_skt2,
  {0,0,0,0},
  4,
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

int create_ed(int pos)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  shcutpos = pos;
  
   MYLIST3* l3 = FindFRShortcutByNum(shcutpos);
   MYLIST* l = FindShortcutByName(l3->shortcut_name);
   bool iself = (l->a.lgp_full_name==MYMAGIC) || (l->a.lgp_short_name==MYMAGIC);
   if (iself)
   {
     MYLIST2* l2 = FindShortcutNameByNum(GetElfNumByFRnum(shcutpos));
     
     //название эльфа
     wsprintf(ews,percent_t,LGP_EDITELFNAME);
     ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//1
     
     str_2ws(ews,l2->full_name,16);
     ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,16);
     AddEditControlToEditQend(eq,&ec,ma);//2
     
     //путь к эльфу
     wsprintf(ews,percent_t,LGP_ENITELFPATH);
     ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//3
     
     str_2ws(ews,l2->elf_path,128);
     ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//4
     
     /*//название эльфа (сокращенное)
     wsprintf(ews,percent_t,);
     ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//3
     
     str_2ws(ews,l2->short_name,16);
     ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,16);
     AddEditControlToEditQend(eq,&ec,ma);//5*/
   }
   else
   {
     wsprintf(ews,percent_t,LGP_EDITSHORTCUTNAME);
     ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//1
     
     //шорткат
     wsprintf(ews,percent_s,l3->shortcut_name);
     ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,16);
     AddEditControlToEditQend(eq,&ec,ma);//2
     
     //название шортката
     wsprintf(ews,percent_t,l->a.lgp_full_name);
     ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
     AddEditControlToEditQend(eq,&ec,ma);//3
   }
  
  //backup = malloc(sizeof(MYLIST));// - не забыть освободить
  //memcpy(backup,l, sizeof(MYLIST));// - сохраняем на случай выхода без сохранения
  
  patch_header(&menuhdr);
  patch_input(&ed_desc);
  int result = CreateInputTextDialog(&ed_desc,&menuhdr,eq,1,0);
  return result;
}

//--------------         Выбор дня недели и будильника        ----------------//

void list_menu_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  int icon;

  WSHDR *ws2;
  WSHDR *ws4;
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  if (curitem != GetFRShortcutsCount())
    {
      MYLIST3* l3 = FindFRShortcutByNum(curitem);
      MYLIST* l = FindShortcutByName(l3->shortcut_name);
      bool iself = (l->a.lgp_full_name==MYMAGIC) || (l->a.lgp_short_name==MYMAGIC);
      icon=iself?ICON_ELF:ICON_SHORTCUT;
      if (iself)
      {
        MYLIST2* l2 = FindShortcutNameByNum(GetElfNumByFRnum(curitem));
        str_2ws(ws1,l2->full_name,63);
        wsprintf(ws3,l2->elf_path);
      }
      else
      {
        wsprintf(ws1,percent_t,l->a.lgp_full_name);
        wsprintf(ws3,percent_t,l3->shortcut_name);
      }
    }
    else
    {
      icon=ICON_ADDNEW;
      wsprintf(ws1,percent_t,LGP_ADDNEWELF);
    }
  ws2=AllocMenuWS(data,ws1->wsbody[0]);
  wstrcpy(ws2,ws1);

  SetMenuItemIconArray(data, item, S_ICONS+icon);
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}

void RecountMenu(int needfocus)
{
  int i;
  void *data;
  data=FindGUIbyId(list_menu_id,NULL);
  i=GetFRShortcutsCount()+1;//+пункт добавления
  if (i!=prev_lmenu_itemcount)
  {
    prev_lmenu_itemcount=i;
    Menu_SetItemCountDyn(data,i);
  }
  if(needfocus) SetCursorToMenuItem(data,needfocus);
  if (IsGuiOnTop(list_menu_id)) RefreshGUI();
}

void list_menu_ghook(void *data, int cmd){
}

int list_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if (msg->keys==0x3D)//джойстик
  {
    if (i==GetFRShortcutsCount())
    {
      int b = GetFRShortcutsCount() - 3;
      AddNewELF();
      RecountMenu(b);
      create_ed(b);
    }
    else
      create_ed(i);
    return (-1);
  }
  else if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    if (key==GREEN_BUTTON)
    {
      int b = GetFRShortcutsCount() - 3;
      AddNewELF();
      RecountMenu(b);
      create_ed(b);
      return(-1);
    }
    else if (key=='#')
    {
      DelFRShortcut(i);
      RecountMenu(i);
      return(-1);
    }
    else if (key==RIGHT_SOFT)
    {
      SaveAlarmConfig();
      return(-1);
    }
  }
  return(0);
}

int create_list_menu()//меню со списком шорткатов
{
  patch_header(&menuhdr);
  
  int to_item = GetFRShortcutsCount();
  if (GetElfCount())
    to_item -=4;
  return list_menu_id=CreateMultiLinesMenu(0,0,&list_menu,&menuhdr,to_item,GetFRShortcutsCount()+1);
}

//-----------------------          CSM                  ----------------------//

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(128);
  csm->gui_id=create_list_menu();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeShortcuts();
  FreeShortcutNames();
  FreeFRShortcuts();
  FreeWS(ews);
  SUBPROC((void *)Killer);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), percent_t, LGP_ELFNAME);
}

//-------------------------      MAIN     ------------------------------------//

int main()
{
  if (!LoadSettings()){
    ShowMSG(1,(int)LGP_ERRORLOADING);
    return 0;
  }
  S_ICONS[0]=(int)icon1;
  S_ICONS[1]=(int)icon2;
  S_ICONS[2]=(int)icon3;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

