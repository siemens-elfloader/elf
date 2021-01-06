/*
* Ping-Pong 2009 - 2010
* lang
* (c) Danil_e71
*/

#include"C:\arm\inc\swilib.h"
#include "lang.h"

void lgpInitLangPack()
{
  switch(langenru)
  {
case 1:
{
strcpy(lang[0],"Ping-Pong");
strcpy(lang[1],"Newgame");
strcpy(lang[2],"Newgame >");
strcpy(lang[3],"< Continue >");
strcpy(lang[4],"< Save");
strcpy(lang[5],"Load >");
strcpy(lang[6],"< Lives");
strcpy(lang[7],"< Career");
strcpy(lang[8],"Points >");
strcpy(lang[9],"Best Record");
strcpy(lang[10],"Preferences");
strcpy(lang[11],"Exit");
strcpy(lang[12],"Parametrs of game");
strcpy(lang[13],"Image");
strcpy(lang[14],"Path");
strcpy(lang[15],"Complexity");
strcpy(lang[16],"Easy >");
strcpy(lang[17],"< Normal >");
strcpy(lang[18],"< Hard");
strcpy(lang[19],"Speed");
strcpy(lang[20],"Slow >");
strcpy(lang[21],"< Normal >");
strcpy(lang[22],"< Fast >");
strcpy(lang[23],"< Veryfast");
strcpy(lang[24],"Lives");
strcpy(lang[25],"Selected for the points");
strcpy(lang[26],"Sounds");
strcpy(lang[27],"Customize");
strcpy(lang[28],"Inc. sound?");
strcpy(lang[29],"No >");
strcpy(lang[30],"< Yes");
strcpy(lang[31],"< Sounds >");
strcpy(lang[32],"< Music");
strcpy(lang[33],"Volume");
strcpy(lang[34],"Vibration");
strcpy(lang[35],"records");
strcpy(lang[36],"< Empty >");
strcpy(lang[37],"Scavenged");
strcpy(lang[38],"Loading.");
strcpy(lang[39],"Loading..");
strcpy(lang[40],"Loading...");
strcpy(lang[41],"Loading....");
strcpy(lang[42],"loaded");
strcpy(lang[43],"Notfound!");
strcpy(lang[44],"Error!Missing graphics!");
strcpy(lang[45],"The game loaded");
strcpy(lang[46],"Error!\nMissing graphics!\n\nThere quired path\n\n");
strcpy(lang[47],"lost:(");
strcpy(lang[48],"You won:)");
strcpy(lang[49],"Press'0'");
strcpy(lang[50],"pause");
strcpy(lang[51],"your goal(");
strcpy(lang[52],"PC loser:-)");
strcpy(lang[53],"can not save data.sys!Check path in the config!");
strcpy(lang[54],"can not load data.sys!Check path in the config!");
strcpy(lang[55],"The game successfully saved!");
strcpy(lang[56],"can not save savedata.pp!Check path in the config!");
strcpy(lang[57],"The game has successfully loaded!");
strcpy(lang[58],"can not load savedata.pp!Check the path in the config!");
break;
}
default:
{
strcpy(lang[0],"Пинг-Понг");
strcpy(lang[1],"Новая игра");
strcpy(lang[2],"Новая игра >");
strcpy(lang[3],"< Продолжить >");
strcpy(lang[4],"< Сохранить");
strcpy(lang[5],"Загрузить >");
strcpy(lang[6],"< Жизни");
strcpy(lang[7],"< Карьера");
strcpy(lang[8],"Очки >");
strcpy(lang[9],"Лучшие рекорды");
strcpy(lang[10],"Настройки");
strcpy(lang[11],"Выход");
strcpy(lang[12],"Параметры игры");
strcpy(lang[13],"Графика");
strcpy(lang[14],"Путь");
strcpy(lang[15],"Сложность");
strcpy(lang[16],"Легко >");
strcpy(lang[17],"< Средне >");
strcpy(lang[18],"< Сложно");
strcpy(lang[19],"Скорость");
strcpy(lang[20],"Медленно >");
strcpy(lang[21],"< Средне >");
strcpy(lang[22],"< Быстро >");
strcpy(lang[23],"< Очень быстро");
strcpy(lang[24],"Жизни");
strcpy(lang[25],"Выбран режим на очки");
strcpy(lang[26],"Звуки");
strcpy(lang[27],"Настроить");
strcpy(lang[28],"Вкл. звук?");
strcpy(lang[29],"Нет >");
strcpy(lang[30],"< Да");
strcpy(lang[31],"< Звуки >");
strcpy(lang[32],"< Музыка");
strcpy(lang[33],"Громкость");
strcpy(lang[34],"Вибрация");
strcpy(lang[35],"Рекорды");
strcpy(lang[36],"< Пусто >");
strcpy(lang[37],"Очищено");
strcpy(lang[38],"Загрузка.");
strcpy(lang[39],"Загрузка..");
strcpy(lang[40],"Загрузка...");
strcpy(lang[41],"Загрузка....");
strcpy(lang[42],"загружен");
strcpy(lang[43],"не найден!");
strcpy(lang[44],"Ошибка!Отсутствует графика!");
strcpy(lang[45],"Игра загружена");
strcpy(lang[46],"Ошибка!\nОтсутствует графика!\n\nТребуемый путь\r\n");
strcpy(lang[47],"Проиграл");
strcpy(lang[48],"выиграл");
strcpy(lang[49],"Нажмите '0'");
strcpy(lang[50],"пауза");
strcpy(lang[51],"тебе гол");
strcpy(lang[52],"комп потерял шарик:-)");
strcpy(lang[53],"немогу сохранить data.sys!Проверьте путь в конфиге!");
strcpy(lang[54],"немогу загрузить data.sys!Проверьте путь в конфиге!");
strcpy(lang[55],"Игра успешно сохранена!");
strcpy(lang[56],"немогу сохранить savedata.pp!Проверьте путь в конфиге!");
strcpy(lang[57],"Игра успешно загружена!");
strcpy(lang[58],"не могу загрузить savedata.pp!Проверьте путь в конфиге!");
break;
}
}
}
