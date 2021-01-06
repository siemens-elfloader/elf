#include "D:\ARM_ALL\inc\cfg_items.h"
#include "define.h"
//Конфигурация

#ifdef CONFIG_EL
enum icons
{
  ICO_locked=0x203,
  ICO_mplayer_pl=0x206,
  ICO_mplayer_pa=0x207,
  ICO_mplayer_st=0x0,
  ICO_vibra=0x256,
  ICO_gprs=0x1EC,
  ICO_gprsred=0x1EB,
  ICO_dumping=0x204,
  ICO_callout=0x1E5,
  ICO_SMS_both=0x209,
  ICO_SMS_recv=0x208,
  ICO_SMS_send=0x20A,
  ICO_net_na=0x267,
  ICO_BT_nvis=0x1C5,
  ICO_BT_vis=0x1C6,
  ICO_BT_ntrans=0x1C7,
  ICO_BT_trans=0x1C8,
  ICO_BT_headset=0x1C9,
  ICO_headset=0x1F0,
  ICO_decrypt=0x256,
  ICO_ringoff=0x1C2,
  ICO_ringon=0x64,
  ICO_ring_onlygroups=0x1E4,
  ICO_car=0x1E6,
  ICO_alarm=0x1C1,
  ICO_camera=0x6B9,
  ICO_lamp=0x6B5,
  ICO_java=0x6B7,
  ICO_java_two=0x6B8,
  ICO_vol=0x6A5,
  ICO_prof=0x6B5,
  ICO_non=0x0
};
#endif

#ifdef CONFIG_NSG
enum icons
{
  ICO_locked=0x234,
  ICO_mplayer_pl=0x46A,
  ICO_mplayer_pa=0x468,
  ICO_mplayer_st=0x0,
  ICO_vibra=0x24D,
  ICO_gprs=0x21B,
  ICO_gprsred=0x21A,
  ICO_dumping=0x337,
  ICO_callout=0x218,
  ICO_SMS_both=0x24C,
  ICO_SMS_recv=0x208,
  ICO_SMS_send=0x20A,
  ICO_net_na=0x267,
  ICO_BT_nvis=0x1F6,
  ICO_BT_vis=0x1F7,
  ICO_BT_ntrans=0x1F8,
  ICO_BT_trans=0x1F9,
  ICO_BT_headset=0x1C9,
  ICO_headset=0x21F,
  ICO_decrypt=0x256,
  ICO_ringoff=0x1F3,
  ICO_ringon=0x64,
  ICO_ring_onlygroups=0x214,
  ICO_car=0x215,
  ICO_alarm=0x1F2,
  ICO_camera=0x139,
  ICO_lamp=0x6B5,
  ICO_java=0x6B7,
  ICO_java_two=0x6B8,
  ICO_vol=0x6A5,
  ICO_prof=0x6B5,
  ICO_irda_trans=0x221,
  ICO_irda=0x222,
  ICO_non=0x0
};
#endif

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Вкл. текст приветствия?",0,0};
__root const int ena_msg=0;

__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"Вкл. сообщение о реконфигурации?",0,0};
__root const int ena_req=0;

//-----------------------------Java---------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Java",1,0};

__root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int java=1;

__root const CFG_HDR cfghdr1_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_java=0;
__root const CFG_CBOX_ITEM cfgcbox1_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr1_3={CFG_UINT,"Номер картинки(1a Java)",0,0xFFF};
__root const unsigned int java_icon=ICO_java;

__root const CFG_HDR cfghdr1_4={CFG_CHECKBOX,"Отображать запуск 2ой Java?",0,0};
__root const int two_java=1;

__root const CFG_HDR cfghdr1_5={CFG_UINT,"Номер картинки(2e Java)",0,0xFFF};
__root const unsigned int two_java_icon=ICO_java_two;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Громкость----------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Громкость",1,0};

__root const CFG_HDR cfghdr2_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int volume=1;

__root const CFG_HDR cfghdr2_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_volume=0;
__root const CFG_CBOX_ITEM cfgcbox2_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr2_3={CFG_CHECKBOX,"Отображать только при музыке?",0,0};
__root const int only_sound=1;

__root const CFG_HDR cfghdr2_4={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int vol_icon=ICO_vol;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Профиль------------------------------------------

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Профиль",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int profile=0;

__root const CFG_HDR cfghdr3_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_profile=0;
__root const CFG_CBOX_ITEM cfgcbox3_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr3_4={CFG_UINT,"Номер картинки профиля 1",0,0xFFF};
__root const unsigned int profile1_icon=ICO_prof;

__root const CFG_HDR cfghdr3_5={CFG_UINT,"Номер картинки профиля 2",0,0xFFF};
__root const unsigned int profile2_icon=ICO_prof+1;

__root const CFG_HDR cfghdr3_6={CFG_UINT,"Номер картинки профиля 3",0,0xFFF};
__root const unsigned int profile3_icon=ICO_prof+2;

__root const CFG_HDR cfghdr3_7={CFG_UINT,"Номер картинки профиля 4",0,0xFFF};
__root const unsigned int profile4_icon=ICO_prof+3;

__root const CFG_HDR cfghdr3_8={CFG_UINT,"Номер картинки профиля 5",0,0xFFF};
__root const unsigned int profile5_icon=ICO_prof+4;

__root const CFG_HDR cfghdr3_9={CFG_UINT,"Номер картинки профиля 6",0,0xFFF};
__root const unsigned int profile6_icon=ICO_prof+5;

__root const CFG_HDR cfghdr3_10={CFG_UINT,"Номер картинки профиля 7",0,0xFFF};
__root const unsigned int profile7_icon=ICO_prof+6;

__root const CFG_HDR cfghdr3_11={CFG_UINT,"Номер картинки профиля 8",0,0xFFF};
__root const unsigned int profile8_icon=ICO_prof+7;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Фонарик------------------------------------------

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Фонарик",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int lamp=0;

__root const CFG_HDR cfghdr4_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_lamp=0;
__root const CFG_CBOX_ITEM cfgcbox4_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr4_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int lamp_icon=ICO_lamp;

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Интернет-----------------------------------------

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"Интернет",1,0};

__root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int inet=1;

__root const CFG_HDR cfghdr5_2={CFG_CBOX,"Отображать",0,3};
__root const int ena_inet=0;
__root const CFG_CBOX_ITEM cfgcbox5_1_1[3]={"Всё","GPRS","EDGE"};

//-------------------------------GPRS-------------------------------------------

__root const CFG_HDR cfghdr_m51_1={CFG_LEVEL,"GPRS",1,0};

__root const CFG_HDR cfghdr5_1_1={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_gprs=0;
__root const CFG_CBOX_ITEM cfgcbox5_1_1_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr5_1_2={CFG_UINT,"Номер картинки(сессия)",0,0xFFF};
__root const unsigned int gprss_icon=ICO_gprs;

__root const CFG_HDR cfghdr5_1_3={CFG_CHECKBOX,"Отображать статус соединения?",0,0};
__root const int gprs_con=1;

__root const CFG_HDR cfghdr5_1_4={CFG_UINT,"Номер картинки(соединение)",0,0xFFF};
__root const unsigned int gprsc_icon=ICO_gprsred;

__root const CFG_HDR cfghdr5_1_5={CFG_CHECKBOX,"Вкл. иконку выкл. GPRS?",0,0};
__root const int gprs_dis=0;

__root const CFG_HDR cfghdr5_1_6={CFG_UINT,"Номер картинки(выкл.)",0,0xFFF};
__root const unsigned int gprsd_icon=ICO_non;

__root const CFG_HDR cfghdr_m50_1={CFG_LEVEL,"",0,0};

//-------------------------------EDGE-------------------------------------------

__root const CFG_HDR cfghdr_m51_2={CFG_LEVEL,"EDGE",1,0};

__root const CFG_HDR cfghdr5_2_1={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_edge=0;
__root const CFG_CBOX_ITEM cfgcbox5_2_1_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr5_2_2={CFG_UINT,"Номер картинки(сессия)",0,0xFFF};
__root const unsigned int edges_icon=ICO_gprs;

__root const CFG_HDR cfghdr5_2_3={CFG_CHECKBOX,"Отображать статус соединения?",0,0};
__root const int edge_con=1;

__root const CFG_HDR cfghdr5_2_4={CFG_UINT,"Номер картинки(соединение)",0,0xFFF};
__root const unsigned int edgec_icon=ICO_gprsred;

__root const CFG_HDR cfghdr5_2_5={CFG_CHECKBOX,"Вкл. иконку выкл. EDGE?",0,0};
__root const int edge_dis=0;

__root const CFG_HDR cfghdr5_2_6={CFG_UINT,"Номер картинки(выкл.)",0,0xFFF};
__root const unsigned int edged_icon=ICO_non;

__root const CFG_HDR cfghdr_m50_2={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Вибра--------------------------------------------

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"Вибра",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int vibra=1;

__root const CFG_HDR cfghdr6_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_vibra=0;
__root const CFG_CBOX_ITEM cfgcbox6_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr6_3={CFG_CHECKBOX,"Вкл. иконку выкл. вибры?",0,0};
__root const int vibra_off=0;

__root const CFG_HDR cfghdr6_4={CFG_UINT,"Номер картинки(вкл.)",0,0xFFF};
__root const unsigned int vibra_icon=ICO_vibra;

__root const CFG_HDR cfghdr6_5={CFG_UINT,"Номер картинки(выкл.)",0,0xFFF};
__root const unsigned int vibra_off_icon=ICO_non;

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Будильник----------------------------------------

__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"Будильник",1,0};

__root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int alarm=1;

__root const CFG_HDR cfghdr7_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_alarm=0;
__root const CFG_CBOX_ITEM cfgcbox7_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr7_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int alarm_icon=ICO_alarm;

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------CSM'ы--------------------------------------------

__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"CSM'ы",1,0};

__root const CFG_HDR cfghdr8_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int allcsm=0;

__root const CFG_HDR cfghdr8_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_allcsm=0;
__root const CFG_CBOX_ITEM cfgcbox8_2_[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr8_1_1={CFG_CHECKBOX,"Вкл. иконку 1?",0,0};
__root const int csm1=1;

__root const CFG_HDR cfghdr8_2_1={CFG_UINT,"Номер картинки 1",0,0xFFF};
__root const unsigned int csm1_icon=0x1C1;

__root const CFG_HDR cfghdr8_3_1={CFG_STR_UTF8,"Имя CSM'а 1",0,63};
__root const char csm1_name[64]="SieJC";

__root const CFG_HDR cfghdr8_1_2={CFG_CHECKBOX,"Вкл. иконку 2?",0,0};
__root const int csm2=1;

__root const CFG_HDR cfghdr8_2_2={CFG_UINT,"Номер картинки 2",0,0xFFF};
__root const unsigned int csm2_icon=0x1C1;

__root const CFG_HDR cfghdr8_3_2={CFG_STR_UTF8,"Имя CSM'а 2",0,63};
__root const char csm2_name[64]="NatICQ";

__root const CFG_HDR cfghdr8_1_3={CFG_CHECKBOX,"Вкл. иконку 3?",0,0};
__root const int csm3=1;

__root const CFG_HDR cfghdr8_2_3={CFG_UINT,"Номер картинки 3",0,0xFFF};
__root const unsigned int csm3_icon=0x1C1;

__root const CFG_HDR cfghdr8_3_3={CFG_STR_UTF8,"Имя CSM'а 3",0,63};
__root const char csm3_name[64]="BalletMini";

__root const CFG_HDR cfghdr8_1_4={CFG_CHECKBOX,"Вкл. иконку 4?",0,0};
__root const int csm4=1;

__root const CFG_HDR cfghdr8_2_4={CFG_UINT,"Номер картинки 4",0,0xFFF};
__root const unsigned int csm4_icon=0x1C1;

__root const CFG_HDR cfghdr8_3_4={CFG_STR_UTF8,"Имя CSM'а 4",0,63};
__root const char csm4_name[64]="";

__root const CFG_HDR cfghdr8_1_5={CFG_CHECKBOX,"Вкл. иконку 5?",0,0};
__root const int csm5=1;

__root const CFG_HDR cfghdr8_2_5={CFG_UINT,"Номер картинки 5",0,0xFFF};
__root const unsigned int csm5_icon=0x1C1;

__root const CFG_HDR cfghdr8_3_5={CFG_STR_UTF8,"Имя CSM'а 5",0,63};
__root const char csm5_name[64]="";

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//-----------------------------Камера-------------------------------------------

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Камера",1,0};

__root const CFG_HDR cfghdr9_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int camera=1;

__root const CFG_HDR cfghdr9_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_camera=0;
__root const CFG_CBOX_ITEM cfgcbox9_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr9_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int camera_icon=ICO_camera;

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Медиаплеер--------------------------------------

__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"Медиаплеер",1,0};

__root const CFG_HDR cfghdr10_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int mediapleer=1;

__root const CFG_HDR cfghdr10_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_mediapleer=0;
__root const CFG_CBOX_ITEM cfgcbox10_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr10_3={CFG_CHECKBOX,"Вкл. статус медиаплеера?",0,0};
__root const int sta_mediapleer=1;

__root const CFG_HDR cfghdr10_4={CFG_UINT,"Номер картинки(воспр.)",0,0xFFF};
__root const unsigned int play_mediapleer_icon=ICO_mplayer_pl;

__root const CFG_HDR cfghdr10_5={CFG_UINT,"Номер картинки(пауза)",0,0xFFF};
__root const unsigned int pausa_mediapleer_icon=ICO_mplayer_pa;

__root const CFG_HDR cfghdr10_6={CFG_UINT,"Номер картинки(стоп)",0,0xFFF};
__root const unsigned int stop_mediapleer_icon=ICO_mplayer_st;

__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Звук--------------------------------------------

__root const CFG_HDR cfghdr_m111={CFG_LEVEL,"Звук",1,0};

__root const CFG_HDR cfghdr11_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int sounds=1;

__root const CFG_HDR cfghdr11_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_sounds=0;
__root const CFG_CBOX_ITEM cfgcbox11_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr11_3={CFG_CHECKBOX,"Вкл. иконку вкл. звука?",0,0};
__root const int sounds_on=0;

__root const CFG_HDR cfghdr11_4={CFG_UINT,"Номер картинки(вкл.)",0,0xFFF};
__root const unsigned int sound_on_icon=ICO_ringon;

__root const CFG_HDR cfghdr11_5={CFG_UINT,"Номер картинки(выкл.)",0,0xFFF};
__root const unsigned int sound_off_icon=ICO_ringoff;

__root const CFG_HDR cfghdr_m110={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Звонок------------------------------------------

__root const CFG_HDR cfghdr_m121={CFG_LEVEL,"Звонок",1,0};

__root const CFG_HDR cfghdr12_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int call=0;

__root const CFG_HDR cfghdr12_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_call=0;
__root const CFG_CBOX_ITEM cfgcbox12_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr12_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int call_icon=ICO_callout;

__root const CFG_HDR cfghdr12_4={CFG_CHECKBOX,"Иконка нешифрованого протокола?",0,0};
__root const int decrypt=0;

__root const CFG_HDR cfghdr12_5={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int decrypt_icon=ICO_decrypt;

//--------------------------------Расширенный-----------------------------------

__root const CFG_HDR cfghdr_m121_1={CFG_LEVEL,"Расширенный",1,0};

__root const CFG_HDR cfghdr12_1_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int ext_call=0;

__root const CFG_HDR cfghdr12_1_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_ext_call=0;
__root const CFG_CBOX_ITEM cfgcbox12_1_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr12_1_3={CFG_UINT,"Номер картинки(исходящий звонок)",0,0xFFF};
__root const unsigned int out_ext_call_icon=ICO_callout;

__root const CFG_HDR cfghdr12_1_4={CFG_UINT,"Номер картинки(входящий звонок)",0,0xFFF};
__root const unsigned int in_ext_call_icon=ICO_callout;

__root const CFG_HDR cfghdr12_1_5={CFG_UINT,"Номер картинки(ожидание)",0,0xFFF};
__root const unsigned int wait_ext_call_icon=ICO_callout;

__root const CFG_HDR cfghdr12_1_6={CFG_UINT,"Номер картинки(разговор)",0,0xFFF};
__root const unsigned int talk_ext_call_icon=ICO_callout;

__root const CFG_HDR cfghdr_m120_1={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m120={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Блокировка--------------------------------------

__root const CFG_HDR cfghdr_m131={CFG_LEVEL,"Блокировка",1,0};

__root const CFG_HDR cfghdr13_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int lock=1;

__root const CFG_HDR cfghdr13_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_lock=0;
__root const CFG_CBOX_ITEM cfgcbox13_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr13_3={CFG_CHECKBOX,"Вкл. иконку выкл. блокировки?",0,0};
__root const int lock_off=0;

__root const CFG_HDR cfghdr13_4={CFG_UINT,"Номер картинки(вкл.)",0,0xFFF};
__root const unsigned int lock_on_icon=ICO_locked;

__root const CFG_HDR cfghdr13_5={CFG_UINT,"Номер картинки(выкл.)",0,0xFFF};
__root const unsigned int lock_off_icon=ICO_non;

__root const CFG_HDR cfghdr_m130={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Гарнитура---------------------------------------

__root const CFG_HDR cfghdr_m141={CFG_LEVEL,"Гарнитура",1,0};

__root const CFG_HDR cfghdr14_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int nayshniki=1;

__root const CFG_HDR cfghdr14_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_nayshniki=0;
__root const CFG_CBOX_ITEM cfgcbox14_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr14_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int nayshniki_icon=ICO_headset;

#ifdef ELKA
#else
__root const CFG_HDR cfghdr14_4={CFG_CHECKBOX,"Отображать Mono гарнитуру?",0,0};
__root const int nayshniki_mono=1;
#endif

__root const CFG_HDR cfghdr_m140={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Bluetooth---------------------------------------

__root const CFG_HDR cfghdr_m151={CFG_LEVEL,"Bluetooth",1,0};

__root const CFG_HDR cfghdr15_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int bt=1;

__root const CFG_HDR cfghdr15_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_bt=0;
__root const CFG_CBOX_ITEM cfgcbox15_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr15_3={CFG_UINT,"Номер картинки вкл. BT(видимый)",0,0xFFF};
__root const unsigned int bt_vis_icon=ICO_BT_vis;

__root const CFG_HDR cfghdr15_4={CFG_UINT,"Вкл. BT(невидимый)",0,0xFFF};
__root const unsigned int bt_nvis_icon=ICO_BT_nvis;

__root const CFG_HDR cfghdr15_5={CFG_UINT,"Вкл. BT(передача)",0,0xFFF};
__root const unsigned int bt_trans_icon=ICO_BT_trans;

__root const CFG_HDR cfghdr15_6={CFG_UINT,"Вкл. BT(невидимая передача)",0,0xFFF};
__root const unsigned int bt_ntrans_icon=ICO_BT_ntrans;

__root const CFG_HDR cfghdr15_7={CFG_UINT,"Вкл. BT(гарнитура)",0,0xFFF};
__root const unsigned int bt_headset_icon=ICO_headset;

__root const CFG_HDR cfghdr15_8={CFG_CHECKBOX,"Отображать иконку выкл. BT?",0,0};
__root const int bt_off=0;

__root const CFG_HDR cfghdr15_9={CFG_UINT,"Номер картинки выкл. BT",0,0xFFF};
__root const unsigned int bt_off_icon=ICO_non;

__root const CFG_HDR cfghdr_m150={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------SMS---------------------------------------------

__root const CFG_HDR cfghdr_m161={CFG_LEVEL,"SMS",1,0};

__root const CFG_HDR cfghdr16_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int sms=1;

__root const CFG_HDR cfghdr16_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_sms=0;
__root const CFG_CBOX_ITEM cfgcbox16_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr16_3={CFG_UINT,"Номер картинки(отправка)",0,0xFFF};
__root const unsigned int sms_send_icon=0x6A5;

__root const CFG_HDR cfghdr16_4={CFG_UINT,"Номер картинки(принятие)",0,0xFFF};
__root const unsigned int sms_recv_icon=0x6A5;

__root const CFG_HDR cfghdr16_5={CFG_CHECKBOX,"Иконка нет новых?",0,0};
__root const int sms_both=0;

__root const CFG_HDR cfghdr16_6={CFG_UINT,"Номер картинки(нет новых SMS)",0,0xFFF};
__root const unsigned int sms_both_icon=0x6A5;

__root const CFG_HDR cfghdr_m160={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------MicroSD-----------------------------------------

#ifdef CONFIG_EL
__root const CFG_HDR cfghdr_m171={CFG_LEVEL,"MicroSD",1,0};

__root const CFG_HDR cfghdr17_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int microsd=0;

__root const CFG_HDR cfghdr17_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_microsd=0;
__root const CFG_CBOX_ITEM cfgcbox17_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr17_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int microsd_icon=ICO_dumping;

__root const CFG_HDR cfghdr_m170={CFG_LEVEL,"",0,0};
#endif

//------------------------------------------------------------------------------

//------------------------------Автомобиль--------------------------------------

__root const CFG_HDR cfghdr_m181={CFG_LEVEL,"Автомобиль",1,0};

__root const CFG_HDR cfghdr18_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int car=0;

__root const CFG_HDR cfghdr18_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_car=0;
__root const CFG_CBOX_ITEM cfgcbox18_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr18_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int car_icon=ICO_car;

__root const CFG_HDR cfghdr_m180={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------irDa--------------------------------------------

#ifdef CONFIG_NSG
__root const CFG_HDR cfghdr_m191={CFG_LEVEL,"irDa",1,0};

__root const CFG_HDR cfghdr19_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int irda=1;

__root const CFG_HDR cfghdr19_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_irda=0;
__root const CFG_CBOX_ITEM cfgcbox19_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr19_3={CFG_UINT,"Номер картинки(вкл.)",0,0xFFF};
__root const unsigned int irda_icon=ICO_irda;

__root const CFG_HDR cfghdr19_4={CFG_UINT,"Номер картинки(передача)",0,0xFFF};
__root const unsigned int irda_trans_icon=ICO_irda_trans;

__root const CFG_HDR cfghdr19_5={CFG_CHECKBOX,"Отображать иконку выкл. ИК?",0,0};
__root const int irda_off=1;

__root const CFG_HDR cfghdr19_6={CFG_UINT,"Номер картинки(выкл. ИК)",0,0xFFF};
__root const unsigned int irda_off_icon=ICO_non;

__root const CFG_HDR cfghdr_m190={CFG_LEVEL,"",0,0};
#endif

//------------------------------------------------------------------------------

//------------------------------Колонки-----------------------------------------

#ifdef CONFIG_NSG
__root const CFG_HDR cfghdr_m201={CFG_LEVEL,"Колонки",1,0};

__root const CFG_HDR cfghdr20_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int colonki=1;

__root const CFG_HDR cfghdr20_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_colonki=0;
__root const CFG_CBOX_ITEM cfgcbox20_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr20_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int colonki_icon=ICO_non;

__root const CFG_HDR cfghdr_m200={CFG_LEVEL,"",0,0};
#endif

//------------------------------------------------------------------------------

//------------------------------Радио-------------------------------------------

#ifdef CONFIG_EL
__root const CFG_HDR cfghdr_m211={CFG_LEVEL,"Радио",1,0};

__root const CFG_HDR cfghdr21_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int radio=0;

__root const CFG_HDR cfghdr21_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_radio=0;
__root const CFG_CBOX_ITEM cfgcbox21_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr21_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int radio_icon=ICO_non;

__root const CFG_HDR cfghdr_m210={CFG_LEVEL,"",0,0};
#endif

//------------------------------------------------------------------------------

//------------------------------ProPlayer---------------------------------------

__root const CFG_HDR cfghdr_m221={CFG_LEVEL,"ProPlayer",1,0};

__root const CFG_HDR cfghdr_m221_1={CFG_LEVEL,"Громкость",1,0};

__root const CFG_HDR cfghdr22_1_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int volume_proplayer=1;

__root const CFG_HDR cfghdr22_2_1={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_provol=0;
__root const CFG_CBOX_ITEM cfgcbox22_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr22_3_1={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int volpro_icon=ICO_vol;

__root const CFG_HDR cfghdr_m220_1={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m221_2={CFG_LEVEL,"Статус",1,0};

__root const CFG_HDR cfghdr22_1_2={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int stat_proplayer=1;

__root const CFG_HDR cfghdr22_2_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_prostat=0;
__root const CFG_CBOX_ITEM cfgcbox22_2[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr22_3_2={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int statpro_icon=ICO_non;

__root const CFG_HDR cfghdr_m220_2={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m220={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------OBEX--------------------------------------------

__root const CFG_HDR cfghdr_m231={CFG_LEVEL,"OBEX",1,0};

__root const CFG_HDR cfghdr23_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int obex=0;

__root const CFG_HDR cfghdr23_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_obex=0;
__root const CFG_CBOX_ITEM cfgcbox23_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr23_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int obex_icon=ICO_non;

__root const CFG_HDR cfghdr_m230={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Набор номера------------------------------------

__root const CFG_HDR cfghdr_m241={CFG_LEVEL,"Набор номера",1,0};

__root const CFG_HDR cfghdr24_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int typing=0;

__root const CFG_HDR cfghdr24_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_typing=0;
__root const CFG_CBOX_ITEM cfgcbox24_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr24_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int typing_icon=ICO_non;

__root const CFG_HDR cfghdr_m240={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------Пользователь------------------------------------

__root const CFG_HDR cfghdr_m251={CFG_LEVEL,"Пользователь",1,0};

__root const CFG_HDR cfghdr25_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int user=0;

__root const CFG_HDR cfghdr25_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_user=0;
__root const CFG_CBOX_ITEM cfgcbox25_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr25_3={CFG_UINT,"Номер картинки",0,0xFFF};
__root const unsigned int user_icon=ICO_non;

__root const CFG_HDR cfghdr_m250={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
