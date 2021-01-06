#ifndef _LANG
#define _LANG

//Оставляем только один дефайн иначе будет кака
#define SET_LANG_RU
//#define SET_LANG_EN

#ifdef SET_LANG_RU
 //Конфиг:
 #define LG_SET_SMS_DAT_PATH        "Путь к SMS.dat"
 #define LG_SET_SMSSOUND            "Путь к мелодии смс"
 #define LG_SET_FOLDERPIC           "Папка с картинками"
 #define LG_SET_FOLDERLOG           "Папка с логом"
 #define LG_SET_SLI                 "Мигать SLI?"
 #define LG_SET_IN_NOTIFY           "Оповещать о новой смс?"
 #define LG_SET_IDLE                "Настройки на ГЭ"
 #define LG_SET_SHOW_IN             "Отображать при"
  #define LG_SET_SHOW_IN_LOCK       "Блокировке"
  #define LG_SET_SHOW_IN_UNLOCK     "Разблокировке"
  #define LG_SET_SHOW_IN_ALLLOCK    "Все случаи"
 #define LG_SET_SHOW_IDLE_TEXT      "Отображать текст на ГЭ?"
 #define LG_SET_TYPE_FNT            "Тип рисования текста"
 #define LG_SET_IDLE_TEXT           "Текст"
 #define LG_SET_TEXT_FORMAT         "Новых SMS %d"
 #define LG_SET_IDLE_XY             "Позиция текста"
 #define LG_SET_IDLE_FNT            "Шрифт"
 #define LG_SET_PNG_FNT             "Путь к пнг шрифту"
 #define LG_SET_FULLFONT            "Полный набор символов?"
 #define LG_SET_ALIGN               "Выровнять"
  #define LG_SET_ALIGN_LEFT         "Влево"
  #define LG_SET_ALIGN_CENTER       "По центру"
  #define LG_SET_ALIGN_RIGHT        "Вправо"
 #define LG_SET_SPACE               "Пиксели между символами"
 #define LG_SET_SHOW_IDLE_PIC       "Отображать картинки на ГЭ?"
 #define LG_SET_IDLE_PIC_XY         "Позиция картинки"
 #define LG_SET_SHOW0NEW            "Отображать при 0 смс?"
 #define LG_SET_PROFILES            "Профили"
 #define LG_SET_PROFILE             "Профиль"
 #define LG_SET_VIBRA               "Вибра"
 #define LG_SET_VIBRA_POWER         "Сила вибры"
 #define LG_SET_VIBRA_COUNT         "Количество циклов"
 #define LG_SET_SOUND               "Использовать звук?"
 #define LG_SET_SOUND_VOLUME        "Громкость звука"
 #define LG_DAEMONS_TEXT            "новых"
 #define LG_LOVENUMBER              "Любимый номер"
#endif

#ifdef LANG_RU
 //Общее:
 const char 
 LG_SEL_NUM[]=            "Выбор номера",
 LG_ANSWER[]=             "Ответ",
 LG_CREATE[]=             "Создать",
 LG_NEW_SMS[]=            "Новое смс",
 LG_NEW_IN[]=             "Новое SMS!",
 LG_NONUM[]=              "Нет номера",
 LG_ADRBOOK[]=            "Адресная книга",
 LG_ADRBOOKD[]=           "Адресная книга(%d)",
 LG_EMPTY[]=              "Пусто",
 LG_CANSEL[]=             "Отмена",
 LG_SEND[]=               "Послать",
 LG_SENDQ[]=              "Отправить?",
 LG_LETTERS[]=            "знаков",
 LG_OPTIONS[]=            "Опции",
 LG_QUIT[]=               "Выход",
 LG_ENT_NUM[]=            "Введите номер!",
 LG_ENT_TEXT[]=           "Введите сообщение!",
 LG_MESS[]=               "Сообщение",
 LG_TO[]=                 "Кому:",
 LG_FROM[]=               "От:",
 LG_INBOX[]=              "Входящие",
 LG_OUTBOX[]=             "Исходящие",
 LG_INCOM[]=              "Входящее",
 LG_OUTCOM[]=             "Исходящее",
 LG_DRAFT[]=              "Черновик",
 LG_STATISTIC[]=          "Статистика",
 LG_SETTINGS[]=           "Настройки",
 LG_OPEN_ERR[]=           "Ошибка открытия",
 LG_TRANSLIT[]=           "Транслит";
// LG_LOVENUMBER[]=         "Любимый номер";
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
