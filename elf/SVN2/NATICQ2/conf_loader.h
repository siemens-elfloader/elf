/*
��������� ������������
(c) Rst7, Kibab
 ������������ �������� ������� � ������������� ������� �������������
*/
#ifndef _CONFLOADER_H_
  #define _CONFLOADER_H_

// ������� ����������� ����� ���������� � ���������� ������������
void InitConfig(const char *config);

extern char *successed_config_filename;
int SaveConfigData(const char *fname);

#endif
