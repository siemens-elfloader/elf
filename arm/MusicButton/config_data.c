#include "c:\arm\inc\swilib.h"
#include "..\inc\cfg_items.h"
//------Defines for key types--------------
#define KEY_ONE_CLICK 0
#define KEY_DOUBLE_CLICK 1
#define KEY_LONG_PRESS 2
#define KEY_TWO 3
#define KEY_NOT_USE 4
#define TYPE_ONLY_LOCK 0
#define TYPE_ONLY_UNLOCK 1
#define TYPE_BOTH 2
//------end of defines--------------------------------------------
__root const CFG_HDR cfghdr0_0={CFG_CBOX,"Когда работать?",0,3};
__root const unsigned int MainType=TYPE_BOTH;
__root const CFG_CBOX_ITEM cfgcbox0_0[]={"Locked","UnLocked","Both"};
//---------------------------------------------------------------
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Пути",1,0};

//__root const CFG_HDR cfghdrm11_0={CFG_STR_UTF8,"Путь к img(просто так)",0,255};
//__root const char PATH_IMG[256]="4:\\ZBin\\PlayersControl\\img";

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Путь к Ivoplay",0,255};
__root const char PATH_IVO[256]="4:\\ZBin\\Ivoplay\\Ivoplay.elf";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Путь к MusicaPlayer",0,255};
__root const char PATH_MAPLAYER[256]="4:\\ZBin\\MusicaPlayer\\MusicaPlayer.elf";

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Путь к SPlayer",0,255};
__root const char PATH_SPLAYER[256]="4:\\ZBin\\SPlayer\\SPlayer.elf";

__root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"Обрабатывать стандартный плеер?",0,0};
__root const  int player0=1;

__root const CFG_HDR cfghdr1_2={CFG_CHECKBOX,"Обрабатывать Ivoplay?",0,0};
__root const  int player1=0;

__root const CFG_HDR cfghdr1_3={CFG_CHECKBOX,"Обрабатывать MusicAPlayer?",0,0};
__root const  int player2=0;

__root const CFG_HDR cfghdr1_4={CFG_CHECKBOX,"Обрабатывать SPlayer?",0,0};
__root const  int player3=0;


__root const CFG_HDR cfghdr1_5={CFG_CHECKBOX,"Свернуть и блок. при запуске?",0,0};
__root const  int ena_lock=0;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
//---------------------------------------------------------------
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Настройки хука",1,0};

__root const CFG_HDR cfghdr_m21_11={CFG_LEVEL,"Запуск стандартного плеера",1,0};

__root const CFG_HDR cfghdr_m21_1_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int StartKey1_1=VOL_UP_BUTTON;

__root const CFG_HDR cfghdr_m21_1_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey1_1Type=KEY_DOUBLE_CLICK;
__root const CFG_CBOX_ITEM cfgcbox_m21_1_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_1_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int StartKey1_2=0;

__root const CFG_HDR cfghdr_m21_1_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey1_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_1_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_10={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------

__root const CFG_HDR cfghdr_m21_21={CFG_LEVEL,"Запуск плеера Ivoplay",1,0};

__root const CFG_HDR cfghdr_m21_2_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int StartKey2_1=0;

__root const CFG_HDR cfghdr_m21_2_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey2_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_2_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_2_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int StartKey2_2=0;

__root const CFG_HDR cfghdr_m21_2_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey2_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_2_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_20={CFG_LEVEL,"",0,0};


//---------------------------------------------------------------


__root const CFG_HDR cfghdr_m21_31={CFG_LEVEL,"Запуск плеера MusicAPlayer",1,0};

__root const CFG_HDR cfghdr_m21_3_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int StartKey3_1=0;

__root const CFG_HDR cfghdr_m21_3_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey3_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_3_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_3_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int StartKey3_2=0;

__root const CFG_HDR cfghdr_m21_3_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey3_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_3_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_30={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------


__root const CFG_HDR cfghdr_m21_131={CFG_LEVEL,"Запуск плеера SPlayer",1,0};

__root const CFG_HDR cfghdr_m21_13_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int StartKey4_1=0;

__root const CFG_HDR cfghdr_m21_13_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey4_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_13_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_13_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int StartKey4_2=0;

__root const CFG_HDR cfghdr_m21_13_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StartKey4_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_13_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_130={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------


__root const CFG_HDR cfghdr_m21_41={CFG_LEVEL,"Закрытие плеера",1,0};

__root const CFG_HDR cfghdr_m21_4_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int CloseKey_1=0;

__root const CFG_HDR cfghdr_m21_4_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int CloseKey_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_4_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_4_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int CloseKey_2=0;

__root const CFG_HDR cfghdr_m21_4_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int CloseKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_4_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_40={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------

__root const CFG_HDR cfghdr_m21_51={CFG_LEVEL,"Плей/Пауза",1,0};

__root const CFG_HDR cfghdr_m21_5_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int PlayPauseKey_1=VOL_UP_BUTTON;

__root const CFG_HDR cfghdr_m21_5_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int PlayPauseKey_1Type=1;
__root const CFG_CBOX_ITEM cfgcbox_m21_5_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_5_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int PlayPauseKey_2=0;

__root const CFG_HDR cfghdr_m21_5_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int PlayPauseKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_5_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_50={CFG_LEVEL,"",0,0};


//---------------------------------------------------------------




__root const CFG_HDR cfghdr_m21_61={CFG_LEVEL,"Стоп",1,0};

__root const CFG_HDR cfghdr_m21_6_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int StopKey_1=0;

__root const CFG_HDR cfghdr_m21_6_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StopKey_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_6_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_6_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int StopKey_2=0;

__root const CFG_HDR cfghdr_m21_6_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int StopKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_6_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_60={CFG_LEVEL,"",0,0};


//---------------------------------------------------------------


__root const CFG_HDR cfghdr_m21_71={CFG_LEVEL,"Следующий трек",1,0};

__root const CFG_HDR cfghdr_m21_7_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int NextKey_1=VOL_UP_BUTTON;

__root const CFG_HDR cfghdr_m21_7_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int NextKey_1Type=2;
__root const CFG_CBOX_ITEM cfgcbox_m21_7_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_7_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int NextKey_2=0;

__root const CFG_HDR cfghdr_m21_7_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int NextKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_7_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_70={CFG_LEVEL,"",0,0};



//---------------------------------------------------------------



__root const CFG_HDR cfghdr_m21_81={CFG_LEVEL,"Предыдущий трек",1,0};

__root const CFG_HDR cfghdr_m21_8_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int PrevKey_1=VOL_DOWN_BUTTON;

__root const CFG_HDR cfghdr_m21_8_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int PrevKey_1Type=2;
__root const CFG_CBOX_ITEM cfgcbox_m21_8_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_8_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int PrevKey_2=0;

__root const CFG_HDR cfghdr_m21_8_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int PrevKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_8_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_80={CFG_LEVEL,"",0,0};


//---------------------------------------------------------------

__root const CFG_HDR cfghdr_m21_91={CFG_LEVEL,"Громкость +",1,0};

__root const CFG_HDR cfghdr_m21_9_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int VolUPKey_1=VOL_UP_BUTTON;

__root const CFG_HDR cfghdr_m21_9_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int VolUPKey_1Type=4;
__root const CFG_CBOX_ITEM cfgcbox_m21_9_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_9_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int VolUPKey_2=0;

__root const CFG_HDR cfghdr_m21_9_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int VolUPKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_9_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_90={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------

__root const CFG_HDR cfghdr_m21_101={CFG_LEVEL,"Громкость -",1,0};

__root const CFG_HDR cfghdr_m21_10_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int VolDOWNKey_1=VOL_DOWN_BUTTON;

__root const CFG_HDR cfghdr_m21_10_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int VolDOWNKey_1Type=4;
__root const CFG_CBOX_ITEM cfgcbox_m21_10_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_10_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int VolDOWNKey_2=0;

__root const CFG_HDR cfghdr_m21_10_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int VolDOWNKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_10_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_100={CFG_LEVEL,"",0,0};


//---------------------------------------------------------------


__root const CFG_HDR cfghdr_m21_111={CFG_LEVEL,"Громкость on/off",1,0};

__root const CFG_HDR cfghdr_m21_11_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int MuteKey_1=0;

__root const CFG_HDR cfghdr_m21_11_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int MuteKey_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_11_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_11_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int MuteKey_2=0;

__root const CFG_HDR cfghdr_m21_11_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int MuteKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_11_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_110={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------
__root const CFG_HDR cfghdr_m21_121={CFG_LEVEL,"Свернуть плеер и залочить клаву",1,0};

__root const CFG_HDR cfghdr_m21_12_0={CFG_KEYCODE,"Кейхук 1",0,100};
__root const unsigned int LockKey_1=0;

__root const CFG_HDR cfghdr_m21_12_0_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int LockKey_1Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_12_0_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_12_1={CFG_KEYCODE,"Кейхук 2",0,100};
__root const unsigned int LockKey_2=0;

__root const CFG_HDR cfghdr_m21_12_1_1={CFG_CBOX,"Метод",0,5};
__root const unsigned int LockKey_2Type=KEY_NOT_USE;
__root const CFG_CBOX_ITEM cfgcbox_m21_12_1_1[]={"Одинарное","Двойное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m21_120={CFG_LEVEL,"",0,0};




//---------------------------------------------------------------



__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};






__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Гарнитура",1,0};

__root const CFG_HDR cfghdr14={CFG_CBOX,"Подключение гарнитуры",0,4};
__root const unsigned int HeadsetCType=2;
__root const CFG_CBOX_ITEM cfgcbox14[]={"Шорткат/адрес","Эльф","Действие","Не использовать"};

__root const CFG_HDR cfghdr14_1={CFG_STR_UTF8,"Шорткат/путь к эльфу/адрес",0,255};
__root const char SHORCUT1[256]="4:\\ZBin\\Ivoplay\\Ivoplay.elf";

__root const CFG_HDR cfghdr14_2={CFG_CBOX,"Действие",0,12};
__root const unsigned int HeadsetCD=0;
__root const CFG_CBOX_ITEM cfgcbox14_2[]={"Запуск стандартного","Запуск Ivoplay","Запуск MusicAPlayer","Запуск SPlayer","Закрытие","Плей/Пауза","Стоп","Следующий","Предыдущий","Громкость +","Громкость -","Звук on/off"};

__root const CFG_HDR cfghdr15={CFG_CBOX,"Отключение гарнитуры",0,4};
__root const unsigned int HeadsetDType=2;
__root const CFG_CBOX_ITEM cfgcbox15[]={"Шорткат/адрес","Эльф","Действие","Не использовать"};

__root const CFG_HDR cfghdr15_1={CFG_STR_UTF8,"Шорткат/путь к эльфу/адрес",0,255};
__root const char SHORCUT2[256]="4:\\ZBin\\Ivoplay\\Ivoplay.elf";

__root const CFG_HDR cfghdr15_2={CFG_CBOX,"Действие",0,12};
__root const unsigned int HeadsetDD=5;
__root const CFG_CBOX_ITEM cfgcbox15_1[]={"Запуск стандартного","Запуск Ivoplay","Запуск MusicAPlayer","Запуск SPlayer","Закрытие","Плей/Пауза","Стоп","Следующий","Предыдущий","Громкость +","Громкость -","Звук on/off"};



__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Таймер выключения",1,0};

__root const CFG_HDR cfghdr_m41_1={CFG_KEYCODE,"Кейхук запуска",0,100};
__root const unsigned int TimerOnKey=0;

__root const CFG_HDR cfghdr_m41_1_1={CFG_CBOX,"Метод",0,4};
__root const unsigned int TimerOnKeyType=3;
__root const CFG_CBOX_ITEM cfgcbox_m41_1_1[]={"Одинарное","Двойное","Длинное","Не использовать"};

__root const CFG_HDR cfghdr_m41_2={CFG_KEYCODE,"Кейхук остановки",0,100};
__root const unsigned int TimerOffKey=0;

__root const CFG_HDR cfghdr_m41_2_1={CFG_CBOX,"Метод",0,4};
__root const unsigned int TimerOffKeyType=3;
__root const CFG_CBOX_ITEM cfgcbox_m41_2_1[]={"Одинарное","Двойное","Длинное","Не использовать"};

__root const CFG_HDR cfghdr_m41_3={CFG_UINT,"Часов",0,255};
__root const int TimerHour=1;

__root const CFG_HDR cfghdr_m41_4={CFG_UINT,"Минут",0,59};
__root const int TimerMin=30;

__root const CFG_HDR cfghdr_m41_5={CFG_CBOX,"Вибрировать при запуске?",0,2};
__root const int TimerVibr=1;
__root const CFG_CBOX_ITEM cfgcbox_m41_5[]={"Нет","Да"};


__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
