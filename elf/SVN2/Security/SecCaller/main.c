#include "..\..\inc\swilib.h"

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

extern void call_sec();

int main(char *exename, char *fname)
{
	call_sec();	
	Killer();
	return 0;
}


/*
Self numbers:
A88BECA6
A88C12D6
A88C3E86

*/

