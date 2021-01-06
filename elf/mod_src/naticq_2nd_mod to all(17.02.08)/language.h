#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_

#define LG_COPYRIGHT     "NATICQ v2.0\nRevision %d\n(C) by Rst7/CBSIE\nKren\nKibab\nShadow\nSeklth"

//Оставляем только один дефайн иначе будет кака
#ifdef EVILFOX_2
#define LANG_EN
#else
#define LANG_RU
#endif
//#define LANG_UA
//#define LANG_EN

#ifdef LANG_RU

#define LG_SLION      "Sli Mode"
#define LG_ILUON      "Illum. Mode"
#define LG_INCON      "Popup Sender"
#define LG_INITSND    "Init Ext. Sounds"
#define LG_MSGINFO    "Msg Info"

#define LG_ALREADY_STARTED "Уже запущена!"

#define LG_CLTITLE "C-List"
#define LG_CLT9INP "Ввод T9: "

#define LG_CLERROR "ошибка"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "Не в списке"
//===============================

#define LG_MENU    "Меню"
#define LG_OPTIONS "Опции"
#define LG_CLOSE   "Закрыть"
#define LG_CLEAR   "<C"
#define LG_DOIT    "Выполнить"
#define LG_PASTESM "Вставить"
//-------------
#define LG_SELECT  "Выбор"
#define	LG_TEXT    "Текст"
#define LG_BACK    "Назад"
//--------------
#define LG_ADD      "Добавить"
#define LG_ADDCNT   "Добавить контакт"
#define LG_ENTERUIN "Введите UIN:"
//--------------
#define LG_ADDREN  "Добав./имя"
#define LG_SETNICK "Set nickname of %u as:" //Какого-то эти строки будучи написаны
#define LG_SMLDESC "Smile: %u %s"           //на русском отображаются крякозябликами
#define LG_ADDSMIL "Вставить смайлик"

//===============================

#define LG_ADDCONT "Добавить контакт..."
#define LG_AUTHREQ   "Авторизуйте меня..."
#define LG_AUTHGRANT "Вы авторизованы"

//================================
#define LG_MNUSTATUS  "Статус"
#define LG_MNUXSTATUS "X-Статус"
#define LG_MNUADDCONT "Добавить контакт"
#define LG_MNUVIBRA   "Режим вибры"
#define LG_MNUSOUND   "Режим звука"
#define LG_MNUSHOWOFF "Офф. контакты"
#define LG_MNUSHOWGROUP "Группы"
#define LG_MNUEDCFG   "Настройки"
#define LG_MNUDISCONNECT "Оборвать связь"
#define LG_MNUPING    "Пинг"
#define LG_MNUABOUT   "Об эльфе"
//--------------
#define LG_MNUQUOTE    "Цитировать"
#define LG_MNUADDSML   "Вставить смайл"
#define LG_MNUSHINFO   "Получить инфо"
#define LG_MNUADDREN   "Добав./имя"
#define LG_MNUSAUTHREQ "Запрос авториз."
#define LG_MNUSAUTHGRT "Авторизовать"
#define LG_MNUOPENLOG  "Открыть историю"
#define LG_MNUCLEARCHT "Очистить чат"

#define LG_MNUEDNEXTACT "Следующий чат"
#define LG_MNUEDPREVACT "Предыдущий чат"

//================================
#define LG_CHGSTATUS "Сменить статус"
#define LG_CHGXSTATUS "Сменить X-статус"

#define LG_STONLINE "В сети"
#define LG_STAWAY   "Отошёл"
#define LG_STNA     "Недоступен"
#define LG_STDND    "Не беспокоить"
#define LG_STOCCUP  "Занят"
#define LG_STFFC    "Готов болтать"
#define LG_STINVIS  "Невидимый"
#define LG_STDEPRESSION "Депрессия"
#define LG_STEVIL "Злой"
#define LG_STHOME "Дома"
#define LG_STLUNCH "Жру"
#define LG_STWORK "На работе"

//================================

#define LG_ALL_CAN_SEE          "Видимый для всех"
#define LG_VISLIST_CAN_SEE      "Видимый только для списка видящих"
#define LG_INVISLIST_CANNOT_SEE "Видимый для всех, кроме списка невидящих"
#define LG_CONTACTLIST_CAN_SEE  "Видимый только для списка контактов"
#define LG_NOBODY_CAN_SEE       "Невидимый для всех"

#define LG_ENTERNAME      "Введите имя"
#define LG_CHOOSEGROUP    "Выберите группу"
#define LG_PRIVSTATUS     "Приватный статус"
#define LG_MANAGELIST     "Управление списком"

//================================

#define LG_MSGILLEGMSGCON "Неверное сообщение ENIP_SOCK_CONNECTED!"
#define LG_MSGILLEGMSGREA "Неверное сообщение ENIP_DATA_READ"
#define LG_MSGCANTCONN    "Невозможно подключиться!"
#define LG_MSGCANTCRSC    "Невозможно создать сокет, перезапуск GPRS!"
#define LG_MSGHOSTNFND    "Сервер не найден!"
#define LG_MSGVIBRADIS    "Вибра отключена!"
#define LG_MSGVIBRAENA    "Вибра включена!"
#define LG_MSGSNDDIS      "Звуки отключены!"
#define LG_MSGSNDENA      "Звуки включены!"
#define LG_MSGNOUINPASS   "Введите UIN/пароль!"
#define LG_MSGSMILNOTFND  "Смайлы не найдены!"

//=================================

#define LG_HISTIOERR "Ошибка I/O  #%u"

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
#define LG_GRGPRSUP      "GPRS up, wait 10 sec..."

#endif

#ifdef LANG_UA

#define LG_ALREADY_STARTED "Вже працює!"

#define LG_CLTITLE "Контакти..."
#define LG_CLT9INP "Ввід T9: "

#define LG_CLERROR "помилка"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "Нема в списку"
//===============================

#define LG_MENU    "Меню"
#define LG_OPTIONS "Опції"
#define LG_CLOSE   "Закрити"
#define LG_CLEAR   "<C"
#define LG_DOIT    "Виконати"
#define LG_PASTESM "Вставити"
//-------------
#define LG_SELECT  "Вибір"
#define	LG_TEXT    "Текст"
#define LG_BACK    "Назад"
//--------------
#define LG_ADD      "Додати"
#define LG_ADDCNT   "Додати контакт"
#define LG_ENTERUIN "Введіть UIN:"
//--------------
#define LG_ADDREN  "Додати/ім'я"
#define LG_SETNICK "Set nickname of %u as:" //Какого-то эти строки будучи написаны
#define LG_SMLDESC "Smile: %u %s"           //на русском отображаются крякозябликами
#define LG_ADDSMIL "Вставити смайлик"

//===============================

#define LG_ADDCONT "Додати контакт..."
#define LG_AUTHREQ   "Авторизуйте мене..."
#define LG_AUTHGRANT "Вас авторизовано"

//================================
#define LG_MNUSTATUS  "Статус"
#define LG_MNUXSTATUS "X-Статус"
#define LG_MNUADDCONT "Додати контакт"
#define LG_MNUVIBRA   "Режим вібри"
#define LG_MNUSOUND   "Режим звуків"
#define LG_MNUSHOWOFF "Офф. контакты"
#define LG_MNUSHOWGROUP "Групи"
#define LG_MNUEDCFG   "Параметри"
#define LG_MNUDISCONNECT "Розiрвати зв'язок"
#define LG_MNUPING    "Пiнг"
#define LG_MNUABOUT   "Про ельфа"
//--------------
#define LG_MNUQUOTE    "Цитувати"
#define LG_MNUADDSML   "Вставити смайл"
#define LG_MNUSHINFO   "Отримати інфо"
#define LG_MNUADDREN   "Додати/ім'я"
#define LG_MNUSAUTHREQ "Запит авториз."
#define LG_MNUSAUTHGRT "Авторизувати"
#define LG_MNUOPENLOG  "Відкрити історію"
#define LG_MNUCLEARCHT "Очистити чат"

#define LG_MNUEDNEXTACT "Наступний чат"
#define LG_MNUEDPREVACT "Попередній чат"

//================================
#define LG_CHGSTATUS "Змінити статус"
#define LG_CHGXSTATUS "Змінити X-статус"

#define LG_STONLINE "В мережі"
#define LG_STAWAY   "Відійшов"
#define LG_STNA     "Недоступний"
#define LG_STDND    "Не турбувати"
#define LG_STOCCUP  "Зайнятий"
#define LG_STFFC    "Вільний для чату"
#define LG_STINVIS  "Невидимий"
#define LG_STDEPRESSION "Депресія"
#define LG_STEVIL "Злий"
#define LG_STHOME "Вдома"
#define LG_STLUNCH "Їм"
#define LG_STWORK "На роботі"

//================================

#define LG_ALL_CAN_SEE          "Видимий для всіх"
#define LG_VISLIST_CAN_SEE      "Видимий тільки для списку, що бачать мене"
#define LG_INVISLIST_CANNOT_SEE "Видимий для всіх, окрім списку, що не бачать мене"
#define LG_CONTACTLIST_CAN_SEE  "Видимий тільки для списку контактів"
#define LG_NOBODY_CAN_SEE       "Невидимий для всіх"

#define LG_ENTERNAME      "Введіть ім'я"
#define LG_CHOOSEGROUP    "Виберіть групу"
#define LG_PRIVSTATUS     "Приватний статус"
#define LG_MANAGELIST     "Управління списком"

//================================

#define LG_MSGILLEGMSGCON "Невірне повідомлення ENIP_SOCK_CONNECTED!"
#define LG_MSGILLEGMSGREA "Невірне повідомлення ENIP_DATA_READ"
#define LG_MSGCANTCONN    "Неможливо підключитись!"
#define LG_MSGCANTCRSC    "Неможливо створити сокет, перезапуск GPRS!"
#define LG_MSGHOSTNFND    "Сервер не знайдено!"
#define LG_MSGVIBRADIS    "Вібру вимкнено!"
#define LG_MSGVIBRAENA    "Вібру увімкнено!"
#define LG_MSGSNDDIS      "Звуки вимкнено!"
#define LG_MSGSNDENA      "Звуки увімкнено!"
#define LG_MSGNOUINPASS   "Введіть UIN/пароль!"
#define LG_MSGSMILNOTFND  "Смайли не знайдено!"

//=================================

#define LG_HISTIOERR "Помилка I/O  #%u"

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
#define LG_GRGPRSUP      "GPRS up, wait 10 sec..."

#endif

#ifdef LANG_EN

#define LG_ALREADY_STARTED "Already started!"

#define LG_CLTITLE "C-List..."
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
#define LG_SLION      "Sli Mode"
#define LG_ILUON      "Illum. Mode"
#define LG_INCON      "Popup Sender"
#define LG_MNUSHOWOFF "Off. contacts"
#define LG_MNUSHOWGROUP "Groups"
#define LG_MNUEDCFG   "Edit config"
#define LG_INITSND    "Init Ext. Sounds"
#define LG_MNUDISCONNECT "Disconnect"
#define LG_MNUPING    "Ping"
#define LG_MSGINFO    "Msg Info"
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
#define LG_MSGVIBRADIS    "Vibrа disabled!"
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
#define LG_GRGPRSUP      "GPRS up, wait 10 sec..."

#endif

#endif


