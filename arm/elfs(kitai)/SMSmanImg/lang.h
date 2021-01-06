#ifndef _LANG
#define _LANG

//�����ѧӧݧ�֧� ���ݧ�ܧ� ��էڧ� �է֧�ѧۧ� �ڧߧѧ�� �ҧ�է֧� �ܧѧܧ�
#define SET_LANG_ZH
//#define SET_LANG_EN

#ifdef SET_LANG_ZH
 //�����ļ�:
 #define LG_SET_SMS_DAT_PATH "SMS.dat·��"
 #define LG_SET_SMSSOUND "��ʾ��"
 #define LG_SET_FOLDERPIC "ͼƬ�ļ���"
 #define LG_SET_IN_NOTIFY "��������Ϣ֪ͨ?"
 #define LG_SET_IDLE "���ô�������"
 #define LG_SET_SHOW_IN "��ʾ��"
  #define LG_SET_SHOW_IN_LOCK "������״̬"
  #define LG_SET_SHOW_IN_UNLOCK "����״̬"
  #define LG_SET_SHOW_IN_ALLLOCK "����״̬"
 #define LG_SET_SHOW_IDLE_TEXT "��ʾ���������ı�?"
 #define LG_SET_TYPE_FNT "�ı�����"
 #define LG_SET_IDLE_TEXT "�����ı�"
 #define LG_SET_TEXT_FORMAT "�¶���%d��"
 #define LG_SET_IDLE_XY "�ı�λ��"
 #define LG_SET_IDLE_FNT "����"
 #define LG_SET_PNG_FNT "png����"
 #define LG_SET_FULLFONT "ʹ����������?"
 #define LG_SET_ALIGN "����"
  #define LG_SET_ALIGN_LEFT "�����"
  #define LG_SET_ALIGN_CENTER "����"
  #define LG_SET_ALIGN_RIGHT "�Ҷ���"
 #define LG_SET_SPACE "��������֮�������"
 #define LG_SET_SHOW_IDLE_PIC "��ʾ����ͼƬ?"
 #define LG_SET_IDLE_PIC_XY "ͼƬλ��"
 #define LG_SET_SHOW0NEW "��ʾ��0������Ϣ?"
 #define LG_SET_PROFILES "�龰ģʽ"
 #define LG_SET_PROFILE "�龰ģʽ"
 #define LG_SET_VIBRA "��"
 #define LG_SET_VIBRA_POWER "��ǿ��"
 #define LG_SET_VIBRA_COUNT "�𶯴���"
 #define LG_SET_SOUND "��ʾ��?"
 #define LG_SET_SOUND_VOLUME "����"
#endif
 
#ifdef LANG_ZH
 //������:
 const char LG_SEL_NUM[]="ѡ�����",
 LG_ANSWER[]="�ظ�",
 LG_CREATE[]="�����¶���",
 LG_NEW_SMS[]="�¶���",
 LG_NEW_IN[]="�¶���!",
 LG_NONUM[]="�޺���",
 LG_ADRBOOK[]="ͨѶ¼",
 LG_ADRBOOKD[]="ͨѶ¼(%d)",
 LG_EMPTY[]="�հ�",
 LG_CANSEL[]="ȡ��",
 LG_SEND[]="����",
 LG_SENDQ[]="����?",
 LG_LETTERS[]="������",
 LG_QUIT[]="�˳�",
 LG_ENT_NUM[] = "���������!",
 LG_ENT_TEXT[] = "���������!",
 LG_MESS[] = "����",
 LG_TO[] = "�ռ���:",
 LG_FROM[] = "�ļ���:",
 LG_INBOX[] = "�ռ���",
 LG_OUTBOX[] = "�ѷ���",
 LG_INCOM[] = "�ռ���",
 LG_OUTCOM[] = "������",
 LG_DRAFT[] = "�ݸ�",
 LG_STATISTIC[] = "ͳ��",
 LG_SETTINGS[] = "����",
 LG_OPEN_ERR[] = "��ʱ��������",
 LG_TRANSLIT[] = "����";
#endif

#ifdef SET_LANG_EN
 //Config:
 #define LG_SET_SMS_DAT_PATH "SMS.dat path"
 #define LG_SET_SMSSOUND "Sound file"
 #define LG_SET_FOLDERPIC "Folder pictures"
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
 LG_QUIT[]="Exit",
 LG_ENT_NUM[] = "Input number!",
 LG_ENT_TEXT[] = "Input message!",
 LG_MESS[] = "Message",
 LG_TO[] = "To:",
 LG_FROM[] = "From:",
 LG_INBOX[] = "Inbox",
 LG_OUTBOX[] = "Outbox",
 LG_INCOM[] = "Inbox",
 LG_OUTCOM[] = "Outbox",
 LG_DRAFT[] = "Draft",
 LG_STATISTIC[] = "Statistics",
 LG_SETTINGS[] = "Settings",
 LG_OPEN_ERR[] = "error while open",
 LG_TRANSLIT[] = "Translit";
#endif

#endif //_LANG
