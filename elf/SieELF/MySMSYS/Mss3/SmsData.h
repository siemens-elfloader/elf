#ifndef _SMSDATA_H_
#define _SMSDATA_H_

#define CHK_RES_DONOTHING 0
#define CHK_RES_RELOAD 1
#define CHK_RES_REFRESH 2

#define FILTER_ALL	0
#define FILTER_NEW	1
#define FILTER_DAT	2
#define FILTER_FILE	3
#define FILTER_NUM	4
#define FILTER_STR	5

#define FTYPE_TXT 0
#define FTYPE_MSS 1

//#define RAM_EAM_BUF 0xA8DAD298 //?? 48 ?? 47 ?? 20 ?? 30 ?? 04 ?? 0C ?? 28 ?? D3 ?? 47
//ELKA &(??48??47??B5??B0??1C??D1??20)

class SmsData :
  public SiememPDU,
  public CFile
{
public:
	static void DeleteAllMssBG(SmsData *smsdata);
	int DeleteAllMss();
	static void ExportAllToTextBG(SmsData *smsdata);
	int ExportAllToText();
	SDLIST * FindLastNew(void);
  SmsData();
  ~SmsData();
  int ReadAllDatMsg(void);
  int ReadMessageOne(int dat_index);
  void FreeDatBuf(void);
  int SaveMss(WSHDR *ws, const char *number, SDLIST *sdl, int type, int need_reload); //need_reload,0 not, 1 all, 2 this
  int GetMssPath(char *path, char *folder, TTime *time, TDate *date);
  int DeleteMessage(SDLIST *sdl);
  int ReadMss(char *fname, SDLIST *sdl);
  int ReadFolder(int type);
  int ReadAllMessage(void);
  static int ReadAllMessageCHK(SmsData *data);
  static int ReadAllMessageFRC(SmsData *data);
  int CheckSMS(int dat_index);
  int IsNewSMS(int dat_index);
  int CheckDat(void);
  int CheckFolder(int type);
  int CheckSDList(void);
  int CheckAll(void);
  static int CheckAllCHK(SmsData *data);

  int NewToReadSMS(SDLIST *sdl);
  int IsExistSDL(SDLIST *sdl);

  int GetFilePathSDL(SDLIST *sdl, char *folder, char *filepath, int ftype);
  int MoveToArchive(SDLIST *sdl);
  int MoveAllToArchive(void);
  static void MoveAllToArchiveBG(SmsData *data);

//list
  static SDLIST *AllocSDL(void);
  void AddByTimeSDL(SDLIST *sdl);
  void DeleteSDL(SDLIST *sdl);
  void FreeAllSDL(void);
  void FreeOneSDL(SDLIST *sdl);
  static SDLIST *CopyOneSDL(SDLIST *sdl);
  SDLIST *FindSDL(WSHDR *text, char *time, char *num);
  SDLIST *FindSDL(char *filename);
  SDLIST *FindSDL(int type, int n);
  SDLIST *FindSDL(int dat_index);
  SDLIST *FindOpmsgSDL(int opmsg_id);

  int GetSMSCount(int type);
  int GetSMSCount(int isfile, int type);

  SDLIST *FindNextSDL(SDLIST *sdl, int type);
  SDLIST *FindPrevSDL(SDLIST *sdl, int type);
//filter
  SDLIST *FilterFindSDL(int n);
  SDLIST *FilterFindSDL(int isfile, int n);
  SDLIST *FilterFindSDL(const char *number, int n);
  SDLIST *FilterFindSDL(WSHDR *str, int n);
  int FilterGetCount(void);
  int FilterGetCount(const char *number);
  int FilterGetCount(WSHDR *str);
  SDLIST *FilterFindNext(SDLIST *sdl);
  SDLIST *FilterFindNext(SDLIST *sdl, const char *number);
  SDLIST *FilterFindNext(SDLIST *sdl, WSHDR *str);
  SDLIST *FilterFindPrev(SDLIST *sdl);
  SDLIST *FilterFindPrev(SDLIST *sdl, const char *number);
  SDLIST *FilterFindPrev(SDLIST *sdl, WSHDR *str);
  int n_new; //新短信条数

  //导出txt
//  int ExportText(SDLIST *sdl);
private:
  char *sms_buf;
  int sms_size;
  SDLIST *sdltop;
  int is_reading;
  int ReadDat(void);
  int DeMsgDataList(SMS_DATA_LIST *lst);
  SMS_DATA_LIST *FindMsgDataL(int dat_index);
  int IsDatExist(int dat_index);
};

extern SmsData *SMSDATA;
#endif


