#include "C:\ARM_ALL\inc\swilib.h"
#include "C:\ARM_ALL\inc\pnglist.h"
#include "rect_patcher.h"
#include "tagmenu.h"
#include "lang.h"

extern long  strtol (const char *nptr,char **endptr,int base);

int TagMenu_ID;
int TypeField;
TID3TagV1_1 TagFile;
extern char tag_file_path[128];

typedef void (*IFN_RET_PROC) (WSHDR *wsname);

extern void TextInput(char *caption, char *prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc);

extern int M_ICONS[];

extern int LaunchEditor();

void Title()
{
  LaunchEditor(0);
}
void Artist()
{
  LaunchEditor(1);
}
void Album()
{
  LaunchEditor(2);
}
void Year()
{
  LaunchEditor(3);
}
void Comment()
{
  LaunchEditor(4);
}
void Track()
{
  LaunchEditor(5);
}
void Genre()
{
}

///-----------------------

static const HEADER_DESC smenuhdr={0,0,131,21,NULL,(int)LGP_EDITTAG,LGP_NULL};

static const int smenusoftkeys[]={0,1,2};

static const char * const smenutexts[7]=
{
 "Title", 
 "Artist",
 "Album",
 "Year",
 "Comment",
 "Track",
 "Genre" 
};

static const void *smenuprocs[7]=
{
  (void *)Title,
  (void *)Artist,
  (void *)Album,
  (void *)Year,
  (void *)Comment,
  (void *)Track,
  (void *)Genre
};

static const SOFTKEY_DESC smenu_sk[]=
{
  {0x0018,0x0000,(int)LGP_EDIT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB smenu_skt=
{
  smenu_sk,0
};

void smenu_ghook(void *data, int cmd)
{
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int smenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(smenuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static void smenuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  switch(curitem)
  {
  case 0:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Title)+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],TagFile.Title);
//    SetMenuItemIconArray(data,item,M_ICONS+7);
    SetMenuItemText(data, item, ws, curitem);
    break;
  case 1:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Artist)+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],TagFile.Artist);
//    SetMenuItemIconArray(data,item,M_ICONS+8);
    SetMenuItemText(data, item, ws, curitem);
    break;
  case 2:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Album)+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],TagFile.Album);
 //   SetMenuItemIconArray(data,item,M_ICONS+9);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 3:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+4+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],TagFile.Year);
//    SetMenuItemIconArray(data,item,M_ICONS+10);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 4:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Comment)+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],TagFile.Comment);
//    SetMenuItemIconArray(data,item,M_ICONS+11);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 5:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+4);
    wsprintf(ws,"%t:%d",smenutexts[curitem],TagFile.Track);
//    SetMenuItemIconArray(data,item,M_ICONS+12);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 6:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(Genres[TagFile.Genre])+1);
    wsprintf(ws,"%t:%t",smenutexts[curitem],Genres[TagFile.Genre]);
//    SetMenuItemIconArray(data,item,M_ICONS+12);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  }
}

static const MENU_DESC smenu=
{
  8,smenu_keyhook,smenu_ghook,NULL,
  smenusoftkeys,
  &smenu_skt,
  0x11,//MENU_FLAG,
  smenuitemhandler,
  NULL,//menuitems,
  NULL,//menuprocs,
  0  
};

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
} 

int CreateTagMenu(void)
{
  int f;
  unsigned int ul;
  if ((f=fopen(tag_file_path,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
  lseek(f,get_file_size(tag_file_path)-128,S_SET,&ul,&ul);
  fread(f,&TagFile, 128, &ul);
  fclose(f,&ul);
  if (strcmp(TagFile.ID,"TAG"))
   {
   patch_header(&smenuhdr);
   TagMenu_ID=CreateMenu(0,0,&smenu,&smenuhdr,0,7,0,0);
   return TagMenu_ID;
   }
   else
   {
   // нет тега
   char s[256];
   snprintf(s,255,"Tag ID3 not found!");
   ShowMSG(2, (int)s);
   return 0;  
   }
  }
  else
  {
    char s[256];
    snprintf(s,255,"Error open file!");
    ShowMSG(2, (int)s);
    // ошибка открытия файла
    return 0; 
  }
  
}

//---------------------------------------------------------------------------
// Test edit dialog
//---------------------------------------------------------------------------
SOFTKEY_DESC menu_sk[]= { { 0, 0, 0 } };

SOFTKEYSTAB menu_skt =
{
	menu_sk, 0
};

extern int char16to8(int c);

int inp_onkey(GUI *gui, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char ss[16];
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
//  В этом куске, вообще говоря, нет смысла, ибо при запущенном XTask
// красная кнопка действует как "Назад"
  if(msg->gbsmsg->submess==RED_BUTTON)
  {
    return(1); // выходим без сохранения.
  }
  if((msg->gbsmsg->submess==GREEN_BUTTON)||(msg->keys==0x18))
  {
    ExtractEditControl(gui,1,&ec);    
    wstrcpy(tmostr,ec.pWS);
    char *s;
    int len;
    switch (TypeField){
    case 0: s=TagFile.Title;len=30;break;
    case 1: s=TagFile.Artist;len=30;break;
    case 2: s=TagFile.Album;len=30;break;
    case 3: s=TagFile.Year;len=4;break;
    case 4: s=TagFile.Comment;len=28;break;
    case 5: s=ss ;len=28;break;
    }
    for (int i=0; i<tmostr->wsbody[0] && i<len; i++)
    {
      *s++=char16to8(tmostr->wsbody[i+1]);
    }
    *s=0;
    if (TypeField==5) TagFile.Track=strtol(ss,0,10);
    
    int f;
    unsigned int ul;
    if ((f=fopen(tag_file_path,A_ReadWrite + A_BIN+A_Create+A_Append, P_READ + P_WRITE,&ul))!=-1)
    {
    lseek(f,get_file_size(tag_file_path)-128,S_SET,&ul,&ul);
    fwrite(f,&TagFile, 128,&ul);
    //fread(f,&TagFile, sizeof(TagFile), &ul);
    fclose(f,&ul);
    }
    return(1); // Выходим
  }
  
  return(0); //Do standart keys

}


void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018, 0x0000,(int)"Ок"};
  
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
  if (cmd==2)
  {
    //Called after onCreate
  }
  if (cmd==3)
  {
    FreeWS(tmostr);    
  }    
  if (cmd==7)
  {
    SetSoftKey(gui,&sk,SET_SOFT_KEY_N);    
  }
}

void inp_locret(void){}

INPUTDIA_DESC inp_desc=
{
  1,
  inp_onkey,
  inp_ghook,
  (void *)inp_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

HEADER_DESC inp_hdr={0,0,131,21,/*icon*/NULL,(int)LGP_EDITTAG,LGP_NULL};

#define MAX_LEN 256
int LaunchEditor(int type)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *tagstr;
  
  tagstr=AllocWS(MAX_LEN);
  TypeField=type;
  switch (type){
  case 0:
    wsprintf(tagstr,"%t",TagFile.Title);
    inp_hdr.lgp_id=(int)"Title";
    break;
  case 1:
    wsprintf(tagstr,"%t",TagFile.Artist);
    inp_hdr.lgp_id=(int)"Artist";
    break;
  case 2:
    wsprintf(tagstr,"%t",TagFile.Album);
    inp_hdr.lgp_id=(int)"Album";
    break;
  case 3:
    wsprintf(tagstr,"%t",TagFile.Year);
    inp_hdr.lgp_id=(int)"Year";
    break;
  case 4:
    wsprintf(tagstr,"%t",TagFile.Comment);
    inp_hdr.lgp_id=(int)"Comment";
    break;
  case 5:
    wsprintf(tagstr,"%d",TagFile.Track);
    inp_hdr.lgp_id=(int)"Track";
    break;
    
  }
  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,tagstr,256);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_header(&inp_hdr);
  patch_input(&inp_desc);
  return CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,tagstr);
}
