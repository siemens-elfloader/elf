#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_
#include "..\multisim_ipc.h"

#define LG_COPYRIGHT     "MultisimElf v0.9b\n(C) by Shadows\nSinclair\n(R)Rst7\nKreN\n"
//Оставляем только один дефайн иначе будет кака
#define LANG_RU
//#define LANG_UA
//#define LANG_EN

#ifdef LANG_RU

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
//--------------

//===============================


//================================
#define LG_MNUEDCFG   "Настройки"
#define LG_MNUPHYSIM  "Физическая сим"
#define LG_MNUVIRTSIM "Виртуальная сим"
#define LG_MNUABOUT   "Об эльфе"
#define LG_MNUCFG   "Открыть конфиг"
#define LG_MNUASNET   "Автовыбор сети"
#define LG_MNUSAVEB   "Сохранить 5401 в файл"
#define LG_MNULOADB   "Обновить 5401 из файла"
#define LG_MNUOPENB   "Открыть файл 5401 в TED"
#define LG_MNUSAVEB1   "Сохранить 5402 в файл"
#define LG_MNULOADB1   "Обновить 5402 из файла"
#define LG_MNUOPENB1   "Открыть файл 5402 в TED"
#define LG_MNUFIX   "Пофиксить блоки (physical SIM must select)"
//--------------
#define LG_CFG_PATH5400S   "Путь для  блока 5401"
#define LG_CFG_PATH5401S   "Путь для  блока 5402"
#define LG_CFG_SEC_FCLICK   "Настройка переключения 1-click"
#define LG_CFG_NSIMENABLE   "Разрешить быстрое переключение"
#define LG_CFG_NMAINSIM   "Номер основной сим"
#define LG_CFG_NADITSIM   "Номер допольнительной сим"
//--------------
#define LG_MSGERRBLOCK     "Блок 5401/5402 не найден либо имеет неверный формат!"
//=================================



//=================================


#endif

#ifdef LANG_UA


#endif

#ifdef LANG_EN


//================================
#define LG_MNUABOUT   "About"

//-------------

//================================
#endif

#endif

