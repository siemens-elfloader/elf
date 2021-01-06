



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

//Ключи для поиска по T9
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

// extern volatile CLIST *cltop; //Начало
// extern void ConstructList(void);

