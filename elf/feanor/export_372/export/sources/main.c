#include "..\inc\swilib.h"
#include "..\siemens_unicode.h"
//#include <string.h>
/*
#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif*/

typedef struct
{
  unsigned short u;
  char dos;
  char win;
  char koi8;
} TUNICODE2CHAR;

const TUNICODE2CHAR unicode2char[]=
{
  // CAPITAL Cyrillic letters (base)
  0x410,0x80,0xC0,0xE1, // А
  0x411,0x81,0xC1,0xE2, // Б
  0x412,0x82,0xC2,0xF7, // В
  0x413,0x83,0xC3,0xE7, // Г
  0x414,0x84,0xC4,0xE4, // Д
  0x415,0x85,0xC5,0xE5, // Е
  0x416,0x86,0xC6,0xF6, // Ж
  0x417,0x87,0xC7,0xFA, // З
  0x418,0x88,0xC8,0xE9, // И
  0x419,0x89,0xC9,0xEA, // Й
  0x41A,0x8A,0xCA,0xEB, // К
  0x41B,0x8B,0xCB,0xEC, // Л
  0x41C,0x8C,0xCC,0xED, // М
  0x41D,0x8D,0xCD,0xEE, // Н
  0x41E,0x8E,0xCE,0xEF, // О
  0x41F,0x8F,0xCF,0xF0, // П
  0x420,0x90,0xD0,0xF2, // Р
  0x421,0x91,0xD1,0xF3, // С
  0x422,0x92,0xD2,0xF4, // Т
  0x423,0x93,0xD3,0xF5, // У
  0x424,0x94,0xD4,0xE6, // Ф
  0x425,0x95,0xD5,0xE8, // Х
  0x426,0x96,0xD6,0xE3, // Ц
  0x427,0x97,0xD7,0xFE, // Ч
  0x428,0x98,0xD8,0xFB, // Ш
  0x429,0x99,0xD9,0xFD, // Щ
  0x42A,0x9A,0xDA,0xFF, // Ъ
  0x42B,0x9B,0xDB,0xF9, // Ы
  0x42C,0x9C,0xDC,0xF8, // Ь
  0x42D,0x9D,0xDD,0xFC, // Э
  0x42E,0x9E,0xDE,0xE0, // Ю
  0x42F,0x9F,0xDF,0xF1, // Я
  // CAPITAL Cyrillic letters (additional)
  0x402,'_',0x80,'_', // _ .*.*
  0x403,'_',0x81,'_', // _ .*.*
  0x409,'_',0x8A,'_', // _ .*.*
  0x40A,'_',0x8C,'_', // _ .*.*
  0x40C,'_',0x8D,'_', // _ .*.*
  0x40B,'_',0x8E,'_', // _ .*.*
  0x40F,'_',0x8F,'_', // _ .*.*
  0x40E,0xF6,0xA1,'_', // Ў ...*
  0x408,0x4A,0xA3,0x4A, // _ .*.*
  0x409,0x83,0xA5,0xBD, // _ .*..
  0x401,0xF0,0xA8,0xB3, // Ё
  0x404,0xF2,0xAA,0xB4, // Є
  0x407,0xF4,0xAF,0xB7, // Ї
  0x406,0x49,0xB2,0xB6, // _ .*..
  0x405,0x53,0xBD,0x53, // _ .*.*
  // SMALL Cyrillic letters (base)
  0x430,0xA0,0xE0,0xC1, // а
  0x431,0xA1,0xE1,0xC2, // б
  0x432,0xA2,0xE2,0xD7, // в
  0x433,0xA3,0xE3,0xC7, // г
  0x434,0xA4,0xE4,0xC4, // д
  0x435,0xA5,0xE5,0xC5, // е
  0x436,0xA6,0xE6,0xD6, // ж
  0x437,0xA7,0xE7,0xDA, // з
  0x438,0xA8,0xE8,0xC9, // и
  0x439,0xA9,0xE9,0xCA, // й
  0x43A,0xAA,0xEA,0xCB, // к
  0x43B,0xAB,0xEB,0xCC, // л
  0x43C,0xAC,0xEC,0xCD, // м
  0x43D,0xAD,0xED,0xCE, // н
  0x43E,0xAE,0xEE,0xCF, // о
  0x43F,0xAF,0xEF,0xD0, // п
  0x440,0xE0,0xF0,0xD2, // р
  0x441,0xE1,0xF1,0xD3, // с
  0x442,0xE2,0xF2,0xD4, // т
  0x443,0xE3,0xF3,0xD5, // у
  0x444,0xE4,0xF4,0xC6, // ф
  0x445,0xE5,0xF5,0xC8, // х
  0x446,0xE6,0xF6,0xC3, // ц
  0x447,0xE7,0xF7,0xDE, // ч
  0x448,0xE8,0xF8,0xDB, // ш
  0x449,0xE9,0xF9,0xDD, // щ
  0x44A,0xEA,0xFA,0xDF, // ъ
  0x44B,0xEB,0xFB,0xD9, // ы
  0x44C,0xEC,0xFC,0xD8, // ь
  0x44D,0xED,0xFD,0xDC, // э
  0x44E,0xEE,0xFE,0xC0, // ю
  0x44F,0xEF,0xFF,0xD1, // я
  // SMALL Cyrillic letters (additional)
  0x452,'_',0x90,'_', // _ .*.*
  0x453,'_',0x83,'_', // _ .*.*
  0x459,'_',0x9A,'_', // _ .*.*
  0x45A,'_',0x9C,'_', // _ .*.*
  0x45C,'_',0x9D,'_', // _ .*.*
  0x45B,'_',0x9E,'_', // _ .*.*
  0x45F,'_',0x9F,'_', // _ .*.*
  0x45E,0xF7,0xA2,'_', // ў ...*
  0x458,0x6A,0xBC,0x6A, // _ .*.*
  0x491,0xA3,0xB4,0xAD, // _ .*..
  0x451,0xF1,0xB8,0xA3, // ё
  0x454,0xF3,0xBA,0xA4, // є
  0x457,0xF5,0xBF,0xA7, // ї
  0x456,0x69,0xB3,0xA6, // _ .*..
  0x455,0x73,0xBE,0x73, // _ .*.*
  0x0A0,'_',0xA0,0x20, // space .*..
  0x0A4,'_',0xA4,0xFD, // ¤   .*..
  0x0A6,'_',0xA6,'_', // ¦   .*.*
  0x0B0,0xF8,0xB0,0x9C, // °
  0x0B7,0xFA,0xB7,0x9E, // ·
  // 0x2022,,0x95,0x95, //    .*..
  // 0x2116,0xFC,0xB9,0x23, // №   ...*
  // 0x2219,,0xF9,0x9E, //    .*..
  // 0x221A,0xFB,,0x96, // v   ..*.
  // 0x25A0,0xFE,,0x94, // ¦
  0x0000,0,0,0
};

const unsigned short win2unicode[128]=
{
  0x0402,0x0403,0x201A,0x0453,0x201E,0x2026,0x2020,0x2021,
  0x20AC,0x2030,0x0409,0x2039,0x040A,0x040C,0x040B,0x040F,
  0x0452,0x2018,0x2019,0x201C,0x201D,0x2022,0x2013,0x2014,
  0x0020,0x2122,0x0459,0x203A,0x045A,0x045C,0x045B,0x045F,
  0x00A0,0x040E,0x045E,0x0408,0x00A4,0x0490,0x00A6,0x00A7,
  0x0401,0x00A9,0x0404,0x00AB,0x00AC,0x00AD,0x00AE,0x0407,
  0x00B0,0x00B1,0x0406,0x0456,0x0491,0x00B5,0x00B6,0x00B7,
  0x0451,0x2116,0x0454,0x00BB,0x0458,0x0405,0x0455,0x0457,
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F
};

unsigned int char8to16(int c)
{
  if (c<0x20 && c!='\r' && c!='\n') {return(c+0xE000);}
  if (c>=128) {return(win2unicode[c-128]);}
  return(c);
}

unsigned int char16to8(unsigned int c)
{
  const TUNICODE2CHAR *p=unicode2char;
  unsigned int i;
  if (c<32) return(' ');
  if (c<128) return(c);
  while((i=p->u))
  {
    if (c==i)
    {
      return(p->win);
    }
    p++;
  }
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}
//================================================

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===================================================================

#include "visual.c"


WSHDR *ews;

typedef struct
{
  char alias[128];
  char path [256];
}ALIAS;

ALIAS *aliases;
int recs;
char dbpath[255];
GUI *ddata;
//=================================================================================================

int LoadDB(char* filename);

void Add(char *txt)
{
  unsigned int ul;
  int f=fopen(dbpath,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,"ALIAS: ",5+2,&ul);
    fwrite(f,txt,strlen(txt),&ul);
    fwrite(f,"\r\n",2,&ul);
    fclose(f,&ul);
  }
  //mfree(txt);
  LoadDB(dbpath);
}

//=================================================================================================
int file_exists(const char *fname)
{
  int handle;
  unsigned int err;
  handle = fopen(fname, A_ReadOnly, P_READ, &err);
  if (handle == -1)
    return 0;
  fclose(handle, &err);
  return 1;
}

int get_file_size(const char *fname)
{
  if (!file_exists(fname)) return -1;
  FSTATS stats;
  unsigned int err;
  if (GetFileStats(fname, &stats, &err)) return -1;
  return (stats.size);
}


int LoadDB(char* filename)
{
  int fsize;
  if (!filename)                  {MsgBoxError(1, (int)"Пустое имя файла!");return 1;}
  if (!file_exists(filename))     {Add("about \'Console.elf. See readme.txt\'\r\n");return 2;}
  
  
  char *database = malloc(fsize = get_file_size(filename));
  int hFile;
  unsigned int err;
  hFile = fopen(filename, A_ReadOnly, P_READ, &err);
  
  if (hFile == -1)                 {MsgBoxError(1, (int)"Не могу открыть файл!"); return 3;}
  
  fread(hFile, database, fsize, &err);
  fclose(hFile, &err);
  
  
  
   int i,j=0,k=0;
   for (i=0; database[i]!=0; i++){if (database[i]=='\r') recs++;}

   aliases = realloc(aliases,sizeof(ALIAS)*recs);
    
   for (i=0; i!=recs; i++)
    {
        memset(aliases[i].alias,'\0',127);
        memset(aliases[i].path,'\0',255);
    }
   for (i=0; database[i]!=0; i++)
    {
       if (k==0 && database[i]!=' ') {continue;}
       if (k==0 && database[i]==' ') {k++; continue;}
       if (k==1 && database[i]!=' ') {aliases[j].alias[strlen(aliases[j].alias)]=database[i];  continue;}
       if (k==1 && database[i]==' ') {k++; continue;}
       if (k==2 && database[i]=='\r') {k=0; j++; continue;}
       if (k==2) {aliases[j].path[strlen(aliases[j].path)]=database[i];    continue;}
    }
  if (database) mfree(database);
  return 0;
}

//=================================================================================================

void AddStrToLog(char *s, char is_newstr)
{
      EDITCONTROL ec;
      ExtractEditControl(ddata,1,&ec);
      WSHDR *log;
      log=AllocWS(ec.pWS->wsbody[0]+strlen(s)+10);
      
      if(is_newstr) {wsprintf(log,"%w\r",ec.pWS);}
      else      {wsprintf(log,"%w",ec.pWS);}
      
      for (int i=0; s[i]!=0; i++) {wsAppendChar(log,char8to16(s[i]));}
        
      if(wstrlen(log)>8195){ wsRemoveChars(log,0,wstrlen(log)-8195 );}
      EDIT_SetTextToEditControl(ddata,1,log);
      REDRAW();
}



void ClearInput()
{
      WSHDR *ws=AllocWS(2);
      char _empty[]="";
      wsprintf(ws,_empty);
      EDIT_SetTextToEditControl(ddata,3,ws);
      FreeWS(ws);
}

void Execute(char *path, char *param)
{
  if(path[1]==':')
  {
      str_2ws(ews,path,128);
      ExecuteFile(ews,0,param); 
  }
     
  if(path[0]=='A' || path[0]=='a')
  {
    int addr;
    sscanf(path,"%08X",&addr);
    SUBPROC((void *)addr);
  }
     
  if(path[4]=='_')
  {
    SUBPROC(GetFunctionPointer(path));
  }
     
  if(path[0]=='\"' || path[0]=='\'')
  {
    AddStrToLog(path,1);
  }
}


int GetAliasID(char alias[128])
{   
     for (int i=recs-1; i!=-1; i--)
     {
       if (!strcmp_nocase(alias,aliases[i].alias)) return i;
     }
     
    return 0xDEAD;
}


/*void AddWSToLog(WSHDR *ws)
{
#error "AddWSToLog does not work correctly"
      EDITCONTROL ec;
      ExtractEditControl(ddata,1,&ec);
      WSHDR *log;
      log=AllocWS(ec.pWS->wsbody[0]+ws->wsbody[0]+10);
      wsprintf(log,"%w\r%w",ec.pWS,ws);
      
      if(wstrlen(log)>8195){ wstrcpybypos(log,log,wstrlen(log)-8195,8195);}
      
      EDIT_SetTextToEditControl(ddata,1,log);
}*/

//=================================================================================================

static const char percent_t[]="%t";

int icon[]={0x58,0};
const int minus11=-11;

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

int my_csm_id;

void ed1_locret(void){}





int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==GREEN_BUTTON && EDIT_GetFocus(data)==3)
    {
      ExtractEditControl(data,3,&ec);
      
      char comm[255], param[255];
      
      memset(comm,0,255); memset(param,0,255);  //Буратино дали два яблока, он съел одно. Сколько яблоку него осталось? Одно? Нифига. Ведь неизвестно, сколько яблок быдо у него изначально. Мораль - обнуляйте переменные.
      
      for (int i=1; i!=ec.pWS->wsbody[0]+1; i++) {comm[i-1] = char16to8(ec.pWS->wsbody[i]);} //В comm пишем содержимое введенной строки
      
      ClearInput(); //чистим поле ввода
      
      if(strstr(comm," ")!=0 ) strcpy(param,strstr(comm," ")+1); else strncpy(param,"\0",1);
      if(strstr(comm," ")!=0 ) strstr(comm," ")[0]=0;
      //разбираем comm на собстна команду (в comm) и параметры (в param)
      
      if(strlen(comm)<1 && strlen(param)<1) return(-1); //нафиг нам пустая команда?
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      char addtolog[255];
      sprintf(addtolog,"\x13%s \x12%s", comm,param);
      AddStrToLog(addtolog,1);

      
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

      //некоторые команды лучше вшить в сам эльф. Но это не тру.
      if(strcmp_nocase(comm, "add")==0)
      {
        if(strlen(param)>0) Add(param);
        return -1;
      }      
      
      if(strcmp_nocase(comm, "clear")==0)
      { 
      wsprintf(ews,"Console%c",UTF16_FONT_SMALL);
      EDIT_SetTextToEditControl(data,1,ews);
      return -1;
      }
      
      if(strcmp_nocase(comm, "list")==0)
      { 
       for (int i=0; i!=recs; i++)
        {
          sprintf(addtolog,"%i:\x13%s \x12%s",i,aliases[i].alias, aliases[i].path);
          AddStrToLog(addtolog,1);
        }
        return -1;
      }
      
      if(strcmp_nocase(comm, "quit")==0 ||strcmp_nocase(comm, "exit")==0 || strcmp_nocase(comm, "halt")==0 ){ CloseCSM(my_csm_id); return -1;}
 //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -            
      int id;
      if ((id=GetAliasID(comm))!=0xDEAD)
      {
      //AddStrToLog(aliases[id].path);
      Execute(aliases[id].path, param);
      }
      else
      {
      AddStrToLog(">> Unknown command",1);
      }
 //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -      

      return(-1);
    }
    
    if (msg->gbsmsg->submess==ENTER_BUTTON && EDIT_GetFocus(data)==3)
    {            
      EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,1);
      return(-1);
  /*wsprintf(ews,"pressed key 1");
  IPC_REQ tmr_gipc;
  tmr_gipc.name_to="Console";
  tmr_gipc.name_from="self";
  tmr_gipc.data=(void*)ews;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&tmr_gipc);*/  
    }
    if(EDIT_GetFocus(data)==1 && msg->gbsmsg->submess>='0' && msg->gbsmsg->submess<='9'){EDIT_SetFocus(data, 3); return(-1);}
  }
   //if(EDIT_GetFocus(data)==1 && msg->gbsmsg->submess>='*' && msg->gbsmsg->msg==KEY_UP){EDIT_SetFocus(data, 3); return(-1);}
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}


void *edit_data;
void ed1_ghook(GUI *data, int cmd)
{
  if(cmd==TI_CMD_CREATE) ddata=data;
  EDITCONTROL ec;
  int i;

}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"Run",LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  1,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;  
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());


  wsprintf(ews,"Console. Rebuilded at: %s %s",__DATE__,__TIME__/*dbpath*/);
  ConstructEditControl(&ec,3,0x40,ews,16384);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"___________________");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"");
  ConstructEditControl(&ec,3,0x40,ews,256);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);
  
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}


void maincsm_oncreate(CSM_RAM *data)
{
  LoadDB(dbpath);
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(16384);
  csm->gui_id=create_ed();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  if (aliases) mfree(aliases);
  FreeWS(ews);
  SUBPROC((void *)Killer);
}


int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  
   if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      	if ( (ipc=(IPC_REQ*)msg->data0) && strcmp_nocase(ipc->name_to,"Console")==0)
	{
      EDITCONTROL ec;
      ExtractEditControl(ddata,1,&ec);
      AddStrToLog((char*)ipc->name_from,1);
      }
    }
   
   
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      /*if (ed1_desc._0x40000000)
      {
	ed1_desc._0x40000000<<=1;
	csm->gui_id=create_ed();
      }
      else*/
      {
	csm->csm.state=-3;
      }
    }
  }
 
  return(1);
}

unsigned short maincsm_name_body[140];

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Console");
}

int main(char *exename, char *fname)
{
  strcpy(dbpath,exename);
  dbpath[strlen(dbpath)-1]='t';
  dbpath[strlen(dbpath)-2]='x';
  dbpath[strlen(dbpath)-3]='t';
  
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  UpdateCSMname();
  my_csm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
