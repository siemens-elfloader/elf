

int Games_GUI_ID;// �� ��� ���� 
const RECT Canvas={0,0,0,0}; 
int hf=1;
//IMGHDR *outim; 
int coordX =65;
int coordy =35;
  int cur_keys;
  int cur_display;
  int uin = 1;
  int temp_keys;
  int temp_display;  
int bond=1; //������ �����
#define TMR_SECOND 216// �������
char Illumination = 0;
char * block;
GBSTMR idle_timer;
GBSTMR time_timer;
GBSTMR sleep_timer;
GBSTMR touch_timer;

char Touch = 0; // ������ ��� ����� ����� ���� ( ���� == 1)(� ������� ������� ��� �������������)

int fore = 0;
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#define IPC_TEXTINFO_NAME "ScreenSaver"
#define IPC_UPDATE_STAT 1
#define IPC_XTASK_NAME "XTask"
#define IPC_XTASK_IDLE 1
#define IPC_XTASK_SHOW_CSM 2
#define IPC_XTASK_LOCK_SHOW 3
#define IPC_XTASK_UNLOCK_SHOW 4
#define IPC_CHECK_DOUBLERUN 2
#define IPC_CHECK_S 12
#define IPC_SHOW_MSG 3
const char ipc_my_name[32]=IPC_TEXTINFO_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;
void CheckDoubleRun(void);
int state = 4;
int tike = 0;
// 0-2 - ��������, 3 - ���� ����, 4 - ... 

int cz = 0; // ��������� ����� ����



char *boxxes = " ";
int xx1 = 0;
int xx2 = -10;
int xx3 = 40;
int xx4 = 55;  //���������� ������
int xx5 = 0;

//----------------------------------- ���������� ��� �������� --------------------
                                                                          //

                                                                                 //
IMGHDR *FImage1;     //������� �� �������                                                           //
IMGHDR *FImage2;     //�������                                                            //
IMGHDR *FImage3;     //����� �������
IMGHDR *FImage3b;     //����� �����                                                      //
IMGHDR *FImage4;     //�������� ��������   
IMGHDR *FImage5;     //������ �������
IMGHDR *FImage5b;     //������ �����   
IMGHDR *FImage6;     //����� �������
IMGHDR *FImage6b;     //����� �����   
IMGHDR *FImage7;     //�����
IMGHDR *FImage7b;     //�����
IMGHDR *FImage8;     //�����
IMGHDR *FImage9;     //�����
IMGHDR *FImage10;     //iconbar_png
IMGHDR *Dig0;     //�����
IMGHDR *Dig1;     //�����
IMGHDR *Dig2;     //�����
IMGHDR *Dig3;     //�����
IMGHDR *Dig4;     //�����
IMGHDR *Dig5;     //�����
IMGHDR *Dig6;     //�����
IMGHDR *Dig7;     //�����
IMGHDR *Dig8;     //�����
IMGHDR *Dig9;     //�����
IMGHDR *Dig10;     //�����

//
//----------------------------------- ���������� ��� �������� --------------------

