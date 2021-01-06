/*
    SieNatJabber Project
    Функции работы с контакт-листом

    Специфический для джаббера разбор XML
*/

#ifndef _JABBER_UTIL_H_
  #define _JABBER_UTIL_H_

#include "xml_parser.h"

#define MAX_MSG_LEN 4096

#define PRES_COUNT 12

typedef enum
{
  ADM_KICK,             // Кик 
  ADM_BAN,              // Бан
  ADM_VOICE_REMOVE,     // Лишить голоса
  ADM_VOICE_GRANT,      // Предоставить голос
  ADM_PARTICIPANT,      // Participant
  ADM_MEMBER,           // Member
  ADM_MODERATOR,        // Moderator
  ADM_MODERATOR_REMOVE,  // Moderator remove
  ADM_ADMIN,            // Admin
  ADM_OWNER             // Owner
}MUC_ADMIN;

// Для хранения текущей инфы о статусе (чтобы восстановить после реконнекта)
// И для установки в конфу, если зашли позже установки статуса в ростере
typedef struct
{
  char status;
  short priority;
  char *txt;
}ONLINEINFO;

/**
  * Функция для отправки настроения
 **/
void Send_Mood(char *mood, char *text);

/*
  Посылка стандартного Jabber Iq
*/
void SendIq(char* to, char* type, char* id, char* xmlns, XMLNode* payload);

/*
  Послать приветствие, на него сервер высылает ответный stream.
  После этого можно общаться с сервером
*/
// Context:HELPER
void Send_Welcome_Packet();

void Send_Welcome_Packet_SASL();

/*
  Послать дисконнект
*/
void Send_Disconnect();

/*
  Авторизация на Jabber-сервере
  Самая тупая, без извращений.
*/
void Send_Auth();

/*
  Послать своё присутствие (в частности, после этого на нас вываливаются 
  присутствия остальных, а мы появляемся в ресурсах своего контакта)
*/
// Context: HELPER
void Send_Presence(PRESENCE_INFO *pr_info);

void Send_ShortPresence(char *to,char type);
// Послать запрос о версии пользователю с указанным JID
// JID указываем в UTF-8
void Send_Version_Request(char *dest_jid);

//Запрос времени клиента с JID
void Send_Time_Request(char *dest_jid);
//vcard
void Send_Vcard_Request(char *dest_jid);

//lastactivity
void Send_LastActivity_Request(char *dest_jid);

// Послать запрос disco#info
// JID указываем в UTF-8
void Send_DiscoInfo_Request(char *dest_jid);

/*
  Послать запрос ростера
*/
// Context: HELPER
void Send_Roster_Query();

void _sendandfree(char *str);

/*
 Обработка входящих Iq-запросов
*/
void Process_Iq_Request(XMLNode* nodeEx);


/*
Презенсы :)
*/
void Process_Presence_Change(XMLNode* node);

/*
Входящие сообщения
*/
void Process_Incoming_Message(XMLNode* nodeEx);

// kibab612@jabber.ru/SieJC  => SieJC
char* Get_Resource_Name_By_FullJID(char* full_jid);

/*
Получить внутренний номер данного типа присутствия по строке с присутсвием
*/
unsigned short GetPresenceIndex(char* presence_str);

/*
Получить внутренний номер данного типа роли/полномочий по строке с присутсвием
*/
unsigned short GetAffRoleIndex(char* str);

// Исполнение административных команд
void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason);

typedef struct
{
  char IsGroupChat;
  char IsAttention;
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

// Уничтожить список комнат  
void MUCList_Destroy();

// Войти в конференцию
void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages);

// Выйти из конференции
void Send_Leave_Conference(char* room, char *reason);

// Установить тему конфы
void Set_Conference_Topic(char *room, char* topic);

///////////////////

#endif
