static volatile char is_call=0; //0 - нет звонка 1 - исходщий(не пишется) 2 - входящий(не пишется) 3 - исходщий(пишется) 4 - входящий(пишется) 5 - авто-перед записью(входящий) 6 - авто-пишется(входящий)
#define CALL_NULL 0
#define CALL_OUT 1
#define CALL_IN 2
#define CALL_OUTW 3
#define CALL_INW 4
#define CALL_AUTO 5
#define CALL_AUTOW 6
GBSTMR tmr;
TDate d;
TTime real_time,t;
unsigned int in=0,out=0,autocall=0;
char name[32];
extern const int profile,time_on_sec,time_on_min,time_off_sec,time_off_min,time_on_on,time_off_off,opmod,add,ena_loud;
extern const unsigned int Key1,Key1Type,Key2,Key2Type;
extern const char mic[9],loud[9];


void OpenCall();
void CloseCall();
void Close();
void Auto();
void UpdateCSMname();
void func(const char *adr);
