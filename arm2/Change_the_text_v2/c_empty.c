#include "c:\arm\inc\swilib.h"


__arm char IsDisabledIconBar() 
{ 
/*#ifdef EL71 
return *(char*)( (*(int*)0xA8E94D88) + 0x18 ); 
#else //E71 8*/
return *(char*)( (*(int*)0xA8E9509C) + 0x18 ); 
}
