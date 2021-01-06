
#define CALL_N 0
#define CALL_O 1
#define CALL_I 2
#define CALL_A 3
#define CALL_W 1
extern GBSTMR tmr;
extern TDate d;
extern TTime real_time,t;
extern int is_call[2];
extern unsigned int in,out,autocall;
extern const int profile,time_on_sec,time_on_min,time_off_sec,time_off_min,time_on_on,time_off_off,opmod,add,ena_loud;
extern const  int Key1,Key1Type,Key2,Key2Type,amrmode,bitrate;
extern const char mic[9],loud[9];
extern const char folder[128];

void OpenCall();
void CloseCall();
void Close(GBSTMR *t);
void Auto(GBSTMR *t);
void UpdateCSMname(void);
