#include "..\inc\swilib.h"
#include "xtask.h"

extern void AddItem(tlistbox *llist, char const *s, void *p);
extern void ClrItems(tlistbox *llist);
extern void DrawListBox(tlistbox *llist, timage *pic, timage *selpic);
extern int KeyPressListBox(tlistbox *llist, int action, int key);
extern void AddRedrawProc(void *p);
extern void DeleteRedrawProc(void *p);
extern void AddKeyProc(void *p);
extern void DeleteKeyProc(void *p);
extern int ww,hh;
extern void mmenu(void);
extern char *palette[24];

extern tmainmenu mainmenu;

tlistbox *xmenu1;
void *subm;

unsigned char dprc[28] = {
	0x0C, 0x00, 0x9F, 0xE5, 0x00, 0x00, 0x90, 0xE5, 0x00, 0x20, 0xA0, 0xE3, 0x00, 0x10, 0xA0, 0xE3, 
	0x00, 0xF0, 0x1F, 0xE5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char kprc[28] = {
	0x01, 0x20, 0xA0, 0xE1, 0x00, 0x10, 0xA0, 0xE1, 0x04, 0x00, 0x9F, 0xE5, 0x00, 0x00, 0x90, 0xE5, 
	0x00, 0xF0, 0x1F, 0xE5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void *DestroyUpSubMenu(void *sm);
void *AddSubMenu(void *sm, NAMELIST *items);

//extern unsigned int exc;
const char perct[]="%t";

void DestroyAllSubMenu(void **sm);

int RunSM(unsigned int vv){
  if ((vv & 0x80000000)!=0){
    if ((vv & 0xA8000000)==0xA8000000){
      WSHDR *ws;
      ws=AllocWS(150);
      wsprintf(ws,perct,(void*)vv);
      ExecuteFile(ws,0,0);
      FreeWS(ws);
      return 1;
    }
    DestroyAllSubMenu(&subm);
    SUBPROC((void*)vv);
    return 1;
  }else{
    if((vv & 0x800)!=0) return 2;
    tmenuitem *tmp=mainmenu.start;
    int ii=(vv & 0xFF);
    while (ii>0){
      if (tmp!=0) tmp=tmp->next;
      ii--;
    }
    if (tmp!=0) subm=AddSubMenu(subm,tmp->start);
  }
  return 2;
}

int keyproc(tlistbox *llist, int action, int key)
{
  KeyPressListBox(llist,action,key);
  if (action==KEY_DOWN) {
    switch(key){
    case RIGHT_BUTTON:
    case ENTER_BUTTON:
      return RunSM((int)llist->selected->p);
    case LEFT_BUTTON:
    case RED_BUTTON:
      subm=DestroyUpSubMenu(subm);
      break;//return(1);
    }
  }
  return 2;
}

void *AddSubMenu(void *sm, NAMELIST *items){
  tsubms *subms=malloc(sizeof(tsubms));
  //void *ap=(void*)&keyproc;
  zeromem(subms,sizeof(tsubms));
  subms->next=sm;
  subms->selected=0;
  subms->llist=malloc(sizeof(tlistbox));
  unsigned int *keyp=malloc(28);
  memcpy(keyp,kprc,28);
  *(keyp+5)=(unsigned int)&subms->llist;
  *(keyp+6)=(unsigned int)&keyproc;
  unsigned int *redp=malloc(28);
  memcpy(redp,dprc,28);
  *(redp+5)=(unsigned int)&subms->llist;
  *(redp+6)=(unsigned int)DrawListBox;
  subms->KeyPressProc=(int(*)(int,int))keyp;
  subms->RedrawProc=(void(*)(void))redp;
  subms->llist->hline=14;
  subms->llist->hfont=14;
  subms->llist->font=SMALL_FONT;
  subms->llist->fatr=1;

  subms->llist->cline=0;
  NAMELIST *tmp=items;
  while (tmp!=0){
    subms->llist->cline++;
    tmp=tmp->next;
  }
  if (subms->llist->cline!=0) subms->llist->cline--;
  if (subms->llist->cline>9) subms->llist->cline=9;
  
  int xx=30;
  int yy=xmenu1->y;//40;
  int ss=(xmenu1->cursor-xmenu1->pos)*xmenu1->hline-2+6;
  if (subms->next!=0){
    xx=((tsubms*)(subms->next))->llist->x+5;
    if (((tsubms*)(subms->next))->llist->width+8>ww) xx=xx-10;
    yy=((tsubms*)(subms->next))->llist->y+5;
    ss=(((tsubms*)(subms->next))->llist->cursor-((tsubms*)(subms->next))->llist->pos)*((tsubms*)(subms->next))->llist->hline-2+6;
    //if (subms->next->llist->width+8>ww) xx=xx-10;
  }
  subms->llist->x=xx;
  subms->llist->width=xx+80;
  
  while (1){
    subms->llist->y=yy+ss;
    subms->llist->ssize=((subms->llist->cline+1)*subms->llist->hline);
    subms->llist->heigh=subms->llist->y+subms->llist->ssize;
    if(subms->llist->heigh>(hh-5)){
      if(subms->llist->y>(subms->llist->ssize-10)){
        int t=subms->llist->y+10;
        subms->llist->y=t-subms->llist->ssize;
        subms->llist->heigh=t;
        break;
      }
      subms->llist->cline--;
    } else break;
  }

  subms->llist->stbc=23;
  subms->llist->sbc=3;
  subms->llist->stfc=1;
  subms->llist->sfc=1;
  subms->llist->fatr=3;  
  subms->llist->bc=1;
  subms->llist->fc=0;
  subms->llist->cursor=0;
  subms->llist->pos=0;
  subms->llist->tpos=0;
  subms->llist->start=0;
  subms->llist->finish=0;
  
  if (items!=0) subms->llist->start=items;
  subms->llist->selected=subms->llist->start;
  AddKeyProc((void *)subms->KeyPressProc);
  AddRedrawProc((void *)subms->RedrawProc);  

  return subms;
}

void *DestroyUpSubMenu(void *sm){
  if (sm!=0) {
    tsubms *subms=sm;
    sm=subms->next;
    DeleteKeyProc((void *)subms->KeyPressProc);
    DeleteRedrawProc((void *)subms->RedrawProc);
    if(subms->KeyPressProc!=0)mfree((void *)subms->KeyPressProc);
    if(subms->RedrawProc!=0)mfree((void *)subms->RedrawProc);
    if(subms->llist!=0)mfree(subms->llist);
    if(subms!=0)mfree(subms);
  }
  return sm;
}

void DestroyAllSubMenu(void **sm){
  while((*sm)!=0){
    (*sm)=DestroyUpSubMenu((*sm));
  }
}

void xmn1destroy(void);

int xmn1keypress(int action, int key)
{
  KeyPressListBox(xmenu1,action,key);
  if (action==KEY_DOWN) {
    switch(key){
    case LEFT_SOFT:
      mmenu();
      break;
    case RIGHT_BUTTON:
    case ENTER_BUTTON:
      return RunSM((unsigned int)xmenu1->selected->p);
    case LEFT_BUTTON:
    case RED_BUTTON:
      xmn1destroy();
      break;//return(1);
    case RIGHT_SOFT:
      return(1);
    }
  }
  return 2;
}

extern char ttime[5];
extern void DrwStr(WSHDR *wshdr, int x, int y, int w, int h, int font, int text_flag, char *pen, char *brush);

void xmn1redraw(void)
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
  //DrawString(xmenu1->selected->name,45,4,ww-3,20,7,1,palette[0],palette[23]);
  DrwStr(xmenu1->selected->name,42,4,ww-48,16,SMALL_FONT,1,palette[0],palette[23]);

  wsprintf(ws,"%t"," Меню     < * >    Назад ");
  //DrawString(ws,2,hh-15,ww-2,hh-2,7,0x80,palette[0],palette[23]);
  DrwStr(ws,2,hh-15,ww-4,13,SMALL_FONT,0x80,palette[0],palette[23]);
  FreeWS(ws);
  DrawListBox(xmenu1,mainmenu.pic,mainmenu.selpic);
}

void xmn1destroy(void)
{
  DeleteKeyProc((void *)&xmn1keypress);
  DeleteRedrawProc((void *)&xmn1redraw);
  DestroyAllSubMenu(&subm);
  //ClrItems(xmenu1);
  mfree(xmenu1);
  xmenu1=0;  
}


void xmenu(void){
  xmenu1=malloc(sizeof(tlistbox));

  xmenu1->x=0;
  xmenu1->y=20;
  xmenu1->width=ww;
  xmenu1->hline=27;
  xmenu1->hfont=17;
  xmenu1->font=MIDDLE_FONT;
  xmenu1->cline=4;
  if(hh<140){
    xmenu1->cline=2;
    xmenu1->hline=30;
  }
  xmenu1->bc=15;
  xmenu1->fc=22;
  xmenu1->stbc=23;
  xmenu1->sbc=3;
  xmenu1->stfc=1;
  xmenu1->sfc=1;
  xmenu1->cursor=0;
  xmenu1->pos=0;
  xmenu1->tpos=27;
  xmenu1->start=0;
  xmenu1->finish=0;
  xmenu1->selected=0;
  xmenu1->fatr=6;
  xmenu1->ssize=((xmenu1->cline+1)*xmenu1->hline);
  xmenu1->heigh=hh-20;
  if (mainmenu.start){
    if (mainmenu.start->start) xmenu1->start=mainmenu.start->start;
  }
  AddItem(xmenu1,"тест 8",(void *)0x00000208);
  AddItem(xmenu1,"тест 7",(void *)0x00000207);
  AddItem(xmenu1,"тест 6",(void *)0x00000206);
  AddItem(xmenu1,"тест 5",(void *)0x00000205);
  AddItem(xmenu1,"тест 4",(void *)0x00000204);
  AddItem(xmenu1,"тест 3",(void *)0x00000203);
  AddItem(xmenu1,"тест 2",(void *)0x00000202);
  AddItem(xmenu1,"тест 1",(void *)0x00000201);*/
  xmenu1->selected=xmenu1->start;
  AddKeyProc((void *)&xmn1keypress);
  AddRedrawProc((void *)&xmn1redraw);  
  subm=0;
}
