//tbase.с - Работа с базой трансляции для применения виртуальных патчей
//(C)Dimadze

#include "..\..\inc\swilib.h"
#include "tbase.h"



int *trans_base = 0;
int  fiq_irq_value = 0;

void SetTBaseAddress(int *tbase)
{
 trans_base = tbase;
}

void LockOSAction()
{
 LockSched();
 fiq_irq_value = DisableINT();
}

void UnLockOSAction()
{
 EnableINT(fiq_irq_value);
 UnlockSched();
}

char GetByteFromAddress(void *addr)
{
 return *((char *)addr);
}



int ApplyPatch(void *addr, char new_byte)
{
 //Проверка на соответсвие адреса патча с адресами flash
 if (((int)addr >= 0xA0000000) && ((int)addr < 0xA4000000) && trans_base)
 {
  unsigned short element = ((int)addr>>0x14)&0xFFF;
  
  //Если элемент таблицы первого уровня стандартный
  if (((trans_base[element])&0xFF) == 0x1E)
   {
    //Разбиваем секцию в 1 МБ на грубую таблицу из 256 страниц по 4 КБ
     
    //Захват памяти и получение адреса секции
    char *addr_section = (char *)(((int)addr)&0xFFF00000);
    int *coarse_table = (int *)malloc(0x100*4+0xFFF+4);
    
    //Выравниваем адрес
    int *coarse_table_a = (int *)(((int)coarse_table + 0xFFF)&0xFFFFF000);
    
    //Непосредственно сама разбивка
    for (int i = 0; i < 0x100; i++) coarse_table_a[i] = (int)addr_section + 0x1000*i + 0x0E;
    
    //Сохраняем невыравненный адрес таблицы последним элементом
    coarse_table_a[0x100] = (int)coarse_table;
    
    //Захват памяти и получение адреса страницы
    unsigned short subelement = ((int)addr>>0x0C)&0xFF;
    char *addr_page = (char *)((coarse_table_a[subelement])&0xFFFFF000);
    char *rampage = (char *)malloc(0x1000 + 0xFFF + 4);
    
    //Выравниваем адрес и копируем туда содержимое flash-страницы
    char *rampage_a = (char *)(((int)rampage + 0xFFF)&0xFFFFF000);
    memcpy(rampage_a, addr_page, 0x1000);
    
    //Сохраняем невыравненный адрес страницы
    int *rampage_int = (int *)rampage_a;
    rampage_int[0x1000] = (int)rampage;
    
    //Получение адреса в странице и сам патчинг 
    short patch_byte =  ((int)addr)&0xFFF;
    rampage_a[patch_byte] = new_byte;
    
    LockOSAction();
    
    //Требования с кешем
    ExecuteIMB();
    
    //Добавление к таблице первого и второго уровней
    coarse_table_a[subelement] = (int)rampage_a + 0x0E;
    trans_base[element] = (int)coarse_table_a + 0x11;
    
    UnLockOSAction();

    return 1;
   }
    //Если уже разбит на страницы
    else
     {
      //Получение адреса таблицы второго уровня и адрес ячейки
      int *coarse_table = (int *)(((int)trans_base[element])&0xFFFFF000);
      unsigned short subelement = ((int)addr>>0x0C)&0xFF;
      char stat_page = (coarse_table[subelement]&0x0F000000)>>0x18;
      
      //Если flash страница не в RAM
      if ((stat_page > 0x00 && stat_page < 0x04) || stat_page == 0x00)
       {
        //Захват памяти и получение адреса страницы
        char *addr_page = (char *)((coarse_table[subelement])&0xFFFFF000);
        char *rampage = (char *)malloc(0x1000 + 0xFFF + 4);
    
        //Выравниваем адрес и копируем туда содержимое flash-страницы
        char *rampage_a = (char *)(((int)rampage + 0xFFF)&0xFFFFF000);
        memcpy(rampage_a, addr_page, 0x1000);
       
        //Сохраняем невыравненный адрес страницы
        int *rampage_int = (int *)rampage_a;
        rampage_int[0x1000] = (int)rampage;
    
        //Получение адреса в странице и сам патчинг 
        short patch_byte =  ((int)addr)&0xFFF;
        rampage_a[patch_byte] = new_byte;
        
        LockOSAction();
        
        //Требования с кешем
        ExecuteIMB();
        //Добавление к таблице второго уровня
        coarse_table[subelement] = (int)rampage_a + 0x0E;
        
        UnLockOSAction();
        
        return 1;
       }
      
       //Если flash страница в RAM
       else
         {
          //Получение адреса страницы
          char *rampage = (char *)((coarse_table[subelement])&0xFFFFF000);
          
          LockOSAction();
          
          //Требования с кешем
          ExecuteIMB();
          
          //Разблокировка доступа на запись
          coarse_table[element] = coarse_table[element]|0xFF0;
          
          //Получение адреса в странице и сам патчинг 
          short patch_byte =  ((int)addr)&0xFFF;
          rampage[patch_byte] = new_byte;
          
          //Блокировка доступа на запись
          coarse_table[subelement] = (int)rampage + 0x0E;
          
          UnLockOSAction();

          return 1;
         }
      
     }
 }
  else return 0;
}

int UndoPatch(void *addr, char old_byte)
{
 
}

