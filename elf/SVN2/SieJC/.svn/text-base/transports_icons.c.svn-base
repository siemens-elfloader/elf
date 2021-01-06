#include "../inc/swilib.h"
#include "string_util.h"
#include "main.h"
#include "transports_icons.h"

extern const char PATH_TO_PIC[];
const char transports_img_folder[] = "transports\\";
static TransportIconsList * til_top = NULL;

/*
  Загрузить из папки "..\img\transports\" все папки с иконками транспортов.
*/
void LoadTranspostIconsList()
{
  DIR_ENTRY de;
  TransportIconsList * til;
  unsigned int err = NULL;
  char * tr_folder = malloc(strlen(PATH_TO_PIC) + 32);
  strcpy(tr_folder, PATH_TO_PIC);
  strcat(tr_folder, transports_img_folder);
  if (isdir(tr_folder, &err)) // Проверяем есть ли вообще папка "transports"
  {
    strcat(tr_folder, "*.*");
    if (FindFirstFile(&de, tr_folder, &err))
    {
      do
      {
        if (de.file_attr & FA_DIRECTORY) // Нашли папку
        {
          til = malloc(sizeof(TransportIconsList)); // Создаем новый список
          strcpy(til->name, de.file_name); // Копируем имя папки в список
          til->next = NULL;
          if (til_top)
          {
            TransportIconsList * til_r = (TransportIconsList *)&til_top;
            TransportIconsList * til_t = til_top;
            while(stricmp(til_t->name, til->name) < 0)
            {
              til_r = til_t;
              til_t = til_t->next;
              if (!til_t) break;
            }
            til->next = til_t;
            til_r->next = til;
          }
          else
            til_top = til;
        }
      }
      while(FindNextFile(&de, &err));
    }
    FindClose(&de, &err);
  }
  mfree(tr_folder);
}

void FreeTranspostIconsList()
{
  while(til_top)
  {
    TransportIconsList * til = til_top;
    til_top = til_top->next;
    mfree(til);
  }
}

/*
  Добавить в путь к иконке папку с иконками транспорта.
  Имя папки берем из жида контакта транспорта (xxxx@icq.jabber.ru -> icq)
*/
void GetTransportIconsPath(char * path_to_pic, TRESOURCE * resEx)
{
  int len = NULL; // Длина имени транспорта
  char * tr_name = NULL; // Имя транспорта
  TransportIconsList * til = til_top;
  if (!til) return;
  if(resEx->entry_type == T_TRANSPORT) // Сам транспорт
  {
    while(resEx->full_name[len] != '.') // Пока не дошли до точки
      len ++;
    tr_name = malloc(len + 1);
    strncpy(tr_name, resEx->full_name, len); // Копируем имя транспорта
    tr_name[len] = NULL;
  }
  else
  {
    char * tmp = strrchr(resEx->full_name, '@'); // Контакт из транспорта
    if (tmp)
    {
      while(tmp[len + 1] != '.')
        len ++;
      tr_name = malloc(len + 1);
      strncpy(tr_name, tmp + 1, len);
      tr_name[len] = NULL;
    }
  }
  if (!tr_name) return; // Наш контакт не является транспортом. Закрываем лавочку ;)
  while(til) // Ищем в списке нашу папку
  {
    if (!stricmp(til->name, tr_name)) // Нашли!
    {
      strcat(path_to_pic, transports_img_folder); // Добавляем папку "transports" в путь к иконке
      strcat(path_to_pic, til->name); // Добавляем нашу папку в путь к иконке
      strcat(path_to_pic, "\\");
      break;
    }
    til = til->next;
  }
  mfree(tr_name);
}
