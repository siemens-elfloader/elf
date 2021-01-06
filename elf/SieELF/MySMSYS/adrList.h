

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
#define SMS_MELODY 0x68
#define PICTURE 0x33
#define CALL_MELODY 0x66
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


typedef struct
{
  void *next;
  //WSHDR *nm[3];
  WSHDR *name;
  char *num[NUMBERS_MAX];
  char *sms_melody_filepath;
}CLIST;

extern volatile CLIST *cltop;
void ConstructList(void);
void FreeCLIST(void);
//int CreateAdrMenu(void *user_pointer);
int findNameByNum(WSHDR *name_to, char *num);
//void InsertAsTxt(void *ed_gui, char *num);
//void SetNumToED(void *ed_gui, char *num, WSHDR *name);
void ConstructListN(void);
CLIST *FindClByNum(const char *num);

