#ifndef _LANG
#define _LANG

//��������� ������ ���� ������ ����� ����� ����
#define SET_LANG_RU
//#define SET_LANG_EN

#ifdef SET_LANG_RU
 //������:
 #define LG_SET_SMS_DAT_PATH        "���� � SMS.dat"
 #define LG_SET_SMSSOUND            "���� � ������� ���"
 #define LG_SET_FOLDERPIC           "����� � ����������"
 #define LG_SET_FOLDERLOG           "����� � �����"
 #define LG_SET_SLI                 "������ SLI?"
 #define LG_SET_IN_NOTIFY           "��������� � ����� ���?"
 #define LG_SET_IDLE                "��������� �� ��"
 #define LG_SET_SHOW_IN             "���������� ���"
  #define LG_SET_SHOW_IN_LOCK       "����������"
  #define LG_SET_SHOW_IN_UNLOCK     "�������������"
  #define LG_SET_SHOW_IN_ALLLOCK    "��� ������"
 #define LG_SET_SHOW_IDLE_TEXT      "���������� ����� �� ��?"
 #define LG_SET_TYPE_FNT            "��� ��������� ������"
 #define LG_SET_IDLE_TEXT           "�����"
 #define LG_SET_TEXT_FORMAT         "����� SMS %d"
 #define LG_SET_IDLE_XY             "������� ������"
 #define LG_SET_IDLE_FNT            "�����"
 #define LG_SET_PNG_FNT             "���� � ��� ������"
 #define LG_SET_FULLFONT            "������ ����� ��������?"
 #define LG_SET_ALIGN               "���������"
  #define LG_SET_ALIGN_LEFT         "�����"
  #define LG_SET_ALIGN_CENTER       "�� ������"
  #define LG_SET_ALIGN_RIGHT        "������"
 #define LG_SET_SPACE               "������� ����� ���������"
 #define LG_SET_SHOW_IDLE_PIC       "���������� �������� �� ��?"
 #define LG_SET_IDLE_PIC_XY         "������� ��������"
 #define LG_SET_SHOW0NEW            "���������� ��� 0 ���?"
 #define LG_SET_PROFILES            "�������"
 #define LG_SET_PROFILE             "�������"
 #define LG_SET_VIBRA               "�����"
 #define LG_SET_VIBRA_POWER         "���� �����"
 #define LG_SET_VIBRA_COUNT         "���������� ������"
 #define LG_SET_SOUND               "������������ ����?"
 #define LG_SET_SOUND_VOLUME        "��������� �����"
 #define LG_DAEMONS_TEXT            "�����"
 #define LG_LOVENUMBER              "������� �����"
#endif

#ifdef LANG_RU
 //�����:
 const char 
 LG_SEL_NUM[]=            "����� ������",
 LG_ANSWER[]=             "�����",
 LG_CREATE[]=             "�������",
 LG_NEW_SMS[]=            "����� ���",
 LG_NEW_IN[]=             "����� SMS!",
 LG_NONUM[]=              "��� ������",
 LG_ADRBOOK[]=            "�������� �����",
 LG_ADRBOOKD[]=           "�������� �����(%d)",
 LG_EMPTY[]=              "�����",
 LG_CANSEL[]=             "������",
 LG_SEND[]=               "�������",
 LG_SENDQ[]=              "���������?",
 LG_LETTERS[]=            "������",
 LG_OPTIONS[]=            "�����",
 LG_QUIT[]=               "�����",
 LG_ENT_NUM[]=            "������� �����!",
 LG_ENT_TEXT[]=           "������� ���������!",
 LG_MESS[]=               "���������",
 LG_TO[]=                 "����:",
 LG_FROM[]=               "��:",
 LG_INBOX[]=              "��������",
 LG_OUTBOX[]=             "���������",
 LG_INCOM[]=              "��������",
 LG_OUTCOM[]=             "���������",
 LG_DRAFT[]=              "��������",
 LG_STATISTIC[]=          "����������",
 LG_SETTINGS[]=           "���������",
 LG_OPEN_ERR[]=           "������ ��������",
 LG_TRANSLIT[]=           "��������";
// LG_LOVENUMBER[]=         "������� �����";
#endif

#ifdef SET_LANG_EN
 //Config:
 #define LG_SET_SMS_DAT_PATH "SMS.dat path"
 #define LG_SET_SMSSOUND "Sound file"
 #define LG_SET_FOLDERPIC "Folder pictures"
 #define LG_SET_FOLDERLOG "Folder log"
 #define LG_SET_SLI "Blink SLI?"
 #define LG_SET_IN_NOTIFY "Incoming notification?"
 #define LG_SET_IDLE "Settings idle"
 #define LG_SET_SHOW_IN "Display under"
  #define LG_SET_SHOW_IN_LOCK "Lock"
  #define LG_SET_SHOW_IN_UNLOCK "Unlock"
  #define LG_SET_SHOW_IN_ALLLOCK "All"
 #define LG_SET_SHOW_IDLE_TEXT "Show idle text?"
 #define LG_SET_TYPE_FNT "Type draw text"
 #define LG_SET_IDLE_TEXT "Text"
 #define LG_SET_TEXT_FORMAT "New SMS %d"
 #define LG_SET_IDLE_XY "Position text"
 #define LG_SET_IDLE_FNT "Font"
 #define LG_SET_PNG_FNT "Patch png font"
 #define LG_SET_FULLFONT "Fullfont use?"
 #define LG_SET_ALIGN "Align"
  #define LG_SET_ALIGN_LEFT "Left"
  #define LG_SET_ALIGN_CENTER "Center"
  #define LG_SET_ALIGN_RIGHT "Right"
 #define LG_SET_SPACE "Pixels between letters"
 #define LG_SET_SHOW_IDLE_PIC "Show idle pictures?"
 #define LG_SET_IDLE_PIC_XY "Position pictures"
 #define LG_SET_SHOW0NEW "Show when 0 new?"
 #define LG_SET_PROFILES "Profiles"
 #define LG_SET_PROFILE "Profile"
 #define LG_SET_VIBRA "Vibra"
 #define LG_SET_VIBRA_POWER "Vibra power"
 #define LG_SET_VIBRA_COUNT "Vibra count"
 #define LG_SET_SOUND "Sound?"
 #define LG_SET_SOUND_VOLUME "Sound volume"
 #define LG_DAEMONS_TEXT "new"
#endif
 
#ifdef LANG_EN
 //Main:
 const char LG_SEL_NUM[]="Select number",
 LG_ANSWER[]="Answer",
 LG_CREATE[]="Create new",
 LG_NEW_SMS[]="New sms",
 LG_NEW_IN[]="New SMS!",
 LG_NONUM[]="No number",
 LG_ADRBOOK[]="Adressbook",
 LG_ADRBOOKD[]="Adressbook(%d)",
 LG_EMPTY[]="Empty",
 LG_CANSEL[]="Cancel",
 LG_SEND[]="Send",
 LG_SENDQ[]="Send?",
 LG_LETTERS[]="letters",
 LG_OPTIONS[]="Options",
 LG_QUIT[]="Exit",
 LG_ENT_NUM[]="Input number!",
 LG_ENT_TEXT[]="Input message!",
 LG_MESS[]="Message",
 LG_TO[]="To:",
 LG_FROM[]="From:",
 LG_INBOX[]="Inbox",
 LG_OUTBOX[]="Outbox",
 LG_INCOM[]="Inbox",
 LG_OUTCOM[]="Outbox",
 LG_DRAFT[]="Draft",
 LG_STATISTIC[]="Statistics",
 LG_SETTINGS[]="Settings",
 LG_OPEN_ERR[]="Error while open",
 LG_TRANSLIT[]="Translit";
#endif

#endif //_LANG
