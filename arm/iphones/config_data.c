// КОНФИГ!!!
#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr2={CFG_LEVEL,"FastRun-панель",1,0};

__root const CFG_HDR cfghdr_q_2={CFG_CHECKBOX,"Показать FastRun панель",0,2};
__root const int FASTRUN_ENA = 1;

__root const CFG_HDR cfghdr1={CFG_LEVEL,"Кнопки",1,0};

__root const CFG_HDR cfghdr2334={CFG_CBOX,"Стиль нажатия",0,2};
__root const int ENA_FR_LONGPRESS=1;
__root const CFG_CBOX_ITEM cfgcbox23[2]={"Краткое нажатие","Нажал и держи)"};

__root const CFG_HDR cfghdr3={CFG_UINT,"Кнопка активации (DEC)",0,65535};
__root const int FR_CALL_BUTTON=GREEN_BUTTON;

__root const CFG_HDR cfghdr4={CFG_UINT,"Кнопка деактивации (DEC)",0,65535};
__root const int FR_EXIT_BUTTON=GREEN_BUTTON;
__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr6={CFG_LEVEL,"Позиция и размер",1,0};
__root const CFG_HDR cfghdr7={CFG_CBOX,"Положение на экране",0,4};
__root const int DRAW_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox1[4]={"Слева","Справа","Вверху","Внизу"};

__root const CFG_HDR cfghdr9={CFG_UINT,"Oтступ",0,320};
__root const unsigned int BEGIN=5;

__root const CFG_HDR cfghdr10={CFG_UINT,"Длинна панели",0,320};
__root const unsigned int LEN=165;

__root const CFG_HDR cfghdr6921={CFG_CBOX,"Размер иконки",0,5};
__root const int FR_PIC_SIZE=0;
__root const CFG_CBOX_ITEM cfgcbox4433[5]={"16x16","24x24","32x32","48x48","64x64"};
__root const CFG_HDR cfghdr11={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr12={CFG_LEVEL,"Цвета",1,0};
__root const CFG_HDR cfghdr60={CFG_COLOR,"Рамка (без прозрачности)",0,0};
__root const char cfgPanBorderCol1[4]={0,126,249,100};

__root const CFG_HDR cfghdr61={CFG_COLOR,"Фон  (без прозрачности)",0,0};
__root const char cfgPanBGCol1[4]={174,174,230,100};

__root const CFG_HDR cfghdr63={CFG_COLOR,"Цвет закладки",0,0};
__root const char cfgBookBGCol[4]={155,155,255,100};

__root const CFG_HDR cfghdr62={CFG_COLOR,"Рамка закладки",0,0};
__root const char cfgBookBorderCol[4]={255,255,255,50};

__root const CFG_HDR cfgh3d15={CFG_STR_UTF8,"Фоновый рисунок",3,127};
__root const char FON_FR[128]="";

__root const CFG_HDR cfghdr13={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr124={CFG_LEVEL,"Управление закладками",1,0};
__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"Закладка 1 ",3,127};
__root const char BM1FILE_FR[128]="";
__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"Иконка 1 ",3,127};
__root const char BM1PIC_FR[128]="";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"Закладка 2 ",3,127};
__root const char BM2FILE_FR[128]="";
__root const CFG_HDR cfghdr18={CFG_STR_UTF8,"Иконка 2 ",3,127};
__root const char BM2PIC_FR[128]="";

__root const CFG_HDR cfghdr20={CFG_STR_UTF8,"Закладка 3 ",3,127};
__root const char BM3FILE_FR[128]="";
__root const CFG_HDR cfghdr21={CFG_STR_UTF8,"Иконка 3 ",3,127};
__root const char BM3PIC_FR[128]="";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Закладка 4 ",3,127};
__root const char BM4FILE_FR[128]="";
__root const CFG_HDR cfghdr24={CFG_STR_UTF8,"Иконка 4 ",3,127};
__root const char BM4PIC_FR[128]="";

__root const CFG_HDR cfghdr26={CFG_STR_UTF8,"Закладка 5 ",3,127};
__root const char BM5FILE_FR[128]="";
__root const CFG_HDR cfghdr27={CFG_STR_UTF8,"Иконка 5 ",3,127};
__root const char BM5PIC_FR[128]="";

__root const CFG_HDR cfghdr29={CFG_STR_UTF8,"Закладка 6 ",3,127};
__root const char BM6FILE_FR[128]="";
__root const CFG_HDR cfghdr30={CFG_STR_UTF8,"Иконка 6 ",3,127};
__root const char BM6PIC_FR[128]="";

__root const CFG_HDR cfghdr32={CFG_STR_UTF8,"Закладка 7 ",3,127};
__root const char BM7FILE_FR[128]="";
__root const CFG_HDR cfghdr33={CFG_STR_UTF8,"Иконка 7 ",3,127};
__root const char BM7PIC_FR[128]="";

__root const CFG_HDR cfghdr35={CFG_STR_UTF8,"Закладка 8 ",3,127};
__root const char BM8FILE_FR[128]="";
__root const CFG_HDR cfghdr36={CFG_STR_UTF8,"Иконка 8 ",3,127};
__root const char BM8PIC_FR[128]="";

__root const CFG_HDR cfghdr38={CFG_STR_UTF8,"Закладка 9 ",3,127};
__root const char BM9FILE_FR[128]="";
__root const CFG_HDR cfghdr39={CFG_STR_UTF8,"Иконка 9 ",3,127};
__root const char BM9PIC_FR[128]="";

__root const CFG_HDR cfghdr41={CFG_STR_UTF8,"Закладка 10 ",3,127};
__root const char BM10FILE_FR[128]="";
__root const CFG_HDR cfghdr42={CFG_STR_UTF8,"Иконка 10 ",3,127};
__root const char BM10PIC_FR[128]="";

__root const CFG_HDR cfghdr44={CFG_STR_UTF8,"Закладка 11 ",3,127};
__root const char BM11FILE_FR[128]="";
__root const CFG_HDR cfghdr45={CFG_STR_UTF8,"Иконка 11 ",3,127};
__root const char BM11PIC_FR[128]="";

__root const CFG_HDR cfghdr47={CFG_STR_UTF8,"Закладка 12 ",3,127};
__root const char BM12FILE_FR[128]="";
__root const CFG_HDR cfghdr48={CFG_STR_UTF8,"Иконка 12 ",3,127};
__root const char BM12PIC_FR[128]="";

__root const CFG_HDR cfghdr50={CFG_STR_UTF8,"Закладка 13 ",3,127};
__root const char BM13FILE_FR[128]="";
__root const CFG_HDR cfghdr51={CFG_STR_UTF8,"Иконка 13 ",3,127};
__root const char BM13PIC_FR[128]="";

__root const CFG_HDR cfghdr53={CFG_STR_UTF8,"Закладка 14 ",3,127};
__root const char BM14FILE_FR[128]="";
__root const CFG_HDR cfghdr54={CFG_STR_UTF8,"Иконка 14 ",3,127};
__root const char BM14PIC_FR[128]="";

__root const CFG_HDR cfghdr56={CFG_STR_UTF8,"Закладка 15 ",3,127};
__root const char BM15FILE_FR[128]="";
__root const CFG_HDR cfghdr57={CFG_STR_UTF8,"Иконка 15 ",3,127};
__root const char BM15PIC_FR[128]="";
__root const CFG_HDR cfghdr158={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr66={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr67={CFG_LEVEL,"IDLE-панель",1,0};

__root const CFG_HDR cfghdr_c_2={CFG_CHECKBOX,"Показать панель",0,2};
__root const int IDLE_ENA = 1;

__root const CFG_HDR cfghdr_c_3={CFG_CHECKBOX,"Горизонтальный вид",0,2};
__root const int IDLE_GORIZO = 0;

__root const CFG_HDR cfghdr6931={CFG_UINT,"Звук активации",0,65535};
__root const unsigned int SOUND_11=6;

__root const CFG_HDR cfghdr199={CFG_LEVEL,"Кнопки",1,0};

__root const CFG_HDR cfghdr2434={CFG_CBOX,"Стиль нажатия",0,2};
__root const int ENA_IDLE_LONGPRESS=1;
__root const CFG_CBOX_ITEM cfgcbox443[2]={"Краткое нажатие","Нажал и держи)"};

__root const CFG_HDR cfghdr389={CFG_UINT,"Код кнопки актив.(DEC)",0,65535};
__root const int IDLE_CALL_BUTTON=62;

__root const CFG_HDR cfghdr487={CFG_UINT,"Код кнопки деактив.(DEC)",0,65535};
__root const int IDLE_EXIT_BUTTON=62;
__root const CFG_HDR cfghdr576={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr671={CFG_LEVEL,"Позиция и размеры",1,0};
__root const CFG_HDR cfghdr68={CFG_COORDINATES,"Координаты",0,0};
__root const unsigned int xx1=0;
__root const unsigned int yy1=39;
//__root const unsigned int x1=0;
//__root const unsigned int y1=39;

__root const CFG_HDR cfghdr69={CFG_UINT,"Длинна панели",0,320};
__root const unsigned int LEN_ID=131;

__root const CFG_HDR cfghdr1112={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr672={CFG_LEVEL,"Цвета",1,0};
__root const CFG_HDR cfghdr134={CFG_COLOR,"Панель активна (фон)",0,0};
__root const char cfgPanBGCol_ID_ena[4]={255,255,255,2};

__root const CFG_HDR cfghdr1343={CFG_COLOR,"Панель НЕактивна (фон)",0,0};
__root const char cfgPanBGCol_ID_dis[4]={255,255,255,2};

__root const CFG_HDR cfghdr135={CFG_COLOR,"Бордюр закладки",0,0};
__root const char cfgBookBorderCol_ID[4]={255,255,255,100};

__root const CFG_HDR cfghdr136={CFG_COLOR,"Фон закладки",0,0};
__root const char cfgBookBGCol_ID[4]={255,255,255,20};


__root const CFG_HDR cfghdr111={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr128={CFG_LEVEL,"Супер эфекты :)",1,0};



__root const CFG_HDR cfghdr13215={CFG_CBOX,"Эфекты иконок",0,5};
__root const int EFFECT=0;
__root const CFG_CBOX_ITEM cfgcbox4r4r33[5]={"Свечение","Тень","Смазывание краев","ДЭ 1","ДЭ 2"};


__root const CFG_HDR cfghdr389COL={CFG_COLOR,"Цвет эфекта",0,65535};
__root const char colo[4]="    ";

__root const CFG_HDR cfghdr26911={CFG_UINT,"Твёрдость эфекта [120]",0,320};
__root const unsigned int PAR1_ID=140;

__root const CFG_HDR cfghdr26911d={CFG_UINT,"Повторитель эфекта [5]",0,320};
__root const unsigned int PAR2_ID=25;

__root const CFG_HDR cfghdr26911e={CFG_UINT,"Расширить картинку",0,320};
__root const unsigned int PAR3_ID=8;

__root const CFG_HDR cfghdr74={CFG_STR_UTF8,"Курсор - подложка",3,127};
__root const char PIC_ID_KUR[128]="";

__root const CFG_HDR cfghd4={CFG_STR_UTF8,"Курсор",3,127};
__root const char PIC_ID_KUR1[128]="";

__root const CFG_HDR cfgj3d15={CFG_STR_UTF8,"Фоновый рисунок",3,127};
__root const char FON_ID[128]="";


__root const CFG_HDR cfghdr138={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr673={CFG_LEVEL,"Закладки",1,0};

__root const CFG_HDR cfghdr73v={CFG_STR_UTF8,"Папка с иконками",3,127};
__root const char BM_FOLDER_ID[128]="";

__root const CFG_HDR cfghdr73={CFG_STR_UTF8,"Закладка 1 ",3,127};
__root const char BM1FILE_ID[128]="";
__root const CFG_HDR cfghdr7h4={CFG_STR_UTF8,"Иконка 1 ",3,127};
__root const char BM1PIC_ID2[128]="";

__root const CFG_HDR cfghdr77={CFG_STR_UTF8,"Закладка 2 ",3,127};
__root const char BM2FILE_ID[128]="";
__root const CFG_HDR cfghdr78={CFG_STR_UTF8,"Иконка 2 ",3,127};
__root const char BM2PIC_ID2[128]="";


__root const CFG_HDR cfghdr81={CFG_STR_UTF8,"Закладка 3 ",3,127};
__root const char BM3FILE_ID[128]="";
__root const CFG_HDR cfghdr82={CFG_STR_UTF8,"Иконка 3 ",3,127};
__root const char BM3PIC_ID2[128]="";


__root const CFG_HDR cfghdr85={CFG_STR_UTF8,"Закладка 4 ",3,127};
__root const char BM4FILE_ID[128]="";
__root const CFG_HDR cfghdr86={CFG_STR_UTF8,"Иконка 4 ",3,127};
__root const char BM4PIC_ID2[128]="";

__root const CFG_HDR cfghdr89={CFG_STR_UTF8,"Закладка 5 ",3,127};
__root const char BM5FILE_ID[128]="";
__root const CFG_HDR cfghdr90={CFG_STR_UTF8,"Иконка 5 ",3,127};
__root const char BM5PIC_ID2[128]="";


__root const CFG_HDR cfghdr93={CFG_STR_UTF8,"Закладка 6 ",3,127};
__root const char BM6FILE_ID[128]="";
__root const CFG_HDR cfghdr94={CFG_STR_UTF8,"Иконка 6 ",3,127};
__root const char BM6PIC_ID2[128]="";


__root const CFG_HDR cfghdr97={CFG_STR_UTF8,"Закладка 7 ",3,127};
__root const char BM7FILE_ID[128]="";
__root const CFG_HDR cfghdr98={CFG_STR_UTF8,"Иконка 7 ",3,127};
__root const char BM7PIC_ID2[128]="";


__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"Закладка 8 ",3,127};
__root const char BM8FILE_ID[128]="";
__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"Иконка 8 ",3,127};
__root const char BM8PIC_ID2[128]="";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"Закладка 9 ",3,127};
__root const char BM9FILE_ID[128]="";
__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"Иконка 9 ",3,127};
__root const char BM9PIC_ID2[128]="";


__root const CFG_HDR cfghdr109={CFG_STR_UTF8,"Закладка 10 ",3,127};
__root const char BM10FILE_ID[128]="";
__root const CFG_HDR cfghdr110={CFG_STR_UTF8,"Иконка 10 ",3,127};
__root const char BM10PIC_ID2[128]="";


__root const CFG_HDR cfghdr133={CFG_STR_UTF8,"Закладка 11 ",3,127};
__root const char BM11FILE_ID[128]="";
__root const CFG_HDR cfghdr114={CFG_STR_UTF8,"Иконка 11 ",3,127};
__root const char BM11PIC_ID2[128]="";


__root const CFG_HDR cfghdr117={CFG_STR_UTF8,"Закладка 12 ",3,127};
__root const char BM12FILE_ID[128]="";
__root const CFG_HDR cfghdr118={CFG_STR_UTF8,"Иконка 12 ",3,127};
__root const char BM12PIC_ID2[128]="";


__root const CFG_HDR cfghdr121={CFG_STR_UTF8,"Закладка 13 ",3,127};
__root const char BM13FILE_ID[128]="";
__root const CFG_HDR cfghdr122={CFG_STR_UTF8,"Иконка 13 ",3,127};
__root const char BM13PIC_ID2[128]="";


__root const CFG_HDR cfghdr125={CFG_STR_UTF8,"Закладка 14 ",3,127};
__root const char BM14FILE_ID[128]="";
__root const CFG_HDR cfghdr126={CFG_STR_UTF8,"Иконка 14 ",3,127};
__root const char BM14PIC_ID2[128]="";


__root const CFG_HDR cfghdr129={CFG_STR_UTF8,"Закладка 15 ",3,127};
__root const char BM15FILE_ID[128]="";
__root const CFG_HDR cfghdr130={CFG_STR_UTF8,"Иконка 15 ",3,127};
__root const char BM15PIC_ID2[128]="";

__root const CFG_HDR cfghdr166c={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr167c={CFG_LEVEL,"Смещение значков",1,0};

__root const CFG_HDR cfghdr692f={CFG_CBOX,"Формула смещения",0,1};
__root const int IDLE444=0;
__root const CFG_CBOX_ITEM cfgcbox4434f[1]={"K+(L*x)+M*cos(N*x))*(-1+P)"};

__root const CFG_HDR cfghdr389k={CFG_UINT,"K",0,4294967295};
__root const int K1=0;

__root const CFG_HDR cfghdr389l={CFG_UINT,"L",0,4294967295};
__root const int L1=0;

__root const CFG_HDR cfghdr389m={CFG_UINT,"M",0,4294967295};
__root const int M1=15;

__root const CFG_HDR cfghdr389n={CFG_UINT,"N",0,65535};
__root const int N1=45;

__root const CFG_HDR cfghdr389p={CFG_UINT,"P",0,65535};
__root const int P1=0;

__root const CFG_HDR cfghdr389r={CFG_INT,"Смещение по длинне [20]",0,65535};
__root const int R1=10;



__root const CFG_HDR cfghdr176={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr166={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr167={CFG_LEVEL,"EMENU",1,0};

__root const CFG_HDR cfghdr229={CFG_STR_UTF8,"Emenu",3,127};
__root const char FILE_EMENU[128]="4:\\Zbin\\utilities\\emenu.elf";

__root const CFG_HDR cfghdr168={CFG_LEVEL,"",0,0};

