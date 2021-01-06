#include "..\..\inc\swilib.h"
#include "..\cfg\conf_loader.h"

extern long elfload(char *filename, void *param1, void *param2, void *param3);
extern int get_file_size(const char * fname);

extern int EDL_system_init();
extern int EDL_system_reinit();
extern int EDL_system_kill();
extern int EDL_load_ep(char *fname);


/*  Оповещение об ошибки запуска  */ 

#define TYPE_ELF 0
#define TYPE_EDL 1

__arm int executer_and_messager(char *filename, void *param1, char type)
{
  char msg[96];
  
  int err;
  if (type == TYPE_ELF) err = elfload(filename,param1,0,0);
                   else err = EDL_load_ep(filename);
  if (err >= 0) return 0;
  else
   {
    char *fn = strrchr(filename,(int)'\\');
    sprintf(msg, "EP 3.0:\n%s\nerr: %d!", fn+1, err);
    MsgBoxError(1, (int)msg);
    return 1;       // Oшибка запуска
   }
}

/*  Вызов из Card-Explorer'a или My Stuff или ExecuteFile()  */
__arm int elf_onload(WSHDR *filename, WSHDR *ext, void *param)
{
  char fn[128];
  ws_2str(filename,fn,126);
  if (fn[1] != ':') param = 0;
  if (executer_and_messager(fn, param, TYPE_ELF)) return 0; else return 1;
}

__arm int edl_onload(WSHDR *filename, WSHDR *ext, void *param)
{
  char fn[128];
  ws_2str(filename,fn,126);
  if (executer_and_messager(fn, 0, TYPE_EDL)) return 0; else return 1;
}



extern void(*OldOnClose)(void *);
extern void(*OldOnCreate)(void *);


extern unsigned int DEFAULT_DISK_N;
extern void InitPngBitMap(void);








/* ---------------- Loading EDL Libs ---------------- */
__arm void LoadLibs()
{
  DIR_ENTRY de;
  unsigned int err;
  unsigned int pathlen;
  char name[256];
  strcpy(name+1,":\\ZBin\\Libs\\");
  name[0]=DEFAULT_DISK_N+'0';
  pathlen=strlen(name);
  strcat(name,"*.edl");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      name[pathlen]=0;
      strcat(name,de.file_name);
      executer_and_messager(name, 0, TYPE_EDL);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

/* ---------------- Loading Daemons ---------------- */


__arm void LoadDaemons()
{
  DIR_ENTRY de;
  WSHDR *ws=AllocWS(160);
  extern char folder_daemons[128];
  unsigned int err;
  unsigned int pathlen;
  pathlen=strlen(folder_daemons);
  strcat(folder_daemons,"*.elf");
  if (FindFirstFile(&de,folder_daemons,&err))
  {
    do
    {
      folder_daemons[pathlen]=0;
      strcat(folder_daemons,de.file_name);
      elfload(folder_daemons,0,0,0);
    }
    while(FindNextFile(&de,&err));
   }
  FindClose(&de,&err);
  FreeWS(ws);
  
}


//ELF
__no_init char smallicons_str[32];
__no_init char bigicons_str[32];

//EDL
__no_init char smallicons_edl_str[32];
__no_init char bigicons_edl_str[32];


__arm int mktree(char* path)
{
        unsigned int err;
	if (isdir(path, &err)) return 1;
	int len = strlen(path);
	char c;
	char buf[128];

	for(int ii=0;ii<len;ii++)
	{
		c = path[ii];
		if (c=='\\')
		{
			buf[ii]=0;
			mkdir(buf, &err);
		}  
		buf[ii]=c;
	}
	return mkdir(path, &err);
}

__arm void MyIDLECSMonCreate(void *data)
{
  //ELF
  static const int smallicons[2]={(int)smallicons_str,0};
  static const int bigicons[2]={(int)bigicons_str,0};
  //EDL
  static const int smallicons_edl[2]={(int)smallicons_edl_str,0};
  static const int bigicons_edl[2]={(int)bigicons_edl_str,0};
  
  
#ifdef NEWSGOLD
  static const REGEXPLEXT elf_reg=
  {
    "elf",
    0x55,
    0xFF,
    8, //Каталог Misc
    MENU_FLAG2,
    smallicons,
    bigicons,
    (int)"Open",    //LGP "Открыть"
    (int)"AltOpen", //LGP "Опции"
    LGP_DOIT_PIC,
    (void *)elf_onload,
    0
  };
  
  static const REGEXPLEXT edl_reg=
  {
    "edl",
    0xFFFF,
    0xFF,
    8, //Каталог Misc
    MENU_FLAG2,
    smallicons_edl,
    bigicons_edl,
    (int)"Open",    //LGP "Открыть"
    (int)"AltOpen", //LGP "Опции"
    LGP_DOIT_PIC,
    (void *)edl_onload,
    0
  };
  
#else
  static const REGEXPLEXT elf_reg=
  {
    "elf",
    0x55,
    0xFF,
    7,
    MENU_FLAG2,
    smallicons,
    bigicons,
    (void *)elf_onload,
    0
  };
  
  static const REGEXPLEXT edl_reg=
  {
    "edl",
    0xFFFF,
    0xFF,
    7,
    MENU_FLAG2,
    smallicons_edl,
    bigicons_edl,
    (void *)edl_onload,
    0
  };
#endif
  
  
    if (LoadConfigData("0:\\ZBin\\Elfpack\\ElfPack.bcfg")<0)
    if (LoadConfigData("1:\\ZBin\\ElfPack\\ElfPack.bcfg")<0)
    if (LoadConfigData("2:\\ZBin\\Elfpack\\ElfPack.bcfg")<0)
    if (LoadConfigData("4:\\ZBin\\Elfpack\\ElfPack.bcfg")<0)
    {
     mktree("0:\\ZBin\\Elfpack\\");
     LoadConfigData("0:\\ZBin\\Elfpack\\ElfPack.bcfg");
    }

  extern void CreateEPC_PROC();
  CreateEPC_PROC();
  
  extern void LoadLibrary();
  LoadLibrary();
  
  extern void DHS_init();
  DHS_init();
  
  EDL_system_init();
  
  InitPngBitMap();
  
  //ELF
  extern  char folder_img[128];
  sprintf(smallicons_str,"%self_small.png",folder_img);
  sprintf(bigicons_str,"%elf_big.png",folder_img);
  
  
  //EDL
  sprintf(smallicons_edl_str,"%edl_small.png",folder_img);
  sprintf(bigicons_edl_str,"%edl_big.png",folder_img);
    
  RegExplorerExt(&elf_reg);
  RegExplorerExt(&edl_reg);
  
  extern int edl_ena;
  if (edl_ena) LoadLibs();
  
  extern int subproc_daem;
  extern int key_break;
  
    #ifdef NEWSGOLD
  
  if(*RamPressedKey()!=key_break)
  {
  if (subproc_daem )
  SUBPROC((void *)LoadDaemons);
  else LoadDaemons();
  }
  #else
   if(*RamKeyBuffer()!=key_break)
  {
  if (subproc_daem )
  SUBPROC((void *)LoadDaemons);
  else LoadDaemons();
  }
  #endif
 
  extern BXR1(void *, void (*)(void *));
  BXR1(data,OldOnCreate);
}

__arm void MyIDLECSMonClose(void *data)
{
  extern BXR1(void *, void (*)(void *));
  extern void KillEPC_PROC();
  KillEPC_PROC();
  //EDL_system_kill();
  extern void DHS_kill();
  DHS_kill();
  
  BXR1(data,OldOnClose);
}




//Патчи
#pragma diag_suppress=Pe177
__root static const int NEW_ONCREATE @ "PATCH_ONCREATE" = (int)MyIDLECSMonCreate;
__root static const int NEW_ONCLOSE @ "PATCH_ONCLOSE" = (int)MyIDLECSMonClose;
#pragma diag_default=Pe177

