/*
Загрузчик конфигурации
(c) Rst7, Kibab
 Осуществляет загрузку конфига и предоставляет функции инициализации
*/
#ifndef _CONFLOADER_H_
  #define _CONFLOADER_H_

// Вызвать обязательно перед обращением к переменным конфигурации
void InitConfig();

// Вызвать с указателем на бинарный профиль, чтобы заполнить его данными
// из конфига
void FillProfile(char *profile);

// Константы смещений данных в бинарном профиле
#define coIntName   0x00   // внутреннее имя профиля
#define coName      0x35   // имя профиля
#define coAPN_name  0x58   // расположение имени точки доступа
#define coDNS       0xA1   // Смещение IP-адреса
#define coDNS_flag  0xA8   // Флаг наличия DNS
#define coLogin     0x1AD  // имени пользователя точки доступа
#define coPass      0x1E0  // пароля точки доступа
#define coTimeout   0x190  // времени разъединения

#endif
