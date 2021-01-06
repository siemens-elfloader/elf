/*
    SieNatJabber Project
    ������� ������ � �������-������

    ������������� ��� �������� ������ XML
*/

#ifndef _JABBER_UTIL_H_
  #define _JABBER_UTIL_H_

#include "xml_parser.h"

#define MAX_MSG_LEN 4096

#define PRES_COUNT 12

typedef enum
{
  ADM_KICK,             // ��� 
  ADM_BAN,              // ���
  ADM_VOICE_REMOVE,     // ������ ������
  ADM_VOICE_GRANT,      // ������������ �����
  ADM_PARTICIPANT,      // Participant
  ADM_MEMBER,           // Member
  ADM_MODERATOR,        // Moderator
  ADM_MODERATOR_REMOVE,  // Moderator remove
  ADM_ADMIN,            // Admin
  ADM_OWNER             // Owner
}MUC_ADMIN;

// ��� �������� ������� ���� � ������� (����� ������������ ����� ����������)
// � ��� ��������� � �����, ���� ����� ����� ��������� ������� � �������
typedef struct
{
  char status;
  short priority;
  char *txt;
}ONLINEINFO;

/**
  * ������� ��� �������� ����������
 **/
void Send_Mood(char *mood, char *text);

/*
  ������� ������������ Jabber Iq
*/
void SendIq(char* to, char* type, char* id, char* xmlns, char* payload);

/*
  ������� �����������, �� ���� ������ �������� �������� stream.
  ����� ����� ����� �������� � ��������
*/
// Context:HELPER
void Send_Welcome_Packet();

void Send_Welcome_Packet_SASL();

/*
  ������� ����������
*/
void Send_Disconnect();

/*
  ����������� �� Jabber-�������
  ����� �����, ��� ����������.
*/
void Send_Auth();

/*
  ������� ��� ����������� (� ���������, ����� ����� �� ��� ������������ 
  ����������� ���������, � �� ���������� � �������� ������ ��������)
*/
// Context: HELPER
void Send_Presence(PRESENCE_INFO *pr_info);

void Send_ShortPresence(char *to,char type);
// ������� ������ � ������ ������������ � ��������� JID
// JID ��������� � UTF-8
void Send_Version_Request(char *dest_jid);

//������ ������� ������� � JID
void Send_Time_Request(char *dest_jid);
//vcard
void Send_Vcard_Request(char *dest_jid);

//lastactivity
void Send_LastActivity_Request(char *dest_jid);

// ������� ������ disco#info
// JID ��������� � UTF-8
void Send_DiscoInfo_Request(char *dest_jid);

/*
  ������� ������ �������
*/
// Context: HELPER
void Send_Roster_Query();

void _sendandfree(char *str);

/*
 ��������� �������� Iq-��������
*/
void Process_Iq_Request(XMLNode* nodeEx);


/*
�������� :)
*/
void Process_Presence_Change(XMLNode* node);

/*
�������� ���������
*/
void Process_Incoming_Message(XMLNode* nodeEx);

// kibab612@jabber.ru/SieJC  => SieJC
char* Get_Resource_Name_By_FullJID(char* full_jid);

/*
�������� ���������� ����� ������� ���� ����������� �� ������ � �����������
*/
unsigned short GetPresenceIndex(char* presence_str);

/*
�������� ���������� ����� ������� ���� ����/���������� �� ������ � �����������
*/
unsigned short GetAffRoleIndex(char* str);

// ���������� ���������������� ������
void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason);

typedef struct
{
  char IsGroupChat;
  char* body;  
}IPC_MESSAGE_S;

typedef struct
{
  char* room_nick;
  char* room_name;
  char* pass;
  int mess_num;
}MUC_ENTER_PARAM;


typedef struct
{
  char *bmname;
  char *mucname;
  char *nick;
  char *pass;
//  char a_join;
//  char *url;
  void *next;
}BM_ITEM;

// Context: HELPER
void SendMessage(char* jid, IPC_MESSAGE_S *mess);

// Context: HELPER
void SendComposing(char* jid, IPC_MESSAGE_S *mess);

// Context: HELPER
void CancelComposing(char* jid, IPC_MESSAGE_S *mess);

// ���������� ������ ������  
void MUCList_Destroy();

// ����� � �����������
void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages);

// ����� �� �����������
void Send_Leave_Conference(char* room);

///////////////////

#endif
