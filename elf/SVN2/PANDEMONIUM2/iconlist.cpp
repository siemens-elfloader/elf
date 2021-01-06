#define TIconName_icons
#include "include.h"

typedef char TIconName[128];

TIconName icons[8];


void LoadIcons(char * base)
{
for(int i=0;i<7;i++)
  sprintf(icons[i],"%s%c%c%s.png",base,i&MODE_ENABLED_NEW?'E':'D',i&MODE_ENABLED_OLD?'E':'D',i&MODE_UPDATEABLE?"G":"");
};

