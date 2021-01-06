

#define ED_VIEW 0
#define ED_EDIT 1
#define ED_REPLY 2
#define ED_NEW 3
#define ED_FREE 4
#define ED_FVIEW 5
#define ED_FEDIT 6
#define ED_FREPLY 7

#define TYPE_SET 0
#define TYPE_INSERT 1
#define TYPE_TXT 2

#define INPUT_EXP_TXT 0
#define INPUT_COV_TXT 1
#define INPUT_COV_DAT 2

#define NAB_AF 0 //allow to free
#define NAB_DN 1 //do nothing
#define NAB_NS 2 //need to set flag

//dat type
#define NML_FILE 0
#define NML_DAT 1
#define ARCHIVE_FILE 2

typedef struct
{
  SMS_DATA *sd;
  void *dlg_csm;
  void *nltop; //num list
  int gui_type;
  int adr_type; //0 SET, 1 insert
  int list_type; //
  int focus_n;
  int dat_type; //
  int chr_cnt; //word count
  int nd_sfd; //need to save draft
}USER_OP;

/*
typedef struct
{
	void *dlg_csm;
	//SMS_DATA *sd;
	USER_OP *uo;
}MU_OP;
*/
int createEditGUI(void *dlg_csm, SMS_DATA *sd, int type, int list_type);
int newSMS(void *dlg_csm);
//int indexView(void *dlg_csm, int index);
//int inboxView(void *dlg_csm, void *inbox_data);
int viewTheLastNew(void *dlg_csm);
int newSMSWithNum(void *dlg_csm, char *num);
int newSMSWithUtf8Text(void *dlg_csm, char *text_utf8);
int DoByOpmsgId(void *dlg_csm, int msg, int opmsg_id);
unsigned int ViewFile(void *dlg_csm, char *fname);
void PathInputDlg(int type, char *path);
int CreateSmsWS(void *dlg_csm, WSHDR *text);
