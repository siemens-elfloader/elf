#pragma once
#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
//#include "pnglist.h"
#include "language.h"
#include "mainmenu.h"

//==============================================================================
// ELKA Compatibility
#pragma inline
static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()-1+YDISP;
}
/*
#pragma inline
static void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}
*/
//==============================================================================
int SetMenu_ID;

extern  int curblock;
#define __SVN_REVISION__  1007
int sS_ICONS[3];
static const SOFTKEY_DESC smenu_sk[] =
{
  {0x0018, 0x0000, (int)LG_SELECT},
  {0x0001, 0x0000, (int)LG_CLOSE},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB smenu_skt =
{
  smenu_sk, 0
};




  extern const char *successed_config_filename;

 void ExecFile(char *name)
{
  WSHDR *ws;
  ws=AllocWS(130);
  str_2ws(ws,name,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);

}

extern IPC_REQ gipc;

unsigned char bp[BL_SZ_5402];
extern const char f5401s[];
extern const char f5402s[];

int WriteFile(char *name, unsigned char *filebuf, int size) {
  int f;
  char *buf=NULL,*bufs;
  const int c=((size<<1)+size)+(size>>3);//==3*size+size/16*2 == по 3 символа на 16-ричное число + 2-байтовый перевод строки после каждых 16 байт

  buf=malloc(c);
  if (!buf)
    return 0;
  memset(buf, 0, c);
  bufs=buf;

  unsigned int ul;
  if ((f=fopen(name, A_BIN+A_Truncate+A_Create+A_WriteOnly, 0, &ul))!=-1) {
    for (int i=0; i<(size>>4); i++) {
      for (int j=0; j<16; j++) {
        buf+=sprintf(buf, "%02X ", *filebuf++);
      }
      *buf++='\r';
      *buf++='\n';
    }
    fwrite(f, bufs, c, &ul);
    fclose(f, &ul);
  }

  mfree(bufs);
  return 1;
}




unsigned char htoi(char c)
{
  if ((c >= '0') && (c <='9'))
    return c - '0';
  if ((c >= 'A') && (c <='F'))
    return c - ('A' - 0xA) ;
  return 0;
}



int ReadFile(char *name)
{
  int size;
  int i, cnt;
  char *filebuf=NULL;

//  char Block5400[1024];

  int f;
  unsigned ul;
  if ((f=fopen(name,A_BIN,P_READ,&ul))!=-1){
    size=lseek(f,0,S_END,&ul,&ul);
    filebuf=malloc(size+1);
    if (filebuf){
      lseek(f,0,S_SET,&ul,&ul);
      fread(f,filebuf,size,&ul);
      fclose(f,&ul);

  // parse file
      cnt = 0;

      for (i=0;i<size;i++)
        if (filebuf[i] > 32)
          bp[cnt++] = (htoi(filebuf[i++])<<4) + htoi(filebuf[i++]) ;
      mfree(filebuf);
      return cnt;
    };

  }
  return 0;

}



static void LoadBlock(void) //from flie
{

  if ((ReadFile((char*)f5401s))==BL_SZ_5401){
    EEFullWriteBlock(5401, bp, 0, BL_SZ_5401,0,0);

  }else {

      MsgBoxError(1,(int)LG_MSGERRBLOCK);
  }
      GeneralFuncF1(1);

}

static void LoadBlock1(void) //from flie
{
  if (ReadFile((char*)f5402s)==BL_SZ_5402){
    EEFullWriteBlock(5402, bp, 0, BL_SZ_5402,0,0);


  }else {
      MsgBoxError(1,(int)LG_MSGERRBLOCK);


  }
      GeneralFuncF1(1);
}

static void FixBlock(void) //from flie
{

  EEFullReadBlock(5402, bp, 0, BL_SZ_5402,0,0);
  for(int i=0;i<MAX_SIM_CNT;i++)
   bp[0x50*i+0x2f]=i;
  EEFullWriteBlock(5402, bp, 0, BL_SZ_5402,0,0);

  EEFullReadBlock(5403, bp, 0, BL_SZ_5403,0,0);
   bp[0x2f]=0;
  EEFullWriteBlock(5403, bp, 0, BL_SZ_5403,0,0);
      GeneralFuncF1(1);
}


static void SaveBlock(void)
{
   EEFullReadBlock(5401, bp, 0, BL_SZ_5401,0,0);
   WriteFile((char*)f5401s,bp,BL_SZ_5401);
//   GeneralFuncF1(1);

  //add hash checking

	  //поидее надо дождаться callback
   //    WriteFile();
}

static void SaveBlock1(void)
{
   EEFullReadBlock(5402, bp, 0, BL_SZ_5402,0,0);
   WriteFile((char*)f5402s,bp,BL_SZ_5402);
//   GeneralFuncF1(1);
}



extern const char *successed_config_filename;


static void OpenCfg(void) //from flie
{
  ExecFile((char*)successed_config_filename);
}

static void OpenBlock(void) //from flie
{
  ExecFile((char*)f5401s);
}

static void OpenBlock1(void) //from flie
{
  ExecFile((char*)f5402s);
}

static const HEADER_DESC smenuhdr={0,0,0,0,NULL,(int)LG_MENU,LGP_NULL};

static const int smmenusoftkeys[]={0,1,2};

static const char * const smenutexts[]=
{
  LG_MNUASNET,
  LG_MNUCFG,
  LG_MNUSAVEB,
  LG_MNULOADB,

  LG_MNUOPENB,
  LG_MNUSAVEB1,
  LG_MNULOADB1,
  LG_MNUOPENB1,
  LG_MNUFIX,

};

extern void SendRequest(int submess, void *data);
static void AutoNet(void)
{
  SendRequest(IPC_MSIM_EEPROM_AUTOSEARCH,(void*)0);
  GeneralFuncF1(1);
//  GeneralFuncF1(1);
}
static const void *smenuprocs[]=
{
  (void *)AutoNet,
  (void *)OpenCfg,
  (void *)SaveBlock,
  (void *)LoadBlock,
  (void *)OpenBlock,
  (void *)SaveBlock1,
  (void *)LoadBlock1,
   (void *)OpenBlock1,
   (void *)FixBlock
};

void stmenu_ghook(void *data, int cmd)
{
  if (cmd==9)
  {}
  if (cmd==0x0A)
  {
    DisableIDLETMR();

   Menu_SetItemCountDyn(data,9);

//    if (simnum<3+simcnt)      SetCursorToMenuItem(data,2+simnum);
  }
}

//static int sicon_array[2];



static void smenuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);

  const char percent_t[]="%t";
//  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(smenutexts[curitem]));
  wsprintf(ws,percent_t,smenutexts[curitem]);

    SetMenuItemText(data, item, ws, curitem);

}

static int stmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
      ((void (*)(void))(smenuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}


static const MENU_DESC stmenu=
{
  8,stmenu_keyhook,stmenu_ghook,NULL,
  smmenusoftkeys,
  &smenu_skt,
  0x10,//MENU_FLAG,
  smenuitemhandler,
  NULL,//menuitems,
  NULL,//menuprocs,
  8
};

int ShowSetMenu()
{
  sS_ICONS[0]=(int)DEFAULT_DISK_CFG ":\\zbin\\naticq\\img\\online.png";
  sS_ICONS[1]=(int)DEFAULT_DISK_CFG ":\\zbin\\naticq\\img\\offline.png";
  sS_ICONS[2]=0;
//  sicon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
//  sicon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  *((int **)(&smenuhdr.icon))=sS_ICONS;
  patch_header(&smenuhdr);
  SetMenu_ID=CreateMenu(0,0,&stmenu,&smenuhdr,0,11,0,0);
  return SetMenu_ID;
}
