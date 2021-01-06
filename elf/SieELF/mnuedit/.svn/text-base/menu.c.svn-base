#include "..\inc\swilib.h"
#include "language.h"
int menu_id;
int it=6;
char *menu_name[]={
/*  "Открыть",
  "Сохранить",
  "Добавить",
  "Удалить",
  "Об эльфе",
  "Выход"*/
  LG_OPEN,
  LG_SAVE,
  LG_ADD,
  LG_DEL,
  LG_ABOUT,
  LG_EXIT
};

extern int item;
extern void about();
extern int id_ed;
extern void del(int i);
extern void SaveFile(char *fname);
extern char file[256];
extern int DrawText(int i);
extern void AddItem();


#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//---------------------Создаем список меню-----------------------//

void menu_iconhnd(void *data, int curitem, void *unk);
const int menusoftke[]={0,1,2};

const SOFTKEY_DESC menu_[]=
{
  {0x0001,0x0000,(int)LG_SELECT},
  {0x0004,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_s=
{
  menu_,0
};

void menu_ghook(void *data, int cmd){};
int menu_onkey2(void *data, GUI_MSG *msg);
HEADER_DESC menuhdr2={0,0,131,21,NULL,(int)LG_MENU,LGP_NULL};

const MENU_DESC menu=
{
  8,menu_onkey2,menu_ghook,NULL,
  menusoftke,
  &menu_s,
  0x10,//0x11,
  menu_iconhnd,
  NULL,   //Items
  NULL,   //Procs
  7   //n
};

void menu_iconhnd(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  char *s;
  void *item=AllocMenuItem(data);
  s=malloc(64);
  sprintf(s,"%s",menu_name[curitem]);
  if (s)
  {
    if (strlen(s))
    { 
      ws=AllocMenuWS(data,strlen(s)+4);
      wsprintf(ws,"%t",s);
    }
    else 
    { 
      ws=AllocMenuWS(data,10);
      wsprintf(ws,"%t","no name");
    }
  }
  else  
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws,"error");
    wsInsertChar(ws,2,1);//Цвет надписей

  }
   SetMenuItemText(data,item,ws,curitem);
}


int menu_onkey2(void *data, GUI_MSG *msg)
{
  int i;
  i=GetCurMenuItem(data);
  int k=msg->gbsmsg->submess;
 if(k=='*')
   {
     about();
     return (-1);
   }
  if (k==ENTER_BUTTON || k==LEFT_SOFT)
  {
    switch(i)
      {
        case 0:  DrawText(item); break;
        case 1:  SaveFile(file); break;
        case 2:  AddItem(); break;
        case 3:  del(item); break;
        case 4:  about(); break;
        case 5:  //exit
            GeneralFunc_flag1(menu_id,1);
            GeneralFunc_flag1(id_ed,1);
            break;
      }
    return(1);
  }
 if(k==RIGHT_SOFT || k==RED_BUTTON)
 {
   GeneralFunc_flag1(menu_id,1);
 }
  return(0);
}

void ShowMainMenu(void)
{ 
 patch_header(&menuhdr2);
 menu_id=CreateMenu(0,0,&menu,&menuhdr2,0,it,0,0);
}
