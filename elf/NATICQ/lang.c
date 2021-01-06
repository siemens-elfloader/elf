#include "..\inc\swilib.h"
#include "lang.h"


char * lgpData[LGP_DATA_NUM];
int lgpLoaded;
int loaded;

//---------------------------------------------------------------------------

LGP_Item LGPTAGS[]=
{
  {"LGP_AlreadyStarted",         LGP_AlreadyStarted},
  {"LGP_ClTitle",                LGP_ClTitle},
  {"LGP_ClT9Inp",                LGP_ClT9Inp},
  {"LGP_ClError",                LGP_ClError},
  {"LGP_ClLoopback",             LGP_ClLoopback},
  {"LGP_GroupNotInList",         LGP_GroupNotInList},
  {"LGP_Menu",                   LGP_Menu},
  {"LGP_Options",                LGP_Options},
  {"LGP_Close",                  LGP_Close},
  {"LGP_Clear",                  LGP_Clear},
  {"LGP_DoIt",                   LGP_DoIt},
  {"LGP_PasteSm",                LGP_PasteSm},
  {"LGP_Select",                 LGP_Select},
  {"LGP_Text",                   LGP_Text},
  {"LGP_Back",                   LGP_Back},
  {"LGP_Add",                    LGP_Add},
  {"LGP_AddCnt",                 LGP_AddCnt},
  {"LGP_EnterUin",               LGP_EnterUin},
  {"LGP_AddRen",                 LGP_AddRen},
  {"LGP_AddSmil",                LGP_AddSmil},
  {"LGP_AddCont",                LGP_AddCont},
  {"LGP_AuthReq",                LGP_AuthReq},
  {"LGP_AuthGrant",              LGP_AuthGrant},
  {"LGP_MnuStatus",              LGP_MnuStatus},
  {"LGP_MnuXStatus",             LGP_MnuXStatus},
  {"LGP_MnuAddCont",             LGP_MnuAddCont},
  {"LGP_MnuVibra",               LGP_MnuVibra},
  {"LGP_MnuSound",               LGP_MnuSound},
  {"LGP_MnuShowOff",             LGP_MnuShowOff},
  {"LGP_MnuShowGroup",           LGP_MnuShowGroup},
  {"LGP_MnuEdCfg",               LGP_MnuEdCfg},
  {"LGP_MnuDisconnect",          LGP_MnuDisconnect},
  {"LGP_MnuPing",                LGP_MnuPing},
  {"LGP_MnuAbout",               LGP_MnuAbout},
  {"LGP_MnuQuote",               LGP_MnuQuote},
  {"LGP_MnuAddSml",              LGP_MnuAddSml},
  {"LGP_MnuShInfo",              LGP_MnuShInfo},
  {"LGP_MnuAddRen",              LGP_MnuAddRen},
  {"LGP_MnuRemCont",             LGP_MnuRemCont},
  {"LGP_MnuRemContQuestions",    LGP_MnuRemContQuestions},
  {"LGP_MnuSAuthReq",            LGP_MnuSAuthReq},
  {"LGP_MnuSAuthGrt",            LGP_MnuSAuthGrt},
  {"LGP_MnuOpenLog",             LGP_MnuOpenLog},
  {"LGP_MnuClearCht",            LGP_MnuClearCht},
  {"LGP_MnuEdNextAct",           LGP_MnuEdNextAct},
  {"LGP_MnuEdPrevAct",           LGP_MnuEdPrevAct},
  {"LGP_ChgStatus",              LGP_ChgStatus},
  {"LGP_ChgXStatus",             LGP_ChgXStatus},
  {"LGP_StOnline",               LGP_StOnline},
  {"LGP_StAway",                 LGP_StAway},
  {"LGP_StNa",                   LGP_StNa},
  {"LGP_StDnd",                  LGP_StDnd},
  {"LGP_StOccup",                LGP_StOccup},
  {"LGP_StFfc",                  LGP_StFfc},
  {"LGP_StInvis",                LGP_StInvis},
  {"LGP_StDepression",           LGP_StDepression},
  {"LGP_StEvil",                 LGP_StEvil},
  {"LGP_StHome",                 LGP_StHome},
  {"LGP_StLunch",                LGP_StLunch},
  {"LGP_StWork",                 LGP_StWork},
  {"LGP_Comment",                LGP_Comment},
  {"LGP_All_Can_See",            LGP_All_Can_See},
  {"LGP_Vislist_Can_See",        LGP_Vislist_Can_See},
  {"LGP_Invislist_Cannot_See",   LGP_Invislist_Cannot_See},
  {"LGP_ContactList_Can_See",    LGP_ContactList_Can_See},
  {"LGP_Nobody_Can_See",         LGP_Nobody_Can_See},
  {"LGP_EnterName",              LGP_EnterName},
  {"LGP_ChooseGroup",            LGP_ChooseGroup},
  {"LGP_PrivStatus",             LGP_PrivStatus},
  {"LGP_ManageList",             LGP_ManageList},
  {"LGP_MsgIllegmsgcon",         LGP_MsgIllegmsgcon},
  {"LGP_MsgIllegmsgrea",         LGP_MsgIllegmsgrea},
  {"LGP_MsgCantConn",            LGP_MsgCantConn},
  {"LGP_MsgCantCrSc",            LGP_MsgCantCrSc},
  {"LGP_MsgHostNFnd",            LGP_MsgHostNFnd},
  {"LGP_MsgVibraDis",            LGP_MsgVibraDis},
  {"LGP_MsgVibraEna",            LGP_MsgVibraEna},
  {"LGP_MsgSndDis",              LGP_MsgSndDis},
  {"LGP_MsgSndEna",              LGP_MsgSndEna},
  {"LGP_MsgNoUinPass",           LGP_MsgNoUinPass},
  {"LGP_MsgSmileNotFnd",         LGP_MsgSmileNotFnd},
  {"LGP_GrsKeyExit",             LGP_GrsKeyExit},
  {"LGP_GrsKeyClist",            LGP_GrsKeyClist},
  {"LGP_LangCode",               LGP_LangCode},

  {"LGP_DATA_NUM",               LGP_DATA_NUM}
};

//---------------------------------------------------------------------------

void lgpModifyLGPString(char *tagstr, char *lgpstr)
{
  int i, id = -1;
  for(i = 0; i < LGP_DATA_NUM; i++)
    if(!strcmp(LGPTAGS[i].tag, tagstr))
    {
      id = LGPTAGS[i].id;
      break;
    }
  if(id == -1 || id > LGP_DATA_NUM) return;
  mfree(lgpData[id]);
  lgpData[id] = (char *) malloc(strlen(lgpstr)+1);
  strcpy(lgpData[id], lgpstr);
}

//---------------------------------------------------------------------------

void lgpLoadDefault()
{
  int i, id;
  
  static char en_lgp[LGP_DATA_NUM][256];
  
  strcpy(en_lgp[LGP_AlreadyStarted],         "Already started!");
  strcpy(en_lgp[LGP_ClTitle],                "Contacts...");
  strcpy(en_lgp[LGP_ClT9Inp],                "T9 Key: ");
  strcpy(en_lgp[LGP_ClError],                "error");
  strcpy(en_lgp[LGP_ClLoopback],             "Loopback");
  strcpy(en_lgp[LGP_GroupNotInList],         "Not in list");
  
  //=================
  strcpy(en_lgp[LGP_Menu],                   "Menu");
  strcpy(en_lgp[LGP_Options],                "Options");
  strcpy(en_lgp[LGP_Close],                  "Close");
  strcpy(en_lgp[LGP_Clear],                  "< C");
  strcpy(en_lgp[LGP_DoIt],                   "Do it!");
  strcpy(en_lgp[LGP_PasteSm],                "Paste it!");
  //-----------------
  strcpy(en_lgp[LGP_Select],                 "Select");
  strcpy(en_lgp[LGP_Text],                   "Text");
  strcpy(en_lgp[LGP_Back],                   "Back");
  //-----------------
  strcpy(en_lgp[LGP_Add],                    "Add!");
  strcpy(en_lgp[LGP_AddCnt],                 "Add Contact");
  strcpy(en_lgp[LGP_EnterUin],               "Please enter uin:");
  //=================
  strcpy(en_lgp[LGP_AddRen],                 "Add/Rename");
  strcpy(en_lgp[LGP_AddSmil],                "Add Smiles");
  //=================
  strcpy(en_lgp[LGP_AddCont],                "Add contact...");
  strcpy(en_lgp[LGP_AuthReq],                "Please authorize me...");
  strcpy(en_lgp[LGP_AuthGrant],              "You are authorized!");
  //=================
  strcpy(en_lgp[LGP_MnuStatus],              "Status");
  strcpy(en_lgp[LGP_MnuXStatus],             "X-Status");
  strcpy(en_lgp[LGP_MnuAddCont],             "Add Contact");
  strcpy(en_lgp[LGP_MnuVibra],               "Vibra mode");
  strcpy(en_lgp[LGP_MnuSound],               "Sound mode");
  strcpy(en_lgp[LGP_MnuShowOff],             "Off. contacts");
  strcpy(en_lgp[LGP_MnuShowGroup],           "Groups");
  strcpy(en_lgp[LGP_MnuEdCfg],               "Edit config");
  strcpy(en_lgp[LGP_MnuDisconnect],          "Disconnect");
  strcpy(en_lgp[LGP_MnuPing],                "Ping");
  strcpy(en_lgp[LGP_MnuAbout],               "About");
  //=================
  strcpy(en_lgp[LGP_MnuQuote],               "Quote");
  strcpy(en_lgp[LGP_MnuAddSml],              "Add smile");
  strcpy(en_lgp[LGP_MnuShInfo],              "Get short info");
  strcpy(en_lgp[LGP_MnuAddRen],              "Add/rename");
  strcpy(en_lgp[LGP_MnuRemCont],             "Remove");
  strcpy(en_lgp[LGP_MnuRemContQuestions],    "Delete a contact?");
  strcpy(en_lgp[LGP_MnuSAuthReq],            "Send Auth Req");
  strcpy(en_lgp[LGP_MnuSAuthGrt],            "Send Auth Grant");
  strcpy(en_lgp[LGP_MnuOpenLog],             "Open logfile");
  strcpy(en_lgp[LGP_MnuClearCht],            "Clear log");
  
  strcpy(en_lgp[LGP_MnuEdNextAct],           "Next active");
  strcpy(en_lgp[LGP_MnuEdPrevAct],           "Prev. active");
  //=================
  strcpy(en_lgp[LGP_ChgStatus],              "Change Status");
  strcpy(en_lgp[LGP_ChgXStatus],             "Change X-Status");
  
  strcpy(en_lgp[LGP_StOnline],               "Online");
  strcpy(en_lgp[LGP_StAway],                 "Away");
  strcpy(en_lgp[LGP_StNa],                   "Not Available");
  strcpy(en_lgp[LGP_StDnd],                  "Do Not Disturb");
  strcpy(en_lgp[LGP_StOccup],                "Occupied");
  strcpy(en_lgp[LGP_StFfc],                  "Free For Chat");
  strcpy(en_lgp[LGP_StInvis],                "Invisible");
  strcpy(en_lgp[LGP_StDepression],           "Depression");
  strcpy(en_lgp[LGP_StEvil],                 "Evil");
  strcpy(en_lgp[LGP_StHome],                 "Home");
  strcpy(en_lgp[LGP_StLunch],                "Lunch");
  strcpy(en_lgp[LGP_StWork],                 "Work");
  
  strcpy(en_lgp[LGP_Comment],                "Comment:");
  //=================
  
  strcpy(en_lgp[LGP_All_Can_See],            "Visible for all");
  strcpy(en_lgp[LGP_Vislist_Can_See],        "Visible only for list seeing");
  strcpy(en_lgp[LGP_Invislist_Cannot_See],   "Visible for all, except for list blind");
  strcpy(en_lgp[LGP_ContactList_Can_See],    "Visible only for list of contacts");
  strcpy(en_lgp[LGP_Nobody_Can_See],         "Invisible for all");
  
  strcpy(en_lgp[LGP_EnterName],              "Enter a name");
  strcpy(en_lgp[LGP_ChooseGroup],            "Choose a group");
  strcpy(en_lgp[LGP_PrivStatus],             "Private status");
  strcpy(en_lgp[LGP_ManageList],             "Management by list");
  
  //=================
  
  strcpy(en_lgp[LGP_MsgIllegmsgcon],         "Illegal message ENIP_SOCK_CONNECTED!");
  strcpy(en_lgp[LGP_MsgIllegmsgrea],         "Illegal message ENIP_DATA_READ");
  strcpy(en_lgp[LGP_MsgCantConn],            "Can't connect!");
  strcpy(en_lgp[LGP_MsgCantCrSc],            "Can't create socket, GPRS restarted!");
  strcpy(en_lgp[LGP_MsgHostNFnd],            "Host not found!");
  strcpy(en_lgp[LGP_MsgVibraDis],            "Vibrà disabled!");
  strcpy(en_lgp[LGP_MsgVibraEna],            "Vibra enabled!");
  strcpy(en_lgp[LGP_MsgSndDis],              "Sounds disabled!");
  strcpy(en_lgp[LGP_MsgSndEna],              "Sounds enabled!");
  strcpy(en_lgp[LGP_MsgNoUinPass],           "Please setup UIN/PASS!");
  strcpy(en_lgp[LGP_MsgSmileNotFnd],         "Can't find smiles!");
  
  //=================
  
  strcpy(en_lgp[LGP_GrsKeyExit],             "Exit");
  strcpy(en_lgp[LGP_GrsKeyClist],            "Clist");
  
  strcpy(en_lgp[LGP_LangCode],               "en");
  
  for(i = 0; i < LGP_DATA_NUM; i++)
  {
    id = LGPTAGS[i].id;
    if(id <= LGP_DATA_NUM)
    {
      lgpData[id] = (char *)malloc(strlen(en_lgp[id]) + 1);
      strcpy(lgpData[id], en_lgp[id]);
    }
  }
}

//---------------------------------------------------------------------------


void  lgpLoadLangpack()
{
  int hFile;
  int size, str_size;
  unsigned int io_error = 0;
  char lang_file[256];
  const char _slash[]="\\";
  char *buf, *b, *e, *c, *str, *tagstr, *lgpstr;
  int ptr;
  extern const char TEMPLATES_PATH[64];
  strcpy(lang_file,TEMPLATES_PATH);
  if (lang_file[strlen(lang_file)-1]!='\\') strcat(lang_file,_slash);
  strcat(lang_file,"lang.txt");

  lgpLoadDefault();

  hFile=fopen(lang_file, A_ReadOnly + A_BIN, P_READ, &io_error);
  //hFile=FileOpen("e:\\ARM\\ARM\\NATICQ\\lng.en", fmOpenRead);
  if(hFile==-1)
    return;

  size = lseek(hFile, 0, 2, &io_error, &io_error);
  //size = FileSeek(hFile, 0, 2);
  lseek(hFile, 0, 0, &io_error, &io_error);
  //FileSeek(hFile, 0, 0);

  buf = (char*)malloc(size+1);

  fread(hFile, buf, size, &io_error);
//  FileRead(hFile, buf, size);
  for(ptr = 0; ptr < size;)
  {
    b = &(buf[ptr]);
    for(e = &(buf[ptr]); *e != 0x0D && *e != 0x0A && ptr <size; ptr++, e = &(buf[ptr]));
    for(c = &(buf[ptr]); (*c == 0x0D || *c == 0x0A) && ptr < size; ptr++, c = &(buf[ptr]));

    str_size = e - b + 1;
    str = (char *) malloc(str_size+1);
    memcpy(str, b, str_size-1);
    str[str_size-1] = 0;

    for(b = str; (*b == 0x20 || *b == 0x09) && b; b++);
    for(e = b;   (*e != '=') && e; e++);

    tagstr = (char *) malloc(e-b+1);
    memcpy(tagstr, b, e-b);
    tagstr[e-b] = 0;
    
    for(b = e; (*b == '=') && b; b++);
  
    lgpstr = (char *) malloc(strlen(b)+1);
    strcpy(lgpstr, b);
    
    lgpModifyLGPString(tagstr, lgpstr);
    mfree(lgpstr);
    mfree(tagstr);
    mfree(str);

  }
  mfree(buf);

  fclose(hFile, &io_error);
  //FileClose(hFile);
  lgpUpdateClHdr();

}

//---------------------------------------------------------------------------

void lgpFreeLangPack(void)
{
  int i, id;
  for(i = 0; i < LGP_DATA_NUM; i++)
  {
    id = LGPTAGS[i].id;
    if(id <= LGP_DATA_NUM)
      mfree(lgpData[id]);
  }
}
//---------------------------------------------------------------------------

