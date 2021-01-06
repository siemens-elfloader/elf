#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_
#include "..\multisim_ipc.h"

#define LG_COPYRIGHT     "MultisimElf v0.9b\n(C) by Shadows\nSinclair\n(R)Rst7\nKreN\n"
//Оставляем только один дефайн иначе будет кака
//#define LANG_RU
//#define LANG_UA
#define LANG_EN

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

#define LG_MENU    "Menu"
#define LG_OPTIONS "Options"
#define LG_CLOSE   "Close"
#define LG_CLEAR   "<C"
#define LG_DOIT    "Doit"
#define LG_PASTESM "Paste"
//-------------
#define LG_SELECT  "Select"
#define	LG_TEXT    "Text"
#define LG_BACK    "Back"
//--------------
#define LG_ADD      "Add"
//--------------

//===============================


//================================
#define LG_MNUEDCFG   "Preferences"
#define LG_MNUPHYSIM  "Physic SIM"
#define LG_MNUVIRTSIM "Virtual SIM"
#define LG_MNUCFG   "Open Config"
#define LG_MNUASNET   "Auto Network"
#define LG_MNUSAVEB   "Save 5401 to file"
#define LG_MNULOADB   "Update 5401 from file"
#define LG_MNUOPENB   "Open File 5401 by TED"
#define LG_MNUSAVEB1   "Save 5402 to file"
#define LG_MNULOADB1   "Update 5402 from file"
#define LG_MNUOPENB1   "Open File 5402 by TED"
#define LG_MNUFIX   "Physic Block(physical SIM must select)"
//--------------
#define LG_CFG_PATH5400S   "Path 5401"
#define LG_CFG_PATH5401S   "Path 5402"
#define LG_CFG_SEC_FCLICK   "Setting switch 1-click"
#define LG_CFG_NSIMENABLE   "Enable rapid switch"
#define LG_CFG_NMAINSIM   "Number Main Sim"
#define LG_CFG_NADITSIM   "Number ADIT Sim"
//--------------
#define LG_MSGERRBLOCK     "Block 5401/5402 not found or in wrong format!"
//=================================

//================================
#define LG_MNUABOUT   "About"

//-------------

//================================
#endif

#endif

