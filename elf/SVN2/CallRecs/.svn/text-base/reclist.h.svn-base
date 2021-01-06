

#ifdef NEWSGOLD
#define MAX_RECORDS 504
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else 
#define MAX_RECORDS 512
//#define LEVEL1_RN	(0x20)
#define LEVEL1_RN	(23)  
#endif
  



#pragma pack(1)
typedef   struct {
#ifdef NEWSGOLD
    long dummy1; //62 33 dc 05
    short len;  //!!!!! НА СГОЛД ХЗ ЕСТЬ ЭТО ПОЛЕ ИЛИ НЕТ
    char bitmap[MAX_RECORDS/8];
#else
    long dummy1; 
    char bitmap[MAX_RECORDS/8];    
#endif    
  } SABmain;
#pragma pack()



typedef struct 
{
  short year;
  short unk;
  char month;
  char day;
  short unk2;
  char hour;
  char min;
  char sec;
  char unk3; 
}dates;



/*

typedef  struct {
  void* next;
  void* next_g;  //указатель на звонки с таким же номером
  dates datetime;
  char number[16];
  char name[31];  
  unsigned int duration;
  unsigned char type; //битовое поле флагов
  unsigned int recid;  //ид записи, мож пригодится
  char cnt;  //если группа то число субитемов -1
  char isGroup;  //признак группы

}CRECS;
*/



typedef  struct {
  unsigned short recId;  //ид записи, мож пригодится
  union {
  unsigned char Number[8]; //BCD
  struct {
      signed int oxFF;     //4  -1
    unsigned short idParentItem; //2
    unsigned short idNext;    //2
  }ids;
  };
}CRECSLIGHT;
#define RECORD_TYPE_ALL 0x0200
#define RECORD_TYPE_RECV 0x0400
#define RECORD_IN_GROUP 0x0800
#define RECORD_GROUP_EXPAND 0x1000
#define RECORD_IS_GROUP 0x2000
#define RECORD_IS_GROUP_EXPND 0x3000
#define RECORD_TYPE_MISS 0x4000
#define RECORD_TYPE_DIAL 0x8000

extern CRECSLIGHT rc[MAX_RECORDS];
extern int rcCnt;

 typedef  struct {
  dates datetime;
  void  *Number;
  void  *Name;  
  unsigned int duration;
  unsigned char type; //битовое поле флагов
  unsigned int recId;  //ид записи, мож пригодится
  char cnt;  //если группа то число субитемов -1
}CContact;

extern int mask;
#define CONTACT_CACHE_SIZE 10
extern CContact cache[CONTACT_CACHE_SIZE];
//константы APO
#define APO_EN "calrec"
#define APO_TYPE 0x37
extern SABmain ABmain;
// exported
int ReadRecord(int lastrecord);//собсветнно чтени АПО  
int FindRecordIdByMenuId(int num, int mask); //
int FindIdByMenuId(int num, int mask);
int GetCacheRecordById(int id);
int CountRecord(void );
int CountRecordExpand(void );
int CountRecordCollapse(void );
int FindContactByContact(CContact *req);
void InitContacts(void);
void ClearContacts(void);
void PostProcessRecords(void);
CContact *GetContactByItem(int i);
int GetCallsCount(int gid);
