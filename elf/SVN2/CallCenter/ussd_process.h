#define MAX_CASH_SIZE (4)

int ProcessUSSD(CSM_RAM* data, GBS_USSD_MSG *msg);
void SendCashReq(void);
void EndUSSDtimer(void);
void LoadCash(void);
void SaveCash(void);
