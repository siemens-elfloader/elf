#include "..\inc\swilib.h"

char colors[4][4]={{0xFF,0,0,0x64},{0,0xFF,0,0x64},{0,0,0xFF,0x64},{0xC6,0xAA,0xAF,0x32}};
char black[4]={0x00,0x00,0x00,0x64};
char white[4]={0xFF,0xFF,0xFF,0x64};
char transparent[4]={0x00,0x00,0x00,0x00};
extern char *loadfile(char *filename);
extern int  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
extern int strcmp_nocase(const char *s, const char *d);
extern char *txtfile;
extern int MENU_GUI_ID;// ИД гуя меню
extern int menuMod;
#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

//===============================================================================================
// ELKA Compatibility

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
//===============================================================================================
//  YDISP нам больше не нужен так как иконбар отключим
#ifdef ELKA
#undef YDISP
#define   YDISP 0
#endif

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  int is_rect_needed;
  int is_first_set;
  int x_pos;
  int y_pos;
  int x2_pos;
  int y2_pos;
  union
  {
    unsigned int *xy;
    RECT *rc;
  };
  int cstep;
}RECT_GUI;

typedef struct
{
  GUI gui;
  WSHDR*ws1;
  int r;
  int g;
  int b;
  int a;
  char *color;
  int current_column;
  char testcolor[4];
  int cstep;
}MAIN_GUI_2;

const char Pointer[5]={0x27,0x27,0xFF,0x27,0x27};
const IMGHDR imgPointer = {5,5,0x1,(char *)Pointer};

void DrwImg2(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}
extern char picpath[];
void method0_rect(RECT_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  FSTATS fs;
  unsigned int ul;
  if (!GetFileStats(picpath,&fs,&ul))
    DrawImg(0,0,(int)picpath);
  else{
    DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,white,white);
    // Нарисуем сетку
    for (int y_0=YDISP; y_0< scr_h;y_0+=10)
    {
      DrawLine(0,y_0,scr_w-1,y_0,1,colors[3]);
    }
    for (int x_0=0; x_0<scr_w;x_0+=10)
    {
      DrawLine(x_0,YDISP,x_0, scr_h-1,1,colors[3]);
    }
  }

  if (data->is_rect_needed)
  {
    DrawRoundedFrame(data->rc->x,data->rc->y,data->rc->x2,data->rc->y2,
                     0,0,0,colors[3],transparent); // Предыдущий рект
    if (data->is_first_set)
    {
      DrawRoundedFrame(data->x2_pos,data->y2_pos,data->x_pos,data->y_pos,
                       0,0,0,black,transparent);
      wsprintf(data->ws1,"%u,%u,%u,%u",data->x2_pos,data->y2_pos,data->x_pos,data->y_pos);
    }
    else
    {
      wsprintf(data->ws1,"%u,%u,%u,%u",data->x_pos,data->y_pos,data->x2_pos,data->y2_pos);
    }
    DrawString(data->ws1,3,scr_h-GetFontYSIZE(FONT_SMALL)-1,scr_w-4,scr_h-1,FONT_SMALL,1,black,transparent);
  }
  else
  {
    wsprintf(data->ws1,"%u,%u",data->x_pos,data->y_pos);
    DrawString(data->ws1,3,scr_h-GetFontYSIZE(FONT_SMALL)-1,scr_w-4,scr_h-1,FONT_SMALL,1,black,transparent);
  }

  //Текущая позиция
  DrwImg2((IMGHDR *)&imgPointer,data->x_pos-2,data->y_pos-2,black,transparent);
}


void method1_rect(RECT_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_rect(RECT_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3_rect(RECT_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
  //DisableIconBar(1);
#endif
  data->gui.state=2;
}

void method4_rect(RECT_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
/*
#define MIN_STEP 1
#define MAX_STEP 8
*/


int method5_rect(RECT_GUI *data, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
       switch(msg->gbsmsg->submess)
       {
       case RIGHT_SOFT:
         if (data->is_rect_needed)
         {
           if (data->is_first_set)
           {
             data->is_first_set=0;
             break;
           }
         }

       case RED_BUTTON:
         return (1);

       case ENTER_BUTTON:
         if (data->is_rect_needed)
         {
           if (!data->is_first_set)
           {
             data->x2_pos=data->x_pos;
             data->y2_pos=data->y_pos;
             data->is_first_set=1;
           }
           else
           {
             data->rc->x=MIN(data->x2_pos,data->x_pos);
             data->rc->y=MIN(data->y2_pos,data->y_pos);
             data->rc->x2=MAX(data->x2_pos,data->x_pos);
             data->rc->y2=MAX(data->y2_pos,data->y_pos);
             return (1);
           }
         }
         else
         {
           data->xy[0]=data->x_pos;
           data->xy[1]=data->y_pos;
           return (1);
         }
       }
    }
    if (msg->gbsmsg->msg==LONG_PRESS)
#ifdef ELKA
      data->cstep=9;
#else
      data->cstep=5;
#endif

    switch(msg->gbsmsg->submess)
    {
    case '1':
      if ((data->x_pos-=data->cstep)<0)
        data->x_pos=0;
      if ((data->y_pos-=data->cstep)<YDISP)
        data->y_pos=YDISP;
      break;

    case '2':
    case UP_BUTTON:
      if ((data->y_pos-=data->cstep)<YDISP)
        data->y_pos=YDISP;
      break;

    case '3':
      if ((data->x_pos+=data->cstep)>ScreenW()-1)
        data->x_pos=ScreenW()-1;
      if ((data->y_pos-=data->cstep)<YDISP)
        data->y_pos=YDISP;
      break;

    case '4':
    case LEFT_BUTTON:
      if ((data->x_pos-=data->cstep)<0)
        data->x_pos=0;
      break;

    case '6':
    case RIGHT_BUTTON:
      if ((data->x_pos+=data->cstep)>ScreenW()-1)
        data->x_pos=ScreenW()-1;
      break;

    case '7':
      if ((data->x_pos-=data->cstep)<0)
        data->x_pos=0;
      if ((data->y_pos+=data->cstep)>ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;

    case '8':
    case DOWN_BUTTON:
      if ((data->y_pos+=data->cstep)>ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;

    case '9':
      if ((data->x_pos+=data->cstep)>ScreenW()-1)
        data->x_pos=ScreenW()-1;
      if ((data->y_pos+=data->cstep)>ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;
    }
  }
  if (msg->gbsmsg->msg==KEY_UP)
    data->cstep=1;

  DirectRedrawGUI();
  return(0);
}

void method7_rect(RECT_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

int method8_rect(void){return(0);}

int method9_rect(void){return(0);}

const void * const gui_methods_rect[11]={
  (void *)method0_rect,	//Redraw
  (void *)method1_rect,	//Create
  (void *)method2_rect,	//Close
  (void *)method3_rect,	//Focus
  (void *)method4_rect,	//Unfocus
  (void *)method5_rect,	//OnKey
  0,
  (void *)method7_rect,	//Destroy
  (void *)method8_rect,
  (void *)method9_rect,
  0
};

const RECT Canvas_1={0,0,0,0};

void EditCoordinates(void *rect_or_xy, int is_rect)
{
  RECT_GUI *rect_gui=malloc(sizeof(RECT_GUI));
  zeromem(rect_gui,sizeof(RECT_GUI));

  rect_gui->is_rect_needed=is_rect;
  if (!is_rect)
  {
    unsigned int *xy=rect_or_xy;
    rect_gui->x_pos=xy[0];
    rect_gui->y_pos=xy[1];
    rect_gui->xy=rect_or_xy;
  }
  else
  {
    RECT *rc=rect_or_xy;
    rect_gui->x_pos=rc->x;
    rect_gui->y_pos=rc->y;
    rect_gui->x2_pos=rc->x2;
    rect_gui->y2_pos=rc->y2;
    rect_gui->rc=rect_or_xy;
  }
  rect_gui->cstep=1;
  patch_rect((RECT*)&Canvas_1,0,YDISP,ScreenW()-1,ScreenH()-1);
  rect_gui->gui.canvas=(void *)(&Canvas_1);
  rect_gui->gui.flag30=2;
  rect_gui->gui.methods=(void *)gui_methods_rect;
  rect_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(rect_gui);
}



void method0_2(MAIN_GUI_2 *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,white,white);

  int fsize=GetFontYSIZE(FONT_SMALL)+1;
  int column_height=scr_h-fsize-fsize-YDISP;
  int column_width=scr_w/9;
  int start_column;
  int y_line;
  wsprintf(data->ws1,"%02X,%02X,%02X,%02X",data->r,data->g,data->b,data->a);

  DrawString(data->ws1,1,YDISP+1,scr_w-20,YDISP+fsize,FONT_SMALL,1,black,transparent);
  fsize+=3;
  for (int i=0;i!=4;i++)
  {
    start_column=column_width+2*i*column_width;
    if (data->current_column==i)
      DrawRectangle(start_column-2,YDISP+fsize-2,start_column+column_width+2,YDISP+fsize+column_height+2,
                    0,black,white);

    DrawRectangle(start_column,YDISP+fsize,start_column+column_width,YDISP+fsize+column_height,
                  0,black,colors[i]);
    switch(i)
    {
    case 0:
      y_line=YDISP+fsize+column_height-(data->r*column_height)/0xFF;
      break;
    case 1:
      y_line=YDISP+fsize+column_height-(data->g*column_height)/0xFF;
      break;
    case 2:
      y_line=YDISP+fsize+column_height-(data->b*column_height)/0xFF;
      break;
    case 3:
      y_line=YDISP+fsize+column_height-(data->a*column_height)/0x64;
      break;
    }
    DrawLine(start_column,y_line,start_column+column_width,y_line,0,black);
  }
  setColor(data->r,data->g,data->b,data->a,data->testcolor);
  DrawRoundedFrame(scr_w-1-fsize,YDISP+1,scr_w-2,YDISP+fsize,2,2,0,black,data->testcolor);
}

void method1_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
  //DisableIconBar(1);
#endif
  data->gui.state=2;
}

void method4_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5_2(MAIN_GUI_2 *data, GUI_MSG *msg)
{
  int n;
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
       switch(msg->gbsmsg->submess)
       {
       case RIGHT_SOFT:
       case RED_BUTTON:
         return (1);

       case ENTER_BUTTON:
         setColor(data->r,data->g,data->b,data->a,data->color);
         return (1);
       }
    }
    if (msg->gbsmsg->msg==LONG_PRESS)
      data->cstep=8;

    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
    case '2':
      switch(data->current_column)
      {
      case 0:
        if ((data->r+=data->cstep)>0xFF)
          data->r=0;
        break;
      case 1:
        if ((data->g+=data->cstep)>0xFF)
          data->g=0;
        break;
      case 2:
        if ((data->b+=data->cstep)>0xFF)
          data->b=0;
        break;
      case 3:
        if ((data->a+=((n=data->cstep)==8?n>>1:n))>0x64)
          data->a=0;
        break;
      }
      break;

    case LEFT_BUTTON:
    case '4':
      if (--data->current_column<0)
        data->current_column=3;
      break;
    case RIGHT_BUTTON:
    case '6':
      if (++data->current_column>3)
        data->current_column=0;
      break;

    case DOWN_BUTTON:
    case '8':
      switch(data->current_column)
      {
      case 0:
        if ((data->r-=data->cstep)<0)
          data->r=0xFF;
        break;
      case 1:
        if ((data->g-=data->cstep)<0)
          data->g=0xFF;
        break;
      case 2:
        if ((data->b-=data->cstep)<0)
          data->b=0xFF;
        break;
      case 3:
        if ((data->a-=((n=data->cstep)==8?n>>1:n))<0)
          data->a=0x64;
        break;
      }
      break;
    }
  }
  if (msg->gbsmsg->msg==KEY_UP)
    data->cstep=1;
  DirectRedrawGUI();
  return(0);
}


void method7_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

int method8_2(void){return(0);}

int method9_2(void){return(0);}


const void * const gui_methods_22[11]={
  (void *)method0_2,	//Redraw
  (void *)method1_2,	//Create
  (void *)method2_2,	//Close
  (void *)method3_2,	//Focus
  (void *)method4_2,	//Unfocus
  (void *)method5_2,	//OnKey
  0,
  (void *)method7_2,	//Destroy
  (void *)method8_2,
  (void *)method9_2,
  0
};

const RECT Canvas_2={0,0,0,0};

void EditColors(char *color)
{
  MAIN_GUI_2 *main_gui=malloc(sizeof(MAIN_GUI_2));
  zeromem(main_gui,sizeof(MAIN_GUI_2));
  main_gui->r=color[0];
  main_gui->g=color[1];
  main_gui->b=color[2];
  main_gui->a=color[3];
  main_gui->color=color;
  patch_rect((RECT*)&Canvas_2,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas_2);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods_22;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
}



typedef struct
{
  void *gui;
  int type;
}FVIEW;

volatile FLIST *fltop;

void Free_FLIST(void)
{
  LockSched();
  FLIST *fl=(FLIST *)fltop;
  fltop=0;
  UnlockSched();
  while(fl)
  {
    FLIST *fl_prev;
    fl_prev=fl;
    fl=fl->next;
    mfree(fl_prev->fullname);
    mfree(fl_prev->name);
    mfree(fl_prev);
  }
}

enum TYPES {IS_BACK, IS_FOLDER, IS_FILE};
const char back[]="..";


/*int strcmp_nocase(const char *s, const char *d)
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
}*/

FLIST *AddToFList(const char* full_name, const char *name, int is_folder)
{
  FLIST *fl;
  FLIST *pr;
  FLIST *fn=malloc(sizeof(FLIST));
  fn->fullname=malloc(strlen(full_name)+1);
  strcpy(fn->fullname,full_name);

  fn->name=malloc(strlen(name)+1);
  strcpy(fn->name,name);

  fn->is_folder=is_folder;
  fn->next=0;
  fl=(FLIST *)fltop;
  if (fl)
  {
    pr=(FLIST *)&fltop;
    while(strcmp_nocase(fl->name,fn->name)<0)
    {
      pr=fl;
      fl=fl->next;
      if (!fl) break;
    }
    fn->next=fl;
    pr->next=fn;
  }
  else
  {
    fltop=fn;
  }
  return (fn);
}

int FindFiles(char *str, int type)  // type == 0 SelectFolder, type == 1 SelectFile
{
  DIR_ENTRY de;
  unsigned int err;
  char *rev,*s,*d;
  int i, c, n=0;
  char path[256];
  char name[128];

  strcpy(path,str);
  Free_FLIST();
  s=path;
  d=name;
  rev=0;
  while((c=*s++))
  {
    *d++=c;
    if (c=='\\' && *s!='\0') rev=d;
  }
  if(rev==0)
    AddToFList("ROOT",back,IS_BACK);
  else
  {
    *rev=0;
    AddToFList(name,back,IS_BACK);
  }
  n++;


  i=strlen(path);
  path[i++]='*';
  path[i]='\0';
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      i=strlen(de.folder_name);
      strcpy(path,de.folder_name);
      path[i++]='\\';
      strcpy(path+i,de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        i=strlen(path);
        path[i++]='\\';
        path[i]=0;
        name[0]='\\';
        strcpy(name+1,de.file_name);
        AddToFList(path,name,IS_FOLDER);
        n++;
      }
      else
      {
        if (type!=0)
        {
          AddToFList(path,de.file_name,IS_FILE);
          n++;
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return n;
}



FLIST *FindFLISTtByNS(int *i, int si)
{
  FLIST *fl;
  fl=(FLIST *)fltop;
  while(fl)
  {
    if (fl->is_folder==si)
    {
      if (!(*i)) return (fl);
      (*i)--;
    }
    fl=fl->next;
  }
  return fl;
}

FLIST *FindFLISTtByN(int n)
{
  FLIST *fl;
  fl=FindFLISTtByNS(&n,IS_BACK); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FOLDER); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FILE); if ((!n)&&(fl)) return(fl);
  return fl;
}

int GetFListN()
{
  int i=0;
  FLIST *fl=(FLIST*)&fltop;
  while((fl=fl->next)) i++;
  return (i);
}
char header[128];
char header2[128];
void SavePath(void *ed_gui, FLIST *fl)
{
  /*EDITCONTROL ec;
  EDIT_ExtractFocusedControl(ed_gui,&ec);
  WSHDR *ws=AllocWS(ec.maxlen);
  str_2ws(ws,fl->fullname,ec.maxlen);
  EDIT_SetTextToFocused(ed_gui,ws);
  FreeWS(ws);*/

  strcpy(header,fl->fullname);
  txtfile=loadfile(fl->fullname);
}



int filelist_menu_onkey(void *data, GUI_MSG *msg)
{
  FVIEW *fview=MenuGetUserPointer(data);
  FLIST *fl;
  int i, n;
  i=GetCurMenuItem(data);
  fl=FindFLISTtByN(i);

  if (msg->keys==0x3D)
  {
    if (fl)
    {
      if (fl->is_folder==IS_FOLDER || fl->is_folder==IS_BACK)
      {
        int len;
        if (strcmp(fl->fullname,"ROOT"))
        {
          strncpy(header,fl->fullname,sizeof(header)-1);
          len=strlen(fl->fullname);
          header[len>sizeof(header)-1?sizeof(header)-1:len]=0;
          n=FindFiles(fl->fullname,fview->type);
        }
        else
        {
          int CreateRootMenu();
          n=CreateRootMenu();
        }
        Menu_SetItemCountDyn(data,n);
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else
      {
        SavePath(fview->gui,fl);
        return (1);
      }
    }
    //    GeneralFunc_F1(1);
    return(-1);
  }
  if (msg->keys==0x18)
  {
    if (fl)
    {
      if (fl->is_folder!=IS_BACK)
      {
        SavePath(fview->gui,fl);
        return (1);
      }
    }
    return (-1);
  }
  return (0);
}

void filelist_menu_ghook(void *data, int cmd)
{
  FVIEW *fview=MenuGetUserPointer(data);
  if (cmd==3)
  {
    Free_FLIST();
    mfree(fview);
  }
 // if (cmd==0x0A)
 /// {
  //  DisableIDLETMR();
 // }
}

void filelist_menu_iconhndl(void *data, int curitem, void *user_pointer)
{
  FLIST *fl;
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  int len;
  fl=FindFLISTtByN(curitem);
  if (fl)
  {
    len=strlen(fl->name);
    ws=AllocMenuWS(data,len+4);
    if (fl->is_folder==IS_BACK || fl->is_folder==IS_FOLDER)
    {
      str_2ws(ws,fl->name,len);
      wsInsertChar(ws,0x0002,1);
      wsInsertChar(ws,0xE008,1);
    }
    else
    {
      str_2ws(ws,fl->name,len);
    }
  }
  else
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws, "Ошибка");
  }
  SetMenuItemText(data, item, ws, curitem);
}

int fmenusoftkeys[]={0,1,2};
SOFTKEY_DESC fmenu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB fmenu_skt=
{
  fmenu_sk,0
};

HEADER_DESC filelist_HDR={0,0,0,0,NULL,(int)header,LGP_NULL};

MENU_DESC filelist_STRUCT=
{
  8,filelist_menu_onkey,filelist_menu_ghook,NULL,
  fmenusoftkeys,
  &fmenu_skt,
  0x10,
  filelist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int CreateRootMenu()
{
  char path[32];
  unsigned int err;
  int n=0;
  Free_FLIST();
  for (int i=0; i!=5; i++)
  {
    path[0]=i+'0';
    path[1]=':';
    path[2]='\\';
    path[3]=0;
    if (isdir(path,&err))
    {
      AddToFList(path,path,IS_FOLDER);
      n++;
    }
  }
  strcpy(header,"Корневой каталог");
  return (n);
}


void open_select_file_gui(void *ed_gui, int type)
{
  EDITCONTROL ec;
  FVIEW *fview;
  char path[128];
  char *s, *rev=0;
  int n, c, len;

  fview=malloc(sizeof(FVIEW));
  fview->gui=ed_gui;
  fview->type=type;
  EDIT_ExtractFocusedControl(ed_gui,&ec);
  ws_2str(ec.pWS,path,127);
  s=path;
  while((c=*s++))
  {
    if (c=='\\' && *s!='\0') rev=s;
  }
  if (!rev)
    n=CreateRootMenu();
  else
  {
    *rev=0;
    strncpy(header,path,sizeof(header)-1);
    len=strlen(path);
    header[len>sizeof(header)-1?sizeof(header)-1:len]=0;
    n=FindFiles(path,type);
  }
  patch_header(&filelist_HDR);
  CreateMenu(0,0,&filelist_STRUCT,&filelist_HDR,0,n,fview,0);
}




void open_fm()
{
  //FVIEW *fview;
  char *s;
  WSHDR *ws=AllocWS(256);
  //fview=malloc(sizeof(FVIEW));
  if (ws->wsbody[0]==0)
  {
    CreateRootMenu();
  }
  else
  {
    ws_2str(ws,header,127);
    s=strrchr(header, '\\');
    if (s) *(s+1)=0;
    int len=strlen(header);
    header[len>127?127:len]=0;
    FindFiles(header,1);
  }
  patch_header(&filelist_HDR);
 // CreateMenu(0,0,&filelist_STRUCT,&filelist_HDR,0,GetFListN(),fview,0);
      menuMod = 3;
      DirectRedrawGUI_ID(MENU_GUI_ID);//DirectRedrawGUI();
}








