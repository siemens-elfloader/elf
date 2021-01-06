/*
TODO:

*/

//для отладки гуя
#define ONLY_GUI_
//для демона
#define DEMON_
#ifdef NEWSGOLD
  #define DEFAULT_DISK "4"
  #define USR_MOBILE 0xE107
#else
  #define DEFAULT_DISK "0"
  #define USR_MOBILE 0xE101
#endif



#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "rect_patcher.h"
#include "conf_loader.h"
#include "language.h" //потом сгодится

#include "reclist.h"

static int prev_clmenu_itemcount;
int curlist=0;
int mask=RECORD_TYPE_DIAL;
SABmain ABmain;

//10*512=5kb;
CRECSLIGHT rc[MAX_RECORDS];
int rcCnt=0;


CContact cache[CONTACT_CACHE_SIZE];


extern void kill_data(void *p, void (*func_p)(void *));




int S_ICONS[8];
int hdr_icon;
int CountRecord(void);

char clm_hdr_text[48]="Calls Records";


volatile int contactlist_menu_id=0;
static const HEADER_DESC contactlist_menuhdr = {0, 0, 0, 0, &hdr_icon, (int)clm_hdr_text, LGP_NULL};

static const int menusoftkeys[] = {0,1,2};

char str[4][15]={"Calls-Dial","Calls-Recv","Calls-Miss","Calls-Moto"};

void UpdateCLheader(void)
{
#ifndef  ONLY_GUI
  
  hdr_icon=S_ICONS[curlist+3];
  sprintf(clm_hdr_text,"%s :%d",str[curlist],CountRecord());
#endif  
}


void contactlist_menu_ghook(void *data, int cmd);
int contactlist_menu_onkey(void *data, GUI_MSG *msg);
void contactlist_menu_iconhndl(void *data, int curitem, void *unk);

char clmenu_sk_r[16]=LG_CLOSE;



void RecountMenu(CContact  *req){
#ifdef ONLY_GUI
  return;
#endif   
  UpdateCLheader();  
  int i;
  int j;
  void *data;
  if (!contactlist_menu_id) return; //Нечего считать

  data=FindGUIbyId(contactlist_menu_id,NULL);
  if (!data)return;
  if (req==NULL)
  {
    j=0;
  }
  else
  {
    j=FindContactByContact(req);
  }
  i=CountRecord();

//  i=1;
  
  if (j>=i) j=i-1;
  if (j<0) j=0;
  
  if (i!=prev_clmenu_itemcount)
  {
    prev_clmenu_itemcount=i;
    Menu_SetItemCountDyn(data,i);
  }
  SetCursorToMenuItem(data,j);


//  if (IsGuiOnTop(contactlist_menu_id)) RefreshGUI();
}

static const SOFTKEY_DESC clmenu_sk[]=
{
//  {0x0018, 0x0000, (int)LG_OPTIONS},  
  {0x0000, 0x0000, (int)""},    
  {0x0001, 0x0000, (int)clmenu_sk_r},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};


static const SOFTKEYSTAB clmenu_skt =
{
  clmenu_sk, 0
};

static const ML_MENU_DESC contactlist_menu=
{
  8,contactlist_menu_onkey,contactlist_menu_ghook,NULL,
  menusoftkeys,
  &clmenu_skt,
  0x11, 
  contactlist_menu_iconhndl,
  NULL, 
  NULL, 
  0,   //n
  2 //Добавочных строк  
};


int create_contactlist_menu(void)
{
  int i;
#ifndef ONLY_GUI  
   i=CountRecord();   
#else
   i=3;   
#endif      

//i=1;
  prev_clmenu_itemcount=i;
  UpdateCLheader();
#ifndef DEMON
  patch_header(&contactlist_menuhdr);
  contactlist_menu_id=CreateMultiLinesMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i);
  return contactlist_menu_id;
#else
  
  return 0;
#endif  
}






void contactlist_menu_ghook(void *data, int cmd)
{
  if (cmd==9)  ///unfocus ?
  {
    ;
  }
  if (cmd==0x0A)
  {
  //pltop->dyn_pltop=XStatusesImgList;

    DisableIDLETMR();
  }
}

/*
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
*/

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{

    CContact *t=NULL;
  int i;
  i=GetCurMenuItem(data);
#ifndef ONLY_GUI
  t=GetContactByItem(i);
#endif   

      
  if (msg->keys==0x3D)
  {
    if (t)
    {
      if (t->recId&RECORD_IS_GROUP)
      {
	t->recId^=RECORD_GROUP_EXPAND;
        rc[FindIdByMenuId(i,mask)].recId^=RECORD_GROUP_EXPAND;
	RecountMenu(t);
	return(-1);
      }
    }
    return(0);
  }else;
  /*
  if (msg->keys==0x01)
  {
    contactlist_menu_id=0;
    return 0;
  } else;   
  */
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    //меняем списки
    int masks[]={RECORD_TYPE_DIAL,RECORD_TYPE_RECV,RECORD_TYPE_MISS,RECORD_TYPE_ALL};//0-all calls
    if (key==RIGHT_BUTTON){
      curlist++; 
      if (curlist>3)curlist=0;
      mask=masks[curlist];
      RecountMenu(NULL);
      return (-1);
    }else
    if (key==LEFT_BUTTON){
      curlist--;
      if (curlist<0)curlist=3;
      mask=masks[curlist];
      RecountMenu(NULL);
            return (-1);
    }else
    if (key==GREEN_BUTTON){      
      contactlist_menu_id=0;            
      char numb[132];
      int ln;
      ws_2utf8(t->Number,numb,&ln,20);
//      sprintf(numb,"=%ls=\n-%hs-  ",);
//        ShowMSG(1,(int)numb);
      MakeVoiceCall(numb,0x10,0x2FFF);

//      return(-1);
      return(1);      //close ?
    }
      
  }
//ТУТ БЫ тоже не плохо было прикрутить поиск по Т9
    
  return(0);
}



const char percent_t[]="%t";
const char percent_d[]="%d";
const char empty_str[]="";

void contactlist_menu_iconhndl(void *data, int curitem, void *unk)
{
  CContact *t=NULL;
  void *item=AllocMLMenuItem(data);
  
  WSHDR *ws2;
  WSHDR *ws4;
  
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  

#ifndef ONLY_GUI
  t=GetContactByItem(curitem);
#endif    

  if (t&&(t->recId!=-1))
  {
    WSHDR *fn=t->Name;
    if (fn->wsbody&&fn->wsbody[0]){  //если есть  имя то
//E01C/E01D - left/right align
//E01E/E01F - center off/on      
    if (t->recId&RECORD_IS_GROUP)
      wsprintf(ws1, "(%d) %w",GetCallsCount(t->recId&0x1ff), t->Name);
    else
        wstrcpy(ws1,t->Name);      
      wsprintf(ws3, "%w\n %02d.%02d.%02d%c%02d:%02d",t->Number,t->datetime.day,t->datetime.month,t->datetime.year%100,0xE01D,t->datetime.hour,t->datetime.min);                      
    }
    else{//иначе тока номер
      if (t->recId&RECORD_IS_GROUP)
        wsprintf(ws1, "(%d) %w",GetCallsCount(t->recId&0x1ff),t->Number);                  
      else
       wsprintf(ws1, "%w",/*FindRecordIdByMenuId(curitem,mask),GetCacheRecordById(FindRecordIdByMenuId(curitem,mask)),*/t->Number);                         
       wsprintf(ws3, " \n%02d.%02d.%02d%c%02d:%02d",t->datetime.day,t->datetime.month,t->datetime.year%100,0xE01D,t->datetime.hour,t->datetime.min);               
    }
    
  }
  else
  {
    wsprintf(ws1, LG_CLERROR);
    wsprintf(ws3, LG_CLERROR);   
  }
 
  ws2=AllocMenuWS(data,ws1->wsbody[0]);
  wstrcpy(ws2,ws1);
  
  char ico=0;
  if (t&&t->recId&RECORD_IS_GROUP)      {//группа
      if (t->recId&RECORD_GROUP_EXPAND)  //развернута -
//        ico=0;
;
     else //свернута +
      ico=1;
  }
  else{
    if (t&&t->recId&RECORD_IN_GROUP) ico=7;
    else
     ico=2;
  }
  SetMenuItemIconArray(data, item, S_ICONS+ico);
  
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}










void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

unsigned short maincsm_name_body[140];


void maincsm_oncreate(CSM_RAM *data)
{
//  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
//  zeromem(main_gui,sizeof(MAIN_GUI));
  /*
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
 */
  csm->csm.state=0;
  csm->csm.unk1=0;
///  csm->gui_id=CreateGUI(main_gui);
#ifndef DEMON  
  csm->gui_id=    create_contactlist_menu();
  
#endif  
//  maincsm=
      RecountMenu(NULL);
  
//  SUBPROC((void*)  ReadCal);
//  ReadCal();    
  
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
  }
  /*
 if (msg->msg==MSG_CSM_DESTROYED)
  {
    RefreshGUI();
  }  
  */
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}


void maincsm_onclose(CSM_RAM *csm)
{
  contactlist_menu_id=0;
  ///kill lists
#ifndef ONLY_GUI  
  ClearContacts();  
#endif  
  SUBPROC((void *)ELF_KILLER);
}

const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Call Records v0.3b");
}

int maincsm;


char str1[]="4:\\zbin\\img\\callrecs\\groupon.png";
char str2[]="4:\\zbin\\img\\callrecs\\groupoff.png";
char str3[]="4:\\zbin\\img\\callrecs\\cd.png";
char str4[]="4:\\zbin\\img\\callrecs\\ci.png";
char str5[]="4:\\zbin\\img\\callrecs\\cm.png";
char str6[]="4:\\zbin\\img\\callrecs\\ca.png";
char str7[]="4:\\zbin\\img\\callrecs\\ce.png";

#ifdef DEMON
int (*old_ed_onkey)(GUI *gui, GUI_MSG *msg);

int my_ed_onkey(GUI *gui, GUI_MSG *msg)
{
  int key=msg->gbsmsg->submess;
  int m=msg->gbsmsg->msg;
  int r;
  if (IsUnlocked()&&(m==KEY_DOWN)&&(key==GREEN_BUTTON)&&(!contactlist_menu_id))
  {
  patch_header(&contactlist_menuhdr);
  curlist=0;
  int i;
#ifndef ONLY_GUI  
   i=CountRecord();   
#else
   i=3;   
#endif    


  contactlist_menu_id=CreateMultiLinesMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i);
  RecountMenu(NULL);

//    ShowCallList(2, 0);
//    ShowCallList(1, 0);
//    ShowCallList(0, 0);
    r=0;
  }
  else    
    r=old_ed_onkey(gui,msg);
  return(r);
}

void DoSplices(GUI *gui)
{
  static INPUTDIA_DESC my_ed;
  memcpy(&my_ed,gui->definition,sizeof(INPUTDIA_DESC));
  if (my_ed.onKey != my_ed_onkey)
  {
    old_ed_onkey=my_ed.onKey;
    my_ed.onKey=my_ed_onkey;
    gui->definition=&my_ed;
  }
}



CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);


int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result=0;

  csm_result=old_icsm_onMessage(data,msg); //Вызываем старый обработчик событий

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])  
  
  if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует (а не в проекте ;))
    {
      DoSplices(igui);
    }
  }
  if (msg->msg==   MSG_END_CALL){
//    refreshbase();
  }
  
  return(csm_result);
}

#endif


void ReadRecord0(){
  ReadRecord(-1);
}
int main(void)
{  
  InitConfig();
  extern const char *successed_config_filename;  
  char m=successed_config_filename[0];
  str1[0]=  m;
  str2[0]=  m;
  str3[0]=  m;
  str4[0]=  m;
  str5[0]=  m;
  str6[0]=  m;
  str7[0]=  m;  
  
  
  S_ICONS[0]=(int)str1;
  S_ICONS[1]=(int)str2;
  S_ICONS[2]=GetPicNByUnicodeSymbol(USR_MOBILE); 
  S_ICONS[3]=(int)str3;
  S_ICONS[4]=(int)str4;
  S_ICONS[5]=(int)str5;
  S_ICONS[6]=(int)str6;//all
  S_ICONS[7]=(int)str7;//empty  

  

  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();

#ifdef DEMON
  CSM_RAM *save_cmpc;
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  maincsm=CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;

  
   CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  // как бы его потом корректно удалить?

#else
  maincsm=CreateCSM(&MAINCSM.maincsm,dummy,0);  
#endif  


  UnlockSched();
//#ifdef ELKA  
//  SUBPROC((void*)  ReadRecord0);
//#else
#ifndef ONLY_GUI  
  InitContacts();
  ReadRecord0();
  PostProcessRecords();
#endif 
  
//#endif  
  return 0;
}
