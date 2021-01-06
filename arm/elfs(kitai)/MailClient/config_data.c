#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_WIN1251,"��½��",0,63};
__root const char MAIL_LOGIN[64]="";

__root const CFG_HDR cfghdr1={CFG_STR_PASS,"����",0,31};
__root const char MAIL_PASS[32]="";

__root const CFG_HDR cfghdr2={CFG_STR_WIN1251,"POP3��ַ",0,31};
__root const char POP3_ADRESS[32]="pop.km.ru";

__root const CFG_HDR cfghdr3={CFG_UINT,"POP3�˿�",0,65535};
__root const unsigned int POP3_PORT=110;

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"Eml�ļ�·��",0,63};
__root const char EML_PATH[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\data\\";

__root const CFG_HDR cfghdr41={CFG_STR_UTF8,"Ĭ�ϸ�������·��",0,63};
__root const char SAVE_AS_FOLDER[64]=DEFAULT_DISK ":\\Misc\\";

__root const CFG_HDR cfghdr5={CFG_CBOX,"����",0,2};
__root const int DEFAULT_ACTION = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"������","���������"};

__root const CFG_HDR cfghdr51={CFG_UINT,"��������ļ���СС��",0,0xFFFFFFFF};
__root const unsigned int LOAD_IF_LESS = 0;

__root const CFG_HDR cfghdr6={CFG_CBOX,"��������ʼ��ڷ������ϱ�ɾ��",0,2};
__root const int IF_DEL_AUX = 0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"���ֻ���ɾ��","������"};

__root const CFG_HDR cfghdr61={CFG_CHECKBOX,"���غ�ӷ�������ɾ��",0,0};
__root const int DEL_AFTER_LOAD = 0;

__root const CFG_HDR cfghdr62={CFG_STR_WIN1251,"Number SMS Forward",0,31};
__root const char SMSFORWARD[32]="684";

__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"δ���ʼ�ͼ��",3,63};
__root const char I_UNREAD[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_unread.png";

__root const CFG_HDR cfghdr8={CFG_STR_UTF8,"�Ѷ��ʼ�ͼ��",3,63};
__root const char I_READ[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_read.png";

__root const CFG_HDR cfghdr9={CFG_STR_UTF8,"�������ʼ�ͼ��",3,63};
__root const char I_HEADER[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\only_head.png";

__root const CFG_HDR cfghdr10={CFG_STR_UTF8,"������������ʼ�ͼ��",3,63};
__root const char I_HEADER_ATT[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\only_head_att.png";

__root const CFG_HDR cfghdr11={CFG_STR_UTF8,"δ���������ʼ�ͼ��",3,63};
__root const char I_MES_UNREAD_ATT[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_unread_att.png";

__root const CFG_HDR cfghdr12={CFG_STR_UTF8,"�Ѷ��������ʼ�ͼ��",3,63};
__root const char I_MES_READ_ATT[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_read_att.png";

__root const CFG_HDR cfghdr13={CFG_STR_UTF8,"�����ʼ�ͼ��",3,63};
__root const char I_MES_DOWN[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_for_download.png";

__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"ɾ���ʼ�ͼ��",3,63};
__root const char I_MES_DEL[64]=DEFAULT_DISK ":\\ZBin\\EMailClient\\img\\mes_for_delete.png";

