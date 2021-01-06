/*
    SieNatJabber Project
    Функции работы с контакт-листом

    Данный API обязан присутствовать во ВСЕХ вариантах контакт-листа
*/

#ifndef _CLIST_UTIL_H_
  #define _CLIST_UTIL_H_

#include "main.h"

#define CHAR_ON_LINE 20

#define CLIST_Y1 5 + SCR_START               // ad: меньше сделал (26->5)

// Отрисовать список контактов
  void CList_RedrawCList();

// Переключить видимость для группы
  void CList_ToggleVisibilityForGroup(int GID);
// Получить состояние видимости группы
  int CList_GetVisibilityForGroup(int GID);

// Получить дескриптор контакта по FullJID (JID вместе с ресурсом)
  CLIST* CList_FindContactByJID(char* jid);
  
// Получить дескриптор конфы по JID
  MUC_ITEM* CList_FindMUCByJID(char* jid);
    
// Узнать, есть ли уже такой ресурс у контакта, по FullJID
  TRESOURCE* CList_IsResourceInList(char* jid);

// Добавить к листу контакт. Возвращает структуру созданного контакта.
  CLIST* CList_AddContact(char* jid,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group
                          );

// Изменить параметры контакта (получена подписка и пр)

  void CList_ChangeContactParams(CLIST* Cont_Ex,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group);

  void CList_ChangeComposingStatus(TRESOURCE* Res_Ex, char composing);
    
// Пишет роли контакта в конфе в структуру
  void CList_MUC_SetRole(char* jid, CONF_DATA priv);

// Добавить сообщение в список сообщений контакта
  void CList_AddMessage(char* jid, MESS_TYPE mtype, char* mtext);

// Добавить системное сообщение
  void CList_AddSystemMessage(char* jid, char status, char* status_msg);
// Оно же, но принимает ANSI-строку. Полезно в отдельных случаях :)
  void CList_AddSystemMessageA(char* jid, char status, char* ansi_status_msg);

  TRESOURCE* CList_AddResourceWithPresence(char* jid, char status, char* status_msg, short priority);

// Получить контакт, на котором стоит курсор
  TRESOURCE* CList_GetActiveContact();

// Делаем оффлайнами все ресурсы заданного контакта. Useful для конференций.
  void CList_MakeAllResourcesOFFLINE(CLIST* ClEx);

// Делаем оффлайнами все контакты.
  void CList_MakeAllContactsOFFLINE();  
// Уничтожить список контактов
  void CList_Destroy();

// Изменить режим отображения контактов оффлайн
  void CList_ToggleOfflineDisplay();

// Получить число онлайн-юзверей
  unsigned int CList_GetNumberOfOnlineUsers();

// Получить число юзверей
  unsigned int CList_GetNumberOfUsers();

// Получить число юзверей, без скрытых контактов
  unsigned int CList_GetNumberOfUsers_Visible();

// Получить число непрочитанных
  unsigned int CList_GetUnreadMessages();

// переход на следующий контакт с непрочитанным сообщением
  void nextUnread();

// ставим курсор на нужный ресурс(для автофокуса тоже пригодится)
  void MoveCursorTo(TRESOURCE* NewResEx);

// Проверить, является ли контакт псевдоконтактом группы
  int CList_isGroup(CLIST *cont);
  
// Проверить, является ли контакт корнем конференции
  int CList_isMUC(CLIST *cont);

// Показать информацию о ресурсе во всплывающем окне
  void CList_Display_Popup_Info(TRESOURCE* ResEx);

// Управление курсором
  void CList_MoveCursorUp(int flagi);
  void CList_MoveCursorDown(int flagi);

  void CList_MoveCursorHome();
  void CList_MoveCursorEnd();

// Убить список сообщений
  void KillMsgList(LOG_MESSAGE* messtop);

  void ParseAnswer(WSHDR *ws, const char *s);
  void ExtractAnswer(WSHDR *ws);
#endif
