#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0 = {CFG_INT,"Клавиша вызова панели",0,100};
__root const int Button = 14;

__root const CFG_HDR cfghdr1 = {CFG_LEVEL, "Настройка вывода",1,0};

__root const CFG_HDR cfghdr1_1 = {8, "Цвет шрифта", 0, 0};
__root const char fontcolor[4] = {0, 0, 0, 64};

__root const CFG_HDR cfghdr1_2 = {8, "Цвет обводки шрифта", 0, 0};
__root const char outline[4] = {255, 255, 255, 64};

__root const CFG_HDR cfghdr1_3 = {7, "Позиция", 0, 0};
__root const int x = 1;
__root const int y = 40;

__root const CFG_HDR cfghdr1_4 = {CFG_INT, "Шрифт", 0, 100};
__root const int font=7;

__root const CFG_HDR cfghdr1_5 = {8, "Бэкграунд", 0, 0};
__root const char backcolor[4] = {0,0,0,64};

__root const CFG_HDR cfghdr1_6 = {8, "Line's color", 0, 0};
__root const char linecolor[4] = {0,0,255,64};

__root const CFG_HDR cfghdr1_7 = {CFG_STR_WIN1251, "D ", 0, 127};
__root const char description[128] = "ПС-117";

__root const CFG_HDR cfghdr1_0 = {CFG_LEVEL,"",0,0};

/// -=Неделя 1=- ///

__root const CFG_HDR cfghdr2 = {CFG_LEVEL, "Неделя 1", 1, 0};

///=Понедельник=///

__root const CFG_HDR cfghdr2_1 = {CFG_LEVEL, "Понедельник", 1, 0};

__root const CFG_HDR cfghdr10_1 = {CFG_STR_WIN1251,"Пара 1", 0, 127};
__root const char Pon11[128] = "";

__root const CFG_HDR cfghdr10_2 = {CFG_STR_WIN1251,"Пара 2", 0, 127};
__root const char Pon12[128] = "Культурология";

__root const CFG_HDR cfghdr10_3 = {CFG_STR_WIN1251,"Пара 3", 0, 127};
__root const char Pon13[128] = "Информатика";

__root const CFG_HDR cfghdr10_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Pon14[128] = "Математика";

__root const CFG_HDR cfghdr10_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Pon15[128] = "";

__root const CFG_HDR cfghdr10_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Pon16[128] = "";

__root const CFG_HDR cfghdr10_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Pon17[128] = "";

__root const CFG_HDR cfghdr2_1_0 = {CFG_LEVEL, "", 0, 0};

///=Вторник=///
__root const CFG_HDR cfghdr2_2 = {CFG_LEVEL, "Вторник", 1, 0};

__root const CFG_HDR cfghdr11_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Vt11[128] = "Физика";

__root const CFG_HDR cfghdr11_2 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Vt12[128] = "Математика";

__root const CFG_HDR cfghdr11_3 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Vt13[128] = "Физ-ра";

__root const CFG_HDR cfghdr11_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Vt14[128] = "";

__root const CFG_HDR cfghdr11_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Vt15[128] = "";

__root const CFG_HDR cfghdr11_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Vt16[128] = "";

__root const CFG_HDR cfghdr11_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Vt17[128] = "";

__root const CFG_HDR cfghdr2_2_0 = {CFG_LEVEL, "", 0, 0};

///=Среда=///

__root const CFG_HDR cfghdr2_3 = {CFG_LEVEL, "Среда", 1, 0};

__root const CFG_HDR cfghdr12_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Sr11[128] = "Инж. графика";

__root const CFG_HDR cfghdr12_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Sr12[128] = "Химия";

__root const CFG_HDR cfghdr12_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Sr13[128] = "Химия";

__root const CFG_HDR cfghdr12_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Sr14[128] = "";

__root const CFG_HDR cfghdr12_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Sr15[128] = "";

__root const CFG_HDR cfghdr12_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Sr16[128] = "";

__root const CFG_HDR cfghdr12_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Sr17[128] = "";

__root const CFG_HDR cfghdr2_3_0 = {CFG_LEVEL, "", 0, 0};

///=Четверг=///

__root const CFG_HDR cfghdr2_4 = {CFG_LEVEL, "Четверг", 1, 0};

__root const CFG_HDR cfghdr13_1 = {CFG_STR_WIN1251,"Пара 1", 0, 127};
__root const char Ch11[128] = "Инж.граф";

__root const CFG_HDR cfghdr13_2 = {CFG_STR_WIN1251,"Пара 2", 0, 127};
__root const char Ch12[128] = "Информатика";

__root const CFG_HDR cfghdr13_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Ch13[128] = "Физ-ра";

__root const CFG_HDR cfghdr13_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Ch14[128] = "";

__root const CFG_HDR cfghdr13_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Ch15[128] = "";

__root const CFG_HDR cfghdr13_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Ch16[128] = "";

__root const CFG_HDR cfghdr13_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Ch17[128] = "";

__root const CFG_HDR cfghdr2_4_0 = {CFG_LEVEL, "", 0, 0};

//=Пятницa=//

__root const CFG_HDR cfghdr2_5 = {CFG_LEVEL, "Пятница", 1, 0};

__root const CFG_HDR cfghdr14_1 = {CFG_STR_WIN1251,"Пара 1", 0, 127};
__root const char Pt11[128] = "Математика";

__root const CFG_HDR cfghdr14_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Pt12[128] = "Физика";

__root const CFG_HDR cfghdr14_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Pt13[128] = "";

__root const CFG_HDR cfghdr14_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Pt14[128] = "";

__root const CFG_HDR cfghdr14_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Pt15[128] = "";

__root const CFG_HDR cfghdr14_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Pt16[128] = "";

__root const CFG_HDR cfghdr14_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Pt17[128] = "";

__root const CFG_HDR cfghdr2_5_0 = {CFG_LEVEL, "", 0, 0};

//=Суббота=//

__root const CFG_HDR cfghdr2_6 = {CFG_LEVEL, "Суббота", 1, 0};

__root const CFG_HDR cfghdr15_1 = {CFG_STR_WIN1251,"Пара 1", 0, 127};
__root const char Su11[128] = "История";

__root const CFG_HDR cfghdr15_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Su12[128] = "Математика";

__root const CFG_HDR cfghdr15_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Su13[128] = "";

__root const CFG_HDR cfghdr15_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Su14[128] = "";

__root const CFG_HDR cfghdr15_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Su15[128] = "";

__root const CFG_HDR cfghdr15_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Su16[128] = "";

__root const CFG_HDR cfghdr15_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Su17[128] = "";

__root const CFG_HDR cfghdr2_6_0 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr2_0 = {CFG_LEVEL, "", 0, 0};

/// -=Неделя 2=- ///

__root const CFG_HDR cfghdr3 = {CFG_LEVEL, "Неделя 2", 1, 0};

///=Понедельник=2///

__root const CFG_HDR cfghdr3_1 = {CFG_LEVEL, "Понедельник", 1, 0};

__root const CFG_HDR cfghdr21_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Pon21[128] = "";

__root const CFG_HDR cfghdr21_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Pon22[128] = "";

__root const CFG_HDR cfghdr21_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Pon23[128] = "";

__root const CFG_HDR cfghdr21_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Pon24[128] = "Математика";

__root const CFG_HDR cfghdr21_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Pon25[128] = "";

__root const CFG_HDR cfghdr21_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Pon26[128] = "";

__root const CFG_HDR cfghdr21_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Pon27[128] = "";

__root const CFG_HDR cfghdr3_1_0 = {CFG_LEVEL, "", 0, 0};

///=Вторник=2///
__root const CFG_HDR cfghdr3_2 = {CFG_LEVEL, "Вторник", 1, 0};

__root const CFG_HDR cfghdr22_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Vt21[128] = "Физика";

__root const CFG_HDR cfghdr22_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Vt22[128] = "Математика";

__root const CFG_HDR cfghdr22_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Vt23[128] = "Физ-ра";

__root const CFG_HDR cfghdr22_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Vt24[128] = "";

__root const CFG_HDR cfghdr22_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Vt25[128] = "";

__root const CFG_HDR cfghdr22_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Vt26[128] = "";

__root const CFG_HDR cfghdr22_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Vt27[128] = "";

__root const CFG_HDR cfghdr3_2_0 = {CFG_LEVEL, "", 0, 0};

///=Среда=2///

__root const CFG_HDR cfghdr3_3 = {CFG_LEVEL, "Среда", 1, 0};

__root const CFG_HDR cfghdr23_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Sr21[128] = "Инж.графика";

__root const CFG_HDR cfghdr23_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Sr22[128] = "Информатика";

__root const CFG_HDR cfghdr23_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Sr23[128] = "Химия";

__root const CFG_HDR cfghdr23_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Sr24[128] = "";

__root const CFG_HDR cfghdr23_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Sr25[128] = "";

__root const CFG_HDR cfghdr23_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Sr26[128] = "";

__root const CFG_HDR cfghdr23_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Sr27[128] = "";

__root const CFG_HDR cfghdr3_3_0 = {CFG_LEVEL, "", 0, 0};

///=Четверг=2///

__root const CFG_HDR cfghdr3_4 = {CFG_LEVEL, "Четверг", 1, 0};

__root const CFG_HDR cfghdr24_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Ch21[128] = "Инж.графика";

__root const CFG_HDR cfghdr24_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Ch22[128] = "Информатика";

__root const CFG_HDR cfghdr24_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Ch23[128] = "Физ-ра";

__root const CFG_HDR cfghdr24_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Ch24[128] = "";

__root const CFG_HDR cfghdr24_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Ch25[128] = "";

__root const CFG_HDR cfghdr24_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Ch26[128] = "";

__root const CFG_HDR cfghdr24_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Ch27[128] = "";

__root const CFG_HDR cfghdr3_4_0 = {CFG_LEVEL, "", 0, 0};

//=Пятницa=2//

__root const CFG_HDR cfghdr3_5 = {CFG_LEVEL, "Пятница", 1, 0};

__root const CFG_HDR cfghdr25_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Pt21[128] = "Математика";

__root const CFG_HDR cfghdr25_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Pt22[128] = "Информатика";

__root const CFG_HDR cfghdr25_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Pt23[128] = "";

__root const CFG_HDR cfghdr25_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Pt24[128] = "";

__root const CFG_HDR cfghdr25_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Pt25[128] = "";

__root const CFG_HDR cfghdr25_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Pt26[128] = "";

__root const CFG_HDR cfghdr25_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Pt27[128] = "";

__root const CFG_HDR cfghdr3_5_0 = {CFG_LEVEL, "", 0, 0};

//=Суббота=2//

__root const CFG_HDR cfghdr3_6 = {CFG_LEVEL, "Суббота", 1, 0};

__root const CFG_HDR cfghdr26_1 = {CFG_STR_WIN1251, "Пара 1", 0, 127};
__root const char Su21[128] = "Культурология";

__root const CFG_HDR cfghdr26_2 = {CFG_STR_WIN1251, "Пара 2", 0, 127};
__root const char Su22[128] = "Математика";

__root const CFG_HDR cfghdr26_3 = {CFG_STR_WIN1251, "Пара 3", 0, 127};
__root const char Su23[128] = "";

__root const CFG_HDR cfghdr26_4 = {CFG_STR_WIN1251, "Пара 4", 0, 127};
__root const char Su24[128] = "";

__root const CFG_HDR cfghdr26_5 = {CFG_STR_WIN1251, "Пара 5", 0, 127};
__root const char Su25[128] = "";

__root const CFG_HDR cfghdr26_6 = {CFG_STR_WIN1251, "Пара 6", 0, 127};
__root const char Su26[128] = "";

__root const CFG_HDR cfghdr26_7 = {CFG_STR_WIN1251, "Пара 7", 0, 127};
__root const char Su27[128] = "";

__root const CFG_HDR cfghdr3_6_0 = {CFG_LEVEL, "", 0, 0};


__root const CFG_HDR cfghdr3_0 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr4 = {CFG_CBOX, "Неделя", 0, 2};
__root const int CurWeek=0;
__root const CFG_CBOX_ITEM CBOX1[2]={"1","2"};

/*
__root const CFG_HDR cfghdr0={8,"Цвет шрифта",0,0};
__root const char fontcolor[4]={00,00,00,64};

__root const CFG_HDR cfghdr0_1={8,"Цвет обводки",0,0};
__root const char outlinecolor[4]={255,255,255,64};


__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"Время",1,0};

__root const CFG_HDR cfghdr1_10={CFG_TIME,"Показывать с",0,0};
__root const TTime ShowS={5,30};

__root const CFG_HDR cfghdr1_11={CFG_TIME,"Покажывать до",0,0};
__root const TTime ShowDo={16,0};

__root const CFG_HDR cfghdr1_1={CFG_TIME,"Первая пара",0,0};
__root const TTime Para1T={8,0};

__root const CFG_HDR cfghdr1_5={CFG_TIME,"Конец",0,0};
__root const TTime Para1C={9,30};

__root const CFG_HDR cfghdr1_2={CFG_TIME,"Вторая пара",0,0};
__root const TTime Para2T={9,45};

__root const CFG_HDR cfghdr1_6={CFG_TIME,"Конец",0,0};
__root const TTime Para2C={11,20};

__root const CFG_HDR cfghdr1_3={CFG_TIME,"Третья пара",0,0};
__root const TTime Para3T={11,30};

__root const CFG_HDR cfghdr1_7={CFG_TIME,"Конец",0,0};
__root const TTime Para3C={13,15};

__root const CFG_HDR cfghdr1_4={CFG_TIME,"Четвертая пара",0,0};
__root const TTime Para4T={13,30};

__root const CFG_HDR cfghdr1_8={CFG_TIME,"Конец",0,0};
__root const TTime Para4C={15,15};

__root const CFG_HDR cfghdr_m1={CFG_LEVEL,"",0,0};
/////////////
__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"Понедельник",1,0};

__root const CFG_HDR cfghdr4_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char PonPara1[128]="Культурология 909";

__root const CFG_HDR cfghdr4_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char PonPara2[128]="Информатика 712";

__root const CFG_HDR cfghdr4_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char PonPara3[128]="Математика 913";

__root const CFG_HDR cfghdr4_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char PonPara4[128]="";

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"",0,0};

/////////////
__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"Вторник",1,0};

__root const CFG_HDR cfghdr6_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char VPara1[128]="Физика 443";

__root const CFG_HDR cfghdr6_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char VPara2[128]="Математ 632";

__root const CFG_HDR cfghdr6_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char VPara3[128]="физ-ра";

__root const CFG_HDR cfghdr6_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char VPara4[128]="";

__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"",0,0};

/////////
__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"Среда",1,0};

__root const CFG_HDR cfghdr8_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char SrPara1[128]="Инжю граф. 590";

__root const CFG_HDR cfghdr8_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char SrPara2[128]="Химия 419";

__root const CFG_HDR cfghdr8_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char SrPara3[128]="Химия 428";

__root const CFG_HDR cfghdr8_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char SrPara4[128]="";

__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"",0,0};

//////////

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"Четверг",1,0};

__root const CFG_HDR cfghdr10_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char ChPara1[128]="Инж. граф 598";

__root const CFG_HDR cfghdr10_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char ChPara2[128]="Информатика 705";

__root const CFG_HDR cfghdr10_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char ChPara3[128]="Физ-ра";

__root const CFG_HDR cfghdr10_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char ChPara4[128]="";

__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"",0,0};

///////
__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"Пятница",1,0};


__root const CFG_HDR cfghdr12_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char PtPara1[128]="Математ 913";

__root const CFG_HDR cfghdr12_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char PtPara2[128]="Физика 1002";

__root const CFG_HDR cfghdr12_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char PtPara3[128]="";

__root const CFG_HDR cfghdr12_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char PtPara4[128]="";

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};

////////

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"Суббота",1,0};

__root const CFG_HDR cfghdr14_1={CFG_STR_WIN1251,"Пара 1",0,127};
__root const char SuPara1[128]="История 434";

__root const CFG_HDR cfghdr14_2={CFG_STR_WIN1251,"Пара 2",0,127};
__root const char SuPara2[128]="Математ 434";

__root const CFG_HDR cfghdr14_3={CFG_STR_WIN1251,"Пара 3",0,127};
__root const char SuPara3[128]="Математика";

__root const CFG_HDR cfghdr14_4={CFG_STR_WIN1251,"Пара 4",0,127};
__root const char SuPara4[128]="";

__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"",0,0};
////

__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"Настройки вывода",1,0};

__root const CFG_HDR cfghdr16_1={7,"x,y",0,0};
__root const int x=1;
__root const int y=101;

__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"Активен",0,2};
__root const int active=1;

__root const CFG_HDR cfghdr1={CFG_CBOX,"Кол-во ярлычков",0,15};
__root const int count=14;
__root const CFG_CBOX_ITEM cfgcbox2[15]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};

////////////
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Ярлык 1",1,0};

__root const CFG_HDR cfghdr11_1={CFG_CBOX,"Тип",0,3};
__root const int type1=0;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"файл","шорткат","энтрипоинт"};


__root const CFG_HDR cfghdr2_1={CFG_STR_UTF8,"Иконка 1",0,127};
__root const char pic1[128]="0:\\Zbin\\IdleLinks\\icq.png";

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"Файл 1/шорткат/энтрипоинт",0,127};
__root const char file1[128]="0:\\Zbin\\naticq\\naticq.elf";

__root const CFG_HDR cfghdr2_3={7,"Координаты 1",0,0};
__root const unsigned int x1=0;
__root const unsigned int y1=60;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
/////////////////

__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Ярлык 2",1,0};

__root const CFG_HDR cfghdr12_1={CFG_CBOX,"Тип",0,3};
__root const int type2=0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"файл","шорткат","энтрипоинт"};


__root const CFG_HDR cfghdr3_1={CFG_STR_UTF8,"Иконка 2",0,127};
__root const char pic2[128]="0:\\Zbin\\IdleLinks\\tc.png";

__root const CFG_HDR cfghdr3_2={CFG_STR_UTF8,"Файл 2/шорткат/энтрипоинт",0,127};
__root const char file2[128]="0:\\Zbin\\screensavers\\screensaver.elf";

__root const CFG_HDR cfghdr3_3={7,"Координаты 2",0,0};
__root const unsigned int x2=20;
__root const unsigned int y2=60;

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};
///////////////////
__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"Ярлык 3",1,0};

__root const CFG_HDR cfghdr13_1={CFG_CBOX,"Тип",0,3};
__root const int type3=0;
__root const CFG_CBOX_ITEM cfgcbox6[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr4_1={CFG_STR_UTF8,"Иконка 3",0,127};
__root const char pic3[128]="0:\\Zbin\\IdleLinks\\ms.png";

__root const CFG_HDR cfghdr4_2={CFG_STR_UTF8,"Файл 3/шорткат/энтрипоинт",0,127};
__root const char file3[128]="0:\\Zbin\\MyStuff\\Stuff.elf";

__root const CFG_HDR cfghdr4_3={7,"Координаты 3",0,0};
__root const unsigned int x3=40;
__root const unsigned int y3=60;

__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"",0,0};
////////////////
__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"Ярлык 4",1,0};

__root const CFG_HDR cfghdr14_1={CFG_CBOX,"Тип",0,3};
__root const int type4=2;
__root const CFG_CBOX_ITEM cfgcbox7[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr5_1={CFG_STR_UTF8,"Иконка 4",0,127};
__root const char pic4[128]="0:\\Zbin\\IdleLinks\\sj.png";

__root const CFG_HDR cfghdr5_2={CFG_STR_UTF8,"Файл 4/шорткат/энтрипоинт",0,127};
__root const char file4[128]="0xA08DF43B";

__root const CFG_HDR cfghdr5_3={7,"Координаты 4",0,0};
__root const unsigned int x4=60;
__root const unsigned int y4=60;

__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"Ярлык 5",1,0};

__root const CFG_HDR cfghdr15_1={CFG_CBOX,"Тип",0,3};
__root const int type5=1;
__root const CFG_CBOX_ITEM cfgcbox8[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr6_1={CFG_STR_UTF8,"Иконка 5",0,127};
__root const char pic5[128]="0:\\Zbin\\IdleLinks\\ir.png";

__root const CFG_HDR cfghdr6_2={CFG_STR_UTF8,"Файл 5/шорткат/энтрипоинт",0,127};
__root const char file5[128]="STUP_CONCT_IRDA";

__root const CFG_HDR cfghdr6_3={7,"Координаты 5",0,0};
__root const unsigned int x5=80;
__root const unsigned int y5=60;

__root const CFG_HDR cfghdr_m19={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m22={CFG_LEVEL,"Ярлык 6",1,0};


__root const CFG_HDR cfghdr16_1={CFG_CBOX,"Тип",0,3};
__root const int type6=1;
__root const CFG_CBOX_ITEM cfgcbox9[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr7_1={CFG_STR_UTF8,"Иконка 6",0,127};
__root const char pic6[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr7_2={CFG_STR_UTF8,"Файл 6/шорткат",0,127};
__root const char file6[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr7_3={7,"Координаты 6",0,0};
__root const unsigned int x6=0;
__root const unsigned int y6=80;

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
/////////
__root const CFG_HDR cfghdr_m26={CFG_LEVEL,"Ярлык 7",1,0};


__root const CFG_HDR cfghdr17_1={CFG_CBOX,"Тип",0,3};
__root const int type7=1;
__root const CFG_CBOX_ITEM cfgcbox10[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr8_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic7[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr8_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file7[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr8_3={7,"Координаты ",0,0};
__root const unsigned int x7=20;
__root const unsigned int y7=80;

__root const CFG_HDR cfghdr_m25={CFG_LEVEL,"",0,0};

/////////////
__root const CFG_HDR cfghdr_m28={CFG_LEVEL,"Ярлык 8",1,0};


__root const CFG_HDR cfghdr18_1={CFG_CBOX,"Тип",0,3};
__root const int type8=1;
__root const CFG_CBOX_ITEM cfgcbox11[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr9_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic8[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr9_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file8[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr9_3={7,"Координаты ",0,0};
__root const unsigned int x8=40;
__root const unsigned int y8=80;

__root const CFG_HDR cfghdr_m27={CFG_LEVEL,"",0,0};

/////////
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"Ярлык 9",1,0};


__root const CFG_HDR cfghdr19_1={CFG_CBOX,"Тип",0,3};
__root const int type9=1;
__root const CFG_CBOX_ITEM cfgcbox12[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr10_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic9[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr10_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file9[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr10_3={7,"Координаты ",0,0};
__root const unsigned int x9=60;
__root const unsigned int y9=80;

__root const CFG_HDR cfghdr_m29={CFG_LEVEL,"",0,0};


///////
__root const CFG_HDR cfghdr_m32={CFG_LEVEL,"Ярлык 10",1,0};


__root const CFG_HDR cfghdr20_1={CFG_CBOX,"Тип",0,3};
__root const int type10=1;
__root const CFG_CBOX_ITEM cfgcbox13[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr21_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic10[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr21_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file10[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr21_3={7,"Координаты ",0,0};
__root const unsigned int x10=80;
__root const unsigned int y10=80;

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};
////////

__root const CFG_HDR cfghdr_m34={CFG_LEVEL,"Ярлык 11",1,0};


__root const CFG_HDR cfghdr22_5={CFG_CBOX,"Тип",0,3};
__root const int type11=1;
__root const CFG_CBOX_ITEM cfgcbox14[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr22_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic11[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr22_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file11[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr22_3={7,"Координаты ",0,0};
__root const unsigned int x11=0;
__root const unsigned int y11=100;

__root const CFG_HDR cfghdr_m33={CFG_LEVEL,"",0,0};

////////
__root const CFG_HDR cfghdr_m36={CFG_LEVEL,"Ярлык 12",1,0};


__root const CFG_HDR cfghdr23_5={CFG_CBOX,"Тип",0,3};
__root const int type12=1;
__root const CFG_CBOX_ITEM cfgcbox15[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr23_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic12[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr23_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file12[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr23_3={7,"Координаты ",0,0};
__root const unsigned int x12=20;
__root const unsigned int y12=100;

__root const CFG_HDR cfghdr_m35={CFG_LEVEL,"",0,0};
////////
__root const CFG_HDR cfghdr_m38={CFG_LEVEL,"Ярлык 13",1,0};


__root const CFG_HDR cfghdr24_5={CFG_CBOX,"Тип",0,3};
__root const int type13=1;
__root const CFG_CBOX_ITEM cfgcbox16[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr24_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic13[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr24_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file13[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr24_3={7,"Координаты ",0,0};
__root const unsigned int x13=40;
__root const unsigned int y13=100;

__root const CFG_HDR cfghdr_m37={CFG_LEVEL,"",0,0};

///////
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"Ярлык 14",1,0};


__root const CFG_HDR cfghdr25_5={CFG_CBOX,"Тип",0,3};
__root const int type14=1;
__root const CFG_CBOX_ITEM cfgcbox17[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr25_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic14[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr25_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file14[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr25_3={7,"Координаты ",0,0};
__root const unsigned int x14=60;
__root const unsigned int y14=100;

__root const CFG_HDR cfghdr_m39={CFG_LEVEL,"",0,0};
///////////
__root const CFG_HDR cfghdr_m42={CFG_LEVEL,"Ярлык 15",1,0};


__root const CFG_HDR cfghdr26_5={CFG_CBOX,"Тип",0,3};
__root const int type15=1;
__root const CFG_CBOX_ITEM cfgcbox18[3]={"файл","шорткат","энтрипоинт"};

__root const CFG_HDR cfghdr26_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic15[128]="0:\\Zbin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr26_2={CFG_STR_UTF8,"Файл/шорткат",0,127};
__root const char file15[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr26_3={7,"Координаты ",0,0};
__root const unsigned int x15=80;
__root const unsigned int y15=100;

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};

/////
__root const CFG_HDR cfghdr_m24={CFG_LEVEL,"Настройка выбора",1,0};
__root const CFG_HDR cfghdr8={CFG_CBOX,"Выбор",0,2};
__root const int vybor=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Цветом","Картинкой"};

__root const CFG_HDR cfghdr51={CFG_STR_UTF8,"Картинка выбора",0,127};
__root const char chpic[128]="0:\\Zbin\\IdleLinks\\choose.png";

__root const CFG_HDR cfghdr121={8,"Цвет выбора",0,0};
__root const char cl[4]={185,113,13,50};

__root const CFG_HDR cfghdr122={8,"Цвет рамки",0,0};
__root const char frcol[4]={255,255,255,100};

__root const CFG_HDR cfghdr123={CFG_STR_UTF8,"Путь к эльфу IdleLinks",0,127};
__root const char put[128]="0:\\Zbin\\IdleLinks\\IdleLinks.elf";

__root const CFG_HDR cfghdr124={CFG_UINT,"up/down изменение позиции",0,7};
__root const unsigned int izpoz=5;

__root const CFG_HDR cfghdr125={CFG_CHECKBOX,"Сохранять позицию",0,2};
__root const  int issavepos=1;

__root const CFG_HDR cfghdr_m23={CFG_LEVEL,"",0,0};
__root const int sel=1;

*/


/////
  /*
  0-Left_SOFT
  1-Right_soft
  2-up
  3-down
  4-left
  5-right
  6-vol up
  7-vol down
  */
