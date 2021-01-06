#ifndef _LANG_H_
#define _LANG_H_

void lgpLoadLangpack(void);
void lgpFreeLangPack(void);
void lgpUpdateClHdr(void);
//void PreFreeLangPack();

//---------------------------------------------------------------------------

enum LGP_ID
{
  LGP_AlreadyStarted=0,
  LGP_ClTitle,
  LGP_ClT9Inp,
  LGP_ClError,
  LGP_ClLoopback,
  LGP_GroupNotInList,

  //=================
  LGP_Menu,
  LGP_Options,
  LGP_Close,
  LGP_Clear,
  LGP_DoIt,
  LGP_PasteSm,
  //-----------------
  LGP_Select,
  LGP_Text,
  LGP_Back,
  //-----------------
  LGP_Add,
  LGP_AddCnt,
  LGP_EnterUin,
  //=================
  LGP_AddRen,
  //LGP_SetNick,
  //LGP_SmlDesc,
  LGP_AddSmil,
  //=================
  LGP_AddCont,
  LGP_AuthReq,
  LGP_AuthGrant,
  //=================
  LGP_MnuStatus,
  LGP_MnuXStatus,
  LGP_MnuAddCont,
  LGP_MnuVibra,
  LGP_MnuSound,
  LGP_MnuShowOff,
  LGP_MnuShowGroup,
  LGP_MnuEdCfg,
  LGP_MnuDisconnect,
  LGP_MnuPing,
  LGP_MnuAbout,
  //=================
  LGP_MnuQuote,
  LGP_MnuRemCont,
  LGP_MnuRemContQuestions,
  LGP_MnuAddSml,
  LGP_MnuShInfo,
  LGP_MnuAddRen,
  LGP_MnuSAuthReq,
  LGP_MnuSAuthGrt,
  LGP_MnuOpenLog,
  LGP_MnuClearCht,
  
  LGP_MnuEdNextAct,
  LGP_MnuEdPrevAct,
  //=================
  LGP_ChgStatus,
  LGP_ChgXStatus,
  
  LGP_StOnline,
  LGP_StAway,
  LGP_StNa,
  LGP_StDnd,
  LGP_StOccup,
  LGP_StFfc,
  LGP_StInvis,
  LGP_StDepression,
  LGP_StEvil,
  LGP_StHome,
  LGP_StLunch,
  LGP_StWork,
  LGP_Comment,
  
  //=================
  
  LGP_All_Can_See,
  LGP_Vislist_Can_See,
  LGP_Invislist_Cannot_See,
  LGP_ContactList_Can_See,
  LGP_Nobody_Can_See,
  
  LGP_EnterName,
  LGP_ChooseGroup,
  LGP_PrivStatus,
  LGP_ManageList,
  
  //=================
  
  LGP_MsgIllegmsgcon,
  LGP_MsgIllegmsgrea,
  LGP_MsgCantConn,
  LGP_MsgCantCrSc,
  LGP_MsgHostNFnd,
  LGP_MsgVibraDis,
  LGP_MsgVibraEna,
  LGP_MsgSndDis,
  LGP_MsgSndEna,
  LGP_MsgNoUinPass,
  LGP_MsgSmileNotFnd,
  //=================
  
  LGP_GrsKeyExit,
  LGP_GrsKeyClist,
  
  LGP_LangCode, // Пусть всегда будет в конце
  
  LGP_DATA_NUM
};

//---------------------------------------------------------------------------
typedef struct LGP_Item LGP_Item;

struct LGP_Item
{
  char *tag;
  int   id;
};

//---------------------------------------------------------------------------

extern LGP_Item LGPTAGS[];

//---------------------------------------------------------------------------

extern char * lgpData[LGP_DATA_NUM];

//---------------------------------------------------------------------------

#endif /* _LANG_H_ */

