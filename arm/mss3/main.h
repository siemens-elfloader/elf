
typedef struct
{
	char numhdr[64];
	char adlhdr[64];
	char edtihdr[64];
	char edophdr[64];
	char slhdr[64];
}HDR_TEXTS;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
  void *gstop;
}DLG_CSM;


typedef struct
{
	WSHDR *txt;
	WSHDR *time;
}INBOX_DATA;

extern int new_sms_n;
extern int is_readall;
extern unsigned int DlgCsmIDs[];
extern char sms_dat[128];
extern char ems_admin_dat[128];
extern unsigned int SNEDSMS_CSM_ID;

int CreateMainMenu(DLG_CSM *dlg_csm);
void OpenArchive(void);
void addCSMidForced0(unsigned int *id_pool, unsigned int id);
int addCSMid(unsigned int *id_pool, unsigned int id);
void delCSMid(unsigned int *id_pool, unsigned int id);
int IsCsmExist(void *dlg_csm);
void UpdateDlgCsmName(DLG_CSM *csm, const char *lgp);
int IsSSOnTop(void);
void SendSimpleIpcMsg(int submess);
