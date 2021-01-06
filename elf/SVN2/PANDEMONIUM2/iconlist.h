#ifndef __iconlist
#define __iconlist


#include "include.h"

typedef char TIconName[128];

#ifndef TIconName_icons
extern TIconName icons[8];
#endif

void LoadIcons(char * base);


#endif
