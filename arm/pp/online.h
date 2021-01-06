int connect_state=0;
GBSTMR reconnect_tmr;
int is_gprs_online=1;
int DNR_ID;
int host_counter;
char logmsg[256];
char hostname[128];;
int DNR_TRIES;
int sock=-1;
unsigned int TOTALRECEIVED,TOTALSENDED;
void SMART_REDRAW();
int GetHostsCount(const char *str);
const char *GetHost(int cnt, const char *str, char *buf);
int GetPort(int cnt, const char *str);
void do_reconnect(void);
void send_login(int dummy, TPKT *p);
void SendAnswer(int dummy, TPKT *p);
int RXstate;
unsigned int ALLTOTALSENDED,ALLTOTALRECEIVED;
volatile int sendq_l=0; //Длинна очереди для send
volatile void *sendq_p=NULL; //указатель очереди
void end_socket(void);
unsigned int tenseconds_to_ping;
int SENDMSGCOUNT;
void get_answer(void);
#define EOP -10
// Константы операций (взаимодействие с сервером шлюза)
#define T_REQLOGIN 1
#define T_SENDMSG 2
#define T_RECVMSG 3
#define T_LOGIN 4
#define T_ERROR 6
#define T_CLENTRY 7
#define T_STATUSCHANGE 9
#define T_AUTHREQ 10
#define T_REQINFOSHORT 11
#define T_ADDCONTACT 12
#define T_SSLRESP 13
#define T_AUTHGRANT 14
#define T_MY_STATUS_CH 15   // Изменение моего статуса
//Сервер (аол) получил сообщение
#define T_SRV_ACK 16
//Клиент получил сообщение
#define T_CLIENT_ACK 17

#define T_ECHO 18
#define T_ECHORET 19

#define T_GROUPID 20
#define T_GROUPFOLLOW 21

#define T_MY_XSTATUS_CH 22

//Мой ответ Чемберлену (подтверждение доставки)
#define T_MSGACK 23

#define T_XTEXT_REQ 24
#define T_XTEXT_ACK 25
#define T_XTEXT_SET 26

#define T_ADDCONTACT_WITH_GRP 27

#define T_ADDGROUP 28
#define T_ADDIGNORE 29
#define T_SETPRIVACY 30
#define T_LASTPRIVACY 31

#define T_SETCLIENT_ID 32
TPKT RXbuf;
TPKT TXbuf;
void ParseRecMsg(int mess[2]);
void SendMSGACK(int i);
void ProcessPacket(TPKT *p);
LOGQ *FindContactLOGQByAck(TPKT *p);
void ClearSendQ(void);
volatile int disautorecconect;
int SendXod(int x, int y);
int SendQuest(char *quest, int flag);
