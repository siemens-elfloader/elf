#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#ifdef ELKA
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif
#endif
/*__root const CFG_HDR cfghdr0={CFG_LEVEL,"",0,0};//Уровень,нужно чтобы не было каки если хочешь чтобы первым пунктом шел уровень,а не строка к примеру

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Общие настройки",1,0};//Делаем уровень
  
  __root const CFG_HDR cfghdr1={CFG_INT,"Размер шрифта",0,99};//Вводим цифры, 0-99 это прмежуток от 0 до 99 тока можно писать
  __root const int font=FONT_SMALL;

  __root const CFG_HDR cfghdr4={CFG_CBOX,"Подсветка",0,2};//Эт конфиг бокс, цифра 2 это количество пунктов в нем
  __root const int illum_mode=0;
  __root const CFG_CBOX_ITEM cfgcbox2[2]={"Нет","Да"};//cfgcbox2[2],тут тоже нужно ставить число 2,если будет 3 пункта,то соответсвенно 3 ставим

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};//Каждый уровень нужно закрывать

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Пути",1,0};//уровень

  __root const CFG_HDR cfghdr12={CFG_STR_UTF8,"Путь к истории",0,127};//НУ это строка,думаю понятно
  __root const char HIST_PATH[128]=DEFAULT_DISK ":\\ZBin\\TextReader\\history\\";

  __root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Путь к закладкам",0,127};
  __root const char BMK_PATH[128]=DEFAULT_DISK ":\\ZBin\\TextReader\\Bookmarks\\";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};//опять закрываем

__root const CFG_HDR cfghdr_2_2={CFG_CHECKBOX,"Enable eMenu",0,2};//это у нас чекбокс,короче ставим галочку))в меню натаси например есть такая штука:)
__root const int ENA_EMENU = 1;//1-включено,0 выключено

__root const CFG_HDR cfghdr68={CFG_COORDINATES,"Coordinates panel",0,0};//настраиваем координаты
__root const unsigned int x1=0;
__root const unsigned int y1=75;

__root const CFG_HDR cfghdr60={CFG_COLOR,"Panel border col",0,0};//выбираем цвет
__root const char cfgPanBorderCol[4]={255,255,255,100};


__root const CFG_HDR cfghdr14={CFG_TIME,"Время",0,0};//Выбираем время
__root const TTime tm={15,0};//структура для времени

__root const CFG_HDR cfghdr1_1={CFG_STR_PASS,"Password",0,8};//Пароль:)
__root const char PASS[9]="";//при ввводе показываются тока звездочки:) *************
*/

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Game path",0,63};
__root const char GAME_PATH[64]=DEFAULT_DISK ":\\ZBin\\Black Raven\\";
