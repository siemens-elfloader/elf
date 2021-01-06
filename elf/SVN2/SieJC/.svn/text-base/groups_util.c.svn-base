#include "../inc/swilib.h"
#include "main.h"
#include "serial_dbg.h"
#include "groups_util.h"

GR_ITEM *GR_ROOT = NULL;

// Инициализация групп
void InitGroupsList()
{
  const char no_group_t[]="No group";
  GR_ITEM *g_ex = malloc(sizeof(GR_ITEM));
  g_ex->name = malloc(strlen(no_group_t)+1);
  strcpy(g_ex->name, no_group_t);
  g_ex->next = NULL;
  GR_ROOT = g_ex;
}

// Уничтожить список групп
void KillGroupsList()
{
  LockSched();
  GR_ITEM* cl=GR_ROOT;
  GR_ROOT=NULL;
  while(cl)
  {
    GR_ITEM *p;
    mfree(cl->name);
    p=cl;
    cl=(GR_ITEM*)(cl->next);
    mfree(p);
    p=NULL;
  }
  UnlockSched();
}

// Добавляем группу в список
int AddGroup(char *gr_name)
{
  if(!gr_name)return 0;
  // Создаем структуру
  GR_ITEM *g_ex = malloc(sizeof(GR_ITEM));
  g_ex->name = malloc(strlen(gr_name)+1);
  strcpy(g_ex->name, gr_name);
  g_ex->next = NULL;

  // Добавляем структуру в список
  // Нет проверки на пустую голову, ибо это заведомо не так
  int i=0;
  // Ищем последний элемент списка, добавляем
  GR_ITEM *tmp = GR_ROOT;
  while(tmp->next){tmp=tmp->next;i++;}
  tmp->next = g_ex;
  return ++i;
}

// Возвращает ID группы с именем gr_name или 0, если такой нет
int GetGroupID(char *gr_name)
{
  if(!GR_ROOT)return 0;
  if(!gr_name)return 0;
  GR_ITEM *tmp = GR_ROOT;
  int i=0;
  while(tmp)
  {
    if(!strcmp(tmp->name, gr_name))return i;
    tmp=tmp->next;
    i++;
  }
  return 0; // не найдено
}

// Возвращает имя группы с ID = gr_id или NULL, если такой нет
char* GetGroupNameByID(int gr_id)
{
  if(!GR_ROOT)return NULL;
  GR_ITEM *tmp = GR_ROOT;
  int i=0;
  while(tmp)
  {
    if(i==gr_id)return tmp->name;
    tmp=tmp->next;
    i++;
  }
  return NULL; // не найдено
}

// Возвращает группу с ID = gr_id или NULL, если такой нет
GR_ITEM* GetGroupByID(int gr_id)
{
  if(!GR_ROOT)return NULL;
  GR_ITEM *tmp = GR_ROOT;
  int i=0;
  while(tmp)
  {
    if(i==gr_id)return tmp;
    tmp=tmp->next;
    i++;
  }
  return NULL; // не найдено
}

//Возвращает количество групп
int GetGroupCount(void)
{
  int i=0;
  // Ищем последний элемент списка, добавляем
  GR_ITEM *tmp = GR_ROOT;
  while(tmp->next){tmp=tmp->next;i++;}
  return i;
}
//EOL,EOF
