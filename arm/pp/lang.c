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
strcpy(lang[0],"����-����");
strcpy(lang[1],"����� ����");
strcpy(lang[2],"����� ���� >");
strcpy(lang[3],"< ���������� >");
strcpy(lang[4],"< ���������");
strcpy(lang[5],"��������� >");
strcpy(lang[6],"< �����");
strcpy(lang[7],"< �������");
strcpy(lang[8],"���� >");
strcpy(lang[9],"������ �������");
strcpy(lang[10],"���������");
strcpy(lang[11],"�����");
strcpy(lang[12],"��������� ����");
strcpy(lang[13],"�������");
strcpy(lang[14],"����");
strcpy(lang[15],"���������");
strcpy(lang[16],"����� >");
strcpy(lang[17],"< ������ >");
strcpy(lang[18],"< ������");
strcpy(lang[19],"��������");
strcpy(lang[20],"�������� >");
strcpy(lang[21],"< ������ >");
strcpy(lang[22],"< ������ >");
strcpy(lang[23],"< ����� ������");
strcpy(lang[24],"�����");
strcpy(lang[25],"������ ����� �� ����");
strcpy(lang[26],"�����");
strcpy(lang[27],"���������");
strcpy(lang[28],"���. ����?");
strcpy(lang[29],"��� >");
strcpy(lang[30],"< ��");
strcpy(lang[31],"< ����� >");
strcpy(lang[32],"< ������");
strcpy(lang[33],"���������");
strcpy(lang[34],"��������");
strcpy(lang[35],"�������");
strcpy(lang[36],"< ����� >");
strcpy(lang[37],"�������");
strcpy(lang[38],"��������.");
strcpy(lang[39],"��������..");
strcpy(lang[40],"��������...");
strcpy(lang[41],"��������....");
strcpy(lang[42],"��������");
strcpy(lang[43],"�� ������!");
strcpy(lang[44],"������!����������� �������!");
strcpy(lang[45],"���� ���������");
strcpy(lang[46],"������!\n����������� �������!\n\n��������� ����\r\n");
strcpy(lang[47],"��������");
strcpy(lang[48],"�������");
strcpy(lang[49],"������� '0'");
strcpy(lang[50],"�����");
strcpy(lang[51],"���� ���");
strcpy(lang[52],"���� ������� �����:-)");
strcpy(lang[53],"������ ��������� data.sys!��������� ���� � �������!");
strcpy(lang[54],"������ ��������� data.sys!��������� ���� � �������!");
strcpy(lang[55],"���� ������� ���������!");
strcpy(lang[56],"������ ��������� savedata.pp!��������� ���� � �������!");
strcpy(lang[57],"���� ������� ���������!");
strcpy(lang[58],"�� ���� ��������� savedata.pp!��������� ���� � �������!");
break;
}
}
}
