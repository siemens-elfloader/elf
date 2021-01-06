extern const char LG_SEL_NUM[], LG_ANSWER[], LG_CREATE[], LG_NEW_SMS[], LG_NEW_IN[], LG_NONUM[], LG_ADRBOOK[], LG_ADRBOOKD[], LG_EMPTY[], LG_CANSEL[], LG_SEND[], LG_SENDQ[], LG_LETTERS[], LG_QUIT[], LG_ENT_NUM[], LG_ENT_TEXT[], LG_MESS[], LG_TO[], LG_FROM[], LG_INCOM[], LG_OUTCOM[], LG_DRAFT[], LG_STATISTIC[], LG_SETTINGS[], LG_OPEN_ERR[];

#define TYPE_OUT	1
#define TYPE_IN		2
#define TYPE_DRAFT	3
#define TYPE_UNK	4

#ifdef VKP
#define PROCESSOR_MODE __thumb
#else
#define PROCESSOR_MODE __arm
#endif

#define IPC_SMSMAN_NAME "SMSman"

#define IPC_CHECK_DOUBLERUN	1
#define IPC_OPEN_GUI		2

extern const char InSMSSound[], log_folder[], pic_folder[], IDLETXT[], SMS_DAT_PATH[], PNG_FNT_PATH[], IDLE_FNT_COL[4],IDLE_FNT_COL_BG[4],lovenumber[];
extern const unsigned int IDLE_X, IDLE_Y, IDLE_FNT, IDLEICON_X, IDLEICON_Y, SPACE,
	S_VOL_1, S_VOL_2, S_VOL_3, S_VOL_4, S_VOL_5, S_VOL_6, S_VOL_7, S_VOL_8,
	V_P_1, V_P_2, V_P_3, V_P_4, V_P_5, V_P_6, V_P_7, V_P_8,
	V_C_1, V_C_2, V_C_3, V_C_4, V_C_5, V_C_6, V_C_7, V_C_8;
	extern const int SHOW0NEW, IN_NOTIFY, SHOW_IDLE_TEXT, SHOW_IDLE_PIC, FULLFONT, ALIGN, TYPE_FNT, IN_SLI,
	VIBR_1, VIBR_2, VIBR_3, VIBR_4, VIBR_5, VIBR_6, VIBR_7, VIBR_8,
	SOUND_1, SOUND_2, SOUND_3, SOUND_4, SOUND_5, SOUND_6, SOUND_7, SOUND_8,
        SLI_1, SLI_2, SLI_3, SLI_4, SLI_5, SLI_6, SLI_7, SLI_8;

typedef struct
{
  int type;
  char SMS_CENTER[32];
  char Number[32];
  char Time[32];
  int tm[6];
  short sig;
  char cnt, n;
  WSHDR *name;
  WSHDR *SMS_TEXT;
}SMS_DATA;

typedef struct
{
  int is7, len, cnt;
}SMS_LEN;

typedef struct
{
  int sz;
  char SMS_CENTER[32];
  char Number[32];
  char Time[32];
  WSHDR *TXT;
}WR_SMS_DATA;



