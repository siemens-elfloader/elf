/*
TODO:
parsing database events - long enough who think little more than 512 slbyty
*/
#define DEBUG_

#define DEMON
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
#include "language.h" //then microscope
static int prev_clmenu_itemcount;
int curlist=0;


extern const char root_dir[];
extern const char str1[];
extern const char str2[];
extern const char str3[];
extern const char str4[];
extern const char str5[];


#ifdef NEWSGOLD
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define COMPANY_NAME 0x29
#define POST_NAME 0x6F
#define DISPLAY_NAME 0x60
#define PICTURE 0x33
#define E_MAIL 0x2E
#else
#define NICKNAME 0x12
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define STREET 0x25
#define POSTCODE 0x26
#define CITY 0x27
#define COUNTRY 0x28
#define COMPANY_NAME 0x29
#define PHONE_OFFICE 0x2A
#define PHONE_FAX 0x2B
#define PHONE_MOBILE 0x2C
#define PHONE_NUMBER 0x2D
#define E_MAIL 0x2E
#define URL 0x2F
#define PICTURE 0x33
#define E_MAIL2 0x5D
#define PHONE_FAX2 0x5E
#define WALKY_TALKY_ID 0x6D
#endif


extern void kill_data(void *p, void (*func_p)(void *));

typedef struct 
{
  short year;
  short unk;
  char month;
  char day;
  short unk2;
  char hour;
  char min;
  char sec;
  char unk3; 
}dates;

//constants APO 
#define APO_TYPE 0x37

int S_ICONS[7];

int CountRecord(void);

char clm_hdr_text[48]="Calls Records";

volatile int contactlist_menu_id=0;
static const HEADER_DESC contactlist_menuhdr = {0, 0, 0, 0, S_ICONS+6, (int)clm_hdr_text, LGP_NULL};

static const int menusoftkeys[] = {0,1,2};

char str[3][15]={"Calls-Dial","Calls-Recv.","Calls-Miss"};

void UpdateCLheader(void)
{
//#ifdef ELKA
  int *p=contactlist_menuhdr.icon;
  *p=S_ICONS[curlist+3];
//#endif  
  sprintf(clm_hdr_text,"%s :%d",str[curlist],CountRecord());
}


void contactlist_menu_ghook(void *data, int cmd);
int contactlist_menu_onkey(void *data, GUI_MSG *msg);
void contactlist_menu_iconhndl(void *data, int curitem, void *unk);

char clmenu_sk_r[16]=LG_CLOSE;



typedef  struct {
  void* next;
  void* next_g;  //pointer to calls from the same number 
  dates datetime;
  char number[16];
  char name[31];  
  unsigned int duration;
  unsigned char type; //bit field flags
  unsigned int recid;  //Id records may be useful 
  char cnt;  //if the group is the number -1 subitemov
  char isGroup;  //Token Group 

}CRECS;


int FindContactByContact(CRECS *req);

void RecountMenu(CRECS  *req){
  int i;
  int j;
  void *data;
  UpdateCLheader();  
  if (!contactlist_menu_id) return; //Nothing to believe 
  
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
  if (j>=i) j=i-1;
  if (j<0) j=0;
  
  if (i!=prev_clmenu_itemcount)
  {
    prev_clmenu_itemcount=i;
    Menu_SetItemCountDyn(data,i);
  }
  SetCursorToMenuItem(data,j);
  if (IsGuiOnTop(contactlist_menu_id)) RefreshGUI();
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
  0x11+0x00010000, //+0x400
  contactlist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  2 //Dobavochnyh lines 
};


int create_contactlist_menu(void)
{
  int i;
  i=CountRecord();

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


typedef struct {
  CRECS *top;
  CRECS *end;  
  CRECS *grp;  
} CRECL;

CRECL list[4]={0}; //3 of the list of challenges, 4 - prozapas y

CRECS *FindNum(char *num,CRECL* cl){
  CRECS *ct=cl->top;
  while (ct){
    if (!strcmp(ct->number,num))return ct;
    ct=ct->next;
  }
  return NULL;
}

int PutRecSub(CRECS* in,CRECL *cl){  //hitrozhopye lists 
  if (!(cl->top)){cl->top=in;
    cl->end=in;    
  }
  else{
    CRECS *ex;
    if ((ex=FindNum(in->number,cl))){
      cl->grp=ex;
      ex->cnt++;      
       while(ex->next_g){
        ex=ex->next_g;
      }
      ex->next_g=in;
      in->next=cl->grp;
      in->isGroup=1;
      return 0;
    }else{
      cl->end->next=in;
      cl->end=in;    
    }
  }
  return 1;
};


int PutRec(CRECS* in){ 
  if ((in->type&0x06)==0x06) //missed
       return PutRecSub(in,&list[2]);
  else
    if ((in->type&0x02)==0x02)//incoming
       return PutRecSub(in,&list[1]);
  else  //others - dialed
       return PutRecSub(in,&list[0]);
};


void contactlist_menu_ghook(void *data, int cmd)
{
 // PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)  ///unfocus ?
  {
//  pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
  //pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
  }
}

CRECS* GetNext(CRECS *ct){  //hitrozhopoe release from the list 
    if (ct->cnt){ //Force 
      if (!(ct->cnt&0x80)){ //Group and curtailed 
        ct=ct->next;
      }else{
        ct=ct->next_g;
      }
    }else{ //BEGIN
      if (ct->isGroup){ //if the link within the group 
       if (ct->next_g)  //if there are groups within a downpayment 
         ct=ct->next_g;
         else{  //otherwise backwards to trace element 
          ct=ct->next;
          ct=ct->next;        
         };
       }
       else  //no group  
       ct=ct->next;       
    }
  
  return ct;
}

CRECS *FindRecordByN(int curitem){
  CRECS *ct=list[curlist].top;

  for (int j=0;ct&&(j<curitem);j++){
    ct=GetNext(ct);
  }
  return ct;
}
int CountRecord(void){
  CRECS *ct=list[curlist].top;

  int j;
  for ( j=0;ct;j++){
    ct=GetNext(ct);
  }
  return j;
}


int FindContactByContact(CRECS *req){
  CRECS *ct=list[curlist].top;

  int j;
  for ( j=0;ct&&ct!=req;j++){
    ct=GetNext(ct);
  }
  return j;
}

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{
  CRECS *t=NULL;
  int i;
  i=GetCurMenuItem(data);
  t=FindRecordByN(i);
/*
  if (msg->keys==0x18)
  {
    ShowMainMenu();
    return(-1);
  }
  */
      
  if (msg->keys==0x3D)
  {
    if (t)
    {
     
      if (t->cnt)
      {
	t->cnt^=0x80;
	RecountMenu(t);
	return(-1);
      }
    }
    return(-1);
  }else
  if (msg->keys==0x01)
  {
    contactlist_menu_id=0;
  } else;   
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    //changing lists 
    if (key==RIGHT_BUTTON){
      curlist++; 
      if (curlist>2)curlist=0;
      RecountMenu(NULL);
      return (-1);
    }else
    if (key==LEFT_BUTTON){
      curlist--;
      if (curlist<0)curlist=2;
      RecountMenu(NULL);
            return (-1);
    }else
    if (key==GREEN_BUTTON){      
      contactlist_menu_id=0;            
      MakeVoiceCall(t->number,0x10,0x2FFF);

      return(-1);
    }
      
  }
//TUT BY too bad, it was not tie search T9 
    
  return(0);
}



const char percent_t[]="%t";
const char percent_d[]="%d";
const char empty_str[]="";

void contactlist_menu_iconhndl(void *data, int curitem, void *unk)
{
  CRECS *t=NULL;
  void *item=AllocMLMenuItem(data);
  
  WSHDR *ws2;
  WSHDR *ws4;
  WSHDR ws1loc0, *ws0;
  unsigned short num0[128];
  ws0=CreateLocalWS(&ws1loc0,num0,128);
  
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  
  t=FindRecordByN(curitem);

  if (t)
  {

    if (t->name[0]){  //if it has a name 
        str_2ws(ws0,t->name,120);    
      if (t->cnt&0x7f)      {//
        wsprintf(ws1, "(%d) ",(t->cnt&0x7f)+1);
        wstrcat(ws1,ws0);
      }
      else
        wstrcpy(ws1,ws0);
     
      //     wsprintf(ws1, "%s -",ws1);
//E01C/E01D - left/right align
//E01E/E01F - center off/on      

       wsprintf(ws3, "%t\n%02d.%02d.%02d%c%02d:%02d",t->number,t->datetime.day,t->datetime.month,t->datetime.year%100,0xE01D,t->datetime.hour,t->datetime.min);                
    }
    else{//otherwise a current number
       if (t->cnt&0x7f)
       wsprintf(ws1, "(%d) %t",(t->cnt&0x7f)+1,t->number);                  
      else
       wsprintf(ws1, "%t",t->number);                         
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
  if (t->cnt)      {//Force 
      if (t->cnt&0x80)  //deployed -- 
//        ico=0;
;
     else //discouraged + 
      ico=1;
  }
  else{
     ico=2;
  }
  SetMenuItemIconArray(data, item, S_ICONS+ico);
  
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}




void ReadCal(void)//sobsvetnno readings APO 
// NOTE WRITTEN IN READING ELKU and probably NSG, and comes with the latest recording, and not the first, the couple must come SGOLD 
{
//  struct cals tmp_cal;
//  tmp_cal.number=AllocWS(250);
//  tmp_cal.name=AllocWS(250);  
  unsigned int ul;

  WSHDR *tel;
  tel=AllocWS(50);
  int fin;
  
#ifdef NEWSGOLD
#define MAX_RECORDS 504
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else 
#define MAX_RECORDS 512
//#define LEVEL1_RN	(0x20)
#define LEVEL1_RN	(23)  
#endif
  
  
  
#pragma pack(1)
  struct {
#ifdef NEWSGOLD
    long dummy1; //62 33 dc 05
    short len;  //!!!!! HZ SGOLD FOR POLE IS IT OR NOT 
    char bitmap[MAX_RECORDS/8];
#else
    long dummy1; 
    char bitmap[MAX_RECORDS/8];    
#endif    
  } ABmain;
#pragma pack()
  
//    unsigned int rec=0;
  unsigned int rec;    
  int fsz;
  char recname[128];
  char szRoot[100];  
  
  AB_UNPRES ur;
  void *buffer;
  int m=0;
//start parsing  
  if ((buffer=malloc(8192)))
  {
    zeromem(&ABmain,sizeof(ABmain));

    strcpy(szRoot, root_dir);
    fin = strlen(szRoot);
    if(fin > 0 && szRoot[fin-1] == '\\')
    szRoot[fin-1] = 0; 
    
    snprintf(recname,128,"%s\\main",szRoot);
    
    if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
    {
  
#ifdef ELKA
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=69)
#else
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
      {
#ifdef NEWSGOLD        
        rec=ABmain.len;  //WTO SOBSTVENNO HERE AND NOT GETTING CYCLE WITH ZERO 
#else
        rec=MAX_RECORDS-1;//cheat
#endif         
        fclose(fin,&ul);
	do
	{
          #ifdef NEWSGOLD
	  if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
          #else
          if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
          #endif   
	  {
            #ifdef NEWSGOLD
	    //The list is in bitmape 
        unsigned int rl1;
	    unsigned int rl2;
	    unsigned int rl3;
	    rl1=rec/LEVEL1_RN;
	    rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
	    rl3=rec%LEVEL2_RN;
	    snprintf(recname,128,"%s\\data\\%02d\\%02d\\%02d",szRoot,rl1,rl2,rl3);
            
            #else
	    unsigned int rl1=rec/LEVEL1_RN;
	    unsigned int r12=rec%LEVEL1_RN;
	    snprintf(recname,128,"%s\\%02x\\%02x",szRoot,rl1,r12);        
            #endif             
	    if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	    {
	      zeromem(&ur,sizeof(AB_UNPRES));
              fsz=lseek(fin,0,S_END,&ul,&ul);
              lseek(fin,0,S_SET,&ul,&ul);
  	      fread(fin,buffer,fsz,&ul);
	      fclose(fin,&ul);
              #ifdef NEWSGOLD
	      UnpackABentry(&ur,((char *)buffer+8),fsz,APO_TYPE);
              #else
              UnpackABentry(&ur,((char *)buffer+4),fsz-4,APO_TYPE);
              #endif
	      int i=0;
              LockSched();
              CRECS *loc;
              loc=malloc(sizeof(CRECS));
              zeromem(loc,sizeof(CRECS));
              loc->  recid=rec;
              UnlockSched();             
              
              while(i<ur.number_of_records)
	      {
                
		AB_UNPRES_ITEM *r=ur.record_list+i;
		if (r->no_data!=1)
		{

                  switch (GetTypeOfAB_UNPRES_ITEM(r->item_type))
                  {
                    case 6: //date 
                      memcpy(&loc->datetime,r->data,sizeof(dates));
                      break;
                    case 5: //name 
                      ws_2str(r->data,loc->name,30) ;    
                      break;    
                      
                    case 1:  {        //Number 
                      PKT_NUM *p=(PKT_NUM*)r->data;
                      if (p){
                        unsigned int c;
                        unsigned int c1;
                        int m,j;
                        j=0;
                        m=0;
                        wsprintf(tel,"");
                        //wsAppendChar(contact.icons,utf_symbs[n]);
                        if (p->format==0x91) wsAppendChar(tel,'+');
			  while(j<p->data_size)
			  {
                            if (m&1) {c1=c>>4; j++;}
                            else c1=(c=p->data[j])&0x0F;
			    if (c1==0x0F) break;
                            
                            if (c1==0xA) c1='*';
                            else if (c1==0xB) c1='#';
                            else if (c1==0xC) c1='+';
                            else if (c1==0xD) c1='?';
                            else c1+='0';
                            wsAppendChar(tel,c1);
			    m++;
			  }
                          ws_2str(tel,loc->number,15) ;    
                      }
                      }
                      break;
                    case 3://unsigned short / timne in secs?
                      if (r->item_type==0x52)
                      {
                        loc->duration=*((short*)r->data);
                      }
                      break;
                    case 0://unsigned int/ boolean ?
                      if (r->item_type==0x54)  loc->type|=0x01*(*((short*)r->data));  //kto polozil trubku (1 -sam)
                      if (r->item_type==0x55)  loc->type|=0x02*(*((short*)r->data)); //if 1 -incomig call
                      if (r->item_type==0x56)  loc->type|=0x04*(*((short*)r->data));  //not answered 
                      if (r->item_type==0x57)  loc->type|=0x08*(*((short*)r->data));  //conected by service  suzh as mts and wrong number 
                      if (r->item_type==0x58)  loc->type|=0x10*(*((short*)r->data));  // ??? rejected
                      if (r->item_type==0x59)  loc->type|=0x20*(*((short*)r->data));  //all side connected
                      if (r->item_type==0x5a)  loc->type|=0x40*(*((short*)r->data));
                                                                                                        //06 -07 missed calls
                      break;
                    
                  };
                }
		i++; //next record
	      }
              //all readed
              LockSched();
              m+=PutRec(loc);
              UnlockSched();
	      FreeUnpackABentry(&ur,mfree_adr());
                 LockSched();
                   RecountMenu(NULL); // once it <adam@lapdoog.doogie.org> apdeititsya 
              UnlockSched();
            }
	
	  }
       
//          rec++;
          rec--;          //cheat 
        }  
//	while(rec<MAX_RECORDS); 
	while(rec>0);        // cheat 
      }
      else
      {
	fclose(fin,&ul);
      }
     mfree(buffer) ;
    }
//    RecountMenu(NULL);
}
///end of parsing
    FreeWS(tel)  ;
#ifdef DEMON
  ShowMSG(1,(int)"CallRecs cached");
#endif
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
  csm->gui_id=  create_contactlist_menu();
  
#endif  
//  maincsm=

  
//  SUBPROC((void*)  ReadCal);
//  ReadCal();    
  
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
  }
 if (msg->msg==MSG_CSM_DESTROYED)
  {
    RefreshGUI();
  }  
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

void FreeList(void){
    for (int i=0;i<3;i++){
    curlist=i;
    int cnt=CountRecord();
    for (int j=cnt-1;j>=0;j--){
      CRECS *t=      FindRecordByN(j);
      mfree(t);
    }
      
  }

}
void maincsm_onclose(CSM_RAM *csm)
{
  contactlist_menu_id=0;
  ///kill lists
  
  SUBPROC((void *)FreeList);  
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Call Records");
}

int maincsm;


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
   i=CountRecord();   

  contactlist_menu_id=CreateMultiLinesMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i);
  RecountMenu(NULL);

//    ShowCallList(2, 0);
//    ShowCallList(1, 0);
//    ShowCallList(0, 0);
    r=0;
  }
  else
  { 
    r=old_ed_onkey(gui,msg);
  }
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
 #define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])  
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg); //Call old handler events 
  
  if (IsGuiOnTop(idlegui_id)) //If IdleGui at the top 
  {
    GUI *igui=GetTopGUI();
    if (igui) //And it exists   and not in the draft
    {
      DoSplices(igui);
    }
  }
  return(csm_result);
}

#endif

int main(void)
{  
  /*
  #pragma pack(1)
  struct {
#ifdef NEWSGOLD
    long dummy1; //62 33 dc 05
    short len;  //!!!!! HZ SGOLD FOR POLE IS IT OR NOT 
    char bitmap[MAX_RECORDS/8];
#else
    long dummy1; // POSSIBLE ON HERE VHODIT there should be two shota otherwise would have to search Urwin 
    char bitmap[MAX_RECORDS/8];    
#endif    
  } ABmain;
#pragma pack()
  char s[256];
  sprintf (s,"%d",sizeof (ABmain));
  
  ShowMSG(1,(int)s);
  return 0;
  */
  InitConfig();

  S_ICONS[0]=(int)str1;
  S_ICONS[1]=(int)str2;
  S_ICONS[2]=GetPicNByUnicodeSymbol(USR_MOBILE); 
  S_ICONS[6]=S_ICONS[2];  
  S_ICONS[3]=(int)str3;
  S_ICONS[4]=(int)str4;
  S_ICONS[5]=(int)str5;

  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
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
  // as if it correctly then removed? 

#else
  maincsm=CreateCSM(&MAINCSM.maincsm,dummy,0);  
#endif  


  UnlockSched();
#ifdef ELKA  
  SUBPROC((void*)  ReadCal);
#else
  ReadCal();
#endif  
  return 0;
}
