#include "..\inc\swilib.h"
#include "language.h"
enum editcontrols
{
  NAME=2,
  ICON=6,
  ACTION=8,
};

int IsShortcut,
    NumOfItems=0;
extern const char SHORTCUTS_FILE[128];
//extern const char ENTRYPOINTS_FILE[128];

char *templates_chars; //§³§à§Ò§ã§ä§Ó§Ö§ß§ß§à §æ§Ñ§Û§Ý
char **templates_lines; //§®§Ñ§ã§ã§Ú§Ó §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§Ö§Û §ß§Ñ §ã§ä§â§à§Ü§Ú

void FreeLines(void)
{
  if (templates_lines) mfree(templates_lines);
  if (templates_chars) mfree(templates_chars);
  templates_lines=NULL;
  templates_chars=NULL;
}

extern const char TEMPLATES_PATH[];

int LoadLines(void)
{
  FSTATS stat;
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p, *pp;
  int c;
  if (GetFileStats(SHORTCUTS_FILE,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(SHORTCUTS_FILE,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=templates_chars=malloc(fsize+1);
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
	templates_lines=realloc(templates_lines,(i+1)*sizeof(char *));
	templates_lines[i++]=pp;
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

extern void ascii2ws(WSHDR *ws, const char *s);

HEADER_DESC ShortcutsMenuHeader={NULL,NULL,NULL,NULL,NULL,NULL,LGP_NULL};

void ShortcutsMenuItemHandler(void *data, int curitem, void *unk)
{
  void *item=AllocMenuItem(data);
  char *p=strrchr(templates_lines[curitem],';')+1;
  WSHDR *ws=AllocMenuWS(data,strlen(p));
  gb2ws(ws,p,strlen(p));
  SetMenuItemText(data, item, ws, curitem);
}

void ShortcutsMenuGHook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    FreeLines();
  }
}

static int ShortcutsMenuKeyHook(void *data, GUI_MSG *msg)
{
  int Selected=GetCurMenuItem(data);
  void *edgui=MenuGetUserPointer(data);
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (NumOfItems)
    {
      EDITCONTROL ec;
      char *str=malloc(128);
      const char *p=strrchr(templates_lines[Selected],';')+1;
      strncpy(str,templates_lines[Selected],p-templates_lines[Selected]-1); 
      str[p-templates_lines[Selected]-1]='\0';
      ExtractEditControl(edgui,ACTION,&ec);
      
      WSHDR *ws=AllocWS(ec.maxlen);
      str_2ws(ws,str,ec.maxlen);
      EDIT_SetTextToEditControl(edgui,ACTION,ws);
      
      gb2ws(ws,p,strlen(p));
      CutWSTR (ws,32);
      EDIT_SetTextToEditControl(edgui,NAME,ws);
      
      gb2ws(ws,"SHORTCUT",strlen("SHORTCUT"));
      CutWSTR (ws,32);
      EDIT_SetTextToEditControl(edgui,ICON,ws);
      mfree(str);
      FreeWS(ws);
      return(1);
    }
  }
  return(0);
}

const int MenuSoftkeys[]={0,1,2};

const SOFTKEY_DESC menu_sk[]=
{
  {0x0004,0x0000,(int)LG_OPTIONS},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB Select_Back_skt=
{
  menu_sk,0
};
static const MENU_DESC ShortcutsMenuStruct=
{
  8,ShortcutsMenuKeyHook,ShortcutsMenuGHook,NULL,
  MenuSoftkeys,
  &Select_Back_skt,
  0x10,
  ShortcutsMenuItemHandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  NULL
};


#pragma inline
void patch_header2(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

int DispShortcutsMenu(void *ed_gui)
{
  NumOfItems=LoadLines();
  if(NumOfItems)
  {
    *((int *)(&ShortcutsMenuHeader.lgp_id))=(int)"Select shortcat";
    patch_header2(&ShortcutsMenuHeader);
    return CreateMenu(0,0,&ShortcutsMenuStruct,&ShortcutsMenuHeader,0,NumOfItems,ed_gui,0);
  }
  MsgBoxError(1, (int)"FILE NOT FOUND!");
  return(0);
}
