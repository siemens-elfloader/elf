#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#ifdef ELKA
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif
#endif
/*__root const CFG_HDR cfghdr0={CFG_LEVEL,"",0,0};//�������,����� ����� �� ���� ���� ���� ������ ����� ������ ������� ��� �������,� �� ������ � �������

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"����� ���������",1,0};//������ �������
  
  __root const CFG_HDR cfghdr1={CFG_INT,"������ ������",0,99};//������ �����, 0-99 ��� ��������� �� 0 �� 99 ���� ����� ������
  __root const int font=FONT_SMALL;

  __root const CFG_HDR cfghdr4={CFG_CBOX,"���������",0,2};//�� ������ ����, ����� 2 ��� ���������� ������� � ���
  __root const int illum_mode=0;
  __root const CFG_CBOX_ITEM cfgcbox2[2]={"���","��"};//cfgcbox2[2],��� ���� ����� ������� ����� 2,���� ����� 3 ������,�� ������������� 3 ������

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};//������ ������� ����� ���������

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"����",1,0};//�������

  __root const CFG_HDR cfghdr12={CFG_STR_UTF8,"���� � �������",0,127};//�� ��� ������,����� �������
  __root const char HIST_PATH[128]=DEFAULT_DISK ":\\ZBin\\TextReader\\history\\";

  __root const CFG_HDR cfghdr23={CFG_STR_UTF8,"���� � ���������",0,127};
  __root const char BMK_PATH[128]=DEFAULT_DISK ":\\ZBin\\TextReader\\Bookmarks\\";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};//����� ���������

__root const CFG_HDR cfghdr_2_2={CFG_CHECKBOX,"Enable eMenu",0,2};//��� � ��� �������,������ ������ �������))� ���� ������ �������� ���� ����� �����:)
__root const int ENA_EMENU = 1;//1-��������,0 ���������

__root const CFG_HDR cfghdr68={CFG_COORDINATES,"Coordinates panel",0,0};//����������� ����������
__root const unsigned int x1=0;
__root const unsigned int y1=75;

__root const CFG_HDR cfghdr60={CFG_COLOR,"Panel border col",0,0};//�������� ����
__root const char cfgPanBorderCol[4]={255,255,255,100};


__root const CFG_HDR cfghdr14={CFG_TIME,"�����",0,0};//�������� �����
__root const TTime tm={15,0};//��������� ��� �������

__root const CFG_HDR cfghdr1_1={CFG_STR_PASS,"Password",0,8};//������:)
__root const char PASS[9]="";//��� ������ ������������ ���� ���������:) *************
*/

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Game path",0,63};
__root const char GAME_PATH[64]=DEFAULT_DISK ":\\ZBin\\Black Raven\\";
