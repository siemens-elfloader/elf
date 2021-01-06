
char *s_ab_main="0:\\System\\apo\\addr\\main";
#ifdef NEWSGOLD
char *s_ab_entry="0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d";
#else
char *s_ab_entry="0:\\System\\apo\\addr\\%02x\\%02x";
#endif

#ifdef ELKA
#define MAX_ESTR_LEN 9
#else
#define MAX_ESTR_LEN 13
#endif

#ifdef NEWSGOLD
#define MAX_RECORDS 5000
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else
#define MAX_RECORDS 1024
#define LEVEL1_RN	(0x20)
#endif

#define NUMBERS_MAX 5

#define wslen(ARG) (ARG->wsbody[0])

#ifdef NEWSGOLD
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define COMPANY_NAME 0x29
#define POST_NAME 0x6F
#define DISPLAY_NAME 0x60
#else
#define NICKNAME 0x12
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define STREET 0x25
#define POSTCODE 0x26
#define CITY 0x27
#define COUNTRY 0x28
#define COMPANY_NAME 0x29
#define PHONE_OFFICE 0x2A
#define PHONE_FAX 0x2B
#define PHONE_MOBILE 0x2C
#define PHONE_NUMBER 0x2D
#define E_MAIL 0x2E
#define URL 0x2F
#define PICTURE 0x33
#define E_MAIL2 0x5D
#define PHONE_FAX2 0x5E
#define WALKY_TALKY_ID 0x6D
#endif

//§¬§Ý§ð§é§Ú §Õ§Ý§ñ §á§à§Ú§ã§Ü§Ñ §á§à T9
static const char table_T9Key[256]=
"11111111111111111111111111111111"
"10001**0***0000*012345678900***0"
"0222333444555666777788899991*110"
"122233344455566677778889999111*1"
"11111111111111111111111111111111"
"11111111311111111111111131111111"
"22223333444455566677778888899999"
"22223333444455566677778888899999";

typedef struct
{
	void *next;
	WSHDR *nm[3];
	WSHDR *name;
	WSHDR *num[NUMBERS_MAX];
// 	WSHDR *icons;
}CLIST;


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

#define IPC_htc_SMS_NAME "htc_SMS"

#define IPC_CHECK_DOUBLERUN	1
#define IPC_OPEN_GUI		2

extern const char InSMSSound[], IDLETXT[], SMS_DAT_PATH[];
extern const unsigned int IDLE_X, IDLE_Y, IDLE_FNT,
	S_VOL_1, S_VOL_2, S_VOL_3, S_VOL_4, S_VOL_5, S_VOL_6, S_VOL_7, S_VOL_8,
	V_P_1, V_P_2, V_P_3, V_P_4, V_P_5, V_P_6, V_P_7, V_P_8,
	V_C_1, V_C_2, V_C_3, V_C_4, V_C_5, V_C_6, V_C_7, V_C_8;
	extern const int show0new, IN_NOTIFY, SHOW_IDLE,
	VIBR_1, VIBR_2, VIBR_3, VIBR_4, VIBR_5, VIBR_6, VIBR_7, VIBR_8,
	SOUND_1, SOUND_2, SOUND_3, SOUND_4, SOUND_5, SOUND_6, SOUND_7, SOUND_8;

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


