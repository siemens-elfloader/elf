/*
    SieNatJabber Project
    Функции работы работы с группами контактов

    Добавление групп в список, получение имени по ID и обратно
*/

#ifndef _GROUPS_UTIL_H_
  #define _GROUPS_UTIL_H_

typedef struct
{
  char *name;
  void *next;
}GR_ITEM;

// Инициализация списка
void InitGroupsList();

// Добавляем группу в список. Возвращает номер созданной группы начиная с 1
int AddGroup(char *gr_name);

// Уничтожить список групп. Необходимо вызвать в конце работы
void KillGroupsList();

// Возвращает ID группы с именем gr_name или 0, если такой нет
int GetGroupID(char *gr_name);

// Возвращает группу с ID = gr_id или NULL, если такой нет
GR_ITEM* GetGroupByID(int gr_id);

// Возвращает имя группы с ID = gr_id или NULL, если такой нет
char* GetGroupNameByID(int gr_id);
#endif
