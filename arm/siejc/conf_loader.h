/*
Загрузчик конфигурации
(c) Rst7, Kibab
 Осуществляет загрузку конфига и предоставляет функции инициализации
*/
#ifndef _CONFLOADER_H_
  #define _CONFLOADER_H_

// Вызвать обязательно перед обращением к переменным конфигурации
void InitConfig(char* fname);
extern char * successed_config_filename;
int SaveConfigData(const char *fname);
void InitIconSet(void);
int LoadColorSetData(const char *fname);
int SaveColorSetData(const char * fname);
#endif
