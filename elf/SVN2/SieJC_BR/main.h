#ifndef _MAIN_H_
  #define _MAIN_H_

#include "jabber.h"

////////////////////////////////////////////////////////////////////////////////
//////////////////// Некоторые дополнительные настройки проекта ////////////////
//#define LOG_ALL       // Включить протоколирование входящих / исходящих потоков
                        // Очень подробный лог, лучше не включать

//#define LOG_XML_TREE    // Включить запись отпарсенного XML-дерева
#ifdef NEWSGOLD
//#define LOG_TO_COM_PORT // Лог данных в ком-порт (по DCA-510) - ТОЛЬКО NEWSGOLD
#endif
//#define LOG_IN_DATA     // Включить запись обрабатываемой порции данных

#define USE_PNG_EXT   // Использовать ли расширение PNG для картинок (ELFLoader >2.0)

// Синхронизация прорисовки с помощю:
//#define IDLEUPD //диспатчера ГЕ
// или
//#define SCRP	//ScrP патча и ScrD.elf ельфа

////////////////////////////////////////////////////////////////////////////////

#define TMR_SECOND 216

// Общие функции модуля MAIN.C

#define color(x) (char *)(&(x))

#define SCR_START YDISP


typedef struct
{
  int buf_size;
  char* xml_buffer;
} IPC_BUFFER;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef enum
{
  JS_NOT_CONNECTED,           // нет соединения, нет сокета
  JS_CONNECTED_STATE,         // получен stream:stream
  JS_ZLIB_INIT_ACK,           // Ожидание подтверждения юзания ZLib
  JS_ZLIB_STREAM_INIT_ACK,    // Ожидание ответного ZLib-потока
  JS_SASL_NEGOTIATION,        // Обмен приветствиями SASL
  JS_SASL_NEG_ANS_WAIT,       // Ожидание ответа от сервера на посланный SASL
  JS_SASL_AUTH_ACK,           // Ожидание <success/> после ответа на rspauth
  JS_SASL_NEW_STREAM_ACK,     // Ожидание инициализации нового потока
  JS_SASL_RESBIND_ACK,        // Ожидание привязки ресурса
  JS_SASL_SESS_INIT_ACK,      // Ожидание инициализации сессии
  JS_AUTH_OK,                 // Не-SASL: получена авторизация
  JS_AUTH_ERROR,              // Ошибка авторизациии
  JS_ONLINE,                  // Рабочее состояние при установленном подключении
  JS_ERROR                    // Общий дестрой
} JABBER_STATE;

////////////////////////////////
// Кой-какие типы сообщений из http://www.xmpp.org/rfcs/rfc3921.html и + свои
typedef enum
{
  MSG_NORMAL, // типа "нормал", по дефолту, See RFC
  MSG_ME,     // от меня контакту
  MSG_CHAT,   // от контакта ко мне
  MSG_GCHAT,   // конференция
  MSG_SYSTEM,  // всякого рода сервисные сообщения
  MSG_STATUS,   // Статусные сообщения
  MSG_SUBJECT   // Тема конференции
} MESS_TYPE;


// Типы узлов в списке контактов
typedef enum
{
  T_NORMAL,       // Обычный (просто ресурс)
  T_VIRTUAL,      // Создаётся при создании контакта, для удаления
  T_CONF_ROOT,    // Корень конференции (место доставки публичных сообщений)
  T_CONF_NODE,    // Участник конференции (отображаем только "ресурс" жида)
  T_TRANSPORT,    // Транспортный агент
  T_GROUP         // Группа
}RES_TYPE;

typedef struct
{
  MESS_TYPE mtype;
  char *muc_author;// Имеет смысл использовать только в конференциях
  char *mess;
  void *next;
}LOG_MESSAGE;

typedef struct
{
  JABBER_GC_AFFILIATION aff;
  JABBER_GC_ROLE role;
  char *real_jid;
}CONF_DATA;

typedef char **VCARD;

typedef struct
{
  char* name;                   // Отображаемое имя ресурса
  char* full_name;              // Полный JID (jid/resource)
  RES_TYPE entry_type;          // Тип записи (см. RES_TYPE)
  char status;                  // Статус
  char compos:1;                  // Сообшение о наборе
  char* status_msg;             // Статусное сообщение
  short priority;               // Приоритет ресурса
  unsigned int has_unread_msg;  // Есть ли непрочитанные и сколько
  unsigned int total_msg_count; // Общее количество сообщений
  LOG_MESSAGE* log;             // Начало лога сообщений
  CONF_DATA muc_privs;          // Тут для конференционных контактов - про роли и риал-жид
  VCARD vcard;                  // Здесь хранится vCard для участников конференций
  void* next;                   // Следующий экземпляр
} TRESOURCE;

typedef struct
{
  char* JID;
  char IsVisible;             // Показывать ли в списке (связано с группами)
  int ResourceCount;
  TRESOURCE* res_list;
  char* name;
  JABBER_SUBSCRIPTION subscription;
  char wants_subscription;
  char group;     // >128 -> конференции
  VCARD vcard; // Полученная VCard, для контактов ростера
  void *next;
} CLIST;


// Для списка конференций
typedef struct
{
  char* conf_jid; //UTF-8
  char* muctema;
  void* next;
}MUC_ITEM;

// Для задания своих параметров присутсвия в сети
typedef struct
{
  short priority;
  char status;
  char* message;
}PRESENCE_INFO;

#pragma pack(push)
#pragma pack(1)
typedef struct{
  unsigned char
  vibra_status:1,
  sound_status:1,
  off_contacts:1,
  auto_status:1,
  player_status:1,
  smiles_status:1;
  char color_name[32];
}DEF_SETTINGS;
#pragma pack(pop)

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

void SendAnswer(char *str);

void Vibrate(int Req_Vibra_Count);

void Play(const char *fname);

void QuitCallbackProc(int decision);

void OpenSettings(void);

#endif
