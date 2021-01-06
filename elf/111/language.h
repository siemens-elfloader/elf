#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_

#define LG_COPYRIGHT     "NATICQ v2.0\nRevision %d\n(C) by Rst7/CBSIE\nKren\nKibab\nShadow\nSeklth"

//��������� ������ ���� ������ ����� ����� ����
#define LANG_RU
//#define LANG_UA
//#define LANG_EN

#ifdef LANG_RU

#define LG_ALREADY_STARTED "��� ��������!"

#define LG_CLTITLE "��������..."
#define LG_CLT9INP "���� T9: "

#define LG_CLERROR "������"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "�� � ������"
//===============================

#define LG_MENU    "����"
#define LG_OPTIONS "�����"
#define LG_CLOSE   "�������"
#define LG_CLEAR   "<C"
#define LG_DOIT    "���������"
#define LG_PASTESM "��������"
//-------------
#define LG_SELECT  "�����"
#define	LG_TEXT    "�����"
#define LG_BACK    "�����"
//--------------
#define LG_ADD      "��������"
#define LG_ADDCNT   "�������� �������"
#define LG_ENTERUIN "������� UIN:"
//--------------
#define LG_ADDREN  "�����./���"
#define LG_SETNICK "Set nickname of %u as:" //������-�� ��� ������ ������ ��������
#define LG_SMLDESC "Smile: %u %s"           //�� ������� ������������ ��������������
#define LG_ADDSMIL "�������� �������"

//===============================

#define LG_ADDCONT "�������� �������..."
#define LG_AUTHREQ   "����������� ����..."
#define LG_AUTHGRANT "�� ������������"

//================================
#define LG_MNUSTATUS  "������"
#define LG_MNUXSTATUS "X-������"
#define LG_MNUADDCONT "�������� �������"
#define LG_MNUVIBRA   "����� �����"
#define LG_MNUSOUND   "����� �����"
#define LG_MNUSHOWOFF "���. ��������"
#define LG_MNUSHOWGROUP "������"
#define LG_MNUEDCFG   "���������"
#define LG_MNUDISCONNECT "�������� �����"
#define LG_MNUPING    "����"
#define LG_MNUABOUT   "�� �����"
//--------------
#define LG_MNUQUOTE    "����������"
#define LG_MNUADDSML   "�������� �����"
#define LG_MNUSHINFO   "�������� ����"
#define LG_MNUADDREN   "�����./���"
#define LG_MNUSAUTHREQ "������ �������."
#define LG_MNUSAUTHGRT "������������"
#define LG_MNUOPENLOG  "������� �������"
#define LG_MNUCLEARCHT "�������� ���"

#define LG_MNUEDNEXTACT "��������� ���"
#define LG_MNUEDPREVACT "���������� ���"

//================================
#define LG_CHGSTATUS "������� ������"
#define LG_CHGXSTATUS "������� X-������"


#define LG_STONLINE "� ����"
#define LG_STAWAY   "������"
#define LG_STNA     "����������"
#define LG_STDND    "�� ����������"
#define LG_STOCCUP  "�����"
#define LG_STFFC    "����� �������"
#define LG_STINVIS  "���������"
#define LG_STDEPRESSION "���������"
#define LG_STEVIL "����"
#define LG_STHOME "����"
#define LG_STLUNCH "���"
#define LG_STWORK "�� ������"

#define LG_COMMENT "�����������:"

//================================

#define LG_ALL_CAN_SEE          "������� ��� ����"
#define LG_VISLIST_CAN_SEE      "������� ������ ��� ������ �������"
#define LG_INVISLIST_CANNOT_SEE "������� ��� ����, ����� ������ ���������"
#define LG_CONTACTLIST_CAN_SEE  "������� ������ ��� ������ ���������"
#define LG_NOBODY_CAN_SEE       "��������� ��� ����"

#define LG_ENTERNAME      "������� ���"
#define LG_CHOOSEGROUP    "�������� ������"
#define LG_PRIVSTATUS     "��������� ������"
#define LG_MANAGELIST     "���������� �������"

//================================

#define LG_MSGILLEGMSGCON "�������� ��������� ENIP_SOCK_CONNECTED!"
#define LG_MSGILLEGMSGREA "�������� ��������� ENIP_DATA_READ"
#define LG_MSGCANTCONN    "���������� ������������!"
#define LG_MSGCANTCRSC    "���������� ������� �����, ���������� GPRS!"
#define LG_MSGHOSTNFND    "������ �� ������!"
#define LG_MSGVIBRADIS    "����� ���������!"
#define LG_MSGVIBRAENA    "����� ��������!"
#define LG_MSGSNDDIS      "����� ���������!"
#define LG_MSGSNDENA      "����� ��������!"
#define LG_MSGNOUINPASS   "������� UIN/������!"
#define LG_MSGSMILNOTFND  "������ �� �������!"

//=================================

#define LG_HISTIOERR "������ I/O  #%u"

//=================================

#define LG_GRSTATESTRING "State: %d, RXstate: %d\nRx:%db,Tx:%db\nQueue: %db\n%s\n%t"

#define LG_GRSKEYEXIT    "Exit"
#define LG_GRSKEYCLIST   "CList"

#define LG_GRTRYLOGIN    "Try to login..."
#define LG_GRWAITFORGPRS "Waiting for GPRS up..."
#define LG_GRSENDDNR     "Send DNR..."
#define LG_GRDNRERROR    "DNR ERROR %d!"
#define LG_GRDNROK       "DNR Ok, connecting..."
#define LG_GRBADPACKET   "Bad packet"
#define LG_GRLOGINMSG    "%s"
#define LG_GRSTATUSCHNG  "SC%d: %04X"
#define LG_GRERROR       "ERR: %s"
#define LG_GRRECVMSG     "MSG%d: %s"
#define LG_GRGPRSUP      "GPRS ������ ��������, ����������� ����� %d ������..."
#define LG_GRDBLCONNECT  "������� ����� � ������� �������"
#define LG_GRRECONNECT   "%s\n������, ��������������� ����� %d ������..."


#endif

#ifdef LANG_UA

#define LG_ALREADY_STARTED "��� ������!"

#define LG_CLTITLE "��������..."
#define LG_CLT9INP "��� T9: "

#define LG_CLERROR "�������"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "���� � ������"
//===============================

#define LG_MENU    "����"
#define LG_OPTIONS "�����"
#define LG_CLOSE   "�������"
#define LG_CLEAR   "<C"
#define LG_DOIT    "��������"
#define LG_PASTESM "��������"
//-------------
#define LG_SELECT  "����"
#define	LG_TEXT    "�����"
#define LG_BACK    "�����"
//--------------
#define LG_ADD      "������"
#define LG_ADDCNT   "������ �������"
#define LG_ENTERUIN "������ UIN:"
//--------------
#define LG_ADDREN  "������/��'�"
#define LG_SETNICK "Set nickname of %u as:" //������-�� ��� ������ ������ ��������
#define LG_SMLDESC "Smile: %u %s"           //�� ������� ������������ ��������������
#define LG_ADDSMIL "�������� �������"

//===============================

#define LG_ADDCONT "������ �������..."
#define LG_AUTHREQ   "����������� ����..."
#define LG_AUTHGRANT "��� ������������"

//================================
#define LG_MNUSTATUS  "������"
#define LG_MNUXSTATUS "X-������"
#define LG_MNUADDCONT "������ �������"
#define LG_MNUVIBRA   "����� ����"
#define LG_MNUSOUND   "����� �����"
#define LG_MNUSHOWOFF "���. ��������"
#define LG_MNUSHOWGROUP "�����"
#define LG_MNUEDCFG   "���������"
#define LG_MNUDISCONNECT "���i����� ��'����"
#define LG_MNUPING    "�i��"
#define LG_MNUABOUT   "��� �����"
//--------------
#define LG_MNUQUOTE    "��������"
#define LG_MNUADDSML   "�������� �����"
#define LG_MNUSHINFO   "�������� ����"
#define LG_MNUADDREN   "������/��'�"
#define LG_MNUSAUTHREQ "����� �������."
#define LG_MNUSAUTHGRT "������������"
#define LG_MNUOPENLOG  "³������ ������"
#define LG_MNUCLEARCHT "�������� ���"

#define LG_MNUEDNEXTACT "��������� ���"
#define LG_MNUEDPREVACT "��������� ���"

//================================
#define LG_CHGSTATUS "������ ������"
#define LG_CHGXSTATUS "������ X-������"

#define LG_STONLINE "� �����"
#define LG_STAWAY   "³�����"
#define LG_STNA     "�����������"
#define LG_STDND    "�� ���������"
#define LG_STOCCUP  "��������"
#define LG_STFFC    "³����� ��� ����"
#define LG_STINVIS  "���������"
#define LG_STDEPRESSION "�������"
#define LG_STEVIL "����"
#define LG_STHOME "�����"
#define LG_STLUNCH "��"
#define LG_STWORK "�� �����"

#define LG_COMMENT "�����������:"

//================================

#define LG_ALL_CAN_SEE          "������� ��� ���"
#define LG_VISLIST_CAN_SEE      "������� ����� ��� ������, �� ������ ����"
#define LG_INVISLIST_CANNOT_SEE "������� ��� ���, ���� ������, �� �� ������ ����"
#define LG_CONTACTLIST_CAN_SEE  "������� ����� ��� ������ ��������"
#define LG_NOBODY_CAN_SEE       "��������� ��� ���"

#define LG_ENTERNAME      "������ ��'�"
#define LG_CHOOSEGROUP    "������� �����"
#define LG_PRIVSTATUS     "��������� ������"
#define LG_MANAGELIST     "��������� �������"

//================================

#define LG_MSGILLEGMSGCON "������ ����������� ENIP_SOCK_CONNECTED!"
#define LG_MSGILLEGMSGREA "������ ����������� ENIP_DATA_READ"
#define LG_MSGCANTCONN    "��������� �����������!"
#define LG_MSGCANTCRSC    "��������� �������� �����, ���������� GPRS!"
#define LG_MSGHOSTNFND    "������ �� ��������!"
#define LG_MSGVIBRADIS    "³��� ��������!"
#define LG_MSGVIBRAENA    "³��� ��������!"
#define LG_MSGSNDDIS      "����� ��������!"
#define LG_MSGSNDENA      "����� ��������!"
#define LG_MSGNOUINPASS   "������ UIN/������!"
#define LG_MSGSMILNOTFND  "������ �� ��������!"

//=================================

#define LG_HISTIOERR "������� I/O  #%u"

//=================================
#define LG_GRSTATESTRING "State: %d, RXstate: %d\nRx: %db, Tx: %db\nQueue: %db\n%s\n%t"
#define LG_GRSKEYEXIT    "Exit"
#define LG_GRSKEYCLIST   "CList"

#define LG_GRTRYLOGIN    "Try to login..."
#define LG_GRWAITFORGPRS "Waiting for GPRS up..."
#define LG_GRSENDDNR     "Send DNR..."
#define LG_GRDNRERROR    "DNR ERROR %d!"
#define LG_GRDNROK       "DNR Ok, connecting..."
#define LG_GRBADPACKET   "Bad packet"
#define LG_GRLOGINMSG    "%s"
#define LG_GRSTATUSCHNG  "SC%d: %04X"
#define LG_GRERROR       "ERR: %s"
#define LG_GRRECVMSG     "MSG%d: %s"
#define LG_GRGPRSUP      "GPRS up, wait %d sec..."
#define LG_GRDBLCONNECT  "Another client connected"
#define LG_GRRECONNECT   "%s\nReconect after %d second..."

#endif

#ifdef LANG_EN

#define LG_ALREADY_STARTED "Already started!"

#define LG_CLTITLE "Contacts..."
#define LG_CLT9INP "T9 Key: "

#define LG_CLERROR "error"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "Not in list"
//===============================

#define LG_MENU    "Menu"
#define LG_OPTIONS "Options"
#define LG_CLOSE   "Close"
#define LG_CLEAR   "< C"
#define LG_DOIT    "Do it!"
#define LG_PASTESM "Paste it!"
//-------------
#define LG_SELECT  "Select"
#define	LG_TEXT    "Text"
#define LG_BACK    "Back"
//--------------
#define LG_ADD      "Add!"
#define LG_ADDCNT   "Add Contact"
#define LG_ENTERUIN "Please enter uin:"
//--------------
#define LG_ADDREN  "Add/Rename"
#define LG_SETNICK "Set nickname of %u as"
#define LG_SMLDESC "Smile: %u %s"
#define LG_ADDSMIL "Add Smiles"

//===============================

#define LG_ADDCONT "Add contact..."
#define LG_AUTHREQ   "Please authorize me..."
#define LG_AUTHGRANT "You are authorized!"

//================================
#define LG_MNUSTATUS  "Status"
#define LG_MNUXSTATUS "X-Status"
#define LG_MNUADDCONT "Add Contact"
#define LG_MNUVIBRA   "Vibra mode"
#define LG_MNUSOUND   "Sound mode"
#define LG_MNUSHOWOFF "Off. contacts"
#define LG_MNUSHOWGROUP "Groups"
#define LG_MNUEDCFG   "Edit config"
#define LG_MNUDISCONNECT "Disconnect"
#define LG_MNUPING    "Ping"
#define LG_MNUABOUT   "About"
//-------------
#define LG_MNUQUOTE    "Quote"
#define LG_MNUADDSML   "Add smile"
#define LG_MNUSHINFO   "Get short info"
#define LG_MNUADDREN   "Add/rename"
#define LG_MNUSAUTHREQ "Send Auth Req"
#define LG_MNUSAUTHGRT "Send Auth Grant"
#define LG_MNUOPENLOG  "Open logfile"
#define LG_MNUCLEARCHT "Clear log"

#define LG_MNUEDNEXTACT "Next active"
#define LG_MNUEDPREVACT "Prev. active"

//================================
#define LG_CHGSTATUS "Change Status"
#define LG_CHGXSTATUS "Change X-Status"

#define LG_STONLINE "Online"
#define LG_STAWAY   "Away"
#define LG_STNA     "Not Available"
#define LG_STDND    "Do Not Disturb"
#define LG_STOCCUP  "Occupied"
#define LG_STFFC    "Free For Chat"
#define LG_STINVIS  "Invisible"
#define LG_STDEPRESSION "Depression"
#define LG_STEVIL "Evil"
#define LG_STHOME "Home"
#define LG_STLUNCH "Lunch"
#define LG_STWORK "Work"

#define LG_COMMENT "Comment:"

//================================

#define LG_ALL_CAN_SEE          "Visible for all"
#define LG_VISLIST_CAN_SEE      "Visible only for list seeing"
#define LG_INVISLIST_CANNOT_SEE "Visible for all, except for list blind"
#define LG_CONTACTLIST_CAN_SEE  "Visible only for list of contacts"
#define LG_NOBODY_CAN_SEE       "Invisible for all"

#define LG_ENTERNAME      "Enter a name"
#define LG_CHOOSEGROUP    "Choose a group"
#define LG_PRIVSTATUS     "Private status"
#define LG_MANAGELIST     "Management by list"

//================================

#define LG_MSGILLEGMSGCON "Illegal message ENIP_SOCK_CONNECTED!"
#define LG_MSGILLEGMSGREA "Illegal message ENIP_DATA_READ"
#define LG_MSGCANTCONN    "Can't connect!"
#define LG_MSGCANTCRSC    "Can't create socket, GPRS restarted!"
#define LG_MSGHOSTNFND    "Host not found!"
#define LG_MSGVIBRADIS    "Vibr� disabled!"
#define LG_MSGVIBRAENA    "Vibra enabled!"
#define LG_MSGSNDDIS      "Sounds disabled!"
#define LG_MSGSNDENA      "Sounds enabled!"
#define LG_MSGNOUINPASS   "Please setup UIN/PASS!"
#define LG_MSGSMILNOTFND  "Can't find smiles!"

//=================================

#define LG_HISTIOERR "I/O Error #%u"

//=================================

#define LG_GRSTATESTRING "State: %d, RXstate: %d\nRx: %db, Tx: %db\nQueue: %db\n%s\n%t"
#define LG_GRSKEYEXIT    "Exit"
#define LG_GRSKEYCLIST   "CList"

#define LG_GRTRYLOGIN    "Try to login..."
#define LG_GRWAITFORGPRS "Waiting for GPRS up..."
#define LG_GRSENDDNR     "Send DNR..."
#define LG_GRDNRERROR    "DNR ERROR %d!"
#define LG_GRDNROK       "DNR Ok, connecting..."
#define LG_GRBADPACKET   "Bad packet"
#define LG_GRLOGINMSG    "%s"
#define LG_GRSTATUSCHNG  "SC%d: %04X"
#define LG_GRERROR       "ERR: %s"
#define LG_GRRECVMSG     "MSG%d: %s"
#define LG_GRGPRSUP      "GPRS up, wait %d sec..."
#define LG_GRDBLCONNECT  "Another client connected"
#define LG_GRRECONNECT   "%s\nReconect after %d second..."

#endif

#endif


