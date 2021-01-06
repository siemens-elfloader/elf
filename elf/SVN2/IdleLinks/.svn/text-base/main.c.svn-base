#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "nsd.h"
#include "conf_ex.h"

extern void kill_data(void *p,void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int main(void)
{
  if (CreatePathToBcfgs() == 1) // Если есть (или  создалась) подпапка в etc
  {
    InitConfig(); // Загружаем основной конфиг
    LoadBcfgs(); // Загружаем конфиги с ярлычками
    NSD_Create(); // Пускаем NSD демона
  }
  else
  {
    ShowMSG(1, (int)"Error creating '?:\\Zbin\\etc\\IdleLinks' folder!"); // Нецнзурно материмся
  }
  return 0;
}
