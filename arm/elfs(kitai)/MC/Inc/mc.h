#ifndef _MC_H
#define _MC_H

#ifndef _SWILIB
#include "..\inc\swilib.h"
#define _SWILIB
#endif

#include "inc\exts.h"
#include "zlib\zlib.h"
#include "zlib\minizip\unzip.h"

#define version		"1.0"

#define FALSE		0
#define TRUE		1

#define MAX_DRV			4
#define DRV_IDX_Data	0
#define DRV_IDX_Cache	1
#define DRV_IDX_Config	2
#define DRV_IDX_MMC		3

//#define MAX_SHOW		8
#define MAX_TABS		2
#define systab			MAX_TABS
#define LONG_SCRL		itms_max
#define MAX_TEXT		19
#define MAX_TXT_W		(ITM_X2-ITM_B-TXT_X-2)

#define KB_DELAY_SHORT	15
#define KB_DELAY_LONG	150

#define FNT_NONE		1
#define FNT_COPY		1
#define FNT_MOVE		2

#define ST_REVERS		0x0100
#define ST_NAME			0x0
#define ST_EXT			0x1
#define ST_SIZE			0x2
#define ST_DATE			0x3
#define STD_MASK		0x0100
#define STV_MASK		0x000F
#define ST_FIRST		ST_NAME
#define ST_LAST			ST_DATE

#define IDYES			0
#define IDNO			1

#ifdef NEWSGOLD
#define DEFAULT_DISK	"4"
#else
#define DEFAULT_DISK	"0"
#endif

extern char successed_config_filename[MAX_PATH];

#define def_new_dir		""

#define FA_CHECK		0x1000

// for type in FILEINF
#define TYPE_COMMON_FILE	0
#define TYPE_COMMON_DIR		1
#define TYPE_ZIP_FILE		2
#define TYPE_ZIP_DIR		3

// fot ftype in FN_ITM

typedef struct
{
	short id;
	int	ftype;
	char* sname;
	short attr;
	unsigned int size;
	unsigned int csize;
	unsigned int time;
	int	uccnt;
	int	inited;
	WSHDR* ws_name;
	WSHDR* ws_short;
	WSHDR* ws_attr;
	WSHDR* ws_size;
	WSHDR* ws_time;
	WSHDR* ws_ratio;
	WSHDR* ws_showname;
	EXTINF* ext;
	void* next;
} FILEINF;

typedef struct
{
	unzFile uf;
	char szZipPath[MAX_PATH];
	char szCurDir[MAX_PATH];
	unz_global_info gi;
	unz_file_info** pfi;
	char** pszNames;
	char* password;
} ZIPINF;

typedef struct
{
	short ccFiles;
	short sort;
	short CurDrv;
	short iIndex[MAX_DRV];
	short iBase[MAX_DRV];
	char  szDirs[MAX_DRV][MAX_PATH];
	char  szFilter[MAX_PATH];
	ZIPINF* zipInfo;
} TABINFO;

typedef struct
{
	int  num;
	char path[3];
	char name[7];
	int  enabled;
} DRVINFO;

typedef struct
{
	int gsize;
	int gcsize;
	int count;
} CHKDS_PARAM;


typedef struct
{
	int ftype;
	int pname;
	char* full;
	void* next;
	char* zipPath;
} FN_ITM;

typedef struct
{
	int count;
	int type;
	FN_ITM *items;
} FN_LIST;

typedef struct
{
	int sig;
	int ver;
	int size;
	int offset;
} mccfg_hdr;


typedef int (*ENUM_FILES_PROC) (DIR_ENTRY *de, int param);
typedef void (*IFN_RET_PROC) (WSHDR *wsname);
typedef int (*ENUM_SEL_PROC) (FILEINF *file, int param);


typedef int (*F_ENUM_PROC)(char* dname, ENUM_FILES_PROC enumproc, unsigned int param);
typedef int (*F_EXISTS_PROC)(char* fname);


#define MAX_INIBUF	256
typedef void (*INIPROC) (char* name, char* value);

typedef void (*KEY_PROC) ();

#define _CurTab   tabs[curtab]
#define _CurCount _CurTab->ccFiles
#define _CurDrv   _CurTab->CurDrv
#define _CurPath  _CurTab->szDirs[_CurDrv]
#define _CurIndex _CurTab->iIndex[_CurDrv]
#define _CurBase  _CurTab->iBase[_CurDrv]

//global vars
extern volatile int Terminate;
extern volatile int GUIStarted;
extern volatile int Busy;
extern unsigned int MAINGUI_ID;

extern int show_hidden;
extern int show_system;
extern int show_hiddrv;

extern int MsgBoxResult;

extern unsigned int err;

extern char* str_empty;

extern const char ext_file[];
extern const char keys_file[];
extern const char cfg_file[];
extern char etc_path[];

extern int progr_stop;
extern int progr_act;
extern int progr_max;
extern int progr_cur;
extern int progr_start;
extern int progrsp_max;
extern int progrsp_cur;
extern int progrsp_start;
extern char* pathbuf;
extern char* pathbuf2;
extern char* pathbuf_fn;
extern char* msgbuf;
extern char* zippathbuf;
extern WSHDR* wsbuf;
extern WSHDR* guibuf;
extern char* szLastNewFile;
extern char* szLastNewDir;
extern FN_LIST tmp_files;

extern int curtab;
extern TABINFO* tabs[];
extern FILEINF* FileListBase[];
extern DRVINFO Drives[];
extern EXTINF ext_chk;
extern EXTINF ext_dir;
extern char in_open_path[MAX_PATH];
extern char mcpath[MAX_PATH];
extern int back_tab;

extern int fa_attr;
extern int fa_sb;
extern FN_LIST buffer;

extern int Colors[];
extern const char mcbm_ext[];

extern SOFTKEYSTAB empty_menu_skt;
extern HEADER_DESC tmenuhdr;
extern SOFTKEY_DESC menu_sk[];
extern MENUITEM_DESC opt_menuitems[];
extern MENUITEM_DESC op_menuitems[];
extern MENUITEM_DESC mis_menuitems[];
extern MENUITEM_DESC fl_menuitems[];
extern MENUITEM_DESC bm_menuitems[];
extern MENUITEM_DESC st_menuitems[];
extern MENUITEM_DESC vw_menuitems[];
extern MENUITEM_DESC zip_opt_menuitems[];
extern MENUITEM_DESC zip_op_menuitems[];
extern char* yesno[];

extern GBSTMR cmtm;
extern GBSTMR offtm;

extern const char _d[];
extern const char _s_stars[];
extern const char _s_s[];
extern const char _s_s_d[];
extern const char _ss[];
extern const char _t[];
extern const char _tc[];
extern const char _d_t[];
extern const char _s_i_s[];

extern const int CONFIG_SHOW_HIDDEN;
extern const int CONFIG_SHOW_SYSTEM;
extern const int CONFIG_SHOW_SYSDRV;
extern const int CONFIG_SHOW_MMC;

extern const int CONFIG_BACK_EXIT;
extern const int CONFIG_SAVE_PATH;
extern const int CONFIG_CUR_DOWN_ON_CHECK;
extern const int CONFIG_LOOP_NAVIGATION_ENABLE;

extern const int CONFIG_AUTO_EXIT_AFTER_MIN;
extern const int CONFIG_ENABLE_BACKGROUND_EXIT;

extern const int CONFIG_ZIP_ENABLE;
extern const int CONFIG_ZIP_DETECT_BY;
extern const char CONFIG_TEMP_PATH[64];
extern const int CONFIG_DELETE_TEMP_FILES_ON_EXIT;

extern const int CONFIG_SCROLL_TEXT_SPEED;
extern const int CONFIG_SCROLL_TEXT_WAIT;
extern const int CONFIG_USE_BOLD_FONT;

extern const int CONFIG_LOAD_ICONS;
extern const int CONFIG_LOAD_KEYS;
extern const int CONFIG_LOAD_MUI;
extern const int CONFIG_LOAD_CS;
extern const char CONFIG_MCCONFIG_PATH[64];

extern const int CONFIG_CONFIRM_EXIT;
extern const int CONFIG_CONFIRM_DELETE;
extern const int CONFIG_CONFIRM_DELETERO;
extern const int CONFIG_CONFIRM_REPLACE;
extern const int CONFIG_CONFIRM_MOVE;
extern const int CONFIG_CONFIRM_COPY;

#ifdef LOG
void _WriteLog(char* buf);
void _WriteLogWS(WSHDR *buf);
void _WriteLog2(char* buf1, char* buf2);
void _WriteLogInt(char* buf, int ii);
void _WriteLogHex(char* buf, int ii);
#endif


//global procs
void UpdateCSMname(void);
void InitConfig();
char* MCFilePath(const char* sfile);
FILEINF *_CurFile();
FILEINF *_CurTabFile(int tab);
void UpdateAll();
void SetTabIndex(int tab, int num, int slide);
int GetTabIndex(int tab);
char* GetTabPath(int tab);
void SetCurTabIndex(int num, int slide);
int SetTabDrv(int tab, int num);
int SetCurTabDrv(int num);
int GetFileIndex(int tab, char* fname);
int GetCurTabFileIndex(char* fname);
char* CurFullPath(char* sfile);
char* CurFullPathBM(char* buff, char* sfile);
char* TmpFullPath2(char* buff, char* sfile);
int GetFilesCnt(char* path);
int TestFileName(WSHDR *wsname);
void CorFileName(WSHDR *wsname);

int MsgBoxYesNoWithParam(int lgind, char* str);
int cd(int tab, char* dname);
int cdsys(char* dname);
void _cd_tab(int tab,int drv,char* dname);
int IsChkAll();
int ChkAll(int chk);
int InvChk();
void ChkFile(FILEINF *file);
int EnumChk(ENUM_SEL_PROC EnumProc, int param);
int EnumSel(ENUM_SEL_PROC EnumProc, int param);
int IsMultiChk();

int cdzip(char* dname);

int isNumericStr(char* s);

void nricp(char* src, char* dst);
int EnumIni(int local, char* ininame, INIPROC proc);
char* GetFileExt(char* fname);
char* strreplace(char* s, char cprev, char cnew);
char* strtolower(char* src, char* dst, int sz);
int stricmp(char* str1, char* str2);
int strnicmp(char* str1, char* str2, int count);
int strircmp(char* str1, char* str2);
int strnircmp(char* str1, char* str2, int count);
int wstrcmpi(WSHDR* ws1, WSHDR* ws2);

char* sz2s(unsigned int size, char* buf);
char* attr2s(int attr, char* buf);
char* fdt2s(unsigned int time, char* buf);
char* GetFileDir(char* fname, char* buf);
char* GetFileName(char* fname);
int getLVC(unsigned short *wsbody, int len, int font);
void cutname(WSHDR *fname, WSHDR *sname, int len);
int fexists(char* fname);
int _EmptyEFP(DIR_ENTRY *de, int param);
int EnumFilesInDir(char* dname, ENUM_FILES_PROC enumproc, unsigned int param, int recursive, int enumDirs);
int EnumFiles(char* dname, ENUM_FILES_PROC enumproc, unsigned int param);
int mktree(char* path);
//int rmtree(char* path);
//int cptree(char* src, char* dst);
//int mvtree(char* src, char* dst);
//int fcopy(char* src, char* dst);
int fsrm(char* path, int ip);
int fscp(char* src, char* dst, int ip);
int fsmv(char* src, char* dst);

void prep_hd(EDITCONTROL* ec);
void prep_inf(EDITCONTROL* ec);

void CloseAllMenu();
void CloseMenu();
void MM_Main(void);
void MM_Oper(void);
void MM_Misc(void);
void MM_File(void);
void MM_BM(void);
void MM_Sort(void);
void MM_View(void);

void MC_FileProp(void);
void MC_DrvInf(void);
void MC_NewDir(void);
void MC_NewFile(void);
void MC_Rename(void);
void MC_Delit(void);
void MC_Open(void);
void MC_Exit(void);
void MC_AboutDlg(void);
void MC_Options(void);
void MC_Paste(void);
void MC_Copy(void);
void MC_Move(void);
void MC_Chk(void);
void MC_ChkAll(void);
void MC_UnChkAll(void);
void MC_InvChk(void);
void MC_SRTName(void);
void MC_SRTExt(void);
void MC_SRTSize(void);
void MC_SRTDate(void);
void MC_SRTRev(void);
void MC_Refresh(void);
void MC_Filter(void);

int _DirSize(DIR_ENTRY *de, int param);
int M_DirSize(FILEINF *file, int param);
int _SetAttr(DIR_ENTRY *de, int param);
void _FileProp(FILEINF *file);
void _NewDir(WSHDR *wsname);
void _NewFile(WSHDR *wsname);
void _Rename(WSHDR *wsname);
int M_FileProp(FILEINF *file, int param);
int M_SetAttr(FILEINF *file, int param);
int M_MoveCopy(FILEINF *file, int param);
void S_ZipOpen(void);

int InitTab(int tab);
void FreeTab(int tab);

FILEINF* CreateFileInfo(int findex, char* fnameOriginal,
				unsigned int fsize, short fattr, unsigned int ftime,
				int fcsize, int ftype);
void FillFileInfo(FILEINF* file);
void FreeFileInfo(FILEINF* file);

int FillFiles(int tab, char* dname);
void DelFiles(int tab);
void LoadKeys();
void SortFiles(int tab);

void AddFile(int tab, int findex, char* fnameOriginal, unsigned int fsize, short fattr,unsigned int ftime, int fcsize, int ftype);

char GetKeynameIndexByKey(char key);
KEY_PROC GetKeyprocByKey(char key);
KEY_PROC GetKeyprocLongByKey(char key);

void ExitFromZip();
void DoKey(int isLongPress, int key);
#define DoMenu MM_Main
int DoRefresh();
void DoFilter();
void DoOpen();
void DoExit();
int DoBack();
void DoSwapTab();
void DoPrvDrv();
void DoNxtDrv();
void DoUp();
void DoDwn();
void DoPgUp();
void DoPgDwn();
void DoBegin();
void DoChk();
void DoChkAll();
void DoUnCAll();
void DoInvChk();
int DoFileProp();
void DoDrvInf();
void DoNewDir();
void DoNewFile();
void DoRen();
void DoPaste();
void DoCancel();
void DoCopy();
void DoMove();
void DoDel();
void DoRoot();
void DoShowPath();
void DoErrKey();
void DoShowHid();
void DoShowSys();
void DoShowHidSys();
void DoShowHidDrv();

void DoBMAdd();
void DoBMList();
void UseBM(char* filename);

void DoSortN();
void DoSortE();
void DoSortS();
void DoSortD();
void DoSetSort();
void DoSortR();

void DoTabCopy();
void DoTabMove();

void DoSysOpen();

void empty_ghook(GUI *gui, int cmd);
void empty_locret(void);
int empty_onkey(GUI *gui, GUI_MSG *msg);
void TextInput(char* caption, char* prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc);

void S_Paste(void);
void S_Delit(void);

void fn_zero(FN_LIST *list);
void fn_fill(FN_LIST *list, char* path);
void fn_add(FN_LIST *list, int type, int ftype, int pname, char* full, char* zipPath);
void fn_rev(FN_LIST *list);
void fn_free(FN_LIST *list);
void fn_log(FN_LIST *list);

void initprogr(int act);
void incprogr(int inc);
void incprogrsp(int inc);
void endprogr();
void endprogrsp();

void InitAllMD();

extern unsigned int MAINCSM_ID;

void ResetAutoExit();
void AutoExitProc();


// из STDLIB.H
extern long  strtol (const char* nptr,char* *endptr,int base);

#endif
