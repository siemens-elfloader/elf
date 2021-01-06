#ifndef _LANGPACK_H_
#define _LANGPACK_H_


typedef struct _LGPACK
{
  const char *LGP_OK;
  const char *LGP_BACK;
  const char *LGP_ADRBK;
  const char *LGP_ERR;
  const char *LGP_SELECT;
  const char *LGP_QUIT;
  const char *LGP_NEW;
  const char *LGP_IN_R;
  const char *LGP_IN_N;
  const char *LGP_IN_A;
  //const char *LGP_OUT;
  const char *LGP_SENT;
  const char *LGP_DRAFT;
  const char *LGP_ALL;
  const char *LGP_OPTIONS;
  const char *LGP_ERR_0NUM;
  const char *LGP_EXIT;
  const char *LGP_CANCEL;
  const char *LGP_SEND;
  const char *LGP_DEL;
  const char *LGP_SAVE_AS_FILE;
  const char *LGP_SAVE_AS_DRAFT;
  const char *LGP_INSERT_ADRNUM;
  const char *LGP_INSERT_BLANKNUM;
  const char *LGP_CHAR_COUNT;
  const char *LGP_VIEW;
  const char *LGP_EDIT;
  const char *LGP_REPLY;
  const char *LGP_NEW_MSG;
  const char *LGP_FROM;
  const char *LGP_CODESHOW;
  const char *LGP_FETION;
  const char *LGP_SAVEALL;
  const char *LGP_CONFIG_UPDATE;
  const char *LGP_CONFIG;
  const char *LGP_SAVE_ALL_ONE;
  const char *LGP_PLS_INPUT_PATH;
  const char *LGP_OTHERS;
  const char *LGP_FILE_FAILED;
  const char *LGP_FILE_EXIST;
  const char *LGP_EXPORT_TXT;
  const char *LGP_MOVE_ARCHIVE;
  const char *LGP_MOVE_ALL_MSS;
  const char *LGP_OPEN_ARCHIVE;
  const char *LGP_EXPORT_N;
  const char *LGP_MOVE_MSSARCHIVER_N;
  const char *LGP_DEL_ALL_MSS;
  const char *LGP_ABOUT;
  const char *LGP_COV_DAT_TXT;
  const char *LGP_SAVE_ALL_AS_FILE;
  const char *LGP_SAF_N;
  const char *LGP_DEL_ALL;
  const char *LGP_DEL_ALL_MSG;
  const char *LGP_MOVE_ALL;
  const char *LGP_DEL_ALL_MSG_MSS;
  const char *LGP_SAVE;
  const char *LGP_MSG_REPORT;
  const char *LGP_MSG_REVEICED; //后加时间
  const char *LGP_UNK_RP_STATUS;
  const char *LGP_TEMPLATE;
  const char *LGP_CALL_ADDRESSBOOK;
  const char *LGP_STATISTICS;
  const char *LGP_IN_SMSDAT;
  const char *LGP_IS_MSSFILE;
  const char *LGP_DAT_FREE;
  const char *LGP_DISK_FREE;
  const char *LGP_MSS_MAINMENU;
  const char *LGP_TRANSLIT;
  const char *LGP_TIME;
  const char *LGP_UNK_NUM;
  const char *LGP_NUMBER;
  const char *LGP_TEXT;
  const char *LGP_TO;
  const char *LGP_UNK;
  const char *LGP_FILTER;
  const char *LGP_INSERT_NUM;
  const char *LGP_HELP;
  const char *LGP_DEL_N;
  const char *LGP_CALL;
}LGPACK;

class LangPack : public CFile
{
public:
  LangPack();
  ~LangPack();
  LGPACK lgp;
private:
  char *lang_buf;
  void FreeLangPack(void);
  void LoadLangPack(void);
  void LoadLangFile(void);
  void InitLgp(void);
  void LoadLgpDefault(void);
  char *GotoLangLineEnd(char *buf);
  char *GotoLangLineStart(char *buf);
};

extern LangPack *LGP;


#endif

