//#define RAM_SMS_dat_FileHandler 0xA8DADE14
//#define RAM_WB_dat_FileHandler 0xA8DADE16
//#define RAM_EMS_Admin_dat_FileHandler 0xA8DEEA20

//0xA8DADE14 short *RAM_SMS_dat_FileHandler
//pattern_NSG=&(??,4E,??,3E,??,68,??,28,??,D0,??,27,??,1C,??,20,??,??,??,??,??,28,??,D0)-8

//0xA8DADE16 short *RAM_WB_dat_FileHandler
//pattern_NSG=&(??,4E,??,3E,??,68,??,28,??,D0,??,27,??,1C,??,20,??,??,??,??,??,28,??,D0)-6

//0xA8DEEA20 short *RAM_EMS_Admin_dat_FileHandler
//pattern_NSG=&(??,4E,??,D0,??,AB,??,33,??,6A,??,42,??,D0,??,AB,??,33,??,1C,??,49,??,A8)


#define TYPE_UNK	0
#define TYPE_OUT	1
#define TYPE_IN_R	2 //readed
#define TYPE_IN_N 3 //new
#define TYPE_DRAFT	4
#define TYPE_IN_ALL 5

#define TYPE_FILTER 0xF
//msg_type
#define ISSMS 0 //00000000
#define ISEMS 1 //00000001
#define ISREPORT 2 //00000010
#define ISDES 4 //00000100 //is destroyed, or not full received
#define IS7BIT 8 //00001000
#define ISUNKE 16 //00010000 //unk text encode type
#define ISUNKT 32 //00100000 //unk sms type

#define MAX_TEXT 2048

//
#define SEGN_MAX 70
#define SEG7_MAX 160

typedef struct
{
	void *next;
	void *prev;
	int type;
	int id; //index of sms.dat
	int opmsg_id;
	int isfile;
	int msg_type;
	int cnt_r;
	char *fname;
//	char SMS_CENTER[32];
	char Number[32];
	char Time[32];
	WSHDR *SMS_TEXT;
}SMS_DATA;

#define MSS_VERSION 2 //add type;
typedef struct
{
	char header[8];
	int version;
	char time[32];
	char number[32];
}MSS_FILE_P1;


typedef struct
{
	char header[8];
	int version;
	int type;
	char time[32];
	char number[32];
}MSS_FILE_P2;

extern SMS_DATA *sdltop;
//extern const IPC_REQ my_ipc_upd;
//sdl
SMS_DATA *AllocSD(void);
void AddToSdlByTime(SMS_DATA *sd);
void freeSDList(void);
void FreeSdOne(SMS_DATA *sd);
SMS_DATA *SdCopyOne(SMS_DATA *sdx);
void delSDList(SMS_DATA *sdl);
//---------------------------
SMS_DATA *FindSdByTxtTimeNum(WSHDR *ws, char *time, char *num);
int IsSdInList(SMS_DATA *sd);
SMS_DATA *FindSDByOpmsgId(int opmsg_id);
//------------------------
int readAllSMS(void);
int ReadAllSmsN(void);
int getCountByType(int type);
int GetCountByIsFileType(int isfile, int type); //0, all
SMS_DATA *getSMSDataByType(int n, int type);
//SMS_DATA *findInSMSByTxtTime(WSHDR *ws, char *time);
int newToRead(SMS_DATA *sd);
int saveFile(WSHDR *ws, char *number, SMS_DATA *sd, int type, int need_reload);
int readFile(int type);
int deleteFile(SMS_DATA *sd, int need_reload);
int deleteDat(SMS_DATA *sd, int need_reload);
SMS_DATA *getLastTheLast(int type);
int SaveAllAsFile(void);
SMS_DATA *FindNextByType(SMS_DATA *sdl, int type);
SMS_DATA *FindPrevByType(SMS_DATA *sdl, int type);
SMS_DATA *FindNextMss(SMS_DATA *sd);
SMS_DATA *FindPrevMss(SMS_DATA *sd);
int ReadMSS(char *fname, SMS_DATA *sd);
int IsHaveNewSMS(void);
void DeleteAllMss(void);
void DeleteAll(void);
//---------------------------
int ExportAllToOneTxt(char *filename);
int ExportOneToTxt(SMS_DATA *sd);
int MoveToArchive(SMS_DATA *sd);
int MoveAllMssToArchive(void);
int MoveAllToArchive(void);
void ShowFileErrCode(int code);
int CovDatToTxt(char *dat_path, char *txt_path);
int IsFileExist(const char *filename);
//--------------
void Add2WS(char *data, char *wsbody, int len);
void Hex2Num(char *hex, char *num, int len);


