#include "..\inc\cfg_items.h"
#include "language.h"
#include "swilib.h"
//Конфигурация

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

//#ifdef BCFG
__root const CFG_HDR cfghdr0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr1={CFG_LEVEL,"Оригинальные настройки",1,0};

//Popup chat
__root const CFG_HDR cfghdr2={CFG_CBOX,"Popup",0,2};
  __root const int DEVELOP_IF_MOD = 1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Use set orig.config", "After unlock"};
    
__root const CFG_HDR cfghdr4={CFG_CBOX,"Save history with name",0,2};
  __root const int HISTORY_SAVE_TYPE = 0;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"No","Yes"};

//Buffer for fill from history
__root const CFG_HDR cfghdr6={CFG_CBOX,"History read buffer",0,3};
    __root const int HISTORY_BUFFER_MOD = 1;
__root const CFG_CBOX_ITEM cfgcbox7[3]={"Use set orig.conf.","4 kbyte","8 kbyte"};    
    
__root const CFG_HDR cfghdr8={CFG_LEVEL,"",0,0};


//-----------------------------------------------------------------------------//
//                                   ИНТЕРФЕЙС                                 //
//-----------------------------------------------------------------------------//

__root const CFG_HDR cfghdr9={CFG_LEVEL,"Интерфейс",1,0};

__root const CFG_HDR cfghdr10= {CFG_UINT, "Кол-во сообщений в чате", 0, 75};  
  __root const unsigned int MAXLOGMSG = 30;    
  
  
__root const CFG_HDR cfghdr11={CFG_CHECKBOX,"Два столбца",0,2};
#ifdef ELKA
   __root const int VIEW_MODE = 1;
#else
   __root const int VIEW_MODE = 0;
#endif
          
__root const CFG_HDR cfghdr12={CFG_CHECKBOX,"Две линии",0,2};
  __root const int LINE_MODE = 0;
  
__root const CFG_HDR cfghdr13={CFG_CBOX,"Показывать",0,3};
  __root const unsigned int SOFT_MODE = 1;
__root const CFG_CBOX_ITEM cfgcbox14[3]={"Ничего","Софты","Инфу"};
  
__root const CFG_HDR cfghdr15={CFG_CHECKBOX,"Статусы в иконбаре",0,2};
  __root const unsigned int ShowStatusToIconBar = 1;
  
__root const CFG_HDR cfghdr16={CFG_CHECKBOX,"Пинг в иконбаре",0,2};
  __root const unsigned int PingToIconBar = 0;
  
__root const CFG_HDR cfghdr17={CFG_CHECKBOX,"Показывать отправку",0,2};
  //__root const unsigned int ShowProcessSend = 0;    

__root const CFG_HDR cfghdr18={CFG_CBOX,"Показывать отправку",0,4};
  __root const unsigned int ShowProcessSend = 0;
__root const CFG_CBOX_ITEM cfgcbox19[4]={"Ничего","Цифрами","Линией","Цифры+Цвет"};  
  
  //history
__root const CFG_HDR cfghdr20={CFG_CBOX,"Показывать активные чаты",0,2};
  __root const int SHOW_ACTIVE = 1;
__root const CFG_CBOX_ITEM cfgcbox21[2]={"No","Yes"};  
  
__root const CFG_HDR cfghdr22={CFG_CBOX,"Выделять активные чаты",0,2};
  __root const int SelBoldActiveChat = 1;
__root const CFG_CBOX_ITEM cfgcbox23[2]={"Обычным","Жирным"};  
    
__root const CFG_HDR cfghdr24={CFG_CHECKBOX,"Подсветка при подключении конт.",0,2};
  __root const unsigned int IllByONCantact = 1;
          
#ifdef ELKA  
__root const CFG_HDR cfghdr25={CFG_STR_UTF8,"Small images .png path",0,63};
  __root const char ICON_PATH2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\img2";
#endif

//------------------------------------------------------------------------------//
//                         SETTING CONTACTLIST HEADER                           //
//------------------------------------------------------------------------------//

__root const CFG_HDR cfghdr26={CFG_LEVEL,"Заголовок КЛ",1,0};

 
__root const CFG_HDR cfghdr27={CFG_UINT,"Время подкл./отключ.(сек)",0,1000};
    __root const unsigned int ON_OFF_TIME=10;  
  
  
__root const CFG_HDR cfghdr28={CFG_CHECKBOX,"Статус",0,2};
    __root const int HEAD_STATUS = 1;
  
__root const CFG_HDR cfghdr29={CFG_CHECKBOX,"Х-Статус",0,2};
    __root const int HEAD_XSTATUS = 1;
  
__root const CFG_HDR cfghdr30={CFG_CHECKBOX,"Приват.статус",0,2};
    __root const int HEAD_PRIVATE = 1;
  
__root const CFG_HDR cfghdr31={CFG_CBOX,"Пинг",0,3};
    __root const int HEAD_PING = 1;
__root const CFG_CBOX_ITEM cfgcbox32[3]={"Картинка","Текст","Ничего"};
    
__root const CFG_HDR cfghdr33={CFG_CHECKBOX,"Отображать траффик",0,2};
    __root const int ShowTraff = 1;
__root const CFG_CBOX_ITEM cfgcbox34[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr35={CFG_CHECKBOX,"Отображать кол-во контактов",0,2};
    __root const int isShowCont = 1;
__root const CFG_CBOX_ITEM cfgcbox36[2]={"No","Yes"};
  
__root const CFG_HDR cfghdr37={CFG_CHECKBOX,"Отображать кол-во непрочит.",0,2};
    __root const int isShowUnread = 1;
__root const CFG_CBOX_ITEM cfgcbox38[2]={"No","Yes"};
  
__root const CFG_HDR cfghdr39={CFG_CHECKBOX,"Отображать вибру [V] ",0,2};
    __root const int isShowV = 1;
__root const CFG_CBOX_ITEM cfgcbox40[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr41={CFG_CHECKBOX,"Отображать звук [S]",0,2};
    __root const int isShowS = 1;
__root const CFG_CBOX_ITEM cfgcbox42[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr43={CFG_CHECKBOX,"Отображать автостатус [A]",0,2};
    __root const int isShowA = 1;
__root const CFG_CBOX_ITEM cfgcbox44[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr45={CFG_CHECKBOX,"Отображать напоминалку [Vr]",0,2};
    __root const int isShowR = 1;
__root const CFG_CBOX_ITEM cfgcbox46[2]={"No","Yes"};
    
    
__root const CFG_HDR cfghdr47={CFG_CHECKBOX,"Отображать заряд батареи",0,2};
    __root const int isShowBat = 0;
__root const CFG_CBOX_ITEM cfgcbox48[2]={"No","Yes"};    
  
__root const CFG_HDR cfghdr49={CFG_LEVEL,"",0,0};

    
    
__root const CFG_HDR cfghdr50={CFG_LEVEL,"Контакт лист",1,0};   

__root const CFG_HDR cfghdr51={CFG_COLOR,"Цвет фона КЛ",0,0};
     __root const char CLBackgrClr[4]={0x00,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr52={CFG_COLOR,"Цвет софтов",0,0};
     __root const char SoftBackgrClr[4]={0xFF,0x48,0x00,0x1B};   
     
__root const CFG_HDR cfghdr53={CFG_COLOR,"Цвет надписей софтов",0,0};
     __root const char SoftFontClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr54={CFG_COLOR,"Цвет заголовка",0,0};
     __root const char HeadBackgrClr[4]={0xFF,0x48,0x00,0x1B};   
     
__root const CFG_HDR cfghdr55={CFG_COLOR,"Цвет надписей заголовка",0,0};
     __root const char HeadFontClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr56={CFG_COLOR,"Цвет скроллбара",0,0};
     __root const char ScrollBarClr[4]={0xFF,0x00,0x00,0x15};
     
__root const CFG_HDR cfghdr57={CFG_COLOR,"Цвет курсора",0,0};
     __root const char ClCursorClr[4]={0xFF,0x00,0x00,0x32};
     
__root const CFG_HDR cfghdr58={CFG_COLOR,"Цвет рамки курсора",0,0};
     __root const char ClCursorBordClr[4]={0x00,0x00,0x00,0x60};
     
__root const CFG_HDR cfghdr59={CFG_COLOR,"Цвет активных",0,0};
     __root const char ActiveClr[4]={0xFF,0xFF,0x00,0x64};
     
__root const CFG_HDR cfghdr60={CFG_COLOR,"Цвет неактивных",0,0};
     __root const char NotActiveClr[4]={0x00,0xFF,0x00,0x64};
     
__root const CFG_HDR cfghdr61={CFG_COLOR,"Цвет групп",0,0};
     __root const char GroupClr[4]={0xFF,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr62={CFG_COLOR,"Цвет подписей",0,0};
     __root const char CLDescricpClr[4]={0xFF,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr63={CFG_COLOR,"Фон доп.инфо",0,0};
     __root const char AddInfoClr[4]={0xFF,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr64={CFG_COLOR,"Шрифт доп.инфо",0,0};
     __root const char FontInfoClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr65={CFG_COLOR,"Цвет не доставленных",0,0};
     __root const char UnAckedClr[4]={0xFF,0xFF,0x0,0x15};
     
__root const CFG_HDR cfghdr66={CFG_COLOR,"Цвет отправленных",0,0};
     __root const char SendClr[4]={0x00,0xFF,0x00,0x15};
  /*      
__root const CFG_HDR cfghdr67={CFG_COLOR,"Цвет фона КЛ",0,0};
     __root const char CLBackgrClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr68={CFG_COLOR,"Цвет софтов",0,0};
     __root const char SoftBackgrClr[4]={0xFF,0x00,0x00,0x15};   
     
__root const CFG_HDR cfghdr69={CFG_COLOR,"Цвет надписей софтов",0,0};
     __root const char SoftFontClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr70={CFG_COLOR,"Цвет заголовка",0,0};
     __root const char HeadBackgrClr[4]={0xFF,0x00,0x00,0x15};   
     
__root const CFG_HDR cfghdr71={CFG_COLOR,"Цвет надписей заголовка",0,0};
     __root const char HeadFontClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr72={CFG_COLOR,"Цвет скроллбара",0,0};
     __root const char ScrollBarClr[4]={0xFF,0x00,0x00,0x15};
     
__root const CFG_HDR cfghdr73={CFG_COLOR,"Цвет курсора",0,0};
     __root const char ClCursorClr[4]={0xFF,0x00,0x00,0x20};
     
__root const CFG_HDR cfghdr74={CFG_COLOR,"Цвет рамки курсора",0,0};
     __root const char ClCursorBordClr[4]={0x00,0x00,0x00,0x60};
     
__root const CFG_HDR cfghdr75={CFG_COLOR,"Цвет активных",0,0};
     __root const char ActiveClr[4]={0xFF,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr76={CFG_COLOR,"Цвет неактивных",0,0};
     __root const char NotActiveClr[4]={0x00,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr77={CFG_COLOR,"Фон доп.инфо",0,0};
     __root const char AddInfoClr[4]={0xFF,0x00,0x00,0x64};
     
__root const CFG_HDR cfghdr78={CFG_COLOR,"Шрифт доп.инфо",0,0};
     __root const char FontInfoClr[4]={0xFF,0xFF,0xFF,0x64};
     
__root const CFG_HDR cfghdr79={CFG_COLOR,"Цвет не доставленных",0,0};
     __root const char UnAckedClr[4]={0x00,0x00,0x0,0x15};
     
__root const CFG_HDR cfghdr80={CFG_COLOR,"Цвет отправленных",0,0};
     __root const char SendClr[4]={0x00,0xFF,0x00,0x15};
*/
     
     
__root const CFG_HDR cfghdr81={CFG_LEVEL,"",0,0};
  
__root const CFG_HDR cfghdr82={CFG_LEVEL,"Главное меню",1,0};
  
__root const CFG_HDR cfghdr83={CFG_COLOR,"Цвет фона",0,0};
      __root const char MMBackgrClr[4]={0x00,0x00,0x00,0x45};//"\x00\x00\x00\x45"
      
__root const CFG_HDR cfghdr84={CFG_COLOR,"Цвет обводки",0,0};
      __root const char MMBackgrBordClr[4]={0xFF,0xFF,0xFF,0x64};
           
__root const CFG_HDR cfghdr85={CFG_COLOR,"Цвет курсора",0,0};
      __root const char MMCursorBGClr[4]={0x00,0x00,0x00,0x00};
      
__root const CFG_HDR cfghdr86={CFG_COLOR,"Цвет обводки курсора",0,0};
      __root const char MMCursorClr[4]={0xFF,0xFF,0xFF,0x64}; 
      

__root const CFG_HDR cfghdr87= {CFG_RECT, "Меню", 0, 0};
#ifdef ELKA
      __root const RECT MMRect = {0,60,179,303};
#else
      __root const RECT MMRect = {0,26,125,164};
#endif
      
__root const CFG_HDR cfghdr88= {CFG_RECT, "Статусы", 0, 0};
      __root const RECT SRect = {30,YDISP+2,190,260};
      
__root const CFG_HDR cfghdr89= {CFG_RECT, "Х-Статусы", 0, 0};
      __root const RECT XSRect = {30,YDISP+2,231,300};   
      
__root const CFG_HDR cfghdr90={CFG_CHECKBOX,"Показывать цифры",0,2};
       __root const unsigned int ShowNumbMenu = 1;    
   
__root const CFG_HDR cfghdr91={CFG_LEVEL,"",0,0};//
          
  //--------------------
  
  
__root const CFG_HDR cfghdr92={CFG_LEVEL,"Пнг шрифт",1,0};//level       
          
__root const CFG_HDR cfghdr93= {CFG_STR_UTF8, "Путь к 1 png шрифту", 0, 127};
          __root const char fontpath2[128] = "";
          
__root const CFG_HDR cfghdr94= {CFG_STR_UTF8, "Путь к 2 png шрифту", 0, 127};
          __root const char fontpath3[128] = "";        
          
__root const CFG_HDR cfghdr95= {CFG_STR_UTF8, "png шрифт заголовка", 0, 127};
          __root const char fontpath4[128] = "";
          
__root const CFG_HDR cfghdr96={CFG_CHECKBOX,"Пнг шрифт заголовка",0,2};
          __root const int PNG_HEADER = 1;
        
__root const CFG_HDR cfghdr97={CFG_CHECKBOX,"Пнг шрифт софтов",0,2};
          __root const int PNG_SOFTKEY = 1;
    
__root const CFG_HDR cfghdr98={CFG_LEVEL,"",0,0};// 
     
     
__root const CFG_HDR cfghdr99={CFG_LEVEL,"Системный шрифт",1,0};//level     
     
__root const CFG_HDR cfghdr100={CFG_CHECKBOX,"Использовать сист. шрифт",0,2};
          __root const int isSystemFont = 1;
          
__root const CFG_HDR cfghdr101= {CFG_UINT, "Шрифт", 0, 15};  
          __root const unsigned int pngFont = FONT_SMALL;
          
__root const CFG_HDR cfghdr102= {CFG_UINT, "Шрифт заголовка", 0, 15};  
          __root const unsigned int HeadFont = FONT_SMALL;
    
__root const CFG_HDR cfghdr103={CFG_LEVEL,"",0,0};//      


    //********* НАСТРОЙКА КЛАВИШ ************//

    //View settings
__root const CFG_HDR cfghdr104={CFG_LEVEL,"Клавиши",1,0};    
    
      //Action on # button in contact list
__root const CFG_HDR cfghdr105={CFG_CBOX,"Действие на # в КЛ",0,2};
        __root const int ActionResh = 0;
__root const CFG_CBOX_ITEM cfgcbox106[2]={"Очистить выделенный чат","След.акт.чат"};
        
    
    //Press vol up or vol down button in CL
__root const CFG_HDR cfghdr107={CFG_CBOX,"Вкл. действие на громк.вниз",0,2};
      __root const int isVolDownButton = 1;
__root const CFG_CBOX_ITEM cfgcbox108[2]={"Нет","Да"};
      
__root const CFG_HDR cfghdr109={CFG_CBOX,"Вкл.действие на громк.вверх",0,2};
      __root const int isVolUpButton = 1;
__root const CFG_CBOX_ITEM cfgcbox110[2]={"Нет","Да"};
      
    
    //{"Без действия","Звук","Вибра","Инвиз","Реж.напоминания","Очистить чаты","Автоответчик","Показ.хстат/время","Конфиг","Конфиг мода","Пинг","Заблокировать","На гэ","Меню юзера"}
__root const CFG_HDR cfghdr111={CFG_LEVEL,"Длинное нажатие",1,0};
        //Long press right in chat
__root const CFG_HDR cfghdr112={CFG_CBOX,"Длинное нажатие вправо в чате",0,3};
          __root const int LongRightAction = 0;
__root const CFG_CBOX_ITEM cfgcbox113[3]={"Ничего","Следующий чат","Вставить смайл"};    
        
        //Long press right in chat
__root const CFG_HDR cfghdr114={CFG_CBOX,"Длинное нажатие влево в чате",0,2};
          __root const int LongLeftAction = 0;
__root const CFG_CBOX_ITEM cfgcbox115[2]={"Ничего","Предыдущий чат"};
          
        
        //Long press vol up button in chat
__root const CFG_HDR cfghdr116={CFG_CBOX,"Длинное нажатие + в чате",0,2};
          __root const int LongVolUpAction = 1;
__root const CFG_CBOX_ITEM cfgcbox117[2]={"Обычно","Вставка посл.сообщения"};
        
        //Long press vol down button in chat
__root const CFG_HDR cfghdr118={CFG_CBOX,"Длинное нажатие - в чате",0,2};
          __root const int LongVolDownAction = 1;
__root const CFG_CBOX_ITEM cfgcbox119[2]={"Обычно","Очистить текст"};
    
    
    
    
__root const CFG_HDR cfghdr120={CFG_CBOX,"Длинная 0 в КЛ",0,14};
          __root const int longAct_0 = 10;
__root const CFG_CBOX_ITEM cfgcbox121[14]={LG_NOT_ACTION,//0
                                                        LG_SOUND,//1
                                                        LG_VIBRA,//2
                                                        LG_INVIS,//3
                                                        LG_VIBRA_REM,//4
                                                        LG_CLAER_ALL_CHAT,//5
                                                        LG_AUTOMSG,//6
                                                        LG_SHOW_XSTATE_TIME,//7
                                                        LG_CONFIG,//8
                                                        LG_CONFIG_MOD,//9
                                                        LG_PING,//10
                                                        LG_HIHE_LOCK,//11
                                                        LG_IDLE,//12
                                                        LG_USERMENU//13
                                                      };
    
__root const CFG_HDR cfghdr122={CFG_CBOX,"Длинная 1 в КЛ",0,14};
          __root const int longAct_1 = 1;
__root const CFG_CBOX_ITEM cfgcbox123[14]={LG_NOT_ACTION,
                                                      LG_SOUND,
                                                      LG_VIBRA,
                                                      LG_INVIS,
                                                      LG_VIBRA_REM,
                                                      LG_CLAER_ALL_CHAT,
                                                      LG_AUTOMSG,
                                                      LG_SHOW_XSTATE_TIME,
                                                      LG_CONFIG,
                                                      LG_CONFIG_MOD,
                                                      LG_PING,
                                                      LG_HIHE_LOCK,
                                                      LG_IDLE,
                                                      LG_USERMENU
                                                    };
    
__root const CFG_HDR cfghdr124={CFG_CBOX,"Длинная 2 в КЛ",0,14};
          __root const int longAct_2 = 2;
__root const CFG_CBOX_ITEM cfgcbox125[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr126={CFG_CBOX,"Длинная 3 в КЛ",0,14};
          __root const int longAct_3 = 3;
__root const CFG_CBOX_ITEM cfgcbox127[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr128={CFG_CBOX,"Длинная 4 в КЛ",0,14};
          __root const int longAct_4 = 4;
__root const CFG_CBOX_ITEM cfgcbox129[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr130={CFG_CBOX,"Длинная 5 в КЛ",0,14};
          __root const int longAct_5 = 5;
__root const CFG_CBOX_ITEM cfgcbox131[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr132={CFG_CBOX,"Длинная 6 в КЛ",0,14};
          __root const int longAct_6 = 6;
__root const CFG_CBOX_ITEM cfgcbox133[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr134={CFG_CBOX,"Длинная 7 в КЛ",0,14};
          __root const int longAct_7 = 7;
__root const CFG_CBOX_ITEM cfgcbox135[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr136={CFG_CBOX,"Длинная 8 в КЛ",0,14};
          __root const int longAct_8 = 8;
__root const CFG_CBOX_ITEM cfgcbox137[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr138={CFG_CBOX,"Длинная 9 в КЛ",0,14};
          __root const int longAct_9 = 9;
__root const CFG_CBOX_ITEM cfgcbox139[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr140={CFG_CBOX,"Длинная # в КЛ",0,14};
          __root const int longAct_10 = 11;
__root const CFG_CBOX_ITEM cfgcbox141[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr142={CFG_CBOX,"Длинная * в КЛ",0,14};
          __root const int longAct_11 = 12;
__root const CFG_CBOX_ITEM cfgcbox143[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
          
__root const CFG_HDR cfghdr144={CFG_CBOX,"Длинная вправо в КЛ",0,14};
          __root const int longAct_RB = 13;
__root const CFG_CBOX_ITEM cfgcbox145[14]={LG_NOT_ACTION,
                                                        LG_SOUND,
                                                        LG_VIBRA,
                                                        LG_INVIS,
                                                        LG_VIBRA_REM,
                                                        LG_CLAER_ALL_CHAT,
                                                        LG_AUTOMSG,
                                                        LG_SHOW_XSTATE_TIME,
                                                        LG_CONFIG,
                                                        LG_CONFIG_MOD,
                                                        LG_PING,
                                                        LG_HIHE_LOCK,
                                                        LG_IDLE,
                                                        LG_USERMENU
                                                      };
    
__root const CFG_HDR cfghdr146={CFG_LEVEL,"",0,0}; //LONG PRESS ACTION
          
__root const CFG_HDR cfghdr147={CFG_LEVEL,"",0,0}; //НАСТРОКА КЛАВИШ

__root const CFG_HDR cfghdr148={CFG_LEVEL,"",0,0};//Интерфейс


//-----------------------------------------------------------------------------//
//---------------------------------- ДОП ЗВУКИ --------------------------------//
//-----------------------------------------------------------------------------//

	
__root const CFG_HDR cfghdr149={CFG_LEVEL,"Доп.звуки",1,0};

__root const CFG_HDR cfghdr150={CFG_CBOX,"Extended sounds",0,2};
    __root const unsigned int extended_sounds = 0;
__root const CFG_CBOX_ITEM cfgcbox151[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr152={CFG_CBOX,"Add sound type file",0,3};
    __root const unsigned int ext_type_sounds = 0;
__root const CFG_CBOX_ITEM cfgcbox153[3]={"Mp3","Wav","Amr"};
    
__root const CFG_HDR cfghdr154={CFG_STR_UTF8,"add online msg path",0,63};
    __root const char sndGlobal2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\Uins_on\\";
  
__root const CFG_HDR cfghdr155={CFG_STR_UTF8,"add new msg path",0,63};
    __root const char sndMsg2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\Uins_msg\\";
    
__root const CFG_HDR cfghdr156={CFG_STR_UTF8,"Пинг",0,63};
    __root const char pingsnd[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndPing.amr";    
    
__root const CFG_HDR cfghdr157={CFG_STR_UTF8,"Обрыв связи",0,63};
    __root const char sndLostConn[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\SndLostConn2.amr";  

__root const CFG_HDR cfghdr158={CFG_LEVEL,"",0,0};


//-----------------------------------------------------------------------------//
//------------------------------- STATUS SETTING ------------------------------//
//-----------------------------------------------------------------------------//
  
__root const CFG_HDR cfghdr159={CFG_LEVEL,"Статусы",1,0};

//Status icon on mainscreen position
#ifdef NEWSGOLD
  #ifdef kluchnik
__root const CFG_HDR cfghdr160= {CFG_CBOX,"Показывать иконку статуса",0,5};
      __root const int ShowStatusIcon = 1;
__root const CFG_CBOX_ITEM cfgcbox161[5]={"На главном экране","В иконбаре","В иконбаре(кроме гэ)","Везде","Нигде"};
  #else
__root const CFG_HDR cfghdr162= {CFG_CBOX,"Показывать иконку статуса",0,5};
      __root const int ShowStatusIcon = 0;
__root const CFG_CBOX_ITEM cfgcbox163[5]={"На главном экране","В иконбаре","В иконбаре(кроме гэ)","Везде","Нигде"};
  #endif
#endif
        
//Show x-status on iconbar or mainscreen
#ifdef kluchnik
__root const CFG_HDR cfghdr164= {CFG_CBOX,"Показ.хстатус иконку",0,4};
    __root const int show_xstatus = 3;
__root const CFG_CBOX_ITEM cfgcbox165[4]={"Нигде","На гэ","В иконбаре","Везде"};
#else
  #ifdef NEWSGOLD
__root const CFG_HDR cfghdr166= {CFG_CBOX,"Показ.хстатус иконку",0,4};
      __root const int show_xstatus = 1;
__root const CFG_CBOX_ITEM cfgcbox167[4]={"Нигде","На гэ","В иконбаре","Везде"};
  #else
__root const CFG_HDR cfghdr168= {CFG_CBOX,"Показ.хстатус иконку",0,2};
      __root const int show_xstatus = 1;
__root const CFG_CBOX_ITEM cfgcbox169[2]={"Нигде","На гэ"};
  #endif
#endif    
__root const CFG_HDR cfghdr170={CFG_COORDINATES,"Позиция хстатус на гэ",0,0};
    __root const unsigned int IDLEICON_XX=2;
    __root const unsigned int IDLEICON_YX=70;
    
__root const CFG_HDR cfghdr171={CFG_CBOX,"Индив.настройки хстатуса",0,2};
    __root const int ind_set_xstatus = 0;
__root const CFG_CBOX_ITEM cfgcbox172[2]={"No","Yes"};
    
#ifdef NEWSGOLD
__root const CFG_HDR cfghdr173={CFG_CBOX,"Мигать при сообщении",0,2};
    __root const int blink_mess = 0;
__root const CFG_CBOX_ITEM cfgcbox174[2]={"No","Yes"};
    
//Number first pic status in folder img for show in iconbar
__root const CFG_HDR cfghdr175={CFG_UINT,"1я картика статуса в иконбаре",0,65535};
    __root const unsigned int NumStatusToIconBar = 8000;  

//Number first pic x-status in folder img for show in iconbar    
__root const CFG_HDR cfghdr176={CFG_UINT,"1я картика хстатуса в иконбаре",0,65535};
    __root const unsigned int NumXStatusToIconBar = 8100;  

__root const CFG_HDR cfghdr177={CFG_LEVEL,"Доп. статус в иконбар",1,0};
 
__root const CFG_HDR cfghdr178={CFG_UINT,"UIN",0,0xFFFFFFFF};
       __root const unsigned int ADDITION_UIN=0;
    
__root const CFG_HDR cfghdr179={CFG_CHECKBOX,"Показывать при активном",0,2};
       __root const int ShowAddStatusToIconBar = 0;
       
__root const CFG_HDR cfghdr180={CFG_CHECKBOX,"Показывать статус",0,2};
       __root const int show_add_state = 0;
__root const CFG_CBOX_ITEM cfgcbox181[2]={"No","Yes"};       

__root const CFG_HDR cfghdr182={CFG_CHECKBOX,"Показывать хстатус",0,2};
       __root const int show_add_xstate = 0;
__root const CFG_CBOX_ITEM cfgcbox183[2]={"No","Yes"};       

__root const CFG_HDR cfghdr184={CFG_LEVEL,"",0,0};//ADDITION STATUS TO ICONBAR
#endif
   
__root const CFG_HDR cfghdr185={CFG_LEVEL,"",0,0};//STATUS SETTINGS
  
  
//-----------------------------------------------------------------------------//
//-------------------------------- PNGFONT SETTING ----------------------------//
//-----------------------------------------------------------------------------//
  
  
__root const CFG_HDR cfghdr186={CFG_LEVEL,"Пнг шрифт",1,0};
   
//Nember png-font or system
__root const CFG_HDR cfghdr187={CFG_UINT,"Номер шрифта (1=png/1xx=system)",0,115};
   __root const unsigned int fonto=1;
    
//Path to png-font
#ifdef kluchnik
__root const CFG_HDR cfghdr188={CFG_STR_UTF8,"Путь к шрифту",0,63};
   __root const char fontpath[64]="4:\\elf\\naticq\\font\\";
#else
__root const CFG_HDR cfghdr189={CFG_STR_UTF8,"Путь к шрифту",0,63};
   __root const char fontpath[64]="";
#endif
__root const CFG_HDR cfghdr190={CFG_UINT,"Расстояние между буквами",0,999999};
   __root const unsigned int spaco1=1;
      
__root const CFG_HDR cfghdr191={CFG_UINT,"Main msg space",0,999999};
   //__root const unsigned int spaco2=0;
    
__root const CFG_HDR cfghdr192={CFG_LEVEL,"",0,0};//PNGFONT SETTING
  

//-----------------------------------------------------------------------------//
//                             SMILES COLOR SETTING                            //
//-----------------------------------------------------------------------------//


__root const CFG_HDR cfghdr193={CFG_LEVEL,"Cмайлы",1,0};


__root const CFG_HDR cfghdr194={CFG_CBOX,"Стандартные клавиши",0,2};
  __root const int UseStandartSmileSel = 0;
__root const CFG_CBOX_ITEM cfgcbox195[2]={"No","Yes"};  
       
__root const CFG_HDR cfghdr196={CFG_COLOR,"Цвет фона",0,0};
  __root const char SmBGcolor[4]={0xFF,0xFF,0xFF,100};
  
__root const CFG_HDR cfghdr197={CFG_COLOR,"Цвет курсора",0,0};
  __root const char SmSelectColor[4]={0xFF,0x00,0x00,0x2A};
  
__root const CFG_HDR cfghdr198={CFG_COLOR,"Цвет текста смайлов",0,0};
  __root const char SmFontColor[4]={0x00,0x00,0x00,100};

__root const CFG_HDR cfghdr199={CFG_LEVEL,"",0,0};

//-----------------------------------------------------------------------------//
//                                 IDLE SETTING
//-----------------------------------------------------------------------------//


__root const CFG_HDR cfghdr200={CFG_LEVEL,"Главный экран",1,0};

__root const CFG_HDR cfghdr201= {CFG_CBOX,"Показывать время",0,2};
    __root const int Is_UPTIME_On = 0;
__root const CFG_CBOX_ITEM cfgcbox202[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr203= {CFG_COORDINATES,"Позиция времени",0,0};
    __root const unsigned int onlineTime_x = 77;
    __root const unsigned int onlineTime_y = 98;

__root const CFG_HDR cfghdr204= {CFG_CBOX,"Пауза при дисконнекте",0,2};
    __root const int Pause_Time = 1;
__root const CFG_CBOX_ITEM cfgcbox205[2]={"No","Yes"};

    
__root const CFG_HDR cfghdr206= {CFG_CBOX,"Показывать пинг",0,2};
    __root const int isPingIdle = 0;
__root const CFG_CBOX_ITEM cfgcbox207[2]={"No","Yes"};
    
    __root const CFG_HDR cfghd66 = {CFG_COORDINATES,"Координаты автопинга",0,0};
    __root const unsigned int Ping_X = 2;
    __root const unsigned int Ping_Y = 262;
    
__root const CFG_HDR cfghdr208={CFG_UINT,"Звук пинга после(сек)",0,50};
    __root const unsigned int ping_time_config = 29;
    
__root const CFG_HDR cfghdr209= {CFG_CBOX,"Показывать непрочитанные",0,2};
    __root const int Is_Unread_On = 0;
__root const CFG_CBOX_ITEM cfgcbox210[2]={"No","Yes"};
    
    __root const CFG_HDR cfghd67 = {CFG_COORDINATES,"Координаты непрочитанных",0,0};
    __root const unsigned int unread_X = 99;
    __root const unsigned int unread_Y = 65;
    
__root const CFG_HDR cfghdr211= {CFG_CBOX,"Показывать подключ.",0,2};
    __root const int Is_Online_On = 1;
__root const CFG_CBOX_ITEM cfgcbox212[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr213= {CFG_CBOX,"Выравнивание подключ.",0,3};
    __root const int Is_Online_On_Align = 1;
__root const CFG_CBOX_ITEM cfgcbox214[3]={"Влево","Центр","Вправо"};
    
    __root const CFG_HDR cfghd71_1 = {CFG_COORDINATES,"Подключ.контакты",0,0};
    __root const unsigned int online_x = 120;
    __root const unsigned int online_y = 240;    
    
    
    
__root const CFG_HDR cfghdr215= {CFG_CBOX,"Показывать сообщения",0,2};
    __root const int Is_SMARTCPU_On = 0;
__root const CFG_CBOX_ITEM cfgcbox216[2]={"No","Yes"};
    
    //Coordinates for message on idle
   __root const CFG_HDR cfghd83 = {CFG_COORDINATES,"Позиция сообщений",0,0};
   __root const unsigned int msg_d_x = 0;
   __root const unsigned int msg_d_y = 65;   
   
__root const CFG_HDR cfghdr217={CFG_UINT,"Показывать секунд",0,1000};
   __root const unsigned int main_msg_timer = 300;
   
__root const CFG_HDR cfghdr218={CFG_COLOR,"Цвет шрифта",0,0};
   __root const char fontColor[4]={0xFF,0xFF,0xFF,100};
  
__root const CFG_HDR cfghdr219={CFG_COLOR,"Цвет фона",0,0};
  __root const char bgrColor[4]={0x00,0x00,0x00,100};

//Max show symbol on idle
__root const CFG_HDR cfghdr220={CFG_UINT,"Количество символов",0,50};
   __root const unsigned int main_lenght = 24;
      
__root const CFG_HDR cfghdr221={CFG_CBOX,"Использовать .. в тектсе ",0,2};
   __root const int use_cutter = 1;
__root const CFG_CBOX_ITEM cfgcbox222[2]={"No","Yes"};

    

__root const CFG_HDR cfghdr223={CFG_LEVEL,"",0,0};



//-----------------------------------------------------------------------------//
//                                AUTO STATUS                                  //
//-----------------------------------------------------------------------------//


__root const CFG_HDR cfghdr224={CFG_LEVEL,"Автостатус",1,0};

__root const CFG_HDR cfghdr225= {CFG_CBOX,"Включить",0,2};
    __root const int Auto_Status = 1;
__root const CFG_CBOX_ITEM cfgcbox226[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr227= {CFG_CBOX,"Вкл. недоступен",0,2};
    __root const int IsOnNAStatus = 1;
__root const CFG_CBOX_ITEM cfgcbox228[2]={"No","Yes"};

__root const CFG_HDR cfghdr229={CFG_UINT,"Время до недоступен(мин)",0,150};
    __root const unsigned int NAStatusTime=20;    
    
__root const CFG_HDR cfghdr230= {CFG_CBOX,"Включить автоматически при",0,13};
    __root const int isAutoStatusOn = 12;
__root const CFG_CBOX_ITEM cfgcbox231[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж

    
__root const CFG_HDR cfghdr232={CFG_UINT,"Время (мин)",0,500};
    __root const unsigned int AUTO_ENGADE=20;
    
__root const CFG_HDR cfghdr233={CFG_UINT,"Количество ответов",0,150};
    __root const unsigned int automsgcount=3;
    
__root const CFG_HDR cfghdr234={CFG_CBOX,"GMT зона",0,33};
    __root const int time_zone = 16;
__root const CFG_CBOX_ITEM cfgcbox235[33]={"-12:00", "-11:00", "-10:00", "-09:00", "-08:00", "-07:00", "-06:00", "-05:00", "-04:00", "-03:30", "-03:00", "-02:00", "-01:00", "0
    
__root const CFG_HDR cfghdr236={CFG_STR_WIN1251,"Сообщение приветствия",0,23};
    __root const char awayHelloMsg[24]="Привет";
    
__root const CFG_HDR cfghdr237={CFG_STR_WIN1251,"Сообщение отсутствия",0,255};
    __root const char awayMsg[256]="я сейчас не могу ответить!";
    
__root const CFG_HDR cfghdr238= {CFG_CBOX,"Отключение автостатуса после",0,2};
    __root const int Reset_timer = 0;
__root const CFG_CBOX_ITEM cfgcbox239[2]={"Отправки сообщения","Нажатия любой клавиши"};
  
//Show away time on idle
__root const CFG_HDR cfghdr240= {CFG_CBOX,"Показывать на гэ",0,2};
    __root const int showAwayIdle = 0;
__root const CFG_CBOX_ITEM cfgcbox241[2]={"No","Yes"};
    
    __root const CFG_HDR cfghd6_7 = {CFG_COORDINATES,"Позиция",0,0};
    __root const unsigned int auto_x = 0;
    __root const unsigned int auto_y = 252;
  
__root const CFG_HDR cfghdr242={CFG_LEVEL,"",0,0};



//-----------------------------------------------------------------------------//
//                             AUTO CHANGE STATUS                              //
//-----------------------------------------------------------------------------//


__root const CFG_HDR cfghdr243={CFG_LEVEL,"Автосмена статусов",1,0};

__root const CFG_HDR cfghdr244={CFG_CBOX,"1 cтатус",0,13};
    __root const int status_1 = 0;
__root const CFG_CBOX_ITEM cfgcbox245[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж

__root const CFG_HDR cfghdr246={CFG_TIME,"Время смены",0,0};
    __root const TTime tm_status_1={15,0};   
    

__root const CFG_HDR cfghdr247={CFG_CBOX,"2 cтатус",0,13};
    __root const int status_2 = 0;
__root const CFG_CBOX_ITEM cfgcbox248[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж

__root const CFG_HDR cfghdr249={CFG_TIME,"Время смены",0,0};
    __root const TTime tm_status_2={15,0};


__root const CFG_HDR cfghdr250={CFG_CBOX,"3 cтатус",0,13};
    __root const int status_3 = 0;
__root const CFG_CBOX_ITEM cfgcbox251[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж
    
__root const CFG_HDR cfghdr252={CFG_TIME,"Время смены",0,0};
    __root const TTime tm_status_3={15,0};


__root const CFG_HDR cfghdr253={CFG_CBOX,"4 cтатус",0,13};
    __root const int status_4 = 0;
__root const CFG_CBOX_ITEM cfgcbox254[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж
    
__root const CFG_HDR cfghdr255={CFG_TIME,"Время смены",0,0};
    __root const TTime tm_status_4={15,0};


__root const CFG_HDR cfghdr256={CFG_CBOX,"5 cтатус",0,13};
    __root const int status_5 = 0;
__root const CFG_CBOX_ITEM cfgcbox257[13]={"Выключен","В сети", "Отошел", "Недоступен", "Не беспокоить", "Занят", "Готов болтать", "Невидимый", "Депрессия", "Злой", "Дома", "Ж
    
__root const CFG_HDR cfghdr258={CFG_TIME,"Время смены",0,0};
    __root const TTime tm_status_5={15,0};


__root const CFG_HDR cfghdr259={CFG_LEVEL,"",0,0};
#ifdef NEWSGOLD
//------------------------------------------------------------------------------//
//                                SCREEN SAVER                                  //
//------------------------------------------------------------------------------//

__root const CFG_HDR cfghdr260={CFG_LEVEL,"Заставка",1,0};

__root const CFG_HDR cfghdr261= {CFG_CBOX,"Включить заставку",0,2};
    __root const int isScreenSaverEna = 0;
__root const CFG_CBOX_ITEM cfgcbox262[2]={"No","Yes"};
    
__root const CFG_HDR cfghdr263={CFG_UINT,"Время до срабатывания(1мин=12)",0,1000};
    __root const unsigned int screenSaverTime=120;

__root const CFG_HDR cfghdr264={CFG_LEVEL,"",0,0};
#endif

//------------------------------------------------------------------------------//
//                                POPUP MESSAGE                                 //
//------------------------------------------------------------------------------//

__root const CFG_HDR cfghdr265={CFG_LEVEL,"Всплывающие сообщ.",1,0};

__root const CFG_HDR cfghdr266= {CFG_CBOX,"Показывать",0,4};
    __root const int PopupShow = 3;
__root const CFG_CBOX_ITEM cfgcbox267[4]={"Ничего","Вход.сообш.","Подкл.конт.","Все"};
    
__root const CFG_HDR cfghdr268={CFG_STR_UTF8,"Формат входящ.сооб.",0,8};
    __root const char PopupMsgString[9]="%s";
    
__root const CFG_HDR cfghdr269={CFG_STR_UTF8,"Формат подкл.контакта",0,8};
    __root const char PopupOnlineString[9]=">%s<";  
    
__root const CFG_HDR cfghdr270={CFG_UINT,"Шрифт всплыв.сообщ",0,1000};
    __root const unsigned int PopupFont=FONT_SMALL;
    
__root const CFG_HDR cfghdr271={CFG_COLOR,"Фон всплыв.сообщ.",0,0};
    __root const char PopupBGCl[4]={0x00,0x00,0x00,100};
    
__root const CFG_HDR cfghdr272={CFG_COLOR,"Цвет подкл.контакта",0,0};
    __root const char PopupOnlineCl[4]={0x00,0xFF,0x00,100};
    
__root const CFG_HDR cfghdr273={CFG_COLOR,"Цвет входящ.сообщ.",0,0};
    __root const char PopupMsgCl[4]={0xFF,0xFF,0xFF,100};
    
    
__root const CFG_HDR cfghdr274={CFG_CHECKBOX,"Показывать отключенных",0,2};
    __root const int isPopupOff = 1;
    
__root const CFG_HDR cfghdr275={CFG_COLOR,"Фон отключившихся",0,0};
    __root const char PopupOffBGCl[4]={0x00,0x00,0x00,100};
    
__root const CFG_HDR cfghdr276={CFG_COLOR,"Цвет отключившихся",0,0};
    __root const char PopupOffCl[4]={0xFF,0x00,0x00,100};

__root const CFG_HDR cfghdr277={CFG_LEVEL,"",0,0};


//------------------------------------------------------------------------------//
//                                EXTRA CONFIG                                  //
//------------------------------------------------------------------------------//


__root const CFG_HDR cfghdr278={CFG_LEVEL,"Экстра опции",1,0};

//Vibra count in vibra remaider
__root const CFG_HDR cfghdr279={CFG_UINT,"Кол-во вибраций в реж.напомин.",0,10};
    __root const unsigned int Vibra_cc=2;

#ifdef NEWSGOLD
//CSM for player
__root const CFG_HDR cfghdr280={CFG_STR_UTF8,"CSM плеера",0,8};
    __root const char CsmAdr[9]="A087B454";  //el=A087B454 //es=A068E244
    
//Text before name track
__root const CFG_HDR cfghdr281={CFG_STR_WIN1251,"Текст для вывода песни",0,31};
    __root const char playing[32]="NatICQ play:";
    
//Id3 tags is any status    
__root const CFG_HDR cfghdr282={CFG_CHECKBOX,"Отображать Id3 при люб.стат.",0,2};
    __root const int Is_ID3_ANY_STATUS = 1;
__root const CFG_CBOX_ITEM cfgcbox283[2]={"No","Yes"};    
    
#endif  
//Show command sending    
__root const CFG_HDR cfghdr284={CFG_CHECKBOX,"Отображать запрос команд",0,2};
    __root const int show_send_info = 1;
__root const CFG_CBOX_ITEM cfgcbox285[2]={"No","Yes"};

    //isLogStatusChange
__root const CFG_HDR cfghdr286={CFG_CHECKBOX,"Показ. время изм.стат.контакта",0,2};
    __root const int isLogStatusChange = 1;
__root const CFG_CBOX_ITEM cfgcbox287[2]={"No","Yes"};
    
//Show Loopback contact in CL
__root const CFG_HDR cfghdr288={CFG_CHECKBOX,"Показывать Loopback в КЛ",0,2};
    __root const int IsShowLoopback = 1;
__root const CFG_CBOX_ITEM cfgcbox289[2]={"No","Yes"};   
    
     
__root const CFG_HDR cfghdr290={CFG_CHECKBOX,"Открывать ссылки",0,2};
    __root const int IsOpenBrowser = 0;
__root const CFG_CBOX_ITEM cfgcbox291[2]={"No","Yes"};   
    
__root const CFG_HDR cfghdr292={CFG_CHECKBOX,"Мульти буффер",0,2};
    __root const int IsMultiBuffer = 1;
__root const CFG_CBOX_ITEM cfgcbox293[2]={"No","Yes"};   

    
__root const CFG_HDR cfghdr294={CFG_LEVEL,"",0,0};





//------------------------------------------------------------------------------//
//                          SETTING LOADING SCREEN                              //
//------------------------------------------------------------------------------//


__root const CFG_HDR cfghdr295={CFG_LEVEL,"Экран заргузки",1,0};

__root const CFG_HDR cfghdr296= {CFG_RECT, "Прогрессбар", 0, 0};
#ifdef ELKA
   __root const RECT PBRECT = {4,280,231,287};//LOadScreenRECT
#else
   __root const RECT PBRECT = {4,150,126,157};//LOadScreenRECT
#endif
   
__root const CFG_HDR cfghdr297={CFG_COLOR,"Цвет прогрессбара",0,0};
  __root const char PBcolor[4]={0xFF,0x00,0x00,0x20};//ProgressBarColor
  
__root const CFG_HDR cfghdr298={CFG_COLOR,"Фон прогрессбара",0,0};
  __root const char BGPBcolor[4]={0xFF,0xFF,0xFF,0x00};//BackGroundProgressBarColor

__root const CFG_HDR cfghdr299={CFG_CBOX,"Менять софты",0,2};
  __root const int IsInvertSoftKey = 1;
__root const CFG_CBOX_ITEM cfgcbox300[2]={"No","Yes"};  

__root const CFG_HDR cfghdr301={CFG_CBOX,"Показывать инфу",0,2};
  __root const int IsShowInfo = 1;
__root const CFG_CBOX_ITEM cfgcbox302[2]={"No","Yes"};    

__root const CFG_HDR cfghdr303={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr304={CFG_STR_WIN1251,"Мое имя",0,31};
#ifdef kluchnik
__root const char I_str[32]="pashka";
#else
__root const char I_str[32]="I";
#endif

__root const CFG_HDR cfghdr305={CFG_STR_UTF8,"Небольшой игнор лист",0,255};
__root const char ignor_list[256]="";


//#endif

