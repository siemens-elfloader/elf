#include "E:\ARM\swilib.h"
#include "xtask.h"

int x1=3;
int y1=46;
int y2=46;
int h=14;
int ssize;// ((maxpos+1)*h)*/
int ww,hh;

extern const char BM1NAME[32];
extern const char BM1FILE[128];
extern const char BM2NAME[32];
extern const char BM2FILE[128];
extern const char BM3NAME[32];
extern const char BM3FILE[128];
extern const char BM4NAME[32];
extern const char BM4FILE[128];
extern const char BM5NAME[32];
extern const char BM5FILE[128];
extern const char BM6NAME[32];
extern const char BM6FILE[128];
extern const char BM7NAME[32];
extern const char BM7FILE[128];
extern const char BM8NAME[32];
extern const char BM8FILE[128];
extern const char BM9NAME[32];
extern const char BM9FILE[128];
extern const char BMANAME[32];
extern const char BMAFILE[128];

extern int gfpe;
extern int mode;
extern CSM_RAM *under_idle;

char const *bmname[10];
char const *bmfile[10];
char *palette[24];

const CSM_DESC maincsm;

tkeymessages *KeyMsgList;
tredrawmessages *RedrawMsgList;


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
  //  int i1;
}MAIN_GUI;

int my_csm_id;

void * volatile selcsm;

NAMELIST * nltop;
NAMELIST * nlbot;
NAMELIST * item;

char ttime[5];
char *csm_text;
const char percent_t[]="%t";

tlistbox *list1;//main
tlistbox *list2;//mainmenu
tlistbox *list3;//submenu
tlistbox *list4;//contextmenu
tlistbox *filelist1;
tmsgbox *msg1;

char fname[128];

#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
#define RGB8(R,G,B) (B+(G<<2)+(R<<5))

unsigned char img1_bmp[14] = {
	0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x30, 0xFF
};
IMGHDR gimg = {27,30,0x85,(char*)&img1_bmp};

void DrwStr(WSHDR *wshdr, int x, int y, int w, int h, int font, int text_flag, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,w,h);
  SetPropTo_Obj1(&drwobj,&rc,0,wshdr,font,text_flag);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void SwapCSMS(void);
void AddItem(tlistbox *llist, char const *s, void *p);
void ClrItems(tlistbox *llist);

void AddRedrawProc(void *p)
{
  LockSched();
  tredrawmessages *msg=malloc(sizeof(tredrawmessages));
  msg->next=0;
  msg->RedrawProc=(void(*)())p;
  if (RedrawMsgList==0) {
    RedrawMsgList=msg;
  } else {
    tredrawmessages *msg2=RedrawMsgList;
    while (msg2->next){
      msg2=msg2->next;
    }
    msg2->next=msg;
  }
  UnlockSched();
}

void DeleteRedrawProc(void *p)
{
  LockSched();
  tredrawmessages *msg;
  tredrawmessages *msg2=RedrawMsgList;
  if ((void *)msg2->RedrawProc==p) {
    RedrawMsgList=msg2->next;
    mfree(msg2);
    msg2=0;
  } else {
    while (msg2->next){
      msg=msg2->next;
      if ((void *)msg->RedrawProc==p) {
        msg2->next=msg->next;
        mfree(msg);
        msg=0;
        break;
      }
      msg2=msg;
    }
  }
  UnlockSched();
}

void AddKeyProc(void *p)
{
  LockSched();
  tkeymessages *msg=malloc(sizeof(tkeymessages));
  msg->next=KeyMsgList;
  msg->KeyPressProc=(int(*)(int,int))p;
  KeyMsgList=msg;
  UnlockSched();
}

void DeleteKeyProc(void *p)
{
  LockSched();
  tkeymessages *msg;
  tkeymessages *msg2=KeyMsgList;
  if ((void *)msg2->KeyPressProc==p) {
    KeyMsgList=msg2->next;
    mfree(msg2);
    msg2=0;
  } else {
    while (msg2->next){
      msg=msg2->next;
      if ((void *)msg->KeyPressProc==p) {
        msg2->next=msg->next;
        mfree(msg);
        msg=0;
        break;
      }
    }
  }
  UnlockSched();
}

void DrawListBox(tlistbox *llist, timage *pic, timage *selpic)
{
  int i,k1,k2;
  int vcur;
  int ppos;
  int size;
  NAMELIST *item;
  timage *ppic=pic;
  timage *sppic=selpic;
  i=0;
  item=llist->start;
  int sbfl=0;
  while(item)
  {
    i++;
    item=item->next;
  }
  size=llist->ssize;
  if (i>(llist->cline+1))sbfl=1;
  int sb_cor;
  if (i)
  {
    //if (llist->cursor>=i) llist->cursor=i-1;
    if (llist->cursor==-1) llist->cursor=i-1;
    if (llist->cursor>=i) llist->cursor=0;
    if ((llist->fatr) & 2) {
      size=(llist->ssize/i);
      sb_cor=i-(llist->heigh-llist->y-size*i);
      if (sb_cor<0) sb_cor=0;
      if (size>llist->ssize) size=llist->ssize;
    }
  }
  else llist->cursor=0;
  item=llist->start;
  if (llist->cursor>llist->pos+llist->cline) 
  {
      llist->pos=llist->cursor-llist->cline;
  }
  else if (llist->cursor<llist->pos)
  {
      llist->pos=llist->cursor;
  }
  vcur=llist->cursor-llist->pos;
  ppos=llist->pos;
  while(ppos)
  {
    if (item) item=item->next;
    if ((llist->fatr) & 4){
      if (ppic) ppic=ppic->next;
      if (sppic) sppic=sppic->next;
    }
    ppos--;
  }


  int si=0;
  if (((llist->fatr) & 2) && (sbfl)){
    int ccr=0;
    si=3;
    if (llist->cursor>=sb_cor) ccr=llist->cursor-sb_cor+1;
    DrawRoundedFrame(llist->width-si,llist->y,llist->width,llist->heigh,0,0,0,
			palette[llist->bc],
			palette[22]);
    DrawRoundedFrame(llist->width+1-si,
                     llist->y+size*llist->cursor+ccr,
                     llist->width+2-si,
                     llist->y+size*(llist->cursor+1)+ccr-1,
                        0,0,0,palette[2],palette[2]);  
  }
  DrawRoundedFrame(llist->x,llist->y,llist->width-si,llist->heigh,0,0,0,
			palette[llist->bc],
			palette[llist->fc]);
  i=0;
  do
  {
    if (item)
    {
      if (item->name)
      {
	k1=llist->font;
        k2=llist->stfc;
        if (i==vcur)
	{
	  llist->selected=item;
          DrawRoundedFrame(llist->x,llist->y+llist->hline*i,llist->width-si,llist->y+llist->hline*(i+1),0,0,0,
			palette[llist->sfc],
			palette[llist->sbc]);
          //k1++;
          k2--;
 	}
        if ((llist->fatr) & 1) {
          if ((((int)item->p) & 0x80000400)==0x400) k2=(((int)item->p) & 0xff0000)>>16;
        }
        int pp=(llist->hline-llist->hfont)>>1;
	/*DrawString(item->name,llist->x+2+llist->tpos,llist->y+2+llist->hline*i+pp,
                   llist->width-3-si,llist->y+llist->hline-1+llist->hline*i-pp,
                   k1,0x80,palette[k2],palette[llist->stbc]);
	*/
        DrwStr(item->name,llist->x+2+llist->tpos,llist->y+2+llist->hline*i+pp,
                   (llist->width-3-si)-(llist->x+2+llist->tpos),llist->hline,
                   k1,0x80,palette[k2],palette[llist->stbc]);
        if ((llist->fatr) & 1) {
          if ((((int)item->p) & 0x80000200)==0x200)
              DrawRoundedFrame(llist->x+4,llist->y+llist->hline+llist->hline*i,
                               llist->width-4-si,llist->y+llist->hline+llist->hline*i,0,0,0,
		               palette[llist->bc],
                               palette[llist->bc]);
          WSHDR *ws=AllocWS(10);
          wsprintf(ws,percent_t,">>");
          if ((((int)item->p) & 0x80000100)==0x100)
        	/*DrawString(ws,llist->width-15,llist->y+2+llist->hline*i+pp,
                   llist->width-3-si,llist->y+llist->hline-1+llist->hline*i-pp,
                   k1,0x80,palette[k2],palette[llist->stbc]);
                */
                DrwStr(ws,llist->width-19,llist->y+2+llist->hline*i+pp,
                   (llist->width-3-si)-(llist->width-19),llist->hline,
                   k1,0x80,palette[k2],palette[llist->stbc]);
          FreeWS(ws);
        }
        if ((llist->fatr) & 4) {
          IMGHDR img1;
          if (i==vcur){
            if (sppic){
              memcpy(&img1,&(selpic->image),sizeof(IMGHDR));
              img1.bitmap=(char*)sppic->image.bitmap;
            }
          } else {
            if (ppic){
              memcpy(&img1,&(pic->image),sizeof(IMGHDR));
              img1.bitmap=(char*)ppic->image.bitmap;
            }
            DrwImg((IMGHDR *)&gimg,llist->x+1,llist->y+1+llist->hline*i,palette[0],palette[1]);
          }
          if (img1.bitmap) {
            int ycor=(llist->hline-img1.h);
            if (ycor<0)ycor=0;
            else ycor=ycor>>1;
            int xcor=(llist->hline-img1.w);
            if (xcor<0)xcor=0;
            else xcor=xcor>>1;
            DrwImg((IMGHDR *)&img1,llist->x+xcor,llist->y+ycor+1+llist->hline*i,palette[0],palette[1]);
          }
          DrawRoundedFrame(llist->x+llist->tpos,llist->y+llist->hline*i,llist->x+llist->tpos,llist->y+llist->hline*(i+1),0,0,0,
			palette[1],
			palette[1]);
          ppic=ppic->next;
          sppic=sppic->next;
        }
      }
      item=item->next;
    }
    i++;
  }
  while(i<=llist->cline);
}

GBSTMR timer; 
int tt;
int kkey;
int *curs;
tlistbox *klist;

void kbdtimer(void){ 
   switch(kkey)
   {
      case UP_BUTTON:
        (*curs)--;
        break;
      case DOWN_BUTTON:
        (*curs)++;
        break;
   }
   DirectRedrawGUI();
   GBS_StartTimerProc(&timer,30,kbdtimer); 
}

int KeyPressListBox(tlistbox *llist, int action, int key)
{
      if (tt) GBS_StopTimer(&timer);
      if (action==LONG_PRESS){
        tt=1;
        kkey=key;
        curs=&llist->cursor;
        GBS_StartTimerProc(&timer,30,kbdtimer);  
      }
      if (action==KEY_UP){
        tt=0;
      }
      if (action==KEY_DOWN){
        tt=0;
        switch(key)
        {
         case RED_BUTTON:
          return(1); 
         case UP_BUTTON:
          //if (llist->cursor) 
           llist->cursor--;
          break;
         case DOWN_BUTTON:
          llist->cursor++;
          break;
        }
      }
  return 0;
}

void DrawMsgBox(tmsgbox *mmsg)
{
  DrawRoundedFrame(mmsg->x,mmsg->y,mmsg->width,mmsg->heigh,0,0,0,
			palette[mmsg->fc],
			palette[mmsg->bc]);
  DrawRoundedFrame(mmsg->x+2,mmsg->y+2,mmsg->width-2,mmsg->heigh-2,0,0,0,
			palette[mmsg->fc],
			palette[mmsg->bc]);
  DrawRoundedFrame(mmsg->x+2,mmsg->y+2,mmsg->width-2,mmsg->hline+mmsg->y+2,0,0,0,
			palette[mmsg->fc],
			palette[mmsg->cbc]);
  WSHDR *ws=AllocWS(512);
  wsprintf(ws,percent_t,mmsg->caption);
  /*DrawString(ws,mmsg->x+7,mmsg->y+5,mmsg->width-7,mmsg->y+2+mmsg->hline,
             mmsg->cfont,mmsg->cfatr,palette[mmsg->tfc],palette[mmsg->cbc]);
  */
  DrwStr(ws,mmsg->x+7,mmsg->y+5,mmsg->width-mmsg->x-14,mmsg->hline,
             mmsg->cfont,mmsg->cfatr,palette[mmsg->tfc],palette[mmsg->cbc]);

  wsprintf(ws,percent_t,mmsg->text);
  /*DrawString(ws,mmsg->x+7,mmsg->y+mmsg->hline+6,mmsg->width-7,mmsg->heigh-6,
             mmsg->font,mmsg->fatr,palette[mmsg->tfc],palette[mmsg->bc]);
  */
  DrwStr(ws,mmsg->x+7,mmsg->y+mmsg->hline+6,mmsg->width-mmsg->x-14,mmsg->heigh-13-mmsg->x,
             mmsg->font,mmsg->fatr,palette[mmsg->tfc],palette[mmsg->bc]);
  FreeWS(ws);
}

int KeyPressMsgBox(tmsgbox *mmsg, int action, int key)
{
   if (action==KEY_DOWN){
     switch(key) {
     case RED_BUTTON:
        return(1);
     }
   }
   return 0;
}

int RunBM(int bm)
{
  const char *s=bmfile[bm];
  if (s)
  {
    if (strlen(s))
    {
      if (strstr(s,":")){
        WSHDR *ws;
        ws=AllocWS(150);
        wsprintf(ws,percent_t,s);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
        return(1);
      }
      void *adr=0;
      if(gfpe) adr=GetFunctionPointer((char *)s);
      if (adr!=0) SUBPROC((void*)adr);
      return(1);
    }
  }
  return(2);
}

void list3destroy(void);

int RunBM2(int i){
  if ((i>=1)&&(i<=10))
  {
    return RunBM(i-1);
  }
  return 2;
}

void submenu2();

int list3keypress(int action, int key)
{
  KeyPressListBox(list3,action,key);
  if (action==KEY_DOWN) {
    if ((key>='0')&&(key<='9'))
    {
      return RunBM(key-'0');
    } else {
    switch(key){
    case ENTER_BUTTON:
      if (((int)list3->selected->p) & 0x800) break;
      return RunBM2(((int)list3->selected->p) & 0xFF);
    case RIGHT_SOFT:
      break;//return(1);
    case RIGHT_BUTTON:
      submenu2();
      break;
    case LEFT_BUTTON:
    case RED_BUTTON:
      list3destroy();
      break;//return(1);
    }
    }
  }
  return 2;
}

void list3redraw(void)
{
  DrawListBox(list3,0,0);
}

void list3destroy(void)
{
  DeleteKeyProc((void *)&list3keypress);
  DeleteRedrawProc((void *)&list3redraw);
  ClrItems(list3);
  mfree(list3);
  list3=0;
}

void list3create(void)
{
  list3=malloc(sizeof(tlistbox));


  list3->width=127;
  list3->hline=14;
  list3->hfont=14;
  list3->cline=9;
  if (hh<140) list3->cline=6;
  list3->font=SMALL_FONT;
  list3->stbc=23;
  list3->sbc=3;
  list3->x=40;
  list3->stfc=1;
  list3->sfc=1;
  list3->fatr=3;  
  list3->bc=1;
  list3->fc=0;
  list3->cursor=0;
  list3->pos=0;
  list3->tpos=0;
  list3->start=0;
  list3->finish=0;
  list3->ssize=((list3->cline+1)*list3->hline);
  list3->y=18;
  list3->heigh=list3->y+list3->ssize;//165;
  int i=10;
  while (i>0) {
    int j=0;
    if (strstr(bmname[i-1],"<")) j=0x00150C00;
    AddItem(list3,bmname[i-1],(void *)(i|j));
    i--;
  }
  AddKeyProc((void *)&list3keypress);
  AddRedrawProc((void *)&list3redraw);
}

void submenu1(void){
  list3create();
}

void SortItems(tlistbox *llist,int flag);

char utf2win(char a, char b){
  if (a==0xd0) {
    if (b==0x81) return 'Ё';
    return (b+0x30);
  } else if (a==0xd1){
    if (b==0x91) return 'ё';
    return (b+0x70);
  } 
  return b;
}

char curdir[128];

void ChDir(int cpath, tlistbox *llist){
  DIR_ENTRY de;
  NAMELIST *curr;
  char name[128];
  unsigned int err;
  int i=0;
  int j;
  if (cpath==0) {
    ClrItems(llist);
    if (isdir("4:\\",&err))  AddItem(filelist1,"4:\\",(void *)(0x102));
    AddItem(filelist1,"0:\\",(void *)(0x101));
    strcpy(curdir,"?");
    return;
  }
  else if (cpath==0xff) {
      i=strlen(curdir);
      i--;
      while (i>1) {
        i--;
        if (curdir[i]=='\\'){
          curdir[i+1]=0; 
          break;
        }
      }
      if (i<2){
       ClrItems(llist);
       if (isdir("4:\\",&err))  AddItem(filelist1,"4:\\",(void *)(0x102));
       AddItem(filelist1,"0:\\",(void *)(0x101));
       strcpy(curdir,"?");
       return;
      }
  } 
  else {
    name[0]=0;
    curr=llist->start;
    while (curr!=0) {
      if ((((int)curr->p)&0xff)==cpath){
        i=wstrlen(curr->name);//(int)curr->name->wsbody[0];
        j=0;
        while (j<i){
          name[j]=(char)curr->name->wsbody[j+1];
          j++;
        }
        name[j]=0;
        if (strlen(curdir)==1) strcpy(curdir,name);
        else {
          strcat(curdir,name);
          strcat(curdir,"\\");
        }
        break;
      }
      curr=curr->next;
    }
  }
  strcpy(name,curdir);
  strcat(name,"*.*");
  ClrItems(llist);
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,percent_t,name);
  ws_2str(ws,name,128);
  FreeWS(ws);
  i=1;
  if (FindFirstFile(&de,name,&err)) {
    do {
      strcpy(name,curdir);
      strcat(name,de.file_name);
      j=0;
      if (isdir(name,&err)) j=0x100;
      if (de.file_name[0]==0x1f) {
        int i1=1;
        int j1=0;
        while (de.file_name[i1]!=0){
          if ((de.file_name[i1]==0xd0)||(de.file_name[i1]==0xd1)){
             de.file_name[j1]=utf2win(de.file_name[i1],de.file_name[i1+1]);
             i1++;
          } else de.file_name[j1]=de.file_name[i1];
          i1++;
          j1++;
        }
        de.file_name[j1]=0;
      }
      AddItem(filelist1,de.file_name,(void *)(i|j));
      i++;
    } while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  SortItems(llist,1);
  //if (strcmp(droot,curdir)!=0) 
  AddItem(llist," ..",(void *)(0x1ff));
}

void filelist1destroy(void);
      
int filelist1keypress(int action, int key)
{
  KeyPressListBox(filelist1,action,key);
  if (action==KEY_DOWN) {
    switch(key){
    case LEFT_BUTTON:
      if ((((int)filelist1->selected->p) & 0x100) !=0) ChDir(0xff,filelist1);
      filelist1->cursor=0;
      break;
    case RIGHT_BUTTON:
    case ENTER_BUTTON:
      if ((((int)filelist1->selected->p) & 0x100) !=0){
        ChDir((((int)filelist1->selected->p) & 0xff),filelist1);
        filelist1->cursor=0;
        break;
      } else {
        char name[128];
        int j1=0;
        ws_2str(filelist1->selected->name,name,128);
        strcpy(fname,curdir);
        int i1=1;
        j1=0;
        if (name[0]==0x1f) {
          while (name[i1]!=0){
            name[j1]=utf2win(name[i1],name[i1+1]);
            i1=i1+2;
            j1++;
          }
          name[j1]=0;
        }
        strcat(fname,name);
        if (filelist1->fatr & 0x10){
          int i=(((int)list3->selected->p) & 0xFF)-1;
          strcpy((char*)bmfile[i],fname);
          strcpy((char*)bmname[i],name);
          list3destroy();
          extern void SaveConfig();
          SUBPROC((void *)SaveConfig);
        } else {
          if (strlen(fname)) {
            WSHDR *ws;
            ws=AllocWS(150);
            wsprintf(ws,percent_t,fname);
            ExecuteFile(ws,0,0);
            FreeWS(ws);
            return(1);          
          }
        }
      }
    case RED_BUTTON:
      filelist1destroy();
      break;//return(1);
    }
  }
  return 2;
}

void filelist1redraw(void)
{
  DrawListBox(filelist1,0,0);
}

void filelist1destroy(void)
{
  DeleteKeyProc((void *)&filelist1keypress);
  DeleteRedrawProc((void *)&filelist1redraw);
  ClrItems(filelist1);
  mfree(filelist1);
  filelist1=0;
}

void filelist1create(void)
{
  filelist1=malloc(sizeof(tlistbox));
  fname[0]=0;
  filelist1->x=10;
  filelist1->width=123;
  filelist1->hline=14;
  filelist1->hfont=14;
  filelist1->font=SMALL_FONT;
  filelist1->cline=10;
  if (hh<140) {
    filelist1->cline=7;
  }
  filelist1->stbc=23;
  filelist1->sbc=3;
  filelist1->stfc=1;
  filelist1->sfc=1;
  filelist1->fatr=3;  
  filelist1->bc=1;
  filelist1->fc=0;
  filelist1->cursor=0;
  filelist1->pos=0;
  filelist1->tpos=0;
  filelist1->start=0;
  filelist1->finish=0;
  filelist1->ssize=((filelist1->cline+1)*filelist1->hline);
  filelist1->y=8;
  filelist1->heigh=filelist1->y+filelist1->ssize;//165;
  ChDir(0,filelist1);
  AddKeyProc((void *)&filelist1keypress);
  AddRedrawProc((void *)&filelist1redraw);
}

void frun(void){
  filelist1create();
}

void msg1destroy(void);
      
int msg1keypress(int action, int key)
{
  KeyPressMsgBox(msg1,action,key);
  if (action==KEY_DOWN) {
    msg1destroy();
  }
  return 2;
}

void msg1redraw(void)
{
  DrawMsgBox(msg1);
}

void msg1destroy(void)
{
  DeleteKeyProc((void *)&msg1keypress);
  DeleteRedrawProc((void *)&msg1redraw);
  mfree(msg1->text);
  mfree(msg1->caption);
  mfree(msg1);
  msg1=0;
}

msg1create(){
  msg1=malloc(sizeof(tmsgbox));
  msg1->text=malloc(256);
  msg1->caption=malloc(40);
  strcpy(msg1->caption,"xtask 1.1");
  strcpy(msg1->text,"GENERAL IDEA:\n(c) by Rst7/CBSIE\n\nMOD & EXTENSIONS:\n by MasterMind");
  msg1->y=47;
  if(hh<140) msg1->y=20;
  msg1->width=126;
  msg1->x=4;
  msg1->bc=9;
  msg1->fc=1;
  msg1->cbc=10;
  msg1->tfc=2;
  msg1->font=SMALL_FONT+1;
  msg1->fatr=2;
  msg1->cfont=8;
  msg1->cfatr=2;
  msg1->hline=16;
  msg1->heigh=msg1->y+88;//135;
  AddKeyProc((void *)&msg1keypress);
  AddRedrawProc((void *)&msg1redraw);
}

void showmsg1(){
  msg1create();
}

void list2destroy(void);

int list2keypress(int action, int key)
{
  KeyPressListBox(list2,action,key);
  if (action==KEY_DOWN) {
    switch(key){
    case ENTER_BUTTON:
    case RIGHT_BUTTON:
      if (((int)list2->selected->p) & 0x800) break;
      switch(((int)list2->selected->p) & 0xFF){
      case 1:
        selcsm=FindCSMbyID(CSM_root()->idle_id);
        SwapCSMS();
        return(1);
      case 3:
        submenu1();
        return 2;
      case 5:
        frun();
        return 2;
      case 6:
        SwapCSMS();
        GBS_SendMessage(MMI_CEPID,LONG_PRESS,RED_BUTTON);
        return 1;
      case 7:
        SwitchPhoneOff();
        return 1;
      case 8:
        showmsg1();
        return 2;
      }
    case LEFT_BUTTON:
    case RED_BUTTON:
      list2destroy();
      return 2;
    }
  }
  return 2;
}

void list2redraw(void)
{
  DrawListBox(list2,0,0);
  WSHDR *ws=AllocWS(40);

  wsprintf(ws,percent_t," Меню ");
  DrawRoundedFrame(5,hh-19,35,hh-3,0,0,0,
			palette[list2->bc],
			palette[list2->fc]);
  DrawRoundedFrame(6,hh-19,34,hh-4,0,0,0,
			palette[list2->fc],
			palette[list2->fc]);
  //DrawString(ws,2,hh-14,55,hh-3,7,0x80,palette[list2->stfc],palette[list2->stbc]);  
  DrwStr(ws,2,hh-14,53,11,7,0x80,palette[list2->stfc],palette[list2->stbc]);  
  FreeWS(ws);
}

void list2destroy(void)
{
  DeleteKeyProc((void *)&list2keypress);
  DeleteRedrawProc((void *)&list2redraw);
  ClrItems(list2);
  mfree(list2);
  list2=0;
}

void list2create(void)
{
  list2=malloc(sizeof(tlistbox));
  list2->width=123;
  list2->hline=18;
  list2->hfont=14;
  list2->font=SMALL_FONT;
  list2->cline=5;
  list2->stbc=23;
  list2->sbc=3;
  list2->x=1;
  list2->stfc=1;
  list2->sfc=1;
  list2->fatr=1;  
  list2->bc=1;
  list2->fc=0;
  list2->cursor=0;
  list2->pos=0;
  list2->tpos=0;
  list2->start=0;
  list2->finish=0;
  list2->ssize=((list2->cline+1)*list2->hline);
  list2->heigh=hh-19;
  list2->y=list2->heigh-list2->ssize-1;
  AddItem(list2,"Выключить телефон",(void *)0x00000007);
  AddItem(list2,"Закрыть все",(void *)0x00150C06);
  AddItem(list2,"Выполнить...",(void *)0x00000005);
  //AddItem(list2,"Выполнить ф-цию",(void *)0x00000004);
  AddItem(list2,"Закладки",(void *)0x00000103);
  //AddItem(list2,"Native",(void *)0x00000002);
  AddItem(list2,"IDLE",(void *)0x00000001);
  AddItem(list2,"О программе...",(void *)0x00000208);
  AddKeyProc((void *)&list2keypress);
  AddRedrawProc((void *)&list2redraw);
}

void mmenu(void)
{
  list2create();
}

void list4destroy(void);

int list4keypress(int action, int key)
{
  KeyPressListBox(list4,action,key);
  if (action==KEY_DOWN) {
    switch(key){
    case ENTER_BUTTON:
    case RIGHT_BUTTON:
      switch(((int)list4->selected->p) & 0xFF){
      case 1: 
        frun();
        filelist1->fatr=0x11;
      }
    case LEFT_BUTTON:
    case RED_BUTTON:
      list4destroy();
      break;//return(1);
    }
  }
  return 2;
}

void list4redraw(void)
{
  DrawListBox(list4,0,0);
}

void list4destroy(void)
{
  DeleteKeyProc((void *)&list4keypress);
  DeleteRedrawProc((void *)&list4redraw);
  ClrItems(list4);
  mfree(list4);
  list4=0;
}

void list4create(void)
{
  list4=malloc(sizeof(tlistbox));

  list4->hline=14;
  list4->hfont=14;
  list4->font=SMALL_FONT;
  list4->cline=0;
  list4->y=list3->y+list3->cursor*list3->hline-2+6;
  list4->heigh=list4->y+list4->hline*list4->cline+1;
  list4->x=list3->x+10;
  list4->width=list4->x+75;
  list4->stbc=23;
  list4->sbc=3;
  list4->stfc=1;
  list4->sfc=1;
  list4->fatr=1;  
  list4->bc=1;
  list4->fc=0;
  list4->cursor=0;
  list4->pos=0;
  list4->tpos=0;
  list4->start=0;
  list4->finish=0;
  list4->ssize=((list4->cline+1)*list4->hline);
  AddItem(list4,"Изменить...",(void *)0x00000001);
  AddKeyProc((void *)&list4keypress);
  AddRedrawProc((void *)&list4redraw);
}

void submenu2(void){
  list4create();
}

void xmnu(void){
  extern void xmenu(void);
  xmenu();
}

int list1keypress(int action, int key)
{
  selcsm=list1->selected->p;
  KeyPressListBox(list1,action,key);
  if (action==KEY_DOWN) {
    if ((key>='0')&&(key<='9'))
    {
      return RunBM(key-'0');
    } else {
    switch(key){
    case LEFT_SOFT:
      mmenu();
      break;
    case '*':
    case LEFT_BUTTON:
    case RIGHT_BUTTON:
      xmnu();
      break;
    case GREEN_BUTTON:  
      selcsm=FindCSMbyID(CSM_root()->idle_id);
    case ENTER_BUTTON:
      SwapCSMS();
    case RIGHT_SOFT:
      return(1);
    }
    }
  }
  return 0;
}

int GetNumberOfDialogs(void);

void list1redraw(void)
{
  
  WSHDR *ws;  
  ws=AllocWS(40);
  DrawRoundedFrame(0,0,ww,hh,0,0,0,
			palette[0],
			palette[20]);
  DrawRoundedFrame(0,0,ww,19,0,0,0,
			palette[0],
			palette[15]);
  DrawRoundedFrame(0,0,37,19,0,0,0,
			palette[0],
			palette[15]);
  DrawRoundedFrame(0,hh-19,ww,hh,0,0,0,
			palette[0],
			palette[15]);

  wsprintf(ws,"%t",ttime);//"xtask");
  //DrawString(ws,4,4,ww-3,20,7,1,palette[0],palette[23]);
  DrwStr(ws,4,4,ww-7,16,SMALL_FONT,1,palette[0],palette[23]);
  wsprintf(ws,"%t%d","Диалогов: ",GetNumberOfDialogs());
  //DrawString(ws,45,4,ww-3,20,7,1,palette[0],palette[23]);
  DrwStr(ws,42,4,ww-48,16,SMALL_FONT,1,palette[0],palette[23]);

  wsprintf(ws,percent_t," Меню     < * >    Назад ");
  //DrawString(ws,2,hh-15,ww-2,hh-2,7,0x80,palette[0],palette[23]);
  DrwStr(ws,2,hh-15,ww-4,13,SMALL_FONT,0x80,palette[0],palette[23]);
  FreeWS(ws);
  DrawListBox(list1,0,0);
}

void list1destroy(void)
{
  DeleteKeyProc((void *)&list1keypress);
  DeleteRedrawProc((void *)&list1redraw);
  mfree(list1);
  list1=0;
}

void list1create(void)
{
  list1=malloc(sizeof(tlistbox));

  list1->x=x1-1;
  list1->y=30;//46;
  list1->width=list1->x+127;
  list1->hline=14;
  list1->hfont=14;
  list1->font=SMALL_FONT;
  list1->cline=7;
  if (hh<140) {
    list1->cline=4;
  }
  list1->bc=15;
  list1->fc=22;
  list1->stbc=23;
  list1->sbc=3;
  list1->stfc=1;
  list1->sfc=1;
  list1->cursor=0;
  list1->pos=0;
  list1->tpos=0;
  list1->start=0;
  list1->finish=0;
  list1->selected=0;
  list1->fatr=2;
  list1->ssize=((list1->cline+1)*list1->hline);
  list1->heigh=list1->y+1+list1->ssize;
  AddKeyProc((void *)&list1keypress);
  AddRedrawProc((void *)&list1redraw);
}

void ClearNL(tlistbox *llist)
{
  LockSched();
  NAMELIST *nl;
  nl=llist->start;
  llist->start=0;
  llist->finish=0;
  UnlockSched();
  while(nl)
  {
    NAMELIST *p=nl;
    FreeWS(nl->name);
    nl=p->next;
    if(p!=0)mfree(p);
    p=0;
  }
}

void AddNL(tlistbox *llist, WSHDR *ws, void *p)
{
  NAMELIST *nnl=malloc(sizeof(NAMELIST));
  nnl->name=ws;
  nnl->next=0;
  LockSched();
  if (!llist->start)
  {
    llist->start=llist->finish=nnl;
  }
  else
  {
    nnl->next=llist->start;
    llist->start=nnl;
  }
  llist->start->p=p;
  UnlockSched();
}


void AddItem(tlistbox *llist, char const *s, void *p)
{
  WSHDR *ws;  
  ws=AllocWS(40);
  wsprintf(ws,percent_t,s);
  AddNL(llist,ws,p);
}

int strcmp2(WSHDR* s1, WSHDR* s2){
  int i,ii,jj;
  ii=wstrlen(s1);
  jj=wstrlen(s2);
  i=jj<ii?jj:ii;
  //i=(i)+2;
  int j=1;
  while (j<=i) {
    unsigned short a=s1->wsbody[j];
    if (a<128) a = a & 0xdf;
    unsigned short b=s2->wsbody[j];
    if (b<128) b = b & 0xdf;

    if (a>b) return 1;
    if (a<b) return -1;    
    j++;
  }
  if(jj<ii) return 1;
  return 0;
}

void SortItems(tlistbox *llist, int flag)
{

  NAMELIST *curr;
  NAMELIST *pred;
  NAMELIST *last=0;
  NAMELIST *next;

  while (last!=llist->start) {
    int i=0;
    pred=llist->start;
    curr=llist->start;
    while (curr!=last) {
      next=curr->next;
      if (next==last) break;
      int cm=strcmp2(curr->name,next->name);
      if ((cm==1)&&(((int)curr->p & 0x100)!=0)&&(((int)next->p & 0x100)==0))cm=-1;
      if ((cm!=1)&&(((int)curr->p & 0x100)==0)&&(((int)next->p & 0x100)!=0))cm=1;
      if (cm==1){
        if (curr==llist->start) {
          llist->start=next;
          pred=llist->start;
        }
        else pred->next=next;
        curr->next=next->next;
        next->next=curr;
      } else 
        curr=curr->next;
      if (i>0) pred=pred->next;
      else 
        i++;
    }
    last=curr;//pred;
  }
}

void ClrItems(tlistbox *llist)
{
  ClearNL(llist);
}

char *find_name(CSM_RAM *csm)
{
  char s[40];
  char *p;
  static char u[40];

  CSM_DESC *desc=csm->constr;

  sprintf(s,"%08X ",desc);
  p=strstr(csm_text,s);
  if (p)
  {
    return(p+9);
  }
  else
  {
    sprintf(u,"Unknown %08X!",desc);
    return(u);
  }
}
///////////////////////////////////////////////////////////////////////////////
int GetNumberOfDialogs(void)
{
  int count=0;
  CSM_RAM *icsm=under_idle->next; //Начало карусели
  if (list1) ClearNL(list1);
  WSHDR *ws;

  void *ircsm=FindCSMbyID(CSM_root()->idle_id);

  do
  {
    if (icsm==ircsm)
    {
      if (list1) 
      {
        AddItem(list1,"IDLE Screen",icsm);
      }
      count++;
    }
    else
    {
      if (icsm->constr!=&maincsm)
      {
	WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
	char *s;
	if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
	{
	  ws=AllocWS(40);
	  wstrcpy(ws,tws);
          if (list1) 
          {
            AddNL(list1,ws,icsm);
          }
	  count++;
	}
	else
	{
	  s=find_name(icsm);
	  if (strncmp(s,"!SKIP!",6))
	  {
	    ws=AllocWS(40);
	    wsprintf(ws,percent_t,s);
	    if (list1)
            {
              AddNL(list1,ws,icsm);
            }
	    count++;
	  }
	}
      }
    }
  }
  while((icsm=icsm->next));
  return(count);
}

void SwapCSMS(void)
{
  CSM_RAM *icsm; //Нижний CSM
  CSM_RAM *ucsm; //Верхний CSM
  CSM_RAM *wcsm; //Перемещаемый CSM
  extern WSHDR *ws_nogui;

  if (GetNumberOfDialogs()<2) return; //Нечего сворачивать
  if (!selcsm) return;
  do
  {
    icsm=under_idle;
    ucsm=FindCSMbyID(my_csm_id);
    wcsm=(CSM_RAM *)ucsm->prev; //Получаем перемещаемый CSM
    ((CSM_RAM *)(wcsm->prev))->next=ucsm; //CSM перед перемещаемым теперь указывает на верхний CSM
    ucsm->prev=wcsm->prev; //prev верхнего CSM указывает на CSM перед перемещаемым
    //Теперь вставляем в нужное место перемещаемый CSM
    ((CSM_RAM *)(wcsm->next=icsm->next))->prev=wcsm;
    icsm->next=wcsm;
    wcsm->prev=icsm;
  }
  while(ucsm->prev!=selcsm);
  //Теперь рисуем "Нет GUI" на всякий случай
  //DrawRoundedFrame(0,0,131,175,0,0,0,
	//		palette(0),
	//		palette(20));
  //DrawString(ws_nogui,3,70,128,172,1,2,palette(2),palette(23));
}


void method0(MAIN_GUI *data)//redraw
{
  tredrawmessages *msgproc;  
  void (*redrawproc)();

  msgproc=RedrawMsgList;
  while (msgproc) {
    redrawproc=msgproc->RedrawProc; 
    if (redrawproc) (*redrawproc)();
    msgproc=msgproc->next;
  }
}

GBSTMR timetimer; 
TTime ot;

int gettime(int tt){
  TTime t;
  TDate d;
  GetDateTime(&d,&t); 
  int i=0;
  if ((ot.hour!=t.hour)||(ot.min!=t.min)||(tt==1)) {
    sprintf(ttime,"%02d:%02d",t.hour,t.min);
    ot=t;
    i=1;
  }
  return i;
}

void tttimer(void){ 
  if (gettime(0)) DirectRedrawGUI();
  GBS_StartTimerProc(&timetimer,262,tttimer); 
}

//unsigned int exc;

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))//create
{
  int f;
  int sz=0;
  unsigned int ul;
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
    ww=ScreenW()-1;
  hh=ScreenH()-1;

  extern const char csmlist_fname[128];
  gettime(1);
  GBS_StartTimerProc(&timetimer,262,tttimer); 
  if ((f=fopen(csmlist_fname,A_ReadOnly+A_BIN,0,&ul))!=-1)
  {
    sz=lseek(f,0,2,&ul,&ul)+1;
    lseek(f,0,0,&ul,&ul);
    csm_text=malloc(sz);
    zeromem(csm_text,sz);
    fread(f,csm_text,sz,&ul);
    fclose(f,&ul);
  }
  selcsm=0;
  list1=0;
  KeyMsgList=0;
  RedrawMsgList=0;
  if(hh>140){
    gimg.h=27;
    img1_bmp[10]=0x5e;
  }

  list1create();
  data->gui.state=1;
}

extern tlistbox *xmenu1;
extern void xmn1destroy(void);

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  GBS_StopTimer(&timetimer);
  if (list2) list2destroy();
  if (list3) list3destroy();
  if (list4) list4destroy();
  if (filelist1) filelist1destroy();
  if (msg1) msg1destroy();
  if (xmenu1) xmn1destroy();
  list1destroy();
  if (list1) list1destroy();
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  if (csm_text!=0)mfree(csm_text);
  csm_text=0;
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  tkeymessages *msgproc;  
  int (*keyproc)(int action, int key);
  
  msgproc=KeyMsgList;
  while (msgproc) {
    keyproc=msgproc->KeyPressProc; 
    if (keyproc) {
      int i=(*keyproc)(msg->gbsmsg->msg, msg->gbsmsg->submess);
      if (i==1) return 1;
      else if (i==2) break;
    }
    msgproc=msgproc->next;
  }
  DirectRedrawGUI();
  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);  
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
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
  csm->csm.state=1;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
  extern void SaveConfig();
  SUBPROC((void *)SaveConfig);
  mode=0;
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

void getbm(){
  bmname[0]=BM1NAME;
  bmname[1]=BM2NAME;
  bmname[2]=BM3NAME;
  bmname[3]=BM4NAME;
  bmname[4]=BM5NAME;
  bmname[5]=BM6NAME;
  bmname[6]=BM7NAME;
  bmname[7]=BM8NAME;
  bmname[8]=BM9NAME;
  bmname[9]=BMANAME;
  bmfile[0]=BM1FILE;
  bmfile[1]=BM2FILE;
  bmfile[2]=BM3FILE;
  bmfile[3]=BM4FILE;
  bmfile[4]=BM5FILE;
  bmfile[5]=BM6FILE;
  bmfile[6]=BM7FILE;
  bmfile[7]=BM8FILE;
  bmfile[8]=BM9FILE;
  bmfile[9]=BMAFILE;
  int i=0;
  while (i<10) {
    if (strlen(bmname[i])==0) strcpy((char*)bmname[i],"     <пусто>");
    i++;
  }
}

void getpal(){
  for (int i=0;i<24;i++){
    palette[i]=GetPaletteAdrByColorIndex(i);
  }
}

void do_gui(void)
{
  getbm();
  getpal();
  char dummy[sizeof(MAIN_CSM)];
  my_csm_id=CreateCSM(&maincsm,dummy,0);
  mode=-1;
}
