#define version         "0.75j"

#define FALSE         0
#define TRUE          1

#define FONT_N   SMALL_FONT
#ifdef ELKA
 #define FONT_B   SMALL_FONT
#else
 #define FONT_B   (SMALL_FONT+1)
#endif

#define MAX_DRV         4
//#define MAX_SHOW        8
#define MAX_TABS        2
#define systab          MAX_TABS
#define LONG_SCRL       itms_max
#define MAX_TEXT        19
#define MAX_TXT_W       (ITM_X2-ITM_B-TXT_X-2)

#define KB_DELAY_SHORT  15
#define KB_DELAY_LONG   150

#define FNT_NONE        1
#define FNT_COPY        1
#define FNT_MOVE        2

#define ST_REVERS       0x0100
#define ST_NAME         0x0
#define ST_EXT          0x1
#define ST_SIZE         0x2
#define ST_DATE         0x3
#define STD_MASK        0x0100
#define STV_MASK        0x000F
#define ST_FIRST       ST_NAME
#define ST_LAST        ST_DATE

//#define MAX_PATH        0x80
#define MAX_PATH        0x100

#ifdef LEFT_YES
 #define IDYES           1
 #define IDNO            0
#else
 #define IDYES           0
 #define IDNO            1
#endif

#ifdef NEWSGOLD
 #define DEFAULT_DISK "4"
#else
 #define DEFAULT_DISK "0"
#endif

#define def_new_dir     "folder"

#define FA_CHECK	0x1000

#define MAX_EXT		8

typedef struct
{
 char ext[MAX_EXT];
 int  ico;
 void *next; 
}EXTINF;

typedef struct
{
 short  id;
 char   *sname;
 short  attr;
 unsigned int size;
 unsigned int time;
 EXTINF *ext;
 void   *next;
 int    inited;
 WSHDR  *ws_name; 
 int    uccnt;
 WSHDR  *ws_short;
 WSHDR  *ws_attr;
 WSHDR  *ws_size;
 WSHDR  *ws_time;
}FILEINF;

typedef struct
{
 short ccFiles;
 short sort;
 short CurDrv;
 short iIndex[MAX_DRV];
 short iBase[MAX_DRV];
 char  szDirs[MAX_DRV][MAX_PATH];
 char  szFilter[MAX_PATH];
}TABINFO;

typedef struct
{
 int  num;
 char path[3];
 char name[7];
}DRVINFO;

typedef struct{
  int gsize;
  int count;
} CHKDS_PARAM;


typedef struct{
  int isfile;
  int pname;
  char *full;
  void *next;
} FN_ITM;

typedef struct{
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
}mccfg_hdr;


typedef int (*ENUM_FILES_PROC) (DIR_ENTRY *de, int param);
typedef void (*IFN_RET_PROC) (WSHDR *wsname);
typedef int (*ENUM_SEL_PROC) (FILEINF *file, int param);

#define MAX_INIBUF 256
typedef void (*INIPROC) (char *name, char *value);

#define _CurTab   tabs[curtab]
#define _CurCount _CurTab->ccFiles
#define _CurDrv   _CurTab->CurDrv
#define _CurPath  _CurTab->szDirs[_CurDrv]
#define _CurIndex _CurTab->iIndex[_CurDrv]
#define _CurBase  _CurTab->iBase[_CurDrv]










extern long  strtol (const char *nptr,char **endptr,int base);



//global vars
extern volatile int Terminate;
extern volatile int GUIStarted;
extern volatile int Busy;
extern unsigned int MAINGUI_ID;

extern unsigned int err;

extern const char ext_file[];
extern const char keys_file[];
extern const char cfg_file[];
extern char etc_path[];

extern int itms_max;
extern int progr_stop;
extern int progr_act;
extern int progr_max;
extern int progr_cur;
extern int progr_start;
extern int progrsp_max;
extern int progrsp_cur;
extern int progrsp_start;
extern char *pathbuf;
extern char *pathbuf2;
extern char *pathbuf_fn;
extern char *msgbuf;
extern WSHDR *wsbuf;
extern WSHDR *guibuf;

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
extern char *yesno[];

extern GBSTMR sctm;
extern GBSTMR cmtm;
extern FILEINF *scfile;

extern const char _d[];
extern const char _s_stars[];
extern const char _s_s[];
extern const char _s_s_d[];
extern const char _ss[];
extern const char _t[];
extern const char _tc[];
extern const char _d_t[];

extern const int SHOW_HIDDEN;
extern const int SHOW_SYSDRV;
extern const int SHOW_MMC;

extern const int SAVE_PATH;
extern const int CONFIRM_EXIT;
extern const int SCROLL_TEXT_SPEED;
extern const int SCROLL_TEXT_WAIT;
extern const int LOAD_ICONS;
extern const int LOAD_KEYS;
extern const int BACK_EXIT;
extern const int LOAD_MUI;
extern const int LOAD_CS;
extern const int SC_ON_CHK;

#ifdef LOG
void _WriteLog(char *buf);
void _WriteLogWS(WSHDR *buf);
void _WriteLog2(char *buf1, char *buf2);
void _WriteLogInt(char *buf, int ii);
void _WriteLogHex(char *buf, int ii);
#endif


//global procs
void UpdateCSMname(void);
void InitConfig();
char *MCFilePath(const char* sfile);
FILEINF *_CurFile();
FILEINF *_CurTabFile(int tab);
void UpdateAll();
void SetTabIndex(int tab, int num, int slide);
int GetTabIndex(int tab);
char* GetTabPath(int tab);
void SetCurTabIndex(int num, int slide);
int SetTabDrv(int tab, int num);
int SetCurTabDrv(int num);
int GetFileIndex(int tab, char *fname);
char *CurFullPath(char* sfile);
char *CurFullPath2(char* buff, char* sfile);
char *TmpFullPath2(char* buff, char* sfile);
int GetFilesCnt(char *path);
int TestFileName(WSHDR *wsname);
void CorFileName(WSHDR *wsname);
void InitScr();
void DrwName();

int cd(int tab, char *dname);
int cdsys(char *dname);
void _cd_tab(int tab,int drv,char *dname);
int IsChkAll();
int ChkAll(int chk);
int InvChk();
void ChkFile(FILEINF *file);
int EnumChk(ENUM_SEL_PROC EnumProc, int param);
int EnumSel(ENUM_SEL_PROC EnumProc, int param);
int IsMultiChk();

void nricp(char* src, char* dst);
int EnumIni(int local, char *ininame, INIPROC proc);
EXTINF *GetExt(char *fname, int fattr);
char *GetFileExt(char *fname);
char *strtolower(char *src, char *dst, int sz);
int wstrcmpi(WSHDR* ws1, WSHDR* ws2);
char *sz2s(unsigned int size, char *buf);
char *attr2s(int attr, char *buf);
char *fdt2s(unsigned int time, char *buf);
char *GetFileDir(char *fname, char *buf);
char *GetFileName(char *fname);
int getLVC(unsigned short *wsbody, int len);
void cutname(WSHDR *fname, WSHDR *sname, int len);
int fexists(char* fname);
int _EmptyEFP(DIR_ENTRY *de, int param);
int EnumFiles(char *dname, ENUM_FILES_PROC enumproc, unsigned int param);
int mktree(char *path);
//int rmtree(char *path);
//int cptree(char *src, char *dst);
//int mvtree(char *src, char *dst);
//int fcopy(char *src, char *dst);
int fsrm(char *path, int ip);
int fscp(char *src, char *dst, int ip);
int fsmv(char *src, char *dst);

void prep_hd(EDITCONTROL* ec);
void prep_inf(EDITCONTROL* ec);

void CloseAllMenu();
void CloseMenu();
void MM_Main(GUI *data);
void MM_Oper(GUI *data);
void MM_Misc(GUI *data);
void MM_File(GUI *data);
void MM_BM(GUI *data);
void MM_Sort(GUI *data);
void MM_View(GUI *data);

void MC_FileProp(GUI *data);
void MC_DrvInf(GUI *data);
void MC_NewDir(GUI *data);
void MC_Rename(GUI *data);
void MC_Delit(GUI *data);
void MC_Open(GUI *data);
void MC_Exit(GUI *data);
void MC_AboutDlg(GUI *data);
void MC_Options(GUI *data);
void MC_Past(GUI *data);
void MC_Copy(GUI *data);
void MC_Move(GUI *data);
void MC_Chk(GUI *data);
void MC_ChkAll(GUI *data);
void MC_UnChkAll(GUI *data);
void MC_InvChk(GUI *data);
void MC_SRTName(GUI *data);
void MC_SRTExt(GUI *data);
void MC_SRTSize(GUI *data);
void MC_SRTDate(GUI *data);
void MC_SRTRev(GUI *data);
void MC_Refresh(GUI *data);
void MC_Filter(GUI *data);

int _DirSize(DIR_ENTRY *de, int param);
int M_DirSize(FILEINF *file, int param);
int _SetAttr(DIR_ENTRY *de, int param);
void _FileProp(FILEINF *file);
void _NewDir(WSHDR *wsname);
void _Rename(WSHDR *wsname);
int M_FileProp(FILEINF *file, int param);
int M_SetAttr(FILEINF *file, int param);
int M_MoveCopy(FILEINF *file, int param);

int InitTab(int tab);
void FreeTab(int tab);
void FullInit(FILEINF *file);
int FillFiles(int tab, char *dname);
void DelFiles(int tab);
void LoadExts();
void LoadKeys();
void FreeExt();
void ShowFiles();
void ShowProgr();
void SortFiles(int tab);

void DoKey(int key);
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
void DoRen();
void DoPast();
void DoCancel();
void DoCopy();
void DoMove();
void DoDel();
void DoRoot();
void DoShowPath();
void DoErrKey();

void DoBMAdd();
void DoBMList();
void UseBM(char* filename);

void DoSortN();
void DoSortE();
void DoSortS();
void DoSortD();
void DoSetSort();
void DoSortR();

void empty_ghook(GUI *gui, int cmd);
void empty_locret(void);
int empty_onkey(GUI *gui, GUI_MSG *msg);
void TextInput(char *caption, char *prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc);

void S_Past(void);
void S_Delit(void);

void fn_zero(FN_LIST *list);
void fn_fill(FN_LIST *list, char *path);
void fn_add(FN_LIST *list, int type, int isfile, int pname, char *full);
void fn_rev(FN_LIST *list);
void fn_free(FN_LIST *list);
void fn_log(FN_LIST *list);

void initprogr(int act);
void incprogr(int inc);
void incprogrsp(int inc);
void endprogr();
void endprogrsp();

void InitAllMD();
