#include "..\..\inc\swilib.h"
#include "config_data.h"
#include "language.h"
#include "MySMSYS_ipc.h"

const char my_ipc_name[]=MY_SMSYS_IPC_NAME;

const char ELFNAME[]="MySMSYS";
#ifdef MEGADIAL
const char ELFNAME_D[]="MssMD";
#else
const char ELFNAME_D[]="MssD";
#endif
const char COPY_RIGHT[]="My SMS System v2.4.1\n(c)BingK (binghelingxi)\n(r)titron,Rst7";

const char PERCENT_T[]="%t";
const char PERCENT_S[]="%s";
const char num_fetion[]="12520";

const char STR_UNK_ED[]="Unknow EdGUI Type (%d)!";
const char STR_LINES[]="----------------";
const char STR_UNK_TXTT[]="Unkown Text Encode Type (%d)!";
const char STR_UNK_TYPE[]="Unknow Type (%d)!";

const char FLDR_IN[]="In\\";
const char FLDR_OUT[]="Out\\";
const char FLDR_DRAFT[]="Draft\\";
const char FLDR_UNK[]="Unknow\\";
const char FLDR_ARCHIVE[]="Archive\\";

#ifdef LANG_EN
/*
const char STR_FROM[]="From";
const char STR_UNK_NUM[]="Unknow Number";
const char STR_NUMBER[]="Number";
const char STR_TEXT[]="Text";
const char STR_TO[]="To";
const char STR_TIME[]="Time";
const char STR_UNK[]="Unknow";
*/
const char STR_UNK_NUM_UTF8[]="Unknow Number";
const char STR_NUMBER_UTF8[]="Number";
const char STR_TEXT_UTF8[]="Text";
const char STR_TO_UTF8[]="To";
const char STR_FROM_UTF8[]="From";
const char STR_TIME_UTF8[]="Time";
const char STR_UNK_UTF8[]="Unknow";
#endif


#ifdef LANG_CN
/*
const char STR_FROM[]="来自";
const char STR_UNK_NUM[]="未知号码";
const char STR_NUMBER[]="号码";
const char STR_TEXT[]="正文";
const char STR_TO[]="发送到";
const char STR_TIME[]="时间";
const char STR_UNK[]="未知";
*/
const char STR_UNK_NUM_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_NUMBER_UTF8[]="\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_TEXT_UTF8[]="\xE6\xAD\xA3\xE6\x96\x87";
const char STR_TO_UTF8[]="\xE5\x8F\x91\xE9\x80\x81\xE5\x88\xB0";
const char STR_FROM_UTF8[]="\xE6\x9D\xA5\xE8\x87\xAA";
const char STR_TIME_UTF8[]="\xE6\x97\xB6\xE9\x97\xB4";
const char STR_UNK_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5";
#endif


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
const char df_LGP_OUT[]="Sent";
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

LGPACK lgp;
char *lang_buf=0;
void LoadLgpDefault(void)
{
  lgp.LGP_OK                =df_LGP_OK;                       
  lgp.LGP_BACK              =df_LGP_BACK;                     
  lgp.LGP_ADRBK             =df_LGP_ADRBK;                    
  lgp.LGP_ERR               =df_LGP_ERR;                      
  lgp.LGP_SELECT            =df_LGP_SELECT;                   
  lgp.LGP_QUIT              =df_LGP_QUIT;                     
  lgp.LGP_NEW               =df_LGP_NEW;                      
  lgp.LGP_IN_R              =df_LGP_IN_R;                     
  lgp.LGP_IN_N              =df_LGP_IN_N;                     
  lgp.LGP_IN_A              =df_LGP_IN_A;                     
  lgp.LGP_OUT               =df_LGP_OUT;                       
  lgp.LGP_DRAFT             =df_LGP_DRAFT;                     
  lgp.LGP_ALL               =df_LGP_ALL;                       
  lgp.LGP_OPTIONS           =df_LGP_OPTIONS;                   
  lgp.LGP_ERR_0NUM          =df_LGP_ERR_0NUM;                  
  lgp.LGP_EXIT              =df_LGP_EXIT;                      
  lgp.LGP_CANCEL            =df_LGP_CANCEL;                    
  lgp.LGP_SEND              =df_LGP_SEND;                      
  lgp.LGP_DEL               =df_LGP_DEL;                       
  lgp.LGP_SAVE_AS_FILE      =df_LGP_SAVE_AS_FILE;              
  lgp.LGP_SAVE_AS_DRAFT     =df_LGP_SAVE_AS_DRAFT;             
  lgp.LGP_INSERT_ADRNUM     =df_LGP_INSERT_ADRNUM;             
  lgp.LGP_INSERT_BLANKNUM   =df_LGP_INSERT_BLANKNUM;           
  lgp.LGP_CHAR_COUNT        =df_LGP_CHAR_COUNT;                
  lgp.LGP_VIEW              =df_LGP_VIEW;                      
  lgp.LGP_EDIT              =df_LGP_EDIT;                      
  lgp.LGP_REPLY             =df_LGP_REPLY;                     
  lgp.LGP_NEW_MSG           =df_LGP_NEW_MSG;                   
  lgp.LGP_FROM              =df_LGP_FROM;                      
  lgp.LGP_CODESHOW          =df_LGP_CODESHOW;                  
  lgp.LGP_FETION            =df_LGP_FETION;                    
  lgp.LGP_SAVEALL           =df_LGP_SAVEALL;                   
  lgp.LGP_CONFIG_UPDATE     =df_LGP_CONFIG_UPDATE;             
  lgp.LGP_CONFIG            =df_LGP_CONFIG;                    
  lgp.LGP_SAVE_ALL_ONE      =df_LGP_SAVE_ALL_ONE;              
  lgp.LGP_PLS_INPUT_PATH    =df_LGP_PLS_INPUT_PATH;            
  lgp.LGP_OTHERS            =df_LGP_OTHERS;                    
  lgp.LGP_FILE_FAILED       =df_LGP_FILE_FAILED;               
  lgp.LGP_FILE_EXIST        =df_LGP_FILE_EXIST;                
  lgp.LGP_EXPORT_TXT        =df_LGP_EXPORT_TXT;                
  lgp.LGP_MOVE_ARCHIVE      =df_LGP_MOVE_ARCHIVE;              
  lgp.LGP_MOVE_ALL_MSS      =df_LGP_MOVE_ALL_MSS;              
  lgp.LGP_OPEN_ARCHIVE      =df_LGP_OPEN_ARCHIVE;              
  lgp.LGP_EXPORT_N          =df_LGP_EXPORT_N;                  
  lgp.LGP_MOVE_MSSARCHIVER_N=df_LGP_MOVE_MSSARCHIVER_N;        
  lgp.LGP_DEL_ALL_MSS       =df_LGP_DEL_ALL_MSS;               
  lgp.LGP_ABOUT             =df_LGP_ABOUT;                     
  lgp.LGP_COV_DAT_TXT       =df_LGP_COV_DAT_TXT;               
  lgp.LGP_SAVE_ALL_AS_FILE  =df_LGP_SAVE_ALL_AS_FILE;          
  lgp.LGP_SAF_N             =df_LGP_SAF_N;                     
  lgp.LGP_DEL_ALL           =df_LGP_DEL_ALL;                   
  lgp.LGP_DEL_ALL_MSG       =df_LGP_DEL_ALL_MSG;               
  lgp.LGP_MOVE_ALL          =df_LGP_MOVE_ALL;                  
  lgp.LGP_DEL_ALL_MSG_MSS   =df_LGP_DEL_ALL_MSG_MSS;           
  lgp.LGP_SAVE              =df_LGP_SAVE;                      
  lgp.LGP_MSG_REPORT        =df_LGP_MSG_REPORT;                
  lgp.LGP_MSG_REVEICED      =df_LGP_MSG_REVEICED; //后加时间   
  lgp.LGP_UNK_RP_STATUS     =df_LGP_UNK_RP_STATUS;             
  lgp.LGP_TEMPLATE          =df_LGP_TEMPLATE;                  
  lgp.LGP_CALL_ADDRESSBOOK  =df_LGP_CALL_ADDRESSBOOK;          
  lgp.LGP_STATISTICS        =df_LGP_STATISTICS;                
  lgp.LGP_IN_SMSDAT         =df_LGP_IN_SMSDAT;                 
  lgp.LGP_IS_MSSFILE        =df_LGP_IS_MSSFILE;                
  lgp.LGP_DAT_FREE          =df_LGP_DAT_FREE;                  
  lgp.LGP_DISK_FREE         =df_LGP_DISK_FREE;                 
  lgp.LGP_MSS_MAINMENU      =df_LGP_MSS_MAINMENU;
  lgp.LGP_TRANSLIT          =df_LGP_TRANSLIT;
  lgp.LGP_TIME              =df_LGP_TIME;
  lgp.LGP_UNK_NUM           =df_LGP_UNK_NUM;
  lgp.LGP_NUMBER            =df_LGP_NUMBER;
  lgp.LGP_TEXT              =df_LGP_TEXT;
  lgp.LGP_TO                =df_LGP_TO;
  lgp.LGP_UNK               =df_LGP_UNK;
  lgp.LGP_FILTER            =df_LGP_FILTER;
}


void InitLgp(void)
{
  //popupGui.c
extern SOFTKEY_DESC popup_sk[];
extern SOFTKEY_DESC msg_popup_sk[];
  popup_sk[0].lgp_id=(int)lgp.LGP_VIEW;
  popup_sk[1].lgp_id=(int)lgp.LGP_BACK;
  msg_popup_sk[0].lgp_id=(int)lgp.LGP_OK;
  //edGui.c
extern SOFTKEY_DESC ed_menu_sk[];
extern int items_lgp_nml_file[];
extern int items_lgp_nml_dat[];
extern int items_lgp_archive_file[];
extern SOFTKEY_DESC SK_OPTIONS;
extern SOFTKEY_DESC SK_ADRBK;
extern SOFTKEY_DESC SK_CANCEL;
  ed_menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  ed_menu_sk[1].lgp_id=(int)lgp.LGP_BACK;
  
  items_lgp_nml_file[0]=(int)lgp.LGP_REPLY;
  items_lgp_nml_file[1]=(int)lgp.LGP_EDIT;
  items_lgp_nml_file[2]=(int)lgp.LGP_DEL;
  items_lgp_nml_file[4]=(int)lgp.LGP_EXPORT_TXT;
  items_lgp_nml_file[5]=(int)lgp.LGP_MOVE_ARCHIVE;
  items_lgp_nml_file[6]=(int)lgp.LGP_EXIT;
  
  items_lgp_nml_dat[0]=(int)lgp.LGP_REPLY;
  items_lgp_nml_dat[1]=(int)lgp.LGP_EDIT;
  items_lgp_nml_dat[2]=(int)lgp.LGP_DEL;
  items_lgp_nml_dat[4]=(int)lgp.LGP_SAVE_AS_FILE;
  items_lgp_nml_dat[5]=(int)lgp.LGP_EXPORT_TXT;
  items_lgp_nml_dat[6]=(int)lgp.LGP_MOVE_ARCHIVE;
  items_lgp_nml_dat[7]=(int)lgp.LGP_EXIT;
  
  items_lgp_archive_file[0]=(int)lgp.LGP_REPLY;
  items_lgp_archive_file[1]=(int)lgp.LGP_EDIT;
  items_lgp_archive_file[2]=(int)lgp.LGP_DEL;
  items_lgp_archive_file[4]=(int)lgp.LGP_EXPORT_TXT;
  items_lgp_archive_file[5]=(int)lgp.LGP_EXIT;
  
  SK_OPTIONS.lgp_id=(int)lgp.LGP_OPTIONS;
  SK_ADRBK.lgp_id=(int)lgp.LGP_ADRBK;
  SK_CANCEL.lgp_id=(int)lgp.LGP_CANCEL;
  
  //main.c
extern SOFTKEY_DESC main_menu_sk[];
extern HEADER_DESC main_menuhdr;
extern int MENU_TEXT[];
extern MENUITEM_DESC oth_menuitems[];
extern HEADER_DESC oth_menuhdr;
  main_menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  main_menu_sk[1].lgp_id=(int)lgp.LGP_QUIT;
  
  main_menuhdr.lgp_id=(int)lgp.LGP_MSS_MAINMENU;
  
  MENU_TEXT[0]=(int)lgp.LGP_NEW;
  MENU_TEXT[1]=(int)lgp.LGP_IN_N;
  MENU_TEXT[2]=(int)lgp.LGP_IN_A;
  MENU_TEXT[3]=(int)lgp.LGP_OUT;
  MENU_TEXT[4]=(int)lgp.LGP_DRAFT;
  //MENU_TEXT[5]=(int)lgp.LGP_ALL;
  //MENU_TEXT[6]=(int)lgp.LGP_OTHERS;
  MENU_TEXT[5]=(int)lgp.LGP_OTHERS;
  
  oth_menuitems[0].lgp_id_small=(int)lgp.LGP_CONFIG;
  oth_menuitems[1].lgp_id_small=(int)lgp.LGP_OPEN_ARCHIVE;
  oth_menuitems[2].lgp_id_small=(int)lgp.LGP_SAVE_ALL_ONE;
  oth_menuitems[3].lgp_id_small=(int)lgp.LGP_MOVE_ALL_MSS;
  oth_menuitems[4].lgp_id_small=(int)lgp.LGP_COV_DAT_TXT;
  oth_menuitems[5].lgp_id_small=(int)lgp.LGP_DEL_ALL_MSG_MSS;
  oth_menuitems[6].lgp_id_small=(int)lgp.LGP_STATISTICS;
  oth_menuitems[7].lgp_id_small=(int)lgp.LGP_ABOUT;
  oth_menuhdr.lgp_id=(int)lgp.LGP_OTHERS;
  //smsList.c
extern int slop_lgp_dat[];
extern int slop_lgp_file[];
extern SOFTKEY_DESC sms_menu_sk[];
extern SOFTKEY_DESC SK_OK2;
  slop_lgp_dat[0]=(int)lgp.LGP_REPLY;
  slop_lgp_dat[1]=(int)lgp.LGP_EDIT;
  slop_lgp_dat[2]=(int)lgp.LGP_DEL;
  slop_lgp_dat[3]=(int)lgp.LGP_SAVE_AS_FILE;
  slop_lgp_dat[4]=(int)lgp.LGP_EXPORT_TXT;
  slop_lgp_dat[5]=(int)lgp.LGP_MOVE_ARCHIVE;
  slop_lgp_dat[6]=(int)lgp.LGP_EXIT;
  
  slop_lgp_file[0]=(int)lgp.LGP_REPLY;
  slop_lgp_file[1]=(int)lgp.LGP_EDIT;
  slop_lgp_file[2]=(int)lgp.LGP_DEL;
  slop_lgp_file[3]=(int)lgp.LGP_EXPORT_TXT;
  slop_lgp_file[4]=(int)lgp.LGP_MOVE_ARCHIVE;
  slop_lgp_file[5]=(int)lgp.LGP_EXIT;
  
  sms_menu_sk[0].lgp_id=(int)lgp.LGP_OPTIONS;
  sms_menu_sk[1].lgp_id=(int)lgp.LGP_EXIT;
  SK_OK2.lgp_id=(int)lgp.LGP_OK;
  
  //template.c
extern SOFTKEY_DESC tplmenu_sk[];
extern HEADER_DESC tplmenuhdr;
  tplmenu_sk[0].lgp_id=(int)lgp.LGP_OK;
  tplmenu_sk[1].lgp_id=(int)lgp.LGP_BACK;
  tplmenuhdr.lgp_id=(int)lgp.LGP_TEMPLATE;
#ifdef MEGADIAL
  extern SOFTKEY_DESC menu_sk[];
  menu_sk[0].lgp_id=(int)lgp.LGP_SELECT;
  menu_sk[1].lgp_id=(int)lgp.LGP_BACK;
#endif
}
char *GotoLineStart(char *buf)    
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

char *GotoLineEnd(char *buf)
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
void FreeLangPack(void)
{
  LoadLgpDefault();
  if(lang_buf)
  {
    mfree(lang_buf);
    lang_buf=0;
  }
}

void LoadLangFile(void)
{
  char fpath[128], *p, **lp, *pp;
  int len, c, fin, size, mn, i;
  unsigned int err;
  strcpy(fpath, CFG_MAIN_FOLDER);
  len=strlen(fpath);
  c=fpath[len-1];
  if(c!='\\' && c!='/')
  {
    fpath[len]='\\';
    fpath[len+1]=0;
  }
  if(!isdir(fpath, &err))
    return;
  strcat(fpath, "lang.txt");
  if((fin=fopen(fpath, A_BIN+A_ReadOnly, P_READ, &err))==-1)
    return;
  FreeLangPack();
  size=lseek(fin, 0, S_END, &err, &err);
  if(!size)
  {
    fclose(fin, &err);
    return;
  }
  lang_buf=malloc((size+3)&(~3));
  lseek(fin, 0, S_SET, &err, &err);
  if(fread(fin, lang_buf, size, &err)!=size)
  {
    fclose(fin, &err);
    return;
  }
  fclose(fin, &err);
  lang_buf[size]=0;
  p=lang_buf;
  lp=(char **)(&lgp);
  mn=sizeof(LGPACK)/sizeof(char *);
  for(i=0;i<mn;i++)
  {
    if(!(pp=GotoLineStart(p)))
      break;
    lp[i]=pp;
    if(!(pp=GotoLineEnd(pp)))
      break;
    *pp=0;
    p=pp+1;
  }
}

void LoadLangPack(void)
{
  LoadLgpDefault();
  LoadLangFile();
  InitLgp();
}

