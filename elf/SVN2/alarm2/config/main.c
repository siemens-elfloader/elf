#include "..\..\inc\swilib.h"
#include <stdbool.h>
#include "..\alarm.h"

extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

//------------------------      ETC           --------------------------------//

//по порядку
enum MY_ICONS {
  ICON_LOGO,
  ICON_ALARM_ON,
  ICON_ALARM_OFF,
  ICON_ADD_ALARM
};

int S_ICONS[4];

WSHDR *ews;
int alarm_wd=-1;
int alarm_num=-1;

int list_menu_id;
int prev_lmenu_itemcount;
MYLIST* backup;
MYLIST* MySettings[7];

int coord[2]={0,0};
char ring_melody[128]={0};

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

char lm_hdr_text[2][64];
static HEADER_DESC alarm_menuhdr = {0, 0, 0, 0, S_ICONS+ICON_LOGO, (int)(lm_hdr_text[0]), LGP_NULL};
static HEADER_DESC alarm_menuhdr2 = {0, 0, 0, 0, S_ICONS+ICON_LOGO, (int)(lm_hdr_text[1]), LGP_NULL};
static HEADER_DESC alarm_menuhdr3 = {0, 0, 0, 0, S_ICONS+ICON_LOGO, (int)LGP_ALARM, LGP_NULL};
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

static SOFTKEY_DESC menu_sk3[]=
{
  {0x0018, 0x0000, (int)LGP_CHANGE},
  {0x0001, 0x0000, (int)LGP_OK},
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

static const SOFTKEYSTAB menu_skt3 =
{
  menu_sk3, 0
};

////////////////////////////////////////////////////////////////////////////////

void list_menu_ghook(void *data, int cmd);
int list_menu_onkey(void *data, GUI_MSG *msg);
void list_menu_iconhndl(void *data, int curitem, void *unk);

static const ML_MENU_DESC list_menu=
{
  8,list_menu_onkey,list_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt2,
  0x11, //+0x400
  list_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1  //Добавночных строк
};

void UpdateHeader(int menu_num)
{
  switch (menu_num){
  case 0: {
    TTime t;
    GetDateTime(0,&t);
#ifdef ELKA
    sprintf(lm_hdr_text[0],"%s  %02d:%02d", LGP_ALARM, t.hour, t.min);
#else
    sprintf(lm_hdr_text[0],"%s   %02d:%02d", LGP_ALARM, t.hour, t.min);
#endif
  }break;
  case 1:{
    sprintf(lm_hdr_text[1],percent_s, weekdays[alarm_wd]);
  }break;
  }
};
//-----------------------         ALARM             --------------------------//

MYLIST* FindSettingsByNum(int num){
  MYLIST* l=MySettings[alarm_wd];
  int i=1;
  if (l && num) while(l->next){
    l=l->next;
    if (i==num) return l;
    i++;
  }
  return l;
}

int GetAlarmCount(int wd){
  if (wd==-1)
    wd=alarm_wd;
  MYLIST* l=MySettings[wd];
  if (!l)
    return 0;
  int i=1;
  while(l=l->next)
    i++;
  return i;
}

void free_alarms(){
  for (int i=0;i<7;i++){
    MYLIST* l = MySettings[i];
    while(l){
      MYLIST* b = l->next;
      mfree(l);
      l=b;
    }
  }
}

void LoadAlarmConfig(char* filename){
  char *newfilename=filename;
  bool needmfree=false;
  if (!newfilename){
    newfilename=malloc(128);
    strcpy(newfilename,default_cfgfile);
    needmfree=true;
  }
  volatile int hFile;
  unsigned int io_error = 0;
  int len=0;
  FSTATS fstat;
  char* data;
  if (GetFileStats(newfilename,&fstat,&io_error)!=-1)
  {
    if ((hFile=fopen(newfilename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
    {
      len=fstat.size;
      if (len>0){
        data=malloc(len+1);
        fread(hFile,data,len,&io_error);
        
        coord[0]=*data;
        coord[1]=*(data+sizeof(int));
        
        int count[7];
        for(int i=0; i<7; i++){
          count[i]=data[2*sizeof(int)+i];
        }
        len=7+2*sizeof(int);
        
        free_alarms();
        for(int i=0; i<7; i++){
          MYLIST *b;
          for (int j=0; j<count[i]; j++){
            MYLIST *l=malloc(sizeof(MYLIST)+1);
            memcpy(l,data+len,sizeof(MYLIST));
            len+=sizeof(MYLIST);
            l->next=0;
            if (j){
              b->next=l;
            }
            else{
              MySettings[i]=l;
            }
            b=l;
          }
        }
        mfree(data);
      }
      fclose(hFile,&io_error);
    }
  }
  if (needmfree)
    mfree(newfilename);
}

void SaveAlarmConfig(char* filename){
  char *newfilename=filename;
  bool needmfree=false;
  if (!newfilename){
    newfilename=malloc(128);
    strcpy(newfilename,default_cfgfile);
    needmfree=true;
  }
  volatile int hFile;
  unsigned int io_error = 0;
  int len=7+2*sizeof(int);
  for(int i = 0; i < 7; ++i){
      MYLIST *l=MySettings[i];
      while (l){
        len+=sizeof(MYLIST);
        l=l->next;
      }
  }
  char* data=malloc(len+1);
  memset(data,0,len+1);
  if ((hFile=fopen(newfilename,A_WriteOnly+A_Create+A_BIN,P_WRITE,&io_error))!=-1){
    *data=coord[0];
    *(data+sizeof(int))=coord[1];
    len=2*sizeof(int);
    for(int i = 0; i < 7; ++i){
      data[len]=GetAlarmCount(i);
      len++;
    }
    for(int i = 0; i < 7; ++i){
      MYLIST *l=MySettings[i];
      while (l){
        memcpy(data+len,l,sizeof(MYLIST));
        len+=sizeof(MYLIST);
        l=l->next;
      }
    }
    fwrite(hFile, data, len, &io_error);
    fclose(hFile,&io_error);
  }
  mfree(data);
  if (needmfree)
    mfree(newfilename);
  GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,alarm_name);
}

void AddNewAlarm(){
  MYLIST* l=malloc(sizeof(MYLIST)+1);
  memset(l,0xFF,sizeof(MYLIST));
  l->next=0;
  l->status=false;
  l->hour=0;
  l->min=0;
  
  sprintf(l->ring.name,txt_null);
  l->ring.magic=MYMAGIC;
  l->ring.use=0;
  if (!strlen(ring_melody))
    sprintf(l->ring.melody,default_cfgmelody);
  else
    strcpy(l->ring.melody,ring_melody);
  l->ring.vibra_power=50;
#ifdef NEWSGOLD
  l->ring.volume=5;
#else
  l->ring.volume=10;
#endif  
  l->ring.set_profile=true;
  l->ring.restart_time=5;
  l->ring.count=0;
  
  int a=GetAlarmCount(-1);
  if (a){
    MYLIST* h=FindSettingsByNum(a-1);
    h->next=l;
  }
  else{
    MySettings[alarm_wd]=l;
  }
}

void DelAlarm(int numindex){
  MYLIST* p = FindSettingsByNum(numindex);
  if (numindex){
    MYLIST* l=FindSettingsByNum(numindex-1);
    l->next=p->next;
  }
  else{
    MySettings[alarm_wd]=p->next;
  }
  if (p)
    mfree(p);
}

//------------------          EDIT ALARM GUI           -----------------------//

void ed_ghook(GUI *data, int cmd)
{
  int i,j;
  char ss[128];
  EDITCONTROL ec;
  if (cmd==TI_CMD_REDRAW)
  {
    i=EDIT_GetFocus(data);
    ExtractEditControl(data,i,&ec);
    MYLIST *l=FindSettingsByNum(alarm_num);
    switch(i){
    case 1:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,l->ring.name,63/*wstrlen(ews)*/);
      } /*название будильника*/ break;
    case 4:
      {
        TTime tt;
        EDIT_GetTime(data,i,&tt);
        l->hour=tt.hour;
        l->min=tt.min;
      }/*время*/ break;
    case 6:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,l->ring.melody,127/*wstrlen(ews)*/);
        ws_2str(ews,ring_melody,127);
      } /*путь к файлу*/ break;
    case 8:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,ss,10);
        l->ring.vibra_power=strtoul(ss,0,10);
      }break;
    case 10:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,ss,10);
        l->ring.volume=strtoul(ss,0,10);
      } break;
    case 14:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,ss,10);
        l->ring.restart_time=strtoul(ss,0,10);
      } break;
    case 16:
      {
        wstrcpy(ews,ec.pWS);
        ws_2str(ews,ss,10);
        l->ring.count=strtoul(ss,0,10);
      } break;
    }
  }
  if (cmd==TI_CMD_COMBOBOX_FOCUS)
  {
    i=EDIT_GetFocus(data);
    ExtractEditControl(data,i,&ec);
        if ((j=EDIT_GetItemNumInFocusedComboBox(data)))
        {
          MYLIST *l=FindSettingsByNum(alarm_num);
          switch(i){
          case 2: wsprintf(ews,percent_t,msg_on_off[j-1]); l->status=(j==2); break;
          case 5: wsprintf(ews,percent_t,use_cbox[j-1]); l->ring.use=j-1; break;
          case 12: wsprintf(ews,percent_t,msg_yes_no[j-1]); l->ring.set_profile=(j==2); break;
          }
        }
        else
        {
          ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
          wstrcpy(ews,ec.pWS);
        }
        EDIT_SetTextToFocused(data,ews);
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

void restore(){
        MYLIST *l=FindSettingsByNum(alarm_num);
        memcpy(l,backup, sizeof(MYLIST));
        mfree(backup);
}

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
      if ((l==ENTER_BUTTON) && (i==6)){
        EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,1);
        return (-1);
      }
#ifdef NEWSGOLD
      else if (l==LEFT_SOFT)//выход с сохранением
#else
      else if (l==RIGHT_SOFT)//выход с сохранением
#endif
      {
        int a = EDIT_GetCursorPos(data);
        if (a==1){
          mfree(backup);
          return 1;
        }
      }
#ifdef NEWSGOLD
      else if (l==RIGHT_SOFT)//выход без сохранения
      {
          int a = EDIT_GetCursorPos(data);
          if (a==1){
            restore();
            return 1;
          }
      }
#else
      else if (l==RED_BUTTON)//выход без сохранения
      {
        restore();
        return (1);
      }
#endif
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
  &menu_skt3,
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

int create_ed()
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  MYLIST *l=FindSettingsByNum(alarm_num);
  
  backup = malloc(sizeof(MYLIST));// - не забыть освободить
  memcpy(backup,l, sizeof(MYLIST));// - сохраняем на случай выхода без сохранения
  
  //название будильника
  str_2ws(ews,l->ring.name,63);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,63);
  AddEditControlToEditQend(eq,&ec,ma);//1
  
//combobox для вкл/выкл статуса
  wsprintf(ews,percent_t,msg_on_off[l->status]);
  ConstructComboBox(&ec,ECT_COMBO_BOX,0x100040,ews,4,0,2,l->status+1);
  AddEditControlToEditQend(eq,&ec,ma);//2

  //Добавляем заголовок итема
  wsprintf(ews,percent_txt,LGP_TIME);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//3
  //время
  TTime tt={l->hour,l->min};
  ConstructEditControl(&ec,ECT_TIME,ECF_APPEND_EOL,0,0);
  ConstructEditTime(&ec,&tt);
  AddEditControlToEditQend(eq,&ec,ma);//4
  
  //использование
  wsprintf(ews,percent_t,use_cbox[l->ring.use]);
  ConstructComboBox(&ec,ECT_COMBO_BOX,ECF_APPEND_EOL,ews,32,0,4,l->ring.use+1);
  AddEditControlToEditQend(eq,&ec,ma);//5

  //путь к файлу
  str_2ws(ews,l->ring.melody,127);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,127);
  AddEditControlToEditQend(eq,&ec,ma);//6
  
  wsprintf(ews,percent_txt,LGP_VIBRA_POWER);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR/*ECF_APPEND_EOL*/,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//7
  //vibra_power
  wsprintf(ews,percent_d,l->ring.vibra_power);
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_POINT,ews,2);
  AddEditControlToEditQend(eq,&ec,ma);//8
  
  wsprintf(ews,percent_txt,LGP_VOLUME_LEVEL);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//9
  //громкость мелодии
  wsprintf(ews,percent_d,l->ring.volume);
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_POINT,ews,2);
  AddEditControlToEditQend(eq,&ec,ma);//10
  
  wsprintf(ews,percent_txt,LGP_SET1STPROFILE);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//11
  //установить 1й профиль при старте
  wsprintf(ews,percent_t,msg_yes_no[l->ring.set_profile]);
  ConstructComboBox(&ec,ECT_COMBO_BOX,0x100040,ews,8,0,2,l->ring.set_profile+11);
  AddEditControlToEditQend(eq,&ec,ma);//12
  
  wsprintf(ews,percent_txt,LGP_RESTARTTIME);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//13
  //время до перезапуска
  wsprintf(ews,percent_d,l->ring.restart_time);
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_POINT,ews,2);
  AddEditControlToEditQend(eq,&ec,ma);//14
  
  wsprintf(ews,percent_txt,LGP_RESTARTNUM);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);//15
  //количество перезапусков
  wsprintf(ews,percent_d,l->ring.count);
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_POINT,ews,1);
  AddEditControlToEditQend(eq,&ec,ma);//16
  
  patch_header(&alarm_menuhdr3);
  patch_input(&ed_desc);
  int result = CreateInputTextDialog(&ed_desc,&alarm_menuhdr3,eq,1,0);
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
  if (curitem != GetAlarmCount(-1))
    {
      MYLIST* l=FindSettingsByNum(curitem);
      icon=(l->status==true)?ICON_ALARM_ON:ICON_ALARM_OFF;
      str_2ws(ws1,l->ring.name,63);
      wsprintf(ws3," %02d:%02d %t",l->hour,l->min,msg_on_off[l->status]);
    }
    else
    {
      icon=ICON_ADD_ALARM;
      wsprintf(ws1,percent_t,LGP_ADDNEWALARM);
    }
  ws2=AllocMenuWS(data,ws1->wsbody[0]);
  wstrcpy(ws2,ws1);

  SetMenuItemIconArray(data, item, S_ICONS+icon);
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}

void RecountMenu(int needfocus)//обновить в гуе список будильников
{
  int i;
  void *data;
  data=FindGUIbyId(list_menu_id,NULL);
  i=GetAlarmCount(-1)+1;//+пункт добавить будильник
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
    if (i==GetAlarmCount(-1))
    {
      AddNewAlarm();
      RecountMenu(GetAlarmCount(-1));
    }
      alarm_num=i;
      create_ed();
    return (-1);
  }
  /*if (msg->keys==1)//софт-кнопка
  {
      return(-1);
  }*/
  else if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    if (key==GREEN_BUTTON)
    {
        AddNewAlarm();
        RecountMenu(GetAlarmCount(-1));
      alarm_num=GetAlarmCount(-1)-1;
      create_ed();
      return(-1);
    }
    if (key=='#')
    {
      int a=GetAlarmCount(-1);
      if (i!=a && a>0)
      {
        DelAlarm(i);
        alarm_num--;
        RecountMenu(i);
      }
      return(-1);
    }
  }
  else
    if (i!=GetAlarmCount(-1))
      alarm_num=i;
  return(0);
}

int create_list_menu()//меню будильников
{
  UpdateHeader(1);
  patch_header(&alarm_menuhdr2);
  
  return list_menu_id=CreateMultiLinesMenu(0,0,&list_menu,&alarm_menuhdr2,0,GetAlarmCount(-1)+1);
}


////////////////////////////////////////////////////////////////////////////////

void wd_menu_ghook(void *data, int cmd){};
void wd_menu_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data,32);
  wsprintf(ws,percent_t,weekdays[curitem]);
  SetMenuItemText(data,item,ws,curitem);
}

extern void EditCoordinates(void *rect_or_xy, int is_rect);

int wd_menu_onkey(void *data, GUI_MSG *msg){
  UpdateHeader(0);
  if (msg->keys==0x3D)//джойстик
  {
    alarm_wd=GetCurMenuItem(data);
    create_list_menu();
    return (-1);
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    if (key==GREEN_BUTTON)
    {
      EditCoordinates(coord,0);
      return(-1);
    }
    else if (key==RIGHT_SOFT)//выход с сохранением
    {
      SaveAlarmConfig(0);
      return (1);
    }
  }
  return(0);
}

MENU_DESC wd_menu=
{
  8,wd_menu_onkey,wd_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  wd_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int create_wd_menu(void)//меню дней недели
{
  UpdateHeader(0);
  patch_header(&alarm_menuhdr);
  return CreateMenu(0,0,&wd_menu,&alarm_menuhdr,0,7,0,0);
}
//-----------------------          CSM                  ----------------------//

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  csm->gui_id=create_wd_menu();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  free_alarms();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), percent_t, "alarm config");
}

//-------------------------      MAIN     ------------------------------------//

int main()
{
  for(int i = 0; i < 7; ++i)
  {
    MySettings[i]=0;
  }
  LoadAlarmConfig(0);
  S_ICONS[0]=(int)icon1;
  S_ICONS[1]=(int)icon2;
  S_ICONS[2]=(int)icon3;
  S_ICONS[3]=(int)icon4;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

