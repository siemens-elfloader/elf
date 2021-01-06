








typedef struct
{
  int type;
  char name[32];
  unsigned int min;
  unsigned int max;
}CFG_HDR;

typedef struct
{
  char cbox_text[32];
}CFG_CBOX_ITEM;








 





















































__root const CFG_HDR cfghdr_CONNECT_LEVEL={9,"��������� �����������",1,0};

__root const CFG_HDR cfghdr0={10,"�����",0,31};
__root const char USERNAME[32]="";

__root const CFG_HDR cfghdr1={6,"������",0,31};
__root const char PASSWORD[32]="";

__root const CFG_HDR cfghdr2={4,"������",0,127};
__root const char JABBER_SERVER[128]="jabber.ru";

__root const CFG_HDR cfghdr3={4,"����",0,127};
__root const char JABBER_HOST[128]="jabber.ru";

__root const CFG_HDR cfghdr3_1={5,"��� �����",0,2};
__root const int IS_IP = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"���","IP �����"};

__root const CFG_HDR cfghdr4={1,"����",0,65535};
__root const unsigned int JABBER_PORT=5222;

__root const CFG_HDR cfghdr5={5,"�����������",0,2};
__root const int USE_SASL = 0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Simple","SASL"};

__root const CFG_HDR cfghdr6={5,"������������� ZLib",0,2};
__root const int USE_ZLIB = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"���","��"};

__root const CFG_HDR cfghdr7={10,"������",0,29};
__root const char RESOURCE[30] = "SieJC";

__root const CFG_HDR cfghdr_CONNECT_LEVEL_END={9,"",0,0};



__root const CFG_HDR cfghdr8={5,"�������",0,2};
__root const int WRITE_HISTORY = 0;
__root const CFG_CBOX_ITEM cfgcbox1435[2]={"���������","��������"};

__root const CFG_HDR cfghdr9={5,"MUC �������",0,2};
__root const int WRITE_MUC_HISTORY = 0;
__root const CFG_CBOX_ITEM cfgcbox36546[2]={"���������","��������"};

__root const CFG_HDR cfghdr10={10,"MUC �� ���������",0,63};
__root const char DEFAULT_MUC[64]="siepatchdb@conference.jabber.ru";

__root const CFG_HDR cfghdr11={10,"��� �� ���������",0,63};
__root const char DEFAULT_MUC_NICK[64]="";

__root const CFG_HDR cfghdr59={1,"���. ����������� ���������",0,20};
__root const unsigned int DEFAULT_MUC_MSGCOUNT=20;

__root const CFG_HDR cfghdr60={11,"�������� � �����������",0,2};
__root const int MUC_AUTOJOIN=0;

__root const CFG_HDR cfghdrshowii={11, "���������� ������ �� idle", 0, 2};
__root const int IDLE_ICON=1;

__root const CFG_HDR cfghdr12={7,"��������� ������",0,0};
__root const unsigned int IDLE_ICON_X=0;
__root const unsigned int IDLE_ICON_Y=50;

__root const CFG_HDR cfghdr17657={11,"���������� POPUP",0,2};
__root const int DISPLAY_POPUPS=1;

__root const CFG_HDR cfghdr17658={11,"������ ����� ���������",0,2};
__root const int FIRST_LETTER = 0;

__root const CFG_HDR cfghdr13={11,"������� ���������",0,2};
__root const int COMPOSING_EVENTS=1;

__root const CFG_HDR cfghdr15345={11,"����� � ��������, ���� ���������",0,2};
__root const int DELIVERY_EVENTS=1;

__root const CFG_HDR cfghdr15346={11,"��������� ������ 'Attention'",0,2};
__root const int USE_ATTENTION=0;

__root const CFG_HDR cfghdr7_3={5,"Time Zone",0,24};
__root const int MY_DEF_ZONE = 2;
__root const CFG_CBOX_ITEM cfgcbox7_1[24]={
  "+0:00",
  "+1:00",
  "+2:00",
  "+3:00",
  "+4:00",
  "+5:00",
  "+6:00",
  "+7:00",
  "+8:00",
  "+9:00",
  "+10:00",
  "+11:00",
  "+12:00",
  "-1:00",
  "-2:00",
  "-3:00",
  "-4:00",
  "-5:00",
  "-6:00",
  "-7:00",
  "-8:00",
  "-9:00",
  "-10:00",
  "-11:00"
  };



__root const CFG_HDR cfghdr_SOUNDS_SETUP={9,"��������� �����",1,0};

__root const CFG_HDR cfghdr130={1,"�������� �����",10,100};
__root const unsigned int vibraPower=10;

__root const CFG_HDR cfghdr14={1,"���������",0,6};
__root const unsigned int sndVolume=6;

__root const CFG_HDR cfghdr15={2,"���� ��������",0,63};
__root const char sndMsgSend[64]= "4" ":\\ZBin\\SieJC\\Sounds\\send.wav";

__root const CFG_HDR cfghdr16={2,"���� ������ �� MUC",0,63};
__root const char sndConf[64]= "4" ":\\ZBin\\SieJC\\Sounds\\conf.wav";

__root const CFG_HDR cfghdr17={2,"���� ������ �� PM",0,63};
__root const char sndPM[64]= "4" ":\\ZBin\\SieJC\\Sounds\\message.wav";

__root const CFG_HDR cfghdrsnd1={2,"���� ������� ������",0,63};
__root const char sndOnline[64]= "4" ":\\ZBin\\SieJC\\Sounds\\online.wav";

__root const CFG_HDR cfghdrsnd2={2,"���� ������� �������",0,63};
__root const char sndOffline[64]= "4" ":\\ZBin\\SieJC\\Sounds\\offline.wav";

__root const CFG_HDR cfghdrsnd3={2,"���� composing-�������",0,63};
__root const char sndComposing[64]= "4" ":\\ZBin\\SieJC\\Sounds\\composing.wav";

__root const CFG_HDR cfghdr_SOUNDS_SETUP_END={9,"",0,0};



__root const CFG_HDR cfghdr_PATHS_LEVEL={9,"��������� �����",1,0};

__root const CFG_HDR cfghdr18={2,"�������",0,127};
__root const char HIST_PATH[128]= "4" ":\\ZBin\\SieJC\\history\\";

__root const CFG_HDR cfghdr19={2,"��������",0,127};
__root const char PATH_TO_PIC[128]= "4" ":\\ZBin\\SieJC\\img\\";

__root const CFG_HDR cfghdr34={2,"�������",0,127};
__root const char PATH_TO_AVATARS[128]= "4" ":\\ZBin\\SieJC\\avatars\\";

__root const CFG_HDR cfghdr20={2,"�������",0,63};
__root const char COMMANDS_PATH[64]= "4" ":\\ZBin\\SieJC\\Templates\\commands.txt";

__root const CFG_HDR cfghdr21={2,"���������",0,63};
__root const char MESSAGES_PATH[64]= "4" ":\\ZBin\\SieJC\\Templates\\Messages.txt";

__root const CFG_HDR cfghdr22={2,"��������� �����������",0,63};
__root const char KNOW_FEATURES_PATH[64]= "4" ":\\ZBin\\SieJC\\Templates\\known_features.txt";

__root const CFG_HDR cfghdr23={2,"������ �������",0,63};
__root const char SMILE_FILE[64]= "4" ":\\ZBin\\SieJC\\smiles.cfg";

__root const CFG_HDR cfghdr233={2,"������� �������",0,63};
__root const char SMILE_PATH[64]= "4" ":\\ZBin\\SieJC\\smiles\\";

__root const CFG_HDR cfghdr24={4,"���� �� ���������",0,127};
__root const char DEFAULT_DISC[128]= "4";

__root const CFG_HDR cfghdr244={2, "������� ����. ����",0, 63};
__root const char color_PATH[64]= "4" ":\\ZBin\\SieJC\\Color\\";

__root const CFG_HDR cfghdr_PATHS_LEVEL_END={9,"",0,0};



__root const CFG_HDR cfghdr_DEFTEXTSTAT_LEVEL={9,"����� ��������",1,0};

__root const CFG_HDR cfghdr25={4,"������",0,255};
__root const char DEFTEX_ONLINE[256]="� ����";

__root const CFG_HDR cfghdr26={4,"����� �������",0,255};
__root const char DEFTEX_CHAT[256]="����� ��������";

__root const CFG_HDR cfghdr27={4,"����������",0,255};
__root const char DEFTEX_AWAY[256]="";

__root const CFG_HDR cfghdr28={4,"����������",0,255};
__root const char DEFTEX_XA[256]="";

__root const CFG_HDR cfghdr29={4,"�����",0,255};
__root const char DEFTEX_DND[256]="�����";

__root const CFG_HDR cfghdr30={4,"�����",0,255};
__root const char DEFTEX_INVISIBLE[256]="";

__root const CFG_HDR cfghdr31={4,"�������",0,255};
__root const char DEFTEX_OFFLINE[256]="";

__root const CFG_HDR cfghdr141={4, "�����-������" ,0,255};
__root const char DEFTEX_PLAYER[256]="������";

__root const CFG_HDR cfghdr142={4,"MUC offline",0,255};
__root const char DEFTEX_MUCOFFLINE[256]="";

__root const CFG_HDR cfghdr_DEFTEXTSTAT_LEVEL_END={9,"",0,0};



__root const CFG_HDR cfghdr35={1,"���������",0,12};
__root const unsigned int DEF_SKR=10;


__root const CFG_HDR cfghdr_FONTS={9,"���",1,0};

__root const CFG_HDR cfghdr36={5,"����� �������",0,6};
__root const int ROSTER_FONT = 0;
__root const CFG_CBOX_ITEM cfgcbox_font_roster[6]={
  "���������",
  "��������� ������",
  "�������",
  "������� ������",
  "�������",
  "������� ������"
};

__root const CFG_HDR cfghdr37={5,"����� ������ ���������",0,6};
__root const int MESSAGES_FONT = 0;
__root const CFG_CBOX_ITEM cfgcbox_font_msgwin[6]={
  "���������",
  "��������� ������",
  "�������",
  "������� ������",
  "�������",
  "������� ������"
};

__root const CFG_HDR cfghdr38={5,"������������� ���������",0,2};
__root const int pod_mess = 0;
__root const CFG_CBOX_ITEM cfgcbox10[2]={"���","��"};


__root const CFG_HDR cfghdr_FONTS_END={9,"",0,0};

__root const CFG_HDR cfghdr39={5,"\"���������\" ����������",0,2};
__root const int KBD_LAYOUT = 0;
__root const CFG_CBOX_ITEM cfgcboxkbd[2]={
  "��������� 1",
  "��������� 2"
};

__root const CFG_HDR cfghdr_AUTOSTATUS={9, "����������", 1,0};

__root const CFG_HDR cfghdr40={11,"�������",0,2};
__root const int AUTOSTATUS_ENABLED = 0;

__root const CFG_HDR cfghdr41={1,"����� (� �������)",1,60};
__root const unsigned int AUTOSTATUS_TIME = 5;

__root const CFG_HDR cfghdr42={4, "�����", 0, 255};
__root const char DEFTEX_AUTOSTATUS[256]="���������� \"����������\" ��������";

__root const CFG_HDR cfghdr_AUTOSTATUS_END={9,"",0,0};


