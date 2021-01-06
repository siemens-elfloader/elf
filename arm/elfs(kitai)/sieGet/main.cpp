#include "include.h"
#include "daemon.h"
#include "conf_loader.h"

extern const char * successed_config_filename;

int main(char * exename, char * filename)
{
  InitConfig();
  SieGetDaemon * daemon = new SieGetDaemon();
  daemon->Create();
  return 0;
}
