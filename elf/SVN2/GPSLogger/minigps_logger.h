/*
    GPSLogger Project
    ��������� ��� ��� � ���������� �����, ������� ���� ���

*/

#ifndef _MINIGPS_LOGGER_H_
  #define _MINIGPS_LOGGER_H_

// ���������������� ��� �������
void InitRamNetCache();

// ����� ��� �������
void KillRamNetCache();

// ������� ���� ������ �� ����
void Del_From_Cache(unsigned short ci, unsigned short lac);

// �������� ������� �������������� �� miniGPS-����
// ������ ���������� ��������, ���������� ������������ ����� ������
// � unsigned short *action ������������ �������� ��� ����������
// ������ ������������ � ��������� UTF-8
char *Get_Current_Location(char *action);

#endif

//EOL,OEF
