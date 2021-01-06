#include "..\inc\swilib.h"
#include "xtask.h"

CSM_RAM *under_idle;
void DestroyMMenu();

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int mode;
int mode_red;
int flag;
int flagexi;
char hkey[10];
int ism;
int gfpe;

extern const int BLOCK_KEYLOCK;

int my_keyhook(int submsg, int msg)
{
  if ((BLOCK_KEYLOCK==1) && (IsUnlocked()==0)) return 0;
  if ((msg==KEY_UP)&&(hkey[flag]==0)&&(mode==-1)) {
    flag=0;
    return(2);
  }
  if (mode==-1) return(0);
  int key=submsg;
  if (msg==KEY_UP) key|=0x80;
  if (msg==LONG_PRESS) key|=0x40;
  if (key==hkey[flag]) flag++;
  else {
    flag=0;
    if (key==hkey[flag]) flag++;
  }
  if (hkey[flag]==0) {
      extern void do_gui(void);
      do_gui();
      return(2);
  } 
  if (msg==KEY_UP) 
  {
    flagexi=0;
    return(0);
  }
  if (submsg=='*') 
  {
    flagexi=1;
    return(0);
  }
  if ((submsg=='0')&&(flagexi==1)) 
  {  
      RemoveKeybMsgHook((void *)my_keyhook);
      DestroyMMenu();
      ShowMSG(1,(int)"XTask отлючен!");
      SUBPROC((void *)ElfKiller);
      return(2);
  } 
  return(0);
}

extern  void InitConfig();
extern const char HOT_KEY[10];
int hex2int(char a1, char a2){
  int i1,i2;
  if ((a1>='0') && (a1<='9')) i1=(int)(a1-'0');
  if (a1>='A') i1=(((int)a1) & 0xDF)-0x37;
  if ((a2>='0') && (a2<='9')) i2=(int)(a2-'0');
  if (a2>='A') i2=(((int)a2) & 0xDF)-0x37;
  return (i1*16)+i2;
}

tmainmenu mainmenu;
tmenuitem *menuitem1;
extern const char percent_t[];

void CreateMMenu(){
   extern const char menu_fname[128];
    char exepath[128];
    strcpy(exepath,menu_fname);
    int f;
    unsigned int ul;
    int fsize;
    char mname[100];
    unsigned int adr;
    char pname1[100];
    int jj=strlen(menu_fname);
    char c,c2;
    zeromem(&mainmenu,sizeof(tmainmenu));
    if ((f=fopen(menu_fname,A_ReadOnly+A_BIN,0,&ul))!=-1) {
      fsize=lseek(f,0,2,&ul,&ul);
      lseek(f,0,0,&ul,&ul);
      char *p=malloc(fsize+16);
      if (p) fread(f,p,fsize,&ul);
      fclose(f,&ul);
      
      while(jj>0){
        jj--;
        if(exepath[jj]=='\\') {
          exepath[jj+1]=0;
          break;
        }
      }
      jj=0;
      
      if ((int)p!=0) {
        int ii=0;
        while (ii<=fsize){
          if ((*(char*)(p+ii))=='?'){
            menuitem1=malloc(sizeof(tmenuitem));
            menuitem1->start=0;
            menuitem1->selected=0;
            menuitem1->next=mainmenu.start;
            mainmenu.start=menuitem1;
            while ((ii<=fsize)&&(*(char*)(p+ii)!=0xa)) ii++;
            ii++;
          }
            jj=0;
            while (ii<=fsize){
              c=*(char*)(p+ii);
              if (c==0xd) c=0;
              mname[jj]=c;
              if ((c==';')||(c==0xa)) break;
              jj++;
              ii++;
            }
            mname[jj]=0;
            c=*(char*)(p+ii+1);
            c2=*(char*)(p+ii+2);
            ii+=3;
            if (c>0x39){
              pname1[0]=c;
              pname1[1]=c2;
              jj=2;
              while (ii<=fsize){
                c=*(char*)(p+ii);
                if (c==0xd) c=0;
                pname1[jj]=c;
                if ((c==';')||(c==0xa)) break;
                jj++;
                ii++;
              }
              pname1[jj]=0;
              if (strlen(pname1)){
                adr=0;
                if(gfpe) adr=(unsigned int)GetFunctionPointer(pname1);
                if(adr==0)adr=0x00150C00;
              }
            }else if (c2=='x'){
              c=*(char*)(p+ii);
              c2=*(char*)(p+ii+1);
              ii+=2;
              adr=(hex2int(c,c2))<<24;
              c=*(char*)(p+ii);
              c2=*(char*)(p+ii+1);
              ii+=2;
              adr=adr|((hex2int(c,c2))<<16);
              c=*(char*)(p+ii);
              c2=*(char*)(p+ii+1);
              ii+=2;
              adr=adr|((hex2int(c,c2))<<8);
              c=*(char*)(p+ii);
              c2=*(char*)(p+ii+1);
              ii+=2;
              adr=adr|(hex2int(c,c2));
            }else if (c2==':'){
              pname1[0]=c;
              pname1[1]=c2;
              jj=2;
              while (ii<=fsize){
                c=*(char*)(p+ii);
                if (c==0xd) c=0;
                pname1[jj]=c;
                if ((c==';')||(c==0xa)) break;
                jj++;
                ii++;
              }
              pname1[jj]=0;
              if (strlen(pname1)){
                adr=(unsigned int)malloc(strlen(pname1)+2);
                strcpy((char*)adr,pname1);
              }
            } else {
              adr=((int)(c-'0')*10)+(int)(c2-'0');
            }
            if (strlen(mname)){
              NAMELIST *tmp=malloc(sizeof(NAMELIST));
              tmp->next=menuitem1->start;
              WSHDR *ws=AllocWS(40);
              wsprintf(ws,percent_t,mname);
              tmp->name=ws;
              if(adr<100)adr|=0x100;
              tmp->p=(void*)adr;
              menuitem1->start=tmp;
            }
            
            
            timage *pic;
            void *picbuf;
            char path[128];
            unsigned int zz;
            
            int picsize;
            if (*(char*)(p+ii)==';'){
              strcpy(path,exepath);
              ii++;
              jj=0;
              while (ii<=fsize){
                c=*(char*)(p+ii);
                if (c==0xd) c=0;
                pname1[jj]=c;
                if ((c==';')||(c==0xa)) break;
                jj++;
                ii++;
              }
              pname1[jj]=0;
              if (strlen(pname1)){
                strcat(path,pname1);
                if ((f=fopen(path,A_ReadOnly+A_BIN,0,&ul))!=-1) {
                  pic=malloc(sizeof(timage));
                  picsize=lseek(f,0,2,&ul,&ul)-0x20;
                  lseek(f,0x14,0,&ul,&ul);
                  fread(f,&zz,4,&ul);
                  lseek(f,0x20,0,&ul,&ul);
                  picbuf=malloc(picsize);
                  if (picbuf!=0) fread(f,picbuf,picsize,&ul);
                  fclose(f,&ul);
                  pic->next=mainmenu.pic;
                  pic->image.bitmap=picbuf;
                  pic->image.h=zz & 0xFF;
                  pic->image.w=(zz >> 8) & 0xFF;
                  pic->image.bpnum=(zz >> 16) & 0xFF;
                  mainmenu.pic=pic;
                }
              }
            }
            if (*(char*)(p+ii)==';'){
              strcpy(path,exepath);
              ii++;
              jj=0;
              while (ii<=fsize){
                c=*(char*)(p+ii);
                if (c==0xd) c=0;
                pname1[jj]=c;
                if ((c==';')||(c==0xa)) break;
                jj++;
                ii++;
              }
              pname1[jj]=0;
              if (strlen(pname1)){
                strcat(path,pname1);
                if ((f=fopen(path,A_ReadOnly+A_BIN,0,&ul))!=-1) {
                  pic=malloc(sizeof(timage));
                  picsize=lseek(f,0,2,&ul,&ul)-0x20;
                  lseek(f,0x14,0,&ul,&ul);
                  fread(f,&zz,4,&ul);
                  lseek(f,0x20,0,&ul,&ul);
                  picbuf=malloc(picsize);
                  if (picbuf!=0) fread(f,picbuf,picsize,&ul);
                  fclose(f,&ul);
                  pic->next=mainmenu.selpic;
                  pic->image.bitmap=picbuf;
                  pic->image.h=zz & 0xFF;
                  pic->image.w=(zz >> 8) & 0xFF;
                  pic->image.bpnum=(zz >> 16) & 0xFF;
                  mainmenu.selpic=pic;
                }
              }
            }
            while ((ii<=fsize)&&(*(char*)(p+ii)!=0xa)) ii++;
            ii++;
        }
        if(p!=0)mfree(p);
        p=0;
      }
    }
 }

void DestroyMMenu(){
  timage *tmp  ;
  while (mainmenu.pic) {
    tmp=mainmenu.pic->next;
    if (mainmenu.pic->image.bitmap!=0)mfree(mainmenu.pic->image.bitmap);
    if (mainmenu.pic!=0)mfree(mainmenu.pic);
    mainmenu.pic=tmp;
  }
  mainmenu.pic=0;
  while (mainmenu.selpic) {
    tmp=mainmenu.selpic->next;
    if(mainmenu.selpic->image.bitmap!=0)mfree(mainmenu.selpic->image.bitmap);
    if(mainmenu.selpic!=0)mfree(mainmenu.selpic);
    mainmenu.selpic=tmp;
  }
  mainmenu.selpic=0;  
  tmenuitem *start=mainmenu.start;
  tmenuitem *sel;
  NAMELIST *st;
  NAMELIST *sl;
  while (start){
    sel=start->next;
    st=start->start;
    while (st){
      sl=st->next;
      FreeWS(st->name);
      if(((unsigned int)st->p & 0xA8000000)==0xA8000000) {
        if(st->p!=0)mfree(st->p);
      }
      if(st!=0)mfree(st);
      st=sl;
    }
    if(start!=0)mfree(start);
    start=sel;
  }
  mainmenu.start=0;
}

int main(char *exename, char *fname)
{
  mode=0;
  InitConfig();
  int sd=strlen(exename);
  hkey[0]=0x2a;
  hkey[1]=0x23;
  hkey[2]=0;
  int fp=0;
  int j=0;
  gfpe=0;
  if (((unsigned long)GetFunctionPointer_adr(""))>>28 == 0xA)gfpe=1;
  
  if (strlen(HOT_KEY)){
    hkey[j]=hex2int(HOT_KEY[0],HOT_KEY[1]);
    j++;
    if (HOT_KEY[2]==','){
      hkey[j]=hkey[j-1] |0x80;
      j++;
    } else if (HOT_KEY[2]=='+'){
      fp++;
    } else goto finish;
    hkey[j]=hex2int(HOT_KEY[3],HOT_KEY[4]);
    if ((hkey[j]==hkey[j-1]) && (fp)) hkey[j]=hkey[j] |0x40;
    j++;
    if (HOT_KEY[5]==','){
      hkey[j]=(hkey[j-1]&0xbf) |0x80;
      j++;
    } else if (HOT_KEY[5]=='+'){
      fp++;
    } else goto finish;
    hkey[j]=hex2int(HOT_KEY[6],HOT_KEY[7]);
    if ((hkey[j]==hkey[j-1]) && (fp==2)) hkey[j]=hkey[j] |0x40;
    j++;
    //hkey[j]=(hkey[j-1]&0xbf) |0x80;
finish:
  hkey[j]=0;
  }

  LockSched();
  if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Невозможно зарегистрировать обработчик!");
    SUBPROC((void *)ElfKiller);
  }
  else
  {
    extern const int ENA_HELLO_MSG;
    CreateMMenu();
    if (ENA_HELLO_MSG) ShowMSG(1,(int)"XTask установлен!");
    under_idle=(FindCSMbyID(CSM_root()->idle_id))->prev; //Ищем idle_dialog
  }
  UnlockSched();
}
