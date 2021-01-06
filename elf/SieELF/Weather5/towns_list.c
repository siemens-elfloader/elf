#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "string_works.h"
#include "main.h"

//=================================== Список городов ===========================================
int Menu_ID;

char **towns_lines; //Массив указателей на строки
int twns_count=0;

void FreeLines(void)
{
  if (towns_lines) mfree(towns_lines);
  towns_lines=NULL;
}

int LoadLines(void)
{
  FSTATS stat;
  char *fn;
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
  FreeLines();
 
  extern const char TOWNS_PATH[];
  fn=(char *)TOWNS_PATH;
  
  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<32)
    {
      if (pp&&(pp!=p))
      {
	towns_lines=realloc(towns_lines,(i+1)*sizeof(char *));
	towns_lines[i++]=pp;
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
}


HEADER_DESC twns_menuhdr={0,0,131,21,NULL,(int)"Выбор города...",LGP_NULL};

int twns_menusoftkeys[]={0,1,2};
extern int edmessage_id;
extern WSHDR* ws_eddata;


SOFTKEY_DESC twns_menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Отмена"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB twns_menu_skt=
{
  twns_menu_sk,3
};

void twns_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  const char *p=strrchr(towns_lines[curitem],';')+1;
  ws=AllocMenuWS(data,strlen(p));
  ascii2ws(ws,p);
  SetMenuItemText(data, item, ws, curitem);
}

void twns_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int twns_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (twns_count) 
    {
      extern int wd_id;
      extern char logbuf[1024];
      extern int page_num;
      extern int itemnum;
      
      const char *p=strrchr(towns_lines[GetCurMenuItem(data)],';')+1;
      strncpy(Town_ID,towns_lines[GetCurMenuItem(data)],p-towns_lines[GetCurMenuItem(data)]-1); 
      Town_ID[p-towns_lines[GetCurMenuItem(data)]-1]='\0';
      //ShowMSG(1, (int)Town_ID);
    
      sprintf(logbuf, "");
      page_num=1;
      itemnum=0;
      
      GeneralFunc_flag1(wd_id,1);
      GeneralFunc_flag1(Menu_ID,1);
      do_start_connection();
    }
       else
         {
           FreeLines();
           GeneralFunc_flag1(Menu_ID,1);           
         }
  }
  
  if (msg->keys==0x01)
  {
    FreeLines();
  }  
  return(0);
}

static const MENU_DESC twns_menu=
{
  0,twns_menu_keyhook,twns_menu_ghook,NULL,
  twns_menusoftkeys,
  &twns_menu_skt,
  8,
  twns_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  0
};

HEADER_DESC twns_menuhdr;

void DispTownsMenu()
{
  twns_count=LoadLines();
  patch_header(&twns_menuhdr);
  Menu_ID = CreateMenu(0,0,&twns_menu,&twns_menuhdr,0,twns_count,0,0);
}
