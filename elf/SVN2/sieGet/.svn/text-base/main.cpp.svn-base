#include "include.h"
#include "daemon.h"
#include "conf_loader.h"

extern const char * successed_config_filename;

SieGetDaemon * daemon;

#ifdef NEWSGOLD
#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short* num);

void addIconBar(short* num)
{
  if(CFG_SHOW_TRAY_ICON) AddIconToIconBar(daemon->DL_Handler->IsAnyDownloadActive()?TRAY_ICON_ON:TRAY_ICON_OFF,num);
}
#endif

int main(char * exename, char * filename)
{
  InitConfig();
  daemon = new SieGetDaemon();
  daemon->Create();
  return 0;
}
