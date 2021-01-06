/*
    GPSLogger Project
    Получение имён сот и управление кешем, ведение лога сот

*/

#ifndef _MINIGPS_LOGGER_H_
  #define _MINIGPS_LOGGER_H_

// Инициализировать кеш записей
void InitRamNetCache();

// Убить кеш записей
void KillRamNetCache();

// Удалить одну запись из кеша
void Del_From_Cache(unsigned short ci, unsigned short lac);

// Получить текущее местоположение из miniGPS-базы
// Строка выделяется функцией, необходимо освобождение после юзания
// в unsigned short *action возвращается действие для выполнения
// Строка возвращается в кодировке UTF-8
char *Get_Current_Location(char *action);

#endif

//EOL,OEF
