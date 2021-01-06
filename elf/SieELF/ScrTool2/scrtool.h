#ifndef _SCRTOOL_H_
 #define _SCRTOOL_H_ 
 #include <sieapi.h> 
#define DAEMON
//#define XTASK//�Ƿ����ʹ��XTASK����ر�S
#define SCR_LITE//�Ƿ���������ı�˵��
#define SCR_NAME "ScrTool"
#define UPDATE_STAT 1
#define TMR_SECOND 216
#define MAX_SCR 18
#define MAX_APP 14
#define SCR_ALARM 3
#define SCR_MENUS 2
#define SCR_TASKS 1
#define LEN 32
#define NoName "�հ�"
#define ELEN 4
#define SLEN 50
#define ETyen "File", "Shortcut", "Address", "Directory"
#define ETycn "�ļ�", "���", "��ַ", "Ŀ¼"
#define AgainEN "Default", "AgainLeft", "Center", "AgainRight"
#define AgainCN "������ʾ", "������ʾ", "������ʾ", "������ʾ"
#define ScrMode "��������", "��������", "��������", "��ֹ����"
#define DateFmt "YYYY/MM/DD","YYYY-MM-DD","YYYY.MM.DD","YYYY MM DD","������","����","MM/DD","MM-DD","MM.DD","MM DD"
#define TimeFmt "01:00PM","01:00:00PM","13:00","13:00:00","13��00��","13��00��00��"
#define WeekFmt "SUNDAY", "SUN","Sunday","Sun","������","��"
static const char cDataFmt[][20]={"%02d/%02d/%02d","%02d-%02d-%02d","%02d.%02d.%02d","%02d %02d %02d",
                                  "%02d��%02d��%02d��","%02d��%02d��","%02d/%02d","%02d-%02d","%02d.%02d",
                                  "%02d %02d"}; 
static const IPC_REQ SCR_IPC={SCR_NAME, SCR_NAME, NULL};
static const int MINUSLL=-11;
static word MTBody[LEN];
static char ANST[]="��������";//����
static char ANTO[]="�ػ�-õ��v2.32";//�ػ�
static char ANRT[]="�����ֻ�";//����
static char ANLK[]="��ס����";//����
static char TASK[]="����˵�";//����˵�
static char ALRM[]="�������";//���ӽ���

 TSTRUCT{
  CSM_RAM CSM;
 }DAEMON_CSM;
 
 TSTRUCT{
  CSM_RAM CSM;
  int TaskID; 
 }TASK_GUI;
 
 TSTRUCT{  
  WSHDR *WS;
  char  PEN[4];
  char  BUH[4];
  byte  Size;
  byte  Style;
  byte  Show;
  short L;//left
  short T;//top
  short R;//right
  short B;//bottom
 }TSCR; 

 TSTRUCT{
  char *P;
  char *C;
  char *N; 
  word  T;
 }TAPP;
 //�����ļ�
 extern const char *cfn;
  //ˢ���ٶ�
 extern const uint REFRESH;
 extern const uint TASK_ENA;
 extern const uint INFO_ENA;
 extern const uint SHOW_EXT;
 extern const uint MODE_KBD;
 extern const uint CALL_BTN; 
 extern const uint DEST_ENA; 
 extern const uint PicSize;
//�������
 extern const uint OFFSET;
 extern const uint AUTO_CLOSE;
 extern const char ATEXT_CS[];
 extern const uint ATEXT_FT;
 extern const char PBDCol[];
 extern const char PBGCol[];
 extern const char BBDCol[];
 //Ĭ�Ϲ���ͼ��
 extern const char AIST[];//����ͼ��
 extern const char AITO[];//�ػ�ͼ��
 extern const char AIRT[];//����ͼ��
 extern const char AILK[];//����ͼ�� 
 extern const char AINO[];//û��ͼ��
 //�����ڲ���ַ
 extern const uint AT04;
 extern const uint AT05;
 extern const uint AT06;
 extern const uint AT07;
 extern const uint AT08;
 extern const uint AT09;
 extern const uint AT10;
 extern const uint AT11;
 extern const uint AT12;
 extern const uint AT13;
 //��������
 extern const char AN04[];
 extern const char AN05[];
 extern const char AN06[];
 extern const char AN07[];
 extern const char AN08[];
 extern const char AN09[];
 extern const char AN10[];
 extern const char AN11[];
 extern const char AN12[];
 extern const char AN13[];
 //����ͼ�� 
 extern const char AI04[]; 
 extern const char AI05[]; 
 extern const char AI06[]; 
 extern const char AI07[];
 extern const char AI08[];
 extern const char AI09[];
 extern const char AI10[];
 extern const char AI11[];
 extern const char AI12[];
 extern const char AI13[];
 //���ܵ���
 extern const char AF04[];
 extern const char AF05[];
 extern const char AF06[];
 extern const char AF07[]; 
 extern const char AF08[];
 extern const char AF09[];
 extern const char AF10[];
 extern const char AF11[];
 extern const char AF12[];
 extern const char AF13[];
//������ղ���
 extern const uint NBIR_ENA;
 extern const uint NBIR_T;
 extern const uint NBIR_X;
 extern const uint NBIR_Y;
 extern const char NBIR_CS[];
 extern const char NBIR_CB[];
 extern const uint NBIR_FT; 
 //������������
 extern const uint OBIR_ENA;
 extern const uint OBIR_T;
 extern const uint OBIR_X;
 extern const uint OBIR_Y;
 extern const char OBIR_CS[];
 extern const char OBIR_CB[];
 extern const uint OBIR_FT;
//�����ļ�
 extern const char BIRS_FILE[];
//��ʾ�ı�
 extern const uint TEXT_ENA;
 extern const uint TEXT_T;
 extern const uint TEXT_X;
 extern const uint TEXT_Y;
 extern const char TEXT_CS[];
 extern const char TEXT_CB[];
 extern const char TEXT_CP[];
 extern const uint TEXT_FT;
//��ʾ�¶�
 extern const uint TEMP_ENA;
 extern const uint TEMP_T;
 extern const uint TEMP_X;
 extern const uint TEMP_Y;
 extern const char TEMP_CS[];
 extern const char TEMP_CB[];
 extern const uint TEMP_FT;
//��ʾ��ѹ
 extern const uint VOLT_ENA;
 extern const uint VOLT_M;
 extern const uint VOLT_T;
 extern const uint VOLT_X;
 extern const uint VOLT_Y;
 extern const char VOLT_CS[];
 extern const char VOLT_CB[];
 extern const uint VOLT_FT;
//��ʾ�ڴ�
 extern const uint RAMT_ENA;
 extern const uint RAMT_T;
 extern const uint RAMT_X;
 extern const uint RAMT_Y;
 extern const char RAMT_CS[];
 extern const char RAMT_CB[];
 extern const uint RAMT_FT;
//��ʾ����
 extern const uint WEEK_ENA;
 extern const uint WEEK_T;
 extern const uint WEEK_X;
 extern const uint WEEK_Y;
 extern const char WEEK_CS[];
 extern const char WEEK_CB[];
 extern const uint WEEK_FT;
 extern const int  WEEK_FMT;
//��ʾ����
 extern const uint DATE_ENA;
 extern const uint DATE_T;
 extern const uint DATE_X;
 extern const uint DATE_Y;
 extern const char DATE_CS[];
 extern const char DATE_CB[];
 extern const uint DATE_FT;
 extern const int  DATE_FMT;
//��ʾʱ��
 extern const uint TIME_ENA;
 extern const uint TIME_T;
 extern const uint TIME_X;
 extern const uint TIME_Y;
 extern const char TIME_CS[];
 extern const char TIME_CB[];
 extern const uint TIME_FT;
 extern const int  TIME_FMT;
//��ʾũ����
 extern const uint CHSY_ENA;
 extern const uint CHSY_T;
 extern const uint CHSY_X;
 extern const uint CHSY_Y;
// extern const char CHSY_CS[];
// extern const char CHSY_CB[];
// extern const uint CHSY_FT;
//��ʾũ������
 extern const uint CHSM_ENA;
 extern const uint CHSM_T;
 extern const uint CHSM_X;
 extern const uint CHSM_Y;
// extern const char CHSM_CS[];
// extern const char CHSM_CB[];
// extern const uint CHSM_FT;
//��ʾũ������
 extern const uint CHSD_ENA;
 extern const uint CHSD_T;
 extern const uint CHSD_X;
 extern const uint CHSD_Y;
// extern const char CHSD_CS[];
// extern const char CHSD_CB[];
// extern const uint CHSD_FT;
 //��ʾũ�������ս���
 extern const uint CHMD_ENA;
 extern const uint CHMD_T;
 extern const uint CHMD_X;
 extern const uint CHMD_Y;
// extern const char CHMD_CS[];
// extern const char CHMD_CB[];
// extern const uint CHMD_FT;
//��ʾũ��ʱ��
 extern const uint CHSH_ENA;
 extern const uint CHSH_T;
 extern const uint CHSH_X;
 extern const uint CHSH_Y;
// extern const char CHSH_CS[];
// extern const char CHSH_CB[];
// extern const uint CHSH_FT;
 extern const uint CHSY_FT;
 extern const char CHSY_CS[];
 extern const char CHSY_CB[];
//��ʾ�ź�ǿ��
 extern const uint NETI_ENA;
 extern const uint NETI_T;
 extern const uint NETI_X;
 extern const uint NETI_Y;
 extern const char NETI_CS[];
 extern const char NETI_CB[];
 extern const uint NETI_FT;
//��ʾ��վ����
 extern const uint MGPS_ENA;
 extern const uint MGPS_T;
 extern const uint MGPS_X;
 extern const uint MGPS_Y;
 extern const char MGPS_CS[];
 extern const char MGPS_CB[];
 extern const uint MGPS_FT;
//��ʾGPRS����
 extern const uint GPRS_ENA;
 extern const uint GPRS_T;
 extern const uint GPRS_X;
 extern const uint GPRS_Y;
 extern const char GPRS_CS[];
 extern const char GPRS_CB[];
 extern const uint GPRS_FT;
 //��ʾCPUʹ����
 extern const uint CPUI_ENA;
 extern const uint CPUI_T;
 extern const uint CPUI_X;
 extern const uint CPUI_Y;
 extern const char CPUI_CS[];
 extern const char CPUI_CB[];
 extern const uint CPUI_FT;
//��������
 extern const char ALRM_FILE[];
 extern const char ALRM_PIC[];
 extern const char ALRM_CBK[];
 extern const char ALRM_CTX[];
 extern const uint ALRM_FT;
 extern const uint ALRM_VOL;
 extern const uint ALRM_COT;
 extern const uint ALRM_ENA;
 extern const uint ALRM_NUM;
 extern const uint ALRV_ENA;
 extern const uint ALRM_VIB;
 extern const uint ALIU_ENA;
//�Զ��ػ�
 extern const uint  SHUT_ENA;
 extern const TTime SHUT_TIME;
//�Զ�����
 extern const uint  ROOT_ENA;
 extern const TTime ROOT_TIME;

#endif
