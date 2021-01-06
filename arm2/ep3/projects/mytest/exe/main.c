#include "..\inc\swilib.h"
#include "tbase_work\tbase.h"

static void Killer(void)
{  
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

/*

Патчи для CX75v25


*/

int main()
{
  
   SetTBaseAddress((int *)TBASE_ADDRESS);
   

   //Шуточный разгон до 133 МГц
   //08EE928: 68 85
   int a = ApplyPatch((void *)0xA08EE928, 133);
   
   //Неотрисовка SCROLL Текста
   //089A59E: C046C046
   ApplyPatch((void *)((int)0xA089A59E+0), 0xC0);
   ApplyPatch((void *)((int)0xA089A59E+1), 0x46);
   ApplyPatch((void *)((int)0xA089A59E+2), 0xC0);
   ApplyPatch((void *)((int)0xA089A59E+3), 0x46);
   

  
   ShowMSG(1, (int)"PATCHED!");
   SUBPROC((void *)Killer);
   
  return 0;
}
