#include "include.h"
#include "File.h"
#include "LangPack.h"



const char df_LGP_OK[]="OK";
const char df_LGP_BACK[]="Back";
const char df_LGP_ADRBK[]="AddressBook";
const char df_LGP_ERR[]="Error!";
const char df_LGP_SELECT[]="Select";
const char df_LGP_QUIT[]="Quit";
const char df_LGP_NEW[]="NewSMS";
const char df_LGP_IN_R[]="InReaded";
const char df_LGP_IN_N[]="InNew";
const char df_LGP_IN_A[]="InBox";
const char df_LGP_SENT[]="Sent";
const char df_LGP_DRAFT[]="Draft";
const char df_LGP_ALL[]="AllSMS";
const char df_LGP_OPTIONS[]="Options";
const char df_LGP_ERR_0NUM[]="No Number !";
const char df_LGP_EXIT[]="Exit";
const char df_LGP_CANCEL[]="Cancel";
const char df_LGP_SEND[]="Send";
const char df_LGP_DEL[]="Delete";
const char df_LGP_SAVE_AS_FILE[]="Save As File";
const char df_LGP_SAVE_AS_DRAFT[]="Save As Draft";
const char df_LGP_INSERT_ADRNUM[]="Insert Number Form AddressBook";
const char df_LGP_INSERT_BLANKNUM[]="Insert Blank Number";
const char df_LGP_CHAR_COUNT[]="Count";
const char df_LGP_VIEW[]="View";
const char df_LGP_EDIT[]="Edit";
const char df_LGP_REPLY[]="Reply";
const char df_LGP_NEW_MSG[]="New Message!";
const char df_LGP_FROM[]="From";
const char df_LGP_CODESHOW[]="CodeShow";
const char df_LGP_FETION[]="Fetion";
const char df_LGP_SAVEALL[]="Save All As File";
const char df_LGP_CONFIG_UPDATE[]="MySMSYS Config Updated!";
const char df_LGP_CONFIG[]="Settings";
const char df_LGP_SAVE_ALL_ONE[]="Export All To One TXT";
const char df_LGP_PLS_INPUT_PATH[]="Please Input The File Path:";
const char df_LGP_OTHERS[]="Others";
const char df_LGP_FILE_FAILED[]="File Operate Failed!";
const char df_LGP_FILE_EXIST[]="File Existed!";
const char df_LGP_EXPORT_TXT[]="Export As Txt";
const char df_LGP_MOVE_ARCHIVE[]="Move To Archive";
const char df_LGP_MOVE_ALL_MSS[]="Move All MSS To Archive";
const char df_LGP_OPEN_ARCHIVE[]="Open Archive";
const char df_LGP_EXPORT_N[]="Export %d SMS Successfully!";
const char df_LGP_MOVE_MSSARCHIVER_N[]="Move %d Mss File to Archive Successfully!";
const char df_LGP_DEL_ALL_MSS[]="Delete All Mss Files?";
const char df_LGP_ABOUT[]="About...";
const char df_LGP_COV_DAT_TXT[]="Cov SMS.dat To Txt";
const char df_LGP_SAVE_ALL_AS_FILE[]="Save All As Files";
const char df_LGP_SAF_N[]="Save %d SMS Successfully!";
const char df_LGP_DEL_ALL[]="Delete All?";
const char df_LGP_DEL_ALL_MSG[]="Delete All Message";
const char df_LGP_MOVE_ALL[]="Move All To Archive";
const char df_LGP_DEL_ALL_MSG_MSS[]="Delete All Mss";
const char df_LGP_SAVE[]="Save";
const char df_LGP_MSG_REPORT[]="Message Report";
const char df_LGP_MSG_REVEICED[]="Message received at"; //后加时间
const char df_LGP_UNK_RP_STATUS[]="SMS Report: Unknow Status";
const char df_LGP_TEMPLATE[]="Template";
const char df_LGP_CALL_ADDRESSBOOK[]="Call Addressbook";
const char df_LGP_STATISTICS[]="Statistics";
const char df_LGP_IN_SMSDAT[]="in SMS.dat";
const char df_LGP_IS_MSSFILE[]="is Mss File";
const char df_LGP_DAT_FREE[]="Free";
const char df_LGP_DISK_FREE[]="Free in Disk";
const char df_LGP_MSS_MAINMENU[]="Mss MainMenu";
const char df_LGP_TRANSLIT[]="Translit";
const char df_LGP_TIME[]="Time";
const char df_LGP_UNK_NUM[]="Unknow Number";
const char df_LGP_NUMBER[]="Number";
const char df_LGP_TEXT[]="Text";
const char df_LGP_TO[]="To";
const char df_LGP_UNK[]="Unknow";
const char df_LGP_FILTER[]="Fliter";
const char df_LGP_INSERT_NUM[]="Ins. Num";
const char df_LGP_HELP[]="Help";
const char df_LGP_DEL_N[]="%d SMS Deleted!";
const char df_LGP_CALL[]="Call";

const char *df_LGPS[]=
{
  df_LGP_OK,
  df_LGP_BACK,
  df_LGP_ADRBK,
  df_LGP_ERR,
  df_LGP_SELECT,
  df_LGP_QUIT,
  df_LGP_NEW,
  df_LGP_IN_R,
  df_LGP_IN_N,
  df_LGP_IN_A,
  df_LGP_SENT,
  df_LGP_DRAFT,
  df_LGP_ALL,
  df_LGP_OPTIONS,
  df_LGP_ERR_0NUM,
  df_LGP_EXIT,
  df_LGP_CANCEL,
  df_LGP_SEND,
  df_LGP_DEL,
  df_LGP_SAVE_AS_FILE,
  df_LGP_SAVE_AS_DRAFT,
  df_LGP_INSERT_ADRNUM,
  df_LGP_INSERT_BLANKNUM,
  df_LGP_CHAR_COUNT,
  df_LGP_VIEW,
  df_LGP_EDIT,
  df_LGP_REPLY,
  df_LGP_NEW_MSG,
  df_LGP_FROM,
  df_LGP_CODESHOW,
  df_LGP_FETION,
  df_LGP_SAVEALL,
  df_LGP_CONFIG_UPDATE,
  df_LGP_CONFIG,
  df_LGP_SAVE_ALL_ONE,
  df_LGP_PLS_INPUT_PATH,
  df_LGP_OTHERS,
  df_LGP_FILE_FAILED,
  df_LGP_FILE_EXIST,
  df_LGP_EXPORT_TXT,
  df_LGP_MOVE_ARCHIVE,
  df_LGP_MOVE_ALL_MSS,
  df_LGP_OPEN_ARCHIVE,
  df_LGP_EXPORT_N,
  df_LGP_MOVE_MSSARCHIVER_N,
  df_LGP_DEL_ALL_MSS,
  df_LGP_ABOUT,
  df_LGP_COV_DAT_TXT,
  df_LGP_SAVE_ALL_AS_FILE,
  df_LGP_SAF_N,
  df_LGP_DEL_ALL,
  df_LGP_DEL_ALL_MSG,
  df_LGP_MOVE_ALL,
  df_LGP_DEL_ALL_MSG_MSS,
  df_LGP_SAVE,
  df_LGP_MSG_REPORT,
  df_LGP_MSG_REVEICED, //后加时间
  df_LGP_UNK_RP_STATUS,
  df_LGP_TEMPLATE,
  df_LGP_CALL_ADDRESSBOOK,
  df_LGP_STATISTICS,
  df_LGP_IN_SMSDAT,
  df_LGP_IS_MSSFILE,
  df_LGP_DAT_FREE,
  df_LGP_DISK_FREE,
  df_LGP_MSS_MAINMENU,
  df_LGP_TRANSLIT,
  df_LGP_TIME,
  df_LGP_UNK_NUM,
  df_LGP_NUMBER,
  df_LGP_TEXT,
  df_LGP_TO,
  df_LGP_UNK,
  df_LGP_FILTER,
  df_LGP_INSERT_NUM,
  df_LGP_HELP,
  df_LGP_DEL_N,
  df_LGP_CALL,
  0,
};

void LangPack::FreeLangPack(void)
{
  LoadLgpDefault();
  if(this->lang_buf)
  {
    delete this->lang_buf;
    this->lang_buf=NULL;
  }
}

void LangPack::LoadLangPack(void)
{
  LoadLgpDefault();
  LoadLangFile();
  InitLgp();
}

void LangPack::LoadLangFile(void)
{
  char fpath[128], *p, **lp, *pp;
  int /*len, c,*/ fin, size, mn, i;
  strcpy(fpath, main_folder);
  //len=strlen(fpath);
  //c=fpath[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  fpath[len]='\\';
  //  fpath[len+1]=0;
  //}
  if(!IsDir(fpath))
    return;
  strcat(fpath, "lang.txt");
  if((fin=FOpen(fpath, A_BIN+A_ReadOnly, P_READ))==-1)
    return;
  size=LSeek(fin, 0, S_END);
  if(!size)
  {
    FClose(fin);
    return;
  }
  this->lang_buf=new char[(size+3)&(~3)];
  LSeek(fin, 0, S_SET);
  if(FRead(fin, lang_buf, size)!=size)
  {
    FClose(fin);
    return;
  }
  FClose(fin);
  this->lang_buf[size]=0;
  p=this->lang_buf;
  lp=(char **)(&lgp);
  mn=sizeof(LGPACK)/sizeof(char *);
  for(i=0;i<mn;i++)
  {
    if(!(pp=GotoLangLineStart(p)))
      break;
    lp[i]=pp;
    if(!(pp=GotoLangLineEnd(pp)))
      break;
    *pp++=0;
    p=pp;
  }
}

void LangPack::LoadLgpDefault(void)
{
  memcpy(&this->lgp, df_LGPS, sizeof(LGPACK));
}

char *LangPack::GotoLangLineEnd(char *buf)
{
  int c;
  char *p=buf;
  while((c=*p))
  {
    if(c=='\r' || c=='\n')
      return p;
    p++;
  }
  return 0;
}

char *LangPack::GotoLangLineStart(char *buf)
{
  int c;
  char *p=buf;
  while((c=*p))
  {
    if(c>=0x1F)
      return p; 
    p++;
  }
  return 0;
}
  

void LangPack::InitLgp(void)
{
  //mainmenu.cpp
  extern SOFTKEY_DESC main_menu_sk[]; 
  extern HEADER_DESC main_menuhdr;
  extern int MM_ITEM_LGPS[];
  main_menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  main_menu_sk[1].lgp_id=(int)lgp.LGP_QUIT;
  main_menuhdr.lgp_id=(int)lgp.LGP_MSS_MAINMENU;
  MM_ITEM_LGPS[0]=(int)lgp.LGP_NEW;
  MM_ITEM_LGPS[1]=(int)lgp.LGP_IN_N;
  MM_ITEM_LGPS[2]=(int)lgp.LGP_IN_A;
  MM_ITEM_LGPS[3]=(int)lgp.LGP_SENT;
  MM_ITEM_LGPS[4]=(int)lgp.LGP_DRAFT;
  MM_ITEM_LGPS[5]=(int)lgp.LGP_OTHERS;

  //SmsListMenu.cpp
  extern SOFTKEY_DESC sms_menu_sk[];
  extern int SLM_HDR_LGPS[];
  extern int SOP_ITEM_LGPS[];
  sms_menu_sk[0].lgp_id=(int)lgp.LGP_OPTIONS;
  sms_menu_sk[1].lgp_id=(int)lgp.LGP_BACK;
  SLM_HDR_LGPS[0]=(int)lgp.LGP_FILTER;
  SLM_HDR_LGPS[1]=(int)lgp.LGP_SENT;
  SLM_HDR_LGPS[2]=(int)lgp.LGP_IN_R;
  SLM_HDR_LGPS[3]=(int)lgp.LGP_IN_N;
  SLM_HDR_LGPS[4]=(int)lgp.LGP_DRAFT;
  SLM_HDR_LGPS[5]=(int)lgp.LGP_IN_A;
  
  SOP_ITEM_LGPS[0]=(int)lgp.LGP_REPLY;
  SOP_ITEM_LGPS[1]=(int)lgp.LGP_EDIT;
  SOP_ITEM_LGPS[2]=(int)lgp.LGP_DEL;
  SOP_ITEM_LGPS[4]=(int)lgp.LGP_CALL;
  SOP_ITEM_LGPS[5]=(int)lgp.LGP_MOVE_ARCHIVE;
  SOP_ITEM_LGPS[6]=(int)lgp.LGP_EXIT;

  //EditGUI.cpp
  extern SOFTKEY_DESC SK_OPTIONS;
  extern SOFTKEY_DESC SK_ADRBK;
  extern SOFTKEY_DESC SK_CANCEL;
  extern SOFTKEY_DESC SK_INSNM;
  extern int EDO_ITEM_LGPS[];
  SK_OPTIONS.lgp_id=(int)lgp.LGP_OPTIONS;
  SK_CANCEL.lgp_id=(int)lgp.LGP_CANCEL;
  SK_ADRBK.lgp_id=(int)lgp.LGP_ADRBK;
  SK_INSNM.lgp_id=(int)lgp.LGP_INSERT_NUM;
  EDO_ITEM_LGPS[0]=(int)lgp.LGP_REPLY;
  EDO_ITEM_LGPS[1]=(int)lgp.LGP_EDIT;
  EDO_ITEM_LGPS[2]=(int)lgp.LGP_DEL;
  EDO_ITEM_LGPS[4]=(int)lgp.LGP_CALL;
  EDO_ITEM_LGPS[5]=(int)lgp.LGP_MOVE_ARCHIVE;
  EDO_ITEM_LGPS[6]=(int)lgp.LGP_EXIT;
  
  //popupgui.cpp
  extern SOFTKEY_DESC pni_sk[];
  pni_sk[0].lgp_id=(int)lgp.LGP_VIEW;
  pni_sk[1].lgp_id=(int)lgp.LGP_BACK;

  //template.cpp
  //extern SOFTKEY_DESC tpl_menu_sk[];
  //tpl_menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  //tpl_menu_sk[1].lgp_id=(int)lgp.LGP_BACK;

  //GlobalVariable.cpp
  extern SOFTKEY_DESC sel_menu_sk[];
  sel_menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  sel_menu_sk[1].lgp_id=(int)lgp.LGP_BACK;

  //othersmenu.cpp
  extern int OTH_ITEM_LGPS[];
  OTH_ITEM_LGPS[0]=(int)lgp.LGP_CONFIG;
  OTH_ITEM_LGPS[1]=(int)lgp.LGP_OPEN_ARCHIVE;
  OTH_ITEM_LGPS[2]=(int)lgp.LGP_MOVE_ALL_MSS;
  OTH_ITEM_LGPS[3]=(int)lgp.LGP_EXPORT_TXT;
  OTH_ITEM_LGPS[4]=(int)lgp.LGP_DEL_ALL_MSG_MSS;
  OTH_ITEM_LGPS[5]=(int)lgp.LGP_HELP;
  OTH_ITEM_LGPS[6]=(int)lgp.LGP_ABOUT;

  //TViewGUI.cpp
  extern SOFTKEY_DESC tview_sk[];
  tview_sk[0].lgp_id=(int)lgp.LGP_OK;
  tview_sk[1].lgp_id=(int)lgp.LGP_BACK;
}

LangPack::LangPack()
{
  this->lang_buf=NULL;
  LoadLgpDefault();
  LoadLangFile();
  InitLgp();
}

LangPack::~LangPack()
{
  LoadLgpDefault();
  if(this->lang_buf)
  {
    delete this->lang_buf;
    this->lang_buf=NULL;
  }
}

LangPack *LGP=NULL;
