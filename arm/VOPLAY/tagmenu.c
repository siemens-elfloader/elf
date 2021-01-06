#include "tagmenu.h"
#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "..\inc\xtask_ipc.h"
#include "language.h"
#include "main.h"
#include "rect_patcher.h"
extern long  strtol(const char *nptr,char **endptr,int base);
typedef void (*IFN_RET_PROC) (WSHDR *wsname);
extern void TextInput(char *caption, char *prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc);
//extern char procfile[128];
extern char now_play[256];
extern int LaunchEditor();
TID3TagV1_1 TagFile;
extern int TagMenu_ID;
int TypeField;
extern IMGHDR *fonn;
extern void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush);
//int ICONS[16];

/*#pragma inline
void patch_header1(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
void patch_input1(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}*/

const char perc_tt_tag[]="%t:%t";
const char perc_td_tag[]="%t:%d";
const char perc_t_tag[]="%t";
const char perc_d_tag[]="%d";

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
void inittag()
{
  WSHDR *ws=AllocWS(256);
  int x=20,y=20,x2=200,y2=300;
  TagFile.Genre=0;
  int n=0;
  DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  for(int i=0; i<20;i++)
  {
    n++;
    if(n<10)
    {
    wsprintf(ws,perc_t_tag,Genres[TagFile.Genre]);
    DrawString(ws,x,y,x2,y2,9,0,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
    TagFile.Genre+=1;
    y+=25;
    }
    else
    {
      if(n==11){y=10;}
      x+=100;
      y+=20;
    }
  }

}
void Genre()
{
  LaunchEditor(6);
 // inittag();
  //ShowMSG(1,(int)"В стадии разработки");
}

HEADER_DESC smenuhdr={0,0,0,0,NULL,(int)LG_EDITTAG,LGP_NULL};

static const int smenusoftkeys[]={0,1,2};

static char *smenutexts[7]=
{
 (char *)LG_TAG_TITLE,
  (char *)LG_TAG_ARTIST,
  (char *)LG_TAG_ALBUM,
  (char *)LG_TAG_YEAR,
  (char *)LG_TAG_COMMENT,
  (char *)LG_TAG_TRACK,
  (char *)LG_TAG_GENRE,
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

SOFTKEY_DESC smenu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB smenu_skt=
{
  smenu_sk,0
};

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if((f=GetFileStats(fname,&fs,&err))==-1)
  return f;
  return(fs.size);
} 
void SaveID3(void)
{
  int f;
  char fn[256];
  unsigned int ul;
  strcpy(fn,now_play);
  if ((f=fopen(fn,A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE+A_Truncate,&ul))!=-1)
  {
    lseek(f,get_file_size(now_play)-128,S_SET,&ul,&ul);
    fwrite(f,&TagFile,128,&ul);
    fclose(f,&ul);
  }
}

static int smenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(smenuprocs[GetCurMenuItem(data)]))();
  }
  if (msg->keys==0x1)
  {
    SaveID3();
    findtegs();
    REDRAW();
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
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],TagFile.Title);
    SetMenuItemText(data, item, ws, curitem);
    break;
  case 1:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Artist)+1);
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],TagFile.Artist);
    SetMenuItemText(data, item, ws, curitem);
    break;
  case 2:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Album)+1);
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],TagFile.Album);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 3:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+4+1);
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],TagFile.Year);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 4:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(TagFile.Comment)+1);
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],TagFile.Comment);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 5:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+4);
    wsprintf(ws,perc_td_tag,smenutexts[curitem],TagFile.Track);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  case 6:
    ws=AllocMenuWS(data,strlen(smenutexts[curitem])+strlen(Genres[TagFile.Genre])+1);
    wsprintf(ws,perc_tt_tag,smenutexts[curitem],Genres[TagFile.Genre]);
    SetMenuItemText(data, item, ws, curitem);
    break;  
  }
}
void smenu_ghook(void *data, int cmd)
{
  //PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    //pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    //pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
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

int CreateTagMenu(void)
{
  int f;
  unsigned int ul;
  if((f=fopen(now_play,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    lseek(f,get_file_size(now_play)-128,S_SET,&ul,&ul);
    fread(f,&TagFile,128,&ul);
    fclose(f,&ul);
    if(TagFile.ID[0]=='T'&&TagFile.ID[1]=='A'&&TagFile.ID[2]=='G')
    {
      smenuhdr.icon=NULL;
      patch_header(&smenuhdr);
      TagMenu_ID=CreateMenu(0,0,&smenu,&smenuhdr,0,7,0,0);
      return TagMenu_ID;
    }
    else
    { //нет тега
      char s[256];
      char tags[128];
      snprintf(s,255,(char *)LG_ERFIND);
      ShowMSG(1,(int)s);
    //  return 0;
      tags[0]='T';
      tags[1]='A';
      tags[2]='G';
      if ((f=fopen(now_play,A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE+A_Truncate,&ul))!=-1)
      {
        fwrite(f,tags,128,&ul);
        fclose(f,&ul);
        ShowMSG(1,(int)"Тэги созданы");
        zeromem(tags,128);
      }
      //smenuhdr.icon=NULL;
     // patch_header(&smenuhdr);
     // TagMenu_ID=CreateMenu(0,0,&smenu,&smenuhdr,0,7,0,0);
     // return TagMenu_ID;
      return 0;
    }
  }
  else
  {
    //ошибка открытия файла
    char s[256];
    snprintf(s,255,(char *)LG_EROPEN);
    ShowMSG(1,(int)s);
    return 0;
  } 
}

SOFTKEY_DESC menu_sk1[]={{0,0,0}};

SOFTKEYSTAB menu_skt1 =
{
  menu_sk1, 0
};

int char16to8(int c)
{
  if (c < 0x400) return (c);
  c -= 0x400;
  if (c < 16)
  {
    if (c == 1) c = 0;  //big_yo
    else if (c == 4) c = 2;  //big_ye
    else if (c == 6) c = 10; //big_i
    else return (c);
  }
  else if (c > 79)
  {
    if (c == 0x51) c = 16; //small_yo
    else if (c == 0x54) c = 18; //small_ye
    else if (c == 0x56) c = 11; //small_i
    else if (c == 0x57) c = 23; //small_yi
    else return (c);
  }
  else c += 8;
  c += 168;
  return (c);
}

int inp_onkey(GUI *gui, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char ss[16];
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
  //В этом куске, вообще говоря, нет смысла, ибо при запущенном XTask
  //красная кнопка действует как "Назад"
  if(msg->gbsmsg->submess==RED_BUTTON)
  {
    return(1);//выходим без сохранения.
  }
  if((msg->gbsmsg->submess==GREEN_BUTTON)||(msg->keys==0x18))
  {
    ExtractEditControl(gui,1,&ec);
    wstrcpy(tmostr,ec.pWS);
    char *s;
    int len;
    switch(TypeField)
    {
    case 0:s=TagFile.Title;len=30;break;
    case 1:s=TagFile.Artist;len=30;break;
    case 2:s=TagFile.Album;len=30;break;
    case 3:s=TagFile.Year;len=4;break;
    case 4:s=TagFile.Comment;len=30;break;
    case 5:s=ss;len=28;break;
  }
  for(int i=0; i<tmostr->wsbody[0] && i<len; i++)
  {
    *s++=char16to8(tmostr->wsbody[i+1]);
  }
  *s=0;
  if(TypeField==5)TagFile.Track=strtol(ss,0,10);
 /* int f;
  unsigned int ul;
  if ((f=fopen(now_play,A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE,&ul))!=-1)
  {
    lseek(f,get_file_size(now_play)-128,S_SET,&ul,&ul);
    fwrite(f,&TagFile,128,&ul);
    //fread(f,&TagFile, sizeof(TagFile), &ul);
    fclose(f,&ul);
  }*/
  return(1); //Выходим
  }
  return(0); //Do standart keys
}

void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"ОK"};
  WSHDR *tmostr=EDIT_GetUserPointer(gui);
  if(cmd==2)
  {
    //Called after onCreate
  }
  if(cmd==3)
  {
    FreeWS(tmostr);
  }    
  if(cmd==7)
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
  &menu_skt1,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};


HEADER_DESC inp_hdr={0,0,131,21,NULL,(int)LG_EDITTAG,LGP_NULL};

int LaunchEditor(int type)
{
  int len;
  void *eq;
  TypeField=type;
  void *ma=malloc_adr();
  WSHDR *tagstr=AllocWS(256);
  WSHDR *gstr=AllocWS(256);
  switch(type)
  {
  case 0:
    wsprintf(tagstr,perc_t_tag,TagFile.Title);
    inp_hdr.lgp_id=(int)LG_TAG_TITLE;
    len=30;
    break;
  case 1:
    wsprintf(tagstr,perc_t_tag,TagFile.Artist);
    inp_hdr.lgp_id=(int)LG_TAG_ARTIST;
    len=30;
    break;
  case 2:
    wsprintf(tagstr,perc_t_tag,TagFile.Album);
    inp_hdr.lgp_id=(int)LG_TAG_ALBUM;
    len=30;
    break;
  case 3:
    wsprintf(tagstr,perc_t_tag,TagFile.Year);
    inp_hdr.lgp_id=(int)LG_TAG_YEAR;
    len=4;
    break;
  case 4:
    wsprintf(tagstr,perc_t_tag,TagFile.Comment);
    inp_hdr.lgp_id=(int)LG_TAG_COMMENT;
    len=30;
    break;
  case 5:
    wsprintf(tagstr,perc_d_tag,TagFile.Track);
    inp_hdr.lgp_id=(int)LG_TAG_TRACK;
    len=28;
    break;
  case 6:
    wsprintf(tagstr,perc_d_tag,TagFile.Genre);
    inp_hdr.lgp_id=(int)LG_TAG_GENRE;
    len=28;
    break;
  }
  EDITCONTROL ec;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,tagstr,len);
  AddEditControlToEditQend(eq,&ec,ma);
  inp_hdr.icon=NULL;
  patch_header(&inp_hdr);
  patch_input(&inp_desc);
  return CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,tagstr);
}
