#include <string.h>
#include "password.h"

char *XORPassword(const char *dest)
{
char *ret=new char(strlen(dest));
for(unsigned int n=0;n<strlen(dest);n++) 
ret[n] = dest[n] ^ szXORTable[n];
return ret;
}
